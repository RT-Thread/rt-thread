/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
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
 * @file n32wb452.h
 * @author Nations
 * @version v1.0.3
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#ifndef __N32WB452_H__
#define __N32WB452_H__

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup N32WB452_Library_Basic
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
#define HSE_STARTUP_TIMEOUT ((uint16_t)0x8000) /*!< Time out for HSE start up */

#define HSI_VALUE (8000000) /*!< Value of the Internal oscillator in Hz*/

#define __N32WB452_STDPERIPH_VERSION_MAIN (0x00) /*!< [31:24] main version */
#define __N32WB452_STDPERIPH_VERSION_SUB1 (0x04) /*!< [23:16] sub1 version */
#define __N32WB452_STDPERIPH_VERSION_SUB2 (0x00) /*!< [15:8]  sub2 version */
#define __N32WB452_STDPERIPH_VERSION_RC   (0x00) /*!< [7:0]  release candidate */

/**
 * @brief N32WB452 Standard Peripheral Library version number
 */
#define __N32WB452_STDPERIPH_VERSION                                                                                    \
    ((__N32WB452_STDPERIPH_VERSION_MAIN << 24) | (__N32WB452_STDPERIPH_VERSION_SUB1 << 16)                               \
     | (__N32WB452_STDPERIPH_VERSION_SUB2 << 8) | (__N32WB452_STDPERIPH_VERSION_RC))

/*
 * Configuration of the Cortex-M4 Processor and Core Peripherals
 */
#ifdef N32WB452
#define __MPU_PRESENT 1          /*!< N32WB452 devices does not provide an MPU */
#define __FPU_PRESENT 1          /*!< FPU present                            */
#endif                           /* N32WB452 */
#define __NVIC_PRIO_BITS       4 /*!< N32WB452 uses 4 Bits for the Priority Levels    */
#define __Vendor_SysTickConfig 0 /*!< Set to 1 if different SysTick Config is used */

/**
 * @brief N32WB452 Interrupt Number Definition
 */
typedef enum IRQn
{
    /******  Cortex-M4 Processor Exceptions Numbers ***************************************************/
    NonMaskableInt_IRQn   = -14, /*!< 2 Non Maskable Interrupt                             */
    HardFault_IRQn        = -13, /*!< 3 Hard Fault Interrupt                               */
    MemoryManagement_IRQn = -12, /*!< 4 Cortex-M4 Memory Management Interrupt              */
    BusFault_IRQn         = -11, /*!< 5 Cortex-M4 Bus Fault Interrupt                      */
    UsageFault_IRQn       = -10, /*!< 6 Cortex-M4 Usage Fault Interrupt                    */
    SVCall_IRQn           = -5,  /*!< 11 Cortex-M4 SV Call Interrupt                       */
    DebugMonitor_IRQn     = -4,  /*!< 12 Cortex-M4 Debug Monitor Interrupt                 */
    PendSV_IRQn           = -2,  /*!< 14 Cortex-M4 Pend SV Interrupt                       */
    SysTick_IRQn          = -1,  /*!< 15 Cortex-M4 System Tick Interrupt                   */

    /******  N32WB452 specific Interrupt Numbers ********************************************************/
    WWDG_IRQn          = 0,  /*!< Window WatchDog Interrupt                            */
    PVD_IRQn           = 1,  /*!< PVD through EXTI Line detection Interrupt            */
    TAMPER_IRQn        = 2,  /*!< Tamper Interrupt                                     */
    RTC_IRQn           = 3,  /*!< RTC global Interrupt                                 */
    FLASH_IRQn         = 4,  /*!< FLASH global Interrupt                               */
    RCC_IRQn           = 5,  /*!< RCC global Interrupt                                 */
    EXTI0_IRQn         = 6,  /*!< EXTI Line0 Interrupt                                 */
    EXTI1_IRQn         = 7,  /*!< EXTI Line1 Interrupt                                 */
    EXTI2_IRQn         = 8,  /*!< EXTI Line2 Interrupt                                 */
    EXTI3_IRQn         = 9,  /*!< EXTI Line3 Interrupt                                 */
    EXTI4_IRQn         = 10, /*!< EXTI Line4 Interrupt                                 */
    DMA1_Channel1_IRQn = 11, /*!< DMA1 Channel 1 global Interrupt                      */
    DMA1_Channel2_IRQn = 12, /*!< DMA1 Channel 2 global Interrupt                      */
    DMA1_Channel3_IRQn = 13, /*!< DMA1 Channel 3 global Interrupt                      */
    DMA1_Channel4_IRQn = 14, /*!< DMA1 Channel 4 global Interrupt                      */
    DMA1_Channel5_IRQn = 15, /*!< DMA1 Channel 5 global Interrupt                      */
    DMA1_Channel6_IRQn = 16, /*!< DMA1 Channel 6 global Interrupt                      */
    DMA1_Channel7_IRQn = 17, /*!< DMA1 Channel 7 global Interrupt                      */

    ADC1_2_IRQn          = 18, /*!< ADC1 and ADC2 global Interrupt                       */
    USB_HP_CAN1_TX_IRQn  = 19, /*!< USB Device High Priority or CAN1 TX Interrupts       */
    USB_LP_CAN1_RX0_IRQn = 20, /*!< USB Device Low Priority or CAN1 RX0 Interrupts       */
    CAN1_RX1_IRQn        = 21, /*!< CAN1 RX1 Interrupt                                   */
    CAN1_SCE_IRQn        = 22, /*!< CAN1 SCE Interrupt                                   */
    EXTI9_5_IRQn         = 23, /*!< External Line[9:5] Interrupts                        */
    TIM1_BRK_IRQn        = 24, /*!< TIM1 Break Interrupt                                 */
    TIM1_UP_IRQn         = 25, /*!< TIM1 Update Interrupt                                */
    TIM1_TRG_COM_IRQn    = 26, /*!< TIM1 Trigger and Commutation Interrupt               */
    TIM1_CC_IRQn         = 27, /*!< TIM1 Capture Compare Interrupt                       */
    TIM2_IRQn            = 28, /*!< TIM2 global Interrupt                                */
    TIM3_IRQn            = 29, /*!< TIM3 global Interrupt                                */
    TIM4_IRQn            = 30, /*!< TIM4 global Interrupt                                */
    I2C1_EV_IRQn         = 31, /*!< I2C1 Event Interrupt                                 */
    I2C1_ER_IRQn         = 32, /*!< I2C1 Error Interrupt                                 */
    I2C2_EV_IRQn         = 33, /*!< I2C2 Event Interrupt                                 */
    I2C2_ER_IRQn         = 34, /*!< I2C2 Error Interrupt                                 */
    SPI1_IRQn            = 35, /*!< SPI1 global Interrupt                                */
    SPI2_IRQn            = 36, /*!< SPI2 global Interrupt                                */
    USART1_IRQn          = 37, /*!< USART1 global Interrupt                              */
    USART2_IRQn          = 38, /*!< USART2 global Interrupt                              */
    USART3_IRQn          = 39, /*!< USART3 global Interrupt                              */
    EXTI15_10_IRQn       = 40, /*!< External Line[15:10] Interrupts                      */
    RTCAlarm_IRQn        = 41, /*!< RTC Alarm through EXTI Line Interrupt                */
    USBWakeUp_IRQn       = 42, /*!< USB Device WakeUp from suspend through EXTI Line Interrupt */
    TIM8_BRK_IRQn        = 43, /*!< TIM8 Break Interrupt                                 */
    TIM8_UP_IRQn         = 44, /*!< TIM8 Update Interrupt                                */
    TIM8_TRG_COM_IRQn    = 45, /*!< TIM8 Trigger and Commutation Interrupt               */
    TIM8_CC_IRQn         = 46, /*!< TIM8 Capture Compare Interrupt                       */
    RESERVE47_IRQn       = 47, /*!< RESERVE47 Interrupt                                  */
    RESERVE48_IRQn       = 48, /*!< RESERVE48 Interrupt                                  */
    SDIO_IRQn            = 49, /*!< SDIO global Interrupt                                */
    TIM5_IRQn            = 50, /*!< TIM5 global Interrupt                                */
    SPI3_IRQn            = 51, /*!< SPI3 global Interrupt                                */
    UART4_IRQn           = 52, /*!< UART4 global Interrupt                               */
    UART5_IRQn           = 53, /*!< UART5 global Interrupt                               */
    TIM6_IRQn            = 54, /*!< TIM6 global Interrupt                                */
    TIM7_IRQn            = 55, /*!< TIM7 global Interrupt                                */
    DMA2_Channel1_IRQn   = 56, /*!< DMA2 Channel 1 global Interrupt                      */
    DMA2_Channel2_IRQn   = 57, /*!< DMA2 Channel 2 global Interrupt                      */
    DMA2_Channel3_IRQn   = 58, /*!< DMA2 Channel 3 global Interrupt                      */
    DMA2_Channel4_IRQn   = 59, /*!< DMA2 Channel 4 global Interrupt                      */
    DMA2_Channel5_IRQn   = 60, /*!< DMA2 Channel 5 global Interrupt                      */
    RESERVE61_IRQn       = 61, /*!< RESERVE61 global Interrupt                           */
    RESERVE62_IRQn       = 62, /*!< RESERVE62  interrupt                                 */
    CAN2_TX_IRQn         = 63, /*!< CAN2 TX Interrupt                                    */
    CAN2_RX0_IRQn        = 64, /*!< CAN2 RX0 Interrupt                                   */
    CAN2_RX1_IRQn        = 65, /*!< CAN2 RX1 Interrupt                                   */
    CAN2_SCE_IRQn        = 66, /*!< CAN2 SCE Interrupt                                   */
    RESERVE67_IRQn       = 67, /*!< RESERVE67 Interrupt                                  */
    DMA2_Channel6_IRQn   = 68, /*!< DMA2 Channel 6 global Interrupt                      */
    DMA2_Channel7_IRQn   = 69, /*!< DMA2 Channel 7 global Interrupt                      */
    I2C3_EV_IRQn         = 70, /*!< I2C3 Event Interrupt                                 */
    I2C3_ER_IRQn         = 71, /*!< I2C3 Error Interrupt                                 */
    I2C4_EV_IRQn         = 72, /*!< I2C4 Event Interrupt                                 */
    I2C4_ER_IRQn         = 73, /*!< I2C4 Error Interrupt                                 */
    UART6_IRQn           = 74, /*!< UART6 global Interrupt                               */
    UART7_IRQn           = 75, /*!< UART7 global Interrupt                               */
    DMA1_Channel8_IRQn   = 76, /*!< DMA1 Channel 8 global Interrupt                      */
    DMA2_Channel8_IRQn   = 77, /*!< DMA2 Channel 8 global Interrupt                      */
    DVP_IRQn             = 78, /*!< DVP global Interrupt                                 */
    SAC_IRQn             = 79, /*!< SAC global Interrupt                                 */
    MMU_IRQn             = 80, /*!< MMU global Interrupt                                 */
    TSC_IRQn             = 81, /*!< TSC global Interrupt                                 */
    RESERVE82_IRQn       = 82, /*!< COMP1 & COMP2 & COMP3 global Interrupt               */
    RESERVE83_IRQn       = 83, /*!< COMP4 & COMP5 & COMP6 global Interrupt               */
    RESERVE84_IRQn       = 84  /*!< COMP7 global Interrupt                               */

} IRQn_Type;

#include "core_cm4.h"
#include "system_n32wb452.h"
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

/* N32WB452 Standard Peripheral Library old definitions (maintained for legacy purpose) */
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
    uint32_t RESERVED0;
    __IO uint32_t TESTR0;
    __IO uint32_t TESTR1;
} AFEC_Module;

/**
 * @brief Backup Registers
 */

typedef struct
{
    uint32_t RESERVED0;
    __IO uint16_t DAT1;
    uint16_t RESERVED1;
    __IO uint16_t DAT2;
    uint16_t RESERVED2;
    __IO uint16_t DAT3;
    uint16_t RESERVED3;
    __IO uint16_t DAT4;
    uint16_t RESERVED4;
    __IO uint16_t DAT5;
    uint16_t RESERVED5;
    __IO uint16_t DAT6;
    uint16_t RESERVED6;
    __IO uint16_t DAT7;
    uint16_t RESERVED7;
    __IO uint16_t DAT8;
    uint16_t RESERVED8;
    __IO uint16_t DAT9;
    uint16_t RESERVED9;
    __IO uint16_t DAT10;
    uint16_t RESERVED10;
    __IO uint16_t RESERVED;
    uint16_t RESERVED11;
    __IO uint16_t CTRL;
    uint16_t RESERVED12;
    __IO uint16_t CTRLSTS;
    uint16_t RESERVED13[5];
    __IO uint16_t DAT11;
    uint16_t RESERVED14;
    __IO uint16_t DAT12;
    uint16_t RESERVED15;
    __IO uint16_t DAT13;
    uint16_t RESERVED16;
    __IO uint16_t DAT14;
    uint16_t RESERVED17;
    __IO uint16_t DAT15;
    uint16_t RESERVED18;
    __IO uint16_t DAT16;
    uint16_t RESERVED19;
    __IO uint16_t DAT17;
    uint16_t RESERVED20;
    __IO uint16_t DAT18;
    uint16_t RESERVED21;
    __IO uint16_t DAT19;
    uint16_t RESERVED22;
    __IO uint16_t DAT20;
    uint16_t RESERVED23;
    __IO uint16_t DAT21;
    uint16_t RESERVED24;
    __IO uint16_t DAT22;
    uint16_t RESERVED25;
    __IO uint16_t DAT23;
    uint16_t RESERVED26;
    __IO uint16_t DAT24;
    uint16_t RESERVED27;
    __IO uint16_t DAT25;
    uint16_t RESERVED28;
    __IO uint16_t DAT26;
    uint16_t RESERVED29;
    __IO uint16_t DAT27;
    uint16_t RESERVED30;
    __IO uint16_t DAT28;
    uint16_t RESERVED31;
    __IO uint16_t DAT29;
    uint16_t RESERVED32;
    __IO uint16_t DAT30;
    uint16_t RESERVED33;
    __IO uint16_t DAT31;
    uint16_t RESERVED34;
    __IO uint16_t DAT32;
    uint16_t RESERVED35;
    __IO uint16_t DAT33;
    uint16_t RESERVED36;
    __IO uint16_t DAT34;
    uint16_t RESERVED37;
    __IO uint16_t DAT35;
    uint16_t RESERVED38;
    __IO uint16_t DAT36;
    uint16_t RESERVED39;
    __IO uint16_t DAT37;
    uint16_t RESERVED40;
    __IO uint16_t DAT38;
    uint16_t RESERVED41;
    __IO uint16_t DAT39;
    uint16_t RESERVED42;
    __IO uint16_t DAT40;
    uint16_t RESERVED43;
    __IO uint16_t DAT41;
    uint16_t RESERVED44;
    __IO uint16_t DAT42;
    uint16_t RESERVED45;
} BKP_Module;

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
    __IO uint32_t DR12CH1;
    __IO uint32_t DL12CH1;
    __IO uint32_t DR8CH1;
    __IO uint32_t DR12CH2;
    __IO uint32_t DL12CH2;
    __IO uint32_t DR8CH2;
    __IO uint32_t DR12DCH;
    __IO uint32_t DL12DCH;
    __IO uint32_t DR8DCH;
    __IO uint32_t DATO1;
    __IO uint32_t DATO2;
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
    __IO uint32_t CHMAPEN;
} DMA_Module;

/**
 * @brief External Interrupt/Event Controller
 */

typedef struct
{
    __IO uint32_t IMASK;
    __IO uint32_t EMASK;
    __IO uint32_t RT_CFG;
    __IO uint32_t FT_CFG;
    __IO uint32_t SWIE;
    __IO uint32_t PEND;
    __IO uint32_t TSSEL;
} EXTI_Module;

/**
 * @brief FLASH Registers
 */

typedef struct
{
    __IO uint32_t AC;
    __IO uint32_t KEY;
    __IO uint32_t OPTKEY;
    __IO uint32_t STS;
    __IO uint32_t CTRL;
    __IO uint32_t ADD;
    __IO uint32_t RESERVED0;
    __IO uint32_t OBR;
    __IO uint32_t WRP;
    __IO uint32_t RESERVED1;
    __IO uint32_t RESERVED2;
    __IO uint32_t RDN;
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
    __IO uint32_t RDP2;
} OB_Module;

/**
 * @brief General Purpose I/O
 */

typedef struct
{
    __IO uint32_t PL_CFG;
    __IO uint32_t PH_CFG;
    __IO uint32_t PID;
    __IO uint32_t POD;
    __IO uint32_t PBSC;
    __IO uint32_t PBC;
    __IO uint32_t PLOCK_CFG;
    uint32_t RESERVED0;
    __IO uint32_t DS_CFG;
    __IO uint32_t SR_CFG;
} GPIO_Module;

/**
 * @brief Alternate Function I/O
 */

typedef struct
{
    __IO uint32_t ECTRL;
    __IO uint32_t RMP_CFG;
    __IO uint32_t EXTI_CFG[4];
    uint32_t RESERVED0;
    uint32_t RESERVED1;
    __IO uint32_t RMP_CFG3;
    __IO uint32_t RMP_CFG4;
    __IO uint32_t RMP_CFG5;
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
    __IO uint32_t CTRL;
    __IO uint32_t CTRLSTS;
    __IO uint32_t CTRL2;
    __IO uint32_t CTRL3;
} PWR_Module;

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
    __IO uint32_t BDCTRL;
    __IO uint32_t CTRLSTS;

    __IO uint32_t AHBPRST;
    __IO uint32_t CFG2;
    __IO uint32_t CFG3;
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
    uint32_t reserved6;        /*!< RTC tamper configuration register,                    Address offset: 0x40 */
    __IO uint32_t ALRMASS;     /*!< RTC alarm A sub second register,                           Address offset: 0x44 */
    __IO uint32_t ALRMBSS;     /*!< RTC alarm B sub second register,                           Address offset: 0x48 */
    __IO uint32_t OPT;         /*!< RTC option register,                                       Address offset: 0x4C */
    uint32_t reserved1;        /*!< Reserved                                                  Address offset: 0x50 */
    uint32_t reserved2;        /*!< Reserved                                                  Address offset: 0x54 */
    uint32_t reserved3;        /*!< Reserved                                                  Address offset: 0x58 */
    uint32_t reserved4;        /*!< Reserved                                                  Address offset: 0x5C */
    uint32_t reserved5;        /*!< Reserved                                                  Address offset: 0x60 */
    __IO uint32_t TSCWKUPCTRL; /*!< RTC backup register 5,                                     Address offset: 0x64 */
    __IO uint32_t TSCWKUPCNT;  /*!< RTC backup register 6,                                     Address offset: 0x68 */
} RTC_Module;

/**
 * @brief SD host Interface
 */

typedef struct
{
    __IO uint32_t PWRCTRL;
    __IO uint32_t CLKCTRL;
    __IO uint32_t CMDARG;
    __IO uint32_t CMDCTRL;
    __I uint32_t CMDRESP;
    __I uint32_t RESPONSE1;
    __I uint32_t RESPONSE2;
    __I uint32_t RESPONSE3;
    __I uint32_t RESPONSE4;
    __IO uint32_t DTIMER;
    __IO uint32_t DATLEN;
    __IO uint32_t DATCTRL;
    __I uint32_t DATCOUNT;
    __I uint32_t STS;
    __IO uint32_t INTCLR;
    __IO uint32_t INTEN;
    uint32_t RESERVED0[2];
    __I uint32_t FIFOCOUNT;
    uint32_t RESERVED1[13];
    __IO uint32_t DATFIFO;
} SDIO_Module;

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
 * @brief Window WATCHDOG
 */

typedef struct
{
    __IO uint32_t CTRL;
    __IO uint32_t CFG;
    __IO uint32_t STS;
} WWDG_Module;

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
    __IO uint32_t RESR0;
    __IO uint32_t RESR1;
    __IO uint32_t RESR2;
    __IO uint32_t THRHD0;
    __IO uint32_t THRHD1;
    __IO uint32_t THRHD2;
    __IO uint32_t THRHD3;
    __IO uint32_t THRHD4;
    __IO uint32_t THRHD5;
    __IO uint32_t THRHD6;
    __IO uint32_t THRHD7;
    __IO uint32_t THRHD8;
    __IO uint32_t THRHD9;
    __IO uint32_t THRHD10;
    __IO uint32_t THRHD11;
    __IO uint32_t THRHD12;
    __IO uint32_t THRHD13;
    __IO uint32_t THRHD14;
    __IO uint32_t THRHD15;
    __IO uint32_t THRHD16;
    __IO uint32_t THRHD17;
    __IO uint32_t THRHD18;
    __IO uint32_t THRHD19;
    __IO uint32_t THRHD20;
    __IO uint32_t THRHD21;
    __IO uint32_t THRHD22;
    __IO uint32_t THRHD23;
} TSC_Module;

/**
 * @brief DVP
 */
typedef struct
{
    __IO uint32_t CTRL;    /*!< DVP control register*/
    __IO uint32_t STS;     /*!< DVP status register*/
    __IO uint32_t INTSTS;  /*!< DVP interrupt status register*/
    __IO uint32_t INTEN;   /*!< DVP interrupt enable register*/
    __IO uint32_t MINTSTS; /*!< DVP interrupt mask status register */
    __IO uint32_t WST;     /*!< DVP start register */
    __IO uint32_t WSIZE;   /*!< DVP size register */
    __IO uint32_t FIFO;    /*!< DVP FIFO register */
} DVP_Module;

#define FLASH_BASE  ((uint32_t)0x08000000) /*!< FLASH base address in the alias region */
#define SRAM_BASE   ((uint32_t)0x20000000) /*!< SRAM base address in the alias region */
#define PERIPH_BASE ((uint32_t)0x40000000) /*!< Peripheral base address in the alias region */

#define SRAM_BB_BASE   ((uint32_t)0x22000000) /*!< SRAM base address in the bit-band region */
#define PERIPH_BB_BASE ((uint32_t)0x42000000) /*!< Peripheral base address in the bit-band region */

#define UCID_BASE           ((uint32_t)0x1FFFF7C0) /*!< UCID Address : 0x1FFF_F7C0 */
#define UCID_LENGTH         ((uint32_t)0x10)       /*!< UCID Length  : 16Bytes */
#define UID_BASE            ((uint32_t)0x1FFFF7F0) /*!< UID Address  : 0x1FFF_F7F0 */
#define UID_LENGTH          ((uint32_t)0x0C)       /*!< UID Length   : 12Bytes */
#define DBGMCU_ID_BASE      ((uint32_t)0xE0042000) /*!< DBGMCU_ID Address */
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
#define RTC_BASE           (APB1PERIPH_BASE + 0x2800)
#define WWDG_BASE          (APB1PERIPH_BASE + 0x2C00)
#define IWDG_BASE          (APB1PERIPH_BASE + 0x3000)
#define TSC_BASE           (APB1PERIPH_BASE + 0x3400)
#define SPI2_BASE          (APB1PERIPH_BASE + 0x3800)
#define SPI3_BASE          (APB1PERIPH_BASE + 0x3C00)
#define USART2_BASE        (APB1PERIPH_BASE + 0x4400)
#define USART3_BASE        (APB1PERIPH_BASE + 0x4800)
#define UART4_BASE         (APB1PERIPH_BASE + 0x4C00)
#define UART5_BASE         (APB1PERIPH_BASE + 0x5000)
#define I2C1_BASE          (APB1PERIPH_BASE + 0x5400)
#define I2C2_BASE          (APB1PERIPH_BASE + 0x5800)
#define USB_BASE           (APB1PERIPH_BASE + 0x5C00)
#define USB_CAN1_SRAM_BASE (APB1PERIPH_BASE + 0x6000)
#define CAN1_BASE          (APB1PERIPH_BASE + 0x6400)
#define CAN2_BASE          (APB1PERIPH_BASE + 0x6800)
#define BKP_BASE           (APB1PERIPH_BASE + 0x6C00)
#define PWR_BASE           (APB1PERIPH_BASE + 0x7000)
#define DAC_BASE           (APB1PERIPH_BASE + 0x7400)

/* APB2 */
#define AFIO_BASE   (APB2PERIPH_BASE + 0x0000)
#define EXTI_BASE   (APB2PERIPH_BASE + 0x0400)
#define GPIOA_BASE  (APB2PERIPH_BASE + 0x0800)
#define GPIOB_BASE  (APB2PERIPH_BASE + 0x0C00)
#define GPIOC_BASE  (APB2PERIPH_BASE + 0x1000)
#define GPIOD_BASE  (APB2PERIPH_BASE + 0x1400)
#define GPIOE_BASE  (APB2PERIPH_BASE + 0x1800)
#define TIM1_BASE   (APB2PERIPH_BASE + 0x2C00)
#define SPI1_BASE   (APB2PERIPH_BASE + 0x3000)
#define TIM8_BASE   (APB2PERIPH_BASE + 0x3400)
#define USART1_BASE (APB2PERIPH_BASE + 0x3800)
#define I2C3_BASE   (APB2PERIPH_BASE + 0x4400)
#define I2C4_BASE   (APB2PERIPH_BASE + 0x4800)
#define DVP_BASE    (APB2PERIPH_BASE + 0x4C00)
#define UART6_BASE  (APB2PERIPH_BASE + 0x5000)
#define UART7_BASE  (APB2PERIPH_BASE + 0x5400)

/* AHB */
#define SDIO_BASE     (AHBPERIPH_BASE + 0x0000)
#define DMA1_BASE     (AHBPERIPH_BASE + 0x8000)
#define DMA1_CH1_BASE (AHBPERIPH_BASE + 0x8008)
#define DMA1_CH2_BASE (AHBPERIPH_BASE + 0x801C)
#define DMA1_CH3_BASE (AHBPERIPH_BASE + 0x8030)
#define DMA1_CH4_BASE (AHBPERIPH_BASE + 0x8044)
#define DMA1_CH5_BASE (AHBPERIPH_BASE + 0x8058)
#define DMA1_CH6_BASE (AHBPERIPH_BASE + 0x806C)
#define DMA1_CH7_BASE (AHBPERIPH_BASE + 0x8080)
#define DMA1_CH8_BASE (AHBPERIPH_BASE + 0x8094)
#define DMA2_BASE     (AHBPERIPH_BASE + 0x8400)
#define DMA2_CH1_BASE (AHBPERIPH_BASE + 0x8408)
#define DMA2_CH2_BASE (AHBPERIPH_BASE + 0x841C)
#define DMA2_CH3_BASE (AHBPERIPH_BASE + 0x8430)
#define DMA2_CH4_BASE (AHBPERIPH_BASE + 0x8444)
#define DMA2_CH5_BASE (AHBPERIPH_BASE + 0x8458)
#define DMA2_CH6_BASE (AHBPERIPH_BASE + 0x846C)
#define DMA2_CH7_BASE (AHBPERIPH_BASE + 0x8480)
#define DMA2_CH8_BASE (AHBPERIPH_BASE + 0x8494)
#define ADC1_BASE     (AHBPERIPH_BASE + 0x8800)
#define ADC2_BASE     (AHBPERIPH_BASE + 0x8C00)
#define RCC_BASE      (AHBPERIPH_BASE + 0x9000)
#define FLASH_R_BASE  (AHBPERIPH_BASE + 0xA000) /*!< Flash registers base address */
#define OB_BASE       ((uint32_t)0x1FFFF800)    /*!< Flash Option Bytes base address */
#define CRC_BASE      (AHBPERIPH_BASE + 0xB000)
#define SAC_BASE      (AHBPERIPH_BASE + 0xC000)
#define SAC_SRAM_BASE (AHBPERIPH_BASE + 0xC400)
#define MMU_BASE      (AHBPERIPH_BASE + 0xCC00)

#define DBG_BASE ((uint32_t)0xE0042000) /*!< Debug MCU registers base address */

#define TIM2        ((TIM_Module*)TIM2_BASE)
#define TIM3        ((TIM_Module*)TIM3_BASE)
#define TIM4        ((TIM_Module*)TIM4_BASE)
#define TIM5        ((TIM_Module*)TIM5_BASE)
#define TIM6        ((TIM_Module*)TIM6_BASE)
#define TIM7        ((TIM_Module*)TIM7_BASE)
#define AFEC        ((AFEC_Module*)AFEC_BASE)
#define RTC         ((RTC_Module*)RTC_BASE)
#define WWDG        ((WWDG_Module*)WWDG_BASE)
#define IWDG        ((IWDG_Module*)IWDG_BASE)
#define TSC         ((TSC_Module*)TSC_BASE)
#define SPI2        ((SPI_Module*)SPI2_BASE)
#define SPI3        ((SPI_Module*)SPI3_BASE)
#define USART2      ((USART_Module*)USART2_BASE)
#define USART3      ((USART_Module*)USART3_BASE)
#define UART4       ((USART_Module*)UART4_BASE)
#define UART5       ((USART_Module*)UART5_BASE)
#define I2C1        ((I2C_Module*)I2C1_BASE)
#define I2C2        ((I2C_Module*)I2C2_BASE)
#define USB         ((USB_Module*)USB_BASE)
#define CAN1        ((CAN_Module*)CAN1_BASE)
#define CAN2        ((CAN_Module*)CAN2_BASE)
#define BKP         ((BKP_Module*)BKP_BASE)
#define PWR         ((PWR_Module*)PWR_BASE)
#define DAC         ((DAC_Module*)DAC_BASE)
#define AFIO        ((AFIO_Module*)AFIO_BASE)
#define EXTI        ((EXTI_Module*)EXTI_BASE)
#define GPIOA       ((GPIO_Module*)GPIOA_BASE)
#define GPIOB       ((GPIO_Module*)GPIOB_BASE)
#define GPIOC       ((GPIO_Module*)GPIOC_BASE)
#define GPIOD       ((GPIO_Module*)GPIOD_BASE)
#define GPIOE       ((GPIO_Module*)GPIOE_BASE)
#define TIM1        ((TIM_Module*)TIM1_BASE)
#define SPI1        ((SPI_Module*)SPI1_BASE)
#define TIM8        ((TIM_Module*)TIM8_BASE)
#define USART1      ((USART_Module*)USART1_BASE)
#define I2C3        ((I2C_Module*)I2C3_BASE)
#define I2C4        ((I2C_Module*)I2C4_BASE)
#define DVP         ((DVP_Module*)DVP_BASE)
#define UART6       ((USART_Module*)UART6_BASE)
#define UART7       ((USART_Module*)UART7_BASE)
#define SDIO        ((SDIO_Module*)SDIO_BASE)
#define DMA1        ((DMA_Module*)DMA1_BASE)
#define DMA2        ((DMA_Module*)DMA2_BASE)
#define DMA1_CH1    ((DMA_ChannelType*)DMA1_CH1_BASE)
#define DMA1_CH2    ((DMA_ChannelType*)DMA1_CH2_BASE)
#define DMA1_CH3    ((DMA_ChannelType*)DMA1_CH3_BASE)
#define DMA1_CH4    ((DMA_ChannelType*)DMA1_CH4_BASE)
#define DMA1_CH5    ((DMA_ChannelType*)DMA1_CH5_BASE)
#define DMA1_CH6    ((DMA_ChannelType*)DMA1_CH6_BASE)
#define DMA1_CH7    ((DMA_ChannelType*)DMA1_CH7_BASE)
#define DMA1_CH8    ((DMA_ChannelType*)DMA1_CH8_BASE)
#define DMA2_CH1    ((DMA_ChannelType*)DMA2_CH1_BASE)
#define DMA2_CH2    ((DMA_ChannelType*)DMA2_CH2_BASE)
#define DMA2_CH3    ((DMA_ChannelType*)DMA2_CH3_BASE)
#define DMA2_CH4    ((DMA_ChannelType*)DMA2_CH4_BASE)
#define DMA2_CH5    ((DMA_ChannelType*)DMA2_CH5_BASE)
#define DMA2_CH6    ((DMA_ChannelType*)DMA2_CH6_BASE)
#define DMA2_CH7    ((DMA_ChannelType*)DMA2_CH7_BASE)
#define DMA2_CH8    ((DMA_ChannelType*)DMA2_CH8_BASE)
#define ADC1        ((ADC_Module*)ADC1_BASE)
#define ADC2        ((ADC_Module*)ADC2_BASE)
#define RCC         ((RCC_Module*)RCC_BASE)
#define FLASH       ((FLASH_Module*)FLASH_R_BASE)
#define OB          ((OB_Module*)OB_BASE)
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

