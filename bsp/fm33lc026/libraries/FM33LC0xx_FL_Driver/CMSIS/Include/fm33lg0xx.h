/**************************************************************************************************** * @file     FM33LG0XX.h
 *
 * @brief    CMSIS CORTEX-M0 Peripheral Access Layer Header File for
 *           FM33LG0XX from Keil.
 *
 * @version  V0.0.1
 * @date     14 july 2020
 *
 * @note     Generated with SVDConv V2.87e
 *           from CMSIS SVD File 'FM33LG0XX.SVD' Version 1.0,
 *
 * @par      ARM Limited (ARM) is supplying this software for use with Cortex-M
 *           processor based microcontroller, but can be equally used for other
 *           suitable processor architectures. This file can be freely distributed.
 *           Modifications to this file shall be clearly marked.
 *
 *           THIS SOFTWARE IS PROVIDED “AS IS”. NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 *           OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 *           MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 *           ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 *           CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 *******************************************************************************************************/


/** @addtogroup Keil
  * @{
  */

/** @addtogroup FM33LG0XX
  * @{
  */

#ifndef __FM33LG0XX_H
#define __FM33LG0XX_H

#ifdef __cplusplus
extern "C" {
#endif


#define __RCHF_INITIAL_CLOCK        (8000000)        /* Value of the Internal RC HIGH oscillator in Hz */
#define __RCLP_CLOCK                (32000)          /* Value of the Internal RC LOW oscillator in Hz */
#define __XTHF_CLOCK                (8000000)        /* Value of the EXTERNAL oscillator in Hz */
#define __XTLF_CLOCK                (32768)          /* Value of the EXTERNAL oscillator in Hz */

/**
  * @brief Configuration of the Cortex-M0 Processor and Core Peripherals
  */
#define __CM0_REV                    0x0100U /*!< Cortex-M0 Core Revision                                               */
#define __MPU_PRESENT                1U      /*!< MPU present or not                                                    */
#define __VTOR_PRESENT               1U      /*!< VTOR present or not                                                   */
#define __NVIC_PRIO_BITS             2U      /*!< Number of Bits used for Priority Levels                               */
#define __Vendor_SysTickConfig       0U      /*!< Set to 1 if different SysTick Config is used                          */
/* -------------------------  Interrupt Number Definition  ------------------------ */

/**
 * @brief FM33LG0XX Interrupt Number Definition, according to the selected device
 *        in @ref Library_configuration_section
 */

typedef enum {
/******  Cortex-M0 Processor Exceptions Numbers ****************************************************************/
  Reset_IRQn                    = -15,              /*!<   1  复位向量 */
  NMI_IRQn                      = -14,              /*!<   2  WKUPx中断、低功耗模式错误中断 */
  HardFault_IRQn                = -13,              /*!<   3  HardFault中断向量 */
  SVC_IRQn                      = -5,               /*!<  11  SVCall系统服务请求 */
  PendSV_IRQn                   = -2,               /*!<  14  可挂起系统服务请求 */
  SysTick_IRQn                  = -1,               /*!<  15  内部定时器中断向量 */

/* --------------------  FM33LG0XX specific Interrupt Numbers  --------------------*/
  WWDT_IRQn                     = 0,                /*!<   0  窗口看门狗或独立看门狗中断 */
  SVD_IRQn                      = 1,                /*!<   1  电源监测报警中断 */
  RTCx_IRQn                       = 2,                /*!<   2  实时时钟中断 */
  FLASH_IRQn                    = 3,                /*!<   3  NVMIF中断 */
  FDET_IRQn                     = 4,                /*!<   4  XTLF或XTHF停振检测中断、系统时钟选择错误中断 */
  ADC_IRQn                      = 5,                /*!<   5  ADC转换完成中断 */
  DAC_IRQn                      = 6,                /*!<   6  DAC中断 */
  SPI0_IRQn                     = 7,                /*!<   7  SPI0中断 */
  SPI1_IRQn                     = 8,                /*!<   8  SPI1中断 */
  SPI2_IRQn                     = 9,                /*!<   9  SPI2中断 */
  UART0_IRQn                    = 10,               /*!<  10  UART0中断 */
  UART1_IRQn                    = 11,               /*!<  11  UART1中断 */
  UART3_IRQn                    = 12,               /*!<  12  UART3中断 */
  UART4_IRQn                    = 13,               /*!<  13  UART4中断 */
  UART5_IRQn                    = 14,               /*!<  14  UART5中断 */
  U7816_IRQn                    = 15,               /*!<  15  U7816中断 */
  LPUARTx_IRQn                  = 16,               /*!<  16  LPUART0/1/2中断 */
  I2C_IRQn                      = 17,               /*!<  17  I2C中断 */
  CCL_IRQn                      = 18,               /*!<  18  时钟校准中断 */
  AES_IRQn                      = 19,               /*!<  19  AES中断 */
  LPTIMx_IRQn                   = 20,               /*!<  20  LPTIM16或LPTIM32中断 */
  DMA_IRQn                      = 21,               /*!<  21  DMA中断 */
  WKUPx_IRQn                    = 22,               /*!<  22  WKUP引脚中断 */
  LUT_IRQn                      = 23,               /*!<  23  LUT中断 */
  BSTIM_IRQn                    = 24,               /*!<  24  BSTIM16或BSTIM32中断 */
  COMPx_IRQn                    = 25,               /*!<  25  COMPx中断 */
  GPTIM01_IRQn                  = 26,               /*!<  26  通用定时器0,1中断 */
  GPTIM2_IRQn                   = 27,               /*!<  27  通用定时器2中断 */
  ATIM_IRQn                     = 28,               /*!<  28  高级定时器中断 */
  VREF_IRQn                     = 29,               /*!<  29  1.2V内部基准电压建立中断、VREF_VREG中断 */
  GPIO_IRQn                     = 30,               /*!<  30  外部引脚中断 */
  CAN_IRQn                      = 31,               /*!<  31  CAN2.0中断 */

} IRQn_Type;


/** @addtogroup Configuration_of_CMSIS
  * @{
  */

/* ================================================================================ */
/* ================      Processor and Core Peripheral Section     ================ */
/* ================================================================================ */

#include "core_cm0plus.h"                            /*!< Cortex-M0 processor and core peripherals */
#include "system_fm33lg0xx.h"                        /*!< FM33LG0XX System */

/* ================================================================================ */
/* ================       Device Specific Peripheral Section       ================ */
/* ================================================================================ */

/** @addtogroup Device_Peripheral_Registers
  * @{
  */

/* -------------------  Start of section using anonymous unions  ------------------ */
#if defined(__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined(__ICCARM__)
  #pragma language=extended
//#elif defined(__GNUC__)
///* anonymous unions are enabled by default */
//#elif defined(__TMS470__)
///* anonymous unions are enabled by default */
//#elif defined(__TASKING__)
//  #pragma warning 586
#else
#warning Not supported compiler type
#endif


/* ================================================================================ */
/* ================                       FLS                      ================ */
/* ================================================================================ */

typedef struct
{
  __IO uint32_t RDCR;                   /*!<  Flash Read Control Register,                          Address offset: 0x00 */
  __IO uint32_t PFCR;                   /*!<  Flash Prefetch Control Register,                      Address offset: 0x04 */
  __I  uint32_t OPTBR;                  /*!<  Flash Option Bytes Register,                          Address offset: 0x08 */
  __IO uint32_t ACLOCK1;                /*!<  Flash Application Code Lock Register1,                Address offset: 0x0C */
  __IO uint32_t ACLOCK2;                /*!<  Flash Application Code Lock Register2,                Address offset: 0x10 */
  __IO uint32_t EPCR;                   /*!<  Flash Erase/Program Control Register,                 Address offset: 0x14 */
  __O  uint32_t KEY;                    /*!<  Flash Key Register,                                   Address offset: 0x18 */
  __IO uint32_t IER;                    /*!<  Flash Interrupt Enable Register,                      Address offset: 0x1C */
  __IO uint32_t ISR;                    /*!<  Flash Interrupt Status Register,                      Address offset: 0x20 */
}FLASH_Type;


/* ================================================================================ */
/* ================                       PMU                      ================ */
/* ================================================================================ */

typedef struct
{
  __IO uint32_t CR;                     /*!<  Power Management Control Register,                    Address offset: 0x00 */
  __IO uint32_t WKTR;                   /*!<  Wakeup Time Register,                                 Address offset: 0x04 */
  __IO uint32_t WKFR;                   /*!<  Wakeup Source Flags Register,                         Address offset: 0x08 */
  __IO uint32_t IER;                    /*!<  PMU Interrupt Enable Register,                        Address offset: 0x0C */
  __IO uint32_t ISR;                    /*!<  PMU Interrupt and Status Register,                    Address offset: 0x10 */
  __IO uint32_t RSV1[9];                /*!<  RESERVED REGISTER,                                    Address offset: 0x14 */
  __IO uint32_t ULPB_TR;                /*!<  ULPBG trim Register,                                  Address offset: 0x38 */
  __IO uint32_t VREFP_CR;               /*!<  VREFP Control Register,                               Address offset: 0x3C */
  __IO uint32_t VREFP_CFGR;             /*!<  VREFP Config Register,                                Address offset: 0x40 */
  __IO uint32_t VREFP_ISR;              /*!<  VREFP Interrupt Status Register,                      Address offset: 0x44 */
  __IO uint32_t VREFP_TR;               /*!<  VREFP Trim Register,                                  Address offset: 0x48 */
}PMU_Type;

/* ================================================================================ */
/* ================                       VREFP                     ================ */
/* ================================================================================ */

typedef struct
{
  __IO uint32_t CR;               /*!<  VREFP Control Register,                               Address offset: 0x00 */
  __IO uint32_t CFGR;             /*!<  VREFP Config Register,                                Address offset: 0x04 */
  __IO uint32_t ISR;              /*!<  VREFP Interrupt Status Register,                      Address offset: 0x08 */
  __IO uint32_t TR;               /*!<  VREFP Trim Register,                                  Address offset: 0x0C */
}VREFP_Type;

/* ================================================================================ */
/* ================                      VREF                      ================ */
/* ================================================================================ */

typedef struct
{
  __IO uint32_t CR;                     /*!<  VREF Control Register,                                Address offset: 0x00 */
  __IO uint32_t CFGR;                   /*!<  VREF Config Register,                                 Address offset: 0x04 */
  __IO uint32_t ISR;                    /*!<  VREF Status Register,                                 Address offset: 0x08 */
  __IO uint32_t IER;                    /*!<  VREF Interrupt Enable Register,                       Address offset: 0x0C */
  __IO uint32_t BUFCR;                  /*!<  Buffer Control Register,                              Address offset: 0x10 */
}VREF_Type;


/* ================================================================================ */
/* ================                       VAO                      ================ */
/* ================================================================================ */

typedef struct
{
  __IO uint32_t RSV1[512];              /*!<  RESERVED REGISTER,                                    Address offset: 0x00 */
  __IO uint32_t RSTCR;                 /*!<  VBAT Reset Control Register,                          Address offset: 0x800 */
  __IO uint32_t XTLFCR;                /*!<  XTLF Control Register,                                Address offset: 0x804 */
  __IO uint32_t XTLFPR;                /*!<  XTLF Power Register,                                  Address offset: 0x808 */
  __IO uint32_t FDIER;                 /*!<  XTLF Oscillation Fail Detection Interrupt Enable Register,Address offset: 0x80C */
  __IO uint32_t FDISR;                 /*!<  XTLF Oscillation Fail Detection Interrupt Status Register,Address offset: 0x810 */
  __IO uint32_t RSV2[251];              /*!<  RESERVED REGISTER,                                    Address offset: 0x814 */
  __IO uint32_t INEN;                   /*!<  VAO IO Input Enable Register,                         Address offset: 0xC00 */
  __IO uint32_t PUEN;                   /*!<  VAO IO Pull-up Enable Register,                       Address offset: 0xC04 */
  __IO uint32_t ODEN;                   /*!<  VAO IO Open Drain Enable Register,                    Address offset: 0xC08 */
  __IO uint32_t FCR;                    /*!<  VAO IO Function Control Register,                     Address offset: 0xC0C */
  __IO uint32_t DOR;                    /*!<  VAO IO Data Output Register,                          Address offset: 0xC10 */
  __I  uint32_t DIR;                    /*!<  VAO IO Data Input Register,                           Address offset: 0xC14 */
  __IO uint32_t VILR;                   /*!<  VAO IO Voltage Input Low Register,                    Address offset: 0xC18 */
}VAO_Type;


/* ================================================================================ */
/* ================                      CDIF                      ================ */
/* ================================================================================ */

typedef struct
{
  __IO uint32_t CR;                     /*!<  ,                                                     Address offset: 0x00 */
  __IO uint32_t PRSC;                   /*!<  ,                                                     Address offset: 0x04 */
}CDIF_Type;


/* ================================================================================ */
/* ================                       RMU                      ================ */
/* ================================================================================ */

typedef struct
{
  __IO uint32_t PDRCR;                  /*!<  PDR Control Register,                                 Address offset: 0x00 */
  __IO uint32_t BORCR;                  /*!<  BOR Control Register,                                 Address offset: 0x04 */
  __IO uint32_t LKPCR;                  /*!<  Reset Config Register,                                Address offset: 0x08 */
  __O  uint32_t SOFTRST;                /*!<  Software Reset Register,                              Address offset: 0x0C */
  __IO uint32_t RSTFR;                  /*!<  Reset Flag Register,                                  Address offset: 0x10 */
  __O  uint32_t PRSTEN;                 /*!<  Peripheral Reset Enable Register,                     Address offset: 0x14 */
  __IO uint32_t AHBRSTCR;               /*!<  AHB Peripherals Reset Register,                       Address offset: 0x18 */
  __IO uint32_t APBRSTCR1;              /*!<  APB Peripherals Reset Register1,                      Address offset: 0x1C */
  __IO uint32_t APBRSTCR2;              /*!<  APB Peripherals Reset Register2,                      Address offset: 0x20 */
}RMU_Type;


/* ================================================================================ */
/* ================                      IWDT                      ================ */
/* ================================================================================ */

typedef struct
{
  __O  uint32_t SERV;                   /*!<  IWDT Service Register,                                Address offset: 0x00 */
  __IO uint32_t CR;                     /*!<  IWDT Config Register,                                 Address offset: 0x04 */
  __I  uint32_t CNT;                    /*!<  IWDT Counter Register,                                Address offset: 0x08 */
  __IO uint32_t WIN;                    /*!<  IWDT Window Register,                                 Address offset: 0x0C */
  __IO uint32_t IER;                    /*!<  IWDT Interrupt Enable Register,                       Address offset: 0x10 */
  __IO uint32_t ISR;                    /*!<  IWDT Interrupt Status Register,                       Address offset: 0x14 */
}IWDT_Type;


/* ================================================================================ */
/* ================                      WWDT                      ================ */
/* ================================================================================ */

typedef struct
{
  __O  uint32_t CR;                     /*!<  WWDT Control Register,                                Address offset: 0x00 */
  __IO uint32_t CFGR;                   /*!<  WWDT Config Register,                                 Address offset: 0x04 */
  __I  uint32_t CNT;                    /*!<  WWDT Counter Register,                                Address offset: 0x08 */
  __IO uint32_t IER;                    /*!<  WWDT Interrupt Enable Register,                       Address offset: 0x0C */
  __IO uint32_t ISR;                    /*!<  WWDT Interrupt Status Register,                       Address offset: 0x10 */
  __I  uint32_t PSC;                    /*!<  WWDT Prescaler Register,                              Address offset: 0x14 */
}WWDT_Type;


/* ================================================================================ */
/* ================                       CMU                      ================ */
/* ================================================================================ */

typedef struct
{
  __IO uint32_t SYSCLKCR;               /*!<  System Clock Control Register,                        Address offset: 0x00 */
  __IO uint32_t RCHFCR;                 /*!<  RCHF Control Register,                                Address offset: 0x04 */
  __IO uint32_t RCHFTR;                 /*!<  RCHF Trim Register,                                   Address offset: 0x08 */
  __IO uint32_t PLLCR;                  /*!<  PLL Control Register,                                 Address offset: 0x0C */
  __IO uint32_t RCLPCR;                 /*!<  RCLP Control Register,                                Address offset: 0x10 */
  __IO uint32_t RCLPTR;                 /*!<  RCLP Trim Register,                                   Address offset: 0x14 */
  __IO uint32_t RSV1;                   /*!<  RESERVED REGISTER,                                    Address offset: 0x18 */
  __IO uint32_t LSCLKSEL;               /*!<  LSCLK Select Register,                                Address offset: 0x1C */
  __IO uint32_t XTHFCR;                 /*!<  XTHF Control Register,                                Address offset: 0x20 */
  __IO uint32_t RCLFCR;                 /*!<  RCLF Control Register,                                Address offset: 0x24 */
  __IO uint32_t RCLFTR;                 /*!<  RCLF Trim Register,                                   Address offset: 0x28 */
  __IO uint32_t IER;                    /*!<  Interrupt Enable Register,                            Address offset: 0x2C */
  __IO uint32_t ISR;                    /*!<  Interrupt Status Register,                            Address offset: 0x30 */
  __IO uint32_t PCLKCR1;                /*!<  Peripheral bus Clock Control Register1,               Address offset: 0x34 */
  __IO uint32_t PCLKCR2;                /*!<  Peripheral bus Clock Control Register2,               Address offset: 0x38 */
  __IO uint32_t PCLKCR3;                /*!<  Peripheral bus Clock Control Register3,               Address offset: 0x3C */
  __IO uint32_t PCLKCR4;                /*!<  Peripheral bus Clock Control Register4,               Address offset: 0x40 */
  __IO uint32_t OPCCR1;                 /*!<  Peripheral Clock Config Register1,                    Address offset: 0x44 */
  __IO uint32_t OPCCR2;                 /*!<  Peripheral Clock Config Register 2,                   Address offset: 0x48 */
  __IO uint32_t OPCCR3;                 /*!<  Peripheral Clock Config Register 3,                   Address offset: 0x4C */
  __IO uint32_t AHBMCR;                 /*!<  AHB Master Control Register,                          Address offset: 0x50 */
  __IO uint32_t CCCR;                   /*!<  Clock Calibration Control Register,                   Address offset: 0x54 */
  __IO uint32_t CCFR;                   /*!<  Clock Calibration Config Register,                    Address offset: 0x58 */
  __I  uint32_t CCNR;                   /*!<  Clock Calibration Counter Register,                   Address offset: 0x5C */
  __IO uint32_t CCISR;                  /*!<  Clock Calibration Interrupt Status Register,          Address offset: 0x60 */
}CMU_Type;


/* ================================================================================ */
/* ================                       SVD                      ================ */
/* ================================================================================ */

typedef struct
{
  __IO uint32_t CFGR;                   /*!<  SVD Config Register,                                  Address offset: 0x00 */
  __IO uint32_t CR;                     /*!<  SVD Control Register,                                 Address offset: 0x04 */
  __IO uint32_t IER;                    /*!<  SVD Interrupt Enable Register,                        Address offset: 0x08 */
  __IO uint32_t ISR;                    /*!<  SVD Interrupt Status Register,                        Address offset: 0x0C */
  __IO uint32_t VSR;                    /*!<  SVD reference Voltage Select Register,                Address offset: 0x10 */
}SVD_Type;


/* ================================================================================ */
/* ================                       AES                      ================ */
/* ================================================================================ */

typedef struct
{
  __IO uint32_t CR;                     /*!<  AES Control Register,                                 Address offset: 0x00 */
  __IO uint32_t IER;                    /*!<  AES Interrupt Enable Register,                        Address offset: 0x04 */
  __IO uint32_t ISR;                    /*!<  AES Interrupt Status Register,                        Address offset: 0x08 */
  __IO uint32_t DIR;                    /*!<  AES Data Input Register,                              Address offset: 0x0C */
  __I  uint32_t DOR;                    /*!<  AES Data Output Register,                             Address offset: 0x10 */
  __IO uint32_t KEY0;                   /*!<  AES Key Register 0,                                   Address offset: 0x14 */
  __IO uint32_t KEY1;                   /*!<  AES Key Register 1,                                   Address offset: 0x18 */
  __IO uint32_t KEY2;                   /*!<  AES Key Register 2,                                   Address offset: 0x1C */
  __IO uint32_t KEY3;                   /*!<  AES Key Register 3,                                   Address offset: 0x20 */
  __IO uint32_t KEY4;                   /*!<  AES Key Register 4,                                   Address offset: 0x24 */
  __IO uint32_t KEY5;                   /*!<  AES Key Register 5,                                   Address offset: 0x28 */
  __IO uint32_t KEY6;                   /*!<  AES Key Register 6,                                   Address offset: 0x2C */
  __IO uint32_t KEY7;                   /*!<  AES Key Register 7,                                   Address offset: 0x30 */
  __IO uint32_t IVR0;                   /*!<  AES Initial Vector Register 0,                        Address offset: 0x34 */
  __IO uint32_t IVR1;                   /*!<  AES Initial Vector Register 1,                        Address offset: 0x38 */
  __IO uint32_t IVR2;                   /*!<  AES Initial Vector Register 2,                        Address offset: 0x3C */
  __IO uint32_t IVR3;                   /*!<  AES Initial Vector Register 3,                        Address offset: 0x40 */
  __IO uint32_t H0;                     /*!<  AES MultH parameter Register 0,                       Address offset: 0x44 */
  __IO uint32_t H1;                     /*!<  AES MultH parameter Register 1,                       Address offset: 0x48 */
  __IO uint32_t H2;                     /*!<  AES MultH parameter Register 2,                       Address offset: 0x4C */
  __IO uint32_t H3;                     /*!<  AES MultH parameter Register 3,                       Address offset: 0x50 */
}AES_Type;


/* ================================================================================ */
/* ================                       RNG                      ================ */
/* ================================================================================ */

typedef struct
{
  __IO uint32_t CR;                     /*!<  Random Number Generator Control Register,             Address offset: 0x00 */
  __I  uint32_t DOR;                    /*!<  Random Number Generator Data Output Register,         Address offset: 0x04 */
  __IO uint32_t RSV1[2];                /*!<  RESERVED REGISTER,                                    Address offset: 0x08 */
  __IO uint32_t SR;                     /*!<  Random Number Generator Status Register,              Address offset: 0x10 */
  __IO uint32_t CRCCR;                 /*!<  CRC Control Register,                                 Address offset: 0x14 */
  __IO uint32_t CRCDIR;                /*!<  CRC Data input Register,                              Address offset: 0x18 */
  __IO uint32_t CRCSR;                 /*!<  CRC Status Register,                                  Address offset: 0x1C */
}RNG_Type;


/* ================================================================================ */
/* ================                       OPA                      ================ */
/* ================================================================================ */

typedef struct
{
  __IO uint32_t CR;                     /*!<  OPA1 Control Register,                                Address offset: 0x00 */
  __IO uint32_t CALR;                   /*!<  OPA1 Calibration Register,                            Address offset: 0x04 */
  __I  uint32_t COR;                    /*!<  OPA1 Calibration Output Register,                     Address offset: 0x08 */
}OPA_Type;


/* ================================================================================ */
/* ================                      COMP                      ================ */
/* ================================================================================ */
typedef struct
{
  __IO uint32_t CR;              /*!< ComparatorControl Register 1,                        Address offset: 0x00 */

} COMP_Type;

typedef struct
{
  __IO uint32_t ICR;                    /*!<  Comparator Interrupt Config Register,                 Address offset: 0x0C */
  __IO uint32_t ISR;                    /*!<  Comparator Interrupt Status Register,                 Address offset: 0x10 */
  __IO uint32_t BUFCR;                  /*!<  Comparator Buffer Control Register,                   Address offset: 0x14 */
}COMP_COMMON_Type;


/* ================================================================================ */
/* ================                      CALC                    ================ */
/* ================================================================================ */

typedef struct
{
  __IO uint32_t OPRD;                   /*!<  Operand Register,                                     Address offset: 0x00 */
  __IO uint32_t DIVSOR;                 /*!<  Divisor Regsiter,                                     Address offset: 0x04 */
  __I  uint32_t QUOT;                   /*!<  Quotient Register,                                    Address offset: 0x08 */
  __I  uint32_t REMD;                   /*!<  Reminder Register,                                    Address offset: 0x0C */
  __I  uint32_t ROOT;                   /*!<  Root Register,                                        Address offset: 0x10 */
  __I  uint32_t SR;                     /*!<  Status Register,                                      Address offset: 0x14 */
  __IO uint32_t CR;                     /*!<  Control Register,                                     Address offset: 0x18 */
}DIVAS_Type;


/* ================================================================================ */
/* ================                       I2C                      ================ */
/* ================================================================================ */

typedef struct
{
  __IO uint32_t MSPCFGR;                /*!<  I2C Master Config Register,                           Address offset: 0x00 */
  __IO uint32_t MSPCR;                  /*!<  I2C Master Control Register,                          Address offset: 0x04 */
  __IO uint32_t MSPIER;                 /*!<  I2C Master Intterupt Enable Register,                 Address offset: 0x08 */
  __IO uint32_t MSPISR;                 /*!<  I2C Master Interrupt Status Register,                 Address offset: 0x0C */
  __IO uint32_t MSPSR;                  /*!<  I2C Master Status Register,                           Address offset: 0x10 */
  __IO uint32_t MSPBGR;                 /*!<  I2C Master Baud rate Generator Register,              Address offset: 0x14 */
  __IO uint32_t MSPBUF;                 /*!<  I2C Master transfer Buffer,                           Address offset: 0x18 */
  __IO uint32_t MSPTCR;                 /*!<  I2C Master Timing Control Register,                   Address offset: 0x1C */
  __IO uint32_t MSPTOR;                 /*!<  I2C Master Time-Out Register,                         Address offset: 0x20 */
  __IO uint32_t SSPCR;                  /*!<  I2C Slave Control Register,                           Address offset: 0x24 */
  __IO uint32_t SSPIER;                 /*!<  I2C Slave Interrupt Enable Register,                  Address offset: 0x28 */
  __IO uint32_t SSPISR;                 /*!<  I2C Slave Interrupt Status Register,                  Address offset: 0x2C */
  __I  uint32_t SSPSR;                  /*!<  I2C Slave Status Register,                            Address offset: 0x30 */
  __IO uint32_t SSPBUF;                 /*!<  I2C Slave transfer Buffer,                            Address offset: 0x34 */
  __IO uint32_t SSPADR;                 /*!<  I2C Slave Address Register,                           Address offset: 0x38 */
}I2C_Type;


/* ================================================================================ */
/* ================                     UART_COMMON                     ================ */
/* ================================================================================ */

typedef struct
{
  __IO uint32_t IRCR;                     /*!<  Infrared modulation Control Register,                 Address offset: 0x00 */
}UART_COMMON_Type;


/* ================================================================================ */
/* ================                      UARTx                     ================ */
/* ================================================================================ */

typedef struct
{
  __IO uint32_t CSR;                    /*!<  UARTx Control Status Register,                        Address offset: 0x00 */
  __IO uint32_t IER;                    /*!<  UARTx Interrupt Enable Register,                      Address offset: 0x04 */
  __IO uint32_t ISR;                    /*!<  UARTx Interrupt Status Register,                      Address offset: 0x08 */
  __IO uint32_t TODR;                   /*!<  UARTx Time-Out and Delay Register,                    Address offset: 0x0C */
  __I  uint32_t RXBUF;                  /*!<  UARTx Receive Buffer,                                 Address offset: 0x10 */
  __O  uint32_t TXBUF;                  /*!<  UARTx Transmit Buffer,                                Address offset: 0x14 */
  __IO uint32_t BGR;                    /*!<  UARTx Baud rate Generator Register,                   Address offset: 0x18 */
}UART_Type;


/* ================================================================================ */
/* ================                     LPUARTx                    ================ */
/* ================================================================================ */

typedef struct
{
  __IO uint32_t CSR;                    /*!<  LPUARTx Control Status Register,                      Address offset: 0x00 */
  __IO uint32_t IER;                    /*!<  LPUARTx Interrupt Enable Register,                    Address offset: 0x04 */
  __IO uint32_t ISR;                    /*!<  LPUARTx Interrupt Status Register,                    Address offset: 0x08 */
  __IO uint32_t BMR;                    /*!<  LPUARTx Baud rate Modulation Register,                Address offset: 0x0C */
  __I  uint32_t RXBUF;                  /*!<  LPUARTx Receive Buffer Register,                      Address offset: 0x10 */
  __IO uint32_t TXBUF;                  /*!<  LPUARTx Transmit Buffer Register,                     Address offset: 0x14 */
  __IO uint32_t DMR;                    /*!<  LPUARTx data Matching Register,                       Address offset: 0x18 */
}LPUART_Type;


/* ================================================================================ */
/* ================                      SPIx                      ================ */
/* ================================================================================ */

typedef struct
{
  __IO uint32_t CR1;                    /*!<  SPIxControl Register1,                                Address offset: 0x00 */
  __IO uint32_t CR2;                    /*!<  SPIxControl Register2,                                Address offset: 0x04 */
  __IO uint32_t CR3;                    /*!<  Control Register3,                                    Address offset: 0x08 */
  __IO uint32_t IER;                    /*!<  SPIxInterrupt Enable Register,                        Address offset: 0x0C */
  __IO uint32_t ISR;                    /*!<  SPIxStatus Register,                                  Address offset: 0x10 */
  __O  uint32_t TXBUF;                  /*!<  SPIxTransmit Buffer,                                  Address offset: 0x14 */
  __I  uint32_t RXBUF;                  /*!<  SPIxReceive Buffer,                                   Address offset: 0x18 */
}SPI_Type;


/* ================================================================================ */
/* ================                      U7816                     ================ */
/* ================================================================================ */

typedef struct
{
  __IO uint32_t CR;                     /*!<  7816 Control Register,                                Address offset: 0x00 */
  __IO uint32_t FFR;                   /*!<  7816 Frame Format Control Register,                   Address offset: 0x04 */
  __IO uint32_t EGTR;                   /*!<  7816 Extra Guard Time Register,                       Address offset: 0x08 */
  __IO uint32_t PSC;                   /*!<  7816 Clock Output Divider Register,                   Address offset: 0x0C */
  __IO uint32_t BGR;                   /*!<  7816 Prescaler Register,                              Address offset: 0x10 */
  __IO uint32_t RXBUF;                   /*!<  7816 data RX Buffer,                                  Address offset: 0x14 */
  __IO uint32_t TXBUF;                   /*!<  7816 data TX Buffer,                                  Address offset: 0x18 */
  __IO uint32_t IER;                    /*!<  7816 Interrupt Enable Register,                       Address offset: 0x1C */
  __IO uint32_t ISR;                    /*!<  7816 Interrupt Status Register,                       Address offset: 0x20 */
}U7816_Type;


/* ================================================================================ */
/* ================                       CAN                      ================ */
/* ================================================================================ */

typedef struct
{
  __IO uint32_t CR;                     /*!<  CAN Control Register,                                 Address offset: 0x00 */
  __IO uint32_t MSR;                    /*!<  CAN mode select register,                             Address offset: 0x04 */
  __IO uint32_t BRPR;                   /*!<  CAN Baud rate Prescaler Register,                     Address offset: 0x08 */
  __IO uint32_t BTR;                    /*!<  CAN Bit Timing Register,                              Address offset: 0x0C */
  __I  uint32_t ECR;                    /*!<  CAN Error Counter Register,                           Address offset: 0x10 */
  __IO uint32_t ESR;                    /*!<  CAN Error Status Register,                            Address offset: 0x14 */
  __I  uint32_t SR;                     /*!<  CAN Status Register,                                  Address offset: 0x18 */
  __I  uint32_t ISR;                    /*!<  CAN Interrupt Status Register,                        Address offset: 0x1C */
  __IO uint32_t IER;                    /*!<  CAN Interrupt Enable Register,                        Address offset: 0x20 */
  __IO uint32_t ICR;                    /*!<  CAN Interrupt Clear Register,                         Address offset: 0x24 */
  __IO uint32_t RSV1[2];                /*!<  RESERVED REGISTER,                                    Address offset: 0x28 */
  __O  uint32_t TXFIDR;                /*!<  CAN TX FIFO ID Register,                              Address offset: 0x30 */
  __O  uint32_t TXFDLCR;               /*!<  CAN TX FIFO DLC Register,                             Address offset: 0x34 */
  __O  uint32_t TXFDW1R;               /*!<  CAN TX FIFO Data Word1 Register,                      Address offset: 0x38 */
  __O  uint32_t TXFDW2R;               /*!<  CAN TX FIFO Data Word2 Register,                      Address offset: 0x3C */
  __O  uint32_t HPBIDR;                /*!<  CAN TX HPB ID Register,                               Address offset: 0x40 */
  __O  uint32_t HPBDLCR;               /*!<  CAN TX HPB DLC Register,                              Address offset: 0x44 */
  __O  uint32_t HPBDW1R;               /*!<  CAN TX HPB Data Word1 Register,                       Address offset: 0x48 */
  __O  uint32_t HPBDW2R;               /*!<  CAN TX HPB Data Word2 Register,                       Address offset: 0x4C */
  __O  uint32_t RXFIDR;                /*!<  CAN RX FIFO ID Register,                              Address offset: 0x50 */
  __O  uint32_t RXFDLCR;               /*!<  CAN RX FIFO DLC Register,                             Address offset: 0x54 */
  __O  uint32_t RXFDW1R;               /*!<  CAN RX FIFO Data Word1 Register,                      Address offset: 0x58 */
  __O  uint32_t RXFDW2R;               /*!<  CAN RX FIFO Data Word2 Register,                      Address offset: 0x5C */
  __IO uint32_t AFR;                    /*!<  Acceptance Filter Register,                           Address offset: 0x60 */
  __IO uint32_t AFMR0;                  /*!<  Acceptance Filter Mask Register0,                     Address offset: 0x64 */
  __IO uint32_t AFIR0;                  /*!<  Acceptance Filter ID Register0,                       Address offset: 0x68 */
  __IO uint32_t AFMR1;                  /*!<  Acceptance Filter Mask Register1,                     Address offset: 0x6C */
  __IO uint32_t AFIR1;                  /*!<  Acceptance Filter ID Register1,                       Address offset: 0x70 */
  __IO uint32_t AFMR2;                  /*!<  Acceptance Filter Mask Register2,                     Address offset: 0x74 */
  __IO uint32_t AFIR2;                  /*!<  Acceptance Filter ID Register2,                       Address offset: 0x78 */
  __IO uint32_t AFMR3;                  /*!<  Acceptance Filter Mask Register3,                     Address offset: 0x7C */
  __IO uint32_t AFIR3;                  /*!<  Acceptance Filter ID Register3,                       Address offset: 0x80 */
}CAN_Type;


/* ================================================================================ */
/* ================                       DMA                      ================ */
/* ================================================================================ */

typedef struct
{
  __IO uint32_t GCR;                    /*!<  DMA Global Control Register,                          Address offset: 0x00 */
  __IO uint32_t CH0CR;                  /*!<  Channel 0 Control Register,                           Address offset: 0x04 */
  __IO uint32_t CH0MAR;                 /*!<  Channel 0 Memory Address Register,                    Address offset: 0x08 */
  __IO uint32_t CH1CR;                  /*!<  Channel 1 Control Register,                           Address offset: 0x0C */
  __IO uint32_t CH1MAR;                 /*!<  Channel 1 Memory Address Register,                    Address offset: 0x10 */
  __IO uint32_t CH2CR;                  /*!<  Channel 2 Control Register,                           Address offset: 0x14 */
  __IO uint32_t CH2MAR;                 /*!<  Channel 2 Memory Address Register,                    Address offset: 0x18 */
  __IO uint32_t CH3CR;                  /*!<  Channel 3 Control Register,                           Address offset: 0x1C */
  __IO uint32_t CH3MAR;                 /*!<  Channel 3 Memory Address Register,                    Address offset: 0x20 */
  __IO uint32_t CH4CR;                  /*!<  Channel 4 Control Register,                           Address offset: 0x24 */
  __IO uint32_t CH4MAR;                 /*!<  Channel 4 Memory Address Register,                    Address offset: 0x28 */
  __IO uint32_t CH5CR;                  /*!<  Channel 5 Control Register,                           Address offset: 0x2C */
  __IO uint32_t CH5MAR;                 /*!<  Channel 5 Memory Address Register,                    Address offset: 0x30 */
  __IO uint32_t CH6CR;                  /*!<  Channel 6 Control Register,                           Address offset: 0x34 */
  __IO uint32_t CH6MAR;                 /*!<  Channel 6 Memory Address Register,                    Address offset: 0x38 */
  __IO uint32_t CH7CR;                  /*!<  Channel 11 Control Register,                          Address offset: 0x3C */
  __IO uint32_t CH7FLSAD;               /*!<  Channel 11 Flash Address Register,                    Address offset: 0x40 */
  __IO uint32_t CH7RAMAD;               /*!<  Channel 11 RAM Address Register,                      Address offset: 0x44 */
  __IO uint32_t ISR;                    /*!<  DMA Interrupt Status Register,                        Address offset: 0x48 */
}DMA_Type;


/* ================================================================================ */
/* ================                       CRC                      ================ */
/* ================================================================================ */

typedef struct
{
  __IO uint32_t DR;                     /*!<  CRC Data Register,                                    Address offset: 0x00 */
  __IO uint32_t CR;                     /*!<   Control Register,                                    Address offset: 0x04 */
  __IO uint32_t LFSR;                   /*!<  CRC Linear Feedback Shift Register,                   Address offset: 0x08 */
  __IO uint32_t XOR;                    /*!<  CRC output XOR Register,                              Address offset: 0x0C */
  __IO uint32_t RSV1[3];                /*!<  RESERVED REGISTER,                                    Address offset: 0x10 */
  __IO uint32_t POLY;                   /*!<  CRC Polynominal Register,                             Address offset: 0x1C */
}CRC_Type;


/* ================================================================================ */
/* ================                      ATIM                      ================ */
/* ================================================================================ */

typedef struct
{
  __IO uint32_t CR1;                    /*!<  ATIM Control Register1,                               Address offset: 0x00 */
  __IO uint32_t CR2;                    /*!<  ATIM Control Register2,                               Address offset: 0x04 */
  __IO uint32_t SMCR;                   /*!<  ATIM Slave Mode Control Register,                     Address offset: 0x08 */
  __IO uint32_t DIER;                   /*!<  ATIM DMA and Interrupt Enable Register,               Address offset: 0x0C */
  __IO uint32_t ISR;                    /*!<  ATIM Interrupt Status Register,                       Address offset: 0x10 */
  __O  uint32_t EGR;                    /*!<  ATIM Event Generation Register,                       Address offset: 0x14 */
  __IO uint32_t CCMR1;                  /*!<  ATIM Capture/Compare Mode Register1,                  Address offset: 0x18 */
  __IO uint32_t CCMR2;                  /*!<  ATIM Capture/Compare Mode Register2,                  Address offset: 0x1C */
  __IO uint32_t CCER;                   /*!<  ATIM Capture/Compare Enable Register,                 Address offset: 0x20 */
  __IO uint32_t CNT;                    /*!<  ATIM Counter Register,                                Address offset: 0x24 */
  __IO uint32_t PSC;                    /*!<  ATIM Prescaler Register,                              Address offset: 0x28 */
  __IO uint32_t ARR;                    /*!<  ATIM Auto-Reload Register,                            Address offset: 0x2C */
  __IO uint32_t RCR;                    /*!<  ATIM Repetition Counter Register,                     Address offset: 0x30 */
  __IO uint32_t CCR1;                   /*!<  ATIM Capture/Compare Register1,                       Address offset: 0x34 */
  __IO uint32_t CCR2;                   /*!<  ATIM Capture/Compare Register2,                       Address offset: 0x38 */
  __IO uint32_t CCR3;                   /*!<  ATIM Capture/Compare Register3,                       Address offset: 0x3C */
  __IO uint32_t CCR4;                   /*!<  ATIM Capture/Compare Register4,                       Address offset: 0x40 */
  __IO uint32_t BDTR;                   /*!<  ATIM Break and Deadtime Register,                     Address offset: 0x44 */
  __IO uint32_t DCR;                    /*!<  ATIM DMA Control Register,                            Address offset: 0x48 */
  __IO uint32_t DMAR;                   /*!<  ATIM DMA Access Register,                             Address offset: 0x4C */
  __IO uint32_t RSV1[4];                /*!<  RESERVED REGISTER,                                    Address offset: 0x50 */
  __IO uint32_t BKCR;                   /*!<  ATIM Break Control Register,                          Address offset: 0x60 */
}ATIM_Type;


/* ================================================================================ */
/* ================                     GPTIMx                     ================ */
/* ================================================================================ */

typedef struct
{
  __IO uint32_t CR1;                    /*!<  GPTIMx Control Register1,                             Address offset: 0x00 */
  __IO uint32_t CR2;                    /*!<  GPTIMx Control Register2,                             Address offset: 0x04 */
  __IO uint32_t SMCR;                   /*!<  GPTIMx Slave Mode Control Register,                   Address offset: 0x08 */
  __IO uint32_t DIER;                   /*!<  GPTIMx DMA and Interrupt Enable Register,             Address offset: 0x0C */
  __IO uint32_t ISR;                     /*!<   Interrupt Status Register,                           Address offset: 0x10 */
  __O  uint32_t EGR;                    /*!<  GPTIMx Event Generation Register,                     Address offset: 0x14 */
  __IO uint32_t CCMR1;                  /*!<  GPTIMx Capture/Compare Mode Register1,                Address offset: 0x18 */
  __IO uint32_t CCMR2;                  /*!<  GPTIMx Capture/Compare Mode Register2,                Address offset: 0x1C */
  __IO uint32_t CCER;                   /*!<  GPTIMx Capture/Compare Enable Register,               Address offset: 0x20 */
  __IO uint32_t CNT;                    /*!<  GPTIMx Counter Register,                              Address offset: 0x24 */
  __IO uint32_t PSC;                    /*!<  GPTIMx Prescaler Register,                            Address offset: 0x28 */
  __IO uint32_t ARR;                    /*!<  GPTIMx Auto-Reload Register,                          Address offset: 0x2C */
  __IO uint32_t RSV1;                   /*!<  RESERVED REGISTER,                                    Address offset: 0x30 */
  __IO uint32_t CCR1;                   /*!<  GPTIMx Capture/Compare Register1,                     Address offset: 0x34 */
  __IO uint32_t CCR2;                   /*!<  GPTIMx Capture/Compare Register2,                     Address offset: 0x38 */
  __IO uint32_t CCR3;                   /*!<  GPTIMx Capture/Compare Register3,                     Address offset: 0x3C */
  __IO uint32_t CCR4;                   /*!<  GPTIMx Capture/Compare Register4,                     Address offset: 0x40 */
  __IO uint32_t RSV2;                   /*!<  RESERVED REGISTER,                                    Address offset: 0x44 */
  __IO uint32_t DCR;                    /*!<  GPTIMx DMA Control Register,                          Address offset: 0x48 */
  __IO uint32_t DMAR;                   /*!<  GPTIMx DMA access Register,                           Address offset: 0x4C */
  __IO uint32_t RSV3[4];                /*!<  RESERVED REGISTER,                                    Address offset: 0x50 */
  __IO uint32_t ITRSEL;                 /*!<  GPTIMx Internal Trigger Select Register,              Address offset: 0x60 */
}GPTIM_Type;


/* ================================================================================ */
/* ================                     BSTIM32                    ================ */
/* ================================================================================ */

typedef struct
{
  __IO uint32_t CR1;                    /*!<  BSTIM Control Register1,                              Address offset: 0x00 */
  __IO uint32_t CR2;                    /*!<  BSTIM Control Register2,                              Address offset: 0x04 */
  __IO uint32_t RSV1;                   /*!<  RESERVED REGISTER,                                    Address offset: 0x08 */
  __IO uint32_t IER;                   /*!<  BSTIM Interrupt Enable Register,                      Address offset: 0x0C */
  __IO uint32_t ISR;                     /*!<  BSTIM Interrupt Status Register,                      Address offset: 0x10 */
  __O  uint32_t EGR;                    /*!<  BSTIM Event Generation Register,                      Address offset: 0x14 */
  __IO uint32_t RSV2[3];                /*!<  RESERVED REGISTER,                                    Address offset: 0x18 */
  __IO uint32_t CNT;                    /*!<  BSTIM Counter Register,                               Address offset: 0x24 */
  __IO uint32_t PSC;                    /*!<  BSTIM Prescaler Register,                             Address offset: 0x28 */
  __IO uint32_t ARR;                    /*!<  BSTIM Auto-Reload Register,                           Address offset: 0x2C */
}BSTIM32_Type;


/* ================================================================================ */
/* ================                     BSTIM16                    ================ */
/* ================================================================================ */

typedef struct
{
  __IO uint32_t CR1;                    /*!<  BSTIM Control Register1,                              Address offset: 0x00 */
  __IO uint32_t CR2;                    /*!<  BSTIM Control Register2,                              Address offset: 0x04 */
  __IO uint32_t RSV1;                   /*!<  RESERVED REGISTER,                                    Address offset: 0x08 */
  __IO uint32_t IER;                   /*!<  BSTIM Interrupt Enable Register,                      Address offset: 0x0C */
  __IO uint32_t ISR;                     /*!<  BSTIM Interrupt Status Register,                      Address offset: 0x10 */
  __O  uint32_t EGR;                    /*!<  BSTIM Event Generation Register,                      Address offset: 0x14 */
  __IO uint32_t RSV2[3];                /*!<  RESERVED REGISTER,                                    Address offset: 0x18 */
  __IO uint32_t CNT;                    /*!<  BSTIM Counter Register,                               Address offset: 0x24 */
  __IO uint32_t PSC;                    /*!<  BSTIM Prescaler Register,                             Address offset: 0x28 */
  __IO uint32_t ARR;                    /*!<  BSTIM Auto-Reload Register,                           Address offset: 0x2C */
}BSTIM16_Type;


/* ================================================================================ */
/* ================                     LPTIM32                    ================ */
/* ================================================================================ */

typedef struct
{
  __IO uint32_t CFGR;                   /*!<  LPTIM32 Config Register,                              Address offset: 0x00 */
  __I  uint32_t CNT;                    /*!<  LPTIM32 Counter Register,                             Address offset: 0x04 */
  __IO uint32_t CCSR;                   /*!<  LPTIM32 Capture/Compare Control and Status Register,  Address offset: 0x08 */
  __IO uint32_t ARR;                    /*!<  LPTIM32 Auto-Reload Register,                         Address offset: 0x0C */
  __IO uint32_t IER;                    /*!<  LPTIM32 Interrupt Enable Register,                    Address offset: 0x10 */
  __IO uint32_t ISR;                    /*!<  LPTIM32 Interrupt Status Register,                    Address offset: 0x14 */
  __IO uint32_t CR;                     /*!<  LPTIM32 Control Register,                             Address offset: 0x18 */
  __IO uint32_t RSV1;                   /*!<  RESERVED REGISTER,                                    Address offset: 0x1C */
  __IO uint32_t CCR1;                   /*!<  LPTIM32 Capture/Compare Register1,                    Address offset: 0x20 */
  __IO uint32_t CCR2;                   /*!<  LPTIM32 Capture/Compare Register2,                    Address offset: 0x24 */
  __IO uint32_t CCR3;                   /*!<  LPTIM32 Capture/Compare Register3,                    Address offset: 0x28 */
  __IO uint32_t CCR4;                   /*!<  LPTIM32 Capture/Compare Register4,                    Address offset: 0x2C */
}LPTIM32_Type;


/* ================================================================================ */
/* ================                     LPTIM16                    ================ */
/* ================================================================================ */

typedef struct
{
  __IO uint32_t CFGR;                   /*!<  LPTIM Config Register,                                Address offset: 0x00 */
  __I  uint32_t CNT;                    /*!<  LPTIM Counter Register,                               Address offset: 0x04 */
  __IO uint32_t CCSR;                   /*!<  LPTIM Capture/Compare Control and Status Register,    Address offset: 0x08 */
  __IO uint32_t ARR;                    /*!<  LPTIM Auto-Reload Register,                           Address offset: 0x0C */
  __IO uint32_t IER;                    /*!<  LPTIM Interrupt Enable Register,                      Address offset: 0x10 */
  __IO uint32_t ISR;                    /*!<  LPTIM Interrupt Status Register,                      Address offset: 0x14 */
  __IO uint32_t CR;                     /*!<  LPTIM Control Register,                               Address offset: 0x18 */
  __IO uint32_t RSV1;                   /*!<  RESERVED REGISTER,                                    Address offset: 0x1C */
  __IO uint32_t CCR1;                   /*!<  LPTIM Capture/Compare Register1,                      Address offset: 0x20 */
  __IO uint32_t CCR2;                   /*!<  LPTIM Capture/Compare Register2,                      Address offset: 0x24 */
}LPTIM16_Type;


/* ================================================================================ */
/* ================                      RTCA                      ================ */
/* ================================================================================ */

typedef struct
{
  __IO uint32_t WER;                    /*!<  RTC Write Enable Register,                            Address offset: 0x00 */
  __IO uint32_t IER;                    /*!<  RTC Interrupt Enable Register,                        Address offset: 0x04 */
  __IO uint32_t ISR;                    /*!<  RTC Interrupt Status Register,                        Address offset: 0x08 */
  __IO uint32_t BCDSEC;                 /*!<  BCD format time second registers,                     Address offset: 0x0C */
  __IO uint32_t BCDMIN;                 /*!<  BCD format time minute registers,                     Address offset: 0x10 */
  __IO uint32_t BCDHOUR;                /*!<  BCD format time hour registers,                       Address offset: 0x14 */
  __IO uint32_t BCDDAY;                 /*!<  BCD format time day registers,                        Address offset: 0x18 */
  __IO uint32_t BCDWEEK;                /*!<  BCD format time week registers,                       Address offset: 0x1C */
  __IO uint32_t BCDMONTH;               /*!<  BCD format time month registers,                      Address offset: 0x20 */
  __IO uint32_t BCDYEAR;                /*!<  BCD format time year registers,                       Address offset: 0x24 */
  __IO uint32_t ALARM;                  /*!<  RTCA Alarm Register,                                  Address offset: 0x28 */
  __IO uint32_t TMSEL;                  /*!<  RTCA Time Mark Select,                                Address offset: 0x2C */
  __IO uint32_t ADJUST;                 /*!<  RTCA time Adjust Register,                            Address offset: 0x30 */
  __IO uint32_t ADSIGN;                 /*!<  RTCA time Adjust Sign Register,                       Address offset: 0x34 */
  __IO uint32_t RSV1;                   /*!<  RESERVED REGISTER,                                    Address offset: 0x38 */
  __IO uint32_t SBSCNT;                 /*!<  RTCA Sub-Second Counter,                              Address offset: 0x3C */
  __IO uint32_t CR;                     /*!<  RTCA Control Register,                                Address offset: 0x40 */
}RTCA_Type;


/* ================================================================================ */
/* ================                      RTCB                      ================ */
/* ================================================================================ */

typedef struct
{
  __IO uint32_t WER;                    /*!<  RTCBWrite Enable Register,                            Address offset: 0x00 */
  __IO uint32_t IER;                    /*!<  RTCBInterrupt Enable Register,                        Address offset: 0x04 */
  __IO uint32_t ISR;                    /*!<  RTCBInterrupt Status Register,                        Address offset: 0x08 */
  __IO uint32_t BCDSEC;                 /*!<  BCD format time second registers,                     Address offset: 0x0C */
  __IO uint32_t BCDMIN;                 /*!<  BCD format time minute registers,                     Address offset: 0x10 */
  __IO uint32_t BCDHOUR;                /*!<  BCD format time hour registers,                       Address offset: 0x14 */
  __IO uint32_t BCDDAY;                 /*!<  BCD format time day registers,                        Address offset: 0x18 */
  __IO uint32_t BCDWEEK;                /*!<  BCD format time week registers,                       Address offset: 0x1C */
  __IO uint32_t BCDMONTH;               /*!<  BCD format time month registers,                      Address offset: 0x20 */
  __IO uint32_t BCDYEAR;                /*!<  BCD format time year registers,                       Address offset: 0x24 */
  __IO uint32_t ALARM;                  /*!<   Alarm Register,                                      Address offset: 0x28 */
  __IO uint32_t TMSEL;                  /*!<  RTCB Time Mark Select,                                Address offset: 0x2C */
  __IO uint32_t ADJR;                   /*!<  RTCB time Adjust Register,                            Address offset: 0x30 */
  __IO uint32_t RSV1[3];                /*!<  RESERVED REGISTER,                                    Address offset: 0x34 */
  __IO uint32_t CR;                     /*!<  RTCB Control Register,                                Address offset: 0x40 */
  __IO uint32_t RSV2;                   /*!<  RESERVED REGISTER,                                    Address offset: 0x44 */
  __IO uint32_t STPCR;                  /*!<  RTCB Time Stamp Control Register,                     Address offset: 0x48 */
  __IO uint32_t STPCLKRR;               /*!<  RTC Time Stamp Clock Record Register,                 Address offset: 0x4C */
  __IO uint32_t STPCALRR;               /*!<  RTCB Time Stamp Calendar Record Register,             Address offset: 0x50 */
  __IO uint32_t RSV3[7];                /*!<  RESERVED REGISTER,                                    Address offset: 0x54 */
  __IO uint32_t BKR0;                   /*!<  RTCBBackup Register0,                                 Address offset: 0x70 */
  __IO uint32_t BKR1;                   /*!<  RTCB Backup Register1,                                Address offset: 0x74 */
  __IO uint32_t BKR2;                   /*!<  RTCB Backup Register2,                                Address offset: 0x78 */
  __IO uint32_t BKR3;                   /*!<  RTCB Backup Register3,                                Address offset: 0x7C */
  __IO uint32_t BKR4;                   /*!<  RTCB Backup Register4,                                Address offset: 0x80 */
}RTCB_Type;


/* ================================================================================ */
/* ================                       LCD                      ================ */
/* ================================================================================ */

typedef struct
{
  __IO uint32_t CR;                     /*!<  LCD Control Register,                                 Address offset: 0x00 */
  __IO uint32_t TEST;                   /*!<  LCD test Register,                                    Address offset: 0x04 */
  __IO uint32_t FCR;                    /*!<  LCD Frequency Control Register,                       Address offset: 0x08 */
  __IO uint32_t FLKT;                   /*!<  LCD Flick Time Register,                              Address offset: 0x0C */
  __IO uint32_t RSV1;                   /*!<  RESERVED REGISTER,                                    Address offset: 0x10 */
  __IO uint32_t IER;                    /*!<  LCD Interrupt Enable Register,                        Address offset: 0x14 */
  __IO uint32_t ISR;                    /*!<  LCD Interrupt Status Register,                        Address offset: 0x18 */
  __IO uint32_t RSV2[2];                /*!<  RESERVED REGISTER,                                    Address offset: 0x1C */
  __IO uint32_t DATA0;                  /*!<  LCD data buffer registers 0,                          Address offset: 0x24 */
  __IO uint32_t DATA1;                  /*!<  LCD data buffer registers 1,                          Address offset: 0x28 */
  __IO uint32_t DATA2;                  /*!<  LCD data buffer registers 2,                          Address offset: 0x2C */
  __IO uint32_t DATA3;                  /*!<  LCD data buffer registers 3,                          Address offset: 0x30 */
  __IO uint32_t DATA4;                  /*!<  LCD data buffer registers 4,                          Address offset: 0x34 */
  __IO uint32_t DATA5;                  /*!<  LCD data buffer registers 5,                          Address offset: 0x38 */
  __IO uint32_t DATA6;                  /*!<  LCD data buffer registers 6,                          Address offset: 0x3C */
  __IO uint32_t DATA7;                  /*!<  LCD data buffer registers 7,                          Address offset: 0x40 */
  __IO uint32_t DATA8;                  /*!<  LCD data buffer registers 8,                          Address offset: 0x44 */
  __IO uint32_t DATA9;                  /*!<  LCD data buffer registers 9,                          Address offset: 0x48 */
  __IO uint32_t RSV3;                   /*!<  RESERVED REGISTER,                                    Address offset: 0x4C */
  __IO uint32_t COMEN;                  /*!<  LCD COM Enable Register,                              Address offset: 0x50 */
  __IO uint32_t SEGEN0;                 /*!<  LCD SEG Enable Register0,                             Address offset: 0x54 */
  __IO uint32_t SEGEN1;                 /*!<  LCD SEG Enable Register 1,                            Address offset: 0x58 */
}LCD_Type;


/* ================================================================================ */
/* ================                       ADC                      ================ */
/* ================================================================================ */

typedef struct
{
  __IO uint32_t ISR;                    /*!<  ADC Interrupt and Status Register,                    Address offset: 0x00 */
  __IO uint32_t IER;                    /*!<  ADC Interrupt Enable Register,                        Address offset: 0x04 */
  __IO uint32_t CR1;                    /*!<  ADC Control Register,                                 Address offset: 0x08 */
  __IO uint32_t CR2;                    /*!<  ADC Control Register,                                 Address offset: 0x0C */
  __IO uint32_t CALR;                   /*!<  ADC Calibration Register,                             Address offset: 0x10 */
  __IO uint32_t CFGR1;                  /*!<  ADC Config Register1,                                 Address offset: 0x14 */
  __IO uint32_t CFGR2;                  /*!<  ADC Config Register2,                                 Address offset: 0x18 */
  __IO uint32_t SMTR;                   /*!<  ADC Sampling Time Register,                           Address offset: 0x1C */
  __IO uint32_t CHER;                   /*!<  ADC Channel Enable Register,                          Address offset: 0x20 */
  __IO uint32_t DCR;                    /*!<  ADC Differential Channel Control Register,            Address offset: 0x24 */
  __I  uint32_t DR;                     /*!<  ADC Data Register,                                    Address offset: 0x28 */
  __IO uint32_t HLTR;                   /*!<  ADC analog watchdog Threshold Register,               Address offset: 0x2C */
}ADC_Type;


/* ================================================================================ */
/* ================                       DAC                      ================ */
/* ================================================================================ */

typedef struct
{
  __IO uint32_t CR1;                    /*!<  DAC Control Register,                                 Address offset: 0x00 */
  __IO uint32_t CR2;                    /*!<  DAC Control Register,                                 Address offset: 0x04 */
  __IO uint32_t CFGR;                   /*!<  DAC Config Register,                                  Address offset: 0x08 */
  __O  uint32_t SWTRGR;                 /*!<  DAC Software Trigger Register,                        Address offset: 0x0C */
  __IO uint32_t DHR;                    /*!<  DAC Data Holding Register,                            Address offset: 0x10 */
  __IO uint32_t ISR;                    /*!<  DAC Interrupt Status Register,                        Address offset: 0x14 */
  __IO uint32_t IER;                    /*!<  DAC Interrupt Enable Register,                        Address offset: 0x18 */
  __IO uint32_t SHTR;                   /*!<  DAC Sample Hold Time Register,                        Address offset: 0x1C */
}DAC_Type;


/* ================================================================================ */
/* ================                       PGL                      ================ */
/* ================================================================================ */

typedef struct
{
  __IO uint32_t CR;                     /*!<  PGL Control Register,                                 Address offset: 0x00 */
  __IO uint32_t CFGR0;                  /*!<  PGL Config Register0,                                 Address offset: 0x04 */
  __IO uint32_t CFGR1;                  /*!<  PGL Config Register1,                                 Address offset: 0x08 */
  __IO uint32_t CFGR2;                  /*!<  PGL Config Register2,                                 Address offset: 0x0C */
  __IO uint32_t CFGR3;                  /*!<  PGL Config Register3,                                 Address offset: 0x10 */
  __IO uint32_t IER;                    /*!<  PGL Interrupt Enable Register,                        Address offset: 0x14 */
  __IO uint32_t ISR;                    /*!<  PGL Interrupt Status Register,                        Address offset: 0x18 */
  __IO uint32_t LUT0;                   /*!<  Look Up Table0,                                       Address offset: 0x1C */
  __IO uint32_t LUT1;                   /*!<  Look Up Table1,                                       Address offset: 0x20 */
  __IO uint32_t LUT2;                   /*!<  Look Up Table2,                                       Address offset: 0x24 */
  __IO uint32_t LUT3;                   /*!<  Look Up Table3,                                       Address offset: 0x28 */
}PGL_Type;


/* ================================================================================ */
/* ================                      GPIO                      ================ */
/* ================================================================================ */

typedef struct
{
  __IO uint32_t INEN;                   /*!<  GPIOx Input Enable Register,                          Address offset: 0x00 */
  __IO uint32_t PUEN;                   /*!<  GPIOx Pull-Up Enable Register,                        Address offset: 0x04 */
  __IO uint32_t ODEN;                   /*!<  GPIOx Open-Drain Enable Register,                     Address offset: 0x08 */
  __IO uint32_t FCR;                    /*!<  GPIOx Function Control Register,                      Address offset: 0x0C */
  __IO uint32_t DO;                     /*!<  GPIOx Data Output Register,                           Address offset: 0x10 */
  __O  uint32_t DSET;                   /*!<  GPIOx Data Set Register,                              Address offset: 0x14 */
  __O  uint32_t DRST;                   /*!<  GPIOx Data Reset Register,                            Address offset: 0x18 */
  __I  uint32_t DIN;                    /*!<  GPIOx Data Input Register,                            Address offset: 0x1C */
  __IO uint32_t DFS;                    /*!<  GPIOx Digital Function Select,                        Address offset: 0x20 */
  __IO uint32_t RSV1;                   /*!<  RESERVED REGISTER,                                    Address offset: 0x24 */
  __IO uint32_t ANEN;                   /*!<  GPIOx Analog channel Enable Register,                 Address offset: 0x28 */
  __IO uint32_t VILR;                   /*!<  GPIOx Voltage Input Low Register,                     Address offset: 0x2C */
}GPIO_Type;


/* ================================================================================ */
/* ================                      GPIO_COMMON               ================ */
/* ================================================================================ */

typedef struct
{
  __IO uint32_t EXTISEL0;               /*!<  External Interrupt Input Select Register0,            Address offset: 0x00 */
  __IO uint32_t EXTISEL1;               /*!<  External Interrupt Input Select Register1,            Address offset: 0x04 */
  __IO uint32_t EXTIEDS0;               /*!<  External Interrupt Edge Select and Enable Register0,  Address offset: 0x08 */
  __IO uint32_t EXTIEDS1;               /*!<  External Interrupt Edge Select and Enable Register1,  Address offset: 0x0C */
  __IO uint32_t EXTIDF;                 /*!<  External Interrupt Digital Filter Register,           Address offset: 0x10 */
  __IO uint32_t EXTIISR;                /*!<  External Interrupt and Status Register,               Address offset: 0x14 */
  __I  uint32_t EXTIDI;                 /*!<  External Interrupt Data Input Register,               Address offset: 0x18 */
  __IO uint32_t RSV1[9];                /*!<  RESERVED REGISTER,                                    Address offset: 0x1C */
  __IO uint32_t FOUTSEL;                /*!<  Frequency Output Select Register,                     Address offset: 0x100 */
  __IO uint32_t RSV2[63];               /*!<  RESERVED REGISTER,                                    Address offset: 0x104 */
  __IO uint32_t PINWKEN;                /*!<  Wakeup Enable Register,                               Address offset: 0x200 */
}GPIO_COMMON_Type;


/* ================================================================================ */
/* ================                       DBG                      ================ */
/* ================================================================================ */

typedef struct
{
  __I  uint32_t SYSCFG;                 /*!<  ,                                                     Address offset: 0x00 */
  __IO uint32_t CR;               /*!<  ,                                                     Address offset: 0x04 */
  __IO uint32_t HDFR;                /*!<  ,                                                     Address offset: 0x08 */
}DBG_Type;



/* --------------------  End of section using anonymous unions  ------------------- */
#if defined(__CC_ARM)
  #pragma pop
#elif defined(__ICCARM__)
  /* leave anonymous unions enabled */
#elif defined(__GNUC__)
/* anonymous unions are enabled by default */
#elif defined(__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined(__TASKING__)
  #pragma warning restore
#else
  #warning Not supported compiler type
#endif


/* ================================================================================ */
/* ================              CPU memory map                    ================ */
/* ================================================================================ */


/* Peripheral and SRAM base address */

#define FLASH_BASE            ((     uint32_t)0x00000000)
#define SRAM_BASE             ((     uint32_t)0x20000000)
#define PERIPH_BASE           ((     uint32_t)0x40000000)


/* ================================================================================ */
/* ================              Peripheral memory map             ================ */
/* ================================================================================ */

/* Peripheral memory map */

#define FLASH_R_BASE                    (PERIPH_BASE        +0x00001000)
#define PMU_BASE                        (PERIPH_BASE        +0x00002000)
#define VREFP_BASE                      (PERIPH_BASE        +0x0000203C)
#define VREF_BASE                       (PERIPH_BASE        +0x0001A400)
#define VAO_BASE                        (PERIPH_BASE        +0x0001F000)
#define CDIF_BASE                       (PERIPH_BASE        +0x0001E000)
#define RMU_BASE                        (PERIPH_BASE        +0x00002800)
#define IWDT_BASE                       (PERIPH_BASE        +0x00011400)
#define WWDT_BASE                       (PERIPH_BASE        +0x00011800)
#define CMU_BASE                        (PERIPH_BASE        +0x00002400)
#define SVD_BASE                        (PERIPH_BASE        +0x00012800)
#define AES_BASE                        (PERIPH_BASE        +0x00013800)
#define RNG_BASE                        (PERIPH_BASE        +0x00013C00)
#define OPA_BASE                        (PERIPH_BASE        +0x0001A000)
#define COMP1_BASE                      (PERIPH_BASE        +0x00015400)
#define COMP2_BASE                      (PERIPH_BASE        +0x00015404)
#define COMP3_BASE                      (PERIPH_BASE        +0x00015408)
#define COMP_COMMON_BASE                (PERIPH_BASE        +0x0001540C)
#define DIVAS_BASE                      (PERIPH_BASE        +0x00019C00)
#define I2C_BASE                        (PERIPH_BASE        +0x00012400)
#define UART_COMMON_BASE                (PERIPH_BASE        +0x00017C00)
#define UART0_BASE                      (PERIPH_BASE        +0x00012000)
#define UART1_BASE                      (PERIPH_BASE        +0x00016800)
#define UART3_BASE                      (PERIPH_BASE        +0x00017000)
#define UART4_BASE                      (PERIPH_BASE        +0x00017400)
#define UART5_BASE                      (PERIPH_BASE        +0x00017800)
#define LPUART0_BASE                    (PERIPH_BASE        +0x00014000)
#define LPUART1_BASE                    (PERIPH_BASE        +0x00014400)
#define LPUART2_BASE                    (PERIPH_BASE        +0x00015000)
#define SPI0_BASE                       (PERIPH_BASE        +0x00010400)
#define SPI1_BASE                       (PERIPH_BASE        +0x00010800)
#define SPI2_BASE                       (PERIPH_BASE        +0x00014800)
#define U7816_BASE                      (PERIPH_BASE        +0x00011C00)
#define CAN_BASE                        (PERIPH_BASE        +0x00019400)
#define DMA_BASE                        (PERIPH_BASE        +0x00000400)
#define CRC_BASE                        (PERIPH_BASE        +0x00010000)
#define ATIM_BASE                       (PERIPH_BASE        +0x00013000)
#define GPTIM0_BASE                     (PERIPH_BASE        +0x00014C00)
#define GPTIM1_BASE                     (PERIPH_BASE        +0x00016400)
#define GPTIM2_BASE                     (PERIPH_BASE        +0x00018000)
#define BSTIM32_BASE                    (PERIPH_BASE        +0x00016000)
#define BSTIM16_BASE                    (PERIPH_BASE        +0x00018C00)
#define LPTIM32_BASE                    (PERIPH_BASE        +0x00013400)
#define LPTIM16_BASE                    (PERIPH_BASE        +0x00018800)
#define RTCA_BASE                       (PERIPH_BASE        +0x00011000)
#define RTCB_BASE                       (PERIPH_BASE        +0x0001F000)
#define LCD_BASE                        (PERIPH_BASE        +0x00010C00)
#define ADC_BASE                        (PERIPH_BASE        +0x00015C00)
#define DAC_BASE                        (PERIPH_BASE        +0x00019800)
#define PGL_BASE                        (PERIPH_BASE        +0x00016C00)
#define GPIOA_BASE                      (PERIPH_BASE        +0x00000C00)
#define GPIOB_BASE                      (PERIPH_BASE        +0x00000C40)
#define GPIOC_BASE                      (PERIPH_BASE        +0x00000C80)
#define GPIOD_BASE                      (PERIPH_BASE        +0x00000CC0)
#define GPIOE_BASE                      (PERIPH_BASE        +0x00000D00)
#define GPIO_COMMON_BASE                (PERIPH_BASE        +0x00000DC0)
#define DBG_BASE                        (PERIPH_BASE        +0x00000000)

/* ================================================================================ */
/* ================             Peripheral declaration             ================ */
/* ================================================================================ */

#define FLASH                           ((FLASH_Type        *) FLASH_R_BASE     )
#define PMU                             ((PMU_Type          *) PMU_BASE         )
#define VREFP                           ((VREFP_Type        *) VREFP_BASE       )
#define VREF                            ((VREF_Type         *) VREF_BASE        )
#define VAO                             ((VAO_Type          *) VAO_BASE         )
#define CDIF                            ((CDIF_Type         *) CDIF_BASE        )
#define RMU                             ((RMU_Type          *) RMU_BASE         )
#define IWDT                            ((IWDT_Type         *) IWDT_BASE        )
#define WWDT                            ((WWDT_Type         *) WWDT_BASE        )
#define CMU                             ((CMU_Type          *) CMU_BASE         )
#define SVD                             ((SVD_Type          *) SVD_BASE         )
#define AES                             ((AES_Type          *) AES_BASE         )
#define RNG                             ((RNG_Type          *) RNG_BASE         )
#define OPA                             ((OPA_Type          *) OPA_BASE         )
#define COMP1                           ((COMP_Type         *) COMP1_BASE       )
#define COMP2                           ((COMP_Type         *) COMP2_BASE       )
#define COMP3                           ((COMP_Type         *) COMP3_BASE       )
#define COMP_COMMON                     ((COMP_COMMON_Type  *)COMP_COMMON_BASE  )
#define DIVAS                           ((DIVAS_Type        *) DIVAS_BASE       )
#define I2C                             ((I2C_Type          *) I2C_BASE         )
#define UART_COMMON                     ((UART_COMMON_Type  *) UART_COMMON_BASE  )
#define UART0                           ((UART_Type        *) UART0_BASE       )
#define UART1                           ((UART_Type        *) UART1_BASE       )
#define UART3                           ((UART_Type        *) UART3_BASE       )
#define UART4                           ((UART_Type        *) UART4_BASE       )
#define UART5                           ((UART_Type        *) UART5_BASE       )
#define LPUART0                         ((LPUART_Type      *) LPUART0_BASE     )
#define LPUART1                         ((LPUART_Type      *) LPUART1_BASE     )
#define LPUART2                         ((LPUART_Type      *) LPUART2_BASE     )
#define SPI0                            ((SPI_Type          *) SPI0_BASE        )
#define SPI1                            ((SPI_Type          *) SPI1_BASE        )
#define SPI2                            ((SPI_Type          *) SPI2_BASE        )
#define U7816                           ((U7816_Type        *) U7816_BASE       )
#define CAN                             ((CAN_Type          *) CAN_BASE         )
#define DMA                             ((DMA_Type          *) DMA_BASE         )
#define CRC                             ((CRC_Type          *) CRC_BASE         )
#define ATIM                            ((ATIM_Type         *) ATIM_BASE        )
#define GPTIM0                          ((GPTIM_Type       *) GPTIM0_BASE      )
#define GPTIM1                          ((GPTIM_Type       *) GPTIM1_BASE      )
#define GPTIM2                          ((GPTIM_Type       *) GPTIM2_BASE      )
#define BSTIM32                         ((BSTIM32_Type      *) BSTIM32_BASE     )
#define BSTIM16                         ((BSTIM16_Type      *) BSTIM16_BASE     )
#define LPTIM32                         ((LPTIM32_Type      *) LPTIM32_BASE     )
#define LPTIM16                         ((LPTIM16_Type      *) LPTIM16_BASE     )
#define RTCA                            ((RTCA_Type         *) RTCA_BASE        )
#define RTCB                            ((RTCB_Type         *) RTCB_BASE        )
#define LCD                             ((LCD_Type          *) LCD_BASE         )
#define ADC                             ((ADC_Type          *) ADC_BASE         )
#define DAC                             ((DAC_Type          *) DAC_BASE         )
#define PGL                             ((PGL_Type          *) PGL_BASE         )
#define GPIOA                           ((GPIO_Type        *) GPIOA_BASE       )
#define GPIOB                           ((GPIO_Type        *) GPIOB_BASE       )
#define GPIOC                           ((GPIO_Type        *) GPIOC_BASE       )
#define GPIOD                           ((GPIO_Type        *) GPIOD_BASE       )
#define GPIOE                           ((GPIO_Type        *) GPIOE_BASE       )
#define GPIO                            ((GPIO_COMMON_Type  *) GPIO_COMMON_BASE )
#define DBG                             ((DBG_Type          *) DBG_BASE         )

/* ================================================================================ */
/* ================             Peripheral include                 ================ */
/* ================================================================================ */

/** @} */ /* End of group Device_Peripheral_Registers */
/** @} */ /* End of group FM33LG0XX */
/** @} */ /* End of group Keil */

#ifdef __cplusplus
}
#endif

#endif  /* FM33LG0XX_H */

