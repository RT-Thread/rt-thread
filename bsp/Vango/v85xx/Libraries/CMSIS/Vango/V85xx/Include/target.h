/**
********************************************************************************
* @file    target.h
* @author  Application Team
* @version V4.4.0
* @date    2018-09-27
* @brief   Register define
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE 
* TIME. AS A RESULT, XXXXX SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
********************************************************************************
*/
#ifndef __TARGET_H
#define __TARGET_H

#ifdef __cplusplus
 extern "C" {
#endif 

#define __Vendor_SysTickConfig 0 /*!< target uses systick config */
#define __NVIC_PRIO_BITS  2      /*!< target uses 2 Bits for the Priority Levels */

typedef enum {ERROR = 0, SUCCESS = !ERROR, RESET = 0, SET = !RESET, DISABLE = 0, ENABLE = !DISABLE} TypeState, EventStatus, ControlStatus, FlagStatus,  ErrStatus;

 /*!< Interrupt Number Definition */
typedef enum
{
/******  Cortex-M0 Processor Exceptions Numbers **************************************************************/
  NMI_IRQn                    = -14,    /*!< 2 Non Maskable Interrupt                                        */
  HardFault_IRQn              = -13,    /*!< 3 Cortex-M0 Hard Fault Interrupt                                */
  SVC_IRQn                    = -5,     /*!< 11 Cortex-M0 SV Call Interrupt                                  */
  PendSV_IRQn                 = -2,     /*!< 14 Cortex-M0 Pend SV Interrupt                                  */
  SysTick_IRQn                = -1,     /*!< 15 Cortex-M0 System Tick Interrupt                              */

/******  target specific Interrupt Numbers ********************************************************************/
  PMU_IRQn                    = 0,      /*!< Power Management Unit Interrupt                                 */
  RTC_IRQn                    = 1,      /*!< RTC global Interrupt                                            */
  U32K0_IRQn                  = 2,      /*!< U32K0 global Interrupt                                          */
  U32K1_IRQn                  = 3,      /*!< U32K1 global Interrupt                                          */
  I2C_IRQn                    = 4,      /*!< I2C global Interrupt                                            */
  SPI1_IRQn                   = 5,      /*!< SPI1 global Interrupt                                           */
  UART0_IRQn                  = 6,      /*!< UART0 global Interrupt                                          */
  UART1_IRQn                  = 7,      /*!< UART1 global Interrupt                                          */
  UART2_IRQn                  = 8,      /*!< UART2 global Interrupt                                          */
  UART3_IRQn                  = 9,      /*!< UART3 global Interrupt                                          */
  UART4_IRQn                  = 10,     /*!< UART4 global Interrupt                                          */
  UART5_IRQn                  = 11,     /*!< UART5 global Interrupt                                          */
  ISO78160_IRQn               = 12,     /*!< ISO78160 global Interrupt                                       */
  ISO78161_IRQn               = 13,     /*!< ISO78161 global Interrupt                                       */
  TMR0_IRQn                   = 14,     /*!< Timer0 global Interrupt                                         */
  TMR1_IRQn                   = 15,     /*!< Timer1 global Interrupt                                         */
  TMR2_IRQn                   = 16,     /*!< Timer2 global Interrupt                                         */
  TMR3_IRQn                   = 17,     /*!< Timer3 global Interrupt                                         */
  PWM0_IRQn                   = 18,     /*!< PWM0 global Interrupt                                           */
  PWM1_IRQn                   = 19,     /*!< PWM1 global Interrupt                                           */
  PWM2_IRQn                   = 20,     /*!< PWM2 global Interrupt                                           */
  PWM3_IRQn                   = 21,     /*!< PWM3 global Interrupt                                           */
  DMA_IRQn                    = 22,     /*!< DMA global Interrupt                                            */
  FLASH_IRQn                  = 23,     /*!< FLASH global Interrupt                                          */
  ANA_IRQn                    = 24,     /*!< ANA global Interrupt                                            */
  SPI2_IRQn                   = 27,     /*!< SPI2 global Interrupt                                           */
} IRQn_Type;

#include "core_cm0.h"
#include "type_def.h"

/** @addtogroup Peripheral_registers_structures
  * @{
  */

/** 
  * @brief Power Management Unit Controller
  */

typedef struct
{
  __IO uint32_t DSLEEPEN;       /*!< PMU deep sleep enable register,                          Address offset: 0x00 */
  __IO uint32_t DSLEEPPASS;     /*!< PMU deep sleep password register,                        Address offset: 0x04 */
  __IO uint32_t CONTROL;        /*!< PMU control register,                                    Address offset: 0x08 */
  __IO uint32_t STS;            /*!< PMU Status register,                                     Address offset: 0x0C */
  __IO uint32_t IOAOEN;         /*!< IOA output enable register,                              Address offset: 0x10 */
  __IO uint32_t IOAIE;          /*!< IOA input enable register,                               Address offset: 0x14 */
  __IO uint32_t IOADAT;         /*!< IOA data register,                                       Address offset: 0x18 */
  __IO uint32_t IOAATT;         /*!< IOA attribute register,                                  Address offset: 0x1C */
  __IO uint32_t IOAWKUEN;       /*!< IOA input status register,                               Address offset: 0x20 */
  __IO uint32_t IOASTS;         /*!< IOA input status register,                               Address offset: 0x24 */
  __IO uint32_t IOAINTSTS;      /*!< IOA input status register,                               Address offset: 0x28 */
       uint32_t RESERVED1;      /*!< Reserved,                                                                0x2C */
       uint32_t RESERVED2;      /*!< Reserved,                                                                0x30 */
       uint32_t RESERVED3;      /*!< Reserved,                                                                0x34 */
  __IO uint32_t IOASEL;         /*!< IOA special function select register,                    Address offset: 0x38 */
  __IO uint32_t VERSIONID_;     /*!< Version ID of chip,                                      Address offset: 0x3C */
  __IO uint32_t WDTPASS;        /*!< Watch dog timing unlock register,                        Address offset: 0x40 */
  __IO uint32_t WDTEN;          /*!< Watch dog timer enable register,                         Address offset: 0x44 */
  __IO uint32_t WDTCLR;         /*!< Watch dog timer clear register,                          Address offset: 0x48 */
//  __IO uint32_t WDTSTS;         /*!< Watch dog timer status register,                         Address offset: 0x4C */
       uint32_t RESERVED4;      /*!< Reserved,                                                                0x4C  */
  __IO uint32_t IOANODEG;       /*!< IOA de-glitch circuit control,                           Address offset: 0x50 */
}PMU_TypeDef;

/** 
  * @brief Power Management Unit Retention RAM
  */

typedef struct
{
  __IO uint32_t RAM[64];        /*!< PMU 32 bits Retention RAM 0-63,                      Address offset: 0x00-0xFC */
}PMU_RETRAM_TypeDef;

/** 
  * @brief Analog control register  
  */

typedef struct
{
  __IO uint32_t REG0;       /*!< Analog control register 0,                                  Address offset:0x00 */
  __IO uint32_t REG1;       /*!< Analog control register 1,                                  Address offset:0x04 */
  __IO uint32_t REG2;       /*!< Analog control register 2,                                  Address offset:0x08 */
  __IO uint32_t REG3;       /*!< Analog control register 3,                                  Address offset:0x0C */
  __IO uint32_t REG4;       /*!< Analog control register 4,                                  Address offset:0x10 */
  __IO uint32_t REG5;       /*!< Analog control register 5,                                  Address offset:0x14 */
  __IO uint32_t REG6;       /*!< Analog control register 6,                                  Address offset:0x18 */
  __IO uint32_t REG7;       /*!< Analog control register 7,                                  Address offset:0x1C */
  __IO uint32_t REG8;       /*!< Analog control register 8,                                  Address offset:0x20 */
  __IO uint32_t REG9;       /*!< Analog control register 9,                                  Address offset:0x24 */
  __IO uint32_t REGA;       /*!< Analog control register 10,                                 Address offset:0x28 */
  __IO uint32_t REGB;       /*!< Analog control register 11,                                 Address offset:0x2C */
  __IO uint32_t REGC;       /*!< Analog control register 12,                                 Address offset:0x30 */
  __IO uint32_t REGD;       /*!< Analog control register 13,                                 Address offset:0x34 */
  __IO uint32_t REGE;       /*!< Analog control register 14,                                 Address offset:0x38 */
  __IO uint32_t REGF;       /*!< Analog control register 15,                                 Address offset:0x3C */
//  __IO uint32_t REG10;      /*!< Analog control register 16,                                 Address offset:0x40 */
//  __IO uint32_t REG11;      /*!< Analog control register 17,                                 Address offset:0x44 */
//  __IO uint32_t REG12;      /*!< Analog control register 18,                                 Address offset:0x48 */
       uint32_t RESERVED1;  /*!< Reserved,                                                                  0x40 */
       uint32_t RESERVED2;  /*!< Reserved,                                                                  0x44 */
       uint32_t RESERVED3;  /*!< Reserved,                                                                  0x48 */
       uint32_t RESERVED4;  /*!< Reserved,                                                                  0x4C */
  __IO uint32_t CTRL;       /*!< Analog misc. control register,                              Address offset:0x50 */
  __IO uint32_t COMPOUT;    /*!< Comparator result register,                                 Address offset:0x54 */
  //__IO uint32_t VERSION;  /*!< Analog IP version register,                                 Address offset:0x58 */
  //__IO uint32_t ADCSTATE; /*!< ADC State register,                                         Address offset:0x5C */
       uint32_t RESERVED5;  /*!< Reserved,                                                                       */
       uint32_t RESERVED6;  /*!< Reserved,                                                                       */
  __IO uint32_t INTSTS;     /*!< Analog interrupt status register,                           Address offset:0x60 */
  __IO uint32_t INTEN;      /*!< Analog interrupt enable register,                           Address offset:0x64 */
  __IO uint32_t ADCCTRL;    /*!< ADC control register,                                       Address offset:0x68 */
       uint32_t RESERVED7;  /*!< Reserved,                                                                  0x6C */
  __IO uint32_t ADCDATA0;   /*!< ADC channel 0 data register,                                Address offset:0x70 */
  __IO uint32_t ADCDATA1;   /*!< ADC channel 1 data register,                                Address offset:0x74 */
  __IO uint32_t ADCDATA2;   /*!< ADC channel 2 data register,                                Address offset:0x78 */
  __IO uint32_t ADCDATA3;   /*!< ADC channel 3 data register,                                Address offset:0x7C */
  __IO uint32_t ADCDATA4;   /*!< ADC channel 4 data register,                                Address offset:0x80 */
  __IO uint32_t ADCDATA5;   /*!< ADC channel 5 data register,                                Address offset:0x84 */
  __IO uint32_t ADCDATA6;   /*!< ADC channel 6 data register,                                Address offset:0x88 */
  __IO uint32_t ADCDATA7;   /*!< ADC channel 7 data register,                                Address offset:0x8C */
  __IO uint32_t ADCDATA8;   /*!< ADC channel 8 data register,                                Address offset:0x90 */
  __IO uint32_t ADCDATA9;   /*!< ADC channel 9 data register,                                Address offset:0x94 */
  __IO uint32_t ADCDATAA;   /*!< ADC channel 10 data register,                               Address offset:0x98 */
  __IO uint32_t ADCDATAB;   /*!< ADC channel 11 data register,                               Address offset:0x9C */
//  __IO uint32_t ADCDATAC;   /*!< ADC channel 12 data register,                               Address offset:0xA0 */
//  __IO uint32_t ADCDATAD;   /*!< ADC channel 13 data register,                               Address offset:0xA4 */
//  __IO uint32_t ADCDATAE;   /*!< ADC channel 14 data register,                               Address offset:0xA8 */
//  __IO uint32_t ADCDATAF;   /*!< ADC channel 15 data register,                               Address offset:0xAC */
       uint32_t RESERVED8;  /*!< Reserved,                                                                  0xA0 */
       uint32_t RESERVED9;  /*!< Reserved,                                                                  0xA4 */
       uint32_t RESERVED10; /*!< Reserved,                                                                  0xA8 */
       uint32_t RESERVED11; /*!< Reserved,                                                                  0xAC */  
  __IO uint32_t CMPCNT1;    /*!< Comparator 1 counter,                                       Address offset:0xB0 */
  __IO uint32_t CMPCNT2;    /*!< Comparator 2 counter,                                       Address offset:0xB4 */
  __IO uint32_t MISC_A;     /*!< MISC,                                                       Address offset:0xB8 */
} ANA_TypeDef;

/** 
  * @brief Real-Time Clock
  */

typedef struct
{                           
  __IO uint32_t SEC;          /*!< RTC second register,                                        Address offset: 0x00 */
  __IO uint32_t MIN;          /*!< RTC minute register,                                        Address offset: 0x04 */
  __IO uint32_t HOUR;         /*!< RTC hour register,                                          Address offset: 0x08 */
  __IO uint32_t DAY;          /*!< RTC day register,                                           Address offset: 0x0C */
  __IO uint32_t WEEK;         /*!< RTC week-day register,                                      Address offset: 0x10 */
  __IO uint32_t MON;          /*!< RTC month register,                                         Address offset: 0x14 */
  __IO uint32_t YEAR;         /*!< RTC year register,                                          Address offset: 0x18 */
       uint32_t RESERVED1;    /*!< Reserved,                                                   Address offset: 0x1C */
  __IO uint32_t WKUSEC;       /*!< RTC wake-up second register,                                Address offset: 0x20 */
  __IO uint32_t WKUMIN;       /*!< RTC wake-up minute register,                                Address offset: 0x24 */
  __IO uint32_t WKUHOUR;      /*!< RTC wake-up hour register,                                  Address offset: 0x28 */
  __IO uint32_t WKUCNT;       /*!< RTC wake-up counter register,                               Address offset: 0x2C */
  __IO uint32_t CAL;          /*!< RTC calibration register,                                   Address offset: 0x30 */
  __IO uint32_t DIV;          /*!< RTC PLL divider register,                                   Address offset: 0x34 */
  __IO uint32_t CTL;          /*!< RTC PLL divider control register,                           Address offset: 0x38 */
       uint32_t RESERVED2;
       uint32_t RESERVED3;
  //__IO uint32_t ITV;        /*!< RTC wake-up interval control,                               Address offset: 0x3C */
  //__IO uint32_t SITV;       /*!< RTC wake-up second interval control,                        Address offset: 0x40 */
  __IO uint32_t PWD;          /*!< RTC password control register,                              Address offset: 0x44 */
  __IO uint32_t CE;           /*!< RTC write enable control register,                          Address offset: 0x48 */
  __IO uint32_t LOAD;         /*!< RTC read enable control register,                           Address offset: 0x4C */
  __IO uint32_t INTSTS;       /*!< RTC interrupt status control register,                      Address offset: 0x50 */
  __IO uint32_t INTEN;        /*!< RTC interrupt enable control register,                      Address offset: 0x54 */
  __IO uint32_t PSCA;         /*!< RTC clock pre-scaler control register,                      Address offset: 0x58 */
       uint32_t RESERVED4[9]; /*!< Reserved,                                              Address offset: 0x5C-0x7C */
  __IO uint32_t ACCTRL;       /*!< RTC auto-calibration control register,                      Address offset: 0x80 */
  __IO uint32_t ACTI;         /*!< RTC auto-calibration center temperature control register,   Address offset: 0x84 */
  __IO uint32_t ACF200;       /*!< RTC auto-calibration 200*frequency control register,        Address offset: 0x88 */
  __IO uint32_t ACADCW;       /*!< RTC auto-calibration manual ADC value control register,     Address offset: 0x8C */
  __IO uint32_t ACP0;         /*!< RTC auto-calibration parameter 0 control register,          Address offset: 0x90 */
  __IO uint32_t ACP1;         /*!< RTC auto-calibration parameter 1 control register,          Address offset: 0x94 */
  __IO uint32_t ACP2;         /*!< RTC auto-calibration parameter 2 control register,          Address offset: 0x98 */
  __IO uint32_t ACP3;         /*!< RTC auto-calibration parameter 3 control register,          Address offset: 0x9C */
  __IO uint32_t ACP4;         /*!< RTC auto-calibration parameter 4 control register,          Address offset: 0xA0 */
  __IO uint32_t ACP5;         /*!< RTC auto-calibration parameter 5 control register,          Address offset: 0xA4 */
  __IO uint32_t ACP6;         /*!< RTC auto-calibration parameter 6 control register,          Address offset: 0xA8 */
  __IO uint32_t ACP7;         /*!< RTC auto-calibration parameter 7 control register,          Address offset: 0xAC */
  __IO uint32_t ACK1;         /*!< RTC auto-calibration parameter k1 control register,         Address offset: 0xB0 */
  __IO uint32_t ACK2;         /*!< RTC auto-calibration parameter k2 control register,         Address offset: 0xB4 */
  __IO uint32_t ACK3;         /*!< RTC auto-calibration parameter k3 control register,         Address offset: 0xB8 */
  __IO uint32_t ACK4;         /*!< RTC auto-calibration parameter k4 control register,         Address offset: 0xBC */
  __IO uint32_t ACK5;         /*!< RTC auto-calibration parameter k5 control register,         Address offset: 0xC0 */
  __IO uint32_t ACTEMP;       /*!< RTC auto-calibration calculated temperature register,       Address offset: 0xC4 */
  __IO uint32_t ACPPM;        /*!< RTC auto-calibration calculated PPM register,               Address offset: 0xC8 */
  __IO uint32_t WKUCNTR;      /*!< RTC current WKUCNT counter value read-out register.,        Address offset: 0xCC */
  __IO uint32_t ACKTEMP;      /*!< RTC auto-calibration k temperature section control register,Address offset: 0xD0 */
  //uint32_t RESERVED37[128+15];/*!< Reserved,                                        Address offset: 0xD4-0x3FC */
  //__IO uint32_t RTC_ACOP0_63[64];  /*!< RTC auto-calibration OP0-OP63 register (only for FPGA),  Address offset: 0x400-0x4FC */
} RTC_TypeDef;

/** 
  * @brief FLASH
  */
typedef struct
{
  __IO uint32_t STS;        /*!< ,                                                   Address offset: 0x00 */
  __IO uint32_t NVRPASS;    /*!< FLASH NVR sector password register,                 Address offset: 0x04 */
  __IO uint32_t BDPASS;     /*!< FLASH Back door register,                           Address offset: 0x08 */
  __IO uint32_t KEY;        /*!< FLASH key register,                                 Address offset: 0x0C */
  __IO uint32_t INT;        /*!< FLASH Checksum interrupt status,                    Address offset: 0x10 */
  __IO uint32_t CSSADDR;    /*!< FLASH Checksum start address,                       Address offset: 0x14 */
  __IO uint32_t CSEADDR;    /*!< FLASH Checksum end address,                         Address offset: 0x18 */
  __IO uint32_t CSVALUE;    /*!< FLASH Checksum value register,                      Address offset: 0x1C */
  __IO uint32_t CSCVALUE;   /*!< FLASH Checksum compare value register,              Address offset: 0x20 */
  __IO uint32_t PASS;       /*!< FLASH password register,                            Address offset: 0x24 */
  __IO uint32_t CTRL;       /*!< FLASH control register,                             Address offset: 0x28 */
  __IO uint32_t PGADDR;     /*!< FLASH program address register,                     Address offset: 0x2C */
  __IO uint32_t PGDATA;     /*!< FLASH program word data register,                   Address offset: 0x30 */
  __IO uint32_t CONF;       /*!< FLASH configuration read/write register,            Address offset: 0x34 */
  __IO uint32_t SERASE;     /*!< FLASH sector erase control register,                Address offset: 0x38 */
  __IO uint32_t CERASE;     /*!< FLASH chip erase control register,                  Address offset: 0x3C */
  __IO uint32_t DSTB;       /*!< FLASH deep standby control register,                Address offset: 0x40 */
} FLASH_TypeDef;


/** 
  * @brief General Purpose IO (GPIOB~GPIOF)
  */

typedef struct
{
  __IO uint32_t OEN;       /*!< IOx output enable register,                               Address offset: 0x00 */
  __IO uint32_t IE;        /*!< IOx input enable register,                                Address offset: 0x04 */
  __IO uint32_t DAT;       /*!< IOx data register,                                        Address offset: 0x08 */
  __IO uint32_t ATT;       /*!< IOx attribute register,                                   Address offset: 0x0C */
  __IO uint32_t STS;       /*!< IOx input status register,                                Address offset: 0x10 */
}GPIO_TypeDef;

/** 
  * @brief General Purpose IO (GPIOA)
  */
typedef struct
{
    __IO uint32_t OEN;
    __IO uint32_t IE;
    __IO uint32_t DAT;
    __IO uint32_t ATT;
    __IO uint32_t WKUEN;
    __IO uint32_t STS;
    __IO uint32_t INT;
         uint32_t RESERVED1;
         uint32_t RESERVED2;
         uint32_t RESERVED3;
    __IO uint32_t SEL;
         uint32_t RESERVED[5];
    __IO uint32_t IOANODEG; 
} GPIOA_TypeDef;

/** 
  * @brief General Purpose IO special function
  */

typedef struct
{
  __IO uint32_t SELB;         /*!< IOB special function select register,                     Address offset: 0x00 */
       uint32_t RESERVED1;    /*!< Reserved,                                                                 0x04 */
       uint32_t RESERVED2;    /*!< Reserved,                                                                 0x08 */
  __IO uint32_t SELE;         /*!< IOE special function select register,                     Address offset: 0x0C */
       uint32_t RESERVED3;    /*!< Reserved,                                                                 0x10 */
       uint32_t RESERVED4;    /*!< Reserved,                                                                 0x14 */
       uint32_t RESERVED5;    /*!< Reserved,                                                                 0x18 */
       uint32_t RESERVED6;    /*!< Reserved,                                                                 0x1C */
  __IO uint32_t _MISC;        /*!< IO misc control register,                                Address offset: 0x20 */
}GPIO_AF_TypeDef;

/** 
  * @brief DMA Controller
  */

typedef struct
{
  __IO uint32_t IE;           /*!< DMA interrupt enable register,                            Address offset:0x00 */
  __IO uint32_t STS;          /*!< DMA status register,                                      Address offset:0x04 */
       uint32_t RESERVED1;    /*!< Reserved,                                                                0x08 */
       uint32_t RESERVED2;    /*!< Reserved,                                                                0x0C */
  __IO uint32_t C0CTL;        /*!< DMA channel 0 control register,                           Address offset:0x10 */
  __IO uint32_t C0SRC;        /*!< DMA channel 0 source register,                            Address offset:0x14 */
  __IO uint32_t C0DST;        /*!< DMA channel 0 destination register,                       Address offset:0x18 */
  __IO uint32_t C0LEN;        /*!< DMA channel 0 transfer length register,                   Address offset:0x1C */
  __IO uint32_t C1CTL;        /*!< DMA channel 1 control register,                           Address offset:0x20 */
  __IO uint32_t C1SRC;        /*!< DMA channel 1 source register,                            Address offset:0x24 */
  __IO uint32_t C1DST;        /*!< DMA channel 1 destination register,                       Address offset:0x28 */
  __IO uint32_t C1LEN;        /*!< DMA channel 1 transfer length register,                   Address offset:0x2C */
  __IO uint32_t C2CTL;        /*!< DMA channel 2 control register,                           Address offset:0x30 */
  __IO uint32_t C2SRC;        /*!< DMA channel 2 source register,                            Address offset:0x34 */
  __IO uint32_t C2DST;        /*!< DMA channel 2 destination register,                       Address offset:0x38 */
  __IO uint32_t C2LEN;        /*!< DMA channel 2 transfer length register,                   Address offset:0x3C */
  __IO uint32_t C3CTL;        /*!< DMA channel 3 control register,                           Address offset:0x40 */
  __IO uint32_t C3SRC;        /*!< DMA channel 3 source register,                            Address offset:0x44 */
  __IO uint32_t C3DST;        /*!< DMA channel 3 destination register,                       Address offset:0x48 */
  __IO uint32_t C3LEN;        /*!< DMA channel 3 transfer length register,                   Address offset:0x4C */
  __IO uint32_t AESCTL;       /*!< DMA AES control register,                                 Address offset:0x50 */
       uint32_t RESERVED3[3]; /*!< Reserved,                                                           0x54-0x5C */
  __IO uint32_t AESKEY0;      /*!< DMA AES key 0 register,                                   Address offset:0x60 */
  __IO uint32_t AESKEY1;      /*!< DMA AES key 1 register,                                   Address offset:0x64 */
  __IO uint32_t AESKEY2;      /*!< DMA AES key 2 register,                                   Address offset:0x68 */
  __IO uint32_t AESKEY3;      /*!< DMA AES key 3 register,                                   Address offset:0x6C */
  __IO uint32_t AESKEY4;      /*!< DMA AES key 4 register,                                   Address offset:0x70 */
  __IO uint32_t AESKEY5;      /*!< DMA AES key 5 register,                                   Address offset:0x74 */
  __IO uint32_t AESKEY6;      /*!< DMA AES key 6 register,                                   Address offset:0x78 */
  __IO uint32_t AESKEY7;      /*!< DMA AES key 7 register,                                   Address offset:0x7C */
} DMA_TypeDef;

/** 
  * @brief Universal Synchronous Asynchronous Receiver Transmitter
  */
  
typedef struct
{
  __IO uint32_t DATA;      /*!< UARTx data register,                                   Address offset: 0x00 */ 
  __IO uint32_t STATE;     /*!< UARTx status register,                                 Address offset: 0x04 */ 
  __IO uint32_t CTRL;      /*!< UARTx control register,                                Address offset: 0x08 */
  __IO uint32_t INTSTS;    /*!< UARTx interrupt status register,                       Address offset: 0x0C */
  __IO uint32_t BAUDDIV;   /*!< UARTx baud rate divide register,                       Address offset: 0x10 */
  __IO uint32_t CTRL2;     /*!< UARTx control register 2,                              Address offset: 0x14 */ 
} UART_TypeDef;

/** 
  * @brief UART 32K Controller
  */
typedef struct
{
  __IO uint32_t CTRL0;     /*!< UART 32K x control register 0,                       Address offset: 0x00 */
  __IO uint32_t CTRL1;     /*!< UART 32K x control register 1,                       Address offset: 0x04 */
  __IO uint32_t PHASE;     /*!< UART 32K x baud rate control register,               Address offset: 0x08 */
  __IO uint32_t DATA;      /*!< UART 32K x receive data buffer,                      Address offset: 0x0C */
  __IO uint32_t STS;       /*!< UART 32K x interrupt status register,                Address offset: 0x10 */
} U32K_TypeDef;

/** 
  * @brief ISO7816 Controller
  */
typedef struct
{
       uint32_t RESERVED1;    /*!< Reserved,                                                            0x00 */
  __IO uint32_t BAUDDIVL;     /*!< ISO7816 x  baud-rate low byte register,              Address offset: 0x04 */
  __IO uint32_t BAUDDIVH;     /*!< ISO7816 x  baud-rate high byte register,             Address offset: 0x08 */
  __IO uint32_t DATA;         /*!< ISO7816 x  data register,                            Address offset: 0x0C */
  __IO uint32_t INFO;         /*!< ISO7816 x  information register,                     Address offset: 0x10 */
  __IO uint32_t CFG;          /*!< ISO7816 x  control register,                         Address offset: 0x14 */
  __IO uint32_t CLK;          /*!< ISO7816 x  clock divider register,                   Address offset: 0x1C */
} ISO7816_TypeDef;

/** 
  * @brief Timer Controller
  */
typedef struct
{
  __IO uint32_t CTRL;     /*!< Timer x’s control register,                        Address offset: 0x00 */
  __IO uint32_t VALUE;    /*!< Timer x’s current count register,                  Address offset: 0x04 */
  __IO uint32_t RELOAD;   /*!< Timer x’s reload register,                         Address offset: 0x08 */
  __IO uint32_t INT;      /*!< Timer x’s interrupt status register,               Address offset: 0x0C */
} TMR_TypeDef;

/** 
  * @brief PWM Controller
  */
typedef struct
{
  __IO uint32_t CTL;    /*!< PWM Timer x’s control register,                        Address offset: 0x00 */
  __IO uint32_t TAR;    /*!< PWM Timer x’s current count register,                  Address offset: 0x04 */
  __IO uint32_t CCTL0;  /*!< PWM Timer x’s compare/capture control register 0,      Address offset: 0x08 */
  __IO uint32_t CCTL1;  /*!< PWM Timer x’s compare/capture control register 1,      Address offset: 0x0C */
  __IO uint32_t CCTL2;  /*!< PWM Timer x’s compare/capture control register 2,      Address offset: 0x10 */
  __IO uint32_t CCR0;   /*!< PWM Timer x’s compare/capture data register 0,         Address offset: 0x14 */
  __IO uint32_t CCR1;   /*!< PWM Timer x’s compare/capture data register 1,         Address offset: 0x18 */
  __IO uint32_t CCR2;   /*!< PWM Timer x’s compare/capture data register 2,         Address offset: 0x1C */
} PWM_TypeDef;

/** 
  * @brief PWMx selection register
  */
typedef struct
{
  __IO uint32_t OSEL;      /*!< PWM output selection register,                         Address offset: 0x00 */
//  __IO uint32_t ISEL01;    /*!< PWM0 and PWM1’s input selection register,              Address offset: 0x04 */
//  __IO uint32_t ISEL23;    /*!< PWM2 and PWM3’s input selection register,              Address offset: 0x08 */
  uint32_t RESERVED0;    /*!< RESERVED0,              Address offset: 0x04 */
  uint32_t RESERVED1;    /*!< RESERVED1,              Address offset: 0x08 */
} PWM_MUX_TypeDef;

/** 
  * @brief LCD
  */

typedef struct
{
  __IO uint32_t FB[40];         /*!< LCD Frame buffer 0~39 register,                      Address offset: 0x00-0x9C */
       uint32_t RESERVED1[24];  /*!< Reserved,                                                            0xA0-0xFC */ 
  __IO uint32_t CTRL;           /*!< LCD control register,                                    Address offset: 0x100 */
  __IO uint32_t CTRL2;          /*!< LCD control register 2,                                  Address offset: 0x104 */
  __IO uint32_t SEGCTRL0;       /*!< LCD segment enable control register 0,                   Address offset: 0x108 */
  __IO uint32_t SEGCTRL1;       /*!< LCD segment enable control register 1,                   Address offset: 0x10C */
  __IO uint32_t SEGCTRL2;       /*!< LCD segment enable control register 2,                   Address offset: 0x110 */
}LCD_TypeDef;

/** 
  * @brief Serial Peripheral Interface
  */
  
typedef struct
{
  __IO uint32_t CTRL;     /*!< SPI x Control Register,                                  Address offset: 0x00 */
  __IO uint32_t TXSTS;    /*!< SPI x Transmit Status Register,                          Address offset: 0x04 */
  __IO uint32_t TXDAT;    /*!< SPI x Transmit FIFO register,                            Address offset: 0x08 */
  __IO uint32_t RXSTS;    /*!< SPI x Receive Status Register,                           Address offset: 0x0C */
  __IO uint32_t RXDAT;    /*!< SPI x Receive FIFO Register,                             Address offset: 0x10 */
  __IO uint32_t MISC_;    /*!< SPI x Misc Control Register,                            Address offset: 0x14 */
} SPI_TypeDef;

/** 
  * @brief Inter-integrated Circuit Interface
  */

typedef struct
{
  __IO uint32_t DATA;        /*!< I2C data register,                                          Address offset: 0x00 */
  __IO uint32_t ADDR;        /*!< I2C address register,                                       Address offset: 0x04 */
  __IO uint32_t CTRL;        /*!< I2C control/status register,                                Address offset: 0x08 */
  __IO uint32_t STS;         /*!< I2C status register,                                        Address offset: 0x0C */
       uint32_t RESERVED1;   /*!< Reserved,                                                                   0x10 */
       uint32_t RESERVED2;   /*!< Reserved,                                                                   0x14 */
  __IO uint32_t CTRL2;       /*!< I2C interrupt enable register,                              Address offset: 0x18 */
}I2C_TypeDef;

/** 
  * @brief MISC Controller
  */
typedef struct
{
  __IO uint32_t SRAMINT;     /*!< SRAM Parity Error Interrupt,                         Address offset: 0x00 */
  __IO uint32_t SRAMINIT;    /*!< SRAM initialize register,                            Address offset: 0x04 */
  __IO uint32_t PARERR;      /*!< SRAM Parity Error address register,                  Address offset: 0x08 */
  __IO uint32_t IREN;        /*!< IR enable control register,                          Address offset: 0x0C */
  __IO uint32_t DUTYL;       /*!< IR Duty low pulse control register,                  Address offset: 0x10 */
  __IO uint32_t DUTYH;       /*!< IR Duty high pulse control register,                 Address offset: 0x14 */
  __IO uint32_t IRQLAT;      /*!< Cortex M0 IRQ latency control register,              Address offset: 0x18 */
       uint32_t RESERVED1;   /*!< Reserved,                                                            0x1C */
  __IO uint32_t HIADDR;      /*!< AHB invalid access address,                          Address offset: 0x20 */
  __IO uint32_t PIADDR;      /*!< APB invalid access address,                          Address offset: 0x24 */
} MISC_TypeDef;

/** 
  * @brief MISC2 Controller 
  */
typedef struct
{
  __IO uint32_t FLASHWC;     /*!< Flash wait cycle register,                           Address offset: 0x00 */
  __IO uint32_t CLKSEL;      /*!< Clock selection register,                            Address offset: 0x04 */
  __IO uint32_t CLKDIVH;     /*!< AHB clock divider control register,                  Address offset: 0x08 */
  __IO uint32_t CLKDIVP;     /*!< APB clock divider control register,                  Address offset: 0x0C */
  __IO uint32_t HCLKEN;      /*!< AHB clock enanle control register,                   Address offset: 0x10 */
  __IO uint32_t PCLKEN;      /*!< APB clock enanle control register,                   Address offset: 0x14 */
} MISC2_TypeDef;

/** 
  * @brief CRYPT Controller 
  */
typedef struct
{
  __IO uint32_t CTRL;        /*!< CRYPT control register,                              Address offset: 0x00 */
  __IO uint32_t PTRA;        /*!< CRYPT pointer A,                                     Address offset: 0x04 */
  __IO uint32_t PTRB;        /*!< CRYPT pointer B,                                     Address offset: 0x08 */
  __IO uint32_t PTRO;        /*!< CRYPT pointer O,                                     Address offset: 0x0C */
  __IO uint32_t CARRY;       /*!< CRYPT carry/borrow bit register,                     Address offset: 0x10 */
} CRYPT_TypeDef;

/** 
  * @}
  */
  
/** @addtogroup Peripheral_memory_map
  * @{
  */

#define FLASH_BASE                   ((uint32_t)0x00000000U)              /*!< FLASH base address in the alias region */
#define FLASH_BANK1_END              ((uint32_t)0x0003FFFFU)              /*!< FLASH END address of bank1 */
#define SRAM_BASE                    ((uint32_t)0x20000000U)              /*!< SRAM base address in the alias region */
#define PERIPH_BASE                  ((uint32_t)0x40000000U)              /*!< Peripheral base address in the alias region */

/*!< Peripheral memory map */
#define AHBPERIPH_BASE               (PERIPH_BASE + 0x00000000U)
#define APBPERIPH_BASE               (PERIPH_BASE + 0x00010000U)

/*!< FLASH */
#define FLASHSFR_BASE                (FLASH_BASE + 0x000FFFBC)

/*!< AHB peripherals */
#define GPIO_BASE                    (AHBPERIPH_BASE + 0x00000000)
#define GPIOB_BASE                   (AHBPERIPH_BASE + 0x00000020)
#define GPIOC_BASE                   (AHBPERIPH_BASE + 0x00000040)
#define GPIOD_BASE                   (AHBPERIPH_BASE + 0x00000060)
#define GPIOE_BASE                   (AHBPERIPH_BASE + 0x00000080)
#define GPIOF_BASE                   (AHBPERIPH_BASE + 0x000000A0)
#define GPIOAF_BASE                  (AHBPERIPH_BASE + 0x000000C0)
#define LCD_BASE                     (AHBPERIPH_BASE + 0x00002000)
#define CRYPT_BASE                   (AHBPERIPH_BASE + 0x00006000)

/*!< APB peripherals */
#define DMA_BASE                     (APBPERIPH_BASE + 0x00000000)
#define I2C_BASE                     (APBPERIPH_BASE + 0x00000800)
#define SPI1_BASE                    (APBPERIPH_BASE + 0x00001000)
#define UART0_BASE                   (APBPERIPH_BASE + 0x00001800)
#define UART1_BASE                   (APBPERIPH_BASE + 0x00001820)
#define UART2_BASE                   (APBPERIPH_BASE + 0x00001840)
#define UART3_BASE                   (APBPERIPH_BASE + 0x00001860)
#define UART4_BASE                   (APBPERIPH_BASE + 0x00001880)
#define UART5_BASE                   (APBPERIPH_BASE + 0x000018A0)
#define ISO78160_BASE                (APBPERIPH_BASE + 0x00002000)
#define ISO78161_BASE                (APBPERIPH_BASE + 0x00002040)
#define TMR0_BASE                    (APBPERIPH_BASE + 0x00002800)
#define TMR1_BASE                    (APBPERIPH_BASE + 0x00002820)
#define TMR2_BASE                    (APBPERIPH_BASE + 0x00002840)
#define TMR3_BASE                    (APBPERIPH_BASE + 0x00002860)
#define PWM0_BASE                    (APBPERIPH_BASE + 0x00002900)
#define PWM1_BASE                    (APBPERIPH_BASE + 0x00002920)
#define PWM2_BASE                    (APBPERIPH_BASE + 0x00002940)
#define PWM3_BASE                    (APBPERIPH_BASE + 0x00002960)
#define PWMMUX_BASE                  (APBPERIPH_BASE + 0x000029F0)
#define MISC_BASE                    (APBPERIPH_BASE + 0x00003000)
#define MISC2_BASE                   (APBPERIPH_BASE + 0x00003E00)
#define PMU_BASE                     (APBPERIPH_BASE + 0x00004000)
#define GPIOA_BASE                   (APBPERIPH_BASE + 0x00004010)
#define PMU_RETRAM_BASE              (APBPERIPH_BASE + 0x00004400)
#define U32K0_BASE                   (APBPERIPH_BASE + 0x00004100)
#define U32K1_BASE                   (APBPERIPH_BASE + 0x00004180)
#define ANA_BASE                     (APBPERIPH_BASE + 0x00004200)
#define RETRAM_BASE                  (APBPERIPH_BASE + 0x00004400)
#define RTC_BASE                     (APBPERIPH_BASE + 0x00004800)
#define SPI2_BASE                    (APBPERIPH_BASE + 0x00005800)

/**
  * @}
  */
  
/** @addtogroup Peripheral_declaration
  * @{
  */  

#define PMU                          ((PMU_TypeDef *) PMU_BASE)
#define PMU_RETRAM                   ((PMU_RETRAM_TypeDef *) PMU_RETRAM_BASE)
#define ANA                          ((ANA_TypeDef *) ANA_BASE)
#define RTC                          ((RTC_TypeDef *) RTC_BASE)
#define FLASH                        ((FLASH_TypeDef *) FLASHSFR_BASE)
#define GPIOA                        ((GPIOA_TypeDef *) GPIOA_BASE)
#define GPIOB                        ((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC                        ((GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD                        ((GPIO_TypeDef *) GPIOD_BASE)
#define GPIOE                        ((GPIO_TypeDef *) GPIOE_BASE)
#define GPIOF                        ((GPIO_TypeDef *) GPIOF_BASE)
#define GPIOAF                       ((GPIO_AF_TypeDef *) GPIOAF_BASE)
#define DMA                          ((DMA_TypeDef *) DMA_BASE)
#define UART0                        ((UART_TypeDef *) UART0_BASE)
#define UART1                        ((UART_TypeDef *) UART1_BASE)
#define UART2                        ((UART_TypeDef *) UART2_BASE)
#define UART3                        ((UART_TypeDef *) UART3_BASE)
#define UART4                        ((UART_TypeDef *) UART4_BASE)
#define UART5                        ((UART_TypeDef *) UART5_BASE)
#define U32K0                        ((U32K_TypeDef *) U32K0_BASE)
#define U32K1                        ((U32K_TypeDef *) U32K1_BASE)
#define ISO78160                     ((ISO7816_TypeDef *) ISO78160_BASE)
#define ISO78161                     ((ISO7816_TypeDef *) ISO78161_BASE)
#define TMR0                         ((TMR_TypeDef *) TMR0_BASE)
#define TMR1                         ((TMR_TypeDef *) TMR1_BASE)
#define TMR2                         ((TMR_TypeDef *) TMR2_BASE)
#define TMR3                         ((TMR_TypeDef *) TMR3_BASE)
#define PWM0                         ((PWM_TypeDef *) PWM0_BASE)
#define PWM1                         ((PWM_TypeDef *) PWM1_BASE)
#define PWM2                         ((PWM_TypeDef *) PWM2_BASE)
#define PWM3                         ((PWM_TypeDef *) PWM3_BASE)
#define PWMMUX                       ((PWM_MUX_TypeDef *) PWMMUX_BASE)
#define LCD                          ((LCD_TypeDef *) LCD_BASE)
#define SPI1                         ((SPI_TypeDef *) SPI1_BASE)
#define SPI2                         ((SPI_TypeDef *) SPI2_BASE)
#define I2C                          ((I2C_TypeDef *) I2C_BASE)
#define MISC                         ((MISC_TypeDef *) MISC_BASE)
#define MISC2                        ((MISC2_TypeDef *) MISC2_BASE)
#define CRYPT                        ((CRYPT_TypeDef *) CRYPT_BASE)

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
/*                                                                            */
/*                        Power Management Unit (PMU)                         */
/*                                                                            */
/******************************************************************************/

/**************  Bits definition for PMU_DSLEEPEN register   ******************/
#define PMU_DSLEEPEN_DSLEEP_Pos       (0U)                                     
#define PMU_DSLEEPEN_DSLEEP_Msk       (0x1U << PMU_DSLEEPEN_DSLEEP_Pos)        /*!< 0x00000001 */
#define PMU_DSLEEPEN_DSLEEP            PMU_DSLEEPEN_DSLEEP_Msk                 /*!< This bit indicates the deep-sleep mode has been entry */
#define PMU_DSLEEPEN_WKU_Pos          (31U)                                     
#define PMU_DSLEEPEN_WKU_Msk          (0x1U << PMU_DSLEEPEN_WKU_Pos)           /*!< 0x80000000 */
#define PMU_DSLEEPEN_WKU               PMU_DSLEEPEN_WKU_Msk                    /*!< Current wake-up signal status, this bit reflect the wake-up status receive by PMU controller */

/**************  Bits definition for PMU_DSLEEPPASS register ******************/
#define PMU_DSLEEPPASS_UNLOCK_Pos     (0U)                                     
#define PMU_DSLEEPPASS_UNLOCK_Msk     (0x1U << PMU_DSLEEPPASS_UNLOCK_Pos)      /*!< 0x00000001 */
#define PMU_DSLEEPPASS_UNLOCK          PMU_DSLEEPPASS_UNLOCK_Msk               /*!< This bit indicates the entry of deep-sleep mode has been unlocked and is ready to entry deep-sleep mode */

/**************  Bits definition for PMU_CONTROL register    ******************/
#define PMU_CONTROL_INT_IOA_EN_Pos    (0U)                                     
#define PMU_CONTROL_INT_IOA_EN_Msk    (0x1U << PMU_CONTROL_INT_IOA_EN_Pos)          /*!< 0x00000001 */
#define PMU_CONTROL_INT_IOA_EN         PMU_CONTROL_INT_IOA_EN_Msk                   /*!< PMU’s interrupt enable register.  This bit is used to control the interrupt signal output to CPU */
#define PMU_CONTROL_RTCLK_SEL_Pos     (1U)                                     
#define PMU_CONTROL_RTCLK_SEL_Msk     (0x1U << PMU_CONTROL_RTCLK_SEL_Pos)      /*!< 0x00000002 */
#define PMU_CONTROL_RTCLK_SEL          PMU_CONTROL_RTCLK_SEL_Msk               /*!< RTC Clock selection */
#define PMU_CONTROL_INT_32K_EN_Pos    (2U)                                     
#define PMU_CONTROL_INT_32K_EN_Msk    (0x1U << PMU_CONTROL_INT_32K_EN_Pos)     /*!< 0x00000004 */
#define PMU_CONTROL_INT_32K_EN         PMU_CONTROL_INT_32K_EN_Msk              /*!< 32K XTAL absent interrupt enable register.  This bit is used to control the interrupt signal output to CPU */
#define PMU_CONTROL_INT_6M_EN_Pos     (3U)                                     
#define PMU_CONTROL_INT_6M_EN_Msk     (0x1U << PMU_CONTROL_INT_6M_EN_Pos)      /*!< 0x00000008 */
#define PMU_CONTROL_INT_6M_EN          PMU_CONTROL_INT_6M_EN_Msk               /*!< 6.5536M XTAL absent interrupt enable register */
#define PMU_CONTROL_PLLH_SEL_Pos      (4U)                                     
#define PMU_CONTROL_PLLH_SEL_Msk      (0x1U << PMU_CONTROL_PLLH_SEL_Pos)       /*!< 0x00000010 */
#define PMU_CONTROL_PLLH_SEL           PMU_CONTROL_PLLH_SEL_Msk                /*!< High speed PLL input clock selection */
#define PMU_CONTROL_PLLL_SEL_Pos      (5U)                                     
#define PMU_CONTROL_PLLL_SEL_Msk      (0x1U << PMU_CONTROL_PLLL_SEL_Pos)       /*!< 0x00000020 */
#define PMU_CONTROL_PLLL_SEL           PMU_CONTROL_PLLL_SEL_Msk                /*!< Low speed PLL input clock selection */
//#define PMU_CONTROL_PD_WKUEN_Pos      (6U)                                     
//#define PMU_CONTROL_PD_WKUEN_Msk      (0x1U << PMU_CONTROL_PD_WKUEN_Pos)       /*!< 0x00000040 */
//#define PMU_CONTROL_PD_WKUEN           PMU_CONTROL_PD_WKUEN_Msk                /*!< Wake-up enable/disable when main power is off */
//#define PMU_CONTROL_PWUPCYC_Pos       (8U)                                     
//#define PMU_CONTROL_PWUPCYC_Msk       (0xFFU << PMU_CONTROL_PWUPCYC_Pos)       /*!< 0x0000FF00 */
//#define PMU_CONTROL_PWUPCYC            PMU_CONTROL_PWUPCYC_Msk                 /*!< Power-up cycle count, this register control the power-up wait time when a wake-up even is received.  The unit is 32K clock period */
//#define PMU_CONTROL_NOWAITLOCK_Pos    (17U)
//#define PMU_CONTROL_NOWAITLOCK_Msk    (0x1U << PMU_CONTROL_NOWAITLOCK_Pos)     /*!< 0x00020000 */
//#define PMU_CONTROL_NOWAITLOCK         PMU_CONTROL_NOWAITLOCK_Msk              /*!< if the hardware will wait for PLLL’s lock signal when switch clock source to PLLL/PLLH */

/**************  Bits definition for PMU_STS register        ******************/
#define PMU_STS_INT_32K_Pos           (0U)                                     
#define PMU_STS_INT_32K_Msk           (0x1U << PMU_STS_INT_32K_Pos)            /*!< 0x00000001 */
#define PMU_STS_INT_32K                PMU_STS_INT_32K_Msk                     /*!< This bit represents the 32K crystal absent interrupt status.  When this bit is set to 1, it means the 32K crystal is removed or broken.  Write 1 to this bit can clear this flag to 0 */
#define PMU_STS_INT_6M_Pos            (1U)                                     
#define PMU_STS_INT_6M_Msk            (0x1U << PMU_STS_INT_6M_Pos)             /*!< 0x00000002 */
#define PMU_STS_INT_6M                 PMU_STS_INT_6M_Msk                      /*!< This bit represents the 6.55364M crystal absent interrupt status.  When this bit is set to 1, it means the 6.55364M crystal is removed or broken.  Write 1 to this bit can clear this flag to 0 */
#define PMU_STS_EXIST_32K_Pos         (2U)                                     
#define PMU_STS_EXIST_32K_Msk         (0x1U << PMU_STS_EXIST_32K_Pos)          /*!< 0x00000004 */
#define PMU_STS_EXIST_32K              PMU_STS_EXIST_32K_Msk                   /*!< 32K XTAL exist status register.  This bit is represent 32K XTAL is existed or absent */
#define PMU_STS_EXIST_6M_Pos          (3U)                                     
#define PMU_STS_EXIST_6M_Msk          (0x1U << PMU_STS_EXIST_6M_Pos)           /*!< 0x00000008 */
#define PMU_STS_EXIST_6M               PMU_STS_EXIST_6M_Msk                    /*!< 6.5536M XTAL exist status register.  This bit is represent 6.5536M XTAL is existed or absent */
#define PMU_STS_EXTRST_Pos            (4U)                                     
#define PMU_STS_EXTRST_Msk            (0x1U << PMU_STS_EXTRST_Pos)             /*!< 0x00000010 */
#define PMU_STS_EXTRST                 PMU_STS_EXTRST_Msk                      /*!< This bit indicated if the last interrupt is cause by external reset signal.  Write 1 to clear this bit */
#define PMU_STS_PORST_Pos             (5U)                                     
#define PMU_STS_PORST_Msk             (0x1U << PMU_STS_PORST_Pos)              /*!< 0x00000020 */
#define PMU_STS_PORST                  PMU_STS_PORST_Msk                       /*!< This bit indicated if the last reset is cause by internal power-on reset signal.  Write 1 to clear this bit */
#define PMU_STS_DPORST_Pos            (6U)                                     
#define PMU_STS_DPORST_Msk            (0x1U << PMU_STS_DPORST_Pos)             /*!< 0x00000040 */
#define PMU_STS_DPORST                 PMU_STS_DPORST_Msk                      /*!< This bit indicated if the last reset is cause by internal digital power-on reset signal.  Write 1 to clear this bit */
#define PMU_STS_MODE_Pos              (24U)
#define PMU_STS_MODE_Msk              (0x1U << PMU_STS_MODE_Pos)               /*!< 0x01000000 */
#define PMU_STS_MODE                   PMU_STS_MODE_Msk                        /*!< This register shows the current status of MODE pin */

/**************  Bits definition for PMU_IOAOEN register     ******************/
#define PMU_IOAOEN_Pos                (0U)                                     
#define PMU_IOAOEN_Msk                (0xFFFFU << PMU_IOAOEN_Pos)              /*!< 0x0000FFFF */
#define PMU_IOAOEN_IOAOEN              PMU_IOAOEN_Msk                          /*!< Each bit control the IOA’s output enable signal */

/**************  Bits definition for PMU_IOAIE register      ******************/
#define PMU_IOAIE_Pos                 (0U)                                     
#define PMU_IOAIE_Msk                 (0xFFFFU << PMU_IOAIE_Pos)               /*!< 0x0000FFFF */
#define PMU_IOAIE_IOAIE                PMU_IOAIE_Msk                           /*!< Each bit control the IOA’s input enable signal */
 
/**************  Bits definition for PMU_IOADAT register     ******************/
#define PMU_IOADAT_Pos                (0U)                                     
#define PMU_IOADAT_Msk                (0xFFFFU << PMU_IOADAT_Pos)              /*!< 0x0000FFFF */
#define PMU_IOADAT_IOADAT              PMU_IOADAT_Msk                          /*!< Each bit control the IOA’s output data and pull low/high function */

/**************  Bits definition for PMU_IOAATT register     ******************/
#define PMU_IOAATT_Pos                (0U)                                     
#define PMU_IOAATT_Msk                (0xFFFFU << PMU_IOAATT_Pos)              /*!< 0x0000FFFF */
#define PMU_IOAATT_IOAATT              PMU_IOAATT_Msk                          /*!< Each bit control the IOA’s attribute and pull low/high function */

/**************  Bits definition for PMU_IOAWKUEN register   ******************/
#define PMU_IOAWKUEN_Pos              (0U)                                     
#define PMU_IOAWKUEN_Msk              (0xFFFFFFFFU << PMU_IOAWKUEN_Pos)        /*!< 0xFFFFFFFF */
#define PMU_IOAWKUEN_IOAWKUEN          PMU_IOAWKUEN_Msk                        /*!< Every 2 bits control the IOA’s wake up function */

/**************  Bits definition for PMU_IOASTS register     ******************/
#define PMU_IOASTS_Pos                (0U)                                     
#define PMU_IOASTS_Msk                (0xFFFFU << PMU_IOASTS_Pos)              /*!< 0x0000FFFF */
#define PMU_IOASTS_IOASTS              PMU_IOASTS_Msk                          /*!< Each bit represents the current IOA’s input data value */

/**************  Bits definition for PMU_IOAINT register     ******************/
#define PMU_IOAINT_Pos                (0U)                                     
#define PMU_IOAINT_Msk                (0xFFFFU << PMU_IOAINT_Pos)              /*!< 0x0000FFFF */
#define PMU_IOAINT_IOAINT              PMU_IOAINT_Msk                          /*!< Each bit represents the IOA’s interrupt status.  The corresponded bit will be set to 1 when corresponded wake-up event is detected.  This register can be clear to 0 by writing corresponded bit to 1 */

/**************  Bits definition for PMU_IOADR register      ******************/
#define PMU_IOADR_IOA0DR_Pos          (0U)                                     
#define PMU_IOADR_IOA0DR_Msk          (0x1U << PMU_IOADR_IOA0DR_Pos)           /*!< 0x00000001 */
#define PMU_IOADR_IOA0DR               PMU_IOADR_IOA0DR_Msk                    /*!< IOA0’s driving strength setting, change to this register will change all setting of IOA0~IOA15 */
#define PMU_IOADR_IOAXDR_Pos          (1U)                                     
#define PMU_IOADR_IOAXDR_Msk          (0x7FFFU << PMU_IOADR_IOAXDR_Pos)        /*!< 0x0000FFFE */
#define PMU_IOADR_IOAXDR               PMU_IOADR_IOAXDR_Msk                    /*!< Each bit represent the current driving strength setting of IOA1~IOA15 */

/**************  Bits definition for PMU_IOASEL register     ******************/
#define PMU_IOASEL_SEL3_Pos           (3U)                                     
#define PMU_IOASEL_SEL3_Msk           (0x1U << PMU_IOASEL_SEL3_Pos)            /*!< 0x00000008 */
#define PMU_IOASEL_SEL3                PMU_IOASEL_SEL3_Msk                     /*!< IOA3 special function select register */
#define PMU_IOASEL_SEL6_Pos           (6U)                                     
#define PMU_IOASEL_SEL6_Msk           (0x1U << PMU_IOASEL_SEL6_Pos)            /*!< 0x00000040 */
#define PMU_IOASEL_SEL6                PMU_IOASEL_SEL6_Msk                     /*!< IOA6 special function select register */
#define PMU_IOASEL_SEL7_Pos           (7U)                                     
#define PMU_IOASEL_SEL7_Msk           (0x1U << PMU_IOASEL_SEL7_Pos)            /*!< 0x00000080 */
#define PMU_IOASEL_SEL7                PMU_IOASEL_SEL7_Msk                     /*!< IOA7 special function select register */

/**************  Bits definition for PMU_WDTPASS register    ******************/
#define PMU_WDTPASS_UNLOCK_Pos        (0U)                                     
#define PMU_WDTPASS_UNLOCK_Msk        (0x1U << PMU_WDTPASS_UNLOCK_Pos)         /*!< 0x00000001 */
#define PMU_WDTPASS_UNLOCK             PMU_WDTPASS_UNLOCK_Msk                  /*!< This bit indicates the watch dog timer enable register has been unlocked and is ready to change the watch dog enable control register */

/**************  Bits definition for PMU_WDTEN register      ******************/
#define PMU_WDTEN_WDTEN_Pos           (0U)                                     
#define PMU_WDTEN_WDTEN_Msk           (0x1U << PMU_WDTEN_WDTEN_Pos)            /*!< 0x00000001 */
#define PMU_WDTEN_WDTEN                PMU_WDTEN_WDTEN_Msk                     /*!< This bit indicates the watch dog timer is enable.  To change the value of this register, UNLOCK bit of MISC_WDTPASS should be set to 1 first */
#define PMU_WDTEN_WDTSEL_Pos          (2U)                                     
#define PMU_WDTEN_WDTSEL_Msk          (0x3U << PMU_WDTEN_WDTSEL_Pos)           /*!< 0x0000000C */
#define PMU_WDTEN_WDTSEL               PMU_WDTEN_WDTSEL_Msk                    /*!< This register is used to control the WDT counting period */
#define PMU_WDTEN_WDTSEL_0            (0x0U << PMU_WDTEN_WDTSEL_Pos)
#define PMU_WDTEN_WDTSEL_1            (0x1U << PMU_WDTEN_WDTSEL_Pos)
#define PMU_WDTEN_WDTSEL_2            (0x2U << PMU_WDTEN_WDTSEL_Pos)
#define PMU_WDTEN_WDTSEL_3            (0x3U << PMU_WDTEN_WDTSEL_Pos)


/**************  Bits definition for PMU_WDTCLR register     ******************/
#define PMU_WDTCLR_WDTCNT_Pos         (0U)                                     
#define PMU_WDTCLR_WDTCNT_Msk         (0xFFFFU << PMU_WDTCLR_WDTCNT_Pos)       /*!< 0x0000FFFF */
#define PMU_WDTCLR_WDTCNT              PMU_WDTCLR_WDTCNT_Msk                   /*!< This register shows the current counter value of wat dog timer.  When this timer count to limit value set by WDTSEL, the WDT will issue a system reset */

/**************  Bits definition for PMU_WDTSTS register     ******************/
//#define PMU_WDTSTS_WDTSTS_Pos         (0U)                                     
//#define PMU_WDTSTS_WDTSTS_Msk         (0x1U << PMU_WDTSTS_WDTSTS_Pos)          /*!< 0x00000001 */
//#define PMU_WDTSTS_WDTSTS              PMU_WDTSTS_WDTSTS_Msk                   /*!< This register indicates that a WDT reset has happened.  Programmer can read this bit to know if this time is the WDT reset.  Write 1 to this bit can clear this flag */

/******************************************************************************/
/*                                                                            */
/*                         Embedded 256 Bytes Retention SRAM (PMU_RAM)        */
/*                                                                            */
/******************************************************************************/

/**************  Bits definition for PMU_RAMx register       ******************/
#define PMU_RAM_RAM_Pos               (0U)                                     
#define PMU_RAM_RAM_Msk               (0xFFFFFFFFU << PMU_RAM_RAM_Pos)         /*!< 0xFFFFFFFF */
#define PMU_RAM_RAM                    PMU_RAM_RAM_Msk                         /*!< There is a 256 bytes (64x32) SRAM embedded in the PMU controller.  This RAM can keep data during deep-sleep mode.  Only word access is allowed to these ports */

/******************************************************************************/
/*                                                                            */
/*                         Analog controller (ANA)                            */
/*                                                                            */
/******************************************************************************/

/**************  Bits definition for ANA_REG0 register       ******************/
//#define ANA_REG0_CURRIT_Pos           (0U)                                     
//#define ANA_REG0_CURRIT_Msk           (0x3U << ANA_REG0_CURRIT_Pos)            /*!< 0x00000003 */
//#define ANA_REG0_CURRIT                ANA_REG0_CURRIT_Msk                     /*!< ADC overall bias current trim */ 
//#define ANA_REG0_CURRIT_0             (0x0U << ANA_REG0_CURRIT_Pos)
//#define ANA_REG0_CURRIT_1             (0x1U << ANA_REG0_CURRIT_Pos)
//#define ANA_REG0_CURRIT_2             (0x2U << ANA_REG0_CURRIT_Pos)
//#define ANA_REG0_CURRIT_3             (0x3U << ANA_REG0_CURRIT_Pos)
//#define ANA_REG0_ADIT1_Pos            (2U)                                     
//#define ANA_REG0_ADIT1_Msk            (0x3U << ANA_REG0_ADIT1_Pos)             /*!< 0x0000000C */
//#define ANA_REG0_ADIT1                 ANA_REG0_ADIT1_Msk                      /*!< Current trim for 1st stage of ADC */ 
//#define ANA_REG0_ADIT1_0              (0x0U << ANA_REG0_ADIT1_Pos)
//#define ANA_REG0_ADIT1_1              (0x1U << ANA_REG0_ADIT1_Pos)
//#define ANA_REG0_ADIT1_2              (0x2U << ANA_REG0_ADIT1_Pos)
//#define ANA_REG0_ADIT1_3              (0x3U << ANA_REG0_ADIT1_Pos)
//#define ANA_REG0_ADIT2_Pos            (4U)                                     
//#define ANA_REG0_ADIT2_Msk            (0x3U << ANA_REG0_ADIT2_Pos)             /*!< 0x00000030 */
//#define ANA_REG0_ADIT2                 ANA_REG0_ADIT2_Msk                      /*!< Current trim for 2st stage of ADC */ 
//#define ANA_REG0_ADIT2_0              (0x0U << ANA_REG0_ADIT2_Pos)
//#define ANA_REG0_ADIT2_1              (0x1U << ANA_REG0_ADIT2_Pos)
//#define ANA_REG0_ADIT2_2              (0x2U << ANA_REG0_ADIT2_Pos)
//#define ANA_REG0_ADIT2_3              (0x3U << ANA_REG0_ADIT2_Pos)
//#define ANA_REG0_REFBIT_Pos           (6U)                                     
//#define ANA_REG0_REFBIT_Msk           (0x1U << ANA_REG0_REFBIT_Pos)            /*!< 0x00000040 */
//#define ANA_REG0_REFBIT                ANA_REG0_REFBIT_Msk                     /*!< Current trim for ADC ref buffer */ 
//#define ANA_REG0_ADQIT_Pos            (7U)                                     
//#define ANA_REG0_ADQIT_Msk            (0x1U << ANA_REG0_ADQIT_Pos)             /*!< 0x00000080 */
//#define ANA_REG0_ADQIT                 ANA_REG0_ADQIT_Msk                      /*!< Current trim for ADC CMP */ 

/**************  Bits definition for ANA_REG1 register       ******************/
//#define ANA_REG1_ADC_SEL_Pos          (0U)                                     
//#define ANA_REG1_ADC_SEL_Msk          (0xFU << ANA_REG1_ADC_SEL_Pos)           /*!< 0x0000000F */
//#define ANA_REG1_ADC_SEL               ANA_REG1_ADC_SEL_Msk                    /*!< This register represents current ADC sampling channels.  The ADC sampling channels are controlled by ADC controller */ 
//#define ANA_REG1_ADC_SEL_0            (0x0U << ANA_REG1_ADC_SEL_Pos)
//#define ANA_REG1_ADC_SEL_1            (0x1U << ANA_REG1_ADC_SEL_Pos)
//#define ANA_REG1_ADC_SEL_2            (0x2U << ANA_REG1_ADC_SEL_Pos)
//#define ANA_REG1_ADC_SEL_3            (0x3U << ANA_REG1_ADC_SEL_Pos)
//#define ANA_REG1_ADC_SEL_4            (0x4U << ANA_REG1_ADC_SEL_Pos)
//#define ANA_REG1_ADC_SEL_5            (0x5U << ANA_REG1_ADC_SEL_Pos)
//#define ANA_REG1_ADC_SEL_6            (0x6U << ANA_REG1_ADC_SEL_Pos)
//#define ANA_REG1_ADC_SEL_7            (0x7U << ANA_REG1_ADC_SEL_Pos)
//#define ANA_REG1_ADC_SEL_8            (0x8U << ANA_REG1_ADC_SEL_Pos)
//#define ANA_REG1_ADC_SEL_9            (0x9U << ANA_REG1_ADC_SEL_Pos)
//#define ANA_REG1_ADC_SEL_10           (0xAU << ANA_REG1_ADC_SEL_Pos)
//#define ANA_REG1_ADC_SEL_11           (0xBU << ANA_REG1_ADC_SEL_Pos)
#define ANA_REG1_RESDIV_Pos           (4U)                                     
#define ANA_REG1_RESDIV_Msk           (0x1U << ANA_REG1_RESDIV_Pos)            /*!< 0x00000010 */
#define ANA_REG1_RESDIV                ANA_REG1_RESDIV_Msk                     /*!< Enable resistor division for M ADC’s input signal */
#define ANA_REG1_GDE4_Pos             (5U)                                     
#define ANA_REG1_GDE4_Msk             (0x1U << ANA_REG1_GDE4_Pos)              /*!< 0x00000020 */
#define ANA_REG1_GDE4                  ANA_REG1_GDE4_Msk                       /*!< Enable cap division for M ADC’s input signal */
//#define ANA_REG1_PRES_EN_Pos          (6U)                                     
//#define ANA_REG1_PRES_EN_Msk          (0x1U << ANA_REG1_PRES_EN_Pos)           /*!< 0x00000040 */
//#define ANA_REG1_PRES_EN               ANA_REG1_PRES_EN_Msk                    /*!< Enable pull down resistor for M ADC’s input signal */
//#define ANA_REG1_ADCRSTM_Pos          (7U)                                     
//#define ANA_REG1_ADCRSTM_Msk          (0x1U << ANA_REG1_ADCRSTM_Pos)           /*!< 0x00000080 */
//#define ANA_REG1_ADCRSTM               ANA_REG1_ADCRSTM_Msk                    /*!<  */

/**************  Bits definition for ANA_REG2 register       ******************/
#define ANA_REG2_CMP1_SEL_Pos         (0U)                                     
#define ANA_REG2_CMP1_SEL_Msk         (0x3U << ANA_REG2_CMP1_SEL_Pos)          /*!< 0x00000003 */
#define ANA_REG2_CMP1_SEL              ANA_REG2_CMP1_SEL_Msk                   /*!< Signal source selection of comparator A */ 
#define ANA_REG2_CMP1_SEL_0           (0x0U << ANA_REG2_CMP1_SEL_Pos)
#define ANA_REG2_CMP1_SEL_1           (0x1U << ANA_REG2_CMP1_SEL_Pos)
#define ANA_REG2_CMP1_SEL_2           (0x2U << ANA_REG2_CMP1_SEL_Pos)
#define ANA_REG2_CMP1_SEL_3           (0x3U << ANA_REG2_CMP1_SEL_Pos)
#define ANA_REG2_CMP2_SEL_Pos         (2U)                                     
#define ANA_REG2_CMP2_SEL_Msk         (0x3U << ANA_REG2_CMP2_SEL_Pos)          /*!< 0x0000000C */
#define ANA_REG2_CMP2_SEL              ANA_REG2_CMP2_SEL_Msk                   /*!< Signal source selection of comparator B */ 
#define ANA_REG2_REFSEL_CMP1_Pos      (4U)                                     
#define ANA_REG2_REFSEL_CMP1_Msk      (0x1U << ANA_REG2_REFSEL_CMP1_Pos)       /*!< 0x00000010 */
#define ANA_REG2_REFSEL_CMP1           ANA_REG2_REFSEL_CMP1_Msk                /*!< REF selection of CMP1 */ 
#define ANA_REG2_REFSEL_CMP2_Pos      (5U)                                     
#define ANA_REG2_REFSEL_CMP2_Msk      (0x1U << ANA_REG2_REFSEL_CMP2_Pos)       /*!< 0x00000020 */
#define ANA_REG2_REFSEL_CMP2           ANA_REG2_REFSEL_CMP2_Msk                /*!< REF selection of CMP2 */ 
//#define ANA_REG2_TEMPPDN_Pos          (6U)                                     
//#define ANA_REG2_TEMPPDN_Msk          (0x1U << ANA_REG2_TEMPPDN_Pos)           /*!< 0x00000040 */
//#define ANA_REG2_TEMPPDN               ANA_REG2_TEMPPDN_Msk                    /*!< Temperature sensor power down control */ 
//#define ANA_REG2_XOLPD_Pos            (7U)                                     
//#define ANA_REG2_XOLPD_Msk            (0x1U << ANA_REG2_XOLPD_Pos)             /*!< 0x00000080 */
//#define ANA_REG2_XOLPD                 ANA_REG2_XOLPD_Msk                      /*!< 32K crystal pad (XOL) power down control */ 

/**************  Bits definition for ANA_REG3 register       ******************/
#define ANA_REG3_ADCPDN_Pos           (0U)                                    
#define ANA_REG3_ADCPDN_Msk           (0x1U << ANA_REG3_ADCPDN_Pos)            /*!< 0x00000001 */
#define ANA_REG3_ADCPDN                ANA_REG3_ADCPDN_Msk                     /*!< ADC power down control signal */ 
#define ANA_REG3_CMP1PDN_Pos          (1U)                                     
#define ANA_REG3_CMP1PDN_Msk          (0x1U << ANA_REG3_CMP1PDN_Pos)           /*!< 0x00000002 */
#define ANA_REG3_CMP1PDN               ANA_REG3_CMP1PDN_Msk                    /*!< CMP1 power down control signal */ 
#define ANA_REG3_CMP2PDN_Pos          (2U)                                     
#define ANA_REG3_CMP2PDN_Msk          (0x1U << ANA_REG3_CMP2PDN_Pos)           /*!< 0x00000004 */
#define ANA_REG3_CMP2PDN               ANA_REG3_CMP2PDN_Msk                    /*!< CMP2 power down control signal */ 
#define ANA_REG3_BGPPD_Pos            (3U)                                    
#define ANA_REG3_BGPPD_Msk            (0x1U << ANA_REG3_BGPPD_Pos)             /*!< 0x00000008 */
#define ANA_REG3_BGPPD                 ANA_REG3_BGPPD_Msk                      /*!< BGP power down control signal */ 
#define ANA_REG3_RCHPD_Pos            (4U)                                     
#define ANA_REG3_RCHPD_Msk            (0x1U << ANA_REG3_RCHPD_Pos)             /*!< 0x00000010 */
#define ANA_REG3_RCHPD                 ANA_REG3_RCHPD_Msk                      /*!< RCH (6.5536M ROSC) power down control signal */ 
#define ANA_REG3_PLLLPDN_Pos          (5U)                                     
#define ANA_REG3_PLLLPDN_Msk          (0x1U << ANA_REG3_PLLLPDN_Pos)           /*!< 0x00000020 */
#define ANA_REG3_PLLLPDN               ANA_REG3_PLLLPDN_Msk                    /*!< PLLL (32768Hz input PLL) power down control signal */ 
#define ANA_REG3_PLLHPDN_Pos          (6U)                                     
#define ANA_REG3_PLLHPDN_Msk          (0x1U << ANA_REG3_PLLHPDN_Pos)           /*!< 0x00000040 */
#define ANA_REG3_PLLHPDN               ANA_REG3_PLLHPDN_Msk                    /*!< PLLL (6.55364MHz input PLL) power down control signal */ 
#define ANA_REG3_XOHPDN_Pos           (7U)                                     
#define ANA_REG3_XOHPDN_Msk           (0x1U << ANA_REG3_XOHPDN_Pos)            /*!< 0x00000080 */
#define ANA_REG3_XOHPDN                ANA_REG3_XOHPDN_Msk                     /*!< Turn on signal of 6.5536M crystal */ 

/**************  Bits definition for ANA_REG4 register       ******************/
//#define ANA_REG4_XRSEL_Pos            (0U)                                     
//#define ANA_REG4_XRSEL_Msk            (0x3U << ANA_REG4_XRSEL_Pos)             /*!< 0x00000003 */
//#define ANA_REG4_XRSEL                 ANA_REG4_XRSEL_Msk                      /*!< After power up, set this register to 0x3 for low power operation */ 
//#define ANA_REG4_XOLLP_Pos            (2U)                                     
//#define ANA_REG4_XOLLP_Msk            (0x1U << ANA_REG4_XOLLP_Pos)             /*!< 0x00000004 */
//#define ANA_REG4_XOLLP                 ANA_REG4_XOLLP_Msk                      /*!< 32K crystal pad low power mode, set this bit to 1 after power-up for low power operation */
//#define ANA_REG4_XCSEL_Pos            (3U)                                     
//#define ANA_REG4_XCSEL_Msk            (0x1U << ANA_REG4_XCSEL_Pos)             /*!< 0x00000008 */
//#define ANA_REG4_XCSEL                 ANA_REG4_XCSEL_Msk                      /*!< 32K crystal capacitance trimming */
//#define ANA_REG4_XRSEL_H_Pos          (4U)                                     
//#define ANA_REG4_XRSEL_H_Msk          (0x3U << ANA_REG4_XRSEL_H_Pos)           /*!< 0x00000030 */
//#define ANA_REG4_XRSEL_H               ANA_REG4_XRSEL_H_Msk                    /*!<  */
//#define ANA_REG4_XCSEL_H_Pos          (6U)                                     
//#define ANA_REG4_XCSEL_H_Msk          (0x3U << ANA_REG4_XCSEL_H_Pos)           /*!< 0x000000C0 */
//#define ANA_REG4_XCSEL_H               ANA_REG4_XCSEL_H_Msk                    /*!<  */

/**************  Bits definition for ANA_REG5 register       ******************/
#define ANA_REG5_IT_CMP1_Pos          (0U)                                   
#define ANA_REG5_IT_CMP1_Msk          (0x3U << ANA_REG5_IT_CMP1_Pos)           /*!< 0x00000003 */
#define ANA_REG5_IT_CMP1               ANA_REG5_IT_CMP1_Msk                    /*!< Bias current selection of CMP1 */ 
#define ANA_REG5_IT_CMP1_0            (0x0U << ANA_REG5_IT_CMP1_Pos)
#define ANA_REG5_IT_CMP1_1            (0x1U << ANA_REG5_IT_CMP1_Pos)
#define ANA_REG5_IT_CMP1_2            (0x2U << ANA_REG5_IT_CMP1_Pos)
#define ANA_REG5_IT_CMP1_3            (0x3U << ANA_REG5_IT_CMP1_Pos)
#define ANA_REG5_IT_CMP2_Pos          (2U)                                   
#define ANA_REG5_IT_CMP2_Msk          (0x3U << ANA_REG5_IT_CMP2_Pos)           /*!< 0x0000000C */
#define ANA_REG5_IT_CMP2               ANA_REG5_IT_CMP2_Msk                    /*!< Bias current selection of CMP2 */ 
//#define ANA_REG5_CMP_HYS_Pos          (4U)                                   
//#define ANA_REG5_CMP_HYS_Msk          (0x1U << ANA_REG5_CMP_HYS_Pos)           /*!< 0x00000010 */
//#define ANA_REG5_CMP_HYS               ANA_REG5_CMP_HYS_Msk                    /*!< HYS voltage selection */ 
//#define ANA_REG5_PW2M_EN_Pos          (5U)                                   
//#define ANA_REG5_PW2M_EN_Msk          (0x1U << ANA_REG5_PW2M_EN_Pos)           /*!< 0x00000020 */
//#define ANA_REG5_PW2M_EN               ANA_REG5_PW2M_EN_Msk                    /*!< Enable power supply to RTC */ 
#define ANA_REG5_PD_AVCCDET_Pos      (6U)                                   
#define ANA_REG5_PD_AVCCDET_Msk      (0x1U << ANA_REG5_PD_AVCCDET_Pos)       /*!< 0x00000040 */
#define ANA_REG5_PD_AVCCDET           ANA_REG5_PD_AVCCDET_Msk                /*!< Power down low voltage detector */ 
//#define ANA_REG5_RTCLDOPD_EN_Pos      (7U)                                   
//#define ANA_REG5_RTCLDOPD_EN_Msk      (0x1U << ANA_REG5_RTCLDOPD_EN_Pos)       /*!< 0x00000080 */
//#define ANA_REG5_RTCLDOPD_EN           ANA_REG5_RTCLDOPD_EN_Msk                /*!< Enable PD RTCLDO when main power is on */ 

/**************  Bits definition for ANA_REG6 register       ******************/
#define ANA_REG6_LCD_BMODE_Pos        (0U)                                     
#define ANA_REG6_LCD_BMODE_Msk        (0x1U << ANA_REG6_LCD_BMODE_Pos)         /*!< 0x00000001 */
#define ANA_REG6_LCD_BMODE             ANA_REG6_LCD_BMODE_Msk                  /*!< LCD BIAS mode selection */ 
#define ANA_REG6_VLCD_Pos             (1U)                                     
#define ANA_REG6_VLCD_Msk             (0xFU << ANA_REG6_VLCD_Pos)              /*!< 0x0000001E */
#define ANA_REG6_VLCD                  ANA_REG6_VLCD_Msk                       /*!< LCD driving voltage */ 
#define ANA_REG6_VLCD_0               (0x0U << ANA_REG6_VLCD_Pos) 
#define ANA_REG6_VLCD_1               (0x1U << ANA_REG6_VLCD_Pos)
#define ANA_REG6_VLCD_2               (0x2U << ANA_REG6_VLCD_Pos)
#define ANA_REG6_VLCD_3               (0x3U << ANA_REG6_VLCD_Pos)
#define ANA_REG6_VLCD_4               (0x4U << ANA_REG6_VLCD_Pos)
#define ANA_REG6_VLCD_5               (0x5U << ANA_REG6_VLCD_Pos)
#define ANA_REG6_VLCD_6               (0x6U << ANA_REG6_VLCD_Pos)
#define ANA_REG6_VLCD_7               (0x7U << ANA_REG6_VLCD_Pos)
#define ANA_REG6_VLCD_8               (0x8U << ANA_REG6_VLCD_Pos)
#define ANA_REG6_VLCD_9               (0x9U << ANA_REG6_VLCD_Pos)
#define ANA_REG6_VLCD_A               (0xAU << ANA_REG6_VLCD_Pos)
#define ANA_REG6_VLCD_B               (0xBU << ANA_REG6_VLCD_Pos)
#define ANA_REG6_VLCD_C               (0xCU << ANA_REG6_VLCD_Pos)
#define ANA_REG6_VLCD_D               (0xDU << ANA_REG6_VLCD_Pos)
#define ANA_REG6_VLCD_E               (0xEU << ANA_REG6_VLCD_Pos)
#define ANA_REG6_VLCD_F               (0xFU << ANA_REG6_VLCD_Pos)
//#define ANA_REG6_LCDVOUT_Pos          (5U)                                     
//#define ANA_REG6_LCDVOUT_Msk          (0x1U << ANA_REG6_LCDVOUT_Pos)           /*!< 0x00000020 */
//#define ANA_REG6_LCDVOUT               ANA_REG6_LCDVOUT_Msk                    /*!< LCD voltage output enable */ 
//#define ANA_REG6_BAT1DISC_Pos         (6U)                                     
//#define ANA_REG6_BAT1DISC_Msk         (0x1U << ANA_REG6_BAT1DISC_Pos)          /*!< 0x00000040 */
//#define ANA_REG6_BAT1DISC              ANA_REG6_BAT1DISC_Msk                   /*!< Discharge the BAT1 battery */ 
#define ANA_REG6_BATRTCDISC_Pos       (7U)                                     
#define ANA_REG6_BATRTCDISC_Msk       (0x1U << ANA_REG6_BATRTCDISC_Pos)        /*!< 0x00000080 */
#define ANA_REG6_BATRTCDISC            ANA_REG6_BATRTCDISC_Msk                 /*!< Discharge the RTCBAT battery */ 

/**************  Bits definition for ANA_REG7 register       ******************/
//#define ANA_REG7_ANAOUT_EN_Pos        (0U)                                     
//#define ANA_REG7_ANAOUT_EN_Msk        (0x1U << ANA_REG7_ANAOUT_EN_Pos)         /*!< 0x00000001 */
//#define ANA_REG7_ANAOUT_EN             ANA_REG7_ANAOUT_EN_Msk                  /*!< Enable analog signal out */ 
//#define ANA_REG7_P10ENN_Pos           (1U)                                     
//#define ANA_REG7_P10ENN_Msk           (0x1U << ANA_REG7_P10ENN_Pos)            /*!< 0x00000002 */
//#define ANA_REG7_P10ENN                ANA_REG7_P10ENN_Msk                     /*!<  */ 
//#define ANA_REG7_MADCHOPN_Pos         (2U)                                     
//#define ANA_REG7_MADCHOPN_Msk         (0x1U << ANA_REG7_MADCHOPN_Pos)          /*!< 0x00000004 */
//#define ANA_REG7_MADCHOPN              ANA_REG7_MADCHOPN_Msk                   /*!<  */ 
//#define ANA_REG7_TMPCKOFF_Pos         (3U)                                     
//#define ANA_REG7_TMPCKOFF_Msk         (0x1U << ANA_REG7_TMPCKOFF_Pos)          /*!< 0x00000008 */
//#define ANA_REG7_TMPCKOFF              ANA_REG7_TMPCKOFF_Msk                   /*!<  */ 
//#define ANA_REG7_LDOISEL_Pos          (4U)                                     
//#define ANA_REG7_LDOISEL_Msk          (0x1U << ANA_REG7_LDOISEL_Pos)           /*!< 0x00000010 */
//#define ANA_REG7_LDOISEL               ANA_REG7_LDOISEL_Msk                    /*!<  */ 
//#define ANA_REG7_SWT2VDD_Pos          (5U)                                     
//#define ANA_REG7_SWT2VDD_Msk          (0x1U << ANA_REG7_SWT2VDD_Pos)       /*!< 0x00000020 */
//#define ANA_REG7_SWT2VDD               ANA_REG7_SWT2VDD_Msk                /*!<  */ 
//#define ANA_REG7_X32KIN_EN_Pos        (6U)                                     
//#define ANA_REG7_X32KIN_EN_Msk        (0x1U << ANA_REG7_X32KIN_EN_Pos)         /*!< 0x00000040 */
//#define ANA_REG7_X32KIN_EN             ANA_REG7_X32KIN_EN_Msk                  /*!< Additional X32K pad input enable */ 
//#define ANA_REG7_CLKOSEL_Pos          (7U)                                     
//#define ANA_REG7_CLKOSEL_Msk          (0x1U << ANA_REG7_CLKOSEL_Pos)           /*!< 0x00000080 */
//#define ANA_REG7_CLKOSEL               ANA_REG7_CLKOSEL_Msk                    /*!<  */ 

/**************  Bits definition for ANA_REG8 register       ******************/
//#define ANA_REG8_DVCCSEL_Pos         (0U)                                     
//#define ANA_REG8_DVCCSEL_Msk         (0x3U << ANA_REG8_DVCCSEL_Pos)          /*!< 0x00000003 */
//#define ANA_REG8_DVCCSEL              ANA_REG8_DVCCSEL_Msk                   /*!< Trimming of DVCC */ 
//#define ANA_REG8_DVCCSEL_0           (0x0U << ANA_REG8_DVCCSEL_Pos)
//#define ANA_REG8_DVCCSEL_1           (0x1U << ANA_REG8_DVCCSEL_Pos)
//#define ANA_REG8_DVCCSEL_2           (0x2U << ANA_REG8_DVCCSEL_Pos)
//#define ANA_REG8_DVCCSEL_3           (0x3U << ANA_REG8_DVCCSEL_Pos)
//#define ANA_REG8_AVCCSEL_Pos         (2U)                                     
//#define ANA_REG8_AVCCSEL_Msk         (0x3U << ANA_REG8_AVCCSEL_Pos)          /*!< 0x0000000C */
//#define ANA_REG8_AVCCSEL              ANA_REG8_AVCCSEL_Msk                   /*!< Trimming of AVCC */ 
#define ANA_REG8_VDDPVDSEL_Pos       (4U)                                   
#define ANA_REG8_VDDPVDSEL_Msk       (0x7U << ANA_REG8_VDDPVDSEL_Pos)        /*!< 0x00000070 */
#define ANA_REG8_VDDPVDSEL            ANA_REG8_VDDPVDSEL_Msk                 /*!< Voltage selection of power detector, the setting in this register will affect the status of QPWRDN */ 
#define ANA_REG8_VDDPVDSEL_0         (0x0U << ANA_REG8_VDDPVDSEL_Pos)  
#define ANA_REG8_VDDPVDSEL_1         (0x1U << ANA_REG8_VDDPVDSEL_Pos)
#define ANA_REG8_VDDPVDSEL_2         (0x2U << ANA_REG8_VDDPVDSEL_Pos)
#define ANA_REG8_VDDPVDSEL_3         (0x3U << ANA_REG8_VDDPVDSEL_Pos)
#define ANA_REG8_VDDPVDSEL_4         (0x4U << ANA_REG8_VDDPVDSEL_Pos)
#define ANA_REG8_VDDPVDSEL_5         (0x5U << ANA_REG8_VDDPVDSEL_Pos)
#define ANA_REG8_VDDPVDSEL_6         (0x6U << ANA_REG8_VDDPVDSEL_Pos)
#define ANA_REG8_VDDPVDSEL_7         (0x7U << ANA_REG8_VDDPVDSEL_Pos)
#define ANA_REG8_PD_AVCCLDO_Pos      (7U)                                     
#define ANA_REG8_PD_AVCCLDO_Msk      (0x1U << ANA_REG8_PD_AVCCLDO_Pos)           /*!< 0x00000080 */
#define ANA_REG8_PD_AVCCLDO           ANA_REG8_PD_AVCCLDO_Msk                    /*!< AVCCLDO Power-down control signal */ 

/**************  Bits definition for ANA_REG9 register       ******************/
#define ANA_REG9_PLLLSEL_Pos          (0U)                                     
#define ANA_REG9_PLLLSEL_Msk          (0x7U << ANA_REG9_PLLLSEL_Pos)           /*!< 0x00000007 */
#define ANA_REG9_PLLLSEL               ANA_REG9_PLLLSEL_Msk                    /*!< Clk frequency selection of PLLL */ 
#define ANA_REG9_PLLLSEL_26M          (0x0U << ANA_REG9_PLLLSEL_Pos)
#define ANA_REG9_PLLLSEL_13M          (0x1U << ANA_REG9_PLLLSEL_Pos)
#define ANA_REG9_PLLLSEL_6_5M         (0x2U << ANA_REG9_PLLLSEL_Pos)
#define ANA_REG9_PLLLSEL_3_2M         (0x3U << ANA_REG9_PLLLSEL_Pos)
#define ANA_REG9_PLLLSEL_1_6M         (0x4U << ANA_REG9_PLLLSEL_Pos)
#define ANA_REG9_PLLLSEL_800K         (0x5U << ANA_REG9_PLLLSEL_Pos)
#define ANA_REG9_PLLLSEL_400K         (0x6U << ANA_REG9_PLLLSEL_Pos)
#define ANA_REG9_PLLLSEL_200K         (0x7U << ANA_REG9_PLLLSEL_Pos)
#define ANA_REG9_PLLHSEL_Pos          (3U)                                     
#define ANA_REG9_PLLHSEL_Msk          (0xFU << ANA_REG9_PLLHSEL_Pos)           /*!< 0x00000078 */
#define ANA_REG9_PLLHSEL               ANA_REG9_PLLHSEL_Msk                    /*!< Clk frequency selection of PLLH */ 
#define ANA_REG9_PLLHSEL_X2           (0xCU << ANA_REG9_PLLHSEL_Pos)
#define ANA_REG9_PLLHSEL_X2_5         (0xDU << ANA_REG9_PLLHSEL_Pos)
#define ANA_REG9_PLLHSEL_X3           (0xEU << ANA_REG9_PLLHSEL_Pos)
#define ANA_REG9_PLLHSEL_X3_5         (0xFU << ANA_REG9_PLLHSEL_Pos)
#define ANA_REG9_PLLHSEL_X4           (0x0U << ANA_REG9_PLLHSEL_Pos)
#define ANA_REG9_PLLHSEL_X4_5         (0x1U << ANA_REG9_PLLHSEL_Pos)
#define ANA_REG9_PLLHSEL_X5           (0x2U << ANA_REG9_PLLHSEL_Pos)
#define ANA_REG9_PLLHSEL_X5_5         (0x3U << ANA_REG9_PLLHSEL_Pos)
#define ANA_REG9_PLLHSEL_X6           (0x4U << ANA_REG9_PLLHSEL_Pos)
#define ANA_REG9_PLLHSEL_X6_5         (0x5U << ANA_REG9_PLLHSEL_Pos)
#define ANA_REG9_PLLHSEL_X7           (0x6U << ANA_REG9_PLLHSEL_Pos)
#define ANA_REG9_PLLHSEL_X7_5         (0x7U << ANA_REG9_PLLHSEL_Pos)
#define ANA_REG9_PDDET_Pos            (7U)                                     
#define ANA_REG9_PDDET_Msk            (0x1U << ANA_REG9_PDDET_Pos)             /*!< 0x00000080 */
#define ANA_REG9_PDDET                 ANA_REG9_PDDET_Msk                      /*!<  */ 

/**************  Bits definition for ANA_REGA register       ******************/
//#define ANA_REGA_VDD2_OFF_Pos         (0U)                                     
//#define ANA_REGA_VDD2_OFF_Msk         (0x1U << ANA_REGA_VDD2_OFF_Pos)          /*!< 0x00000001 */
//#define ANA_REGA_VDD2_OFF              ANA_REGA_VDD2_OFF_Msk                   /*!< This register is controlled by hardware and should be set to 0 for all the time */ 
//#define ANA_REGA_VDD3_OFF_Pos         (1U)                                     
//#define ANA_REGA_VDD3_OFF_Msk         (0x1U << ANA_REGA_VDD3_OFF_Pos)          /*!< 0x00000002 */
//#define ANA_REGA_VDD3_OFF              ANA_REGA_VDD3_OFF_Msk                   /*!< This register is controlled by hardware and should be set to 0 for all the time */ 
////#define ANA_REGA_RTCVSEL_Pos          (2U)                                     
//#define ANA_REGA_RTCVSEL_Msk          (0x1U << ANA_REGA_RTCVSEL_Pos)           /*!< 0x00000004 */
//#define ANA_REGA_RTCVSEL               ANA_REGA_RTCVSEL_Msk                    /*!< RTC LDO voltage selection */ 
//#define ANA_REGA_SWT2BAT1_Pos         (3U)                                     
//#define ANA_REGA_SWT2BAT1_Msk         (0x1U << ANA_REGA_SWT2BAT1_Pos)          /*!< 0x00000008 */
//#define ANA_REGA_SWT2BAT1              ANA_REGA_SWT2BAT1_Msk                   /*!< Switching from VDCIN to BAT1 manually */ 
//#define ANA_REGA_PSLSEL_Pos           (4U)                                     
//#define ANA_REGA_PSLSEL_Msk           (0x1U << ANA_REGA_PSLSEL_Pos)            /*!< 0x00000010 */
//#define ANA_REGA_PSLSEL                ANA_REGA_PSLSEL_Msk                     /*!< power switch level selection */ 
//#define ANA_REGA_PD_PORH_Pos          (5U)                                     
//#define ANA_REGA_PD_PORH_Msk          (0x1U << ANA_REGA_PD_PORH_Pos)           /*!< 0x00000020 */
//#define ANA_REGA_PD_PORH               ANA_REGA_PD_PORH_Msk                    /*!< PD POR_H module, output '1' when PD */ 
//#define ANA_REGA_PD_RCL_Pos           (6U)                                     
//#define ANA_REGA_PD_RCL_Msk           (0x1U << ANA_REGA_PD_RCL_Pos)            /*!< 0x00000040 */
//#define ANA_REGA_PD_RCL                ANA_REGA_PD_RCL_Msk                     /*!< PD 32K RC module */ 
#define ANA_REGA_PD_VDCINDET_Pos        (7U)                                     
#define ANA_REGA_PD_VDCINDET_Msk        (0x1U << ANA_REGA_PD_VDCINDET_Pos)     /*!< 0x00000080 */
#define ANA_REGA_PD_VDCINDET             ANA_REGA_PD_VDCINDET_Msk              /*!< PD VDCIN detector */ 

/**************  Bits definition for ANA_REGB register       ******************/
#define ANA_REGB_RCLTRIM_Pos          (0U)                                     
#define ANA_REGB_RCLTRIM_Msk          (0x1FU << ANA_REGB_RCLTRIM_Pos)          /*!< 0x0000001F */
#define ANA_REGB_RCLTRIM               ANA_REGB_RCLTRIM_Msk                    /*!< Trimming of 32kHz RC */ 
#define ANA_REGB_RCLTRIM_0            (0x00U << ANA_REGB_RCLTRIM_Pos)
#define ANA_REGB_RCLTRIM_1            (0x01U << ANA_REGB_RCLTRIM_Pos)
#define ANA_REGB_RCLTRIM_2            (0x02U << ANA_REGB_RCLTRIM_Pos)
#define ANA_REGB_RCLTRIM_3            (0x03U << ANA_REGB_RCLTRIM_Pos)
#define ANA_REGB_RCLTRIM_4            (0x04U << ANA_REGB_RCLTRIM_Pos)
#define ANA_REGB_RCLTRIM_5            (0x05U << ANA_REGB_RCLTRIM_Pos)
#define ANA_REGB_RCLTRIM_6            (0x06U << ANA_REGB_RCLTRIM_Pos)
#define ANA_REGB_RCLTRIM_7            (0x07U << ANA_REGB_RCLTRIM_Pos)
#define ANA_REGB_RCLTRIM_8            (0x08U << ANA_REGB_RCLTRIM_Pos)
#define ANA_REGB_RCLTRIM_9            (0x09U << ANA_REGB_RCLTRIM_Pos)
#define ANA_REGB_RCLTRIM_10           (0x0AU << ANA_REGB_RCLTRIM_Pos)
#define ANA_REGB_RCLTRIM_11           (0x0BU << ANA_REGB_RCLTRIM_Pos)
#define ANA_REGB_RCLTRIM_12           (0x0CU << ANA_REGB_RCLTRIM_Pos)
#define ANA_REGB_RCLTRIM_13           (0x0DU << ANA_REGB_RCLTRIM_Pos)
#define ANA_REGB_RCLTRIM_14           (0x0EU << ANA_REGB_RCLTRIM_Pos)
#define ANA_REGB_RCLTRIM_15           (0x0FU << ANA_REGB_RCLTRIM_Pos)
#define ANA_REGB_RCLTRIM_16           (0x10U << ANA_REGB_RCLTRIM_Pos)
#define ANA_REGB_RCLTRIM_17           (0x11U << ANA_REGB_RCLTRIM_Pos)
#define ANA_REGB_RCLTRIM_18           (0x12U << ANA_REGB_RCLTRIM_Pos)
#define ANA_REGB_RCLTRIM_19           (0x13U << ANA_REGB_RCLTRIM_Pos)
#define ANA_REGB_RCLTRIM_20           (0x14U << ANA_REGB_RCLTRIM_Pos)
#define ANA_REGB_RCLTRIM_21           (0x15U << ANA_REGB_RCLTRIM_Pos)
#define ANA_REGB_RCLTRIM_22           (0x16U << ANA_REGB_RCLTRIM_Pos)
#define ANA_REGB_RCLTRIM_23           (0x17U << ANA_REGB_RCLTRIM_Pos)
#define ANA_REGB_RCLTRIM_24           (0x18U << ANA_REGB_RCLTRIM_Pos)
#define ANA_REGB_RCLTRIM_25           (0x19U << ANA_REGB_RCLTRIM_Pos)
#define ANA_REGB_RCLTRIM_26           (0x1AU << ANA_REGB_RCLTRIM_Pos)
#define ANA_REGB_RCLTRIM_27           (0x1BU << ANA_REGB_RCLTRIM_Pos)
#define ANA_REGB_RCLTRIM_28           (0x1CU << ANA_REGB_RCLTRIM_Pos)
#define ANA_REGB_RCLTRIM_29           (0x1DU << ANA_REGB_RCLTRIM_Pos)
#define ANA_REGB_RCLTRIM_30           (0x1EU << ANA_REGB_RCLTRIM_Pos)
#define ANA_REGB_RCLTRIM_31           (0x1FU << ANA_REGB_RCLTRIM_Pos)

/**************  Bits definition for ANA_REGC register       ******************/
#define ANA_REGC_RCHTRIM_Pos          (0U)                                     
#define ANA_REGC_RCHTRIM_Msk          (0x3FU << ANA_REGC_RCHTRIM_Pos)          /*!< 0x0000003F */
#define ANA_REGC_RCHTRIM               ANA_REGC_RCHTRIM_Msk                    /*!< Trimming of 6.55364MHz RC */ 
#define ANA_REGC_RCHTRIM_0            (0x00U << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_1            (0x01U << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_2            (0x02U << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_3            (0x03U << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_4            (0x04U << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_5            (0x05U << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_6            (0x06U << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_7            (0x07U << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_8            (0x08U << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_9            (0x09U << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_10           (0x0AU << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_11           (0x0BU << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_12           (0x0CU << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_13           (0x0DU << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_14           (0x0EU << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_15           (0x0FU << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_16           (0x10U << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_17           (0x11U << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_18           (0x12U << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_19           (0x13U << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_20           (0x14U << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_21           (0x15U << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_22           (0x16U << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_23           (0x17U << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_24           (0x18U << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_25           (0x19U << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_26           (0x1AU << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_27           (0x1BU << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_28           (0x1CU << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_29           (0x1DU << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_30           (0x1EU << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_31           (0x1FU << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_32           (0x20U << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_33           (0x21U << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_34           (0x22U << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_35           (0x23U << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_36           (0x24U << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_37           (0x25U << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_38           (0x26U << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_39           (0x27U << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_40           (0x28U << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_41           (0x29U << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_42           (0x2AU << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_43           (0x2BU << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_44           (0x2CU << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_45           (0x2DU << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_46           (0x2EU << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_47           (0x2FU << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_48           (0x30U << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_49           (0x31U << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_50           (0x32U << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_51           (0x33U << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_52           (0x34U << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_53           (0x35U << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_54           (0x36U << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_55           (0x37U << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_56           (0x38U << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_57           (0x39U << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_58           (0x3AU << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_59           (0x3BU << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_60           (0x3CU << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_61           (0x3DU << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_62           (0x3EU << ANA_REGC_RCHTRIM_Pos)
#define ANA_REGC_RCHTRIM_63           (0x3FU << ANA_REGC_RCHTRIM_Pos)

/**************  Bits definition for ANA_REGD register       ******************/
#define ANA_REGD_DVCCTRIM_Pos        (0U)                                     
#define ANA_REGD_DVCCTRIM_Msk        (0x7U << ANA_REGD_DVCCTRIM_Pos)         /*!< 0x00000007 */
#define ANA_REGD_DVCCTRIM             ANA_REGD_DVCCTRIM_Msk                  /*!< Trimming of DVCC */ 
#define ANA_REGD_DVCCTRIM_0          (0x0U << ANA_REGD_DVCCTRIM_Pos)
#define ANA_REGD_DVCCTRIM_1          (0x1U << ANA_REGD_DVCCTRIM_Pos)
#define ANA_REGD_DVCCTRIM_2          (0x2U << ANA_REGD_DVCCTRIM_Pos)
#define ANA_REGD_DVCCTRIM_3          (0x3U << ANA_REGD_DVCCTRIM_Pos)
#define ANA_REGD_DVCCTRIM_4          (0x4U << ANA_REGD_DVCCTRIM_Pos)
#define ANA_REGD_DVCCTRIM_5          (0x5U << ANA_REGD_DVCCTRIM_Pos)
#define ANA_REGD_DVCCTRIM_6          (0x6U << ANA_REGD_DVCCTRIM_Pos)
#define ANA_REGD_DVCCTRIM_7          (0x7U << ANA_REGD_DVCCTRIM_Pos)
#define ANA_REGD_AVCCTRIM_Pos        (3U)                                     
#define ANA_REGD_AVCCTRIM_Msk        (0x7U << ANA_REGD_AVCCTRIM_Pos)         /*!< 0x00000038 */
#define ANA_REGD_AVCCTRIM             ANA_REGD_AVCCTRIM_Msk                  /*!< Trimming of AVCC */ 
#define ANA_REGD_AVCCTRIM_0          (0x0U << ANA_REGD_AVCCTRIM_Pos)
#define ANA_REGD_AVCCTRIM_1          (0x1U << ANA_REGD_AVCCTRIM_Pos)
#define ANA_REGD_AVCCTRIM_2          (0x2U << ANA_REGD_AVCCTRIM_Pos)
#define ANA_REGD_AVCCTRIM_3          (0x3U << ANA_REGD_AVCCTRIM_Pos)
#define ANA_REGD_AVCCTRIM_4          (0x4U << ANA_REGD_AVCCTRIM_Pos)
#define ANA_REGD_AVCCTRIM_5          (0x5U << ANA_REGD_AVCCTRIM_Pos)
#define ANA_REGD_AVCCTRIM_6          (0x6U << ANA_REGD_AVCCTRIM_Pos)
#define ANA_REGD_AVCCTRIM_7          (0x7U << ANA_REGD_AVCCTRIM_Pos)
#define ANA_REGD_VREFTRIM_Pos         (6U)                                     
#define ANA_REGD_VREFTRIM_Msk         (0x3U << ANA_REGD_VREFTRIM_Pos)          /*!< 0x000000C0 */
#define ANA_REGD_VREFTRIM              ANA_REGD_VREFTRIM_Msk                   /*!< Trimming of VREF, which will affect DVCC/33’s output by same ratio */ 
#define ANA_REGD_VREFTRIM_0           (0x0U << ANA_REGD_VREFTRIM_Pos)
#define ANA_REGD_VREFTRIM_1           (0x1U << ANA_REGD_VREFTRIM_Pos)
#define ANA_REGD_VREFTRIM_2           (0x2U << ANA_REGD_VREFTRIM_Pos)
#define ANA_REGD_VREFTRIM_3           (0x3U << ANA_REGD_VREFTRIM_Pos)

/**************  Bits definition for ANA_REGE register       ******************/
#define ANA_REGE_REST_Pos             (0U)                                     
#define ANA_REGE_REST_Msk             (0x7U << ANA_REGE_REST_Pos)              /*!< 0x00000007 */
#define ANA_REGE_REST                  ANA_REGE_REST_Msk                       /*!< Fine trimming of bandgap */ 
#define ANA_REGE_REST_0               (0x0U << ANA_REGE_REST_Pos)
#define ANA_REGE_REST_1               (0x1U << ANA_REGE_REST_Pos)
#define ANA_REGE_REST_2               (0x2U << ANA_REGE_REST_Pos)
#define ANA_REGE_REST_3               (0x3U << ANA_REGE_REST_Pos)
#define ANA_REGE_REST_4               (0x4U << ANA_REGE_REST_Pos)
#define ANA_REGE_REST_5               (0x5U << ANA_REGE_REST_Pos)
#define ANA_REGE_REST_6               (0x6U << ANA_REGE_REST_Pos)
#define ANA_REGE_REST_7               (0x7U << ANA_REGE_REST_Pos)
#define ANA_REGE_RESTL_Pos            (4U)                                     
#define ANA_REGE_RESTL_Msk            (0x3U << ANA_REGE_RESTL_Pos)             /*!< 0x00000018 */
#define ANA_REGE_RESTL                 ANA_REGE_RESTL_Msk                      /*!< Coarse  trimming of bandgap */ 
#define ANA_REGE_RESTL_0              (0x0U << ANA_REGE_RESTL_Pos)
#define ANA_REGE_RESTL_1              (0x1U << ANA_REGE_RESTL_Pos)
#define ANA_REGE_RESTL_2              (0x2U << ANA_REGE_RESTL_Pos)
#define ANA_REGE_RESTL_3              (0x3U << ANA_REGE_RESTL_Pos)
#define ANA_REGE_RESTD_Pos            (6U)
#define ANA_REGE_RESTD_Msk            (0x1U << ANA_REGE_RESTD_Pos)
#define ANA_REGE_RESTD                 ANA_REGE_RESTD_Msk
/**************  Bits definition for ANA_REGF register       ******************/
//#define ANA_REGF_TRB_Pos              (0U)                                     
//#define ANA_REGF_TRB_Msk              (0x3U << ANA_REGF_TRB_Pos)               /*!< 0x00000003 */
//#define ANA_REGF_TRB                   ANA_REGF_TRB_Msk                        /*!< Bias voltage trim for ADCs */ 
#define ANA_REGF_AVCCO_EN_Pos         (2U)
#define ANA_REGF_AVCCO_EN_Msk         (0x1U << ANA_REGF_AVCCO_EN_Pos) 
#define ANA_REGF_AVCCO_EN              ANA_REGF_AVCCO_EN_Msk
#define ANA_REGF_PDNADT_Pos           (3U)
#define ANA_REGF_PDNADT_Msk           (0x1U << ANA_REGF_PDNADT_Pos)   
#define ANA_REGF_PDNADT                ANA_REGF_PDNADT_Msk 
#define ANA_REGF_SELADT_Pos           (4U)
#define ANA_REGF_SELADT_Msk           (0x1U << ANA_REGF_SELADT_Pos) 
#define ANA_REGF_SELADT                ANA_REGF_SELADT_Msk 
#define ANA_REGF_ADTREF1SEL_Pos       (5U)
#define ANA_REGF_ADTREF1SEL_Msk       (0x1U << ANA_REGF_ADTREF1SEL_Pos) 
#define ANA_REGF_ADTREF1SEL            ANA_REGF_ADTREF1SEL_Msk
#define ANA_REGF_ADTREF2SEL_Pos       (6U)
#define ANA_REGF_ADTREF2SEL_Msk       (0x1U << ANA_REGF_ADTREF2SEL_Pos) 
#define ANA_REGF_ADTREF2SEL            ANA_REGF_ADTREF2SEL_Msk
#define ANA_REGF_ADTREF3SEL_Pos       (7U)
#define ANA_REGF_ADTREF3SEL_Msk       (0x1U << ANA_REGF_ADTREF3SEL_Pos) 
#define ANA_REGF_ADTREF3SEL            ANA_REGF_ADTREF3SEL_Msk
///**************  Bits definition for ANA_REG10 register      ******************/
//#define ANA_REG10_Pos                 (0U)                                     
//#define ANA_REG10_Msk                 (0xFFU << ANA_REG10_Pos)                 /*!< 0x000000FF */
//#define ANA_REG10                      ANA_REG10_Msk                           /*!< Analog control register 16 */ 
//
///**************  Bits definition for ANA_REG11 register      ******************/
//#define ANA_REG11_Pos                 (0U)                                     
//#define ANA_REG11_Msk                 (0xFFU << ANA_REG11_Pos)                 /*!< 0x000000FF */
//#define ANA_REG11                      ANA_REG11_Msk                           /*!< Analog control register 17 */ 
//
///**************  Bits definition for ANA_REG12 register      ******************/
//#define ANA_REG12_Pos                 (0U)                                     
//#define ANA_REG12_Msk                 (0xFFU << ANA_REG12_Pos)                 /*!< 0x000000FF */
//#define ANA_REG12                      ANA_REG12_Msk                           /*!< Analog control register 18 */ 

/**************  Bits definition for ANA_CTRL register       ******************/
#define ANA_CTRL_COMP1_SEL_Pos        (0U)                                     
#define ANA_CTRL_COMP1_SEL_Msk        (0x3U << ANA_CTRL_COMP1_SEL_Pos)         /*!< 0x00000003 */
#define ANA_CTRL_COMP1_SEL             ANA_CTRL_COMP1_SEL_Msk                  /*!< This register is used to control the interrupt and wake-up signal generation of COMP1 */ 
#define ANA_CTRL_COMP1_SEL_0          (0x0U << ANA_CTRL_COMP1_SEL_Pos)
#define ANA_CTRL_COMP1_SEL_1          (0x1U << ANA_CTRL_COMP1_SEL_Pos)
#define ANA_CTRL_COMP1_SEL_2          (0x2U << ANA_CTRL_COMP1_SEL_Pos)
#define ANA_CTRL_COMP1_SEL_3          (0x3U << ANA_CTRL_COMP1_SEL_Pos)
#define ANA_CTRL_COMP2_SEL_Pos        (2U)                                     
#define ANA_CTRL_COMP2_SEL_Msk        (0x3U << ANA_CTRL_COMP2_SEL_Pos)         /*!< 0x0000000C */
#define ANA_CTRL_COMP2_SEL             ANA_CTRL_COMP2_SEL_Msk                  /*!< This register is used to control the interrupt and wake-up signal generation of COMP2 */ 
//#define ANA_CTRL_PORLOFF_Pos          (4U)                                    
//#define ANA_CTRL_PORLOFF_Msk          (0x1U << ANA_CTRL_PORLOFF_Pos)           /*!< 0x00000010 */
//#define ANA_CTRL_PORLOFF               ANA_CTRL_PORLOFF_Msk                    /*!< This register can disable the PORL reset */ 
//#define ANA_CTRL_PORHOFF_Pos          (5U)                                     
//#define ANA_CTRL_PORHOFF_Msk          (0x1U << ANA_CTRL_PORHOFF_Pos)           /*!< 0x00000020 */
//#define ANA_CTRL_PORHOFF               ANA_CTRL_PORHOFF_Msk                    /*!< This register can disable the PORH reset */ 
#define ANA_CTRL_PDNS_Pos             (6U)                                     
#define ANA_CTRL_PDNS_Msk             (0x1U << ANA_CTRL_PDNS_Pos)              /*!< 0x00000040 */
#define ANA_CTRL_PDNS                  ANA_CTRL_PDNS_Msk                       /*!< This register is used to set the deep sleep behavior when VDCIN is not drop */ 
//#define ANA_CTRL_DVCCSW_Pos          (7U)                                     
//#define ANA_CTRL_DVCCSW_Msk          (0x1U << ANA_CTRL_DVCCSW_Pos)           /*!< 0x00000080 */
//#define ANA_CTRL_DVCCSW               ANA_CTRL_DVCCSW_Msk                    /*!< DVCC auto switch enable at sleep or deep-sleep mode */ 
#define ANA_CTRL_RCHTGT_Pos           (8U)                                     
#define ANA_CTRL_RCHTGT_Msk           (0xFFU << ANA_CTRL_RCHTGT_Pos)           /*!< 0x0000FF00 */
#define ANA_CTRL_RCHTGT                ANA_CTRL_RCHTGT_Msk                     /*!< RCH auto0calibration target register.  This register is used to store the target value of RCH */ 
//#define ANA_CTRL_DVCCSWSEL_Pos       (16U)                                     
//#define ANA_CTRL_DVCCSWSEL_Msk       (0x3U << ANA_CTRL_DVCCSWSEL_Pos)        /*!< 0x00030000 */
//#define ANA_CTRL_DVCCSWSEL            ANA_CTRL_DVCCSWSEL_Msk                 /*!< DVCC auto-switching setting at sleep mode or deep-sleep mode */ 
//#define ANA_CTRL_DVCCSWSEL_0         (0x0U << ANA_CTRL_DVCCSWSEL_Pos)
//#define ANA_CTRL_DVCCSWSEL_1         (0x1U << ANA_CTRL_DVCCSWSEL_Pos)
//#define ANA_CTRL_DVCCSWSEL_2         (0x2U << ANA_CTRL_DVCCSWSEL_Pos)
//#define ANA_CTRL_DVCCSWSEL_3         (0x3U << ANA_CTRL_DVCCSWSEL_Pos)
#define ANA_CTRL_CMP1DEB_Pos          (20U)                                     
#define ANA_CTRL_CMP1DEB_Msk          (0x3U << ANA_CTRL_CMP1DEB_Pos)           /*!< 0x00300000 */
#define ANA_CTRL_CMP1DEB               ANA_CTRL_CMP1DEB_Msk                    /*!< Comparator 1 de-bounce control register */ 
#define ANA_CTRL_CMP1DEB_0            (0x0U << ANA_CTRL_CMP1DEB_Pos)
#define ANA_CTRL_CMP1DEB_1            (0x1U << ANA_CTRL_CMP1DEB_Pos)
#define ANA_CTRL_CMP1DEB_2            (0x2U << ANA_CTRL_CMP1DEB_Pos)
#define ANA_CTRL_CMP1DEB_3            (0x3U << ANA_CTRL_CMP1DEB_Pos)
#define ANA_CTRL_CMP2DEB_Pos          (22U)                                     
#define ANA_CTRL_CMP2DEB_Msk          (0x3U << ANA_CTRL_CMP2DEB_Pos)           /*!< 0x00C00000 */
#define ANA_CTRL_CMP2DEB               ANA_CTRL_CMP2DEB_Msk                    /*!< Comparator 2 de-bounce control register */ 
#define ANA_CTRL_PWRDROPDEB_Pos       (24U)                                     
#define ANA_CTRL_PWRDROPDEB_Msk       (0x3U << ANA_CTRL_PWRDROPDEB_Pos)        /*!< 0x03000000 */
#define ANA_CTRL_PWRDROPDEB            ANA_CTRL_PWRDROPDEB_Msk                 /*!< Power drop de-bounce control register */ 
#define ANA_CTRL_PWRDROPDEB_0         (0x0U << ANA_CTRL_PWRDROPDEB_Pos)
#define ANA_CTRL_PWRDROPDEB_1         (0x1U << ANA_CTRL_PWRDROPDEB_Pos)
#define ANA_CTRL_PWRDROPDEB_2         (0x2U << ANA_CTRL_PWRDROPDEB_Pos)
#define ANA_CTRL_PWRDROPDEB_3         (0x3U << ANA_CTRL_PWRDROPDEB_Pos)
#define ANA_CTRL_PDNS2_Pos            (26U)
#define ANA_CTRL_PDNS2_Msk            (0x1U << ANA_CTRL_PDNS2_Pos)             /*!< 0x04000000 */
#define ANA_CTRL_PDNS2                 ANA_CTRL_PDNS2_Msk                      /*!< This register is used to set the deep sleep behavior when VDD is not drop */
//#define ANA_CTRL_ANATEST_Pos          (28U)                                    
//#define ANA_CTRL_ANATEST_Msk          (0xFU << ANA_CTRL_ANATEST_Pos)           /*!< 0xF0000000 */
//#define ANA_CTRL_ANATEST               ANA_CTRL_ANATEST_Msk                    /*!< This register is used to control the internal analog test signal.  When one of the internal signal is selected, the hardware will use IOA[15] as input to simulation the behavior of the internal signal */ 

/**************  Bits definition for ANA_COMPOUT register    ******************/
#define ANA_COMPOUT_LOCKH_Pos         (0U)                                     
#define ANA_COMPOUT_LOCKH_Msk         (0x1U << ANA_COMPOUT_LOCKH_Pos)          /*!< 0x00000001 */
#define ANA_COMPOUT_LOCKH              ANA_COMPOUT_LOCKH_Msk                   /*!< PLLH lock status */ 
#define ANA_COMPOUT_LOCKL_Pos         (1U)                                     
#define ANA_COMPOUT_LOCKL_Msk         (0x1U << ANA_COMPOUT_LOCKL_Pos)          /*!< 0x00000002 */
#define ANA_COMPOUT_LOCKL              ANA_COMPOUT_LOCKL_Msk                   /*!< PLLL lock status */ 
#define ANA_COMPOUT_COMP1_Pos         (2U)                                     
#define ANA_COMPOUT_COMP1_Msk         (0x1U << ANA_COMPOUT_COMP1_Pos)          /*!< 0x00000004 */
#define ANA_COMPOUT_COMP1              ANA_COMPOUT_COMP1_Msk                   /*!< This bit shows the output of comparator 1 */ 
#define ANA_COMPOUT_COMP2_Pos         (3U)                                     
#define ANA_COMPOUT_COMP2_Msk         (0x1U << ANA_COMPOUT_COMP2_Pos)          /*!< 0x00000008 */
#define ANA_COMPOUT_COMP2              ANA_COMPOUT_COMP2_Msk                   /*!< This bit shows the output of comparator 2 */ 
//#define ANA_COMPOUT_MAINPDN_Pos       (4U)                                     
//#define ANA_COMPOUT_MAINPDN_Msk       (0x1U << ANA_COMPOUT_MAINPDN_Pos)        /*!< 0x00000010 */
//#define ANA_COMPOUT_MAINPDN            ANA_COMPOUT_MAINPDN_Msk                 /*!< Main power power-down status */ 
//#define ANA_COMPOUT_BATRTCPDN_Pos     (5U)                                     
//#define ANA_COMPOUT_BATRTCPDN_Msk     (0x1U << ANA_COMPOUT_BATRTCPDN_Pos)      /*!< 0x00000020 */
//#define ANA_COMPOUT_BATRTCPDN          ANA_COMPOUT_BATRTCPDN_Msk               /*!< RTC power power-down status */ 
//#define ANA_COMPOUT_MAINPRSTS_Pos     (6U)                                     
//#define ANA_COMPOUT_MAINPRSTS_Msk     (0x1U << ANA_COMPOUT_MAINPRSTS_Pos)        /*!< 0x00000040 */
//#define ANA_COMPOUT_MAINPRSTS          ANA_COMPOUT_MAINPRSTS_Msk                 /*!< This bit show the status of MAINPRSTS */ 
#define ANA_COMPOUT_VDDALARM_Pos      (7U)                                     
#define ANA_COMPOUT_VDDALARM_Msk      (0x1U << ANA_COMPOUT_VDDALARM_Pos)     /*!< 0x00000080 */
#define ANA_COMPOUT_VDDALARM           ANA_COMPOUT_VDDALARM_Msk              /*!< This bit shows the output of POWALARM */ 
#define ANA_COMPOUT_VDCINDROP_Pos     (8U)                                     
#define ANA_COMPOUT_VDCINDROP_Msk     (0x1U << ANA_COMPOUT_VDCINDROP_Pos)      /*!< 0x00000100 */
#define ANA_COMPOUT_VDCINDROP          ANA_COMPOUT_VDCINDROP_Msk               /*!< VDCIN drop status */ 
#define ANA_COMPOUT_AVCCLV_Pos       (10U)                                     
#define ANA_COMPOUT_AVCCLV_Msk       (0x1U << ANA_COMPOUT_AVCCLV_Pos)        /*!< 0x00000400 */
#define ANA_COMPOUT_AVCCLV            ANA_COMPOUT_AVCCLV_Msk                 /*!< AVCC low power status */ 
#define ANA_COMPOUT_TADCO_Pos         (14UL)
#define ANA_COMPOUT_TADCO_Msk         (0x03UL << ANA_COMPOUT_TADCO_Pos)
#define ANA_COMPOUT_TADCO              ANA_COMPOUT_TADCO_Msk

///**************  Bits definition for ANA_VERSION register    ******************/
//#define ANA_VERSION_VERSION_Pos       (0U)                                     
//#define ANA_VERSION_VERSION_Msk       (0x3U << ANA_VERSION_VERSION_Pos)        /*!< 0x00000003 */
//#define ANA_VERSION_VERSION            ANA_VERSION_VERSION_Msk                 /*!< This bit shows the version information of analog module */ 

///**************  Bits definition for ANA_ADCSTATE register   ******************/
//#define ANA_ADCSTATE_ADCSTATE_Pos     (0U)                                     
//#define ANA_ADCSTATE_ADCSTATE_Msk     (0x7U << ANA_ADCSTATE_ADCSTATE_Pos)      /*!< 0x00000007 */
//#define ANA_ADCSTATE_ADCSTATE          ANA_ADCSTATE_ADCSTATE_Msk               /*!< This bit shows the ADC state of ADC CIC filter */ 

/**************  Bits definition for ANA_INTSTS register     ******************/
#define ANA_INTSTS_Msk                (0x1DFFUL)
#define ANA_INTSTS_INTSTS0_Pos        (0U)                                     
#define ANA_INTSTS_INTSTS0_Msk        (0x1U << ANA_INTSTS_INTSTS0_Pos)         /*!< 0x00000001 */
#define ANA_INTSTS_INTSTS0             ANA_INTSTS_INTSTS0_Msk                  /*!< Interrupt flag of manual ADC conversion done */ 
#define ANA_INTSTS_INTSTS1_Pos        (1U)                                     
#define ANA_INTSTS_INTSTS1_Msk        (0x1U << ANA_INTSTS_INTSTS1_Pos)         /*!< 0x00000002 */
#define ANA_INTSTS_INTSTS1             ANA_INTSTS_INTSTS1_Msk                  /*!< Interrupt flag of auto ADC conversion done */ 
#define ANA_INTSTS_INTSTS2_Pos        (2U)                                     
#define ANA_INTSTS_INTSTS2_Msk        (0x1U << ANA_INTSTS_INTSTS2_Pos)         /*!< 0x00000004 */
#define ANA_INTSTS_INTSTS2             ANA_INTSTS_INTSTS2_Msk                  /*!< Interrupt flag of COMP1, the interrupt generate condition is controlled by COMP1_SEL */ 
#define ANA_INTSTS_INTSTS3_Pos        (3U)                                     
#define ANA_INTSTS_INTSTS3_Msk        (0x1U << ANA_INTSTS_INTSTS3_Pos)         /*!< 0x00000008 */
#define ANA_INTSTS_INTSTS3             ANA_INTSTS_INTSTS3_Msk                  /*!< Interrupt flag of COMP2, the interrupt generate condition is controlled by COMP2_SEL */ 
//#define ANA_INTSTS_INTSTS4_Pos        (4U)                                     
//#define ANA_INTSTS_INTSTS4_Msk        (0x1U << ANA_INTSTS_INTSTS4_Pos)         /*!< 0x00000010 */
//#define ANA_INTSTS_INTSTS4             ANA_INTSTS_INTSTS4_Msk                  /*!< Interrupt flag of MAINPDN, this interrupt will be generated when MAINPDN rising or falling */ 
//#define ANA_INTSTS_INTSTS5_Pos        (5U)                                     
//#define ANA_INTSTS_INTSTS5_Msk        (0x1U << ANA_INTSTS_INTSTS5_Pos)         /*!< 0x00000020 */
//#define ANA_INTSTS_INTSTS5             ANA_INTSTS_INTSTS5_Msk                  /*!< Interrupt flag of RTCPDN, this interrupt will be generated when RTCPDN rising or falling */ 
//#define ANA_INTSTS_INTSTS6_Pos        (6U)                                     
//#define ANA_INTSTS_INTSTS6_Msk        (0x1U << ANA_INTSTS_INTSTS6_Pos)         /*!< 0x00000040 */
//#define ANA_INTSTS_INTSTS6             ANA_INTSTS_INTSTS6_Msk                  /*!< Interrupt flag of SWT2BAT, this interrupt will be generated when SWT2BAT rising or falling */ 
#define ANA_INTSTS_INTSTS7_Pos        (7U)                                     
#define ANA_INTSTS_INTSTS7_Msk        (0x1U << ANA_INTSTS_INTSTS7_Pos)         /*!< 0x00000080 */
#define ANA_INTSTS_INTSTS7             ANA_INTSTS_INTSTS7_Msk                  /*!< Interrupt flag of POWALARMQPWRDN, this interrupt will be generated when POWALARM QPWRDN rising or falling */ 
#define ANA_INTSTS_INTSTS8_Pos        (8U)                                     
#define ANA_INTSTS_INTSTS8_Msk        (0x1U << ANA_INTSTS_INTSTS8_Pos)         /*!< 0x00000100 */
#define ANA_INTSTS_INTSTS8             ANA_INTSTS_INTSTS8_Msk                  /*!< Interrupt flag of PWRDROP, this interrupt will be generated when PWRDOP rising or falling */ 
#define ANA_INTSTS_INTSTS10_Pos       (10U)                                     
#define ANA_INTSTS_INTSTS10_Msk       (0x1U << ANA_INTSTS_INTSTS10_Pos)        /*!< 0x00000400 */
#define ANA_INTSTS_INTSTS10            ANA_INTSTS_INTSTS10_Msk                 /*!< Interrupt flag of POWLV, this interrupt will be generated when POWLV rising or falling */ 
#define ANA_INTSTS_INTSTS11_Pos       (11U)                                     
#define ANA_INTSTS_INTSTS11_Msk       (0x1U << ANA_INTSTS_INTSTS11_Pos)        /*!< 0x00000800 */
#define ANA_INTSTS_INTSTS11            ANA_INTSTS_INTSTS11_Msk                 /*!< Interrupt flag of sleep mode entry under PWRDROP is 0(i.e. VDCIN higher than threshold), this interrupt will be generated when PWRDROP is 0 and the entry of sleep or deep-sleep modes are detected.  Programmer can enable this interrupt to force CPU wake-up from sleep or deep-sleep mode when PWRDROP is 0 */ 
#define ANA_INTSTS_INTSTS12_Pos       (12U)                                     
#define ANA_INTSTS_INTSTS12_Msk       (0x1U << ANA_INTSTS_INTSTS12_Pos)        /*!< 0x00001000 */
#define ANA_INTSTS_INTSTS12            ANA_INTSTS_INTSTS12_Msk                 /*!< ANA_REGx error flag.  This interrupt is used to detect the error status of ANA_REGx, an automatically check0sum and parity check is applied to ANA_REGx, when external noise cause by ESD or other problem affect the setting of ANA_REGx, this interrupt will be asserted and programmer can use this flag to determine if it is necessary to recover the setting in the ANA_REGx */ 
#define ANA_INTSTS_INTSTS13_Pos       (13U)
#define ANA_INTSTS_INTSTS13_Msk       (0x1U << ANA_INTSTS_INTSTS13_Pos)
#define ANA_INTSTS_INTSTS13            ANA_INTSTS_INTSTS13_Msk

/**************  Bits definition for ANA_INTEN register      ******************/
#define ANA_INTEN_INTEN0_Pos          (0U)                                     
#define ANA_INTEN_INTEN0_Msk          (0x1U << ANA_INTEN_INTEN0_Pos)           /*!< 0x00000001 */
#define ANA_INTEN_INTEN0               ANA_INTEN_INTEN0_Msk                    /*!< Interrupt enable control of manual ADC conversion done */ 
#define ANA_INTEN_INTEN1_Pos          (1U)                                     
#define ANA_INTEN_INTEN1_Msk          (0x1U << ANA_INTEN_INTEN1_Pos)           /*!< 0x00000002 */
#define ANA_INTEN_INTEN1               ANA_INTEN_INTEN1_Msk                    /*!< Interrupt enable control of auto ADC conversion done */ 
#define ANA_INTEN_INTEN2_Pos          (2U)                                     
#define ANA_INTEN_INTEN2_Msk          (0x1U << ANA_INTEN_INTEN2_Pos)           /*!< 0x00000004 */
#define ANA_INTEN_INTEN2               ANA_INTEN_INTEN2_Msk                    /*!< Interrupt and wake-up enable control of COMP1 */ 
#define ANA_INTEN_INTEN3_Pos          (3U)                                     
#define ANA_INTEN_INTEN3_Msk          (0x1U << ANA_INTEN_INTEN3_Pos)           /*!< 0x00000008 */
#define ANA_INTEN_INTEN3               ANA_INTEN_INTEN3_Msk                    /*!< Interrupt and wake-up enable control of COMP2 */ 
//#define ANA_INTEN_INTEN4_Pos          (4U)                                     
//#define ANA_INTEN_INTEN4_Msk          (0x1U << ANA_INTEN_INTEN4_Pos)           /*!< 0x00000010 */
//#define ANA_INTEN_INTEN4               ANA_INTEN_INTEN4_Msk                    /*!< Interrupt and wake-up enable control of MAINPDN falling */ 
//#define ANA_INTEN_INTEN5_Pos          (5U)                                     
//#define ANA_INTEN_INTEN5_Msk          (0x1U << ANA_INTEN_INTEN5_Pos)           /*!< 0x00000020 */
//#define ANA_INTEN_INTEN5               ANA_INTEN_INTEN5_Msk                    /*!< Interrupt and wake-up enable control of RTCPDN falling */ 
//#define ANA_INTEN_INTEN6_Pos          (6U)                                     
//#define ANA_INTEN_INTEN6_Msk          (0x1U << ANA_INTEN_INTEN6_Pos)           /*!< 0x00000040 */
//#define ANA_INTEN_INTEN6               ANA_INTEN_INTEN6_Msk                    /*!< Interrupt and wake-up enable control of SWT2BAT */ 
#define ANA_INTEN_INTEN7_Pos          (7U)                                     
#define ANA_INTEN_INTEN7_Msk          (0x1U << ANA_INTEN_INTEN7_Pos)           /*!< 0x00000080 */
#define ANA_INTEN_INTEN7               ANA_INTEN_INTEN7_Msk                    /*!< Interrupt and wake-up enable control of POWALARM */ 
#define ANA_INTEN_INTEN8_Pos          (8U)                                     
#define ANA_INTEN_INTEN8_Msk          (0x1U << ANA_INTEN_INTEN8_Pos)           /*!< 0x00000100 */
#define ANA_INTEN_INTEN8               ANA_INTEN_INTEN8_Msk                    /*!< Interrupt and wake-up enable control of PWRDROP */ 
#define ANA_INTEN_INTEN10_Pos         (10U)                                     
#define ANA_INTEN_INTEN10_Msk         (0x1U << ANA_INTEN_INTEN10_Pos)          /*!< 0x00000400 */
#define ANA_INTEN_INTEN10              ANA_INTEN_INTEN10_Msk                   /*!< Interrupt and wake-up enable control of POWLV */ 
#define ANA_INTEN_INTEN11_Pos         (11U)                                     
#define ANA_INTEN_INTEN11_Msk         (0x1U << ANA_INTEN_INTEN11_Pos)          /*!< 0x00000800 */
#define ANA_INTEN_INTEN11              ANA_INTEN_INTEN11_Msk                   /*!< Interrupt and wake-up enable control of sleep mode entry */ 
#define ANA_INTEN_INTEN12_Pos         (12U)                                     
#define ANA_INTEN_INTEN12_Msk         (0x1U << ANA_INTEN_INTEN12_Pos)          /*!< 0x00001000 */
#define ANA_INTEN_INTEN12              ANA_INTEN_INTEN12_Msk                   /*!< Interrupt and wake-up enable control of ANA_REGx error */ 
#define ANA_INTEN_INTEN13_Pos         (13U)                                     
#define ANA_INTEN_INTEN13_Msk         (0x1U << ANA_INTEN_INTEN13_Pos)          /*!< 0x00001000 */
#define ANA_INTEN_INTEN13              ANA_INTEN_INTEN13_Msk 

/**************  Bits definition for ANA_ADCCTRL register    ******************/
#define ANA_ADCCTRL_MCH_Pos           (0U)                                     
#define ANA_ADCCTRL_MCH_Msk           (0xFU << ANA_ADCCTRL_MCH_Pos)            /*!< 0x0000000F */
#define ANA_ADCCTRL_MCH                ANA_ADCCTRL_MCH_Msk                     /*!< Manual ADC channel control */ 
#define ANA_ADCCTRL_ACH_Pos           (4U)                                     
#define ANA_ADCCTRL_ACH_Msk           (0xFU << ANA_ADCCTRL_ACH_Pos)            /*!< 0x000000F0 */
#define ANA_ADCCTRL_ACH                ANA_ADCCTRL_ACH_Msk                     /*!< Auto ADC channel control */ 
#define ANA_ADCCTRL_CLKDIV_Pos        (8U)                                     
#define ANA_ADCCTRL_CLKDIV_Msk        (0xFU << ANA_ADCCTRL_CLKDIV_Pos)         /*!< 0x00000700 */
#define ANA_ADCCTRL_CLKDIV             ANA_ADCCTRL_CLKDIV_Msk                  /*!< ADC clock divider, the ADC main clock is necessary to be 3.2768MHz, so when different clock source is selected, it is necessary to set correct clock division rate to generate ADC clock */ 
#define ANA_ADCCTRL_CLKDIV_1          (0x0U << ANA_ADCCTRL_CLKDIV_Pos)
#define ANA_ADCCTRL_CLKDIV_2          (0x1U << ANA_ADCCTRL_CLKDIV_Pos)
#define ANA_ADCCTRL_CLKDIV_3          (0x2U << ANA_ADCCTRL_CLKDIV_Pos)
#define ANA_ADCCTRL_CLKDIV_4          (0x3U << ANA_ADCCTRL_CLKDIV_Pos)
#define ANA_ADCCTRL_CLKDIV_5          (0x4U << ANA_ADCCTRL_CLKDIV_Pos)
#define ANA_ADCCTRL_CLKDIV_6          (0x5U << ANA_ADCCTRL_CLKDIV_Pos)
#define ANA_ADCCTRL_CLKDIV_7          (0x6U << ANA_ADCCTRL_CLKDIV_Pos)
#define ANA_ADCCTRL_CLKDIV_8          (0x7U << ANA_ADCCTRL_CLKDIV_Pos)
#define ANA_ADCCTRL_CLKDIV_9          (0x8U << ANA_ADCCTRL_CLKDIV_Pos)
#define ANA_ADCCTRL_CLKDIV_10         (0x9U << ANA_ADCCTRL_CLKDIV_Pos)
#define ANA_ADCCTRL_CLKDIV_11         (0xAU << ANA_ADCCTRL_CLKDIV_Pos)
#define ANA_ADCCTRL_CLKDIV_12         (0xBU << ANA_ADCCTRL_CLKDIV_Pos)
#define ANA_ADCCTRL_CLKDIV_13         (0xCU << ANA_ADCCTRL_CLKDIV_Pos)
#define ANA_ADCCTRL_CLKDIV_14         (0xDU << ANA_ADCCTRL_CLKDIV_Pos)
#define ANA_ADCCTRL_CLKDIV_15         (0xEU << ANA_ADCCTRL_CLKDIV_Pos)
#define ANA_ADCCTRL_CLKDIV_16         (0xFU << ANA_ADCCTRL_CLKDIV_Pos)
#define ANA_ADCCTRL_CLKSEL_Pos        (12U)
#define ANA_ADCCTRL_CLKSEL_Msk        (0x1U << ANA_ADCCTRL_CLKSEL_Pos)         /*!< 0x00001000 */
#define ANA_ADCCTRL_CLKSEL             ANA_ADCCTRL_CLKSEL_Msk                  /*!< ADC clock source selection */
#define ANA_ADCCTRL_AEN_Pos           (16U)                                     
#define ANA_ADCCTRL_AEN_Msk           (0x7U << ANA_ADCCTRL_AEN_Pos)            /*!< 0x00070000 */
#define ANA_ADCCTRL_AEN                ANA_ADCCTRL_AEN_Msk                     /*!< Auto ADC conversion enable control register */ 
#define ANA_ADCCTRL_AEN_OFF           (0x0U << ANA_ADCCTRL_AEN_Pos)
#define ANA_ADCCTRL_AEN_TMR0          (0x4U << ANA_ADCCTRL_AEN_Pos)
#define ANA_ADCCTRL_AEN_TMR1          (0x5U << ANA_ADCCTRL_AEN_Pos)
#define ANA_ADCCTRL_AEN_TMR2          (0x6U << ANA_ADCCTRL_AEN_Pos)
#define ANA_ADCCTRL_AEN_TMR3          (0x7U << ANA_ADCCTRL_AEN_Pos)
//#define ANA_ADCCTRL_STOP_Pos          (19U)                                     
//#define ANA_ADCCTRL_STOP_Msk          (0x1U << ANA_ADCCTRL_STOP_Pos)           /*!< 0x00080000 */
//#define ANA_ADCCTRL_STOP               ANA_ADCCTRL_STOP_Msk                    /*!< Force stop current ADC conversion process */ 
#define ANA_ADCCTRL_MMODE_Pos         (20U)                                     
#define ANA_ADCCTRL_MMODE_Msk         (0x1U << ANA_ADCCTRL_MMODE_Pos)          /*!< 0x00100000 */
#define ANA_ADCCTRL_MMODE              ANA_ADCCTRL_MMODE_Msk                   /*!< Manual ADC mode control */ 
#define ANA_ADCCTRL_AMODE_Pos         (21U)                                     
#define ANA_ADCCTRL_AMODE_Msk         (0x1U << ANA_ADCCTRL_AMODE_Pos)          /*!< 0x00200000 */
#define ANA_ADCCTRL_AMODE              ANA_ADCCTRL_AMODE_Msk                   /*!< Auto ADC mode control */ 
#define ANA_ADCCTRL_DSRSEL_Pos        (22U)                                     
#define ANA_ADCCTRL_DSRSEL_Msk        (0x3U << ANA_ADCCTRL_DSRSEL_Pos)         /*!< 0x00C00000 */
#define ANA_ADCCTRL_DSRSEL             ANA_ADCCTRL_DSRSEL_Msk                  /*!< CIC down sampling rate control register.  The higher down-sampling rate, the higher output data stability, and also lower sampling rate */ 
#define ANA_ADCCTRL_DSRSEL_512        (0x0U << ANA_ADCCTRL_DSRSEL_Pos)
#define ANA_ADCCTRL_DSRSEL_256        (0x1U << ANA_ADCCTRL_DSRSEL_Pos)
#define ANA_ADCCTRL_DSRSEL_128        (0x2U << ANA_ADCCTRL_DSRSEL_Pos)
#define ANA_ADCCTRL_DSRSEL_64         (0x3U << ANA_ADCCTRL_DSRSEL_Pos)
#define ANA_ADCCTRL_CICSKIP_Pos       (24U)                                     
#define ANA_ADCCTRL_CICSKIP_Msk       (0x7U << ANA_ADCCTRL_CICSKIP_Pos)        /*!< 0x07000000 */
#define ANA_ADCCTRL_CICSKIP            ANA_ADCCTRL_CICSKIP_Msk                 /*!< CIC output skip control register.  This register is used to control how many samples will be skipped at the beginning of ADC sample.  If CICAON is 1 and the ADC channel is not changed, the CIC output will not be skipped by the ADC controller, this can be used for high speed capture to single channel */ 
#define ANA_ADCCTRL_CICSKIP_4         (0x0U << ANA_ADCCTRL_CICSKIP_Pos)
#define ANA_ADCCTRL_CICSKIP_5         (0x1U << ANA_ADCCTRL_CICSKIP_Pos)
#define ANA_ADCCTRL_CICSKIP_6         (0x2U << ANA_ADCCTRL_CICSKIP_Pos)
#define ANA_ADCCTRL_CICSKIP_7         (0x3U << ANA_ADCCTRL_CICSKIP_Pos)
#define ANA_ADCCTRL_CICSKIP_0         (0x4U << ANA_ADCCTRL_CICSKIP_Pos)
#define ANA_ADCCTRL_CICSKIP_1         (0x5U << ANA_ADCCTRL_CICSKIP_Pos)
#define ANA_ADCCTRL_CICSKIP_2         (0x6U << ANA_ADCCTRL_CICSKIP_Pos)
#define ANA_ADCCTRL_CICSKIP_3         (0x7U << ANA_ADCCTRL_CICSKIP_Pos)
#define ANA_ADCCTRL_CICSCA_Pos        (27U)                                     
#define ANA_ADCCTRL_CICSCA_Msk        (0x1U << ANA_ADCCTRL_CICSCA_Pos)         /*!< 0x08000000 */
#define ANA_ADCCTRL_CICSCA             ANA_ADCCTRL_CICSCA_Msk                  /*!< CIC output scale-down selection */ 
#define ANA_ADCCTRL_CICINV_Pos        (28U)                                     
#define ANA_ADCCTRL_CICINV_Msk        (0x1U << ANA_ADCCTRL_CICINV_Pos)         /*!< 0x10000000 */
#define ANA_ADCCTRL_CICINV             ANA_ADCCTRL_CICINV_Msk                  /*!< CIC filter input inversion */ 
#define ANA_ADCCTRL_CICAON_Pos        (29U)                                     
#define ANA_ADCCTRL_CICAON_Msk        (0x1U << ANA_ADCCTRL_CICAON_Pos)         /*!< 0x20000000 */
#define ANA_ADCCTRL_CICAON             ANA_ADCCTRL_CICAON_Msk                  /*!< CIC filter always on control register */ 
//#define ANA_ADCCTRL_16CH_Pos          (30U)                                     
//#define ANA_ADCCTRL_16CH_Msk          (0x1U << ANA_ADCCTRL_16CH_Pos)           /*!< 0x40000000 */
//#define ANA_ADCCTRL_16CH               ANA_ADCCTRL_16CH_Msk                    /*!< ADC multi channels scan control register */ 
#define ANA_ADCCTRL_MTRIG_Pos         (31U)                                     
#define ANA_ADCCTRL_MTRIG_Msk         (0x1U << ANA_ADCCTRL_MTRIG_Pos)          /*!< 0x80000000 */
#define ANA_ADCCTRL_MTRIG              ANA_ADCCTRL_MTRIG_Msk                   /*!< Manual ADC trigger */ 

/**************  Bits definition for ANA_ADCDATAx register   ******************/
#define ANA_ADCDATA_Pos               (0U)                                     
#define ANA_ADCDATA_Msk               (0xFFFFU << ANA_ADCDATA_Pos)             /*!< 0x0000FFFF */
#define ANA_ADCDATA                    ANA_ADCDATA_Msk                         /*!< The result of ADC conversion will be stored in these registers */ 

/**************  Bits definition for ANA_CMPCNTx register    ******************/
#define ANA_CMPCNT_CNT_Pos            (0U)                                     
#define ANA_CMPCNT_CNT_Msk            (0xFFFFFFFFU << ANA_CMPCNT_CNT_Pos)      /*!< 0xFFFFFFFF */
#define ANA_CMPCNT_CNT                 ANA_CMPCNT_CNT_Msk                      /*!< This register store the happen times of comparator x according to the setting in COMPx_SEL */

/**************  Bits definition for ANA_MISC register    ******************/
//#define ANA_MISC_FORCEPWR2MP_Pos      (1U)
//#define ANA_MISC_FORCEPWR2MP_Msk      (0x1U << ANA_MISC_FORCEPWR2MP_Pos)       /*!< 0x00000002 */
//#define ANA_MISC_FORCEPWR2MP           ANA_MISC_FORCEPWR2MP_Msk                /*!< Force BATRTC feed into VDDIO function when doing RTC auto-calibration control */
#define ANA_MISC_TADCTH_Pos           (4U)
#define ANA_MISC_TADCTH_Msk           (0x03UL << ANA_MISC_TADCTH_Pos)
#define ANA_MISC_TADCTH                ANA_MISC_TADCTH_Msk
#define ANA_MISC_TADCTH_0             (0x00UL << ANA_MISC_TADCTH_Pos)
#define ANA_MISC_TADCTH_1             (0x01UL << ANA_MISC_TADCTH_Pos)
#define ANA_MISC_TADCTH_2             (0x02UL << ANA_MISC_TADCTH_Pos)
#define ANA_MISC_TADCTH_3             (0x03UL << ANA_MISC_TADCTH_Pos)

/******************************************************************************/
/*                                                                            */
/*                         RTC controller (RTC)                               */
/*                                                                            */
/******************************************************************************/

/**************  Bits definition for RTC_SEC register        ******************/
#define RTC_SEC_Pos                   (0U)                                     
#define RTC_SEC_Msk                   (0x7FU << RTC_SEC_Pos)                   /*!< 0x0000007F */
#define RTC_SEC_SEC                    RTC_SEC_Msk                             /*!< RTC second register */ 

/**************  Bits definition for RTC_MIN register        ******************/
#define RTC_MIN_Pos                   (0U)                                     
#define RTC_MIN_Msk                   (0x7FU << RTC_MIN_Pos)                   /*!< 0x0000007F */
#define RTC_MIN_MIN                    RTC_MIN_Msk                             /*!< RTC minute register */ 

/**************  Bits definition for RTC_HOUR register       ******************/
#define RTC_HOUR_Pos                  (0U)                                     
#define RTC_HOUR_Msk                  (0x3FU << RTC_HOUR_Pos)                  /*!< 0x0000003F */
#define RTC_HOUR_HOUR                  RTC_HOUR_Msk                            /*!< RTC hour register */ 

/**************  Bits definition for RTC_DAY register        ******************/
#define RTC_DAY_Pos                   (0U)                                     
#define RTC_DAY_Msk                   (0x3FU << RTC_DAY_Pos)                   /*!< 0x0000003F */
#define RTC_DAY_DAY                    RTC_DAY_Msk                             /*!< RTC day register */ 

/**************  Bits definition for RTC_WEEK register       ******************/
#define RTC_WEEK_Pos                  (0U)                                     
#define RTC_WEEK_Msk                  (0x7U << RTC_WEEK_Pos)                  /*!< 0x00000007 */
#define RTC_WEEK_WEEK                  RTC_WEEK_Msk                           /*!< RTC week-day register */ 

/**************  Bits definition for RTC_MON register        ******************/
#define RTC_MON_Pos                   (0U)                                     
#define RTC_MON_Msk                   (0x1FU << RTC_MON_Pos)                   /*!< 0x0000001F */
#define RTC_MON_MON                    RTC_MON_Msk                             /*!< RTC month register */ 

/**************  Bits definition for RTC_YEAR register       ******************/
#define RTC_YEAR_Pos                  (0U)                                     
#define RTC_YEAR_Msk                  (0xFFU << RTC_YEAR_Pos)                  /*!< 0x000000FF */
#define RTC_YEAR_YEAR                  RTC_YEAR_Msk                            /*!< RTC year register */ 

/**************  Bits definition for RTC_WKUSEC register     ******************/
#define RTC_WKUSEC_Pos                (0U)                                     
#define RTC_WKUSEC_Msk                (0x3FU << RTC_WKUSEC_Pos)                /*!< 0x0000003F */
#define RTC_WKUSEC_WKUSEC              RTC_WKUSEC_Msk                          /*!< This register is used to control the multi-second wake-up function.  The wake-up period is (WKUSEC + 1)*1 second */ 

/**************  Bits definition for RTC_WKUMIN register     ******************/
#define RTC_WKUMIN_Pos                (0U)                                     
#define RTC_WKUMIN_Msk                (0x3FU << RTC_WKUMIN_Pos)                /*!< 0x0000003F */
#define RTC_WKUMIN_WKUMIN              RTC_WKUMIN_Msk                          /*!< This register is used to control the multi-minute wake-up function.  The wake-up period is (WKUMIN + 1)*1 minute */ 

/**************  Bits definition for RTC_WKUHOUR register    ******************/
#define RTC_WKUHOUR_Pos               (0U)                                     
#define RTC_WKUHOUR_Msk               (0x1FU << RTC_WKUHOUR_Pos)               /*!< 0x0000001F */
#define RTC_WKUHOUR_WKUHOUR            RTC_WKUHOUR_Msk                         /*!< This register is used to control the multi-hour wake-up function.  The wake-up period is (WKUHOUR + 1)*1 hour */ 

/**************  Bits definition for RTC_WKUCNT register     ******************/
#define RTC_WKUCNT_WKUCNT_Pos         (0U)                                     
#define RTC_WKUCNT_WKUCNT_Msk         (0xFFFFFFU << RTC_WKUCNT_WKUCNT_Pos)     /*!< 0x00FFFFFF */
#define RTC_WKUCNT_WKUCNT              RTC_WKUCNT_WKUCNT_Msk                   /*!< This register is used to control the 32K counter wake-up function.  The wake-up period is (WKUCNT + 1)*Counter Clock */ 
#define RTC_WKUCNT_CNTSEL_Pos         (24U)                                     
#define RTC_WKUCNT_CNTSEL_Msk         (0x3U << RTC_WKUCNT_CNTSEL_Pos)          /*!< 0x03000000 */
#define RTC_WKUCNT_CNTSEL              RTC_WKUCNT_CNTSEL_Msk                   /*!< This is register is used to set the counter clock of WKUCNT */ 
#define RTC_WKUCNT_CNTSEL_0           (0x0U << RTC_WKUCNT_CNTSEL_Pos)
#define RTC_WKUCNT_CNTSEL_1           (0x1U << RTC_WKUCNT_CNTSEL_Pos)
#define RTC_WKUCNT_CNTSEL_2           (0x2U << RTC_WKUCNT_CNTSEL_Pos)
#define RTC_WKUCNT_CNTSEL_3           (0x3U << RTC_WKUCNT_CNTSEL_Pos)

/**************  Bits definition for RTC_CAL register        ******************/
#define RTC_CAL_Pos                   (0U)                                     
#define RTC_CAL_Msk                   (0x3FFFU << RTC_CAL_Pos)                 /*!< 0x00003FFF */
#define RTC_CAL_CAL                    RTC_CAL_Msk                             /*!< RTC 32768 calibration register, the RTC engine will do calibration for every 30 seconds, the internal counter will count 32768 times during 1~29 second.  At the 30 second, it will count [32768-(CAL-1)] for a second, so it can let the average 1 second pulse in 30 seconds become an accurate 1 second pulse */ 

/**************  Bits definition for RTC_DIV register        ******************/
#define RTC_DIV_RTCDIV_Pos            (0U)                                     
#define RTC_DIV_RTCDIV_Msk            (0x3FFFFFFU << RTC_DIV_RTCDIV_Pos)       /*!< 0x03FFFFFF */
#define RTC_DIV_RTCDIV                 RTC_DIV_RTCDIV_Msk                      /*!< This register is used to store capture value during capture mode of used to generate divider output during generation mode.  The output frequency is PCLK/(2*(RTCDIV+1)) */ 

/**************  Bits definition for RTC_CTL register        ******************/
//#define RTC_CTL_MODE_Pos              (0U)                                     
//#define RTC_CTL_MODE_Msk              (0x3U << RTC_CTL_MODE_Pos)               /*!< 0x00000003 */
//#define RTC_CTL_MODE                   RTC_CTL_MODE_Msk                        /*!< This register is used to control the capture/divider mode of high frequency divider */ 
//#define RTC_CTL_MODE_0                (0x0U << RTC_CTL_MODE_Pos)
//#define RTC_CTL_MODE_1                (0x1U << RTC_CTL_MODE_Pos)
//#define RTC_CTL_MODE_2                (0x2U << RTC_CTL_MODE_Pos)
//#define RTC_CTL_MODE_3                (0x3U << RTC_CTL_MODE_Pos)
#define RTC_CTL_RTCPLLOE_Pos          (2U)                                     
#define RTC_CTL_RTCPLLOE_Msk          (0x1U << RTC_CTL_RTCPLLOE_Pos)           /*!< 0x00000004 */
#define RTC_CTL_RTCPLLOE               RTC_CTL_RTCPLLOE_Msk                    /*!< RTCPLL Divider output enable, this register is used to control the RTCPLL divider output */ 
//#define RTC_CTL_SPOE_Pos              (3U)                                     
//#define RTC_CTL_SPOE_Msk              (0x1U << RTC_CTL_SPOE_Pos)               /*!< 0x00000008 */
//#define RTC_CTL_SPOE                   RTC_CTL_SPOE_Msk                        /*!< RTC second pulse output enable, this register is used to control the RTC second pulse output */ 

///**************  Bits definition for RTC_ITV register        ******************/
//#define RTC_ITV_ITV_Pos               (0U)                                     
//#define RTC_ITV_ITV_Msk               (0x7U << RTC_ITV_ITV_Pos)                /*!< 0x00000007 */
//#define RTC_ITV_ITV                    RTC_ITV_ITV_Msk                         /*!< This register is used to control wake-up and interrupt interval of RTC.  This register operates independently with RTC_WKUSEC and RTC_WKUMIN and RTC_WKUHOUR */ 
//#define RTC_ITV_ITV_0                 (0x0U << RTC_ITV_ITV_Pos)
//#define RTC_ITV_ITV_1                 (0x1U << RTC_ITV_ITV_Pos)
//#define RTC_ITV_ITV_2                 (0x2U << RTC_ITV_ITV_Pos)
//#define RTC_ITV_ITV_3                 (0x3U << RTC_ITV_ITV_Pos)
//#define RTC_ITV_ITV_4                 (0x4U << RTC_ITV_ITV_Pos)
//#define RTC_ITV_ITV_5                 (0x5U << RTC_ITV_ITV_Pos)
//#define RTC_ITV_ITV_6                 (0x6U << RTC_ITV_ITV_Pos)
//#define RTC_ITV_ITV_7                 (0x7U << RTC_ITV_ITV_Pos)
//
///**************  Bits definition for RTC_SITV register       ******************/
//#define RTC_SITV_SITV_Pos             (0U)                                     
//#define RTC_SITV_SITV_Msk             (0x3FU << RTC_SITV_SITV_Pos)             /*!< 0x0000003F */
//#define RTC_SITV_SITV                  RTC_SITV_SITV_Msk                       /*!< Multi second wake-up interval control register.  This register is valid only when ITV is 7 and SITVEN is 1 */
//#define RTC_SITV_SITVEN_Pos           (6U)                                     
//#define RTC_SITV_SITVEN_Msk           (0x1U << RTC_SITV_SITVEN_Pos)            /*!< 0x00000040 */
//#define RTC_SITV_SITVEN                RTC_SITV_SITVEN_Msk                     /*!< Multi Second interval enable register, this register is valid only when ITV is set to 7 */

/**************  Bits definition for RTC_PWD register        ******************/
#define RTC_PWD_PWDEN_Pos             (0U)                                     
#define RTC_PWD_PWDEN_Msk             (0x1U << RTC_PWD_PWDEN_Pos)              /*!< 0x00000001 */
#define RTC_PWD_PWDEN                  RTC_PWD_PWDEN_Msk                       /*!< This register is used to protect the RTC_CE port’s access.  Before access the RTC_CE, programmer should write 0x5AA55AA5 to this port, and the PWDEN will be set to 1.  This bit will be cleared automatically after any write to RTC_CE port.  Which means programmer should write to this port again before next access to RTC_CE port */ 

/**************  Bits definition for RTC_CE register         ******************/
#define RTC_CE_CE_Pos                 (0U)                                     
#define RTC_CE_CE_Msk                 (0x1U << RTC_CE_CE_Pos)                  /*!< 0x00000001 */
#define RTC_CE_CE                      RTC_CE_CE_Msk                           /*!< This register is used to unlock the access to RTC register.  This register can be only when PWDEN is set to 1 and 0xA55AA55B is written to this register.  After this bit is set to 1, the RTC register can be programmed, but the actual update to RTC core will be start after this bit is cleared to 0.  To clear this bit, the PWDEN should be set to 1 and 0xA55AA55A should be written to this register */ 
#define RTC_CE_BSY_Pos                (1U)                                     
#define RTC_CE_BSY_Msk                (0x1U << RTC_CE_BSY_Pos)                 /*!< 0x00000002 */
#define RTC_CE_BSY                     RTC_CE_BSY_Msk                          /*!< This flag is used to indicated the RTC update procedure or RTC read procedure is ongoing.  This bit will be set immediately after the CE is cleared from 1 to 0 or when RTC_LOAD port is read by CPU.  This bit will cleared automatically after the read or write procedure is done.  Programmer can polling this bit to know if the RTC update is done or not.  The update or read procedure take around 3 32K period, which is around 100 us */ 

/**************  Bits definition for RTC_LOAD register       ******************/
#define RTC_LOAD_LOAD_Pos             (0U)                                     
#define RTC_LOAD_LOAD_Msk             (0xFFFFFFFFU << RTC_LOAD_LOAD_Pos)       /*!< 0xFFFFFFFF */
#define RTC_LOAD_LOAD                  RTC_LOAD_LOAD_Msk                       /*!< This register is used to let RTC engine read data from RTC core.  When programmer read from this port, the current time will be latched and programmer can read data from RTC_SEC ~ RTC_YEAR register.  The read procedure will takes 3 32K cycles, programmer can check the BSY bit to know if the procedure is done.  The read data from this port is invalid */ 

/**************  Bits definition for RTC_INTSTS register     ******************/
//#define RTC_INTSTS_INTSTS0_Pos        (0U)                                     
//#define RTC_INTSTS_INTSTS0_Msk        (0x1U << RTC_INTSTS_INTSTS0_Pos)         /*!< 0x00000001 */
//#define RTC_INTSTS_INTSTS0             RTC_INTSTS_INTSTS0_Msk                  /*!< Interrupt status 0, this interrupt is controlled by ITV and SITV.  Write 1 to clear this bit */ 
#define RTC_INTSTS_INTSTS1_Pos        (1U)                                     
#define RTC_INTSTS_INTSTS1_Msk        (0x1U << RTC_INTSTS_INTSTS1_Pos)         /*!< 0x00000002 */
#define RTC_INTSTS_INTSTS1             RTC_INTSTS_INTSTS1_Msk                  /*!< Interrupt status 1, this interrupt will be set when illegal time format is written into RTC core.  Write 1 to clear this bit */ 
#define RTC_INTSTS_INTSTS2_Pos        (2U)                                     
#define RTC_INTSTS_INTSTS2_Msk        (0x1U << RTC_INTSTS_INTSTS2_Pos)         /*!< 0x00000004 */
#define RTC_INTSTS_INTSTS2             RTC_INTSTS_INTSTS2_Msk                  /*!< Interrupt status 2, this interrupt will be set when multi-second interrupt period set by WKUSEC is reach.  Write 1 to clear this bit */ 
#define RTC_INTSTS_INTSTS3_Pos        (3U)                                     
#define RTC_INTSTS_INTSTS3_Msk        (0x1U << RTC_INTSTS_INTSTS3_Pos)         /*!< 0x00000008 */
#define RTC_INTSTS_INTSTS3             RTC_INTSTS_INTSTS3_Msk                  /*!< Interrupt status 3, this interrupt will be set when multi-minute interrupt period set by WKUMIN is reach.  Write 1 to clear this bit */ 
#define RTC_INTSTS_INTSTS4_Pos        (4U)                                     
#define RTC_INTSTS_INTSTS4_Msk        (0x1U << RTC_INTSTS_INTSTS4_Pos)         /*!< 0x00000010 */
#define RTC_INTSTS_INTSTS4             RTC_INTSTS_INTSTS4_Msk                  /*!< Interrupt status 4, this interrupt will be set when multi-hour interrupt period set by WKUHOUR is reach.  Write 1 to clear this bit */ 
#define RTC_INTSTS_INTSTS5_Pos        (5U)                                     
#define RTC_INTSTS_INTSTS5_Msk        (0x1U << RTC_INTSTS_INTSTS5_Pos)         /*!< 0x00000020 */
#define RTC_INTSTS_INTSTS5             RTC_INTSTS_INTSTS5_Msk                  /*!< Interrupt status 5, this interrupt will be set when mid-night (00:00) is reach.  Write 1 to clear this bit */ 
#define RTC_INTSTS_INTSTS6_Pos        (6U)                                     
#define RTC_INTSTS_INTSTS6_Msk        (0x1U << RTC_INTSTS_INTSTS6_Pos)         /*!< 0x00000040 */
#define RTC_INTSTS_INTSTS6             RTC_INTSTS_INTSTS6_Msk                  /*!< Interrupt status 6, this interrupt will be set when 32K counter interrupt period set by WKUCNT is reach.    Write 1 to clear this bit */ 
#define RTC_INTSTS_INTSTS7_Pos        (7U)                                     
#define RTC_INTSTS_INTSTS7_Msk        (0x1U << RTC_INTSTS_INTSTS7_Pos)         /*!< 0x00000080 */
#define RTC_INTSTS_INTSTS7             RTC_INTSTS_INTSTS7_Msk                  /*!< Interrupt status 7, this interrupt will be set when an auto calibration is done.  Write 1 to clear this bit */ 
#define RTC_INTSTS_INTSTS8_Pos        (8U)                                     
#define RTC_INTSTS_INTSTS8_Msk        (0x1U << RTC_INTSTS_INTSTS8_Pos)         /*!< 0x00000100 */
#define RTC_INTSTS_INTSTS8             RTC_INTSTS_INTSTS8_Msk                  /*!< Interrupt status 8, this interrupt will be set when an illegal write to CE register is happened.  The illegal write means the BSY bit is still 1 but CE is set to 1 again or RTC_LOAD port is read again.  Write 1 to clear this bit */ 
#define RTC_INTSTS_ACBSY_Pos          (9U)                                     
#define RTC_INTSTS_ACBSY_Msk          (0x1U << RTC_INTSTS_ACBSY_Pos)           /*!< 0x00000200 */
#define RTC_INTSTS_ACBSY               RTC_INTSTS_ACBSY_Msk                    /*!< Auto-calibration busy flag */ 

/**************  Bits definition for RTC_INTEN register      ******************/
//#define RTC_INTEN_INTEN0_Pos          (0U)                                     
//#define RTC_INTEN_INTEN0_Msk          (0x1U << RTC_INTEN_INTEN0_Pos)           /*!< 0x00000001 */
//#define RTC_INTEN_INTEN0               RTC_INTEN_INTEN0_Msk                    /*!< Interrupt enable 0, when this bit is 1, the INTSTS0 interrupt will be asserted to CPU and wake-up signal will be asserted to PMU controller */ 
#define RTC_INTEN_INTEN1_Pos          (1U)                                     
#define RTC_INTEN_INTEN1_Msk          (0x1U << RTC_INTEN_INTEN1_Pos)           /*!< 0x00000002 */
#define RTC_INTEN_INTEN1               RTC_INTEN_INTEN1_Msk                    /*!< Interrupt enable 1, when this bit is 1, the INTSTS1 interrupt will be asserted to CPU and wake-up signal will be asserted to PMU controller */ 
#define RTC_INTEN_INTEN2_Pos          (2U)                                     
#define RTC_INTEN_INTEN2_Msk          (0x1U << RTC_INTEN_INTEN2_Pos)           /*!< 0x00000004 */
#define RTC_INTEN_INTEN2               RTC_INTEN_INTEN2_Msk                    /*!< Interrupt enable 2, when this bit is 1, the INTSTS2 interrupt will be asserted to CPU and wake-up signal will be asserted to PMU controller */ 
#define RTC_INTEN_INTEN3_Pos          (3U)                                     
#define RTC_INTEN_INTEN3_Msk          (0x1U << RTC_INTEN_INTEN3_Pos)           /*!< 0x00000008 */
#define RTC_INTEN_INTEN3               RTC_INTEN_INTEN3_Msk                    /*!< Interrupt enable 3, when this bit is 1, the INTSTS3 interrupt will be asserted to CPU and wake-up signal will be asserted to PMU controller */ 
#define RTC_INTEN_INTEN4_Pos          (4U)                                     
#define RTC_INTEN_INTEN4_Msk          (0x1U << RTC_INTEN_INTEN4_Pos)           /*!< 0x00000010 */
#define RTC_INTEN_INTEN4               RTC_INTEN_INTEN4_Msk                    /*!< Interrupt enable 4, when this bit is 1, the INTSTS3 interrupt will be asserted to CPU and wake-up signal will be asserted to PMU controller */ 
#define RTC_INTEN_INTEN5_Pos          (5U)                                     
#define RTC_INTEN_INTEN5_Msk          (0x1U << RTC_INTEN_INTEN5_Pos)           /*!< 0x00000020 */
#define RTC_INTEN_INTEN5               RTC_INTEN_INTEN5_Msk                    /*!< Interrupt enable 5, when this bit is 1, the INTSTS5 interrupt will be asserted to CPU and wake-up signal will be asserted to PMU controller */ 
#define RTC_INTEN_INTEN6_Pos          (6U)                                     
#define RTC_INTEN_INTEN6_Msk          (0x1U << RTC_INTEN_INTEN6_Pos)           /*!< 0x00000040 */
#define RTC_INTEN_INTEN6               RTC_INTEN_INTEN6_Msk                    /*!< Interrupt enable 6, when this bit is 1, the INTSTS6 interrupt will be asserted to CPU and wake-up signal will be asserted to PMU controller */ 
#define RTC_INTEN_INTEN7_Pos          (7U)                                     
#define RTC_INTEN_INTEN7_Msk          (0x1U << RTC_INTEN_INTEN7_Pos)           /*!< 0x00000080 */
#define RTC_INTEN_INTEN7               RTC_INTEN_INTEN7_Msk                    /*!< Interrupt enable 7, when this bit is 1, the INTSTS7 can be set, and interrupt will be asserted to CPU and wake-up signal will be asserted to PMU controller */ 
#define RTC_INTEN_INTEN8_Pos          (8U)                                     
#define RTC_INTEN_INTEN8_Msk          (0x1U << RTC_INTEN_INTEN8_Pos)           /*!< 0x00000100 */
#define RTC_INTEN_INTEN8               RTC_INTEN_INTEN8_Msk                    /*!< Interrupt enable 8, when this bit is 1 and INTSTS86 is set, and interrupt will be asserted to CPU */ 

/**************  Bits definition for RTC_PSCA register       ******************/
#define RTC_PSCA_PSCA_Pos             (0U)                                     
#define RTC_PSCA_PSCA_Msk             (0x3U << RTC_PSCA_PSCA_Pos)              /*!< 0x00000003 */
#define RTC_PSCA_PSCA                  RTC_PSCA_PSCA_Msk                       /*!< This register is used to control the RTC clock pre-scaler.  When slow down the RTC clock, it can significantly reduce the power under sleep or deep-sleep mode */ 
#define RTC_PSCA_PSCA_0               (0x0U << RTC_PSCA_PSCA_Pos)
#define RTC_PSCA_PSCA_1               (0x1U << RTC_PSCA_PSCA_Pos)
//#define RTC_PSCA_PSCA_2               (0x2U << RTC_PSCA_PSCA_Pos)
//#define RTC_PSCA_PSCA_3               (0x3U << RTC_PSCA_PSCA_Pos)

/**************  Bits definition for RTC_ACCTRL register     ******************/
#define RTC_ACCTRL_ACEN_Pos           (0U)                                     
#define RTC_ACCTRL_ACEN_Msk           (0x1U << RTC_ACCTRL_ACEN_Pos)            /*!< 0x00000001 */
#define RTC_ACCTRL_ACEN                RTC_ACCTRL_ACEN_Msk                     /*!< Auto-calibration enable control register */ 
#define RTC_ACCTRL_MANU_Pos           (1U)                                     
#define RTC_ACCTRL_MANU_Msk           (0x1U << RTC_ACCTRL_MANU_Pos)            /*!< 0x00000002 */
#define RTC_ACCTRL_MANU                RTC_ACCTRL_MANU_Msk                     /*!< Auto-calibration manual trigger function.  Write 1 to this register will trigger an auto-calibration procedure.  This bit will be cleared to 0 when the procedure is done */ 
#define RTC_ACCTRL_ADCSEL_Pos         (3U)                                     
#define RTC_ACCTRL_ADCSEL_Msk         (0x1U << RTC_ACCTRL_ADCSEL_Pos)          /*!< 0x00000008 */
#define RTC_ACCTRL_ADCSEL              RTC_ACCTRL_ADCSEL_Msk                   /*!< ADC source select register */ 
#define RTC_ACCTRL_ACCLK_Pos          (4U)                                     
#define RTC_ACCTRL_ACCLK_Msk          (0x3U << RTC_ACCTRL_ACCLK_Pos)           /*!< 0x00000030 */
#define RTC_ACCTRL_ACCLK               RTC_ACCTRL_ACCLK_Msk                    /*!< Auto-trigger clock source selection */ 
#define RTC_ACCTRL_ACCLK_0            (0x0U << RTC_ACCTRL_ACCLK_Pos)
#define RTC_ACCTRL_ACCLK_1            (0x1U << RTC_ACCTRL_ACCLK_Pos)
#define RTC_ACCTRL_ACCLK_2            (0x2U << RTC_ACCTRL_ACCLK_Pos)
#define RTC_ACCTRL_ACCLK_3            (0x3U << RTC_ACCTRL_ACCLK_Pos)
#define RTC_ACCTRL_ACDEL_Pos          (6U)                                     
#define RTC_ACCTRL_ACDEL_Msk          (0x3U << RTC_ACCTRL_ACDEL_Pos)           /*!< 0x000000C0 */
#define RTC_ACCTRL_ACDEL               RTC_ACCTRL_ACDEL_Msk                    /*!< Auto-calibration delay period selection, before doing auto-calibration, a specified delay will be applied to ensure the main power is stable */ 
#define RTC_ACCTRL_ACDEL_0            (0x0U << RTC_ACCTRL_ACDEL_Pos) 
#define RTC_ACCTRL_ACDEL_1            (0x1U << RTC_ACCTRL_ACDEL_Pos)
#define RTC_ACCTRL_ACDEL_2            (0x2U << RTC_ACCTRL_ACDEL_Pos)
#define RTC_ACCTRL_ACDEL_3            (0x3U << RTC_ACCTRL_ACDEL_Pos)
#define RTC_ACCTRL_ACPER_Pos          (8U)                                     
#define RTC_ACCTRL_ACPER_Msk          (0x3FU << RTC_ACCTRL_ACPER_Pos)          /*!< 0x00003F00 */
#define RTC_ACCTRL_ACPER               RTC_ACCTRL_ACPER_Msk                    /*!< Auto trigger period control register, the actual period is controlled by (ACPER + 1)*ACCLK.  For example, when ACCLK is set to 2 (1 minute), and ACPER is set to 5, then the auto trigger period is (5+1)*1 minute = 6 minutes */ 
 
/**************  Bits definition for RTC_ACTI register       ******************/
#define RTC_ACTI_ACTI_Pos             (0U)                                     
#define RTC_ACTI_ACTI_Msk             (0x3FFFU << RTC_ACTI_ACTI_Pos)           /*!< 0x00003FFF */
#define RTC_ACTI_ACTI                  RTC_ACTI_ACTI_Msk                       /*!< Auto-calibration Ti control register.  This register is used to store the Ti value which is used as the center temperature during calibration.  This register is 8 bits integer and 8 bits fraction value.  For example, 0x1880 means 24.5 degree.  This register can be updated only when CE is 1, and should be fixed value when ACEN is 1 */ 

/**************  Bits definition for RTC_ACF200 register     ******************/
#define RTC_ACF200_F200_Pos           (0U)                                     
#define RTC_ACF200_F200_Msk           (0x3FFFFFFU << RTC_ACF200_F200_Pos)      /*!< 0x03FFFFFF */
#define RTC_ACF200_F200                RTC_ACF200_F200_Msk                     /*!< Auto-calibration F200 control register.  This register is used to store the current PCLK speed value which is used for the calculation of PLLDIV value.  This register is 26 bits integer */ 

/**************  Bits definition for RTC_ACADCW register     ******************/
#define RTC_ACADCW_ADCW_Pos           (0U)                                     
#define RTC_ACADCW_ADCW_Msk           (0xFFFU << RTC_ACADCW_ADCW_Pos)          /*!< 0x00000FFF */
#define RTC_ACADCW_ADCW                RTC_ACADCW_ADCW_Msk                     /*!< Auto-calibration manual ADC value control register.  This register is used to store the manual ADC value  which is used for the calculation for temperature.  By default, the auto-calibration engine will read the ADC value automatically, but if programmer wishes to control the ADC value manually, this register can be used to control the ADC value read by the engine.  This register is 12 bits integer.  This register is valid only when ADCSEL is set to 1 */ 

/**************  Bits definition for RTC_ACP0 register       ******************/
#define RTC_ACP_P0_Pos                (0U)                                     
#define RTC_ACP_P0_Msk                (0xFFFF << RTC_ACP_P0_Pos)               /*!< 0x0000FFFF */
#define RTC_ACP_P0                     RTC_ACP_P0_Msk                          /*!< The P0~P7 registers are used for auto-calibration.  Only P2 is 32 bits signed value, other P0~P7 is 16 bits signed value */ 

/**************  Bits definition for RTC_ACP1 register       ******************/
#define RTC_ACP_P1_Pos                (0U)                                     
#define RTC_ACP_P1_Msk                (0xFFFF << RTC_ACP_P1_Pos)               /*!< 0x0000FFFF */
#define RTC_ACP_P1                     RTC_ACP_P1_Msk                          /*!< The P0~P7 registers are used for auto-calibration.  Only P2 is 32 bits signed value, other P0~P7 is 16 bits signed value */ 

/**************  Bits definition for RTC_ACP2 register       ******************/
#define RTC_ACP_P2_Pos                (0U)                                     
#define RTC_ACP_P2_Msk                (0xFFFFFFFF << RTC_ACP_P2_Pos)           /*!< 0xFFFFFFFF */
#define RTC_ACP_P2                     RTC_ACP_P2_Msk                          /*!< The P0~P7 registers are used for auto-calibration.  Only P2 is 32 bits signed value, other P0~P7 is 16 bits signed value */ 

/**************  Bits definition for RTC_ACP3 register       ******************/
#define RTC_ACP_P3_Pos                (0U)                                     
#define RTC_ACP_P3_Msk                (0xFFFF << RTC_ACP_P3_Pos)               /*!< 0x0000FFFF */
#define RTC_ACP_P3                     RTC_ACP_P3_Msk                          /*!< The P0~P7 registers are used for auto-calibration.  Only P2 is 32 bits signed value, other P0~P7 is 16 bits signed value */ 

/**************  Bits definition for RTC_ACP4 register       ******************/
#define RTC_ACP_P4_Pos                (0U)                                     
#define RTC_ACP_P4_Msk                (0xFFFF << RTC_ACP_P4_Pos)               /*!< 0x0000FFFF */
#define RTC_ACP_P4                     RTC_ACP_P4_Msk                          /*!< The P0~P7 registers are used for auto-calibration.  Only P2 is 32 bits signed value, other P0~P7 is 16 bits signed value */ 

/**************  Bits definition for RTC_ACP5 register       ******************/
#define RTC_ACP_P5_Pos                (0U)                                     
#define RTC_ACP_P5_Msk                (0xFFFF << RTC_ACP_P5_Pos)               /*!< 0x0000FFFF */
#define RTC_ACP_P5                     RTC_ACP_P5_Msk                          /*!< The P0~P7 registers are used for auto-calibration.  Only P2 is 32 bits signed value, other P0~P7 is 16 bits signed value */ 

/**************  Bits definition for RTC_ACP6 register       ******************/
#define RTC_ACP_P6_Pos                (0U)                                     
#define RTC_ACP_P6_Msk                (0xFFFF << RTC_ACP_P6_Pos)               /*!< 0x0000FFFF */
#define RTC_ACP_P6                     RTC_ACP_P6_Msk                          /*!< The P0~P7 registers are used for auto-calibration.  Only P2 is 32 bits signed value, other P0~P7 is 16 bits signed value */ 
 
/**************  Bits definition for RTC_ACP7 register       ******************/
#define RTC_ACP_P7_Pos                (0U)                                     
#define RTC_ACP_P7_Msk                (0xFFFF << RTC_ACP_P7_Pos)               /*!< 0x0000FFFF */
#define RTC_ACP_P7                     RTC_ACP_P7_Msk                          /*!< The P0~P7 registers are used for auto-calibration.  Only P2 is 32 bits signed value, other P0~P7 is 16 bits signed value */ 

/**************  Bits definition for RTC_ACK1 register       ******************/
#define RTC_ACK_K1_Pos                (0U)                                     
#define RTC_ACK_K1_Msk                (0xFFFFU << RTC_ACK_K1_Pos)              /*!< 0x0000FFFF */
#define RTC_ACK_K1                     RTC_ACK_K1_Msk                          /*!< The K1~K5 registers are used for auto-calibration.  These registers are 16 bits signed register.  Hardware will auto select a suitable Kx according to calculated temperature and represent on P3 */ 

/**************  Bits definition for RTC_ACK2 register       ******************/
#define RTC_ACK_K2_Pos                (0U)                                     
#define RTC_ACK_K2_Msk                (0xFFFFU << RTC_ACK_K2_Pos)              /*!< 0x0000FFFF */
#define RTC_ACK_K2                     RTC_ACK_K2_Msk                          /*!< The K1~K5 registers are used for auto-calibration.  These registers are 16 bits signed register.  Hardware will auto select a suitable Kx according to calculated temperature and represent on P3 */ 

/**************  Bits definition for RTC_ACK3 register       ******************/
#define RTC_ACK_K3_Pos                (0U)                                     
#define RTC_ACK_K3_Msk                (0xFFFFU << RTC_ACK_K3_Pos)              /*!< 0x0000FFFF */
#define RTC_ACK_K3                     RTC_ACK_K3_Msk                          /*!< The K1~K5 registers are used for auto-calibration.  These registers are 16 bits signed register.  Hardware will auto select a suitable Kx according to calculated temperature and represent on P3 */ 

/**************  Bits definition for RTC_ACK4 register       ******************/
#define RTC_ACK_K4_Pos                (0U)                                     
#define RTC_ACK_K4_Msk                (0xFFFFU << RTC_ACK_K4_Pos)              /*!< 0x0000FFFF */
#define RTC_ACK_K4                     RTC_ACK_K4_Msk                          /*!< The K1~K5 registers are used for auto-calibration.  These registers are 16 bits signed register.  Hardware will auto select a suitable Kx according to calculated temperature and represent on P3 */ 

/**************  Bits definition for RTC_ACK5 register       ******************/
#define RTC_ACK_K5_Pos                (0U)                                     
#define RTC_ACK_K5_Msk                (0xFFFFU << RTC_ACK_K5_Pos)              /*!< 0x0000FFFF */
#define RTC_ACK_K5                     RTC_ACK_K5_Msk                          /*!< The K1~K5 registers are used for auto-calibration.  These registers are 16 bits signed register.  Hardware will auto select a suitable Kx according to calculated temperature and represent on P3 */ 

/**************  Bits definition for RTC_ACTEMP register     ******************/
#define RTC_ACTEMP_TEMP_Pos           (0U)                                     
#define RTC_ACTEMP_TEMP_Msk           (0xFFFFU << RTC_ACTEMP_TEMP_Pos)         /*!< 0x0000FFFF */
#define RTC_ACTEMP_TEMP                RTC_ACTEMP_TEMP_Msk                     /*!< This register is used to store the calculated result of current temperature.  This register will be updated automatically after the auto-calibration procedure is done */ 

/**************  Bits definition for RTC_ACPPM register      ******************/
#define RTC_ACPPM_PPM_Pos             (0U)                                     
#define RTC_ACPPM_PPM_Msk             (0xFFFFU << RTC_ACPPM_PPM_Pos)           /*!< 0x0000FFFF */
#define RTC_ACPPM_PPM                  RTC_ACPPM_PPM_Msk                       /*!< This register is used to store the calculated result of current temperature.  This register will be updated automatically after the auto-calibration procedure is done.  This register is a 16 bits signed value and the unit of this register is 0.1 PPM */ 

/**************  Bits definition for RTC_ACADCR register     ******************/
#define RTC_ACADCR_ADCR_Pos           (0U)                                     
#define RTC_ACADCR_ADCR_Msk           (0xFFFFU << RTC_ACADCR_ADCR_Pos)         /*!< 0x0000FFFF */
#define RTC_ACADCR_ADCR                RTC_ACADCR_ADCR_Msk                     /*!< This register is used to represent the ADC value used by the auto-calibration engine, the value of this register is the 12 bits ADC value * 8.  When the ADCSEL is 0, it will store the value read from ADC and multiplied by 8, when ADCSEL is 1, this value will equal to ADCW *8 */ 

/**************  Bits definition for RTC_ACKTEMP register    ******************/
#define RTC_ACKTEMP_KTEMP1_Pos        (0U)                                     
#define RTC_ACKTEMP_KTEMP1_Msk        (0xFFU << RTC_ACKTEMP_KTEMP1_Pos)        /*!< 0x000000FF */
#define RTC_ACKTEMP_KTEMP1             RTC_ACKTEMP_KTEMP1_Msk                  /*!< This register is used to control the section 1 temperature.  This is a signed 8 bits value.  This register can be updated only when CE is 1, and should be fixed value when ACEN is 1 */ 
#define RTC_ACKTEMP_KTEMP2_Pos        (8U)                                     
#define RTC_ACKTEMP_KTEMP2_Msk        (0xFFU << RTC_ACKTEMP_KTEMP2_Pos)        /*!< 0x0000FF00 */
#define RTC_ACKTEMP_KTEMP2             RTC_ACKTEMP_KTEMP2_Msk                  /*!< This register is used to control the section 2 temperature.  This is a signed 8 bits value.  This register can be updated only when CE is 1, and should be fixed value when ACEN is 1 */ 
#define RTC_ACKTEMP_KTEMP3_Pos        (16U)                                    
#define RTC_ACKTEMP_KTEMP3_Msk        (0xFFU << RTC_ACKTEMP_KTEMP3_Pos)        /*!< 0x00FF0000 */
#define RTC_ACKTEMP_KTEMP3             RTC_ACKTEMP_KTEMP3_Msk                  /*!< This register is used to control the section 3 temperature.  This is a signed 8 bits value.  This register can be updated only when CE is 1, and should be fixed value when ACEN is 1 */ 
#define RTC_ACKTEMP_KTEMP4_Pos        (24U)                                     
#define RTC_ACKTEMP_KTEMP4_Msk        (0xFFU << RTC_ACKTEMP_KTEMP4_Pos)        /*!< 0xFF000000 */
#define RTC_ACKTEMP_KTEMP4             RTC_ACKTEMP_KTEMP4_Msk                  /*!< This register is used to control the section 3 temperature.  This is a signed 8 bits value.  This register can be updated only when CE is 1, and should be fixed value when ACEN is 1 */ 

/**************  Bits definition for RTC_ACOPx register      ******************/
#define RTC_ACOP_OP_Pos               (0U)                                     
#define RTC_ACOP_OP_Msk               (0x1FFU << RTC_ACOP_OP_Pos)              /*!< 0x000001FF */
#define RTC_ACOP_OP                    RTC_ACOP_OP_Msk                         /*!< The OP0~OP63 register is valid only for FPGA.  These Ops are used for internal ALU to calculate the auto-calibration data.  Before the auto-calibration procedure, all necessary OP should be program correctly into these registers.  For real chip, this part will become ROM table and no longer be able to read/write by CPU */ 

/******************************************************************************/
/*                                                                            */
/*                         FLASH controller (FLASH)                           */
/*                                                                            */
/******************************************************************************/

/**************  Bits definition for FLASH_STS register      ******************/
#define FLASH_STS_Pos                 (0U)                                     
#define FLASH_STS_Msk                 (0x1U << FLASH_STS_Pos)                  /*!< 0x00000001 */
#define FLASH_STS                      FLASH_STS_Msk                           /*!<  */ 

/**************  Bits definition for FLASH_NVRPASS register  ******************/
#define FLASH_NVRPASS_Pos             (0U)                                     
#define FLASH_NVRPASS_Msk             (0xFFFFFFFFU << FLASH_NVRPASS_Pos)       /*!< 0xFFFFFFFF */
#define FLASH_NVRPASS_NVRPASS          FLASH_NVRPASS_Msk                       /*!< programmer should write 0xAA5555AA to this register */ 
#define FLASH_NVRPASS_NVRUNLOCK_Pos   (0U)                                     
#define FLASH_NVRPASS_NVRUNLOCK_Msk   (0x1U << FLASH_NVRPASS_NVRUNLOCK_Pos)    /*!< 0x00000001 */
#define FLASH_NVRPASS_NVRUNLOCK        FLASH_NVRPASS_NVRUNLOCK_Msk             /*!< The NVRUNLOCK bit is used to indicate the NVR sector program has been unlocked or not */ 

/**************  Bits definition for FLASH_BDPASS register   ******************/
//#define FLASH_BDPASS_BDEN_Pos         (0U)                                     
//#define FLASH_BDPASS_BDEN_Msk         (0x1U << FLASH_BDPASS_BDEN_Pos)          /*!< 0x00000001 */
//#define FLASH_BDPASS_BDEN              FLASH_BDPASS_BDEN_Msk                   /*!< This register is not opened for customer */ 

/**************  Bits definition for FLASH_KEY register      ******************/
#define FLASH_KEY_Pos                 (0U)                                     
#define FLASH_KEY_Msk                 (0xFFFFFFFFU << FLASH_KEY_Pos)           /*!< 0xFFFFFFFF */
#define FLASH_KEY_KEY                  FLASH_KEY_Msk                           /*!< The KEY register is used to unlock those blocked function */ 

/**************  Bits definition for FLASH_INT register      ******************/
#define FLASH_INT_CSERR_Pos           (0U)                                     
#define FLASH_INT_CSERR_Msk           (0x1U << FLASH_INT_CSERR_Pos)            /*!< 0x00000001 */
#define FLASH_INT_CSERR                FLASH_INT_CSERR_Msk                     /*!< Checksum error status bit */ 

/**************  Bits definition for FLASH_CSSADDR register  ******************/
#define FLASH_CSSADDR_Pos             (0U)                                     
#define FLASH_CSSADDR_Msk             (0x3FFFFU << FLASH_CSSADDR_Pos)          /*!< 0x0003FFFF */
#define FLASH_CSSADDR_CSSADDR          FLASH_CSSADDR_Msk                       /*!< Checksum start address register */ 

/**************  Bits definition for FLASH_CSEADDR register  ******************/
#define FLASH_CSEADDR_Pos             (0U)                                     
#define FLASH_CSEADDR_Msk             (0x3FFFFU << FLASH_CSEADDR_Pos)          /*!< 0x0003FFFF */
#define FLASH_CSEADDR_CSEADDR          FLASH_CSEADDR_Msk                       /*!< Checksum end address register */ 

/**************  Bits definition for FLASH_CSVALUE register  ******************/
#define FLASH_CSVALUE_Pos             (0U)                                     
#define FLASH_CSVALUE_Msk             (0xFFFFFFFFU << FLASH_CSVALUE_Pos)       /*!< 0xFFFFFFFF */
#define FLASH_CSVALUE_CSVALUE          FLASH_CSVALUE_Msk                       /*!< Checksum latched value register */  

/**************  Bits definition for FLASH_CSCVALUE register ******************/
#define FLASH_CSCVALUE_Pos            (0U)                                     
#define FLASH_CSCVALUE_Msk            (0xFFFFFFFFU << FLASH_CSCVALUE_Pos)      /*!< 0xFFFFFFFF */
#define FLASH_CSCVALUE_CSCVALUE        FLASH_CSCVALUE_Msk                      /*!< Checksum compare value register */ 

/**************  Bits definition for FLASH_PASS register     ******************/
#define FLASH_PASS_Pos                (0U)                                     
#define FLASH_PASS_Msk                (0xFFFFFFFFU << FLASH_PASS_Pos)          /*!< 0xFFFFFFFF */
#define FLASH_PASS_PASS                FLASH_PASS_Msk                          /*!< programmer should write 0x55AAAA55 to this register */ 
#define FLASH_PASS_UNLOCK_Pos         (0U)                                     
#define FLASH_PASS_UNLOCK_Msk         (0x1U << FLASH_PASS_UNLOCK_Pos)          /*!< 0x00000001 */
#define FLASH_PASS_UNLOCK              FLASH_PASS_UNLOCK_Msk                   /*!< The UNLOCK bit is used to indicate the Flash program has been unlocked or not */ 

/**************  Bits definition for FLASH_CTRL register     ******************/
#define FLASH_CTRL_CSMODE_Pos         (0U)                                     
#define FLASH_CTRL_CSMODE_Msk         (0x3U << FLASH_CTRL_CSMODE_Pos)          /*!< 0x00000003 */
#define FLASH_CTRL_CSMODE              FLASH_CTRL_CSMODE_Msk                   /*!< This register is used to control the checksum mode */ 
#define FLASH_CTRL_CSMODE_DISABLE     (0x0U << FLASH_CTRL_CSMODE_Pos)          /*!< 0x00000000 */
#define FLASH_CTRL_CSMODE_ALWAYSON    (0x1U << FLASH_CTRL_CSMODE_Pos)          /*!< 0x00000001 */
#define FLASH_CTRL_CSMODE_TIM2OV      (0x2U << FLASH_CTRL_CSMODE_Pos)          /*!< 0x00000002 */
#define FLASH_CTRL_CSMODE_RTC         (0x3U << FLASH_CTRL_CSMODE_Pos)          /*!< 0x00000003 */
#define FLASH_CTRL_CSINTEN_Pos        (2U)                                     
#define FLASH_CTRL_CSINTEN_Msk        (0x1U << FLASH_CTRL_CSINTEN_Pos)         /*!< 0x00000004 */
#define FLASH_CTRL_CSINTEN             FLASH_CTRL_CSINTEN_Msk                  /*!< This register is used to control the interrupt enable of checksum error */ 
//#define FLASH_CTRL_READM0_Pos         (4U)                                     
//#define FLASH_CTRL_READM0_Msk         (0x1U << FLASH_CTRL_READM0_Pos)          /*!< 0x00000010 */
//#define FLASH_CTRL_READM0              FLASH_CTRL_READM0_Msk                   /*!< This bit is used to control the READM0 pin of Flash IP */ 
//#define FLASH_CTRL_READM1_Pos         (5U)                                     
//#define FLASH_CTRL_READM1_Msk         (0x1U << FLASH_CTRL_READM1_Pos)          /*!< 0x00000020 */
//#define FLASH_CTRL_READM1              FLASH_CTRL_READM1_Msk                   /*!< This bit is used to control the READM1 pin of Flash IP */ 
//#define FLASH_CTRL_NVR_Pos            (6U)                                     
//#define FLASH_CTRL_NVR_Msk            (0x1U << FLASH_CTRL_NVR_Pos)             /*!< 0x00000040 */
//#define FLASH_CTRL_NVR                 FLASH_CTRL_NVR_Msk                      /*!< This register is used to control the NVR program */ 
//#define FLASH_CTRL_SFTRST_Pos         (7U)                                     
//#define FLASH_CTRL_SFTRST_Msk         (0x1U << FLASH_CTRL_SFTRST_Pos)          /*!< 0x00000080 */
//#define FLASH_CTRL_SFTRST              FLASH_CTRL_SFTRST_Msk                   /*!< This register is used to reset the internal FIFO, just for test usage */ 
//#define FLASH_CTRL_FORCESWAP_Pos      (8U)                                     
//#define FLASH_CTRL_FORCESWAP_Msk      (0x1U << FLASH_CTRL_FORCESWAP_Pos)       /*!< 0x00000100 */
//#define FLASH_CTRL_FORCESWAP           FLASH_CTRL_FORCESWAP_Msk                /*!< This register is used to control the swap function in-between normal sector and NVR sector */ 

/**************  Bits definition for FLASH_PGADDR register   ******************/
#define FLASH_PGADDR_Pos              (0U)                                     
#define FLASH_PGADDR_Msk              (0x3FFFFU << FLASH_PGADDR_Pos)           /*!< 0x0003FFFF */
#define FLASH_PGADDR_PGADDR            FLASH_PGADDR_Msk                        /*!< This register is used to control the program address before doing program */ 

/**************  Bits definition for FLASH_PGDATA register   ******************/
#define FLASH_PGDATA_Pos              (0U)                                     
#define FLASH_PGDATA_Msk              (0xFFFFFFFFU << FLASH_PGDATA_Pos)        /*!< 0xFFFFFFFF */
#define FLASH_PGDATA_PGDATA            FLASH_PGDATA_Msk                        /*!< This register is used to control the program data */ 

/**************  Bits definition for FLASH_PGDB0 register    ******************/
#define FLASH_PGDB0_Pos               (0U)                                     
#define FLASH_PGDB0_Msk               (0xFFU << FLASH_PGDB0_Pos)               /*!< 0x000000FF */
#define FLASH_PGDB0                    FLASH_PGDB0_Msk                         /*!< This register is used to control the program data */ 

/**************  Bits definition for FLASH_PGDB1 register    ******************/
#define FLASH_PGDB1_Pos               (0U)                                     
#define FLASH_PGDB1_Msk               (0xFFU << FLASH_PGDB1_Pos)               /*!< 0x000000FF */
#define FLASH_PGDB1                    FLASH_PGDB1_Msk                         /*!< This register is used to control the program data */ 

/**************  Bits definition for FLASH_PGDB2 register    ******************/
#define FLASH_PGDB2_Pos               (0U)                                     
#define FLASH_PGDB2_Msk               (0xFFU << FLASH_PGDB2_Pos)               /*!< 0x000000FF */
#define FLASH_PGDB2                    FLASH_PGDB2_Msk                         /*!< This register is used to control the program data */ 

/**************  Bits definition for FLASH_PGDB3 register    ******************/
#define FLASH_PGDB3_Pos               (0U)                                     
#define FLASH_PGDB3_Msk               (0xFFU << FLASH_PGDB3_Pos)               /*!< 0x000000FF */
#define FLASH_PGDB3                    FLASH_PGDB3_Msk                         /*!< This register is used to control the program data */ 

/**************  Bits definition for FLASH_PGDHW0 register   ******************/
#define FLASH_PGDHW0_Pos              (0U)                                     
#define FLASH_PGDHW0_Msk              (0xFFFFU << FLASH_PGDHW0_Pos)            /*!< 0x0000FFFF */
#define FLASH_PGDHW0                   FLASH_PGDHW0_Msk                        /*!< This register is used to control the program data */ 

/**************  Bits definition for FLASH_PGDHW1 register   ******************/
#define FLASH_PGDHW1_Pos              (0U)                                     
#define FLASH_PGDHW1_Msk              (0xFFFFU << FLASH_PGDHW1_Pos)            /*!< 0x0000FFFF */
#define FLASH_PGDHW1                   FLASH_PGDHW1_Msk                        /*!< This register is used to control the program data */ 

/**************  Bits definition for FLASH_CONF register     ******************/
//#define FLASH_CONF_Pos                (0U)                                     
//#define FLASH_CONF_Msk                (0xFFFFFFFFU << FLASH_CONF_Pos)          /*!< 0xFFFFFFFF */
//#define FLASH_CONF_CONF                FLASH_CONF_Msk                          /*!< This register is used to read/write the Flash IP’s configuration register */ 

/**************  Bits definition for FLASH_SERASE register   ******************/
#define FLASH_SERASE_Pos              (0U)                                     
#define FLASH_SERASE_Msk              (0xFFFFFFFFU << FLASH_SERASE_Pos)        /*!< 0xFFFFFFFF */
#define FLASH_SERASE_SERASE            FLASH_SERASE_Msk                        /*!< This bit can be set when UNLOCK is 1 and programmer write 0xAA5555AA to this register */ 
#define FLASH_SERASE_BIT0_Pos         (0U)                                     
#define FLASH_SERASE_BIT0_Msk         (0x1U << FLASH_SERASE_BIT0_Pos)          /*!< 0x00000001 */
#define FLASH_SERASE_BIT0              FLASH_SERASE_BIT0_Msk                   /*!< This bit is used to indicate if the sector erase is ongoing or not */ 

/**************  Bits definition for FLASH_CERASE register   ******************/
#define FLASH_CERASE_Pos              (0U)                                     
#define FLASH_CERASE_Msk              (0xFFFFFFFFU << FLASH_CERASE_Pos)        /*!< 0xFFFFFFFF */
#define FLASH_CERASE_CERASE            FLASH_CERASE_Msk                        /*!< This bit can be set when UNLOCK is 1 and programmer write 0xAA5555AA to this register */ 
#define FLASH_CERASE_BIT0_Pos         (0U)                                     
#define FLASH_CERASE_BIT0_Msk         (0x1U << FLASH_CERASE_BIT0_Pos)          /*!< 0x00000001 */
#define FLASH_CERASE_BIT0              FLASH_CERASE_BIT0_Msk                   /*!< This bit is used to indicate if the chip erase is ongoing or not */ 

/**************  Bits definition for FLASH_DSTB register     ******************/
#define FLASH_DSTB_Pos                (0U)                                     
#define FLASH_DSTB_Msk                (0xFFFFFFFFU << FLASH_DSTB_Pos)          /*!< 0xFFFFFFFF */
#define FLASH_DSTB_DSTB                FLASH_DSTB_Msk                          /*!< This bit can be set when UNLOCK is 1 and programmer write 0xAA5555AA to this register */ 
#define FLASH_DSTB_BIT0_Pos           (0U)                                     
#define FLASH_DSTB_BIT0_Msk           (0x1U << FLASH_DSTB_BIT0_Pos)            /*!< 0x00000001 */
#define FLASH_DSTB_BIT0                FLASH_DSTB_BIT0_Msk                     /*!< This bit is used to indicate if the Flash IP is entering deep standby */ 


/******************************************************************************/
/*                                                                            */
/*                         GPIO controller (GPIO)                             */
/*                                                                            */
/******************************************************************************/

/**************  Bits definition for IOx_OEN register        ******************/
#define IOx_OEN_IOXOEN_Pos            (0U)                                     
#define IOx_OEN_IOXOEN_Msk            (0xFFFFU << IOx_OEN_IOXOEN_Pos)          /*!< 0x0000FFFF */
#define IOx_OEN_IOXOEN                 IOx_OEN_IOXOEN_Msk                      /*!< Each bit control the IOX’s output enable signal */

/**************  Bits definition for IOx_IE register         ******************/
#define IOx_IE_IOXIE_Pos              (0U)                                     
#define IOx_IE_IOXIE_Msk              (0xFFFFU << IOx_IE_IOXIE_Pos)            /*!< 0x0000FFFF */
#define IOx_IE_IOXIE                   IOx_IE_IOXIE_Msk                        /*!< Each bit control the IOX’s input enable signal */

/**************  Bits definition for IOx_DAT register        ******************/
#define IOx_DAT_IOXDAT_Pos            (0U)                                     
#define IOx_DAT_IOXDAT_Msk            (0xFFFFU << IOx_DAT_IOXDAT_Pos)          /*!< 0x0000FFFF */
#define IOx_DAT_IOXDAT                 IOx_DAT_IOXDAT_Msk                      /*!< Each bit control the IOX’s output data and pull low/high function */

/**************  Bits definition for IOx_ATT register        ******************/
#define IOx_ATT_IOXATT_Pos            (0U)                                     
#define IOx_ATT_IOXATT_Msk            (0xFFFFU << IOx_ATT_IOXATT_Pos)          /*!< 0x0000FFFF */
#define IOx_ATT_IOXATT                 IOx_ATT_IOXATT_Msk                      /*!< Each bit control the IOX’s attribute and pull low/high function */

/**************  Bits definition for IOx_STS register        ******************/
#define IOx_STS_IOXSTS_Pos            (0U)                                     
#define IOx_STS_IOXSTS_Msk            (0xFFFFU << IOx_STS_IOXSTS_Pos)          /*!< 0x0000FFFF */
#define IOx_STS_IOXSTS                 IOx_STS_IOXSTS_Msk                      /*!< Each bit represents the current IOX’s input data value */

///**************  Bits definition for IOx_CM register         ******************/
//#define IOx_CM_IOXCM0_Pos             (0U)                                     
//#define IOx_CM_IOXCM0_Msk             (0x1U << IOx_CM_IOXCM0_Pos)              /*!< 0x00000001 */
//#define IOx_CM_IOXCM0                  IOx_CM_IOXCM0_Msk                       /*!< IOX0’s Schmitt trigger setting, change to this register will change all setting of IOX0~IOX7 */
//#define IOx_CM_IOXCM1_7_Pos           (1U)                                     
//#define IOx_CM_IOXCM1_7_Msk           (0x7FU << IOx_CM_IOXCM1_7_Pos)           /*!< 0x000000FE */
//#define IOx_CM_IOXCM1_7                IOx_CM_IOXCM1_7_Msk                     /*!< Each bit represent the current Schmitt trigger setting of IOX1~IOX7 */
//#define IOx_CM_IOXCM8_Pos             (8U)                                     
//#define IOx_CM_IOXCM8_Msk             (0x1U << IOx_CM_IOXCM8_Pos)              /*!< 0x00000100 */
//#define IOx_CM_IOXCM8                  IOx_CM_IOXCM8_Msk                       /*!< IOX8’s Schmitt trigger setting, change to this register will change all setting of IOX8~IOX15 */
//#define IOx_CM_IOXCM9_15_Pos          (9U)                                     
//#define IOx_CM_IOXCM9_15_Msk          (0x7FU << IOx_CM_IOXCM9_15_Pos)          /*!< 0x0000FE00 */
//#define IOx_CM_IOXCM9_15               IOx_CM_IOXCM9_15_Msk                    /*!< Each bit represent the current Schmitt trigger setting of IOX9~IOX15 */
//
///**************  Bits definition for IOx_SR register         ******************/
//#define IOx_SR_IOXSR0_Pos             (0U)                                     
//#define IOx_SR_IOXSR0_Msk             (0x1U << IOx_SR_IOXSR0_Pos)              /*!< 0x00000001 */
//#define IOx_SR_IOXSR0                  IOx_SR_IOXSR0_Msk                       /*!< IOX0’s slew rate setting, change to this register will change all setting of IOX0~IOX7 */
//#define IOx_SR_IOXSR1_7_Pos           (1U)                                     
//#define IOx_SR_IOXSR1_7_Msk           (0x7FU << IOx_SR_IOXSR1_7_Pos)           /*!< 0x000000FE */
//#define IOx_SR_IOXSR1_7                IOx_SR_IOXSR1_7_Msk                     /*!< Each bit represent the current slew rate setting of IOX1~IOX7 */
//#define IOx_SR_IOXSR8_Pos             (8U)                                     
//#define IOx_SR_IOXSR8_Msk             (0x1U << IOx_SR_IOXSR8_Pos)              /*!< 0x00000100 */
//#define IOx_SR_IOXSR8                  IOx_SR_IOXSR8_Msk                       /*!< IOX8’s slew rate setting, change to this register will change all setting of IOX8~IOX15 */
//#define IOx_SR_IOXSR9_15_Pos          (9U)                                     
//#define IOx_SR_IOXSR9_15_Msk          (0x7FU << IOx_SR_IOXSR9_15_Pos)          /*!< 0x0000FE00 */
//#define IOx_SR_IOXSR9_15               IOx_SR_IOXSR9_15_Msk                    /*!< Each bit represent the current slew rate setting of IOX9~IOX15 */
//
///**************  Bits definition for IOx_DR register         ******************/
//#define IOx_DR_IOXDR0_Pos             (0U)                                     
//#define IOx_DR_IOXDR0_Msk             (0x1U << IOx_DR_IOXDR0_Pos)              /*!< 0x00000001 */
//#define IOx_DR_IOXDR0                  IOx_DR_IOXDR0_Msk                       /*!< IOX0’s driving strength setting, change to this register will change all setting of IOX0~IOX7 */
//#define IOx_DR_IOXDR1_7_Pos           (1U)                                     
//#define IOx_DR_IOXDR1_7_Msk           (0x7FU << IOx_DR_IOXDR1_7_Pos)           /*!< 0x000000FE */
//#define IOx_DR_IOXDR1_7                IOx_DR_IOXDR1_7_Msk                     /*!< Each bit represent the current driving strength setting of IOX1~IOX7 */
//#define IOx_DR_IOXDR8_Pos             (8U)                                     
//#define IOx_DR_IOXDR8_Msk             (0x1U << IOx_DR_IOXDR8_Pos)              /*!< 0x00000100 */
//#define IOx_DR_IOXDR8                  IOx_DR_IOXDR8_Msk                       /*!< IOX8’s driving strength setting, change to this register will change all setting of IOX8~IOX15 */
//#define IOx_DR_IOXDR9_15_Pos          (9U)                                     
//#define IOx_DR_IOXDR9_15_Msk          (0x7FU << IOx_DR_IOXDR9_15_Pos)          /*!< 0x0000FE00 */
//#define IOx_DR_IOXDR9_15               IOx_DR_IOXDR9_15_Msk                    /*!< Each bit represent the current driving strength setting of IOX9~IOX15 */

/**************  Bits definition for IOB_SEL register        ******************/
#define IOB_SEL_SEL1_Pos              (1U)                                     
#define IOB_SEL_SEL1_Msk              (0x1U << IOB_SEL_SEL1_Pos)               /*!< 0x00000002 */
#define IOB_SEL_SEL1                   IOB_SEL_SEL1_Msk                        /*!< IOB1 special function select register */
#define IOB_SEL_SEL2_Pos              (2U)                                     
#define IOB_SEL_SEL2_Msk              (0x1U << IOB_SEL_SEL2_Pos)               /*!< 0x00000004 */
#define IOB_SEL_SEL2                   IOB_SEL_SEL2_Msk                        /*!< IOB2 special function select register */
#define IOB_SEL_SEL6_Pos              (6U)                                     
#define IOB_SEL_SEL6_Msk              (0x1U << IOB_SEL_SEL6_Pos)               /*!< 0x00000040 */
#define IOB_SEL_SEL6                   IOB_SEL_SEL6_Msk                        /*!< IOB6 special function select register */


/**************  Bits definition for IOE_SEL register        ******************/
#define IOE_SEL_SEL7_Pos              (7U)                                     
#define IOE_SEL_SEL7_Msk              (0x1U << IOE_SEL_SEL7_Pos)               /*!< 0x00000080 */
#define IOE_SEL_SEL7                   IOE_SEL_SEL7_Msk                        /*!< IOE7 special function select register */

/**************  Bits definition for IO_MISC register        ******************/
#define IO_MISC_PLLHDIV_Pos           (0U)                                     
#define IO_MISC_PLLHDIV_Msk           (0x7U << IO_MISC_PLLHDIV_Pos)            /*!< 0x00000007 */
#define IO_MISC_PLLHDIV                IO_MISC_PLLHDIV_Msk                     /*!< When IOB1 is selected to special function 3, this register is used to control the divide ratio of PLLH’s output */
#define IO_MISC_PLLHDIV_1             (0x0U << IO_MISC_PLLHDIV_Pos)
#define IO_MISC_PLLHDIV_2             (0x1U << IO_MISC_PLLHDIV_Pos)
#define IO_MISC_PLLHDIV_4             (0x2U << IO_MISC_PLLHDIV_Pos)
#define IO_MISC_PLLHDIV_8             (0x3U << IO_MISC_PLLHDIV_Pos)
#define IO_MISC_PLLHDIV_16            (0x4U << IO_MISC_PLLHDIV_Pos)
#define IO_MISC_I2CIOC_Pos            (5U)                                     
#define IO_MISC_I2CIOC_Msk            (0x1U << IO_MISC_I2CIOC_Pos)             /*!< 0x00000020 */
#define IO_MISC_I2CIOC                 IO_MISC_I2CIOC_Msk                      /*!< This register is used to control the I2C function is at IOB or IOC */

/******************************************************************************/
/*                                                                            */
/*                         DMA controller (DMA)                               */
/*                                                                            */
/******************************************************************************/

/**************  Bits definition for DMA_IE register         ******************/
#define DMA_IE_C0PEIE_Pos             (0U)                                     
#define DMA_IE_C0PEIE_Msk             (0x1U << DMA_IE_C0PEIE_Pos)              /*!< 0x00000001 */
#define DMA_IE_C0PEIE                  DMA_IE_C0PEIE_Msk                       /*!< Channel 0 package end interrupt enable */ 
#define DMA_IE_C1PEIE_Pos             (1U)                                     
#define DMA_IE_C1PEIE_Msk             (0x1U << DMA_IE_C1PEIE_Pos)              /*!< 0x00000002 */
#define DMA_IE_C1PEIE                  DMA_IE_C1PEIE_Msk                       /*!< Channel 1 package end interrupt enable */ 
#define DMA_IE_C2PEIE_Pos             (2U)                                     
#define DMA_IE_C2PEIE_Msk             (0x1U << DMA_IE_C2PEIE_Pos)              /*!< 0x00000004 */
#define DMA_IE_C2PEIE                  DMA_IE_C2PEIE_Msk                       /*!< Channel 2 package end interrupt enable */ 
#define DMA_IE_C3PEIE_Pos             (3U)                                     
#define DMA_IE_C3PEIE_Msk             (0x1U << DMA_IE_C3PEIE_Pos)              /*!< 0x00000008 */
#define DMA_IE_C3PEIE                  DMA_IE_C3PEIE_Msk                       /*!< Channel 3 package end interrupt enable */ 
#define DMA_IE_C0FEIE_Pos             (4U)                                     
#define DMA_IE_C0FEIE_Msk             (0x1U << DMA_IE_C0FEIE_Pos)              /*!< 0x00000010 */
#define DMA_IE_C0FEIE                  DMA_IE_C0FEIE_Msk                       /*!< Channel 0 frame end interrupt enable */ 
#define DMA_IE_C1FEIE_Pos             (5U)                                     
#define DMA_IE_C1FEIE_Msk             (0x1U << DMA_IE_C1FEIE_Pos)              /*!< 0x00000020 */
#define DMA_IE_C1FEIE                  DMA_IE_C1FEIE_Msk                       /*!< Channel 1 frame end interrupt enable */ 
#define DMA_IE_C2FEIE_Pos             (6U)                                     
#define DMA_IE_C2FEIE_Msk             (0x1U << DMA_IE_C2FEIE_Pos)              /*!< 0x00000040 */
#define DMA_IE_C2FEIE                  DMA_IE_C2FEIE_Msk                       /*!< Channel 2 frame end interrupt enable */ 
#define DMA_IE_C3FEIE_Pos             (7U)                                     
#define DMA_IE_C3FEIE_Msk             (0x1U << DMA_IE_C3FEIE_Pos)              /*!< 0x00000080 */
#define DMA_IE_C3FEIE                  DMA_IE_C3FEIE_Msk                       /*!< Channel 3 frame end interrupt enable */ 
#define DMA_IE_C0DAIE_Pos             (8U)                                     
#define DMA_IE_C0DAIE_Msk             (0x1U << DMA_IE_C0DAIE_Pos)              /*!< 0x00000100 */
#define DMA_IE_C0DAIE                  DMA_IE_C0DAIE_Msk                       /*!< Channel 0 data about interrupt enable */ 
#define DMA_IE_C1DAIE_Pos             (9U)                                     
#define DMA_IE_C1DAIE_Msk             (0x1U << DMA_IE_C1DAIE_Pos)              /*!< 0x00000200 */
#define DMA_IE_C1DAIE                  DMA_IE_C1DAIE_Msk                       /*!< Channel 1 data about interrupt enable */ 
#define DMA_IE_C2DAIE_Pos             (10U)                                     
#define DMA_IE_C2DAIE_Msk             (0x1U << DMA_IE_C2DAIE_Pos)              /*!< 0x00000400 */
#define DMA_IE_C2DAIE                  DMA_IE_C2DAIE_Msk                       /*!< Channel 2 data about interrupt enable */ 
#define DMA_IE_C3DAIE_Pos             (11U)                                     
#define DMA_IE_C3DAIE_Msk             (0x1U << DMA_IE_C3DAIE_Pos)              /*!< 0x00000800 */
#define DMA_IE_C3DAIE                  DMA_IE_C3DAIE_Msk                       /*!< Channel 3 data about interrupt enable */ 

/**************  Bits definition for DMA_STS register        ******************/
#define DMA_STS_C0BUSY_Pos            (0U)                                     
#define DMA_STS_C0BUSY_Msk            (0x1U << DMA_STS_C0BUSY_Pos)             /*!< 0x00000001 */
#define DMA_STS_C0BUSY                 DMA_STS_C0BUSY_Msk                      /*!< DMA channel 0 busy register */ 
#define DMA_STS_C1BUSY_Pos            (1U)                                     
#define DMA_STS_C1BUSY_Msk            (0x1U << DMA_STS_C1BUSY_Pos)             /*!< 0x00000002 */
#define DMA_STS_C1BUSY                 DMA_STS_C1BUSY_Msk                      /*!< DMA channel 1 busy register */ 
#define DMA_STS_C2BUSY_Pos            (2U)                                     
#define DMA_STS_C2BUSY_Msk            (0x1U << DMA_STS_C2BUSY_Pos)             /*!< 0x00000004 */
#define DMA_STS_C2BUSY                 DMA_STS_C2BUSY_Msk                      /*!< DMA channel 2 busy register */ 
#define DMA_STS_C3BUSY_Pos            (3U)                                     
#define DMA_STS_C3BUSY_Msk            (0x1U << DMA_STS_C3BUSY_Pos)             /*!< 0x00000008 */
#define DMA_STS_C3BUSY                 DMA_STS_C3BUSY_Msk                      /*!< DMA channel 3 busy register */ 
#define DMA_STS_C0PE_Pos              (4U)                                     
#define DMA_STS_C0PE_Msk              (0x1U << DMA_STS_C0PE_Pos)               /*!< 0x00000010 */
#define DMA_STS_C0PE                   DMA_STS_C0PE_Msk                        /*!< Channel 0 package end interrupt flag, write 1 to clear this flag */ 
#define DMA_STS_C1PE_Pos              (5U)                                     
#define DMA_STS_C1PE_Msk              (0x1U << DMA_STS_C1PE_Pos)               /*!< 0x00000020 */
#define DMA_STS_C1PE                   DMA_STS_C1PE_Msk                        /*!< Channel 1 package end interrupt flag, write 1 to clear this flag */ 
#define DMA_STS_C2PE_Pos              (6U)                                     
#define DMA_STS_C2PE_Msk              (0x1U << DMA_STS_C2PE_Pos)               /*!< 0x00000040 */
#define DMA_STS_C2PE                   DMA_STS_C2PE_Msk                        /*!< Channel 2 package end interrupt flag, write 1 to clear this flag */ 
#define DMA_STS_C3PE_Pos              (7U)                                     
#define DMA_STS_C3PE_Msk              (0x1U << DMA_STS_C3PE_Pos)               /*!< 0x00000080 */
#define DMA_STS_C3PE                   DMA_STS_C3PE_Msk                        /*!< Channel 3 package end interrupt flag, write 1 to clear this flag */ 
#define DMA_STS_C0FE_Pos              (8U)                                     
#define DMA_STS_C0FE_Msk              (0x1U << DMA_STS_C0FE_Pos)               /*!< 0x00000100 */
#define DMA_STS_C0FE                   DMA_STS_C0FE_Msk                        /*!< Channel 0 frame end interrupt flag, write 1 to clear this flag */ 
#define DMA_STS_C1FE_Pos              (9U)                                     
#define DMA_STS_C1FE_Msk              (0x1U << DMA_STS_C1FE_Pos)               /*!< 0x00000200 */
#define DMA_STS_C1FE                   DMA_STS_C1FE_Msk                        /*!< Channel 1 frame end interrupt flag, write 1 to clear this flag */ 
#define DMA_STS_C2FE_Pos              (10U)                                     
#define DMA_STS_C2FE_Msk              (0x1U << DMA_STS_C2FE_Pos)               /*!< 0x00000400 */
#define DMA_STS_C2FE                   DMA_STS_C2FE_Msk                        /*!< Channel 2 frame end interrupt flag, write 1 to clear this flag */ 
#define DMA_STS_C3FE_Pos              (11U)                                     
#define DMA_STS_C3FE_Msk              (0x1U << DMA_STS_C3FE_Pos)               /*!< 0x00000800 */
#define DMA_STS_C3FE                   DMA_STS_C3FE_Msk                        /*!< Channel 3 frame end interrupt flag, write 1 to clear this flag */ 
#define DMA_STS_C0DA_Pos              (12U)                                     
#define DMA_STS_C0DA_Msk              (0x1U << DMA_STS_C0DA_Pos)               /*!< 0x00001000 */
#define DMA_STS_C0DA                   DMA_STS_C0DA_Msk                        /*!< Channel 0 data about interrupt flag, write 1 to clear this flag */ 
#define DMA_STS_C1DA_Pos              (13U)                                     
#define DMA_STS_C1DA_Msk              (0x1U << DMA_STS_C1DA_Pos)               /*!< 0x00002000 */
#define DMA_STS_C1DA                   DMA_STS_C1DA_Msk                        /*!< Channel 1 data about interrupt flag, write 1 to clear this flag */ 
#define DMA_STS_C2DA_Pos              (14U)                                     
#define DMA_STS_C2DA_Msk              (0x1U << DMA_STS_C2DA_Pos)               /*!< 0x00004000 */
#define DMA_STS_C2DA                   DMA_STS_C2DA_Msk                        /*!< Channel 2 data about interrupt flag, write 1 to clear this flag */ 
#define DMA_STS_C3DA_Pos              (15U)                                     
#define DMA_STS_C3DA_Msk              (0x1U << DMA_STS_C3DA_Pos)               /*!< 0x00008000 */
#define DMA_STS_C3DA                   DMA_STS_C3DA_Msk                        /*!< Channel 3 data about interrupt flag, write 1 to clear this flag */ 

/**************  Bits definition for DMA_CxCTL register      ******************/
#define DMA_CxCTL_EN_Pos              (0U)                                     
#define DMA_CxCTL_EN_Msk              (0x1U << DMA_CxCTL_EN_Pos)               /*!< 0x00000001 */
#define DMA_CxCTL_EN                   DMA_CxCTL_EN_Msk                        /*!< DMA channel enable register */ 
#define DMA_CxCTL_SIZE_Pos            (1U)                                     
#define DMA_CxCTL_SIZE_Msk            (0x3U << DMA_CxCTL_SIZE_Pos)             /*!< 0x00000006 */
#define DMA_CxCTL_SIZE                 DMA_CxCTL_SIZE_Msk                     /*!< Transfer size mode */ 
#define DMA_CxCTL_SIZE_BYTE           (0x0U << DMA_CxCTL_SIZE_Pos)             /*!< 0x00000000 */
#define DMA_CxCTL_SIZE_HWORD          (0x1U << DMA_CxCTL_SIZE_Pos)             /*!< 0x00000002 */
#define DMA_CxCTL_SIZE_WORD           (0x2U << DMA_CxCTL_SIZE_Pos)             /*!< 0x00000004 */
#define DMA_CxCTL_SMODE_Pos           (3U)                                     
#define DMA_CxCTL_SMODE_Msk           (0x3U << DMA_CxCTL_SMODE_Pos)            /*!< 0x00000018 */
#define DMA_CxCTL_SMODE                DMA_CxCTL_SMODE_Msk                     /*!< Source address mode */ 
#define DMA_CxCTL_SMODE_FIX           (0x0U << DMA_CxCTL_SMODE_Pos)            /*!< 0x00000000 */
#define DMA_CxCTL_SMODE_PEND          (0x1U << DMA_CxCTL_SMODE_Pos)            /*!< 0x00000080 */
#define DMA_CxCTL_SMODE_FEND          (0x2U << DMA_CxCTL_SMODE_Pos)            /*!< 0x00000010 */
#define DMA_CxCTL_DMODE_Pos           (5U)                                     
#define DMA_CxCTL_DMODE_Msk           (0x3U << DMA_CxCTL_DMODE_Pos)            /*!< 0x00000060 */
#define DMA_CxCTL_DMODE                DMA_CxCTL_DMODE_Msk                     /*!< Destination address mode */ 
#define DMA_CxCTL_DMODE_FIX           (0x0U << DMA_CxCTL_DMODE_Pos)            /*!< 0x00000000 */
#define DMA_CxCTL_DMODE_PEND          (0x1U << DMA_CxCTL_DMODE_Pos)            /*!< 0x00000020 */
#define DMA_CxCTL_DMODE_FEND          (0x2U << DMA_CxCTL_DMODE_Pos)            /*!< 0x00000040 */
#define DMA_CTL_DMASEL_Pos            (7U)                                     
#define DMA_CTL_DMASEL_Msk            (0x1FU << DMA_CTL_DMASEL_Pos)            /*!< 0x00000F80 */
#define DMA_CTL_DMASEL                 DMA_CTL_DMASEL_Msk                      /*!< DMA request source selection */ 
#define DMA_CTL_DMASEL_SOFT           (0x0U << DMA_CTL_DMASEL_Pos)             /*!< 0x00000000 */
#define DMA_CTL_DMASEL_UART0TX        (0x2U << DMA_CTL_DMASEL_Pos)             /*!< 0x00000100 */
#define DMA_CTL_DMASEL_UART0RX        (0x3U << DMA_CTL_DMASEL_Pos)             /*!< 0x00000180 */
#define DMA_CTL_DMASEL_UART1TX        (0x4U << DMA_CTL_DMASEL_Pos)             /*!< 0x00000200 */
#define DMA_CTL_DMASEL_UART1RX        (0x5U << DMA_CTL_DMASEL_Pos)             /*!< 0x00000280 */
#define DMA_CTL_DMASEL_UART2TX        (0x6U << DMA_CTL_DMASEL_Pos)             /*!< 0x00000300 */
#define DMA_CTL_DMASEL_UART2RX        (0x7U << DMA_CTL_DMASEL_Pos)             /*!< 0x00000380 */
#define DMA_CTL_DMASEL_UART3TX        (0x8U << DMA_CTL_DMASEL_Pos)             /*!< 0x00000400 */
#define DMA_CTL_DMASEL_UART3RX        (0x9U << DMA_CTL_DMASEL_Pos)             /*!< 0x00000480 */
#define DMA_CTL_DMASEL_UART4TX        (0xAU << DMA_CTL_DMASEL_Pos)             /*!< 0x00000500 */
#define DMA_CTL_DMASEL_UART4RX        (0xBU << DMA_CTL_DMASEL_Pos)             /*!< 0x00000580 */
#define DMA_CTL_DMASEL_UART5TX        (0xCU << DMA_CTL_DMASEL_Pos)             /*!< 0x00000600 */
#define DMA_CTL_DMASEL_UART5RX        (0xDU << DMA_CTL_DMASEL_Pos)             /*!< 0x00000680 */
#define DMA_CTL_DMASEL_ISO78160TX     (0xEU << DMA_CTL_DMASEL_Pos)             /*!< 0x00000700 */
#define DMA_CTL_DMASEL_ISO78160RX     (0xFU << DMA_CTL_DMASEL_Pos)             /*!< 0x00000780 */
#define DMA_CTL_DMASEL_ISO78161TX     (0x10U << DMA_CTL_DMASEL_Pos)            /*!< 0x00000800 */
#define DMA_CTL_DMASEL_ISO78161RX     (0x11U << DMA_CTL_DMASEL_Pos)            /*!< 0x00000880 */
#define DMA_CTL_DMASEL_TIMER0         (0x12U << DMA_CTL_DMASEL_Pos)            /*!< 0x00000900 */
#define DMA_CTL_DMASEL_TIMER1         (0x13U << DMA_CTL_DMASEL_Pos)            /*!< 0x00000980 */
#define DMA_CTL_DMASEL_TIMER2         (0x14U << DMA_CTL_DMASEL_Pos)            /*!< 0x00000A00 */
#define DMA_CTL_DMASEL_TIMER3         (0x15U << DMA_CTL_DMASEL_Pos)            /*!< 0x00000A80 */
#define DMA_CTL_DMASEL_SPI1TX         (0x16U << DMA_CTL_DMASEL_Pos)            /*!< 0x00000B00 */
#define DMA_CTL_DMASEL_SPI1RX         (0x17U << DMA_CTL_DMASEL_Pos)            /*!< 0x00000B80 */
#define DMA_CTL_DMASEL_U32K0          (0x18U << DMA_CTL_DMASEL_Pos)            /*!< 0x00000C00 */
#define DMA_CTL_DMASEL_U32K1          (0x19U << DMA_CTL_DMASEL_Pos)            /*!< 0x00000C80 */
#define DMA_CTL_DMASEL_CMP1           (0x1AU << DMA_CTL_DMASEL_Pos)            /*!< 0x00000D00 */
#define DMA_CTL_DMASEL_CMP2           (0x1BU << DMA_CTL_DMASEL_Pos)            /*!< 0x00000D80 */
//#define DMA_CTL_DMASEL_DSPPROG        (0x1CU << DMA_CTL_DMASEL_Pos)            /*!< 0x00000E00 */
//#define DMA_CTL_DMASEL_DSPHBF         (0x1DU << DMA_CTL_DMASEL_Pos)            /*!< 0x00000E80 */
#define DMA_CTL_DMASEL_SPI2TX         (0x1EU << DMA_CTL_DMASEL_Pos)            /*!< 0x00000F00 */
#define DMA_CTL_DMASEL_SPI2RX         (0x1FU << DMA_CTL_DMASEL_Pos)            /*!< 0x00000F80 */
#define DMA_CTL_TMODE_Pos             (12U)                                     
#define DMA_CTL_TMODE_Msk             (0x1U << DMA_CTL_TMODE_Pos)              /*!< 0x00001000 */
#define DMA_CTL_TMODE                  DMA_CTL_TMODE_Msk                       /*!< Transfer mode selection register */ 
#define DMA_CTL_CONT_Pos              (13U)                                     
#define DMA_CTL_CONT_Msk              (0x1U << DMA_CTL_CONT_Pos)               /*!< 0x00002000 */
#define DMA_CTL_CONT                   DMA_CTL_CONT_Msk                        /*!< Continuous mode, DMA transfer will not stop until STOP bit is set to 1 */ 
#define DMA_CTL_AESEN_Pos             (14U)                                     
#define DMA_CTL_AESEN_Msk             (0x1U << DMA_CTL_AESEN_Pos)              /*!< 0x00004000 */
#define DMA_CTL_AESEN                  DMA_CTL_AESEN_Msk                       /*!< Enable AES encrypt/decrypt function of DMA channel */ 
#define DMA_CTL_STOP_Pos              (15U)                                     
#define DMA_CTL_STOP_Msk              (0x1U << DMA_CTL_STOP_Pos)               /*!< 0x00008000 */
#define DMA_CTL_STOP                   DMA_CTL_STOP_Msk                        /*!< Force stop DMA transfer */ 
#define DMA_CTL_PLEN_Pos              (16U)                                     
#define DMA_CTL_PLEN_Msk              (0xFFU << DMA_CTL_PLEN_Pos)              /*!< 0x00FF0000 */
#define DMA_CTL_PLEN                   DMA_CTL_PLEN_Msk                        /*!< Package length register, actual transfer package length is (PLEN + 1) */ 
#define DMA_CTL_FLEN_Pos              (24U)                                     
#define DMA_CTL_FLEN_Msk              (0xFFU << DMA_CTL_FLEN_Pos)              /*!< 0xFF000000 */
#define DMA_CTL_FLEN                   DMA_CTL_FLEN_Msk                        /*!< Frame length register, actual transfer frame length is (FLEN + 1) */ 

/**************  Bits definition for DMA_CxSRC register      ******************/
#define DMA_CxSRC_SRC_Pos             (0U)                                     
#define DMA_CxSRC_SRC_Msk             (0xFFFFFFFFU << DMA_CxSRC_SRC_Pos)       /*!< 0xFFFFFFFF */
#define DMA_CxSRC_SRC                  DMA_CxSRC_SRC_Msk                       /*!< DMA source address register */ 

/**************  Bits definition for DMA_CxDST register      ******************/
#define DMA_CxDST_DST_Pos             (0U)                                     
#define DMA_CxDST_DST_Msk             (0xFFFFFFFFU << DMA_CxDST_DST_Pos)       /*!< 0xFFFFFFFF */
#define DMA_CxDST_DST                  DMA_CxDST_DST_Msk                       /*!< DMA destination address register */ 

/**************  Bits definition for DMA_CxLEN register      ******************/
#define DMA_CxLEN_CPLEN_Pos           (0U)                                     
#define DMA_CxLEN_CPLEN_Msk           (0xFFU << DMA_CxLEN_CPLEN_Pos)           /*!< 0x000000FF */
#define DMA_CxLEN_CPLEN                DMA_CxLEN_CPLEN_Msk                     /*!< Current package transferred length */ 
#define DMA_CxLEN_CFLEN_Pos           (8U)                                     
#define DMA_CxLEN_CFLEN_Msk           (0xFFU << DMA_CxLEN_CFLEN_Pos)           /*!< 0x0000FF00 */
#define DMA_CxLEN_CFLEN                DMA_CxLEN_CFLEN_Msk                     /*!< Current frame transferred length */ 

/**************  Bits definition for DMA_AESCTL register     ******************/
#define DMA_AESCTL_ENC_Pos            (0U)                                     
#define DMA_AESCTL_ENC_Msk            (0x1U << DMA_AESCTL_ENC_Pos)             /*!< 0x00000001 */
#define DMA_AESCTL_ENC                 DMA_AESCTL_ENC_Msk                      /*!< AES encode/decode selection register */ 
#define DMA_AESCTL_MODE_Pos           (2U)                                     
#define DMA_AESCTL_MODE_Msk           (0x3U << DMA_AESCTL_MODE_Pos)            /*!< 0x0000000C */
#define DMA_AESCTL_MODE                DMA_AESCTL_MODE_Msk                     /*!< AES mode selection register */ 
#define DMA_AESCTL_MODE_AES128        (0x0U << DMA_AESCTL_MODE_Pos)            /*!< 0x00000000 */
#define DMA_AESCTL_MODE_AES192        (0x1U << DMA_AESCTL_MODE_Pos)            /*!< 0x00000004 */
#define DMA_AESCTL_MODE_AES256        (0x2U << DMA_AESCTL_MODE_Pos)            /*!< 0x00000008 */

/**************  Bits definition for DMA_AESKEY0 register    ******************/
#define DMA_AESKEY0_Pos               (0U)                                     
#define DMA_AESKEY0_Msk               (0xFFFFFFFFU << DMA_AESKEY0_Pos)         /*!< 0xFFFFFFFF */
#define DMA_AESKEY0_KEY0               DMA_AESKEY0_Msk                         /*!< AES KEY register 0 */ 

/**************  Bits definition for DMA_AESKEY1 register    ******************/
#define DMA_AESKEY1_Pos               (0U)                                     
#define DMA_AESKEY1_Msk               (0xFFFFFFFFU << DMA_AESKEY1_Pos)         /*!< 0xFFFFFFFF */
#define DMA_AESKEY1_KEY1               DMA_AESKEY1_Msk                         /*!< AES KEY register 1 */ 

/**************  Bits definition for DMA_AESKEY2 register    ******************/
#define DMA_AESKEY2_Pos               (0U)                                     
#define DMA_AESKEY2_Msk               (0xFFFFFFFFU << DMA_AESKEY2_Pos)         /*!< 0xFFFFFFFF */
#define DMA_AESKEY2_KEY2               DMA_AESKEY2_Msk                         /*!< AES KEY register 2 */ 

/**************  Bits definition for DMA_AESKEY3 register    ******************/
#define DMA_AESKEY3_Pos               (0U)                                     
#define DMA_AESKEY3_Msk               (0xFFFFFFFFU << DMA_AESKEY3_Pos)         /*!< 0xFFFFFFFF */
#define DMA_AESKEY3_KEY3               DMA_AESKEY3_Msk                         /*!< AES KEY register 3 */ 

/**************  Bits definition for DMA_AESKEY4 register    ******************/
#define DMA_AESKEY4_Pos               (0U)                                     
#define DMA_AESKEY4_Msk               (0xFFFFFFFFU << DMA_AESKEY4_Pos)         /*!< 0xFFFFFFFF */
#define DMA_AESKEY4_KEY4               DMA_AESKEY4_Msk                         /*!< AES KEY register 4 */ 

/**************  Bits definition for DMA_AESKEY5 register    ******************/
#define DMA_AESKEY5_Pos               (0U)                                     
#define DMA_AESKEY5_Msk               (0xFFFFFFFFU << DMA_AESKEY5_Pos)         /*!< 0xFFFFFFFF */
#define DMA_AESKEY5_KEY5               DMA_AESKEY5_Msk                         /*!< AES KEY register 5 */ 

/**************  Bits definition for DMA_AESKEY6 register    ******************/
#define DMA_AESKEY6_Pos               (0U)                                     
#define DMA_AESKEY6_Msk               (0xFFFFFFFFU << DMA_AESKEY6_Pos)         /*!< 0xFFFFFFFF */
#define DMA_AESKEY6_KEY6               DMA_AESKEY6_Msk                         /*!< AES KEY register 6 */ 

/**************  Bits definition for DMA_AESKEY7 register    ******************/
#define DMA_AESKEY7_Pos               (0U)                                     
#define DMA_AESKEY7_Msk               (0xFFFFFFFFU << DMA_AESKEY7_Pos)         /*!< 0xFFFFFFFF */
#define DMA_AESKEY7_KEY7               DMA_AESKEY7_Msk                         /*!< AES KEY register 7 */ 

/******************************************************************************/
/*                                                                            */
/*                         UART controller (UART)                             */
/*                                                                            */
/******************************************************************************/

/**************  Bits definition for UARTx_DATA register     ******************/
#define UART_DATA_Pos                 (0U)                                     
#define UART_DATA_Msk                 (0xFFU << UART_DATA_Pos)                 /*!< 0x000000FF */
#define UART_DATA                      UART_DATA_Msk                           /*!< Receive data and Transmit data */

/**************  Bits definition for UARTx_STATE register    ******************/
//#define UART_STATE_TXFULL_Pos         (0U)                                     
//#define UART_STATE_TXFULL_Msk         (0x1U << UART_STATE_TXFULL_Pos)          /*!< 0x00000001 */
//#define UART_STATE_TXFULL              UART_STATE_TXFULL_Msk                   /*!< Transmit buffer full register */
#define UART_STATE_RXFULL_Pos         (1U)                                     
#define UART_STATE_RXFULL_Msk         (0x1U << UART_STATE_RXFULL_Pos)          /*!< 0x00000002 */
#define UART_STATE_RXFULL              UART_STATE_RXFULL_Msk                   /*!< Receive buffer full register */
#define UART_STATE_TXOV_Pos           (2U)                                     
#define UART_STATE_TXOV_Msk           (0x1U << UART_STATE_TXOV_Pos)            /*!< 0x00000004 */
#define UART_STATE_TXOV                UART_STATE_TXOV_Msk                     /*!< Transmit buffer overrun flag */
#define UART_STATE_RXOV_Pos           (3U)                                     
#define UART_STATE_RXOV_Msk           (0x1U << UART_STATE_RXOV_Pos)            /*!< 0x00000008 */
#define UART_STATE_RXOV                UART_STATE_RXOV_Msk                     /*!< Receive buffer overrun flag */
#define UART_STATE_RXPE_Pos           (4U)                                     
#define UART_STATE_RXPE_Msk           (0x1U << UART_STATE_RXPE_Pos)            /*!< 0x00000010 */
#define UART_STATE_RXPE                UART_STATE_RXPE_Msk                     /*!< Receive parity error flag */
#define UART_STATE_TXDONE_Pos         (5U)                                     
#define UART_STATE_TXDONE_Msk         (0x1U << UART_STATE_TXDONE_Pos)          /*!< 0x00000020 */
#define UART_STATE_TXDONE              UART_STATE_TXDONE_Msk                   /*!< Transmit done flag */
#define UART_STATE_RXPSTS_Pos         (6U)                                     
#define UART_STATE_RXPSTS_Msk         (0x1U << UART_STATE_RXPSTS_Pos)          /*!< 0x00000040 */
#define UART_STATE_RXPSTS              UART_STATE_RXPSTS_Msk                   /*!< Receive parity data flag */

/**************  Bits definition for UARTx_CTRL register     ******************/
#define UART_CTRL_TXEN_Pos            (0U)                                     
#define UART_CTRL_TXEN_Msk            (0x1U << UART_CTRL_TXEN_Pos)             /*!< 0x00000001 */
#define UART_CTRL_TXEN                 UART_CTRL_TXEN_Msk                      /*!< Transmit engine enable register */
#define UART_CTRL_RXEN_Pos            (1U)                                     
#define UART_CTRL_RXEN_Msk            (0x1U << UART_CTRL_RXEN_Pos)             /*!< 0x00000002 */
#define UART_CTRL_RXEN                 UART_CTRL_RXEN_Msk                      /*!< Receive engine enable register */
//#define UART_CTRL_TXIE_Pos            (2U)                                     
//#define UART_CTRL_TXIE_Msk            (0x1U << UART_CTRL_TXIE_Pos)             /*!< 0x00000004 */
//#define UART_CTRL_TXIE                 UART_CTRL_TXIE_Msk                      /*!< Transmit interrupt enable register */
#define UART_CTRL_RXIE_Pos            (3U)                                     
#define UART_CTRL_RXIE_Msk            (0x1U << UART_CTRL_RXIE_Pos)             /*!< 0x00000008 */
#define UART_CTRL_RXIE                 UART_CTRL_RXIE_Msk                      /*!< Receive interrupt enable register */
#define UART_CTRL_TXOVIE_Pos          (4U)                                     
#define UART_CTRL_TXOVIE_Msk          (0x1U << UART_CTRL_TXOVIE_Pos)           /*!< 0x00000010 */
#define UART_CTRL_TXOVIE               UART_CTRL_TXOVIE_Msk                    /*!< Transmit overrun interrupt enable register */
#define UART_CTRL_RXOVIE_Pos          (5U)                                     
#define UART_CTRL_RXOVIE_Msk          (0x1U << UART_CTRL_RXOVIE_Pos)           /*!< 0x00000020 */
#define UART_CTRL_RXOVIE               UART_CTRL_RXOVIE_Msk                    /*!< Receive overrun interrupt enable register */
//#define UART_CTRL_TEST_Pos            (6U)                                     
//#define UART_CTRL_TEST_Msk            (0x1U << UART_CTRL_TEST_Pos)             /*!< 0x00000040 */
//#define UART_CTRL_TEST                 UART_CTRL_TEST_Msk                      /*!< High speed test mode for TX only */
#define UART_CTRL_RXPEIE_Pos          (7U)                                     
#define UART_CTRL_RXPEIE_Msk          (0x1U << UART_CTRL_RXPEIE_Pos)           /*!< 0x00000080 */
#define UART_CTRL_RXPEIE               UART_CTRL_RXPEIE_Msk                    /*!< Receive parity error interrupt enable register */
#define UART_CTRL_TXDONEIE_Pos        (8U)                                     
#define UART_CTRL_TXDONEIE_Msk        (0x1U << UART_CTRL_TXDONEIE_Pos)         /*!< 0x00000100 */
#define UART_CTRL_TXDONEIE             UART_CTRL_TXDONEIE_Msk                  /*!< Transmit done interrupt enable register */

/**************  Bits definition for UARTx_INTSTS register   ******************/
//#define UART_INTSTS_TXIF_Pos          (0U)                                     
//#define UART_INTSTS_TXIF_Msk          (0x1U << UART_INTSTS_TXIF_Pos)           /*!< 0x00000001 */
//#define UART_INTSTS_TXIF               UART_INTSTS_TXIF_Msk                    /*!< Transmit interrupt flag */
#define UART_INTSTS_RXIF_Pos          (1U)                                     
#define UART_INTSTS_RXIF_Msk          (0x1U << UART_INTSTS_RXIF_Pos)           /*!< 0x00000002 */
#define UART_INTSTS_RXIF               UART_INTSTS_RXIF_Msk                    /*!< Receive interrupt flag */
#define UART_INTSTS_TXOVIF_Pos        (2U)                                     
#define UART_INTSTS_TXOVIF_Msk        (0x1U << UART_INTSTS_TXOVIF_Pos)         /*!< 0x00000004 */
#define UART_INTSTS_TXOVIF             UART_INTSTS_TXOVIF_Msk                  /*!< Transmit buffer overrun flag */
#define UART_INTSTS_RXOVIF_Pos        (3U)                                     
#define UART_INTSTS_RXOVIF_Msk        (0x1U << UART_INTSTS_RXOVIF_Pos)         /*!< 0x00000008 */
#define UART_INTSTS_RXOVIF             UART_INTSTS_RXOVIF_Msk                  /*!< Receive buffer overrun flag */
#define UART_INTSTS_RXPEIF_Pos        (4U)                                     
#define UART_INTSTS_RXPEIF_Msk        (0x1U << UART_INTSTS_RXPEIF_Pos)         /*!< 0x00000010 */
#define UART_INTSTS_RXPEIF             UART_INTSTS_RXPEIF_Msk                  /*!< Receive parity error flag */
#define UART_INTSTS_TXDONEIF_Pos      (5U)                                     
#define UART_INTSTS_TXDONEIF_Msk      (0x1U << UART_INTSTS_TXDONEIF_Pos)       /*!< 0x00000020 */
#define UART_INTSTS_TXDONEIF           UART_INTSTS_TXDONEIF_Msk                /*!< Transmit done flag */

/**************  Bits definition for UARTx_BAUDDIV register  ******************/
#define UART_BAUDDIV_Pos              (0U)                                     
#define UART_BAUDDIV_Msk              (0xFFFFFU << UART_BAUDDIV_Pos)           /*!< 0x000FFFFF */
#define UART_BAUDDIV                   UART_BAUDDIV_Msk                        /*!< Baud rate divider register */

/**************  Bits definition for UARTx_CTRL2 register    ******************/
#define UART_CTRL2_MSB_Pos            (0U)                                     
#define UART_CTRL2_MSB_Msk            (0x1U << UART_CTRL2_MSB_Pos)             /*!< 0x00000001 */
#define UART_CTRL2_MSB                 UART_CTRL2_MSB_Msk                      /*!< LSB/MSB transmit order control register */
#define UART_CTRL2_MODE_Pos           (1U)                                     
#define UART_CTRL2_MODE_Msk           (0x1U << UART_CTRL2_MODE_Pos)            /*!< 0x00000002 */
#define UART_CTRL2_MODE                UART_CTRL2_MODE_Msk                     /*!< UART mode control register */
#define UART_CTRL2_PMODE_Pos          (2U)                                     
#define UART_CTRL2_PMODE_Msk          (0x3U << UART_CTRL2_PMODE_Pos)           /*!< 0x0000000C */
#define UART_CTRL2_PMODE               UART_CTRL2_PMODE_Msk                    /*!< Parity mode control register */
#define UART_CTRL2_PMODE_EVEN         (0x0U << UART_CTRL2_PMODE_Pos)           /*!< 0x00000000 */
#define UART_CTRL2_PMODE_ODD          (0x1U << UART_CTRL2_PMODE_Pos)           /*!< 0x00000004 */
#define UART_CTRL2_PMODE_0            (0x2U << UART_CTRL2_PMODE_Pos)           /*!< 0x00000008 */
#define UART_CTRL2_PMODE_1            (0x3U << UART_CTRL2_PMODE_Pos)           /*!< 0x0000000C */


/******************************************************************************/
/*                                                                            */
/*                         U32K controller (U32K)                             */
/*                                                                            */
/******************************************************************************/

/**************  Bits definition for U32Kx_CTRL0 register    ******************/
#define U32K_CTRL0_EN_Pos             (0U)                                     
#define U32K_CTRL0_EN_Msk             (0x1U << U32K_CTRL0_EN_Pos)              /*!< 0x00000001 */
#define U32K_CTRL0_EN                  U32K_CTRL0_EN_Msk                       /*!< UART 32K controller enable register */
#define U32K_CTRL0_ACOFF_Pos          (1U)                                     
#define U32K_CTRL0_ACOFF_Msk          (0x1U << U32K_CTRL0_ACOFF_Pos)           /*!< 0x00000002 */
#define U32K_CTRL0_ACOFF               U32K_CTRL0_ACOFF_Msk                    /*!< Auto-calibration off control register */
#define U32K_CTRL0_MSB_Pos            (2U)                                     
#define U32K_CTRL0_MSB_Msk            (0x1U << U32K_CTRL0_MSB_Pos)             /*!< 0x00000004 */
#define U32K_CTRL0_MSB                 U32K_CTRL0_MSB_Msk                      /*!< UART receive order control register */ 
#define U32K_CTRL0_MODE_Pos           (3U)                                     
#define U32K_CTRL0_MODE_Msk           (0x1U << U32K_CTRL0_MODE_Pos)            /*!< 0x00000008 */
#define U32K_CTRL0_MODE                U32K_CTRL0_MODE_Msk                     /*!< UART mode control register */ 
#define U32K_CTRL0_PMODE_Pos          (4U)                                     
#define U32K_CTRL0_PMODE_Msk          (0x3U << U32K_CTRL0_PMODE_Pos)           /*!< 0x00000030 */
#define U32K_CTRL0_PMODE               U32K_CTRL0_PMODE_Msk                    /*!< Parity mode control register */ 
#define U32K_CTRL0_PMODE_EVEN         (0x0U << U32K_CTRL0_PMODE_Pos)           /*!< 0x00000000 */
#define U32K_CTRL0_PMODE_ODD          (0x1U << U32K_CTRL0_PMODE_Pos)           /*!< 0x00000010 */
#define U32K_CTRL0_PMODE_0            (0x2U << U32K_CTRL0_PMODE_Pos)           /*!< 0x00000020 */
#define U32K_CTRL0_PMODE_1            (0x3U << U32K_CTRL0_PMODE_Pos)           /*!< 0x00000030 */
#define U32K_CTRL0_DEBSEL_Pos         (6U)                                     
#define U32K_CTRL0_DEBSEL_Msk         (0x3U << U32K_CTRL0_DEBSEL_Pos)          /*!< 0x000000C0 */
#define U32K_CTRL0_DEBSEL              U32K_CTRL0_DEBSEL_Msk                   /*!< De-bounce control register */ 
#define U32K_CTRL0_DEBSEL_0           (0x0U << U32K_CTRL0_DEBSEL_Pos)          /*!< 0x00000000 */
#define U32K_CTRL0_DEBSEL_1           (0x1U << U32K_CTRL0_DEBSEL_Pos)          /*!< 0x00000040 */
#define U32K_CTRL0_DEBSEL_2           (0x2U << U32K_CTRL0_DEBSEL_Pos)          /*!< 0x00000080 */
#define U32K_CTRL0_DEBSEL_3           (0x3U << U32K_CTRL0_DEBSEL_Pos)          /*!< 0x000000C0 */
#define U32K_CTRL0_WKUMODE_Pos        (8U)                                     
#define U32K_CTRL0_WKUMODE_Msk        (0x1U << U32K_CTRL0_WKUMODE_Pos)         /*!< 0x00000100 */
#define U32K_CTRL0_WKUMODE             U32K_CTRL0_WKUMODE_Msk                  /*!< Wake-up mode control register */

/**************  Bits definition for U32Kx_CTRL1 register    ******************/
#define U32K_CTRL1_RXIE_Pos           (0U)                                     
#define U32K_CTRL1_RXIE_Msk           (0x1U << U32K_CTRL1_RXIE_Pos)            /*!< 0x00000001 */
#define U32K_CTRL1_RXIE                U32K_CTRL1_RXIE_Msk                     /*!< Receive interrupt/wake-up enable register */ 
#define U32K_CTRL1_RXPEIE_Pos         (1U)                                     
#define U32K_CTRL1_RXPEIE_Msk         (0x1U << U32K_CTRL1_RXPEIE_Pos)          /*!< 0x00000002 */
#define U32K_CTRL1_RXPEIE              U32K_CTRL1_RXPEIE_Msk                   /*!< Receive parity error interrupt/wake-up enable register */ 
#define U32K_CTRL1_RXOVIE_Pos         (2U)                                     
#define U32K_CTRL1_RXOVIE_Msk         (0x1U << U32K_CTRL1_RXOVIE_Pos)          /*!< 0x00000004 */
#define U32K_CTRL1_RXOVIE              U32K_CTRL1_RXOVIE_Msk                   /*!< Receive overrun interrupt/wake-up enable register */ 
#define U32K_CTRL1_RXSEL_Pos          (4U)                                     
#define U32K_CTRL1_RXSEL_Msk          (0x3U << U32K_CTRL1_RXSEL_Pos)           /*!< 0x00000030 */
#define U32K_CTRL1_RXSEL               U32K_CTRL1_RXSEL_Msk                    /*!< Receive data select register */ 
#define U32K_CTRL1_RXSEL_RX0          (0x0U << U32K_CTRL1_RXSEL_Pos)           /*!< 0x00000000 */
#define U32K_CTRL1_RXSEL_RX1          (0x1U << U32K_CTRL1_RXSEL_Pos)           /*!< 0x00000010 */
#define U32K_CTRL1_RXSEL_RX2          (0x2U << U32K_CTRL1_RXSEL_Pos)           /*!< 0x00000020 */
#define U32K_CTRL1_RXSEL_RX3          (0x3U << U32K_CTRL1_RXSEL_Pos)           /*!< 0x00000030 */

/**************  Bits definition for U32Kx_PHASE register    ******************/
#define U32K_PHASE_Pos                (0U)                                     
#define U32K_PHASE_Msk                (0xFFFFU << U32K_PHASE_Pos)              /*!< 0x0000FFFF */
#define U32K_PHASE                     U32K_PHASE_Msk                          /*!< Baud rate divider register */ 

/**************  Bits definition for U32Kx_DATA register     ******************/
#define U32K_DATA_Pos                 (0U)                                     
#define U32K_DATA_Msk                 (0xFFU << U32K_DATA_Pos)                 /*!< 0x000000FF */
#define U32K_DATA                      U32K_DATA_Msk                           /*!< Receive data */ 

/**************  Bits definition for U32Kx_STS register      ******************/
#define U32K_STS_RCMsk                (0x07UL)
#define U32K_STS_RXIF_Pos             (0U)                                     
#define U32K_STS_RXIF_Msk             (0x1U << U32K_STS_RXIF_Pos)              /*!< 0x00000001 */
#define U32K_STS_RXIF                  U32K_STS_RXIF_Msk                       /*!< Receive interrupt flag */ 
#define U32K_STS_RXPE_Pos             (1U)                                      
#define U32K_STS_RXPE_Msk             (0x1U << U32K_STS_RXPE_Pos)              /*!< 0x00000002 */
#define U32K_STS_RXPE                  U32K_STS_RXPE_Msk                       /*!< Receive parity error flag */ 
#define U32K_STS_RXOV_Pos             (2U)                                     
#define U32K_STS_RXOV_Msk             (0x1U << U32K_STS_RXOV_Pos)              /*!< 0x00000004 */
#define U32K_STS_RXOV                  U32K_STS_RXOV_Msk                       /*!< Receive buffer overrun flag */ 

/******************************************************************************/
/*                                                                            */
/*                         ISO7816 controller (ISO7816)                       */
/*                                                                            */
/******************************************************************************/

/**************  Bits definition for ISO7816x_BAUDDIVL register  **************/
#define ISO7816_BAUDDIVL_Pos          (0U)                                     
#define ISO7816_BAUDDIVL_Msk          (0xFFU << ISO7816_BAUDDIVL_Pos)          /*!< 0x000000FF */
#define ISO7816_BAUDDIVL               ISO7816_BAUDDIVL_Msk                    /*!< Low byte of baud-rate divider */ 

/**************  Bits definition for ISO7816x_BAUDDIVH register  **************/
#define ISO7816_BAUDDIVH_Pos          (0U)                                     
#define ISO7816_BAUDDIVH_Msk          (0xFFU << ISO7816_BAUDDIVH_Pos)          /*!< 0x000000FF */
#define ISO7816_BAUDDIVH               ISO7816_BAUDDIVH_Msk                    /*!< High byte of baud-rate divider */  

/**************  Bits definition for ISO7816x_DATA register  ******************/
#define ISO7816_DATA_Pos              (0U)                                     
#define ISO7816_DATA_Msk              (0xFFU << ISO7816_DATA_Pos)              /*!< 0x000000FF */
#define ISO7816_DATA                   ISO7816_DATA_Msk                        /*!< Transmit or Receive data */ 

/**************  Bits definition for ISO7816x_INFO register  ******************/
#define ISO7816_INFO_RCACK_Pos        (0U)                                     
#define ISO7816_INFO_RCACK_Msk        (0x1U << ISO7816_INFO_RCACK_Pos)         /*!< 0x00000001 */
#define ISO7816_INFO_RCACK             ISO7816_INFO_RCACK_Msk                  /*!< The received ACK at the end of transmit */ 
#define ISO7816_INFO_CHKSUM_Pos       (1U)                                     
#define ISO7816_INFO_CHKSUM_Msk       (0x1U << ISO7816_INFO_CHKSUM_Pos)        /*!< 0x00000002 */
#define ISO7816_INFO_CHKSUM            ISO7816_INFO_CHKSUM_Msk                 /*!< The transmitted or received data’s check sum bit */ 
#define ISO7816_INFO_RCERR_Pos        (2U)                                     
#define ISO7816_INFO_RCERR_Msk        (0x1U << ISO7816_INFO_RCERR_Pos)         /*!< 0x00000004 */
#define ISO7816_INFO_RCERR             ISO7816_INFO_RCERR_Msk                  /*!< When received data have check sum error */ 
#define ISO7816_INFO_SDERR_Pos        (3U)                                     
#define ISO7816_INFO_SDERR_Msk        (0x1U << ISO7816_INFO_SDERR_Pos)         /*!< 0x00000008 */
#define ISO7816_INFO_SDERR             ISO7816_INFO_SDERR_Msk                  /*!< When the received ACK is 0 during transmit mode */ 
#define ISO7816_INFO_LSB_Pos          (4U)                                     
#define ISO7816_INFO_LSB_Msk          (0x1U << ISO7816_INFO_LSB_Pos)           /*!< 0x00000010 */
#define ISO7816_INFO_LSB               ISO7816_INFO_LSB_Msk                    /*!< MSB/LSB transmit order control register */ 
#define ISO7816_INFO_RCIF_Pos         (5U)                                     
#define ISO7816_INFO_RCIF_Msk         (0x1U << ISO7816_INFO_RCIF_Pos)          /*!< 0x00000020 */
#define ISO7816_INFO_RCIF              ISO7816_INFO_RCIF_Msk                   /*!< Receive interrupt flag */ 
#define ISO7816_INFO_SDIF_Pos         (6U)                                     
#define ISO7816_INFO_SDIF_Msk         (0x1U << ISO7816_INFO_SDIF_Pos)          /*!< 0x00000040 */
#define ISO7816_INFO_SDIF              ISO7816_INFO_SDIF_Msk                   /*!< Transmit interrupt flag */ 
#define ISO7816_INFO_OVIF_Pos         (7U)                                    
#define ISO7816_INFO_OVIF_Msk         (0x1U << ISO7816_INFO_OVIF_Pos)          /*!< 0x00000080 */
#define ISO7816_INFO_OVIF              ISO7816_INFO_OVIF_Msk                   /*!< Receive overflow flag */ 

/**************  Bits definition for ISO7816x_CFG register   ******************/
#define ISO7816_CFG_EN_Pos            (0U)                                     
#define ISO7816_CFG_EN_Msk            (0x1U << ISO7816_CFG_EN_Pos)             /*!< 0x00000001 */
#define ISO7816_CFG_EN                 ISO7816_CFG_EN_Msk                      /*!< ISO7816 enable register */ 
#define ISO7816_CFG_CHKP_Pos          (1U)                                     
#define ISO7816_CFG_CHKP_Msk          (0x1U << ISO7816_CFG_CHKP_Pos)           /*!< 0x00000002 */
#define ISO7816_CFG_CHKP               ISO7816_CFG_CHKP_Msk                    /*!< Transmit interrupt enable register */ 
//#define ISO7816_CFG_AUTORC_Pos        (2U)                                     
//#define ISO7816_CFG_AUTORC_Msk        (0x1U << ISO7816_CFG_AUTORC_Pos)         /*!< 0x00000004 */
//#define ISO7816_CFG_AUTORC             ISO7816_CFG_AUTORC_Msk                  /*!< Receive interrupt enable register */ 
//#define ISO7816_CFG_AUTOSD_Pos        (3U)                                     
//#define ISO7816_CFG_AUTOSD_Msk        (0x1U << ISO7816_CFG_AUTOSD_Pos)         /*!< 0x00000008 */
//#define ISO7816_CFG_AUTOSD             ISO7816_CFG_AUTOSD_Msk                  /*!< ACK low period when receive an error data */ 
#define ISO7816_CFG_ACKLEN_Pos        (4U)                                     
#define ISO7816_CFG_ACKLEN_Msk        (0x1U << ISO7816_CFG_ACKLEN_Pos)         /*!< 0x00000010 */
#define ISO7816_CFG_ACKLEN             ISO7816_CFG_ACKLEN_Msk                  /*!< Automatic re-transmit when receive ACK is 0 */ 
#define ISO7816_CFG_RCIE_Pos          (5U)                                     
#define ISO7816_CFG_RCIE_Msk          (0x1U << ISO7816_CFG_RCIE_Pos)           /*!< 0x00000020 */
#define ISO7816_CFG_RCIE               ISO7816_CFG_RCIE_Msk                    /*!< Automatic response ACK as 0 when receive an error data to let transmitter re-send the data */ 
#define ISO7816_CFG_SDIE_Pos          (6U)                                     
#define ISO7816_CFG_SDIE_Msk          (0x1U << ISO7816_CFG_SDIE_Pos)           /*!< 0x00000040 */
#define ISO7816_CFG_SDIE               ISO7816_CFG_SDIE_Msk                    /*!< Parity mode control register */ 
#define ISO7816_CFG_OVIE_Pos          (7U)                                     
#define ISO7816_CFG_OVIE_Msk          (0x1U << ISO7816_CFG_OVIE_Pos)           /*!< 0x00000080 */
#define ISO7816_CFG_OVIE               ISO7816_CFG_OVIE_Msk                    /*!< Receive overrun interrupt enable register */ 

/**************  Bits definition for ISO7816x_CLK register   ******************/
#define ISO7816_CLK_CLKDIV_Pos        (0U)                                     
#define ISO7816_CLK_CLKDIV_Msk        (0x7FU << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x0000007F */
#define ISO7816_CLK_CLKDIV             ISO7816_CLK_CLKDIV_Msk                  /*!< The ISO7816 clock divider ratio */ 
#define ISO7816_CLK_CLKDIV_1          (0x0U << ISO7816_CLK_CLKDIV_Pos)         /*!< 0x00000000 */
#define ISO7816_CLK_CLKDIV_2          (0x1U << ISO7816_CLK_CLKDIV_Pos)         /*!< 0x00000001 */
#define ISO7816_CLK_CLKDIV_3          (0x2U << ISO7816_CLK_CLKDIV_Pos)         /*!< 0x00000002 */
#define ISO7816_CLK_CLKDIV_4          (0x3U << ISO7816_CLK_CLKDIV_Pos)         /*!< 0x00000003 */
#define ISO7816_CLK_CLKDIV_5          (0x4U << ISO7816_CLK_CLKDIV_Pos)         /*!< 0x00000004 */
#define ISO7816_CLK_CLKDIV_6          (0x5U << ISO7816_CLK_CLKDIV_Pos)         /*!< 0x00000005 */
#define ISO7816_CLK_CLKDIV_7          (0x6U << ISO7816_CLK_CLKDIV_Pos)         /*!< 0x00000006 */
#define ISO7816_CLK_CLKDIV_8          (0x7U << ISO7816_CLK_CLKDIV_Pos)         /*!< 0x00000007 */
#define ISO7816_CLK_CLKDIV_9          (0x8U << ISO7816_CLK_CLKDIV_Pos)         /*!< 0x00000008 */
#define ISO7816_CLK_CLKDIV_10         (0x9U << ISO7816_CLK_CLKDIV_Pos)         /*!< 0x00000009 */
#define ISO7816_CLK_CLKDIV_11         (0xAU << ISO7816_CLK_CLKDIV_Pos)         /*!< 0x0000000A */
#define ISO7816_CLK_CLKDIV_12         (0xBU << ISO7816_CLK_CLKDIV_Pos)         /*!< 0x0000000B */
#define ISO7816_CLK_CLKDIV_13         (0xCU << ISO7816_CLK_CLKDIV_Pos)         /*!< 0x0000000C */
#define ISO7816_CLK_CLKDIV_14         (0xDU << ISO7816_CLK_CLKDIV_Pos)         /*!< 0x0000000D */
#define ISO7816_CLK_CLKDIV_15         (0xEU << ISO7816_CLK_CLKDIV_Pos)         /*!< 0x0000000E */
#define ISO7816_CLK_CLKDIV_16         (0xFU << ISO7816_CLK_CLKDIV_Pos)         /*!< 0x0000000F */
#define ISO7816_CLK_CLKDIV_17         (0x10U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000010 */
#define ISO7816_CLK_CLKDIV_18         (0x11U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000011 */
#define ISO7816_CLK_CLKDIV_19         (0x12U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000012 */
#define ISO7816_CLK_CLKDIV_20         (0x13U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000013 */
#define ISO7816_CLK_CLKDIV_21         (0x14U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000014 */
#define ISO7816_CLK_CLKDIV_22         (0x15U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000015 */
#define ISO7816_CLK_CLKDIV_23         (0x16U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000016 */
#define ISO7816_CLK_CLKDIV_24         (0x17U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000017 */
#define ISO7816_CLK_CLKDIV_25         (0x18U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000018 */
#define ISO7816_CLK_CLKDIV_26         (0x19U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000019 */
#define ISO7816_CLK_CLKDIV_27         (0x1AU << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x0000001A */
#define ISO7816_CLK_CLKDIV_28         (0x1BU << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x0000001B */
#define ISO7816_CLK_CLKDIV_29         (0x1CU << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x0000001C */
#define ISO7816_CLK_CLKDIV_30         (0x1DU << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x0000001D */
#define ISO7816_CLK_CLKDIV_31         (0x1EU << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x0000001E */
#define ISO7816_CLK_CLKDIV_32         (0x1FU << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x0000001F */
#define ISO7816_CLK_CLKDIV_33         (0x20U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000020 */
#define ISO7816_CLK_CLKDIV_34         (0x21U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000021 */
#define ISO7816_CLK_CLKDIV_35         (0x22U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000022 */
#define ISO7816_CLK_CLKDIV_36         (0x23U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000023 */
#define ISO7816_CLK_CLKDIV_37         (0x24U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000024 */
#define ISO7816_CLK_CLKDIV_38         (0x25U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000025 */
#define ISO7816_CLK_CLKDIV_39         (0x26U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000026 */
#define ISO7816_CLK_CLKDIV_40         (0x27U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000027 */
#define ISO7816_CLK_CLKDIV_41         (0x28U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000028 */
#define ISO7816_CLK_CLKDIV_42         (0x29U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000029 */
#define ISO7816_CLK_CLKDIV_43         (0x2AU << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x0000002A */
#define ISO7816_CLK_CLKDIV_44         (0x2BU << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x0000002B */
#define ISO7816_CLK_CLKDIV_45         (0x2CU << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x0000002C */
#define ISO7816_CLK_CLKDIV_46         (0x2DU << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x0000002D */
#define ISO7816_CLK_CLKDIV_47         (0x2EU << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x0000002E */
#define ISO7816_CLK_CLKDIV_48         (0x2FU << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x0000002F */
#define ISO7816_CLK_CLKDIV_49         (0x30U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000030 */
#define ISO7816_CLK_CLKDIV_50         (0x31U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000031 */
#define ISO7816_CLK_CLKDIV_51         (0x32U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000032 */
#define ISO7816_CLK_CLKDIV_52         (0x33U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000033 */
#define ISO7816_CLK_CLKDIV_53         (0x34U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000034 */
#define ISO7816_CLK_CLKDIV_54         (0x35U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000035 */
#define ISO7816_CLK_CLKDIV_55         (0x36U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000036 */
#define ISO7816_CLK_CLKDIV_56         (0x37U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000037 */
#define ISO7816_CLK_CLKDIV_57         (0x38U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000038 */
#define ISO7816_CLK_CLKDIV_58         (0x39U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000039 */
#define ISO7816_CLK_CLKDIV_59         (0x3AU << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x0000003A */
#define ISO7816_CLK_CLKDIV_60         (0x3BU << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x0000003B */
#define ISO7816_CLK_CLKDIV_61         (0x3CU << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x0000003C */
#define ISO7816_CLK_CLKDIV_62         (0x3DU << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x0000003D */
#define ISO7816_CLK_CLKDIV_63         (0x3EU << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x0000003E */
#define ISO7816_CLK_CLKDIV_64         (0x3FU << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x0000003F */
#define ISO7816_CLK_CLKDIV_65         (0x40U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000040 */
#define ISO7816_CLK_CLKDIV_66         (0x41U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000041 */
#define ISO7816_CLK_CLKDIV_67         (0x42U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000042 */
#define ISO7816_CLK_CLKDIV_68         (0x43U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000043 */
#define ISO7816_CLK_CLKDIV_69         (0x44U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000044 */
#define ISO7816_CLK_CLKDIV_70         (0x45U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000045 */
#define ISO7816_CLK_CLKDIV_71         (0x46U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000046 */
#define ISO7816_CLK_CLKDIV_72         (0x47U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000047 */
#define ISO7816_CLK_CLKDIV_73         (0x48U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000048 */
#define ISO7816_CLK_CLKDIV_74         (0x49U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000049 */
#define ISO7816_CLK_CLKDIV_75         (0x4AU << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x0000004A */
#define ISO7816_CLK_CLKDIV_76         (0x4BU << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x0000004B */
#define ISO7816_CLK_CLKDIV_77         (0x4CU << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x0000004C */
#define ISO7816_CLK_CLKDIV_78         (0x4DU << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x0000004D */
#define ISO7816_CLK_CLKDIV_79         (0x4EU << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x0000004E */
#define ISO7816_CLK_CLKDIV_80         (0x4FU << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x0000004F */
#define ISO7816_CLK_CLKDIV_81         (0x50U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000050 */
#define ISO7816_CLK_CLKDIV_82         (0x51U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000051 */
#define ISO7816_CLK_CLKDIV_83         (0x52U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000052 */
#define ISO7816_CLK_CLKDIV_84         (0x53U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000053 */
#define ISO7816_CLK_CLKDIV_85         (0x54U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000054 */
#define ISO7816_CLK_CLKDIV_86         (0x55U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000055 */
#define ISO7816_CLK_CLKDIV_87         (0x56U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000056 */
#define ISO7816_CLK_CLKDIV_88         (0x57U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000057 */
#define ISO7816_CLK_CLKDIV_89         (0x58U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000058 */
#define ISO7816_CLK_CLKDIV_90         (0x59U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000059 */
#define ISO7816_CLK_CLKDIV_91         (0x5AU << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x0000005A */
#define ISO7816_CLK_CLKDIV_92         (0x5BU << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x0000005B */
#define ISO7816_CLK_CLKDIV_93         (0x5CU << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x0000005C */
#define ISO7816_CLK_CLKDIV_94         (0x5DU << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x0000005D */
#define ISO7816_CLK_CLKDIV_95         (0x5EU << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x0000005E */
#define ISO7816_CLK_CLKDIV_96         (0x5FU << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x0000005F */
#define ISO7816_CLK_CLKDIV_97         (0x60U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000060 */
#define ISO7816_CLK_CLKDIV_98         (0x61U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000061 */
#define ISO7816_CLK_CLKDIV_99         (0x62U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000062 */
#define ISO7816_CLK_CLKDIV_100        (0x63U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000063 */
#define ISO7816_CLK_CLKDIV_101        (0x64U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000064 */
#define ISO7816_CLK_CLKDIV_102        (0x65U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000065 */
#define ISO7816_CLK_CLKDIV_103        (0x66U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000066 */
#define ISO7816_CLK_CLKDIV_104        (0x67U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000067 */
#define ISO7816_CLK_CLKDIV_105        (0x68U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000068 */
#define ISO7816_CLK_CLKDIV_106        (0x69U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000069 */
#define ISO7816_CLK_CLKDIV_107        (0x6AU << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x0000006A */
#define ISO7816_CLK_CLKDIV_108        (0x6BU << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x0000006B */
#define ISO7816_CLK_CLKDIV_109        (0x6CU << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x0000006C */
#define ISO7816_CLK_CLKDIV_110        (0x6DU << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x0000006D */
#define ISO7816_CLK_CLKDIV_111        (0x6EU << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x0000006E */
#define ISO7816_CLK_CLKDIV_112        (0x6FU << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x0000006F */
#define ISO7816_CLK_CLKDIV_113        (0x70U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000070 */
#define ISO7816_CLK_CLKDIV_114        (0x71U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000071 */
#define ISO7816_CLK_CLKDIV_115        (0x72U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000072 */
#define ISO7816_CLK_CLKDIV_116        (0x73U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000073 */
#define ISO7816_CLK_CLKDIV_117        (0x74U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000074 */
#define ISO7816_CLK_CLKDIV_118        (0x75U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000075 */
#define ISO7816_CLK_CLKDIV_119        (0x76U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000076 */
#define ISO7816_CLK_CLKDIV_120        (0x77U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000077 */
#define ISO7816_CLK_CLKDIV_121        (0x78U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000078 */
#define ISO7816_CLK_CLKDIV_122        (0x79U << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x00000079 */
#define ISO7816_CLK_CLKDIV_123        (0x7AU << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x0000007A */
#define ISO7816_CLK_CLKDIV_124        (0x7BU << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x0000007B */
#define ISO7816_CLK_CLKDIV_125        (0x7CU << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x0000007C */
#define ISO7816_CLK_CLKDIV_126        (0x7DU << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x0000007D */
#define ISO7816_CLK_CLKDIV_127        (0x7EU << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x0000007E */
#define ISO7816_CLK_CLKDIV_128        (0x7FU << ISO7816_CLK_CLKDIV_Pos)        /*!< 0x0000007F */
#define ISO7816_CLK_CLKEN_Pos         (7U)                                     
#define ISO7816_CLK_CLKEN_Msk         (0x1U << ISO7816_CLK_CLKEN_Pos)          /*!< 0x00000080 */
#define ISO7816_CLK_CLKEN              ISO7816_CLK_CLKEN_Msk                   /*!< ISO7816 clock output enable */ 

/******************************************************************************/
/*                                                                            */
/*                              Timer Controller (timer)                      */
/*                                                                            */
/******************************************************************************/

/**************  Bits definition for TMRx_CTRL register      ******************/
#define TMR_CTRL_EN_Pos               (0U)                                     
#define TMR_CTRL_EN_Msk               (0x1U << TMR_CTRL_EN_Pos)                /*!< 0x00000001 */
#define TMR_CTRL_EN                    TMR_CTRL_EN_Msk                         /*!< Timer x enable control register */
#define TMR_CTRL_EXTEN_Pos            (1U)                                     
#define TMR_CTRL_EXTEN_Msk            (0x1U << TMR_CTRL_EXTEN_Pos)             /*!< 0x00000002 */
#define TMR_CTRL_EXTEN                 TMR_CTRL_EXTEN_Msk                      /*!< Select ext_clk as clock enable */
#define TMR_CTRL_EXTCLK_Pos           (2U)                                     
#define TMR_CTRL_EXTCLK_Msk           (0x1U << TMR_CTRL_EXTCLK_Pos)            /*!< 0x00000004 */
#define TMR_CTRL_EXTCLK                TMR_CTRL_EXTCLK_Msk                     /*!< Select ext_clk as clock source */
#define TMR_CTRL_INTEN_Pos            (3U)                                     
#define TMR_CTRL_INTEN_Msk            (0x1U << TMR_CTRL_INTEN_Pos)             /*!< 0x00000008 */
#define TMR_CTRL_INTEN                 TMR_CTRL_INTEN_Msk                      /*!< Timer x interrupt enable register */

/**************  Bits definition for TMRx_VALUE register     ******************/
#define TMR_VALUE_VALUE_Pos           (0U)                                     
#define TMR_VALUE_VALUE_Msk           (0xFFFFFFFFU << TMR_VALUE_VALUE_Pos)     /*!< 0xFFFFFFFF */
#define TMR_VALUE_VALUE                TMR_VALUE_VALUE_Msk                     /*!< Timer x current value register */

/**************  Bits definition for TMRx_RELOAD register    ******************/
#define TMR_RELOAD_RELOAD_Pos         (0U)                                     
#define TMR_RELOAD_RELOAD_Msk         (0xFFFFFFFFU << TMR_RELOAD_RELOAD_Pos)   /*!< 0xFFFFFFFF */
#define TMR_RELOAD_RELOAD              TMR_RELOAD_RELOAD_Msk                   /*!< Timer x reload value register.  A write to this register sets the current value */

/**************  Bits definition for TMRx_INT register       ******************/
#define TMR_INT_INT_Pos               (0U)                                     
#define TMR_INT_INT_Msk               (0x1U << TMR_INT_INT_Pos)                /*!< 0x00000001 */
#define TMR_INT_INT                    TMR_INT_INT_Msk                         /*!< Timer x interrupt status register, write 1 to clear this bit. */

/******************************************************************************/
/*                                                                            */
/*                                 PWM controller (PWM)                       */
/*                                                                            */
/******************************************************************************/

/**************  Bits definition for PWMx_CTL register       ******************/
#define PWM_CTL_IFG_Pos               (0U)                                     
#define PWM_CTL_IFG_Msk               (0x1U << PWM_CTL_IFG_Pos)                /*!< 0x00000001 */
#define PWM_CTL_IFG                    PWM_CTL_IFG_Msk                         /*!< PWM Timer x’s interrupt status flag, write 1 to clear this flag to 0 */
#define PWM_CTL_IE_Pos                (1U)                                     
#define PWM_CTL_IE_Msk                (0x1U << PWM_CTL_IE_Pos)                 /*!< 0x00000002 */
#define PWM_CTL_IE                     PWM_CTL_IE_Msk                          /*!< PWM Timer x’s interrupt enable register */
#define PWM_CTL_CLR_Pos               (2U)                                     
#define PWM_CTL_CLR_Msk               (0x1U << PWM_CTL_CLR_Pos)                /*!< 0x00000004 */
#define PWM_CTL_CLR                    PWM_CTL_CLR_Msk                         /*!< TAR clear register, when this bit is set to 1, the TAR will be clear to 0 */
#define PWM_CTL_TESL_Pos              (3U)                                     
#define PWM_CTL_TESL_Msk              (0x1U << PWM_CTL_TESL_Pos)               /*!< 0x00000008 */
#define PWM_CTL_TESL                   PWM_CTL_TESL_Msk                        /*!< Clock source selection */
#define PWM_CTL_TESL_APBDIV128        (0x0U << PWM_CTL_TESL_Pos)               /*!< 0x00000000 */
#define PWM_CTL_TESL_APBDIV1          (0x1U << PWM_CTL_TESL_Pos)               /*!< 0x00000008 */
#define PWM_CTL_MC_Pos                (4U)                                     
#define PWM_CTL_MC_Msk                (0x3U << PWM_CTL_MC_Pos)                 /*!< 0x00000030 */
#define PWM_CTL_MC                     PWM_CTL_MC_Msk                          /*!< PWM Timer mode control */
#define PWM_CTL_MC_STOP               (0x0U << PWM_CTL_MC_Pos)                 /*!< 0x00000000 */
#define PWM_CTL_MC_UP                 (0x1U << PWM_CTL_MC_Pos)                 /*!< 0x00000010 */
#define PWM_CTL_MC_CONTINUE           (0x2U << PWM_CTL_MC_Pos)                 /*!< 0x00000020 */
#define PWM_CTL_MC_UPDOWN             (0x3U << PWM_CTL_MC_Pos)                 /*!< 0x00000030 */
#define PWM_CTL_ID_Pos                (6U)                                     
#define PWM_CTL_ID_Msk                (0x3U << PWM_CTL_ID_Pos)                 /*!< 0x000000C0 */
#define PWM_CTL_ID                     PWM_CTL_ID_Msk                          /*!< PWM timer x’s Input clock divider control */
#define PWM_CTL_ID_DIV2               (0x0U << PWM_CTL_ID_Pos)                 /*!< 0x00000000 */
#define PWM_CTL_ID_DIV4               (0x1U << PWM_CTL_ID_Pos)                 /*!< 0x00000040 */
#define PWM_CTL_ID_DIV8               (0x2U << PWM_CTL_ID_Pos)                 /*!< 0x00000080 */
#define PWM_CTL_ID_DIV16              (0x3U << PWM_CTL_ID_Pos)                 /*!< 0x000000C0 */

/**************  Bits definition for PWMx_TAR register       ******************/
#define PWM_TAR_TAR_Pos               (0U)                                     
#define PWM_TAR_TAR_Msk               (0xFFFFU << PWM_TAR_TAR_Pos)             /*!< 0x0000FFFF */
#define PWM_TAR_TAR                    PWM_TAR_TAR_Msk                         /*!< PWM Timer x’s current count register */

/**************  Bits definition for PWMx_CCTLy register     ******************/
#define PWM_CCTL_CCIGG_Pos            (0U)                                     
#define PWM_CCTL_CCIGG_Msk            (0x1U << PWM_CCTL_CCIGG_Pos)             /*!< 0x00000001 */
#define PWM_CCTL_CCIGG                 PWM_CCTL_CCIGG_Msk                      /*!< Under compare mode, this bit will be set when TAR=CCRx. */
//#define PWM_CCTL_COV_Pos              (1U)                                     
//#define PWM_CCTL_COV_Msk              (0x1U << PWM_CCTL_COV_Pos)               /*!< 0x00000002 */
//#define PWM_CCTL_COV                   PWM_CCTL_COV_Msk                        /*!< Capture overflow flag, this bit will be set when the CCIFG bit is 1 and another capture event is coming */
#define PWM_CCTL_OUT_Pos              (2U)                                     
#define PWM_CCTL_OUT_Msk              (0x1U << PWM_CCTL_OUT_Pos)               /*!< 0x00000004 */
#define PWM_CCTL_OUT                   PWM_CCTL_OUT_Msk                        /*!< This bit is used to control the output value of OUTx when OUTMOD is set to 0 */
//#define PWM_CCTL_CCI_Pos              (3U)                                     
//#define PWM_CCTL_CCI_Msk              (0x1U << PWM_CCTL_CCI_Pos)               /*!< 0x00000008 */
//#define PWM_CCTL_CCI                   PWM_CCTL_CCI_Msk                        /*!< The read only register shows the current status of INx’s input */
#define PWM_CCTL_CCIE_Pos             (4U)                                     
#define PWM_CCTL_CCIE_Msk             (0x1U << PWM_CCTL_CCIE_Pos)              /*!< 0x00000010 */
#define PWM_CCTL_CCIE                  PWM_CCTL_CCIE_Msk                       /*!< Compare interrupt enable register */
#define PWM_CCTL_OUTMOD_Pos           (5U)                                     
#define PWM_CCTL_OUTMOD_Msk           (0x7U << PWM_CCTL_OUTMOD_Pos)            /*!< 0x000000E0 */
#define PWM_CCTL_OUTMOD                PWM_CCTL_OUTMOD_Msk                     /*!< Output mode selection */
#define PWM_CCTL_OUTMOD_CONST         (0x00UL << PWM_CCTL_OUTMOD_Pos) 
#define PWM_CCTL_OUTMOD_SET           (0x01UL << PWM_CCTL_OUTMOD_Pos) 
#define PWM_CCTL_OUTMOD_TOGGLE_RESET  (0x02UL << PWM_CCTL_OUTMOD_Pos) 
#define PWM_CCTL_OUTMOD_SET_RESET     (0x03UL << PWM_CCTL_OUTMOD_Pos) 
#define PWM_CCTL_OUTMOD_TOGGLE        (0x04UL << PWM_CCTL_OUTMOD_Pos) 
#define PWM_CCTL_OUTMOD_RESET         (0x05UL << PWM_CCTL_OUTMOD_Pos) 
#define PWM_CCTL_OUTMOD_TOGGLE_SET    (0x06UL << PWM_CCTL_OUTMOD_Pos) 
#define PWM_CCTL_OUTMOD_RESET_SET     (0x07UL << PWM_CCTL_OUTMOD_Pos) 
//#define PWM_CCTL_CAP_Pos              (8U)                                     
//#define PWM_CCTL_CAP_Msk              (0x1U << PWM_CCTL_CAP_Pos)               /*!< 0x00000100 */
//#define PWM_CCTL_CAP                   PWM_CCTL_CAP_Msk                        /*!< Capture/Compare mode selection */
#define PWM_CCTL_OUTEN_Pos            (9U)                                     
#define PWM_CCTL_OUTEN_Msk            (0x1U << PWM_CCTL_OUTEN_Pos)             /*!< 0x00000200 */
#define PWM_CCTL_OUTEN                 PWM_CCTL_OUTEN_Msk                      /*!< OUTx output enable control register */
//#define PWM_CCTL_SCCI_Pos             (10U)                                     
//#define PWM_CCTL_SCCI_Msk             (0x1U << PWM_CCTL_SCCI_Pos)              /*!< 0x00000400 */
//#define PWM_CCTL_SCCI                  PWM_CCTL_SCCI_Msk                       /*!< The read only register shows the INx’s input value when the TAR is equal to CCRx */
//#define PWM_CCTL_CM_Pos               (14U)                                     
//#define PWM_CCTL_CM_Msk               (0x3U << PWM_CCTL_CM_Pos)                /*!< 0x0000C000 */
//#define PWM_CCTL_CM                    PWM_CCTL_CM_Msk                         /*!< Capture edge selection */
//#define PWM_CCTL_CM_DISABLE           (0x0U << PWM_CCTL_CM_Pos)
//#define PWM_CCTL_CM_RISING            (0x1U << PWM_CCTL_CM_Pos)
//#define PWM_CCTL_CM_FALLING           (0x2U << PWM_CCTL_CM_Pos)
//#define PWM_CCTL_CM_BOTH              (0x3U << PWM_CCTL_CM_Pos)

/**************  Bits definition for PWMx_CCRy register      ******************/
#define PWM_CCR_CCR_Pos               (0U)                                     
#define PWM_CCR_CCR_Msk               (0xFFFFU << PWM_CCR_CCR_Pos)             /*!< 0x0000FFFF */
#define PWM_CCR_CCR                    PWM_CCR_CCR_Msk                         /*!< Compare/Capture data register */

/**************  Bits definition for PWM_O_SEL register      ******************/
#define PWM_O_SEL_O_SEL0_Pos          (0U)                                     
#define PWM_O_SEL_O_SEL0_Msk          (0xFU << PWM_O_SEL_O_SEL0_Pos)           /*!< 0x0000000F */
#define PWM_O_SEL_O_SEL0               PWM_O_SEL_O_SEL0_Msk                    /*!< External output PWM0’s output selection register */
#define PWM_O_SEL_O_SEL1_Pos          (4U)                                     
#define PWM_O_SEL_O_SEL1_Msk          (0xFU << PWM_O_SEL_O_SEL1_Pos)           /*!< 0x000000F0 */
#define PWM_O_SEL_O_SEL1               PWM_O_SEL_O_SEL1_Msk                    /*!< External output PWM1’s output selection register */
#define PWM_O_SEL_O_SEL2_Pos          (8U)                                     
#define PWM_O_SEL_O_SEL2_Msk          (0xFU << PWM_O_SEL_O_SEL2_Pos)           /*!< 0x000000F00 */
#define PWM_O_SEL_O_SEL2               PWM_O_SEL_O_SEL2_Msk                    /*!< External output PWM2’s output selection register */
#define PWM_O_SEL_O_SEL3_Pos          (12U)                                     
#define PWM_O_SEL_O_SEL3_Msk          (0xFU << PWM_O_SEL_O_SEL3_Pos)           /*!< 0x0000F000 */
#define PWM_O_SEL_O_SEL3               PWM_O_SEL_O_SEL3_Msk                    /*!< External output PWM3’s output selection register */

///**************  Bits definition for PWM_I_SEL01 register    ******************/
//#define PWM_I_SEL01_I_SEL00_Pos       (0U)                                     
//#define PWM_I_SEL01_I_SEL00_Msk       (0x3U << PWM_I_SEL01_I_SEL00_Pos)        /*!< 0x00000003 */
//#define PWM_I_SEL01_I_SEL00            PWM_I_SEL01_I_SEL00_Msk                 /*!< PWM0’s IN0 external input control */
//#define PWM_I_SEL01_I_SEL01_Pos       (2U)                                     
//#define PWM_I_SEL01_I_SEL01_Msk       (0x3U << PWM_I_SEL01_I_SEL01_Pos)        /*!< 0x000000C */
//#define PWM_I_SEL01_I_SEL01            PWM_I_SEL01_I_SEL01_Msk                 /*!< PWM0’s IN1 external input control */
//#define PWM_I_SEL01_I_SEL02_Pos       (4U)                                     
//#define PWM_I_SEL01_I_SEL02_Msk       (0x3U << PWM_I_SEL01_I_SEL02_Pos)        /*!< 0x00000030 */
//#define PWM_I_SEL01_I_SEL02            PWM_I_SEL01_I_SEL02_Msk                 /*!< PWM0’s IN2 external input control */
//#define PWM_I_SEL01_I_SEL10_Pos       (16U)                                     
//#define PWM_I_SEL01_I_SEL10_Msk       (0x3U << PWM_I_SEL01_I_SEL10_Pos)        /*!< 0x00030000 */
//#define PWM_I_SEL01_I_SEL10            PWM_I_SEL01_I_SEL10_Msk                 /*!< PWM1’s IN0 external input control */
//#define PWM_I_SEL01_I_SEL11_Pos       (18U)                                     
//#define PWM_I_SEL01_I_SEL11_Msk       (0x3U << PWM_I_SEL01_I_SEL11_Pos)        /*!< 0x000C0000 */
//#define PWM_I_SEL01_I_SEL11            PWM_I_SEL01_I_SEL11_Msk                 /*!< PWM1’s IN1 external input control */
//#define PWM_I_SEL01_I_SEL12_Pos       (20U)                                     
//#define PWM_I_SEL01_I_SEL12_Msk       (0x3U << PWM_I_SEL01_I_SEL12_Pos)        /*!< 0x00300000 */
//#define PWM_I_SEL01_I_SEL12            PWM_I_SEL01_I_SEL12_Msk                 /*!< PWM1’s IN2 external input control */
//
///**************  Bits definition for PWM_I_SEL23 register    ******************/
//#define PWM_I_SEL23_I_SEL20_Pos       (0U)                                     
//#define PWM_I_SEL23_I_SEL20_Msk       (0x3U << PWM_I_SEL23_I_SEL20_Pos)        /*!< 0x00000003 */
//#define PWM_I_SEL23_I_SEL20            PWM_I_SEL23_I_SEL20_Msk                 /*!< PWM2’s IN0 external input control */
//#define PWM_I_SEL23_I_SEL21_Pos       (2U)                                     
//#define PWM_I_SEL23_I_SEL21_Msk       (0x3U << PWM_I_SEL23_I_SEL21_Pos)        /*!< 0x0000000C */
//#define PWM_I_SEL23_I_SEL21            PWM_I_SEL23_I_SEL21_Msk                 /*!< PWM2’s IN1 external input control */
//#define PWM_I_SEL23_I_SEL22_Pos       (4U)                                     
//#define PWM_I_SEL23_I_SEL22_Msk       (0x3U << PWM_I_SEL23_I_SEL22_Pos)        /*!< 0x00000030 */
//#define PWM_I_SEL23_I_SEL22            PWM_I_SEL23_I_SEL22_Msk                 /*!< PWM2’s IN2 external input control */
//#define PWM_I_SEL23_I_SEL30_Pos       (16U)                                     
//#define PWM_I_SEL23_I_SEL30_Msk       (0x3U << PWM_I_SEL23_I_SEL30_Pos)        /*!< 0x00030000 */
//#define PWM_I_SEL23_I_SEL30            PWM_I_SEL23_I_SEL30_Msk                 /*!< PWM3’s IN0 external input control */
//#define PWM_I_SEL23_I_SEL31_Pos       (18U)                                     
//#define PWM_I_SEL23_I_SEL31_Msk       (0x3U << PWM_I_SEL23_I_SEL31_Pos)        /*!< 0x000C0000 */
//#define PWM_I_SEL23_I_SEL31            PWM_I_SEL23_I_SEL31_Msk                 /*!< PWM3’s IN1 external input control */
//#define PWM_I_SEL23_I_SEL32_Pos       (20U)                                     
//#define PWM_I_SEL23_I_SEL32_Msk       (0x3U << PWM_I_SEL23_I_SEL32_Pos)        /*!< 0x00300000 */
//#define PWM_I_SEL23_I_SEL32            PWM_I_SEL23_I_SEL32_Msk                 /*!< PWM3’s IN2 external input control */

/******************************************************************************/
/*                                                                            */
/*                              LCD controller (LCD)                          */
/*                                                                            */
/******************************************************************************/

/**************  Bits definition for LCD_FB00~27 register    ******************/
#define LCD_FB_WORD_Pos               (0U)                                     
#define LCD_FB_WORD_Msk               (0xFFFFFFFFU << LCD_FB_WORD_Pos)         /*!< 0xFFFFFFFF */
#define LCD_FB_WORD                    LCD_FB_WORD_Msk                         /*!< LCD Frame buffer x register bit0~31 */
#define LCD_FB_BYTE0_Pos              (0U)                                     
#define LCD_FB_BYTE0_Msk              (0xFFU << LCD_FB_BYTE0_Pos)              /*!< 0x000000FF */
#define LCD_FB_BYTE0                   LCD_FB_BYTE0_Msk                        /*!< LCD Frame buffer x register bit0~7 */
#define LCD_FB_BYTE1_Pos              (8U)                                     
#define LCD_FB_BYTE1_Msk              (0xFFU << LCD_FB_BYTE1_Pos)              /*!< 0x0000FF00 */
#define LCD_FB_BYTE1                   LCD_FB_BYTE1_Msk                        /*!< LCD Frame buffer x register bit8~15 */
#define LCD_FB_BYTE2_Pos              (16U)                                     
#define LCD_FB_BYTE2_Msk              (0xFFU << LCD_FB_BYTE2_Pos)              /*!< 0x00FF0000 */
#define LCD_FB_BYTE2                   LCD_FB_BYTE2_Msk                        /*!< LCD Frame buffer x register bit16~23 */
#define LCD_FB_BYTE3_Pos              (24U)                                     
#define LCD_FB_BYTE3_Msk              (0xFFU << LCD_FB_BYTE3_Pos)              /*!< 0xFF000000 */
#define LCD_FB_BYTE3                   LCD_FB_BYTE3_Msk                        /*!< LCD Frame buffer x register bit24~31 */

/**************  Bits definition for LCD_CTRL register       ******************/
#define LCD_CTRL_FRQ_Pos              (0U)                                     
#define LCD_CTRL_FRQ_Msk              (0x3U << LCD_CTRL_FRQ_Pos)               /*!< 0x00000003 */
#define LCD_CTRL_FRQ                   LCD_CTRL_FRQ_Msk                        /*!< LCD scan frequency */
#define LCD_CTRL_FRQ_64HZ             (0x0U << LCD_CTRL_FRQ_Pos)               /*!< 0x00000000 */
#define LCD_CTRL_FRQ_128HZ            (0x1U << LCD_CTRL_FRQ_Pos)               /*!< 0x00000001 */
#define LCD_CTRL_FRQ_256HZ            (0x2U << LCD_CTRL_FRQ_Pos)               /*!< 0x00000002 */
#define LCD_CTRL_FRQ_512HZ            (0x3U << LCD_CTRL_FRQ_Pos)               /*!< 0x00000003 */
#define LCD_CTRL_DRV_Pos              (2U)                                     
#define LCD_CTRL_DRV_Msk              (0x3U << LCD_CTRL_DRV_Pos)               /*!< 0x0000000C */
#define LCD_CTRL_DRV                   LCD_CTRL_DRV_Msk                        /*!< LCD driving resister control register */
#define LCD_CTRL_DRV_300KOHM          (0x0U << LCD_CTRL_DRV_Pos)               /*!< 0x00000000 */
#define LCD_CTRL_DRV_600KOHM          (0x1U << LCD_CTRL_DRV_Pos)               /*!< 0x00000004 */
#define LCD_CTRL_DRV_150KOHM          (0x2U << LCD_CTRL_DRV_Pos)               /*!< 0x00000008 */
#define LCD_CTRL_DRV_200KOHM          (0x3U << LCD_CTRL_DRV_Pos)               /*!< 0x0000000C */
#define LCD_CTRL_TYPE_Pos             (4U)                                     
#define LCD_CTRL_TYPE_Msk             (0x3U << LCD_CTRL_TYPE_Pos)              /*!< 0x00000030 */
#define LCD_CTRL_TYPE                  LCD_CTRL_TYPE_Msk                       /*!< LCD type control register */
#define LCD_CTRL_TYPE_4COM            (0x0U << LCD_CTRL_TYPE_Pos)              /*!< 0x00000000 */
#define LCD_CTRL_TYPE_6COM            (0x1U << LCD_CTRL_TYPE_Pos)              /*!< 0x00000010 */
#define LCD_CTRL_TYPE_8COM            (0x2U << LCD_CTRL_TYPE_Pos)              /*!< 0x00000020 */
#define LCD_CTRL_EN_Pos               (7U)                                     
#define LCD_CTRL_EN_Msk               (0x1U << LCD_CTRL_EN_Pos)                /*!< 0x00000080 */
#define LCD_CTRL_EN                    LCD_CTRL_EN_Msk                         /*!< LCD controller enable register */

/**************  Bits definition for LCD_CTRL2 register      ******************/
#define LCD_CTRL2_BKFILL_Pos          (4U)                                     
#define LCD_CTRL2_BKFILL_Msk          (0x1U << LCD_CTRL2_BKFILL_Pos)           /*!< 0x00000010 */
#define LCD_CTRL2_BKFILL               LCD_CTRL2_BKFILL_Msk                    /*!< Fill value at blank period */
#define LCD_CTRL2_FBMODE_Pos          (6U)                                     
#define LCD_CTRL2_FBMODE_Msk          (0x3U << LCD_CTRL2_FBMODE_Pos)           /*!< 0x000000C0 */
#define LCD_CTRL2_FBMODE               LCD_CTRL2_FBMODE_Msk                    /*!< LCD frame buffer switch mode control register */
#define LCD_CTRL2_FBMODE_BUFA         (0x0U << LCD_CTRL2_FBMODE_Pos)           /*!< 0x00000000 */
#define LCD_CTRL2_FBMODE_BUFAANDBUFB  (0x1U << LCD_CTRL2_FBMODE_Pos)           /*!< 0x00000040 */
#define LCD_CTRL2_FBMODE_BUFAANDBLANK (0x2U << LCD_CTRL2_FBMODE_Pos)           /*!< 0x00000080 */
#define LCD_CTRL2_SWPR_Pos            (8U)                                     
#define LCD_CTRL2_SWPR_Msk            (0xFFU << LCD_CTRL2_SWPR_Pos)            /*!< 0x000FF00 */
#define LCD_CTRL2_SWPR                 LCD_CTRL2_SWPR_Msk                     /*!< Frame buffer switch period */

/**************  Bits definition for LCD_SEGCTRL0 register   ******************/
#define LCD_SEGCTRL0_SEG0_Pos         (0U)
#define LCD_SEGCTRL0_SEG0_Msk         (0x1U << LCD_SEGCTRL0_SEG0_Pos)          /*!< 0x00000001 */
#define LCD_SEGCTRL0_SEG0             LCD_SEGCTRL0_SEG0_Msk                    /*!< SEG 0’s enable control */
#define LCD_SEGCTRL0_SEG1_Pos         (1U)
#define LCD_SEGCTRL0_SEG1_Msk         (0x1U << LCD_SEGCTRL0_SEG1_Pos)          /*!< 0x00000002 */
#define LCD_SEGCTRL0_SEG1             LCD_SEGCTRL0_SEG1_Msk                    /*!< SEG 1’s enable control */
#define LCD_SEGCTRL0_SEG2_Pos         (2U)
#define LCD_SEGCTRL0_SEG2_Msk         (0x1U << LCD_SEGCTRL0_SEG2_Pos)          /*!< 0x00000004 */
#define LCD_SEGCTRL0_SEG2             LCD_SEGCTRL0_SEG2_Msk                    /*!< SEG 2’s enable control */
#define LCD_SEGCTRL0_SEG3_Pos         (3U)
#define LCD_SEGCTRL0_SEG3_Msk         (0x1U << LCD_SEGCTRL0_SEG3_Pos)          /*!< 0x00000008 */
#define LCD_SEGCTRL0_SEG3             LCD_SEGCTRL0_SEG3_Msk                    /*!< SEG 3’s enable control */
#define LCD_SEGCTRL0_SEG4_Pos         (4U)
#define LCD_SEGCTRL0_SEG4_Msk         (0x1U << LCD_SEGCTRL0_SEG4_Pos)          /*!< 0x00000010 */
#define LCD_SEGCTRL0_SEG4             LCD_SEGCTRL0_SEG4_Msk                    /*!< SEG 4’s enable control */
#define LCD_SEGCTRL0_SEG5_Pos         (5U)
#define LCD_SEGCTRL0_SEG5_Msk         (0x1U << LCD_SEGCTRL0_SEG5_Pos)          /*!< 0x00000020 */
#define LCD_SEGCTRL0_SEG5             LCD_SEGCTRL0_SEG5_Msk                    /*!< SEG 5’s enable control */
#define LCD_SEGCTRL0_SEG6_Pos         (6U)
#define LCD_SEGCTRL0_SEG6_Msk         (0x1U << LCD_SEGCTRL0_SEG6_Pos)          /*!< 0x00000040 */
#define LCD_SEGCTRL0_SEG6             LCD_SEGCTRL0_SEG6_Msk                    /*!< SEG 6’s enable control */
#define LCD_SEGCTRL0_SEG7_Pos         (7U)
#define LCD_SEGCTRL0_SEG7_Msk         (0x1U << LCD_SEGCTRL0_SEG7_Pos)          /*!< 0x00000080 */
#define LCD_SEGCTRL0_SEG7             LCD_SEGCTRL0_SEG7_Msk                    /*!< SEG 7’s enable control */
#define LCD_SEGCTRL0_SEG8_Pos         (8U)
#define LCD_SEGCTRL0_SEG8_Msk         (0x1U << LCD_SEGCTRL0_SEG8_Pos)          /*!< 0x00000100 */
#define LCD_SEGCTRL0_SEG8             LCD_SEGCTRL0_SEG8_Msk                    /*!< SEG 8’s enable control */
#define LCD_SEGCTRL0_SEG9_Pos         (9U)
#define LCD_SEGCTRL0_SEG9_Msk         (0x1U << LCD_SEGCTRL0_SEG9_Pos)          /*!< 0x00000200 */
#define LCD_SEGCTRL0_SEG9             LCD_SEGCTRL0_SEG9_Msk                    /*!< SEG 9’s enable control */
#define LCD_SEGCTRL0_SEG10_Pos        (10U)
#define LCD_SEGCTRL0_SEG10_Msk        (0x1U << LCD_SEGCTRL0_SEG10_Pos)         /*!< 0x00000400 */
#define LCD_SEGCTRL0_SEG10             LCD_SEGCTRL0_SEG10_Msk                  /*!< SEG 10’s enable control */
#define LCD_SEGCTRL0_SEG11_Pos        (11U)
#define LCD_SEGCTRL0_SEG11_Msk        (0x1U << LCD_SEGCTRL0_SEG11_Pos)         /*!< 0x00000800 */
#define LCD_SEGCTRL0_SEG11             LCD_SEGCTRL0_SEG11_Msk                  /*!< SEG 11’s enable control */
#define LCD_SEGCTRL0_SEG12_Pos        (12U)
#define LCD_SEGCTRL0_SEG12_Msk        (0x1U << LCD_SEGCTRL0_SEG12_Pos)         /*!< 0x00001000 */
#define LCD_SEGCTRL0_SEG12             LCD_SEGCTRL0_SEG12_Msk                  /*!< SEG 12’s enable control */
#define LCD_SEGCTRL0_SEG13_Pos        (13U)
#define LCD_SEGCTRL0_SEG13_Msk        (0x1U << LCD_SEGCTRL0_SEG13_Pos)         /*!< 0x00002000 */
#define LCD_SEGCTRL0_SEG13             LCD_SEGCTRL0_SEG13_Msk                  /*!< SEG 13’s enable control */
#define LCD_SEGCTRL0_SEG14_Pos        (14U)
#define LCD_SEGCTRL0_SEG14_Msk        (0x1U << LCD_SEGCTRL0_SEG14_Pos)         /*!< 0x00004000 */
#define LCD_SEGCTRL0_SEG14             LCD_SEGCTRL0_SEG14_Msk                  /*!< SEG 14’s enable control */
#define LCD_SEGCTRL0_SEG15_Pos        (15U)
#define LCD_SEGCTRL0_SEG15_Msk        (0x1U << LCD_SEGCTRL0_SEG15_Pos)         /*!< 0x00008000 */
#define LCD_SEGCTRL0_SEG15             LCD_SEGCTRL0_SEG15_Msk                  /*!< SEG 15’s enable control */
#define LCD_SEGCTRL0_SEG16_Pos        (16U)
#define LCD_SEGCTRL0_SEG16_Msk        (0x1U << LCD_SEGCTRL0_SEG16_Pos)         /*!< 0x00010000 */
#define LCD_SEGCTRL0_SEG16             LCD_SEGCTRL0_SEG16_Msk                  /*!< SEG 16’s enable control */
#define LCD_SEGCTRL0_SEG17_Pos        (17U)
#define LCD_SEGCTRL0_SEG17_Msk        (0x1U << LCD_SEGCTRL0_SEG17_Pos)         /*!< 0x00020000 */
#define LCD_SEGCTRL0_SEG17             LCD_SEGCTRL0_SEG17_Msk                  /*!< SEG 17’s enable control */
#define LCD_SEGCTRL0_SEG18_Pos        (18U)
#define LCD_SEGCTRL0_SEG18_Msk        (0x1U << LCD_SEGCTRL0_SEG18_Pos)         /*!< 0x00040000 */
#define LCD_SEGCTRL0_SEG18             LCD_SEGCTRL0_SEG18_Msk                  /*!< SEG 18’s enable control */
#define LCD_SEGCTRL0_SEG19_Pos        (19U)
#define LCD_SEGCTRL0_SEG19_Msk        (0x1U << LCD_SEGCTRL0_SEG19_Pos)         /*!< 0x00080000 */
#define LCD_SEGCTRL0_SEG19             LCD_SEGCTRL0_SEG19_Msk                  /*!< SEG 19’s enable control */
#define LCD_SEGCTRL0_SEG20_Pos        (20U)
#define LCD_SEGCTRL0_SEG20_Msk        (0x1U << LCD_SEGCTRL0_SEG20_Pos)         /*!< 0x00100000 */
#define LCD_SEGCTRL0_SEG20             LCD_SEGCTRL0_SEG20_Msk                  /*!< SEG 20’s enable control */
#define LCD_SEGCTRL0_SEG21_Pos        (21U)
#define LCD_SEGCTRL0_SEG21_Msk        (0x1U << LCD_SEGCTRL0_SEG21_Pos)         /*!< 0x00200000 */
#define LCD_SEGCTRL0_SEG21             LCD_SEGCTRL0_SEG21_Msk                  /*!< SEG 21’s enable control */
#define LCD_SEGCTRL0_SEG22_Pos        (22U)
#define LCD_SEGCTRL0_SEG22_Msk        (0x1U << LCD_SEGCTRL0_SEG22_Pos)         /*!< 0x00400000 */
#define LCD_SEGCTRL0_SEG22             LCD_SEGCTRL0_SEG22_Msk                  /*!< SEG 22’s enable control */
#define LCD_SEGCTRL0_SEG23_Pos        (23U)
#define LCD_SEGCTRL0_SEG23_Msk        (0x1U << LCD_SEGCTRL0_SEG23_Pos)         /*!< 0x00800000 */
#define LCD_SEGCTRL0_SEG23             LCD_SEGCTRL0_SEG23_Msk                  /*!< SEG 23’s enable control */
#define LCD_SEGCTRL0_SEG24_Pos        (24U)
#define LCD_SEGCTRL0_SEG24_Msk        (0x1U << LCD_SEGCTRL0_SEG24_Pos)         /*!< 0x01000000 */
#define LCD_SEGCTRL0_SEG24             LCD_SEGCTRL0_SEG24_Msk                  /*!< SEG 24’s enable control */
#define LCD_SEGCTRL0_SEG25_Pos        (25U)
#define LCD_SEGCTRL0_SEG25_Msk        (0x1U << LCD_SEGCTRL0_SEG25_Pos)         /*!< 0x02000000 */
#define LCD_SEGCTRL0_SEG25             LCD_SEGCTRL0_SEG25_Msk                  /*!< SEG 25’s enable control */
#define LCD_SEGCTRL0_SEG26_Pos        (26U)
#define LCD_SEGCTRL0_SEG26_Msk        (0x1U << LCD_SEGCTRL0_SEG26_Pos)         /*!< 0x04000000 */
#define LCD_SEGCTRL0_SEG26             LCD_SEGCTRL0_SEG26_Msk                  /*!< SEG 26’s enable control */
#define LCD_SEGCTRL0_SEG27_Pos        (27U)
#define LCD_SEGCTRL0_SEG27_Msk        (0x1U << LCD_SEGCTRL0_SEG27_Pos)         /*!< 0x08000000 */
#define LCD_SEGCTRL0_SEG27             LCD_SEGCTRL0_SEG27_Msk                  /*!< SEG 27’s enable control */
#define LCD_SEGCTRL0_SEG28_Pos        (28U)
#define LCD_SEGCTRL0_SEG28_Msk        (0x1U << LCD_SEGCTRL0_SEG28_Pos)         /*!< 0x10000000 */
#define LCD_SEGCTRL0_SEG28             LCD_SEGCTRL0_SEG28_Msk                  /*!< SEG 28’s enable control */
#define LCD_SEGCTRL0_SEG29_Pos        (29U)
#define LCD_SEGCTRL0_SEG29_Msk        (0x1U << LCD_SEGCTRL0_SEG29_Pos)         /*!< 0x20000000 */
#define LCD_SEGCTRL0_SEG29             LCD_SEGCTRL0_SEG29_Msk                  /*!< SEG 29’s enable control */
#define LCD_SEGCTRL0_SEG30_Pos        (30U)
#define LCD_SEGCTRL0_SEG30_Msk        (0x1U << LCD_SEGCTRL0_SEG30_Pos)         /*!< 0x40000000 */
#define LCD_SEGCTRL0_SEG30             LCD_SEGCTRL0_SEG30_Msk                  /*!< SEG 30’s enable control */
#define LCD_SEGCTRL0_SEG31_Pos        (31U)
#define LCD_SEGCTRL0_SEG31_Msk        (0x1U << LCD_SEGCTRL0_SEG31_Pos)         /*!< 0x80000000 */
#define LCD_SEGCTRL0_SEG31             LCD_SEGCTRL0_SEG31_Msk                  /*!< SEG 31’s enable control */

/**************  Bits definition for LCD_SEGCTRL1 register   ******************/
#define LCD_SEGCTRL1_SEG32_Pos        (0U)
#define LCD_SEGCTRL1_SEG32_Msk        (0x1U << LCD_SEGCTRL1_SEG32_Pos)         /*!< 0x00000001 */
#define LCD_SEGCTRL1_SEG32             LCD_SEGCTRL1_SEG32_Msk                  /*!< SEG 32’s enable control */
#define LCD_SEGCTRL1_SEG33_Pos        (1U)
#define LCD_SEGCTRL1_SEG33_Msk        (0x1U << LCD_SEGCTRL1_SEG33_Pos)         /*!< 0x00000002 */
#define LCD_SEGCTRL1_SEG33             LCD_SEGCTRL1_SEG33_Msk                  /*!< SEG 33’s enable control */
#define LCD_SEGCTRL1_SEG34_Pos        (2U)
#define LCD_SEGCTRL1_SEG34_Msk        (0x1U << LCD_SEGCTRL1_SEG34_Pos)         /*!< 0x00000004 */
#define LCD_SEGCTRL1_SEG34             LCD_SEGCTRL1_SEG34_Msk                  /*!< SEG 34’s enable control */
#define LCD_SEGCTRL1_SEG35_Pos        (3U)
#define LCD_SEGCTRL1_SEG35_Msk        (0x1U << LCD_SEGCTRL1_SEG35_Pos)         /*!< 0x00000008 */
#define LCD_SEGCTRL1_SEG35             LCD_SEGCTRL1_SEG35_Msk                  /*!< SEG 35’s enable control */
#define LCD_SEGCTRL1_SEG36_Pos        (4U)
#define LCD_SEGCTRL1_SEG36_Msk        (0x1U << LCD_SEGCTRL1_SEG36_Pos)         /*!< 0x00000010 */
#define LCD_SEGCTRL1_SEG36             LCD_SEGCTRL1_SEG36_Msk                  /*!< SEG 36’s enable control */
#define LCD_SEGCTRL1_SEG37_Pos        (5U)
#define LCD_SEGCTRL1_SEG37_Msk        (0x1U << LCD_SEGCTRL1_SEG37_Pos)         /*!< 0x00000020 */
#define LCD_SEGCTRL1_SEG37             LCD_SEGCTRL1_SEG37_Msk                  /*!< SEG 37’s enable control */
#define LCD_SEGCTRL1_SEG38_Pos        (6U)
#define LCD_SEGCTRL1_SEG38_Msk        (0x1U << LCD_SEGCTRL1_SEG38_Pos)         /*!< 0x00000040 */
#define LCD_SEGCTRL1_SEG38             LCD_SEGCTRL1_SEG38_Msk                  /*!< SEG 38’s enable control */
#define LCD_SEGCTRL1_SEG39_Pos        (7U)
#define LCD_SEGCTRL1_SEG39_Msk        (0x1U << LCD_SEGCTRL1_SEG39_Pos)         /*!< 0x00000080 */
#define LCD_SEGCTRL1_SEG39             LCD_SEGCTRL1_SEG39_Msk                  /*!< SEG 39’s enable control */
#define LCD_SEGCTRL1_SEG40_Pos        (8U)
#define LCD_SEGCTRL1_SEG40_Msk        (0x1U << LCD_SEGCTRL1_SEG40_Pos)         /*!< 0x00000100 */
#define LCD_SEGCTRL1_SEG40             LCD_SEGCTRL1_SEG40_Msk                  /*!< SEG 40’s enable control */
#define LCD_SEGCTRL1_SEG41_Pos        (9U)
#define LCD_SEGCTRL1_SEG41_Msk        (0x1U << LCD_SEGCTRL1_SEG41_Pos)         /*!< 0x00000200 */
#define LCD_SEGCTRL1_SEG41             LCD_SEGCTRL1_SEG41_Msk                  /*!< SEG 41’s enable control */
#define LCD_SEGCTRL1_SEG42_Pos        (10U)
#define LCD_SEGCTRL1_SEG42_Msk        (0x1U << LCD_SEGCTRL1_SEG42_Pos)         /*!< 0x00000400 */
#define LCD_SEGCTRL1_SEG42             LCD_SEGCTRL1_SEG42_Msk                  /*!< SEG 42’s enable control */
#define LCD_SEGCTRL1_SEG43_Pos        (11U)
#define LCD_SEGCTRL1_SEG43_Msk        (0x1U << LCD_SEGCTRL1_SEG43_Pos)         /*!< 0x00000800 */
#define LCD_SEGCTRL1_SEG43             LCD_SEGCTRL1_SEG43_Msk                  /*!< SEG 43’s enable control */
#define LCD_SEGCTRL1_SEG44_Pos        (12U)
#define LCD_SEGCTRL1_SEG44_Msk        (0x1U << LCD_SEGCTRL1_SEG44_Pos)         /*!< 0x00001000 */
#define LCD_SEGCTRL1_SEG44             LCD_SEGCTRL1_SEG44_Msk                  /*!< SEG 44’s enable control */
#define LCD_SEGCTRL1_SEG45_Pos        (13U)
#define LCD_SEGCTRL1_SEG45_Msk        (0x1U << LCD_SEGCTRL1_SEG45_Pos)         /*!< 0x00002000 */
#define LCD_SEGCTRL1_SEG45             LCD_SEGCTRL1_SEG45_Msk                  /*!< SEG 45’s enable control */
#define LCD_SEGCTRL1_SEG46_Pos        (14U)
#define LCD_SEGCTRL1_SEG46_Msk        (0x1U << LCD_SEGCTRL1_SEG46_Pos)         /*!< 0x00004000 */
#define LCD_SEGCTRL1_SEG46             LCD_SEGCTRL1_SEG46_Msk                  /*!< SEG 46’s enable control */
#define LCD_SEGCTRL1_SEG47_Pos        (15U)
#define LCD_SEGCTRL1_SEG47_Msk        (0x1U << LCD_SEGCTRL1_SEG47_Pos)         /*!< 0x00008000 */
#define LCD_SEGCTRL1_SEG47             LCD_SEGCTRL1_SEG47_Msk                  /*!< SEG 47’s enable control */
#define LCD_SEGCTRL1_SEG48_Pos        (16U)
#define LCD_SEGCTRL1_SEG48_Msk        (0x1U << LCD_SEGCTRL1_SEG48_Pos)         /*!< 0x00010000 */
#define LCD_SEGCTRL1_SEG48             LCD_SEGCTRL1_SEG48_Msk                  /*!< SEG 48’s enable control */
#define LCD_SEGCTRL1_SEG49_Pos        (17U)
#define LCD_SEGCTRL1_SEG49_Msk        (0x1U << LCD_SEGCTRL1_SEG49_Pos)         /*!< 0x00020000 */
#define LCD_SEGCTRL1_SEG49             LCD_SEGCTRL1_SEG49_Msk                  /*!< SEG 49’s enable control */
#define LCD_SEGCTRL1_SEG50_Pos        (18U)
#define LCD_SEGCTRL1_SEG50_Msk        (0x1U << LCD_SEGCTRL1_SEG50_Pos)         /*!< 0x00040000 */
#define LCD_SEGCTRL1_SEG50             LCD_SEGCTRL1_SEG50_Msk                  /*!< SEG 50’s enable control */
#define LCD_SEGCTRL1_SEG51_Pos        (19U)
#define LCD_SEGCTRL1_SEG51_Msk        (0x1U << LCD_SEGCTRL1_SEG51_Pos)         /*!< 0x00080000 */
#define LCD_SEGCTRL1_SEG51             LCD_SEGCTRL1_SEG51_Msk                  /*!< SEG 51’s enable control */
#define LCD_SEGCTRL1_SEG52_Pos        (20U)
#define LCD_SEGCTRL1_SEG52_Msk        (0x1U << LCD_SEGCTRL1_SEG52_Pos)         /*!< 0x00100000 */
#define LCD_SEGCTRL1_SEG52             LCD_SEGCTRL1_SEG52_Msk                  /*!< SEG 52’s enable control */
#define LCD_SEGCTRL1_SEG53_Pos        (21U)
#define LCD_SEGCTRL1_SEG53_Msk        (0x1U << LCD_SEGCTRL1_SEG53_Pos)         /*!< 0x00200000 */
#define LCD_SEGCTRL1_SEG53             LCD_SEGCTRL1_SEG53_Msk                  /*!< SEG 53’s enable control */
#define LCD_SEGCTRL1_SEG54_Pos        (22U)
#define LCD_SEGCTRL1_SEG54_Msk        (0x1U << LCD_SEGCTRL1_SEG54_Pos)         /*!< 0x00400000 */
#define LCD_SEGCTRL1_SEG54             LCD_SEGCTRL1_SEG54_Msk                  /*!< SEG 54’s enable control */
#define LCD_SEGCTRL1_SEG55_Pos        (23U)
#define LCD_SEGCTRL1_SEG55_Msk        (0x1U << LCD_SEGCTRL1_SEG55_Pos)         /*!< 0x00800000 */
#define LCD_SEGCTRL1_SEG55             LCD_SEGCTRL1_SEG55_Msk                  /*!< SEG 55’s enable control */
#define LCD_SEGCTRL1_SEG56_Pos        (24U)
#define LCD_SEGCTRL1_SEG56_Msk        (0x1U << LCD_SEGCTRL1_SEG56_Pos)         /*!< 0x01000000 */
#define LCD_SEGCTRL1_SEG56             LCD_SEGCTRL1_SEG56_Msk                  /*!< SEG 56’s enable control */
#define LCD_SEGCTRL1_SEG57_Pos        (25U)
#define LCD_SEGCTRL1_SEG57_Msk        (0x1U << LCD_SEGCTRL1_SEG57_Pos)         /*!< 0x02000000 */
#define LCD_SEGCTRL1_SEG57             LCD_SEGCTRL1_SEG57_Msk                  /*!< SEG 57’s enable control */
#define LCD_SEGCTRL1_SEG58_Pos        (26U)
#define LCD_SEGCTRL1_SEG58_Msk        (0x1U << LCD_SEGCTRL1_SEG58_Pos)         /*!< 0x04000000 */
#define LCD_SEGCTRL1_SEG58             LCD_SEGCTRL1_SEG58_Msk                  /*!< SEG 58’s enable control */
#define LCD_SEGCTRL1_SEG59_Pos        (27U)
#define LCD_SEGCTRL1_SEG59_Msk        (0x1U << LCD_SEGCTRL1_SEG59_Pos)         /*!< 0x08000000 */
#define LCD_SEGCTRL1_SEG59             LCD_SEGCTRL1_SEG59_Msk                  /*!< SEG 59’s enable control */
#define LCD_SEGCTRL1_SEG60_Pos        (28U)
#define LCD_SEGCTRL1_SEG60_Msk        (0x1U << LCD_SEGCTRL1_SEG60_Pos)         /*!< 0x10000000 */
#define LCD_SEGCTRL1_SEG60             LCD_SEGCTRL1_SEG60_Msk                  /*!< SEG 60’s enable control */
#define LCD_SEGCTRL1_SEG61_Pos        (29U)
#define LCD_SEGCTRL1_SEG61_Msk        (0x1U << LCD_SEGCTRL1_SEG61_Pos)         /*!< 0x20000000 */
#define LCD_SEGCTRL1_SEG61             LCD_SEGCTRL1_SEG61_Msk                  /*!< SEG 61’s enable control */
#define LCD_SEGCTRL1_SEG62_Pos        (30U)
#define LCD_SEGCTRL1_SEG62_Msk        (0x1U << LCD_SEGCTRL1_SEG62_Pos)         /*!< 0x40000000 */
#define LCD_SEGCTRL1_SEG62             LCD_SEGCTRL1_SEG62_Msk                  /*!< SEG 62’s enable control */
#define LCD_SEGCTRL1_SEG63_Pos        (31U)
#define LCD_SEGCTRL1_SEG63_Msk        (0x1U << LCD_SEGCTRL1_SEG63_Pos)         /*!< 0x80000000 */
#define LCD_SEGCTRL1_SEG63             LCD_SEGCTRL1_SEG63_Msk                  /*!< SEG 63’s enable control */

/**************  Bits definition for LCD_SEGCTRL2 register   ******************/
#define LCD_SEGCTRL2_SEG64_Pos        (0U)
#define LCD_SEGCTRL2_SEG64_Msk        (0x1U << LCD_SEGCTRL2_SEG64_Pos)         /*!< 0x00000001 */
#define LCD_SEGCTRL2_SEG64             LCD_SEGCTRL2_SEG64_Msk                  /*!< SEG 64’s enable control */
#define LCD_SEGCTRL2_SEG65_Pos        (1U)
#define LCD_SEGCTRL2_SEG65_Msk        (0x1U << LCD_SEGCTRL2_SEG65_Pos)         /*!< 0x00000002 */
#define LCD_SEGCTRL2_SEG65             LCD_SEGCTRL2_SEG65_Msk                  /*!< SEG 65’s enable control */
#define LCD_SEGCTRL2_SEG66_Pos        (2U)
#define LCD_SEGCTRL2_SEG66_Msk        (0x1U << LCD_SEGCTRL2_SEG66_Pos)         /*!< 0x00000004 */
#define LCD_SEGCTRL2_SEG66             LCD_SEGCTRL2_SEG66_Msk                  /*!< SEG 66’s enable control */
#define LCD_SEGCTRL2_SEG67_Pos        (3U)
#define LCD_SEGCTRL2_SEG67_Msk        (0x1U << LCD_SEGCTRL2_SEG67_Pos)         /*!< 0x00000008 */
#define LCD_SEGCTRL2_SEG67             LCD_SEGCTRL2_SEG67_Msk                  /*!< SEG 67’s enable control */
#define LCD_SEGCTRL2_SEG68_Pos        (4U)
#define LCD_SEGCTRL2_SEG68_Msk        (0x1U << LCD_SEGCTRL2_SEG68_Pos)         /*!< 0x00000010 */
#define LCD_SEGCTRL2_SEG68             LCD_SEGCTRL2_SEG68_Msk                  /*!< SEG 68’s enable control */
#define LCD_SEGCTRL2_SEG69_Pos        (5U)
#define LCD_SEGCTRL2_SEG69_Msk        (0x1U << LCD_SEGCTRL2_SEG69_Pos)         /*!< 0x00000020 */
#define LCD_SEGCTRL2_SEG69             LCD_SEGCTRL2_SEG69_Msk                  /*!< SEG 69’s enable control */
#define LCD_SEGCTRL2_SEG70_Pos        (6U)
#define LCD_SEGCTRL2_SEG70_Msk        (0x1U << LCD_SEGCTRL2_SEG70_Pos)         /*!< 0x00000040 */
#define LCD_SEGCTRL2_SEG70             LCD_SEGCTRL2_SEG70_Msk                  /*!< SEG 70’s enable control */
#define LCD_SEGCTRL2_SEG71_Pos        (7U)
#define LCD_SEGCTRL2_SEG71_Msk        (0x1U << LCD_SEGCTRL2_SEG71_Pos)         /*!< 0x00000080 */
#define LCD_SEGCTRL2_SEG71             LCD_SEGCTRL2_SEG71_Msk                  /*!< SEG 71’s enable control */
#define LCD_SEGCTRL2_SEG72_Pos        (8U)
#define LCD_SEGCTRL2_SEG72_Msk        (0x1U << LCD_SEGCTRL2_SEG72_Pos)         /*!< 0x00000100 */
#define LCD_SEGCTRL2_SEG72             LCD_SEGCTRL2_SEG72_Msk                  /*!< SEG 72’s enable control */
#define LCD_SEGCTRL2_SEG73_Pos        (9U)
#define LCD_SEGCTRL2_SEG73_Msk        (0x1U << LCD_SEGCTRL2_SEG73_Pos)         /*!< 0x00000200 */
#define LCD_SEGCTRL2_SEG73             LCD_SEGCTRL2_SEG73_Msk                  /*!< SEG 73’s enable control */
#define LCD_SEGCTRL2_SEG74_Pos        (10U)
#define LCD_SEGCTRL2_SEG74_Msk        (0x1U << LCD_SEGCTRL2_SEG74_Pos)         /*!< 0x00000400 */
#define LCD_SEGCTRL2_SEG74             LCD_SEGCTRL2_SEG74_Msk                  /*!< SEG 74’s enable control */
#define LCD_SEGCTRL2_SEG75_Pos        (11U)
#define LCD_SEGCTRL2_SEG75_Msk        (0x1U << LCD_SEGCTRL2_SEG75_Pos)         /*!< 0x00000800 */
#define LCD_SEGCTRL2_SEG75             LCD_SEGCTRL2_SEG75_Msk                  /*!< SEG 75’s enable control */
#define LCD_SEGCTRL2_SEG76_Pos        (12U)
#define LCD_SEGCTRL2_SEG76_Msk        (0x1U << LCD_SEGCTRL2_SEG76_Pos)         /*!< 0x00001000 */
#define LCD_SEGCTRL2_SEG76             LCD_SEGCTRL2_SEG76_Msk                  /*!< SEG 76’s enable control */
#define LCD_SEGCTRL2_SEG77_Pos        (13U)
#define LCD_SEGCTRL2_SEG77_Msk        (0x1U << LCD_SEGCTRL2_SEG77_Pos)         /*!< 0x00002000 */
#define LCD_SEGCTRL2_SEG77             LCD_SEGCTRL2_SEG77_Msk                  /*!< SEG 77’s enable control */
#define LCD_SEGCTRL2_SEG78_Pos        (14U)
#define LCD_SEGCTRL2_SEG78_Msk        (0x1U << LCD_SEGCTRL2_SEG78_Pos)         /*!< 0x00004000 */
#define LCD_SEGCTRL2_SEG78             LCD_SEGCTRL2_SEG78_Msk                  /*!< SEG 78’s enable control */
#define LCD_SEGCTRL2_SEG79_Pos        (15U)
#define LCD_SEGCTRL2_SEG79_Msk        (0x1U << LCD_SEGCTRL2_SEG79_Pos)         /*!< 0x00008000 */
#define LCD_SEGCTRL2_SEG79             LCD_SEGCTRL2_SEG79_Msk                  /*!< SEG 79’s enable control */

/******************************************************************************/
/*                                                                            */
/*                               SPI controller (SPI)                         */
/*                                                                            */
/******************************************************************************/

/**************  Bits definition for SPIx_CTRL register      ******************/
#define SPI_CTRL_SCKSEL_Pos           (0U)                                     
#define SPI_CTRL_SCKSEL_Msk           (0x7U << SPI_CTRL_SCKSEL_Pos)            /*!< 0x00000007 */
#define SPI_CTRL_SCKSEL                SPI_CTRL_SCKSEL_Msk                     /*!< Master mode clock selection */
#define SPI_CTRL_SCKSEL_0             (0x1U << SPI_CTRL_SCKSEL_Pos)            /*!< 0x00000001 */
#define SPI_CTRL_SCKSEL_1             (0x2U << SPI_CTRL_SCKSEL_Pos)            /*!< 0x00000002 */
#define SPI_CTRL_SCKSEL_2             (0x4U << SPI_CTRL_SCKSEL_Pos)            /*!< 0x00000004 */
#define SPI_CTRL_SCKPOL_Pos           (4U)                                     
#define SPI_CTRL_SCKPOL_Msk           (0x1U << SPI_CTRL_SCKPOL_Pos)            /*!< 0x00000010 */
#define SPI_CTRL_SCKPOL                SPI_CTRL_SCKPOL_Msk                     /*!< SPI clock polarity */
#define SPI_CTRL_SCKPHA_Pos           (5U)                                     
#define SPI_CTRL_SCKPHA_Msk           (0x1U << SPI_CTRL_SCKPHA_Pos)            /*!< 0x00000020 */
#define SPI_CTRL_SCKPHA                SPI_CTRL_SCKPHA_Msk                     /*!< SPI clock phase */
#define SPI_CTRL_MOD_Pos              (8U)                                     
#define SPI_CTRL_MOD_Msk              (0x1U << SPI_CTRL_MOD_Pos)               /*!< 0x00000100 */
#define SPI_CTRL_MOD                   SPI_CTRL_MOD_Msk                        /*!< SPI Mode Selection register */
#define SPI_CTRL_SWAP_Pos             (9U)                                     
#define SPI_CTRL_SWAP_Msk             (0x1U << SPI_CTRL_SWAP_Pos)              /*!< 0x00000200 */
#define SPI_CTRL_SWAP                  SPI_CTRL_SWAP_Msk                       /*!< SPI MISO/MOSI swap control register */
#define SPI_CTRL_CSGPIO_Pos           (10U)                                     
#define SPI_CTRL_CSGPIO_Msk           (0x1U << SPI_CTRL_CSGPIO_Pos)            /*!< 0x00000400 */
#define SPI_CTRL_CSGPIO                SPI_CTRL_CSGPIO_Msk                     /*!< SPI CS pin is controlled by GPIO or H/W */
#define SPI_CTRL_SPIRST_Pos           (11U)                                     
#define SPI_CTRL_SPIRST_Msk           (0x1U << SPI_CTRL_SPIRST_Pos)            /*!< 0x00000800 */
#define SPI_CTRL_SPIRST                SPI_CTRL_SPIRST_Msk                     /*!< SPI Soft Reset */
#define SPI_CTRL_SPIEN_Pos            (15U)                                  
#define SPI_CTRL_SPIEN_Msk            (0x1U << SPI_CTRL_SPIEN_Pos)             /*!< 0x00008000 */
#define SPI_CTRL_SPIEN                 SPI_CTRL_SPIEN_Msk                      /*!< SPI enable */

/**************  Bits definition for SPIx_TXSTS register     ******************/
#define SPI_TXSTS_TXFFLAG_Pos         (0U)                                     
#define SPI_TXSTS_TXFFLAG_Msk         (0x7U << SPI_TXSTS_TXFFLAG_Pos)          /*!< 0x0000000F */
#define SPI_TXSTS_TXFFLAG              SPI_TXSTS_TXFFLAG_Msk                   /*!< Transmit FIFO Data Level */
#define SPI_TXSTS_TXFLEV_Pos          (4U)                                     
#define SPI_TXSTS_TXFLEV_Msk          (0x7U << SPI_TXSTS_TXFLEV_Pos)           /*!< 0x00000070 */
#define SPI_TXSTS_TXFLEV               SPI_TXSTS_TXFLEV_Msk                    /*!< Transmit FIFO interrupt level register */
#define SPI_TXSTS_TXFLEV_0            (0x1U << SPI_TXSTS_TXFLEV_Pos)           /*!< 0x00000010 */
#define SPI_TXSTS_TXFLEV_1            (0x2U << SPI_TXSTS_TXFLEV_Pos)           /*!< 0x00000020 */
#define SPI_TXSTS_TXFLEV_2            (0x4U << SPI_TXSTS_TXFLEV_Pos)           /*!< 0x00000040 */
#define SPI_TXSTS_TXFUR_Pos           (8U)                                     
#define SPI_TXSTS_TXFUR_Msk           (0x1U << SPI_TXSTS_TXFUR_Pos)            /*!< 0x00000100 */
#define SPI_TXSTS_TXFUR                SPI_TXSTS_TXFUR_Msk                     /*!< Transmit FIFO under run register */
#define SPI_TXSTS_TXEMPTY_Pos         (9U)                                     
#define SPI_TXSTS_TXEMPTY_Msk         (0x1U << SPI_TXSTS_TXEMPTY_Pos)          /*!< 0x00000200 */
#define SPI_TXSTS_TXEMPTY              SPI_TXSTS_TXEMPTY_Msk                   /*!< Transmot FIFO empty register */
#define SPI_TXSTS_TXIEN_Pos           (14U)                                     
#define SPI_TXSTS_TXIEN_Msk           (0x1U << SPI_TXSTS_TXIEN_Pos)            /*!< 0x00004000 */
#define SPI_TXSTS_TXIEN                SPI_TXSTS_TXIEN_Msk                     /*!< SPI Transmit Interrupt Enable */
#define SPI_TXSTS_TXIF_Pos            (15U)                                     
#define SPI_TXSTS_TXIF_Msk            (0x1U << SPI_TXSTS_TXIF_Pos)             /*!< 0x00008000 */
#define SPI_TXSTS_TXIF                 SPI_TXSTS_TXIF_Msk                      /*!< SPI Transmit Interrupt flag */

/**************  Bits definition for SPIx_TXDAT register     ******************/
#define SPI_TXDAT_SPITXD_Pos          (0U)                                     
#define SPI_TXDAT_SPITXD_Msk          (0xFFU << SPI_TXDAT_SPITXD_Pos)             /*!< 0x000000FF */
#define SPI_TXDAT_SPITXD               SPI_TXDAT_SPITXD_Msk                      /*!< Write data to SPI Transmit FIFO */

/**************  Bits definition for SPIx_RXSTS register     ******************/
#define SPI_RXSTS_RXFFLAG_Pos         (0U)                                     
#define SPI_RXSTS_RXFFLAG_Msk         (0x7U << SPI_RXSTS_RXFFLAG_Pos)          /*!< 0x0000000F */
#define SPI_RXSTS_RXFFLAG              SPI_RXSTS_RXFFLAG_Msk                   /*!< Receive FIFO Data Level */
#define SPI_RXSTS_RXFLEV_Pos          (4U)                                     
#define SPI_RXSTS_RXFLEV_Msk          (0x7U << SPI_RXSTS_RXFLEV_Pos)           /*!< 0x00000070 */
#define SPI_RXSTS_RXFLEV               SPI_RXSTS_RXFLEV_Msk                    /*!< Receive FIFO interrupt level register */
#define SPI_RXSTS_RXFLEV_0            (0x1U << SPI_RXSTS_RXFLEV_Pos)           /*!< 0x00000010 */
#define SPI_RXSTS_RXFLEV_1            (0x2U << SPI_RXSTS_RXFLEV_Pos)           /*!< 0x00000020 */
#define SPI_RXSTS_RXFLEV_2            (0x4U << SPI_RXSTS_RXFLEV_Pos)           /*!< 0x00000040 */
#define SPI_RXSTS_RXFOV_Pos           (8U)                                     
#define SPI_RXSTS_RXFOV_Msk           (0x1U << SPI_RXSTS_RXFOV_Pos)            /*!< 0x00000100 */
#define SPI_RXSTS_RXFOV                SPI_RXSTS_RXFOV_Msk                     /*!< Receive FIFO over run register */
#define SPI_RXSTS_RXFULL_Pos          (9U)                                     
#define SPI_RXSTS_RXFULL_Msk          (0x1U << SPI_RXSTS_RXFULL_Pos)           /*!< 0x00000200 */
#define SPI_RXSTS_RXFULL               SPI_RXSTS_RXFULL_Msk                    /*!< Receive FIFO full register */
#define SPI_RXSTS_RXIEN_Pos           (14U)                                     
#define SPI_RXSTS_RXIEN_Msk           (0x1U << SPI_RXSTS_RXIEN_Pos)            /*!< 0x00004000 */
#define SPI_RXSTS_RXIEN                SPI_RXSTS_RXIEN_Msk                     /*!< SPI Receive Interrupt Enable */
#define SPI_RXSTS_RXIF_Pos            (15U)                                    
#define SPI_RXSTS_RXIF_Msk            (0x1U << SPI_RXSTS_RXIF_Pos)             /*!< 0x00008000 */
#define SPI_RXSTS_RXIF                 SPI_RXSTS_RXIF_Msk                      /*!< SPI Receive Interrupt flag */

/**************  Bits definition for SPIx_RXDAT register     ******************/
#define SPI_RXDAT_SPIRXD_Pos          (0U)                                     
#define SPI_RXDAT_SPIRXD_Msk          (0xFFU << SPI_RXDAT_SPIRXD_Pos)             /*!< 0x000000FF */
#define SPI_RXDAT_SPIRXD               SPI_RXDAT_SPIRXD_Msk                      /*!< Read data from SPI Receive FIFO */

/**************  Bits definition for SPIx_MISC register      ******************/
#define SPI_MISC_TFE_Pos              (0U)                                    
#define SPI_MISC_TFE_Msk              (0x1U << SPI_MISC_TFE_Pos)               /*!< 0x0000001 */
#define SPI_MISC_TFE                   SPI_MISC_TFE_Msk                        /*!< Transmit FIFO Empty Flag */
#define SPI_MISC_TNF_Pos              (1U)                                    
#define SPI_MISC_TNF_Msk              (0x1U << SPI_MISC_TNF_Pos)               /*!< 0x0000002 */
#define SPI_MISC_TNF                   SPI_MISC_TNF_Msk                        /*!< Transmit FIFO Not Full Flag */
#define SPI_MISC_RNE_Pos              (2U)                                    
#define SPI_MISC_RNE_Msk              (0x1U << SPI_MISC_RNE_Pos)               /*!< 0x0000004 */
#define SPI_MISC_RNE                   SPI_MISC_RNE_Msk                        /*!< Receive FIFO Not Empty Flag */
#define SPI_MISC_RFF_Pos              (3U)                                    
#define SPI_MISC_RFF_Msk              (0x1U << SPI_MISC_RFF_Pos)               /*!< 0x0000008 */
#define SPI_MISC_RFF                   SPI_MISC_RFF_Msk                        /*!< Receive FIFO Full Flag */
#define SPI_MISC_BSY_Pos              (4U)                                    
#define SPI_MISC_BSY_Msk              (0x1U << SPI_MISC_BSY_Pos)               /*!< 0x0000010 */
#define SPI_MISC_BSY                   SPI_MISC_BSY_Msk                        /*!< SPI Controller Busy Flag */
#define SPI_MISC_SMART_Pos            (8U)                                    
#define SPI_MISC_SMART_Msk            (0x1U << SPI_MISC_SMART_Pos)             /*!< 0x0000100 */
#define SPI_MISC_SMART                 SPI_MISC_SMART_Msk                      /*!< SPI FIFO SMART Mode Register */
#define SPI_MISC_OVER_Pos             (9U)                                    
#define SPI_MISC_OVER_Msk             (0x1U << SPI_MISC_OVER_Pos)              /*!< 0x0000200 */
#define SPI_MISC_OVER                  SPI_MISC_OVER_Msk                       /*!< SPI FIFO Over Write Mode */

/******************************************************************************/
/*                                                                            */
/*                               I2C controller (I2C)                         */
/*                                                                            */
/******************************************************************************/

/**************  Bits definition for I2C_DATA register       ******************/
#define I2C_DATA_DATA_Pos             (0U)                                    
#define I2C_DATA_DATA_Msk             (0xFFU << I2C_DATA_DATA_Pos)             /*!< 0x00000FF */
#define I2C_DATA_DATA                  I2C_DATA_DATA_Msk                       /*!< The I2C_DATA register contains a byte to be transmitted through I2C bus or a byte which has just been received through I2C bus */

/**************  Bits definition for I2C_ADDR register       ******************/
#define I2C_ADDR_GC_Pos               (0U)                                    
#define I2C_ADDR_GC_Msk               (0x1U << I2C_ADDR_GC_Pos)                /*!< 0x0000001 */
#define I2C_ADDR_GC                    I2C_ADDR_GC_Msk                         /*!< General Call Address Acknowledge */
#define I2C_ADDR_SLA_Pos              (1U)                                    
#define I2C_ADDR_SLA_Msk              (0xFEU << I2C_ADDR_SLA_Pos)              /*!< 0x00000FE */
#define I2C_ADDR_SLA                   I2C_ADDR_SLA_Msk                        /*!< Own I2C slave address (7 bit) */

/**************  Bits definition for I2C_CTRL register       ******************/
#define I2C_CTRL_CR_Pos               (0U)                                    
#define I2C_CTRL_CR_Msk               (0x83U << I2C_CTRL_CR_Pos)               /*!< 0x0000083 */
#define I2C_CTRL_CR                    I2C_CTRL_CR_Msk                         /*!< Clock rate bit0-2 */
#define I2C_CTRL_CR_0                 (0x0U << I2C_CTRL_CR_Pos)                /*!< 0x0000000 */
#define I2C_CTRL_CR_1                 (0x1U << I2C_CTRL_CR_Pos)                /*!< 0x0000001 */
#define I2C_CTRL_CR_2                 (0x2U << I2C_CTRL_CR_Pos)                /*!< 0x0000002 */
#define I2C_CTRL_CR_3                 (0x3U << I2C_CTRL_CR_Pos)                /*!< 0x0000003 */
#define I2C_CTRL_CR_4                 (0x80U << I2C_CTRL_CR_Pos)               /*!< 0x0000080 */
#define I2C_CTRL_CR_5                 (0x81U << I2C_CTRL_CR_Pos)               /*!< 0x0000081 */
#define I2C_CTRL_CR_6                 (0x82U << I2C_CTRL_CR_Pos)               /*!< 0x0000082 */
#define I2C_CTRL_CR_7                 (0x83U << I2C_CTRL_CR_Pos)               /*!< 0x0000083 */
#define I2C_CTRL_AA_Pos               (2U)                                    
#define I2C_CTRL_AA_Msk               (0x1U << I2C_CTRL_AA_Pos)                /*!< 0x0000004 */
#define I2C_CTRL_AA                    I2C_CTRL_AA_Msk                         /*!< Assert Acknowledge Flag */
#define I2C_CTRL_SI_Pos               (3U)                                    
#define I2C_CTRL_SI_Msk               (0x1U << I2C_CTRL_SI_Pos)                /*!< 0x0000008 */
#define I2C_CTRL_SI                    I2C_CTRL_SI_Msk                         /*!< Serial Interrupt Flag */
#define I2C_CTRL_STO_Pos              (4U)                                    
#define I2C_CTRL_STO_Msk              (0x1U << I2C_CTRL_STO_Pos)               /*!< 0x0000010 */
#define I2C_CTRL_STO                   I2C_CTRL_STO_Msk                        /*!< STOP Flag */
#define I2C_CTRL_STA_Pos              (5U)                                    
#define I2C_CTRL_STA_Msk              (0x1U << I2C_CTRL_STA_Pos)               /*!< 0x0000020 */
#define I2C_CTRL_STA                   I2C_CTRL_STA_Msk                        /*!< START Flag */
#define I2C_CTRL_EN_Pos               (6U)                                    
#define I2C_CTRL_EN_Msk               (0x1U << I2C_CTRL_EN_Pos)                /*!< 0x0000040 */
#define I2C_CTRL_EN                    I2C_CTRL_EN_Msk                         /*!< I2C enable bit */
                                  
/**************  Bits definition for I2C_STS register        ******************/
#define I2C_STS_STS_Pos               (3U)                                    
#define I2C_STS_STS_Msk               (0x1FU << I2C_STS_STS_Pos)               /*!< 0x00000F8 */
#define I2C_STS_STS                    I2C_STS_STS_Msk                         /*!< I2C Status Code */
#define I2C_STS_STS_0x00              (0x0U << I2C_STS_STS_Pos)                /*!< 0x0000000 */
#define I2C_STS_STS_0x08              (0x1U << I2C_STS_STS_Pos)                /*!< 0x0000008 */
#define I2C_STS_STS_0x10              (0x2U << I2C_STS_STS_Pos)                /*!< 0x0000010 */
#define I2C_STS_STS_0x18              (0x3U << I2C_STS_STS_Pos)                /*!< 0x0000018 */
#define I2C_STS_STS_0x20              (0x4U << I2C_STS_STS_Pos)                /*!< 0x0000020 */
#define I2C_STS_STS_0x28              (0x5U << I2C_STS_STS_Pos)                /*!< 0x0000028 */
#define I2C_STS_STS_0x30              (0x6U << I2C_STS_STS_Pos)                /*!< 0x0000030 */
#define I2C_STS_STS_0x38              (0x7U << I2C_STS_STS_Pos)                /*!< 0x0000038 */
#define I2C_STS_STS_0x40              (0x8U << I2C_STS_STS_Pos)                /*!< 0x0000040 */
#define I2C_STS_STS_0x48              (0x9U << I2C_STS_STS_Pos)                /*!< 0x0000048 */
#define I2C_STS_STS_0x50              (0xAU << I2C_STS_STS_Pos)                /*!< 0x0000050 */
#define I2C_STS_STS_0x58              (0xBU << I2C_STS_STS_Pos)                /*!< 0x0000058 */
#define I2C_STS_STS_0x60              (0xCU << I2C_STS_STS_Pos)                /*!< 0x0000060 */
#define I2C_STS_STS_0x68              (0xDU << I2C_STS_STS_Pos)                /*!< 0x0000068 */
#define I2C_STS_STS_0x70              (0xEU << I2C_STS_STS_Pos)                /*!< 0x0000070 */
#define I2C_STS_STS_0x78              (0xFU << I2C_STS_STS_Pos)                /*!< 0x0000078 */
#define I2C_STS_STS_0x80              (0x10U << I2C_STS_STS_Pos)               /*!< 0x0000080 */
#define I2C_STS_STS_0x88              (0x11U << I2C_STS_STS_Pos)               /*!< 0x0000088 */
#define I2C_STS_STS_0x90              (0x12U << I2C_STS_STS_Pos)               /*!< 0x0000090 */
#define I2C_STS_STS_0x98              (0x13U << I2C_STS_STS_Pos)               /*!< 0x0000098 */
#define I2C_STS_STS_0xA0              (0x14U << I2C_STS_STS_Pos)               /*!< 0x00000A0 */
#define I2C_STS_STS_0xA8              (0x15U << I2C_STS_STS_Pos)               /*!< 0x00000A8 */
#define I2C_STS_STS_0xB0              (0x16U << I2C_STS_STS_Pos)               /*!< 0x00000B0 */
#define I2C_STS_STS_0xB8              (0x17U << I2C_STS_STS_Pos)               /*!< 0x00000B8 */
#define I2C_STS_STS_0xC0              (0x18U << I2C_STS_STS_Pos)               /*!< 0x00000C0 */
#define I2C_STS_STS_0xC8              (0x19U << I2C_STS_STS_Pos)               /*!< 0x00000C8 */
#define I2C_STS_STS_0xF8              (0x1FU << I2C_STS_STS_Pos)               /*!< 0x00000F8 */

/**************  Bits definition for I2C_CTRL2 register      ******************/
#define I2C_CTRL2_INTEN_Pos           (0U)                                    
#define I2C_CTRL2_INTEN_Msk           (0x1U << I2C_CTRL2_INTEN_Pos)            /*!< 0x0000001 */
#define I2C_CTRL2_INTEN                I2C_CTRL2_INTEN_Msk                     /*!< Interrupt enable control of I2C controller */

/******************************************************************************/
/*                                                                            */
/*                               MISC controller (MISC)                       */
/*                                                                            */
/******************************************************************************/

/**************  Bits definition for MISC_SRAMINT register   ******************/
#define MISC_SRAMINT_PERR_Pos         (0U)                                     
#define MISC_SRAMINT_PERR_Msk         (0x1U << MISC_SRAMINT_PERR_Pos)          /*!< 0x00000001 */
#define MISC_SRAMINT_PERR              MISC_SRAMINT_PERR_Msk                   /*!< This bit indicates that a SRAM parity error is happened during the SRAM read process */ 
//#define MISC_SRAMINT_HIAL_Pos         (1U)                                     
//#define MISC_SRAMINT_HIAL_Msk         (0x1U << MISC_SRAMINT_HIAL_Pos)          /*!< 0x00000002 */
//#define MISC_SRAMINT_HIAL              MISC_SRAMINT_HIAL_Msk                   /*!< This bit indicates that an invalid align access on AHB bus is occurred */ 
#define MISC_SRAMINT_HIAC_Pos         (2U)                                     
#define MISC_SRAMINT_HIAC_Msk         (0x1U << MISC_SRAMINT_HIAC_Pos)          /*!< 0x00000004 */
#define MISC_SRAMINT_HIAC              MISC_SRAMINT_HIAC_Msk                   /*!< This bit indicates that an invalid address access on AHB bus is occurred */ 
#define MISC_SRAMINT_PIAC_Pos         (3U)                                     
#define MISC_SRAMINT_PIAC_Msk         (0x1U << MISC_SRAMINT_PIAC_Pos)          /*!< 0x00000008 */
#define MISC_SRAMINT_PIAC              MISC_SRAMINT_PIAC_Msk                   /*!< This bit indicates that an invalid address access on APB bus is occurred */ 
#define MISC_SRAMINT_LOCKUP_Pos       (4U)                                     
#define MISC_SRAMINT_LOCKUP_Msk       (0x1U << MISC_SRAMINT_LOCKUP_Pos)        /*!< 0x00000010 */
#define MISC_SRAMINT_LOCKUP            MISC_SRAMINT_LOCKUP_Msk                 /*!< This bit indicates the CM0 lockup has happened */ 

/**************  Bits definition for MISC_SRAMINIT register  ******************/
#define MISC_SRAMINIT_PEN_Pos         (0U)                                     
#define MISC_SRAMINIT_PEN_Msk         (0x1U << MISC_SRAMINIT_PEN_Pos)          /*!< 0x00000001 */
#define MISC_SRAMINIT_PEN              MISC_SRAMINIT_PEN_Msk                   /*!< Parity check enable register */ 
#define MISC_SRAMINIT_PERRIE_Pos      (1U)                                     
#define MISC_SRAMINIT_PERRIE_Msk      (0x1U << MISC_SRAMINIT_PERRIE_Pos)       /*!< 0x00000002 */
#define MISC_SRAMINIT_PERRIE           MISC_SRAMINIT_PERRIE_Msk                /*!< SRAM parity error NMI enable register */ 
#define MISC_SRAMINIT_INIT_Pos        (2U)                                     
#define MISC_SRAMINIT_INIT_Msk        (0x1U << MISC_SRAMINIT_INIT_Pos)         /*!< 0x00000004 */
#define MISC_SRAMINIT_INIT             MISC_SRAMINIT_INIT_Msk                  /*!< SRAM initialize register */ 
//#define MISC_SRAMINIT_HIALIE_Pos      (4U)                                     
//#define MISC_SRAMINIT_HIALIE_Msk      (0x1U << MISC_SRAMINIT_HIALIE_Pos)       /*!< 0x00000010 */
//#define MISC_SRAMINIT_HIALIE           MISC_SRAMINIT_HIALIE_Msk                /*!< AHB invalid aligned access NMI enable register */ 
#define MISC_SRAMINIT_HIACIE_Pos      (5U)                                     
#define MISC_SRAMINIT_HIACIE_Msk      (0x1U << MISC_SRAMINIT_HIACIE_Pos)       /*!< 0x00000020 */
#define MISC_SRAMINIT_HIACIE           MISC_SRAMINIT_HIACIE_Msk                /*!< AHB invalid address access NMI enable register */ 
#define MISC_SRAMINIT_PIACIE_Pos      (6U)                                     
#define MISC_SRAMINIT_PIACIE_Msk      (0x1U << MISC_SRAMINIT_PIACIE_Pos)       /*!< 0x00000040 */
#define MISC_SRAMINIT_PIACIE           MISC_SRAMINIT_PIACIE_Msk                /*!< APB invalid address access NMI enable register */ 
#define MISC_SRAMINIT_LOCKIE_Pos      (7U)                                     
#define MISC_SRAMINIT_LOCKIE_Msk      (0x1U << MISC_SRAMINIT_LOCKIE_Pos)       /*!< 0x00000080 */
#define MISC_SRAMINIT_LOCKIE           MISC_SRAMINIT_LOCKIE_Msk                /*!< CM0 lockup NMI enable register */ 

/**************  Bits definition for MISC_PARERR register    ******************/
#define MISC_PARERR_PEADDR_Pos        (0U)                                     
#define MISC_PARERR_PEADDR_Msk        (0xFFFU << MISC_PARERR_PEADDR_Pos)       /*!< 0x00000FFF */
#define MISC_PARERR_PEADDR             MISC_PARERR_PEADDR_Msk                  /*!< Parity error address */ 

/**************  Bits definition for MISC_IREN register      ******************/
#define MISC_IREN_IREN_Pos            (0U)                                     
#define MISC_IREN_IREN_Msk            (0x3FU << MISC_IREN_IREN_Pos)            /*!< 0x0000003F */
#define MISC_IREN_IREN                 MISC_IREN_IREN_Msk                      /*!< IR enable control register */
#define MISC_IREN_UART0               (0x01U)
#define MISC_IREN_UART1               (0x02U)
#define MISC_IREN_UART2               (0x04U)
#define MISC_IREN_UART3               (0x08U)
#define MISC_IREN_UART4               (0x10U)
#define MISC_IREN_UART5               (0x20U)

/**************  Bits definition for MISC_DUTYL register     ******************/
#define MISC_DUTYL_DUTYL_Pos          (0U)                                     
#define MISC_DUTYL_DUTYL_Msk          (0xFFFFU << MISC_DUTYL_DUTYL_Pos)        /*!< 0x0000FFFF */
#define MISC_DUTYL_DUTYL               MISC_DUTYL_DUTYL_Msk                    /*!< IR low pulse width control register */ 

/**************  Bits definition for MISC_DUTYH register     ******************/
#define MISC_DUTYH_DUTYH_Pos          (0U)                                     
#define MISC_DUTYH_DUTYH_Msk          (0xFFFFU << MISC_DUTYH_DUTYH_Pos)        /*!< 0x0000FFFF */
#define MISC_DUTYH_DUTYH               MISC_DUTYH_DUTYH_Msk                    /*!< IR high pulse width control register */ 

/**************  Bits definition for MISC_IRQLAT register    ******************/
#define MISC_IRQLAT_IRQLAT_Pos        (0U)                                     
#define MISC_IRQLAT_IRQLAT_Msk        (0xFFU << MISC_IRQLAT_IRQLAT_Pos)        /*!< 0x000000FF */
#define MISC_IRQLAT_IRQLAT             MISC_IRQLAT_IRQLAT_Msk                  /*!< This register is used to control the Cortex M0 IRQ latency */ 
#define MISC_IRQLAT_LOCKRESET_Pos     (8U)                                    
#define MISC_IRQLAT_LOCKRESET_Msk     (0x1U << MISC_IRQLAT_LOCKRESET_Pos)      /*!< 0x00000100 */
#define MISC_IRQLAT_LOCKRESET          MISC_IRQLAT_LOCKRESET_Msk               /*!< This register is used to control if the lockup will issue a system reset */ 
#define MISC_IRQLAT_NOHARDFAULT_Pos   (9U)                                    
#define MISC_IRQLAT_NOHARDFAULT_Msk   (0x1U << MISC_IRQLAT_NOHARDFAULT_Pos)    /*!< 0x00000200 */
#define MISC_IRQLAT_NOHARDFAULT        MISC_IRQLAT_NOHARDFAULT_Msk             /*!< This register is used to disable the hard fault generation to CPU */ 

/**************  Bits definition for MISC_HIADDR register    ******************/
#define MISC_HIADDR_Pos               (0U)                                     
#define MISC_HIADDR_Msk               (0xFFFFFFFFU << MISC_HIADDR_Pos)         /*!< 0xFFFFFFFF */
#define MISC_HIADDR                    MISC_HIADDR_Msk                         /*!< AHB invalid access address */ 

/**************  Bits definition for MISC_PIADDR register    ******************/
#define MISC_PIADDR_Pos               (0U)                                     
#define MISC_PIADDR_Msk               (0xFFFFFFFFU << MISC_PIADDR_Pos)         /*!< 0xFFFFFFFF */
#define MISC_PIADDR                    MISC_PIADDR_Msk                         /*!< APB invalid access address */ 

/**************  Bits definition for MISC2_FLASHWC register  ******************/
#define MISC2_FLASHWC_FLASHWC_Pos     (0U)                                     
#define MISC2_FLASHWC_FLASHWC_Msk     (0x3U << MISC2_FLASHWC_FLASHWC_Pos)      /*!< 0x00000003 */
#define MISC2_FLASHWC_FLASHWC          MISC2_FLASHWC_FLASHWC_Msk               /*!< This register is used to control wait cycle of Flash access */ 
#define MISC2_FLASHWC_FLASHWC_0Wait   (0x0U << MISC2_FLASHWC_FLASHWC_Pos)      /*!< 0x00000000 */
#define MISC2_FLASHWC_FLASHWC_1Wait   (0x1U << MISC2_FLASHWC_FLASHWC_Pos)      /*!< 0x00000001 */
#define MISC2_FLASHWC_FLASHWC_2Wait   (0x2U << MISC2_FLASHWC_FLASHWC_Pos)      /*!< 0x00000002 */
#define MISC2_FLASHWC_FLASHWC_3Wait   (0x3U << MISC2_FLASHWC_FLASHWC_Pos)      /*!< 0x00000003 */
#define MISC2_FLASHWC_1USCYCLE_Pos    (8U)                                     
#define MISC2_FLASHWC_1USCYCLE_Msk    (0x3FU << MISC2_FLASHWC_1USCYCLE_Pos)    /*!< 0x00003F00 */
#define MISC2_FLASHWC_1USCYCLE         MISC2_FLASHWC_1USCYCLE_Msk              /*!< This register is used for Flash controller to calculate 1us tick from AHB clock */ 

/**************  Bits definition for MISC2_CLKSEL register   ******************/
#define MISC2_CLKSEL_CLKSEL_Pos       (0U)                                     
#define MISC2_CLKSEL_CLKSEL_Msk       (0x7U << MISC2_CLKSEL_CLKSEL_Pos)        /*!< 0x00000007 */
#define MISC2_CLKSEL_CLKSEL            MISC2_CLKSEL_CLKSEL_Msk                 /*!< This register is used to control AHB clock source */ 
#define MISC2_CLKSEL_CLKSEL_RCOH      (0x0U << MISC2_CLKSEL_CLKSEL_Pos)        /*!< 0x00000000 */
#define MISC2_CLKSEL_CLKSEL_XOH       (0x1U << MISC2_CLKSEL_CLKSEL_Pos)        /*!< 0x00000001 */
#define MISC2_CLKSEL_CLKSEL_PLLH      (0x2U << MISC2_CLKSEL_CLKSEL_Pos)        /*!< 0x00000002 */
#define MISC2_CLKSEL_CLKSEL_RTCCLK    (0x3U << MISC2_CLKSEL_CLKSEL_Pos)        /*!< 0x00000003 */
#define MISC2_CLKSEL_CLKSEL_PLLL      (0x4U << MISC2_CLKSEL_CLKSEL_Pos)        /*!< 0x00000004 */

/**************  Bits definition for MISC2_CLKDIVH register  ******************/
#define MISC2_CLKDIVH_CLKDIVH_Pos     (0U)                                     
#define MISC2_CLKDIVH_CLKDIVH_Msk     (0xFFU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000FF */
#define MISC2_CLKDIVH_CLKDIVH          MISC2_CLKDIVH_CLKDIVH_Msk               /*!< This register is used to control AHB clock divider */ 
#define MISC2_CLKDIVH_CLKDIVH_DIV1    (0x0U << MISC2_CLKDIVH_CLKDIVH_Pos)      /*!< 0x00000000 */
#define MISC2_CLKDIVH_CLKDIVH_DIV2    (0x1U << MISC2_CLKDIVH_CLKDIVH_Pos)      /*!< 0x00000001 */
#define MISC2_CLKDIVH_CLKDIVH_DIV3    (0x2U << MISC2_CLKDIVH_CLKDIVH_Pos)      /*!< 0x00000002 */
#define MISC2_CLKDIVH_CLKDIVH_DIV4    (0x3U << MISC2_CLKDIVH_CLKDIVH_Pos)      /*!< 0x00000003 */
#define MISC2_CLKDIVH_CLKDIVH_DIV5    (0x4U << MISC2_CLKDIVH_CLKDIVH_Pos)      /*!< 0x00000004 */
#define MISC2_CLKDIVH_CLKDIVH_DIV6    (0x5U << MISC2_CLKDIVH_CLKDIVH_Pos)      /*!< 0x00000005 */
#define MISC2_CLKDIVH_CLKDIVH_DIV7    (0x6U << MISC2_CLKDIVH_CLKDIVH_Pos)      /*!< 0x00000006 */
#define MISC2_CLKDIVH_CLKDIVH_DIV8    (0x7U << MISC2_CLKDIVH_CLKDIVH_Pos)      /*!< 0x00000007 */
#define MISC2_CLKDIVH_CLKDIVH_DIV9    (0x8U << MISC2_CLKDIVH_CLKDIVH_Pos)      /*!< 0x00000008 */
#define MISC2_CLKDIVH_CLKDIVH_DIV10   (0x9U << MISC2_CLKDIVH_CLKDIVH_Pos)      /*!< 0x00000009 */
#define MISC2_CLKDIVH_CLKDIVH_DIV11   (0xAU << MISC2_CLKDIVH_CLKDIVH_Pos)      /*!< 0x0000000A */
#define MISC2_CLKDIVH_CLKDIVH_DIV12   (0xBU << MISC2_CLKDIVH_CLKDIVH_Pos)      /*!< 0x0000000B */
#define MISC2_CLKDIVH_CLKDIVH_DIV13   (0xCU << MISC2_CLKDIVH_CLKDIVH_Pos)      /*!< 0x0000000C */
#define MISC2_CLKDIVH_CLKDIVH_DIV14   (0xDU << MISC2_CLKDIVH_CLKDIVH_Pos)      /*!< 0x0000000D */
#define MISC2_CLKDIVH_CLKDIVH_DIV15   (0xEU << MISC2_CLKDIVH_CLKDIVH_Pos)      /*!< 0x0000000E */
#define MISC2_CLKDIVH_CLKDIVH_DIV16   (0xFU << MISC2_CLKDIVH_CLKDIVH_Pos)      /*!< 0x0000000F */
#define MISC2_CLKDIVH_CLKDIVH_DIV17   (0x10U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000010 */
#define MISC2_CLKDIVH_CLKDIVH_DIV18   (0x11U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000011 */
#define MISC2_CLKDIVH_CLKDIVH_DIV19   (0x12U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000012 */
#define MISC2_CLKDIVH_CLKDIVH_DIV20   (0x13U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000013 */
#define MISC2_CLKDIVH_CLKDIVH_DIV21   (0x14U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000014 */
#define MISC2_CLKDIVH_CLKDIVH_DIV22   (0x15U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000015 */
#define MISC2_CLKDIVH_CLKDIVH_DIV23   (0x16U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000016 */
#define MISC2_CLKDIVH_CLKDIVH_DIV24   (0x17U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000017 */
#define MISC2_CLKDIVH_CLKDIVH_DIV25   (0x18U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000018 */
#define MISC2_CLKDIVH_CLKDIVH_DIV26   (0x19U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000019 */
#define MISC2_CLKDIVH_CLKDIVH_DIV27   (0x1AU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x0000001A */
#define MISC2_CLKDIVH_CLKDIVH_DIV28   (0x1BU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x0000001B */
#define MISC2_CLKDIVH_CLKDIVH_DIV29   (0x1CU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x0000001C */
#define MISC2_CLKDIVH_CLKDIVH_DIV30   (0x1DU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x0000001D */
#define MISC2_CLKDIVH_CLKDIVH_DIV31   (0x1EU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x0000001E */
#define MISC2_CLKDIVH_CLKDIVH_DIV32   (0x1FU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x0000001F */
#define MISC2_CLKDIVH_CLKDIVH_DIV33   (0x20U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000020 */
#define MISC2_CLKDIVH_CLKDIVH_DIV34   (0x21U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000021 */
#define MISC2_CLKDIVH_CLKDIVH_DIV35   (0x22U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000022 */
#define MISC2_CLKDIVH_CLKDIVH_DIV36   (0x23U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000023 */
#define MISC2_CLKDIVH_CLKDIVH_DIV37   (0x24U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000024 */
#define MISC2_CLKDIVH_CLKDIVH_DIV38   (0x25U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000025 */
#define MISC2_CLKDIVH_CLKDIVH_DIV39   (0x26U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000026 */
#define MISC2_CLKDIVH_CLKDIVH_DIV40   (0x27U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000027 */
#define MISC2_CLKDIVH_CLKDIVH_DIV41   (0x28U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000028 */
#define MISC2_CLKDIVH_CLKDIVH_DIV42   (0x29U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000029 */
#define MISC2_CLKDIVH_CLKDIVH_DIV43   (0x2AU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x0000002A */
#define MISC2_CLKDIVH_CLKDIVH_DIV44   (0x2BU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x0000002B */
#define MISC2_CLKDIVH_CLKDIVH_DIV45   (0x2CU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x0000002C */
#define MISC2_CLKDIVH_CLKDIVH_DIV46   (0x2DU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x0000002D */
#define MISC2_CLKDIVH_CLKDIVH_DIV47   (0x2EU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x0000002E */
#define MISC2_CLKDIVH_CLKDIVH_DIV48   (0x2FU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x0000002F */
#define MISC2_CLKDIVH_CLKDIVH_DIV49   (0x30U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000030 */
#define MISC2_CLKDIVH_CLKDIVH_DIV50   (0x31U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000031 */
#define MISC2_CLKDIVH_CLKDIVH_DIV51   (0x32U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000032 */
#define MISC2_CLKDIVH_CLKDIVH_DIV52   (0x33U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000033 */
#define MISC2_CLKDIVH_CLKDIVH_DIV53   (0x34U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000034 */
#define MISC2_CLKDIVH_CLKDIVH_DIV54   (0x35U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000035 */
#define MISC2_CLKDIVH_CLKDIVH_DIV55   (0x36U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000036 */
#define MISC2_CLKDIVH_CLKDIVH_DIV56   (0x37U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000037 */
#define MISC2_CLKDIVH_CLKDIVH_DIV57   (0x38U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000038 */
#define MISC2_CLKDIVH_CLKDIVH_DIV58   (0x39U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000039 */
#define MISC2_CLKDIVH_CLKDIVH_DIV59   (0x3AU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x0000003A */
#define MISC2_CLKDIVH_CLKDIVH_DIV60   (0x3BU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x0000003B */
#define MISC2_CLKDIVH_CLKDIVH_DIV61   (0x3CU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x0000003C */
#define MISC2_CLKDIVH_CLKDIVH_DIV62   (0x3DU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x0000003D */
#define MISC2_CLKDIVH_CLKDIVH_DIV63   (0x3EU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x0000003E */
#define MISC2_CLKDIVH_CLKDIVH_DIV64   (0x3FU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x0000003F */
#define MISC2_CLKDIVH_CLKDIVH_DIV65   (0x40U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000040 */
#define MISC2_CLKDIVH_CLKDIVH_DIV66   (0x41U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000041 */
#define MISC2_CLKDIVH_CLKDIVH_DIV67   (0x42U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000042 */
#define MISC2_CLKDIVH_CLKDIVH_DIV68   (0x43U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000043 */
#define MISC2_CLKDIVH_CLKDIVH_DIV69   (0x44U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000044 */
#define MISC2_CLKDIVH_CLKDIVH_DIV70   (0x45U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000045 */
#define MISC2_CLKDIVH_CLKDIVH_DIV71   (0x46U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000046 */
#define MISC2_CLKDIVH_CLKDIVH_DIV72   (0x47U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000047 */
#define MISC2_CLKDIVH_CLKDIVH_DIV73   (0x48U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000048 */
#define MISC2_CLKDIVH_CLKDIVH_DIV74   (0x49U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000049 */
#define MISC2_CLKDIVH_CLKDIVH_DIV75   (0x4AU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x0000004A */
#define MISC2_CLKDIVH_CLKDIVH_DIV76   (0x4BU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x0000004B */
#define MISC2_CLKDIVH_CLKDIVH_DIV77   (0x4CU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x0000004C */
#define MISC2_CLKDIVH_CLKDIVH_DIV78   (0x4DU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x0000004D */
#define MISC2_CLKDIVH_CLKDIVH_DIV79   (0x4EU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x0000004E */
#define MISC2_CLKDIVH_CLKDIVH_DIV80   (0x4FU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x0000004F */
#define MISC2_CLKDIVH_CLKDIVH_DIV81   (0x50U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000050 */
#define MISC2_CLKDIVH_CLKDIVH_DIV82   (0x51U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000051 */
#define MISC2_CLKDIVH_CLKDIVH_DIV83   (0x52U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000052 */
#define MISC2_CLKDIVH_CLKDIVH_DIV84   (0x53U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000053 */
#define MISC2_CLKDIVH_CLKDIVH_DIV85   (0x54U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000054 */
#define MISC2_CLKDIVH_CLKDIVH_DIV86   (0x55U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000055 */
#define MISC2_CLKDIVH_CLKDIVH_DIV87   (0x56U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000056 */
#define MISC2_CLKDIVH_CLKDIVH_DIV88   (0x57U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000057 */
#define MISC2_CLKDIVH_CLKDIVH_DIV89   (0x58U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000058 */
#define MISC2_CLKDIVH_CLKDIVH_DIV90   (0x59U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000059 */
#define MISC2_CLKDIVH_CLKDIVH_DIV91   (0x5AU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x0000005A */
#define MISC2_CLKDIVH_CLKDIVH_DIV92   (0x5BU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x0000005B */
#define MISC2_CLKDIVH_CLKDIVH_DIV93   (0x5CU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x0000005C */
#define MISC2_CLKDIVH_CLKDIVH_DIV94   (0x5DU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x0000005D */
#define MISC2_CLKDIVH_CLKDIVH_DIV95   (0x5EU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x0000005E */
#define MISC2_CLKDIVH_CLKDIVH_DIV96   (0x5FU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x0000005F */
#define MISC2_CLKDIVH_CLKDIVH_DIV97   (0x60U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000060 */
#define MISC2_CLKDIVH_CLKDIVH_DIV98   (0x61U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000061 */
#define MISC2_CLKDIVH_CLKDIVH_DIV99   (0x62U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000062 */
#define MISC2_CLKDIVH_CLKDIVH_DIV100  (0x63U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000063 */
#define MISC2_CLKDIVH_CLKDIVH_DIV101  (0x64U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000064 */
#define MISC2_CLKDIVH_CLKDIVH_DIV102  (0x65U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000065 */
#define MISC2_CLKDIVH_CLKDIVH_DIV103  (0x66U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000066 */
#define MISC2_CLKDIVH_CLKDIVH_DIV104  (0x67U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000067 */
#define MISC2_CLKDIVH_CLKDIVH_DIV105  (0x68U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000068 */
#define MISC2_CLKDIVH_CLKDIVH_DIV106  (0x69U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000069 */
#define MISC2_CLKDIVH_CLKDIVH_DIV107  (0x6AU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x0000006A */
#define MISC2_CLKDIVH_CLKDIVH_DIV108  (0x6BU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x0000006B */
#define MISC2_CLKDIVH_CLKDIVH_DIV109  (0x6CU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x0000006C */
#define MISC2_CLKDIVH_CLKDIVH_DIV110  (0x6DU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x0000006D */
#define MISC2_CLKDIVH_CLKDIVH_DIV111  (0x6EU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x0000006E */
#define MISC2_CLKDIVH_CLKDIVH_DIV112  (0x6FU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x0000006F */
#define MISC2_CLKDIVH_CLKDIVH_DIV113  (0x70U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000070 */
#define MISC2_CLKDIVH_CLKDIVH_DIV114  (0x71U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000071 */
#define MISC2_CLKDIVH_CLKDIVH_DIV115  (0x72U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000072 */
#define MISC2_CLKDIVH_CLKDIVH_DIV116  (0x73U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000073 */
#define MISC2_CLKDIVH_CLKDIVH_DIV117  (0x74U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000074 */
#define MISC2_CLKDIVH_CLKDIVH_DIV118  (0x75U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000075 */
#define MISC2_CLKDIVH_CLKDIVH_DIV119  (0x76U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000076 */
#define MISC2_CLKDIVH_CLKDIVH_DIV120  (0x77U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000077 */
#define MISC2_CLKDIVH_CLKDIVH_DIV121  (0x78U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000078 */
#define MISC2_CLKDIVH_CLKDIVH_DIV122  (0x79U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000079 */
#define MISC2_CLKDIVH_CLKDIVH_DIV123  (0x7AU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x0000007A */
#define MISC2_CLKDIVH_CLKDIVH_DIV124  (0x7BU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x0000007B */
#define MISC2_CLKDIVH_CLKDIVH_DIV125  (0x7CU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x0000007C */
#define MISC2_CLKDIVH_CLKDIVH_DIV126  (0x7DU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x0000007D */
#define MISC2_CLKDIVH_CLKDIVH_DIV127  (0x7EU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x0000007E */
#define MISC2_CLKDIVH_CLKDIVH_DIV128  (0x7FU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x0000007F */
#define MISC2_CLKDIVH_CLKDIVH_DIV129  (0x80U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000080 */
#define MISC2_CLKDIVH_CLKDIVH_DIV130  (0x81U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000081 */
#define MISC2_CLKDIVH_CLKDIVH_DIV131  (0x82U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000082 */
#define MISC2_CLKDIVH_CLKDIVH_DIV132  (0x83U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000083 */
#define MISC2_CLKDIVH_CLKDIVH_DIV133  (0x84U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000084 */
#define MISC2_CLKDIVH_CLKDIVH_DIV134  (0x85U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000085 */
#define MISC2_CLKDIVH_CLKDIVH_DIV135  (0x86U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000086 */
#define MISC2_CLKDIVH_CLKDIVH_DIV136  (0x87U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000087 */
#define MISC2_CLKDIVH_CLKDIVH_DIV137  (0x88U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000088 */
#define MISC2_CLKDIVH_CLKDIVH_DIV138  (0x89U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000089 */
#define MISC2_CLKDIVH_CLKDIVH_DIV139  (0x8AU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x0000008A */
#define MISC2_CLKDIVH_CLKDIVH_DIV140  (0x8BU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x0000008B */
#define MISC2_CLKDIVH_CLKDIVH_DIV141  (0x8CU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x0000008C */
#define MISC2_CLKDIVH_CLKDIVH_DIV142  (0x8DU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x0000008D */
#define MISC2_CLKDIVH_CLKDIVH_DIV143  (0x8EU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x0000008E */
#define MISC2_CLKDIVH_CLKDIVH_DIV144  (0x8FU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x0000008F */
#define MISC2_CLKDIVH_CLKDIVH_DIV145  (0x90U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000090 */
#define MISC2_CLKDIVH_CLKDIVH_DIV146  (0x91U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000091 */
#define MISC2_CLKDIVH_CLKDIVH_DIV147  (0x92U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000092 */
#define MISC2_CLKDIVH_CLKDIVH_DIV148  (0x93U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000093 */
#define MISC2_CLKDIVH_CLKDIVH_DIV149  (0x94U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000094 */
#define MISC2_CLKDIVH_CLKDIVH_DIV150  (0x95U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000095 */
#define MISC2_CLKDIVH_CLKDIVH_DIV151  (0x96U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000096 */
#define MISC2_CLKDIVH_CLKDIVH_DIV152  (0x97U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000097 */
#define MISC2_CLKDIVH_CLKDIVH_DIV153  (0x98U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000098 */
#define MISC2_CLKDIVH_CLKDIVH_DIV154  (0x99U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x00000099 */
#define MISC2_CLKDIVH_CLKDIVH_DIV155  (0x9AU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x0000009A */
#define MISC2_CLKDIVH_CLKDIVH_DIV156  (0x9BU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x0000009B */
#define MISC2_CLKDIVH_CLKDIVH_DIV157  (0x9CU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x0000009C */
#define MISC2_CLKDIVH_CLKDIVH_DIV158  (0x9DU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x0000009D */
#define MISC2_CLKDIVH_CLKDIVH_DIV159  (0x9EU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x0000009E */
#define MISC2_CLKDIVH_CLKDIVH_DIV160  (0x9FU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x0000009F */
#define MISC2_CLKDIVH_CLKDIVH_DIV161  (0xA0U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000A0 */
#define MISC2_CLKDIVH_CLKDIVH_DIV162  (0xA1U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000A1 */
#define MISC2_CLKDIVH_CLKDIVH_DIV163  (0xA2U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000A2 */
#define MISC2_CLKDIVH_CLKDIVH_DIV164  (0xA3U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000A3 */
#define MISC2_CLKDIVH_CLKDIVH_DIV165  (0xA4U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000A4 */
#define MISC2_CLKDIVH_CLKDIVH_DIV166  (0xA5U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000A5 */
#define MISC2_CLKDIVH_CLKDIVH_DIV167  (0xA6U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000A6 */
#define MISC2_CLKDIVH_CLKDIVH_DIV168  (0xA7U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000A7 */
#define MISC2_CLKDIVH_CLKDIVH_DIV169  (0xA8U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000A8 */
#define MISC2_CLKDIVH_CLKDIVH_DIV170  (0xA9U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000A9 */
#define MISC2_CLKDIVH_CLKDIVH_DIV171  (0xAAU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000AA */
#define MISC2_CLKDIVH_CLKDIVH_DIV172  (0xABU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000AB */
#define MISC2_CLKDIVH_CLKDIVH_DIV173  (0xACU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000AC */
#define MISC2_CLKDIVH_CLKDIVH_DIV174  (0xADU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000AD */
#define MISC2_CLKDIVH_CLKDIVH_DIV175  (0xAEU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000AE */
#define MISC2_CLKDIVH_CLKDIVH_DIV176  (0xAFU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000AF */
#define MISC2_CLKDIVH_CLKDIVH_DIV177  (0xB0U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000B0 */
#define MISC2_CLKDIVH_CLKDIVH_DIV178  (0xB1U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000B1 */
#define MISC2_CLKDIVH_CLKDIVH_DIV179  (0xB2U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000B2 */
#define MISC2_CLKDIVH_CLKDIVH_DIV180  (0xB3U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000B3 */
#define MISC2_CLKDIVH_CLKDIVH_DIV181  (0xB4U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000B4 */
#define MISC2_CLKDIVH_CLKDIVH_DIV182  (0xB5U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000B5 */
#define MISC2_CLKDIVH_CLKDIVH_DIV183  (0xB6U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000B6 */
#define MISC2_CLKDIVH_CLKDIVH_DIV184  (0xB7U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000B7 */
#define MISC2_CLKDIVH_CLKDIVH_DIV185  (0xB8U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000B8 */
#define MISC2_CLKDIVH_CLKDIVH_DIV186  (0xB9U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000B9 */
#define MISC2_CLKDIVH_CLKDIVH_DIV187  (0xBAU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000BA */
#define MISC2_CLKDIVH_CLKDIVH_DIV188  (0xBBU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000BB */
#define MISC2_CLKDIVH_CLKDIVH_DIV189  (0xBCU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000BC */
#define MISC2_CLKDIVH_CLKDIVH_DIV190  (0xBDU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000BD */
#define MISC2_CLKDIVH_CLKDIVH_DIV191  (0xBEU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000BE */
#define MISC2_CLKDIVH_CLKDIVH_DIV192  (0xBFU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000BF */
#define MISC2_CLKDIVH_CLKDIVH_DIV193  (0xC0U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000C0 */
#define MISC2_CLKDIVH_CLKDIVH_DIV194  (0xC1U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000C1 */
#define MISC2_CLKDIVH_CLKDIVH_DIV195  (0xC2U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000C2 */
#define MISC2_CLKDIVH_CLKDIVH_DIV196  (0xC3U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000C3 */
#define MISC2_CLKDIVH_CLKDIVH_DIV197  (0xC4U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000C4 */
#define MISC2_CLKDIVH_CLKDIVH_DIV198  (0xC5U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000C5 */
#define MISC2_CLKDIVH_CLKDIVH_DIV199  (0xC6U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000C6 */
#define MISC2_CLKDIVH_CLKDIVH_DIV200  (0xC7U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000C7 */
#define MISC2_CLKDIVH_CLKDIVH_DIV201  (0xC8U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000C8 */
#define MISC2_CLKDIVH_CLKDIVH_DIV202  (0xC9U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000C9 */
#define MISC2_CLKDIVH_CLKDIVH_DIV203  (0xCAU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000CA */
#define MISC2_CLKDIVH_CLKDIVH_DIV204  (0xCBU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000CB */
#define MISC2_CLKDIVH_CLKDIVH_DIV205  (0xCCU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000CC */
#define MISC2_CLKDIVH_CLKDIVH_DIV206  (0xCDU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000CD */
#define MISC2_CLKDIVH_CLKDIVH_DIV207  (0xCEU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000CE */
#define MISC2_CLKDIVH_CLKDIVH_DIV208  (0xCFU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000CF */
#define MISC2_CLKDIVH_CLKDIVH_DIV209  (0xD0U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000D0 */
#define MISC2_CLKDIVH_CLKDIVH_DIV210  (0xD1U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000D1 */
#define MISC2_CLKDIVH_CLKDIVH_DIV211  (0xD2U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000D2 */
#define MISC2_CLKDIVH_CLKDIVH_DIV212  (0xD3U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000D3 */
#define MISC2_CLKDIVH_CLKDIVH_DIV213  (0xD4U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000D4 */
#define MISC2_CLKDIVH_CLKDIVH_DIV214  (0xD5U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000D5 */
#define MISC2_CLKDIVH_CLKDIVH_DIV215  (0xD6U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000D6 */
#define MISC2_CLKDIVH_CLKDIVH_DIV216  (0xD7U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000D7 */
#define MISC2_CLKDIVH_CLKDIVH_DIV217  (0xD8U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000D8 */
#define MISC2_CLKDIVH_CLKDIVH_DIV218  (0xD9U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000D9 */
#define MISC2_CLKDIVH_CLKDIVH_DIV219  (0xDAU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000DA */
#define MISC2_CLKDIVH_CLKDIVH_DIV220  (0xDBU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000DB */
#define MISC2_CLKDIVH_CLKDIVH_DIV221  (0xDCU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000DC */
#define MISC2_CLKDIVH_CLKDIVH_DIV222  (0xDDU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000DD */
#define MISC2_CLKDIVH_CLKDIVH_DIV223  (0xDEU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000DE */
#define MISC2_CLKDIVH_CLKDIVH_DIV224  (0xDFU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000DF */
#define MISC2_CLKDIVH_CLKDIVH_DIV225  (0xE0U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000E0 */
#define MISC2_CLKDIVH_CLKDIVH_DIV226  (0xE1U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000E1 */
#define MISC2_CLKDIVH_CLKDIVH_DIV227  (0xE2U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000E2 */
#define MISC2_CLKDIVH_CLKDIVH_DIV228  (0xE3U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000E3 */
#define MISC2_CLKDIVH_CLKDIVH_DIV229  (0xE4U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000E4 */
#define MISC2_CLKDIVH_CLKDIVH_DIV230  (0xE5U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000E5 */
#define MISC2_CLKDIVH_CLKDIVH_DIV231  (0xE6U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000E6 */
#define MISC2_CLKDIVH_CLKDIVH_DIV232  (0xE7U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000E7 */
#define MISC2_CLKDIVH_CLKDIVH_DIV233  (0xE8U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000E8 */
#define MISC2_CLKDIVH_CLKDIVH_DIV234  (0xE9U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000E9 */
#define MISC2_CLKDIVH_CLKDIVH_DIV235  (0xEAU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000EA */
#define MISC2_CLKDIVH_CLKDIVH_DIV236  (0xEBU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000EB */
#define MISC2_CLKDIVH_CLKDIVH_DIV237  (0xECU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000EC */
#define MISC2_CLKDIVH_CLKDIVH_DIV238  (0xEDU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000ED */
#define MISC2_CLKDIVH_CLKDIVH_DIV239  (0xEEU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000EE */
#define MISC2_CLKDIVH_CLKDIVH_DIV240  (0xEFU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000EF */
#define MISC2_CLKDIVH_CLKDIVH_DIV241  (0xF0U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000F0 */
#define MISC2_CLKDIVH_CLKDIVH_DIV242  (0xF1U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000F1 */
#define MISC2_CLKDIVH_CLKDIVH_DIV243  (0xF2U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000F2 */
#define MISC2_CLKDIVH_CLKDIVH_DIV244  (0xF3U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000F3 */
#define MISC2_CLKDIVH_CLKDIVH_DIV245  (0xF4U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000F4 */
#define MISC2_CLKDIVH_CLKDIVH_DIV246  (0xF5U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000F5 */
#define MISC2_CLKDIVH_CLKDIVH_DIV247  (0xF6U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000F6 */
#define MISC2_CLKDIVH_CLKDIVH_DIV248  (0xF7U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000F7 */
#define MISC2_CLKDIVH_CLKDIVH_DIV249  (0xF8U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000F8 */
#define MISC2_CLKDIVH_CLKDIVH_DIV250  (0xF9U << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000F9 */
#define MISC2_CLKDIVH_CLKDIVH_DIV251  (0xFAU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000FA */
#define MISC2_CLKDIVH_CLKDIVH_DIV252  (0xFBU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000FB */
#define MISC2_CLKDIVH_CLKDIVH_DIV253  (0xFCU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000FC */
#define MISC2_CLKDIVH_CLKDIVH_DIV254  (0xFDU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000FD */
#define MISC2_CLKDIVH_CLKDIVH_DIV255  (0xFEU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000FE */
#define MISC2_CLKDIVH_CLKDIVH_DIV256  (0xFFU << MISC2_CLKDIVH_CLKDIVH_Pos)     /*!< 0x000000FF */

/**************  Bits definition for MISC2_CLKDIVP register  ******************/
#define MISC2_CLKDIVP_CLKDIVP_Pos     (0U)                                     
#define MISC2_CLKDIVP_CLKDIVP_Msk     (0xFFU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000FF */
#define MISC2_CLKDIVP_CLKDIVP          MISC2_CLKDIVP_CLKDIVP_Msk               /*!< This register is used to control APB clock divider */ 
#define MISC2_CLKDIVP_CLKDIVP_DIV1    (0x0U << MISC2_CLKDIVP_CLKDIVP_Pos)      /*!< 0x00000000 */
#define MISC2_CLKDIVP_CLKDIVP_DIV2    (0x1U << MISC2_CLKDIVP_CLKDIVP_Pos)      /*!< 0x00000001 */
#define MISC2_CLKDIVP_CLKDIVP_DIV3    (0x2U << MISC2_CLKDIVP_CLKDIVP_Pos)      /*!< 0x00000002 */
#define MISC2_CLKDIVP_CLKDIVP_DIV4    (0x3U << MISC2_CLKDIVP_CLKDIVP_Pos)      /*!< 0x00000003 */
#define MISC2_CLKDIVP_CLKDIVP_DIV5    (0x4U << MISC2_CLKDIVP_CLKDIVP_Pos)      /*!< 0x00000004 */
#define MISC2_CLKDIVP_CLKDIVP_DIV6    (0x5U << MISC2_CLKDIVP_CLKDIVP_Pos)      /*!< 0x00000005 */
#define MISC2_CLKDIVP_CLKDIVP_DIV7    (0x6U << MISC2_CLKDIVP_CLKDIVP_Pos)      /*!< 0x00000006 */
#define MISC2_CLKDIVP_CLKDIVP_DIV8    (0x7U << MISC2_CLKDIVP_CLKDIVP_Pos)      /*!< 0x00000007 */
#define MISC2_CLKDIVP_CLKDIVP_DIV9    (0x8U << MISC2_CLKDIVP_CLKDIVP_Pos)      /*!< 0x00000008 */
#define MISC2_CLKDIVP_CLKDIVP_DIV10   (0x9U << MISC2_CLKDIVP_CLKDIVP_Pos)      /*!< 0x00000009 */
#define MISC2_CLKDIVP_CLKDIVP_DIV11   (0xAU << MISC2_CLKDIVP_CLKDIVP_Pos)      /*!< 0x0000000A */
#define MISC2_CLKDIVP_CLKDIVP_DIV12   (0xBU << MISC2_CLKDIVP_CLKDIVP_Pos)      /*!< 0x0000000B */
#define MISC2_CLKDIVP_CLKDIVP_DIV13   (0xCU << MISC2_CLKDIVP_CLKDIVP_Pos)      /*!< 0x0000000C */
#define MISC2_CLKDIVP_CLKDIVP_DIV14   (0xDU << MISC2_CLKDIVP_CLKDIVP_Pos)      /*!< 0x0000000D */
#define MISC2_CLKDIVP_CLKDIVP_DIV15   (0xEU << MISC2_CLKDIVP_CLKDIVP_Pos)      /*!< 0x0000000E */
#define MISC2_CLKDIVP_CLKDIVP_DIV16   (0xFU << MISC2_CLKDIVP_CLKDIVP_Pos)      /*!< 0x0000000F */
#define MISC2_CLKDIVP_CLKDIVP_DIV17   (0x10U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000010 */
#define MISC2_CLKDIVP_CLKDIVP_DIV18   (0x11U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000011 */
#define MISC2_CLKDIVP_CLKDIVP_DIV19   (0x12U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000012 */
#define MISC2_CLKDIVP_CLKDIVP_DIV20   (0x13U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000013 */
#define MISC2_CLKDIVP_CLKDIVP_DIV21   (0x14U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000014 */
#define MISC2_CLKDIVP_CLKDIVP_DIV22   (0x15U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000015 */
#define MISC2_CLKDIVP_CLKDIVP_DIV23   (0x16U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000016 */
#define MISC2_CLKDIVP_CLKDIVP_DIV24   (0x17U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000017 */
#define MISC2_CLKDIVP_CLKDIVP_DIV25   (0x18U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000018 */
#define MISC2_CLKDIVP_CLKDIVP_DIV26   (0x19U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000019 */
#define MISC2_CLKDIVP_CLKDIVP_DIV27   (0x1AU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x0000001A */
#define MISC2_CLKDIVP_CLKDIVP_DIV28   (0x1BU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x0000001B */
#define MISC2_CLKDIVP_CLKDIVP_DIV29   (0x1CU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x0000001C */
#define MISC2_CLKDIVP_CLKDIVP_DIV30   (0x1DU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x0000001D */
#define MISC2_CLKDIVP_CLKDIVP_DIV31   (0x1EU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x0000001E */
#define MISC2_CLKDIVP_CLKDIVP_DIV32   (0x1FU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x0000001F */
#define MISC2_CLKDIVP_CLKDIVP_DIV33   (0x20U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000020 */
#define MISC2_CLKDIVP_CLKDIVP_DIV34   (0x21U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000021 */
#define MISC2_CLKDIVP_CLKDIVP_DIV35   (0x22U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000022 */
#define MISC2_CLKDIVP_CLKDIVP_DIV36   (0x23U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000023 */
#define MISC2_CLKDIVP_CLKDIVP_DIV37   (0x24U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000024 */
#define MISC2_CLKDIVP_CLKDIVP_DIV38   (0x25U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000025 */
#define MISC2_CLKDIVP_CLKDIVP_DIV39   (0x26U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000026 */
#define MISC2_CLKDIVP_CLKDIVP_DIV40   (0x27U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000027 */
#define MISC2_CLKDIVP_CLKDIVP_DIV41   (0x28U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000028 */
#define MISC2_CLKDIVP_CLKDIVP_DIV42   (0x29U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000029 */
#define MISC2_CLKDIVP_CLKDIVP_DIV43   (0x2AU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x0000002A */
#define MISC2_CLKDIVP_CLKDIVP_DIV44   (0x2BU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x0000002B */
#define MISC2_CLKDIVP_CLKDIVP_DIV45   (0x2CU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x0000002C */
#define MISC2_CLKDIVP_CLKDIVP_DIV46   (0x2DU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x0000002D */
#define MISC2_CLKDIVP_CLKDIVP_DIV47   (0x2EU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x0000002E */
#define MISC2_CLKDIVP_CLKDIVP_DIV48   (0x2FU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x0000002F */
#define MISC2_CLKDIVP_CLKDIVP_DIV49   (0x30U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000030 */
#define MISC2_CLKDIVP_CLKDIVP_DIV50   (0x31U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000031 */
#define MISC2_CLKDIVP_CLKDIVP_DIV51   (0x32U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000032 */
#define MISC2_CLKDIVP_CLKDIVP_DIV52   (0x33U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000033 */
#define MISC2_CLKDIVP_CLKDIVP_DIV53   (0x34U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000034 */
#define MISC2_CLKDIVP_CLKDIVP_DIV54   (0x35U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000035 */
#define MISC2_CLKDIVP_CLKDIVP_DIV55   (0x36U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000036 */
#define MISC2_CLKDIVP_CLKDIVP_DIV56   (0x37U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000037 */
#define MISC2_CLKDIVP_CLKDIVP_DIV57   (0x38U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000038 */
#define MISC2_CLKDIVP_CLKDIVP_DIV58   (0x39U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000039 */
#define MISC2_CLKDIVP_CLKDIVP_DIV59   (0x3AU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x0000003A */
#define MISC2_CLKDIVP_CLKDIVP_DIV60   (0x3BU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x0000003B */
#define MISC2_CLKDIVP_CLKDIVP_DIV61   (0x3CU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x0000003C */
#define MISC2_CLKDIVP_CLKDIVP_DIV62   (0x3DU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x0000003D */
#define MISC2_CLKDIVP_CLKDIVP_DIV63   (0x3EU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x0000003E */
#define MISC2_CLKDIVP_CLKDIVP_DIV64   (0x3FU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x0000003F */
#define MISC2_CLKDIVP_CLKDIVP_DIV65   (0x40U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000040 */
#define MISC2_CLKDIVP_CLKDIVP_DIV66   (0x41U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000041 */
#define MISC2_CLKDIVP_CLKDIVP_DIV67   (0x42U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000042 */
#define MISC2_CLKDIVP_CLKDIVP_DIV68   (0x43U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000043 */
#define MISC2_CLKDIVP_CLKDIVP_DIV69   (0x44U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000044 */
#define MISC2_CLKDIVP_CLKDIVP_DIV70   (0x45U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000045 */
#define MISC2_CLKDIVP_CLKDIVP_DIV71   (0x46U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000046 */
#define MISC2_CLKDIVP_CLKDIVP_DIV72   (0x47U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000047 */
#define MISC2_CLKDIVP_CLKDIVP_DIV73   (0x48U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000048 */
#define MISC2_CLKDIVP_CLKDIVP_DIV74   (0x49U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000049 */
#define MISC2_CLKDIVP_CLKDIVP_DIV75   (0x4AU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x0000004A */
#define MISC2_CLKDIVP_CLKDIVP_DIV76   (0x4BU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x0000004B */
#define MISC2_CLKDIVP_CLKDIVP_DIV77   (0x4CU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x0000004C */
#define MISC2_CLKDIVP_CLKDIVP_DIV78   (0x4DU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x0000004D */
#define MISC2_CLKDIVP_CLKDIVP_DIV79   (0x4EU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x0000004E */
#define MISC2_CLKDIVP_CLKDIVP_DIV80   (0x4FU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x0000004F */
#define MISC2_CLKDIVP_CLKDIVP_DIV81   (0x50U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000050 */
#define MISC2_CLKDIVP_CLKDIVP_DIV82   (0x51U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000051 */
#define MISC2_CLKDIVP_CLKDIVP_DIV83   (0x52U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000052 */
#define MISC2_CLKDIVP_CLKDIVP_DIV84   (0x53U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000053 */
#define MISC2_CLKDIVP_CLKDIVP_DIV85   (0x54U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000054 */
#define MISC2_CLKDIVP_CLKDIVP_DIV86   (0x55U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000055 */
#define MISC2_CLKDIVP_CLKDIVP_DIV87   (0x56U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000056 */
#define MISC2_CLKDIVP_CLKDIVP_DIV88   (0x57U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000057 */
#define MISC2_CLKDIVP_CLKDIVP_DIV89   (0x58U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000058 */
#define MISC2_CLKDIVP_CLKDIVP_DIV90   (0x59U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000059 */
#define MISC2_CLKDIVP_CLKDIVP_DIV91   (0x5AU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x0000005A */
#define MISC2_CLKDIVP_CLKDIVP_DIV92   (0x5BU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x0000005B */
#define MISC2_CLKDIVP_CLKDIVP_DIV93   (0x5CU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x0000005C */
#define MISC2_CLKDIVP_CLKDIVP_DIV94   (0x5DU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x0000005D */
#define MISC2_CLKDIVP_CLKDIVP_DIV95   (0x5EU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x0000005E */
#define MISC2_CLKDIVP_CLKDIVP_DIV96   (0x5FU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x0000005F */
#define MISC2_CLKDIVP_CLKDIVP_DIV97   (0x60U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000060 */
#define MISC2_CLKDIVP_CLKDIVP_DIV98   (0x61U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000061 */
#define MISC2_CLKDIVP_CLKDIVP_DIV99   (0x62U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000062 */
#define MISC2_CLKDIVP_CLKDIVP_DIV100  (0x63U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000063 */
#define MISC2_CLKDIVP_CLKDIVP_DIV101  (0x64U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000064 */
#define MISC2_CLKDIVP_CLKDIVP_DIV102  (0x65U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000065 */
#define MISC2_CLKDIVP_CLKDIVP_DIV103  (0x66U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000066 */
#define MISC2_CLKDIVP_CLKDIVP_DIV104  (0x67U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000067 */
#define MISC2_CLKDIVP_CLKDIVP_DIV105  (0x68U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000068 */
#define MISC2_CLKDIVP_CLKDIVP_DIV106  (0x69U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000069 */
#define MISC2_CLKDIVP_CLKDIVP_DIV107  (0x6AU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x0000006A */
#define MISC2_CLKDIVP_CLKDIVP_DIV108  (0x6BU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x0000006B */
#define MISC2_CLKDIVP_CLKDIVP_DIV109  (0x6CU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x0000006C */
#define MISC2_CLKDIVP_CLKDIVP_DIV110  (0x6DU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x0000006D */
#define MISC2_CLKDIVP_CLKDIVP_DIV111  (0x6EU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x0000006E */
#define MISC2_CLKDIVP_CLKDIVP_DIV112  (0x6FU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x0000006F */
#define MISC2_CLKDIVP_CLKDIVP_DIV113  (0x70U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000070 */
#define MISC2_CLKDIVP_CLKDIVP_DIV114  (0x71U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000071 */
#define MISC2_CLKDIVP_CLKDIVP_DIV115  (0x72U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000072 */
#define MISC2_CLKDIVP_CLKDIVP_DIV116  (0x73U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000073 */
#define MISC2_CLKDIVP_CLKDIVP_DIV117  (0x74U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000074 */
#define MISC2_CLKDIVP_CLKDIVP_DIV118  (0x75U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000075 */
#define MISC2_CLKDIVP_CLKDIVP_DIV119  (0x76U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000076 */
#define MISC2_CLKDIVP_CLKDIVP_DIV120  (0x77U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000077 */
#define MISC2_CLKDIVP_CLKDIVP_DIV121  (0x78U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000078 */
#define MISC2_CLKDIVP_CLKDIVP_DIV122  (0x79U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000079 */
#define MISC2_CLKDIVP_CLKDIVP_DIV123  (0x7AU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x0000007A */
#define MISC2_CLKDIVP_CLKDIVP_DIV124  (0x7BU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x0000007B */
#define MISC2_CLKDIVP_CLKDIVP_DIV125  (0x7CU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x0000007C */
#define MISC2_CLKDIVP_CLKDIVP_DIV126  (0x7DU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x0000007D */
#define MISC2_CLKDIVP_CLKDIVP_DIV127  (0x7EU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x0000007E */
#define MISC2_CLKDIVP_CLKDIVP_DIV128  (0x7FU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x0000007F */
#define MISC2_CLKDIVP_CLKDIVP_DIV129  (0x80U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000080 */
#define MISC2_CLKDIVP_CLKDIVP_DIV130  (0x81U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000081 */
#define MISC2_CLKDIVP_CLKDIVP_DIV131  (0x82U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000082 */
#define MISC2_CLKDIVP_CLKDIVP_DIV132  (0x83U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000083 */
#define MISC2_CLKDIVP_CLKDIVP_DIV133  (0x84U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000084 */
#define MISC2_CLKDIVP_CLKDIVP_DIV134  (0x85U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000085 */
#define MISC2_CLKDIVP_CLKDIVP_DIV135  (0x86U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000086 */
#define MISC2_CLKDIVP_CLKDIVP_DIV136  (0x87U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000087 */
#define MISC2_CLKDIVP_CLKDIVP_DIV137  (0x88U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000088 */
#define MISC2_CLKDIVP_CLKDIVP_DIV138  (0x89U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000089 */
#define MISC2_CLKDIVP_CLKDIVP_DIV139  (0x8AU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x0000008A */
#define MISC2_CLKDIVP_CLKDIVP_DIV140  (0x8BU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x0000008B */
#define MISC2_CLKDIVP_CLKDIVP_DIV141  (0x8CU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x0000008C */
#define MISC2_CLKDIVP_CLKDIVP_DIV142  (0x8DU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x0000008D */
#define MISC2_CLKDIVP_CLKDIVP_DIV143  (0x8EU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x0000008E */
#define MISC2_CLKDIVP_CLKDIVP_DIV144  (0x8FU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x0000008F */
#define MISC2_CLKDIVP_CLKDIVP_DIV145  (0x90U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000090 */
#define MISC2_CLKDIVP_CLKDIVP_DIV146  (0x91U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000091 */
#define MISC2_CLKDIVP_CLKDIVP_DIV147  (0x92U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000092 */
#define MISC2_CLKDIVP_CLKDIVP_DIV148  (0x93U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000093 */
#define MISC2_CLKDIVP_CLKDIVP_DIV149  (0x94U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000094 */
#define MISC2_CLKDIVP_CLKDIVP_DIV150  (0x95U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000095 */
#define MISC2_CLKDIVP_CLKDIVP_DIV151  (0x96U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000096 */
#define MISC2_CLKDIVP_CLKDIVP_DIV152  (0x97U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000097 */
#define MISC2_CLKDIVP_CLKDIVP_DIV153  (0x98U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000098 */
#define MISC2_CLKDIVP_CLKDIVP_DIV154  (0x99U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x00000099 */
#define MISC2_CLKDIVP_CLKDIVP_DIV155  (0x9AU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x0000009A */
#define MISC2_CLKDIVP_CLKDIVP_DIV156  (0x9BU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x0000009B */
#define MISC2_CLKDIVP_CLKDIVP_DIV157  (0x9CU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x0000009C */
#define MISC2_CLKDIVP_CLKDIVP_DIV158  (0x9DU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x0000009D */
#define MISC2_CLKDIVP_CLKDIVP_DIV159  (0x9EU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x0000009E */
#define MISC2_CLKDIVP_CLKDIVP_DIV160  (0x9FU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x0000009F */
#define MISC2_CLKDIVP_CLKDIVP_DIV161  (0xA0U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000A0 */
#define MISC2_CLKDIVP_CLKDIVP_DIV162  (0xA1U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000A1 */
#define MISC2_CLKDIVP_CLKDIVP_DIV163  (0xA2U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000A2 */
#define MISC2_CLKDIVP_CLKDIVP_DIV164  (0xA3U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000A3 */
#define MISC2_CLKDIVP_CLKDIVP_DIV165  (0xA4U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000A4 */
#define MISC2_CLKDIVP_CLKDIVP_DIV166  (0xA5U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000A5 */
#define MISC2_CLKDIVP_CLKDIVP_DIV167  (0xA6U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000A6 */
#define MISC2_CLKDIVP_CLKDIVP_DIV168  (0xA7U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000A7 */
#define MISC2_CLKDIVP_CLKDIVP_DIV169  (0xA8U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000A8 */
#define MISC2_CLKDIVP_CLKDIVP_DIV170  (0xA9U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000A9 */
#define MISC2_CLKDIVP_CLKDIVP_DIV171  (0xAAU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000AA */
#define MISC2_CLKDIVP_CLKDIVP_DIV172  (0xABU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000AB */
#define MISC2_CLKDIVP_CLKDIVP_DIV173  (0xACU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000AC */
#define MISC2_CLKDIVP_CLKDIVP_DIV174  (0xADU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000AD */
#define MISC2_CLKDIVP_CLKDIVP_DIV175  (0xAEU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000AE */
#define MISC2_CLKDIVP_CLKDIVP_DIV176  (0xAFU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000AF */
#define MISC2_CLKDIVP_CLKDIVP_DIV177  (0xB0U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000B0 */
#define MISC2_CLKDIVP_CLKDIVP_DIV178  (0xB1U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000B1 */
#define MISC2_CLKDIVP_CLKDIVP_DIV179  (0xB2U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000B2 */
#define MISC2_CLKDIVP_CLKDIVP_DIV180  (0xB3U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000B3 */
#define MISC2_CLKDIVP_CLKDIVP_DIV181  (0xB4U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000B4 */
#define MISC2_CLKDIVP_CLKDIVP_DIV182  (0xB5U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000B5 */
#define MISC2_CLKDIVP_CLKDIVP_DIV183  (0xB6U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000B6 */
#define MISC2_CLKDIVP_CLKDIVP_DIV184  (0xB7U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000B7 */
#define MISC2_CLKDIVP_CLKDIVP_DIV185  (0xB8U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000B8 */
#define MISC2_CLKDIVP_CLKDIVP_DIV186  (0xB9U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000B9 */
#define MISC2_CLKDIVP_CLKDIVP_DIV187  (0xBAU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000BA */
#define MISC2_CLKDIVP_CLKDIVP_DIV188  (0xBBU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000BB */
#define MISC2_CLKDIVP_CLKDIVP_DIV189  (0xBCU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000BC */
#define MISC2_CLKDIVP_CLKDIVP_DIV190  (0xBDU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000BD */
#define MISC2_CLKDIVP_CLKDIVP_DIV191  (0xBEU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000BE */
#define MISC2_CLKDIVP_CLKDIVP_DIV192  (0xBFU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000BF */
#define MISC2_CLKDIVP_CLKDIVP_DIV193  (0xC0U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000C0 */
#define MISC2_CLKDIVP_CLKDIVP_DIV194  (0xC1U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000C1 */
#define MISC2_CLKDIVP_CLKDIVP_DIV195  (0xC2U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000C2 */
#define MISC2_CLKDIVP_CLKDIVP_DIV196  (0xC3U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000C3 */
#define MISC2_CLKDIVP_CLKDIVP_DIV197  (0xC4U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000C4 */
#define MISC2_CLKDIVP_CLKDIVP_DIV198  (0xC5U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000C5 */
#define MISC2_CLKDIVP_CLKDIVP_DIV199  (0xC6U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000C6 */
#define MISC2_CLKDIVP_CLKDIVP_DIV200  (0xC7U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000C7 */
#define MISC2_CLKDIVP_CLKDIVP_DIV201  (0xC8U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000C8 */
#define MISC2_CLKDIVP_CLKDIVP_DIV202  (0xC9U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000C9 */
#define MISC2_CLKDIVP_CLKDIVP_DIV203  (0xCAU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000CA */
#define MISC2_CLKDIVP_CLKDIVP_DIV204  (0xCBU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000CB */
#define MISC2_CLKDIVP_CLKDIVP_DIV205  (0xCCU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000CC */
#define MISC2_CLKDIVP_CLKDIVP_DIV206  (0xCDU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000CD */
#define MISC2_CLKDIVP_CLKDIVP_DIV207  (0xCEU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000CE */
#define MISC2_CLKDIVP_CLKDIVP_DIV208  (0xCFU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000CF */
#define MISC2_CLKDIVP_CLKDIVP_DIV209  (0xD0U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000D0 */
#define MISC2_CLKDIVP_CLKDIVP_DIV210  (0xD1U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000D1 */
#define MISC2_CLKDIVP_CLKDIVP_DIV211  (0xD2U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000D2 */
#define MISC2_CLKDIVP_CLKDIVP_DIV212  (0xD3U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000D3 */
#define MISC2_CLKDIVP_CLKDIVP_DIV213  (0xD4U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000D4 */
#define MISC2_CLKDIVP_CLKDIVP_DIV214  (0xD5U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000D5 */
#define MISC2_CLKDIVP_CLKDIVP_DIV215  (0xD6U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000D6 */
#define MISC2_CLKDIVP_CLKDIVP_DIV216  (0xD7U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000D7 */
#define MISC2_CLKDIVP_CLKDIVP_DIV217  (0xD8U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000D8 */
#define MISC2_CLKDIVP_CLKDIVP_DIV218  (0xD9U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000D9 */
#define MISC2_CLKDIVP_CLKDIVP_DIV219  (0xDAU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000DA */
#define MISC2_CLKDIVP_CLKDIVP_DIV220  (0xDBU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000DB */
#define MISC2_CLKDIVP_CLKDIVP_DIV221  (0xDCU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000DC */
#define MISC2_CLKDIVP_CLKDIVP_DIV222  (0xDDU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000DD */
#define MISC2_CLKDIVP_CLKDIVP_DIV223  (0xDEU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000DE */
#define MISC2_CLKDIVP_CLKDIVP_DIV224  (0xDFU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000DF */
#define MISC2_CLKDIVP_CLKDIVP_DIV225  (0xE0U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000E0 */
#define MISC2_CLKDIVP_CLKDIVP_DIV226  (0xE1U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000E1 */
#define MISC2_CLKDIVP_CLKDIVP_DIV227  (0xE2U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000E2 */
#define MISC2_CLKDIVP_CLKDIVP_DIV228  (0xE3U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000E3 */
#define MISC2_CLKDIVP_CLKDIVP_DIV229  (0xE4U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000E4 */
#define MISC2_CLKDIVP_CLKDIVP_DIV230  (0xE5U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000E5 */
#define MISC2_CLKDIVP_CLKDIVP_DIV231  (0xE6U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000E6 */
#define MISC2_CLKDIVP_CLKDIVP_DIV232  (0xE7U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000E7 */
#define MISC2_CLKDIVP_CLKDIVP_DIV233  (0xE8U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000E8 */
#define MISC2_CLKDIVP_CLKDIVP_DIV234  (0xE9U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000E9 */
#define MISC2_CLKDIVP_CLKDIVP_DIV235  (0xEAU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000EA */
#define MISC2_CLKDIVP_CLKDIVP_DIV236  (0xEBU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000EB */
#define MISC2_CLKDIVP_CLKDIVP_DIV237  (0xECU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000EC */
#define MISC2_CLKDIVP_CLKDIVP_DIV238  (0xEDU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000ED */
#define MISC2_CLKDIVP_CLKDIVP_DIV239  (0xEEU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000EE */
#define MISC2_CLKDIVP_CLKDIVP_DIV240  (0xEFU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000EF */
#define MISC2_CLKDIVP_CLKDIVP_DIV241  (0xF0U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000F0 */
#define MISC2_CLKDIVP_CLKDIVP_DIV242  (0xF1U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000F1 */
#define MISC2_CLKDIVP_CLKDIVP_DIV243  (0xF2U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000F2 */
#define MISC2_CLKDIVP_CLKDIVP_DIV244  (0xF3U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000F3 */
#define MISC2_CLKDIVP_CLKDIVP_DIV245  (0xF4U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000F4 */
#define MISC2_CLKDIVP_CLKDIVP_DIV246  (0xF5U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000F5 */
#define MISC2_CLKDIVP_CLKDIVP_DIV247  (0xF6U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000F6 */
#define MISC2_CLKDIVP_CLKDIVP_DIV248  (0xF7U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000F7 */
#define MISC2_CLKDIVP_CLKDIVP_DIV249  (0xF8U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000F8 */
#define MISC2_CLKDIVP_CLKDIVP_DIV250  (0xF9U << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000F9 */
#define MISC2_CLKDIVP_CLKDIVP_DIV251  (0xFAU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000FA */
#define MISC2_CLKDIVP_CLKDIVP_DIV252  (0xFBU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000FB */
#define MISC2_CLKDIVP_CLKDIVP_DIV253  (0xFCU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000FC */
#define MISC2_CLKDIVP_CLKDIVP_DIV254  (0xFDU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000FD */
#define MISC2_CLKDIVP_CLKDIVP_DIV255  (0xFEU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000FE */
#define MISC2_CLKDIVP_CLKDIVP_DIV256  (0xFFU << MISC2_CLKDIVP_CLKDIVP_Pos)     /*!< 0x000000FF */

/**************  Bits definition for MISC2_HCLKEN register   ******************/
//#define MISC2_HCLKEN_HCLKEN_Pos       (0U)                                     
//#define MISC2_HCLKEN_HCLKEN_Msk       (0x1FFU << MISC2_HCLKEN_HCLKEN_Pos)      /*!< 0x000001FF */
//#define MISC2_HCLKEN_HCLKEN            MISC2_HCLKEN_HCLKEN_Msk                 /*!< This register is used to control clock enable of each AHB module */ 
//#define MISC2_HCLKEN_ARB_Pos          (1U)                                     
//#define MISC2_HCLKEN_ARB_Msk          (0x1U << MISC2_HCLKEN_ARB_Pos)           /*!< 0x00000002 */
//#define MISC2_HCLKEN_ARB               MISC2_HCLKEN_ARB_Msk                    /*!< Arbiter & Bus Matrix */ 
//#define MISC2_HCLKEN_FLASH_Pos        (2U)                                     
//#define MISC2_HCLKEN_FLASH_Msk        (0x1U << MISC2_HCLKEN_FLASH_Pos)         /*!< 0x00000004 */
//#define MISC2_HCLKEN_FLASH             MISC2_HCLKEN_FLASH_Msk                  /*!< Flash Controller */ 
//#define MISC2_HCLKEN_SRAM_Pos         (3U)                                     
//#define MISC2_HCLKEN_SRAM_Msk         (0x1U << MISC2_HCLKEN_SRAM_Pos)          /*!< 0x00000008 */
//#define MISC2_HCLKEN_SRAM              MISC2_HCLKEN_SRAM_Msk                   /*!< SRAM Controller */ 
#define MISC2_HCLKEN_DMA_Pos          (4U)                                     
#define MISC2_HCLKEN_DMA_Msk          (0x1U << MISC2_HCLKEN_DMA_Pos)           /*!< 0x00000010 */
#define MISC2_HCLKEN_DMA               MISC2_HCLKEN_DMA_Msk                    /*!< DMA Controller */ 
#define MISC2_HCLKEN_GPIO_Pos         (5U)                                     
#define MISC2_HCLKEN_GPIO_Msk         (0x1U << MISC2_HCLKEN_GPIO_Pos)          /*!< 0x00000020 */
#define MISC2_HCLKEN_GPIO              MISC2_HCLKEN_GPIO_Msk                   /*!< GPIO Controller */ 
#define MISC2_HCLKEN_LCD_Pos          (6U)                                     
#define MISC2_HCLKEN_LCD_Msk          (0x1U << MISC2_HCLKEN_LCD_Pos)           /*!< 0x00000040 */
#define MISC2_HCLKEN_LCD               MISC2_HCLKEN_LCD_Msk                    /*!< LCD Controller */ 
#define MISC2_HCLKEN_CRYPT_Pos        (8U)                                     
#define MISC2_HCLKEN_CRYPT_Msk        (0x1U << MISC2_HCLKEN_CRYPT_Pos)         /*!< 0x00000100 */
#define MISC2_HCLKEN_CRYPT             MISC2_HCLKEN_CRYPT_Msk                  /*!< CRYPT Controller */ 

/**************  Bits definition for MISC2_PCLKEN register   ******************/
//#define MISC2_PCLKEN_PCLKEN_Pos       (0U)                                     
//#define MISC2_PCLKEN_PCLKEN_Msk       (0x002FFFFFU << MISC2_PCLKEN_PCLKEN_Pos) /*!< 0x002FFFFF */
//#define MISC2_PCLKEN_PCLKEN            MISC2_PCLKEN_PCLKEN_Msk                 /*!< This register is used to control clock enable of each APB module */ 
//#define MISC2_PCLKEN_AHB2APB_Pos      (0U)                                     
//#define MISC2_PCLKEN_AHB2APB_Msk      (0x1U << MISC2_PCLKEN_AHB2APB_Pos)       /*!< 0x00000001 */
//#define MISC2_PCLKEN_AHB2APB           MISC2_PCLKEN_AHB2APB_Msk                /*!< AHB2APB Bridge */ 
#define MISC2_PCLKEN_DMA_Pos          (1U)                                     
#define MISC2_PCLKEN_DMA_Msk          (0x1U << MISC2_PCLKEN_DMA_Pos)           /*!< 0x00000002 */
#define MISC2_PCLKEN_DMA               MISC2_PCLKEN_DMA_Msk                    /*!< DMA Controller */ 
#define MISC2_PCLKEN_I2C_Pos          (2U)                                     
#define MISC2_PCLKEN_I2C_Msk          (0x1U << MISC2_PCLKEN_I2C_Pos)           /*!< 0x00000004 */
#define MISC2_PCLKEN_I2C               MISC2_PCLKEN_I2C_Msk                    /*!< I2C */ 
#define MISC2_PCLKEN_SPI1_Pos         (3U)                                     
#define MISC2_PCLKEN_SPI1_Msk         (0x1U << MISC2_PCLKEN_SPI1_Pos)          /*!< 0x00000008 */
#define MISC2_PCLKEN_SPI1              MISC2_PCLKEN_SPI1_Msk                   /*!< SPI1 */ 
#define MISC2_PCLKEN_UART0_Pos        (4U)                                     
#define MISC2_PCLKEN_UART0_Msk        (0x1U << MISC2_PCLKEN_UART0_Pos)         /*!< 0x00000010 */
#define MISC2_PCLKEN_UART0             MISC2_PCLKEN_UART0_Msk                  /*!< UART0 */ 
#define MISC2_PCLKEN_UART1_Pos        (5U)                                     
#define MISC2_PCLKEN_UART1_Msk        (0x1U << MISC2_PCLKEN_UART1_Pos)         /*!< 0x00000020 */
#define MISC2_PCLKEN_UART1             MISC2_PCLKEN_UART1_Msk                  /*!< UART1 */ 
#define MISC2_PCLKEN_UART2_Pos        (6U)                                     
#define MISC2_PCLKEN_UART2_Msk        (0x1U << MISC2_PCLKEN_UART2_Pos)         /*!< 0x00000040 */
#define MISC2_PCLKEN_UART2             MISC2_PCLKEN_UART2_Msk                  /*!< UART2 */ 
#define MISC2_PCLKEN_UART3_Pos        (7U)                                     
#define MISC2_PCLKEN_UART3_Msk        (0x1U << MISC2_PCLKEN_UART3_Pos)         /*!< 0x00000080 */
#define MISC2_PCLKEN_UART3             MISC2_PCLKEN_UART3_Msk                  /*!< UART3 */ 
#define MISC2_PCLKEN_UART4_Pos        (8U)                                     
#define MISC2_PCLKEN_UART4_Msk        (0x1U << MISC2_PCLKEN_UART4_Pos)         /*!< 0x00000100 */
#define MISC2_PCLKEN_UART4             MISC2_PCLKEN_UART4_Msk                  /*!< UART4 */ 
#define MISC2_PCLKEN_UART5_Pos        (9U)                                    
#define MISC2_PCLKEN_UART5_Msk        (0x1U << MISC2_PCLKEN_UART5_Pos)         /*!< 0x00000200 */
#define MISC2_PCLKEN_UART5             MISC2_PCLKEN_UART5_Msk                  /*!< UART5 */ 
#define MISC2_PCLKEN_ISO78160_Pos     (10U)                                     
#define MISC2_PCLKEN_ISO78160_Msk     (0x1U << MISC2_PCLKEN_ISO78160_Pos)      /*!< 0x00000400 */
#define MISC2_PCLKEN_ISO78160          MISC2_PCLKEN_ISO78160_Msk               /*!< ISO78160 */ 
#define MISC2_PCLKEN_ISO78161_Pos     (11U)                                     
#define MISC2_PCLKEN_ISO78161_Msk     (0x1U << MISC2_PCLKEN_ISO78161_Pos)      /*!< 0x00000800 */
#define MISC2_PCLKEN_ISO78161          MISC2_PCLKEN_ISO78161_Msk               /*!< ISO78161 */ 
#define MISC2_PCLKEN_TIMER_Pos        (12U)                                     
#define MISC2_PCLKEN_TIMER_Msk        (0x1U << MISC2_PCLKEN_TIMER_Pos)         /*!< 0x00001000 */
#define MISC2_PCLKEN_TIMER             MISC2_PCLKEN_TIMER_Msk                  /*!< Timer */ 
#define MISC2_PCLKEN_MISC_Pos         (13U)                                     
#define MISC2_PCLKEN_MISC_Msk         (0x1U << MISC2_PCLKEN_MISC_Pos)          /*!< 0x00002000 */
#define MISC2_PCLKEN_MISC              MISC2_PCLKEN_MISC_Msk                   /*!< MISC */ 
#define MISC2_PCLKEN_MISC2_Pos        (14U)                                     
#define MISC2_PCLKEN_MISC2_Msk        (0x1U << MISC2_PCLKEN_MISC2_Pos)     /*!< 0x00004000 */
#define MISC2_PCLKEN_MISC2             MISC2_PCLKEN_MISC2_Msk              /*!< LCD & MISC2 */ 
#define MISC2_PCLKEN_PMU_Pos          (15U)                                     
#define MISC2_PCLKEN_PMU_Msk          (0x1U << MISC2_PCLKEN_PMU_Pos)           /*!< 0x00008000 */
#define MISC2_PCLKEN_PMU               MISC2_PCLKEN_PMU_Msk                    /*!< PMU */ 
#define MISC2_PCLKEN_RTC_Pos          (16U)                                     
#define MISC2_PCLKEN_RTC_Msk          (0x1U << MISC2_PCLKEN_RTC_Pos)           /*!< 0x00010000 */
#define MISC2_PCLKEN_RTC               MISC2_PCLKEN_RTC_Msk                    /*!< RTC */ 
#define MISC2_PCLKEN_ANA_Pos          (17U)                                     
#define MISC2_PCLKEN_ANA_Msk          (0x1U << MISC2_PCLKEN_ANA_Pos)           /*!< 0x00020000 */
#define MISC2_PCLKEN_ANA               MISC2_PCLKEN_ANA_Msk                    /*!< ANA */ 
#define MISC2_PCLKEN_U32K0_Pos        (18U)                                     
#define MISC2_PCLKEN_U32K0_Msk        (0x1U << MISC2_PCLKEN_U32K0_Pos)         /*!< 0x00040000 */
#define MISC2_PCLKEN_U32K0             MISC2_PCLKEN_U32K0_Msk                  /*!< U32K 0 */ 
#define MISC2_PCLKEN_U32K1_Pos        (19U)                                     
#define MISC2_PCLKEN_U32K1_Msk        (0x1U << MISC2_PCLKEN_U32K1_Pos)         /*!< 0x00080000 */
#define MISC2_PCLKEN_U32K1             MISC2_PCLKEN_U32K1_Msk                  /*!< U32K 1 */ 
#define MISC2_PCLKEN_SPI2_Pos         (21U)                                     
#define MISC2_PCLKEN_SPI2_Msk         (0x1U << MISC2_PCLKEN_SPI2_Pos)          /*!< 0x00200000 */
#define MISC2_PCLKEN_SPI2              MISC2_PCLKEN_SPI2_Msk                   /*!< SPI2 */ 

/******************************************************************************/
/*                                                                            */
/*                              CRYPT controller (CRYPT)                      */
/*                                                                            */
/******************************************************************************/

/**************  Bits definition for CRYPT_CTRL register     ******************/
#define CRYPT_CTRL_ACT_Pos            (0U)                                     
#define CRYPT_CTRL_ACT_Msk            (0x1U << CRYPT_CTRL_ACT_Pos)             /*!< 0x00000001 */
#define CRYPT_CTRL_ACT                 CRYPT_CTRL_ACT_Msk                      /*!< Write 1 to this bit will start an operation specified in the MODE register */ 
#define CRYPT_CTRL_MODE_Pos           (4U)                                     
#define CRYPT_CTRL_MODE_Msk           (0x7U << CRYPT_CTRL_MODE_Pos)            /*!< 0x00000070 */
#define CRYPT_CTRL_MODE                CRYPT_CTRL_MODE_Msk                     /*!< This register controls the operation mode of crypt engine */ 
#define CRYPT_CTRL_MODE_MULTIPLY      (0x0U << CRYPT_CTRL_MODE_Pos) 
#define CRYPT_CTRL_MODE_ADD           (0x1U << CRYPT_CTRL_MODE_Pos)
#define CRYPT_CTRL_MODE_SUB           (0x2U << CRYPT_CTRL_MODE_Pos)
#define CRYPT_CTRL_MODE_RSHIFT1       (0x3U << CRYPT_CTRL_MODE_Pos)
#define CRYPT_CTRL_LENGTH_Pos         (8U)                                     
#define CRYPT_CTRL_LENGTH_Msk         (0xFU << CRYPT_CTRL_LENGTH_Pos)          /*!< 0x00000F00 */
#define CRYPT_CTRL_LENGTH              CRYPT_CTRL_LENGTH_Msk                   /*!< This bit is used to control the VLI length of current operation */ 
#define CRYPT_CTRL_LENGTH_32          (0x0U << CRYPT_CTRL_LENGTH_Pos)
#define CRYPT_CTRL_LENGTH_64          (0x1U << CRYPT_CTRL_LENGTH_Pos)
#define CRYPT_CTRL_LENGTH_96          (0x2U << CRYPT_CTRL_LENGTH_Pos)
#define CRYPT_CTRL_LENGTH_128         (0x3U << CRYPT_CTRL_LENGTH_Pos)
#define CRYPT_CTRL_LENGTH_160         (0x4U << CRYPT_CTRL_LENGTH_Pos)
#define CRYPT_CTRL_LENGTH_192         (0x5U << CRYPT_CTRL_LENGTH_Pos)
#define CRYPT_CTRL_LENGTH_224         (0x6U << CRYPT_CTRL_LENGTH_Pos)
#define CRYPT_CTRL_LENGTH_256         (0x7U << CRYPT_CTRL_LENGTH_Pos)
#define CRYPT_CTRL_LENGTH_288         (0x8U << CRYPT_CTRL_LENGTH_Pos)
#define CRYPT_CTRL_LENGTH_320         (0x9U << CRYPT_CTRL_LENGTH_Pos)
#define CRYPT_CTRL_LENGTH_352         (0xAU << CRYPT_CTRL_LENGTH_Pos)
#define CRYPT_CTRL_LENGTH_384         (0xBU << CRYPT_CTRL_LENGTH_Pos)
#define CRYPT_CTRL_LENGTH_416         (0xCU << CRYPT_CTRL_LENGTH_Pos)
#define CRYPT_CTRL_LENGTH_448         (0xDU << CRYPT_CTRL_LENGTH_Pos)
#define CRYPT_CTRL_LENGTH_480         (0xEU << CRYPT_CTRL_LENGTH_Pos)
#define CRYPT_CTRL_LENGTH_512         (0xFU << CRYPT_CTRL_LENGTH_Pos)
#define CRYPT_CTRL_NOSTOP_Pos         (15U)                                     
#define CRYPT_CTRL_NOSTOP_Msk         (0x1U << CRYPT_CTRL_NOSTOP_Pos)          /*!< 0x00008000 */
#define CRYPT_CTRL_NOSTOP              CRYPT_CTRL_NOSTOP_Msk                   /*!< This register is used to control if the CPU will be stop by CRYPT engine when the CRYPT engine is busy and CPU read or write CRYPT engine register */ 

/**************  Bits definition for CRYPT_PTRA register     ******************/
#define CRYPT_PTRA_PTRA_Pos            (0U)                                     
#define CRYPT_PTRA_PTRA_Msk            (0x7FFFU << CRYPT_PTRA_PTRA_Pos)        /*!< 0x00007FFF */
#define CRYPT_PTRA_PTRA                 CRYPT_PTRA_PTRA_Msk                    /*!< This is the PTRA register of CRYPT controller */ 

/**************  Bits definition for CRYPT_PTRB register     ******************/
#define CRYPT_PTRB_PTRB_Pos            (0U)                                     
#define CRYPT_PTRB_PTRB_Msk            (0x7FFFU << CRYPT_PTRB_PTRB_Pos)        /*!< 0x00007FFF */
#define CRYPT_PTRB_PTRB                 CRYPT_PTRB_PTRB_Msk                    /*!< This is the PTRB register of CRYPT controller */ 

/**************  Bits definition for CRYPT_PTRO register     ******************/
#define CRYPT_PTRO_PTRO_Pos            (0U)                                     
#define CRYPT_PTRO_PTRO_Msk            (0x7FFFU << CRYPT_PTRO_PTRO_Pos)        /*!< 0x00007FFF */
#define CRYPT_PTRO_PTRO                 CRYPT_PTRO_PTRO_Msk                    /*!< This is the PTRO register of CRYPT controller */ 

/*************  Bits definition for CRYPT_CARRY register     ******************/
#define CRYPT_CARRY_CARRY_Pos          (0U)                                     
#define CRYPT_CARRY_CARRY_Msk          (0x1U << CRYPT_CARRY_CARRY_Pos)         /*!< 0x00000001 */
#define CRYPT_CARRY_CARRY               CRYPT_CARRY_CARRY_Msk                  /*!< This bit represent the carry bit after add operation is done */ 


/**
  * @}
  */

/******************************************************************************/
/*                                                                            */
/*                        Power Management Unit (PMU)                         */
/*                                                                            */
/******************************************************************************/
#define PMU_DSLEEPEN     (volatile unsigned *)(PMU_BASE + 0x0000)
#define PMU_DSLEEPPASS   (volatile unsigned *)(PMU_BASE + 0x0004)
#define PMU_CONTROL      (volatile unsigned *)(PMU_BASE + 0x0008)
#define PMU_STS          (volatile unsigned *)(PMU_BASE + 0x000C)
#define PMU_IOAOEN       (volatile unsigned *)(PMU_BASE + 0x0010)
#define PMU_IOAIE        (volatile unsigned *)(PMU_BASE + 0x0014)
#define PMU_IOADAT       (volatile unsigned *)(PMU_BASE + 0x0018)
#define PMU_IOAATT       (volatile unsigned *)(PMU_BASE + 0x001C)
#define PMU_IOAWKUEN     (volatile unsigned *)(PMU_BASE + 0x0020)
#define PMU_IOASTS       (volatile unsigned *)(PMU_BASE + 0x0024)
#define PMU_IOAINTSTS    (volatile unsigned *)(PMU_BASE + 0x0028)
#define PMU_IOASEL       (volatile unsigned *)(PMU_BASE + 0x0038)
#define VERSIONID        (volatile unsigned *)(PMU_BASE + 0x003C)
#define PMU_WDTPASS      (volatile unsigned *)(PMU_BASE + 0x0040)
#define PMU_WDTEN        (volatile unsigned *)(PMU_BASE + 0x0044)
#define PMU_WDTCLR       (volatile unsigned *)(PMU_BASE + 0x0048)
//#define PMU_WDTSTS       (volatile unsigned *)(PMU_BASE + 0x004C)
#define PMU_IOANODEG     (volatile unsigned *)(PMU_BASE + 0x0050)

#define PMU_RAM0         (volatile unsigned *)(RETRAM_BASE + 0x0000)
#define PMU_RAM1         (volatile unsigned *)(RETRAM_BASE + 0x0004)
#define PMU_RAM2         (volatile unsigned *)(RETRAM_BASE + 0x0008)
#define PMU_RAM3         (volatile unsigned *)(RETRAM_BASE + 0x000C)
#define PMU_RAM4         (volatile unsigned *)(RETRAM_BASE + 0x0010)
#define PMU_RAM5         (volatile unsigned *)(RETRAM_BASE + 0x0014)
#define PMU_RAM6         (volatile unsigned *)(RETRAM_BASE + 0x0018)
#define PMU_RAM7         (volatile unsigned *)(RETRAM_BASE + 0x001C)
#define PMU_RAM8         (volatile unsigned *)(RETRAM_BASE + 0x0020)
#define PMU_RAM9         (volatile unsigned *)(RETRAM_BASE + 0x0024)
#define PMU_RAM10        (volatile unsigned *)(RETRAM_BASE + 0x0028)
#define PMU_RAM11        (volatile unsigned *)(RETRAM_BASE + 0x002C)
#define PMU_RAM12        (volatile unsigned *)(RETRAM_BASE + 0x0030)
#define PMU_RAM13        (volatile unsigned *)(RETRAM_BASE + 0x0034)
#define PMU_RAM14        (volatile unsigned *)(RETRAM_BASE + 0x0038)
#define PMU_RAM15        (volatile unsigned *)(RETRAM_BASE + 0x003C)
#define PMU_RAM16        (volatile unsigned *)(RETRAM_BASE + 0x0040)
#define PMU_RAM17        (volatile unsigned *)(RETRAM_BASE + 0x0044)
#define PMU_RAM18        (volatile unsigned *)(RETRAM_BASE + 0x0048)
#define PMU_RAM19        (volatile unsigned *)(RETRAM_BASE + 0x004C)
#define PMU_RAM20        (volatile unsigned *)(RETRAM_BASE + 0x0050)
#define PMU_RAM21        (volatile unsigned *)(RETRAM_BASE + 0x0054)
#define PMU_RAM22        (volatile unsigned *)(RETRAM_BASE + 0x0058)
#define PMU_RAM23        (volatile unsigned *)(RETRAM_BASE + 0x005C)
#define PMU_RAM24        (volatile unsigned *)(RETRAM_BASE + 0x0060)
#define PMU_RAM25        (volatile unsigned *)(RETRAM_BASE + 0x0064)
#define PMU_RAM26        (volatile unsigned *)(RETRAM_BASE + 0x0068)
#define PMU_RAM27        (volatile unsigned *)(RETRAM_BASE + 0x006C)
#define PMU_RAM28        (volatile unsigned *)(RETRAM_BASE + 0x0070)
#define PMU_RAM29        (volatile unsigned *)(RETRAM_BASE + 0x0074)
#define PMU_RAM30        (volatile unsigned *)(RETRAM_BASE + 0x0078)
#define PMU_RAM31        (volatile unsigned *)(RETRAM_BASE + 0x007C)
#define PMU_RAM32        (volatile unsigned *)(RETRAM_BASE + 0x0080)
#define PMU_RAM33        (volatile unsigned *)(RETRAM_BASE + 0x0084)
#define PMU_RAM34        (volatile unsigned *)(RETRAM_BASE + 0x0088)
#define PMU_RAM35        (volatile unsigned *)(RETRAM_BASE + 0x008C)
#define PMU_RAM36        (volatile unsigned *)(RETRAM_BASE + 0x0090)
#define PMU_RAM37        (volatile unsigned *)(RETRAM_BASE + 0x0094)
#define PMU_RAM38        (volatile unsigned *)(RETRAM_BASE + 0x0098)
#define PMU_RAM39        (volatile unsigned *)(RETRAM_BASE + 0x009C)
#define PMU_RAM40        (volatile unsigned *)(RETRAM_BASE + 0x00A0)
#define PMU_RAM41        (volatile unsigned *)(RETRAM_BASE + 0x00A4)
#define PMU_RAM42        (volatile unsigned *)(RETRAM_BASE + 0x00A8)
#define PMU_RAM43        (volatile unsigned *)(RETRAM_BASE + 0x00AC)
#define PMU_RAM44        (volatile unsigned *)(RETRAM_BASE + 0x00B0)
#define PMU_RAM45        (volatile unsigned *)(RETRAM_BASE + 0x00B4)
#define PMU_RAM46        (volatile unsigned *)(RETRAM_BASE + 0x00B8)
#define PMU_RAM47        (volatile unsigned *)(RETRAM_BASE + 0x00BC)
#define PMU_RAM48        (volatile unsigned *)(RETRAM_BASE + 0x00C0)
#define PMU_RAM49        (volatile unsigned *)(RETRAM_BASE + 0x00C4)
#define PMU_RAM50        (volatile unsigned *)(RETRAM_BASE + 0x00C8)
#define PMU_RAM51        (volatile unsigned *)(RETRAM_BASE + 0x00CC)
#define PMU_RAM52        (volatile unsigned *)(RETRAM_BASE + 0x00D0)
#define PMU_RAM53        (volatile unsigned *)(RETRAM_BASE + 0x00D4)
#define PMU_RAM54        (volatile unsigned *)(RETRAM_BASE + 0x00D8)
#define PMU_RAM55        (volatile unsigned *)(RETRAM_BASE + 0x00DC)
#define PMU_RAM56        (volatile unsigned *)(RETRAM_BASE + 0x00E0)
#define PMU_RAM57        (volatile unsigned *)(RETRAM_BASE + 0x00E4)
#define PMU_RAM58        (volatile unsigned *)(RETRAM_BASE + 0x00E8)
#define PMU_RAM59        (volatile unsigned *)(RETRAM_BASE + 0x00EC)
#define PMU_RAM60        (volatile unsigned *)(RETRAM_BASE + 0x00F0)
#define PMU_RAM61        (volatile unsigned *)(RETRAM_BASE + 0x00F4)
#define PMU_RAM62        (volatile unsigned *)(RETRAM_BASE + 0x00F8)
#define PMU_RAM63        (volatile unsigned *)(RETRAM_BASE + 0x00FC)

/******************************************************************************/
/*                                                                            */
/*                          Analog Controller (ANA)                           */
/*                                                                            */
/******************************************************************************/
#define ANA_REG0        (volatile unsigned *)(ANA_BASE + 0x0000)
#define ANA_REG1        (volatile unsigned *)(ANA_BASE + 0x0004)
#define ANA_REG2        (volatile unsigned *)(ANA_BASE + 0x0008)
#define ANA_REG3        (volatile unsigned *)(ANA_BASE + 0x000C)
#define ANA_REG4        (volatile unsigned *)(ANA_BASE + 0x0010)
#define ANA_REG5        (volatile unsigned *)(ANA_BASE + 0x0014)
#define ANA_REG6        (volatile unsigned *)(ANA_BASE + 0x0018)
#define ANA_REG7        (volatile unsigned *)(ANA_BASE + 0x001C)
#define ANA_REG8        (volatile unsigned *)(ANA_BASE + 0x0020)
#define ANA_REG9        (volatile unsigned *)(ANA_BASE + 0x0024)
#define ANA_REGA        (volatile unsigned *)(ANA_BASE + 0x0028)
#define ANA_REGB        (volatile unsigned *)(ANA_BASE + 0x002C)
#define ANA_REGC        (volatile unsigned *)(ANA_BASE + 0x0030)
#define ANA_REGD        (volatile unsigned *)(ANA_BASE + 0x0034)
#define ANA_REGE        (volatile unsigned *)(ANA_BASE + 0x0038)
#define ANA_REGF        (volatile unsigned *)(ANA_BASE + 0x003C)
//#define ANA_REG10       (volatile unsigned *)(ANA_BASE + 0x0040)
//#define ANA_REG11       (volatile unsigned *)(ANA_BASE + 0x0044)
//#define ANA_REG12       (volatile unsigned *)(ANA_BASE + 0x0048)
#define ANA_CTRL        (volatile unsigned *)(ANA_BASE + 0x0050)
#define ANA_CMPOUT      (volatile unsigned *)(ANA_BASE + 0x0054)
//#define ANA_VERSION     (volatile unsigned *)(ANA_BASE + 0x0058)
//#define ANA_ADCSTATE    (volatile unsigned *)(ANA_BASE + 0x005C)
#define ANA_INTSTS      (volatile unsigned *)(ANA_BASE + 0x0060)
#define ANA_INTEN       (volatile unsigned *)(ANA_BASE + 0x0064)
#define ANA_ADCCTRL     (volatile unsigned *)(ANA_BASE + 0x0068)
#define ANA_ADCDATA0    (volatile unsigned *)(ANA_BASE + 0x0070)
#define ANA_ADCDATA1    (volatile unsigned *)(ANA_BASE + 0x0074)
#define ANA_ADCDATA2    (volatile unsigned *)(ANA_BASE + 0x0078)
#define ANA_ADCDATA3    (volatile unsigned *)(ANA_BASE + 0x007C)
#define ANA_ADCDATA4    (volatile unsigned *)(ANA_BASE + 0x0080)
#define ANA_ADCDATA5    (volatile unsigned *)(ANA_BASE + 0x0084)
#define ANA_ADCDATA6    (volatile unsigned *)(ANA_BASE + 0x0088)
#define ANA_ADCDATA7    (volatile unsigned *)(ANA_BASE + 0x008C)
#define ANA_ADCDATA8    (volatile unsigned *)(ANA_BASE + 0x0090)
#define ANA_ADCDATA9    (volatile unsigned *)(ANA_BASE + 0x0094)
#define ANA_ADCDATAA    (volatile unsigned *)(ANA_BASE + 0x0098)
#define ANA_ADCDATAB    (volatile unsigned *)(ANA_BASE + 0x009C)
//#define ANA_ADCDATAC    (volatile unsigned *)(ANA_BASE + 0x00A0)
//#define ANA_ADCDATAD    (volatile unsigned *)(ANA_BASE + 0x00A4)
//#define ANA_ADCDATAE    (volatile unsigned *)(ANA_BASE + 0x00A8)
//#define ANA_ADCDATAF    (volatile unsigned *)(ANA_BASE + 0x00AC)
#define ANA_CMPCNT1     (volatile unsigned *)(ANA_BASE + 0x00B0)
#define ANA_CMPCNT2     (volatile unsigned *)(ANA_BASE + 0x00B4)
#define ANA_MISC        (volatile unsigned *)(ANA_BASE + 0x00B8)

/******************************************************************************/
/*                                                                            */
/*                           RTC Controller (RTC)                             */
/*                                                                            */
/******************************************************************************/
#define RTC_SEC          (volatile unsigned *)(RTC_BASE + 0x0000)
#define RTC_MIN          (volatile unsigned *)(RTC_BASE + 0x0004)
#define RTC_HOUR         (volatile unsigned *)(RTC_BASE + 0x0008)
#define RTC_DAY          (volatile unsigned *)(RTC_BASE + 0x000C)
#define RTC_WEEK         (volatile unsigned *)(RTC_BASE + 0x0010)
#define RTC_MON          (volatile unsigned *)(RTC_BASE + 0x0014)
#define RTC_YEAR         (volatile unsigned *)(RTC_BASE + 0x0018)
#define RTC_WKUSEC       (volatile unsigned *)(RTC_BASE + 0x0020)
#define RTC_WKUMIN       (volatile unsigned *)(RTC_BASE + 0x0024)
#define RTC_WKUHOUR      (volatile unsigned *)(RTC_BASE + 0x0028)
#define RTC_WKUCNT       (volatile unsigned *)(RTC_BASE + 0x002C)
#define RTC_CAL          (volatile unsigned *)(RTC_BASE + 0x0030)
#define RTC_DIV          (volatile unsigned *)(RTC_BASE + 0x0034)
#define RTC_CTL          (volatile unsigned *)(RTC_BASE + 0x0038)
//#define RTC_ITV          (volatile unsigned *)(RTC_BASE + 0x003C)
//#define RTC_SITV         (volatile unsigned *)(RTC_BASE + 0x0040)
#define RTC_PWD          (volatile unsigned *)(RTC_BASE + 0x0044)
#define RTC_CE           (volatile unsigned *)(RTC_BASE + 0x0048)
#define RTC_LOAD         (volatile unsigned *)(RTC_BASE + 0x004C)
#define RTC_INTSTS       (volatile unsigned *)(RTC_BASE + 0x0050)
#define RTC_INTEN        (volatile unsigned *)(RTC_BASE + 0x0054)
#define RTC_PSCA         (volatile unsigned *)(RTC_BASE + 0x0058)
#define RTC_ACCTRL       (volatile unsigned *)(RTC_BASE + 0x0080)
#define RTC_ACTI         (volatile unsigned *)(RTC_BASE + 0x0084)
#define RTC_ACF200       (volatile unsigned *)(RTC_BASE + 0x0088)
#define RTC_ACADCW       (volatile unsigned *)(RTC_BASE + 0x008C)
#define RTC_ACP0         (volatile unsigned *)(RTC_BASE + 0x0090)
#define RTC_ACP1         (volatile unsigned *)(RTC_BASE + 0x0094)
#define RTC_ACP2         (volatile unsigned *)(RTC_BASE + 0x0098)
#define RTC_ACP3         (volatile unsigned *)(RTC_BASE + 0x009C)
#define RTC_ACP4         (volatile unsigned *)(RTC_BASE + 0x00A0)
#define RTC_ACP5         (volatile unsigned *)(RTC_BASE + 0x00A4)
#define RTC_ACP6         (volatile unsigned *)(RTC_BASE + 0x00A8)
#define RTC_ACP7         (volatile unsigned *)(RTC_BASE + 0x00AC)
#define RTC_ACK1         (volatile unsigned *)(RTC_BASE + 0x00B0)
#define RTC_ACK2         (volatile unsigned *)(RTC_BASE + 0x00B4)
#define RTC_ACK3         (volatile unsigned *)(RTC_BASE + 0x00B8)
#define RTC_ACK4         (volatile unsigned *)(RTC_BASE + 0x00BC)
#define RTC_ACK5         (volatile unsigned *)(RTC_BASE + 0x00C0)
#define RTC_ACTEMP       (volatile unsigned *)(RTC_BASE + 0x00C4)
#define RTC_ACPPM        (volatile unsigned *)(RTC_BASE + 0x00C8)
#define RTC_ACADCR       (volatile unsigned *)(RTC_BASE + 0x00CC)
#define RTC_ACOP0        (volatile unsigned *)(RTC_BASE + 0x0400)
#define RTC_ACOP1        (volatile unsigned *)(RTC_BASE + 0x0404)
#define RTC_ACOP2        (volatile unsigned *)(RTC_BASE + 0x0408)
#define RTC_ACOP3        (volatile unsigned *)(RTC_BASE + 0x040C)
#define RTC_ACOP4        (volatile unsigned *)(RTC_BASE + 0x0410)
#define RTC_ACOP5        (volatile unsigned *)(RTC_BASE + 0x0414)
#define RTC_ACOP6        (volatile unsigned *)(RTC_BASE + 0x0418)
#define RTC_ACOP7        (volatile unsigned *)(RTC_BASE + 0x041C)
#define RTC_ACOP8        (volatile unsigned *)(RTC_BASE + 0x0420)
#define RTC_ACOP9        (volatile unsigned *)(RTC_BASE + 0x0424)
#define RTC_ACOP10       (volatile unsigned *)(RTC_BASE + 0x0428)
#define RTC_ACOP11       (volatile unsigned *)(RTC_BASE + 0x042C)
#define RTC_ACOP12       (volatile unsigned *)(RTC_BASE + 0x0430)
#define RTC_ACOP13       (volatile unsigned *)(RTC_BASE + 0x0434)
#define RTC_ACOP14       (volatile unsigned *)(RTC_BASE + 0x0438)
#define RTC_ACOP15       (volatile unsigned *)(RTC_BASE + 0x043C)
#define RTC_ACOP16       (volatile unsigned *)(RTC_BASE + 0x0440)
#define RTC_ACOP17       (volatile unsigned *)(RTC_BASE + 0x0444)
#define RTC_ACOP18       (volatile unsigned *)(RTC_BASE + 0x0448)
#define RTC_ACOP19       (volatile unsigned *)(RTC_BASE + 0x044C)
#define RTC_ACOP20       (volatile unsigned *)(RTC_BASE + 0x0450)
#define RTC_ACOP21       (volatile unsigned *)(RTC_BASE + 0x0454)
#define RTC_ACOP22       (volatile unsigned *)(RTC_BASE + 0x0458)
#define RTC_ACOP23       (volatile unsigned *)(RTC_BASE + 0x045C)
#define RTC_ACOP24       (volatile unsigned *)(RTC_BASE + 0x0460)
#define RTC_ACOP25       (volatile unsigned *)(RTC_BASE + 0x0464)
#define RTC_ACOP26       (volatile unsigned *)(RTC_BASE + 0x0468)
#define RTC_ACOP27       (volatile unsigned *)(RTC_BASE + 0x046C)
#define RTC_ACOP28       (volatile unsigned *)(RTC_BASE + 0x0470)
#define RTC_ACOP29       (volatile unsigned *)(RTC_BASE + 0x0474)
#define RTC_ACOP30       (volatile unsigned *)(RTC_BASE + 0x0478)
#define RTC_ACOP31       (volatile unsigned *)(RTC_BASE + 0x047C)
#define RTC_ACOP32       (volatile unsigned *)(RTC_BASE + 0x0480)
#define RTC_ACOP33       (volatile unsigned *)(RTC_BASE + 0x0484)
#define RTC_ACOP34       (volatile unsigned *)(RTC_BASE + 0x0488)
#define RTC_ACOP35       (volatile unsigned *)(RTC_BASE + 0x048C)
#define RTC_ACOP36       (volatile unsigned *)(RTC_BASE + 0x0490)
#define RTC_ACOP37       (volatile unsigned *)(RTC_BASE + 0x0494)
#define RTC_ACOP38       (volatile unsigned *)(RTC_BASE + 0x0498)
#define RTC_ACOP39       (volatile unsigned *)(RTC_BASE + 0x049C)
#define RTC_ACOP40       (volatile unsigned *)(RTC_BASE + 0x04A0)
#define RTC_ACOP41       (volatile unsigned *)(RTC_BASE + 0x04A4)
#define RTC_ACOP42       (volatile unsigned *)(RTC_BASE + 0x04A8)
#define RTC_ACOP43       (volatile unsigned *)(RTC_BASE + 0x04AC)
#define RTC_ACOP44       (volatile unsigned *)(RTC_BASE + 0x04B0)
#define RTC_ACOP45       (volatile unsigned *)(RTC_BASE + 0x04B4)
#define RTC_ACOP46       (volatile unsigned *)(RTC_BASE + 0x04B8)
#define RTC_ACOP47       (volatile unsigned *)(RTC_BASE + 0x04BC)
#define RTC_ACOP48       (volatile unsigned *)(RTC_BASE + 0x04C0)
#define RTC_ACOP49       (volatile unsigned *)(RTC_BASE + 0x04C4)
#define RTC_ACOP50       (volatile unsigned *)(RTC_BASE + 0x04C8)
#define RTC_ACOP51       (volatile unsigned *)(RTC_BASE + 0x04CC)
#define RTC_ACOP52       (volatile unsigned *)(RTC_BASE + 0x04D0)
#define RTC_ACOP53       (volatile unsigned *)(RTC_BASE + 0x04D4)
#define RTC_ACOP54       (volatile unsigned *)(RTC_BASE + 0x04D8)
#define RTC_ACOP55       (volatile unsigned *)(RTC_BASE + 0x04DC)
#define RTC_ACOP56       (volatile unsigned *)(RTC_BASE + 0x04E0)
#define RTC_ACOP57       (volatile unsigned *)(RTC_BASE + 0x04E4)
#define RTC_ACOP58       (volatile unsigned *)(RTC_BASE + 0x04E8)
#define RTC_ACOP59       (volatile unsigned *)(RTC_BASE + 0x04EC)
#define RTC_ACOP60       (volatile unsigned *)(RTC_BASE + 0x04F0)
#define RTC_ACOP61       (volatile unsigned *)(RTC_BASE + 0x04F4)
#define RTC_ACOP62       (volatile unsigned *)(RTC_BASE + 0x04F8)
#define RTC_ACOP63       (volatile unsigned *)(RTC_BASE + 0x04FC)

/******************************************************************************/
/*                                                                            */
/*                         Flash Controller (Flash)                           */
/*                                                                            */
/******************************************************************************/
#define FLASH_STA       (volatile unsigned *)     (FLASH_BASE + 0xFFFBC)
#define FLASH_INT       (volatile unsigned *)     (FLASH_BASE + 0x000FFFCC)
#define FLASH_CSSADDR   (volatile unsigned *)     (FLASH_BASE + 0x000FFFD0)
#define FLASH_CSEADDR   (volatile unsigned *)     (FLASH_BASE + 0x000FFFD4)
#define FLASH_CSVALUE   (volatile unsigned *)     (FLASH_BASE + 0x000FFFD8)
#define FLASH_CSCVALUE  (volatile unsigned *)     (FLASH_BASE + 0x000FFFDC)
#define FLASH_PASS      (volatile unsigned *)     (FLASH_BASE + 0x000FFFE0)
#define FLASH_CTRL      (volatile unsigned *)     (FLASH_BASE + 0x000FFFE4)
#define FLASH_PGADDR    (volatile unsigned *)     (FLASH_BASE + 0x000FFFE8)
#define FLASH_PGDATA    (volatile unsigned *)     (FLASH_BASE + 0x000FFFEC)
#define FLASH_PGB0      (volatile unsigned char*) (FLASH_BASE + 0x000FFFEC)
#define FLASH_PGB1      (volatile unsigned char*) (FLASH_BASE + 0x000FFFED)
#define FLASH_PGB2      (volatile unsigned char*) (FLASH_BASE + 0x000FFFEE)
#define FLASH_PGB3      (volatile unsigned char*) (FLASH_BASE + 0x000FFFEF)
#define FLASH_PGHW0     (volatile unsigned short*)(FLASH_BASE + 0x000FFFEC)
#define FLASH_PGHW1     (volatile unsigned short*)(FLASH_BASE + 0x000FFFEE)
#define FLASH_CONF      (volatile unsigned *)     (FLASH_BASE + 0x000FFFF0)
#define FLASH_SERASE    (volatile unsigned *)     (FLASH_BASE + 0x000FFFF4)
#define FLASH_CERASE    (volatile unsigned *)     (FLASH_BASE + 0x000FFFF8)
#define FLASH_DSTB      (volatile unsigned *)     (FLASH_BASE + 0x000FFFFC)

#define FLASH_NVRPASS   (volatile unsigned *)     (FLASH_BASE + 0xFFFC0)
#define FLASH_BDPASS    (volatile unsigned *)     (FLASH_BASE + 0xFFFC4)
#define FLASH_KEY       (volatile unsigned *)     (FLASH_BASE + 0xFFFC8)

/******************************************************************************/
/*                                                                            */
/*                          GPIO Controller (GPIO)                            */
/*                                                                            */
/******************************************************************************/
#define IOB_OEN         (volatile unsigned *)(GPIO_BASE + 0x00000020)
#define IOB_IE          (volatile unsigned *)(GPIO_BASE + 0x00000024)
#define IOB_DAT         (volatile unsigned *)(GPIO_BASE + 0x00000028)
#define IOB_ATT         (volatile unsigned *)(GPIO_BASE + 0x0000002C)
#define IOB_STS         (volatile unsigned *)(GPIO_BASE + 0x00000030)
#define IOC_OEN         (volatile unsigned *)(GPIO_BASE + 0x00000040)
#define IOC_IE          (volatile unsigned *)(GPIO_BASE + 0x00000044)
#define IOC_DAT         (volatile unsigned *)(GPIO_BASE + 0x00000048)
#define IOC_ATT         (volatile unsigned *)(GPIO_BASE + 0x0000004C)
#define IOC_STS         (volatile unsigned *)(GPIO_BASE + 0x00000050)
#define IOD_OEN         (volatile unsigned *)(GPIO_BASE + 0x00000060)
#define IOD_IE          (volatile unsigned *)(GPIO_BASE + 0x00000064)
#define IOD_DAT         (volatile unsigned *)(GPIO_BASE + 0x00000068)
#define IOD_ATT         (volatile unsigned *)(GPIO_BASE + 0x0000006C)
#define IOD_STS         (volatile unsigned *)(GPIO_BASE + 0x00000070)
#define IOE_OEN         (volatile unsigned *)(GPIO_BASE + 0x00000080)
#define IOE_IE          (volatile unsigned *)(GPIO_BASE + 0x00000084)
#define IOE_DAT         (volatile unsigned *)(GPIO_BASE + 0x00000088)
#define IOE_ATT         (volatile unsigned *)(GPIO_BASE + 0x0000008C)
#define IOE_STS         (volatile unsigned *)(GPIO_BASE + 0x00000090)
#define IOF_OEN         (volatile unsigned *)(GPIO_BASE + 0x000000A0)
#define IOF_IE          (volatile unsigned *)(GPIO_BASE + 0x000000A4)
#define IOF_DAT         (volatile unsigned *)(GPIO_BASE + 0x000000A8)
#define IOF_ATT         (volatile unsigned *)(GPIO_BASE + 0x000000AC)
#define IOF_STS         (volatile unsigned *)(GPIO_BASE + 0x000000B0)
#define IOB_SEL         (volatile unsigned *)(GPIO_BASE + 0x000000C0)
#define IOE_SEL         (volatile unsigned *)(GPIO_BASE + 0x000000CC)
#define IO_MISC         (volatile unsigned *)(GPIO_BASE + 0x000000E0)

/******************************************************************************/
/*                                                                            */
/*                           DMA Controller (DMA)                             */
/*                                                                            */
/******************************************************************************/
#define DMA_IE          (volatile unsigned *)(DMA_BASE + 0x0000)
#define DMA_STS         (volatile unsigned *)(DMA_BASE + 0x0004)
#define DMA_C0CTL       (volatile unsigned *)(DMA_BASE + 0x0010)
#define DMA_C0SRC       (volatile unsigned *)(DMA_BASE + 0x0014)
#define DMA_C0DST       (volatile unsigned *)(DMA_BASE + 0x0018)
#define DMA_C0LEN       (volatile unsigned *)(DMA_BASE + 0x001C)
#define DMA_C1CTL       (volatile unsigned *)(DMA_BASE + 0x0020)
#define DMA_C1SRC       (volatile unsigned *)(DMA_BASE + 0x0024)
#define DMA_C1DST       (volatile unsigned *)(DMA_BASE + 0x0028)
#define DMA_C1LEN       (volatile unsigned *)(DMA_BASE + 0x002C)
#define DMA_C2CTL       (volatile unsigned *)(DMA_BASE + 0x0030)
#define DMA_C2SRC       (volatile unsigned *)(DMA_BASE + 0x0034)
#define DMA_C2DST       (volatile unsigned *)(DMA_BASE + 0x0038)
#define DMA_C2LEN       (volatile unsigned *)(DMA_BASE + 0x003C)
#define DMA_C3CTL       (volatile unsigned *)(DMA_BASE + 0x0040)
#define DMA_C3SRC       (volatile unsigned *)(DMA_BASE + 0x0044)
#define DMA_C3DST       (volatile unsigned *)(DMA_BASE + 0x0048)
#define DMA_C3LEN       (volatile unsigned *)(DMA_BASE + 0x004C)
#define DMA_AESCTL      (volatile unsigned *)(DMA_BASE + 0x0050)
#define DMA_AESKEY0     (volatile unsigned *)(DMA_BASE + 0x0060)
#define DMA_AESKEY1     (volatile unsigned *)(DMA_BASE + 0x0064)
#define DMA_AESKEY2     (volatile unsigned *)(DMA_BASE + 0x0068)
#define DMA_AESKEY3     (volatile unsigned *)(DMA_BASE + 0x006C)
#define DMA_AESKEY4     (volatile unsigned *)(DMA_BASE + 0x0070)
#define DMA_AESKEY5     (volatile unsigned *)(DMA_BASE + 0x0074)
#define DMA_AESKEY6     (volatile unsigned *)(DMA_BASE + 0x0078)
#define DMA_AESKEY7     (volatile unsigned *)(DMA_BASE + 0x007C)

/******************************************************************************/
/*                                                                            */
/*                          UART Controller (UART)                            */
/*                                                                            */
/******************************************************************************/
#define UART0_DATA      (volatile unsigned *)(UART0_BASE + 0x0000)
#define UART0_STATE     (volatile unsigned *)(UART0_BASE + 0x0004)
#define UART0_CTRL      (volatile unsigned *)(UART0_BASE + 0x0008)
#define UART0_INTSTS    (volatile unsigned *)(UART0_BASE + 0x000C)
#define UART0_BAUDDIV   (volatile unsigned *)(UART0_BASE + 0x0010)
#define UART0_CTRL2     (volatile unsigned *)(UART0_BASE + 0x0014)
#define UART1_DATA      (volatile unsigned *)(UART1_BASE + 0x0000)
#define UART1_STATE     (volatile unsigned *)(UART1_BASE + 0x0004)
#define UART1_CTRL      (volatile unsigned *)(UART1_BASE + 0x0008)
#define UART1_INTSTS    (volatile unsigned *)(UART1_BASE + 0x000C)
#define UART1_BAUDDIV   (volatile unsigned *)(UART1_BASE + 0x0010)
#define UART1_CTRL2     (volatile unsigned *)(UART1_BASE + 0x0014)
#define UART2_DATA      (volatile unsigned *)(UART2_BASE + 0x0000)
#define UART2_STATE     (volatile unsigned *)(UART2_BASE + 0x0004)
#define UART2_CTRL      (volatile unsigned *)(UART2_BASE + 0x0008)
#define UART2_INTSTS    (volatile unsigned *)(UART2_BASE + 0x000C)
#define UART2_BAUDDIV   (volatile unsigned *)(UART2_BASE + 0x0010)
#define UART2_CTRL2     (volatile unsigned *)(UART2_BASE + 0x0014)
#define UART3_DATA      (volatile unsigned *)(UART3_BASE + 0x0000)
#define UART3_STATE     (volatile unsigned *)(UART3_BASE + 0x0004)
#define UART3_CTRL      (volatile unsigned *)(UART3_BASE + 0x0008)
#define UART3_INTSTS    (volatile unsigned *)(UART3_BASE + 0x000C)
#define UART3_BAUDDIV   (volatile unsigned *)(UART3_BASE + 0x0010)
#define UART3_CTRL2     (volatile unsigned *)(UART3_BASE + 0x0014)
#define UART4_DATA      (volatile unsigned *)(UART4_BASE + 0x0000)
#define UART4_STATE     (volatile unsigned *)(UART4_BASE + 0x0004)
#define UART4_CTRL      (volatile unsigned *)(UART4_BASE + 0x0008)
#define UART4_INTSTS    (volatile unsigned *)(UART4_BASE + 0x000C)
#define UART4_BAUDDIV   (volatile unsigned *)(UART4_BASE + 0x0010)
#define UART4_CTRL2     (volatile unsigned *)(UART4_BASE + 0x0014)
#define UART5_DATA      (volatile unsigned *)(UART5_BASE + 0x0000)
#define UART5_STATE     (volatile unsigned *)(UART5_BASE + 0x0004)
#define UART5_CTRL      (volatile unsigned *)(UART5_BASE + 0x0008)
#define UART5_INTSTS    (volatile unsigned *)(UART5_BASE + 0x000C)
#define UART5_BAUDDIV   (volatile unsigned *)(UART5_BASE + 0x0010)
#define UART5_CTRL2     (volatile unsigned *)(UART5_BASE + 0x0014)

/******************************************************************************/
/*                                                                            */
/*                        UART 32K Controller (U32K)                          */
/*                                                                            */
/******************************************************************************/
#define U32K0_CTRL0      (volatile unsigned *)(U32K0_BASE + 0x0000)
#define U32K0_CTRL1      (volatile unsigned *)(U32K0_BASE + 0x0004)
#define U32K0_PHASE      (volatile unsigned *)(U32K0_BASE + 0x0008)
#define U32K0_DATA       (volatile unsigned *)(U32K0_BASE + 0x000C)
#define U32K0_STS        (volatile unsigned *)(U32K0_BASE + 0x0010)

#define U32K1_CTRL0      (volatile unsigned *)(U32K1_BASE + 0x0000)
#define U32K1_CTRL1      (volatile unsigned *)(U32K1_BASE + 0x0004)
#define U32K1_PHASE      (volatile unsigned *)(U32K1_BASE + 0x0008)
#define U32K1_DATA       (volatile unsigned *)(U32K1_BASE + 0x000C)
#define U32K1_STS        (volatile unsigned *)(U32K1_BASE + 0x0010)

/******************************************************************************/
/*                                                                            */
/*                       ISO7816 Controller (ISO7816)                         */
/*                                                                            */
/******************************************************************************/
#define ISO78160_BAUDDIVL  (volatile unsigned *)(ISO78160_BASE + 0x0004)
#define ISO78160_BAUDDIVH  (volatile unsigned *)(ISO78160_BASE + 0x0008)
#define ISO78160_DATA      (volatile unsigned *)(ISO78160_BASE + 0x000C)
#define ISO78160_INFO      (volatile unsigned *)(ISO78160_BASE + 0x0010)
#define ISO78160_CFG       (volatile unsigned *)(ISO78160_BASE + 0x0014)
#define ISO78160_CLK       (volatile unsigned *)(ISO78160_BASE + 0x0018)
#define ISO78161_BAUDDIVL  (volatile unsigned *)(ISO78161_BASE + 0x0004)
#define ISO78161_BAUDDIVH  (volatile unsigned *)(ISO78161_BASE + 0x0008)
#define ISO78161_DATA      (volatile unsigned *)(ISO78161_BASE + 0x000C)
#define ISO78161_INFO      (volatile unsigned *)(ISO78161_BASE + 0x0010)
#define ISO78161_CFG       (volatile unsigned *)(ISO78161_BASE + 0x0014)
#define ISO78161_CLK       (volatile unsigned *)(ISO78161_BASE + 0x0018)

/******************************************************************************/
/*                                                                            */
/*                         Timer Controller (Timer)                           */
/*                                                                            */
/******************************************************************************/
#define TMR0_CTRL       (volatile unsigned *)(TMR0_BASE + 0x0000)
#define TMR0_VALUE      (volatile unsigned *)(TMR0_BASE + 0x0004)
#define TMR0_RELOAD     (volatile unsigned *)(TMR0_BASE + 0x0008)
#define TMR0_INT        (volatile unsigned *)(TMR0_BASE + 0x000C)
#define TMR1_CTRL       (volatile unsigned *)(TMR1_BASE + 0x0000)
#define TMR1_VALUE      (volatile unsigned *)(TMR1_BASE + 0x0004)
#define TMR1_RELOAD     (volatile unsigned *)(TMR1_BASE + 0x0008)
#define TMR1_INT        (volatile unsigned *)(TMR1_BASE + 0x000C)
#define TMR2_CTRL       (volatile unsigned *)(TMR2_BASE + 0x0000)
#define TMR2_VALUE      (volatile unsigned *)(TMR2_BASE + 0x0004)
#define TMR2_RELOAD     (volatile unsigned *)(TMR2_BASE + 0x0008)
#define TMR2_INT        (volatile unsigned *)(TMR2_BASE + 0x000C)
#define TMR3_CTRL       (volatile unsigned *)(TMR3_BASE + 0x0000)
#define TMR3_VALUE      (volatile unsigned *)(TMR3_BASE + 0x0004)
#define TMR3_RELOAD     (volatile unsigned *)(TMR3_BASE + 0x0008)
#define TMR3_INT        (volatile unsigned *)(TMR3_BASE + 0x000C)

/******************************************************************************/
/*                                                                            */
/*                           PWM Controller (PWM)                             */
/*                                                                            */
/******************************************************************************/
#define PWM0_CTL        (volatile unsigned *)(PWM0_BASE + 0x0000)
#define PWM0_TAR        (volatile unsigned *)(PWM0_BASE + 0x0004)
#define PWM0_CCTL0      (volatile unsigned *)(PWM0_BASE + 0x0008)
#define PWM0_CCTL1      (volatile unsigned *)(PWM0_BASE + 0x000C)
#define PWM0_CCTL2      (volatile unsigned *)(PWM0_BASE + 0x0010)
#define PWM0_CCR0       (volatile unsigned *)(PWM0_BASE + 0x0014)
#define PWM0_CCR1       (volatile unsigned *)(PWM0_BASE + 0x0018)
#define PWM0_CCR2       (volatile unsigned *)(PWM0_BASE + 0x001C)
#define PWM1_CTL        (volatile unsigned *)(PWM1_BASE + 0x0000)
#define PWM1_TAR        (volatile unsigned *)(PWM1_BASE + 0x0004)
#define PWM1_CCTL0      (volatile unsigned *)(PWM1_BASE + 0x0008)
#define PWM1_CCTL1      (volatile unsigned *)(PWM1_BASE + 0x000C)
#define PWM1_CCTL2      (volatile unsigned *)(PWM1_BASE + 0x0010)
#define PWM1_CCR0       (volatile unsigned *)(PWM1_BASE + 0x0014)
#define PWM1_CCR1       (volatile unsigned *)(PWM1_BASE + 0x0018)
#define PWM1_CCR2       (volatile unsigned *)(PWM1_BASE + 0x001C)
#define PWM2_CTL        (volatile unsigned *)(PWM2_BASE + 0x0000)
#define PWM2_TAR        (volatile unsigned *)(PWM2_BASE + 0x0004)
#define PWM2_CCTL0      (volatile unsigned *)(PWM2_BASE + 0x0008)
#define PWM2_CCTL1      (volatile unsigned *)(PWM2_BASE + 0x000C)
#define PWM2_CCTL2      (volatile unsigned *)(PWM2_BASE + 0x0010)
#define PWM2_CCR0       (volatile unsigned *)(PWM2_BASE + 0x0014)
#define PWM2_CCR1       (volatile unsigned *)(PWM2_BASE + 0x0018)
#define PWM2_CCR2       (volatile unsigned *)(PWM2_BASE + 0x001C)
#define PWM3_CTL        (volatile unsigned *)(PWM3_BASE + 0x0000)
#define PWM3_TAR        (volatile unsigned *)(PWM3_BASE + 0x0004)
#define PWM3_CCTL0      (volatile unsigned *)(PWM3_BASE + 0x0008)
#define PWM3_CCTL1      (volatile unsigned *)(PWM3_BASE + 0x000C)
#define PWM3_CCTL2      (volatile unsigned *)(PWM3_BASE + 0x0010)
#define PWM3_CCR0       (volatile unsigned *)(PWM3_BASE + 0x0014)
#define PWM3_CCR1       (volatile unsigned *)(PWM3_BASE + 0x0018)
#define PWM3_CCR2       (volatile unsigned *)(PWM3_BASE + 0x001C)
#define PWM_O_SEL       (volatile unsigned *)(PWM0_BASE + 0x00F0)
//#define PWM_I_SEL01     (volatile unsigned *)(PWM0_BASE + 0x00F4)
//#define PWM_I_SEL23     (volatile unsigned *)(PWM0_BASE + 0x00F8)

/******************************************************************************/
/*                                                                            */
/*                           LCD Controller (LCD)                             */
/*                                                                            */
/******************************************************************************/
#define LCD_FB00        (volatile unsigned *)(LCD_BASE + 0x0000)
#define LCD_FB01        (volatile unsigned *)(LCD_BASE + 0x0004)
#define LCD_FB02        (volatile unsigned *)(LCD_BASE + 0x0008)
#define LCD_FB03        (volatile unsigned *)(LCD_BASE + 0x000C)
#define LCD_FB04        (volatile unsigned *)(LCD_BASE + 0x0010)
#define LCD_FB05        (volatile unsigned *)(LCD_BASE + 0x0014)
#define LCD_FB06        (volatile unsigned *)(LCD_BASE + 0x0018)
#define LCD_FB07        (volatile unsigned *)(LCD_BASE + 0x001C)
#define LCD_FB08        (volatile unsigned *)(LCD_BASE + 0x0020)
#define LCD_FB09        (volatile unsigned *)(LCD_BASE + 0x0024)
#define LCD_FB0A        (volatile unsigned *)(LCD_BASE + 0x0028)
#define LCD_FB0B        (volatile unsigned *)(LCD_BASE + 0x002C)
#define LCD_FB0C        (volatile unsigned *)(LCD_BASE + 0x0030)
#define LCD_FB0D        (volatile unsigned *)(LCD_BASE + 0x0034)
#define LCD_FB0E        (volatile unsigned *)(LCD_BASE + 0x0038)
#define LCD_FB0F        (volatile unsigned *)(LCD_BASE + 0x003C)
#define LCD_FB10        (volatile unsigned *)(LCD_BASE + 0x0040)
#define LCD_FB11        (volatile unsigned *)(LCD_BASE + 0x0044)
#define LCD_FB12        (volatile unsigned *)(LCD_BASE + 0x0048)
#define LCD_FB13        (volatile unsigned *)(LCD_BASE + 0x004C)
#define LCD_FB14        (volatile unsigned *)(LCD_BASE + 0x0050)
#define LCD_FB15        (volatile unsigned *)(LCD_BASE + 0x0054)
#define LCD_FB16        (volatile unsigned *)(LCD_BASE + 0x0058)
#define LCD_FB17        (volatile unsigned *)(LCD_BASE + 0x005C)
#define LCD_FB18        (volatile unsigned *)(LCD_BASE + 0x0060)
#define LCD_FB19        (volatile unsigned *)(LCD_BASE + 0x0064)
#define LCD_FB1A        (volatile unsigned *)(LCD_BASE + 0x0068)
#define LCD_FB1B        (volatile unsigned *)(LCD_BASE + 0x006C)
#define LCD_FB1C        (volatile unsigned *)(LCD_BASE + 0x0070)
#define LCD_FB1D        (volatile unsigned *)(LCD_BASE + 0x0074)
#define LCD_FB1E        (volatile unsigned *)(LCD_BASE + 0x0078)
#define LCD_FB1F        (volatile unsigned *)(LCD_BASE + 0x007C)
#define LCD_FB20        (volatile unsigned *)(LCD_BASE + 0x0080)
#define LCD_FB21        (volatile unsigned *)(LCD_BASE + 0x0084)
#define LCD_FB22        (volatile unsigned *)(LCD_BASE + 0x0088)
#define LCD_FB23        (volatile unsigned *)(LCD_BASE + 0x008C)
#define LCD_FB24        (volatile unsigned *)(LCD_BASE + 0x0090)
#define LCD_FB25        (volatile unsigned *)(LCD_BASE + 0x0094)
#define LCD_FB26        (volatile unsigned *)(LCD_BASE + 0x0098)
#define LCD_FB27        (volatile unsigned *)(LCD_BASE + 0x009C)
#define LCD_CTRL        (volatile unsigned *)(LCD_BASE + 0x0100)
#define LCD_CTRL2       (volatile unsigned *)(LCD_BASE + 0x0104)
#define LCD_SEGCTRL0    (volatile unsigned *)(LCD_BASE + 0x0108)
#define LCD_SEGCTRL1    (volatile unsigned *)(LCD_BASE + 0x010C)
#define LCD_SEGCTRL2    (volatile unsigned *)(LCD_BASE + 0x0110)

/******************************************************************************/
/*                                                                            */
/*                           SPI Controller (SPI)                             */
/*                                                                            */
/******************************************************************************/
#define SPI1_CTRL       (volatile unsigned *)(SPI1_BASE + 0x0000)
#define SPI1_TXSTS      (volatile unsigned *)(SPI1_BASE + 0x0004)
#define SPI1_TXDATA     (volatile unsigned *)(SPI1_BASE + 0x0008)
#define SPI1_RXSTS      (volatile unsigned *)(SPI1_BASE + 0x000C)
#define SPI1_RXDATA     (volatile unsigned *)(SPI1_BASE + 0x0010)
#define SPI1_MISC       (volatile unsigned *)(SPI1_BASE + 0x0014)
#define SPI2_CTRL       (volatile unsigned *)(SPI2_BASE + 0x0000)
#define SPI2_TXSTS      (volatile unsigned *)(SPI2_BASE + 0x0004)
#define SPI2_TXDATA     (volatile unsigned *)(SPI2_BASE + 0x0008)
#define SPI2_RXSTS      (volatile unsigned *)(SPI2_BASE + 0x000C)
#define SPI2_RXDATA     (volatile unsigned *)(SPI2_BASE + 0x0010)
#define SPI2_MISC       (volatile unsigned *)(SPI2_BASE + 0x0014)

/******************************************************************************/
/*                                                                            */
/*                           I2C Controller (I2C)                             */
/*                                                                            */
/******************************************************************************/
#define I2C_DATA        (volatile unsigned *)(I2C_BASE + 0x0000)
#define I2C_ADDR        (volatile unsigned *)(I2C_BASE + 0x0004)
#define I2C_CTRL        (volatile unsigned *)(I2C_BASE + 0x0008)
#define I2C_STS         (volatile unsigned *)(I2C_BASE + 0x000C)
#define I2C_SMBSEL      (volatile unsigned *)(I2C_BASE + 0x0010)
#define I2C_SMBDST      (volatile unsigned *)(I2C_BASE + 0x0014)
#define I2C_CTRL2       (volatile unsigned *)(I2C_BASE + 0x0018)

/******************************************************************************/
/*                                                                            */
/*                          MISC Controller (MISC)                            */
/*                                                                            */
/******************************************************************************/
#define MISC_SRAMINT    (volatile unsigned *)(MISC_BASE + 0x0000)
#define MISC_SRAMINIT   (volatile unsigned *)(MISC_BASE + 0x0004)
#define MISC_PARERR     (volatile unsigned *)(MISC_BASE + 0x0008)
#define MISC_IREN       (volatile unsigned *)(MISC_BASE + 0x000C)
#define MISC_DUTYL      (volatile unsigned *)(MISC_BASE + 0x0010)
#define MISC_DUTYH      (volatile unsigned *)(MISC_BASE + 0x0014)
#define MISC_IRQLAT     (volatile unsigned *)(MISC_BASE + 0x0018)

#define MISC2_FLASHWC   (volatile unsigned *)(MISC2_BASE + 0x0000)
#define MISC2_CLKSEL    (volatile unsigned *)(MISC2_BASE + 0x0004)
#define MISC2_CLKDIVH   (volatile unsigned *)(MISC2_BASE + 0x0008)
#define MISC2_CLKDIVP   (volatile unsigned *)(MISC2_BASE + 0x000C)
#define MISC2_HCLKEN    (volatile unsigned *)(MISC2_BASE + 0x0010)
#define MISC2_PCLKEN    (volatile unsigned *)(MISC2_BASE + 0x0014)

/******************************************************************************/
/*                                                                            */
/*                         CRYPT Controller (CRYPT)                           */
/*                                                                            */
/******************************************************************************/
#define CRYPT_CTRL      (volatile unsigned *)(CRYPT_BASE + 0x0000)
#define CRYPT_PTRA      (volatile unsigned *)(CRYPT_BASE + 0x0004)
#define CRYPT_PTRB      (volatile unsigned *)(CRYPT_BASE + 0x0008)
#define CRYPT_PTRO      (volatile unsigned *)(CRYPT_BASE + 0x000C)
#define CRYPT_CARRY     (volatile unsigned *)(CRYPT_BASE + 0x0010)

/** @addtogroup Exported_macro
  * @{
  */

/****************************** PMU Instances *********************************/
#define IS_PMU_ALL_INSTANCE(INSTANCE) ((INSTANCE) == PMU)

/****************************** PMU_RETRAM Instances **************************/
#define IS_PMU_RETRAM_ALL_INSTANCE(INSTANCE) ((INSTANCE) == PMU_RETRAM)

/****************************** ANA Instances *********************************/
#define IS_ANA_ALL_INSTANCE(INSTANCE) ((INSTANCE) == ANA)

/****************************** RTC Instances *********************************/
#define IS_RTC_ALL_INSTANCE(INSTANCE) ((INSTANCE) == RTC)

/****************************** FLASH Instances *******************************/
#define IS_FLASH_ALL_INSTANCE(INSTANCE) ((INSTANCE) == FLASH)

/****************************** GPIO Instances ********************************/
#define IS_GPIO_ALL_INSTANCE(INSTANCE)  (((INSTANCE) == GPIOB) || \
                                         ((INSTANCE) == GPIOC) || \
                                         ((INSTANCE) == GPIOD) || \
                                         ((INSTANCE) == GPIOE) || \
																				 ((INSTANCE) == GPIOF))

#define IS_PMUIO_ALL_INSTANCE(INSTANCE)  ((INSTANCE) == GPIOA)

#define IS_GPIOAF_ALL_INSTANCE(INSTANCE)  (((INSTANCE) == GPIOB) || \
                                           ((INSTANCE) == GPIOE))

/****************************** DMA Instances *********************************/
#define IS_DMA_ALL_INSTANCE(INSTANCE) ((INSTANCE) == DMA)

/****************************** UART Instances ********************************/
#define IS_UART_ALL_INSTANCE(INSTANCE) (((INSTANCE) == UART0) || \
                                        ((INSTANCE) == UART1) || \
                                        ((INSTANCE) == UART2) || \
                                        ((INSTANCE) == UART3) || \
                                        ((INSTANCE) == UART4) || \
                                        ((INSTANCE) == UART5))

/****************************** U32K Instances ********************************/
#define IS_U32K_ALL_INSTANCE(INSTANCE) (((INSTANCE) == U32K0) || \
                                        ((INSTANCE) == U32K1))

/****************************** ISO7816 Instances *****************************/
#define IS_ISO7816_ALL_INSTANCE(INSTANCE) (((INSTANCE) == ISO78160) || \
                                           ((INSTANCE) == ISO78161))

/****************************** TMR Instances *********************************/
#define IS_TMR_ALL_INSTANCE(INSTANCE) (((INSTANCE) == TMR0) || \
                                       ((INSTANCE) == TMR1) || \
                                       ((INSTANCE) == TMR2) || \
                                       ((INSTANCE) == TMR3))

/****************************** PWM Instances *********************************/
#define IS_PWM_ALL_INSTANCE(INSTANCE) (((INSTANCE) == PWM0) || \
                                       ((INSTANCE) == PWM1) || \
                                       ((INSTANCE) == PWM2) || \
                                       ((INSTANCE) == PWM3))

#define IS_PWMMUX_ALL_INSTANCE(INSTANCE) ((INSTANCE) == PWMMUX)

/****************************** LCD Instances *********************************/
#define IS_LCD_ALL_INSTANCE(INSTANCE) ((INSTANCE) == LCD)

/****************************** SPI Instances *********************************/
#define IS_SPI_ALL_INSTANCE(INSTANCE) (((INSTANCE) == SPI1) || \
                                       ((INSTANCE) == SPI2))

/****************************** I2C Instances *********************************/
#define IS_I2C_ALL_INSTANCE(INSTANCE) ((INSTANCE) == I2C)

/****************************** MISC Instances ********************************/
#define IS_MISC_ALL_INSTANCE(INSTANCE) ((INSTANCE) == MISC)

#define IS_MISC2_ALL_INSTANCE(INSTANCE) ((INSTANCE) == MISC2)

/****************************** CRYPT Instances *******************************/
#define IS_CRYPT_ALL_INSTANCE(INSTANCE) ((INSTANCE) == CRYPT)



#ifdef USE_TARGET_DRIVER
    #include "lib_conf.h"
#endif

#ifdef __cplusplus
}
#endif

#endif 

/*********************************** END OF FILE ******************************/