/********************  Bit definition for PWR_CTRL register  ********************/
#define PWR_CTRL_LPS     ((uint16_t)0x0001) /*!< Low-Power Deepsleep */
#define PWR_CTRL_PDS     ((uint16_t)0x0002) /*!< Power Down Deepsleep */
#define PWR_CTRL_CWKUP   ((uint16_t)0x0004) /*!< Clear Wakeup Flag */
#define PWR_CTRL_CSBVBAT ((uint16_t)0x0008) /*!< Clear Standby Flag */
#define PWR_CTRL_PVDEN   ((uint16_t)0x0010) /*!< Power Voltage Detector Enable */

#define PWR_CTRL_PRS   ((uint16_t)0x00E0) /*!< PRS[2:0] bits (PVD Level Selection) */
#define PWR_CTRL_PRS_0 ((uint16_t)0x0020) /*!< Bit 0 */
#define PWR_CTRL_PRS_1 ((uint16_t)0x0040) /*!< Bit 1 */
#define PWR_CTRL_PRS_2 ((uint16_t)0x0080) /*!< Bit 2 */

/*!< PVD level configuration */
#define PWR_CTRL_PRS_2V2 ((uint16_t)0x0000) /*!< PVD level 2.2V */
#define PWR_CTRL_PRS_2V3 ((uint16_t)0x0020) /*!< PVD level 2.3V */
#define PWR_CTRL_PRS_2V4 ((uint16_t)0x0040) /*!< PVD level 2.4V */
#define PWR_CTRL_PRS_2V5 ((uint16_t)0x0060) /*!< PVD level 2.5V */
#define PWR_CTRL_PRS_2V6 ((uint16_t)0x0080) /*!< PVD level 2.6V */
#define PWR_CTRL_PRS_2V7 ((uint16_t)0x00A0) /*!< PVD level 2.7V */
#define PWR_CTRL_PRS_2V8 ((uint16_t)0x00C0) /*!< PVD level 2.8V */
#define PWR_CTRL_PRS_2V9 ((uint16_t)0x00E0) /*!< PVD level 2.9V */

#define PWR_CTRL_DBKP ((uint16_t)0x0100) /*!< Disable Backup Domain write protection */
#define PWR_CTRL_MSB  ((uint16_t)0x0200) /*!< Bit 9 */

/*******************  Bit definition for PWR_CTRLSTS register  ********************/
#define PWR_CTRLSTS_WKUPF  ((uint16_t)0x0001) /*!< Wakeup Flag */
#define PWR_CTRLSTS_SBF    ((uint16_t)0x0002) /*!< Standby Flag */
#define PWR_CTRLSTS_PVDO   ((uint16_t)0x0004) /*!< PVD Output */
#define PWR_CTRLSTS_VBATF  ((uint16_t)0x0008) /*!< VBAT Flag */
#define PWR_CTRLSTS_WKUPEN ((uint16_t)0x0100) /*!< Enable WKUP pin */

/*******************  Bit definition for PWR_CTRL2 register  ********************/
#define PWR_CTRL2_STOP2S    ((uint16_t)0x0001) /*!< Enable STOP2 */
#define PWR_CTRL2_SR2VBRET  ((uint16_t)0x0002) /*!< VBAT mode SRAM2 retention */
#define PWR_CTRL2_SR2STBRET ((uint16_t)0x0004) /*!< Standby mode SRAM2 retention  */
#define PWR_CTRL2_TMPWPEN   ((uint16_t)0x0008) /*!< Enable Tamper WakeUp */
#define PWR_CTRL2_LSITRIM   ((uint16_t)0x01F0) /*!< config the LSI trimming value */
#define PWR_CTRL2_IWDGWPEN  ((uint16_t)0x0200) /*!< Enable IWDG WakeUp */
#define PWR_CTRL2_IWDGRSTEN ((uint16_t)0x0400) /*!< Enable IWDG RST WakeUp */

/*******************  Bit definition for PWR_CTRL3 register  ********************/
#define PWR_CTRL3_EXMODE        ((uint16_t)0x0001) /*!< BKPM Mode */
#define PWR_CTRL3_EXMODE_EXTEND ((uint16_t)0x0001) /*!< EXTEND Mode */
#define PWR_CTRL3_EXMODE_NORMAL ((uint16_t)0x0000) /*!< NORMAL Mode */


/******************************************************************************/
/*                                                                            */
/*                            Backup registers                                */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for BKP_DAT1 register  ********************/
#define BKP_DAT1_DAT ((uint16_t)0xFFFF) /*!< Backup data */

/*******************  Bit definition for BKP_DAT2 register  ********************/
#define BKP_DAT2_DAT ((uint16_t)0xFFFF) /*!< Backup data */

/*******************  Bit definition for BKP_DAT3 register  ********************/
#define BKP_DAT3_DAT ((uint16_t)0xFFFF) /*!< Backup data */

/*******************  Bit definition for BKP_DAT4 register  ********************/
#define BKP_DAT4_DAT ((uint16_t)0xFFFF) /*!< Backup data */

/*******************  Bit definition for BKP_DAT5 register  ********************/
#define BKP_DAT5_DAT ((uint16_t)0xFFFF) /*!< Backup data */

/*******************  Bit definition for BKP_DAT6 register  ********************/
#define BKP_DAT6_DAT ((uint16_t)0xFFFF) /*!< Backup data */

/*******************  Bit definition for BKP_DAT7 register  ********************/
#define BKP_DAT7_DAT ((uint16_t)0xFFFF) /*!< Backup data */

/*******************  Bit definition for BKP_DAT8 register  ********************/
#define BKP_DAT8_DAT ((uint16_t)0xFFFF) /*!< Backup data */

/*******************  Bit definition for BKP_DAT9 register  ********************/
#define BKP_DAT9_DAT ((uint16_t)0xFFFF) /*!< Backup data */

/*******************  Bit definition for BKP_DAT10 register  *******************/
#define BKP_DAT10_DAT ((uint16_t)0xFFFF) /*!< Backup data */

/*******************  Bit definition for BKP_DAT11 register  *******************/
#define BKP_DAT11_DAT ((uint16_t)0xFFFF) /*!< Backup data */

/*******************  Bit definition for BKP_DAT12 register  *******************/
#define BKP_DAT12_DAT ((uint16_t)0xFFFF) /*!< Backup data */

/*******************  Bit definition for BKP_DAT13 register  *******************/
#define BKP_DAT13_DAT ((uint16_t)0xFFFF) /*!< Backup data */

/*******************  Bit definition for BKP_DAT14 register  *******************/
#define BKP_DAT14_DAT ((uint16_t)0xFFFF) /*!< Backup data */

/*******************  Bit definition for BKP_DAT15 register  *******************/
#define BKP_DAT15_DAT ((uint16_t)0xFFFF) /*!< Backup data */

/*******************  Bit definition for BKP_DAT16 register  *******************/
#define BKP_DAT16_DAT ((uint16_t)0xFFFF) /*!< Backup data */

/*******************  Bit definition for BKP_DAT17 register  *******************/
#define BKP_DAT17_DAT ((uint16_t)0xFFFF) /*!< Backup data */

/******************  Bit definition for BKP_DAT18 register  ********************/
#define BKP_DAT18_DAT ((uint16_t)0xFFFF) /*!< Backup data */

/*******************  Bit definition for BKP_DAT19 register  *******************/
#define BKP_DAT19_DAT ((uint16_t)0xFFFF) /*!< Backup data */

/*******************  Bit definition for BKP_DAT20 register  *******************/
#define BKP_DAT20_DAT ((uint16_t)0xFFFF) /*!< Backup data */

/*******************  Bit definition for BKP_DAT21 register  *******************/
#define BKP_DAT21_DAT ((uint16_t)0xFFFF) /*!< Backup data */

/*******************  Bit definition for BKP_DAT22 register  *******************/
#define BKP_DAT22_DAT ((uint16_t)0xFFFF) /*!< Backup data */

/*******************  Bit definition for BKP_DAT23 register  *******************/
#define BKP_DAT23_DAT ((uint16_t)0xFFFF) /*!< Backup data */

/*******************  Bit definition for BKP_DAT24 register  *******************/
#define BKP_DAT24_DAT ((uint16_t)0xFFFF) /*!< Backup data */

/*******************  Bit definition for BKP_DAT25 register  *******************/
#define BKP_DAT25_DAT ((uint16_t)0xFFFF) /*!< Backup data */

/*******************  Bit definition for BKP_DAT26 register  *******************/
#define BKP_DAT26_DAT ((uint16_t)0xFFFF) /*!< Backup data */

/*******************  Bit definition for BKP_DAT27 register  *******************/
#define BKP_DAT27_DAT ((uint16_t)0xFFFF) /*!< Backup data */

/*******************  Bit definition for BKP_DAT28 register  *******************/
#define BKP_DAT28_DAT ((uint16_t)0xFFFF) /*!< Backup data */

/*******************  Bit definition for BKP_DAT29 register  *******************/
#define BKP_DAT29_DAT ((uint16_t)0xFFFF) /*!< Backup data */

/*******************  Bit definition for BKP_DAT30 register  *******************/
#define BKP_DAT30_DAT ((uint16_t)0xFFFF) /*!< Backup data */

/*******************  Bit definition for BKP_DAT31 register  *******************/
#define BKP_DAT31_DAT ((uint16_t)0xFFFF) /*!< Backup data */

/*******************  Bit definition for BKP_DAT32 register  *******************/
#define BKP_DAT32_DAT ((uint16_t)0xFFFF) /*!< Backup data */

/*******************  Bit definition for BKP_DAT33 register  *******************/
#define BKP_DAT33_DAT ((uint16_t)0xFFFF) /*!< Backup data */

/*******************  Bit definition for BKP_DAT34 register  *******************/
#define BKP_DAT34_DAT ((uint16_t)0xFFFF) /*!< Backup data */

/*******************  Bit definition for BKP_DAT35 register  *******************/
#define BKP_DAT35_DAT ((uint16_t)0xFFFF) /*!< Backup data */

/*******************  Bit definition for BKP_DAT36 register  *******************/
#define BKP_DAT36_DAT ((uint16_t)0xFFFF) /*!< Backup data */

/*******************  Bit definition for BKP_DAT37 register  *******************/
#define BKP_DAT37_DAT ((uint16_t)0xFFFF) /*!< Backup data */

/*******************  Bit definition for BKP_DAT38 register  *******************/
#define BKP_DAT38_DAT ((uint16_t)0xFFFF) /*!< Backup data */

/*******************  Bit definition for BKP_DAT39 register  *******************/
#define BKP_DAT39_DAT ((uint16_t)0xFFFF) /*!< Backup data */

/*******************  Bit definition for BKP_DAT40 register  *******************/
#define BKP_DAT40_DAT ((uint16_t)0xFFFF) /*!< Backup data */

/*******************  Bit definition for BKP_DAT41 register  *******************/
#define BKP_DAT41_DAT ((uint16_t)0xFFFF) /*!< Backup data */

/*******************  Bit definition for BKP_DAT42 register  *******************/
#define BKP_DAT42_DAT ((uint16_t)0xFFFF) /*!< Backup data */

/********************  Bit definition for BKP_CTRL register  ********************/
#define BKP_CTRL_TP_EN   ((uint8_t)0x01) /*!< TAMPER pin enable */
#define BKP_CTRL_TP_ALEV ((uint8_t)0x02) /*!< TAMPER pin active level */

/*******************  Bit definition for BKP_CTRLSTS register  ********************/
#define BKP_CTRLSTS_CLRTE    ((uint16_t)0x0001) /*!< Clear Tamper event */
#define BKP_CTRLSTS_CLRTINT  ((uint16_t)0x0002) /*!< Clear Tamper Interrupt */
#define BKP_CTRLSTS_TPINT_EN ((uint16_t)0x0004) /*!< TAMPER Pin interrupt enable */
#define BKP_CTRLSTS_TEF      ((uint16_t)0x0100) /*!< Tamper Event Flag */
#define BKP_CTRLSTS_TINTF    ((uint16_t)0x0200) /*!< Tamper Interrupt Flag */

/******************************************************************************/
/*                                                                            */
/*                         Reset and Clock Control                            */
/*                                                                            */
/******************************************************************************/

/********************  Bit definition for RCC_CTRL register  ********************/
#define RCC_CTRL_HSIEN   ((uint32_t)0x00000001) /*!< Internal High Speed clock enable */
#define RCC_CTRL_HSIRDF  ((uint32_t)0x00000002) /*!< Internal High Speed clock ready flag */
#define RCC_CTRL_HSITRIM ((uint32_t)0x000000F8) /*!< Internal High Speed clock trimming */
#define RCC_CTRL_HSICAL  ((uint32_t)0x0000FF00) /*!< Internal High Speed clock Calibration */
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

#define RCC_CFG_SCLKSW_HSI ((uint32_t)0x00000000) /*!< HSI selected as system clock */
#define RCC_CFG_SCLKSW_HSE ((uint32_t)0x00000001) /*!< HSE selected as system clock */
#define RCC_CFG_SCLKSW_PLL ((uint32_t)0x00000002) /*!< PLL selected as system clock */

/*!< SWS configuration */
#define RCC_CFG_SCLKSTS   ((uint32_t)0x0000000C) /*!< SWS[1:0] bits (System Clock Switch Status) */
#define RCC_CFG_SCLKSTS_0 ((uint32_t)0x00000004) /*!< Bit 0 */
#define RCC_CFG_SCLKSTS_1 ((uint32_t)0x00000008) /*!< Bit 1 */

#define RCC_CFG_SCLKSTS_HSI ((uint32_t)0x00000000) /*!< HSI oscillator used as system clock */
#define RCC_CFG_SCLKSTS_HSE ((uint32_t)0x00000004) /*!< HSE oscillator used as system clock */
#define RCC_CFG_SCLKSTS_PLL ((uint32_t)0x00000008) /*!< PLL used as system clock */

/*!< HPRE configuration */
#define RCC_CFG_AHBPRES   ((uint32_t)0x000000F0) /*!< HPRE[3:0] bits (AHB prescaler) */
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

/*!< PPRE1 configuration */
#define RCC_CFG_APB1PRES   ((uint32_t)0x00000700) /*!< PRE1[2:0] bits (APB1 prescaler) */
#define RCC_CFG_APB1PRES_0 ((uint32_t)0x00000100) /*!< Bit 0 */
#define RCC_CFG_APB1PRES_1 ((uint32_t)0x00000200) /*!< Bit 1 */
#define RCC_CFG_APB1PRES_2 ((uint32_t)0x00000400) /*!< Bit 2 */

#define RCC_CFG_APB1PRES_DIV1  ((uint32_t)0x00000000) /*!< HCLK not divided */
#define RCC_CFG_APB1PRES_DIV2  ((uint32_t)0x00000400) /*!< HCLK divided by 2 */
#define RCC_CFG_APB1PRES_DIV4  ((uint32_t)0x00000500) /*!< HCLK divided by 4 */
#define RCC_CFG_APB1PRES_DIV8  ((uint32_t)0x00000600) /*!< HCLK divided by 8 */
#define RCC_CFG_APB1PRES_DIV16 ((uint32_t)0x00000700) /*!< HCLK divided by 16 */

/*!< PPRE2 configuration */
#define RCC_CFG_APB2PRES   ((uint32_t)0x00003800) /*!< PRE2[2:0] bits (APB2 prescaler) */
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

/*!< PLLXTPRE configuration */
#define RCC_CFG_PLLHSEPRES ((uint32_t)0x00020000) /*!< HSE divider for PLL entry */

/*!< PLLMUL configuration */
#define RCC_CFG_PLLMULFCT   ((uint32_t)0x083C0000) /*!< PLLMUL[4:0] bits (PLL multiplication factor) */
#define RCC_CFG_PLLMULFCT_0 ((uint32_t)0x00040000) /*!< Bit 0 */
#define RCC_CFG_PLLMULFCT_1 ((uint32_t)0x00080000) /*!< Bit 1 */
#define RCC_CFG_PLLMULFCT_2 ((uint32_t)0x00100000) /*!< Bit 2 */
#define RCC_CFG_PLLMULFCT_3 ((uint32_t)0x00200000) /*!< Bit 3 */
#define RCC_CFG_PLLMULFCT_4 ((uint32_t)0x08000000) /*!< Bit 4 */

#define RCC_CFG_PLLSRC_HSI_DIV2                                                                                        \
    ((uint32_t)0x00000000)                        /*!< HSI clock divided by 2 selected as PLL entry clock source       \
                                                   */
#define RCC_CFG_PLLSRC_HSE ((uint32_t)0x00010000) /*!< HSE clock selected as PLL entry clock source */

#define RCC_CFG_PLLHSEPRES_HSE      ((uint32_t)0x00000000) /*!< HSE clock not divided for PLL entry */
#define RCC_CFG_PLLHSEPRES_HSE_DIV2 ((uint32_t)0x00020000) /*!< HSE clock divided by 2 for PLL entry */
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
#define RCC_CFG_MCO_SYSCLK ((uint32_t)0x04000000) /*!< System clock selected as MCO source */
#define RCC_CFG_MCO_HSI    ((uint32_t)0x05000000) /*!< HSI clock selected as MCO source */
#define RCC_CFG_MCO_HSE    ((uint32_t)0x06000000) /*!< HSE clock selected as MCO source  */
#define RCC_CFG_MCO_PLL    ((uint32_t)0x07000000) /*!< PLL clock divided by 2 selected as MCO source */

/*!< MCOPRE configuration */
#define RCC_CFG_MCOPRES                                                                                                \
    ((uint32_t)0xF0000000) /*!< MCOPRE[3:0] bits ( PLL prescaler set and cleared by software to generate MCOPRE        \
                              clock.) */
#define RCC_CFG_MCOPRES_0 ((uint32_t)0x10000000) /*!< Bit 0 */
#define RCC_CFG_MCOPRES_1 ((uint32_t)0x20000000) /*!< Bit 1 */
#define RCC_CFG_MCOPRES_2 ((uint32_t)0x40000000) /*!< Bit 2 */
#define RCC_CFG_MCOPRES_3 ((uint32_t)0x80000000) /*!< Bit 3 */

#define RCC_CFG_MCOPRES_PLLDIV2  ((uint32_t)0x20000000) /*!< PLL clock is divided by 2 */
#define RCC_CFG_MCOPRES_PLLDIV3  ((uint32_t)0x30000000) /*!< PLL clock is divided by 3 */
#define RCC_CFG_MCOPRES_PLLDIV4  ((uint32_t)0x40000000) /*!< PLL clock is divided by 4 */
#define RCC_CFG_MCOPRES_PLLDIV5  ((uint32_t)0x50000000) /*!< PLL clock is divided by 5 */
#define RCC_CFG_MCOPRES_PLLDIV6  ((uint32_t)0x60000000) /*!< PLL clock is divided by 6 */
#define RCC_CFG_MCOPRES_PLLDIV7  ((uint32_t)0x70000000) /*!< PLL clock is divided by 7 */
#define RCC_CFG_MCOPRES_PLLDIV8  ((uint32_t)0x80000000) /*!< PLL clock is divided by 8 */
#define RCC_CFG_MCOPRES_PLLDIV9  ((uint32_t)0x90000000) /*!< PLL clock is divided by 9 */
#define RCC_CFG_MCOPRES_PLLDIV10 ((uint32_t)0xA0000000) /*!< PLL clock is divided by 10 */
#define RCC_CFG_MCOPRES_PLLDIV11 ((uint32_t)0xB0000000) /*!< PLL clock is divided by 11 */
#define RCC_CFG_MCOPRES_PLLDIV12 ((uint32_t)0xC0000000) /*!< PLL clock is divided by 12 */
#define RCC_CFG_MCOPRES_PLLDIV13 ((uint32_t)0xD0000000) /*!< PLL clock is divided by 13 */
#define RCC_CFG_MCOPRES_PLLDIV14 ((uint32_t)0xE0000000) /*!< PLL clock is divided by 14 */
#define RCC_CFG_MCOPRES_PLLDIV15 ((uint32_t)0xF0000000) /*!< PLL clock is divided by 15 */

/*!<******************  Bit definition for RCC_CLKINT register  ********************/
#define RCC_CLKINT_LSIRDIF   ((uint32_t)0x00000001) /*!< LSI Ready Interrupt flag */
#define RCC_CLKINT_LSERDIF   ((uint32_t)0x00000002) /*!< LSE Ready Interrupt flag */
#define RCC_CLKINT_HSIRDIF   ((uint32_t)0x00000004) /*!< HSI Ready Interrupt flag */
#define RCC_CLKINT_HSERDIF   ((uint32_t)0x00000008) /*!< HSE Ready Interrupt flag */
#define RCC_CLKINT_PLLRDIF   ((uint32_t)0x00000010) /*!< PLL Ready Interrupt flag */
#define RCC_CLKINT_CLKSSIF   ((uint32_t)0x00000080) /*!< Clock Security System Interrupt flag */
#define RCC_CLKINT_LSIRDIEN  ((uint32_t)0x00000100) /*!< LSI Ready Interrupt Enable */
#define RCC_CLKINT_LSERDIEN  ((uint32_t)0x00000200) /*!< LSE Ready Interrupt Enable */
#define RCC_CLKINT_HSIRDIEN  ((uint32_t)0x00000400) /*!< HSI Ready Interrupt Enable */
#define RCC_CLKINT_HSERDIEN  ((uint32_t)0x00000800) /*!< HSE Ready Interrupt Enable */
#define RCC_CLKINT_PLLRDIEN  ((uint32_t)0x00001000) /*!< PLL Ready Interrupt Enable */
#define RCC_CLKINT_LSIRDICLR ((uint32_t)0x00010000) /*!< LSI Ready Interrupt Clear */
#define RCC_CLKINT_LSERDICLR ((uint32_t)0x00020000) /*!< LSE Ready Interrupt Clear */
#define RCC_CLKINT_HSIRDICLR ((uint32_t)0x00040000) /*!< HSI Ready Interrupt Clear */
#define RCC_CLKINT_HSERDICLR ((uint32_t)0x00080000) /*!< HSE Ready Interrupt Clear */
#define RCC_CLKINT_PLLRDICLR ((uint32_t)0x00100000) /*!< PLL Ready Interrupt Clear */
#define RCC_CLKINT_CLKSSICLR ((uint32_t)0x00800000) /*!< Clock Security System Interrupt Clear */

/*****************  Bit definition for RCC_APB2PRST register  *****************/
#define RCC_APB2PRST_AFIORST   ((uint32_t)0x00000001) /*!< Alternate Function I/O reset */
#define RCC_APB2PRST_IOPARST   ((uint32_t)0x00000004) /*!< I/O port A reset */
#define RCC_APB2PRST_IOPBRST   ((uint32_t)0x00000008) /*!< I/O port B reset */
#define RCC_APB2PRST_IOPCRST   ((uint32_t)0x00000010) /*!< I/O port C reset */
#define RCC_APB2PRST_IOPDRST   ((uint32_t)0x00000020) /*!< I/O port D reset */
#define RCC_APB2PRST_IOPERST   ((uint32_t)0x00000040) /*!< I/O port E reset */
#define RCC_APB2PRST_IOPFRST   ((uint32_t)0x00000080) /*!< I/O port F reset */
#define RCC_APB2PRST_IOPGRST   ((uint32_t)0x00000100) /*!< I/O port G reset */
#define RCC_APB2PRST_TIM1RST   ((uint32_t)0x00000800) /*!< TIM1 Timer reset */
#define RCC_APB2PRST_SPI1RST   ((uint32_t)0x00001000) /*!< SPI 1 reset */
#define RCC_APB2PRST_TIM8RST   ((uint32_t)0x00002000) /*!< TIM8 Timer reset */
#define RCC_APB2PRST_USART1RST ((uint32_t)0x00004000) /*!< USART1 reset */
#define RCC_APB2PRST_DVPRST    ((uint32_t)0x00010000) /*!< DVP reset */
#define RCC_APB2PRST_UART6RST  ((uint32_t)0x00020000) /*!< UART6 reset */
#define RCC_APB2PRST_UART7RST  ((uint32_t)0x00040000) /*!< UART7 reset */
#define RCC_APB2PRST_I2C3RST   ((uint32_t)0x00080000) /*!< I2C3 reset */
#define RCC_APB2PRST_I2C4RST   ((uint32_t)0x00100000) /*!< I2C4 reset */

/*****************  Bit definition for RCC_APB1PRST register  *****************/
#define RCC_APB1PRST_TIM2RST   ((uint32_t)0x00000001) /*!< Timer 2 reset */
#define RCC_APB1PRST_TIM3RST   ((uint32_t)0x00000002) /*!< Timer 3 reset */
#define RCC_APB1PRST_TIM4RST   ((uint32_t)0x00000004) /*!< Timer 4 reset */
#define RCC_APB1PRST_TIM5RST   ((uint32_t)0x00000008) /*!< Timer 5 reset */
#define RCC_APB1PRST_TIM6RST   ((uint32_t)0x00000010) /*!< Timer 6 reset */
#define RCC_APB1PRST_TIM7RST   ((uint32_t)0x00000020) /*!< Timer 7 reset */
#define RCC_APB1PRST_TSCRST    ((uint32_t)0x00000400) /*!< TSC reset */
#define RCC_APB1PRST_WWDGRST   ((uint32_t)0x00000800) /*!< Window Watchdog reset */
#define RCC_APB1PRST_SPI2RST   ((uint32_t)0x00004000) /*!< SPI 2 reset */
#define RCC_APB1PRST_SPI3RST   ((uint32_t)0x00008000) /*!< SPI 3 reset */
#define RCC_APB1PRST_USART2RST ((uint32_t)0x00020000) /*!< USART 2 reset */
#define RCC_APB1PRST_USART3RST ((uint32_t)0x00040000) /*!< USART 3 reset */
#define RCC_APB1PRST_UART4RST  ((uint32_t)0x00080000) /*!< UART 4 reset */
#define RCC_APB1PRST_UART5RST  ((uint32_t)0x00100000) /*!< UART 5 reset */
#define RCC_APB1PRST_I2C1RST   ((uint32_t)0x00200000) /*!< I2C 1 reset */
#define RCC_APB1PRST_I2C2RST   ((uint32_t)0x00400000) /*!< I2C 2 reset */
#define RCC_APB1PRST_USBRST    ((uint32_t)0x00800000) /*!< USB Device reset */
#define RCC_APB1PRST_CAN1RST   ((uint32_t)0x02000000) /*!< CAN1 reset */
#define RCC_APB1PRST_CAN2RST   ((uint32_t)0x04000000) /*!< CAN2 reset */
#define RCC_APB1PRST_BKPRST    ((uint32_t)0x08000000) /*!< Backup interface reset */
#define RCC_APB1PRST_PWRRST    ((uint32_t)0x10000000) /*!< Power interface reset */
#define RCC_APB1PRST_DACRST    ((uint32_t)0x20000000) /*!< DAC interface reset */

/******************  Bit definition for RCC_AHBPCLKEN register  ******************/
#define RCC_AHBPCLKEN_DMA1EN   ((uint32_t)0x00000001) /*!< DMA1 clock enable */
#define RCC_AHBPCLKEN_DMA2EN   ((uint32_t)0x00000002) /*!< DMA2 clock enable */
#define RCC_AHBPCLKEN_SRAMEN   ((uint32_t)0x00000004) /*!< SRAM interface clock enable */
#define RCC_AHBPCLKEN_FLITFEN  ((uint32_t)0x00000010) /*!< FLITF clock enable */
#define RCC_AHBPCLKEN_CRCEN    ((uint32_t)0x00000040) /*!< CRC clock enable */
#define RCC_AHBPCLKEN_RNGCEN   ((uint32_t)0x00000200) /*!< RNGC clock enable */
#define RCC_AHBPCLKEN_SDIOEN   ((uint32_t)0x00000400) /*!< SDIO clock enable */
#define RCC_AHBPCLKEN_SACEN    ((uint32_t)0x00000800) /*!< SAC clock enable */
#define RCC_AHBPCLKEN_ADC1EN   ((uint32_t)0x00001000) /*!< ADC1 clock enable */
#define RCC_AHBPCLKEN_ADC2EN   ((uint32_t)0x00002000) /*!< ADC2 clock enable */

