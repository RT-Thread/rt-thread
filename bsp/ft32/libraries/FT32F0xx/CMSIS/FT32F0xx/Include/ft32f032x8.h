/**
  ******************************************************************************
  * @file               ft32f030x8.h
  * @author             FMD AE
  * @brief              CMSIS Cortex-M0 Device Peripheral Access Layer Header File.
  * @details            This file contains all the peripheral register's definitions, bits
  *                     definitions and memory mapping for FT32F030X8 devices.
  * @version            V1.0.0
  * @date               2021-07-01
  *******************************************************************************
  */

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup ft32f030x8
  * @{
  */

#ifndef __FT32F030X8_H
#define __FT32F030X8_H

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup Library_configuration_section
  * @{
  */

/* Uncomment the line below according to the target FT32F0 device used in your
   application
  */

#if !defined (FT32F030X8)
  #define FT32F030X8
#endif

/*  Tip: To avoid modifying this file each time you need to switch between these
        devices, you can define the device in your toolchain compiler preprocessor.
  */


#if !defined  USE_STDPERIPH_DRIVER
/**
 * @brief Comment the line below if you will not use the peripherals drivers.
   In this case, these drivers will not be included and the application code will
   be based on direct access to peripherals registers
   */
  /*#define USE_STDPERIPH_DRIVER*/
#endif /* USE_STDPERIPH_DRIVER */

/**
 * @brief In the following line adjust the value of External High Speed oscillator (HSE)
   used in your application

   Tip: To avoid modifying this file each time you need to use different HSE, you
        can define the HSE value in your toolchain compiler preprocessor.
  */
#if !defined  (HSE_VALUE)
#define HSE_VALUE    ((uint32_t)8000000) /*!< Value of the External oscillator in Hz*/
#endif /* HSE_VALUE */

/**
 * @brief In the following line adjust the External High Speed oscillator (HSE) Startup
   Timeout value
   */
#if !defined  (HSE_STARTUP_TIMEOUT)
#define HSE_STARTUP_TIMEOUT   ((uint16_t)0x5000) /*!< Time out for HSE start up */
#endif /* HSE_STARTUP_TIMEOUT */

/**
 * @brief In the following line adjust the Internal High Speed oscillator (HSI) Startup
   Timeout value
   */
#if !defined  (HSI_STARTUP_TIMEOUT)
#define HSI_STARTUP_TIMEOUT   ((uint16_t)0x5000) /*!< Time out for HSI start up */
#endif /* HSI_STARTUP_TIMEOUT */

#if !defined  (HSI_VALUE)
#define HSI_VALUE  ((uint32_t)8000000) /*!< Value of the Internal High Speed oscillator in Hz.
                                             The real value may vary depending on the variations
                                             in voltage and temperature.  */
#endif /* HSI_VALUE */

#if !defined  (HSI14_VALUE)
#define HSI14_VALUE ((uint32_t)14000000) /*!< Value of the Internal High Speed oscillator for ADC in Hz.
                                             The real value may vary depending on the variations
                                             in voltage and temperature.  */
#endif /* HSI14_VALUE */

#if !defined  (HSI48_VALUE)
#define HSI48_VALUE ((uint32_t)48000000) /*!< Value of the Internal High Speed oscillator for USB in Hz.
                                             The real value may vary depending on the variations
                                             in voltage and temperature.  */
#endif /* HSI48_VALUE */

#if !defined  (LSI_VALUE)
#define LSI_VALUE  ((uint32_t)40000)    /*!< Value of the Internal Low Speed oscillator in Hz
                                             The real value may vary depending on the variations
                                             in voltage and temperature.  */
#endif /* LSI_VALUE */

#if !defined  (LSE_VALUE)
#define LSE_VALUE  ((uint32_t)32768)    /*!< Value of the External Low Speed oscillator in Hz */
#endif /* LSE_VALUE */

/**
 * @brief FT32F0XX Standard Peripheral Library version number V1.0.0
   */
#define __FT32F0XX_STDPERIPH_VERSION_MAIN   (0x01) /*!< [31:24] main version */
#define __FT32F0XX_STDPERIPH_VERSION_SUB1   (0x05) /*!< [23:16] sub1 version */
#define __FT32F0XX_STDPERIPH_VERSION_SUB2   (0x00) /*!< [15:8]  sub2 version */
#define __FT32F0XX_STDPERIPH_VERSION_RC     (0x00) /*!< [7:0]  release candidate */
#define __FT32F0XX_STDPERIPH_VERSION        ((__FT32F0XX_STDPERIPH_VERSION_MAIN << 24)\
                                             |(__FT32F0XX_STDPERIPH_VERSION_SUB1 << 16)\
                                             |(__FT32F0XX_STDPERIPH_VERSION_SUB2 << 8)\
                                             |(__FT32F0XX_STDPERIPH_VERSION_RC))

/**
  * @}
  */

/** @addtogroup Configuration_section_for_CMSIS
  * @{
  */

/**
 * @brief FT32F030X8 Interrupt Number Definition, according to the selected device
 *        in @ref Library_configuration_section
 */
#define __CM0_REV                 0 /*!< Core Revision r0p0                            */
#define __MPU_PRESENT             0 /*!< FT32F030X8 do not provide MPU                  */
#define __NVIC_PRIO_BITS          2 /*!< FT32F030X8 uses 2 Bits for the Priority Levels */
#define __Vendor_SysTickConfig    0 /*!< Set to 1 if different SysTick Config is used  */

/*!< Interrupt Number Definition */
typedef enum IRQn
{
/******  Cortex-M0 Processor Exceptions Numbers ******************************************************/
  NonMaskableInt_IRQn         = -14,    /*!< 2 Non Maskable Interrupt                                */
  HardFault_IRQn              = -13,    /*!< 3 Cortex-M0 Hard Fault Interrupt                        */
  SVC_IRQn                    = -5,     /*!< 11 Cortex-M0 SV Call Interrupt                          */
  PendSV_IRQn                 = -2,     /*!< 14 Cortex-M0 Pend SV Interrupt                          */
  SysTick_IRQn                = -1,     /*!< 15 Cortex-M0 System Tick Interrupt                      */

/******  FT32F0 specific Interrupt Numbers ******************************************************************/
  WWDG_IRQn                   = 0,      /*!< Window WatchDog Interrupt                                     */
  PVD_VDDIO2_IRQn             = 1,      /*!< PVD and VDDIO2 supply comparator through EXTI Line detect Interrupt */
  RTC_IRQn                    = 2,      /*!< RTC through EXTI Line Interrupt                               */
  FLASH_IRQn                  = 3,      /*!< FLASH Interrupt                                               */
  RCC_CRS_IRQn                = 4,      /*!< RCC and CRS Interrupts                                        */
  EXTI0_1_IRQn                = 5,      /*!< EXTI Line 0 and 1 Interrupts                                  */
  EXTI2_3_IRQn                = 6,      /*!< EXTI Line 2 and 3 Interrupts                                  */
  EXTI4_15_IRQn               = 7,      /*!< EXTI Line 4 to 15 Interrupts                                  */
  DMA1_Channel1_IRQn          = 9,      /*!< DMA1 Channel 1 Interrupt                                      */
  DMA1_Channel2_3_IRQn        = 10,     /*!< DMA1 Channel 2 and Channel 3 Interrupts                       */
  DMA1_Channel4_5_IRQn        = 11,     /*!< DMA1 Channel 4, Channel 5, Channel 6 and Channel 7 Interrupts */
  ADC1_COMP_IRQn              = 12,     /*!< ADC1, COMP1 and COMP2 Interrupts                              */
  TIM1_BRK_UP_TRG_COM_IRQn    = 13,     /*!< TIM1 Break, Update, Trigger and Commutation Interrupts        */
  TIM1_CC_IRQn                = 14,     /*!< TIM1 Capture Compare Interrupt                                */
  TIM3_IRQn                   = 16,     /*!< TIM3 Interrupt                                                */
  TIM6_DAC_IRQn               = 17,     /*!< TIM6 and DAC Interrupts                                       */
  TIM14_IRQn                  = 19,     /*!< TIM14 Interrupt                                               */
  TIM15_IRQn                  = 20,     /*!< TIM15 Interrupt                                               */
  TIM16_IRQn                  = 21,     /*!< TIM16 Interrupt                                               */
  TIM17_IRQn                  = 22,     /*!< TIM17 Interrupt                                               */
  I2C1_IRQn                   = 23,     /*!< I2C1 Interrupt                                                */
  I2C2_IRQn                   = 24,     /*!< I2C2 Interrupt                                                */
  SPI1_IRQn                   = 25,     /*!< SPI1 Interrupt                                                */
  SPI2_IRQn                   = 26,     /*!< SPI2 Interrupt                                                */
  USART1_IRQn                 = 27,     /*!< USART1 Interrupt                                              */
  USART2_IRQn                 = 28,     /*!< USART2 Interrupt                                              */
  USB_IRQn                    = 31      /*!< USB Low Priority global Interrupt                             */
}IRQn_Type;

/**
  * @}
  */

#include "core_cm0.h"
#include "ft32f0xx.h"
#include "system_ft32f0xx.h"
#include <stdint.h>

/** @addtogroup Exported_types
  * @{
  */

typedef enum
{
  RESET = 0,
  SET = !RESET
} FlagStatus, ITStatus;

typedef enum
{
  DISABLE = 0,
  ENABLE = !DISABLE
} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

typedef enum
{
  ERROR = 0,
  SUCCESS = !ERROR
} ErrorStatus;

/**
  * @brief Analog to Digital Converter
  */

typedef struct
{
  __IO uint32_t ISR;          /*!< ADC Interrupt and Status register,                          Address offset:0x00 */
  __IO uint32_t IER;          /*!< ADC Interrupt Enable register,                              Address offset:0x04 */
  __IO uint32_t CR;           /*!< ADC Control register,                                       Address offset:0x08 */
  __IO uint32_t CFGR1;        /*!< ADC Configuration register 1,                               Address offset:0x0C */
  __IO uint32_t CFGR2;        /*!< ADC Configuration register 2,                               Address offset:0x10 */
  __IO uint32_t SMPR;         /*!< ADC Sampling time register,                                 Address offset:0x14 */
  uint32_t   RESERVED1;       /*!< Reserved,                                                                  0x18 */
  uint32_t   RESERVED2;       /*!< Reserved,                                                                  0x1C */
  __IO uint32_t TR;           /*!< ADC watchdog threshold register,                            Address offset:0x20 */
  uint32_t   RESERVED3;       /*!< Reserved,                                                                  0x24 */
  __IO uint32_t CHSELR;       /*!< ADC channel selection register,                             Address offset:0x28 */
  uint32_t   RESERVED4[5];    /*!< Reserved,                                                                  0x2C */
   __IO uint32_t DR;          /*!< ADC data register,                                          Address offset:0x40 */
} ADC_TypeDef;

typedef struct
{
  __IO uint32_t CCR;                    /*Address offset:0x308 */
  __IO uint32_t CR2;                    /*Address offset:0x30C */
} ADC_Common_TypeDef;

/**
  * @brief Comparator
  */

typedef struct
{
    __IO uint32_t RESERVED[7];     /*!< Reserved,                               Address offset: 0x18-0x00 */
  __IO uint32_t CSR;                     /*!< COMP comparator control and status register, Address offset: 0x1C */
} COMP_TypeDef;

/**
  * @brief OPA
  */
typedef struct
{
    __IO uint32_t RESERVED[12];     /*!< Reserved,                               Address offset: 0x2C-0x00 */
  __IO uint32_t CR;                  /*!< COMP comparator control and status register, Address offset: 0x30 */
} OPA_TypeDef;

/**
  * @brief DAC Configuration
  */
typedef struct
{
    __IO uint32_t RESERVED[8];    /*!< Reserved,                                          Address offset: 0x1C-0x00 */
  __IO uint32_t CTRL;           /*!< DAC configuration register                              Address offset: 0x20 */
  __IO uint32_t DATA1;          /*!< DAC1 Input  data                                        Address offset: 0x24 */
  __IO uint32_t DATA2;          /*!< DAC2 Input  data                                        Address offset: 0x28 */
}DAC_TypeDef;

/**
  * @brief CRC calculation unit
  */

typedef struct
{
  __IO uint32_t DR;          /*!< CRC Data register,                           Address offset: 0x00 */
    __IO uint32_t IDR;         /*!< CRC Independent data register,               Address offset: 0x04 */
  __IO uint32_t CR;          /*!< CRC Control register,                        Address offset: 0x08 */
  uint32_t      RESERVED2;   /*!< Reserved,                                                    0x0C */
  __IO uint32_t INIT;        /*!< Initial CRC value register,                  Address offset: 0x10 */
  __IO uint32_t RESERVED3;   /*!< Reserved,                                                    0x14 */
} CRC_TypeDef;

/**
  * @brief Clock Recovery System
  */
typedef struct
{
__IO uint32_t CR;     /*!< CRS ccontrol register,              Address offset: 0x00 */
__IO uint32_t CFGR;   /*!< CRS configuration register,         Address offset: 0x04 */
__IO uint32_t ISR;    /*!< CRS interrupt and status register,  Address offset: 0x08 */
__IO uint32_t ICR;    /*!< CRS interrupt flag clear register,  Address offset: 0x0C */
} CRS_TypeDef;

/**
  * @brief Debug MCU
  */

typedef struct
{
  __IO uint32_t IDCODE;       /*!< MCU device ID code,                          Address offset: 0x00 */
  __IO uint32_t CR;           /*!< Debug MCU configuration register,            Address offset: 0x04 */
  __IO uint32_t APB1FZ;       /*!< Debug MCU APB1 freeze register,              Address offset: 0x08 */
  __IO uint32_t APB2FZ;       /*!< Debug MCU APB2 freeze register,              Address offset: 0x0C */
}DBGMCU_TypeDef;

/**
  * @brief DMA Controller
  */

typedef struct
{
  __IO uint32_t CCR;          /*!< DMA channel x configuration register                                           */
  __IO uint32_t CNDTR;        /*!< DMA channel x number of data register                                          */
  __IO uint32_t CPAR;         /*!< DMA channel x peripheral address register                                      */
  __IO uint32_t CMAR;         /*!< DMA channel x memory address register                                          */
} DMA_Channel_TypeDef;

typedef struct
{
  __IO uint32_t ISR;          /*!< DMA interrupt status register,                            Address offset: 0x00 */
  __IO uint32_t IFCR;         /*!< DMA interrupt flag clear register,                        Address offset: 0x04 */
}DMA_TypeDef;

/**
  * @brief External Interrupt/Event Controller
  */

typedef struct
{
  __IO uint32_t IMR;          /*!<EXTI Interrupt mask register,                             Address offset: 0x00 */
  __IO uint32_t EMR;          /*!<EXTI Event mask register,                                 Address offset: 0x04 */
  __IO uint32_t RTSR;         /*!<EXTI Rising trigger selection register ,                  Address offset: 0x08 */
  __IO uint32_t FTSR;         /*!<EXTI Falling trigger selection register,                  Address offset: 0x0C */
  __IO uint32_t SWIER;        /*!<EXTI Software interrupt event register,                   Address offset: 0x10 */
  __IO uint32_t PR;           /*!<EXTI Pending register,                                    Address offset: 0x14 */
}EXTI_TypeDef;

/**
  * @brief FLASH Registers
  */
typedef struct
{
  __IO uint32_t ACR;          /*!<FLASH access control register,                 Address offset: 0x00 */
  __IO uint32_t KEYR;         /*!<FLASH key register,                            Address offset: 0x04 */
  __IO uint32_t OPTKEYR;      /*!<FLASH OPT key register,                        Address offset: 0x08 */
  __IO uint32_t SR;           /*!<FLASH status register,                         Address offset: 0x0C */
  __IO uint32_t CR;           /*!<FLASH control register,                        Address offset: 0x10 */
  __IO uint32_t AR;           /*!<FLASH address register,                        Address offset: 0x14 */
  __IO uint32_t RESERVED;     /*!< Reserved,                                                     0x18 */
  __IO uint32_t OBR;          /*!<FLASH option bytes register,                   Address offset: 0x1C */
  __IO uint32_t WRPR;         /*!<FLASH option bytes register,                   Address offset: 0x20 */
} FLASH_TypeDef;


/**
  * @brief Option Bytes Registers
  */
typedef struct
{
  __IO uint32_t USER_RDP;          /*!< FLASH option byte Read protection,             Address offset: 0x00-0x03 */
  __IO uint32_t DATA1_DATA0;       /*!< User data byte 0 (stored in FLASH_OBR[23:16]), Address offset: 0x04-0x07 */
  __IO uint32_t WRP1_WRP0;         /*!< FLASH option byte write protection 0,1         Address offset: 0x08-0x0b */
  __IO uint32_t WRP3_WRP2;         /*!< FLASH option byte write protection 2,          Address offset: 0x0C-0x0f */
} OB_TypeDef;


/**
  * @brief General Purpose IO
  */

typedef struct
{
  __IO uint32_t MODER;        /*!< GPIO port mode register,                                  Address offset: 0x00 */
  __IO uint16_t OTYPER;       /*!< GPIO port output type register,                           Address offset: 0x04 */
  uint16_t RESERVED0;         /*!< Reserved,                                                                 0x06 */
  __IO uint32_t OSPEEDR;      /*!< GPIO port output speed register,                          Address offset: 0x08 */
  __IO uint32_t PUPDR;        /*!< GPIO port pull-up/pull-down register,                     Address offset: 0x0C */
  __IO uint16_t IDR;          /*!< GPIO port input data register,                            Address offset: 0x10 */
  uint16_t RESERVED1;         /*!< Reserved,                                                                 0x12 */
  __IO uint16_t ODR;          /*!< GPIO port output data register,                           Address offset: 0x14 */
  uint16_t RESERVED2;         /*!< Reserved,                                                                 0x16 */
  __IO uint32_t BSRR;         /*!< GPIO port bit set/reset registerBSRR,                     Address offset: 0x18 */
  __IO uint32_t LCKR;         /*!< GPIO port configuration lock register,                    Address offset: 0x1C */
  __IO uint32_t AFR[2];       /*!< GPIO alternate function low register,                Address offset: 0x20-0x24 */
  __IO uint16_t BRR;          /*!< GPIO bit reset register,                                  Address offset: 0x28 */
  uint32_t RESERVED3;         /*!< Reserved,                                                                 0x2C */
  __IO uint32_t LEDM;         /*!< GPIO LEDM register,                                       Address offset: 0x30 */
}GPIO_TypeDef;

/**
  * @brief SysTem Configuration
  */

typedef struct
{
  __IO uint32_t CFGR1;          /*!< SYSCFG configuration register 1,                        Address offset: 0x00 */
       uint32_t RESERVED;       /*!< Reserved,                                                               0x04 */
  __IO uint32_t EXTICR[4];      /*!< SYSCFG external interrupt configuration register,  Address offset: 0x14-0x08 */
  __IO uint32_t CFGR2;          /*!< SYSCFG configuration register 2,                        Address offset: 0x18 */
}SYSCFG_TypeDef;

/**
  * @brief Inter-integrated Circuit Interface
  */

typedef struct
{
  __IO uint32_t CR1;      /*!< I2C Control register 1,            Address offset: 0x00 */
  __IO uint32_t CR2;      /*!< I2C Control register 2,            Address offset: 0x04 */
  __IO uint32_t OAR1;     /*!< I2C Own address 1 register,        Address offset: 0x08 */
  __IO uint32_t OAR2;     /*!< I2C Own address 2 register,        Address offset: 0x0C */
  __IO uint32_t TIMINGR;  /*!< I2C Timing register,               Address offset: 0x10 */
  __IO uint32_t TIMEOUTR; /*!< I2C Timeout register,              Address offset: 0x14 */
  __IO uint32_t ISR;      /*!< I2C Interrupt and status register, Address offset: 0x18 */
  __IO uint32_t ICR;      /*!< I2C Interrupt clear register,      Address offset: 0x1C */
  __IO uint32_t PECR;     /*!< I2C PEC register,                  Address offset: 0x20 */
  __IO uint32_t RXDR;     /*!< I2C Receive data register,         Address offset: 0x24 */
  __IO uint32_t TXDR;     /*!< I2C Transmit data register,        Address offset: 0x28 */
}I2C_TypeDef;


/**
  * @brief Independent WATCHDOG
  */
typedef struct
{
  __IO uint32_t KR;   /*!< IWDG Key register,       Address offset: 0x00 */
  __IO uint32_t PR;   /*!< IWDG Prescaler register, Address offset: 0x04 */
  __IO uint32_t RLR;  /*!< IWDG Reload register,    Address offset: 0x08 */
  __IO uint32_t SR;   /*!< IWDG Status register,    Address offset: 0x0C */
  __IO uint32_t WINR; /*!< IWDG Window register,    Address offset: 0x10 */
} IWDG_TypeDef;

/**
  * @brief USB
  */
typedef struct
{
    __IO uint8_t FADDR;      /*!<  function address register,                            Address offset: 0x00 */
    __IO uint8_t POWER;      /*!<  power management register,                            Address offset: 0x01 */
    __IO uint8_t INTRIN;     /*!<  interrupt register endpint0 plus IN Endpoit 1 to 7,   Address offset: 0x02 */
    __IO uint8_t RES1;       /*!<  RES1                                                  Address offset: 0x03 */
    __IO uint8_t INTROUT;    /*!<  interrupt register for OUT Endpoints 1 to 7,          Address offset: 0x04 */
    __IO uint8_t RES2;       /*!<  RES2                                                  Address offset: 0x05 */
    __IO uint8_t INTRUSB;    /*!<  interrupt register for common USB interrrupts,        Address offset: 0x06 */
    __IO uint8_t INTRINE;    /*!<  inerrupt enable register for INTRIN,                  Address offset: 0x07 */
    __IO uint8_t RES3;       /*!<  RES3                                                  Address offset: 0x08 */
    __IO uint8_t INTROUTE;   /*!<  inerrupt enable register for INTROUT,                 Address offset: 0x09 */
    __IO uint8_t RES4;       /*!<  RES4                                                  Address offset: 0x0A */
    __IO uint8_t INTRUSBE;   /*!<  inerrupt enable register for INTRUSB,                 Address offset: 0x0B */
    __IO uint8_t FRAM1;      /*!<  frame number bits 0 to 7,                             Address offset: 0x0C */
    __IO uint8_t FRAM2;      /*!<  frame number bits 8 to 15,                            Address offset: 0x0D */
    __IO uint8_t INDEX;      /*!<  selecting then endpoint status and control register , Address offset: 0x0E */
    __IO uint8_t PDCTRL;     /*!<  pull down pull up control ,                           Address offset: 0x0F */
    __IO uint8_t INMAXP;     /*!<  Maximum packet size for IN endpoint,                  Address offset: 0x10 */
    union
    {
        __IO uint8_t INCSR0; /*!<  control status register fie endpoint 0,               Address offset: 0x11 */
        __IO uint8_t INCSR1; /*!<  Control Status register 1 for IN Endpoint,            Address offset: 0x11 */
    }INCSR;
    __IO uint8_t INCSR2;     /*!<  Control Status register 2 for IN Endpoint,            Address offset: 0x12 */
    //__IO uint8_t RES;        /*!<  Control Status register 2 for IN Endpoint,            Address offset: 0x12 */
    __IO uint8_t OUTMAXP;    /*!<  Maximum packet size for OUT endpoint,                 Address offset: 0x13 */
    __IO uint8_t OUTCSR1;    /*!<  Control Status register 1 for OUT Endpoint,           Address offset: 0x14 */
    __IO uint8_t OUTCSR2;    /*!<  Control Status register 2 for OUT Endpoint,           Address offset: 0x15 */
    __IO uint8_t OUTCOUNTER; /*!<  number of bytes in OUT endpoint FIFO ,                Address offset: 0x16 */
    __IO uint8_t RES5;       /*!<  RES5                                                  Address offset: 0x17 */
    __IO uint8_t RES6;       /*!<  RES6                                                  Address offset: 0x18 */
    __IO uint8_t RES7;       /*!<  RES7                                                  Address offset: 0x19 */
    __IO uint8_t FIFO0;      /*!<  FIFO for Endpoint 0,                                  Address offset: 0x20 */
    __IO uint8_t RES8;       /*!<  RES8                                                  Address offset: 0x21 */
    __IO uint8_t RES9;       /*!<  RES9                                                  Address offset: 0x22 */
    __IO uint8_t RES10;      /*!<  RES10                                                 Address offset: 0x23 */
    __IO uint8_t FIFO1;      /*!<  FIFO for Endpoint 1,                                  Address offset: 0x24 */
    __IO uint8_t RES11;      /*!<  RES11                                                 Address offset: 0x25 */
    __IO uint8_t RES12;      /*!<  RES12                                                 Address offset: 0x26 */
    __IO uint8_t RES13;      /*!<  RES13                                                 Address offset: 0x27 */
    __IO uint8_t FIFO2;      /*!<  FIFO for Endpoint 2,                                  Address offset: 0x28 */
    __IO uint8_t RES14;      /*!<  RES14                                                 Address offset: 0x29 */
    __IO uint8_t RES15;      /*!<  RES15                                                 Address offset: 0x2A */
    __IO uint8_t RES16;      /*!<  RES16                                                 Address offset: 0x2B */
    __IO uint8_t FIFO3;      /*!<  FIFO for Endpoint 3,                                  Address offset: 0x2C */
    __IO uint8_t RES17;      /*!<  RES17                                                 Address offset: 0x2D */
    __IO uint8_t RES18;      /*!<  RES18                                                 Address offset: 0x2E */
    __IO uint8_t RES19;      /*!<  RES19                                                 Address offset: 0x2F */
    __IO uint8_t FIFO4;      /*!<  FIFO for Endpoint 4,                                  Address offset: 0x30 */
    __IO uint8_t RES20;      /*!<  RES20                                                 Address offset: 0x31 */
    __IO uint8_t RES21;      /*!<  RES21                                                 Address offset: 0x32 */
    __IO uint8_t RES22;      /*!<  RES22                                                 Address offset: 0x33 */
    __IO uint8_t FIFO5;      /*!<  FIFO for Endpoint 5,                                  Address offset: 0x34 */
    __IO uint8_t RES23;      /*!<  RES23                                                 Address offset: 0x35 */
    __IO uint8_t RES24;      /*!<  RES24                                                 Address offset: 0x36 */
    __IO uint8_t RES25;      /*!<  RES25                                                 Address offset: 0x37 */
    __IO uint8_t FIFO6;      /*!<  FIFO for Endpoint 6,                                  Address offset: 0x38 */
    __IO uint8_t RES26;      /*!<  RES26                                                 Address offset: 0x39 */
    __IO uint8_t RES27;      /*!<  RES27                                                 Address offset: 0x3A */
    __IO uint8_t RES28;      /*!<  RES28                                                 Address offset: 0x3B */
    __IO uint8_t FIFO7;      /*!<  FIFO for Endpoint 7,                                  Address offset: 0x3C */
}USB_TypeDef;

/**
  * @brief Power Control
  */

typedef struct
{
  __IO uint32_t CR;   /*!< PWR power control register,        Address offset: 0x00 */
  __IO uint32_t CSR;  /*!< PWR power control/status register, Address offset: 0x04 */
} PWR_TypeDef;


/**
  * @brief Reset and Clock Control
  */
typedef struct
{
  __IO uint32_t CR;         /*!< RCC clock control register,                                  Address offset: 0x00 */
  __IO uint32_t CFGR;       /*!< RCC clock configuration register,                            Address offset: 0x04 */
  __IO uint32_t CIR;        /*!< RCC clock interrupt register,                                Address offset: 0x08 */
  __IO uint32_t APB2RSTR;   /*!< RCC APB2 peripheral reset register,                          Address offset: 0x0C */
  __IO uint32_t APB1RSTR;   /*!< RCC APB1 peripheral reset register,                          Address offset: 0x10 */
  __IO uint32_t AHBENR;     /*!< RCC AHB peripheral clock register,                           Address offset: 0x14 */
  __IO uint32_t APB2ENR;    /*!< RCC APB2 peripheral clock enable register,                   Address offset: 0x18 */
  __IO uint32_t APB1ENR;    /*!< RCC APB1 peripheral clock enable register,                   Address offset: 0x1C */
  __IO uint32_t BDCR;       /*!< RCC Backup domain control register,                          Address offset: 0x20 */
  __IO uint32_t CSR;        /*!< RCC clock control & status register,                         Address offset: 0x24 */
  __IO uint32_t AHBRSTR;    /*!< RCC AHB peripheral reset register,                           Address offset: 0x28 */
  __IO uint32_t CFGR2;      /*!< RCC clock configuration register 2,                          Address offset: 0x2C */
  __IO uint32_t CFGR3;      /*!< RCC clock configuration register 3,                          Address offset: 0x30 */
  __IO uint32_t CR2;        /*!< RCC clock control register 2,                                Address offset: 0x34 */
  __IO uint32_t HSECFG;      /*!< RCC clock configuration register 2,                         Address offset: 0x38 New*/
  __IO uint32_t CFGR4;      /*!< RCC clock configuration register 3,                          Address offset: 0x3C New*/
  __IO uint32_t TRIM;        /*!< RCC clock control register 2,                               Address offset: 0x40 New*/
} RCC_TypeDef;

/**
  * @brief Real-Time Clock
  */

typedef struct
{
  __IO uint32_t TR;         /*!< RTC time register,                                         Address offset: 0x00 */
  __IO uint32_t DR;         /*!< RTC date register,                                         Address offset: 0x04 */
  __IO uint32_t CR;         /*!< RTC control register,                                      Address offset: 0x08 */
  __IO uint32_t ISR;        /*!< RTC initialization and status register,                    Address offset: 0x0C */
  __IO uint32_t PRER;       /*!< RTC prescaler register,                                    Address offset: 0x10 */
       uint32_t RESERVED1;  /*!< Reserved,                                                  Address offset: 0x14 */
       uint32_t RESERVED2;  /*!< Reserved,                                                  Address offset: 0x18 */
  __IO uint32_t ALRMAR;     /*!< RTC alarm A register,                                      Address offset: 0x1C */
       uint32_t RESERVED3;  /*!< Reserved,                                                  Address offset: 0x20 */
  __IO uint32_t WPR;        /*!< RTC write protection register,                             Address offset: 0x24 */
  __IO uint32_t SSR;        /*!< RTC sub second register,                                   Address offset: 0x28 */
  __IO uint32_t SHIFTR;     /*!< RTC shift control register,                                Address offset: 0x2C */
  __IO uint32_t TSTR;       /*!< RTC time stamp time register,                              Address offset: 0x30 */
  __IO uint32_t TSDR;       /*!< RTC time stamp date register,                              Address offset: 0x34 */
  __IO uint32_t TSSSR;      /*!< RTC time-stamp sub second register,                        Address offset: 0x38 */
  __IO uint32_t CALR;       /*!< RTC calibration register,                                  Address offset: 0x3C */
  __IO uint32_t TAFCR;      /*!< RTC tamper and alternate function configuration register,  Address offset: 0x40 */
  __IO uint32_t ALRMASSR;   /*!< RTC alarm A sub second register,                           Address offset: 0x44 */
} RTC_TypeDef;

/* Old register name definition maintained for legacy purpose */
#define CAL   CALR

/**
  * @brief Serial Peripheral Interface
  */

typedef struct
{
  __IO uint16_t CR1;      /*!< SPI Control register 1 (not used in I2S mode),       Address offset: 0x00 */
  uint16_t  RESERVED0;    /*!< Reserved, 0x02                                                            */
  __IO uint16_t CR2;      /*!< SPI Control register 2,                              Address offset: 0x04 */
  uint16_t  RESERVED1;    /*!< Reserved, 0x06                                                            */
  __IO uint16_t SR;       /*!< SPI Status register,                                 Address offset: 0x08 */
  uint16_t  RESERVED2;    /*!< Reserved, 0x0A                                                            */
  __IO uint16_t DR;       /*!< SPI data register,                                   Address offset: 0x0C */
  uint16_t  RESERVED3;    /*!< Reserved, 0x0E                                                            */
  __IO uint16_t CRCPR;    /*!< SPI CRC polynomial register (not used in I2S mode),  Address offset: 0x10 */
  uint16_t  RESERVED4;    /*!< Reserved, 0x12                                                            */
  __IO uint16_t RXCRCR;   /*!< SPI Rx CRC register (not used in I2S mode),          Address offset: 0x14 */
  uint16_t  RESERVED5;    /*!< Reserved, 0x16                                                            */
  __IO uint16_t TXCRCR;   /*!< SPI Tx CRC register (not used in I2S mode),          Address offset: 0x18 */
  uint16_t  RESERVED6;    /*!< Reserved, 0x1A                                                            */
 // __IO uint16_t I2SCFGR;  /*!< SPI_I2S configuration register,                      Address offset: 0x1C */
 // uint16_t  RESERVED7;    /*!< Reserved, 0x1E                                                            */
 // __IO uint16_t I2SPR;    /*!< SPI_I2S prescaler register,                          Address offset: 0x20 */
  //uint16_t  RESERVED8;    /*!< Reserved, 0x22                                                            */
} SPI_TypeDef;


/**
  * @brief TIM
  */
typedef struct
{
  __IO uint16_t CR1;             /*!< TIM control register 1,                      Address offset: 0x00 */
  uint16_t      RESERVED0;       /*!< Reserved,                                                    0x02 */
  __IO uint16_t CR2;             /*!< TIM control register 2,                      Address offset: 0x04 */
  uint16_t      RESERVED1;       /*!< Reserved,                                                    0x06 */
  __IO uint16_t SMCR;            /*!< TIM slave Mode Control register,             Address offset: 0x08 */
  uint16_t      RESERVED2;       /*!< Reserved,                                                    0x0A */
  __IO uint16_t DIER;            /*!< TIM DMA/interrupt enable register,           Address offset: 0x0C */
  uint16_t      RESERVED3;       /*!< Reserved,                                                    0x0E */
  __IO uint16_t SR;              /*!< TIM status register,                         Address offset: 0x10 */
  uint16_t      RESERVED4;       /*!< Reserved,                                                    0x12 */
  __IO uint16_t EGR;             /*!< TIM event generation register,               Address offset: 0x14 */
  uint16_t      RESERVED5;       /*!< Reserved,                                                    0x16 */
  __IO uint16_t CCMR1;           /*!< TIM  capture/compare mode register 1,        Address offset: 0x18 */
  uint16_t      RESERVED6;       /*!< Reserved,                                                    0x1A */
  __IO uint16_t CCMR2;           /*!< TIM  capture/compare mode register 2,        Address offset: 0x1C */
  uint16_t      RESERVED7;       /*!< Reserved,                                                    0x1E */
  __IO uint16_t CCER;            /*!< TIM capture/compare enable register,         Address offset: 0x20 */
  uint16_t      RESERVED8;       /*!< Reserved,                                                    0x22 */
  __IO uint32_t CNT;             /*!< TIM counter register,                        Address offset: 0x24 */
  __IO uint16_t PSC;             /*!< TIM prescaler register,                      Address offset: 0x28 */
  uint16_t      RESERVED10;      /*!< Reserved,                                                    0x2A */
  __IO uint32_t ARR;             /*!< TIM auto-reload register,                    Address offset: 0x2C */
  __IO uint16_t RCR;             /*!< TIM  repetition counter register,            Address offset: 0x30 */
  uint16_t      RESERVED12;      /*!< Reserved,                                                    0x32 */
  __IO uint32_t CCR1;            /*!< TIM capture/compare register 1,              Address offset: 0x34 */
  __IO uint32_t CCR2;            /*!< TIM capture/compare register 2,              Address offset: 0x38 */
  __IO uint32_t CCR3;            /*!< TIM capture/compare register 3,              Address offset: 0x3C */
  __IO uint32_t CCR4;            /*!< TIM capture/compare register 4,              Address offset: 0x40 */
  __IO uint16_t BDTR;            /*!< TIM break and dead-time register,            Address offset: 0x44 */
  uint16_t      RESERVED17;      /*!< Reserved,                                                    0x26 */
  __IO uint16_t DCR;             /*!< TIM DMA control register,                    Address offset: 0x48 */
  uint16_t      RESERVED18;      /*!< Reserved,                                                    0x4A */
  __IO uint16_t DMAR;            /*!< TIM DMA address for full transfer register,  Address offset: 0x4C */
  uint16_t      RESERVED19;      /*!< Reserved,                                                    0x4E */
  __IO uint16_t OR;              /*!< TIM option register,                         Address offset: 0x50 */
  uint16_t      RESERVED20;      /*!< Reserved,                                                    0x52 */
} TIM_TypeDef;

/**
  * @brief TSC
  */

typedef struct
{
  __IO uint32_t CR;          /*!< TSC configer register                          Address offset: 0x00 */
  __IO uint32_t CFGR;        /*!< TSC configuration register,                    Address offset: 0x04 */
}TSC_TypeDef;

/**
  * @brief Universal Synchronous Asynchronous Receiver Transmitter
  */

typedef struct
{
  __IO uint32_t CR1;    /*!< USART Control register 1,                 Address offset: 0x00 */
  __IO uint32_t CR2;    /*!< USART Control register 2,                 Address offset: 0x04 */
  __IO uint32_t CR3;    /*!< USART Control register 3,                 Address offset: 0x08 */
  __IO uint16_t BRR;    /*!< USART Baud rate register,                 Address offset: 0x0C */
  //uint16_t  RESERVED1;  /*!< Reserved, 0x0E                                                 */
  //__IO uint16_t GTPR;   /*!< USART Guard time and prescaler register,  Address offset: 0x10 */
  //uint16_t  RESERVED2;  /*!< Reserved, 0x12                                                 */
  uint32_t  RESERVED2;  /*!< Reserved, 0x12                                                 */
  __IO uint32_t RTOR;   /*!< USART Receiver Time Out register,         Address offset: 0x14 */
  __IO uint16_t RQR;    /*!< USART Request register,                   Address offset: 0x18 */
  uint16_t  RESERVED3;  /*!< Reserved, 0x1A                                                 */
  __IO uint32_t ISR;    /*!< USART Interrupt and status register,      Address offset: 0x1C */
  __IO uint32_t ICR;    /*!< USART Interrupt flag Clear register,      Address offset: 0x20 */
  __IO uint16_t RDR;    /*!< USART Receive Data register,              Address offset: 0x24 */
  uint16_t  RESERVED4;  /*!< Reserved, 0x26                                                 */
  __IO uint16_t TDR;    /*!< USART Transmit Data register,             Address offset: 0x28 */
  uint16_t  RESERVED5;  /*!< Reserved, 0x2A                                                 */
} USART_TypeDef;


/**
  * @brief Window WATCHDOG
  */
typedef struct
{
  __IO uint32_t CR;   /*!< WWDG Control register,       Address offset: 0x00 */
  __IO uint32_t CFR;  /*!< WWDG Configuration register, Address offset: 0x04 */
  __IO uint32_t SR;   /*!< WWDG Status register,        Address offset: 0x08 */
} WWDG_TypeDef;

typedef struct
{
    __IO uint32_t RESERVED[12];   /*!< Reserved,                                          Address offset: 0x2C-0x00 */
  __IO uint32_t CR;             /*!< OP0 configuration register                              Address offset: 0x30 */
}OP0_TypeDef;

/**
  * @}
  */

/** @addtogroup Peripheral_memory_map
  * @{
  */

#define FLASH_BASE            ((uint32_t)0x08000000) /*!< FLASH base address in the alias region */
#define SRAM_BASE             ((uint32_t)0x20000000) /*!< SRAM base address in the alias region */
#define PERIPH_BASE           ((uint32_t)0x40000000) /*!< Peripheral base address in the alias region */

/*!< Peripheral memory map */
#define APBPERIPH_BASE        PERIPH_BASE
#define AHBPERIPH_BASE        (PERIPH_BASE + 0x00020000)
#define AHB2PERIPH_BASE       (PERIPH_BASE + 0x08000000)

#define TIM2_BASE             (APBPERIPH_BASE + 0x00000000)
#define TIM3_BASE             (APBPERIPH_BASE + 0x00000400)
#define TIM6_BASE             (APBPERIPH_BASE + 0x00001000)
//#define TIM7_BASE             (APBPERIPH_BASE + 0x00001400)
#define TIM14_BASE            (APBPERIPH_BASE + 0x00002000)
#define RTC_BASE              (APBPERIPH_BASE + 0x00002800)
#define WWDG_BASE             (APBPERIPH_BASE + 0x00002C00)
#define IWDG_BASE             (APBPERIPH_BASE + 0x00003000)
#define SPI2_BASE             (APBPERIPH_BASE + 0x00003800)
#define USART2_BASE           (APBPERIPH_BASE + 0x00004400)
#define I2C1_BASE             (APBPERIPH_BASE + 0x00005400)
#define I2C2_BASE             (APBPERIPH_BASE + 0x00005800)
#define USB_BASE              (APBPERIPH_BASE + 0x00005C00)
#define CRS_BASE              (APBPERIPH_BASE + 0x00006C00)
#define PWR_BASE              (APBPERIPH_BASE + 0x00007000)

#define SYSCFG_BASE           (APBPERIPH_BASE + 0x00010000)
#define COMP_BASE             (APBPERIPH_BASE + 0x00010000)
#define DAC_BASE              (APBPERIPH_BASE + 0x00010000)
#define OPA_BASE              (APBPERIPH_BASE + 0x00010000)

#define OP0_BASE              (APBPERIPH_BASE + 0x00010000)

#define EXTI_BASE             (APBPERIPH_BASE + 0x00010400)
#define ADC1_BASE             (APBPERIPH_BASE + 0x00012400) /* KVL: TBC*/
#define ADC_BASE              (APBPERIPH_BASE + 0x00012708) /* KVL: TBC*/
#define TIM1_BASE             (APBPERIPH_BASE + 0x00012C00)
#define SPI1_BASE             (APBPERIPH_BASE + 0x00013000)
#define USART1_BASE           (APBPERIPH_BASE + 0x00013800)
#define TIM15_BASE            (APBPERIPH_BASE + 0x00014000)
#define TIM16_BASE            (APBPERIPH_BASE + 0x00014400)
#define TIM17_BASE            (APBPERIPH_BASE + 0x00014800)
#define DBGMCU_BASE           (APBPERIPH_BASE + 0x00015800)

#define DMA1_BASE             (AHBPERIPH_BASE + 0x00000000)
#define DMA1_Channel1_BASE    (DMA1_BASE + 0x00000008)
#define DMA1_Channel2_BASE    (DMA1_BASE + 0x0000001C)
#define DMA1_Channel3_BASE    (DMA1_BASE + 0x00000030)
#define DMA1_Channel4_BASE    (DMA1_BASE + 0x00000044)
#define DMA1_Channel5_BASE    (DMA1_BASE + 0x00000058)
#define DMA1_Channel6_BASE    (DMA1_BASE + 0x0000006C)
#define DMA1_Channel7_BASE    (DMA1_BASE + 0x00000080)

#define RCC_BASE              (AHBPERIPH_BASE + 0x00001000)
#define FLASH_R_BASE          (AHBPERIPH_BASE + 0x00002000) /*!< FLASH registers base address */
#define OB_BASE               ((uint32_t)0x1FFFF800)        /*!< FLASH Option Bytes base address */
#define CRC_BASE              (AHBPERIPH_BASE + 0x00003000)
#define TSC_BASE              (AHBPERIPH_BASE + 0x00004000)

#define GPIOA_BASE            (AHB2PERIPH_BASE + 0x00000000)
#define GPIOB_BASE            (AHB2PERIPH_BASE + 0x00000400)
#define GPIOC_BASE            (AHB2PERIPH_BASE + 0x00000800)
#define GPIOD_BASE            (AHB2PERIPH_BASE + 0x00000C00)
//#define GPIOE_BASE            (AHB2PERIPH_BASE + 0x00001000)
#define GPIOF_BASE            (AHB2PERIPH_BASE + 0x00001400)

/**
  * @}
  */

/** @addtogroup Peripheral_declaration
  * @{
  */

#define TIM2                ((TIM_TypeDef *) TIM2_BASE)
#define TIM3                ((TIM_TypeDef *) TIM3_BASE)
#define TIM6                ((TIM_TypeDef *) TIM6_BASE)
#define TIM7                ((TIM_TypeDef *) TIM7_BASE)
#define TIM14               ((TIM_TypeDef *) TIM14_BASE)
#define RTC                 ((RTC_TypeDef *) RTC_BASE)
#define WWDG                ((WWDG_TypeDef *) WWDG_BASE)
#define IWDG                ((IWDG_TypeDef *) IWDG_BASE)
#define SPI2                ((SPI_TypeDef *) SPI2_BASE)
#define USART2              ((USART_TypeDef *) USART2_BASE)
#define I2C1                ((I2C_TypeDef *) I2C1_BASE)
#define I2C2                ((I2C_TypeDef *) I2C2_BASE)
#define USB                 ((USB_TypeDef *) USB_BASE)
#define CRS                 ((CRS_TypeDef *) CRS_BASE)
#define PWR                 ((PWR_TypeDef *) PWR_BASE)

#define SYSCFG              ((SYSCFG_TypeDef *) SYSCFG_BASE)
#define COMP                ((COMP_TypeDef *) COMP_BASE)
#define OPA                 ((OPA_TypeDef *) OPA_BASE)
#define DAC                 ((DAC_TypeDef *) DAC_BASE)
#define OP0                 ((OP0_TypeDef *) OP0_BASE)
#define EXTI                ((EXTI_TypeDef *) EXTI_BASE)
#define ADC1                ((ADC_TypeDef *) ADC1_BASE)
#define ADC                 ((ADC_Common_TypeDef *) ADC_BASE)
#define TIM1                ((TIM_TypeDef *) TIM1_BASE)
#define SPI1                ((SPI_TypeDef *) SPI1_BASE)
#define USART1              ((USART_TypeDef *) USART1_BASE)
#define TIM15               ((TIM_TypeDef *) TIM15_BASE)
#define TIM16               ((TIM_TypeDef *) TIM16_BASE)
#define TIM17               ((TIM_TypeDef *) TIM17_BASE)
#define DBGMCU              ((DBGMCU_TypeDef *) DBGMCU_BASE)

#define DMA1                ((DMA_TypeDef *) DMA1_BASE)
#define DMA1_Channel1       ((DMA_Channel_TypeDef *) DMA1_Channel1_BASE)
#define DMA1_Channel2       ((DMA_Channel_TypeDef *) DMA1_Channel2_BASE)
#define DMA1_Channel3       ((DMA_Channel_TypeDef *) DMA1_Channel3_BASE)
#define DMA1_Channel4       ((DMA_Channel_TypeDef *) DMA1_Channel4_BASE)
#define DMA1_Channel5       ((DMA_Channel_TypeDef *) DMA1_Channel5_BASE)
#define DMA1_Channel6       ((DMA_Channel_TypeDef *) DMA1_Channel6_BASE)
#define DMA1_Channel7       ((DMA_Channel_TypeDef *) DMA1_Channel7_BASE)

#define FLASH               ((FLASH_TypeDef *) FLASH_R_BASE)
#define OB                  ((OB_TypeDef *) OB_BASE)
#define RCC                 ((RCC_TypeDef *) RCC_BASE)
#define CRC                 ((CRC_TypeDef *) CRC_BASE)
#define TSC                 ((TSC_TypeDef *) TSC_BASE)

#define GPIOA               ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB               ((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC               ((GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD               ((GPIO_TypeDef *) GPIOD_BASE)
//#define GPIOE               ((GPIO_TypeDef *) GPIOE_BASE)
#define GPIOF               ((GPIO_TypeDef *) GPIOF_BASE)

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
/*                         Peripheral Registers Bits Definition               */
/******************************************************************************/
/******************************************************************************/
/*                                                                            */
/*                      Analog to Digital Converter (ADC)                     */
/*                                                                            */
/******************************************************************************/
/********************  Bits definition for ADC_ISR register  ******************/
#define ADC_ISR_AWD                          ((uint32_t)0x00000080)        /*!< Analog watchdog flag */
#define ADC_ISR_OVR                          ((uint32_t)0x00000010)        /*!< Overrun flag */
#define ADC_ISR_EOSEQ                        ((uint32_t)0x00000008)        /*!< End of Sequence flag */
#define ADC_ISR_EOC                          ((uint32_t)0x00000004)        /*!< End of Conversion */
#define ADC_ISR_EOSMP                        ((uint32_t)0x00000002)        /*!< End of sampling flag */
#define ADC_ISR_ADRDY                        ((uint32_t)0x00000001)        /*!< ADC Ready */

/* Old EOSEQ bit definition, maintained for legacy purpose */
#define ADC_ISR_EOS                          ADC_ISR_EOSEQ

/********************  Bits definition for ADC_IER register  ******************/
#define ADC_IER_AWDIE                        ((uint32_t)0x00000080)        /*!< Analog Watchdog interrupt enable */
#define ADC_IER_OVRIE                        ((uint32_t)0x00000010)        /*!< Overrun interrupt enable */
#define ADC_IER_EOSEQIE                      ((uint32_t)0x00000008)        /*!< End of Sequence of conversion interrupt enable */
#define ADC_IER_EOCIE                        ((uint32_t)0x00000004)        /*!< End of Conversion interrupt enable */
#define ADC_IER_EOSMPIE                      ((uint32_t)0x00000002)        /*!< End of sampling interrupt enable */
#define ADC_IER_ADRDYIE                      ((uint32_t)0x00000001)        /*!< ADC Ready interrupt enable */

/* Old EOSEQIE bit definition, maintained for legacy purpose */
#define ADC_IER_EOSIE                        ADC_IER_EOSEQIE

/********************  Bits definition for ADC_CR register  *******************/
#define ADC_CR_ADCAL                         ((uint32_t)0x80000000)        /*!< ADC calibration */
#define ADC_CR_ADSTP                         ((uint32_t)0x00000010)        /*!< ADC stop of conversion command */
#define ADC_CR_ADSTART                       ((uint32_t)0x00000004)        /*!< ADC start of conversion */
#define ADC_CR_ADDIS                         ((uint32_t)0x00000002)        /*!< ADC disable command */
#define ADC_CR_ADEN                          ((uint32_t)0x00000001)        /*!< ADC enable control */

/*******************  Bits definition for ADC_CFGR1 register  *****************/
#define  ADC_CFGR1_AWDCH                      ((uint32_t)0x7C000000)       /*!< AWDCH[4:0] bits (Analog watchdog channel select bits) */
#define  ADC_CFGR1_AWDCH_0                    ((uint32_t)0x04000000)       /*!< Bit 0 */
#define  ADC_CFGR1_AWDCH_1                    ((uint32_t)0x08000000)       /*!< Bit 1 */
#define  ADC_CFGR1_AWDCH_2                    ((uint32_t)0x10000000)       /*!< Bit 2 */
#define  ADC_CFGR1_AWDCH_3                    ((uint32_t)0x20000000)       /*!< Bit 3 */
#define  ADC_CFGR1_AWDCH_4                    ((uint32_t)0x40000000)       /*!< Bit 4 */
#define  ADC_CFGR1_AWDEN                      ((uint32_t)0x00800000)       /*!< Analog watchdog enable on regular channels */
#define  ADC_CFGR1_AWDSGL                     ((uint32_t)0x00400000)       /*!< Enable the watchdog on a single channel or on all channels  */
#define  ADC_CFGR1_DISCEN                     ((uint32_t)0x00010000)       /*!< Discontinuous mode on regular channels */
#define  ADC_CFGR1_AUTOFF                     ((uint32_t)0x00008000)       /*!< ADC auto power off */
#define  ADC_CFGR1_WAIT                       ((uint32_t)0x00004000)       /*!< ADC wait conversion mode */
#define  ADC_CFGR1_CONT                       ((uint32_t)0x00002000)       /*!< Continuous Conversion */
#define  ADC_CFGR1_OVRMOD                     ((uint32_t)0x00001000)       /*!< Overrun mode */
#define  ADC_CFGR1_EXTEN                      ((uint32_t)0x00000C00)       /*!< EXTEN[1:0] bits (External Trigger Conversion mode for regular channels) */
#define  ADC_CFGR1_EXTEN_0                    ((uint32_t)0x00000400)       /*!< Bit 0 */
#define  ADC_CFGR1_EXTEN_1                    ((uint32_t)0x00000800)       /*!< Bit 1 */
#define  ADC_CFGR1_EXTSEL                     ((uint32_t)0x000001C0)       /*!< EXTSEL[2:0] bits (External Event Select for regular group) */
#define  ADC_CFGR1_EXTSEL_0                   ((uint32_t)0x00000040)       /*!< Bit 0 */
#define  ADC_CFGR1_EXTSEL_1                   ((uint32_t)0x00000080)       /*!< Bit 1 */
#define  ADC_CFGR1_EXTSEL_2                   ((uint32_t)0x00000100)       /*!< Bit 2 */
#define  ADC_CFGR1_ALIGN                      ((uint32_t)0x00000020)       /*!< Data Alignment */
#define  ADC_CFGR1_RES                        ((uint32_t)0x00000018)       /*!< RES[1:0] bits (Resolution) */
#define  ADC_CFGR1_RES_0                      ((uint32_t)0x00000008)       /*!< Bit 0 */
#define  ADC_CFGR1_RES_1                      ((uint32_t)0x00000010)       /*!< Bit 1 */
#define  ADC_CFGR1_SCANDIR                    ((uint32_t)0x00000004)       /*!< Sequence scan direction */
#define  ADC_CFGR1_DMACFG                     ((uint32_t)0x00000002)       /*!< Direct memory access configuration */
#define  ADC_CFGR1_DMAEN                      ((uint32_t)0x00000001)       /*!< Direct memory access enable */

/* Old WAIT bit definition, maintained for legacy purpose */
#define  ADC_CFGR1_AUTDLY                     ADC_CFGR1_WAIT

/*******************  Bits definition for ADC_CFGR2 register  *****************/
#define  ADC_CFGR2_CKMODE                     ((uint32_t)0xC0000000)       /*!< ADC clock mode */
#define  ADC_CFGR2_CKMODE_1                   ((uint32_t)0x80000000)       /*!< ADC clocked by PCLK div4 */
#define  ADC_CFGR2_CKMODE_0                   ((uint32_t)0x40000000)       /*!< ADC clocked by PCLK div2 */

/* Old bit definition, maintained for legacy purpose */
#define  ADC_CFGR2_JITOFFDIV4                 ADC_CFGR2_CKMODE_1           /*!< ADC clocked by PCLK div4 */
#define  ADC_CFGR2_JITOFFDIV2                 ADC_CFGR2_CKMODE_0           /*!< ADC clocked by PCLK div2 */

/******************  Bit definition for ADC_SMPR register  ********************/
#define  ADC_SMPR_SMP                      ((uint32_t)0x00000007)        /*!< SMP[2:0] bits (Sampling time selection) */
#define  ADC_SMPR_SMP_0                    ((uint32_t)0x00000001)        /*!< Bit 0 */
#define  ADC_SMPR_SMP_1                    ((uint32_t)0x00000002)        /*!< Bit 1 */
#define  ADC_SMPR_SMP_2                    ((uint32_t)0x00000004)        /*!< Bit 2 */

/* Old bit definition, maintained for legacy purpose */
#define  ADC_SMPR1_SMPR                      ADC_SMPR_SMP        /*!< SMP[2:0] bits (Sampling time selection) */
#define  ADC_SMPR1_SMPR_0                    ADC_SMPR_SMP_0        /*!< Bit 0 */
#define  ADC_SMPR1_SMPR_1                    ADC_SMPR_SMP_1        /*!< Bit 1 */
#define  ADC_SMPR1_SMPR_2                    ADC_SMPR_SMP_2        /*!< Bit 2 */

/*******************  Bit definition for ADC_TR register  ********************/
#define  ADC_TR_HT                          ((uint32_t)0x0FFF0000)        /*!< Analog watchdog high threshold */
#define  ADC_TR_LT                          ((uint32_t)0x00000FFF)        /*!< Analog watchdog low threshold */

/* Old bit definition, maintained for legacy purpose */
#define  ADC_HTR_HT                          ADC_TR_HT                    /*!< Analog watchdog high threshold */
#define  ADC_LTR_LT                          ADC_TR_LT                    /*!< Analog watchdog low threshold */

/******************  Bit definition for ADC_CHSELR register  ******************/
#define  ADC_CHSELR_CHSEL19                   ((uint32_t)0x00080000)        /*!< Channel 19 selection */
#define  ADC_CHSELR_CHSEL18                   ((uint32_t)0x00040000)        /*!< Channel 18 selection */
#define  ADC_CHSELR_CHSEL17                   ((uint32_t)0x00020000)        /*!< Channel 17 selection */
#define  ADC_CHSELR_CHSEL16                   ((uint32_t)0x00010000)        /*!< Channel 16 selection */
#define  ADC_CHSELR_CHSEL15                   ((uint32_t)0x00008000)        /*!< Channel 15 selection */
#define  ADC_CHSELR_CHSEL14                   ((uint32_t)0x00004000)        /*!< Channel 14 selection */
#define  ADC_CHSELR_CHSEL13                   ((uint32_t)0x00002000)        /*!< Channel 13 selection */
#define  ADC_CHSELR_CHSEL12                   ((uint32_t)0x00001000)        /*!< Channel 12 selection */
#define  ADC_CHSELR_CHSEL11                   ((uint32_t)0x00000800)        /*!< Channel 11 selection */
#define  ADC_CHSELR_CHSEL10                   ((uint32_t)0x00000400)        /*!< Channel 10 selection */
#define  ADC_CHSELR_CHSEL9                    ((uint32_t)0x00000200)        /*!< Channel 9 selection */
#define  ADC_CHSELR_CHSEL8                    ((uint32_t)0x00000100)        /*!< Channel 8 selection */
#define  ADC_CHSELR_CHSEL7                    ((uint32_t)0x00000080)        /*!< Channel 7 selection */
#define  ADC_CHSELR_CHSEL6                    ((uint32_t)0x00000040)        /*!< Channel 6 selection */
#define  ADC_CHSELR_CHSEL5                    ((uint32_t)0x00000020)        /*!< Channel 5 selection */
#define  ADC_CHSELR_CHSEL4                    ((uint32_t)0x00000010)        /*!< Channel 4 selection */
#define  ADC_CHSELR_CHSEL3                    ((uint32_t)0x00000008)        /*!< Channel 3 selection */
#define  ADC_CHSELR_CHSEL2                    ((uint32_t)0x00000004)        /*!< Channel 2 selection */
#define  ADC_CHSELR_CHSEL1                    ((uint32_t)0x00000002)        /*!< Channel 1 selection */
#define  ADC_CHSELR_CHSEL0                    ((uint32_t)0x00000001)        /*!< Channel 0 selection */

/********************  Bit definition for ADC_DR register  ********************/
#define  ADC_DR_DATA                         ((uint32_t)0x0000FFFF)        /*!< Regular data */

/*******************  Bit definition for ADC_CCR register  ********************/
#define  ADC_CCR_VBATEN                       ((uint32_t)0x01000000)       /*!< Voltage battery enable */
#define  ADC_CCR_TSEN                         ((uint32_t)0x00800000)       /*!< Tempurature sensore enable */
#define  ADC_CCR_VREFEN                       ((uint32_t)0x00400000)       /*!< Vrefint enable */

/*******************  Bit definition for ADC_CR2 register  ********************/
#define  ADC_CR2_VREFEN                       ((uint32_t)0x00000002)       /*!< Voltage battery enable */
#define  ADC_CR2_VREFSEL                      ((uint32_t)0x0000000C)       /*!< Tempurature sensore enable */
#define  ADC_CR2_VREFSEL_0                    ((uint32_t)0x00000004)       /*!< Tempurature sensore enable */
#define  ADC_CR2_VREFSEL_1                    ((uint32_t)0x00000008)       /*!< Tempurature sensore enable */
#define  ADC_CR2_VREF_DECIB                   ((uint32_t)0x00000010)       /*!< Vrefint enable */
#define  ADC_CR2_IOSH1_AMPEN                  ((uint32_t)0x00000100)       /*!< Vrefint enable */
#define  ADC_CR2_IOSH1_SMPEN                  ((uint32_t)0x00000200)       /*!< Vrefint enable */

/******************************************************************************/
/*                                                                            */
/*                      Analog Comparators (COMP)                             */
/*                                                                            */
/******************************************************************************/
/***********************  Bit definition for COMP_CSR register  ***************/
/* NCOMP bits definition */
#define COMP_CSR_NCOMPEN                             ((uint32_t)0x00000001) /*!< MCOMP enable */
#define COMP_CSR_NCOMP_VIP_SEL               ((uint32_t)0x0000000e) /*!<  */
#define COMP_CSR_NCOMP_VIP_SEL_0             ((uint32_t)0x00000002) /*!<  */
#define COMP_CSR_NCOMP_VIP_SEL_1             ((uint32_t)0x00000004) /*!<  */
#define COMP_CSR_NCOMP_VIP_SEL_2             ((uint32_t)0x00000008) /*!<  */
#define COMP_CSR_NCOMP_VIN_SEL               ((uint32_t)0x00000030) /*!<  */
#define COMP_CSR_NCOMP_VIN_SEL_0             ((uint32_t)0x00000010) /*!<  */
#define COMP_CSR_NCOMP_VIN_SEL_1             ((uint32_t)0x00000020) /*!<  */
#define COMP_CSR_NCOMPOUTSEL                     ((uint32_t)0x00000600) /*!<  */
#define COMP_CSR_NCOMPOUTSEL_0               ((uint32_t)0x00000200) /*!<  */
#define COMP_CSR_NCOMPOUTSEL_1               ((uint32_t)0x00000400) /*!<  */
#define COMP_CSR_NCOMP_POL                       ((uint32_t)0x00000800) /*!<  */
#define COMP_CSR_COMP1OUT                            ((uint32_t)0x00004000) /*!<  */
#define COMP_CSR_NCOMPLOCK                       ((uint32_t)0x00008000) /*!<  */

/* PCOMP bits definition */
#define COMP_CSR_PCOMPEN                             ((uint32_t)0x00010000) /*!< PCOMP enable */
#define COMP_CSR_PCOMP_VIP_SEL               ((uint32_t)0x00060000) /*!<  */
#define COMP_CSR_PCOMP_VIP_SEL_0             ((uint32_t)0x00020000) /*!<  */
#define COMP_CSR_PCOMP_VIP_SEL_1             ((uint32_t)0x00040000) /*!<  */
#define COMP_CSR_PCOMP_VIN_SEL               ((uint32_t)0x00180000) /*!<  */
#define COMP_CSR_PCOMP_VIN_SEL_0             ((uint32_t)0x00080000) /*!<  */
#define COMP_CSR_PCOMP_VIN_SEL_1             ((uint32_t)0x00100000) /*!<  */
#define COMP_CSR_WNDWEN                              ((uint32_t)0x00800000) /*!<  */

#define COMP_CSR_PCOMPOUTSEL                     ((uint32_t)0x07000000) /*!<  */
#define COMP_CSR_PCOMPOUTSEL_0               ((uint32_t)0x01000000) /*!<  */
#define COMP_CSR_PCOMPOUTSEL_1               ((uint32_t)0x02000000) /*!<  */
#define COMP_CSR_PCOMPOUTSEL_2               ((uint32_t)0x04000000) /*!<  */
#define COMP_CSR_PCOMP_POL                       ((uint32_t)0x08000000) /*!<  */
#define COMP_CSR_COMP2OUT                            ((uint32_t)0x40000000) /*!<  */
#define COMP_CSR_PCOMP_LOCK                      ((uint32_t)0x80000000) /*!<  */

/******************************************************************************/
/*                                                                            */
/*                       CRC calculation unit (CRC)                           */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for CRC_DR register  *********************/
#define  CRC_DR_DR                           ((uint32_t)0xFFFFFFFF) /*!< Data register bits */

/*******************  Bit definition for CRC_IDR register  ********************/
#define  CRC_IDR_IDR                         ((uint8_t)0xFF)        /*!< General-purpose 8-bit data register bits */

/********************  Bit definition for CRC_CR register  ********************/
#define  CRC_CR_RESET                        ((uint32_t)0x00000001) /*!< RESET the CRC computation unit bit */
//#define  CRC_CR_POLSIZE                      ((uint32_t)0x00000018) /*!< Polynomial size bits (only for FT32F030X8 devices)*/
//#define  CRC_CR_POLSIZE_0                    ((uint32_t)0x00000008) /*!< Polynomial size bit 0 (only for FT32F030X8 devices) */
//#define  CRC_CR_POLSIZE_1                    ((uint32_t)0x00000010) /*!< Polynomial size bit 1 (only for FT32F030X8 devices) */
#define  CRC_CR_REV_IN                       ((uint32_t)0x00000060) /*!< REV_IN Reverse Input Data bits */
#define  CRC_CR_REV_IN_0                     ((uint32_t)0x00000020) /*!< REV_IN Bit 0 */
#define  CRC_CR_REV_IN_1                     ((uint32_t)0x00000040) /*!< REV_IN Bit 1 */
#define  CRC_CR_REV_OUT                      ((uint32_t)0x00000080) /*!< REV_OUT Reverse Output Data bits */

/*******************  Bit definition for CRC_INIT register  *******************/
#define  CRC_INIT_INIT                       ((uint32_t)0xFFFFFFFF) /*!< Initial CRC value bits */

/*******************  Bit definition for CRC_POL register  ********************/
//#define  CRC_POL_POL                         ((uint32_t)0xFFFFFFFF) /*!< Coefficients of the polynomial (only for FT32F030X8 devices) */

/******************************************************************************/
/*                                                                            */
/*                          CRS Clock Recovery System                         */
/*                   (Available only for FT32F030X8 devices)                */
/******************************************************************************/

/*******************  Bit definition for CRS_CR register  *********************/
#define  CRS_CR_SYNCOKIE                     ((uint32_t)0x00000001) /* SYNC event OK interrupt enable        */
#define  CRS_CR_SYNCWARNIE                   ((uint32_t)0x00000002) /* SYNC warning interrupt enable         */
#define  CRS_CR_ERRIE                        ((uint32_t)0x00000004) /* SYNC error interrupt enable           */
#define  CRS_CR_ESYNCIE                      ((uint32_t)0x00000008) /* Expected SYNC(ESYNCF) interrupt Enable*/
#define  CRS_CR_CEN                          ((uint32_t)0x00000020) /* Frequency error counter enable        */
#define  CRS_CR_AUTOTRIMEN                   ((uint32_t)0x00000040) /* Automatic trimming enable             */
#define  CRS_CR_SWSYNC                       ((uint32_t)0x00000080) /* A Software SYNC event is generated    */
#define  CRS_CR_TRIM                         ((uint32_t)0x00003F00) /* HSI48 oscillator smooth trimming      */

/*******************  Bit definition for CRS_CFGR register  *********************/
#define  CRS_CFGR_RELOAD                     ((uint32_t)0x0000FFFF) /* Counter reload value               */
#define  CRS_CFGR_FELIM                      ((uint32_t)0x00FF0000) /* Frequency error limit              */
#define  CRS_CFGR_SYNCDIV                    ((uint32_t)0x07000000) /* SYNC divider                       */
#define  CRS_CFGR_SYNCDIV_0                  ((uint32_t)0x01000000) /* Bit 0                              */
#define  CRS_CFGR_SYNCDIV_1                  ((uint32_t)0x02000000) /* Bit 1                              */
#define  CRS_CFGR_SYNCDIV_2                  ((uint32_t)0x04000000) /* Bit 2                              */
#define  CRS_CFGR_SYNCSRC                    ((uint32_t)0x30000000) /* SYNC signal source selection       */
#define  CRS_CFGR_SYNCSRC_0                  ((uint32_t)0x10000000) /* Bit 0                              */
#define  CRS_CFGR_SYNCSRC_1                  ((uint32_t)0x20000000) /* Bit 1                              */
#define  CRS_CFGR_SYNCPOL                    ((uint32_t)0x80000000) /* SYNC polarity selection            */

/*******************  Bit definition for CRS_ISR register  *********************/
#define  CRS_ISR_SYNCOKF                     ((uint32_t)0x00000001) /* SYNC event OK flag             */
#define  CRS_ISR_SYNCWARNF                   ((uint32_t)0x00000002) /* SYNC warning                   */
#define  CRS_ISR_ERRF                        ((uint32_t)0x00000004) /* SYNC error flag                */
#define  CRS_ISR_ESYNCF                      ((uint32_t)0x00000008) /* Expected SYNC flag             */
#define  CRS_ISR_SYNCERR                     ((uint32_t)0x00000100) /* SYNC error                     */
#define  CRS_ISR_SYNCMISS                    ((uint32_t)0x00000200) /* SYNC missed                    */
#define  CRS_ISR_TRIMOVF                     ((uint32_t)0x00000400) /* Trimming overflow or underflow */
#define  CRS_ISR_FEDIR                       ((uint32_t)0x00008000) /* Frequency error direction      */
#define  CRS_ISR_FECAP                       ((uint32_t)0xFFFF0000) /* Frequency error capture        */

/*******************  Bit definition for CRS_ICR register  *********************/
#define  CRS_ICR_SYNCOKC                     ((uint32_t)0x00000001) /* SYNC event OK clear flag     */
#define  CRS_ICR_SYNCWARNC                   ((uint32_t)0x00000002) /* SYNC warning clear flag      */
#define  CRS_ICR_ERRC                        ((uint32_t)0x00000004) /* Error clear flag        */
#define  CRS_ICR_ESYNCC                      ((uint32_t)0x00000008) /* Expected SYNC clear flag     */

/******************************************************************************/
/*                                                                            */
/*                 Digital to Analog Converter (DAC)                          */
/*                                                                            */
/******************************************************************************/
/********************  Bit definition for DAC_CTRL register  ********************/
#define DAC_CTRL_EN     ((uint32_t)(0x00000001))
#define DAC_CTRL_REF_SEL    ((uint32_t)(0x00000006))
#define DAC_CTRL_REF_SEL_0  ((uint32_t)(0x00000000))        // 2V
#define DAC_CTRL_REF_SEL_1  ((uint32_t)(0x00000002))        // 3V
#define DAC_CTRL_REF_SEL_2  ((uint32_t)(0x00000004))        // 4V
#define DAC_CTRL_REF_SEL_3  ((uint32_t)(0x00000006))        // VDDA

#define IS_DAC_REF_SEL(SEL) (((SEL) == DAC_CTRL_REF_SEL_0) ||\
                (((SEL) == DAC_CTRL_REF_SEL_1) ||\
                (((SEL) == DAC_CTRL_REF_SEL_2) ||\
                ((SEL) == DAC_CTRL_REF_SEL_3))

/******************************************************************************/
/*                                                                            */
/*                           Debug MCU (DBGMCU)                               */
/*                                                                            */
/******************************************************************************/

/****************  Bit definition for DBGMCU_IDCODE register  *****************/
//#define  DBGMCU_IDCODE_DEV_ID                ((uint32_t)0x00000FFF)        /*!< Device Identifier */
//
//#define  DBGMCU_IDCODE_REV_ID                ((uint32_t)0xFFFF0000)        /*!< REV_ID[15:0] bits (Revision Identifier) */
//#define  DBGMCU_IDCODE_REV_ID_0              ((uint32_t)0x00010000)        /*!< Bit 0 */
//#define  DBGMCU_IDCODE_REV_ID_1              ((uint32_t)0x00020000)        /*!< Bit 1 */
//#define  DBGMCU_IDCODE_REV_ID_2              ((uint32_t)0x00040000)        /*!< Bit 2 */
//#define  DBGMCU_IDCODE_REV_ID_3              ((uint32_t)0x00080000)        /*!< Bit 3 */
//#define  DBGMCU_IDCODE_REV_ID_4              ((uint32_t)0x00100000)        /*!< Bit 4 */
//#define  DBGMCU_IDCODE_REV_ID_5              ((uint32_t)0x00200000)        /*!< Bit 5 */
//#define  DBGMCU_IDCODE_REV_ID_6              ((uint32_t)0x00400000)        /*!< Bit 6 */
//#define  DBGMCU_IDCODE_REV_ID_7              ((uint32_t)0x00800000)        /*!< Bit 7 */
//#define  DBGMCU_IDCODE_REV_ID_8              ((uint32_t)0x01000000)        /*!< Bit 8 */
//#define  DBGMCU_IDCODE_REV_ID_9              ((uint32_t)0x02000000)        /*!< Bit 9 */
//#define  DBGMCU_IDCODE_REV_ID_10             ((uint32_t)0x04000000)        /*!< Bit 10 */
//#define  DBGMCU_IDCODE_REV_ID_11             ((uint32_t)0x08000000)        /*!< Bit 11 */
//#define  DBGMCU_IDCODE_REV_ID_12             ((uint32_t)0x10000000)        /*!< Bit 12 */
//#define  DBGMCU_IDCODE_REV_ID_13             ((uint32_t)0x20000000)        /*!< Bit 13 */
//#define  DBGMCU_IDCODE_REV_ID_14             ((uint32_t)0x40000000)        /*!< Bit 14 */
//#define  DBGMCU_IDCODE_REV_ID_15             ((uint32_t)0x80000000)        /*!< Bit 15 */

#define  DBGMCU_IDCODE_DESIGNER                              ((uint32_t)0x00000FFE)        /*!< Device Identifier */

#define  DBGMCU_IDCODE_PARTNO                                  ((uint32_t)0x0FFFF000)        /*!< Device Identifier */
#define  DBGMCU_IDCODE_PARTNO_0                ((uint32_t)0x00010000)        /*!< Bit 0 */
#define  DBGMCU_IDCODE_PARTNO_1                ((uint32_t)0x00020000)        /*!< Bit 1 */
#define  DBGMCU_IDCODE_PARTNO_2                ((uint32_t)0x00040000)        /*!< Bit 2 */
#define  DBGMCU_IDCODE_PARTNO_3                ((uint32_t)0x00080000)        /*!< Bit 3 */
#define  DBGMCU_IDCODE_PARTNO_4                ((uint32_t)0x00100000)        /*!< Bit 4 */
#define  DBGMCU_IDCODE_PARTNO_5                ((uint32_t)0x00200000)        /*!< Bit 5 */
#define  DBGMCU_IDCODE_PARTNO_6                ((uint32_t)0x00400000)        /*!< Bit 6 */
#define  DBGMCU_IDCODE_PARTNO_7                ((uint32_t)0x00800000)        /*!< Bit 7 */
#define  DBGMCU_IDCODE_PARTNO_8                ((uint32_t)0x01000000)        /*!< Bit 8 */
#define  DBGMCU_IDCODE_PARTNO_9                ((uint32_t)0x02000000)        /*!< Bit 9 */
#define  DBGMCU_IDCODE_PARTNO_10               ((uint32_t)0x04000000)        /*!< Bit 10 */
#define  DBGMCU_IDCODE_PARTNO_11               ((uint32_t)0x08000000)        /*!< Bit 11 */
#define  DBGMCU_IDCODE_PARTNO_12               ((uint32_t)0x10000000)        /*!< Bit 12 */
#define  DBGMCU_IDCODE_PARTNO_13               ((uint32_t)0x20000000)        /*!< Bit 13 */
#define  DBGMCU_IDCODE_PARTNO_14               ((uint32_t)0x40000000)        /*!< Bit 14 */
#define  DBGMCU_IDCODE_PARTNO_15               ((uint32_t)0x80000000)        /*!< Bit 15 */

#define  DBGMCU_IDCODE_VERSION                               ((uint32_t)0xF0000000)        /*!< Device Identifier */

/******************  Bit definition for DBGMCU_CR register  *******************/
#define  DBGMCU_CR_DBG_STOP                  ((uint32_t)0x00000002)        /*!< Debug Stop Mode */
#define  DBGMCU_CR_DBG_STANDBY               ((uint32_t)0x00000004)        /*!< Debug Standby mode */

/******************  Bit definition for DBGMCU_APB1_FZ register  **************/
//#define  DBGMCU_APB1_FZ_DBG_TIM2_STOP        ((uint32_t)0x00000001)        /*!< TIM2 counter stopped when core is halted */
#define  DBGMCU_APB1_FZ_DBG_TIM3_STOP        ((uint32_t)0x00000002)        /*!< TIM3 counter stopped when core is halted */
#define  DBGMCU_APB1_FZ_DBG_TIM6_STOP        ((uint32_t)0x00000010)        /*!< TIM6 counter stopped when core is halted */
#define  DBGMCU_APB1_FZ_DBG_TIM7_STOP        ((uint32_t)0x00000020)        /*!< TIM7 counter stopped when core is halted (only for FT32F030X8 devices) */
#define  DBGMCU_APB1_FZ_DBG_TIM14_STOP       ((uint32_t)0x00000100)        /*!< TIM14 counter stopped when core is halted */
#define  DBGMCU_APB1_FZ_DBG_RTC_STOP         ((uint32_t)0x00000400)        /*!< RTC Calendar frozen when core is halted */
#define  DBGMCU_APB1_FZ_DBG_WWDG_STOP        ((uint32_t)0x00000800)        /*!< Debug Window Watchdog stopped when Core is halted */
#define  DBGMCU_APB1_FZ_DBG_IWDG_STOP        ((uint32_t)0x00001000)        /*!< Debug Independent Watchdog stopped when Core is halted */
#define  DBGMCU_APB1_FZ_DBG_I2C1_SMBUS_TIMEOUT    ((uint32_t)0x20000000)   /*!< I2C1 SMBUS timeout mode stopped when Core is halted */
//#define  DBGMCU_APB1_FZ_DBG_CAN_STOP         ((uint32_t)0x02000000)        /*!< CAN debug stopped when Core is halted (only for FT32F030X8 devices) */

/******************  Bit definition for DBGMCU_APB2_FZ register  **************/
#define  DBGMCU_APB2_FZ_DBG_TIM1_STOP        ((uint32_t)0x00000800)        /*!< TIM1 counter stopped when core is halted */
#define  DBGMCU_APB2_FZ_DBG_TIM15_STOP       ((uint32_t)0x00010000)        /*!< TIM15 counter stopped when core is halted */
#define  DBGMCU_APB2_FZ_DBG_TIM16_STOP       ((uint32_t)0x00020000)        /*!< TIM16 counter stopped when core is halted */
#define  DBGMCU_APB2_FZ_DBG_TIM17_STOP       ((uint32_t)0x00040000)        /*!< TIM17 counter stopped when core is halted */

/******************************************************************************/
/*                                                                            */
/*                           OPA Controller (OPA)                             */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for OPA register  ********************/
#define OPA_OP1_OUT                         ((uint32_t)0x00010000)        /*!< OP1 OUT STATE                                */
#define OPA_OP1_PSEL                        ((uint32_t)0x00008000)        /*!< OP1 normal phase input selection             */
#define OPA_OP1_NSEL                        ((uint32_t)0x00006000)        /*!< OP1 inverting terminal input selection       */
#define OPA_OP1_NSEL_0                      ((uint32_t)0x00002000)        /*!< OP1 inverting terminal input selection BIT0  */
#define OPA_OP1_NSEL_1                      ((uint32_t)0x00004000)        /*!< OP1 inverting terminal input selection BIT1  */
#define OPA_OP1_FR                          ((uint32_t)0x00001C00)        /*!< OP1 feedback resistor selection              */
#define OPA_OP1_FR_0                        ((uint32_t)0x00000400)        /*!< OP1 feedback resistor selection BIT0         */
#define OPA_OP1_FR_1                        ((uint32_t)0x00000800)        /*!< OP1 feedback resistor selection BIT1         */
#define OPA_OP1_FR_2                        ((uint32_t)0x00001000)        /*!< OP1 feedback resistor selection BIT2         */
#define OPA_OP1_FCAPE                       ((uint32_t)0x00000200)        /*!< OP1 compensation capacitor enable BIT        */
#define OPA_OP1_TM                          ((uint32_t)0x00000100)        /*!< OP1 input misalignment calibration mode      */
#define OPA_OP1_TODIG                       ((uint32_t)0x00000080)        /*!< OP1 outputs to the register control bit      */
#define OPA_OP1_TOIO                        ((uint32_t)0x00000040)        /*!< OP1 outputs to the ENABLE bit of PA0         */
#define OPA_OP1_COF                         ((uint32_t)0x0000003E)        /*!< OP1 input misalignment calibration           */
#define OPA_OP1_COF_0                       ((uint32_t)0x00000002)        /*!< OP1 input misalignment calibration BIT0      */
#define OPA_OP1_COF_1                       ((uint32_t)0x00000004)        /*!< OP1 input misalignment calibration BIT1      */
#define OPA_OP1_COF_2                       ((uint32_t)0x00000008)        /*!< OP1 input misalignment calibration BIT2      */
#define OPA_OP1_COF_3                       ((uint32_t)0x00000010)        /*!< OP1 input misalignment calibration BIT3      */
#define OPA_OP1_COF_4                       ((uint32_t)0x00000020)        /*!< OP1 input misalignment calibration BIT4      */
#define OPA_OP1_ON                          ((uint32_t)0x00000001)        /*!< OP1 enable BIT                               */


/******************************************************************************/
/*                                                                            */
/*                           DMA Controller (DMA)                             */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for DMA_ISR register  ********************/
#define  DMA_ISR_GIF1                        ((uint32_t)0x00000001)        /*!< Channel 1 Global interrupt flag    */
#define  DMA_ISR_TCIF1                       ((uint32_t)0x00000002)        /*!< Channel 1 Transfer Complete flag   */
#define  DMA_ISR_HTIF1                       ((uint32_t)0x00000004)        /*!< Channel 1 Half Transfer flag       */
#define  DMA_ISR_TEIF1                       ((uint32_t)0x00000008)        /*!< Channel 1 Transfer Error flag      */
#define  DMA_ISR_GIF2                        ((uint32_t)0x00000010)        /*!< Channel 2 Global interrupt flag    */
#define  DMA_ISR_TCIF2                       ((uint32_t)0x00000020)        /*!< Channel 2 Transfer Complete flag   */
#define  DMA_ISR_HTIF2                       ((uint32_t)0x00000040)        /*!< Channel 2 Half Transfer flag       */
#define  DMA_ISR_TEIF2                       ((uint32_t)0x00000080)        /*!< Channel 2 Transfer Error flag      */
#define  DMA_ISR_GIF3                        ((uint32_t)0x00000100)        /*!< Channel 3 Global interrupt flag    */
#define  DMA_ISR_TCIF3                       ((uint32_t)0x00000200)        /*!< Channel 3 Transfer Complete flag   */
#define  DMA_ISR_HTIF3                       ((uint32_t)0x00000400)        /*!< Channel 3 Half Transfer flag       */
#define  DMA_ISR_TEIF3                       ((uint32_t)0x00000800)        /*!< Channel 3 Transfer Error flag      */
#define  DMA_ISR_GIF4                        ((uint32_t)0x00001000)        /*!< Channel 4 Global interrupt flag    */
#define  DMA_ISR_TCIF4                       ((uint32_t)0x00002000)        /*!< Channel 4 Transfer Complete flag   */
#define  DMA_ISR_HTIF4                       ((uint32_t)0x00004000)        /*!< Channel 4 Half Transfer flag       */
#define  DMA_ISR_TEIF4                       ((uint32_t)0x00008000)        /*!< Channel 4 Transfer Error flag      */
#define  DMA_ISR_GIF5                        ((uint32_t)0x00010000)        /*!< Channel 5 Global interrupt flag    */
#define  DMA_ISR_TCIF5                       ((uint32_t)0x00020000)        /*!< Channel 5 Transfer Complete flag   */
#define  DMA_ISR_HTIF5                       ((uint32_t)0x00040000)        /*!< Channel 5 Half Transfer flag       */
#define  DMA_ISR_TEIF5                       ((uint32_t)0x00080000)        /*!< Channel 5 Transfer Error flag      */
//#define  DMA_ISR_GIF6                        ((uint32_t)0x00100000)        /*!< Channel 6 Global interrupt flag (only for FT32F030X8 devices) */
//#define  DMA_ISR_TCIF6                       ((uint32_t)0x00200000)        /*!< Channel 6 Transfer Complete flag (only for FT32F030X8 devices) */
//#define  DMA_ISR_HTIF6                       ((uint32_t)0x00400000)        /*!< Channel 6 Half Transfer flag (only for FT32F030X8 devices) */
//#define  DMA_ISR_TEIF6                       ((uint32_t)0x00800000)        /*!< Channel 6 Transfer Error flag (only for FT32F030X8 devices) */
//#define  DMA_ISR_GIF7                        ((uint32_t)0x01000000)        /*!< Channel 7 Global interrupt flag (only for FT32F030X8 devices) */
//#define  DMA_ISR_TCIF7                       ((uint32_t)0x02000000)        /*!< Channel 7 Transfer Complete flag (only for FT32F030X8 devices) */
//#define  DMA_ISR_HTIF7                       ((uint32_t)0x04000000)        /*!< Channel 7 Half Transfer flag (only for FT32F030X8 devices) */
//#define  DMA_ISR_TEIF7                       ((uint32_t)0x08000000)        /*!< Channel 7 Transfer Error flag (only for FT32F030X8 devices) */

/*******************  Bit definition for DMA_IFCR register  *******************/
#define  DMA_IFCR_CGIF1                      ((uint32_t)0x00000001)        /*!< Channel 1 Global interrupt clear    */
#define  DMA_IFCR_CTCIF1                     ((uint32_t)0x00000002)        /*!< Channel 1 Transfer Complete clear   */
#define  DMA_IFCR_CHTIF1                     ((uint32_t)0x00000004)        /*!< Channel 1 Half Transfer clear       */
#define  DMA_IFCR_CTEIF1                     ((uint32_t)0x00000008)        /*!< Channel 1 Transfer Error clear      */
#define  DMA_IFCR_CGIF2                      ((uint32_t)0x00000010)        /*!< Channel 2 Global interrupt clear    */
#define  DMA_IFCR_CTCIF2                     ((uint32_t)0x00000020)        /*!< Channel 2 Transfer Complete clear   */
#define  DMA_IFCR_CHTIF2                     ((uint32_t)0x00000040)        /*!< Channel 2 Half Transfer clear       */
#define  DMA_IFCR_CTEIF2                     ((uint32_t)0x00000080)        /*!< Channel 2 Transfer Error clear      */
#define  DMA_IFCR_CGIF3                      ((uint32_t)0x00000100)        /*!< Channel 3 Global interrupt clear    */
#define  DMA_IFCR_CTCIF3                     ((uint32_t)0x00000200)        /*!< Channel 3 Transfer Complete clear   */
#define  DMA_IFCR_CHTIF3                     ((uint32_t)0x00000400)        /*!< Channel 3 Half Transfer clear       */
#define  DMA_IFCR_CTEIF3                     ((uint32_t)0x00000800)        /*!< Channel 3 Transfer Error clear      */
#define  DMA_IFCR_CGIF4                      ((uint32_t)0x00001000)        /*!< Channel 4 Global interrupt clear    */
#define  DMA_IFCR_CTCIF4                     ((uint32_t)0x00002000)        /*!< Channel 4 Transfer Complete clear   */
#define  DMA_IFCR_CHTIF4                     ((uint32_t)0x00004000)        /*!< Channel 4 Half Transfer clear       */
#define  DMA_IFCR_CTEIF4                     ((uint32_t)0x00008000)        /*!< Channel 4 Transfer Error clear      */
#define  DMA_IFCR_CGIF5                      ((uint32_t)0x00010000)        /*!< Channel 5 Global interrupt clear    */
#define  DMA_IFCR_CTCIF5                     ((uint32_t)0x00020000)        /*!< Channel 5 Transfer Complete clear   */
#define  DMA_IFCR_CHTIF5                     ((uint32_t)0x00040000)        /*!< Channel 5 Half Transfer clear       */
#define  DMA_IFCR_CTEIF5                     ((uint32_t)0x00080000)        /*!< Channel 5 Transfer Error clear      */
//#define  DMA_IFCR_CGIF6                      ((uint32_t)0x00100000)        /*!< Channel 6 Global interrupt clear (only for FT32F030X8 devices) */
//#define  DMA_IFCR_CTCIF6                     ((uint32_t)0x00200000)        /*!< Channel 6 Transfer Complete clear (only for FT32F030X8 devices) */
//#define  DMA_IFCR_CHTIF6                     ((uint32_t)0x00400000)        /*!< Channel 6 Half Transfer clear (only for FT32F030X8 devices) */
//#define  DMA_IFCR_CTEIF6                     ((uint32_t)0x00800000)        /*!< Channel 6 Transfer Error clear (only for FT32F030X8 devices) */
//#define  DMA_IFCR_CGIF7                      ((uint32_t)0x01000000)        /*!< Channel 7 Global interrupt clear (only for FT32F030X8 devices) */
//#define  DMA_IFCR_CTCIF7                     ((uint32_t)0x02000000)        /*!< Channel 7 Transfer Complete clear (only for FT32F030X8 devices) */
//#define  DMA_IFCR_CHTIF7                     ((uint32_t)0x04000000)        /*!< Channel 7 Half Transfer clear (only for FT32F030X8 devices) */
//#define  DMA_IFCR_CTEIF7                     ((uint32_t)0x08000000)        /*!< Channel 7 Transfer Error clear (only for FT32F030X8 devices) */

/*******************  Bit definition for DMA_CCR register  ********************/
#define  DMA_CCR_EN                          ((uint32_t)0x00000001)        /*!< Channel enable                      */
#define  DMA_CCR_TCIE                        ((uint32_t)0x00000002)        /*!< Transfer complete interrupt enable  */
#define  DMA_CCR_HTIE                        ((uint32_t)0x00000004)        /*!< Half Transfer interrupt enable      */
#define  DMA_CCR_TEIE                        ((uint32_t)0x00000008)        /*!< Transfer error interrupt enable     */
#define  DMA_CCR_DIR                         ((uint32_t)0x00000010)        /*!< Data transfer direction             */
#define  DMA_CCR_CIRC                        ((uint32_t)0x00000020)        /*!< Circular mode                       */
#define  DMA_CCR_PINC                        ((uint32_t)0x00000040)        /*!< Peripheral increment mode           */
#define  DMA_CCR_MINC                        ((uint32_t)0x00000080)        /*!< Memory increment mode               */

#define  DMA_CCR_PSIZE                       ((uint32_t)0x00000300)        /*!< PSIZE[1:0] bits (Peripheral size)   */
#define  DMA_CCR_PSIZE_0                     ((uint32_t)0x00000100)        /*!< Bit 0                               */
#define  DMA_CCR_PSIZE_1                     ((uint32_t)0x00000200)        /*!< Bit 1                               */

#define  DMA_CCR_MSIZE                       ((uint32_t)0x00000C00)        /*!< MSIZE[1:0] bits (Memory size)       */
#define  DMA_CCR_MSIZE_0                     ((uint32_t)0x00000400)        /*!< Bit 0                               */
#define  DMA_CCR_MSIZE_1                     ((uint32_t)0x00000800)        /*!< Bit 1                               */

#define  DMA_CCR_PL                          ((uint32_t)0x00003000)        /*!< PL[1:0] bits(Channel Priority level)*/
#define  DMA_CCR_PL_0                        ((uint32_t)0x00001000)        /*!< Bit 0                               */
#define  DMA_CCR_PL_1                        ((uint32_t)0x00002000)        /*!< Bit 1                               */

#define  DMA_CCR_MEM2MEM                     ((uint32_t)0x00004000)        /*!< Memory to memory mode               */

/******************  Bit definition for DMA_CNDTR register  *******************/
#define  DMA_CNDTR_NDT                       ((uint32_t)0x00000FFF)        /*!< Number of data to Transfer          */

/******************  Bit definition for DMA_CPAR register  ********************/
#define  DMA_CPAR1_PA                        ((uint32_t)0xFFFFFFFF)        /*!< Peripheral Address                  */
#define  DMA_CPAR2_PA                        ((uint32_t)0xFFFFFFFF)        /*!< Peripheral Address                  */
#define  DMA_CPAR3_PA                        ((uint32_t)0xFFFFFFFF)        /*!< Peripheral Address                  */
#define  DMA_CPAR4_PA                        ((uint32_t)0xFFFFFFFF)        /*!< Peripheral Address                  */
#define  DMA_CPAR5_PA                        ((uint32_t)0xFFFFFFFF)        /*!< Peripheral Address                  */

/******************  Bit definition for DMA_CMAR register  ********************/
#define  DMA_CMAR1_MA                        ((uint32_t)0xFFFFFFFF)        /*!< Memory Address                      */
#define  DMA_CMAR2_MA                        ((uint32_t)0xFFFFFFFF)        /*!< Memory Address                      */
#define  DMA_CMAR3_MA                        ((uint32_t)0xFFFFFFFF)        /*!< Memory Address                      */
#define  DMA_CMAR4_MA                        ((uint32_t)0xFFFFFFFF)        /*!< Memory Address                      */
#define  DMA_CMAR5_MA                        ((uint32_t)0xFFFFFFFF)        /*!< Memory Address                      */

/******************  Bit definition for DMA_RMPCR1 register  ********************/
//#define DMA_RMPCR1_DEFAULT                  ((uint32_t)0x00000000)        /*!< Default remap position for DMA1 */
//#define DMA_RMPCR1_CH1_ADC                  ((uint32_t)0x00000001)        /*!< Remap ADC on DMA1 Channel 1*/
//#define DMA_RMPCR1_CH1_TIM17_CH1            ((uint32_t)0x00000007)        /*!< Remap TIM17 channel 1 on DMA1 channel 1 */
//#define DMA_RMPCR1_CH1_TIM17_UP             ((uint32_t)0x00000007)        /*!< Remap TIM17 up on DMA1 channel 1 */
//#define DMA_RMPCR1_CH1_USART1_RX            ((uint32_t)0x00000008)        /*!< Remap USART1 Rx on DMA1 channel 1 */
//#define DMA_RMPCR1_CH1_USART2_RX            ((uint32_t)0x00000009)        /*!< Remap USART2 Rx on DMA1 channel 1 */
//#define DMA_RMPCR1_CH1_USART3_RX            ((uint32_t)0x0000000A)        /*!< Remap USART3 Rx on DMA1 channel 1 */
//#define DMA_RMPCR1_CH1_USART4_RX            ((uint32_t)0x0000000B)        /*!< Remap USART4 Rx on DMA1 channel 1 */
//#define DMA_RMPCR1_CH1_USART5_RX            ((uint32_t)0x0000000C)        /*!< Remap USART5 Rx on DMA1 channel 1 */
//#define DMA_RMPCR1_CH1_USART6_RX            ((uint32_t)0x0000000D)        /*!< Remap USART6 Rx on DMA1 channel 1 */
//#define DMA_RMPCR1_CH1_USART7_RX            ((uint32_t)0x0000000E)        /*!< Remap USART7 Rx on DMA1 channel 1 */
//#define DMA_RMPCR1_CH1_USART8_RX            ((uint32_t)0x0000000F)        /*!< Remap USART8 Rx on DMA1 channel 1 */
//#define DMA_RMPCR1_CH2_ADC                  ((uint32_t)0x00000010)        /*!< Remap ADC on DMA1 channel 2 */
//#define DMA_RMPCR1_CH2_I2C1_TX              ((uint32_t)0x00000020)        /*!< Remap I2C1 Tx on DMA1 channel 2 */
//#define DMA_RMPCR1_CH2_SPI_1RX              ((uint32_t)0x00000030)        /*!< Remap SPI1 Rx on DMA1 channel 2 */
//#define DMA_RMPCR1_CH2_TIM1_CH1             ((uint32_t)0x00000040)        /*!< Remap TIM1 channel 1 on DMA1 channel 2 */
//#define DMA_RMPCR1_CH2_TIM17_CH1            ((uint32_t)0x00000070)        /*!< Remap TIM17 channel 1 on DMA1 channel 2 */
//#define DMA_RMPCR1_CH2_TIM17_UP             ((uint32_t)0x00000070)        /*!< Remap TIM17 up on DMA1 channel 2 */
//#define DMA_RMPCR1_CH2_USART1_TX            ((uint32_t)0x00000080)        /*!< Remap USART1 Tx on DMA1 channel 2 */
//#define DMA_RMPCR1_CH2_USART2_TX            ((uint32_t)0x00000090)        /*!< Remap USART2 Tx on DMA1 channel 2 */
//#define DMA_RMPCR1_CH2_USART3_TX            ((uint32_t)0x000000A0)        /*!< Remap USART3 Tx on DMA1 channel 2 */
//#define DMA_RMPCR1_CH2_USART4_TX            ((uint32_t)0x000000B0)        /*!< Remap USART4 Tx on DMA1 channel 2 */
//#define DMA_RMPCR1_CH2_USART5_TX            ((uint32_t)0x000000C0)        /*!< Remap USART5 Tx on DMA1 channel 2 */
//#define DMA_RMPCR1_CH2_USART6_TX            ((uint32_t)0x000000D0)        /*!< Remap USART6 Tx on DMA1 channel 2 */
//#define DMA_RMPCR1_CH2_USART7_TX            ((uint32_t)0x000000E0)        /*!< Remap USART7 Tx on DMA1 channel 2 */
//#define DMA_RMPCR1_CH2_USART8_TX            ((uint32_t)0x000000F0)        /*!< Remap USART8 Tx on DMA1 channel 2 */
//#define DMA_RMPCR1_CH3_TIM6_UP              ((uint32_t)0x00000100)        /*!< Remap TIM6 up on DMA1 channel 3 */
//#define DMA_RMPCR1_CH3_DAC_CH1              ((uint32_t)0x00000100)        /*!< Remap DAC Channel 1on DMA1 channel 3 */
//#define DMA_RMPCR1_CH3_I2C1_RX              ((uint32_t)0x00000200)        /*!< Remap I2C1 Rx on DMA1 channel 3 */
//#define DMA_RMPCR1_CH3_SPI1_TX              ((uint32_t)0x00000300)        /*!< Remap SPI1 Tx on DMA1 channel 3 */
//#define DMA_RMPCR1_CH3_TIM1_CH2             ((uint32_t)0x00000400)        /*!< Remap TIM1 channel 2 on DMA1 channel 3 */
//#define DMA_RMPCR1_CH3_TIM2_CH2             ((uint32_t)0x00000500)        /*!< Remap TIM2 channel 2 on DMA1 channel 3 */
//#define DMA_RMPCR1_CH3_TIM16_CH1            ((uint32_t)0x00000700)        /*!< Remap TIM16 channel 1 on DMA1 channel 3 */
//#define DMA_RMPCR1_CH3_TIM16_UP             ((uint32_t)0x00000700)        /*!< Remap TIM16 up on DMA1 channel 3 */
//#define DMA_RMPCR1_CH3_USART1_RX            ((uint32_t)0x00000800)        /*!< Remap USART1 Rx on DMA1 channel 3 */
//#define DMA_RMPCR1_CH3_USART2_RX            ((uint32_t)0x00000900)        /*!< Remap USART2 Rx on DMA1 channel 3 */
//#define DMA_RMPCR1_CH3_USART3_RX            ((uint32_t)0x00000A00)        /*!< Remap USART3 Rx on DMA1 channel 3 */
//#define DMA_RMPCR1_CH3_USART4_RX            ((uint32_t)0x00000B00)        /*!< Remap USART4 Rx on DMA1 channel 3 */
//#define DMA_RMPCR1_CH3_USART5_RX            ((uint32_t)0x00000C00)        /*!< Remap USART5 Rx on DMA1 channel 3 */
//#define DMA_RMPCR1_CH3_USART6_RX            ((uint32_t)0x00000D00)        /*!< Remap USART6 Rx on DMA1 channel 3 */
//#define DMA_RMPCR1_CH3_USART7_RX            ((uint32_t)0x00000E00)        /*!< Remap USART7 Rx on DMA1 channel 3 */
//#define DMA_RMPCR1_CH3_USART8_RX            ((uint32_t)0x00000F00)        /*!< Remap USART8 Rx on DMA1 channel 3 */
//#define DMA_RMPCR1_CH4_TIM7_UP              ((uint32_t)0x00001000)        /*!< Remap TIM7 up on DMA1 channel 4 */
//#define DMA_RMPCR1_CH4_DAC_CH2              ((uint32_t)0x00001000)        /*!< Remap DAC Channel 2 on DMA1 channel 4 */
//#define DMA_RMPCR1_CH4_I2C2_TX              ((uint32_t)0x00002000)        /*!< Remap I2C2 Tx on DMA1 channel 4 */
//#define DMA_RMPCR1_CH4_SPI2_RX              ((uint32_t)0x00003000)        /*!< Remap SPI2 Rx on DMA1 channel 4 */
//#define DMA_RMPCR1_CH4_TIM2_CH4             ((uint32_t)0x00005000)        /*!< Remap TIM2 channel 4 on DMA1 channel 4 */
//#define DMA_RMPCR1_CH4_TIM3_CH1             ((uint32_t)0x00006000)        /*!< Remap TIM3 channel 1 on DMA1 channel 4 */
//#define DMA_RMPCR1_CH4_TIM3_TRIG            ((uint32_t)0x00006000)        /*!< Remap TIM3 Trig on DMA1 channel 4 */
//#define DMA_RMPCR1_CH4_TIM16_CH1            ((uint32_t)0x00007000)        /*!< Remap TIM16 channel 1 on DMA1 channel 4 */
//#define DMA_RMPCR1_CH4_TIM16_UP             ((uint32_t)0x00007000)        /*!< Remap TIM16 up on DMA1 channel 4 */
//#define DMA_RMPCR1_CH4_USART1_TX            ((uint32_t)0x00008000)        /*!< Remap USART1 Tx on DMA1 channel 4 */
//#define DMA_RMPCR1_CH4_USART2_TX            ((uint32_t)0x00009000)        /*!< Remap USART2 Tx on DMA1 channel 4 */
//#define DMA_RMPCR1_CH4_USART3_TX            ((uint32_t)0x0000A000)        /*!< Remap USART3 Tx on DMA1 channel 4 */
//#define DMA_RMPCR1_CH4_USART4_TX            ((uint32_t)0x0000B000)        /*!< Remap USART4 Tx on DMA1 channel 4 */
//#define DMA_RMPCR1_CH4_USART5_TX            ((uint32_t)0x0000C000)        /*!< Remap USART5 Tx on DMA1 channel 4 */
//#define DMA_RMPCR1_CH4_USART6_TX            ((uint32_t)0x0000D000)        /*!< Remap USART6 Tx on DMA1 channel 4 */
//#define DMA_RMPCR1_CH4_USART7_TX            ((uint32_t)0x0000E000)        /*!< Remap USART7 Tx on DMA1 channel 4 */
//#define DMA_RMPCR1_CH4_USART8_TX            ((uint32_t)0x0000F000)        /*!< Remap USART8 Tx on DMA1 channel 4 */
//#define DMA_RMPCR1_CH5_I2C2_RX              ((uint32_t)0x00020000)        /*!< Remap I2C2 Rx on DMA1 channel 5 */
//#define DMA_RMPCR1_CH5_SPI2_TX              ((uint32_t)0x00030000)        /*!< Remap SPI1 Tx on DMA1 channel 5 */
//#define DMA_RMPCR1_CH5_TIM1_CH3             ((uint32_t)0x00040000)        /*!< Remap TIM1 channel 3 on DMA1 channel 5 */
//#define DMA_RMPCR1_CH5_USART1_RX            ((uint32_t)0x00080000)        /*!< Remap USART1 Rx on DMA1 channel 5 */
//#define DMA_RMPCR1_CH5_USART2_RX            ((uint32_t)0x00090000)        /*!< Remap USART2 Rx on DMA1 channel 5 */
//#define DMA_RMPCR1_CH5_USART3_RX            ((uint32_t)0x000A0000)        /*!< Remap USART3 Rx on DMA1 channel 5 */
//#define DMA_RMPCR1_CH5_USART4_RX            ((uint32_t)0x000B0000)        /*!< Remap USART4 Rx on DMA1 channel 5 */
//#define DMA_RMPCR1_CH5_USART5_RX            ((uint32_t)0x000C0000)        /*!< Remap USART5 Rx on DMA1 channel 5 */
//#define DMA_RMPCR1_CH5_USART6_RX            ((uint32_t)0x000D0000)        /*!< Remap USART6 Rx on DMA1 channel 5 */
//#define DMA_RMPCR1_CH5_USART7_RX            ((uint32_t)0x000E0000)        /*!< Remap USART7 Rx on DMA1 channel 5 */
//#define DMA_RMPCR1_CH5_USART8_RX            ((uint32_t)0x000F0000)        /*!< Remap USART8 Rx on DMA1 channel 5 */
//#define DMA_RMPCR1_CH6_I2C1_TX              ((uint32_t)0x00200000)        /*!< Remap I2C1 Tx on DMA1 channel 6 */
//#define DMA_RMPCR1_CH6_SPI2_RX              ((uint32_t)0x00300000)        /*!< Remap SPI2 Rx on DMA1 channel 6 */
//#define DMA_RMPCR1_CH6_TIM1_CH1             ((uint32_t)0x00400000)        /*!< Remap TIM1 channel 1 on DMA1 channel 6 */
//#define DMA_RMPCR1_CH6_TIM1_CH2             ((uint32_t)0x00400000)        /*!< Remap TIM1 channel 2 on DMA1 channel 6 */
//#define DMA_RMPCR1_CH6_TIM1_CH3             ((uint32_t)0x00400000)        /*!< Remap TIM1 channel 3 on DMA1 channel 6 */
//#define DMA_RMPCR1_CH6_TIM3_CH1             ((uint32_t)0x00600000)        /*!< Remap TIM3 channel 1 on DMA1 channel 6 */
//#define DMA_RMPCR1_CH6_TIM3_TRIG            ((uint32_t)0x00600000)        /*!< Remap TIM3 Trig on DMA1 channel 6 */
//#define DMA_RMPCR1_CH6_TIM16_CH1            ((uint32_t)0x00700000)        /*!< Remap TIM16 channel 1 on DMA1 channel 6 */
//#define DMA_RMPCR1_CH6_TIM16_UP             ((uint32_t)0x00700000)        /*!< Remap TIM16 up on DMA1 channel 6 */
//#define DMA_RMPCR1_CH6_USART1_RX            ((uint32_t)0x00800000)        /*!< Remap USART1 Rx on DMA1 channel 6 */
//#define DMA_RMPCR1_CH6_USART2_RX            ((uint32_t)0x00900000)        /*!< Remap USART2 Rx on DMA1 channel 6 */
//#define DMA_RMPCR1_CH6_USART3_RX            ((uint32_t)0x00A00000)        /*!< Remap USART3 Rx on DMA1 channel 6 */
//#define DMA_RMPCR1_CH6_USART4_RX            ((uint32_t)0x00B00000)        /*!< Remap USART4 Rx on DMA1 channel 6 */
//#define DMA_RMPCR1_CH6_USART5_RX            ((uint32_t)0x00C00000)        /*!< Remap USART5 Rx on DMA1 channel 6 */
//#define DMA_RMPCR1_CH6_USART6_RX            ((uint32_t)0x00D00000)        /*!< Remap USART6 Rx on DMA1 channel 6 */
//#define DMA_RMPCR1_CH6_USART7_RX            ((uint32_t)0x00E00000)        /*!< Remap USART7 Rx on DMA1 channel 6 */
//#define DMA_RMPCR1_CH6_USART8_RX            ((uint32_t)0x00F00000)        /*!< Remap USART8 Rx on DMA1 channel 6 */
//#define DMA_RMPCR1_CH7_I2C1_RX              ((uint32_t)0x02000000)        /*!< Remap I2C1 Rx on DMA1 channel 7 */
//#define DMA_RMPCR1_CH7_SPI2_TX              ((uint32_t)0x03000000)        /*!< Remap SPI2 Tx on DMA1 channel 7 */
//#define DMA_RMPCR1_CH7_TIM2_CH2             ((uint32_t)0x05000000)        /*!< Remap TIM2 channel 2 on DMA1 channel 7 */
//#define DMA_RMPCR1_CH7_TIM2_CH4             ((uint32_t)0x05000000)        /*!< Remap TIM2 channel 4 on DMA1 channel 7 */
//#define DMA_RMPCR1_CH7_TIM17_CH1            ((uint32_t)0x07000000)        /*!< Remap TIM17 channel 1 on DMA1 channel 7 */
//#define DMA_RMPCR1_CH7_TIM17_UP             ((uint32_t)0x07000000)        /*!< Remap TIM17 up on DMA1 channel 7 */
//#define DMA_RMPCR1_CH7_USART1_TX            ((uint32_t)0x08000000)        /*!< Remap USART1 Tx on DMA1 channel 7 */
//#define DMA_RMPCR1_CH7_USART2_TX            ((uint32_t)0x09000000)        /*!< Remap USART2 Tx on DMA1 channel 7 */
//#define DMA_RMPCR1_CH7_USART3_TX            ((uint32_t)0x0A000000)        /*!< Remap USART3 Tx on DMA1 channel 7 */
//#define DMA_RMPCR1_CH7_USART4_TX            ((uint32_t)0x0B000000)        /*!< Remap USART4 Tx on DMA1 channel 7 */
//#define DMA_RMPCR1_CH7_USART5_TX            ((uint32_t)0x0C000000)        /*!< Remap USART5 Tx on DMA1 channel 7 */
//#define DMA_RMPCR1_CH7_USART6_TX            ((uint32_t)0x0D000000)        /*!< Remap USART6 Tx on DMA1 channel 7 */
//#define DMA_RMPCR1_CH7_USART7_TX            ((uint32_t)0x0E000000)        /*!< Remap USART7 Tx on DMA1 channel 7 */
//#define DMA_RMPCR1_CH7_USART8_TX            ((uint32_t)0x0F000000)        /*!< Remap USART8 Tx on DMA1 channel 7 */
//
///******************  Bit definition for DMA_RMPCR2 register  ********************/
//#define DMA_RMPCR2_DEFAULT                  ((uint32_t)0x00000000)        /*!< Default remap position for DMA2 */
//#define DMA_RMPCR2_CH1_I2C2_TX              ((uint32_t)0x00000002)        /*!< Remap I2C2 TX on DMA2 channel 1 */
//#define DMA_RMPCR2_CH1_USART1_TX            ((uint32_t)0x00000008)        /*!< Remap USART1 Tx on DMA2 channel 1 */
//#define DMA_RMPCR2_CH1_USART2_TX            ((uint32_t)0x00000009)        /*!< Remap USART2 Tx on DMA2 channel 1 */
//#define DMA_RMPCR2_CH1_USART3_TX            ((uint32_t)0x0000000A)        /*!< Remap USART3 Tx on DMA2 channel 1 */
//#define DMA_RMPCR2_CH1_USART4_TX            ((uint32_t)0x0000000B)        /*!< Remap USART4 Tx on DMA2 channel 1 */
//#define DMA_RMPCR2_CH1_USART5_TX            ((uint32_t)0x0000000C)        /*!< Remap USART5 Tx on DMA2 channel 1 */
//#define DMA_RMPCR2_CH1_USART6_TX            ((uint32_t)0x0000000D)        /*!< Remap USART6 Tx on DMA2 channel 1 */
//#define DMA_RMPCR2_CH1_USART7_TX            ((uint32_t)0x0000000E)        /*!< Remap USART7 Tx on DMA2 channel 1 */
//#define DMA_RMPCR2_CH1_USART8_TX            ((uint32_t)0x0000000F)        /*!< Remap USART8 Tx on DMA2 channel 1 */
//#define DMA_RMPCR2_CH2_I2C2_RX              ((uint32_t)0x00000020)        /*!< Remap I2C2 Rx on DMA2 channel 2 */
//#define DMA_RMPCR2_CH2_USART1_RX            ((uint32_t)0x00000080)        /*!< Remap USART1 Rx on DMA2 channel 2 */
//#define DMA_RMPCR2_CH2_USART2_RX            ((uint32_t)0x00000090)        /*!< Remap USART2 Rx on DMA2 channel 2 */
//#define DMA_RMPCR2_CH2_USART3_RX            ((uint32_t)0x000000A0)        /*!< Remap USART3 Rx on DMA2 channel 2 */
//#define DMA_RMPCR2_CH2_USART4_RX            ((uint32_t)0x000000B0)        /*!< Remap USART4 Rx on DMA2 channel 2 */
//#define DMA_RMPCR2_CH2_USART5_RX            ((uint32_t)0x000000C0)        /*!< Remap USART5 Rx on DMA2 channel 2 */
//#define DMA_RMPCR2_CH2_USART6_RX            ((uint32_t)0x000000D0)        /*!< Remap USART6 Rx on DMA2 channel 2 */
//#define DMA_RMPCR2_CH2_USART7_RX            ((uint32_t)0x000000E0)        /*!< Remap USART7 Rx on DMA2 channel 2 */
//#define DMA_RMPCR2_CH2_USART8_RX            ((uint32_t)0x000000F0)        /*!< Remap USART8 Rx on DMA2 channel 2 */
//#define DMA_RMPCR2_CH3_TIM6_UP              ((uint32_t)0x00000100)        /*!< Remap TIM6 up on DMA2 channel 3 */
//#define DMA_RMPCR2_CH3_DAC_CH1              ((uint32_t)0x00000100)        /*!< Remap DAC channel 1 on DMA2 channel 3 */
//#define DMA_RMPCR2_CH3_SPI1_RX              ((uint32_t)0x00000300)        /*!< Remap SPI1 Rx on DMA2 channel 3 */
//#define DMA_RMPCR2_CH3_USART1_RX            ((uint32_t)0x00000800)        /*!< Remap USART1 Rx on DMA2 channel 3 */
//#define DMA_RMPCR2_CH3_USART2_RX            ((uint32_t)0x00000900)        /*!< Remap USART2 Rx on DMA2 channel 3 */
//#define DMA_RMPCR2_CH3_USART3_RX            ((uint32_t)0x00000A00)        /*!< Remap USART3 Rx on DMA2 channel 3 */
//#define DMA_RMPCR2_CH3_USART4_RX            ((uint32_t)0x00000B00)        /*!< Remap USART4 Rx on DMA2 channel 3 */
//#define DMA_RMPCR2_CH3_USART5_RX            ((uint32_t)0x00000C00)        /*!< Remap USART5 Rx on DMA2 channel 3 */
//#define DMA_RMPCR2_CH3_USART6_RX            ((uint32_t)0x00000D00)        /*!< Remap USART6 Rx on DMA2 channel 3 */
//#define DMA_RMPCR2_CH3_USART7_RX            ((uint32_t)0x00000E00)        /*!< Remap USART7 Rx on DMA2 channel 3 */
//#define DMA_RMPCR2_CH3_USART8_RX            ((uint32_t)0x00000F00)        /*!< Remap USART8 Rx on DMA2 channel 3 */
//#define DMA_RMPCR2_CH4_TIM7_UP              ((uint32_t)0x00001000)        /*!< Remap TIM7 up on DMA2 channel 4 */
//#define DMA_RMPCR2_CH4_DAC_CH2              ((uint32_t)0x00001000)        /*!< Remap DAC channel 2 on DMA2 channel 4 */
//#define DMA_RMPCR2_CH4_SPI1_TX              ((uint32_t)0x00003000)        /*!< Remap SPI1 Tx on DMA2 channel 4 */
//#define DMA_RMPCR2_CH4_USART1_TX            ((uint32_t)0x00008000)        /*!< Remap USART1 Tx on DMA2 channel 4 */
//#define DMA_RMPCR2_CH4_USART2_TX            ((uint32_t)0x00009000)        /*!< Remap USART2 Tx on DMA2 channel 4 */
//#define DMA_RMPCR2_CH4_USART3_TX            ((uint32_t)0x0000A000)        /*!< Remap USART3 Tx on DMA2 channel 4 */
//#define DMA_RMPCR2_CH4_USART4_TX            ((uint32_t)0x0000B000)        /*!< Remap USART4 Tx on DMA2 channel 4 */
//#define DMA_RMPCR2_CH4_USART5_TX            ((uint32_t)0x0000C000)        /*!< Remap USART5 Tx on DMA2 channel 4 */
//#define DMA_RMPCR2_CH4_USART6_TX            ((uint32_t)0x0000D000)        /*!< Remap USART6 Tx on DMA2 channel 4 */
//#define DMA_RMPCR2_CH4_USART7_TX            ((uint32_t)0x0000E000)        /*!< Remap USART7 Tx on DMA2 channel 4 */
//#define DMA_RMPCR2_CH4_USART8_TX            ((uint32_t)0x0000F000)        /*!< Remap USART8 Tx on DMA2 channel 4 */
//#define DMA_RMPCR2_CH5_ADC                  ((uint32_t)0x00010000)        /*!< Remap ADC on DMA2 channel 5 */
//#define DMA_RMPCR2_CH5_USART1_TX            ((uint32_t)0x00080000)        /*!< Remap USART1 Tx on DMA2 channel 5 */
//#define DMA_RMPCR2_CH5_USART2_TX            ((uint32_t)0x00090000)        /*!< Remap USART2 Tx on DMA2 channel 5 */
//#define DMA_RMPCR2_CH5_USART3_TX            ((uint32_t)0x000A0000)        /*!< Remap USART3 Tx on DMA2 channel 5 */
//#define DMA_RMPCR2_CH5_USART4_TX            ((uint32_t)0x000B0000)        /*!< Remap USART4 Tx on DMA2 channel 5 */
//#define DMA_RMPCR2_CH5_USART5_TX            ((uint32_t)0x000C0000)        /*!< Remap USART5 Tx on DMA2 channel 5 */
//#define DMA_RMPCR2_CH5_USART6_TX            ((uint32_t)0x000D0000)        /*!< Remap USART6 Tx on DMA2 channel 5 */
//#define DMA_RMPCR2_CH5_USART7_TX            ((uint32_t)0x000E0000)        /*!< Remap USART7 Tx on DMA2 channel 5 */
//#define DMA_RMPCR2_CH5_USART8_TX            ((uint32_t)0x000F0000)        /*!< Remap USART8 Tx on DMA2 channel 5 */

/******************************************************************************/
/*                                                                            */
/*                 External Interrupt/Event Controller (EXTI)                 */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for EXTI_IMR register  *******************/
#define  EXTI_IMR_MR0                        ((uint32_t)0x00000001)        /*!< Interrupt Mask on line 0  */
#define  EXTI_IMR_MR1                        ((uint32_t)0x00000002)        /*!< Interrupt Mask on line 1  */
#define  EXTI_IMR_MR2                        ((uint32_t)0x00000004)        /*!< Interrupt Mask on line 2  */
#define  EXTI_IMR_MR3                        ((uint32_t)0x00000008)        /*!< Interrupt Mask on line 3  */
#define  EXTI_IMR_MR4                        ((uint32_t)0x00000010)        /*!< Interrupt Mask on line 4  */
#define  EXTI_IMR_MR5                        ((uint32_t)0x00000020)        /*!< Interrupt Mask on line 5  */
#define  EXTI_IMR_MR6                        ((uint32_t)0x00000040)        /*!< Interrupt Mask on line 6  */
#define  EXTI_IMR_MR7                        ((uint32_t)0x00000080)        /*!< Interrupt Mask on line 7  */
#define  EXTI_IMR_MR8                        ((uint32_t)0x00000100)        /*!< Interrupt Mask on line 8  */
#define  EXTI_IMR_MR9                        ((uint32_t)0x00000200)        /*!< Interrupt Mask on line 9  */
#define  EXTI_IMR_MR10                       ((uint32_t)0x00000400)        /*!< Interrupt Mask on line 10 */
#define  EXTI_IMR_MR11                       ((uint32_t)0x00000800)        /*!< Interrupt Mask on line 11 */
#define  EXTI_IMR_MR12                       ((uint32_t)0x00001000)        /*!< Interrupt Mask on line 12 */
#define  EXTI_IMR_MR13                       ((uint32_t)0x00002000)        /*!< Interrupt Mask on line 13 */
#define  EXTI_IMR_MR14                       ((uint32_t)0x00004000)        /*!< Interrupt Mask on line 14 */
#define  EXTI_IMR_MR15                       ((uint32_t)0x00008000)        /*!< Interrupt Mask on line 15 */
#define  EXTI_IMR_MR16                       ((uint32_t)0x00010000)        /*!< Interrupt Mask on line 16 */
#define  EXTI_IMR_MR17                       ((uint32_t)0x00020000)        /*!< Interrupt Mask on line 17 */
#define  EXTI_IMR_MR18                       ((uint32_t)0x00040000)        /*!< Interrupt Mask on line 18 */
#define  EXTI_IMR_MR19                       ((uint32_t)0x00080000)        /*!< Interrupt Mask on line 19 */
#define  EXTI_IMR_MR20                       ((uint32_t)0x00100000)        /*!< Interrupt Mask on line 20 */
#define  EXTI_IMR_MR21                       ((uint32_t)0x00200000)        /*!< Interrupt Mask on line 21 */
#define  EXTI_IMR_MR22                       ((uint32_t)0x00400000)        /*!< Interrupt Mask on line 22 */
#define  EXTI_IMR_MR23                       ((uint32_t)0x00800000)        /*!< Interrupt Mask on line 23 */
#define  EXTI_IMR_MR24                       ((uint32_t)0x01000000)        /*!< Interrupt Mask on line 24 */
#define  EXTI_IMR_MR25                       ((uint32_t)0x02000000)        /*!< Interrupt Mask on line 25 */
#define  EXTI_IMR_MR26                       ((uint32_t)0x04000000)        /*!< Interrupt Mask on line 26 */
#define  EXTI_IMR_MR27                       ((uint32_t)0x08000000)        /*!< Interrupt Mask on line 27 */
#define  EXTI_IMR_MR28                       ((uint32_t)0x10000000)        /*!< Interrupt Mask on line 28 */
#define  EXTI_IMR_MR29                       ((uint32_t)0x20000000)        /*!< Interrupt Mask on line 29 */
#define  EXTI_IMR_MR30                       ((uint32_t)0x40000000)        /*!< Interrupt Mask on line 30 */
#define  EXTI_IMR_MR31                       ((uint32_t)0x80000000)        /*!< Interrupt Mask on line 31 */

/******************  Bit definition for EXTI_EMR register  ********************/
#define  EXTI_EMR_MR0                        ((uint32_t)0x00000001)        /*!< Event Mask on line 0  */
#define  EXTI_EMR_MR1                        ((uint32_t)0x00000002)        /*!< Event Mask on line 1  */
#define  EXTI_EMR_MR2                        ((uint32_t)0x00000004)        /*!< Event Mask on line 2  */
#define  EXTI_EMR_MR3                        ((uint32_t)0x00000008)        /*!< Event Mask on line 3  */
#define  EXTI_EMR_MR4                        ((uint32_t)0x00000010)        /*!< Event Mask on line 4  */
#define  EXTI_EMR_MR5                        ((uint32_t)0x00000020)        /*!< Event Mask on line 5  */
#define  EXTI_EMR_MR6                        ((uint32_t)0x00000040)        /*!< Event Mask on line 6  */
#define  EXTI_EMR_MR7                        ((uint32_t)0x00000080)        /*!< Event Mask on line 7  */
#define  EXTI_EMR_MR8                        ((uint32_t)0x00000100)        /*!< Event Mask on line 8  */
#define  EXTI_EMR_MR9                        ((uint32_t)0x00000200)        /*!< Event Mask on line 9  */
#define  EXTI_EMR_MR10                       ((uint32_t)0x00000400)        /*!< Event Mask on line 10 */
#define  EXTI_EMR_MR11                       ((uint32_t)0x00000800)        /*!< Event Mask on line 11 */
#define  EXTI_EMR_MR12                       ((uint32_t)0x00001000)        /*!< Event Mask on line 12 */
#define  EXTI_EMR_MR13                       ((uint32_t)0x00002000)        /*!< Event Mask on line 13 */
#define  EXTI_EMR_MR14                       ((uint32_t)0x00004000)        /*!< Event Mask on line 14 */
#define  EXTI_EMR_MR15                       ((uint32_t)0x00008000)        /*!< Event Mask on line 15 */
#define  EXTI_EMR_MR16                       ((uint32_t)0x00010000)        /*!< Event Mask on line 16 */
#define  EXTI_EMR_MR17                       ((uint32_t)0x00020000)        /*!< Event Mask on line 17 */
#define  EXTI_EMR_MR18                       ((uint32_t)0x00040000)        /*!< Event Mask on line 18 */
#define  EXTI_EMR_MR19                       ((uint32_t)0x00080000)        /*!< Event Mask on line 19 */
#define  EXTI_EMR_MR20                       ((uint32_t)0x00100000)        /*!< Event Mask on line 20 */
#define  EXTI_EMR_MR21                       ((uint32_t)0x00200000)        /*!< Event Mask on line 21 */
#define  EXTI_EMR_MR22                       ((uint32_t)0x00400000)        /*!< Event Mask on line 22 */
#define  EXTI_EMR_MR23                       ((uint32_t)0x00800000)        /*!< Event Mask on line 23 */
#define  EXTI_EMR_MR24                       ((uint32_t)0x01000000)        /*!< Event Mask on line 24 */
#define  EXTI_EMR_MR25                       ((uint32_t)0x02000000)        /*!< Event Mask on line 25 */
#define  EXTI_EMR_MR26                       ((uint32_t)0x04000000)        /*!< Event Mask on line 26 */
#define  EXTI_EMR_MR27                       ((uint32_t)0x08000000)        /*!< Event Mask on line 27 */
#define  EXTI_EMR_MR28                       ((uint32_t)0x10000000)        /*!< Event Mask on line 28 */
#define  EXTI_EMR_MR29                       ((uint32_t)0x20000000)        /*!< Event Mask on line 29 */
#define  EXTI_EMR_MR30                       ((uint32_t)0x40000000)        /*!< Event Mask on line 30 */
#define  EXTI_EMR_MR31                       ((uint32_t)0x80000000)        /*!< Event Mask on line 31 */

/*******************  Bit definition for EXTI_RTSR register  ******************/
#define  EXTI_RTSR_TR0                       ((uint32_t)0x00000001)        /*!< Rising trigger event configuration bit of line 0 */
#define  EXTI_RTSR_TR1                       ((uint32_t)0x00000002)        /*!< Rising trigger event configuration bit of line 1 */
#define  EXTI_RTSR_TR2                       ((uint32_t)0x00000004)        /*!< Rising trigger event configuration bit of line 2 */
#define  EXTI_RTSR_TR3                       ((uint32_t)0x00000008)        /*!< Rising trigger event configuration bit of line 3 */
#define  EXTI_RTSR_TR4                       ((uint32_t)0x00000010)        /*!< Rising trigger event configuration bit of line 4 */
#define  EXTI_RTSR_TR5                       ((uint32_t)0x00000020)        /*!< Rising trigger event configuration bit of line 5 */
#define  EXTI_RTSR_TR6                       ((uint32_t)0x00000040)        /*!< Rising trigger event configuration bit of line 6 */
#define  EXTI_RTSR_TR7                       ((uint32_t)0x00000080)        /*!< Rising trigger event configuration bit of line 7 */
#define  EXTI_RTSR_TR8                       ((uint32_t)0x00000100)        /*!< Rising trigger event configuration bit of line 8 */
#define  EXTI_RTSR_TR9                       ((uint32_t)0x00000200)        /*!< Rising trigger event configuration bit of line 9 */
#define  EXTI_RTSR_TR10                      ((uint32_t)0x00000400)        /*!< Rising trigger event configuration bit of line 10 */
#define  EXTI_RTSR_TR11                      ((uint32_t)0x00000800)        /*!< Rising trigger event configuration bit of line 11 */
#define  EXTI_RTSR_TR12                      ((uint32_t)0x00001000)        /*!< Rising trigger event configuration bit of line 12 */
#define  EXTI_RTSR_TR13                      ((uint32_t)0x00002000)        /*!< Rising trigger event configuration bit of line 13 */
#define  EXTI_RTSR_TR14                      ((uint32_t)0x00004000)        /*!< Rising trigger event configuration bit of line 14 */
#define  EXTI_RTSR_TR15                      ((uint32_t)0x00008000)        /*!< Rising trigger event configuration bit of line 15 */
#define  EXTI_RTSR_TR16                      ((uint32_t)0x00010000)        /*!< Rising trigger event configuration bit of line 16 */
#define  EXTI_RTSR_TR17                      ((uint32_t)0x00020000)        /*!< Rising trigger event configuration bit of line 17 */
#define  EXTI_RTSR_TR19                      ((uint32_t)0x00080000)        /*!< Rising trigger event configuration bit of line 19 */
//#define  EXTI_RTSR_TR20                      ((uint32_t)0x00100000)        /*!< Rising trigger event configuration bit of line 20 */
#define  EXTI_RTSR_TR21                      ((uint32_t)0x00200000)        /*!< Rising trigger event configuration bit of line 21 */
#define  EXTI_RTSR_TR22                      ((uint32_t)0x00400000)        /*!< Rising trigger event configuration bit of line 22 */

/*******************  Bit definition for EXTI_FTSR register *******************/
#define  EXTI_FTSR_TR0                       ((uint32_t)0x00000001)        /*!< Falling trigger event configuration bit of line 0 */
#define  EXTI_FTSR_TR1                       ((uint32_t)0x00000002)        /*!< Falling trigger event configuration bit of line 1 */
#define  EXTI_FTSR_TR2                       ((uint32_t)0x00000004)        /*!< Falling trigger event configuration bit of line 2 */
#define  EXTI_FTSR_TR3                       ((uint32_t)0x00000008)        /*!< Falling trigger event configuration bit of line 3 */
#define  EXTI_FTSR_TR4                       ((uint32_t)0x00000010)        /*!< Falling trigger event configuration bit of line 4 */
#define  EXTI_FTSR_TR5                       ((uint32_t)0x00000020)        /*!< Falling trigger event configuration bit of line 5 */
#define  EXTI_FTSR_TR6                       ((uint32_t)0x00000040)        /*!< Falling trigger event configuration bit of line 6 */
#define  EXTI_FTSR_TR7                       ((uint32_t)0x00000080)        /*!< Falling trigger event configuration bit of line 7 */
#define  EXTI_FTSR_TR8                       ((uint32_t)0x00000100)        /*!< Falling trigger event configuration bit of line 8 */
#define  EXTI_FTSR_TR9                       ((uint32_t)0x00000200)        /*!< Falling trigger event configuration bit of line 9 */
#define  EXTI_FTSR_TR10                      ((uint32_t)0x00000400)        /*!< Falling trigger event configuration bit of line 10 */
#define  EXTI_FTSR_TR11                      ((uint32_t)0x00000800)        /*!< Falling trigger event configuration bit of line 11 */
#define  EXTI_FTSR_TR12                      ((uint32_t)0x00001000)        /*!< Falling trigger event configuration bit of line 12 */
#define  EXTI_FTSR_TR13                      ((uint32_t)0x00002000)        /*!< Falling trigger event configuration bit of line 13 */
#define  EXTI_FTSR_TR14                      ((uint32_t)0x00004000)        /*!< Falling trigger event configuration bit of line 14 */
#define  EXTI_FTSR_TR15                      ((uint32_t)0x00008000)        /*!< Falling trigger event configuration bit of line 15 */
#define  EXTI_FTSR_TR16                      ((uint32_t)0x00010000)        /*!< Falling trigger event configuration bit of line 16 */
#define  EXTI_FTSR_TR17                      ((uint32_t)0x00020000)        /*!< Falling trigger event configuration bit of line 17 */
#define  EXTI_FTSR_TR19                      ((uint32_t)0x00080000)        /*!< Falling trigger event configuration bit of line 19 */
//#define  EXTI_FTSR_TR20                      ((uint32_t)0x00100000)        /*!< Falling trigger event configuration bit of line 20 */
#define  EXTI_FTSR_TR21                      ((uint32_t)0x00200000)        /*!< Falling trigger event configuration bit of line 21 */
#define  EXTI_FTSR_TR22                      ((uint32_t)0x00400000)        /*!< Falling trigger event configuration bit of line 22 */

/******************* Bit definition for EXTI_SWIER register *******************/
#define  EXTI_SWIER_SWIER0                   ((uint32_t)0x00000001)        /*!< Software Interrupt on line 0  */
#define  EXTI_SWIER_SWIER1                   ((uint32_t)0x00000002)        /*!< Software Interrupt on line 1  */
#define  EXTI_SWIER_SWIER2                   ((uint32_t)0x00000004)        /*!< Software Interrupt on line 2  */
#define  EXTI_SWIER_SWIER3                   ((uint32_t)0x00000008)        /*!< Software Interrupt on line 3  */
#define  EXTI_SWIER_SWIER4                   ((uint32_t)0x00000010)        /*!< Software Interrupt on line 4  */
#define  EXTI_SWIER_SWIER5                   ((uint32_t)0x00000020)        /*!< Software Interrupt on line 5  */
#define  EXTI_SWIER_SWIER6                   ((uint32_t)0x00000040)        /*!< Software Interrupt on line 6  */
#define  EXTI_SWIER_SWIER7                   ((uint32_t)0x00000080)        /*!< Software Interrupt on line 7  */
#define  EXTI_SWIER_SWIER8                   ((uint32_t)0x00000100)        /*!< Software Interrupt on line 8  */
#define  EXTI_SWIER_SWIER9                   ((uint32_t)0x00000200)        /*!< Software Interrupt on line 9  */
#define  EXTI_SWIER_SWIER10                  ((uint32_t)0x00000400)        /*!< Software Interrupt on line 10 */
#define  EXTI_SWIER_SWIER11                  ((uint32_t)0x00000800)        /*!< Software Interrupt on line 11 */
#define  EXTI_SWIER_SWIER12                  ((uint32_t)0x00001000)        /*!< Software Interrupt on line 12 */
#define  EXTI_SWIER_SWIER13                  ((uint32_t)0x00002000)        /*!< Software Interrupt on line 13 */
#define  EXTI_SWIER_SWIER14                  ((uint32_t)0x00004000)        /*!< Software Interrupt on line 14 */
#define  EXTI_SWIER_SWIER15                  ((uint32_t)0x00008000)        /*!< Software Interrupt on line 15 */
#define  EXTI_SWIER_SWIER16                  ((uint32_t)0x00010000)        /*!< Software Interrupt on line 16 */
#define  EXTI_SWIER_SWIER17                  ((uint32_t)0x00020000)        /*!< Software Interrupt on line 17 */
#define  EXTI_SWIER_SWIER19                  ((uint32_t)0x00080000)        /*!< Software Interrupt on line 19 */
//#define  EXTI_SWIER_SWIER20                  ((uint32_t)0x00100000)        /*!< Software Interrupt on line 20 */
#define  EXTI_SWIER_SWIER21                  ((uint32_t)0x00200000)        /*!< Software Interrupt on line 21 */
#define  EXTI_SWIER_SWIER22                  ((uint32_t)0x00400000)        /*!< Software Interrupt on line 22 */

/******************  Bit definition for EXTI_PR register  *********************/
#define  EXTI_PR_PR0                         ((uint32_t)0x00000001)        /*!< Pending bit 0  */
#define  EXTI_PR_PR1                         ((uint32_t)0x00000002)        /*!< Pending bit 1  */
#define  EXTI_PR_PR2                         ((uint32_t)0x00000004)        /*!< Pending bit 2  */
#define  EXTI_PR_PR3                         ((uint32_t)0x00000008)        /*!< Pending bit 3  */
#define  EXTI_PR_PR4                         ((uint32_t)0x00000010)        /*!< Pending bit 4  */
#define  EXTI_PR_PR5                         ((uint32_t)0x00000020)        /*!< Pending bit 5  */
#define  EXTI_PR_PR6                         ((uint32_t)0x00000040)        /*!< Pending bit 6  */
#define  EXTI_PR_PR7                         ((uint32_t)0x00000080)        /*!< Pending bit 7  */
#define  EXTI_PR_PR8                         ((uint32_t)0x00000100)        /*!< Pending bit 8  */
#define  EXTI_PR_PR9                         ((uint32_t)0x00000200)        /*!< Pending bit 9  */
#define  EXTI_PR_PR10                        ((uint32_t)0x00000400)        /*!< Pending bit 10 */
#define  EXTI_PR_PR11                        ((uint32_t)0x00000800)        /*!< Pending bit 11 */
#define  EXTI_PR_PR12                        ((uint32_t)0x00001000)        /*!< Pending bit 12 */
#define  EXTI_PR_PR13                        ((uint32_t)0x00002000)        /*!< Pending bit 13 */
#define  EXTI_PR_PR14                        ((uint32_t)0x00004000)        /*!< Pending bit 14 */
#define  EXTI_PR_PR15                        ((uint32_t)0x00008000)        /*!< Pending bit 15 */
#define  EXTI_PR_PR16                        ((uint32_t)0x00010000)        /*!< Pending bit 16 */
#define  EXTI_PR_PR17                        ((uint32_t)0x00020000)        /*!< Pending bit 17 */
#define  EXTI_PR_PR19                        ((uint32_t)0x00080000)        /*!< Pending bit 19 */
//#define  EXTI_PR_PR20                        ((uint32_t)0x00100000)        /*!< Pending bit 20 */
#define  EXTI_PR_PR21                        ((uint32_t)0x00200000)        /*!< Pending bit 21 */
#define  EXTI_PR_PR22                        ((uint32_t)0x00400000)        /*!< Pending bit 22 */

/******************************************************************************/
/*                                                                            */
/*                      FLASH and Option Bytes Registers                      */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for FLASH_ACR register  ******************/
#define  FLASH_ACR_LATENCY                   ((uint32_t)0x00000001)        /*!< LATENCY bit (Latency) */

#define  FLASH_ACR_PRFTBE                    ((uint32_t)0x00000010)        /*!< Prefetch Buffer Enable */
#define  FLASH_ACR_PRFTBS                    ((uint32_t)0x00000020)        /*!< Prefetch Buffer Status */

/******************  Bit definition for FLASH_KEYR register  ******************/
#define  FLASH_KEYR_FKEYR                    ((uint32_t)0xFFFFFFFF)        /*!< FPEC Key */

/*****************  Bit definition for FLASH_OPTKEYR register  ****************/
#define  FLASH_OPTKEYR_OPTKEYR               ((uint32_t)0xFFFFFFFF)        /*!< Option Byte Key */

/******************  FLASH Keys  **********************************************/
#define FLASH_FKEY1                          ((uint32_t)0x45670123)        /*!< Flash program erase key1 */
#define FLASH_FKEY2                          ((uint32_t)0xCDEF89AB)        /*!< Flash program erase key2: used with FLASH_PEKEY1
                                                                                to unlock the write access to the FPEC. */

#define FLASH_OPTKEY1                        ((uint32_t)0x45670123)        /*!< Flash option key1 */
#define FLASH_OPTKEY2                        ((uint32_t)0xCDEF89AB)        /*!< Flash option key2: used with FLASH_OPTKEY1 to
                                                                                unlock the write access to the option byte block */
#define FLASH_KEY1                                                      FLASH_FKEY1
#define FLASH_KEY2                                                      FLASH_FKEY2
/******************  Bit definition for FLASH_SR register  *******************/
#define  FLASH_SR_BSY                        ((uint32_t)0x00000001)        /*!< Busy */
#define  FLASH_SR_PGERR                      ((uint32_t)0x00000004)        /*!< Programming Error */
#define  FLASH_SR_WRPRTERR                   ((uint32_t)0x00000010)        /*!< Write Protection Error */
#define  FLASH_SR_EOP                        ((uint32_t)0x00000020)        /*!< End of operation */
#define  FLASH_SR_WRPERR                     FLASH_SR_WRPRTERR             /*!< Legacy of Write Protection Error */

/*******************  Bit definition for FLASH_CR register  *******************/
#define  FLASH_CR_PG                         ((uint32_t)0x00000001)        /*!< Programming */
#define  FLASH_CR_PER                        ((uint32_t)0x00000002)        /*!< Page Erase */
#define  FLASH_CR_MER                        ((uint32_t)0x00000004)        /*!< Mass Erase */
#define  FLASH_CR_MAS2K                      ((uint32_t)0x00000008)        /*!< Mass Erase */
#define  FLASH_CR_OPTPG                      ((uint32_t)0x00000010)        /*!< Option Byte Programming */
#define  FLASH_CR_OPTER                      ((uint32_t)0x00000020)        /*!< Option Byte Erase */
#define  FLASH_CR_STRT                       ((uint32_t)0x00000040)        /*!< Start */
#define  FLASH_CR_LOCK                       ((uint32_t)0x00000080)        /*!< Lock */
#define  FLASH_CR_OPTWRE                     ((uint32_t)0x00000200)        /*!< Option Bytes Write Enable */
#define  FLASH_CR_ERRIE                      ((uint32_t)0x00000400)        /*!< Error Interrupt Enable */
#define  FLASH_CR_EOPIE                      ((uint32_t)0x00001000)        /*!< End of operation interrupt enable */
#define  FLASH_CR_OBL_LAUNCH                 ((uint32_t)0x00002000)        /*!< Option Bytes Loader Launch */

/*******************  Bit definition for FLASH_AR register  *******************/
#define  FLASH_AR_FAR                        ((uint32_t)0xFFFFFFFF)        /*!< Flash Address */

/******************  Bit definition for FLASH_OBR register  *******************/
#define  FLASH_OBR_OPTERR                    ((uint32_t)0x00000001)        /*!< Option Byte Error */
#define  FLASH_OBR_RDPRT1                    ((uint32_t)0x00000002)        /*!< Read protection Level bit 1 */
#define  FLASH_OBR_RDPRT2                    ((uint32_t)0x00000004)        /*!< Read protection Level bit 2 */

//#define  FLASH_OBR_USER                      ((uint32_t)0x00003700)        /*!< User Option Bytes */
#define  FLASH_OBR_IWDG_SW                   ((uint32_t)0x00000100)        /*!< IWDG SW */
#define  FLASH_OBR_nRST_STOP                 ((uint32_t)0x00000200)        /*!< nRST_STOP */
#define  FLASH_OBR_nRST_STDBY                ((uint32_t)0x00000400)        /*!< nRST_STDBY */
//#define  FLASH_OBR_nBOOT0                    ((uint32_t)0x00000800)        /*!< nBOOT0 */
#define  FLASH_OBR_nBOOT1                    ((uint32_t)0x00001000)        /*!< nBOOT1 */
#define  FLASH_OBR_VDDA_MONITOR              ((uint32_t)0x00002000)        /*!< VDDA power supply supervisor */
//#define  FLASH_OBR_RAM_PARITY_CHECK          ((uint32_t)0x00004000)        /*!< RAM Parity Check */
//#define  FLASH_OBR_nBOOT0_SW                 ((uint32_t)0x00008000)        /*!< nBOOT0 SW*/
#define  FLASH_OBR_DATA0                     ((uint32_t)0x00FF0000)        /*!< DATA0 */
#define  FLASH_OBR_DATA1                     ((uint32_t)0xFF000000)        /*!< DATA0 */

/* Old BOOT1 bit definition, maintained for legacy purpose */
#define FLASH_OBR_BOOT1                      FLASH_OBR_nBOOT1

/* Old OBR_VDDA bit definition, maintained for legacy purpose */
#define FLASH_OBR_VDDA_ANALOG                FLASH_OBR_VDDA_MONITOR

/******************  Bit definition for FLASH_WRPR register  ******************/
#define  FLASH_WRPR_WRP                      ((uint32_t)0xFFFFFFFF)        /*!< Write Protect */

/*----------------------------------------------------------------------------*/

/******************  Bit definition for OB_RDP register  **********************/
#define  OB_RDP_RDP                          ((uint32_t)0x000000FF)        /*!< Read protection option byte */
#define  OB_RDP_nRDP                         ((uint32_t)0x0000FF00)        /*!< Read protection complemented option byte */

/******************  Bit definition for OB_USER register  *********************/
#define  OB_USER_USER                        ((uint32_t)0x00FF0000)        /*!< User option byte */
#define  OB_USER_nUSER                       ((uint32_t)0xFF000000)        /*!< User complemented option byte */

/******************  Bit definition for OB_WRP0 register  *********************/
#define  OB_WRP0_WRP0                        ((uint32_t)0x000000FF)        /*!< Flash memory write protection option bytes */
#define  OB_WRP0_nWRP0                       ((uint32_t)0x0000FF00)        /*!< Flash memory write protection complemented option bytes */

/******************  Bit definition for OB_WRP1 register  *********************/
#define  OB_WRP1_WRP1                        ((uint32_t)0x00FF0000)        /*!< Flash memory write protection option bytes */
#define  OB_WRP1_nWRP1                       ((uint32_t)0xFF000000)        /*!< Flash memory write protection complemented option bytes */

/******************  Bit definition for OB_WRP2 register  *********************/
#define  OB_WRP2_WRP2                        ((uint32_t)0x000000FF)        /*!< Flash memory write protection option bytes (only for FT32F030X8 devices) */
#define  OB_WRP2_nWRP2                       ((uint32_t)0x0000FF00)        /*!< Flash memory write protection complemented option bytes (only for FT32F030X8 devices) */

/******************  Bit definition for OB_WRP3 register  *********************/
#define  OB_WRP3_WRP3                        ((uint32_t)0x00FF0000)        /*!< Flash memory write protection option bytes (only for FT32F030X8 devices) */
#define  OB_WRP3_nWRP3                       ((uint32_t)0xFF000000)        /*!< Flash memory write protection complemented option bytes (only for FT32F030X8 devices) */

/******************************************************************************/
/*                                                                            */
/*                       General Purpose IOs (GPIO)                           */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for GPIO_MODER register  *****************/
#define GPIO_MODER_MODER0          ((uint32_t)0x00000003)
#define GPIO_MODER_MODER0_0        ((uint32_t)0x00000001)
#define GPIO_MODER_MODER0_1        ((uint32_t)0x00000002)
#define GPIO_MODER_MODER1          ((uint32_t)0x0000000C)
#define GPIO_MODER_MODER1_0        ((uint32_t)0x00000004)
#define GPIO_MODER_MODER1_1        ((uint32_t)0x00000008)
#define GPIO_MODER_MODER2          ((uint32_t)0x00000030)
#define GPIO_MODER_MODER2_0        ((uint32_t)0x00000010)
#define GPIO_MODER_MODER2_1        ((uint32_t)0x00000020)
#define GPIO_MODER_MODER3          ((uint32_t)0x000000C0)
#define GPIO_MODER_MODER3_0        ((uint32_t)0x00000040)
#define GPIO_MODER_MODER3_1        ((uint32_t)0x00000080)
#define GPIO_MODER_MODER4          ((uint32_t)0x00000300)
#define GPIO_MODER_MODER4_0        ((uint32_t)0x00000100)
#define GPIO_MODER_MODER4_1        ((uint32_t)0x00000200)
#define GPIO_MODER_MODER5          ((uint32_t)0x00000C00)
#define GPIO_MODER_MODER5_0        ((uint32_t)0x00000400)
#define GPIO_MODER_MODER5_1        ((uint32_t)0x00000800)
#define GPIO_MODER_MODER6          ((uint32_t)0x00003000)
#define GPIO_MODER_MODER6_0        ((uint32_t)0x00001000)
#define GPIO_MODER_MODER6_1        ((uint32_t)0x00002000)
#define GPIO_MODER_MODER7          ((uint32_t)0x0000C000)
#define GPIO_MODER_MODER7_0        ((uint32_t)0x00004000)
#define GPIO_MODER_MODER7_1        ((uint32_t)0x00008000)
#define GPIO_MODER_MODER8          ((uint32_t)0x00030000)
#define GPIO_MODER_MODER8_0        ((uint32_t)0x00010000)
#define GPIO_MODER_MODER8_1        ((uint32_t)0x00020000)
#define GPIO_MODER_MODER9          ((uint32_t)0x000C0000)
#define GPIO_MODER_MODER9_0        ((uint32_t)0x00040000)
#define GPIO_MODER_MODER9_1        ((uint32_t)0x00080000)
#define GPIO_MODER_MODER10         ((uint32_t)0x00300000)
#define GPIO_MODER_MODER10_0       ((uint32_t)0x00100000)
#define GPIO_MODER_MODER10_1       ((uint32_t)0x00200000)
#define GPIO_MODER_MODER11         ((uint32_t)0x00C00000)
#define GPIO_MODER_MODER11_0       ((uint32_t)0x00400000)
#define GPIO_MODER_MODER11_1       ((uint32_t)0x00800000)
#define GPIO_MODER_MODER12         ((uint32_t)0x03000000)
#define GPIO_MODER_MODER12_0       ((uint32_t)0x01000000)
#define GPIO_MODER_MODER12_1       ((uint32_t)0x02000000)
#define GPIO_MODER_MODER13         ((uint32_t)0x0C000000)
#define GPIO_MODER_MODER13_0       ((uint32_t)0x04000000)
#define GPIO_MODER_MODER13_1       ((uint32_t)0x08000000)
#define GPIO_MODER_MODER14         ((uint32_t)0x30000000)
#define GPIO_MODER_MODER14_0       ((uint32_t)0x10000000)
#define GPIO_MODER_MODER14_1       ((uint32_t)0x20000000)
#define GPIO_MODER_MODER15         ((uint32_t)0xC0000000)
#define GPIO_MODER_MODER15_0       ((uint32_t)0x40000000)
#define GPIO_MODER_MODER15_1       ((uint32_t)0x80000000)

/******************  Bit definition for GPIO_OTYPER register  *****************/
#define GPIO_OTYPER_OT_0           ((uint32_t)0x00000001)
#define GPIO_OTYPER_OT_1           ((uint32_t)0x00000002)
#define GPIO_OTYPER_OT_2           ((uint32_t)0x00000004)
#define GPIO_OTYPER_OT_3           ((uint32_t)0x00000008)
#define GPIO_OTYPER_OT_4           ((uint32_t)0x00000010)
#define GPIO_OTYPER_OT_5           ((uint32_t)0x00000020)
#define GPIO_OTYPER_OT_6           ((uint32_t)0x00000040)
#define GPIO_OTYPER_OT_7           ((uint32_t)0x00000080)
#define GPIO_OTYPER_OT_8           ((uint32_t)0x00000100)
#define GPIO_OTYPER_OT_9           ((uint32_t)0x00000200)
#define GPIO_OTYPER_OT_10          ((uint32_t)0x00000400)
#define GPIO_OTYPER_OT_11          ((uint32_t)0x00000800)
#define GPIO_OTYPER_OT_12          ((uint32_t)0x00001000)
#define GPIO_OTYPER_OT_13          ((uint32_t)0x00002000)
#define GPIO_OTYPER_OT_14          ((uint32_t)0x00004000)
#define GPIO_OTYPER_OT_15          ((uint32_t)0x00008000)

/****************  Bit definition for GPIO_OSPEEDR register  ******************/
#define GPIO_OSPEEDR_OSPEEDR0     ((uint32_t)0x00000003)
#define GPIO_OSPEEDR_OSPEEDR0_0   ((uint32_t)0x00000001)
#define GPIO_OSPEEDR_OSPEEDR0_1   ((uint32_t)0x00000002)
#define GPIO_OSPEEDR_OSPEEDR1     ((uint32_t)0x0000000C)
#define GPIO_OSPEEDR_OSPEEDR1_0   ((uint32_t)0x00000004)
#define GPIO_OSPEEDR_OSPEEDR1_1   ((uint32_t)0x00000008)
#define GPIO_OSPEEDR_OSPEEDR2     ((uint32_t)0x00000030)
#define GPIO_OSPEEDR_OSPEEDR2_0   ((uint32_t)0x00000010)
#define GPIO_OSPEEDR_OSPEEDR2_1   ((uint32_t)0x00000020)
#define GPIO_OSPEEDR_OSPEEDR3     ((uint32_t)0x000000C0)
#define GPIO_OSPEEDR_OSPEEDR3_0   ((uint32_t)0x00000040)
#define GPIO_OSPEEDR_OSPEEDR3_1   ((uint32_t)0x00000080)
#define GPIO_OSPEEDR_OSPEEDR4     ((uint32_t)0x00000300)
#define GPIO_OSPEEDR_OSPEEDR4_0   ((uint32_t)0x00000100)
#define GPIO_OSPEEDR_OSPEEDR4_1   ((uint32_t)0x00000200)
#define GPIO_OSPEEDR_OSPEEDR5     ((uint32_t)0x00000C00)
#define GPIO_OSPEEDR_OSPEEDR5_0   ((uint32_t)0x00000400)
#define GPIO_OSPEEDR_OSPEEDR5_1   ((uint32_t)0x00000800)
#define GPIO_OSPEEDR_OSPEEDR6     ((uint32_t)0x00003000)
#define GPIO_OSPEEDR_OSPEEDR6_0   ((uint32_t)0x00001000)
#define GPIO_OSPEEDR_OSPEEDR6_1   ((uint32_t)0x00002000)
#define GPIO_OSPEEDR_OSPEEDR7     ((uint32_t)0x0000C000)
#define GPIO_OSPEEDR_OSPEEDR7_0   ((uint32_t)0x00004000)
#define GPIO_OSPEEDR_OSPEEDR7_1   ((uint32_t)0x00008000)
#define GPIO_OSPEEDR_OSPEEDR8     ((uint32_t)0x00030000)
#define GPIO_OSPEEDR_OSPEEDR8_0   ((uint32_t)0x00010000)
#define GPIO_OSPEEDR_OSPEEDR8_1   ((uint32_t)0x00020000)
#define GPIO_OSPEEDR_OSPEEDR9     ((uint32_t)0x000C0000)
#define GPIO_OSPEEDR_OSPEEDR9_0   ((uint32_t)0x00040000)
#define GPIO_OSPEEDR_OSPEEDR9_1   ((uint32_t)0x00080000)
#define GPIO_OSPEEDR_OSPEEDR10    ((uint32_t)0x00300000)
#define GPIO_OSPEEDR_OSPEEDR10_0  ((uint32_t)0x00100000)
#define GPIO_OSPEEDR_OSPEEDR10_1  ((uint32_t)0x00200000)
#define GPIO_OSPEEDR_OSPEEDR11    ((uint32_t)0x00C00000)
#define GPIO_OSPEEDR_OSPEEDR11_0  ((uint32_t)0x00400000)
#define GPIO_OSPEEDR_OSPEEDR11_1  ((uint32_t)0x00800000)
#define GPIO_OSPEEDR_OSPEEDR12    ((uint32_t)0x03000000)
#define GPIO_OSPEEDR_OSPEEDR12_0  ((uint32_t)0x01000000)
#define GPIO_OSPEEDR_OSPEEDR12_1  ((uint32_t)0x02000000)
#define GPIO_OSPEEDR_OSPEEDR13    ((uint32_t)0x0C000000)
#define GPIO_OSPEEDR_OSPEEDR13_0  ((uint32_t)0x04000000)
#define GPIO_OSPEEDR_OSPEEDR13_1  ((uint32_t)0x08000000)
#define GPIO_OSPEEDR_OSPEEDR14    ((uint32_t)0x30000000)
#define GPIO_OSPEEDR_OSPEEDR14_0  ((uint32_t)0x10000000)
#define GPIO_OSPEEDR_OSPEEDR14_1  ((uint32_t)0x20000000)
#define GPIO_OSPEEDR_OSPEEDR15    ((uint32_t)0xC0000000)
#define GPIO_OSPEEDR_OSPEEDR15_0  ((uint32_t)0x40000000)
#define GPIO_OSPEEDR_OSPEEDR15_1  ((uint32_t)0x80000000)

/* Old Bit definition for GPIO_OSPEEDR register maintained for legacy purpose */
#define GPIO_OSPEEDER_OSPEEDR0     GPIO_OSPEEDR_OSPEEDR0
#define GPIO_OSPEEDER_OSPEEDR0_0   GPIO_OSPEEDR_OSPEEDR0_0
#define GPIO_OSPEEDER_OSPEEDR0_1   GPIO_OSPEEDR_OSPEEDR0_1
#define GPIO_OSPEEDER_OSPEEDR1     GPIO_OSPEEDR_OSPEEDR1
#define GPIO_OSPEEDER_OSPEEDR1_0   GPIO_OSPEEDR_OSPEEDR1_0
#define GPIO_OSPEEDER_OSPEEDR1_1   GPIO_OSPEEDR_OSPEEDR1_1
#define GPIO_OSPEEDER_OSPEEDR2     GPIO_OSPEEDR_OSPEEDR2
#define GPIO_OSPEEDER_OSPEEDR2_0   GPIO_OSPEEDR_OSPEEDR2_0
#define GPIO_OSPEEDER_OSPEEDR2_1   GPIO_OSPEEDR_OSPEEDR2_1
#define GPIO_OSPEEDER_OSPEEDR3     GPIO_OSPEEDR_OSPEEDR3
#define GPIO_OSPEEDER_OSPEEDR3_0   GPIO_OSPEEDR_OSPEEDR3_0
#define GPIO_OSPEEDER_OSPEEDR3_1   GPIO_OSPEEDR_OSPEEDR3_1
#define GPIO_OSPEEDER_OSPEEDR4     GPIO_OSPEEDR_OSPEEDR4
#define GPIO_OSPEEDER_OSPEEDR4_0   GPIO_OSPEEDR_OSPEEDR4_0
#define GPIO_OSPEEDER_OSPEEDR4_1   GPIO_OSPEEDR_OSPEEDR4_1
#define GPIO_OSPEEDER_OSPEEDR5     GPIO_OSPEEDR_OSPEEDR5
#define GPIO_OSPEEDER_OSPEEDR5_0   GPIO_OSPEEDR_OSPEEDR5_0
#define GPIO_OSPEEDER_OSPEEDR5_1   GPIO_OSPEEDR_OSPEEDR5_1
#define GPIO_OSPEEDER_OSPEEDR6     GPIO_OSPEEDR_OSPEEDR6
#define GPIO_OSPEEDER_OSPEEDR6_0   GPIO_OSPEEDR_OSPEEDR6_0
#define GPIO_OSPEEDER_OSPEEDR6_1   GPIO_OSPEEDR_OSPEEDR6_1
#define GPIO_OSPEEDER_OSPEEDR7     GPIO_OSPEEDR_OSPEEDR7
#define GPIO_OSPEEDER_OSPEEDR7_0   GPIO_OSPEEDR_OSPEEDR7_0
#define GPIO_OSPEEDER_OSPEEDR7_1   GPIO_OSPEEDR_OSPEEDR7_1
#define GPIO_OSPEEDER_OSPEEDR8     GPIO_OSPEEDR_OSPEEDR8
#define GPIO_OSPEEDER_OSPEEDR8_0   GPIO_OSPEEDR_OSPEEDR8_0
#define GPIO_OSPEEDER_OSPEEDR8_1   GPIO_OSPEEDR_OSPEEDR8_1
#define GPIO_OSPEEDER_OSPEEDR9     GPIO_OSPEEDR_OSPEEDR9
#define GPIO_OSPEEDER_OSPEEDR9_0   GPIO_OSPEEDR_OSPEEDR9_0
#define GPIO_OSPEEDER_OSPEEDR9_1   GPIO_OSPEEDR_OSPEEDR9_1
#define GPIO_OSPEEDER_OSPEEDR10    GPIO_OSPEEDR_OSPEEDR10
#define GPIO_OSPEEDER_OSPEEDR10_0  GPIO_OSPEEDR_OSPEEDR10_0
#define GPIO_OSPEEDER_OSPEEDR10_1  GPIO_OSPEEDR_OSPEEDR10_1
#define GPIO_OSPEEDER_OSPEEDR11    GPIO_OSPEEDR_OSPEEDR11
#define GPIO_OSPEEDER_OSPEEDR11_0  GPIO_OSPEEDR_OSPEEDR11_0
#define GPIO_OSPEEDER_OSPEEDR11_1  GPIO_OSPEEDR_OSPEEDR11_1
#define GPIO_OSPEEDER_OSPEEDR12    GPIO_OSPEEDR_OSPEEDR12
#define GPIO_OSPEEDER_OSPEEDR12_0  GPIO_OSPEEDR_OSPEEDR12_0
#define GPIO_OSPEEDER_OSPEEDR12_1  GPIO_OSPEEDR_OSPEEDR12_1
#define GPIO_OSPEEDER_OSPEEDR13    GPIO_OSPEEDR_OSPEEDR13
#define GPIO_OSPEEDER_OSPEEDR13_0  GPIO_OSPEEDR_OSPEEDR13_0
#define GPIO_OSPEEDER_OSPEEDR13_1  GPIO_OSPEEDR_OSPEEDR13_1
#define GPIO_OSPEEDER_OSPEEDR14    GPIO_OSPEEDR_OSPEEDR14
#define GPIO_OSPEEDER_OSPEEDR14_0  GPIO_OSPEEDR_OSPEEDR14_0
#define GPIO_OSPEEDER_OSPEEDR14_1  GPIO_OSPEEDR_OSPEEDR14_1
#define GPIO_OSPEEDER_OSPEEDR15    GPIO_OSPEEDR_OSPEEDR15
#define GPIO_OSPEEDER_OSPEEDR15_0  GPIO_OSPEEDR_OSPEEDR15_0
#define GPIO_OSPEEDER_OSPEEDR15_1  GPIO_OSPEEDR_OSPEEDR15_1

/*******************  Bit definition for GPIO_PUPDR register ******************/
#define GPIO_PUPDR_PUPDR0          ((uint32_t)0x00000003)
#define GPIO_PUPDR_PUPDR0_0        ((uint32_t)0x00000001)
#define GPIO_PUPDR_PUPDR0_1        ((uint32_t)0x00000002)
#define GPIO_PUPDR_PUPDR1          ((uint32_t)0x0000000C)
#define GPIO_PUPDR_PUPDR1_0        ((uint32_t)0x00000004)
#define GPIO_PUPDR_PUPDR1_1        ((uint32_t)0x00000008)
#define GPIO_PUPDR_PUPDR2          ((uint32_t)0x00000030)
#define GPIO_PUPDR_PUPDR2_0        ((uint32_t)0x00000010)
#define GPIO_PUPDR_PUPDR2_1        ((uint32_t)0x00000020)
#define GPIO_PUPDR_PUPDR3          ((uint32_t)0x000000C0)
#define GPIO_PUPDR_PUPDR3_0        ((uint32_t)0x00000040)
#define GPIO_PUPDR_PUPDR3_1        ((uint32_t)0x00000080)
#define GPIO_PUPDR_PUPDR4          ((uint32_t)0x00000300)
#define GPIO_PUPDR_PUPDR4_0        ((uint32_t)0x00000100)
#define GPIO_PUPDR_PUPDR4_1        ((uint32_t)0x00000200)
#define GPIO_PUPDR_PUPDR5          ((uint32_t)0x00000C00)
#define GPIO_PUPDR_PUPDR5_0        ((uint32_t)0x00000400)
#define GPIO_PUPDR_PUPDR5_1        ((uint32_t)0x00000800)
#define GPIO_PUPDR_PUPDR6          ((uint32_t)0x00003000)
#define GPIO_PUPDR_PUPDR6_0        ((uint32_t)0x00001000)
#define GPIO_PUPDR_PUPDR6_1        ((uint32_t)0x00002000)
#define GPIO_PUPDR_PUPDR7          ((uint32_t)0x0000C000)
#define GPIO_PUPDR_PUPDR7_0        ((uint32_t)0x00004000)
#define GPIO_PUPDR_PUPDR7_1        ((uint32_t)0x00008000)
#define GPIO_PUPDR_PUPDR8          ((uint32_t)0x00030000)
#define GPIO_PUPDR_PUPDR8_0        ((uint32_t)0x00010000)
#define GPIO_PUPDR_PUPDR8_1        ((uint32_t)0x00020000)
#define GPIO_PUPDR_PUPDR9          ((uint32_t)0x000C0000)
#define GPIO_PUPDR_PUPDR9_0        ((uint32_t)0x00040000)
#define GPIO_PUPDR_PUPDR9_1        ((uint32_t)0x00080000)
#define GPIO_PUPDR_PUPDR10         ((uint32_t)0x00300000)
#define GPIO_PUPDR_PUPDR10_0       ((uint32_t)0x00100000)
#define GPIO_PUPDR_PUPDR10_1       ((uint32_t)0x00200000)
#define GPIO_PUPDR_PUPDR11         ((uint32_t)0x00C00000)
#define GPIO_PUPDR_PUPDR11_0       ((uint32_t)0x00400000)
#define GPIO_PUPDR_PUPDR11_1       ((uint32_t)0x00800000)
#define GPIO_PUPDR_PUPDR12         ((uint32_t)0x03000000)
#define GPIO_PUPDR_PUPDR12_0       ((uint32_t)0x01000000)
#define GPIO_PUPDR_PUPDR12_1       ((uint32_t)0x02000000)
#define GPIO_PUPDR_PUPDR13         ((uint32_t)0x0C000000)
#define GPIO_PUPDR_PUPDR13_0       ((uint32_t)0x04000000)
#define GPIO_PUPDR_PUPDR13_1       ((uint32_t)0x08000000)
#define GPIO_PUPDR_PUPDR14         ((uint32_t)0x30000000)
#define GPIO_PUPDR_PUPDR14_0       ((uint32_t)0x10000000)
#define GPIO_PUPDR_PUPDR14_1       ((uint32_t)0x20000000)
#define GPIO_PUPDR_PUPDR15         ((uint32_t)0xC0000000)
#define GPIO_PUPDR_PUPDR15_0       ((uint32_t)0x40000000)
#define GPIO_PUPDR_PUPDR15_1       ((uint32_t)0x80000000)

/*******************  Bit definition for GPIO_IDR register  *******************/
#define GPIO_IDR_0                 ((uint32_t)0x00000001)
#define GPIO_IDR_1                 ((uint32_t)0x00000002)
#define GPIO_IDR_2                 ((uint32_t)0x00000004)
#define GPIO_IDR_3                 ((uint32_t)0x00000008)
#define GPIO_IDR_4                 ((uint32_t)0x00000010)
#define GPIO_IDR_5                 ((uint32_t)0x00000020)
#define GPIO_IDR_6                 ((uint32_t)0x00000040)
#define GPIO_IDR_7                 ((uint32_t)0x00000080)
#define GPIO_IDR_8                 ((uint32_t)0x00000100)
#define GPIO_IDR_9                 ((uint32_t)0x00000200)
#define GPIO_IDR_10                ((uint32_t)0x00000400)
#define GPIO_IDR_11                ((uint32_t)0x00000800)
#define GPIO_IDR_12                ((uint32_t)0x00001000)
#define GPIO_IDR_13                ((uint32_t)0x00002000)
#define GPIO_IDR_14                ((uint32_t)0x00004000)
#define GPIO_IDR_15                ((uint32_t)0x00008000)

/******************  Bit definition for GPIO_ODR register  ********************/
#define GPIO_ODR_0                 ((uint32_t)0x00000001)
#define GPIO_ODR_1                 ((uint32_t)0x00000002)
#define GPIO_ODR_2                 ((uint32_t)0x00000004)
#define GPIO_ODR_3                 ((uint32_t)0x00000008)
#define GPIO_ODR_4                 ((uint32_t)0x00000010)
#define GPIO_ODR_5                 ((uint32_t)0x00000020)
#define GPIO_ODR_6                 ((uint32_t)0x00000040)
#define GPIO_ODR_7                 ((uint32_t)0x00000080)
#define GPIO_ODR_8                 ((uint32_t)0x00000100)
#define GPIO_ODR_9                 ((uint32_t)0x00000200)
#define GPIO_ODR_10                ((uint32_t)0x00000400)
#define GPIO_ODR_11                ((uint32_t)0x00000800)
#define GPIO_ODR_12                ((uint32_t)0x00001000)
#define GPIO_ODR_13                ((uint32_t)0x00002000)
#define GPIO_ODR_14                ((uint32_t)0x00004000)
#define GPIO_ODR_15                ((uint32_t)0x00008000)

/****************** Bit definition for GPIO_BSRR register  ********************/
#define GPIO_BSRR_BS_0             ((uint32_t)0x00000001)
#define GPIO_BSRR_BS_1             ((uint32_t)0x00000002)
#define GPIO_BSRR_BS_2             ((uint32_t)0x00000004)
#define GPIO_BSRR_BS_3             ((uint32_t)0x00000008)
#define GPIO_BSRR_BS_4             ((uint32_t)0x00000010)
#define GPIO_BSRR_BS_5             ((uint32_t)0x00000020)
#define GPIO_BSRR_BS_6             ((uint32_t)0x00000040)
#define GPIO_BSRR_BS_7             ((uint32_t)0x00000080)
#define GPIO_BSRR_BS_8             ((uint32_t)0x00000100)
#define GPIO_BSRR_BS_9             ((uint32_t)0x00000200)
#define GPIO_BSRR_BS_10            ((uint32_t)0x00000400)
#define GPIO_BSRR_BS_11            ((uint32_t)0x00000800)
#define GPIO_BSRR_BS_12            ((uint32_t)0x00001000)
#define GPIO_BSRR_BS_13            ((uint32_t)0x00002000)
#define GPIO_BSRR_BS_14            ((uint32_t)0x00004000)
#define GPIO_BSRR_BS_15            ((uint32_t)0x00008000)
#define GPIO_BSRR_BR_0             ((uint32_t)0x00010000)
#define GPIO_BSRR_BR_1             ((uint32_t)0x00020000)
#define GPIO_BSRR_BR_2             ((uint32_t)0x00040000)
#define GPIO_BSRR_BR_3             ((uint32_t)0x00080000)
#define GPIO_BSRR_BR_4             ((uint32_t)0x00100000)
#define GPIO_BSRR_BR_5             ((uint32_t)0x00200000)
#define GPIO_BSRR_BR_6             ((uint32_t)0x00400000)
#define GPIO_BSRR_BR_7             ((uint32_t)0x00800000)
#define GPIO_BSRR_BR_8             ((uint32_t)0x01000000)
#define GPIO_BSRR_BR_9             ((uint32_t)0x02000000)
#define GPIO_BSRR_BR_10            ((uint32_t)0x04000000)
#define GPIO_BSRR_BR_11            ((uint32_t)0x08000000)
#define GPIO_BSRR_BR_12            ((uint32_t)0x10000000)
#define GPIO_BSRR_BR_13            ((uint32_t)0x20000000)
#define GPIO_BSRR_BR_14            ((uint32_t)0x40000000)
#define GPIO_BSRR_BR_15            ((uint32_t)0x80000000)

/****************** Bit definition for GPIO_LCKR register  ********************/
#define GPIO_LCKR_LCK0             ((uint32_t)0x00000001)
#define GPIO_LCKR_LCK1             ((uint32_t)0x00000002)
#define GPIO_LCKR_LCK2             ((uint32_t)0x00000004)
#define GPIO_LCKR_LCK3             ((uint32_t)0x00000008)
#define GPIO_LCKR_LCK4             ((uint32_t)0x00000010)
#define GPIO_LCKR_LCK5             ((uint32_t)0x00000020)
#define GPIO_LCKR_LCK6             ((uint32_t)0x00000040)
#define GPIO_LCKR_LCK7             ((uint32_t)0x00000080)
#define GPIO_LCKR_LCK8             ((uint32_t)0x00000100)
#define GPIO_LCKR_LCK9             ((uint32_t)0x00000200)
#define GPIO_LCKR_LCK10            ((uint32_t)0x00000400)
#define GPIO_LCKR_LCK11            ((uint32_t)0x00000800)
#define GPIO_LCKR_LCK12            ((uint32_t)0x00001000)
#define GPIO_LCKR_LCK13            ((uint32_t)0x00002000)
#define GPIO_LCKR_LCK14            ((uint32_t)0x00004000)
#define GPIO_LCKR_LCK15            ((uint32_t)0x00008000)
#define GPIO_LCKR_LCKK             ((uint32_t)0x00010000)

/****************** Bit definition for GPIO_AFRL register  ********************/
#define GPIO_AFRL_AFR0            ((uint32_t)0x0000000F)
#define GPIO_AFRL_AFR1            ((uint32_t)0x000000F0)
#define GPIO_AFRL_AFR2            ((uint32_t)0x00000F00)
#define GPIO_AFRL_AFR3            ((uint32_t)0x0000F000)
#define GPIO_AFRL_AFR4            ((uint32_t)0x000F0000)
#define GPIO_AFRL_AFR5            ((uint32_t)0x00F00000)
#define GPIO_AFRL_AFR6            ((uint32_t)0x0F000000)
#define GPIO_AFRL_AFR7            ((uint32_t)0xF0000000)

/****************** Bit definition for GPIO_AFRH register  ********************/
#define GPIO_AFRH_AFR8            ((uint32_t)0x0000000F)
#define GPIO_AFRH_AFR9            ((uint32_t)0x000000F0)
#define GPIO_AFRH_AFR10            ((uint32_t)0x00000F00)
#define GPIO_AFRH_AFR11            ((uint32_t)0x0000F000)
#define GPIO_AFRH_AFR12            ((uint32_t)0x000F0000)
#define GPIO_AFRH_AFR13            ((uint32_t)0x00F00000)
#define GPIO_AFRH_AFR14            ((uint32_t)0x0F000000)
#define GPIO_AFRH_AFR15            ((uint32_t)0xF0000000)

/* Old Bit definition for GPIO_AFRL register maintained for legacy purpose ****/
#define GPIO_AFRL_AFRL0            GPIO_AFRL_AFR0
#define GPIO_AFRL_AFRL1            GPIO_AFRL_AFR1
#define GPIO_AFRL_AFRL2            GPIO_AFRL_AFR2
#define GPIO_AFRL_AFRL3            GPIO_AFRL_AFR3
#define GPIO_AFRL_AFRL4            GPIO_AFRL_AFR4
#define GPIO_AFRL_AFRL5            GPIO_AFRL_AFR5
#define GPIO_AFRL_AFRL6            GPIO_AFRL_AFR6
#define GPIO_AFRL_AFRL7            GPIO_AFRL_AFR7

/* Old Bit definition for GPIO_AFRH register maintained for legacy purpose ****/
#define GPIO_AFRH_AFRH0            GPIO_AFRH_AFR8
#define GPIO_AFRH_AFRH1            GPIO_AFRH_AFR9
#define GPIO_AFRH_AFRH2            GPIO_AFRH_AFR10
#define GPIO_AFRH_AFRH3            GPIO_AFRH_AFR11
#define GPIO_AFRH_AFRH4            GPIO_AFRH_AFR12
#define GPIO_AFRH_AFRH5            GPIO_AFRH_AFR13
#define GPIO_AFRH_AFRH6            GPIO_AFRH_AFR14
#define GPIO_AFRH_AFRH7            GPIO_AFRH_AFR15

/****************** Bit definition for GPIO_BRR register  *********************/
#define GPIO_BRR_BR_0              ((uint32_t)0x00000001)
#define GPIO_BRR_BR_1              ((uint32_t)0x00000002)
#define GPIO_BRR_BR_2              ((uint32_t)0x00000004)
#define GPIO_BRR_BR_3              ((uint32_t)0x00000008)
#define GPIO_BRR_BR_4              ((uint32_t)0x00000010)
#define GPIO_BRR_BR_5              ((uint32_t)0x00000020)
#define GPIO_BRR_BR_6              ((uint32_t)0x00000040)
#define GPIO_BRR_BR_7              ((uint32_t)0x00000080)
#define GPIO_BRR_BR_8              ((uint32_t)0x00000100)
#define GPIO_BRR_BR_9              ((uint32_t)0x00000200)
#define GPIO_BRR_BR_10             ((uint32_t)0x00000400)
#define GPIO_BRR_BR_11             ((uint32_t)0x00000800)
#define GPIO_BRR_BR_12             ((uint32_t)0x00001000)
#define GPIO_BRR_BR_13             ((uint32_t)0x00002000)
#define GPIO_BRR_BR_14             ((uint32_t)0x00004000)
#define GPIO_BRR_BR_15             ((uint32_t)0x00008000)

#define GPIO_BRR_BR0               GPIO_BRR_BR_0
#define GPIO_BRR_BR1               GPIO_BRR_BR_1
#define GPIO_BRR_BR2               GPIO_BRR_BR_2
#define GPIO_BRR_BR3               GPIO_BRR_BR_3
#define GPIO_BRR_BR4               GPIO_BRR_BR_4
#define GPIO_BRR_BR5               GPIO_BRR_BR_5
#define GPIO_BRR_BR6               GPIO_BRR_BR_6
#define GPIO_BRR_BR7               GPIO_BRR_BR_7
#define GPIO_BRR_BR8               GPIO_BRR_BR_8
#define GPIO_BRR_BR9               GPIO_BRR_BR_9
#define GPIO_BRR_BR10              GPIO_BRR_BR_10
#define GPIO_BRR_BR11              GPIO_BRR_BR_11
#define GPIO_BRR_BR12              GPIO_BRR_BR_12
#define GPIO_BRR_BR13              GPIO_BRR_BR_13
#define GPIO_BRR_BR14              GPIO_BRR_BR_14
#define GPIO_BRR_BR15              GPIO_BRR_BR_15

/*******************  Bit definition for GPIO_LEDM register  *******************/
#define GPIOA_LEDM_LEDM8                    ((uint32_t)0x00000100)
#define GPIOA_LEDM_LEDM9                    ((uint32_t)0x00000200)
#define GPIOA_LEDM_LEDM10                   ((uint32_t)0x00000400)
#define GPIOA_LEDM_LEDM13                   ((uint32_t)0x00002000)
#define GPIOA_LEDM_LEDM14                   ((uint32_t)0x00004000)
#define GPIOA_LEDM_LEDM15                   ((uint32_t)0x00008000)


#define GPIOB_LEDM_LEDM0                    ((uint32_t)0x00000001)
#define GPIOB_LEDM_LEDM1                    ((uint32_t)0x00000002)
#define GPIOB_LEDM_LEDM3                    ((uint32_t)0x00000008)
#define GPIOB_LEDM_LEDM4                    ((uint32_t)0x00000010)
#define GPIOB_LEDM_LEDM5                    ((uint32_t)0x00000020)
#define GPIOB_LEDM_LEDM6                    ((uint32_t)0x00000040)
#define GPIOB_LEDM_LEDM7                    ((uint32_t)0x00000080)
/******************************************************************************/
/*                                                                            */
/*                   Inter-integrated Circuit Interface (I2C)                 */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for I2C_CR1 register  *******************/
#define  I2C_CR1_PE                          ((uint32_t)0x00000001)        /*!< Peripheral enable */
#define  I2C_CR1_TXIE                        ((uint32_t)0x00000002)        /*!< TX interrupt enable */
#define  I2C_CR1_RXIE                        ((uint32_t)0x00000004)        /*!< RX interrupt enable */
#define  I2C_CR1_ADDRIE                      ((uint32_t)0x00000008)        /*!< Address match interrupt enable */
#define  I2C_CR1_NACKIE                      ((uint32_t)0x00000010)        /*!< NACK received interrupt enable */
#define  I2C_CR1_STOPIE                      ((uint32_t)0x00000020)        /*!< STOP detection interrupt enable */
#define  I2C_CR1_TCIE                        ((uint32_t)0x00000040)        /*!< Transfer complete interrupt enable */
#define  I2C_CR1_ERRIE                       ((uint32_t)0x00000080)        /*!< Errors interrupt enable */
#define  I2C_CR1_DFN                         ((uint32_t)0x00000F00)        /*!< Digital noise filter */
#define  I2C_CR1_ANFOFF                      ((uint32_t)0x00001000)        /*!< Analog noise filter OFF */
//#define  I2C_CR1_SWRST                       ((uint32_t)0x00002000)        /*!< Software reset */
#define  I2C_CR1_TXDMAEN                     ((uint32_t)0x00004000)        /*!< DMA transmission requests enable */
#define  I2C_CR1_RXDMAEN                     ((uint32_t)0x00008000)        /*!< DMA reception requests enable */
#define  I2C_CR1_SBC                         ((uint32_t)0x00010000)        /*!< Slave byte control */
#define  I2C_CR1_NOSTRETCH                   ((uint32_t)0x00020000)        /*!< Clock stretching disable */
#define  I2C_CR1_GCEN                        ((uint32_t)0x00080000)        /*!< General call enable */
#define  I2C_CR1_SMBHEN                      ((uint32_t)0x00100000)        /*!< SMBus host address enable */
#define  I2C_CR1_SMBDEN                      ((uint32_t)0x00200000)        /*!< SMBus device default address enable */
#define  I2C_CR1_ALERTEN                     ((uint32_t)0x00400000)        /*!< SMBus alert enable */
#define  I2C_CR1_PECEN                       ((uint32_t)0x00800000)        /*!< PEC enable */

/******************  Bit definition for I2C_CR2 register  ********************/
#define  I2C_CR2_SADD                        ((uint32_t)0x000003FF)        /*!< Slave address (master mode) */
#define  I2C_CR2_RD_WRN                      ((uint32_t)0x00000400)        /*!< Transfer direction (master mode) */
#define  I2C_CR2_ADD10                       ((uint32_t)0x00000800)        /*!< 10-bit addressing mode (master mode) */
#define  I2C_CR2_HEAD10R                     ((uint32_t)0x00001000)        /*!< 10-bit address header only read direction (master mode) */
#define  I2C_CR2_START                       ((uint32_t)0x00002000)        /*!< START generation */
#define  I2C_CR2_STOP                        ((uint32_t)0x00004000)        /*!< STOP generation (master mode) */
#define  I2C_CR2_NACK                        ((uint32_t)0x00008000)        /*!< NACK generation (slave mode) */
#define  I2C_CR2_NBYTES                      ((uint32_t)0x00FF0000)        /*!< Number of bytes */
#define  I2C_CR2_RELOAD                      ((uint32_t)0x01000000)        /*!< NBYTES reload mode */
#define  I2C_CR2_AUTOEND                     ((uint32_t)0x02000000)        /*!< Automatic end mode (master mode) */
#define  I2C_CR2_PECBYTE                     ((uint32_t)0x04000000)        /*!< Packet error checking byte */

/*******************  Bit definition for I2C_OAR1 register  ******************/
#define  I2C_OAR1_OA1                        ((uint32_t)0x000003FF)        /*!< Interface own address 1 */
#define  I2C_OAR1_OA1MODE                    ((uint32_t)0x00000400)        /*!< Own address 1 10-bit mode */
#define  I2C_OAR1_OA1EN                      ((uint32_t)0x00008000)        /*!< Own address 1 enable */

/*******************  Bit definition for I2C_OAR2 register  ******************/
#define  I2C_OAR2_OA2                        ((uint32_t)0x000000FE)        /*!< Interface own address 2 */
#define  I2C_OAR2_OA2MSK                     ((uint32_t)0x00000700)        /*!< Own address 2 masks */
#define  I2C_OAR2_OA2EN                      ((uint32_t)0x00008000)        /*!< Own address 2 enable */

/*******************  Bit definition for I2C_TIMINGR register *******************/
#define  I2C_TIMINGR_SCLL                    ((uint32_t)0x000000FF)        /*!< SCL low period (master mode) */
#define  I2C_TIMINGR_SCLH                    ((uint32_t)0x0000FF00)        /*!< SCL high period (master mode) */
#define  I2C_TIMINGR_SDADEL                  ((uint32_t)0x000F0000)        /*!< Data hold time */
#define  I2C_TIMINGR_SCLDEL                  ((uint32_t)0x00F00000)        /*!< Data setup time */
#define  I2C_TIMINGR_PRESC                   ((uint32_t)0xF0000000)        /*!< Timings prescaler */

/******************* Bit definition for I2C_TIMEOUTR register *******************/
#define  I2C_TIMEOUTR_TIMEOUTA               ((uint32_t)0x00000FFF)        /*!< Bus timeout A */
#define  I2C_TIMEOUTR_TIDLE                  ((uint32_t)0x00001000)        /*!< Idle clock timeout detection */
#define  I2C_TIMEOUTR_TIMOUTEN               ((uint32_t)0x00008000)        /*!< Clock timeout enable */
#define  I2C_TIMEOUTR_TIMEOUTB               ((uint32_t)0x0FFF0000)        /*!< Bus timeout B*/
#define  I2C_TIMEOUTR_TEXTEN                 ((uint32_t)0x80000000)        /*!< Extended clock timeout enable */

/******************  Bit definition for I2C_ISR register  *********************/
#define  I2C_ISR_TXE                         ((uint32_t)0x00000001)        /*!< Transmit data register empty */
#define  I2C_ISR_TXIS                        ((uint32_t)0x00000002)        /*!< Transmit interrupt status */
#define  I2C_ISR_RXNE                        ((uint32_t)0x00000004)        /*!< Receive data register not empty */
#define  I2C_ISR_ADDR                        ((uint32_t)0x00000008)        /*!< Address matched (slave mode)*/
#define  I2C_ISR_NACKF                       ((uint32_t)0x00000010)        /*!< NACK received flag */
#define  I2C_ISR_STOPF                       ((uint32_t)0x00000020)        /*!< STOP detection flag */
#define  I2C_ISR_TC                          ((uint32_t)0x00000040)        /*!< Transfer complete (master mode) */
#define  I2C_ISR_TCR                         ((uint32_t)0x00000080)        /*!< Transfer complete reload */
#define  I2C_ISR_BERR                        ((uint32_t)0x00000100)        /*!< Bus error */
#define  I2C_ISR_ARLO                        ((uint32_t)0x00000200)        /*!< Arbitration lost */
#define  I2C_ISR_OVR                         ((uint32_t)0x00000400)        /*!< Overrun/Underrun */
#define  I2C_ISR_PECERR                      ((uint32_t)0x00000800)        /*!< PEC error in reception */
#define  I2C_ISR_TIMEOUT                     ((uint32_t)0x00001000)        /*!< Timeout or Tlow detection flag */
#define  I2C_ISR_ALERT                       ((uint32_t)0x00002000)        /*!< SMBus alert */
#define  I2C_ISR_BUSY                        ((uint32_t)0x00008000)        /*!< Bus busy */
#define  I2C_ISR_DIR                         ((uint32_t)0x00010000)        /*!< Transfer direction (slave mode) */
#define  I2C_ISR_ADDCODE                     ((uint32_t)0x00FE0000)        /*!< Address match code (slave mode) */

/******************  Bit definition for I2C_ICR register  *********************/
#define  I2C_ICR_ADDRCF                      ((uint32_t)0x00000008)        /*!< Address matched clear flag */
#define  I2C_ICR_NACKCF                      ((uint32_t)0x00000010)        /*!< NACK clear flag */
#define  I2C_ICR_STOPCF                      ((uint32_t)0x00000020)        /*!< STOP detection clear flag */
#define  I2C_ICR_BERRCF                      ((uint32_t)0x00000100)        /*!< Bus error clear flag */
#define  I2C_ICR_ARLOCF                      ((uint32_t)0x00000200)        /*!< Arbitration lost clear flag */
#define  I2C_ICR_OVRCF                       ((uint32_t)0x00000400)        /*!< Overrun/Underrun clear flag */
#define  I2C_ICR_PECCF                       ((uint32_t)0x00000800)        /*!< PAC error clear flag */
#define  I2C_ICR_TIMOUTCF                    ((uint32_t)0x00001000)        /*!< Timeout clear flag */
#define  I2C_ICR_ALERTCF                     ((uint32_t)0x00002000)        /*!< Alert clear flag */

/******************  Bit definition for I2C_PECR register  *********************/
#define  I2C_PECR_PEC                        ((uint32_t)0x000000FF)       /*!< PEC register */

/******************  Bit definition for I2C_RXDR register  *********************/
#define  I2C_RXDR_RXDATA                     ((uint32_t)0x000000FF)        /*!< 8-bit receive data */

/******************  Bit definition for I2C_TXDR register  *********************/
#define  I2C_TXDR_TXDATA                     ((uint32_t)0x000000FF)        /*!< 8-bit transmit data */

/******************************************************************************/
/*                                                                            */
/*                        Independent WATCHDOG (IWDG)                         */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for IWDG_KR register  ********************/
#define  IWDG_KR_KEY                         ((uint16_t)0xFFFF)            /*!< Key value (write only, read 0000h) */

/*******************  Bit definition for IWDG_PR register  ********************/
#define  IWDG_PR_PR                          ((uint8_t)0x07)               /*!< PR[2:0] (Prescaler divider) */
#define  IWDG_PR_PR_0                        ((uint8_t)0x01)               /*!< Bit 0 */
#define  IWDG_PR_PR_1                        ((uint8_t)0x02)               /*!< Bit 1 */
#define  IWDG_PR_PR_2                        ((uint8_t)0x04)               /*!< Bit 2 */

/*******************  Bit definition for IWDG_RLR register  *******************/
#define  IWDG_RLR_RL                         ((uint16_t)0x0FFF)            /*!< Watchdog counter reload value */

/*******************  Bit definition for IWDG_SR register  ********************/
#define  IWDG_SR_PVU                         ((uint8_t)0x01)               /*!< Watchdog prescaler value update */
#define  IWDG_SR_RVU                         ((uint8_t)0x02)               /*!< Watchdog counter reload value update */
#define  IWDG_SR_WVU                         ((uint8_t)0x04)               /*!< Watchdog counter window value update */

/*******************  Bit definition for IWDG_KR register  ********************/
#define  IWDG_WINR_WIN                         ((uint16_t)0x0FFF)            /*!< Watchdog counter window value */

/******************************************************************************/
/*                                                                            */
/*                          Power Control (PWR)                               */
/*                                                                            */
/******************************************************************************/

/********************  Bit definition for PWR_CR register  ********************/
#define  PWR_CR_LPDS                         ((uint16_t)0x0001)     /*!< Low-power deepsleep/sleep */
#define  PWR_CR_PDDS                         ((uint16_t)0x0002)     /*!< Power Down Deepsleep */
#define  PWR_CR_CWUF                         ((uint16_t)0x0004)     /*!< Clear Wakeup Flag */
#define  PWR_CR_CSBF                         ((uint16_t)0x0008)     /*!< Clear Standby Flag */
#define  PWR_CR_PVDE                         ((uint16_t)0x0010)     /*!< Power Voltage Detector Enable */

#define  PWR_CR_PLS                          ((uint16_t)0x02E0)     /*!< PLS[3] PLS[2:0] bits (PVD Level Selection) */
#define  PWR_CR_PLS_0                        ((uint16_t)0x0020)     /*!< Bit 0 */
#define  PWR_CR_PLS_1                        ((uint16_t)0x0040)     /*!< Bit 1 */
#define  PWR_CR_PLS_2                        ((uint16_t)0x0080)     /*!< Bit 2 */
#define  PWR_CR_PLS_3                        ((uint16_t)0x0200)     /*!< Bit 3 */
#define  PWR_CR_DBP                          ((uint16_t)0x0100)     /*!<       */

/* PVD level configuration */
#define  PWR_CR_PLS_LEV0                     ((uint16_t)0x0000)     /*!< PVD level 0 */
#define  PWR_CR_PLS_LEV1                     ((uint16_t)0x0020)     /*!< PVD level 1 */
#define  PWR_CR_PLS_LEV2                     ((uint16_t)0x0040)     /*!< PVD level 2 */
#define  PWR_CR_PLS_LEV3                     ((uint16_t)0x0060)     /*!< PVD level 3 */
#define  PWR_CR_PLS_LEV4                     ((uint16_t)0x0080)     /*!< PVD level 4 */
#define  PWR_CR_PLS_LEV5                     ((uint16_t)0x00A0)     /*!< PVD level 5 */
#define  PWR_CR_PLS_LEV6                     ((uint16_t)0x00C0)     /*!< PVD level 6 */
#define  PWR_CR_PLS_LEV7                     ((uint16_t)0x00E0)     /*!< PVD level 7 */
#define  PWR_CR_PLS_LEV8                     ((uint16_t)0x0200)     /*!< PVD level 8 */
#define  PWR_CR_PLS_LEV9                     ((uint16_t)0x0220)     /*!< PVD level 9 */
#define  PWR_CR_PLS_LEV10                    ((uint16_t)0x0240)     /*!< PVD level 10 */
#define  PWR_CR_PLS_LEV11                    ((uint16_t)0x0260)     /*!< PVD level 11 */
#define  PWR_CR_PLS_LEV12                    ((uint16_t)0x0280)     /*!< PVD level 12 */
#define  PWR_CR_PLS_LEV13                    ((uint16_t)0x02A0)     /*!< PVD level 13 */
#define  PWR_CR_PLS_LEV14                    ((uint16_t)0x02C0)     /*!< PVD level 14 */
#define  PWR_CR_PLS_LEV15                    ((uint16_t)0x02E0)     /*!< PVD level 15 */


#define  PWR_CR_DBP                          ((uint16_t)0x0100)     /*!< Disable Backup Domain write protection */

/* Old Bit definition maintained for legacy purpose ****/
#define  PWR_CR_LPSDSR                       PWR_CR_LPDS     /*!< Low-power deepsleep */

/*******************  Bit definition for PWR_CSR register  ********************/
#define  PWR_CSR_WUF                         ((uint16_t)0x0001)     /*!< Wakeup Flag */
#define  PWR_CSR_SBF                         ((uint16_t)0x0002)     /*!< Standby Flag */
#define  PWR_CSR_PVDO                        ((uint16_t)0x0004)     /*!< PVD Output */
//#define  PWR_CSR_VREFINTRDY                  ((uint16_t)0x0008)     /*!< Internal voltage reference (VREFINT) ready */

#define  PWR_CSR_EWUP1                       ((uint16_t)0x0100)     /*!< Enable WKUP pin 1 */
#define  PWR_CSR_EWUP2                       ((uint16_t)0x0200)     /*!< Enable WKUP pin 2 */
//#define  PWR_CSR_EWUP3                       ((uint16_t)0x0400)     /*!< Enable WKUP pin 3 */
//#define  PWR_CSR_EWUP4                       ((uint16_t)0x0800)     /*!< Enable WKUP pin 4 */
//#define  PWR_CSR_EWUP5                       ((uint16_t)0x1000)     /*!< Enable WKUP pin 5 */
//#define  PWR_CSR_EWUP6                       ((uint16_t)0x2000)     /*!< Enable WKUP pin 6 */
//#define  PWR_CSR_EWUP7                       ((uint16_t)0x4000)     /*!< Enable WKUP pin 7 */
//#define  PWR_CSR_EWUP8                       ((uint16_t)0x8000)     /*!< Enable WKUP pin 8 */

/* Old Bit definition maintained for legacy purpose ****/
//#define  PWR_CSR_VREFINTRDYF                 PWR_CSR_VREFINTRDY     /*!< Internal voltage reference (VREFINT) ready flag */
/******************************************************************************/
/*                                                                            */
/*                         Reset and Clock Control                            */
/*                                                                            */
/******************************************************************************/

/********************  Bit definition for RCC_CR register  ********************/
#define  RCC_CR_HSION                        ((uint32_t)0x00000001)        /*!< Internal High Speed clock enable */
#define  RCC_CR_HSIRDY                       ((uint32_t)0x00000002)        /*!< Internal High Speed clock ready flag */
#define  RCC_CR_HSITRIM                      ((uint32_t)0x000000F8)        /*!< Internal High Speed clock trimming */
#define  RCC_CR_HSICAL                       ((uint32_t)0x0000FF00)        /*!< Internal High Speed clock Calibration */
#define  RCC_CR_HSEON                        ((uint32_t)0x00010000)        /*!< External High Speed clock enable */
#define  RCC_CR_HSERDY                       ((uint32_t)0x00020000)        /*!< External High Speed clock ready flag */
#define  RCC_CR_HSEBYP                       ((uint32_t)0x00040000)        /*!< External High Speed clock Bypass */
#define  RCC_CR_CSSON                        ((uint32_t)0x00080000)        /*!< Clock Security System enable */
#define  RCC_CR_PLLON                        ((uint32_t)0x01000000)        /*!< PLL enable */
#define  RCC_CR_PLLRDY                       ((uint32_t)0x02000000)        /*!< PLL clock ready flag */

/*******************  Bit definition for RCC_CFGR register  *******************/
#define  RCC_CFGR_SW                         ((uint32_t)0x00000003)        /*!< SW[1:0] bits (System clock Switch) */
#define  RCC_CFGR_SW_0                       ((uint32_t)0x00000001)        /*!< Bit 0 */
#define  RCC_CFGR_SW_1                       ((uint32_t)0x00000002)        /*!< Bit 1 */
/* SW configuration */
#define  RCC_CFGR_SW_HSI                     ((uint32_t)0x00000000)        /*!< HSI selected as system clock */
#define  RCC_CFGR_SW_HSE                     ((uint32_t)0x00000001)        /*!< HSE selected as system clock */
#define  RCC_CFGR_SW_PLL                     ((uint32_t)0x00000002)        /*!< PLL selected as system clock */
#define  RCC_CFGR_SW_HSI48                   ((uint32_t)0x00000003)        /*!< HSI48 selected as system clock */

#define  RCC_CFGR_SWS                        ((uint32_t)0x0000000C)        /*!< SWS[1:0] bits (System Clock Switch Status) */
#define  RCC_CFGR_SWS_0                      ((uint32_t)0x00000004)        /*!< Bit 0 */
#define  RCC_CFGR_SWS_1                      ((uint32_t)0x00000008)        /*!< Bit 1 */
/* SWS configuration */
#define  RCC_CFGR_SWS_HSI                    ((uint32_t)0x00000000)        /*!< HSI oscillator used as system clock */
#define  RCC_CFGR_SWS_HSE                    ((uint32_t)0x00000004)        /*!< HSE oscillator used as system clock */
#define  RCC_CFGR_SWS_PLL                    ((uint32_t)0x00000008)        /*!< PLL used as system clock */
#define  RCC_CFGR_SWS_HSI48                  ((uint32_t)0x0000000C)        /*!< HSI48 used as system clock */

#define  RCC_CFGR_HPRE                       ((uint32_t)0x000000F0)        /*!< HPRE[3:0] bits (AHB prescaler) */
#define  RCC_CFGR_HPRE_0                     ((uint32_t)0x00000010)        /*!< Bit 0 */
#define  RCC_CFGR_HPRE_1                     ((uint32_t)0x00000020)        /*!< Bit 1 */
#define  RCC_CFGR_HPRE_2                     ((uint32_t)0x00000040)        /*!< Bit 2 */
#define  RCC_CFGR_HPRE_3                     ((uint32_t)0x00000080)        /*!< Bit 3 */
/* HPRE configuration */
#define  RCC_CFGR_HPRE_DIV1                  ((uint32_t)0x00000000)        /*!< SYSCLK not divided */
#define  RCC_CFGR_HPRE_DIV2                  ((uint32_t)0x00000080)        /*!< SYSCLK divided by 2 */
#define  RCC_CFGR_HPRE_DIV4                  ((uint32_t)0x00000090)        /*!< SYSCLK divided by 4 */
#define  RCC_CFGR_HPRE_DIV8                  ((uint32_t)0x000000A0)        /*!< SYSCLK divided by 8 */
#define  RCC_CFGR_HPRE_DIV16                 ((uint32_t)0x000000B0)        /*!< SYSCLK divided by 16 */
#define  RCC_CFGR_HPRE_DIV64                 ((uint32_t)0x000000C0)        /*!< SYSCLK divided by 64 */
#define  RCC_CFGR_HPRE_DIV128                ((uint32_t)0x000000D0)        /*!< SYSCLK divided by 128 */
#define  RCC_CFGR_HPRE_DIV256                ((uint32_t)0x000000E0)        /*!< SYSCLK divided by 256 */
#define  RCC_CFGR_HPRE_DIV512                ((uint32_t)0x000000F0)        /*!< SYSCLK divided by 512 */

#define  RCC_CFGR_PPRE                       ((uint32_t)0x00000700)        /*!< PRE[2:0] bits (APB prescaler) */
#define  RCC_CFGR_PPRE_0                     ((uint32_t)0x00000100)        /*!< Bit 0 */
#define  RCC_CFGR_PPRE_1                     ((uint32_t)0x00000200)        /*!< Bit 1 */
#define  RCC_CFGR_PPRE_2                     ((uint32_t)0x00000400)        /*!< Bit 2 */
/* PPRE configuration */
#define  RCC_CFGR_PPRE_DIV1                  ((uint32_t)0x00000000)        /*!< HCLK not divided */
#define  RCC_CFGR_PPRE_DIV2                  ((uint32_t)0x00000400)        /*!< HCLK divided by 2 */
#define  RCC_CFGR_PPRE_DIV4                  ((uint32_t)0x00000500)        /*!< HCLK divided by 4 */
#define  RCC_CFGR_PPRE_DIV8                  ((uint32_t)0x00000600)        /*!< HCLK divided by 8 */
#define  RCC_CFGR_PPRE_DIV16                 ((uint32_t)0x00000700)        /*!< HCLK divided by 16 */

#define  RCC_CFGR_ADCPRE                     ((uint32_t)0x00004000)        /*!< ADC prescaler: Obsolete. Proper ADC clock selection is
                                                                                done inside the ADC_CFGR2 */

#define  RCC_CFGR_PLLSRC                     ((uint32_t)0x00018000)        /*!< PLL entry clock source */
#define  RCC_CFGR_PLLSRC_0                   ((uint32_t)0x00008000)        /*!< Bit 0 (available only in the FT32F030X8 devices) */
#define  RCC_CFGR_PLLSRC_1                   ((uint32_t)0x00010000)        /*!< Bit 1 */

#define  RCC_CFGR_PLLSRC_PREDIV1             ((uint32_t)0x00010000)        /*!< PREDIV1 clock selected as PLL entry clock source;
                                                                                Old PREDIV1 bit definition, maintained for legacy purpose */
#define  RCC_CFGR_PLLSRC_HSI_DIV2            ((uint32_t)0x00000000)        /*!< HSI clock divided by 2 selected as PLL entry clock source */
#define  RCC_CFGR_PLLSRC_HSI_PREDIV          ((uint32_t)0x00008000)        /*!< HSI PREDIV clock selected as PLL entry clock source
                                                                                (This bit and configuration is only available for FT32F030X8 devices)*/
#define  RCC_CFGR_PLLSRC_HSE_PREDIV          ((uint32_t)0x00010000)        /*!< HSE PREDIV clock selected as PLL entry clock source */
#define  RCC_CFGR_PLLSRC_HSI48_PREDIV        ((uint32_t)0x00018000)        /*!< HSI48 PREDIV clock selected as PLL entry clock source */

#define  RCC_CFGR_PLLXTPRE                   ((uint32_t)0x00020000)        /*!< HSE divider for PLL entry */
#define  RCC_CFGR_PLLXTPRE_PREDIV1           ((uint32_t)0x00000000)        /*!< PREDIV1 clock not divided for PLL entry */
#define  RCC_CFGR_PLLXTPRE_PREDIV1_Div2      ((uint32_t)0x00020000)        /*!< PREDIV1 clock divided by 2 for PLL entry */

/*!< Old bit definition maintained for legacy purposes */
#define  RCC_CFGR_PLLSRC_HSI_Div2            RCC_CFGR_PLLSRC_HSI_DIV2

/* PLLMUL configuration */
#define  RCC_CFGR_PLLMUL                    ((uint32_t)0x003C0000)        /*!< PLLMUL[3:0] bits (PLL multiplication factor) */
#define  RCC_CFGR_PLLMUL_0                  ((uint32_t)0x00040000)        /*!< Bit 0 */
#define  RCC_CFGR_PLLMUL_1                  ((uint32_t)0x00080000)        /*!< Bit 1 */
#define  RCC_CFGR_PLLMUL_2                  ((uint32_t)0x00100000)        /*!< Bit 2 */
#define  RCC_CFGR_PLLMUL_3                  ((uint32_t)0x00200000)        /*!< Bit 3 */

#define  RCC_CFGR_PLLMUL2                   ((uint32_t)0x00000000)        /*!< PLL input clock*2 */
#define  RCC_CFGR_PLLMUL3                   ((uint32_t)0x00040000)        /*!< PLL input clock*3 */
#define  RCC_CFGR_PLLMUL4                   ((uint32_t)0x00080000)        /*!< PLL input clock*4 */
#define  RCC_CFGR_PLLMUL5                   ((uint32_t)0x000C0000)        /*!< PLL input clock*5 */
#define  RCC_CFGR_PLLMUL6                   ((uint32_t)0x00100000)        /*!< PLL input clock*6 */
#define  RCC_CFGR_PLLMUL7                   ((uint32_t)0x00140000)        /*!< PLL input clock*7 */
#define  RCC_CFGR_PLLMUL8                   ((uint32_t)0x00180000)        /*!< PLL input clock*8 */
#define  RCC_CFGR_PLLMUL9                   ((uint32_t)0x001C0000)        /*!< PLL input clock*9 */
#define  RCC_CFGR_PLLMUL10                  ((uint32_t)0x00200000)        /*!< PLL input clock10 */
#define  RCC_CFGR_PLLMUL11                  ((uint32_t)0x00240000)        /*!< PLL input clock*11 */
#define  RCC_CFGR_PLLMUL12                  ((uint32_t)0x00280000)        /*!< PLL input clock*12 */
#define  RCC_CFGR_PLLMUL13                  ((uint32_t)0x002C0000)        /*!< PLL input clock*13 */
#define  RCC_CFGR_PLLMUL14                  ((uint32_t)0x00300000)        /*!< PLL input clock*14 */
#define  RCC_CFGR_PLLMUL15                  ((uint32_t)0x00340000)        /*!< PLL input clock*15 */
#define  RCC_CFGR_PLLMUL16                  ((uint32_t)0x00380000)        /*!< PLL input clock*16 */

/* Old PLLMUL configuration bit definition maintained for legacy purposes */
#define  RCC_CFGR_PLLMULL                    RCC_CFGR_PLLMUL        /*!< PLLMUL[3:0] bits (PLL multiplication factor) */
#define  RCC_CFGR_PLLMULL_0                  RCC_CFGR_PLLMUL_0        /*!< Bit 0 */
#define  RCC_CFGR_PLLMULL_1                  RCC_CFGR_PLLMUL_1        /*!< Bit 1 */
#define  RCC_CFGR_PLLMULL_2                  RCC_CFGR_PLLMUL_2        /*!< Bit 2 */
#define  RCC_CFGR_PLLMULL_3                  RCC_CFGR_PLLMUL_3       /*!< Bit 3 */

#define  RCC_CFGR_PLLMULL2                   RCC_CFGR_PLLMUL2       /*!< PLL input clock*2 */
#define  RCC_CFGR_PLLMULL3                   RCC_CFGR_PLLMUL3        /*!< PLL input clock*3 */
#define  RCC_CFGR_PLLMULL4                   RCC_CFGR_PLLMUL4        /*!< PLL input clock*4 */
#define  RCC_CFGR_PLLMULL5                   RCC_CFGR_PLLMUL5        /*!< PLL input clock*5 */
#define  RCC_CFGR_PLLMULL6                   RCC_CFGR_PLLMUL6        /*!< PLL input clock*6 */
#define  RCC_CFGR_PLLMULL7                   RCC_CFGR_PLLMUL7        /*!< PLL input clock*7 */
#define  RCC_CFGR_PLLMULL8                   RCC_CFGR_PLLMUL8        /*!< PLL input clock*8 */
#define  RCC_CFGR_PLLMULL9                   RCC_CFGR_PLLMUL9        /*!< PLL input clock*9 */
#define  RCC_CFGR_PLLMULL10                  RCC_CFGR_PLLMUL10        /*!< PLL input clock10 */
#define  RCC_CFGR_PLLMULL11                  RCC_CFGR_PLLMUL11        /*!< PLL input clock*11 */
#define  RCC_CFGR_PLLMULL12                  RCC_CFGR_PLLMUL12        /*!< PLL input clock*12 */
#define  RCC_CFGR_PLLMULL13                  RCC_CFGR_PLLMUL13        /*!< PLL input clock*13 */
#define  RCC_CFGR_PLLMULL14                  RCC_CFGR_PLLMUL14        /*!< PLL input clock*14 */
#define  RCC_CFGR_PLLMULL15                  RCC_CFGR_PLLMUL15        /*!< PLL input clock*15 */
#define  RCC_CFGR_PLLMULL16                  RCC_CFGR_PLLMUL16        /*!< PLL input clock*16 */

#define  RCC_CFGR_MCO                        ((uint32_t)0x0F000000)        /*!< MCO[2:0] bits (Microcontroller Clock Output) */
#define  RCC_CFGR_MCO_0                      ((uint32_t)0x01000000)        /*!< Bit 0 */
#define  RCC_CFGR_MCO_1                      ((uint32_t)0x02000000)        /*!< Bit 1 */
#define  RCC_CFGR_MCO_2                      ((uint32_t)0x04000000)        /*!< Bit 2 */
#define  RCC_CFGR_MCO_3                      ((uint32_t)0x08000000)        /*!< Bit 3 */
/* MCO configuration */
#define  RCC_CFGR_MCO_NOCLOCK                ((uint32_t)0x00000000)        /*!< No clock */
#define  RCC_CFGR_MCO_HSI14                  ((uint32_t)0x01000000)        /*!< HSI14 clock selected as MCO source */
#define  RCC_CFGR_MCO_LSI                    ((uint32_t)0x02000000)        /*!< LSI clock selected as MCO source */
#define  RCC_CFGR_MCO_LSE                    ((uint32_t)0x03000000)        /*!< LSE clock selected as MCO source */
#define  RCC_CFGR_MCO_SYSCLK                 ((uint32_t)0x04000000)        /*!< System clock selected as MCO source */
#define  RCC_CFGR_MCO_HSI                    ((uint32_t)0x05000000)        /*!< HSI clock selected as MCO source */
#define  RCC_CFGR_MCO_HSE                    ((uint32_t)0x06000000)        /*!< HSE clock selected as MCO source  */
#define  RCC_CFGR_MCO_PLL                    ((uint32_t)0x07000000)        /*!< PLL clock selected as MCO source */
#define  RCC_CFGR_MCO_HSI48                  ((uint32_t)0x08000000)        /*!< HSI48 clock selected as MCO source */

#define  RCC_CFGR_MCO_PRE                    ((uint32_t)0x70000000)        /*!< MCO prescaler*/
#define  RCC_CFGR_MCO_PRE_1                  ((uint32_t)0x00000000)        /*!< MCO is divided by 1*/
#define  RCC_CFGR_MCO_PRE_2                  ((uint32_t)0x10000000)        /*!< MCO is divided by 2*/
#define  RCC_CFGR_MCO_PRE_4                  ((uint32_t)0x20000000)        /*!< MCO is divided by 4*/
#define  RCC_CFGR_MCO_PRE_8                  ((uint32_t)0x30000000)        /*!< MCO is divided by 8*/
#define  RCC_CFGR_MCO_PRE_16                 ((uint32_t)0x40000000)        /*!< MCO is divided by 16*/
#define  RCC_CFGR_MCO_PRE_32                 ((uint32_t)0x50000000)        /*!< MCO is divided by 32*/
#define  RCC_CFGR_MCO_PRE_64                 ((uint32_t)0x60000000)        /*!< MCO is divided by 64*/
#define  RCC_CFGR_MCO_PRE_128                ((uint32_t)0x70000000)        /*!< MCO is divided by 128*/

#define  RCC_CFGR_MCOPRE                     RCC_CFGR_MCO_PRE            /*!< MCO prescaler*/
#define  RCC_CFGR_MCOPRE_1                   RCC_CFGR_MCO_PRE_1          /*!< MCO is divided by 1*/
#define  RCC_CFGR_MCOPRE_2                   RCC_CFGR_MCO_PRE_2          /*!< MCO is divided by 2*/
#define  RCC_CFGR_MCOPRE_4                   RCC_CFGR_MCO_PRE_4          /*!< MCO is divided by 4*/
#define  RCC_CFGR_MCOPRE_8                   RCC_CFGR_MCO_PRE_8          /*!< MCO is divided by 8*/
#define  RCC_CFGR_MCOPRE_16                  RCC_CFGR_MCO_PRE_16         /*!< MCO is divided by 16*/
#define  RCC_CFGR_MCOPRE_32                  RCC_CFGR_MCO_PRE_32         /*!< MCO is divided by 32*/
#define  RCC_CFGR_MCOPRE_64                  RCC_CFGR_MCO_PRE_64         /*!< MCO is divided by 64*/
#define  RCC_CFGR_MCOPRE_128                 RCC_CFGR_MCO_PRE_128        /*!< MCO is divided by 128*/

#define  RCC_CFGR_PLLNODIV                   ((uint32_t)0x80000000)        /*!< PLL is not divided to MCO */

/*******************  Bit definition for RCC_CIR register  ********************/
#define  RCC_CIR_LSIRDYF                     ((uint32_t)0x00000001)        /*!< LSI Ready Interrupt flag */
#define  RCC_CIR_LSERDYF                     ((uint32_t)0x00000002)        /*!< LSE Ready Interrupt flag */
#define  RCC_CIR_HSIRDYF                     ((uint32_t)0x00000004)        /*!< HSI Ready Interrupt flag */
#define  RCC_CIR_HSERDYF                     ((uint32_t)0x00000008)        /*!< HSE Ready Interrupt flag */
#define  RCC_CIR_PLLRDYF                     ((uint32_t)0x00000010)        /*!< PLL Ready Interrupt flag */
#define  RCC_CIR_HSI14RDYF                   ((uint32_t)0x00000020)        /*!< HSI14 Ready Interrupt flag */
//#define  RCC_CIR_HSI48RDYF                   ((uint32_t)0x00000040)        /*!< HSI48 Ready Interrupt flag */
#define  RCC_CIR_CSSF                        ((uint32_t)0x00000080)        /*!< Clock Security System Interrupt flag */
#define  RCC_CIR_LSIRDYIE                    ((uint32_t)0x00000100)        /*!< LSI Ready Interrupt Enable */
#define  RCC_CIR_LSERDYIE                    ((uint32_t)0x00000200)        /*!< LSE Ready Interrupt Enable */
#define  RCC_CIR_HSIRDYIE                    ((uint32_t)0x00000400)        /*!< HSI Ready Interrupt Enable */
#define  RCC_CIR_HSERDYIE                    ((uint32_t)0x00000800)        /*!< HSE Ready Interrupt Enable */
#define  RCC_CIR_PLLRDYIE                    ((uint32_t)0x00001000)        /*!< PLL Ready Interrupt Enable */
#define  RCC_CIR_HSI14RDYIE                  ((uint32_t)0x00002000)        /*!< HSI14 Ready Interrupt Enable */
#define  RCC_CIR_HSI48RDYIE                  ((uint32_t)0x00004000)        /*!< HSI48 Ready Interrupt Enable */
#define  RCC_CIR_LSIRDYC                     ((uint32_t)0x00010000)        /*!< LSI Ready Interrupt Clear */
#define  RCC_CIR_LSERDYC                     ((uint32_t)0x00020000)        /*!< LSE Ready Interrupt Clear */
#define  RCC_CIR_HSIRDYC                     ((uint32_t)0x00040000)        /*!< HSI Ready Interrupt Clear */
#define  RCC_CIR_HSERDYC                     ((uint32_t)0x00080000)        /*!< HSE Ready Interrupt Clear */
#define  RCC_CIR_PLLRDYC                     ((uint32_t)0x00100000)        /*!< PLL Ready Interrupt Clear */
#define  RCC_CIR_HSI14RDYC                   ((uint32_t)0x00200000)        /*!< HSI14 Ready Interrupt Clear */
#define  RCC_CIR_HSI48RDYC                   ((uint32_t)0x00400000)        /*!< HSI48 Ready Interrupt Clear */
#define  RCC_CIR_CSSC                        ((uint32_t)0x00800000)        /*!< Clock Security System Interrupt Clear */

/*****************  Bit definition for RCC_APB2RSTR register  *****************/
#define  RCC_APB2RSTR_SYSCFGRST              ((uint32_t)0x00000001)        /*!< SYSCFG clock reset */
//#define  RCC_APB2RSTR_USART8RST              ((uint32_t)0x00000080)        /*!< USART8 clock reset */
//#define  RCC_APB2RSTR_USART7RST              ((uint32_t)0x00000040)        /*!< USART7 clock reset */
//#define  RCC_APB2RSTR_USART6RST              ((uint32_t)0x00000020)        /*!< USART6 clock reset */
#define  RCC_APB2RSTR_ADCRST                 ((uint32_t)0x00000200)        /*!< ADC clock reset */
#define  RCC_APB2RSTR_TIM1RST                ((uint32_t)0x00000800)        /*!< TIM1 clock reset */
#define  RCC_APB2RSTR_SPI1RST                ((uint32_t)0x00001000)        /*!< SPI1 clock reset */
#define  RCC_APB2RSTR_USART1RST              ((uint32_t)0x00004000)        /*!< USART1 clock reset */
#define  RCC_APB2RSTR_TIM15RST               ((uint32_t)0x00010000)        /*!< TIM15 clock reset */
#define  RCC_APB2RSTR_TIM16RST               ((uint32_t)0x00020000)        /*!< TIM16 clock reset */
#define  RCC_APB2RSTR_TIM17RST               ((uint32_t)0x00040000)        /*!< TIM17 clock reset */
#define  RCC_APB2RSTR_DBGMCURST              ((uint32_t)0x00400000)        /*!< DBGMCU clock reset */

/* Old ADC1 clock reset bit definition maintained for legacy purpose */
#define  RCC_APB2RSTR_ADC1RST                RCC_APB2RSTR_ADCRST

/*****************  Bit definition for RCC_APB1RSTR register  *****************/
//#define  RCC_APB1RSTR_TIM2RST                ((uint32_t)0x00000001)        /*!< Timer 2 clock reset */
#define  RCC_APB1RSTR_TIM3RST                ((uint32_t)0x00000002)        /*!< Timer 3 clock reset */
#define  RCC_APB1RSTR_TIM6RST                ((uint32_t)0x00000010)        /*!< Timer 6 clock reset */
//#define  RCC_APB1RSTR_TIM7RST                ((uint32_t)0x00000020)        /*!< Timer 7 clock reset */
#define  RCC_APB1RSTR_TIM14RST               ((uint32_t)0x00000100)        /*!< Timer 14 clock reset */
#define  RCC_APB1RSTR_WWDGRST                ((uint32_t)0x00000800)        /*!< Window Watchdog clock reset */
#define  RCC_APB1RSTR_SPI2RST                ((uint32_t)0x00004000)        /*!< SPI2 clock reset */
#define  RCC_APB1RSTR_USART2RST              ((uint32_t)0x00020000)        /*!< USART 2 clock reset */
//#define  RCC_APB1RSTR_USART3RST              ((uint32_t)0x00040000)        /*!< USART 3 clock reset */
//#define  RCC_APB1RSTR_USART4RST              ((uint32_t)0x00080000)        /*!< USART 4 clock reset */
//#define  RCC_APB1RSTR_USART5RST              ((uint32_t)0x00100000)        /*!< USART 5 clock reset */
#define  RCC_APB1RSTR_I2C1RST                ((uint32_t)0x00200000)        /*!< I2C 1 clock reset */
#define  RCC_APB1RSTR_I2C2RST                ((uint32_t)0x00400000)        /*!< I2C 2 clock reset */
#define  RCC_APB1RSTR_USBRST                 ((uint32_t)0x00800000)        /*!< USB clock reset */
//#define  RCC_APB1RSTR_CANRST                 ((uint32_t)0x02000000)        /*!< CAN clock reset */
#define  RCC_APB1RSTR_CRSRST                 ((uint32_t)0x08000000)        /*!< CRS clock reset */
#define  RCC_APB1RSTR_PWRRST                 ((uint32_t)0x10000000)        /*!< PWR clock reset */
//#define  RCC_APB1RSTR_DACRST                 ((uint32_t)0x20000000)        /*!< DAC clock reset */
//#define  RCC_APB1RSTR_CECRST                 ((uint32_t)0x40000000)        /*!< CEC clock reset */

/******************  Bit definition for RCC_AHBENR register  ******************/
#define  RCC_AHBENR_DMAEN                    ((uint32_t)0x00000001)        /*!< DMA clock enable */
//#define  RCC_AHBENR_DMA2EN                   ((uint32_t)0x00000002)        /*!< DMA2 clock enable */
#define  RCC_AHBENR_SRAMEN                   ((uint32_t)0x00000004)        /*!< SRAM interface clock enable */
//#define  RCC_AHBENR_FLITFEN                  ((uint32_t)0x00000010)        /*!< FLITF clock enable */
#define  RCC_AHBENR_CRCEN                    ((uint32_t)0x00000040)        /*!< CRC clock enable */
#define  RCC_AHBENR_GPIOAEN                  ((uint32_t)0x00020000)        /*!< GPIOA clock enable */
#define  RCC_AHBENR_GPIOBEN                  ((uint32_t)0x00040000)        /*!< GPIOB clock enable */
#define  RCC_AHBENR_GPIOCEN                  ((uint32_t)0x00080000)        /*!< GPIOC clock enable */
#define  RCC_AHBENR_GPIODEN                  ((uint32_t)0x00100000)        /*!< GPIOD clock enable */
//#define  RCC_AHBENR_GPIOEEN                  ((uint32_t)0x00200000)        /*!< GPIOE clock enable */
#define  RCC_AHBENR_GPIOFEN                  ((uint32_t)0x00400000)        /*!< GPIOF clock enable */
#define  RCC_AHBENR_TSCEN                    ((uint32_t)0x01000000)        /*!< TS controller clock enable */

#define  RCC_AHBENR_IOPAEN                  RCC_AHBENR_GPIOAEN          /*!< GPIOA clock enable */
#define  RCC_AHBENR_IOPBEN                  RCC_AHBENR_GPIOBEN          /*!< GPIOB clock enable */
#define  RCC_AHBENR_IOPCEN                  RCC_AHBENR_GPIOCEN          /*!< GPIOC clock enable */
#define  RCC_AHBENR_IOPDEN                  RCC_AHBENR_GPIODEN          /*!< GPIOD clock enable */

#define  RCC_AHBENR_IOPFEN                  RCC_AHBENR_GPIOFEN          /*!< GPIOF clock enable */
/* Old Bit definition maintained for legacy purpose */
#define  RCC_AHBENR_DMA1EN                   RCC_AHBENR_DMAEN        /*!< DMA1 clock enable */
#define  RCC_AHBENR_TSEN                     RCC_AHBENR_TSCEN        /*!< TS clock enable */

/*****************  Bit definition for RCC_APB2ENR register  ******************/
#define  RCC_APB2ENR_SYSCFGCOMPEN            ((uint32_t)0x00000001)        /*!< SYSCFG and comparator clock enable */
//#define  RCC_APB2ENR_USART6EN                ((uint32_t)0x00000020)        /*!< USART6 clock enable */
//#define  RCC_APB2ENR_USART7EN                ((uint32_t)0x00000040)        /*!< USART7 clock enable */
//#define  RCC_APB2ENR_USART8EN                ((uint32_t)0x00000080)        /*!< USART8 clock enable */
#define  RCC_APB2ENR_ADCEN                   ((uint32_t)0x00000200)        /*!< ADC1 clock enable */
#define  RCC_APB2ENR_TIM1EN                  ((uint32_t)0x00000800)        /*!< TIM1 clock enable */
#define  RCC_APB2ENR_SPI1EN                  ((uint32_t)0x00001000)        /*!< SPI1 clock enable */
#define  RCC_APB2ENR_USART1EN                ((uint32_t)0x00004000)        /*!< USART1 clock enable */
#define  RCC_APB2ENR_TIM15EN                 ((uint32_t)0x00010000)        /*!< TIM15 clock enable */
#define  RCC_APB2ENR_TIM16EN                 ((uint32_t)0x00020000)        /*!< TIM16 clock enable */
#define  RCC_APB2ENR_TIM17EN                 ((uint32_t)0x00040000)        /*!< TIM17 clock enable */
#define  RCC_APB2ENR_DBGMCUEN                ((uint32_t)0x00400000)        /*!< DBGMCU clock enable */

/* Old Bit definition maintained for legacy purpose */
#define  RCC_APB2ENR_SYSCFGEN                RCC_APB2ENR_SYSCFGCOMPEN        /*!< SYSCFG clock enable */
#define  RCC_APB2ENR_ADC1EN                  RCC_APB2ENR_ADCEN               /*!< ADC1 clock enable */

/*****************  Bit definition for RCC_APB1ENR register  ******************/
//#define  RCC_APB1ENR_TIM2EN                  ((uint32_t)0x00000001)        /*!< Timer 2 clock enable */
#define  RCC_APB1ENR_TIM3EN                  ((uint32_t)0x00000002)        /*!< Timer 3 clock enable */
#define  RCC_APB1ENR_TIM6EN                  ((uint32_t)0x00000010)        /*!< Timer 6 clock enable */
//#define  RCC_APB1ENR_TIM7EN                  ((uint32_t)0x00000020)        /*!< Timer 7 clock enable */
#define  RCC_APB1ENR_TIM14EN                 ((uint32_t)0x00000100)        /*!< Timer 14 clock enable */
#define  RCC_APB1ENR_WWDGEN                  ((uint32_t)0x00000800)        /*!< Window Watchdog clock enable */
#define  RCC_APB1ENR_SPI2EN                  ((uint32_t)0x00004000)        /*!< SPI2 clock enable */
#define  RCC_APB1ENR_USART2EN                ((uint32_t)0x00020000)        /*!< USART2 clock enable */
//#define  RCC_APB1ENR_USART3EN                ((uint32_t)0x00040000)        /*!< USART3 clock enable */
//#define  RCC_APB1ENR_USART4EN                ((uint32_t)0x00080000)        /*!< USART4 clock enable */
//#define  RCC_APB1ENR_USART5EN                ((uint32_t)0x00100000)        /*!< USART5 clock enable */
#define  RCC_APB1ENR_I2C1EN                  ((uint32_t)0x00200000)        /*!< I2C1 clock enable */
#define  RCC_APB1ENR_I2C2EN                  ((uint32_t)0x00400000)        /*!< I2C2 clock enable */
#define  RCC_APB1ENR_USBEN                   ((uint32_t)0x00800000)        /*!< USB clock enable */
//#define  RCC_APB1ENR_CANEN                   ((uint32_t)0x02000000)         /*!< CAN clock enable */
#define  RCC_APB1ENR_CRSEN                   ((uint32_t)0x08000000)        /*!< CRS clock enable */
#define  RCC_APB1ENR_PWREN                   ((uint32_t)0x10000000)        /*!< PWR clock enable */
//#define  RCC_APB1ENR_DACEN                   ((uint32_t)0x20000000)        /*!< DAC clock enable */
//#define  RCC_APB1ENR_CECEN                   ((uint32_t)0x40000000)        /*!< CEC clock enable */

/*******************  Bit definition for RCC_BDCR register  *******************/
#define  RCC_BDCR_LSEON                      ((uint32_t)0x00000001)        /*!< External Low Speed oscillator enable */
#define  RCC_BDCR_LSERDY                     ((uint32_t)0x00000002)        /*!< External Low Speed oscillator Ready */
#define  RCC_BDCR_LSEBYP                     ((uint32_t)0x00000004)        /*!< External Low Speed oscillator Bypass */

#define  RCC_BDCR_LSEDRV                     ((uint32_t)0x00000038)        /*!< LSEDRV[1:0] bits (LSE Osc. drive capability) */
#define  RCC_BDCR_LSEDRV_0                   ((uint32_t)0x00000008)        /*!< Bit 0 */
#define  RCC_BDCR_LSEDRV_1                   ((uint32_t)0x00000010)        /*!< Bit 1 */
#define  RCC_BDCR_LSEDRV_2                   ((uint32_t)0x00000020)        /*!< Bit 2 */

#define  RCC_BDCR_RTCSEL                     ((uint32_t)0x00000300)        /*!< RTCSEL[1:0] bits (RTC clock source selection) */
#define  RCC_BDCR_RTCSEL_0                   ((uint32_t)0x00000100)        /*!< Bit 0 */
#define  RCC_BDCR_RTCSEL_1                   ((uint32_t)0x00000200)        /*!< Bit 1 */

/* RTC configuration */
#define  RCC_BDCR_RTCSEL_NOCLOCK             ((uint32_t)0x00000000)        /*!< No clock */
#define  RCC_BDCR_RTCSEL_LSE                 ((uint32_t)0x00000100)        /*!< LSE oscillator clock used as RTC clock */
#define  RCC_BDCR_RTCSEL_LSI                 ((uint32_t)0x00000200)        /*!< LSI oscillator clock used as RTC clock */
#define  RCC_BDCR_RTCSEL_HSE                 ((uint32_t)0x00000300)        /*!< HSE oscillator clock divided by 32 used as RTC clock */

#define  RCC_BDCR_RTCISO                     ((uint32_t)0x00002000)        /*!<  */
#define  RCC_BDCR_RTCPD                      ((uint32_t)0x00004000)        /*!<   */
#define  RCC_BDCR_RTCEN                      ((uint32_t)0x00008000)        /*!< RTC clock enable */
#define  RCC_BDCR_BDRST                      ((uint32_t)0x00010000)        /*!< Backup domain software reset  */

/*******************  Bit definition for RCC_CSR register  ********************/
#define  RCC_CSR_LSION                       ((uint32_t)0x00000001)        /*!< Internal Low Speed oscillator enable */
#define  RCC_CSR_LSIRDY                      ((uint32_t)0x00000002)        /*!< Internal Low Speed oscillator Ready */
#define  RCC_CSR_V18PWRRSTF                  ((uint32_t)0x00800000)        /*!< V1.8 power domain reset flag */
#define  RCC_CSR_RMVF                        ((uint32_t)0x01000000)        /*!< Remove reset flag */
#define  RCC_CSR_OBLRSTF                     ((uint32_t)0x02000000)        /*!< OBL reset flag */
#define  RCC_CSR_PINRSTF                     ((uint32_t)0x04000000)        /*!< PIN reset flag */
#define  RCC_CSR_PORRSTF                     ((uint32_t)0x08000000)        /*!< POR/PDR reset flag */
#define  RCC_CSR_SFTRSTF                     ((uint32_t)0x10000000)        /*!< Software Reset flag */
#define  RCC_CSR_IWDGRSTF                    ((uint32_t)0x20000000)        /*!< Independent Watchdog reset flag */
#define  RCC_CSR_WWDGRSTF                    ((uint32_t)0x40000000)        /*!< Window watchdog reset flag */
#define  RCC_CSR_LPWRRSTF                    ((uint32_t)0x80000000)        /*!< Low-Power reset flag */

/* Old Bit definition maintained for legacy purpose */
#define  RCC_CSR_OBL                         RCC_CSR_OBLRSTF        /*!< OBL reset flag */
#define  RCC_CSR_VDDLRSTF                    RCC_CSR_V18PWRRSTF
/*******************  Bit definition for RCC_AHBRSTR register  ****************/
#define  RCC_AHBRSTR_GPIOARST                ((uint32_t)0x00020000)         /*!< GPIOA clock reset */
#define  RCC_AHBRSTR_GPIOBRST                ((uint32_t)0x00040000)         /*!< GPIOB clock reset */
#define  RCC_AHBRSTR_GPIOCRST                ((uint32_t)0x00080000)         /*!< GPIOC clock reset */
#define  RCC_AHBRSTR_GPIODRST                ((uint32_t)0x00010000)         /*!< GPIOD clock reset */
//#define  RCC_AHBRSTR_GPIOERST                ((uint32_t)0x00020000)         /*!< GPIOE clock reset */
#define  RCC_AHBRSTR_GPIOFRST                ((uint32_t)0x00040000)         /*!< GPIOF clock reset */
#define  RCC_AHBRSTR_TSCRST                  ((uint32_t)0x00100000)         /*!< TS clock reset */

/* Old Bit definition maintained for legacy purpose */
#define  RCC_AHBRSTR_TSRST                   RCC_AHBRSTR_TSCRST         /*!< TS clock reset */

#define  RCC_AHBRSTR_IOPARST                 RCC_AHBRSTR_GPIOARST
#define  RCC_AHBRSTR_IOPBRST                 RCC_AHBRSTR_GPIOBRST
#define  RCC_AHBRSTR_IOPCRST                 RCC_AHBRSTR_GPIOCRST
#define  RCC_AHBRSTR_IOPDRST                 RCC_AHBRSTR_GPIODRST
#define  RCC_AHBRSTR_IOPFRST                 RCC_AHBRSTR_GPIOFRST

/*******************  Bit definition for RCC_CFGR2 register  ******************/
/* PREDIV1 configuration */
#define  RCC_CFGR2_PREDIV1                   ((uint32_t)0x0000000F)        /*!< PREDIV1[3:0] bits */
#define  RCC_CFGR2_PREDIV1_0                 ((uint32_t)0x00000001)        /*!< Bit 0 */
#define  RCC_CFGR2_PREDIV1_1                 ((uint32_t)0x00000002)        /*!< Bit 1 */
#define  RCC_CFGR2_PREDIV1_2                 ((uint32_t)0x00000004)        /*!< Bit 2 */
#define  RCC_CFGR2_PREDIV1_3                 ((uint32_t)0x00000008)        /*!< Bit 3 */

#define  RCC_CFGR2_PREDIV1_DIV1              ((uint32_t)0x00000000)        /*!< PREDIV1 input clock not divided */
#define  RCC_CFGR2_PREDIV1_DIV2              ((uint32_t)0x00000001)        /*!< PREDIV1 input clock divided by 2 */
#define  RCC_CFGR2_PREDIV1_DIV3              ((uint32_t)0x00000002)        /*!< PREDIV1 input clock divided by 3 */
#define  RCC_CFGR2_PREDIV1_DIV4              ((uint32_t)0x00000003)        /*!< PREDIV1 input clock divided by 4 */
#define  RCC_CFGR2_PREDIV1_DIV5              ((uint32_t)0x00000004)        /*!< PREDIV1 input clock divided by 5 */
#define  RCC_CFGR2_PREDIV1_DIV6              ((uint32_t)0x00000005)        /*!< PREDIV1 input clock divided by 6 */
#define  RCC_CFGR2_PREDIV1_DIV7              ((uint32_t)0x00000006)        /*!< PREDIV1 input clock divided by 7 */
#define  RCC_CFGR2_PREDIV1_DIV8              ((uint32_t)0x00000007)        /*!< PREDIV1 input clock divided by 8 */
#define  RCC_CFGR2_PREDIV1_DIV9              ((uint32_t)0x00000008)        /*!< PREDIV1 input clock divided by 9 */
#define  RCC_CFGR2_PREDIV1_DIV10             ((uint32_t)0x00000009)        /*!< PREDIV1 input clock divided by 10 */
#define  RCC_CFGR2_PREDIV1_DIV11             ((uint32_t)0x0000000A)        /*!< PREDIV1 input clock divided by 11 */
#define  RCC_CFGR2_PREDIV1_DIV12             ((uint32_t)0x0000000B)        /*!< PREDIV1 input clock divided by 12 */
#define  RCC_CFGR2_PREDIV1_DIV13             ((uint32_t)0x0000000C)        /*!< PREDIV1 input clock divided by 13 */
#define  RCC_CFGR2_PREDIV1_DIV14             ((uint32_t)0x0000000D)        /*!< PREDIV1 input clock divided by 14 */
#define  RCC_CFGR2_PREDIV1_DIV15             ((uint32_t)0x0000000E)        /*!< PREDIV1 input clock divided by 15 */
#define  RCC_CFGR2_PREDIV1_DIV16             ((uint32_t)0x0000000F)        /*!< PREDIV1 input clock divided by 16 */

/* Old Bit definition maintained for legacy purpose */
#define  RCC_CFGR2_PREDIV                  RCC_CFGR2_PREDIV1
#define  RCC_CFGR2_PREDIV_0                RCC_CFGR2_PREDIV1_0
#define  RCC_CFGR2_PREDIV_1                RCC_CFGR2_PREDIV1_1
#define  RCC_CFGR2_PREDIV_2                RCC_CFGR2_PREDIV1_2
#define  RCC_CFGR2_PREDIV_3                RCC_CFGR2_PREDIV1_3

#define  RCC_CFGR2_PREDIV_DIV1             RCC_CFGR2_PREDIV1_DIV1
#define  RCC_CFGR2_PREDIV_DIV2             RCC_CFGR2_PREDIV1_DIV2
#define  RCC_CFGR2_PREDIV_DIV3             RCC_CFGR2_PREDIV1_DIV3
#define  RCC_CFGR2_PREDIV_DIV4             RCC_CFGR2_PREDIV1_DIV4
#define  RCC_CFGR2_PREDIV_DIV5             RCC_CFGR2_PREDIV1_DIV5
#define  RCC_CFGR2_PREDIV_DIV6             RCC_CFGR2_PREDIV1_DIV6
#define  RCC_CFGR2_PREDIV_DIV7             RCC_CFGR2_PREDIV1_DIV7
#define  RCC_CFGR2_PREDIV_DIV8             RCC_CFGR2_PREDIV1_DIV8
#define  RCC_CFGR2_PREDIV_DIV9             RCC_CFGR2_PREDIV1_DIV9
#define  RCC_CFGR2_PREDIV_DIV10            RCC_CFGR2_PREDIV1_DIV10
#define  RCC_CFGR2_PREDIV_DIV11            RCC_CFGR2_PREDIV1_DIV11
#define  RCC_CFGR2_PREDIV_DIV12            RCC_CFGR2_PREDIV1_DIV12
#define  RCC_CFGR2_PREDIV_DIV13            RCC_CFGR2_PREDIV1_DIV13
#define  RCC_CFGR2_PREDIV_DIV14            RCC_CFGR2_PREDIV1_DIV14
#define  RCC_CFGR2_PREDIV_DIV15            RCC_CFGR2_PREDIV1_DIV15
#define  RCC_CFGR2_PREDIV_DIV16            RCC_CFGR2_PREDIV1_DIV16
/*******************  Bit definition for RCC_CFGR3 register  ******************/
#define  RCC_CFGR3_USART1SW                  ((uint32_t)0x00000003)        /*!< USART1SW[1:0] bits */
#define  RCC_CFGR3_USART1SW_0                ((uint32_t)0x00000001)        /*!< Bit 0 */
#define  RCC_CFGR3_USART1SW_1                ((uint32_t)0x00000002)        /*!< Bit 1 */
#define  RCC_CFGR3_I2C1SW                    ((uint32_t)0x00000010)        /*!< I2C1SW bits */
//#define  RCC_CFGR3_CECSW                     ((uint32_t)0x00000040)        /*!< CECSW bits */
#define  RCC_CFGR3_USBSW                     ((uint32_t)0x00000080)        /*!< USBSW bits */
#define  RCC_CFGR3_ADCSW                     ((uint32_t)0x00000100)        /*!< ADCSW bits */
//#define  RCC_CFGR3_USART2SW                  ((uint32_t)0x00030000)        /*!< USART2SW[1:0] bits */
//#define  RCC_CFGR3_USART2SW_0                ((uint32_t)0x00010000)        /*!< Bit 0 */
//#define  RCC_CFGR3_USART2SW_1                ((uint32_t)0x00020000)        /*!< Bit 1 */
//#define  RCC_CFGR3_USART3SW                  ((uint32_t)0x000C0000)        /*!< USART3SW[1:0] bits */
//#define  RCC_CFGR3_USART3SW_0                ((uint32_t)0x00040000)        /*!< Bit 0 */
//#define  RCC_CFGR3_USART3SW_1                ((uint32_t)0x00080000)        /*!< Bit 1 */


/*******************  Bit definition for RCC_CR2 register  ********************/
#define  RCC_CR2_HSI14ON                     ((uint32_t)0x00000001)        /*!< Internal High Speed 14MHz clock enable */
#define  RCC_CR2_HSI14RDY                    ((uint32_t)0x00000002)        /*!< Internal High Speed 14MHz clock ready flag */
#define  RCC_CR2_HSI14DIS                    ((uint32_t)0x00000004)        /*!< Internal High Speed 14MHz clock disable */
#define  RCC_CR2_HSI14TRIM                   ((uint32_t)0x000000F8)        /*!< Internal High Speed 14MHz clock trimming */
#define  RCC_CR2_HSI14CAL                    ((uint32_t)0x0000FF00)        /*!< Internal High Speed 14MHz clock Calibration */
#define  RCC_CR2_HSI48ON                     ((uint32_t)0x00010000)        /*!< Internal High Speed 48MHz clock enable */
#define  RCC_CR2_HSI48RDY                    ((uint32_t)0x00020000)        /*!< Internal High Speed 48MHz clock ready flag */
#define  RCC_CR2_HSI48CAL                    ((uint32_t)0xFF800000)        /*!< Internal High Speed 48MHz clock Calibration */

/******************************************************************************/
/*                                                                            */
/*                           Real-Time Clock (RTC)                            */
/*                                                                            */
/******************************************************************************/
/********************  Bits definition for RTC_TR register  *******************/
#define RTC_TR_SU                            ((uint32_t)0x0000000F)
#define RTC_TR_SU_0                          ((uint32_t)0x00000001)
#define RTC_TR_SU_1                          ((uint32_t)0x00000002)
#define RTC_TR_SU_2                          ((uint32_t)0x00000004)
#define RTC_TR_SU_3                          ((uint32_t)0x00000008)
#define RTC_TR_ST                            ((uint32_t)0x00000070)
#define RTC_TR_ST_0                          ((uint32_t)0x00000010)
#define RTC_TR_ST_1                          ((uint32_t)0x00000020)
#define RTC_TR_ST_2                          ((uint32_t)0x00000040)
#define RTC_TR_MNU                           ((uint32_t)0x00000F00)
#define RTC_TR_MNU_0                         ((uint32_t)0x00000100)
#define RTC_TR_MNU_1                         ((uint32_t)0x00000200)
#define RTC_TR_MNU_2                         ((uint32_t)0x00000400)
#define RTC_TR_MNU_3                         ((uint32_t)0x00000800)
#define RTC_TR_MNT                           ((uint32_t)0x00007000)
#define RTC_TR_MNT_0                         ((uint32_t)0x00001000)
#define RTC_TR_MNT_1                         ((uint32_t)0x00002000)
#define RTC_TR_MNT_2                         ((uint32_t)0x00004000)
#define RTC_TR_HU                            ((uint32_t)0x000F0000)
#define RTC_TR_HU_0                          ((uint32_t)0x00010000)
#define RTC_TR_HU_1                          ((uint32_t)0x00020000)
#define RTC_TR_HU_2                          ((uint32_t)0x00040000)
#define RTC_TR_HU_3                          ((uint32_t)0x00080000)
#define RTC_TR_HT                            ((uint32_t)0x00300000)
#define RTC_TR_HT_0                          ((uint32_t)0x00100000)
#define RTC_TR_HT_1                          ((uint32_t)0x00200000)
#define RTC_TR_PM                            ((uint32_t)0x00400000)

/********************  Bits definition for RTC_DR register  *******************/
#define RTC_DR_DU                            ((uint32_t)0x0000000F)
#define RTC_DR_DU_0                          ((uint32_t)0x00000001)
#define RTC_DR_DU_1                          ((uint32_t)0x00000002)
#define RTC_DR_DU_2                          ((uint32_t)0x00000004)
#define RTC_DR_DU_3                          ((uint32_t)0x00000008)
#define RTC_DR_DT                            ((uint32_t)0x00000030)
#define RTC_DR_DT_0                          ((uint32_t)0x00000010)
#define RTC_DR_DT_1                          ((uint32_t)0x00000020)
#define RTC_DR_MU                            ((uint32_t)0x00000F00)
#define RTC_DR_MU_0                          ((uint32_t)0x00000100)
#define RTC_DR_MU_1                          ((uint32_t)0x00000200)
#define RTC_DR_MU_2                          ((uint32_t)0x00000400)
#define RTC_DR_MU_3                          ((uint32_t)0x00000800)
#define RTC_DR_MT                            ((uint32_t)0x00001000)
#define RTC_DR_WDU                           ((uint32_t)0x0000E000)
#define RTC_DR_WDU_0                         ((uint32_t)0x00002000)
#define RTC_DR_WDU_1                         ((uint32_t)0x00004000)
#define RTC_DR_WDU_2                         ((uint32_t)0x00008000)
#define RTC_DR_YU                            ((uint32_t)0x000F0000)
#define RTC_DR_YU_0                          ((uint32_t)0x00010000)
#define RTC_DR_YU_1                          ((uint32_t)0x00020000)
#define RTC_DR_YU_2                          ((uint32_t)0x00040000)
#define RTC_DR_YU_3                          ((uint32_t)0x00080000)
#define RTC_DR_YT                            ((uint32_t)0x00F00000)
#define RTC_DR_YT_0                          ((uint32_t)0x00100000)
#define RTC_DR_YT_1                          ((uint32_t)0x00200000)
#define RTC_DR_YT_2                          ((uint32_t)0x00400000)
#define RTC_DR_YT_3                          ((uint32_t)0x00800000)

/********************  Bits definition for RTC_CR register  *******************/
//#define RTC_CR_WUCKSEL                       ((uint32_t)0x00000007)
//#define RTC_CR_WUCKSEL_0                     ((uint32_t)0x00000001)
//#define RTC_CR_WUCKSEL_1                     ((uint32_t)0x00000002)
//#define RTC_CR_WUCKSEL_2                     ((uint32_t)0x00000004)
#define RTC_CR_TSEDGE                        ((uint32_t)0x00000008)
#define RTC_CR_REFCKON                       ((uint32_t)0x00000010)
#define RTC_CR_BYPSHAD                       ((uint32_t)0x00000020)
#define RTC_CR_FMT                           ((uint32_t)0x00000040)
#define RTC_CR_ALRAE                         ((uint32_t)0x00000100)
//#define RTC_CR_WUTE                          ((uint32_t)0x00000400)
#define RTC_CR_TSE                           ((uint32_t)0x00000800)
#define RTC_CR_ALRAIE                        ((uint32_t)0x00001000)
//#define RTC_CR_WUTIE                         ((uint32_t)0x00004000)
#define RTC_CR_TSIE                          ((uint32_t)0x00008000)
#define RTC_CR_ADD1H                         ((uint32_t)0x00010000)
#define RTC_CR_SUB1H                         ((uint32_t)0x00020000)
#define RTC_CR_BKP                           ((uint32_t)0x00040000)
#define RTC_CR_COSEL                         ((uint32_t)0x00080000)
#define RTC_CR_POL                           ((uint32_t)0x00100000)
#define RTC_CR_OSEL                          ((uint32_t)0x00200000)
//#define RTC_CR_OSEL_0                        ((uint32_t)0x00200000)
//#define RTC_CR_OSEL_1                        ((uint32_t)0x00400000)
#define RTC_CR_COE                           ((uint32_t)0x00800000)

/* Old bit definition maintained for legacy purpose */
#define RTC_CR_BCK                           RTC_CR_BKP
#define RTC_CR_CALSEL                        RTC_CR_COSEL

/********************  Bits definition for RTC_ISR register  ******************/
#define RTC_ISR_RECALPF                      ((uint32_t)0x00010000)
//#define RTC_ISR_TAMP3F                       ((uint32_t)0x00008000)
#define RTC_ISR_TAMP2F                       ((uint32_t)0x00004000)
#define RTC_ISR_TAMP1F                       ((uint32_t)0x00002000)
#define RTC_ISR_TSOVF                        ((uint32_t)0x00001000)
#define RTC_ISR_TSF                          ((uint32_t)0x00000800)
//#define RTC_ISR_WUTF                         ((uint32_t)0x00000400)
#define RTC_ISR_ALRAF                        ((uint32_t)0x00000100)
#define RTC_ISR_INIT                         ((uint32_t)0x00000080)
#define RTC_ISR_INITF                        ((uint32_t)0x00000040)
#define RTC_ISR_RSF                          ((uint32_t)0x00000020)
#define RTC_ISR_INITS                        ((uint32_t)0x00000010)
#define RTC_ISR_SHPF                         ((uint32_t)0x00000008)
//#define RTC_ISR_WUTWF                        ((uint32_t)0x00000004)
#define RTC_ISR_ALRAWF                       ((uint32_t)0x00000001)

/********************  Bits definition for RTC_PRER register  *****************/
#define RTC_PRER_PREDIV_A                    ((uint32_t)0x007F0000)
#define RTC_PRER_PREDIV_S                    ((uint32_t)0x00007FFF)

/********************  Bits definition for RTC_WUTR register  *****************/
//#define RTC_WUTR_WUT                         ((uint32_t)0x0000FFFF)

/********************  Bits definition for RTC_ALRMAR register  ***************/
#define RTC_ALRMAR_MSK4                      ((uint32_t)0x80000000)
#define RTC_ALRMAR_WDSEL                     ((uint32_t)0x40000000)
#define RTC_ALRMAR_DT                        ((uint32_t)0x30000000)
#define RTC_ALRMAR_DT_0                      ((uint32_t)0x10000000)
#define RTC_ALRMAR_DT_1                      ((uint32_t)0x20000000)
#define RTC_ALRMAR_DU                        ((uint32_t)0x0F000000)
#define RTC_ALRMAR_DU_0                      ((uint32_t)0x01000000)
#define RTC_ALRMAR_DU_1                      ((uint32_t)0x02000000)
#define RTC_ALRMAR_DU_2                      ((uint32_t)0x04000000)
#define RTC_ALRMAR_DU_3                      ((uint32_t)0x08000000)
#define RTC_ALRMAR_MSK3                      ((uint32_t)0x00800000)
#define RTC_ALRMAR_PM                        ((uint32_t)0x00400000)
#define RTC_ALRMAR_HT                        ((uint32_t)0x00300000)
#define RTC_ALRMAR_HT_0                      ((uint32_t)0x00100000)
#define RTC_ALRMAR_HT_1                      ((uint32_t)0x00200000)
#define RTC_ALRMAR_HU                        ((uint32_t)0x000F0000)
#define RTC_ALRMAR_HU_0                      ((uint32_t)0x00010000)
#define RTC_ALRMAR_HU_1                      ((uint32_t)0x00020000)
#define RTC_ALRMAR_HU_2                      ((uint32_t)0x00040000)
#define RTC_ALRMAR_HU_3                      ((uint32_t)0x00080000)
#define RTC_ALRMAR_MSK2                      ((uint32_t)0x00008000)
#define RTC_ALRMAR_MNT                       ((uint32_t)0x00007000)
#define RTC_ALRMAR_MNT_0                     ((uint32_t)0x00001000)
#define RTC_ALRMAR_MNT_1                     ((uint32_t)0x00002000)
#define RTC_ALRMAR_MNT_2                     ((uint32_t)0x00004000)
#define RTC_ALRMAR_MNU                       ((uint32_t)0x00000F00)
#define RTC_ALRMAR_MNU_0                     ((uint32_t)0x00000100)
#define RTC_ALRMAR_MNU_1                     ((uint32_t)0x00000200)
#define RTC_ALRMAR_MNU_2                     ((uint32_t)0x00000400)
#define RTC_ALRMAR_MNU_3                     ((uint32_t)0x00000800)
#define RTC_ALRMAR_MSK1                      ((uint32_t)0x00000080)
#define RTC_ALRMAR_ST                        ((uint32_t)0x00000070)
#define RTC_ALRMAR_ST_0                      ((uint32_t)0x00000010)
#define RTC_ALRMAR_ST_1                      ((uint32_t)0x00000020)
#define RTC_ALRMAR_ST_2                      ((uint32_t)0x00000040)
#define RTC_ALRMAR_SU                        ((uint32_t)0x0000000F)
#define RTC_ALRMAR_SU_0                      ((uint32_t)0x00000001)
#define RTC_ALRMAR_SU_1                      ((uint32_t)0x00000002)
#define RTC_ALRMAR_SU_2                      ((uint32_t)0x00000004)
#define RTC_ALRMAR_SU_3                      ((uint32_t)0x00000008)

/********************  Bits definition for RTC_WPR register  ******************/
#define RTC_WPR_KEY                          ((uint32_t)0x000000FF)

/********************  Bits definition for RTC_SSR register  ******************/
//#define RTC_SSR_SS                           ((uint32_t)0x0003FFFF)
#define RTC_SSR_SS                           ((uint32_t)0x0000FFFF)

/********************  Bits definition for RTC_SHIFTR register  ***************/
#define RTC_SHIFTR_SUBFS                     ((uint32_t)0x00007FFF)
#define RTC_SHIFTR_ADD1S                     ((uint32_t)0x80000000)

/********************  Bits definition for RTC_TSTR register  *****************/
#define RTC_TSTR_PM                          ((uint32_t)0x00400000)
#define RTC_TSTR_HT                          ((uint32_t)0x00300000)
#define RTC_TSTR_HT_0                        ((uint32_t)0x00100000)
#define RTC_TSTR_HT_1                        ((uint32_t)0x00200000)
#define RTC_TSTR_HU                          ((uint32_t)0x000F0000)
#define RTC_TSTR_HU_0                        ((uint32_t)0x00010000)
#define RTC_TSTR_HU_1                        ((uint32_t)0x00020000)
#define RTC_TSTR_HU_2                        ((uint32_t)0x00040000)
#define RTC_TSTR_HU_3                        ((uint32_t)0x00080000)
#define RTC_TSTR_MNT                         ((uint32_t)0x00007000)
#define RTC_TSTR_MNT_0                       ((uint32_t)0x00001000)
#define RTC_TSTR_MNT_1                       ((uint32_t)0x00002000)
#define RTC_TSTR_MNT_2                       ((uint32_t)0x00004000)
#define RTC_TSTR_MNU                         ((uint32_t)0x00000F00)
#define RTC_TSTR_MNU_0                       ((uint32_t)0x00000100)
#define RTC_TSTR_MNU_1                       ((uint32_t)0x00000200)
#define RTC_TSTR_MNU_2                       ((uint32_t)0x00000400)
#define RTC_TSTR_MNU_3                       ((uint32_t)0x00000800)
#define RTC_TSTR_ST                          ((uint32_t)0x00000070)
#define RTC_TSTR_ST_0                        ((uint32_t)0x00000010)
#define RTC_TSTR_ST_1                        ((uint32_t)0x00000020)
#define RTC_TSTR_ST_2                        ((uint32_t)0x00000040)
#define RTC_TSTR_SU                          ((uint32_t)0x0000000F)
#define RTC_TSTR_SU_0                        ((uint32_t)0x00000001)
#define RTC_TSTR_SU_1                        ((uint32_t)0x00000002)
#define RTC_TSTR_SU_2                        ((uint32_t)0x00000004)
#define RTC_TSTR_SU_3                        ((uint32_t)0x00000008)

/********************  Bits definition for RTC_TSDR register  *****************/
#define RTC_TSDR_WDU                         ((uint32_t)0x0000E000)
#define RTC_TSDR_WDU_0                       ((uint32_t)0x00002000)
#define RTC_TSDR_WDU_1                       ((uint32_t)0x00004000)
#define RTC_TSDR_WDU_2                       ((uint32_t)0x00008000)
#define RTC_TSDR_MT                          ((uint32_t)0x00001000)
#define RTC_TSDR_MU                          ((uint32_t)0x00000F00)
#define RTC_TSDR_MU_0                        ((uint32_t)0x00000100)
#define RTC_TSDR_MU_1                        ((uint32_t)0x00000200)
#define RTC_TSDR_MU_2                        ((uint32_t)0x00000400)
#define RTC_TSDR_MU_3                        ((uint32_t)0x00000800)
#define RTC_TSDR_DT                          ((uint32_t)0x00000030)
#define RTC_TSDR_DT_0                        ((uint32_t)0x00000010)
#define RTC_TSDR_DT_1                        ((uint32_t)0x00000020)
#define RTC_TSDR_DU                          ((uint32_t)0x0000000F)
#define RTC_TSDR_DU_0                        ((uint32_t)0x00000001)
#define RTC_TSDR_DU_1                        ((uint32_t)0x00000002)
#define RTC_TSDR_DU_2                        ((uint32_t)0x00000004)
#define RTC_TSDR_DU_3                        ((uint32_t)0x00000008)

/********************  Bits definition for RTC_TSSSR register  ****************/
//#define RTC_TSSSR_SS                         ((uint32_t)0x0003FFFF)
#define RTC_TSSSR_SS                         ((uint32_t)0x0000FFFF)

/********************  Bits definition for RTC_CALR register  ******************/
#define RTC_CALR_CALP                         ((uint32_t)0x00008000)
#define RTC_CALR_CALW8                        ((uint32_t)0x00004000)
#define RTC_CALR_CALW16                       ((uint32_t)0x00002000)
#define RTC_CALR_CALM                         ((uint32_t)0x000001FF)
#define RTC_CALR_CALM_0                       ((uint32_t)0x00000001)
#define RTC_CALR_CALM_1                       ((uint32_t)0x00000002)
#define RTC_CALR_CALM_2                       ((uint32_t)0x00000004)
#define RTC_CALR_CALM_3                       ((uint32_t)0x00000008)
#define RTC_CALR_CALM_4                       ((uint32_t)0x00000010)
#define RTC_CALR_CALM_5                       ((uint32_t)0x00000020)
#define RTC_CALR_CALM_6                       ((uint32_t)0x00000040)
#define RTC_CALR_CALM_7                       ((uint32_t)0x00000080)
#define RTC_CALR_CALM_8                       ((uint32_t)0x00000100)

/* Old Bits definition for RTC_CAL register maintained for legacy purpose */
#define RTC_CAL_CALP                         RTC_CALR_CALP
#define RTC_CAL_CALW8                        RTC_CALR_CALW8
#define RTC_CAL_CALW16                       RTC_CALR_CALW16
#define RTC_CAL_CALM                         RTC_CALR_CALM
#define RTC_CAL_CALM_0                       RTC_CALR_CALM_0
#define RTC_CAL_CALM_1                       RTC_CALR_CALM_1
#define RTC_CAL_CALM_2                       RTC_CALR_CALM_2
#define RTC_CAL_CALM_3                       RTC_CALR_CALM_3
#define RTC_CAL_CALM_4                       RTC_CALR_CALM_4
#define RTC_CAL_CALM_5                       RTC_CALR_CALM_5
#define RTC_CAL_CALM_6                       RTC_CALR_CALM_6
#define RTC_CAL_CALM_7                       RTC_CALR_CALM_7
#define RTC_CAL_CALM_8                       RTC_CALR_CALM_8

/********************  Bits definition for RTC_TAFCR register  ****************/
#define RTC_TAFCR_PC15MODE                   ((uint32_t)0x00800000)
#define RTC_TAFCR_PC15VALUE                  ((uint32_t)0x00400000)
#define RTC_TAFCR_PC14MODE                   ((uint32_t)0x00200000)
#define RTC_TAFCR_PC14VALUE                  ((uint32_t)0x00100000)
#define RTC_TAFCR_PC13MODE                   ((uint32_t)0x00080000)
#define RTC_TAFCR_PC13VALUE                  ((uint32_t)0x00040000)
#define RTC_TAFCR_TAMPPUDIS                  ((uint32_t)0x00008000)
#define RTC_TAFCR_TAMPPRCH                   ((uint32_t)0x00006000)
#define RTC_TAFCR_TAMPPRCH_0                 ((uint32_t)0x00002000)
#define RTC_TAFCR_TAMPPRCH_1                 ((uint32_t)0x00004000)
#define RTC_TAFCR_TAMPFLT                    ((uint32_t)0x00001800)
#define RTC_TAFCR_TAMPFLT_0                  ((uint32_t)0x00000800)
#define RTC_TAFCR_TAMPFLT_1                  ((uint32_t)0x00001000)
#define RTC_TAFCR_TAMPFREQ                   ((uint32_t)0x00000700)
#define RTC_TAFCR_TAMPFREQ_0                 ((uint32_t)0x00000100)
#define RTC_TAFCR_TAMPFREQ_1                 ((uint32_t)0x00000200)
#define RTC_TAFCR_TAMPFREQ_2                 ((uint32_t)0x00000400)
#define RTC_TAFCR_TAMPTS                     ((uint32_t)0x00000080)
//#define RTC_TAFCR_TAMP3EDGE                  ((uint32_t)0x00000040)
//#define RTC_TAFCR_TAMP3E                     ((uint32_t)0x00000020)
#define RTC_TAFCR_TAMP2EDGE                  ((uint32_t)0x00000010)
#define RTC_TAFCR_TAMP2E                     ((uint32_t)0x00000008)
#define RTC_TAFCR_TAMPIE                     ((uint32_t)0x00000004)
#define RTC_TAFCR_TAMP1TRG                   ((uint32_t)0x00000002)
#define RTC_TAFCR_TAMP1E                     ((uint32_t)0x00000001)

/* Old bit definition maintained for legacy purpose */
#define RTC_TAFCR_ALARMOUTTYPE               RTC_TAFCR_PC13VALUE
#define RTC_TAFCR_TAMP2TRG                                   RTC_TAFCR_TAMP2EDGE
/********************  Bits definition for RTC_ALRMASSR register  *************/
#define RTC_ALRMASSR_MASKSS                  ((uint32_t)0x0F000000)
#define RTC_ALRMASSR_MASKSS_0                ((uint32_t)0x01000000)
#define RTC_ALRMASSR_MASKSS_1                ((uint32_t)0x02000000)
#define RTC_ALRMASSR_MASKSS_2                ((uint32_t)0x04000000)
#define RTC_ALRMASSR_MASKSS_3                ((uint32_t)0x08000000)
#define RTC_ALRMASSR_SS                      ((uint32_t)0x00007FFF)

/********************  Bits definition for RTC_BKP0R register  ****************/
#define RTC_BKP0R                            ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for RTC_BKP1R register  ****************/
#define RTC_BKP1R                            ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for RTC_BKP2R register  ****************/
#define RTC_BKP2R                            ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for RTC_BKP3R register  ****************/
#define RTC_BKP3R                            ((uint32_t)0xFFFFFFFF)

/********************  Bits definition for RTC_BKP4R register  ****************/
#define RTC_BKP4R                            ((uint32_t)0xFFFFFFFF)

/******************************************************************************/
/*                                                                            */
/*                        Serial Peripheral Interface (SPI)                   */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for SPI_CR1 register  ********************/
#define  SPI_CR1_CPHA                        ((uint16_t)0x0001)            /*!< Clock Phase */
#define  SPI_CR1_CPOL                        ((uint16_t)0x0002)            /*!< Clock Polarity */
#define  SPI_CR1_MSTR                        ((uint16_t)0x0004)            /*!< Master Selection */
#define  SPI_CR1_BR                          ((uint16_t)0x0038)            /*!< BR[2:0] bits (Baud Rate Control) */
#define  SPI_CR1_BR_0                        ((uint16_t)0x0008)            /*!< Bit 0 */
#define  SPI_CR1_BR_1                        ((uint16_t)0x0010)            /*!< Bit 1 */
#define  SPI_CR1_BR_2                        ((uint16_t)0x0020)            /*!< Bit 2 */
#define  SPI_CR1_SPE                         ((uint16_t)0x0040)            /*!< SPI Enable */
#define  SPI_CR1_LSBFIRST                    ((uint16_t)0x0080)            /*!< Frame Format */
#define  SPI_CR1_SSI                         ((uint16_t)0x0100)            /*!< Internal slave select */
#define  SPI_CR1_SSM                         ((uint16_t)0x0200)            /*!< Software slave management */
#define  SPI_CR1_RXONLY                      ((uint16_t)0x0400)            /*!< Receive only */
#define  SPI_CR1_CRCL                        ((uint16_t)0x0800)            /*!< CRC Length */
#define  SPI_CR1_CRCNEXT                     ((uint16_t)0x1000)            /*!< Transmit CRC next */
#define  SPI_CR1_CRCEN                       ((uint16_t)0x2000)            /*!< Hardware CRC calculation enable */
#define  SPI_CR1_BIDIOE                      ((uint16_t)0x4000)            /*!< Output enable in bidirectional mode */
#define  SPI_CR1_BIDIMODE                    ((uint16_t)0x8000)            /*!< Bidirectional data mode enable */

/*******************  Bit definition for SPI_CR2 register  ********************/
#define  SPI_CR2_RXDMAEN                     ((uint16_t)0x0001)            /*!< Rx Buffer DMA Enable */
#define  SPI_CR2_TXDMAEN                     ((uint16_t)0x0002)            /*!< Tx Buffer DMA Enable */
#define  SPI_CR2_SSOE                        ((uint16_t)0x0004)            /*!< SS Output Enable */
#define  SPI_CR2_NSSP                        ((uint16_t)0x0008)            /*!< NSS pulse management Enable */
#define  SPI_CR2_FRF                         ((uint16_t)0x0010)            /*!< Frame Format Enable */
#define  SPI_CR2_ERRIE                       ((uint16_t)0x0020)            /*!< Error Interrupt Enable */
#define  SPI_CR2_RXNEIE                      ((uint16_t)0x0040)            /*!< RX buffer Not Empty Interrupt Enable */
#define  SPI_CR2_TXEIE                       ((uint16_t)0x0080)            /*!< Tx buffer Empty Interrupt Enable */
#define  SPI_CR2_DS                          ((uint16_t)0x0F00)            /*!< DS[3:0] Data Size */
#define  SPI_CR2_DS_0                        ((uint16_t)0x0100)            /*!< Bit 0 */
#define  SPI_CR2_DS_1                        ((uint16_t)0x0200)            /*!< Bit 1 */
#define  SPI_CR2_DS_2                        ((uint16_t)0x0400)            /*!< Bit 2 */
#define  SPI_CR2_DS_3                        ((uint16_t)0x0800)            /*!< Bit 3 */
#define  SPI_CR2_FRXTH                       ((uint16_t)0x1000)            /*!< FIFO reception Threshold */
#define  SPI_CR2_LDMARX                      ((uint16_t)0x2000)            /*!< Last DMA transfer for reception */
#define  SPI_CR2_LDMATX                      ((uint16_t)0x4000)            /*!< Last DMA transfer for transmission */

/********************  Bit definition for SPI_SR register  ********************/
#define  SPI_SR_RXNE                         ((uint16_t)0x0001)            /*!< Receive buffer Not Empty */
#define  SPI_SR_TXE                          ((uint16_t)0x0002)            /*!< Transmit buffer Empty */
//#define  SPI_SR_CHSIDE                       ((uint16_t)0x0004)            /*!< Channel side */
//#define  SPI_SR_UDR                          ((uint16_t)0x0008)            /*!< Underrun flag */
#define  SPI_SR_CRCERR                       ((uint16_t)0x0010)            /*!< CRC Error flag */
#define  SPI_SR_MODF                         ((uint16_t)0x0020)            /*!< Mode fault */
#define  SPI_SR_OVR                          ((uint16_t)0x0040)            /*!< Overrun flag */
#define  SPI_SR_BSY                          ((uint16_t)0x0080)            /*!< Busy flag */
#define  SPI_SR_FRE                          ((uint16_t)0x0100)            /*!< TI frame format error */
#define  SPI_SR_FRLVL                        ((uint16_t)0x0600)            /*!< FIFO Reception Level */
#define  SPI_SR_FRLVL_0                      ((uint16_t)0x0200)            /*!< Bit 0 */
#define  SPI_SR_FRLVL_1                      ((uint16_t)0x0400)            /*!< Bit 1 */
#define  SPI_SR_FTLVL                        ((uint16_t)0x1800)            /*!< FIFO Transmission Level */
#define  SPI_SR_FTLVL_0                      ((uint16_t)0x0800)            /*!< Bit 0 */
#define  SPI_SR_FTLVL_1                      ((uint16_t)0x1000)            /*!< Bit 1 */

/********************  Bit definition for SPI_DR register  ********************/
#define  SPI_DR_DR                           ((uint16_t)0xFFFF)            /*!< Data Register */

/*******************  Bit definition for SPI_CRCPR register  ******************/
#define  SPI_CRCPR_CRCPOLY                   ((uint16_t)0xFFFF)            /*!< CRC polynomial register */

/******************  Bit definition for SPI_RXCRCR register  ******************/
#define  SPI_RXCRCR_RXCRC                    ((uint16_t)0xFFFF)            /*!< Rx CRC Register */

/******************  Bit definition for SPI_TXCRCR register  ******************/
#define  SPI_TXCRCR_TXCRC                    ((uint16_t)0xFFFF)            /*!< Tx CRC Register */

/******************  Bit definition for SPI_I2SCFGR register  *****************/
//#define  SPI_I2SCFGR_CHLEN                   ((uint16_t)0x0001)            /*!<Channel length (number of bits per audio channel) */
//#define  SPI_I2SCFGR_DATLEN                  ((uint16_t)0x0006)            /*!<DATLEN[1:0] bits (Data length to be transferred) */
//#define  SPI_I2SCFGR_DATLEN_0                ((uint16_t)0x0002)            /*!<Bit 0 */
//#define  SPI_I2SCFGR_DATLEN_1                ((uint16_t)0x0004)            /*!<Bit 1 */
//#define  SPI_I2SCFGR_CKPOL                   ((uint16_t)0x0008)            /*!<steady state clock polarity */
//#define  SPI_I2SCFGR_I2SSTD                  ((uint16_t)0x0030)            /*!<I2SSTD[1:0] bits (I2S standard selection) */
//#define  SPI_I2SCFGR_I2SSTD_0                ((uint16_t)0x0010)            /*!<Bit 0 */
//#define  SPI_I2SCFGR_I2SSTD_1                ((uint16_t)0x0020)            /*!<Bit 1 */
//#define  SPI_I2SCFGR_PCMSYNC                 ((uint16_t)0x0080)            /*!<PCM frame synchronization */
//#define  SPI_I2SCFGR_I2SCFG                  ((uint16_t)0x0300)            /*!<I2SCFG[1:0] bits (I2S configuration mode) */
//#define  SPI_I2SCFGR_I2SCFG_0                ((uint16_t)0x0100)            /*!<Bit 0 */
//#define  SPI_I2SCFGR_I2SCFG_1                ((uint16_t)0x0200)            /*!<Bit 1 */
//#define  SPI_I2SCFGR_I2SE                    ((uint16_t)0x0400)            /*!<I2S Enable */
//#define  SPI_I2SCFGR_I2SMOD                  ((uint16_t)0x0800)            /*!<I2S mode selection */

/******************  Bit definition for SPI_I2SPR register  *******************/
//#define  SPI_I2SPR_I2SDIV                    ((uint16_t)0x00FF)            /*!<I2S Linear prescaler */
//#define  SPI_I2SPR_ODD                       ((uint16_t)0x0100)            /*!<Odd factor for the prescaler */
//#define  SPI_I2SPR_MCKOE                     ((uint16_t)0x0200)            /*!<Master Clock Output Enable */

/******************************************************************************/
/*                                                                            */
/*                       System Configuration (SYSCFG)                        */
/*                                                                            */
/******************************************************************************/
/*****************  Bit definition for SYSCFG_CFGR1 register  ****************/
#define SYSCFG_CFGR1_MEM_MODE               ((uint32_t)0x00000003) /*!< SYSCFG_Memory Remap Config */
#define SYSCFG_CFGR1_MEM_MODE_0             ((uint32_t)0x00000001) /*!< SYSCFG_Memory Remap Config Bit 0 */
#define SYSCFG_CFGR1_MEM_MODE_1             ((uint32_t)0x00000002) /*!< SYSCFG_Memory Remap Config Bit 1 */
#define SYSCFG_CFGR1_IRDA_ENV_SEL           ((uint32_t)0x000000C0) /*!< IRDA_SEL_ENV config */
#define SYSCFG_CFGR1_IRDA_ENV_SEL_0         ((uint32_t)0x00000040) /*!< IRDA_SEL_ENV Bit 0 */
#define SYSCFG_CFGR1_IRDA_ENV_SEL_1         ((uint32_t)0x00000080) /*!< IRDA_SEL_ENV Bit 1 */
#define SYSCFG_CFGR1_ADC_DMA_RMP            ((uint32_t)0x00000100) /*!< ADC DMA remap */
#define SYSCFG_CFGR1_USART1TX_DMA_RMP       ((uint32_t)0x00000200) /*!< USART1 TX DMA remap */
#define SYSCFG_CFGR1_USART1RX_DMA_RMP       ((uint32_t)0x00000400) /*!< USART1 RX DMA remap */
#define SYSCFG_CFGR1_TIM16_DMA_RMP          ((uint32_t)0x00000800) /*!< Timer 16 DMA remap */
#define SYSCFG_CFGR1_TIM17_DMA_RMP          ((uint32_t)0x00001000) /*!< Timer 17 DMA remap */
#define SYSCFG_CFGR1_I2C_PB6_FMP            ((uint32_t)0x00010000) /*!< I2C PB6 Fast mode plus */
#define SYSCFG_CFGR1_I2C_PB7_FMP            ((uint32_t)0x00020000) /*!< I2C PB7 Fast mode plus */
#define SYSCFG_CFGR1_I2C_PB8_FMP            ((uint32_t)0x00040000) /*!< I2C PB8 Fast mode plus */
#define SYSCFG_CFGR1_I2C_PB9_FMP            ((uint32_t)0x00080000) /*!< I2C PB9 Fast mode plus */
#define SYSCFG_CFGR1_I2C1_FMP               ((uint32_t)0x00100000) /*!< I2C PB9 Fast mode plus */


/* Old bit definition maintained for legacy purpose */
#define SYSCFG_CFGR1_I2C_FMP_PB6               SYSCFG_CFGR1_I2C_PB6_FMP
#define SYSCFG_CFGR1_I2C_FMP_PB7               SYSCFG_CFGR1_I2C_PB7_FMP
#define SYSCFG_CFGR1_I2C_FMP_PB8               SYSCFG_CFGR1_I2C_PB8_FMP
#define SYSCFG_CFGR1_I2C_FMP_PB9               SYSCFG_CFGR1_I2C_PB9_FMP



/*****************  Bit definition for SYSCFG_EXTICR1 register  ***************/
#define SYSCFG_EXTICR1_EXTI0            ((uint16_t)0x000F) /*!< EXTI 0 configuration */
#define SYSCFG_EXTICR1_EXTI1            ((uint16_t)0x00F0) /*!< EXTI 1 configuration */
#define SYSCFG_EXTICR1_EXTI2            ((uint16_t)0x0F00) /*!< EXTI 2 configuration */
#define SYSCFG_EXTICR1_EXTI3            ((uint16_t)0xF000) /*!< EXTI 3 configuration */

/**
  * @brief  EXTI0 configuration
  */
#define SYSCFG_EXTICR1_EXTI0_PA         ((uint16_t)0x0000) /*!< PA[0] pin */
#define SYSCFG_EXTICR1_EXTI0_PB         ((uint16_t)0x0001) /*!< PB[0] pin */
#define SYSCFG_EXTICR1_EXTI0_PC         ((uint16_t)0x0002) /*!< PC[0] pin */
//#define SYSCFG_EXTICR1_EXTI0_PD         ((uint16_t)0x0003) /*!< PD[0] pin */
//#define SYSCFG_EXTICR1_EXTI0_PE         ((uint16_t)0x0004) /*!< PE[0] pin */
#define SYSCFG_EXTICR1_EXTI0_PF         ((uint16_t)0x0005) /*!< PF[0] pin */

/**
  * @brief  EXTI1 configuration
  */
#define SYSCFG_EXTICR1_EXTI1_PA         ((uint16_t)0x0000) /*!< PA[1] pin */
#define SYSCFG_EXTICR1_EXTI1_PB         ((uint16_t)0x0010) /*!< PB[1] pin */
#define SYSCFG_EXTICR1_EXTI1_PC         ((uint16_t)0x0020) /*!< PC[1] pin */
//#define SYSCFG_EXTICR1_EXTI1_PD         ((uint16_t)0x0030) /*!< PD[1] pin */
//#define SYSCFG_EXTICR1_EXTI1_PE         ((uint16_t)0x0040) /*!< PE[1] pin */
#define SYSCFG_EXTICR1_EXTI1_PF         ((uint16_t)0x0050) /*!< PF[1] pin */

/**
  * @brief  EXTI2 configuration
  */
#define SYSCFG_EXTICR1_EXTI2_PA         ((uint16_t)0x0000) /*!< PA[2] pin */
#define SYSCFG_EXTICR1_EXTI2_PB         ((uint16_t)0x0100) /*!< PB[2] pin */
#define SYSCFG_EXTICR1_EXTI2_PC         ((uint16_t)0x0200) /*!< PC[2] pin */
#define SYSCFG_EXTICR1_EXTI2_PD         ((uint16_t)0x0300) /*!< PD[2] pin */
//#define SYSCFG_EXTICR1_EXTI2_PE         ((uint16_t)0x0400) /*!< PE[2] pin */
//#define SYSCFG_EXTICR1_EXTI2_PF         ((uint16_t)0x0500) /*!< PF[2] pin */

/**
  * @brief  EXTI3 configuration
  */
#define SYSCFG_EXTICR1_EXTI3_PA         ((uint16_t)0x0000) /*!< PA[3] pin */
#define SYSCFG_EXTICR1_EXTI3_PB         ((uint16_t)0x1000) /*!< PB[3] pin */
#define SYSCFG_EXTICR1_EXTI3_PC         ((uint16_t)0x2000) /*!< PC[3] pin */
//#define SYSCFG_EXTICR1_EXTI3_PD         ((uint16_t)0x3000) /*!< PD[3] pin */
//#define SYSCFG_EXTICR1_EXTI3_PE         ((uint16_t)0x4000) /*!< PE[3] pin */
//#define SYSCFG_EXTICR1_EXTI3_PF         ((uint16_t)0x5000) /*!< PF[3] pin */

/*****************  Bit definition for SYSCFG_EXTICR2 register  *****************/
#define SYSCFG_EXTICR2_EXTI4            ((uint16_t)0x000F) /*!< EXTI 4 configuration */
#define SYSCFG_EXTICR2_EXTI5            ((uint16_t)0x00F0) /*!< EXTI 5 configuration */
#define SYSCFG_EXTICR2_EXTI6            ((uint16_t)0x0F00) /*!< EXTI 6 configuration */
#define SYSCFG_EXTICR2_EXTI7            ((uint16_t)0xF000) /*!< EXTI 7 configuration */

/**
  * @brief  EXTI4 configuration
  */
#define SYSCFG_EXTICR2_EXTI4_PA         ((uint16_t)0x0000) /*!< PA[4] pin */
#define SYSCFG_EXTICR2_EXTI4_PB         ((uint16_t)0x0001) /*!< PB[4] pin */
#define SYSCFG_EXTICR2_EXTI4_PC         ((uint16_t)0x0002) /*!< PC[4] pin */
//#define SYSCFG_EXTICR2_EXTI4_PD         ((uint16_t)0x0003) /*!< PD[4] pin */
//#define SYSCFG_EXTICR2_EXTI4_PE         ((uint16_t)0x0004) /*!< PE[4] pin */
#define SYSCFG_EXTICR2_EXTI4_PF         ((uint16_t)0x0005) /*!< PF[4] pin */

/**
  * @brief  EXTI5 configuration
  */
#define SYSCFG_EXTICR2_EXTI5_PA         ((uint16_t)0x0000) /*!< PA[5] pin */
#define SYSCFG_EXTICR2_EXTI5_PB         ((uint16_t)0x0010) /*!< PB[5] pin */
#define SYSCFG_EXTICR2_EXTI5_PC         ((uint16_t)0x0020) /*!< PC[5] pin */
//#define SYSCFG_EXTICR2_EXTI5_PD         ((uint16_t)0x0030) /*!< PD[5] pin */
//#define SYSCFG_EXTICR2_EXTI5_PE         ((uint16_t)0x0040) /*!< PE[5] pin */
#define SYSCFG_EXTICR2_EXTI5_PF         ((uint16_t)0x0050) /*!< PF[5] pin */

/**
  * @brief  EXTI6 configuration
  */
#define SYSCFG_EXTICR2_EXTI6_PA         ((uint16_t)0x0000) /*!< PA[6] pin */
#define SYSCFG_EXTICR2_EXTI6_PB         ((uint16_t)0x0100) /*!< PB[6] pin */
#define SYSCFG_EXTICR2_EXTI6_PC         ((uint16_t)0x0200) /*!< PC[6] pin */
//#define SYSCFG_EXTICR2_EXTI6_PD         ((uint16_t)0x0300) /*!< PD[6] pin */
//#define SYSCFG_EXTICR2_EXTI6_PE         ((uint16_t)0x0400) /*!< PE[6] pin */
#define SYSCFG_EXTICR2_EXTI6_PF         ((uint16_t)0x0500) /*!< PF[6] pin */

/**
  * @brief  EXTI7 configuration
  */
#define SYSCFG_EXTICR2_EXTI7_PA         ((uint16_t)0x0000) /*!< PA[7] pin */
#define SYSCFG_EXTICR2_EXTI7_PB         ((uint16_t)0x1000) /*!< PB[7] pin */
#define SYSCFG_EXTICR2_EXTI7_PC         ((uint16_t)0x2000) /*!< PC[7] pin */
//#define SYSCFG_EXTICR2_EXTI7_PD         ((uint16_t)0x3000) /*!< PD[7] pin */
//#define SYSCFG_EXTICR2_EXTI7_PE         ((uint16_t)0x4000) /*!< PE[7] pin */
#define SYSCFG_EXTICR2_EXTI7_PF         ((uint16_t)0x5000) /*!< PF[7] pin */

/*****************  Bit definition for SYSCFG_EXTICR3 register  *****************/
#define SYSCFG_EXTICR3_EXTI8            ((uint16_t)0x000F) /*!< EXTI 8 configuration */
#define SYSCFG_EXTICR3_EXTI9            ((uint16_t)0x00F0) /*!< EXTI 9 configuration */
#define SYSCFG_EXTICR3_EXTI10           ((uint16_t)0x0F00) /*!< EXTI 10 configuration */
#define SYSCFG_EXTICR3_EXTI11           ((uint16_t)0xF000) /*!< EXTI 11 configuration */

/**
  * @brief  EXTI8 configuration
  */
#define SYSCFG_EXTICR3_EXTI8_PA         ((uint16_t)0x0000) /*!< PA[8] pin */
#define SYSCFG_EXTICR3_EXTI8_PB         ((uint16_t)0x0001) /*!< PB[8] pin */
#define SYSCFG_EXTICR3_EXTI8_PC         ((uint16_t)0x0002) /*!< PC[8] pin */
//#define SYSCFG_EXTICR3_EXTI8_PD         ((uint16_t)0x0003) /*!< PD[8] pin */
//#define SYSCFG_EXTICR3_EXTI8_PE         ((uint16_t)0x0004) /*!< PE[8] pin */

/**
  * @brief  EXTI9 configuration
  */
#define SYSCFG_EXTICR3_EXTI9_PA         ((uint16_t)0x0000) /*!< PA[9] pin */
#define SYSCFG_EXTICR3_EXTI9_PB         ((uint16_t)0x0010) /*!< PB[9] pin */
#define SYSCFG_EXTICR3_EXTI9_PC         ((uint16_t)0x0020) /*!< PC[9] pin */
//#define SYSCFG_EXTICR3_EXTI9_PD         ((uint16_t)0x0030) /*!< PD[9] pin */
//#define SYSCFG_EXTICR3_EXTI9_PE         ((uint16_t)0x0040) /*!< PE[9] pin */
//#define SYSCFG_EXTICR3_EXTI9_PF         ((uint16_t)0x0050) /*!< PF[9] pin */

/**
  * @brief  EXTI10 configuration
  */
#define SYSCFG_EXTICR3_EXTI10_PA        ((uint16_t)0x0000) /*!< PA[10] pin */
#define SYSCFG_EXTICR3_EXTI10_PB        ((uint16_t)0x0100) /*!< PB[10] pin */
#define SYSCFG_EXTICR3_EXTI10_PC        ((uint16_t)0x0200) /*!< PC[10] pin */
//#define SYSCFG_EXTICR3_EXTI10_PD        ((uint16_t)0x0300) /*!< PE[10] pin */
//#define SYSCFG_EXTICR3_EXTI10_PE        ((uint16_t)0x0400) /*!< PD[10] pin */
//#define SYSCFG_EXTICR3_EXTI10_PF        ((uint16_t)0x0500) /*!< PF[10] pin */

/**
  * @brief  EXTI11 configuration
  */
#define SYSCFG_EXTICR3_EXTI11_PA        ((uint16_t)0x0000) /*!< PA[11] pin */
#define SYSCFG_EXTICR3_EXTI11_PB        ((uint16_t)0x1000) /*!< PB[11] pin */
#define SYSCFG_EXTICR3_EXTI11_PC        ((uint16_t)0x2000) /*!< PC[11] pin */
//#define SYSCFG_EXTICR3_EXTI11_PD        ((uint16_t)0x3000) /*!< PD[11] pin */
//#define SYSCFG_EXTICR3_EXTI11_PE        ((uint16_t)0x4000) /*!< PE[11] pin */

/*****************  Bit definition for SYSCFG_EXTICR4 register  *****************/
#define SYSCFG_EXTICR4_EXTI12           ((uint16_t)0x000F) /*!< EXTI 12 configuration */
#define SYSCFG_EXTICR4_EXTI13           ((uint16_t)0x00F0) /*!< EXTI 13 configuration */
#define SYSCFG_EXTICR4_EXTI14           ((uint16_t)0x0F00) /*!< EXTI 14 configuration */
#define SYSCFG_EXTICR4_EXTI15           ((uint16_t)0xF000) /*!< EXTI 15 configuration */

/**
  * @brief  EXTI12 configuration
  */
#define SYSCFG_EXTICR4_EXTI12_PA        ((uint16_t)0x0000) /*!< PA[12] pin */
#define SYSCFG_EXTICR4_EXTI12_PB        ((uint16_t)0x0001) /*!< PB[12] pin */
#define SYSCFG_EXTICR4_EXTI12_PC        ((uint16_t)0x0002) /*!< PC[12] pin */
//#define SYSCFG_EXTICR4_EXTI12_PD        ((uint16_t)0x0003) /*!< PD[12] pin */
//#define SYSCFG_EXTICR4_EXTI12_PE        ((uint16_t)0x0004) /*!< PE[12] pin */

/**
  * @brief  EXTI13 configuration
  */
#define SYSCFG_EXTICR4_EXTI13_PA        ((uint16_t)0x0000) /*!< PA[13] pin */
#define SYSCFG_EXTICR4_EXTI13_PB        ((uint16_t)0x0010) /*!< PB[13] pin */
#define SYSCFG_EXTICR4_EXTI13_PC        ((uint16_t)0x0020) /*!< PC[13] pin */
//#define SYSCFG_EXTICR4_EXTI13_PD        ((uint16_t)0x0030) /*!< PD[13] pin */
//#define SYSCFG_EXTICR4_EXTI13_PE        ((uint16_t)0x0040) /*!< PE[13] pin */

/**
  * @brief  EXTI14 configuration
  */
#define SYSCFG_EXTICR4_EXTI14_PA        ((uint16_t)0x0000) /*!< PA[14] pin */
#define SYSCFG_EXTICR4_EXTI14_PB        ((uint16_t)0x0100) /*!< PB[14] pin */
#define SYSCFG_EXTICR4_EXTI14_PC        ((uint16_t)0x0200) /*!< PC[14] pin */
//#define SYSCFG_EXTICR4_EXTI14_PD        ((uint16_t)0x0300) /*!< PD[14] pin */
//#define SYSCFG_EXTICR4_EXTI14_PE        ((uint16_t)0x0400) /*!< PE[14] pin */

/**
  * @brief  EXTI15 configuration
  */
#define SYSCFG_EXTICR4_EXTI15_PA        ((uint16_t)0x0000) /*!< PA[15] pin */
#define SYSCFG_EXTICR4_EXTI15_PB        ((uint16_t)0x1000) /*!< PB[15] pin */
#define SYSCFG_EXTICR4_EXTI15_PC        ((uint16_t)0x2000) /*!< PC[15] pin */
//#define SYSCFG_EXTICR4_EXTI15_PD        ((uint16_t)0x3000) /*!< PD[15] pin */
//#define SYSCFG_EXTICR4_EXTI15_PE        ((uint16_t)0x4000) /*!< PE[15] pin */

/*****************  Bit definition for SYSCFG_CFGR2 register  ****************/
#define SYSCFG_CFGR2_LOCKUP_LOCK               ((uint32_t)0x00000001) /*!< Enables and locks the PVD connection with Timer1 Break Input and also the PVD_EN and PVDSEL[2:0] bits of the Power Control Interface */
#define SYSCFG_CFGR2_PVD_LOCK                  ((uint32_t)0x00000004) /*!< Enables and locks the LOCKUP (Hardfault) output of CortexM0 with Break Input of TIMER1 */

/* Old Bit definition maintained for legacy purpose */


/*****************  Bit definition for SYSCFG_xxx ISR Wrapper register  ****************/
//#define SYSCFG_ITLINE0_SR_EWDG                ((uint32_t)0x00000001) /*!< EWDG interrupt */
//#define SYSCFG_ITLINE1_SR_PVDOUT              ((uint32_t)0x00000001) /*!< Power voltage detection -> exti[31] Interrupt */
//#define SYSCFG_ITLINE1_SR_VDDIO2              ((uint32_t)0x00000002) /*!< VDDIO2 -> exti[16] Interrupt */
//#define SYSCFG_ITLINE2_SR_RTC_WAKEUP          ((uint32_t)0x00000001) /*!< RTC WAKEUP -> exti[20] Interrupt */
//#define SYSCFG_ITLINE2_SR_RTC_TSTAMP          ((uint32_t)0x00000002) /*!< RTC Time Stamp -> exti[19] interrupt */
//#define SYSCFG_ITLINE2_SR_RTC_ALRA            ((uint32_t)0x00000003) /*!< RTC Alarm -> exti[17] interrupt .... */
//#define SYSCFG_ITLINE3_SR_FLASH_ITF           ((uint32_t)0x00000001) /*!< Flash ITF Interrupt */
//#define SYSCFG_ITLINE4_SR_CRS                 ((uint32_t)0x00000001) /*!< CRS interrupt */
//#define SYSCFG_ITLINE4_SR_CLK_CTRL            ((uint32_t)0x00000002) /*!< CLK CTRL interrupt */
//#define SYSCFG_ITLINE5_SR_EXTI0               ((uint32_t)0x00000001) /*!< External Interrupt 0 */
//#define SYSCFG_ITLINE5_SR_EXTI1               ((uint32_t)0x00000002) /*!< External Interrupt 1 */
//#define SYSCFG_ITLINE6_SR_EXTI2               ((uint32_t)0x00000001) /*!< External Interrupt 2 */
//#define SYSCFG_ITLINE6_SR_EXTI3               ((uint32_t)0x00000002) /*!< External Interrupt 3 */
//#define SYSCFG_ITLINE7_SR_EXTI4               ((uint32_t)0x00000001) /*!< External Interrupt 15 to 4 */
//#define SYSCFG_ITLINE7_SR_EXTI5               ((uint32_t)0x00000002) /*!< External Interrupt 15 to 4 */
//#define SYSCFG_ITLINE7_SR_EXTI6               ((uint32_t)0x00000004) /*!< External Interrupt 15 to 4 */
//#define SYSCFG_ITLINE7_SR_EXTI7               ((uint32_t)0x00000008) /*!< External Interrupt 15 to 4 */
//#define SYSCFG_ITLINE7_SR_EXTI8               ((uint32_t)0x00000010) /*!< External Interrupt 15 to 4 */
//#define SYSCFG_ITLINE7_SR_EXTI9               ((uint32_t)0x00000020) /*!< External Interrupt 15 to 4 */
//#define SYSCFG_ITLINE7_SR_EXTI10              ((uint32_t)0x00000040) /*!< External Interrupt 15 to 4 */
//#define SYSCFG_ITLINE7_SR_EXTI11              ((uint32_t)0x00000080) /*!< External Interrupt 15 to 4 */
//#define SYSCFG_ITLINE7_SR_EXTI12              ((uint32_t)0x00000100) /*!< External Interrupt 15 to 4 */
//#define SYSCFG_ITLINE7_SR_EXTI13              ((uint32_t)0x00000200) /*!< External Interrupt 15 to 4 */
//#define SYSCFG_ITLINE7_SR_EXTI14              ((uint32_t)0x00000400) /*!< External Interrupt 15 to 4 */
//#define SYSCFG_ITLINE7_SR_EXTI15              ((uint32_t)0x00000800) /*!< External Interrupt 15 to 4 */
//#define SYSCFG_ITLINE8_SR_TSC_EOA             ((uint32_t)0x00000001) /*!< Touch control EOA Interrupt */
//#define SYSCFG_ITLINE8_SR_TSC_MCE             ((uint32_t)0x00000002) /*!< Touch control MCE Interrupt */
//#define SYSCFG_ITLINE9_SR_DMA1_CH1            ((uint32_t)0x00000001) /*!< DMA1 Channel 1 Interrupt */
//#define SYSCFG_ITLINE10_SR_DMA1_CH2           ((uint32_t)0x00000001) /*!< DMA1 Channel 2 Interrupt */
//#define SYSCFG_ITLINE10_SR_DMA1_CH3           ((uint32_t)0x00000002) /*!< DMA2 Channel 3 Interrupt */
//#define SYSCFG_ITLINE10_SR_DMA2_CH1           ((uint32_t)0x00000004) /*!< DMA2 Channel 1 Interrupt */
//#define SYSCFG_ITLINE10_SR_DMA2_CH2           ((uint32_t)0x00000008) /*!< DMA2 Channel 2 Interrupt */
//#define SYSCFG_ITLINE11_SR_DMA1_CH4           ((uint32_t)0x00000001) /*!< DMA1 Channel 4 Interrupt */
//#define SYSCFG_ITLINE11_SR_DMA1_CH5           ((uint32_t)0x00000002) /*!< DMA1 Channel 5 Interrupt */
//#define SYSCFG_ITLINE11_SR_DMA1_CH6           ((uint32_t)0x00000004) /*!< DMA1 Channel 6 Interrupt */
//#define SYSCFG_ITLINE11_SR_DMA1_CH7           ((uint32_t)0x00000008) /*!< DMA1 Channel 7 Interrupt */
//#define SYSCFG_ITLINE11_SR_DMA2_CH3           ((uint32_t)0x00000010) /*!< DMA2 Channel 3 Interrupt */
//#define SYSCFG_ITLINE11_SR_DMA2_CH4           ((uint32_t)0x00000020) /*!< DMA2 Channel 4 Interrupt */
//#define SYSCFG_ITLINE11_SR_DMA2_CH5           ((uint32_t)0x00000040) /*!< DMA2 Channel 5 Interrupt */
//#define SYSCFG_ITLINE12_SR_ADC                ((uint32_t)0x00000001) /*!< ADC Interrupt */
//#define SYSCFG_ITLINE12_SR_COMP1              ((uint32_t)0x00000002) /*!< COMP1 Interrupt -> exti[21] */
//#define SYSCFG_ITLINE12_SR_COMP2              ((uint32_t)0x00000004) /*!< COMP2 Interrupt -> exti[22] */
//#define SYSCFG_ITLINE13_SR_TIM1_BRK           ((uint32_t)0x00000001) /*!< TIM1 BRK Interrupt */
//#define SYSCFG_ITLINE13_SR_TIM1_UPD           ((uint32_t)0x00000002) /*!< TIM1 UPD Interrupt */
//#define SYSCFG_ITLINE13_SR_TIM1_TRG           ((uint32_t)0x00000004) /*!< TIM1 TRG Interrupt */
//#define SYSCFG_ITLINE13_SR_TIM1_CCU           ((uint32_t)0x00000008) /*!< TIM1 CCU Interrupt */
//#define SYSCFG_ITLINE14_SR_TIM1_CC            ((uint32_t)0x00000001) /*!< TIM1 CC Interrupt */
//#define SYSCFG_ITLINE15_SR_TIM2_GLB           ((uint32_t)0x00000001) /*!< TIM2 GLB Interrupt */
//#define SYSCFG_ITLINE16_SR_TIM3_GLB           ((uint32_t)0x00000001) /*!< TIM3 GLB Interrupt */
//#define SYSCFG_ITLINE17_SR_DAC                ((uint32_t)0x00000001) /*!< DAC Interrupt */
//#define SYSCFG_ITLINE17_SR_TIM6_GLB           ((uint32_t)0x00000002) /*!< TIM6 GLB Interrupt */
//#define SYSCFG_ITLINE18_SR_TIM7_GLB           ((uint32_t)0x00000001) /*!< TIM7 GLB Interrupt */
//#define SYSCFG_ITLINE19_SR_TIM14_GLB          ((uint32_t)0x00000001) /*!< TIM14 GLB Interrupt */
//#define SYSCFG_ITLINE20_SR_TIM15_GLB          ((uint32_t)0x00000001) /*!< TIM15 GLB Interrupt */
//#define SYSCFG_ITLINE21_SR_TIM16_GLB          ((uint32_t)0x00000001) /*!< TIM16 GLB Interrupt */
//#define SYSCFG_ITLINE22_SR_TIM17_GLB          ((uint32_t)0x00000001) /*!< TIM17 GLB Interrupt */
//#define SYSCFG_ITLINE23_SR_I2C1_GLB           ((uint32_t)0x00000001) /*!< I2C1 GLB Interrupt -> exti[23] */
//#define SYSCFG_ITLINE24_SR_I2C2_GLB           ((uint32_t)0x00000001) /*!< I2C2 GLB Interrupt */
//#define SYSCFG_ITLINE25_SR_SPI1               ((uint32_t)0x00000001) /*!< SPI1 Interrupt */
//#define SYSCFG_ITLINE26_SR_SPI2               ((uint32_t)0x00000001) /*!< SPI2  Interrupt */
//#define SYSCFG_ITLINE27_SR_USART1_GLB         ((uint32_t)0x00000001) /*!< USART1 GLB Interrupt -> exti[25] */
//#define SYSCFG_ITLINE28_SR_USART2_GLB         ((uint32_t)0x00000001) /*!< USART2 GLB Interrupt -> exti[26] */
//#define SYSCFG_ITLINE29_SR_USART3_GLB         ((uint32_t)0x00000001) /*!< USART3 GLB Interrupt -> exti[28] */
//#define SYSCFG_ITLINE29_SR_USART4_GLB         ((uint32_t)0x00000002) /*!< USART4 GLB Interrupt */
//#define SYSCFG_ITLINE29_SR_USART5_GLB         ((uint32_t)0x00000004) /*!< USART5 GLB Interrupt */
//#define SYSCFG_ITLINE29_SR_USART6_GLB         ((uint32_t)0x00000008) /*!< USART6 GLB Interrupt */
//#define SYSCFG_ITLINE29_SR_USART7_GLB         ((uint32_t)0x00000010) /*!< USART7 GLB Interrupt */
//#define SYSCFG_ITLINE29_SR_USART8_GLB         ((uint32_t)0x00000020) /*!< USART8 GLB Interrupt */
//#define SYSCFG_ITLINE30_SR_CAN                ((uint32_t)0x00000001) /*!< CAN Interrupt */
//#define SYSCFG_ITLINE30_SR_CEC                ((uint32_t)0x00000002) /*!< CEC Interrupt */

/******************************************************************************/
/*                                                                            */
/*                               Timers (TIM)                                 */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for TIM_CR1 register  ********************/
#define  TIM_CR1_CEN                         ((uint16_t)0x0001)            /*!<Counter enable */
#define  TIM_CR1_UDIS                        ((uint16_t)0x0002)            /*!<Update disable */
#define  TIM_CR1_URS                         ((uint16_t)0x0004)            /*!<Update request source */
#define  TIM_CR1_OPM                         ((uint16_t)0x0008)            /*!<One pulse mode */
#define  TIM_CR1_DIR                         ((uint16_t)0x0010)            /*!<Direction */

#define  TIM_CR1_CMS                         ((uint16_t)0x0060)            /*!<CMS[1:0] bits (Center-aligned mode selection) */
#define  TIM_CR1_CMS_0                       ((uint16_t)0x0020)            /*!<Bit 0 */
#define  TIM_CR1_CMS_1                       ((uint16_t)0x0040)            /*!<Bit 1 */

#define  TIM_CR1_ARPE                        ((uint16_t)0x0080)            /*!<Auto-reload preload enable */

#define  TIM_CR1_CKD                         ((uint16_t)0x0300)            /*!<CKD[1:0] bits (clock division) */
#define  TIM_CR1_CKD_0                       ((uint16_t)0x0100)            /*!<Bit 0 */
#define  TIM_CR1_CKD_1                       ((uint16_t)0x0200)            /*!<Bit 1 */

/*******************  Bit definition for TIM_CR2 register  ********************/
#define  TIM_CR2_CCPC                        ((uint16_t)0x0001)            /*!<Capture/Compare Preloaded Control */
#define  TIM_CR2_CCUS                        ((uint16_t)0x0004)            /*!<Capture/Compare Control Update Selection */
#define  TIM_CR2_CCDS                        ((uint16_t)0x0008)            /*!<Capture/Compare DMA Selection */

#define  TIM_CR2_MMS                         ((uint16_t)0x0070)            /*!<MMS[2:0] bits (Master Mode Selection) */
#define  TIM_CR2_MMS_0                       ((uint16_t)0x0010)            /*!<Bit 0 */
#define  TIM_CR2_MMS_1                       ((uint16_t)0x0020)            /*!<Bit 1 */
#define  TIM_CR2_MMS_2                       ((uint16_t)0x0040)            /*!<Bit 2 */

#define  TIM_CR2_TI1S                        ((uint16_t)0x0080)            /*!<TI1 Selection */
#define  TIM_CR2_OIS1                        ((uint16_t)0x0100)            /*!<Output Idle state 1 (OC1 output) */
#define  TIM_CR2_OIS1N                       ((uint16_t)0x0200)            /*!<Output Idle state 1 (OC1N output) */
#define  TIM_CR2_OIS2                        ((uint16_t)0x0400)            /*!<Output Idle state 2 (OC2 output) */
#define  TIM_CR2_OIS2N                       ((uint16_t)0x0800)            /*!<Output Idle state 2 (OC2N output) */
#define  TIM_CR2_OIS3                        ((uint16_t)0x1000)            /*!<Output Idle state 3 (OC3 output) */
#define  TIM_CR2_OIS3N                       ((uint16_t)0x2000)            /*!<Output Idle state 3 (OC3N output) */
#define  TIM_CR2_OIS4                        ((uint16_t)0x4000)            /*!<Output Idle state 4 (OC4 output) */

/*******************  Bit definition for TIM_SMCR register  *******************/
#define  TIM_SMCR_SMS                        ((uint16_t)0x0007)            /*!<SMS[2:0] bits (Slave mode selection) */
#define  TIM_SMCR_SMS_0                      ((uint16_t)0x0001)            /*!<Bit 0 */
#define  TIM_SMCR_SMS_1                      ((uint16_t)0x0002)            /*!<Bit 1 */
#define  TIM_SMCR_SMS_2                      ((uint16_t)0x0004)            /*!<Bit 2 */

#define  TIM_SMCR_OCCS                       ((uint16_t)0x0008)            /*!< OCREF clear selection */

#define  TIM_SMCR_TS                         ((uint16_t)0x0070)            /*!<TS[2:0] bits (Trigger selection) */
#define  TIM_SMCR_TS_0                       ((uint16_t)0x0010)            /*!<Bit 0 */
#define  TIM_SMCR_TS_1                       ((uint16_t)0x0020)            /*!<Bit 1 */
#define  TIM_SMCR_TS_2                       ((uint16_t)0x0040)            /*!<Bit 2 */

#define  TIM_SMCR_MSM                        ((uint16_t)0x0080)            /*!<Master/slave mode */

#define  TIM_SMCR_ETF                        ((uint16_t)0x0F00)            /*!<ETF[3:0] bits (External trigger filter) */
#define  TIM_SMCR_ETF_0                      ((uint16_t)0x0100)            /*!<Bit 0 */
#define  TIM_SMCR_ETF_1                      ((uint16_t)0x0200)            /*!<Bit 1 */
#define  TIM_SMCR_ETF_2                      ((uint16_t)0x0400)            /*!<Bit 2 */
#define  TIM_SMCR_ETF_3                      ((uint16_t)0x0800)            /*!<Bit 3 */

#define  TIM_SMCR_ETPS                       ((uint16_t)0x3000)            /*!<ETPS[1:0] bits (External trigger prescaler) */
#define  TIM_SMCR_ETPS_0                     ((uint16_t)0x1000)            /*!<Bit 0 */
#define  TIM_SMCR_ETPS_1                     ((uint16_t)0x2000)            /*!<Bit 1 */

#define  TIM_SMCR_ECE                        ((uint16_t)0x4000)            /*!<External clock enable */
#define  TIM_SMCR_ETP                        ((uint16_t)0x8000)            /*!<External trigger polarity */

/*******************  Bit definition for TIM_DIER register  *******************/
#define  TIM_DIER_UIE                        ((uint16_t)0x0001)            /*!<Update interrupt enable */
#define  TIM_DIER_CC1IE                      ((uint16_t)0x0002)            /*!<Capture/Compare 1 interrupt enable */
#define  TIM_DIER_CC2IE                      ((uint16_t)0x0004)            /*!<Capture/Compare 2 interrupt enable */
#define  TIM_DIER_CC3IE                      ((uint16_t)0x0008)            /*!<Capture/Compare 3 interrupt enable */
#define  TIM_DIER_CC4IE                      ((uint16_t)0x0010)            /*!<Capture/Compare 4 interrupt enable */
#define  TIM_DIER_COMIE                      ((uint16_t)0x0020)            /*!<COM interrupt enable */
#define  TIM_DIER_TIE                        ((uint16_t)0x0040)            /*!<Trigger interrupt enable */
#define  TIM_DIER_BIE                        ((uint16_t)0x0080)            /*!<Break interrupt enable */
#define  TIM_DIER_UDE                        ((uint16_t)0x0100)            /*!<Update DMA request enable */
#define  TIM_DIER_CC1DE                      ((uint16_t)0x0200)            /*!<Capture/Compare 1 DMA request enable */
#define  TIM_DIER_CC2DE                      ((uint16_t)0x0400)            /*!<Capture/Compare 2 DMA request enable */
#define  TIM_DIER_CC3DE                      ((uint16_t)0x0800)            /*!<Capture/Compare 3 DMA request enable */
#define  TIM_DIER_CC4DE                      ((uint16_t)0x1000)            /*!<Capture/Compare 4 DMA request enable */
#define  TIM_DIER_COMDE                      ((uint16_t)0x2000)            /*!<COM DMA request enable */
#define  TIM_DIER_TDE                        ((uint16_t)0x4000)            /*!<Trigger DMA request enable */

/********************  Bit definition for TIM_SR register  ********************/
#define  TIM_SR_UIF                          ((uint16_t)0x0001)            /*!<Update interrupt Flag */
#define  TIM_SR_CC1IF                        ((uint16_t)0x0002)            /*!<Capture/Compare 1 interrupt Flag */
#define  TIM_SR_CC2IF                        ((uint16_t)0x0004)            /*!<Capture/Compare 2 interrupt Flag */
#define  TIM_SR_CC3IF                        ((uint16_t)0x0008)            /*!<Capture/Compare 3 interrupt Flag */
#define  TIM_SR_CC4IF                        ((uint16_t)0x0010)            /*!<Capture/Compare 4 interrupt Flag */
#define  TIM_SR_COMIF                        ((uint16_t)0x0020)            /*!<COM interrupt Flag */
#define  TIM_SR_TIF                          ((uint16_t)0x0040)            /*!<Trigger interrupt Flag */
#define  TIM_SR_BIF                          ((uint16_t)0x0080)            /*!<Break interrupt Flag */
#define  TIM_SR_CC1OF                        ((uint16_t)0x0200)            /*!<Capture/Compare 1 Overcapture Flag */
#define  TIM_SR_CC2OF                        ((uint16_t)0x0400)            /*!<Capture/Compare 2 Overcapture Flag */
#define  TIM_SR_CC3OF                        ((uint16_t)0x0800)            /*!<Capture/Compare 3 Overcapture Flag */
#define  TIM_SR_CC4OF                        ((uint16_t)0x1000)            /*!<Capture/Compare 4 Overcapture Flag */

/*******************  Bit definition for TIM_EGR register  ********************/
#define  TIM_EGR_UG                          ((uint8_t)0x01)               /*!<Update Generation */
#define  TIM_EGR_CC1G                        ((uint8_t)0x02)               /*!<Capture/Compare 1 Generation */
#define  TIM_EGR_CC2G                        ((uint8_t)0x04)               /*!<Capture/Compare 2 Generation */
#define  TIM_EGR_CC3G                        ((uint8_t)0x08)               /*!<Capture/Compare 3 Generation */
#define  TIM_EGR_CC4G                        ((uint8_t)0x10)               /*!<Capture/Compare 4 Generation */
#define  TIM_EGR_COMG                        ((uint8_t)0x20)               /*!<Capture/Compare Control Update Generation */
#define  TIM_EGR_TG                          ((uint8_t)0x40)               /*!<Trigger Generation */
#define  TIM_EGR_BG                          ((uint8_t)0x80)               /*!<Break Generation */

/******************  Bit definition for TIM_CCMR1 register  *******************/
#define  TIM_CCMR1_CC1S                      ((uint16_t)0x0003)            /*!<CC1S[1:0] bits (Capture/Compare 1 Selection) */
#define  TIM_CCMR1_CC1S_0                    ((uint16_t)0x0001)            /*!<Bit 0 */
#define  TIM_CCMR1_CC1S_1                    ((uint16_t)0x0002)            /*!<Bit 1 */

#define  TIM_CCMR1_OC1FE                     ((uint16_t)0x0004)            /*!<Output Compare 1 Fast enable */
#define  TIM_CCMR1_OC1PE                     ((uint16_t)0x0008)            /*!<Output Compare 1 Preload enable */

#define  TIM_CCMR1_OC1M                      ((uint16_t)0x0070)            /*!<OC1M[2:0] bits (Output Compare 1 Mode) */
#define  TIM_CCMR1_OC1M_0                    ((uint16_t)0x0010)            /*!<Bit 0 */
#define  TIM_CCMR1_OC1M_1                    ((uint16_t)0x0020)            /*!<Bit 1 */
#define  TIM_CCMR1_OC1M_2                    ((uint16_t)0x0040)            /*!<Bit 2 */

#define  TIM_CCMR1_OC1CE                     ((uint16_t)0x0080)            /*!<Output Compare 1Clear Enable */

#define  TIM_CCMR1_CC2S                      ((uint16_t)0x0300)            /*!<CC2S[1:0] bits (Capture/Compare 2 Selection) */
#define  TIM_CCMR1_CC2S_0                    ((uint16_t)0x0100)            /*!<Bit 0 */
#define  TIM_CCMR1_CC2S_1                    ((uint16_t)0x0200)            /*!<Bit 1 */

#define  TIM_CCMR1_OC2FE                     ((uint16_t)0x0400)            /*!<Output Compare 2 Fast enable */
#define  TIM_CCMR1_OC2PE                     ((uint16_t)0x0800)            /*!<Output Compare 2 Preload enable */

#define  TIM_CCMR1_OC2M                      ((uint16_t)0x7000)            /*!<OC2M[2:0] bits (Output Compare 2 Mode) */
#define  TIM_CCMR1_OC2M_0                    ((uint16_t)0x1000)            /*!<Bit 0 */
#define  TIM_CCMR1_OC2M_1                    ((uint16_t)0x2000)            /*!<Bit 1 */
#define  TIM_CCMR1_OC2M_2                    ((uint16_t)0x4000)            /*!<Bit 2 */

#define  TIM_CCMR1_OC2CE                     ((uint16_t)0x8000)            /*!<Output Compare 2 Clear Enable */

/*----------------------------------------------------------------------------*/

#define  TIM_CCMR1_IC1PSC                    ((uint16_t)0x000C)            /*!<IC1PSC[1:0] bits (Input Capture 1 Prescaler) */
#define  TIM_CCMR1_IC1PSC_0                  ((uint16_t)0x0004)            /*!<Bit 0 */
#define  TIM_CCMR1_IC1PSC_1                  ((uint16_t)0x0008)            /*!<Bit 1 */

#define  TIM_CCMR1_IC1F                      ((uint16_t)0x00F0)            /*!<IC1F[3:0] bits (Input Capture 1 Filter) */
#define  TIM_CCMR1_IC1F_0                    ((uint16_t)0x0010)            /*!<Bit 0 */
#define  TIM_CCMR1_IC1F_1                    ((uint16_t)0x0020)            /*!<Bit 1 */
#define  TIM_CCMR1_IC1F_2                    ((uint16_t)0x0040)            /*!<Bit 2 */
#define  TIM_CCMR1_IC1F_3                    ((uint16_t)0x0080)            /*!<Bit 3 */

#define  TIM_CCMR1_IC2PSC                    ((uint16_t)0x0C00)            /*!<IC2PSC[1:0] bits (Input Capture 2 Prescaler) */
#define  TIM_CCMR1_IC2PSC_0                  ((uint16_t)0x0400)            /*!<Bit 0 */
#define  TIM_CCMR1_IC2PSC_1                  ((uint16_t)0x0800)            /*!<Bit 1 */

#define  TIM_CCMR1_IC2F                      ((uint16_t)0xF000)            /*!<IC2F[3:0] bits (Input Capture 2 Filter) */
#define  TIM_CCMR1_IC2F_0                    ((uint16_t)0x1000)            /*!<Bit 0 */
#define  TIM_CCMR1_IC2F_1                    ((uint16_t)0x2000)            /*!<Bit 1 */
#define  TIM_CCMR1_IC2F_2                    ((uint16_t)0x4000)            /*!<Bit 2 */
#define  TIM_CCMR1_IC2F_3                    ((uint16_t)0x8000)            /*!<Bit 3 */

/******************  Bit definition for TIM_CCMR2 register  *******************/
#define  TIM_CCMR2_CC3S                      ((uint16_t)0x0003)            /*!<CC3S[1:0] bits (Capture/Compare 3 Selection) */
#define  TIM_CCMR2_CC3S_0                    ((uint16_t)0x0001)            /*!<Bit 0 */
#define  TIM_CCMR2_CC3S_1                    ((uint16_t)0x0002)            /*!<Bit 1 */

#define  TIM_CCMR2_OC3FE                     ((uint16_t)0x0004)            /*!<Output Compare 3 Fast enable */
#define  TIM_CCMR2_OC3PE                     ((uint16_t)0x0008)            /*!<Output Compare 3 Preload enable */

#define  TIM_CCMR2_OC3M                      ((uint16_t)0x0070)            /*!<OC3M[2:0] bits (Output Compare 3 Mode) */
#define  TIM_CCMR2_OC3M_0                    ((uint16_t)0x0010)            /*!<Bit 0 */
#define  TIM_CCMR2_OC3M_1                    ((uint16_t)0x0020)            /*!<Bit 1 */
#define  TIM_CCMR2_OC3M_2                    ((uint16_t)0x0040)            /*!<Bit 2 */

#define  TIM_CCMR2_OC3CE                     ((uint16_t)0x0080)            /*!<Output Compare 3 Clear Enable */

#define  TIM_CCMR2_CC4S                      ((uint16_t)0x0300)            /*!<CC4S[1:0] bits (Capture/Compare 4 Selection) */
#define  TIM_CCMR2_CC4S_0                    ((uint16_t)0x0100)            /*!<Bit 0 */
#define  TIM_CCMR2_CC4S_1                    ((uint16_t)0x0200)            /*!<Bit 1 */

#define  TIM_CCMR2_OC4FE                     ((uint16_t)0x0400)            /*!<Output Compare 4 Fast enable */
#define  TIM_CCMR2_OC4PE                     ((uint16_t)0x0800)            /*!<Output Compare 4 Preload enable */

#define  TIM_CCMR2_OC4M                      ((uint16_t)0x7000)            /*!<OC4M[2:0] bits (Output Compare 4 Mode) */
#define  TIM_CCMR2_OC4M_0                    ((uint16_t)0x1000)            /*!<Bit 0 */
#define  TIM_CCMR2_OC4M_1                    ((uint16_t)0x2000)            /*!<Bit 1 */
#define  TIM_CCMR2_OC4M_2                    ((uint16_t)0x4000)            /*!<Bit 2 */

#define  TIM_CCMR2_OC4CE                     ((uint16_t)0x8000)            /*!<Output Compare 4 Clear Enable */

/*----------------------------------------------------------------------------*/

#define  TIM_CCMR2_IC3PSC                    ((uint16_t)0x000C)            /*!<IC3PSC[1:0] bits (Input Capture 3 Prescaler) */
#define  TIM_CCMR2_IC3PSC_0                  ((uint16_t)0x0004)            /*!<Bit 0 */
#define  TIM_CCMR2_IC3PSC_1                  ((uint16_t)0x0008)            /*!<Bit 1 */

#define  TIM_CCMR2_IC3F                      ((uint16_t)0x00F0)            /*!<IC3F[3:0] bits (Input Capture 3 Filter) */
#define  TIM_CCMR2_IC3F_0                    ((uint16_t)0x0010)            /*!<Bit 0 */
#define  TIM_CCMR2_IC3F_1                    ((uint16_t)0x0020)            /*!<Bit 1 */
#define  TIM_CCMR2_IC3F_2                    ((uint16_t)0x0040)            /*!<Bit 2 */
#define  TIM_CCMR2_IC3F_3                    ((uint16_t)0x0080)            /*!<Bit 3 */

#define  TIM_CCMR2_IC4PSC                    ((uint16_t)0x0C00)            /*!<IC4PSC[1:0] bits (Input Capture 4 Prescaler) */
#define  TIM_CCMR2_IC4PSC_0                  ((uint16_t)0x0400)            /*!<Bit 0 */
#define  TIM_CCMR2_IC4PSC_1                  ((uint16_t)0x0800)            /*!<Bit 1 */

#define  TIM_CCMR2_IC4F                      ((uint16_t)0xF000)            /*!<IC4F[3:0] bits (Input Capture 4 Filter) */
#define  TIM_CCMR2_IC4F_0                    ((uint16_t)0x1000)            /*!<Bit 0 */
#define  TIM_CCMR2_IC4F_1                    ((uint16_t)0x2000)            /*!<Bit 1 */
#define  TIM_CCMR2_IC4F_2                    ((uint16_t)0x4000)            /*!<Bit 2 */
#define  TIM_CCMR2_IC4F_3                    ((uint16_t)0x8000)            /*!<Bit 3 */

/*******************  Bit definition for TIM_CCER register  *******************/
#define  TIM_CCER_CC1E                       ((uint16_t)0x0001)            /*!<Capture/Compare 1 output enable */
#define  TIM_CCER_CC1P                       ((uint16_t)0x0002)            /*!<Capture/Compare 1 output Polarity */
#define  TIM_CCER_CC1NE                      ((uint16_t)0x0004)            /*!<Capture/Compare 1 Complementary output enable */
#define  TIM_CCER_CC1NP                      ((uint16_t)0x0008)            /*!<Capture/Compare 1 Complementary output Polarity */
#define  TIM_CCER_CC2E                       ((uint16_t)0x0010)            /*!<Capture/Compare 2 output enable */
#define  TIM_CCER_CC2P                       ((uint16_t)0x0020)            /*!<Capture/Compare 2 output Polarity */
#define  TIM_CCER_CC2NE                      ((uint16_t)0x0040)            /*!<Capture/Compare 2 Complementary output enable */
#define  TIM_CCER_CC2NP                      ((uint16_t)0x0080)            /*!<Capture/Compare 2 Complementary output Polarity */
#define  TIM_CCER_CC3E                       ((uint16_t)0x0100)            /*!<Capture/Compare 3 output enable */
#define  TIM_CCER_CC3P                       ((uint16_t)0x0200)            /*!<Capture/Compare 3 output Polarity */
#define  TIM_CCER_CC3NE                      ((uint16_t)0x0400)            /*!<Capture/Compare 3 Complementary output enable */
#define  TIM_CCER_CC3NP                      ((uint16_t)0x0800)            /*!<Capture/Compare 3 Complementary output Polarity */
#define  TIM_CCER_CC4E                       ((uint16_t)0x1000)            /*!<Capture/Compare 4 output enable */
#define  TIM_CCER_CC4P                       ((uint16_t)0x2000)            /*!<Capture/Compare 4 output Polarity */
//#define  TIM_CCER_CC4NP                      ((uint16_t)0x8000)            /*!<Capture/Compare 4 Complementary output Polarity */

/*******************  Bit definition for TIM_CNT register  ********************/
#define  TIM_CNT_CNT                         ((uint16_t)0xFFFF)            /*!<Counter Value */

/*******************  Bit definition for TIM_PSC register  ********************/
#define  TIM_PSC_PSC                         ((uint16_t)0xFFFF)            /*!<Prescaler Value */

/*******************  Bit definition for TIM_ARR register  ********************/
#define  TIM_ARR_ARR                         ((uint16_t)0xFFFF)            /*!<actual auto-reload Value */

/*******************  Bit definition for TIM_RCR register  ********************/
#define  TIM_RCR_REP                         ((uint8_t)0xFF)               /*!<Repetition Counter Value */

/*******************  Bit definition for TIM_CCR1 register  *******************/
#define  TIM_CCR1_CCR1                       ((uint16_t)0xFFFF)            /*!<Capture/Compare 1 Value */

/*******************  Bit definition for TIM_CCR2 register  *******************/
#define  TIM_CCR2_CCR2                       ((uint16_t)0xFFFF)            /*!<Capture/Compare 2 Value */

/*******************  Bit definition for TIM_CCR3 register  *******************/
#define  TIM_CCR3_CCR3                       ((uint16_t)0xFFFF)            /*!<Capture/Compare 3 Value */

/*******************  Bit definition for TIM_CCR4 register  *******************/
#define  TIM_CCR4_CCR4                       ((uint16_t)0xFFFF)            /*!<Capture/Compare 4 Value */

/*******************  Bit definition for TIM_BDTR register  *******************/
#define  TIM_BDTR_DTG                        ((uint16_t)0x00FF)            /*!<DTG[0:7] bits (Dead-Time Generator set-up) */
#define  TIM_BDTR_DTG_0                      ((uint16_t)0x0001)            /*!<Bit 0 */
#define  TIM_BDTR_DTG_1                      ((uint16_t)0x0002)            /*!<Bit 1 */
#define  TIM_BDTR_DTG_2                      ((uint16_t)0x0004)            /*!<Bit 2 */
#define  TIM_BDTR_DTG_3                      ((uint16_t)0x0008)            /*!<Bit 3 */
#define  TIM_BDTR_DTG_4                      ((uint16_t)0x0010)            /*!<Bit 4 */
#define  TIM_BDTR_DTG_5                      ((uint16_t)0x0020)            /*!<Bit 5 */
#define  TIM_BDTR_DTG_6                      ((uint16_t)0x0040)            /*!<Bit 6 */
#define  TIM_BDTR_DTG_7                      ((uint16_t)0x0080)            /*!<Bit 7 */

#define  TIM_BDTR_LOCK                       ((uint16_t)0x0300)            /*!<LOCK[1:0] bits (Lock Configuration) */
#define  TIM_BDTR_LOCK_0                     ((uint16_t)0x0100)            /*!<Bit 0 */
#define  TIM_BDTR_LOCK_1                     ((uint16_t)0x0200)            /*!<Bit 1 */

#define  TIM_BDTR_OSSI                       ((uint16_t)0x0400)            /*!<Off-State Selection for Idle mode */
#define  TIM_BDTR_OSSR                       ((uint16_t)0x0800)            /*!<Off-State Selection for Run mode */
#define  TIM_BDTR_BKE                        ((uint16_t)0x1000)            /*!<Break enable */
#define  TIM_BDTR_BKP                        ((uint16_t)0x2000)            /*!<Break Polarity */
#define  TIM_BDTR_AOE                        ((uint16_t)0x4000)            /*!<Automatic Output enable */
#define  TIM_BDTR_MOE                        ((uint16_t)0x8000)            /*!<Main Output enable */

/*******************  Bit definition for TIM_DCR register  ********************/
#define  TIM_DCR_DBA                         ((uint16_t)0x001F)            /*!<DBA[4:0] bits (DMA Base Address) */
#define  TIM_DCR_DBA_0                       ((uint16_t)0x0001)            /*!<Bit 0 */
#define  TIM_DCR_DBA_1                       ((uint16_t)0x0002)            /*!<Bit 1 */
#define  TIM_DCR_DBA_2                       ((uint16_t)0x0004)            /*!<Bit 2 */
#define  TIM_DCR_DBA_3                       ((uint16_t)0x0008)            /*!<Bit 3 */
#define  TIM_DCR_DBA_4                       ((uint16_t)0x0010)            /*!<Bit 4 */

#define  TIM_DCR_DBL                         ((uint16_t)0x1F00)            /*!<DBL[4:0] bits (DMA Burst Length) */
#define  TIM_DCR_DBL_0                       ((uint16_t)0x0100)            /*!<Bit 0 */
#define  TIM_DCR_DBL_1                       ((uint16_t)0x0200)            /*!<Bit 1 */
#define  TIM_DCR_DBL_2                       ((uint16_t)0x0400)            /*!<Bit 2 */
#define  TIM_DCR_DBL_3                       ((uint16_t)0x0800)            /*!<Bit 3 */
#define  TIM_DCR_DBL_4                       ((uint16_t)0x1000)            /*!<Bit 4 */

/*******************  Bit definition for TIM_DMAR register  *******************/
#define  TIM_DMAR_DMAB                       ((uint16_t)0xFFFF)            /*!<DMA register for burst accesses */

/*******************  Bit definition for TIM_OR register  *********************/
#define TIM14_OR_TI1_RMP                       ((uint16_t)0x0003)            /*!<TI1_RMP[1:0] bits (TIM14 Input 4 remap) */
#define TIM14_OR_TI1_RMP_0                     ((uint16_t)0x0001)            /*!<Bit 0 */
#define TIM14_OR_TI1_RMP_1                     ((uint16_t)0x0002)            /*!<Bit 1 */


/******************************************************************************/
/*                                                                            */
/*      Universal Synchronous Asynchronous Receiver Transmitter (USART)       */
/*                                                                            */
/******************************************************************************/
/******************  Bit definition for USART_CR1 register  *******************/
#define  USART_CR1_UE                        ((uint32_t)0x00000001)            /*!< USART Enable */
#define  USART_CR1_UESM                      ((uint32_t)0x00000002)            /*!< USART Enable in STOP Mode */
#define  USART_CR1_RE                        ((uint32_t)0x00000004)            /*!< Receiver Enable */
#define  USART_CR1_TE                        ((uint32_t)0x00000008)            /*!< Transmitter Enable */
#define  USART_CR1_IDLEIE                    ((uint32_t)0x00000010)            /*!< IDLE Interrupt Enable */
#define  USART_CR1_RXNEIE                    ((uint32_t)0x00000020)            /*!< RXNE Interrupt Enable */
#define  USART_CR1_TCIE                      ((uint32_t)0x00000040)            /*!< Transmission Complete Interrupt Enable */
#define  USART_CR1_TXEIE                     ((uint32_t)0x00000080)            /*!< TXE Interrupt Enable */
#define  USART_CR1_PEIE                      ((uint32_t)0x00000100)            /*!< PE Interrupt Enable */
#define  USART_CR1_PS                        ((uint32_t)0x00000200)            /*!< Parity Selection */
#define  USART_CR1_PCE                       ((uint32_t)0x00000400)            /*!< Parity Control Enable */
#define  USART_CR1_WAKE                      ((uint32_t)0x00000800)            /*!< Receiver Wakeup method */
#define  USART_CR1_M0                        ((uint32_t)0x00001000)            /*!< Word length */
#define  USART_CR1_MME                       ((uint32_t)0x00002000)            /*!< Mute Mode Enable */
#define  USART_CR1_CMIE                      ((uint32_t)0x00004000)            /*!< Character match interrupt enable */
#define  USART_CR1_OVER8                     ((uint32_t)0x00008000)            /*!< Oversampling by 8-bit or 16-bit mode */
#define  USART_CR1_DEDT                      ((uint32_t)0x001F0000)            /*!< DEDT[4:0] bits (Driver Enable Deassertion Time) */
#define  USART_CR1_DEDT_0                    ((uint32_t)0x00010000)            /*!< Bit 0 */
#define  USART_CR1_DEDT_1                    ((uint32_t)0x00020000)            /*!< Bit 1 */
#define  USART_CR1_DEDT_2                    ((uint32_t)0x00040000)            /*!< Bit 2 */
#define  USART_CR1_DEDT_3                    ((uint32_t)0x00080000)            /*!< Bit 3 */
#define  USART_CR1_DEDT_4                    ((uint32_t)0x00100000)            /*!< Bit 4 */
#define  USART_CR1_DEAT                      ((uint32_t)0x03E00000)            /*!< DEAT[4:0] bits (Driver Enable Assertion Time) */
#define  USART_CR1_DEAT_0                    ((uint32_t)0x00200000)            /*!< Bit 0 */
#define  USART_CR1_DEAT_1                    ((uint32_t)0x00400000)            /*!< Bit 1 */
#define  USART_CR1_DEAT_2                    ((uint32_t)0x00800000)            /*!< Bit 2 */
#define  USART_CR1_DEAT_3                    ((uint32_t)0x01000000)            /*!< Bit 3 */
#define  USART_CR1_DEAT_4                    ((uint32_t)0x02000000)            /*!< Bit 4 */
#define  USART_CR1_RTOIE                     ((uint32_t)0x04000000)            /*!< Receive Time Out interrupt enable */
//#define  USART_CR1_EOBIE                     ((uint32_t)0x08000000)            /*!< End of Block interrupt enable */
#define  USART_CR1_M1                        ((uint32_t)0x10000000)            /*!< End of Block interrupt enable */

#define  USART_CR1_M                         USART_CR1_M0
/******************  Bit definition for USART_CR2 register  *******************/
#define  USART_CR2_ADDM7                     ((uint32_t)0x00000010)            /*!< 7-bit or 4-bit Address Detection */
//#define  USART_CR2_LBDL                      ((uint32_t)0x00000020)            /*!< LIN Break Detection Length */
//#define  USART_CR2_LBDIE                     ((uint32_t)0x00000040)            /*!< LIN Break Detection Interrupt Enable */
#define  USART_CR2_LBCL                      ((uint32_t)0x00000100)            /*!< Last Bit Clock pulse */
#define  USART_CR2_CPHA                      ((uint32_t)0x00000200)            /*!< Clock Phase */
#define  USART_CR2_CPOL                      ((uint32_t)0x00000400)            /*!< Clock Polarity */
#define  USART_CR2_CLKEN                     ((uint32_t)0x00000800)            /*!< Clock Enable */
#define  USART_CR2_STOP                      ((uint32_t)0x00003000)            /*!< STOP[1:0] bits (STOP bits) */
#define  USART_CR2_STOP_0                    ((uint32_t)0x00001000)            /*!< Bit 0 */
#define  USART_CR2_STOP_1                    ((uint32_t)0x00002000)            /*!< Bit 1 */
#define  USART_CR2_LINEN                     ((uint32_t)0x00004000)            /*!< LIN mode enable */
#define  USART_CR2_SWAP                      ((uint32_t)0x00008000)            /*!< SWAP TX/RX pins */
#define  USART_CR2_RXINV                     ((uint32_t)0x00010000)            /*!< RX pin active level inversion */
#define  USART_CR2_TXINV                     ((uint32_t)0x00020000)            /*!< TX pin active level inversion */
#define  USART_CR2_DATAINV                   ((uint32_t)0x00040000)            /*!< Binary data inversion */
#define  USART_CR2_MSBFIRST                  ((uint32_t)0x00080000)            /*!< Most Significant Bit First */
#define  USART_CR2_ABRE                      ((uint32_t)0x00100000)            /*!< Auto Baud-Rate Enable*/
#define  USART_CR2_ABRMOD                    ((uint32_t)0x00600000)            /*!< ABRMOD[1:0] bits (Auto Baud-Rate Mode) */
#define  USART_CR2_ABRMOD_0                  ((uint32_t)0x00200000)            /*!< Bit 0 */
#define  USART_CR2_ABRMOD_1                  ((uint32_t)0x00400000)            /*!< Bit 1 */
#define  USART_CR2_RTOEN                     ((uint32_t)0x00800000)            /*!< Receiver Time-Out enable */
#define  USART_CR2_ADD                       ((uint32_t)0xFF000000)            /*!< Address of the USART node */

#define  USART_CR2_ABRMODE                                   USART_CR2_ABRMOD
#define  USART_CR2_ABRMODE_0                 USART_CR2_ABRMOD_0
#define  USART_CR2_ABRMODE_1                 USART_CR2_ABRMOD_1
#define  USART_CR2_ABREN                     USART_CR2_ABRE
/******************  Bit definition for USART_CR3 register  *******************/
#define  USART_CR3_EIE                       ((uint32_t)0x00000001)            /*!< Error Interrupt Enable */
//#define  USART_CR3_IREN                      ((uint32_t)0x00000002)            /*!< IrDA mode Enable */
//#define  USART_CR3_IRLP                      ((uint32_t)0x00000004)            /*!< IrDA Low-Power */
#define  USART_CR3_HDSEL                     ((uint32_t)0x00000008)            /*!< Half-Duplex Selection */
//#define  USART_CR3_NACK                      ((uint32_t)0x00000010)            /*!< SmartCard NACK enable */
//#define  USART_CR3_SCEN                      ((uint32_t)0x00000020)            /*!< SmartCard mode enable */
#define  USART_CR3_DMAR                      ((uint32_t)0x00000040)            /*!< DMA Enable Receiver */
#define  USART_CR3_DMAT                      ((uint32_t)0x00000080)            /*!< DMA Enable Transmitter */
#define  USART_CR3_RTSE                      ((uint32_t)0x00000100)            /*!< RTS Enable */
#define  USART_CR3_CTSE                      ((uint32_t)0x00000200)            /*!< CTS Enable */
#define  USART_CR3_CTSIE                     ((uint32_t)0x00000400)            /*!< CTS Interrupt Enable */
#define  USART_CR3_ONEBIT                    ((uint32_t)0x00000800)            /*!< One sample bit method enable */
#define  USART_CR3_OVRDIS                    ((uint32_t)0x00001000)            /*!< Overrun Disable */
#define  USART_CR3_DDRE                      ((uint32_t)0x00002000)            /*!< DMA Disable on Reception Error */
#define  USART_CR3_DEM                       ((uint32_t)0x00004000)            /*!< Driver Enable Mode */
#define  USART_CR3_DEP                       ((uint32_t)0x00008000)            /*!< Driver Enable Polarity Selection */
//#define  USART_CR3_SCARCNT                   ((uint32_t)0x000E0000)            /*!< SCARCNT[2:0] bits (SmartCard Auto-Retry Count) */
//#define  USART_CR3_SCARCNT_0                 ((uint32_t)0x00020000)            /*!< Bit 0 */
//#define  USART_CR3_SCARCNT_1                 ((uint32_t)0x00040000)            /*!< Bit 1 */
//#define  USART_CR3_SCARCNT_2                 ((uint32_t)0x00080000)            /*!< Bit 2 */
//#define  USART_CR3_WUS                       ((uint32_t)0x00300000)            /*!< WUS[1:0] bits (Wake UP Interrupt Flag Selection) */
//#define  USART_CR3_WUS_0                     ((uint32_t)0x00100000)            /*!< Bit 0 */
//#define  USART_CR3_WUS_1                     ((uint32_t)0x00200000)            /*!< Bit 1 */
//#define  USART_CR3_WUFIE                     ((uint32_t)0x00400000)            /*!< Wake Up Interrupt Enable */

/******************  Bit definition for USART_BRR register  *******************/
//#define  USART_BRR_DIV_FRACTION              ((uint16_t)0x000F)                /*!< Fraction of USARTDIV */
//#define  USART_BRR_DIV_MANTISSA              ((uint16_t)0xFFF0)                /*!< Mantissa of USARTDIV */
#define  USART_BRR_BRR                       ((uint16_t)0xFFFF)                /*!< Fraction of USARTDIV */

/******************  Bit definition for USART_GTPR register  ******************/
#define  USART_GTPR_PSC                      ((uint16_t)0x00FF)                /*!< PSC[7:0] bits (Prescaler value) */
#define  USART_GTPR_GT                       ((uint16_t)0xFF00)                /*!< GT[7:0] bits (Guard time value) */


/*******************  Bit definition for USART_RTOR register  *****************/
#define  USART_RTOR_RTO                      ((uint32_t)0x00FFFFFF)            /*!< Receiver Time Out Value */
//#define  USART_RTOR_BLEN                     ((uint32_t)0xFF000000)            /*!< Block Length */

/*******************  Bit definition for USART_RQR register  ******************/
#define  USART_RQR_ABRRQ                    ((uint16_t)0x0001)                /*!< Auto-Baud Rate Request */
#define  USART_RQR_SBKRQ                    ((uint16_t)0x0002)                /*!< Send Break Request */
#define  USART_RQR_MMRQ                     ((uint16_t)0x0004)                /*!< Mute Mode Request */
#define  USART_RQR_RXFRQ                    ((uint16_t)0x0008)                /*!< Receive Data flush Request */
#define  USART_RQR_TXFRQ                    ((uint16_t)0x0010)                /*!< Transmit data flush Request */

/*******************  Bit definition for USART_ISR register  ******************/
#define  USART_ISR_PE                        ((uint32_t)0x00000001)            /*!< Parity Error */
#define  USART_ISR_FE                        ((uint32_t)0x00000002)            /*!< Framing Error */
#define  USART_ISR_NE                        ((uint32_t)0x00000004)            /*!< Noise detected Flag */
#define  USART_ISR_ORE                       ((uint32_t)0x00000008)            /*!< OverRun Error */
#define  USART_ISR_IDLE                      ((uint32_t)0x00000010)            /*!< IDLE line detected */
#define  USART_ISR_RXNE                      ((uint32_t)0x00000020)            /*!< Read Data Register Not Empty */
#define  USART_ISR_TC                        ((uint32_t)0x00000040)            /*!< Transmission Complete */
#define  USART_ISR_TXE                       ((uint32_t)0x00000080)            /*!< Transmit Data Register Empty */
//#define  USART_ISR_LBD                       ((uint32_t)0x00000100)            /*!< LIN Break Detection Flag */
#define  USART_ISR_CTSIF                     ((uint32_t)0x00000200)            /*!< CTS interrupt flag */
#define  USART_ISR_CTS                       ((uint32_t)0x00000400)            /*!< CTS flag */
#define  USART_ISR_RTOF                      ((uint32_t)0x00000800)            /*!< Receiver Time Out */
//#define  USART_ISR_EOBF                      ((uint32_t)0x00001000)            /*!< End Of Block Flag */
#define  USART_ISR_ABRE                      ((uint32_t)0x00004000)            /*!< Auto-Baud Rate Error */
#define  USART_ISR_ABRF                      ((uint32_t)0x00008000)            /*!< Auto-Baud Rate Flag */
#define  USART_ISR_BUSY                      ((uint32_t)0x00010000)            /*!< Busy Flag */
#define  USART_ISR_CMF                       ((uint32_t)0x00020000)            /*!< Character Match Flag */
#define  USART_ISR_SBKF                      ((uint32_t)0x00040000)            /*!< Send Break Flag */
#define  USART_ISR_RWU                       ((uint32_t)0x00080000)            /*!< Receive Wake Up from mute mode Flag */
//#define  USART_ISR_WUF                       ((uint32_t)0x00100000)            /*!< Wake Up from stop mode Flag */
//#define  USART_ISR_TEACK                     ((uint32_t)0x00200000)            /*!< Transmit Enable Acknowledge Flag */
//#define  USART_ISR_REACK                     ((uint32_t)0x00400000)            /*!< Receive Enable Acknowledge Flag */

/*******************  Bit definition for USART_ICR register  ******************/
#define  USART_ICR_PECF                      ((uint32_t)0x00000001)            /*!< Parity Error Clear Flag */
#define  USART_ICR_FECF                      ((uint32_t)0x00000002)            /*!< Framing Error Clear Flag */
#define  USART_ICR_NCF                      ((uint32_t)0x00000004)             /*!< Noise detected Clear Flag */
#define  USART_ICR_ORECF                     ((uint32_t)0x00000008)            /*!< OverRun Error Clear Flag */
#define  USART_ICR_IDLECF                    ((uint32_t)0x00000010)            /*!< IDLE line detected Clear Flag */
#define  USART_ICR_TCCF                      ((uint32_t)0x00000040)            /*!< Transmission Complete Clear Flag */
#define  USART_ICR_LBDCF                     ((uint32_t)0x00000100)            /*!< LIN Break Detection Clear Flag */
#define  USART_ICR_CTSCF                     ((uint32_t)0x00000200)            /*!< CTS Interrupt Clear Flag */
#define  USART_ICR_RTOCF                     ((uint32_t)0x00000800)            /*!< Receiver Time Out Clear Flag */
//#define  USART_ICR_EOBCF                     ((uint32_t)0x00001000)            /*!< End Of Block Clear Flag */
#define  USART_ICR_CMCF                      ((uint32_t)0x00020000)            /*!< Character Match Clear Flag */
//#define  USART_ICR_WUCF                      ((uint32_t)0x00100000)            /*!< Wake Up from stop mode Clear Flag */

/*******************  Bit definition for USART_RDR register  ******************/
#define  USART_RDR_RDR                       ((uint16_t)0x01FF)                /*!< RDR[8:0] bits (Receive Data value) */

/*******************  Bit definition for USART_TDR register  ******************/
#define  USART_TDR_TDR                       ((uint16_t)0x01FF)                /*!< TDR[8:0] bits (Transmit Data value) */

/******************************************************************************/
/*                                                                            */
/*                         Window WATCHDOG (WWDG)                             */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for WWDG_CR register  ********************/
#define  WWDG_CR_T                           ((uint8_t)0x7F)               /*!< T[6:0] bits (7-Bit counter (MSB to LSB)) */
#define  WWDG_CR_T0                          ((uint8_t)0x01)               /*!< Bit 0 */
#define  WWDG_CR_T1                          ((uint8_t)0x02)               /*!< Bit 1 */
#define  WWDG_CR_T2                          ((uint8_t)0x04)               /*!< Bit 2 */
#define  WWDG_CR_T3                          ((uint8_t)0x08)               /*!< Bit 3 */
#define  WWDG_CR_T4                          ((uint8_t)0x10)               /*!< Bit 4 */
#define  WWDG_CR_T5                          ((uint8_t)0x20)               /*!< Bit 5 */
#define  WWDG_CR_T6                          ((uint8_t)0x40)               /*!< Bit 6 */

#define  WWDG_CR_WDGA                        ((uint8_t)0x80)               /*!< Activation bit */

/*******************  Bit definition for WWDG_CFR register  *******************/
#define  WWDG_CFR_W                          ((uint16_t)0x007F)            /*!< W[6:0] bits (7-bit window value) */
#define  WWDG_CFR_W0                         ((uint16_t)0x0001)            /*!< Bit 0 */
#define  WWDG_CFR_W1                         ((uint16_t)0x0002)            /*!< Bit 1 */
#define  WWDG_CFR_W2                         ((uint16_t)0x0004)            /*!< Bit 2 */
#define  WWDG_CFR_W3                         ((uint16_t)0x0008)            /*!< Bit 3 */
#define  WWDG_CFR_W4                         ((uint16_t)0x0010)            /*!< Bit 4 */
#define  WWDG_CFR_W5                         ((uint16_t)0x0020)            /*!< Bit 5 */
#define  WWDG_CFR_W6                         ((uint16_t)0x0040)            /*!< Bit 6 */

#define  WWDG_CFR_WDGTB                      ((uint16_t)0x0180)            /*!< WDGTB[1:0] bits (Timer Base) */
#define  WWDG_CFR_WDGTB0                     ((uint16_t)0x0080)            /*!< Bit 0 */
#define  WWDG_CFR_WDGTB1                     ((uint16_t)0x0100)            /*!< Bit 1 */

#define  WWDG_CFR_EWI                        ((uint16_t)0x0200)            /*!< Early Wakeup Interrupt */

/*******************  Bit definition for WWDG_SR register  ********************/
#define  WWDG_SR_EWIF                        ((uint8_t)0x01)               /*!< Early Wakeup Interrupt Flag */





/**
  * @}
  */

 /**
  * @}
  */

#ifdef USE_STDPERIPH_DRIVER
  #include "FT32f0xx_conf.h"
#endif

/** @addtogroup Exported_macro
  * @{
  */
/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __FT32F030X8_H */

/**
  * @}
  */

  /**
  * @}
  */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/
