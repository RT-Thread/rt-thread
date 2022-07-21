
/****************************************************************************************************//**
 * @file     FM33LC0XX.h
 *
 * @brief    CMSIS Cortex-M0 Peripheral Access Layer Header File for
 *           FM33LC0XX from Keil.
 *
 * @version  V0.0.1
 * @date     13. august 2019
 *
 * @note     Generated with SVDConv V2.87e
 *           from CMSIS SVD File 'FM33LC0XX.SVD' Version 1.0,
 *
 * @par      ARM Limited (ARM) is supplying this software for use with Cortex-M
 *           processor based microcontroller, but can be equally used for other
 *           suitable processor architectures. This file can be freely distributed.
 *           Modifications to this file shall be clearly marked.
 *
 *           THIS SOFTWARE IS PROVIDED "AS IS". NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 *           OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 *           MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 *           ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 *           CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 *******************************************************************************************************/


/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup FM33LC0XX
  * @{
  */

#ifndef __FM33LC0XX_H
#define __FM33LC0XX_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
  * @brief Configuration of the Cortex-M0 Processor and Core Peripherals
  */
#define __CM0_REV                    0x0100U /*!< Cortex-M0 Core Revision                                               */
#define __MPU_PRESENT                0U      /*!< MPU present or not                                                    */
#define __VTOR_PRESENT               1U      /*!< VTOR present or not                                                   */
#define __NVIC_PRIO_BITS             2U      /*!< Number of Bits used for Priority Levels                               */
#define __Vendor_SysTickConfig       0U      /*!< Set to 1 if different SysTick Config is used                          */


/**
 * @brief FM33LC0XX Interrupt Number Definition, according to the selected device
 *        in @ref Library_configuration_section
 */
typedef enum {
/******  Cortex-M0 Processor Exceptions Numbers ****************************************************************/
  Reset_IRQn                    = -15,     /*!<  1  Reset Vector, invoked on Power up and warm reset           */
  NMI_IRQn                      = -14,     /*!<  2  Non maskable Interrupt, cannot be stopped or preempted     */
  HardFault_IRQn                = -13,     /*!<  3  Hard Fault, all classes of Fault                           */
  SVCall_IRQn                   = -5,      /*!<  11  System Service Call via SVC instruction                   */
  PendSV_IRQn                   = -2,      /*!<  14  Pendable request for system service                       */
  SysTick_IRQn                  = -1,      /*!<  15  System Tick Timer                                         */
/******  FM33LC0XX specific Interrupt Numbers ******************************************************************/
  WWDT_IRQn                     = 0,       /*!<  0    Window WatchDog Interrupt                                */
  SVD_IRQn                      = 1,       /*!<  1    SVD Interrupt                                            */
  RTC_IRQn                      = 2,       /*!<  2    RTC Interrupt                                            */
  FLASH_IRQn                    = 3,       /*!<  3    FLASH global Interrupt                                   */
  LFDET_IRQn                    = 4,       /*!<  4    LFDET Interrupt                                          */
  ADC_IRQn                      = 5,       /*!<  5    ADC Interrupt                                            */
  IWDT_IRQn                     = 6,       /*!<  6    IWDT Interrupt                                           */
  SPI1_IRQn                     = 7,       /*!<  7    SPI1 Interrupt                                           */
  SPI2_IRQn                     = 8,       /*!<  8    SPI2 Interrupt                                           */
  LCD_IRQn                      = 9,       /*!<  9    LCD Interrupt                                            */
  UART0_IRQn                    = 10,      /*!<  10   UART0 global Interrupt                                   */
  UART1_IRQn                    = 11,      /*!<  11   UART1 global Interrupt                                   */
  UART4_IRQn                    = 12,      /*!<  12   UART4 global Interrupt                                   */
  UART5_IRQn                    = 13,      /*!<  13   UART5 global Interrupt                                   */
  HFDET_IRQn                    = 14,      /*!<  14   HFDET Interrupt                                          */
  U7816_IRQn                    = 15,      /*!<  15   U7816 Interrupt                                          */
  LPUART1_IRQn                  = 16,      /*!<  16   LPUART1 Interrupt                                        */
  I2C_IRQn                      = 17,      /*!<  17   I2C global Interrupt                                     */
  USB_IRQn                      = 18,      /*!<  18   USB Interrupt                                            */
  AES_IRQn                      = 19,      /*!<  19   AES Interrupt                                            */
  LPTIM_IRQn                    = 20,      /*!<  20   LPTIM Interrupt                                          */
  DMA_IRQn                      = 21,      /*!<  21   DMA Interrupt                                            */
  WKUP_IRQn                     = 22,      /*!<  22   WKUP Interrupt                                           */
  OPAx_IRQn                     = 23,      /*!<  23   OPAx Interrupt                                           */
  BSTIM_IRQn                    = 24,      /*!<  24   BSTIM Interrupt                                          */
  COMPx_IRQn                    = 25,      /*!<  25   COMPx Interrupt                                          */
  GPTIM0_IRQn                   = 26,      /*!<  26   GTIM0 global Interrupt                                   */
  GPTIM1_IRQn                   = 27,      /*!<  27   GTIM1 global Interrupt                                   */
  ATIM_IRQn                     = 28,      /*!<  28   ATIM global Interrupt                                    */
  VREF_IRQn                     = 29,      /*!<  29   VREF Interrupt                                           */
  GPIO_IRQn                     = 30,      /*!<  30   GPIO Interrupt                                           */
  LPUART0_IRQn                  = 31       /*!<  31   LPUART0 Interrupt                                        */
} IRQn_Type;


/** @addtogroup Configuration_of_CMSIS
  * @{
  */


/* ================================================================================ */
/* ================      Processor and Core Peripheral Section     ================ */
/* ================================================================================ */


#include "core_cm0plus.h"                            /*!< Cortex-M0 processor and core peripherals             */
#include "system_fm33lc0xx.h"                        /*!< FM33LC0XX System                                     */
#include <stdint.h>

/** @addtogroup Peripheral_registers_structures
  * @{
  */

/**
  * @brief Analog to Digital Converter
  */
typedef struct
{
  __IO uint32_t ISR;              /*!< ADC Interrupt and Status Register,                   Address offset: 0x00 */
  __IO uint32_t IER;              /*!< ADC Interrupt Enable Register,                       Address offset: 0x04 */
  __IO uint32_t CR;               /*!< ADC Control Register,                                Address offset: 0x08 */
  __IO uint32_t CFGR;             /*!< ADC Config Register,                                 Address offset: 0x0C */
  __IO uint32_t SMTR;             /*!< ADC Sampling Time Register,                          Address offset: 0x10 */
  __IO uint32_t CHER;             /*!< ADC Channel Enable Register,                         Address offset: 0x14 */
  __IO uint32_t DR;               /*!< ADC Data Register,                                   Address offset: 0x18 */
  __IO uint32_t SAMPT;            /*!< ADC Calibration Register,                            Address offset: 0x1C */
  __IO uint32_t HLTR;             /*!< ADC analog watchdog Threshold Register,              Address offset: 0x20 */
} ADC_Type;

typedef struct
{
  __IO uint32_t CR;               /*!< AES Control Register,                                Address offset: 0x00 */
  __IO uint32_t IER;              /*!< AES Interrupt Enable Register,                       Address offset: 0x04 */
  __IO uint32_t ISR;              /*!< AES Interrupt Status Register,                       Address offset: 0x08 */
  __IO uint32_t DIR;              /*!< AES Data Input Register,                             Address offset: 0x0C */
  __IO uint32_t DOR;              /*!< AES Data Output Register,                            Address offset: 0x10 */
  __IO uint32_t KEY0;             /*!< AES Key Register 0,                                  Address offset: 0x14 */
  __IO uint32_t KEY1;             /*!< AES Key Register 1,                                  Address offset: 0x18 */
  __IO uint32_t KEY2;             /*!< AES Key Register 2,                                  Address offset: 0x1C */
  __IO uint32_t KEY3;             /*!< AES Key Register 3,                                  Address offset: 0x20 */
  __IO uint32_t KEY4;             /*!< AES Key Register 4,                                  Address offset: 0x24 */
  __IO uint32_t KEY5;             /*!< AES Key Register 5,                                  Address offset: 0x28 */
  __IO uint32_t KEY6;             /*!< AES Key Register 6,                                  Address offset: 0x2C */
  __IO uint32_t KEY7;             /*!< AES Key Register 7,                                  Address offset: 0x30 */
  __IO uint32_t IVR0;             /*!< AES Initial Vector Register 0,                       Address offset: 0x34 */
  __IO uint32_t IVR1;             /*!< AES Initial Vector Register 1,                       Address offset: 0x38 */
  __IO uint32_t IVR2;             /*!< AES Initial Vector Register 2,                       Address offset: 0x3C */
  __IO uint32_t IVR3;             /*!< AES Initial Vector Register 3,                       Address offset: 0x40 */
} AES_Type;

typedef struct
{
  __IO uint32_t CR1;              /*!< ATIM Control Register1,                              Address offset: 0x00 */
  __IO uint32_t CR2;              /*!< ATIM Control Register2,                              Address offset: 0x04 */
  __IO uint32_t SMCR;             /*!< ATIM Slave Mode Control Register,                    Address offset: 0x08 */
  __IO uint32_t DIER;             /*!< ATIM DMA and Interrupt Enable Register,              Address offset: 0x0C */
  __IO uint32_t ISR;              /*!< ATIM Interrupt Status Register,                      Address offset: 0x10 */
  __IO uint32_t EGR;              /*!< ATIM Event Generation Register,                      Address offset: 0x14 */
  __IO uint32_t CCMR1;            /*!< ATIM Capture/Compare Mode Register1,                 Address offset: 0x18 */
  __IO uint32_t CCMR2;            /*!< ATIM Capture/Compare Mode Register2,                 Address offset: 0x1C */
  __IO uint32_t CCER;             /*!< ATIM Capture/Compare Enable Register,                Address offset: 0x20 */
  __IO uint32_t CNT;              /*!< ATIM Counter Register,                               Address offset: 0x24 */
  __IO uint32_t PSC;              /*!< ATIM Prescaler Register,                             Address offset: 0x28 */
  __IO uint32_t ARR;              /*!< ATIM Auto-Reload Register,                           Address offset: 0x2C */
  __IO uint32_t RCR;              /*!< ATIM Repetition Counter Register,                    Address offset: 0x30 */
  __IO uint32_t CCR1;             /*!< ATIM Capture/Compare Register1,                      Address offset: 0x34 */
  __IO uint32_t CCR2;             /*!< ATIM Capture/Compare Register2,                      Address offset: 0x38 */
  __IO uint32_t CCR3;             /*!< ATIM Capture/Compare Register3,                      Address offset: 0x3C */
  __IO uint32_t CCR4;             /*!< ATIM Capture/Compare Register4,                      Address offset: 0x40 */
  __IO uint32_t BDTR;             /*!< ATIM Break and Deadtime Register,                    Address offset: 0x44 */
  __IO uint32_t DCR;              /*!< ATIM DMA Control Register,                           Address offset: 0x48 */
  __IO uint32_t DMAR;             /*!< ATIM DMA Access Register,                            Address offset: 0x4C */
  __IO uint32_t RSV0;             /*!< RESERVED REGISTER0,                                  Address offset: 0x50 */
  __IO uint32_t RSV1;             /*!< RESERVED REGISTER1,                                  Address offset: 0x54 */
  __IO uint32_t RSV2;             /*!< RESERVED REGISTER2,                                  Address offset: 0x58 */
  __IO uint32_t RSV3;             /*!< RESERVED REGISTER3,                                  Address offset: 0x5C */
  __IO uint32_t BKCR;             /*!< ATIM Break Control Register,                         Address offset: 0x60 */
} ATIM_Type;

typedef struct
{
  __IO uint32_t CR1;              /*!< BSTIM Control Register1,                             Address offset: 0x00 */
  __IO uint32_t CR2;              /*!< BSTIM Control Register2,                             Address offset: 0x04 */
  __IO uint32_t RSV0;             /*!< RESERVED REGISTER0,                                  Address offset: 0x08 */
  __IO uint32_t IER;              /*!< BSTIM Interrupt Enable Register,                     Address offset: 0x0C */
  __IO uint32_t ISR;              /*!< BSTIM Interrupt Status Register,                     Address offset: 0x10 */
  __IO uint32_t EGR;              /*!< BSTIM Event Generation Register,                     Address offset: 0x14 */
  __IO uint32_t RSV1;             /*!< RESERVED REGISTER1,                                  Address offset: 0x18 */
  __IO uint32_t RSV2;             /*!< RESERVED REGISTER2,                                  Address offset: 0x1C */
  __IO uint32_t RSV3;             /*!< RESERVED REGISTER3,                                  Address offset: 0x20 */
  __IO uint32_t CNT;              /*!< BSTIM Counter Register,                              Address offset: 0x24 */
  __IO uint32_t PSC;              /*!< BSTIM Prescaler Register,                            Address offset: 0x28 */
  __IO uint32_t ARR;              /*!< BSTIM Auto-Reload Register,                          Address offset: 0x2C */
} BSTIM32_Type;

typedef struct
{
  __IO uint32_t CR;              /*!< ComparatorControl Register 1,                        Address offset: 0x00 */

} COMP_Type;

typedef struct
{
  __IO uint32_t ICR;             /*!< Comparator Interrupt Config Register,                Address offset: 0x08 */
  __IO uint32_t ISR;             /*!< Comparator Interrupt Status Register,                Address offset: 0x0C */
} COMP_COMMON_Type;

typedef struct
{
  __IO uint32_t DR;               /*!< CRC Data Register,                                   Address offset: 0x00 */
  __IO uint32_t CR;               /*!< CRC Control Register,                                Address offset: 0x04 */
  __IO uint32_t LFSR;             /*!< CRC Linear Feedback Shift Register,                  Address offset: 0x08 */
  __IO uint32_t XOR;              /*!< CRC output XOR Register,                             Address offset: 0x0C */
  __IO uint32_t RSV0;             /*!< RESERVED REGISTER0,                                  Address offset: 0x10 */
  __IO uint32_t RSV1;             /*!< RESERVED REGISTER1,                                  Address offset: 0x14 */
  __IO uint32_t RSV2;             /*!< RESERVED REGISTER2,                                  Address offset: 0x18 */
  __IO uint32_t POLY;             /*!< CRC Polynominal Register,                            Address offset: 0x1C */
} CRC_Type;

typedef struct
{
  __IO uint32_t RSV;
  __IO uint32_t CR;               /*!< Debug Configuration Register */
  __IO uint32_t HDFR;             /*!< HardFault Flag Register*/

} DBG_Type;

typedef struct
{
  __IO uint32_t GCR;              /*!< DMA Global Control Register         ,                Address offset: 0x00 */
  __IO uint32_t CH0CR;            /*!< Channel 0 Control Register          ,                Address offset: 0x04 */
  __IO uint32_t CH0MAD;           /*!< Channel 0 Memory Address Register   ,                Address offset: 0x08 */
  __IO uint32_t CH1CR;            /*!< Channel 1 Control Register          ,                Address offset: 0x0C */
  __IO uint32_t CH1MAD;           /*!< Channel 1 Memory Address Register   ,                Address offset: 0x10 */
  __IO uint32_t CH2CR;            /*!< Channel 2 Control Register          ,                Address offset: 0x14 */
  __IO uint32_t CH2MAD;           /*!< Channel 2 Memory Address Register   ,                Address offset: 0x18 */
  __IO uint32_t CH3CR;            /*!< Channel 3 Control Register          ,                Address offset: 0x1C */
  __IO uint32_t CH3MAD;           /*!< Channel 3 Memory Address Register   ,                Address offset: 0x20 */
  __IO uint32_t CH4CR;            /*!< Channel 4 Control Register          ,                Address offset: 0x24 */
  __IO uint32_t CH4MAD;           /*!< Channel 4 Memory Address Register   ,                Address offset: 0x28 */
  __IO uint32_t CH5CR;            /*!< Channel 5 Control Register          ,                Address offset: 0x2C */
  __IO uint32_t CH5MAD;           /*!< Channel 5 Memory Address Register   ,                Address offset: 0x30 */
  __IO uint32_t CH6CR;            /*!< Channel 6 Control Register          ,                Address offset: 0x34 */
  __IO uint32_t CH6MAD;           /*!< Channel 6 Memory Address Register   ,                Address offset: 0x38 */
  __IO uint32_t CH7CR;            /*!< Channel 7 Control Register          ,                Address offset: 0x3C */
  __IO uint32_t CH7FLSAD;         /*!< Channel 7 Flash Address Register    ,                Address offset: 0x40 */
  __IO uint32_t CH7RAMAD;         /*!< Channel 7 RAM Address Register      ,                Address offset: 0x44 */
  __IO uint32_t ISR;              /*!< DMA Interrupt Status Register       ,                Address offset: 0x48 */
} DMA_Type;

typedef struct
{
  __IO uint32_t IER;              /*!< XTLF Oscillation Fail Detection Interrupt Enable Register, Address offset: 0x00 */
  __IO uint32_t ISR;              /*!< XTLF Oscillation Fail Detection Interrupt Status Register, Address offset: 0x04 */
}FDET_Type;


typedef struct
{
  __IO uint32_t RDCR;             /*!< Flash Read Control Register,                         Address offset: 0x00 */
  __IO uint32_t PFCR;             /*!< Flash Prefetch Control Register,                     Address offset: 0x04 */
  __I  uint32_t OPTBR;            /*!< Flash Option Bytes Register,                         Address offset: 0x08 */
  __IO uint32_t ACLOCK1;          /*!< Flash Application Code Lock Register 1,              Address offset: 0x0C */
  __IO uint32_t ACLOCK2;          /*!< Flash Application Code Lock Register 2,              Address offset: 0x10 */
  __IO uint32_t EPCR;             /*!< Flash Erase/Program Control Register,                Address offset: 0x14 */
  __IO uint32_t KEY;              /*!< Flash Key Register,                                  Address offset: 0x18 */
  __IO uint32_t IER;              /*!< Flash Interrupt Enable Register,                     Address offset: 0x1C */
  __IO uint32_t ISR;              /*!< Flash Interrupt Status Register,                     Address offset: 0x20 */
} FLASH_Type;

typedef struct
{
  __IO uint32_t INEN;             /*!< Input Enable Register          */
  __IO uint32_t PUEN;             /*!< Pull-Up Enable Register        */
  __IO uint32_t ODEN;             /*!< Open-Drain Enable Register     */
  __IO uint32_t FCR;              /*!< Function Control Register      */
  __IO uint32_t DO;               /*!< Data Output Register           */
  __O  uint32_t DSET;             /*!< Data Set Register              */
  __O  uint32_t DRST;             /*!< Data Reset Register            */
  __I uint32_t  DIN;              /*!< Data Input RegisterR           */
  __IO uint32_t DFS;              /*!< Digital Function Select        */
  __IO uint32_t RSV;              /*!< RESERVED REGISTER              */
  __IO uint32_t ANEN;             /*!< Analog channel Enable Register */
} GPIO_Type;

typedef struct
{
  __IO uint32_t EXTISEL;          /*!< External Interrupt input Select Register            */
  __IO uint32_t EXTIEDS;          /*!< External Interrupt Edge Select and Enable Register  */
  __IO uint32_t EXTIDF;           /*!< External Interrupt Digital Filter Register          */
  __IO uint32_t EXTIISR;          /*!< External Interrupt and Status Register              */
  __IO uint32_t EXTIDI;           /*!< External Interrupt Data Input Register              */
  __IO uint32_t RSV0[59];         /*!< RESERVED REGISTER                                   */
  __IO uint32_t FOUTSEL;          /*!< Frequency Output Select Register                    */
  __IO uint32_t RSV1[63];         /*!< RESERVED REGISTER                                   */
  __IO uint32_t PINWKEN;          /*!< Wakeup Enable Register                              */
} GPIO_COMMON_Type;

typedef struct
{
  __IO uint32_t CR1;              /*!< GPTIM Control Register1,                             Address offset: 0x00 */
  __IO uint32_t CR2;              /*!< GPTIM Control Register2,                             Address offset: 0x04 */
  __IO uint32_t SMCR;             /*!< GPTIM Slave Mode Control Register,                   Address offset: 0x08 */
  __IO uint32_t DIER;             /*!< GPTIM DMA and Interrupt Enable Register,             Address offset: 0x0C */
  __IO uint32_t ISR;              /*!< GPTIM Interrupt Status Register,                     Address offset: 0x10 */
  __IO uint32_t EGR;              /*!< GPTIM EVENT GENERATE REGISTER,                       Address offset: 0x14 */
  __IO uint32_t CCMR1;            /*!< GPTIM Capture/Compare Mode Register1,                Address offset: 0x18 */
  __IO uint32_t CCMR2;            /*!< GPTIM Capture/Compare Mode Register2,                Address offset: 0x1C */
  __IO uint32_t CCER;             /*!< GPTIM Capture/Compare Enable Register,               Address offset: 0x20 */
  __IO uint32_t CNT;              /*!< GPTIM Counter Register,                              Address offset: 0x24 */
  __IO uint32_t PSC;              /*!< GPTIM Prescaler Register,                            Address offset: 0x28 */
  __IO uint32_t ARR;              /*!< GPTIM Auto-Reload Register,                          Address offset: 0x2C */
  __IO uint32_t RSV0;             /*!< RESERVED REGISTER0,                                  Address offset: 0x30 */
  __IO uint32_t CCR1;             /*!< GPTIM Capture/Compare Register1,                     Address offset: 0x34 */
  __IO uint32_t CCR2;             /*!< GPTIM Capture/Compare Register2,                     Address offset: 0x38 */
  __IO uint32_t CCR3;             /*!< GPTIM Capture/Compare Register3,                     Address offset: 0x3C */
  __IO uint32_t CCR4;             /*!< GPTIM Capture/Compare Register4,                     Address offset: 0x40 */
  __IO uint32_t RSV1;             /*!< RESERVED REGISTER1,                                  Address offset: 0x44 */
  __IO uint32_t DCR;              /*!< GPTIM DMA CONTROL REGISTER,                          Address offset: 0x48 */
  __IO uint32_t DMAR;             /*!< GPTIM DMA access Register,                           Address offset: 0x4C */
  __IO uint32_t RSV2;             /*!< RESERVED REGISTER2,                                  Address offset: 0x50 */
  __IO uint32_t RSV3;             /*!< RESERVED REGISTER3,                                  Address offset: 0x54 */
  __IO uint32_t RSV4;             /*!< RESERVED REGISTER4,                                  Address offset: 0x58 */
  __IO uint32_t RSV5;             /*!< RESERVED REGISTER5,                                  Address offset: 0x5C */
  __IO uint32_t ITRSEL;           /*!< GPTIM  Internal Trigger Select Register,             Address offset: 0x60 */
} GPTIM_Type;

typedef struct
{
  __IO uint32_t END;              /*!< Dividend Register,                                   Address offset: 0x00 */
  __IO uint32_t SOR;              /*!< Divisor Regsiter,                                    Address offset: 0x04 */
  __IO uint32_t QUOT;             /*!< Quotient Register,                                   Address offset: 0x08 */
  __IO uint32_t REMD;             /*!< Reminder Register,                                   Address offset: 0x0C */
  __IO uint32_t SR;               /*!< Status Register,                                     Address offset: 0x10 */
} DIV_Type;


typedef struct
{
  __IO uint32_t MSPCFGR;          /*!< I2C Master Config Register,                          Address offset: 0x00 */
  __IO uint32_t MSPCR;            /*!< I2C Master Control Register,                         Address offset: 0x04 */
  __IO uint32_t MSPIER;           /*!< I2C Master Intterupt Enable Register,                Address offset: 0x08 */
  __IO uint32_t MSPISR;           /*!< I2C Master Interrupt Status Register,                Address offset: 0x0C */
  __IO uint32_t MSPSR;            /*!< I2C Master Status Register,                          Address offset: 0x10 */
  __IO uint32_t MSPBGR;           /*!< I2C Master Baud rate Generator Register,             Address offset: 0x14 */
  __IO uint32_t MSPBUF;           /*!< I2C Master transfer Buffer,                          Address offset: 0x18 */
  __IO uint32_t MSPTCR;           /*!< I2C Master Timing Control Register,                  Address offset: 0x1C */
  __IO uint32_t MSPTOR;           /*!< I2C Master Time-Out Register,                        Address offset: 0x20 */
  __IO uint32_t SSPCR;            /*!< I2C Slave Control Register,                          Address offset: 0x24 */
  __IO uint32_t SSPIER;           /*!< I2C Slave Interrupt Enable Register,                 Address offset: 0x28 */
  __IO uint32_t SSPISR;           /*!< I2C Slave Interrupt Status Register,                 Address offset: 0x2C */
  __IO uint32_t SSPSR;            /*!< I2C Slave Status Register,                           Address offset: 0x30 */
  __IO uint32_t SSPBUF;           /*!< I2C Slave transfer Buffer,                           Address offset: 0x34 */
  __IO uint32_t SSPADR;           /*!< I2C Slave Address Register,                          Address offset: 0x38 */
} I2C_Type;

typedef struct
{
  __IO uint32_t SERV;             /*!< IWDT Service Register,                               Address offset: 0x00 */
  __IO uint32_t CR;               /*!< IWDT Config Register,                                Address offset: 0x04 */
  __I  uint32_t CNT;              /*!< IWDT Counter Register,                               Address offset: 0x08 */
  __IO uint32_t WIN;              /*!< IWDT Window Register,                                Address offset: 0x0C */
  __IO uint32_t IER;              /*!< IWDT Status Register,                                Address offset: 0x10 */
  __IO uint32_t ISR;              /*!< IWDT Status Register,                                Address offset: 0x10 */
} IWDT_Type;

typedef struct
{
  __IO uint32_t CR;               /*!< LCD Control Register,                                Address offset: 0x00 */
  __IO uint32_t TEST;             /*!< LCD test Register,                                   Address offset: 0x04 */
  __IO uint32_t FCR;              /*!< LCD Frequency Control Register,                      Address offset: 0x08 */
  __IO uint32_t FLKT;             /*!< LCD Flick Time Register,                             Address offset: 0x0C */
  __IO uint32_t RSV0;             /*!< NULL,                                                Address offset: 0x10 */
  __IO uint32_t IER;              /*!< LCD Interrupt Enable Register,                       Address offset: 0x14 */
  __IO uint32_t ISR;              /*!< LCD Interrupt Status Register,                       Address offset: 0x18 */
  __IO uint32_t RSV1;             /*!< NULL,                                                Address offset: 0x1C */
  __IO uint32_t RSV2;             /*!< NULL,                                                Address offset: 0x20 */
  __IO uint32_t DATA0;            /*!< LCD data buffer registers 0,                         Address offset: 0x24 */
  __IO uint32_t DATA1;            /*!< LCD data buffer registers 1,                         Address offset: 0x28 */
  __IO uint32_t DATA2;            /*!< LCD data buffer registers 2,                         Address offset: 0x2C */
  __IO uint32_t DATA3;            /*!< LCD data buffer registers 3,                         Address offset: 0x30 */
  __IO uint32_t DATA4;            /*!< LCD data buffer registers 4,                         Address offset: 0x34 */
  __IO uint32_t DATA5;            /*!< LCD data buffer registers 5,                         Address offset: 0x38 */
  __IO uint32_t DATA6;            /*!< LCD data buffer registers 6,                         Address offset: 0x3C */
  __IO uint32_t DATA7;            /*!< LCD data buffer registers 7,                         Address offset: 0x40 */
  __IO uint32_t RSV3;             /*!< NULL,                                                Address offset: 0x44 */
  __IO uint32_t RSV4;             /*!< NULL,                                                Address offset: 0x48 */
  __IO uint32_t RSV5;             /*!< NULL,                                                Address offset: 0x4C */
  __IO uint32_t COMEN;            /*!< LCD COM Enable Register,                             Address offset: 0x50 */
  __IO uint32_t SEGEN0;           /*!< LCD SEG Enable Register0,                            Address offset: 0x54 */
} LCD_Type;

typedef struct
{
  __IO uint32_t CFGR;             /*!< LPTIM Config Register,                               Address offset: 0x00 */
  __IO uint32_t CNT;              /*!< LPTIM Counter Register,                              Address offset: 0x04 */
  __IO uint32_t CCSR;             /*!< LPTIM Capture/Compare Control and Status Register,   Address offset: 0x08 */
  __IO uint32_t ARR;              /*!< LPTIM Auto-Reload Register,                          Address offset: 0x0C */
  __IO uint32_t IER;              /*!< LPTIM Interrupt Enable Register,                     Address offset: 0x10 */
  __IO uint32_t ISR;              /*!< LPTIM Interrupt Status Register,                     Address offset: 0x14 */
  __IO uint32_t CR;               /*!< LPTIM Control Register,                              Address offset: 0x18 */
  __IO uint32_t RSV;              /*!< RESERVED REGISTER,                                   Address offset: 0x1C */
  __IO uint32_t CCR1;             /*!< LPTIM Capture/Compare Register1,                     Address offset: 0x20 */
  __IO uint32_t CCR2;             /*!< LPTIM Capture/Compare Register2,                     Address offset: 0x24 */
} LPTIM32_Type;

typedef struct
{
  __IO uint32_t CSR;              /*!< LPUART Control Status Register,                      Address offset: 0x00 */
  __IO uint32_t IER;              /*!< LPUART Interrupt Enable Register,                    Address offset: 0x04 */
  __IO uint32_t ISR;              /*!< LPUART Interrupt Status Register,                    Address offset: 0x08 */
  __IO uint32_t BMR;              /*!< LPUART Baud rate Modulation Register,                Address offset: 0x0C */
  __IO uint32_t RXBUF;            /*!< LPUART Receive Buffer Register,                      Address offset: 0x10 */
  __IO uint32_t TXBUF;            /*!< LPUART Transmit Buffer Register,                     Address offset: 0x14 */
  __IO uint32_t DMR;              /*!< LPUART  data Matching Register,                      Address offset: 0x18 */
} LPUART_Type;


typedef struct
{
  __IO uint32_t CR;               /*!< OPA Control Register               */
  __IO uint32_t CALR;             /*!< OPA Calibration Register           */
  __IO uint32_t IER;              /*!< OPA Interrupt Enable Register      */
  __IO uint32_t ISR;              /*!< OPA Interrupt Status Register      */
} OPA_Type;

typedef struct
{
  __IO uint32_t CR;               /*!< Power Management Control Register  */
  __IO uint32_t WKTR;             /*!< Wakeup Time Register               */
  __IO uint32_t WKFR;             /*!< Wakeup Source Flags Register       */
  __IO uint32_t IER;              /*!< PMU Interrupt Enable Register      */
  __IO uint32_t ISR;              /*!< PMU Interrupt and Status Register  */
} PMU_Type;

typedef struct
{
  __IO uint32_t LKPCR;            /*!< Lockup reset Control Register               ,        Address offset: 0x00 */
  __IO uint32_t SOFTRST;          /*!< Software Reset Register                     ,        Address offset: 0x04 */
  __IO uint32_t RSTFR;            /*!< Reset Flag Register                         ,        Address offset: 0x08 */
  __IO uint32_t SYSCLKCR;         /*!< System Clock Control Register               ,        Address offset: 0x0C */
  __IO uint32_t RCHFCR;           /*!< RCHF Control Register                       ,        Address offset: 0x10 */
  __IO uint32_t RCHFTR;           /*!< RCHF Trim Register                          ,        Address offset: 0x14 */
  __IO uint32_t PLLCR;            /*!< PLL Control Register                        ,        Address offset: 0x18 */
  __IO uint32_t LPOSCCR;          /*!< LPOSC Control Register                      ,        Address offset: 0x1C */
  __IO uint32_t LPOSCTR;          /*!< LPOSC Trim Register                         ,        Address offset: 0x20 */
  __IO uint32_t XTLFCR;           /*!< XTLF CONFIG REGISTER                        ,        Address offset: 0x24 */
  __IO uint32_t PCLKCR1;          /*!< Peripheral bus Clock Control Register1      ,        Address offset: 0x28 */
  __IO uint32_t PCLKCR2;          /*!< Peripheral bus Clock Control Register2      ,        Address offset: 0x2C */
  __IO uint32_t PCLKCR3;          /*!< Peripheral bus Clock Control Register3      ,        Address offset: 0x30 */
  __IO uint32_t PCLKCR4;          /*!< Peripheral bus Clock Control Register4      ,        Address offset: 0x34 */
  __IO uint32_t LSCLKSEL;         /*!< LSCLK Select Register                       ,        Address offset: 0x38 */
  __IO uint32_t RSV0;             /*!< RESERVED REGISTER 1                         ,        Address offset: 0x3C */
  __IO uint32_t RSV1;             /*!< RESERVED REGISTER 2                         ,        Address offset: 0x40 */
  __IO uint32_t AHBMCR;           /*!< AHB Master Control Register                 ,        Address offset: 0x44 */
  __IO uint32_t RSV2;             /*!< RESERVED REGISTER 3                         ,        Address offset: 0x48 */
  __IO uint32_t RSV3;             /*!< RESERVED REGISTER 4                         ,        Address offset: 0x4C */
  __IO uint32_t PRSTEN;           /*!< Peripheral Reset Enable Register            ,        Address offset: 0x50 */
  __IO uint32_t AHBRSTCR;         /*!< AHB Peripherals Reset Control Register      ,        Address offset: 0x54 */
  __IO uint32_t APBRSTCR1;        /*!< APB Peripherals Reset Control Register1     ,        Address offset: 0x58 */
  __IO uint32_t APBRSTCR2;        /*!< APB Peripherals Reset Control Register2     ,        Address offset: 0x5C */
  __IO uint32_t XTHFCR;           /*!< XTHF Control Register                       ,        Address offset: 0x60 */
  __IO uint32_t RCMFCR;           /*!< RCMF Control Register                       ,        Address offset: 0x64 */
  __IO uint32_t RCMFTR;           /*!< RCHF Trim Register                          ,        Address offset: 0x68 */
  __IO uint32_t OPCCR1;           /*!< Peripheral Operation Clock Control Register1,        Address offset: 0x6C */
  __IO uint32_t OPCCR2;           /*!< Peripheral Operation Clock Control Register2,        Address offset: 0x70 */
  __IO uint32_t PHYCR;            /*!< PHY Control Register                        ,        Address offset: 0x74 */
  __IO uint32_t PHYBCKCR;         /*!< PHY BCK Control Register                    ,        Address offset: 0x78 */
} RCC_Type;


typedef struct
{
  __IO uint32_t PDRCR;            /*!< PDR Control Register  */
  __IO uint32_t BORCR;            /*!< BOR Control Register  */
} RMU_Type;

typedef struct
{
  __IO uint32_t CR;               /*!< RNG CONTROL REGISTER, */
} RNGCTL_Type;

typedef struct
{
  __IO uint32_t RSV0;             /*!< RESERVED REGISTER,                                   Address offset: 0x00 */
  __IO uint32_t DOR;              /*!< RNG OUTPUT REGISTER,                                 Address offset: 0x04 */
  __IO uint32_t RSV1;             /*!< RESERVED REGISTER,                                   Address offset: 0x08 */
  __IO uint32_t RSV2;             /*!< RESERVED REGISTER,                                   Address offset: 0x0C */
  __IO uint32_t SR;               /*!< RNG FLAG REGISTER,                                   Address offset: 0x10 */
  __IO uint32_t CRCCR;            /*!< RNG CRC CONTROL REGISTER,                            Address offset: 0x14 */
  __IO uint32_t CRCDIR;           /*!< RNG CRC INPUT REGISTER,                              Address offset: 0x18 */
  __IO uint32_t CRCSR;            /*!< RNG CRC FLAG REGISTER,                               Address offset: 0x1C */
} RNG_Type;

typedef struct
{
  __IO uint32_t WER;              /*!< RTC Write Enable Register,                           Address offset: 0x00 */
  __IO uint32_t IER;              /*!< RTC Interrupt Enable Register,                       Address offset: 0x04 */
  __IO uint32_t ISR;              /*!< RTC Interrupt Status Register,                       Address offset: 0x08 */
  __IO uint32_t BCDSEC;           /*!< RTC SECOND IN BCD REGISTER,                          Address offset: 0x0C */
  __IO uint32_t BCDMIN;           /*!< RTC MINITE IN BCD REGISTER,                          Address offset: 0x10 */
  __IO uint32_t BCDHOUR;          /*!< RTC HOUR IN BCD REGISTER,                            Address offset: 0x14 */
  __IO uint32_t BCDDAY;           /*!< RTC DAY IN BCD REGISTER,                             Address offset: 0x18 */
  __IO uint32_t BCDWEEK;          /*!< RTC WEEK IN BCD REGISTER,                            Address offset: 0x1C */
  __IO uint32_t BCDMONTH;         /*!< RTC MONTH IN BCD REGISTER,                           Address offset: 0x20 */
  __IO uint32_t BCDYEAR;          /*!< RTC YEAR IN BCD REGISTER,                            Address offset: 0x24 */
  __IO uint32_t ALARM;            /*!< RTC Alarm Register,                                  Address offset: 0x28 */
  __IO uint32_t TMSEL;            /*!< RTC Time Mark Select,                                Address offset: 0x2C */
  __IO uint32_t ADJUST;           /*!< RTC time Adjust Register,                            Address offset: 0x30 */
  __IO uint32_t ADSIGN;           /*!< RTC time Adjust Sign Register,                       Address offset: 0x34 */
  __IO uint32_t RSV0;             /*!< NULL,                                                Address offset: 0x38 */
  __IO uint32_t SBSCNT;           /*!< RTC Sub-Second Counter,                              Address offset: 0x3C */
  __IO uint32_t RSV1[12];         /*!< NULL,                                                Address offset: 0x40 */
  __IO uint32_t BKR0;             /*!< RTC BACKUP REGISTER0,                                Address offset: 0x70 */
  __IO uint32_t BKR1;             /*!< RTC BACKUP REGISTER1,                                Address offset: 0x74 */
  __IO uint32_t BKR2;             /*!< RTC BACKUP REGISTER2,                                Address offset: 0x78 */
  __IO uint32_t BKR3;             /*!< RTC BACKUP REGISTER3,                                Address offset: 0x7C */
  __IO uint32_t BKR4;             /*!< RTC BACKUP REGISTER4,                                Address offset: 0x80 */
  __IO uint32_t BKR5;             /*!< RTC BACKUP REGISTER5,                                Address offset: 0x84 */
  __IO uint32_t BKR6;             /*!< RTC BACKUP REGISTER6,                                Address offset: 0x88 */
  __IO uint32_t BKR7;             /*!< RTC BACKUP REGISTER7,                                Address offset: 0x8C */
} RTC_Type;

typedef struct
{
  __IO uint32_t CR1;              /*!< SPI1 Control Register1         */
  __IO uint32_t CR2;              /*!< SPI1 Control Register2         */
  __IO uint32_t CR3;              /*!< SPI1 Control Register3         */
  __IO uint32_t IER;              /*!< SPI1 Interrupt Enable Register */
  __IO uint32_t ISR;              /*!< SPI1 Status Register           */
  __IO uint32_t TXBUF;            /*!< SPI1 Transmit Buffer           */
  __IO uint32_t RXBUF;            /*!< SPI1 Receive Buffer            */
} SPI_Type;


typedef struct
{
  __IO uint32_t CFGR;             /*!< SVD Config Register,                                 Address offset: 0x24 */
  __IO uint32_t CR;               /*!< SVD Control Register,                                Address offset: 0x28 */
  __IO uint32_t IER;              /*!< SVD Interrupt Enable Register,                       Address offset: 0x2C */
  __IO uint32_t ISR;              /*!< SVD Interrupt Status Register,                       Address offset: 0x30 */
  __IO uint32_t VSR;              /*!< SVD reference Voltage Select Register,               Address offset: 0x34 */
} SVD_Type;

typedef struct
{
  __IO uint32_t CR;               /*!< U7816 Control Register,                              Address offset: 0x00 */
  __IO uint32_t FFR;              /*!< U7816 Frame Format Register,                         Address offset: 0x04 */
  __IO uint32_t EGTR;             /*!< U7816 Extra Guard Time Register,                     Address offset: 0x08 */
  __IO uint32_t PSC;              /*!< U7816 Prescaler Register,                            Address offset: 0x0C */
  __IO uint32_t BGR;              /*!< U7816 Baud rate Generator Register,                  Address offset: 0x10 */
  __IO uint32_t RXBUF;            /*!< U7816 Receive Buffer,                                Address offset: 0x14 */
  __IO uint32_t TXBUF;            /*!< U7816 Transmit Buffer,                               Address offset: 0x18 */
  __IO uint32_t IER;              /*!< U7816 Interrupt Enable Register,                     Address offset: 0x1C */
  __IO uint32_t ISR;              /*!< U7816 Interrupt Status Register,                     Address offset: 0x20 */
} U7816_Type;

typedef struct
{
  __IO uint32_t RSV0;             /*!< RESERVED REGISTER0,                                  Address offset: 0x00 */
  __IO uint32_t RSV1;             /*!< RESERVED REGISTER1,                                  Address offset: 0x04 */
  __IO uint32_t GAHBCFG;          /*!< USB AHB Global Config Register,                      Address offset: 0x08 */
  __IO uint32_t GUSBCFG;          /*!< USB Global Config Register,                          Address offset: 0x0C */
  __IO uint32_t GRSTCTL;          /*!< USB Global Reset Control Register,                   Address offset: 0x10 */
  __IO uint32_t GINTSTS;          /*!< USB Global Interrupt Status Register,                Address offset: 0x14 */
  __IO uint32_t GINTMSK;          /*!< USB Global Interrupt Mask Register,                  Address offset: 0x18 */
  __IO uint32_t GRXSTSR;          /*!< USB Receive Status Debug Read Register,              Address offset: 0x1C */
  __IO uint32_t GRXSTSP;          /*!< USB Receive Status and Pop Register,                 Address offset: 0x20 */
  __IO uint32_t GRXFSIZ;          /*!< USB Receive FIFO size Register,                      Address offset: 0x24 */
  __IO uint32_t GNPTXFSIZ;        /*!< USB Non-Periodic Transmit FIFO size Register,        Address offset: 0x28 */
  __IO uint32_t RSV2[10];         /*!< Reserved                                                                  */
  __IO uint32_t GLPMCFG;          /*!< USB Low-Power-Mode config Register,                  Address offset: 0x54 */
  __IO uint32_t RSV3[490];        /*!< Reserved                                                                  */
  __IO uint32_t DCFG;             /*!< USB Device Config Register,                          Address offset: 0x800*/
  __IO uint32_t DCTL;             /*!< USB Device Control Register,                         Address offset: 0x804*/
  __IO uint32_t DSTS;             /*!< USB Device Status Register,                          Address offset: 0x808*/
  __IO uint32_t RSV31;            /*!< Reserved ,                                          Address offset: 0x80C*/
  __IO uint32_t DIEPMSK;          /*!< USB Device In Endpoint Interrupt Mask Register,      Address offset: 0x810*/
  __IO uint32_t DOEPMSK;          /*!< USB Device OUT Endpoint Interrupt Mask Registe,      Address offset: 0x814*/
  __IO uint32_t DAINT;            /*!< USB Device All Endpoint Interrupt Register,          Address offset: 0x818*/
  __IO uint32_t DAINTMSK;         /*!< USB Device All Endpoint Interrupt Mask Register,     Address offset: 0x81C*/
  __IO uint32_t RSV4[5];          /*!< Reserved                                                                  */
  __IO uint32_t DIEPEMPMSK;       /*!< USB Device IN endpoint FIFO empty interrupt Mask Register,Address offset: 0x834 */
  __IO uint32_t RSV5[50];         /*!< Reserved                                                                  */
  __IO uint32_t DIEPCTL0;         /*!< USB Device In Endpoint 0 Control Register,           Address offset: 0x900*/
  __IO uint32_t RSV6;             /*!< Reserved                                                                  */
  __IO uint32_t DIEPINT0;         /*!< USB Device In Endpoint 0 Interrupt Register,         Address offset: 0x908*/
  __IO uint32_t RSV7;             /*!< Reserved                                                                  */
  __IO uint32_t DIEPTSIZ0;        /*!< USB Device IN Endpoint 0 Transfer Size Register,     Address offset: 0x910*/
  __IO uint32_t RSV8;             /*!< Reserved                                                                  */
  __IO uint32_t DTXFSTS0;         /*!< USB Device In Endpoint 0 Tranmit FIFO Status Register,Address offset: 0x918 */
  __IO uint32_t RSV9;             /*!< Reserved                                                                  */
  __IO uint32_t DIEPCTL1;         /*!< USB Device In Endpoint 1 Control Register,           Address offset: 0x920*/
  __IO uint32_t RSV10;            /*!< Reserved                                                                  */
  __IO uint32_t DIEPINT1;         /*!< USB Device In Endpoint 1 Interrupt Register,         Address offset: 0x928*/
  __IO uint32_t RSV11;            /*!< Reserved                                                                  */
  __IO uint32_t DIEPTSIZ1;        /*!< USB Device IN Endpoint 1 Transfer Size Register,     Address offset: 0x930*/
  __IO uint32_t RSV12;            /*!< Reserved                                                                  */
  __IO uint32_t DTXFSTS1;         /*!< USB Device In Endpoint 1 Tranmit FIFO Status Register,Address offset: 0x938 */
  __IO uint32_t RSV13;            /*!< Reserved                                                                  */
  __IO uint32_t DIEPCTL2;         /*!< USB Device In Endpoint 2 Control Register,           Address offset: 0x940*/
  __IO uint32_t RSV14;            /*!< Reserved                                                                  */
  __IO uint32_t DIEPINT2;         /*!< USB Device In Endpoint 2 Interrupt Register,         Address offset: 0x948*/
  __IO uint32_t RSV15;            /*!< Reserved                                                                  */
  __IO uint32_t DIEPTSIZ2;        /*!< USB Device In Endpoint 2 Tranmit FIFO Status Register,Address offset: 0x950 */
  __IO uint32_t RSV16;            /*!< Reserved                                                                  */
  __IO uint32_t DTXFSTS2;         /*!< USB Device In Endpoint 2 Tranmit FIFO Status Register,Address offset: 0x958 */
  __IO uint32_t RSV17[105];       /*!< Reserved                                                                  */
  __IO uint32_t DOEPCTL0;         /*!< USB Device Out Endpoint 0 Control Register,          Address offset: 0xB00*/
  __IO uint32_t RSV18;            /*!< Reserved                                                                  */
  __IO uint32_t DOEPINT0;         /*!< USB Device Out Endpoint 0 Interrupt Register,        Address offset: 0xB08*/
  __IO uint32_t RSV19;            /*!< Reserved                                                                  */
  __IO uint32_t DOEPTSIZ0;        /*!< USB Device Out Endpoint 0 Transfer Size  Register,   Address offset: 0xB10*/
  __IO uint32_t RSV20;            /*!< Reserved                                                                  */
  __IO uint32_t RSV21;            /*!< Reserved                                                                  */
  __IO uint32_t RSV22;            /*!< Reserved                                                                  */
  __IO uint32_t DOEPCTL1;         /*!< USB Device Out Endpoint 1 Control Register,          Address offset: 0xB20*/
  __IO uint32_t RSV23;            /*!< Reserved                                                                  */
  __IO uint32_t DOEPINT1;         /*!< USB Device Out Endpoint 1 Interrupt Register,        Address offset: 0xB28*/
  __IO uint32_t RSV24;            /*!< Reserved                                                                  */
  __IO uint32_t DOEPTSIZ1;        /*!< USB Device Out Endpoint 1 Transfer Size  Register,   Address offset: 0xB30*/
  __IO uint32_t RSV25;            /*!< Reserved                                                                  */
  __IO uint32_t RSV26;            /*!< Reserved                                                                  */
  __IO uint32_t RSV27;            /*!< Reserved                                                                  */
  __IO uint32_t DOEPCTL2;         /*!< USB Device Out Endpoint 2 Control Register,          Address offset: 0xB40*/
  __IO uint32_t RSV28;            /*!< Reserved                                                                  */
  __IO uint32_t DOEPINT2;         /*!< USB Device Out Endpoint 2 Interrupt Register,        Address offset: 0xB48*/
  __IO uint32_t RSV29;            /*!< Reserved                                                                  */
  __IO uint32_t DOEPTSIZ2;        /*!< USB Device Out Endpoint 2 Transfer Size  Register,   Address offset: 0xB50*/
  __IO uint32_t RSV30[171];       /*!< Reserved                                                                  */
  __IO uint32_t PCGCCTL;          /*!< USB Power Control Global Control Register,           Address offset: 0xE00*/
} USB_Type;

typedef struct
{
  __IO uint32_t IRCR;             /*!< Infrared modulation Control Register */
} UART_COMMON_Type;

typedef struct
{
  __IO uint32_t CSR;              /*!< UART Control Status Register      */
  __IO uint32_t IER;              /*!< UART  Interrupt Enable Register   */
  __IO uint32_t ISR;              /*!< UART Interrupt Status Register    */
  __IO uint32_t TODR;             /*!< UART Time-Out and Delay Register  */
  __IO uint32_t RXBUF;            /*!< UART  Receive Buffer              */
  __IO uint32_t TXBUF;            /*!< UART Transmit Buffer              */
  __IO uint32_t BGR;              /*!< UART Baud rate Generator Register */
} UART_Type;


typedef struct
{
  __IO uint32_t CR;               /*!< VREF Control Register             */
  __IO uint32_t SR;               /*!< VREF Status Register              */
  __IO uint32_t IER;              /*!< VREF Interrupt Enable Register    */
  __IO uint32_t BUFCR;            /*!< VREF Interrupt Enable Register    */
} VREF_Type;

typedef struct
{
  __IO uint32_t CR;               /*!< WWDT Control Register,                               Address offset: 0x00 */
  __IO uint32_t CFGR;             /*!< WWDT Config Register,                                Address offset: 0x04 */
  __IO uint32_t CNT;              /*!< WWDT Counter Register,                               Address offset: 0x08 */
  __IO uint32_t IER;              /*!< WWDT Interrupt Enable Register,                      Address offset: 0x0C */
  __IO uint32_t ISR;              /*!< WWDT Interrupt Status Register,                      Address offset: 0x10 */
  __IO uint32_t PSC;              /*!< WWDT Prescaler Register,                             Address offset: 0x14 */
} WWDT_Type;



/** @addtogroup Peripheral_memory_map
  * @{
  */
#define FLASH_BASE            0x00000000UL /*!< FLASH(up to 1 MB) base address in the alias region      */
#define SRAM_BASE             0x20000000UL
#define PERIPH_BASE           0x40000000UL

/* ================================================================================ */
/* ================              Peripheral memory map             ================ */
/* ================================================================================ */

/*!< Peripheral memory map */
#define DBG_BASE              (PERIPH_BASE + 0x00000000UL)
#define PMU_BASE              (PERIPH_BASE + 0x00000100UL)
#define RCC_BASE              (PERIPH_BASE + 0x00000200UL)
#define DMA_BASE              (PERIPH_BASE + 0x00000400UL)
#define GPIOA_BASE            (PERIPH_BASE + 0x00000C00UL)
#define GPIOB_BASE            (PERIPH_BASE + 0x00000C40UL)
#define GPIOC_BASE            (PERIPH_BASE + 0x00000C80UL)
#define GPIOD_BASE            (PERIPH_BASE + 0x00000CC0UL)
#define GPIO_COMMON_BASE      (PERIPH_BASE + 0x00000D00UL)
#define FLASH_R_BASE          (PERIPH_BASE + 0x00001000UL)
#define U7816_BASE            (PERIPH_BASE + 0x00010000UL)
#define LPUART0_BASE          (PERIPH_BASE + 0x00010400UL)
#define SPI2_BASE             (PERIPH_BASE + 0x00010800UL)
#define LCD_BASE              (PERIPH_BASE + 0x00010C00UL)
#define RTC_BASE              (PERIPH_BASE + 0x00011000UL)
#define IWDT_BASE             (PERIPH_BASE + 0x00011400UL)
#define WWDT_BASE             (PERIPH_BASE + 0x00011800UL)
#define UART0_BASE            (PERIPH_BASE + 0x00011C00UL)
#define UART1_BASE            (PERIPH_BASE + 0x00012000UL)
#define I2C_BASE              (PERIPH_BASE + 0x00012400UL)
#define LPTIM32_BASE          (PERIPH_BASE + 0x00013400UL)
#define GPTIM0_BASE           (PERIPH_BASE + 0x00013800UL)
#define GPTIM1_BASE           (PERIPH_BASE + 0x00013C00UL)
#define CRC_BASE              (PERIPH_BASE + 0x00018000UL)
#define LPUART1_BASE          (PERIPH_BASE + 0x00018400UL)
#define SPI1_BASE             (PERIPH_BASE + 0x00018C00UL)
#define DIVAS_BASE            (PERIPH_BASE + 0x00019000UL)
#define UART_COMMON_BASE      (PERIPH_BASE + 0x00019C00UL)
#define UART4_BASE            (PERIPH_BASE + 0x0001A000UL)
#define UART5_BASE            (PERIPH_BASE + 0x0001A400UL)
#define RMU_BASE              (PERIPH_BASE + 0x0001A800UL)
#define VREF_BASE             (PERIPH_BASE + 0x0001A80CUL)
#define SVD_BASE              (PERIPH_BASE + 0x0001A824UL)
#define FDET_BASE             (PERIPH_BASE + 0x0001A838UL)
#define OPA1_BASE             (PERIPH_BASE + 0x0001A844UL)
#define OPA2_BASE             (PERIPH_BASE + 0x0001A854UL)
#define RNGCTL_BASE           (PERIPH_BASE + 0x0001A868UL)
#define COMP1_BASE            (PERIPH_BASE + 0x0001A870UL)
#define COMP2_BASE            (PERIPH_BASE + 0x0001A874UL)
#define COMP_COMMON_BASE      (PERIPH_BASE + 0x0001A878UL)
#define ADC_BASE              (PERIPH_BASE + 0x0001AC00UL)
#define AES_BASE              (PERIPH_BASE + 0x0001B800UL)
#define RNG_BASE              (PERIPH_BASE + 0x0001BC00UL)
#define ATIM_BASE             (PERIPH_BASE + 0x0001B000UL)
#define BSTIM32_BASE          (PERIPH_BASE + 0x0001B400UL)
#define USB_BASE              (PERIPH_BASE + 0x10000000UL)
/* ================================================================================ */
/* ================             Peripheral declaration             ================ */
/* ================================================================================ */

#define DBG                   ((DBG_Type *) DBG_BASE)
#define PMU                   ((PMU_Type *) PMU_BASE)
#define VREF                  ((VREF_Type *) VREF_BASE)
#define RCC                   ((RCC_Type *) RCC_BASE)
#define RMU                   ((RMU_Type *) RMU_BASE)
#define DMA                   ((DMA_Type *) DMA_BASE)
#define GPIOA                 ((GPIO_Type *) GPIOA_BASE)
#define GPIOB                 ((GPIO_Type *) GPIOB_BASE)
#define GPIOC                 ((GPIO_Type *) GPIOC_BASE)
#define GPIOD                 ((GPIO_Type *) GPIOD_BASE)
#define GPIO                  ((GPIO_COMMON_Type *) GPIO_COMMON_BASE)
#define FLASH                 ((FLASH_Type *) FLASH_R_BASE)
#define CRC                   ((CRC_Type *) CRC_BASE)
#define LPUART0               ((LPUART_Type *) LPUART0_BASE)
#define LPUART1               ((LPUART_Type *) LPUART1_BASE)
#define SPI1                  ((SPI_Type *) SPI1_BASE)
#define SPI2                  ((SPI_Type *) SPI2_BASE)
#define LCD                   ((LCD_Type *) LCD_BASE)
#define RTC                   ((RTC_Type *) RTC_BASE)
#define IWDT                  ((IWDT_Type *) IWDT_BASE)
#define WWDT                  ((WWDT_Type *) WWDT_BASE)
#define U7816                 ((U7816_Type *) U7816_BASE)
#define UART                  ((UART_COMMON_Type *) UART_COMMON_BASE)
#define UART0                 ((UART_Type *) UART0_BASE)
#define UART1                 ((UART_Type *) UART1_BASE)
#define UART4                 ((UART_Type *) UART4_BASE)
#define UART5                 ((UART_Type *) UART5_BASE)
#define I2C                   ((I2C_Type *) I2C_BASE)
#define FDET                  ((FDET_Type *) FDET_BASE)
#define SVD                   ((SVD_Type *) SVD_BASE)
#define OPA1                  ((OPA_Type *) OPA1_BASE)
#define OPA2                  ((OPA_Type *) OPA2_BASE)
#define LPTIM32               ((LPTIM32_Type *) LPTIM32_BASE)
#define AES                   ((AES_Type *) AES_BASE)
#define RNG                   ((RNG_Type *) RNG_BASE)
#define RNGCTL                ((RNGCTL_Type *) RNGCTL_BASE)
#define ATIM                  ((ATIM_Type *) ATIM_BASE)
#define GPTIM0                ((GPTIM_Type *) GPTIM0_BASE)
#define GPTIM1                ((GPTIM_Type *) GPTIM1_BASE)
#define BSTIM32               ((BSTIM32_Type *) BSTIM32_BASE)
#define ADC                   ((ADC_Type *) ADC_BASE)
#define COMP1                 ((COMP_Type *) COMP1_BASE)
#define COMP2                 ((COMP_Type *) COMP2_BASE)
#define COMP                  ((COMP_COMMON_Type*)COMP_COMMON_BASE)
#define DIV                   ((DIV_Type *) DIVAS_BASE)
#define USB                   ((USB_Type *) USB_BASE)
/* ================================================================================ */
/* ================             Peripheral include                 ================ */
/* ================================================================================ */

/** @} */ /* End of group Device_Peripheral_Registers */
/** @} */ /* End of group FM33LC0XX */
/** @} */ /* End of group Keil */

#ifdef __cplusplus
}
#endif

#endif  /* FM33LC0XX_H */