/******************  Bit definition for RCC_APB2PCLKEN register  *****************/
#define RCC_APB2PCLKEN_AFIOEN   ((uint32_t)0x00000001) /*!< Alternate Function I/O clock enable */
#define RCC_APB2PCLKEN_IOPAEN   ((uint32_t)0x00000004) /*!< I/O port A clock enable */
#define RCC_APB2PCLKEN_IOPBEN   ((uint32_t)0x00000008) /*!< I/O port B clock enable */
#define RCC_APB2PCLKEN_IOPCEN   ((uint32_t)0x00000010) /*!< I/O port C clock enable */
#define RCC_APB2PCLKEN_IOPDEN   ((uint32_t)0x00000020) /*!< I/O port D clock enable */
#define RCC_APB2PCLKEN_IOPEEN   ((uint32_t)0x00000040) /*!< I/O port E clock enable */
#define RCC_APB2PCLKEN_IOPFEN   ((uint32_t)0x00000080) /*!< I/O port F clock enable */
#define RCC_APB2PCLKEN_IOPGEN   ((uint32_t)0x00000100) /*!< I/O port G clock enable */
#define RCC_APB2PCLKEN_TIM1EN   ((uint32_t)0x00000800) /*!< TIM1 Timer clock enable */
#define RCC_APB2PCLKEN_SPI1EN   ((uint32_t)0x00001000) /*!< SPI1 clock enable */
#define RCC_APB2PCLKEN_TIM8EN   ((uint32_t)0x00002000) /*!< TIM8 Timer clock enable */
#define RCC_APB2PCLKEN_USART1EN ((uint32_t)0x00004000) /*!< USART1 clock enable */
#define RCC_APB2PCLKEN_DVPEN    ((uint32_t)0x00010000) /*!< DVP clock enable */
#define RCC_APB2PCLKEN_UART6EN  ((uint32_t)0x00020000) /*!< UART6 clock enable */
#define RCC_APB2PCLKEN_UART7EN  ((uint32_t)0x00040000) /*!< UART7 clock enable */
#define RCC_APB2PCLKEN_I2C3EN   ((uint32_t)0x00080000) /*!< I2C3 clock enable */
#define RCC_APB2PCLKEN_I2C4EN   ((uint32_t)0x00100000) /*!< I2C4 clock enable */

/*****************  Bit definition for RCC_APB1PCLKEN register  ******************/
#define RCC_APB1PCLKEN_TIM2EN     ((uint32_t)0x00000001) /*!< Timer 2 clock enabled*/
#define RCC_APB1PCLKEN_TIM3EN     ((uint32_t)0x00000002) /*!< Timer 3 clock enable */
#define RCC_APB1PCLKEN_TIM4EN     ((uint32_t)0x00000004) /*!< Timer 4 clock enable */
#define RCC_APB1PCLKEN_TIM5EN     ((uint32_t)0x00000008) /*!< Timer 5 clock enable */
#define RCC_APB1PCLKEN_TIM6EN     ((uint32_t)0x00000010) /*!< Timer 6 clock enable */
#define RCC_APB1PCLKEN_TIM7EN     ((uint32_t)0x00000020) /*!< Timer 7 clock enable */
#define RCC_APB1PCLKEN_COMPEN     ((uint32_t)0x00000040) /*!< COMP clock enable */
#define RCC_APB1PCLKEN_COMPFILTEN ((uint32_t)0x00000080) /*!< COMPFILT clock enable */
#define RCC_APB1PCLKEN_TSCEN      ((uint32_t)0x00000400) /*!< TSC clock enable */
#define RCC_APB1PCLKEN_WWDGEN     ((uint32_t)0x00000800) /*!< Window Watchdog clock enable */
#define RCC_APB1PCLKEN_SPI2EN     ((uint32_t)0x00004000) /*!< SPI 2 clock enable */
#define RCC_APB1PCLKEN_SPI3EN     ((uint32_t)0x00008000) /*!< SPI 3 clock enable */
#define RCC_APB1PCLKEN_USART2EN   ((uint32_t)0x00020000) /*!< USART 2 clock enable */
#define RCC_APB1PCLKEN_USART3EN   ((uint32_t)0x00040000) /*!< USART 3 clock enable */
#define RCC_APB1PCLKEN_UART4EN    ((uint32_t)0x00080000) /*!< UART 4 clock enable */
#define RCC_APB1PCLKEN_UART5EN    ((uint32_t)0x00100000) /*!< UART 5 clock enable */
#define RCC_APB1PCLKEN_I2C1EN     ((uint32_t)0x00200000) /*!< I2C 1 clock enable */
#define RCC_APB1PCLKEN_I2C2EN     ((uint32_t)0x00400000) /*!< I2C 2 clock enable */
#define RCC_APB1PCLKEN_USBEN      ((uint32_t)0x00800000) /*!< USB Device clock enable */
#define RCC_APB1PCLKEN_CAN1EN     ((uint32_t)0x02000000) /*!< CAN1 clock enable */
#define RCC_APB1PCLKEN_CAN2EN     ((uint32_t)0x04000000) /*!< CAN2 clock enable */
#define RCC_APB1PCLKEN_BKPEN      ((uint32_t)0x08000000) /*!< Backup interface clock enable */
#define RCC_APB1PCLKEN_PWREN      ((uint32_t)0x10000000) /*!< Power interface clock enable */
#define RCC_APB1PCLKEN_DACEN      ((uint32_t)0x20000000) /*!< DAC interface clock enable */
#define RCC_APB1PCLKEN_OPAMPEN    ((uint32_t)0x80000000) /*!< OPAMP interface clock enable */

/*******************  Bit definition for RCC_BDCTRL register  *******************/
#define RCC_BDCTRL_LSEEN ((uint32_t)0x00000001) /*!< External Low Speed oscillator enable */
#define RCC_BDCTRL_LSERD ((uint32_t)0x00000002) /*!< External Low Speed oscillator Ready */
#define RCC_BDCTRL_LSEBP ((uint32_t)0x00000004) /*!< External Low Speed oscillator Bypass */

#define RCC_BDCTRL_RTCSEL   ((uint32_t)0x00000300) /*!< RTCSEL[1:0] bits (RTC clock source selection) */
#define RCC_BDCTRL_RTCSEL_0 ((uint32_t)0x00000100) /*!< Bit 0 */
#define RCC_BDCTRL_RTCSEL_1 ((uint32_t)0x00000200) /*!< Bit 1 */

/*!< RTC congiguration */
#define RCC_BDCTRL_RTCSEL_NOCLOCK ((uint32_t)0x00000000) /*!< No clock */
#define RCC_BDCTRL_RTCSEL_LSE     ((uint32_t)0x00000100) /*!< LSE oscillator clock used as RTC clock */
#define RCC_BDCTRL_RTCSEL_LSI     ((uint32_t)0x00000200) /*!< LSI oscillator clock used as RTC clock */
#define RCC_BDCTRL_RTCSEL_HSE     ((uint32_t)0x00000300) /*!< HSE oscillator clock divided by 128 used as RTC clock */

#define RCC_BDCTRL_RTCEN    ((uint32_t)0x00008000) /*!< RTC clock enable */
#define RCC_BDCTRL_BDSFTRST ((uint32_t)0x00010000) /*!< Backup domain software reset  */

/*******************  Bit definition for RCC_CTRLSTS register  ********************/
#define RCC_CTRLSTS_LSIEN    ((uint32_t)0x00000001) /*!< Internal Low Speed oscillator enable */
#define RCC_CTRLSTS_LSIRD    ((uint32_t)0x00000002) /*!< Internal Low Speed oscillator Ready */
#define RCC_CTRLSTS_BORRSTF  ((uint32_t)0x00080000) /*!< BOR reset flag */
#define RCC_CTRLSTS_RETEMCF  ((uint32_t)0x00100000) /*!< RET_EMC reset flag */
#define RCC_CTRLSTS_BKPEMCF  ((uint32_t)0x00200000) /*!< BKP_EMC reset flag */
#define RCC_CTRLSTS_RAMRSTF  ((uint32_t)0x00800000) /*!< RAM reset flag */
#define RCC_CTRLSTS_RMRSTF   ((uint32_t)0x01000000) /*!< Remove reset flag */
#define RCC_CTRLSTS_MMURSTF  ((uint32_t)0x02000000) /*!< MMU reset flag */
#define RCC_CTRLSTS_PINRSTF  ((uint32_t)0x04000000) /*!< PIN reset flag */
#define RCC_CTRLSTS_PORRSTF  ((uint32_t)0x08000000) /*!< POR/PDR reset flag */
#define RCC_CTRLSTS_SFTRSTF  ((uint32_t)0x10000000) /*!< Software Reset flag */
#define RCC_CTRLSTS_IWDGRSTF ((uint32_t)0x20000000) /*!< Independent Watchdog reset flag */
#define RCC_CTRLSTS_WWDGRSTF ((uint32_t)0x40000000) /*!< Window watchdog reset flag */
#define RCC_CTRLSTS_LPWRRSTF ((uint32_t)0x80000000) /*!< Low-Power reset flag */

/*******************  Bit definition for RCC_AHBPRST register  ****************/
#define RCC_AHBRST_RNGCRST   ((uint32_t)0x00000200) /*!< RNGC reset */
#define RCC_AHBRST_SACRST    ((uint32_t)0x00000800) /*!< SAC reset */
#define RCC_AHBRST_ADC1RST   ((uint32_t)0x00001000) /*!< ADC1 reset */
#define RCC_AHBRST_ADC2RST   ((uint32_t)0x00002000) /*!< ADC2 reset */

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

/*!< ADC1MSEL configuration */
#define RCC_CFG2_ADC1MSEL ((uint32_t)0x00000400) /*!< ADC1M clock source select */

#define RCC_CFG2_ADC1MSEL_HSI ((uint32_t)0x00000000) /*!< HSI clock selected as ADC1M input clock */
#define RCC_CFG2_ADC1MSEL_HSE ((uint32_t)0x00000400) /*!< HSE clock selected as ADC1M input clock */

/*!< ADC1MPRE configuration */
#define RCC_CFG2_ADC1MPRES   ((uint32_t)0x0000F800) /*!< ADC1MPRE[4:0] bits */
#define RCC_CFG2_ADC1MPRES_0 ((uint32_t)0x00000800) /*!< Bit 0 */
#define RCC_CFG2_ADC1MPRES_1 ((uint32_t)0x00001000) /*!< Bit 1 */
#define RCC_CFG2_ADC1MPRES_2 ((uint32_t)0x00002000) /*!< Bit 2 */
#define RCC_CFG2_ADC1MPRES_3 ((uint32_t)0x00004000) /*!< Bit 3 */
#define RCC_CFG2_ADC1MPRES_4 ((uint32_t)0x00008000) /*!< Bit 4 */

#define RCC_CFG2_ADC1MPRES_DIV1  ((uint32_t)0x00000000) /*!< ADC1M source clock is divided by 1 */
#define RCC_CFG2_ADC1MPRES_DIV2  ((uint32_t)0x00000800) /*!< ADC1M source clock is divided by 2 */
#define RCC_CFG2_ADC1MPRES_DIV3  ((uint32_t)0x00001000) /*!< ADC1M source clock is divided by 3 */
#define RCC_CFG2_ADC1MPRES_DIV4  ((uint32_t)0x00001800) /*!< ADC1M source clock is divided by 4 */
#define RCC_CFG2_ADC1MPRES_DIV5  ((uint32_t)0x00002000) /*!< ADC1M source clock is divided by 5 */
#define RCC_CFG2_ADC1MPRES_DIV6  ((uint32_t)0x00002800) /*!< ADC1M source clock is divided by 6 */
#define RCC_CFG2_ADC1MPRES_DIV7  ((uint32_t)0x00003000) /*!< ADC1M source clock is divided by 7 */
#define RCC_CFG2_ADC1MPRES_DIV8  ((uint32_t)0x00003800) /*!< ADC1M source clock is divided by 8 */
#define RCC_CFG2_ADC1MPRES_DIV9  ((uint32_t)0x00004000) /*!< ADC1M source clock is divided by 9 */
#define RCC_CFG2_ADC1MPRES_DIV10 ((uint32_t)0x00004800) /*!< ADC1M source clock is divided by 10 */
#define RCC_CFG2_ADC1MPRES_DIV11 ((uint32_t)0x00005000) /*!< ADC1M source clock is divided by 11 */
#define RCC_CFG2_ADC1MPRES_DIV12 ((uint32_t)0x00005800) /*!< ADC1M source clock is divided by 12 */
#define RCC_CFG2_ADC1MPRES_DIV13 ((uint32_t)0x00006000) /*!< ADC1M source clock is divided by 13 */
#define RCC_CFG2_ADC1MPRES_DIV14 ((uint32_t)0x00006800) /*!< ADC1M source clock is divided by 14 */
#define RCC_CFG2_ADC1MPRES_DIV15 ((uint32_t)0x00007000) /*!< ADC1M source clock is divided by 15 */
#define RCC_CFG2_ADC1MPRES_DIV16 ((uint32_t)0x00007800) /*!< ADC1M source clock is divided by 16 */
#define RCC_CFG2_ADC1MPRES_DIV17 ((uint32_t)0x00008000) /*!< ADC1M source clock is divided by 17 */
#define RCC_CFG2_ADC1MPRES_DIV18 ((uint32_t)0x00008800) /*!< ADC1M source clock is divided by 18 */
#define RCC_CFG2_ADC1MPRES_DIV19 ((uint32_t)0x00009000) /*!< ADC1M source clock is divided by 19 */
#define RCC_CFG2_ADC1MPRES_DIV20 ((uint32_t)0x00009800) /*!< ADC1M source clock is divided by 20 */
#define RCC_CFG2_ADC1MPRES_DIV21 ((uint32_t)0x0000A000) /*!< ADC1M source clock is divided by 21 */
#define RCC_CFG2_ADC1MPRES_DIV22 ((uint32_t)0x0000A800) /*!< ADC1M source clock is divided by 22 */
#define RCC_CFG2_ADC1MPRES_DIV23 ((uint32_t)0x0000B000) /*!< ADC1M source clock is divided by 23 */
#define RCC_CFG2_ADC1MPRES_DIV24 ((uint32_t)0x0000B800) /*!< ADC1M source clock is divided by 24 */
#define RCC_CFG2_ADC1MPRES_DIV25 ((uint32_t)0x0000C000) /*!< ADC1M source clock is divided by 25 */
#define RCC_CFG2_ADC1MPRES_DIV26 ((uint32_t)0x0000C800) /*!< ADC1M source clock is divided by 26 */
#define RCC_CFG2_ADC1MPRES_DIV27 ((uint32_t)0x0000D000) /*!< ADC1M source clock is divided by 27 */
#define RCC_CFG2_ADC1MPRES_DIV28 ((uint32_t)0x0000D800) /*!< ADC1M source clock is divided by 28 */
#define RCC_CFG2_ADC1MPRES_DIV29 ((uint32_t)0x0000E000) /*!< ADC1M source clock is divided by 29 */
#define RCC_CFG2_ADC1MPRES_DIV30 ((uint32_t)0x0000E800) /*!< ADC1M source clock is divided by 30 */
#define RCC_CFG2_ADC1MPRES_DIV31 ((uint32_t)0x0000F000) /*!< ADC1M source clock is divided by 31 */
#define RCC_CFG2_ADC1MPRES_DIV32 ((uint32_t)0x0000F800) /*!< ADC1M source clock is divided by 32 */

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
/*!< BORRSTEN configuration */
#define RCC_CFG3_BORRSTEN ((uint32_t)0x00000040) /*!< BOR reset enable */

#define RCC_CFG3_BORRSTEN_ENABLE  ((uint32_t)0x00000040) /*!< BOR reset enable */
#define RCC_CFG3_BORRSTEN_DISABLE ((uint32_t)0x00000000) /*!< BOR reset disable */

/*!< TRNG1MPRE configuration */
#define RCC_CFG3_TRNG1MPRES   ((uint32_t)0x0000F800) /*!< TRNG1MPRE[4:0] bits */
#define RCC_CFG3_TRNG1MPRES_0 ((uint32_t)0x00000800) /*!< Bit 0 */
#define RCC_CFG3_TRNG1MPRES_1 ((uint32_t)0x00001000) /*!< Bit 1 */
#define RCC_CFG3_TRNG1MPRES_2 ((uint32_t)0x00002000) /*!< Bit 2 */
#define RCC_CFG3_TRNG1MPRES_3 ((uint32_t)0x00004000) /*!< Bit 3 */
#define RCC_CFG3_TRNG1MPRES_4 ((uint32_t)0x00008000) /*!< Bit 4 */

#define RCC_CFG3_TRNG1MPRES_VAL1  ((uint32_t)0x00000000) /*!< TRNG 1M source clock is divided by 2 */
#define RCC_CFG3_TRNG1MPRES_VAL2  ((uint32_t)0x00000800) /*!< TRNG 1M source clock is divided by 2 */
#define RCC_CFG3_TRNG1MPRES_VAL3  ((uint32_t)0x00001000) /*!< TRNG 1M source clock is divided by 4 */
#define RCC_CFG3_TRNG1MPRES_VAL4  ((uint32_t)0x00001800) /*!< TRNG 1M source clock is divided by 4 */
#define RCC_CFG3_TRNG1MPRES_VAL5  ((uint32_t)0x00002000) /*!< TRNG 1M source clock is divided by 6 */
#define RCC_CFG3_TRNG1MPRES_VAL6  ((uint32_t)0x00002800) /*!< TRNG 1M source clock is divided by 6 */
#define RCC_CFG3_TRNG1MPRES_VAL7  ((uint32_t)0x00003000) /*!< TRNG 1M source clock is divided by 8 */
#define RCC_CFG3_TRNG1MPRES_VAL8  ((uint32_t)0x00003800) /*!< TRNG 1M source clock is divided by 8 */
#define RCC_CFG3_TRNG1MPRES_VAL9  ((uint32_t)0x00004000) /*!< TRNG 1M source clock is divided by 10 */
#define RCC_CFG3_TRNG1MPRES_VAL10 ((uint32_t)0x00004800) /*!< TRNG 1M source clock is divided by 10 */
#define RCC_CFG3_TRNG1MPRES_VAL11 ((uint32_t)0x00005000) /*!< TRNG 1M source clock is divided by 12 */
#define RCC_CFG3_TRNG1MPRES_VAL12 ((uint32_t)0x00005800) /*!< TRNG 1M source clock is divided by 12 */
#define RCC_CFG3_TRNG1MPRES_VAL13 ((uint32_t)0x00006000) /*!< TRNG 1M source clock is divided by 14 */
#define RCC_CFG3_TRNG1MPRES_VAL14 ((uint32_t)0x00006800) /*!< TRNG 1M source clock is divided by 14 */
#define RCC_CFG3_TRNG1MPRES_VAL15 ((uint32_t)0x00007000) /*!< TRNG 1M source clock is divided by 16 */
#define RCC_CFG3_TRNG1MPRES_VAL16 ((uint32_t)0x00007800) /*!< TRNG 1M source clock is divided by 16 */
#define RCC_CFG3_TRNG1MPRES_VAL17 ((uint32_t)0x00008000) /*!< TRNG 1M source clock is divided by 18 */
#define RCC_CFG3_TRNG1MPRES_VAL18 ((uint32_t)0x00008800) /*!< TRNG 1M source clock is divided by 18 */
#define RCC_CFG3_TRNG1MPRES_VAL19 ((uint32_t)0x00009000) /*!< TRNG 1M source clock is divided by 20 */
#define RCC_CFG3_TRNG1MPRES_VAL20 ((uint32_t)0x00009800) /*!< TRNG 1M source clock is divided by 20 */
#define RCC_CFG3_TRNG1MPRES_VAL21 ((uint32_t)0x0000A000) /*!< TRNG 1M source clock is divided by 22 */
#define RCC_CFG3_TRNG1MPRES_VAL22 ((uint32_t)0x0000A800) /*!< TRNG 1M source clock is divided by 22 */
#define RCC_CFG3_TRNG1MPRES_VAL23 ((uint32_t)0x0000B000) /*!< TRNG 1M source clock is divided by 24 */
#define RCC_CFG3_TRNG1MPRES_VAL24 ((uint32_t)0x0000B800) /*!< TRNG 1M source clock is divided by 24 */
#define RCC_CFG3_TRNG1MPRES_VAL25 ((uint32_t)0x0000C000) /*!< TRNG 1M source clock is divided by 26 */
#define RCC_CFG3_TRNG1MPRES_VAL26 ((uint32_t)0x0000C800) /*!< TRNG 1M source clock is divided by 26 */
#define RCC_CFG3_TRNG1MPRES_VAL27 ((uint32_t)0x0000D000) /*!< TRNG 1M source clock is divided by 28 */
#define RCC_CFG3_TRNG1MPRES_VAL28 ((uint32_t)0x0000D800) /*!< TRNG 1M source clock is divided by 28 */
#define RCC_CFG3_TRNG1MPRES_VAL29 ((uint32_t)0x0000E000) /*!< TRNG 1M source clock is divided by 30 */
#define RCC_CFG3_TRNG1MPRES_VAL30 ((uint32_t)0x0000E800) /*!< TRNG 1M source clock is divided by 30 */
#define RCC_CFG3_TRNG1MPRES_VAL31 ((uint32_t)0x0000F000) /*!< TRNG 1M source clock is divided by 32 */
#define RCC_CFG3_TRNG1MPRES_VAL32 ((uint32_t)0x0000F800) /*!< TRNG 1M source clock is divided by 32 */

/*!< TRNG1MSEL configuration */
#define RCC_CFG3_TRNG1MSEL ((uint32_t)0x00020000) /*!< TRNG_1M clock source select */

#define RCC_CFG3_TRNG1MSEL_HSI ((uint32_t)0x00000000) /*!< HSI clock selected as TRNG_1M input clock */
#define RCC_CFG3_TRNG1MSEL_HSE ((uint32_t)0x00020000) /*!< HSE clock selected as TRNG_1M input clock */

/*!< TRNG1MEN configuration */
#define RCC_CFG3_TRNG1MEN ((uint32_t)0x00040000) /*!< TRNG_1M clock enable */

#define RCC_CFG3_TRNG1MEN_DISABLE ((uint32_t)0x00000000) /*!< TRNG_1M clock disable */
#define RCC_CFG3_TRNG1MEN_ENABLE  ((uint32_t)0x00040000) /*!< TRNG_1M clock enable */

/******************************************************************************/
/*                                                                            */
/*                General Purpose and Alternate Function I/O                  */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for GPIO_PL_CFG register  *******************/
#define GPIO_PL_CFG_PMODE ((uint32_t)0x33333333) /*!< Port x mode bits */

#define GPIO_PL_CFG_PMODE0   ((uint32_t)0x00000003) /*!< MODE0[1:0] bits (Port x mode bits, pin 0) */
#define GPIO_PL_CFG_PMODE0_0 ((uint32_t)0x00000001) /*!< Bit 0 */
#define GPIO_PL_CFG_PMODE0_1 ((uint32_t)0x00000002) /*!< Bit 1 */

#define GPIO_PL_CFG_PMODE1   ((uint32_t)0x00000030) /*!< MODE1[1:0] bits (Port x mode bits, pin 1) */
#define GPIO_PL_CFG_PMODE1_0 ((uint32_t)0x00000010) /*!< Bit 0 */
#define GPIO_PL_CFG_PMODE1_1 ((uint32_t)0x00000020) /*!< Bit 1 */

#define GPIO_PL_CFG_PMODE2   ((uint32_t)0x00000300) /*!< MODE2[1:0] bits (Port x mode bits, pin 2) */
#define GPIO_PL_CFG_PMODE2_0 ((uint32_t)0x00000100) /*!< Bit 0 */
#define GPIO_PL_CFG_PMODE2_1 ((uint32_t)0x00000200) /*!< Bit 1 */

#define GPIO_PL_CFG_PMODE3   ((uint32_t)0x00003000) /*!< MODE3[1:0] bits (Port x mode bits, pin 3) */
#define GPIO_PL_CFG_PMODE3_0 ((uint32_t)0x00001000) /*!< Bit 0 */
#define GPIO_PL_CFG_PMODE3_1 ((uint32_t)0x00002000) /*!< Bit 1 */

#define GPIO_PL_CFG_PMODE4   ((uint32_t)0x00030000) /*!< MODE4[1:0] bits (Port x mode bits, pin 4) */
#define GPIO_PL_CFG_PMODE4_0 ((uint32_t)0x00010000) /*!< Bit 0 */
#define GPIO_PL_CFG_PMODE4_1 ((uint32_t)0x00020000) /*!< Bit 1 */

#define GPIO_PL_CFG_PMODE5   ((uint32_t)0x00300000) /*!< MODE5[1:0] bits (Port x mode bits, pin 5) */
#define GPIO_PL_CFG_PMODE5_0 ((uint32_t)0x00100000) /*!< Bit 0 */
#define GPIO_PL_CFG_PMODE5_1 ((uint32_t)0x00200000) /*!< Bit 1 */

#define GPIO_PL_CFG_PMODE6   ((uint32_t)0x03000000) /*!< MODE6[1:0] bits (Port x mode bits, pin 6) */
#define GPIO_PL_CFG_PMODE6_0 ((uint32_t)0x01000000) /*!< Bit 0 */
#define GPIO_PL_CFG_PMODE6_1 ((uint32_t)0x02000000) /*!< Bit 1 */

#define GPIO_PL_CFG_PMODE7   ((uint32_t)0x30000000) /*!< MODE7[1:0] bits (Port x mode bits, pin 7) */
#define GPIO_PL_CFG_PMODE7_0 ((uint32_t)0x10000000) /*!< Bit 0 */
#define GPIO_PL_CFG_PMODE7_1 ((uint32_t)0x20000000) /*!< Bit 1 */

#define GPIO_PL_CFG_PCFG ((uint32_t)0xCCCCCCCC) /*!< Port x configuration bits */

#define GPIO_PL_CFG_PCFG0   ((uint32_t)0x0000000C) /*!< CNF0[1:0] bits (Port x configuration bits, pin 0) */
#define GPIO_PL_CFG_PCFG0_0 ((uint32_t)0x00000004) /*!< Bit 0 */
#define GPIO_PL_CFG_PCFG0_1 ((uint32_t)0x00000008) /*!< Bit 1 */

#define GPIO_PL_CFG_PCFG1   ((uint32_t)0x000000C0) /*!< CNF1[1:0] bits (Port x configuration bits, pin 1) */
#define GPIO_PL_CFG_PCFG1_0 ((uint32_t)0x00000040) /*!< Bit 0 */
#define GPIO_PL_CFG_PCFG1_1 ((uint32_t)0x00000080) /*!< Bit 1 */

#define GPIO_PL_CFG_PCFG2   ((uint32_t)0x00000C00) /*!< CNF2[1:0] bits (Port x configuration bits, pin 2) */
#define GPIO_PL_CFG_PCFG2_0 ((uint32_t)0x00000400) /*!< Bit 0 */
#define GPIO_PL_CFG_PCFG2_1 ((uint32_t)0x00000800) /*!< Bit 1 */

#define GPIO_PL_CFG_PCFG3   ((uint32_t)0x0000C000) /*!< CNF3[1:0] bits (Port x configuration bits, pin 3) */
#define GPIO_PL_CFG_PCFG3_0 ((uint32_t)0x00004000) /*!< Bit 0 */
#define GPIO_PL_CFG_PCFG3_1 ((uint32_t)0x00008000) /*!< Bit 1 */

#define GPIO_PL_CFG_PCFG4   ((uint32_t)0x000C0000) /*!< CNF4[1:0] bits (Port x configuration bits, pin 4) */
#define GPIO_PL_CFG_PCFG4_0 ((uint32_t)0x00040000) /*!< Bit 0 */
#define GPIO_PL_CFG_PCFG4_1 ((uint32_t)0x00080000) /*!< Bit 1 */

#define GPIO_PL_CFG_PCFG5   ((uint32_t)0x00C00000) /*!< CNF5[1:0] bits (Port x configuration bits, pin 5) */
#define GPIO_PL_CFG_PCFG5_0 ((uint32_t)0x00400000) /*!< Bit 0 */
#define GPIO_PL_CFG_PCFG5_1 ((uint32_t)0x00800000) /*!< Bit 1 */

#define GPIO_PL_CFG_PCFG6   ((uint32_t)0x0C000000) /*!< CNF6[1:0] bits (Port x configuration bits, pin 6) */
#define GPIO_PL_CFG_PCFG6_0 ((uint32_t)0x04000000) /*!< Bit 0 */
#define GPIO_PL_CFG_PCFG6_1 ((uint32_t)0x08000000) /*!< Bit 1 */

#define GPIO_PL_CFG_PCFG7   ((uint32_t)0xC0000000) /*!< CNF7[1:0] bits (Port x configuration bits, pin 7) */
#define GPIO_PL_CFG_PCFG7_0 ((uint32_t)0x40000000) /*!< Bit 0 */
#define GPIO_PL_CFG_PCFG7_1 ((uint32_t)0x80000000) /*!< Bit 1 */

/*******************  Bit definition for GPIO_PH_CFG register  *******************/
#define GPIO_PH_CFG_PMODE ((uint32_t)0x33333333) /*!< Port x mode bits */

#define GPIO_PH_CFG_PMODE8   ((uint32_t)0x00000003) /*!< MODE8[1:0] bits (Port x mode bits, pin 8) */
#define GPIO_PH_CFG_PMODE8_0 ((uint32_t)0x00000001) /*!< Bit 0 */
#define GPIO_PH_CFG_PMODE8_1 ((uint32_t)0x00000002) /*!< Bit 1 */

#define GPIO_PH_CFG_PMODE1   ((uint32_t)0x00000030) /*!< MODE9[1:0] bits (Port x mode bits, pin 9) */
#define GPIO_PH_CFG_PMODE9_0 ((uint32_t)0x00000010) /*!< Bit 0 */
#define GPIO_PH_CFG_PMODE9_1 ((uint32_t)0x00000020) /*!< Bit 1 */

#define GPIO_PH_CFG_PMODE10   ((uint32_t)0x00000300) /*!< MODE10[1:0] bits (Port x mode bits, pin 10) */
#define GPIO_PH_CFG_PMODE10_0 ((uint32_t)0x00000100) /*!< Bit 0 */
#define GPIO_PH_CFG_PMODE10_1 ((uint32_t)0x00000200) /*!< Bit 1 */

#define GPIO_PH_CFG_PMODE11   ((uint32_t)0x00003000) /*!< MODE11[1:0] bits (Port x mode bits, pin 11) */
#define GPIO_PH_CFG_PMODE11_0 ((uint32_t)0x00001000) /*!< Bit 0 */
#define GPIO_PH_CFG_PMODE11_1 ((uint32_t)0x00002000) /*!< Bit 1 */

#define GPIO_PH_CFG_PMODE12   ((uint32_t)0x00030000) /*!< MODE12[1:0] bits (Port x mode bits, pin 12) */
#define GPIO_PH_CFG_PMODE12_0 ((uint32_t)0x00010000) /*!< Bit 0 */
#define GPIO_PH_CFG_PMODE12_1 ((uint32_t)0x00020000) /*!< Bit 1 */

#define GPIO_PH_CFG_PMODE13   ((uint32_t)0x00300000) /*!< MODE13[1:0] bits (Port x mode bits, pin 13) */
#define GPIO_PH_CFG_PMODE13_0 ((uint32_t)0x00100000) /*!< Bit 0 */
#define GPIO_PH_CFG_PMODE13_1 ((uint32_t)0x00200000) /*!< Bit 1 */

#define GPIO_PH_CFG_PMODE14   ((uint32_t)0x03000000) /*!< MODE14[1:0] bits (Port x mode bits, pin 14) */
#define GPIO_PH_CFG_PMODE14_0 ((uint32_t)0x01000000) /*!< Bit 0 */
#define GPIO_PH_CFG_PMODE14_1 ((uint32_t)0x02000000) /*!< Bit 1 */

#define GPIO_PH_CFG_PMODE15   ((uint32_t)0x30000000) /*!< MODE15[1:0] bits (Port x mode bits, pin 15) */
#define GPIO_PH_CFG_PMODE15_0 ((uint32_t)0x10000000) /*!< Bit 0 */
#define GPIO_PH_CFG_PMODE15_1 ((uint32_t)0x20000000) /*!< Bit 1 */

#define GPIO_PH_CFG_PCFG ((uint32_t)0xCCCCCCCC) /*!< Port x configuration bits */

#define GPIO_PH_CFG_PCFG8   ((uint32_t)0x0000000C) /*!< CNF8[1:0] bits (Port x configuration bits, pin 8) */
#define GPIO_PH_CFG_PCFG8_0 ((uint32_t)0x00000004) /*!< Bit 0 */
#define GPIO_PH_CFG_PCFG8_1 ((uint32_t)0x00000008) /*!< Bit 1 */

#define GPIO_PH_CFG_PCFG9   ((uint32_t)0x000000C0) /*!< CNF9[1:0] bits (Port x configuration bits, pin 9) */
#define GPIO_PH_CFG_PCFG9_0 ((uint32_t)0x00000040) /*!< Bit 0 */
#define GPIO_PH_CFG_PCFG9_1 ((uint32_t)0x00000080) /*!< Bit 1 */

#define GPIO_PH_CFG_PCFG10   ((uint32_t)0x00000C00) /*!< CNF10[1:0] bits (Port x configuration bits, pin 10) */
#define GPIO_PH_CFG_PCFG10_0 ((uint32_t)0x00000400) /*!< Bit 0 */
#define GPIO_PH_CFG_PCFG10_1 ((uint32_t)0x00000800) /*!< Bit 1 */

#define GPIO_PH_CFG_PCFG11   ((uint32_t)0x0000C000) /*!< CNF11[1:0] bits (Port x configuration bits, pin 11) */
#define GPIO_PH_CFG_PCFG11_0 ((uint32_t)0x00004000) /*!< Bit 0 */
#define GPIO_PH_CFG_PCFG11_1 ((uint32_t)0x00008000) /*!< Bit 1 */

#define GPIO_PH_CFG_PCFG12   ((uint32_t)0x000C0000) /*!< CNF12[1:0] bits (Port x configuration bits, pin 12) */
#define GPIO_PH_CFG_PCFG12_0 ((uint32_t)0x00040000) /*!< Bit 0 */
#define GPIO_PH_CFG_PCFG12_1 ((uint32_t)0x00080000) /*!< Bit 1 */

#define GPIO_PH_CFG_PCFG13   ((uint32_t)0x00C00000) /*!< CNF13[1:0] bits (Port x configuration bits, pin 13) */
#define GPIO_PH_CFG_PCFG13_0 ((uint32_t)0x00400000) /*!< Bit 0 */
#define GPIO_PH_CFG_PCFG13_1 ((uint32_t)0x00800000) /*!< Bit 1 */

#define GPIO_PH_CFG_PCFG14   ((uint32_t)0x0C000000) /*!< CNF14[1:0] bits (Port x configuration bits, pin 14) */
#define GPIO_PH_CFG_PCFG14_0 ((uint32_t)0x04000000) /*!< Bit 0 */
#define GPIO_PH_CFG_PCFG14_1 ((uint32_t)0x08000000) /*!< Bit 1 */

#define GPIO_PH_CFG_PCFG15   ((uint32_t)0xC0000000) /*!< CNF15[1:0] bits (Port x configuration bits, pin 15) */
#define GPIO_PH_CFG_PCFG15_0 ((uint32_t)0x40000000) /*!< Bit 0 */
#define GPIO_PH_CFG_PCFG15_1 ((uint32_t)0x80000000) /*!< Bit 1 */

/*!<******************  Bit definition for GPIO_PID register  *******************/
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

/******************  Bit definition for GPIO_PBSC register  *******************/
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

/*******************  Bit definition for GPIO_PBC register  *******************/
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

/******************  Bit definition for GPIO_PLOCK_CFG register  *******************/
#define GPIO_PLOCK_CFG_PLOCK_CFG0  ((uint32_t)0x00000001) /*!< Port x Lock bit 0 */
#define GPIO_PLOCK_CFG_PLOCK_CFG1  ((uint32_t)0x00000002) /*!< Port x Lock bit 1 */
#define GPIO_PLOCK_CFG_PLOCK_CFG2  ((uint32_t)0x00000004) /*!< Port x Lock bit 2 */
#define GPIO_PLOCK_CFG_PLOCK_CFG3  ((uint32_t)0x00000008) /*!< Port x Lock bit 3 */
#define GPIO_PLOCK_CFG_PLOCK_CFG4  ((uint32_t)0x00000010) /*!< Port x Lock bit 4 */
#define GPIO_PLOCK_CFG_PLOCK_CFG5  ((uint32_t)0x00000020) /*!< Port x Lock bit 5 */
#define GPIO_PLOCK_CFG_PLOCK_CFG6  ((uint32_t)0x00000040) /*!< Port x Lock bit 6 */
#define GPIO_PLOCK_CFG_PLOCK_CFG7  ((uint32_t)0x00000080) /*!< Port x Lock bit 7 */
#define GPIO_PLOCK_CFG_PLOCK_CFG8  ((uint32_t)0x00000100) /*!< Port x Lock bit 8 */
#define GPIO_PLOCK_CFG_PLOCK_CFG9  ((uint32_t)0x00000200) /*!< Port x Lock bit 9 */
#define GPIO_PLOCK_CFG_PLOCK_CFG10 ((uint32_t)0x00000400) /*!< Port x Lock bit 10 */
#define GPIO_PLOCK_CFG_PLOCK_CFG11 ((uint32_t)0x00000800) /*!< Port x Lock bit 11 */
#define GPIO_PLOCK_CFG_PLOCK_CFG12 ((uint32_t)0x00001000) /*!< Port x Lock bit 12 */
#define GPIO_PLOCK_CFG_PLOCK_CFG13 ((uint32_t)0x00002000) /*!< Port x Lock bit 13 */
#define GPIO_PLOCK_CFG_PLOCK_CFG14 ((uint32_t)0x00004000) /*!< Port x Lock bit 14 */
#define GPIO_PLOCK_CFG_PLOCK_CFG15 ((uint32_t)0x00008000) /*!< Port x Lock bit 15 */
#define GPIO_PLOCK_CFG_PLOCKK_CFG  ((uint32_t)0x00010000) /*!< Lock key */

/*******************  Bit definition for GPIO_DS_CFG register  *******************/
#define GPIO_DS_CFG0  ((uint16_t)0x0001) /*!< Port x Drive bit 0 */
#define GPIO_DS_CFG1  ((uint16_t)0x0002) /*!< Port x Drive bit 1 */
#define GPIO_DS_CFG2  ((uint16_t)0x0004) /*!< Port x Drive bit 2 */
#define GPIO_DS_CFG3  ((uint16_t)0x0008) /*!< Port x Drive bit 3 */
#define GPIO_DS_CFG4  ((uint16_t)0x0010) /*!< Port x Drive bit 4 */
#define GPIO_DS_CFG5  ((uint16_t)0x0020) /*!< Port x Drive bit 5 */
#define GPIO_DS_CFG6  ((uint16_t)0x0040) /*!< Port x Drive bit 6 */
#define GPIO_DS_CFG7  ((uint16_t)0x0080) /*!< Port x Drive bit 7 */
#define GPIO_DS_CFG8  ((uint16_t)0x0100) /*!< Port x Drive bit 8 */
#define GPIO_DS_CFG9  ((uint16_t)0x0200) /*!< Port x Drive bit 9 */
#define GPIO_DS_CFG10 ((uint16_t)0x0400) /*!< Port x Drive bit 10 */
#define GPIO_DS_CFG11 ((uint16_t)0x0800) /*!< Port x Drive bit 11 */
#define GPIO_DS_CFG12 ((uint16_t)0x1000) /*!< Port x Drive bit 12 */
#define GPIO_DS_CFG13 ((uint16_t)0x2000) /*!< Port x Drive bit 13 */
#define GPIO_DS_CFG14 ((uint16_t)0x4000) /*!< Port x Drive bit 14 */
#define GPIO_DS_CFG15 ((uint16_t)0x8000) /*!< Port x Drive bit 15 */

/*******************  Bit definition for GPIO_SR_CFG register  *******************/
#define GPIO_SR_CFG0  ((uint16_t)0x0001) /*!< Port x Turn bit 0 */
#define GPIO_SR_CFG1  ((uint16_t)0x0002) /*!< Port x Turn bit 1 */
#define GPIO_SR_CFG2  ((uint16_t)0x0004) /*!< Port x Turn bit 2 */
#define GPIO_SR_CFG3  ((uint16_t)0x0008) /*!< Port x Turn bit 3 */
#define GPIO_SR_CFG4  ((uint16_t)0x0010) /*!< Port x Turn bit 4 */
#define GPIO_SR_CFG5  ((uint16_t)0x0020) /*!< Port x Turn bit 5 */
#define GPIO_SR_CFG6  ((uint16_t)0x0040) /*!< Port x Turn bit 6 */
#define GPIO_SR_CFG7  ((uint16_t)0x0080) /*!< Port x Turn bit 7 */
#define GPIO_SR_CFG8  ((uint16_t)0x0100) /*!< Port x Turn bit 8 */
#define GPIO_SR_CFG9  ((uint16_t)0x0200) /*!< Port x Turn bit 9 */
#define GPIO_SR_CFG10 ((uint16_t)0x0400) /*!< Port x Turn bit 10 */
#define GPIO_SR_CFG11 ((uint16_t)0x0800) /*!< Port x Turn bit 11 */
#define GPIO_SR_CFG12 ((uint16_t)0x1000) /*!< Port x Turn bit 12 */
#define GPIO_SR_CFG13 ((uint16_t)0x2000) /*!< Port x Turn bit 13 */
#define GPIO_SR_CFG14 ((uint16_t)0x4000) /*!< Port x Turn bit 14 */
#define GPIO_SR_CFG15 ((uint16_t)0x8000) /*!< Port x Turn bit 15 */

/*----------------------------------------------------------------------------*/

/******************  Bit definition for AFIO_ECTRL register  *******************/
#define AFIO_ECTRL_PIN_SEL   ((uint8_t)0x0F) /*!< PIN[3:0] bits (Pin selection) */
#define AFIO_ECTRL_PIN_SEL_0 ((uint8_t)0x01) /*!< Bit 0 */
#define AFIO_ECTRL_PIN_SEL_1 ((uint8_t)0x02) /*!< Bit 1 */
#define AFIO_ECTRL_PIN_SEL_2 ((uint8_t)0x04) /*!< Bit 2 */
#define AFIO_ECTRL_PIN_SEL_3 ((uint8_t)0x08) /*!< Bit 3 */

/*!< PIN configuration */
#define AFIO_ECTRL_PIN_SEL_PIN0  ((uint8_t)0x00) /*!< Pin 0 selected */
#define AFIO_ECTRL_PIN_SEL_PIN1  ((uint8_t)0x01) /*!< Pin 1 selected */
#define AFIO_ECTRL_PIN_SEL_PIN2  ((uint8_t)0x02) /*!< Pin 2 selected */
#define AFIO_ECTRL_PIN_SEL_PIN3  ((uint8_t)0x03) /*!< Pin 3 selected */
#define AFIO_ECTRL_PIN_SEL_PIN4  ((uint8_t)0x04) /*!< Pin 4 selected */
#define AFIO_ECTRL_PIN_SEL_PIN5  ((uint8_t)0x05) /*!< Pin 5 selected */
#define AFIO_ECTRL_PIN_SEL_PIN6  ((uint8_t)0x06) /*!< Pin 6 selected */
#define AFIO_ECTRL_PIN_SEL_PIN7  ((uint8_t)0x07) /*!< Pin 7 selected */
#define AFIO_ECTRL_PIN_SEL_PIN8  ((uint8_t)0x08) /*!< Pin 8 selected */
#define AFIO_ECTRL_PIN_SEL_PIN9  ((uint8_t)0x09) /*!< Pin 9 selected */
#define AFIO_ECTRL_PIN_SEL_PIN10 ((uint8_t)0x0A) /*!< Pin 10 selected */
#define AFIO_ECTRL_PIN_SEL_PIN11 ((uint8_t)0x0B) /*!< Pin 11 selected */
#define AFIO_ECTRL_PIN_SEL_PIN12 ((uint8_t)0x0C) /*!< Pin 12 selected */
#define AFIO_ECTRL_PIN_SEL_PIN13 ((uint8_t)0x0D) /*!< Pin 13 selected */
#define AFIO_ECTRL_PIN_SEL_PIN14 ((uint8_t)0x0E) /*!< Pin 14 selected */
#define AFIO_ECTRL_PIN_SEL_PIN15 ((uint8_t)0x0F) /*!< Pin 15 selected */

#define AFIO_ECTRL_PORT_SEL   ((uint8_t)0x70) /*!< PORT[2:0] bits (Port selection) */
#define AFIO_ECTRL_PORT_SEL_0 ((uint8_t)0x10) /*!< Bit 0 */
#define AFIO_ECTRL_PORT_SEL_1 ((uint8_t)0x20) /*!< Bit 1 */
#define AFIO_ECTRL_PORT_SEL_2 ((uint8_t)0x40) /*!< Bit 2 */

/*!< PORT configuration */
#define AFIO_ECTRL_PORT_SEL_PA ((uint8_t)0x00) /*!< Port A selected */
#define AFIO_ECTRL_PORT_SEL_PB ((uint8_t)0x10) /*!< Port B selected */
#define AFIO_ECTRL_PORT_SEL_PC ((uint8_t)0x20) /*!< Port C selected */
#define AFIO_ECTRL_PORT_SEL_PD ((uint8_t)0x30) /*!< Port D selected */
#define AFIO_ECTRL_PORT_SEL_PE ((uint8_t)0x40) /*!< Port E selected */

#define AFIO_ECTRL_EOE ((uint8_t)0x80) /*!< Event Output Enable */

/******************  Bit definition for AFIO_RMP_CFG register  *******************/
#define AFIO_RMP_CFG_SPI1_RMP_0   ((uint32_t)0x00000001) /*!< SPI1_RMP_0 remapping */
#define AFIO_RMP_CFG_I2C1_RMP     ((uint32_t)0x00000002) /*!< I2C1 remapping */
#define AFIO_RMP_CFG_USART1_RMP   ((uint32_t)0x00000004) /*!< USART1 remapping */
#define AFIO_RMP_CFG_USART2_RMP_0 ((uint32_t)0x00000008) /*!< USART2_RMP_0 remapping */

#define AFIO_RMP_CFG_USART3_RMP   ((uint32_t)0x00000030) /*!< USART3_REMAP[1:0] bits (USART3 remapping) */
#define AFIO_RMP_CFG_USART3_RMP_0 ((uint32_t)0x00000010) /*!< Bit 0 */
#define AFIO_RMP_CFG_USART3_RMP_1 ((uint32_t)0x00000020) /*!< Bit 1 */

/* USART3_REMAP configuration */
#define AFIO_RMP_CFG_USART3_RMP_NONE                                                                                   \
    ((uint32_t)0x00000000) /*!< No remap (TX/PB10, RX/PB11, CK/PB12, CTS/PB13, RTS/PB14) */
#define AFIO_RMP_CFG_USART3_RMP_PART                                                                                   \
    ((uint32_t)0x00000010) /*!< Partial remap (TX/PC10, RX/PC11, CK/PC12, CTS/PB13, RTS/PB14) */
#define AFIO_RMP_CFG_USART3_RMP_ALL                                                                                    \
    ((uint32_t)0x00000030) /*!< Full remap (TX/PD8, RX/PD9, CK/PD10, CTS/PD11, RTS/PD12) */

#define AFIO_RMP_CFG_TIM1_RMP   ((uint32_t)0x000000C0) /*!< TIM1_REMAP[1:0] bits (TIM1 remapping) */
#define AFIO_RMP_CFG_TIM1_RMP_0 ((uint32_t)0x00000040) /*!< Bit 0 */
#define AFIO_RMP_CFG_TIM1_RMP_1 ((uint32_t)0x00000080) /*!< Bit 1 */

/*!< TIM1_REMAP configuration */
#define AFIO_RMP_CFG_TIM1_RMP_NONE                                                                                     \
    ((uint32_t)0x00000000) /*!< No remap (ETR/PA12, CH1/PA8, CH2/PA9, CH3/PA10, CH4/PA11, BKIN/PB12, CH1N/PB13,        \
                              CH2N/PB14, CH3N/PB15) */
#define AFIO_RMP_CFG_TIM1_RMP_PART                                                                                     \
    ((uint32_t)0x00000040) /*!< Partial remap (ETR/PA12, CH1/PA8, CH2/PA9, CH3/PA10, CH4/PA11, BKIN/PA6, CH1N/PA7,     \
                              CH2N/PB0, CH3N/PB1) */
#define AFIO_RMP_CFG_TIM1_RMP_ALL                                                                                      \
    ((uint32_t)0x000000C0) /*!< Full remap (ETR/PE7, CH1/PE9, CH2/PE11, CH3/PE13, CH4/PE14, BKIN/PE15, CH1N/PE8,       \
                              CH2N/PE10, CH3N/PE12) */

#define AFIO_RMP_CFG_TIM2_RMP   ((uint32_t)0x00000300) /*!< TIM2_REMAP[1:0] bits (TIM2 remapping) */
#define AFIO_RMP_CFG_TIM2_RMP_0 ((uint32_t)0x00000100) /*!< Bit 0 */
#define AFIO_RMP_CFG_TIM2_RMP_1 ((uint32_t)0x00000200) /*!< Bit 1 */

/*!< TIM2_REMAP configuration */
#define AFIO_RMP_CFG_TIM2_RMP_NONE ((uint32_t)0x00000000) /*!< No remap (CH1/ETR/PA0, CH2/PA1, CH3/PA2, CH4/PA3) */
#define AFIO_RMP_CFG_TIM2_RMP_PART1                                                                                    \
    ((uint32_t)0x00000100) /*!< Partial remap (CH1/ETR/PA15, CH2/PB3, CH3/PA2, CH4/PA3) */
#define AFIO_RMP_CFG_TIM2_RMP_PART2                                                                                    \
    ((uint32_t)0x00000200) /*!< Partial remap (CH1/ETR/PA0, CH2/PA1, CH3/PB10, CH4/PB11) */
#define AFIO_RMP_CFG_TIM2_RMP_ALL                                                                                      \
    ((uint32_t)0x00000300) /*!< Full remap (CH1/ETR/PA15, CH2/PB3, CH3/PB10, CH4/PB11)                                 \
                            */

#define AFIO_RMP_CFG_TIM3_RMP   ((uint32_t)0x00000C00) /*!< TIM3_REMAP[1:0] bits (TIM3 remapping) */
#define AFIO_RMP_CFG_TIM3_RMP_0 ((uint32_t)0x00000400) /*!< Bit 0 */
#define AFIO_RMP_CFG_TIM3_RMP_1 ((uint32_t)0x00000800) /*!< Bit 1 */

/*!< TIM3_REMAP configuration */
#define AFIO_RMP_CFG_TIM3_RMP_NONE ((uint32_t)0x00000000) /*!< No remap (CH1/PA6, CH2/PA7, CH3/PB0, CH4/PB1) */
#define AFIO_RMP_CFG_TIM3_RMP_PART ((uint32_t)0x00000800) /*!< Partial remap (CH1/PB4, CH2/PB5, CH3/PB0, CH4/PB1) */
#define AFIO_RMP_CFG_TIM3_RMP_ALL  ((uint32_t)0x00000C00) /*!< Full remap (CH1/PC6, CH2/PC7, CH3/PC8, CH4/PC9) */

#define AFIO_RMP_CFG_TIM4_RMP ((uint32_t)0x00001000) /*!< TIM4_REMAP bit (TIM4 remapping) */

#define AFIO_RMP_CFG_CAN1_RMP   ((uint32_t)0x00006000) /*!< CAN1_RMP[1:0] bits (CAN1 Alternate function remapping) */
#define AFIO_RMP_CFG_CAN1_RMP_0 ((uint32_t)0x00002000) /*!< Bit 0 */
#define AFIO_RMP_CFG_CAN1_RMP_1 ((uint32_t)0x00004000) /*!< Bit 1 */

/*!< CAN1_REMAP configuration */
#define AFIO_RMP_CFG_CAN1_RMP_RMP1 ((uint32_t)0x00000000) /*!< CAN1RX mapped to PA11, CAN1TX mapped to PA12 */
#define AFIO_RMP_CFG_CAN1_RMP_RMP2 ((uint32_t)0x00004000) /*!< CAN1RX mapped to PB8, CAN1TX mapped to PB9 */
#define AFIO_RMP_CFG_CAN1_RMP_RMP3 ((uint32_t)0x00006000) /*!< CAN1RX mapped to PD0, CAN1TX mapped to PD1 */
#define AFIO_RMP_CFG_CAN1_RMP_RMP4 ((uint32_t)0x00002000) /*!< CAN1RX mapped to PD12, CAN1TX mapped to PD13 */

#define AFIO_RMP_CFG_PD01_RMP      ((uint32_t)0x00008000) /*!< Port D0/Port D1 mapping on OSC_IN/OSC_OUT */
#define AFIO_RMP_CFG_TIM5CH4_RMP   ((uint32_t)0x00010000) /*!< TIM5 Channel4 Internal Remap */
#define AFIO_RMP_CFG_ADC1_ETRI_RMP ((uint32_t)0x00020000) /*!< ADC 1 External Trigger Injected Conversion remapping */
#define AFIO_RMP_CFG_ADC1_ETRR_RMP ((uint32_t)0x00040000) /*!< ADC 1 External Trigger Regular Conversion remapping */
#define AFIO_RMP_CFG_ADC2_ETRI_RMP ((uint32_t)0x00080000) /*!< ADC 2 External Trigger Injected Conversion remapping */
#define AFIO_RMP_CFG_ADC2_ETRR_RMP ((uint32_t)0x00100000) /*!< ADC 2 External Trigger Regular Conversion remapping */
#define AFIO_RMP_CFG_MII_RMII_SEL  ((uint32_t)0x00800000) /*!< ETH MAC MII_RMII_SEL remapping */
/*!< SWJ_CFG configuration */
#define AFIO_RMP_CFG_SW_JTAG_CFG  ((uint32_t)0x07000000) /*!< SWJ_CFG[2:0] bits (Serial Wire JTAG configuration) */
#define AFIO_RMP_CFG_SW_JTAG_CFG0 ((uint32_t)0x01000000) /*!< Bit 0 */
#define AFIO_RMP_CFG_SW_JTAG_CFG1 ((uint32_t)0x02000000) /*!< Bit 1 */
#define AFIO_RMP_CFG_SW_JTAG_CFG2 ((uint32_t)0x04000000) /*!< Bit 2 */

#define AFIO_RMP_CFG_SW_JTAG_CFG_RESET ((uint32_t)0x00000000) /*!< Full SWJ (JTAG-DP + SW-DP) : Reset State */
#define AFIO_RMP_CFG_SW_JTAG_CFG_NO_NJTRST  ((uint32_t)0x01000000)    /*!< Full SWJ (JTAG-DP + SW-DP) but without JNTRST   \
                                                                   */
#define AFIO_RMP_CFG_SW_JTAG_CFG_SW_ENABLE ((uint32_t)0x02000000) /*!< JTAG-DP Disabled and SW-DP Enabled */
#define AFIO_RMP_CFG_SW_JTAG_CFG_DISABLE   ((uint32_t)0x04000000) /*!< JTAG-DP Disabled and SW-DP Disabled */

/*****************  Bit definition for AFIO_EXTI_CFG1 register  *****************/
#define AFIO_EXTI_CFG1_EXTI0 ((uint16_t)0x000F) /*!< EXTI 0 configuration */
#define AFIO_EXTI_CFG1_EXTI1 ((uint16_t)0x00F0) /*!< EXTI 1 configuration */
#define AFIO_EXTI_CFG1_EXTI2 ((uint16_t)0x0F00) /*!< EXTI 2 configuration */
#define AFIO_EXTI_CFG1_EXTI3 ((uint16_t)0xF000) /*!< EXTI 3 configuration */

/*!< EXTI0 configuration */
#define AFIO_EXTI_CFG1_EXTI0_PA ((uint16_t)0x0000) /*!< PA[0] pin */
#define AFIO_EXTI_CFG1_EXTI0_PB ((uint16_t)0x0001) /*!< PB[0] pin */
#define AFIO_EXTI_CFG1_EXTI0_PC ((uint16_t)0x0002) /*!< PC[0] pin */
#define AFIO_EXTI_CFG1_EXTI0_PD ((uint16_t)0x0003) /*!< PD[0] pin */
#define AFIO_EXTI_CFG1_EXTI0_PE ((uint16_t)0x0004) /*!< PE[0] pin */
#define AFIO_EXTI_CFG1_EXTI0_PF ((uint16_t)0x0005) /*!< PF[0] pin */
#define AFIO_EXTI_CFG1_EXTI0_PG ((uint16_t)0x0006) /*!< PG[0] pin */

/*!< EXTI1 configuration */
#define AFIO_EXTI_CFG1_EXTI1_PA ((uint16_t)0x0000) /*!< PA[1] pin */
#define AFIO_EXTI_CFG1_EXTI1_PB ((uint16_t)0x0010) /*!< PB[1] pin */
#define AFIO_EXTI_CFG1_EXTI1_PC ((uint16_t)0x0020) /*!< PC[1] pin */
#define AFIO_EXTI_CFG1_EXTI1_PD ((uint16_t)0x0030) /*!< PD[1] pin */
#define AFIO_EXTI_CFG1_EXTI1_PE ((uint16_t)0x0040) /*!< PE[1] pin */
#define AFIO_EXTI_CFG1_EXTI1_PF ((uint16_t)0x0050) /*!< PF[1] pin */
#define AFIO_EXTI_CFG1_EXTI1_PG ((uint16_t)0x0060) /*!< PG[1] pin */

/*!< EXTI2 configuration */
#define AFIO_EXTI_CFG1_EXTI2_PA ((uint16_t)0x0000) /*!< PA[2] pin */
#define AFIO_EXTI_CFG1_EXTI2_PB ((uint16_t)0x0100) /*!< PB[2] pin */
#define AFIO_EXTI_CFG1_EXTI2_PC ((uint16_t)0x0200) /*!< PC[2] pin */
#define AFIO_EXTI_CFG1_EXTI2_PD ((uint16_t)0x0300) /*!< PD[2] pin */
#define AFIO_EXTI_CFG1_EXTI2_PE ((uint16_t)0x0400) /*!< PE[2] pin */
#define AFIO_EXTI_CFG1_EXTI2_PF ((uint16_t)0x0500) /*!< PF[2] pin */
#define AFIO_EXTI_CFG1_EXTI2_PG ((uint16_t)0x0600) /*!< PG[2] pin */

/*!< EXTI3 configuration */
#define AFIO_EXTI_CFG1_EXTI3_PA ((uint16_t)0x0000) /*!< PA[3] pin */
#define AFIO_EXTI_CFG1_EXTI3_PB ((uint16_t)0x1000) /*!< PB[3] pin */
#define AFIO_EXTI_CFG1_EXTI3_PC ((uint16_t)0x2000) /*!< PC[3] pin */
#define AFIO_EXTI_CFG1_EXTI3_PD ((uint16_t)0x3000) /*!< PD[3] pin */
#define AFIO_EXTI_CFG1_EXTI3_PE ((uint16_t)0x4000) /*!< PE[3] pin */
#define AFIO_EXTI_CFG1_EXTI3_PF ((uint16_t)0x5000) /*!< PF[3] pin */
#define AFIO_EXTI_CFG1_EXTI3_PG ((uint16_t)0x6000) /*!< PG[3] pin */

/*****************  Bit definition for AFIO_EXTI_CFG2 register  *****************/
#define AFIO_EXTI_CFG2_EXTI4 ((uint16_t)0x000F) /*!< EXTI 4 configuration */
#define AFIO_EXTI_CFG2_EXTI5 ((uint16_t)0x00F0) /*!< EXTI 5 configuration */
#define AFIO_EXTI_CFG2_EXTI6 ((uint16_t)0x0F00) /*!< EXTI 6 configuration */
#define AFIO_EXTI_CFG2_EXTI7 ((uint16_t)0xF000) /*!< EXTI 7 configuration */

/*!< EXTI4 configuration */
#define AFIO_EXTI_CFG2_EXTI4_PA ((uint16_t)0x0000) /*!< PA[4] pin */
#define AFIO_EXTI_CFG2_EXTI4_PB ((uint16_t)0x0001) /*!< PB[4] pin */
#define AFIO_EXTI_CFG2_EXTI4_PC ((uint16_t)0x0002) /*!< PC[4] pin */
#define AFIO_EXTI_CFG2_EXTI4_PD ((uint16_t)0x0003) /*!< PD[4] pin */
#define AFIO_EXTI_CFG2_EXTI4_PE ((uint16_t)0x0004) /*!< PE[4] pin */
#define AFIO_EXTI_CFG2_EXTI4_PF ((uint16_t)0x0005) /*!< PF[4] pin */
#define AFIO_EXTI_CFG2_EXTI4_PG ((uint16_t)0x0006) /*!< PG[4] pin */

/* EXTI5 configuration */
#define AFIO_EXTI_CFG2_EXTI5_PA ((uint16_t)0x0000) /*!< PA[5] pin */
#define AFIO_EXTI_CFG2_EXTI5_PB ((uint16_t)0x0010) /*!< PB[5] pin */
#define AFIO_EXTI_CFG2_EXTI5_PC ((uint16_t)0x0020) /*!< PC[5] pin */
#define AFIO_EXTI_CFG2_EXTI5_PD ((uint16_t)0x0030) /*!< PD[5] pin */
#define AFIO_EXTI_CFG2_EXTI5_PE ((uint16_t)0x0040) /*!< PE[5] pin */
#define AFIO_EXTI_CFG2_EXTI5_PF ((uint16_t)0x0050) /*!< PF[5] pin */
#define AFIO_EXTI_CFG2_EXTI5_PG ((uint16_t)0x0060) /*!< PG[5] pin */

/*!< EXTI6 configuration */
#define AFIO_EXTI_CFG2_EXTI6_PA ((uint16_t)0x0000) /*!< PA[6] pin */
#define AFIO_EXTI_CFG2_EXTI6_PB ((uint16_t)0x0100) /*!< PB[6] pin */
#define AFIO_EXTI_CFG2_EXTI6_PC ((uint16_t)0x0200) /*!< PC[6] pin */
#define AFIO_EXTI_CFG2_EXTI6_PD ((uint16_t)0x0300) /*!< PD[6] pin */
#define AFIO_EXTI_CFG2_EXTI6_PE ((uint16_t)0x0400) /*!< PE[6] pin */
#define AFIO_EXTI_CFG2_EXTI6_PF ((uint16_t)0x0500) /*!< PF[6] pin */
#define AFIO_EXTI_CFG2_EXTI6_PG ((uint16_t)0x0600) /*!< PG[6] pin */

/*!< EXTI7 configuration */
#define AFIO_EXTI_CFG2_EXTI7_PA ((uint16_t)0x0000) /*!< PA[7] pin */
#define AFIO_EXTI_CFG2_EXTI7_PB ((uint16_t)0x1000) /*!< PB[7] pin */
#define AFIO_EXTI_CFG2_EXTI7_PC ((uint16_t)0x2000) /*!< PC[7] pin */
#define AFIO_EXTI_CFG2_EXTI7_PD ((uint16_t)0x3000) /*!< PD[7] pin */
#define AFIO_EXTI_CFG2_EXTI7_PE ((uint16_t)0x4000) /*!< PE[7] pin */
#define AFIO_EXTI_CFG2_EXTI7_PF ((uint16_t)0x5000) /*!< PF[7] pin */
#define AFIO_EXTI_CFG2_EXTI7_PG ((uint16_t)0x6000) /*!< PG[7] pin */

/*****************  Bit definition for AFIO_EXTI_CFG3 register  *****************/
#define AFIO_EXTI_CFG3_EXTI8  ((uint16_t)0x000F) /*!< EXTI 8 configuration */
#define AFIO_EXTI_CFG3_EXTI9  ((uint16_t)0x00F0) /*!< EXTI 9 configuration */
#define AFIO_EXTI_CFG3_EXTI10 ((uint16_t)0x0F00) /*!< EXTI 10 configuration */
#define AFIO_EXTI_CFG3_EXTI11 ((uint16_t)0xF000) /*!< EXTI 11 configuration */

/*!< EXTI8 configuration */
#define AFIO_EXTI_CFG3_EXTI8_PA ((uint16_t)0x0000) /*!< PA[8] pin */
#define AFIO_EXTI_CFG3_EXTI8_PB ((uint16_t)0x0001) /*!< PB[8] pin */
#define AFIO_EXTI_CFG3_EXTI8_PC ((uint16_t)0x0002) /*!< PC[8] pin */
#define AFIO_EXTI_CFG3_EXTI8_PD ((uint16_t)0x0003) /*!< PD[8] pin */
#define AFIO_EXTI_CFG3_EXTI8_PE ((uint16_t)0x0004) /*!< PE[8] pin */
#define AFIO_EXTI_CFG3_EXTI8_PF ((uint16_t)0x0005) /*!< PF[8] pin */
#define AFIO_EXTI_CFG3_EXTI8_PG ((uint16_t)0x0006) /*!< PG[8] pin */

/*!< EXTI9 configuration */
#define AFIO_EXTI_CFG3_EXTI9_PA ((uint16_t)0x0000) /*!< PA[9] pin */
#define AFIO_EXTI_CFG3_EXTI9_PB ((uint16_t)0x0010) /*!< PB[9] pin */
#define AFIO_EXTI_CFG3_EXTI9_PC ((uint16_t)0x0020) /*!< PC[9] pin */
#define AFIO_EXTI_CFG3_EXTI9_PD ((uint16_t)0x0030) /*!< PD[9] pin */
#define AFIO_EXTI_CFG3_EXTI9_PE ((uint16_t)0x0040) /*!< PE[9] pin */
#define AFIO_EXTI_CFG3_EXTI9_PF ((uint16_t)0x0050) /*!< PF[9] pin */
#define AFIO_EXTI_CFG3_EXTI9_PG ((uint16_t)0x0060) /*!< PG[9] pin */

/*!< EXTI10 configuration */
#define AFIO_EXTI_CFG3_EXTI10_PA ((uint16_t)0x0000) /*!< PA[10] pin */
#define AFIO_EXTI_CFG3_EXTI10_PB ((uint16_t)0x0100) /*!< PB[10] pin */
#define AFIO_EXTI_CFG3_EXTI10_PC ((uint16_t)0x0200) /*!< PC[10] pin */
#define AFIO_EXTI_CFG3_EXTI10_PD ((uint16_t)0x0300) /*!< PD[10] pin */
#define AFIO_EXTI_CFG3_EXTI10_PE ((uint16_t)0x0400) /*!< PE[10] pin */
#define AFIO_EXTI_CFG3_EXTI10_PF ((uint16_t)0x0500) /*!< PF[10] pin */
#define AFIO_EXTI_CFG3_EXTI10_PG ((uint16_t)0x0600) /*!< PG[10] pin */

/*!< EXTI11 configuration */
#define AFIO_EXTI_CFG3_EXTI11_PA ((uint16_t)0x0000) /*!< PA[11] pin */
#define AFIO_EXTI_CFG3_EXTI11_PB ((uint16_t)0x1000) /*!< PB[11] pin */
#define AFIO_EXTI_CFG3_EXTI11_PC ((uint16_t)0x2000) /*!< PC[11] pin */
#define AFIO_EXTI_CFG3_EXTI11_PD ((uint16_t)0x3000) /*!< PD[11] pin */
#define AFIO_EXTI_CFG3_EXTI11_PE ((uint16_t)0x4000) /*!< PE[11] pin */
#define AFIO_EXTI_CFG3_EXTI11_PF ((uint16_t)0x5000) /*!< PF[11] pin */
#define AFIO_EXTI_CFG3_EXTI11_PG ((uint16_t)0x6000) /*!< PG[11] pin */

/*****************  Bit definition for AFIO_EXTI_CFG4 register  *****************/
#define AFIO_EXTI_CFG4_EXTI12 ((uint16_t)0x000F) /*!< EXTI 12 configuration */
#define AFIO_EXTI_CFG4_EXTI13 ((uint16_t)0x00F0) /*!< EXTI 13 configuration */
#define AFIO_EXTI_CFG4_EXTI14 ((uint16_t)0x0F00) /*!< EXTI 14 configuration */
#define AFIO_EXTI_CFG4_EXTI15 ((uint16_t)0xF000) /*!< EXTI 15 configuration */

/* EXTI12 configuration */
#define AFIO_EXTI_CFG4_EXTI12_PA ((uint16_t)0x0000) /*!< PA[12] pin */
#define AFIO_EXTI_CFG4_EXTI12_PB ((uint16_t)0x0001) /*!< PB[12] pin */
#define AFIO_EXTI_CFG4_EXTI12_PC ((uint16_t)0x0002) /*!< PC[12] pin */
#define AFIO_EXTI_CFG4_EXTI12_PD ((uint16_t)0x0003) /*!< PD[12] pin */
#define AFIO_EXTI_CFG4_EXTI12_PE ((uint16_t)0x0004) /*!< PE[12] pin */
#define AFIO_EXTI_CFG4_EXTI12_PF ((uint16_t)0x0005) /*!< PF[12] pin */
#define AFIO_EXTI_CFG4_EXTI12_PG ((uint16_t)0x0006) /*!< PG[12] pin */

/* EXTI13 configuration */
#define AFIO_EXTI_CFG4_EXTI13_PA ((uint16_t)0x0000) /*!< PA[13] pin */
#define AFIO_EXTI_CFG4_EXTI13_PB ((uint16_t)0x0010) /*!< PB[13] pin */
#define AFIO_EXTI_CFG4_EXTI13_PC ((uint16_t)0x0020) /*!< PC[13] pin */
#define AFIO_EXTI_CFG4_EXTI13_PD ((uint16_t)0x0030) /*!< PD[13] pin */
#define AFIO_EXTI_CFG4_EXTI13_PE ((uint16_t)0x0040) /*!< PE[13] pin */
#define AFIO_EXTI_CFG4_EXTI13_PF ((uint16_t)0x0050) /*!< PF[13] pin */
#define AFIO_EXTI_CFG4_EXTI13_PG ((uint16_t)0x0060) /*!< PG[13] pin */

/*!< EXTI14 configuration */
#define AFIO_EXTI_CFG4_EXTI14_PA ((uint16_t)0x0000) /*!< PA[14] pin */
#define AFIO_EXTI_CFG4_EXTI14_PB ((uint16_t)0x0100) /*!< PB[14] pin */
#define AFIO_EXTI_CFG4_EXTI14_PC ((uint16_t)0x0200) /*!< PC[14] pin */
#define AFIO_EXTI_CFG4_EXTI14_PD ((uint16_t)0x0300) /*!< PD[14] pin */
#define AFIO_EXTI_CFG4_EXTI14_PE ((uint16_t)0x0400) /*!< PE[14] pin */
#define AFIO_EXTI_CFG4_EXTI14_PF ((uint16_t)0x0500) /*!< PF[14] pin */
#define AFIO_EXTI_CFG4_EXTI14_PG ((uint16_t)0x0600) /*!< PG[14] pin */

/*!< EXTI15 configuration */
#define AFIO_EXTI_CFG4_EXTI15_PA ((uint16_t)0x0000) /*!< PA[15] pin */
#define AFIO_EXTI_CFG4_EXTI15_PB ((uint16_t)0x1000) /*!< PB[15] pin */
#define AFIO_EXTI_CFG4_EXTI15_PC ((uint16_t)0x2000) /*!< PC[15] pin */
#define AFIO_EXTI_CFG4_EXTI15_PD ((uint16_t)0x3000) /*!< PD[15] pin */
#define AFIO_EXTI_CFG4_EXTI15_PE ((uint16_t)0x4000) /*!< PE[15] pin */
#define AFIO_EXTI_CFG4_EXTI15_PF ((uint16_t)0x5000) /*!< PF[15] pin */
#define AFIO_EXTI_CFG4_EXTI15_PG ((uint16_t)0x6000) /*!< PG[15] pin */

/******************  Bit definition for AFIO_RMP_CFG3 register  *******************/
#define AFIO_RMP_CFG3_SDIO_RMP   ((uint32_t)0x00000001) /*!< SDIO remapping */
#define AFIO_RMP_CFG3_CAN2_RMP   ((uint32_t)0x00000006) /*!<CAN2_RMP[1:0] bits (CAN2 Alternate function remapping) */
#define AFIO_RMP_CFG3_CAN2_RMP_0 ((uint32_t)0x00000002) /*!< Bit 0 */
#define AFIO_RMP_CFG3_CAN2_RMP_1 ((uint32_t)0x00000004) /*!< Bit 1*/
#define AFIO_RMP_CFG3_QSPI_RMP   ((uint32_t)0x00000030) /*!<QSPI_RMP[1:0] bits (QSPI Alternate function remapping) */
#define AFIO_RMP_CFG3_QSPI_RMP_0 ((uint32_t)0x00000010) /*!< Bit 0 */
#define AFIO_RMP_CFG3_QSPI_RMP_1 ((uint32_t)0x00000020) /*!< Bit 1*/
#define AFIO_RMP_CFG3_I2C2_RMP   ((uint32_t)0x000000C0) /*!<I2C2_RMP[1:0] bits (I2C2 Alternate function remapping) */
#define AFIO_RMP_CFG3_I2C2_RMP_0 ((uint32_t)0x00000040) /*!< Bit 0 */
#define AFIO_RMP_CFG3_I2C2_RMP_1 ((uint32_t)0x00000080) /*!< Bit 1*/
#define AFIO_RMP_CFG3_I2C3_RMP   ((uint32_t)0x00000300) /*!<I2C3_RMP[1:0] bits (I2C3 Alternate function remapping) */
#define AFIO_RMP_CFG3_I2C3_RMP_0 ((uint32_t)0x00000100) /*!< Bit 0 */
#define AFIO_RMP_CFG3_I2C3_RMP_1 ((uint32_t)0x00000200) /*!< Bit 1*/
#define AFIO_RMP_CFG3_I2C4_RMP   ((uint32_t)0x00000C00) /*!<I2C4_RMP[1:0] bits (I2C4 Alternate function remapping) */
#define AFIO_RMP_CFG3_I2C4_RMP_0 ((uint32_t)0x00000400) /*!< Bit 0 */
#define AFIO_RMP_CFG3_I2C4_RMP_1 ((uint32_t)0x00000800) /*!< Bit 1*/
#define AFIO_RMP_CFG3_SPI2_RMP   ((uint32_t)0x00003000) /*!<SPI2_RMP[1:0] bits (SPI2 Alternate function remapping) */
#define AFIO_RMP_CFG3_SPI2_RMP_0 ((uint32_t)0x00001000) /*!< Bit 0 */
#define AFIO_RMP_CFG3_SPI2_RMP_1 ((uint32_t)0x00002000) /*!< Bit 1*/
#define AFIO_RMP_CFG3_SPI3_RMP   ((uint32_t)0x0000C000) /*!<SPI3_RMP[1:0] bits (SPI3 Alternate function remapping) */
#define AFIO_RMP_CFG3_SPI3_RMP_0 ((uint32_t)0x00004000) /*!< Bit 0 */
#define AFIO_RMP_CFG3_SPI3_RMP_1 ((uint32_t)0x00008000) /*!< Bit 1*/
#define AFIO_RMP_CFG3_ETH_RMP    ((uint32_t)0x00030000) /*!<ETH_RMP[1:0] bits (ETH Alternate function remapping) */
#define AFIO_RMP_CFG3_ETH_RMP_0  ((uint32_t)0x00010000) /*!< Bit 0 */
#define AFIO_RMP_CFG3_ETH_RMP_1  ((uint32_t)0x00020000) /*!< Bit 1*/
#define AFIO_RMP_CFG3_SPI1_RMP_1 ((uint32_t)0x00040000) /*!<SPI1_RMP[1:0]  Bit 1 (SPI1 Alternate function remapping) */
#define AFIO_RMP_CFG3_USART2_RMP_1  ((uint32_t)0x00080000) /*!<USART2_RMP[1:0]  Bit 1 (USART2 Alternate function remapping) */
#define AFIO_RMP_CFG3_UART4_RMP   ((uint32_t)0x00300000) /*!<UART4_RMP[1:0] bits (UART4 Alternate function remapping) */
#define AFIO_RMP_CFG3_UART4_RMP_0 ((uint32_t)0x00200000) /*!< Bit 0 */
#define AFIO_RMP_CFG3_UART4_RMP_1 ((uint32_t)0x00100000) /*!< Bit 1*/
#define AFIO_RMP_CFG3_UART5_RMP   ((uint32_t)0x00C00000) /*!<UART5_RMP[1:0] bits (UART5 Alternate function remapping) */
#define AFIO_RMP_CFG3_UART5_RMP_0 ((uint32_t)0x00800000) /*!< Bit 0 */
#define AFIO_RMP_CFG3_UART5_RMP_1 ((uint32_t)0x00400000) /*!< Bit 1*/
#define AFIO_RMP_CFG3_UART6_RMP   ((uint32_t)0x03000000) /*!<UART6_RMP[1:0] bits (UART6 Alternate function remapping) */
#define AFIO_RMP_CFG3_UART6_RMP_0 ((uint32_t)0x02000000) /*!< Bit 0 */
#define AFIO_RMP_CFG3_UART6_RMP_1 ((uint32_t)0x01000000) /*!< Bit 1*/
#define AFIO_RMP_CFG3_UART7_RMP   ((uint32_t)0x0C000000) /*!<UART7_RMP[1:0] bits (UART7 Alternate function remapping) */
#define AFIO_RMP_CFG3_UART7_RMP_0 ((uint32_t)0x08000000) /*!< Bit 0 */
#define AFIO_RMP_CFG3_UART7_RMP_1 ((uint32_t)0x04000000) /*!< Bit 1*/
#define AFIO_RMP_CFG3_TIM8_RMP    ((uint32_t)0xC0000000) /*!<TIM8_RMP[1:0] bits (TIM8 Alternate function remapping) */
#define AFIO_RMP_CFG3_TIM8_RMP_0  ((uint32_t)0x40000000) /*!< Bit 0 */
#define AFIO_RMP_CFG3_TIM8_RMP_1  ((uint32_t)0x80000000) /*!< Bit 1*/

/******************  Bit definition for AFIO_RMP_CFG4 register  *******************/
#define AFIO_RMP_CFG4_COMP1_RMP    ((uint32_t)0x00000003) /*!<COMP1_RMP[1:0] bits (COMP1 Alternate function remapping) */
#define AFIO_RMP_CFG4_COMP1_RMP_0  ((uint32_t)0x00000001) /*!< Bit 0 */
#define AFIO_RMP_CFG4_COMP1_RMP_1  ((uint32_t)0x00000002) /*!< Bit 1*/
#define AFIO_RMP_CFG4_COMP2_RMP    ((uint32_t)0x0000000C) /*!<COMP2_RMP[1:0] bits (COMP2 Alternate function remapping) */
#define AFIO_RMP_CFG4_COMP2_RMP_0  ((uint32_t)0x00000004) /*!< Bit 0 */
#define AFIO_RMP_CFG4_COMP2_RMP_1  ((uint32_t)0x00000008) /*!< Bit 1*/
#define AFIO_RMP_CFG4_COMP3_RMP    ((uint32_t)0x00000030) /*!<COMP3_RMP[1:0] bits (COMP3 Alternate function remapping) */
#define AFIO_RMP_CFG4_COMP3_RMP_0  ((uint32_t)0x00000010) /*!< Bit 0 */
#define AFIO_RMP_CFG4_COMP3_RMP_1  ((uint32_t)0x00000020) /*!< Bit 1*/
#define AFIO_RMP_CFG4_COMP4_RMP    ((uint32_t)0x000000C0) /*!<COMP4_RMP[1:0] bits (COMP4 Alternate function remapping) */
#define AFIO_RMP_CFG4_COMP4_RMP_0  ((uint32_t)0x00000040) /*!< Bit 0 */
#define AFIO_RMP_CFG4_COMP4_RMP_1  ((uint32_t)0x00000080) /*!< Bit 1*/
#define AFIO_RMP_CFG4_COMP5_RMP    ((uint32_t)0x00000300) /*!<COMP5_RMP[1:0] bits (COMP5 Alternate function remapping) */
#define AFIO_RMP_CFG4_COMP5_RMP_0  ((uint32_t)0x00000100) /*!< Bit 0 */
#define AFIO_RMP_CFG4_COMP5_RMP_1  ((uint32_t)0x00000200) /*!< Bit 1*/
#define AFIO_RMP_CFG4_COMP6_RMP    ((uint32_t)0x00000C00) /*!<COMP6_RMP[1:0] bits (COMP6 Alternate function remapping) */
#define AFIO_RMP_CFG4_COMP6_RMP_0  ((uint32_t)0x00000400) /*!< Bit 0 */
#define AFIO_RMP_CFG4_COMP6_RMP_1  ((uint32_t)0x00000800) /*!< Bit 1*/
#define AFIO_RMP_CFG4_COMP7_RMP    ((uint32_t)0x00001000) /*!< COMP7 remapping */
#define AFIO_RMP_CFG4_ADC3_ETRI_RMP    ((uint32_t)0x00004000) /*!< ADC3_ETRI remapping */
#define AFIO_RMP_CFG4_ADC3_ETRR_RMP    ((uint32_t)0x00008000) /*!< ADC3_ETRR remapping */
#define AFIO_RMP_CFG4_ADC4_ETRI_RMP    ((uint32_t)0x00010000) /*!< ADC4_ETRI remapping */
#define AFIO_RMP_CFG4_ADC4_ETRR_RMP    ((uint32_t)0x00020000) /*!< ADC4_ETRR remapping */
#define AFIO_RMP_CFG4_TSC_OUT_CTRL_RMP ((uint32_t)0x00040000) /*!< TSC_OUT_CTRL remapping */
#define AFIO_RMP_CFG4_QSPI_XIP_EN_RMP  ((uint32_t)0x00080000) /*!< QSPI_XIP remapping */
#define AFIO_RMP_CFG4_DVP_RMP      ((uint32_t)0x00300000) /*!<DVP_RMP[1:0] bits (DVP Alternate function remapping) */
#define AFIO_RMP_CFG4_DVP_RMP_0    ((uint32_t)0x00100000) /*!< Bit 0 */
#define AFIO_RMP_CFG4_DVP_RMP_1    ((uint32_t)0x00200000) /*!< Bit 1*/
#define AFIO_RMP_CFG4_SPI1_NSS_RMP ((uint32_t)0x00400000) /*!< SPI1_NSS remapping */
#define AFIO_RMP_CFG4_SPI2_NSS_RMP ((uint32_t)0x00800000) /*!< SPI2_NSS remapping */
#define AFIO_RMP_CFG4_SPI3_NSS_RMP ((uint32_t)0x01000000) /*!< SPI3_NSS remapping */
#define AFIO_RMP_CFG4_QSPI_MISO_RMP ((uint32_t)0x02000000) /*!< QSPI_MISO remapping */

/******************  Bit definition for AFIO_RMP_CFG5 register  *******************/
#define AFIO_RMP_CFG5_ECLAMP1_RST_EN_RMP    ((uint32_t)0x00000001) /*!< ECLAMP1_RST_EN remapping */
#define AFIO_RMP_CFG5_ECLAMP2_RST_EN_RMP    ((uint32_t)0x00000002) /*!< ECLAMP2_RST_EN remapping */
#define AFIO_RMP_CFG5_ECLAMP3_RST_EN_RMP    ((uint32_t)0x00000004) /*!< ECLAMP3_RST_EN remapping */
#define AFIO_RMP_CFG5_ECLAMP4_RST_EN_RMP    ((uint32_t)0x00000008) /*!< ECLAMP4_RST_EN remapping */
#define AFIO_RMP_CFG5_EGBN1_RST_EN_RMP      ((uint32_t)0x00000010) /*!< EGBN1_RST_EN remapping */
#define AFIO_RMP_CFG5_EGBN2_RST_EN_RMP      ((uint32_t)0x00000020) /*!< EGBN2_RST_EN remapping */
#define AFIO_RMP_CFG5_EGBN3_RST_EN_RMP      ((uint32_t)0x00000040) /*!< EGBN3_RST_EN remapping */
#define AFIO_RMP_CFG5_EGBN4_RST_EN_RMP      ((uint32_t)0x00000080) /*!< EGBN4_RST_EN remapping */
#define AFIO_RMP_CFG5_EGB1_RST_EN_RMP       ((uint32_t)0x00000100) /*!< EGB1_RST_EN remapping */
#define AFIO_RMP_CFG5_EGB2_RST_EN_RMP       ((uint32_t)0x00000200) /*!< EGB2_RST_EN remapping */
#define AFIO_RMP_CFG5_EGB3_RST_EN_RMP       ((uint32_t)0x00000400) /*!< EGB3_RST_EN remapping */
#define AFIO_RMP_CFG5_EGB4_RST_EN_RMP       ((uint32_t)0x00000800) /*!< EGB4_RST_EN remapping */
#define AFIO_RMP_CFG5_ECLAMP1_DET_EN_RMP    ((uint32_t)0x00001000) /*!< ECLAMP1_DET_EN remapping */
#define AFIO_RMP_CFG5_ECLAMP2_DET_EN_RMP    ((uint32_t)0x00002000) /*!< ECLAMP2_DET_EN remapping */
#define AFIO_RMP_CFG5_ECLAMP3_DET_EN_RMP    ((uint32_t)0x00004000) /*!< ECLAMP3_DET_EN remapping */
#define AFIO_RMP_CFG5_ECLAMP4_DET_EN_RMP    ((uint32_t)0x00008000) /*!< ECLAMP4_DET_EN remapping */
#define AFIO_RMP_CFG5_EGBN1_DET_EN_RMP      ((uint32_t)0x00010000) /*!< EGBN1_DET_EN remapping */
#define AFIO_RMP_CFG5_EGBN2_DET_EN_RMP      ((uint32_t)0x00020000) /*!< EGBN2_DET_EN remapping */
#define AFIO_RMP_CFG5_EGBN3_DET_EN_RMP      ((uint32_t)0x00040000) /*!< EGBN3_DET_EN remapping */
#define AFIO_RMP_CFG5_EGBN4_DET_EN_RMP      ((uint32_t)0x00080000) /*!< EGBN4_DET_EN remapping */
#define AFIO_RMP_CFG5_EGB1_DET_EN_RMP       ((uint32_t)0x00100000) /*!< EGB1_DET_EN remapping */
#define AFIO_RMP_CFG5_EGB2_DET_EN_RMP       ((uint32_t)0x00200000) /*!< EGB2_DET_EN remapping */
#define AFIO_RMP_CFG5_EGB3_DET_EN_RMP       ((uint32_t)0x00400000) /*!< EGB3_DET_EN remapping */
#define AFIO_RMP_CFG5_EGB4_DET_EN_RMP       ((uint32_t)0x00800000) /*!< EGB4_DET_EN remapping */
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
/*                    External Interrupt/Event Controller                     */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for EXTI_IMASK register  *******************/
#define EXTI_IMASK_IMASK_ALL  ((uint32_t)0x003FFFFF) /*!< Interrupt Mask for all lines */
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

/*******************  Bit definition for EXTI_EMASK register  *******************/
#define EXTI_EMASK_EMASK_ALL  ((uint32_t)0x003FFFFF) /*!< Event Mask for all lines */
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

/******************  Bit definition for EXTI_RT_CFG register  *******************/
#define EXTI_EMASK_RT_CFG_RTCFG_ALL  ((uint32_t)0x003FFFFF) /*!< Rising trigger event configuration for all lines */
#define EXTI_EMASK_RT_CFG_RTCFG0  ((uint32_t)0x00000001) /*!< Rising trigger event configuration bit of line 0 */
#define EXTI_EMASK_RT_CFG_RTCFG1  ((uint32_t)0x00000002) /*!< Rising trigger event configuration bit of line 1 */
#define EXTI_EMASK_RT_CFG_RTCFG2  ((uint32_t)0x00000004) /*!< Rising trigger event configuration bit of line 2 */
#define EXTI_EMASK_RT_CFG_RTCFG3  ((uint32_t)0x00000008) /*!< Rising trigger event configuration bit of line 3 */
#define EXTI_EMASK_RT_CFG_RTCFG4  ((uint32_t)0x00000010) /*!< Rising trigger event configuration bit of line 4 */
#define EXTI_EMASK_RT_CFG_RTCFG5  ((uint32_t)0x00000020) /*!< Rising trigger event configuration bit of line 5 */
#define EXTI_EMASK_RT_CFG_RTCFG6  ((uint32_t)0x00000040) /*!< Rising trigger event configuration bit of line 6 */
#define EXTI_EMASK_RT_CFG_RTCFG7  ((uint32_t)0x00000080) /*!< Rising trigger event configuration bit of line 7 */
#define EXTI_EMASK_RT_CFG_RTCFG8  ((uint32_t)0x00000100) /*!< Rising trigger event configuration bit of line 8 */
#define EXTI_EMASK_RT_CFG_RT_CFG9 ((uint32_t)0x00000200) /*!< Rising trigger event configuration bit of line 9 */
#define EXTI_EMASK_RT_CFG_RTCFG10 ((uint32_t)0x00000400) /*!< Rising trigger event configuration bit of line 10 */
#define EXTI_EMASK_RT_CFG_RTCFG11 ((uint32_t)0x00000800) /*!< Rising trigger event configuration bit of line 11 */
#define EXTI_EMASK_RT_CFG_RTCFG12 ((uint32_t)0x00001000) /*!< Rising trigger event configuration bit of line 12 */
#define EXTI_EMASK_RT_CFG_RTCFG13 ((uint32_t)0x00002000) /*!< Rising trigger event configuration bit of line 13 */
#define EXTI_EMASK_RT_CFG_RTCFG14 ((uint32_t)0x00004000) /*!< Rising trigger event configuration bit of line 14 */
#define EXTI_EMASK_RT_CFG_RTCFG15 ((uint32_t)0x00008000) /*!< Rising trigger event configuration bit of line 15 */
#define EXTI_EMASK_RT_CFG_RTCFG16 ((uint32_t)0x00010000) /*!< Rising trigger event configuration bit of line 16 */
#define EXTI_EMASK_RT_CFG_RTCFG17 ((uint32_t)0x00020000) /*!< Rising trigger event configuration bit of line 17 */
#define EXTI_EMASK_RT_CFG_RTCFG18 ((uint32_t)0x00040000) /*!< Rising trigger event configuration bit of line 18 */
#define EXTI_EMASK_RT_CFG_RTCFG19 ((uint32_t)0x00080000) /*!< Rising trigger event configuration bit of line 19 */
#define EXTI_EMASK_RT_CFG_RTCFG20 ((uint32_t)0x00100000) /*!< Rising trigger event configuration bit of line 20 */
#define EXTI_EMASK_RT_CFG_RTCFG21 ((uint32_t)0x00200000) /*!< Rising trigger event configuration bit of line 21 */

/******************  Bit definition for EXTI_FT_CFG register  *******************/
#define EXTI_EMASK_FT_CFG_FTCFG_ALL  ((uint32_t)0x003FFFFF) /*!< Falling trigger event configuration for all lines */
#define EXTI_EMASK_FT_CFG_FTCFG0  ((uint32_t)0x00000001) /*!< Falling trigger event configuration bit of line 0 */
#define EXTI_EMASK_FT_CFG_FTCFG1  ((uint32_t)0x00000002) /*!< Falling trigger event configuration bit of line 1 */
#define EXTI_EMASK_FT_CFG_FTCFG2  ((uint32_t)0x00000004) /*!< Falling trigger event configuration bit of line 2 */
#define EXTI_EMASK_FT_CFG_FTCFG3  ((uint32_t)0x00000008) /*!< Falling trigger event configuration bit of line 3 */
#define EXTI_EMASK_FT_CFG_FTCFG4  ((uint32_t)0x00000010) /*!< Falling trigger event configuration bit of line 4 */
#define EXTI_EMASK_FT_CFG_FTCFG5  ((uint32_t)0x00000020) /*!< Falling trigger event configuration bit of line 5 */
#define EXTI_EMASK_FT_CFG_FTCFG6  ((uint32_t)0x00000040) /*!< Falling trigger event configuration bit of line 6 */
#define EXTI_EMASK_FT_CFG_FTCFG7  ((uint32_t)0x00000080) /*!< Falling trigger event configuration bit of line 7 */
#define EXTI_EMASK_FT_CFG_FTCFG8  ((uint32_t)0x00000100) /*!< Falling trigger event configuration bit of line 8 */
#define EXTI_EMASK_FT_CFG_FTCFG9  ((uint32_t)0x00000200) /*!< Falling trigger event configuration bit of line 9 */
#define EXTI_EMASK_FT_CFG_FTCFG10 ((uint32_t)0x00000400) /*!< Falling trigger event configuration bit of line 10 */
#define EXTI_EMASK_FT_CFG_FTCFG11 ((uint32_t)0x00000800) /*!< Falling trigger event configuration bit of line 11 */
#define EXTI_EMASK_FT_CFG_FTCFG12 ((uint32_t)0x00001000) /*!< Falling trigger event configuration bit of line 12 */
#define EXTI_EMASK_FT_CFG_FTCFG13 ((uint32_t)0x00002000) /*!< Falling trigger event configuration bit of line 13 */
#define EXTI_EMASK_FT_CFG_FTCFG14 ((uint32_t)0x00004000) /*!< Falling trigger event configuration bit of line 14 */
#define EXTI_EMASK_FT_CFG_FTCFG15 ((uint32_t)0x00008000) /*!< Falling trigger event configuration bit of line 15 */
#define EXTI_EMASK_FT_CFG_FTCFG16 ((uint32_t)0x00010000) /*!< Falling trigger event configuration bit of line 16 */
#define EXTI_EMASK_FT_CFG_FTCFG17 ((uint32_t)0x00020000) /*!< Falling trigger event configuration bit of line 17 */
#define EXTI_EMASK_FT_CFG_FTCFG18 ((uint32_t)0x00040000) /*!< Falling trigger event configuration bit of line 18 */
#define EXTI_EMASK_FT_CFG_FTCFG19 ((uint32_t)0x00080000) /*!< Falling trigger event configuration bit of line 19 */
#define EXTI_EMASK_FT_CFG_FTCFG20 ((uint32_t)0x00100000) /*!< Falling trigger event configuration bit of line 20 */
#define EXTI_EMASK_FT_CFG_FTCFG21 ((uint32_t)0x00200000) /*!< Falling trigger event configuration bit of line 21 */

/******************  Bit definition for EXTI_SWIE register  ******************/
#define EXTI_SWIE_SWIE_ALL  ((uint32_t)0x003FFFFF) /*!< Software Interrupt for all lines */
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

/*******************  Bit definition for EXTI_PEND register  ********************/
#define EXTI_PEND_PEND_ALL  ((uint32_t)0x003FFFFF) /*!< Pending for all lines */
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

/*******************  Bit definition for EXTI_TS_SEL register  ********************/
#define EXTI_TSSEL_TSSEL_ALL ((uint32_t)0x0000F) /*!<TSSEL[3:0] bits */
#define EXTI_TSSEL_TSSEL0    ((uint32_t)0x00001) /*!< Bit 0 */
#define EXTI_TSSEL_TSSEL1    ((uint32_t)0x00002) /*!< Bit 1 */
#define EXTI_TSSEL_TSSEL2    ((uint32_t)0x00004) /*!< Bit 2 */
#define EXTI_TSSEL_TSSEL3    ((uint32_t)0x00008) /*!< Bit 3 */

#define EXTI_TSSEL_LINE0     ((uint32_t)0x00000) /*!< External interrupt line 0 */
#define EXTI_TSSEL_LINE1     ((uint32_t)0x00001) /*!< External interrupt line 1 */
#define EXTI_TSSEL_LINE2     ((uint32_t)0x00002) /*!< External interrupt line 2 */
#define EXTI_TSSEL_LINE3     ((uint32_t)0x00003) /*!< External interrupt line 3 */
#define EXTI_TSSEL_LINE4     ((uint32_t)0x00004) /*!< External interrupt line 4 */
#define EXTI_TSSEL_LINE5     ((uint32_t)0x00005) /*!< External interrupt line 5 */
#define EXTI_TSSEL_LINE6     ((uint32_t)0x00006) /*!< External interrupt line 6 */
#define EXTI_TSSEL_LINE7     ((uint32_t)0x00007) /*!< External interrupt line 7 */
#define EXTI_TSSEL_LINE8     ((uint32_t)0x00008) /*!< External interrupt line 8 */
#define EXTI_TSSEL_LINE9     ((uint32_t)0x00009) /*!< External interrupt line 9 */
#define EXTI_TSSEL_LINE10    ((uint32_t)0x0000A) /*!< External interrupt line 10 */
#define EXTI_TSSEL_LINE11    ((uint32_t)0x0000B) /*!< External interrupt line 11 */
#define EXTI_TSSEL_LINE12    ((uint32_t)0x0000C) /*!< External interrupt line 12 */
#define EXTI_TSSEL_LINE13    ((uint32_t)0x0000D) /*!< External interrupt line 13 */
#define EXTI_TSSEL_LINE14    ((uint32_t)0x0000E) /*!< External interrupt line 14 */
#define EXTI_TSSEL_LINE15    ((uint32_t)0x0000F) /*!< External interrupt line 15 */

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

/******************  Bit definition for DMA_CHSEL1 register  *******************/
#define DMA_CHSEL1_CH_SEL ((uint32_t)0x0000003F) /*!< Channel Select */

/******************  Bit definition for DMA_CHSEL2 register  *******************/
#define DMA_CHSEL2_CH_SEL ((uint32_t)0x0000003F) /*!< Channel Select */

/******************  Bit definition for DMA_CHSEL3 register  *******************/
#define DMA_CHSEL3_CH_SEL ((uint32_t)0x0000003F) /*!< Channel Select */

/******************  Bit definition for DMA_CHSEL4 register  *******************/
#define DMA_CHSEL4_CH_SEL ((uint32_t)0x0000003F) /*!< Channel Select */

/******************  Bit definition for DMA_CHSEL5 register  *******************/
#define DMA_CHSEL5_CH_SEL ((uint32_t)0x0000003F) /*!< Channel Select */

/******************  Bit definition for DMA_CHSEL6 register  *******************/
#define DMA_CHSEL6_CH_SEL ((uint32_t)0x0000003F) /*!< Channel Select */

/******************  Bit definition for DMA_CHSEL7 register  *******************/
#define DMA_CHSEL7_CH_SEL ((uint32_t)0x0000003F) /*!< Channel Select */

/******************  Bit definition for DMA_CHSEL8 register  *******************/
#define DMA_CHSEL8_CH_SEL ((uint32_t)0x0000003F) /*!< Channel Select */

/******************  Bit definition for DMA_CHMAPEN register  *******************/
#define DMA_CHMAPEN_MAP_EN ((uint32_t)0x00000001) /*!< Channel Map Enable */

/******************************************************************************/
/*                                                                            */
/*                        Analog to Digital Converter                         */
/*                                                                            */
/******************************************************************************/

/********************  Bit definition for ADC_STS register  ********************/
#define ADC_STS_AWDG   ((uint8_t)0x01) /*!< Analog watchdog flag */
#define ADC_STS_ENDC   ((uint8_t)0x02) /*!< End of conversion */
#define ADC_STS_JENDC  ((uint8_t)0x04) /*!< Injected channel end of conversion */
#define ADC_STS_JSTR   ((uint8_t)0x08) /*!< Injected channel Start flag */
#define ADC_STS_STR    ((uint8_t)0x10) /*!< Regular channel Start flag */
#define ADC_STS_ENDCA  ((uint8_t)0x20) /*!< Any end of conversion */
#define ADC_STS_JENDCA ((uint8_t)0x40) /*!< Any injected channel end of conversion */

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

#define ADC_CTRL1_DUSEL   ((uint32_t)0x000F0000) /*!< DUALMOD[3:0] bits (Dual mode selection) */
#define ADC_CTRL1_DUSEL_0 ((uint32_t)0x00010000) /*!< Bit 0 */
#define ADC_CTRL1_DUSEL_1 ((uint32_t)0x00020000) /*!< Bit 1 */
#define ADC_CTRL1_DUSEL_2 ((uint32_t)0x00040000) /*!< Bit 2 */
#define ADC_CTRL1_DUSEL_3 ((uint32_t)0x00080000) /*!< Bit 3 */

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
#define ADC_DAT_ADC2DAT ((uint32_t)0xFFFF0000) /*!< ADC2 data */

/********************  Bit definition for ADC_DIFSEL register  *****************/
#define ADC_DIFSEL_DIFSEL_MASK ((uint32_t)0x0007FFFE)
#define ADC_DIFSEL_DIFSEL_CH1  ((uint32_t)0x00000002)
#define ADC_DIFSEL_DIFSEL_CH2  ((uint32_t)0x00000004)
#define ADC_DIFSEL_DIFSEL_CH3  ((uint32_t)0x00000008)
#define ADC_DIFSEL_DIFSEL_CH4  ((uint32_t)0x00000010)
#define ADC_DIFSEL_DIFSEL_CH5  ((uint32_t)0x00000020)
#define ADC_DIFSEL_DIFSEL_CH6  ((uint32_t)0x00000040)
#define ADC_DIFSEL_DIFSEL_CH7  ((uint32_t)0x00000080)
#define ADC_DIFSEL_DIFSEL_CH8  ((uint32_t)0x00000100)
#define ADC_DIFSEL_DIFSEL_CH9  ((uint32_t)0x00000200)
#define ADC_DIFSEL_DIFSEL_CH10 ((uint32_t)0x00000400)
#define ADC_DIFSEL_DIFSEL_CH11 ((uint32_t)0x00000800)
#define ADC_DIFSEL_DIFSEL_CH12 ((uint32_t)0x00001000)
#define ADC_DIFSEL_DIFSEL_CH13 ((uint32_t)0x00002000)
#define ADC_DIFSEL_DIFSEL_CH14 ((uint32_t)0x00004000)
#define ADC_DIFSEL_DIFSEL_CH15 ((uint32_t)0x00008000)
#define ADC_DIFSEL_DIFSEL_CH16 ((uint32_t)0x00010000)
#define ADC_DIFSEL_DIFSEL_CH17 ((uint32_t)0x00020000)
#define ADC_DIFSEL_DIFSEL_CH18 ((uint32_t)0x00040000)

/********************  Bit definition for ADC_CALFACT register  ***************/
#define ADC_CALFACT_CALFACTD_MASK ((uint32_t)0x007F0000)
#define ADC_CALFACT_CALFACTS_MASK ((uint32_t)0x0000007F)

/********************  Bit definition for ADC_CTRL3 register  *****************/
#define ADC_CTRL3_VBATMEN   ((uint32_t)0x00000800)
#define ADC_CTRL3_DPWMOD    ((uint32_t)0x00000400)
#define ADC_CTRL3_JENDCAIEN ((uint32_t)0x00000200)
#define ADC_CTRL3_ENDCAIEN  ((uint32_t)0x00000100)
#define ADC_CTRL3_BPCAL     ((uint32_t)0x00000080)
#define ADC_CTRL3_PDRDY     ((uint32_t)0x00000040)
#define ADC_CTRL3_RDY       ((uint32_t)0x00000020)
#define ADC_CTRL3_CKMOD_BIT ((uint32_t)0x00000010)
#define ADC_CTRL3_CALALD    ((uint32_t)0x00000008)
#define ADC_CTRL3_CALDIF    ((uint32_t)0x00000004)
#define ADC_CTRL3_RES_MASK  ((uint32_t)0x00000003)

/********************  Bit definition for ADC_SAMPT3 register  ****************/
#define ADC_SAMPT3_SAMPSEL  ((uint32_t)0x00000008)
#define ADC_SAMPT3_SAMP18   ((uint32_t)0x00000007) /*!< SMP18[2:0] bits (Channel 18 Sample time selection) */
#define ADC_SAMPT3_SAMP18_0 ((uint32_t)0x00000001) /*!< Bit 0 */
#define ADC_SAMPT3_SAMP18_1 ((uint32_t)0x00000002) /*!< Bit 1 */
#define ADC_SAMPT3_SAMP18_2 ((uint32_t)0x00000004) /*!< Bit 2 */

/******************************************************************************/
/*                                                                            */
/*                      Digital to Analog Converter                           */
/*                                                                            */
/******************************************************************************/

/********************  Bit definition for DAC_CTRL register  ********************/
#define DAC_CTRL_CH1EN ((uint32_t)0x00000001) /*!< DAC channel1 enable */
#define DAC_CTRL_B1EN  ((uint32_t)0x00000002) /*!< DAC channel1 output buffer enable */
#define DAC_CTRL_T1EN  ((uint32_t)0x00000004) /*!< DAC channel1 Trigger enable */

#define DAC_CTRL_T1SEL   ((uint32_t)0x00000038) /*!< TSEL1[2:0] (DAC channel1 Trigger selection) */
#define DAC_CTRL_T1SEL_0 ((uint32_t)0x00000008) /*!< Bit 0 */
#define DAC_CTRL_T1SEL_1 ((uint32_t)0x00000010) /*!< Bit 1 */
#define DAC_CTRL_T1SEL_2 ((uint32_t)0x00000020) /*!< Bit 2 */

#define DAC_CTRL_W1EN   ((uint32_t)0x000000C0) /*!< WAVE1[1:0] (DAC channel1 noise/triangle wave generation enable) */
#define DAC_CTRL_W1EN_0 ((uint32_t)0x00000040) /*!< Bit 0 */
#define DAC_CTRL_W1EN_1 ((uint32_t)0x00000080) /*!< Bit 1 */

#define DAC_CTRL_MA1SEL   ((uint32_t)0x00000F00) /*!< MAMP1[3:0] (DAC channel1 Mask/Amplitude selector) */
#define DAC_CTRL_MA1SEL_0 ((uint32_t)0x00000100) /*!< Bit 0 */
#define DAC_CTRL_MA1SEL_1 ((uint32_t)0x00000200) /*!< Bit 1 */
#define DAC_CTRL_MA1SEL_2 ((uint32_t)0x00000400) /*!< Bit 2 */
#define DAC_CTRL_MA1SEL_3 ((uint32_t)0x00000800) /*!< Bit 3 */

#define DAC_CTRL_DMA1EN ((uint32_t)0x00001000) /*!< DAC channel1 DMA enable */
#define DAC_CTRL_CH2EN  ((uint32_t)0x00010000) /*!< DAC channel2 enable */
#define DAC_CTRL_B2EN   ((uint32_t)0x00020000) /*!< DAC channel2 output buffer enable */
#define DAC_CTRL_T2EN   ((uint32_t)0x00040000) /*!< DAC channel2 Trigger enable */

#define DAC_CTRL_T2SEL   ((uint32_t)0x00380000) /*!< TSEL2[2:0] (DAC channel2 Trigger selection) */
#define DAC_CTRL_T2SEL_0 ((uint32_t)0x00080000) /*!< Bit 0 */
#define DAC_CTRL_T2SEL_1 ((uint32_t)0x00100000) /*!< Bit 1 */
#define DAC_CTRL_T2SEL_2 ((uint32_t)0x00200000) /*!< Bit 2 */

#define DAC_CTRL_W2EN   ((uint32_t)0x00C00000) /*!< WAVE2[1:0] (DAC channel2 noise/triangle wave generation enable) */
#define DAC_CTRL_W2EN_0 ((uint32_t)0x00400000) /*!< Bit 0 */
#define DAC_CTRL_W2EN_1 ((uint32_t)0x00800000) /*!< Bit 1 */

#define DAC_CTRL_MA2SEL   ((uint32_t)0x0F000000) /*!< MAMP2[3:0] (DAC channel2 Mask/Amplitude selector) */
#define DAC_CTRL_MA2SEL_0 ((uint32_t)0x01000000) /*!< Bit 0 */
#define DAC_CTRL_MA2SEL_1 ((uint32_t)0x02000000) /*!< Bit 1 */
#define DAC_CTRL_MA2SEL_2 ((uint32_t)0x04000000) /*!< Bit 2 */
#define DAC_CTRL_MA2SEL_3 ((uint32_t)0x08000000) /*!< Bit 3 */

#define DAC_CTRL_DMA2EN ((uint32_t)0x10000000) /*!< DAC channel2 DMA enabled */

/*****************  Bit definition for DAC_SOTTR register  ******************/
#define DAC_SOTTR_TR1EN ((uint8_t)0x01) /*!< DAC channel1 software trigger */
#define DAC_SOTTR_TR2EN ((uint8_t)0x02) /*!< DAC channel2 software trigger */

/*****************  Bit definition for DAC_DR12CH1 register  ******************/
#define DAC_DR12CH1_DACCH1D ((uint16_t)0x0FFF) /*!< DAC channel1 12-bit Right aligned data */

/*****************  Bit definition for DAC_DL12CH1 register  ******************/
#define DAC_DL12CH1_DACCH1D ((uint16_t)0xFFF0) /*!< DAC channel1 12-bit Left aligned data */

/******************  Bit definition for DAC_DR8CH1 register  ******************/
#define DAC_DR8CH1_DACCH1D ((uint8_t)0xFF) /*!< DAC channel1 8-bit Right aligned data */

/*****************  Bit definition for DAC_DR12CH2 register  ******************/
#define DAC_DR12CH2_DACCH2D ((uint16_t)0x0FFF) /*!< DAC channel2 12-bit Right aligned data */

/*****************  Bit definition for DAC_DL12CH2 register  ******************/
#define DAC_DL12CH2_DACCH2D ((uint16_t)0xFFF0) /*!< DAC channel2 12-bit Left aligned data */

/******************  Bit definition for DAC_DR8CH2 register  ******************/
#define DAC_DR8CH2_DACCH2D ((uint8_t)0xFF) /*!< DAC channel2 8-bit Right aligned data */

/*****************  Bit definition for DAC_DR12DCH register  ******************/
#define DAC_DR12DCH_DACCH1D ((uint32_t)0x00000FFF) /*!< DAC channel1 12-bit Right aligned data */
#define DAC_DR12DCH_DACCH2D ((uint32_t)0x0FFF0000) /*!< DAC channel2 12-bit Right aligned data */

/*****************  Bit definition for DAC_DL12DCH register  ******************/
#define DAC_DL12DCH_DACCH1D ((uint32_t)0x0000FFF0) /*!< DAC channel1 12-bit Left aligned data */
#define DAC_DL12DCH_DACCH2D ((uint32_t)0xFFF00000) /*!< DAC channel2 12-bit Left aligned data */

/******************  Bit definition for DAC_DR8DCH register  ******************/
#define DAC_DR8DCH_DACCH1D ((uint16_t)0x00FF) /*!< DAC channel1 8-bit Right aligned data */
#define DAC_DR8DCH_DACCH2D ((uint16_t)0xFF00) /*!< DAC channel2 8-bit Right aligned data */

/*******************  Bit definition for DAC_DATO1 register  *******************/
#define DAC_DATO1_DACCH1DO ((uint16_t)0x0FFF) /*!< DAC channel1 data output */

/*******************  Bit definition for DAC_DATO2 register  *******************/
#define DAC_DATO2_DACCH2DO ((uint16_t)0x0FFF) /*!< DAC channel2 data output */



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
//#define TIM_CTRL1_C2SEL    ((uint32_t)0x00001000) /*!< Channel 2 selection from IOM/COMP */
//#define TIM_CTRL1_C3SEL    ((uint32_t)0x00002000) /*!< Channel 3 selection from IOM/COMP */
//#define TIM_CTRL1_C4SEL    ((uint32_t)0x00004000) /*!< Channel 4 selection from IOM/COMP */
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

#define RTC_CTRL_WTIEN    ((uint32_t)0x00004000)
#define RTC_CTRL_ALBIEN   ((uint32_t)0x00002000)
#define RTC_CTRL_ALAIEN   ((uint32_t)0x00001000)
#define RTC_CTRL_TSEN     ((uint32_t)0x00000800)
#define RTC_CTRL_WTEN     ((uint32_t)0x00000400)
#define RTC_CTRL_ALBEN    ((uint32_t)0x00000200)
#define RTC_CTRL_ALAEN    ((uint32_t)0x00000100)

#define RTC_CTRL_HFMT      ((uint32_t)0x00000040)
#define RTC_CTRL_BYPS      ((uint32_t)0x00000020)

#define RTC_CTRL_TSPOL     ((uint32_t)0x00000008)
#define RTC_CTRL_WKUPSEL   ((uint32_t)0x00000007)
#define RTC_CTRL_WKUPSEL_0 ((uint32_t)0x00000001)
#define RTC_CTRL_WKUPSEL_1 ((uint32_t)0x00000002)
#define RTC_CTRL_WKUPSEL_2 ((uint32_t)0x00000004)

/********************  Bits definition for RTC_INITSTS register  ******************/
#define RTC_INITSTS_RECPF  ((uint32_t)0x00010000)

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
#define RTC_SCTRL_ADFS   ((uint32_t)0x00007FFF)
#define RTC_SCTRL_SUB1S  ((uint32_t)0x80000000)

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



/******************************************************************************/
/*                                                                            */
/*                           Independent WATCHDOG                             */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for IWDG_KR register  ********************/
#define IWDG_KEY_KEYV ((uint16_t)0xFFFF) /*!< Key value (write only, read 0000h) */

/*******************  Bit definition for IWDG_PR register  ********************/
#define IWDG_PREDIV_PD ((uint8_t)0x07) /*!< PEND[2:0] (Prescaler divider) */
#define IWDG_PR_PR_0   ((uint8_t)0x01) /*!< Bit 0 */
#define IWDG_PR_PR_1   ((uint8_t)0x02) /*!< Bit 1 */
#define IWDG_PR_PR_2   ((uint8_t)0x04) /*!< Bit 2 */

/*******************  Bit definition for IWDG_RLR register  *******************/
#define IWDG_RELV_REL ((uint16_t)0x0FFF) /*!< Watchdog counter reload value */

/*******************  Bit definition for IWDG_SR register  ********************/
#define IWDG_STS_PVU  ((uint8_t)0x01) /*!< Watchdog prescaler value update */
#define IWDG_STS_CRVU ((uint8_t)0x02) /*!< Watchdog counter reload value update */

/******************************************************************************/
/*                                                                            */
/*                            Window WATCHDOG                                 */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for WWDG_CR register  ********************/
#define WWDG_CTRL_T  ((uint8_t)0x7F) /*!< T[6:0] bits (7-Bit counter (MSB to LSB)) */
#define WWDG_CTRL_T0 ((uint8_t)0x01) /*!< Bit 0 */
#define WWDG_CTRL_T1 ((uint8_t)0x02) /*!< Bit 1 */
#define WWDG_CTRL_T2 ((uint8_t)0x04) /*!< Bit 2 */
#define WWDG_CTRL_T3 ((uint8_t)0x08) /*!< Bit 3 */
#define WWDG_CTRL_T4 ((uint8_t)0x10) /*!< Bit 4 */
#define WWDG_CTRL_T5 ((uint8_t)0x20) /*!< Bit 5 */
#define WWDG_CTRL_T6 ((uint8_t)0x40) /*!< Bit 6 */

#define WWDG_CTRL_ACTB ((uint8_t)0x80) /*!< Activation bit */

/*******************  Bit definition for WWDG_CFR register  *******************/
#define WWDG_CFG_W  ((uint16_t)0x007F) /*!< W[6:0] bits (7-bit window value) */
#define WWDG_CFG_W0 ((uint16_t)0x0001) /*!< Bit 0 */
#define WWDG_CFG_W1 ((uint16_t)0x0002) /*!< Bit 1 */
#define WWDG_CFG_W2 ((uint16_t)0x0004) /*!< Bit 2 */
#define WWDG_CFG_W3 ((uint16_t)0x0008) /*!< Bit 3 */
#define WWDG_CFG_W4 ((uint16_t)0x0010) /*!< Bit 4 */
#define WWDG_CFG_W5 ((uint16_t)0x0020) /*!< Bit 5 */
#define WWDG_CFG_W6 ((uint16_t)0x0040) /*!< Bit 6 */

#define WWDG_CFG_TIMERB  ((uint16_t)0x0180) /*!< WDGTB[1:0] bits (Timer Base) */
#define WWDG_CFG_TIMERB0 ((uint16_t)0x0080) /*!< Bit 0 */
#define WWDG_CFG_TIMERB1 ((uint16_t)0x0100) /*!< Bit 1 */

#define WWDG_CFG_EWINT ((uint16_t)0x0200) /*!< Early Wakeup Interrupt */

/*******************  Bit definition for WWDG_SR register  ********************/
#define WWDG_STS_EWINTF ((uint8_t)0x01) /*!< Early Wakeup Interrupt Flag */

/******************************************************************************/
/*                                                                            */
/*                          SD host Interface                                 */
/*                                                                            */
/******************************************************************************/

/******************  Bit definition for SDIO_PWRCTRL register  ******************/
#define SDIO_PWRCTRL_PWRCTRL   ((uint8_t)0x03) /*!< PWRCTRL[1:0] bits (Power supply control bits) */
#define SDIO_PWRCTRL_PWRCTRL_0 ((uint8_t)0x01) /*!< Bit 0 */
#define SDIO_PWRCTRL_PWRCTRL_1 ((uint8_t)0x02) /*!< Bit 1 */

/******************  Bit definition for SDIO_CLKCTRL register  ******************/
#define SDIO_CLKCTRL_DIV     ((uint16_t)0x00FF) /*!< Clock divide factor */
#define SDIO_CLKCTRL_CLOCKEN ((uint16_t)0x0100) /*!< Clock enable bit */
#define SDIO_CLKCTRL_PWRCFG  ((uint16_t)0x0200) /*!< Power saving configuration bit */
#define SDIO_CLKCTRL_CLKBYP  ((uint16_t)0x0400) /*!< Clock divider bypass enable bit */

#define SDIO_CLKCTRL_BUSMODE   ((uint16_t)0x1800) /*!< WIDBUS[1:0] bits (Wide bus mode enable bit) */
#define SDIO_CLKCTRL_BUSMODE_0 ((uint16_t)0x0800) /*!< Bit 0 */
#define SDIO_CLKCTRL_BUSMODE_1 ((uint16_t)0x1000) /*!< Bit 1 */

#define SDIO_CLKCTRL_CLKEDGE ((uint16_t)0x2000) /*!< SDIO_CK dephasing selection bit */
#define SDIO_CLKCTRL_HWCLKEN ((uint16_t)0x4000) /*!< HW Flow Control enable */

/*******************  Bit definition for SDIO_CMDARG register  *******************/
#define SDIO_CMDARG_CMDARG ((uint32_t)0xFFFFFFFF) /*!< Command argument */

/*******************  Bit definition for SDIO_CMDCTRL register  *******************/
#define SDIO_CMDCTRL_CMDIDX ((uint16_t)0x003F) /*!< Command Index */

#define SDIO_CMDCTRL_CMDRESP   ((uint16_t)0x00C0) /*!< WAITRESP[1:0] bits (Wait for response bits) */
#define SDIO_CMDCTRL_CMDRESP_0 ((uint16_t)0x0040) /*!<  Bit 0 */
#define SDIO_CMDCTRL_CMDRESP_1 ((uint16_t)0x0080) /*!<  Bit 1 */

#define SDIO_CMDCTRL_WINTREQ ((uint16_t)0x0100) /*!< CPSM Waits for Interrupt Request */
#define SDIO_CMDCTRL_WDATEND ((uint16_t)0x0200) /*!< CPSM Waits for ends of data transfer (CmdPend internal signal) */
#define SDIO_CMDCTRL_CPSMEN  ((uint16_t)0x0400) /*!< Command path state machine (CPSM) Enable bit */
#define SDIO_CMDCTRL_SUSPEND ((uint16_t)0x0800) /*!< SD I/O suspend command */
#define SDIO_CMDCTRL_ENCMDF  ((uint16_t)0x1000) /*!< Enable CMDCTRL completion */
#define SDIO_CMDCTRL_INTDIS  ((uint16_t)0x2000) /*!< Not Interrupt Enable */
#define SDIO_CMDCTRL_CEATAEN ((uint16_t)0x4000) /*!< CE-ATA command */

/*****************  Bit definition for SDIO_CMDRESP register  *****************/
#define SDIO_CMDRESP_RESPCMDIDX ((uint8_t)0x3F) /*!< Response command index */

/******************  Bit definition for SDIO_RESPONSE_0 register  ******************/
#define SDIO_RESP0_CARDSTS0 ((uint32_t)0xFFFFFFFF) /*!< Card Status */

/******************  Bit definition for SDIO_RESPONSE_1 register  ******************/
#define SDIO_RESP1_CARDSTS1 ((uint32_t)0xFFFFFFFF) /*!< Card Status */

/******************  Bit definition for SDIO_RESPONSE_2 register  ******************/
#define SDIO_RESP2_CARDSTS2 ((uint32_t)0xFFFFFFFF) /*!< Card Status */

/******************  Bit definition for SDIO_RESPONSE_3 register  ******************/
#define SDIO_RESP3_CARDSTS3 ((uint32_t)0xFFFFFFFF) /*!< Card Status */

/******************  Bit definition for SDIO_RESPONSE_4 register  ******************/
#define SDIO_RESP4_CARDSTS4 ((uint32_t)0xFFFFFFFF) /*!< Card Status */

/******************  Bit definition for SDIO_DATTIMEOUT register  *****************/
#define SDIO_DATTIMEOUT_DATTIMEOUT ((uint32_t)0xFFFFFFFF) /*!< Data timeout period. */

/******************  Bit definition for SDIO_DATLEN register  *******************/
#define SDIO_DATLEN_DATLEN ((uint32_t)0x01FFFFFF) /*!< Data length value */

/******************  Bit definition for SDIO_DATCTRL register  ******************/
#define SDIO_DATCTRL_DATEN    ((uint16_t)0x0001) /*!< Data transfer enabled bit */
#define SDIO_DATCTRL_DATDIR   ((uint16_t)0x0002) /*!< Data transfer direction selection */
#define SDIO_DATCTRL_TRANSMOD ((uint16_t)0x0004) /*!< Data transfer mode selection */
#define SDIO_DATCTRL_DMAEN    ((uint16_t)0x0008) /*!< DMA enabled bit */

#define SDIO_DATCTRL_BLKSIZE   ((uint16_t)0x00F0) /*!< DBLOCKSIZE[3:0] bits (Data block size) */
#define SDIO_DATCTRL_BLKSIZE_0 ((uint16_t)0x0010) /*!< Bit 0 */
#define SDIO_DATCTRL_BLKSIZE_1 ((uint16_t)0x0020) /*!< Bit 1 */
#define SDIO_DATCTRL_BLKSIZE_2 ((uint16_t)0x0040) /*!< Bit 2 */
#define SDIO_DATCTRL_BLKSIZE_3 ((uint16_t)0x0080) /*!< Bit 3 */

#define SDIO_DATCTRL_RWAITEN   ((uint16_t)0x0100) /*!< Read wait start */
#define SDIO_DATCTRL_RWAITSTOP ((uint16_t)0x0200) /*!< Read wait stop */
#define SDIO_DATCTRL_RWAITMOD  ((uint16_t)0x0400) /*!< Read wait mode */
#define SDIO_DATCTRL_SDIOEN    ((uint16_t)0x0800) /*!< SD I/O enable functions */

/******************  Bit definition for SDIO_DATCOUNT register  *****************/
#define SDIO_DATCOUNT_DATCOUNT ((uint32_t)0x01FFFFFF) /*!< Data count value */

/******************  Bit definition for SDIO_STS register  ********************/
#define SDIO_STS_CCRCERR     ((uint32_t)0x00000001) /*!< Command response received (CRC check failed) */
#define SDIO_STS_DCRCERR     ((uint32_t)0x00000002) /*!< Data block sent/received (CRC check failed) */
#define SDIO_STS_CMDTIMEOUT  ((uint32_t)0x00000004) /*!< Command response timeout */
#define SDIO_STS_DATTIMEOUT  ((uint32_t)0x00000008) /*!< Data timeout */
#define SDIO_STS_TXURERR     ((uint32_t)0x00000010) /*!< Transmit DATFIFO underrun error */
#define SDIO_STS_RXORERR     ((uint32_t)0x00000020) /*!< Received DATFIFO overrun error */
#define SDIO_STS_CMDRESPRECV ((uint32_t)0x00000040) /*!< Command response received (CRC check passed) */
#define SDIO_STS_CMDSEND     ((uint32_t)0x00000080) /*!< Command sent (no response required) */
#define SDIO_STS_DATEND      ((uint32_t)0x00000100) /*!< Data end (data counter, SDIDCOUNT, is zero) */
#define SDIO_STS_SBERR       ((uint32_t)0x00000200) /*!< Start bit not detected on all data signals in wide bus mode */
#define SDIO_STS_DATBLKEND   ((uint32_t)0x00000400) /*!< Data block sent/received (CRC check passed) */
#define SDIO_STS_CMDRUN      ((uint32_t)0x00000800) /*!< Command transfer in progress */
#define SDIO_STS_TXRUN       ((uint32_t)0x00001000) /*!< Data transmit in progress */
#define SDIO_STS_RXRUN       ((uint32_t)0x00002000) /*!< Data receive in progress */
#define SDIO_STS_TFIFOHE                                                                                               \
    ((uint32_t)0x00004000) /*!< Transmit DATFIFO Half Empty: at least 8 words can be written into the DATFIFO */
#define SDIO_STS_RFIFOHF                                                                                               \
    ((uint32_t)0x00008000) /*!< Receive DATFIFO Half Full: there are at least 8 words in the DATFIFO */
#define SDIO_STS_TFIFOF    ((uint32_t)0x00010000) /*!< Transmit DATFIFO full */
#define SDIO_STS_RFIFOF    ((uint32_t)0x00020000) /*!< Receive DATFIFO full */
#define SDIO_STS_TFIFOE    ((uint32_t)0x00040000) /*!< Transmit DATFIFO empty */
#define SDIO_STS_RFIFOE    ((uint32_t)0x00080000) /*!< Receive DATFIFO empty */
#define SDIO_STS_TDATVALID ((uint32_t)0x00100000) /*!< Data available in transmit DATFIFO */
#define SDIO_STS_RDATVALID ((uint32_t)0x00200000) /*!< Data available in receive DATFIFO */
#define SDIO_STS_SDIOINT   ((uint32_t)0x00400000) /*!< SDIO interrupt received */
#define SDIO_STS_CEATAF    ((uint32_t)0x00800000) /*!< CE-ATA command completion signal received for CMD61 */

/*******************  Bit definition for SDIO_INTCLR register  *******************/
#define SDIO_INTCLR_CCRCERRC     ((uint32_t)0x00000001) /*!< CCRCFAIL flag clear bit */
#define SDIO_INTCLR_DCRCERRC     ((uint32_t)0x00000002) /*!< DCRCFAIL flag clear bit */
#define SDIO_INTCLR_CMDTIMEOUTC  ((uint32_t)0x00000004) /*!< CTIMEOUT flag clear bit */
#define SDIO_INTCLR_DATTIMEOUTC  ((uint32_t)0x00000008) /*!< DTIMEOUT flag clear bit */
#define SDIO_INTCLR_TXURERRC     ((uint32_t)0x00000010) /*!< TXUNDERR flag clear bit */
#define SDIO_INTCLR_RXORERRC     ((uint32_t)0x00000020) /*!< RXOVERR flag clear bit */
#define SDIO_INTCLR_CMDRESPRECVC ((uint32_t)0x00000040) /*!< CMDREND flag clear bit */
#define SDIO_INTCLR_CMDSENDC     ((uint32_t)0x00000080) /*!< CMDSENT flag clear bit */
#define SDIO_INTCLR_DATENDC      ((uint32_t)0x00000100) /*!< DATAEND flag clear bit */
#define SDIO_INTCLR_SBERRC       ((uint32_t)0x00000200) /*!< STBITERR flag clear bit */
#define SDIO_INTCLR_DATBLKENDC   ((uint32_t)0x00000400) /*!< DBCKEND flag clear bit */
#define SDIO_INTCLR_SDIOINTC     ((uint32_t)0x00400000) /*!< SDIOIT flag clear bit */
#define SDIO_INTCLR_CEATAFC      ((uint32_t)0x00800000) /*!< CEATAEND flag clear bit */

/******************  Bit definition for SDIO_INTEN register  *******************/
#define SDIO_INTEN_CCRCERREN     ((uint32_t)0x00000001) /*!< Command CRC Fail Interrupt Enable */
#define SDIO_INTEN_DCRCERREN     ((uint32_t)0x00000002) /*!< Data CRC Fail Interrupt Enable */
#define SDIO_INTEN_CMDTIMEOUTEN  ((uint32_t)0x00000004) /*!< Command TimeOut Interrupt Enable */
#define SDIO_INTEN_DATTIMEOUTEN  ((uint32_t)0x00000008) /*!< Data TimeOut Interrupt Enable */
#define SDIO_INTEN_TXURERREN     ((uint32_t)0x00000010) /*!< Tx DATFIFO UnderRun Error Interrupt Enable */
#define SDIO_INTEN_RXORERREN     ((uint32_t)0x00000020) /*!< Rx DATFIFO OverRun Error Interrupt Enable */
#define SDIO_INTEN_CMDRESPRECVEN ((uint32_t)0x00000040) /*!< Command Response Received Interrupt Enable */
#define SDIO_INTEN_CMDSENDEN     ((uint32_t)0x00000080) /*!< Command Sent Interrupt Enable */
#define SDIO_INTEN_DATENDEN      ((uint32_t)0x00000100) /*!< Data End Interrupt Enable */
#define SDIO_INTEN_SBERREN       ((uint32_t)0x00000200) /*!< Start Bit Error Interrupt Enable */
#define SDIO_INTEN_DATBLKENDEN   ((uint32_t)0x00000400) /*!< Data Block End Interrupt Enable */
#define SDIO_INTEN_CMDRUNEN      ((uint32_t)0x00000800) /*!< Command Acting Interrupt Enable */
#define SDIO_INTEN_TXRUNEN       ((uint32_t)0x00001000) /*!< Data Transmit Acting Interrupt Enable */
#define SDIO_INTEN_RXRUNEN       ((uint32_t)0x00002000) /*!< Data receive acting interrupt enabled */
#define SDIO_INTEN_TFIFOHEEN     ((uint32_t)0x00004000) /*!< Tx DATFIFO Half Empty interrupt Enable */
#define SDIO_INTEN_RFIFOHFEN     ((uint32_t)0x00008000) /*!< Rx DATFIFO Half Full interrupt Enable */
#define SDIO_INTEN_TFIFOFEN      ((uint32_t)0x00010000) /*!< Tx DATFIFO Full interrupt Enable */
#define SDIO_INTEN_RFIFOFEN      ((uint32_t)0x00020000) /*!< Rx DATFIFO Full interrupt Enable */
#define SDIO_INTEN_TFIFOEEN      ((uint32_t)0x00040000) /*!< Tx DATFIFO Empty interrupt Enable */
#define SDIO_INTEN_RFIFOEEN      ((uint32_t)0x00080000) /*!< Rx DATFIFO Empty interrupt Enable */
#define SDIO_INTEN_TDATVALIDEN   ((uint32_t)0x00100000) /*!< Data available in Tx DATFIFO interrupt Enable */
#define SDIO_INTEN_RDATVALIDEN   ((uint32_t)0x00200000) /*!< Data available in Rx DATFIFO interrupt Enable */
#define SDIO_INTEN_SDIOINTEN     ((uint32_t)0x00400000) /*!< SDIO Mode Interrupt Received interrupt Enable */
#define SDIO_INTEN_CEATAFEN      ((uint32_t)0x00800000) /*!< CE-ATA command completion signal received Interrupt Enable */

/*****************  Bit definition for SDIO_FIFOCOUNT register  *****************/
#define SDIO_FIFOCOUNT_FIFOCOUNT                                                                                       \
    ((uint32_t)0x00FFFFFF) /*!< Remaining number of words to be written to or read from the DATFIFO */

/******************  Bit definition for SDIO_DATFIFO register  *******************/
#define SDIO_DATFIFO_FIFIDAT ((uint32_t)0xFFFFFFFF) /*!< Receive and transmit DATFIFO data */

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
/*******************  Bit definition for CAN_MCR register  ********************/
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
#define DBG_CTRL_CAN1_STOP    ((uint32_t)0x00004000) /*!< Debug CAN1 stopped when Core is halted */
#define DBG_CTRL_I2C1SMBUS_TO ((uint32_t)0x00008000) /*!< I2C1 SMBUS timeout mode stopped when Core is halted */
#define DBG_CTRL_I2C2SMBUS_TO ((uint32_t)0x00010000) /*!< I2C2 SMBUS timeout mode stopped when Core is halted */
#define DBG_CTRL_TIM8_STOP    ((uint32_t)0x00020000) /*!< TIM8 counter stopped when core is halted */
#define DBG_CTRL_TIM5_STOP    ((uint32_t)0x00040000) /*!< TIM5 counter stopped when core is halted */
#define DBG_CTRL_TIM6_STOP    ((uint32_t)0x00080000) /*!< TIM6 counter stopped when core is halted */
#define DBG_CTRL_TIM7_STOP    ((uint32_t)0x00100000) /*!< TIM7 counter stopped when core is halted */
#define DBG_CTRL_CAN2_STOP    ((uint32_t)0x00200000) /*!< Debug CAN2 stopped when Core is halted */
/******************************************************************************/
/*                                                                            */
/*                      FLASH and Option Bytes Registers                      */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for FLASH_AC register  ******************/
#define FLASH_AC_LATENCY   ((uint8_t)0x07) /*!< LATENCY[2:0] bits (Latency) */
#define FLASH_AC_LATENCY_0 ((uint8_t)0x00) /*!< Bit 0 = 0 */
#define FLASH_AC_LATENCY_1 ((uint8_t)0x01) /*!< Bit 0 = 1 */
#define FLASH_AC_LATENCY_2 ((uint8_t)0x02) /*!< Bit 0 = 0; Bit 1 = 1 */
#define FLASH_AC_LATENCY_3 ((uint8_t)0x03) /*!< Bit 0 = 1; Bit 1 = 1 */
#define FLASH_AC_LATENCY_4 ((uint8_t)0x04) /*!< Bit 0 = 0; Bit 1 = 0; Bit 2 = 1 */

#define FLASH_AC_PRFTBFEN  ((uint8_t)0x10) /*!< Prefetch Buffer Enable */
#define FLASH_AC_PRFTBFSTS ((uint8_t)0x20) /*!< Prefetch Buffer Status */
#define FLASH_AC_ICAHRST   ((uint8_t)0x40) /*!< Icache Reset */
#define FLASH_AC_ICAHEN    ((uint8_t)0x80) /*!< Icache Enable */

/******************  Bit definition for FLASH_KEY register  ******************/
#define FLASH_KEY_FKEY ((uint32_t)0xFFFFFFFF) /*!< FPEC Key */

/*****************  Bit definition for FLASH_OPTKEY register  ****************/
#define FLASH_OPTKEY_OPTKEY ((uint32_t)0xFFFFFFFF) /*!< Option Byte Key */

/******************  Bit definition for FLASH_SR register  *******************/
#define FLASH_STS_BUSY     ((uint8_t)0x01) /*!< Busy */
#define FLASH_STS_PGERR    ((uint8_t)0x04) /*!< Programming Error */
#define FLASH_STS_PVERR    ((uint8_t)0x08) /*!< Programming Verify ERROR after program */
#define FLASH_STS_WRPERR   ((uint8_t)0x10) /*!< Write Protection Error */
#define FLASH_STS_EOP      ((uint8_t)0x20) /*!< End of operation */
#define FLASH_STS_EVERR    ((uint8_t)0x40) /*!< Erase Verify ERROR after page erase */

/*******************  Bit definition for FLASH_CR register  *******************/
#define FLASH_CTRL_PG        ((uint16_t)0x0001) /*!< Programming */
#define FLASH_CTRL_PER       ((uint16_t)0x0002) /*!< Page Erase */
#define FLASH_CTRL_MER       ((uint16_t)0x0004) /*!< Mass Erase */
#define FLASH_CTRL_OPTPG     ((uint16_t)0x0010) /*!< Option Byte Programming */
#define FLASH_CTRL_OPTER     ((uint16_t)0x0020) /*!< Option Byte Erase */
#define FLASH_CTRL_START     ((uint16_t)0x0040) /*!< Start */
#define FLASH_CTRL_LOCK      ((uint16_t)0x0080) /*!< Lock */
#define FLASH_CTRL_SMPSEL    ((uint16_t)0x0100) /*!< Flash Program Option Select */
#define FLASH_CTRL_OPTWRE    ((uint16_t)0x0200) /*!< Option Bytes Write Enable */
#define FLASH_CTRL_ERRITE    ((uint16_t)0x0400) /*!< Error Interrupt Enable */
#define FLASH_CTRL_FERRITE   ((uint16_t)0x0800) /*!< EVERR PVERR Error Interrupt Enable */
#define FLASH_CTRL_EOPITE    ((uint16_t)0x1000) /*!< End of operation Interrupt Enable */

/*******************  Bit definition for FLASH_ADD register  *******************/
#define FLASH_ADD_FADD ((uint32_t)0xFFFFFFFF) /*!< Flash Address */

/******************  Bit definition for FLASH_OBR register  *******************/
#define FLASH_OB_OBERR   ((uint16_t)0x0001) /*!< Option Byte Error */
#define FLASH_OBR_RDPRT1 ((uint16_t)0x0002) /*!< Read Protection */

#define FLASH_OBR_USER       ((uint16_t)0x03FC) /*!< User Option Bytes */
#define FLASH_OBR_WDG_SW     ((uint16_t)0x0004) /*!< WDG_SW */
#define FLASH_OBR_NRST_STOP0 ((uint16_t)0x0008) /*!< nRST_STOP */
#define FLASH_OBR_NRST_STDBY ((uint16_t)0x0010) /*!< nRST_STDBY */

#define FLASH_OBR_DATA0_MSK ((uint32_t)0x0003FC00) /*!< Data0 Mask */
#define FLASH_OBR_DATA1_MSK ((uint32_t)0x03FC0000) /*!< Data1 Mask */
#define FLASH_OBR_RDPRT2    ((uint32_t)0x80000000) /*!< Read Protection Level 2 */

/******************  Bit definition for FLASH_WRP register  ******************/
#define FLASH_WRP_WRPT ((uint32_t)0xFFFFFFFF) /*!< Write Protect */

/******************  Bit definition for FLASH_RDN register  ******************/
#define FLASH_RDN_FLASH_RDN0_MSK ((uint32_t)0x000001FF) /*!< RDN0 Mask */
#define FLASH_RDN_FLASH_RDN1_MSK ((uint32_t)0x01FF0000) /*!< RDN1 Mask */

/******************  Bit definition for FLASH_CAHR register  ******************/
#define FLASH_CAHR_LOCKSTRT_MSK ((uint32_t)0x000F) /*!< LOCKSTRT Mask */
#define FLASH_CAHR_LOCKSTOP_MSK ((uint32_t)0x00F0) /*!< LOCKSTOP Mask */
/*----------------------------------------------------------------------------*/

/******************  Bit definition for FLASH_RDP register  *******************/
#define FLASH_RDP_RDP1  ((uint32_t)0x000000FF) /*!< Read protection option byte */
#define FLASH_RDP_NRDP1 ((uint32_t)0x0000FF00) /*!< Read protection complemented option byte */

/******************  Bit definition for FLASH_USER register  ******************/
#define FLASH_USER_USER  ((uint32_t)0x00FF0000) /*!< User option byte */
#define FLASH_USER_NUSER ((uint32_t)0xFF000000) /*!< User complemented option byte */

/******************  Bit definition for FLASH_Data0 register  *****************/
#define FLASH_Data0_Data0  ((uint32_t)0x000000FF) /*!< User data storage option byte */
#define FLASH_Data0_NData0 ((uint32_t)0x0000FF00) /*!< User data storage complemented option byte */

/******************  Bit definition for FLASH_Data1 register  *****************/
#define FLASH_Data1_Data1  ((uint32_t)0x00FF0000) /*!< User data storage option byte */
#define FLASH_Data1_NData1 ((uint32_t)0xFF000000) /*!< User data storage complemented option byte */

/******************  Bit definition for FLASH_WRP0 register  ******************/
#define FLASH_WRP0_WRP0  ((uint32_t)0x000000FF) /*!< Flash memory write protection option bytes */
#define FLASH_WRP0_NWRP0 ((uint32_t)0x0000FF00) /*!< Flash memory write protection complemented option bytes */

/******************  Bit definition for FLASH_WRP1 register  ******************/
#define FLASH_WRP1_WRP1  ((uint32_t)0x00FF0000) /*!< Flash memory write protection option bytes */
#define FLASH_WRP1_NWRP1 ((uint32_t)0xFF000000) /*!< Flash memory write protection complemented option bytes */

/******************  Bit definition for FLASH_WRP2 register  ******************/
#define FLASH_WRP2_WRP2  ((uint32_t)0x000000FF) /*!< Flash memory write protection option bytes */
#define FLASH_WRP2_NWRP2 ((uint32_t)0x0000FF00) /*!< Flash memory write protection complemented option bytes */

/******************  Bit definition for FLASH_WRP3 register  ******************/
#define FLASH_WRP3_WRP3  ((uint32_t)0x00FF0000) /*!< Flash memory write protection option bytes */
#define FLASH_WRP3_NWRP3 ((uint32_t)0xFF000000) /*!< Flash memory write protection complemented option bytes */

/******************  Bit definition for FLASH_RDP2 register  *******************/
#define FLASH_RDP_RDP2  ((uint32_t)0x000000FF) /*!< Read protection level 2 option byte */
#define FLASH_RDP_NRDP2 ((uint32_t)0x0000FF00) /*!< Read protection level 2 complemented option byte */

/******************************************************************************/
/*                                                                            */
/*                                 TSC Registers                              */
/*                                                                            */
/******************************************************************************/
/****************  Bit definition for TSC_CTRL register         ****************/
#define TSC_CTRL_TM2_ETR_CH1_SHIFT      (13U)
#define TSC_CTRL_TM2_ETR_CH1_MASK       (0x1UL << TSC_CTRL_TM2_ETR_CH1_SHIFT)
#define TSC_CTRL_TM2_ETR_CH1            (TSC_CTRL_TM2_ETR_CH1_MASK)      /*!<TSC_out connected to TIM2_ETR and TIM2_CH1*/

#define TSC_CTRL_TM4_ETR_SHIFT          (12U)
#define TSC_CTRL_TM4_ETR_MASK           (0x1UL << TSC_CTRL_TM4_ETR_SHIFT)
#define TSC_CTRL_TM4_ETR                (TSC_CTRL_TM4_ETR_MASK)          /*!<TSC_out connected to TIM4_ETR*/

#define TSC_CTRL_DET_INTEN_SHIFT        (10U)
#define TSC_CTRL_DET_INTEN_MASK         (0x1UL << TSC_CTRL_DET_INTEN_SHIFT)
#define TSC_CTRL_DET_INTEN              (TSC_CTRL_DET_INTEN_MASK)        /*!<TSC interrupt control bit*/

#define TSC_CTRL_GREAT_DET_SEL_SHIFT    (9U)
#define TSC_CTRL_GREAT_DET_SEL_MASK     (0x1UL << TSC_CTRL_GREAT_DET_SEL_SHIFT)
#define TSC_CTRL_GREAT_DET_SEL          (TSC_CTRL_GREAT_DET_SEL_MASK)    /*!<TSC great detect control*/

#define TSC_CTRL_LESS_DET_SEL_SHIFT     (8U)
#define TSC_CTRL_LESS_DET_SEL_MASK      (0x1UL << TSC_CTRL_LESS_DET_SEL_SHIFT)
#define TSC_CTRL_LESS_DET_SEL           (TSC_CTRL_LESS_DET_SEL_MASK)     /*!<TSC less detect control*/

#define TSC_CTRL_HW_DET_ST_SHIFT        (7U)
#define TSC_CTRL_HW_DET_ST_MASK         (0x1UL << TSC_CTRL_HW_DET_ST_SHIFT)
#define TSC_CTRL_HW_DET_ST              (TSC_CTRL_HW_DET_ST_MASK)        /*!<Status of TSC hardware detect mode*/

#define TSC_CTRL_HW_DET_MODE_SHIFT      (6U)
#define TSC_CTRL_HW_DET_MODE_MASK       (0x1UL << TSC_CTRL_HW_DET_MODE_SHIFT)
#define TSC_CTRL_HW_DET_MODE            (TSC_CTRL_HW_DET_MODE_MASK)      /*!<TSC hardware detect mode control*/

#define TSC_CTRL_DET_FILTER_SHIFT       (4U)
#define TSC_CTRL_DET_FILTER_MASK        (0x3UL << TSC_CTRL_DET_FILTER_SHIFT)
#define TSC_CTRL_DET_FILTER             (TSC_CTRL_DET_FILTER_MASK)       /*!<TSC filter for continuously detect */
#define TSC_CTRL_DET_FILTER_0           (0x1UL << TSC_CTRL_DET_FILTER_SHIFT)
#define TSC_CTRL_DET_FILTER_1           (0x2UL << TSC_CTRL_DET_FILTER_SHIFT)

#define TSC_CTRL_DET_PERIOD_SHIFT       (0U)
#define TSC_CTRL_DET_PERIOD_MASK        (0xFUL << TSC_CTRL_DET_PERIOD_SHIFT)
#define TSC_CTRL_DET_PERIOD             (TSC_CTRL_DET_PERIOD_MASK)       /*!<TSC detect time of one sample */
#define TSC_CTRL_DET_PERIOD_0           (0x1UL << TSC_CTRL_DET_PERIOD_SHIFT)
#define TSC_CTRL_DET_PERIOD_1           (0x2UL << TSC_CTRL_DET_PERIOD_SHIFT)
#define TSC_CTRL_DET_PERIOD_2           (0x4UL << TSC_CTRL_DET_PERIOD_SHIFT)
#define TSC_CTRL_DET_PERIOD_3           (0x8UL << TSC_CTRL_DET_PERIOD_SHIFT)

/****************  Bit definition for TSC TSC_CHNEN register    ****************/
#define TSC_CHNEN_CHN_SEL_MASK          (0x00FFFFFF)
#define TSC_CHNEN_CHN_SEL_SHIFT         (0U)
#define TSC_CHNEN_CHN_SEL0              (0x1UL << 0) /*!< Channel 0 enable bit */
#define TSC_CHNEN_CHN_SEL1              (0x1UL << 1) /*!< Channel 1 enable bit */
#define TSC_CHNEN_CHN_SEL2              (0x1UL << 2) /*!< Channel 2 enable bit */
#define TSC_CHNEN_CHN_SEL3              (0x1UL << 3) /*!< Channel 3 enable bit */
#define TSC_CHNEN_CHN_SEL4              (0x1UL << 4) /*!< Channel 4 enable bit */
#define TSC_CHNEN_CHN_SEL5              (0x1UL << 5) /*!< Channel 5 enable bit */
#define TSC_CHNEN_CHN_SEL6              (0x1UL << 6) /*!< Channel 6 enable bit */
#define TSC_CHNEN_CHN_SEL7              (0x1UL << 7) /*!< Channel 7 enable bit */
#define TSC_CHNEN_CHN_SEL8              (0x1UL << 8) /*!< Channel 8 enable bit */
#define TSC_CHNEN_CHN_SEL9              (0x1UL << 9) /*!< Channel 9 enable bit */
#define TSC_CHNEN_CHN_SEL10             (0x1UL << 10) /*!< Channel 10 enable bit */
#define TSC_CHNEN_CHN_SEL11             (0x1UL << 11) /*!< Channel 11 enable bit */
#define TSC_CHNEN_CHN_SEL12             (0x1UL << 12) /*!< Channel 12 enable bit */
#define TSC_CHNEN_CHN_SEL13             (0x1UL << 13) /*!< Channel 13 enable bit */
#define TSC_CHNEN_CHN_SEL14             (0x1UL << 14) /*!< Channel 14 enable bit */
#define TSC_CHNEN_CHN_SEL15             (0x1UL << 15) /*!< Channel 15 enable bit */
#define TSC_CHNEN_CHN_SEL16             (0x1UL << 16) /*!< Channel 16 enable bit */
#define TSC_CHNEN_CHN_SEL17             (0x1UL << 17) /*!< Channel 17 enable bit */
#define TSC_CHNEN_CHN_SEL18             (0x1UL << 18) /*!< Channel 18 enable bit */
#define TSC_CHNEN_CHN_SEL19             (0x1UL << 19) /*!< Channel 19 enable bit */
#define TSC_CHNEN_CHN_SEL20             (0x1UL << 20) /*!< Channel 20 enable bit */
#define TSC_CHNEN_CHN_SEL21             (0x1UL << 21) /*!< Channel 21 enable bit */
#define TSC_CHNEN_CHN_SEL22             (0x1UL << 22) /*!< Channel 22 enable bit */
#define TSC_CHNEN_CHN_SEL23             (0x1UL << 23) /*!< Channel 23 enable bit */

/****************  Bit definition for TSC TSC_STS register      ****************/
#define TSC_STS_CHN_NUM_SHIFT           (16U)
#define TSC_STS_CHN_NUM_MASK            (0x1FUL << TSC_STS_CHN_NUM_SHIFT)
#define TSC_STS_CHN_NUM                 TSC_STS_CHN_NUM_MASK     /*!<Current detect channel number */
#define TSC_STS_CHN_NUM_0               (0x1UL  << TSC_STS_CHN_NUM_SHIFT)
#define TSC_STS_CHN_NUM_1               (0x2UL  << TSC_STS_CHN_NUM_SHIFT)
#define TSC_STS_CHN_NUM_2               (0x4UL  << TSC_STS_CHN_NUM_SHIFT)
#define TSC_STS_CHN_NUM_3               (0x8UL  << TSC_STS_CHN_NUM_SHIFT)
#define TSC_STS_CHN_NUM_4               (0x10UL << TSC_STS_CHN_NUM_SHIFT)

#define TSC_STS_GREAT_DET_SHIFT         (13U)
#define TSC_STS_GREAT_DET_MASK          (0x1UL << TSC_STS_GREAT_DET_SHIFT)
#define TSC_STS_GREAT_DET               TSC_STS_GREAT_DET_MASK   /*!<Status of TSC great detect*/

#define TSC_STS_LESS_DET_SHIFT          (12U)
#define TSC_STS_LESS_DET_MASK           (0x1UL << TSC_STS_LESS_DET_SHIFT)
#define TSC_STS_LESS_DET                TSC_STS_LESS_DET_MASK    /*!<Status of TSC less detect*/

#define TSC_STS_CNT_VAL_SHIFT           (0U)
#define TSC_STS_CNT_VAL_MASK            (0x7FFUL << TSC_STS_CNT_VAL_SHIFT)
#define TSC_STS_CNT_VAL                 TSC_STS_CNT_VAL_MASK     /*!<The pulse count value for current channel*/
#define TSC_STS_CNT_VAL_0               (0x001UL << TSC_STS_CNT_VAL_SHIFT)
#define TSC_STS_CNT_VAL_1               (0x002UL << TSC_STS_CNT_VAL_SHIFT)
#define TSC_STS_CNT_VAL_2               (0x004UL << TSC_STS_CNT_VAL_SHIFT)
#define TSC_STS_CNT_VAL_3               (0x008UL << TSC_STS_CNT_VAL_SHIFT)
#define TSC_STS_CNT_VAL_4               (0x010UL << TSC_STS_CNT_VAL_SHIFT)
#define TSC_STS_CNT_VAL_5               (0x020UL << TSC_STS_CNT_VAL_SHIFT)
#define TSC_STS_CNT_VAL_6               (0x040UL << TSC_STS_CNT_VAL_SHIFT)
#define TSC_STS_CNT_VAL_7               (0x080UL << TSC_STS_CNT_VAL_SHIFT)
#define TSC_STS_CNT_VAL_8               (0x100UL << TSC_STS_CNT_VAL_SHIFT)
#define TSC_STS_CNT_VAL_9               (0x200UL << TSC_STS_CNT_VAL_SHIFT)
#define TSC_STS_CNT_VAL_10              (0x400UL << TSC_STS_CNT_VAL_SHIFT)

/****************  Bit definition for TSC_ANA_CTRL register      ****************/
#define TSC_ANA_CTRL_SW_TSC_EN_SHIFT    (5U)
#define TSC_ANA_CTRL_SW_TSC_EN_MASK     (0x1UL << TSC_ANA_CTRL_SW_TSC_EN_SHIFT)
#define TSC_ANA_CTRL_SW_TSC_EN          TSC_ANA_CTRL_SW_TSC_EN_MASK  /*!<TSC software detect mode control bit*/

#define TSC_ANA_CTRL_SW_PAD_MUX_SHIFT   (0U)
#define TSC_ANA_CTRL_SW_PAD_MUX_MASK    (0x1FUL << TSC_ANA_CTRL_SW_PAD_MUX_SHIFT)
#define TSC_ANA_CTRL_SW_PAD_MUX         TSC_ANA_CTRL_SW_PAD_MUX_MASK /*!<Current channel number of TSC software detect mode*/
#define TSC_ANA_CTRL_SW_PAD_MUX_0       (0x01UL << TSC_ANA_CTRL_SW_PAD_MUX_SHIFT)
#define TSC_ANA_CTRL_SW_PAD_MUX_1       (0x02UL << TSC_ANA_CTRL_SW_PAD_MUX_SHIFT)
#define TSC_ANA_CTRL_SW_PAD_MUX_2       (0x04UL << TSC_ANA_CTRL_SW_PAD_MUX_SHIFT)
#define TSC_ANA_CTRL_SW_PAD_MUX_3       (0x08UL << TSC_ANA_CTRL_SW_PAD_MUX_SHIFT)
#define TSC_ANA_CTRL_SW_PAD_MUX_4       (0x10UL << TSC_ANA_CTRL_SW_PAD_MUX_SHIFT)


/****************  Bit definition for TSC_ANA_SEL register      ****************/
#define TSC_ANA_SEL_PAD_OPT_SHIFT       (6U)
#define TSC_ANA_SEL_PAD_OPT_MASK        (0x01UL << TSC_ANA_SEL_PAD_OPT_SHIFT)
#define TSC_ANA_SEL_PAD_OPT             TSC_ANA_SEL_PAD_OPT_MASK     /*!<TSC charge pad control bit,internal or external resistor*/

#define TSC_ANA_SEL_SP_OPT_SHIFT        (4U)
#define TSC_ANA_SEL_SP_OPT_MASK         (0x3UL << TSC_ANA_SEL_SP_OPT_SHIFT)
#define TSC_ANA_SEL_SP_OPT              TSC_ANA_SEL_SP_OPT_MASK          /*!<TSC speed control bits*/
#define TSC_ANA_SEL_SP_OPT_0            (0x1UL << TSC_ANA_SEL_SP_OPT_SHIFT)
#define TSC_ANA_SEL_SP_OPT_1            (0x2UL << TSC_ANA_SEL_SP_OPT_SHIFT)

/*****************  Resistor value of  TSC_RESRx register  *****************/
#define TSC_RESR_CHN_RESIST_MASK        (0x7UL) /*!< TSC_RESR 0 channel 0 */
#define TSC_RESR_CHN_RESIST_1M          (0x0UL) /*!< 1M ohm */
#define TSC_RESR_CHN_RESIST_875K        (0x1UL) /*!< 875K 0hm */
#define TSC_RESR_CHN_RESIST_750K        (0x2UL) /*!< 750K ohm */
#define TSC_RESR_CHN_RESIST_625K        (0x3UL) /*!< 625K ohm */
#define TSC_RESR_CHN_RESIST_500K        (0x4UL) /*!< 500K ohm */
#define TSC_RESR_CHN_RESIST_375K        (0x5UL) /*!< 375K ohm */
#define TSC_RESR_CHN_RESIST_250K        (0x6UL) /*!< 250K ohm */
#define TSC_RESR_CHN_RESIST_125K        (0x7UL) /*!< 125K ohm */

/*****************  Bit definition for TSC_RESR0 register  *****************/
#define TSC_RESR0_CHN_RESIST0_SHIFT     (0U)  /*!< TSC_RESR 0 channel 0 */
#define TSC_RESR0_CHN_RESIST1_SHIFT     (4U)  /*!< TSC_RESR 0 channel 1 */
#define TSC_RESR0_CHN_RESIST2_SHIFT     (8U)  /*!< TSC_RESR 0 channel 2 */
#define TSC_RESR0_CHN_RESIST3_SHIFT     (12U) /*!< TSC_RESR 0 channel 3 */
#define TSC_RESR0_CHN_RESIST4_SHIFT     (16U) /*!< TSC_RESR 0 channel 4 */
#define TSC_RESR0_CHN_RESIST5_SHIFT     (20U) /*!< TSC_RESR 0 channel 5 */
#define TSC_RESR0_CHN_RESIST6_SHIFT     (24U) /*!< TSC_RESR 0 channel 6 */
#define TSC_RESR0_CHN_RESIST7_SHIFT     (28U) /*!< TSC_RESR 0 channel 7 */

/*****************  Bit definition for TSC_RESR1 register  *****************/
#define TSC_RESR1_CHN_RESIST8_SHIFT     (0U)  /*!< TSC_RESR 1 channel 8  */
#define TSC_RESR1_CHN_RESIST9_SHIFT     (4U)  /*!< TSC_RESR 1 channel 9  */
#define TSC_RESR1_CHN_RESIST10_SHIFT    (8U)  /*!< TSC_RESR 1 channel 10 */
#define TSC_RESR1_CHN_RESIST11_SHIFT    (12U) /*!< TSC_RESR 1 channel 11 */
#define TSC_RESR1_CHN_RESIST12_SHIFT    (16U) /*!< TSC_RESR 1 channel 12 */
#define TSC_RESR1_CHN_RESIST13_SHIFT    (20U) /*!< TSC_RESR 1 channel 13 */
#define TSC_RESR1_CHN_RESIST14_SHIFT    (24U) /*!< TSC_RESR 1 channel 14 */
#define TSC_RESR1_CHN_RESIST15_SHIFT    (28U) /*!< TSC_RESR 1 channel 15 */

/*****************  Bit definition for TSC_RESR2 register  *****************/
#define TSC_RESR2_CHN_RESIST16_SHIFT    (0U)  /*!< TSC_RESR 2 channel 16 */
#define TSC_RESR2_CHN_RESIST17_SHIFT    (4U)  /*!< TSC_RESR 2 channel 17 */
#define TSC_RESR2_CHN_RESIST18_SHIFT    (8U)  /*!< TSC_RESR 2 channel 18 */
#define TSC_RESR2_CHN_RESIST19_SHIFT    (12U) /*!< TSC_RESR 2 channel 19 */
#define TSC_RESR2_CHN_RESIST20_SHIFT    (16U) /*!< TSC_RESR 2 channel 20 */
#define TSC_RESR2_CHN_RESIST21_SHIFT    (20U) /*!< TSC_RESR 2 channel 21 */
#define TSC_RESR2_CHN_RESIST22_SHIFT    (24U) /*!< TSC_RESR 2 channel 22 */
#define TSC_RESR2_CHN_RESIST23_SHIFT    (28U) /*!< TSC_RESR 2 channel 23 */

/****************  Bit definition for TSC_THRHDx register       ****************/
#define TSC_THRHD_DELTA_SHIFT           (16U)
#define TSC_THRHD_DELTA_MASK            (0xFF << TSC_THRHD_DELTA_SHIFT)
#define TSC_THRHD_DELTA                 TSC_THRHD_DELTA_MASK    /*!<TSC_THRHD register delta bit */
#define TSC_THRHD_DELTA_0               (0x01UL << TSC_THRHD_DELTA_SHIFT)
#define TSC_THRHD_DELTA_1               (0x02UL << TSC_THRHD_DELTA_SHIFT)
#define TSC_THRHD_DELTA_2               (0x04UL << TSC_THRHD_DELTA_SHIFT)
#define TSC_THRHD_DELTA_3               (0x08UL << TSC_THRHD_DELTA_SHIFT)
#define TSC_THRHD_DELTA_4               (0x10UL << TSC_THRHD_DELTA_SHIFT)
#define TSC_THRHD_DELTA_5               (0x20UL << TSC_THRHD_DELTA_SHIFT)
#define TSC_THRHD_DELTA_6               (0x40UL << TSC_THRHD_DELTA_SHIFT)
#define TSC_THRHD_DELTA_7               (0x80UL << TSC_THRHD_DELTA_SHIFT)

#define TSC_THRHD_BASE_SHIFT            (0U)
#define TSC_THRHD_BASE_MASK             (0x7FFUL << TSC_THRHD_BASE_SHIFT)
#define TSC_THRHD_BASE                  TSC_THRHD_BASE_MASK     /*!<TSC_THRHD register base bit */
#define TSC_THRHD_BASE_0                (0x001UL << TSC_THRHD_BASE_SHIFT)
#define TSC_THRHD_BASE_1                (0x002UL << TSC_THRHD_BASE_SHIFT)
#define TSC_THRHD_BASE_2                (0x004UL << TSC_THRHD_BASE_SHIFT)
#define TSC_THRHD_BASE_3                (0x008UL << TSC_THRHD_BASE_SHIFT)
#define TSC_THRHD_BASE_4                (0x010UL << TSC_THRHD_BASE_SHIFT)
#define TSC_THRHD_BASE_5                (0x020UL << TSC_THRHD_BASE_SHIFT)
#define TSC_THRHD_BASE_6                (0x040UL << TSC_THRHD_BASE_SHIFT)
#define TSC_THRHD_BASE_7                (0x080UL << TSC_THRHD_BASE_SHIFT)
#define TSC_THRHD_BASE_8                (0x100UL << TSC_THRHD_BASE_SHIFT)
#define TSC_THRHD_BASE_9                (0x200UL << TSC_THRHD_BASE_SHIFT)
#define TSC_THRHD_BASE_10               (0x400UL << TSC_THRHD_BASE_SHIFT)

/******************************************************************************/
/*                                                                            */
/*                                 DVP Registers                              */
/*                                                                            */
/******************************************************************************/

/****************  Bit definition for DVP_CTRL register        ****************/
#define DVP_CTRL_FFSWRST_SHIFT              (16UL)
#define DVP_CTRL_FFSWRST_MASK               (0x1UL << DVP_CTRL_FFSWRST_SHIFT)
#define DVP_CTRL_FFSWRST                    (DVP_CTRL_FFSWRST_MASK)

#define DVP_CTRL_FWM_SHIFT                  (12UL)
#define DVP_CTRL_FWM_MASK                   (0x7UL << DVP_CTRL_FWM_SHIFT)
#define DVP_CTRL_FWM                        (DVP_CTRL_FWM_MASK)
#define DVP_CTRL_FWM_0                      (0x1UL << DVP_CTRL_FWM_SHIFT)
#define DVP_CTRL_FWM_1                      (0x2UL << DVP_CTRL_FWM_SHIFT)
#define DVP_CTRL_FWM_2                      (0x4UL << DVP_CTRL_FWM_SHIFT)

#define DVP_CTRL_LSM_SHIFT                  (9UL)
#define DVP_CTRL_LSM_MASK                   (0x7UL << DVP_CTRL_LSM_SHIFT)
#define DVP_CTRL_LSM                        (DVP_CTRL_LSM_MASK)
#define DVP_CTRL_LSM_0                      (0x1UL << DVP_CTRL_LSM_SHIFT)
#define DVP_CTRL_LSM_1                      (0x2UL << DVP_CTRL_LSM_SHIFT)
#define DVP_CTRL_LSM_2                      (0x4UL << DVP_CTRL_LSM_SHIFT)

#define DVP_CTRL_BSM_SHIFT                  (6UL)
#define DVP_CTRL_BSM_MASK                   (0x7UL << DVP_CTRL_BSM_SHIFT)
#define DVP_CTRL_BSM                        (DVP_CTRL_BSM_MASK)
#define DVP_CTRL_BSM_0                      (0x1UL << DVP_CTRL_BSM_SHIFT)
#define DVP_CTRL_BSM_1                      (0x2UL << DVP_CTRL_BSM_SHIFT)
#define DVP_CTRL_BSM_2                      (0x4UL << DVP_CTRL_BSM_SHIFT)

#define DVP_CTRL_DATINV_SHIFT               (5UL)
#define DVP_CTRL_DATINV_MASK                (0x1UL << DVP_CTRL_DATINV_SHIFT)
#define DVP_CTRL_DATINV                     (DVP_CTRL_DATINV_MASK)

#define DVP_CTRL_PCKPOL_SHIFT               (4UL)
#define DVP_CTRL_PCKPOL_MASK                (0x1UL << DVP_CTRL_PCKPOL_SHIFT)
#define DVP_CTRL_PCKPOL                     (DVP_CTRL_PCKPOL_MASK)

#define DVP_CTRL_VSPOL_SHIFT                (3UL)
#define DVP_CTRL_VSPOL_MASK                 (0x1UL << DVP_CTRL_VSPOL_SHIFT)
#define DVP_CTRL_VSPOL                      (DVP_CTRL_VSPOL_MASK)

#define DVP_CTRL_HSPOL_SHIFT                (2UL)
#define DVP_CTRL_HSPOL_MASK                 (0x1UL << DVP_CTRL_HSPOL_SHIFT)
#define DVP_CTRL_HSPOL                      (DVP_CTRL_HSPOL_MASK)

#define DVP_CTRL_CM_SHIFT                   (1UL)
#define DVP_CTRL_CM_MASK                    (0x1UL << DVP_CTRL_CM_SHIFT)
#define DVP_CTRL_CM                         (DVP_CTRL_CM_MASK)

#define DVP_CTRL_CAPTURE_SHIFT              (0UL)
#define DVP_CTRL_CAPTURE_MASK               (0x1UL << DVP_CTRL_CAPTURE_SHIFT)
#define DVP_CTRL_CAPTURE                    (DVP_CTRL_CAPTURE_MASK)

/****************  Bit definition for DVP_STS register        ****************/
#define DVP_STS_FCNT_SHIFT                  (1UL)
#define DVP_STS_FCNT_MASK                   (0x7UL << DVP_STS_FCNT_SHIFT)
#define DVP_STS_FCNT                        (DVP_STS_FCNT_MASK)
#define DVP_STS_FCNT_0                      (0x1UL << DVP_STS_FCNT_SHIFT)
#define DVP_STS_FCNT_1                      (0x2UL << DVP_STS_FCNT_SHIFT)
#define DVP_STS_FCNT_2                      (0x4UL << DVP_STS_FCNT_SHIFT)

#define DVP_STS_FNE_SHIFT                   (0UL)
#define DVP_STS_FNE_MASK                    (0x1UL << DVP_STS_FNE_SHIFT)
#define DVP_STS_FNE                         (DVP_STS_FNE_MASK)

/****************  Bit definition for DVP_INTSTS register     ****************/
#define DVP_INTSTS_HERRIS_SHIFT             (9UL)
#define DVP_INTSTS_HERRIS_MASK              (0x1UL << DVP_INTSTS_HERRIS_SHIFT)
#define DVP_INTSTS_HERRIS                   (DVP_INTSTS_HERRIS_MASK)

#define DVP_INTSTS_VERRIS_SHIFT             (8UL)
#define DVP_INTSTS_VERRIS_MASK              (0x1UL << DVP_INTSTS_VERRIS_SHIFT)
#define DVP_INTSTS_VERRIS                   (DVP_INTSTS_VERRIS_MASK)

#define DVP_INTSTS_FOIS_SHIFT               (7UL)
#define DVP_INTSTS_FOIS_MASK                (0x1UL << DVP_INTSTS_FOIS_SHIFT)
#define DVP_INTSTS_FOIS                     (DVP_INTSTS_FOIS_MASK)

#define DVP_INTSTS_FWIS_SHIFT               (6UL)
#define DVP_INTSTS_FWIS_MASK                (0x1UL << DVP_INTSTS_FWIS_SHIFT)
#define DVP_INTSTS_FWIS                     (DVP_INTSTS_FWIS_MASK)

#define DVP_INTSTS_FFIS_SHIFT               (5UL)
#define DVP_INTSTS_FFIS_MASK                (0x1UL << DVP_INTSTS_FFIS_SHIFT)
#define DVP_INTSTS_FFIS                     (DVP_INTSTS_FFIS_MASK)

#define DVP_INTSTS_FEIS_SHIFT               (4UL)
#define DVP_INTSTS_FEIS_MASK                (0x1UL << DVP_INTSTS_FEIS_SHIFT)
#define DVP_INTSTS_FEIS                     (DVP_INTSTS_FEIS_MASK)

#define DVP_INTSTS_LEIS_SHIFT               (3UL)
#define DVP_INTSTS_LEIS_MASK                (0x1UL << DVP_INTSTS_LEIS_SHIFT)
#define DVP_INTSTS_LEIS                     (DVP_INTSTS_LEIS_MASK)

#define DVP_INTSTS_LSIS_SHIFT               (2UL)
#define DVP_INTSTS_LSIS_MASK                (0x1UL << DVP_INTSTS_LSIS_SHIFT)
#define DVP_INTSTS_LSIS                     (DVP_INTSTS_LSIS_MASK)

#define DVP_INTSTS_FMEIS_SHIFT              (1UL)
#define DVP_INTSTS_FMEIS_MASK               (0x1UL << DVP_INTSTS_FMEIS_SHIFT)
#define DVP_INTSTS_FMEIS                    (DVP_INTSTS_FMEIS_MASK)

#define DVP_INTSTS_FMSIS_SHIFT              (0UL)
#define DVP_INTSTS_FMSIS_MASK               (0x1UL << DVP_INTSTS_FMSIS_SHIFT)
#define DVP_INTSTS_FMSIS                    (DVP_INTSTS_FMSIS_MASK)

/****************  Bit definition for DVP_INTEN register      ****************/
#define DVP_INTEN_DMAEN_SHIFT               (10UL)
#define DVP_INTEN_DMAEN_MASK                (0x1UL << DVP_INTEN_DMAEN_SHIFT)
#define DVP_INTEN_DMAEN                     (DVP_INTEN_DMAEN_MASK)

#define DVP_INTEN_HERRIE_SHIFT              (9UL)
#define DVP_INTEN_HERRIE_MASK               (0x1UL << DVP_INTEN_HERRIE_SHIFT)
#define DVP_INTEN_HERRIE                    (DVP_INTEN_HERRIE_MASK)

#define DVP_INTEN_VERRIE_SHIFT              (8UL)
#define DVP_INTEN_VERRIE_MASK               (0x1UL << DVP_INTEN_VERRIE_SHIFT)
#define DVP_INTEN_VERRIE                    (DVP_INTEN_VERRIE_MASK)

#define DVP_INTEN_FOIE_SHIFT                (7UL)
#define DVP_INTEN_FOIE_MASK                 (0x1UL << DVP_INTEN_FOIE_SHIFT)
#define DVP_INTEN_FOIE                      (DVP_INTEN_FOIE_MASK)

#define DVP_INTEN_FWIE_SHIFT                (6UL)
#define DVP_INTEN_FWIE_MASK                 (0x1UL << DVP_INTEN_FWIE_SHIFT)
#define DVP_INTEN_FWIE                      (DVP_INTEN_FWIE_MASK)

#define DVP_INTEN_FFIE_SHIFT                (5UL)
#define DVP_INTEN_FFIE_MASK                 (0x1UL << DVP_INTEN_FFIE_SHIFT)
#define DVP_INTEN_FFIE                      (DVP_INTEN_FFIE_MASK)

#define DVP_INTEN_FEIE_SHIFT                (4UL)
#define DVP_INTEN_FEIE_MASK                 (0x1UL << DVP_INTEN_FEIE_SHIFT)
#define DVP_INTEN_FEIE                      (DVP_INTEN_FEIE_MASK)

#define DVP_INTEN_LEIE_SHIFT                (3UL)
#define DVP_INTEN_LEIE_MASK                 (0x1UL << DVP_INTEN_LEIE_SHIFT)
#define DVP_INTEN_LEIE                      (DVP_INTEN_LEIE_MASK)

#define DVP_INTEN_LSIE_SHIFT                (2UL)
#define DVP_INTEN_LSIE_MASK                 (0x1UL << DVP_INTEN_LSIE_SHIFT)
#define DVP_INTEN_LSIE                      (DVP_INTEN_LSIE_MASK)

#define DVP_INTEN_FMEIE_SHIFT               (1UL)
#define DVP_INTEN_FMEIE_MASK                (0x1UL << DVP_INTEN_FMEIE_SHIFT)
#define DVP_INTEN_FMEIE                     (DVP_INTEN_FMEIE_MASK)

#define DVP_INTEN_FMSIE_SHIFT               (0UL)
#define DVP_INTEN_FMSIE_MASK                (0x1UL << DVP_INTEN_FMSIE_SHIFT)
#define DVP_INTEN_FMSIE                     (DVP_INTEN_FMSIE_MASK)

/****************  Bit definition for DVP_MINTSTS register    ****************/
#define DVP_MINTSTS_HERRMIS_SHIFT           (9UL)
#define DVP_MINTSTS_HERRMIS_MASK            (0x1UL << DVP_MINTSTS_HERRMIS_SHIFT)
#define DVP_MINTSTS_HERRMIS                 (DVP_MINTSTS_HERRMIS_MASK)

#define DVP_MINTSTS_VERRMIS_SHIFT           (8UL)
#define DVP_MINTSTS_VERRMIS_MASK            (0x1UL << DVP_MINTSTS_VERRMIS_SHIFT)
#define DVP_MINTSTS_VERRMIS                 (DVP_MINTSTS_VERRMIS_MASK)

#define DVP_MINTSTS_FOMIS_SHIFT             (7UL)
#define DVP_MINTSTS_FOMIS_MASK              (0x1UL << DVP_MINTSTS_FOMIS_SHIFT)
#define DVP_MINTSTS_FOMIS                   (DVP_MINTSTS_FOMIS_MASK)

#define DVP_MINTSTS_FWMIS_SHIFT             (6UL)
#define DVP_MINTSTS_FWMIS_MASK              (0x1UL << DVP_MINTSTS_FWMIS_SHIFT)
#define DVP_MINTSTS_FWMIS                   (DVP_MINTSTS_FWMIS_MASK)

#define DVP_MINTSTS_FFMIS_SHIFT             (5UL)
#define DVP_MINTSTS_FFMIS_MASK              (0x1UL << DVP_MINTSTS_FFMIS_SHIFT)
#define DVP_MINTSTS_FFMIS                   (DVP_MINTSTS_FFMIS_MASK)

#define DVP_MINTSTS_FEMIS_SHIFT             (4UL)
#define DVP_MINTSTS_FEMIS_MASK              (0x1UL << DVP_MINTSTS_FEMIS_SHIFT)
#define DVP_MINTSTS_FEMIS                   (DVP_MINTSTS_FEMIS_MASK)

#define DVP_MINTSTS_LEMIS_SHIFT             (3UL)
#define DVP_MINTSTS_LEMIS_MASK              (0x1UL << DVP_MINTSTS_LEMIS_SHIFT)
#define DVP_MINTSTS_LEMIS                   (DVP_MINTSTS_LEMIS_MASK)

#define DVP_MINTSTS_LSMIS_SHIFT             (2UL)
#define DVP_MINTSTS_LSMIS_MASK              (0x1UL << DVP_MINTSTS_LSMIS_SHIFT)
#define DVP_MINTSTS_LSMIS                   (DVP_MINTSTS_LSMIS_MASK)

#define DVP_MINTSTS_FMEMIS_SHIFT            (1UL)
#define DVP_MINTSTS_FMEMIS_MASK             (0x1UL << DVP_MINTSTS_FMEMIS_SHIFT)
#define DVP_MINTSTS_FMEMIS                  (DVP_MINTSTS_FMEMIS_MASK)

#define DVP_MINTSTS_FMSMIS_SHIFT            (0UL)
#define DVP_MINTSTS_FMSMIS_MASK             (0x1UL << DVP_MINTSTS_FMSMIS_SHIFT)
#define DVP_MINTSTS_FMSMIS                  (DVP_MINTSTS_FMSMIS_MASK)

/****************  Bit definition for DVP_WST register      ****************/
#define DVP_WST_VST_SHIFT                   (13UL)
#define DVP_WST_VST_MASK                    (0x7FFUL << DVP_WST_VST_SHIFT)
#define DVP_WST_VST                         (DVP_WST_VST_MASK)
#define DVP_WST_VST_0                       (0x001UL << DVP_WST_VST_SHIFT)
#define DVP_WST_VST_1                       (0x002UL << DVP_WST_VST_SHIFT)
#define DVP_WST_VST_2                       (0x004UL << DVP_WST_VST_SHIFT)
#define DVP_WST_VST_3                       (0x008UL << DVP_WST_VST_SHIFT)
#define DVP_WST_VST_4                       (0x010UL << DVP_WST_VST_SHIFT)
#define DVP_WST_VST_5                       (0x020UL << DVP_WST_VST_SHIFT)
#define DVP_WST_VST_6                       (0x040UL << DVP_WST_VST_SHIFT)
#define DVP_WST_VST_7                       (0x080UL << DVP_WST_VST_SHIFT)
#define DVP_WST_VST_8                       (0x100UL << DVP_WST_VST_SHIFT)
#define DVP_WST_VST_9                       (0x200UL << DVP_WST_VST_SHIFT)
#define DVP_WST_VST_10                      (0x400UL << DVP_WST_VST_SHIFT)

#define DVP_WST_HST_SHIFT                   (0UL)
#define DVP_WST_HST_MASK                    (0x7FFUL << DVP_WST_HST_SHIFT)
#define DVP_WST_HST                         (DVP_WST_HST_MASK)
#define DVP_WST_HST_0                       (0x001UL << DVP_WST_HST_SHIFT)
#define DVP_WST_HST_1                       (0x002UL << DVP_WST_HST_SHIFT)
#define DVP_WST_HST_2                       (0x004UL << DVP_WST_HST_SHIFT)
#define DVP_WST_HST_3                       (0x008UL << DVP_WST_HST_SHIFT)
#define DVP_WST_HST_4                       (0x010UL << DVP_WST_HST_SHIFT)
#define DVP_WST_HST_5                       (0x020UL << DVP_WST_HST_SHIFT)
#define DVP_WST_HST_6                       (0x040UL << DVP_WST_HST_SHIFT)
#define DVP_WST_HST_7                       (0x080UL << DVP_WST_HST_SHIFT)
#define DVP_WST_HST_8                       (0x100UL << DVP_WST_HST_SHIFT)
#define DVP_WST_HST_9                       (0x200UL << DVP_WST_HST_SHIFT)
#define DVP_WST_HST_10                      (0x400UL << DVP_WST_HST_SHIFT)

/****************  Bit definition for DVP_WSIZE register   ****************/
#define DVP_WSIZE_VLINE_SHIFT               (13UL)
#define DVP_WSIZE_VLINE_MASK                (0x7FFUL << DVP_WSIZE_VLINE_SHIFT)
#define DVP_WSIZE_VLINE                     (DVP_WSIZE_VLINE_MASK)
#define DVP_WSIZE_VLINE_0                   (0x001UL << DVP_WSIZE_VLINE_SHIFT)
#define DVP_WSIZE_VLINE_1                   (0x002UL << DVP_WSIZE_VLINE_SHIFT)
#define DVP_WSIZE_VLINE_2                   (0x004UL << DVP_WSIZE_VLINE_SHIFT)
#define DVP_WSIZE_VLINE_3                   (0x008UL << DVP_WSIZE_VLINE_SHIFT)
#define DVP_WSIZE_VLINE_4                   (0x010UL << DVP_WSIZE_VLINE_SHIFT)
#define DVP_WSIZE_VLINE_5                   (0x020UL << DVP_WSIZE_VLINE_SHIFT)
#define DVP_WSIZE_VLINE_6                   (0x040UL << DVP_WSIZE_VLINE_SHIFT)
#define DVP_WSIZE_VLINE_7                   (0x080UL << DVP_WSIZE_VLINE_SHIFT)
#define DVP_WSIZE_VLINE_8                   (0x100UL << DVP_WSIZE_VLINE_SHIFT)
#define DVP_WSIZE_VLINE_9                   (0x200UL << DVP_WSIZE_VLINE_SHIFT)
#define DVP_WSIZE_VLINE_10                  (0x400UL << DVP_WSIZE_VLINE_SHIFT)

#define DVP_WSIZE_HCNT_SHIFT                (0UL)
#define DVP_WSIZE_HCNT_MASK                 (0x7FFUL << DVP_WSIZE_HCNT_SHIFT)
#define DVP_WSIZE_HCNT                      (DVP_WSIZE_HCNT_MASK)
#define DVP_WSIZE_HCNT_0                    (0x001UL << DVP_WSIZE_HCNT_SHIFT)
#define DVP_WSIZE_HCNT_1                    (0x002UL << DVP_WSIZE_HCNT_SHIFT)
#define DVP_WSIZE_HCNT_2                    (0x004UL << DVP_WSIZE_HCNT_SHIFT)
#define DVP_WSIZE_HCNT_3                    (0x008UL << DVP_WSIZE_HCNT_SHIFT)
#define DVP_WSIZE_HCNT_4                    (0x010UL << DVP_WSIZE_HCNT_SHIFT)
#define DVP_WSIZE_HCNT_5                    (0x020UL << DVP_WSIZE_HCNT_SHIFT)
#define DVP_WSIZE_HCNT_6                    (0x040UL << DVP_WSIZE_HCNT_SHIFT)
#define DVP_WSIZE_HCNT_7                    (0x080UL << DVP_WSIZE_HCNT_SHIFT)
#define DVP_WSIZE_HCNT_8                    (0x100UL << DVP_WSIZE_HCNT_SHIFT)
#define DVP_WSIZE_HCNT_9                    (0x200UL << DVP_WSIZE_HCNT_SHIFT)
#define DVP_WSIZE_HCNT_10                   (0x400UL << DVP_WSIZE_HCNT_SHIFT)

/****************  Bit definition for DVP_FIFO register   ****************/
#define DVP_FIFO_DAT3_SHIFT                 (24UL)
#define DVP_FIFO_DAT3_MASK                  (0xFFUL << DVP_FIFO_DAT3_SHIFT)
#define DVP_FIFO_DAT3                       (DVP_FIFO_DAT3_MASK)

#define DVP_FIFO_DAT2_SHIFT                 (16UL)
#define DVP_FIFO_DAT2_MASK                  (0xFFUL << DVP_FIFO_DAT2_SHIFT)
#define DVP_FIFO_DAT2                       (DVP_FIFO_DAT2_MASK)

#define DVP_FIFO_DAT1_SHIFT                 (8UL)
#define DVP_FIFO_DAT1_MASK                  (0xFFUL << DVP_FIFO_DAT1_SHIFT)
#define DVP_FIFO_DAT1                       (DVP_FIFO_DAT1_MASK)

#define DVP_FIFO_DAT0_SHIFT                 (0UL)
#define DVP_FIFO_DAT0_MASK                  (0xFFUL << DVP_FIFO_DAT0_SHIFT)
#define DVP_FIFO_DAT0                       (DVP_FIFO_DAT0_MASK)

/**
 * @}
 */

/** @addtogroup Exported_macros
  * @{
  */

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
#include "n32wb452_conf.h"
#endif

#ifdef __cplusplus
}
#endif

#endif /* __N32WB452_H__ */
