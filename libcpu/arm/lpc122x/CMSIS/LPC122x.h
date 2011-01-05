/****************************************************************************
 *   $Id:: LPC122x.h 5637 2010-11-18 00:02:05Z nxp28433                     $
 *   Project: NXP LPC122x software example  
 *
 *   Description:
 *     CMSIS Cortex-M0 Core Peripheral Access Layer Header File for 
 *     NXP LPC122x Device Series 
 *
 ****************************************************************************
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors
 * reserves the right to make changes in the software without
 * notification. NXP Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
****************************************************************************/
#ifndef __LPC122x_H__
#define __LPC122x_H__

#ifdef __cplusplus
 extern "C" {
#endif 

/** @addtogroup LPC122x_Definitions LPC122x Definitions
  This file defines all structures and symbols for LPC122x:
    - Registers and bitfields
    - peripheral base address
    - peripheral ID
    - PIO definitions
  @{
*/


/******************************************************************************/
/*                Processor and Core Peripherals                              */
/******************************************************************************/
/** @addtogroup LPC122x_CMSIS LPC122x CMSIS Definitions
  Configuration of the Cortex-M0 Processor and Core Peripherals
  @{
*/

/*
 * ==========================================================================
 * ---------- Interrupt Number Definition -----------------------------------
 * ==========================================================================
 */

typedef enum IRQn
{
/******  Cortex-M0 Processor Exceptions Numbers ***************************************************/
  NonMaskableInt_IRQn           = -14,      /*!< 2 Non Maskable Interrupt                         */
  MemoryManagement_IRQn         = -12,      /*!< 4 Cortex-M0 Memory Management Interrupt          */
  BusFault_IRQn                 = -11,      /*!< 5 Cortex-M0 Bus Fault Interrupt                  */
  UsageFault_IRQn               = -10,      /*!< 6 Cortex-M0 Usage Fault Interrupt                */
  SVCall_IRQn                   = -5,       /*!< 11 Cortex-M0 SV Call Interrupt                   */
  DebugMonitor_IRQn             = -4,       /*!< 12 Cortex-M0 Debug Monitor Interrupt             */
  PendSV_IRQn                   = -2,       /*!< 14 Cortex-M0 Pend SV Interrupt                   */
  SysTick_IRQn                  = -1,       /*!< 15 Cortex-M0 System Tick Interrupt               */

/******  LPC122x Specific Interrupt Numbers *******************************************************/
  WAKEUP0_IRQn                  = 0,        /*!< The I/O pins can be used as wakeup source.       */
  WAKEUP1_IRQn                  = 1,
  WAKEUP2_IRQn                  = 2,
  WAKEUP3_IRQn                  = 3,
  WAKEUP4_IRQn                  = 4,   
  WAKEUP5_IRQn                  = 5,        
  WAKEUP6_IRQn                  = 6,        
  WAKEUP7_IRQn                  = 7,        
  WAKEUP8_IRQn                  = 8,        
  WAKEUP9_IRQn                  = 9,        
  WAKEUP10_IRQn                 = 10,       
  WAKEUP11_IRQn                 = 11,       /*!< 0 through 11 are WAKEUP interrupts               */
  I2C_IRQn                      = 12,       /*!< I2C Interrupt                                    */
  TIMER_16_0_IRQn               = 13,       /*!< 16-bit Timer0 Interrupt                          */
  TIMER_16_1_IRQn               = 14,       /*!< 16-bit Timer1 Interrupt                          */
  TIMER_32_0_IRQn               = 15,       /*!< 32-bit Timer0 Interrupt                          */
  TIMER_32_1_IRQn               = 16,       /*!< 32-bit Timer1 Interrupt                          */
  SSP_IRQn                      = 17,       /*!< SSP Interrupt                                    */
  UART0_IRQn                    = 18,       /*!< UART0 Interrupt                                  */
  UART1_IRQn                    = 19,       /*!< UART1 Interrupt                                  */
  CMP_IRQn                      = 20,       /*!< Comparator Interrupt                             */
  ADC_IRQn                      = 21,       /*!< A/D Converter Interrupt                          */
  WDT_IRQn                      = 22,       /*!< Watchdog timer Interrupt                         */  
  BOD_IRQn                      = 23,       /*!< Brown Out Detect(BOD) Interrupt                  */
  FLASH_IRQn                    = 24,       /*!< Flash Interrupt                                  */
  EINT0_IRQn                    = 25,       /*!< External Interrupt 0 Interrupt                   */
  EINT1_IRQn                    = 26,       /*!< External Interrupt 1 Interrupt                   */
  EINT2_IRQn                    = 27,       /*!< External Interrupt 2 Interrupt                   */
  PMU_IRQn                      = 28,       /*!< PMU Interrupt                                    */
  DMA_IRQn                      = 29,       /*!< DMA Interrupt                                    */
  RTC_IRQn                      = 30,       /*!< RTC Interrupt                                    */
  EDM_IRQn                      = 31,       /*!< EDT Interrupt                                    */
} IRQn_Type;


/*
 * ==========================================================================
 * ----------- Processor and Core Peripheral Section ------------------------
 * ==========================================================================
 */

/* Configuration of the Cortex-M3 Processor and Core Peripherals */
#define __MPU_PRESENT             1         /*!< MPU present or not                               */
#define __NVIC_PRIO_BITS          2         /*!< Number of Bits used for Priority Levels          */
#define __Vendor_SysTickConfig    0         /*!< Set to 1 if different SysTick Config is used     */

/*@}*/ /* end of group LPC122x_CMSIS */


#include "core_cm0.h"                       /* Cortex-M0 processor and core peripherals           */
#include "system_LPC122x.h"                 /* System Header                                      */


/******************************************************************************/
/*                Device Specific Peripheral Registers structures             */
/******************************************************************************/

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

/*------------- System Control (SYSCON) --------------------------------------*/
/** @addtogroup LPC122x_SYSCON LPC122x System Control Block 
  @{
*/
typedef struct
{
  __IO uint32_t SYSMEMREMAP;     /* Sys mem. Remap, Offset 0x0   */
  __IO uint32_t PRESETCTRL;
  __IO uint32_t SYSPLLCTRL;      /* Sys PLL control              */
  __IO uint32_t SYSPLLSTAT;
       uint32_t RESERVED0[4];

  __IO uint32_t SYSOSCCTRL;      /* Offset 0x20 */
  __IO uint32_t WDTOSCCTRL;
  __IO uint32_t IRCCTRL;
       uint32_t RESERVED0b;
  __IO uint32_t SYSRESSTAT;      /* Offset 0x30 */
       uint32_t RESERVED1[3];
  __IO uint32_t SYSPLLCLKSEL;    /* Offset 0x40 */	
  __IO uint32_t SYSPLLCLKUEN;
       uint32_t RESERVED2[10];

  __IO uint32_t MAINCLKSEL;      /* Offset 0x70 */
  __IO uint32_t MAINCLKUEN;
  __IO uint32_t SYSAHBCLKDIV;
       uint32_t RESERVED3[1];

  __IO uint32_t SYSAHBCLKCTRL;   /* Offset 0x80 */
       uint32_t RESERVED4[4];
  __IO uint32_t SSPCLKDIV;                 
  __IO uint32_t UART0CLKDIV;
  __IO uint32_t UART1CLKDIV;
  __IO uint32_t RTCCLKDIV;
       uint32_t RESERVED5[2];
  __IO uint32_t TRACECLKDIV;

  __IO uint32_t SYSTICKCLKDIV;   /* Offset 0xB0 */
  __IO uint32_t I2CCLKDIV;           
       uint32_t RESERVED6[10];

  __IO uint32_t CLKOUTCLKSEL;    /* Offset 0xE0 */
  __IO uint32_t CLKOUTUEN;
  __IO uint32_t CLKOUTDIV;              
       uint32_t RESERVED7[5];
  
  __IO uint32_t PIOPORCAP0;      /* Offset 0x100 */           
  __IO uint32_t PIOPORCAP1;
       uint32_t RESERVED8[11];
  __IO uint32_t FILTERCLKCFG6;
  __IO uint32_t FILTERCLKCFG5;
  __IO uint32_t FILTERCLKCFG4;
  __IO uint32_t FILTERCLKCFG3;   /* Offset 0x140 */
  __IO uint32_t FILTERCLKCFG2;
  __IO uint32_t FILTERCLKCFG1;
  __IO uint32_t FILTERCLKCFG0;	  	  	            
  __IO uint32_t BODCTRL;         /* Offset 0x150 */
       uint32_t RESERVED9[1];
  __IO uint32_t SYSTCKCAL;
 	   uint32_t RESERVED10[5];
  __IO uint32_t INT_IRQ_LATENCY; /* Offset 0x170 */
  __IO uint32_t INTNMI;
       uint32_t RESERVED11[34];          

  __IO uint32_t STARTAPRP0;      /* Offset 0x200 */     
  __IO uint32_t STARTERP0;             
  __IO uint32_t STARTRSRP0CLR;
  __IO uint32_t STARTSRP0;
  __IO uint32_t STARTAPRP1;           
  __IO uint32_t STARTERP1;             
  __IO uint32_t STARTRSRP1CLR;
  __IO uint32_t STARTSRP1;
       uint32_t RESERVED12[4];

  __IO uint32_t PDSLEEPCFG;      /* Offset 0x230 */
  __IO uint32_t PDAWAKECFG;              
  __IO uint32_t PDRUNCFG;
	   uint32_t RESERVED13;
  __IO uint32_t EZHBOOT;
  __IO uint32_t EZHCTRL;
  __IO uint32_t EZHMUXSEL;
  __IO uint32_t EZHARM2EZH;
  __IO uint32_t EZHEZH2ARM;
  __IO uint32_t EZHEZHPC;
  __IO uint32_t EZHEZHSP;
  __IO uint32_t EZHINTERRUPT;
       uint32_t RESERVED14[101];

  __I  uint32_t DEVICE_ID;
} LPC_SYSCON_TypeDef;


/*------------- Pin Connect Block (IOCON) --------------------------------*/
/** @addtogroup LPC122x_IOCON LPC122x I/O Configuration Block 
  @{
*/
typedef struct
{
  __IO uint32_t PIO2_28;		/* 0x00 */
  __IO uint32_t PIO2_29;
  __IO uint32_t PIO0_19;
  __IO uint32_t PIO0_20;
  __IO uint32_t PIO0_21;
  __IO uint32_t PIO0_22;
  __IO uint32_t PIO0_23;
  __IO uint32_t PIO0_24;

  __IO uint32_t SWDIO_PIO0_25;	/* 0x20 */
  __IO uint32_t SWCLK_PIO0_26;
  __IO uint32_t PIO0_27;
  __IO uint32_t PIO2_12;
  __IO uint32_t PIO2_13;
  __IO uint32_t PIO2_14;
  __IO uint32_t PIO2_15;
  __IO uint32_t PIO0_28;

  __IO uint32_t PIO0_29;		/* 0x40 */
  __IO uint32_t PIO0_0;
  __IO uint32_t PIO0_1;
  __IO uint32_t PIO0_2;
       uint32_t RESERVED0;
  __IO uint32_t PIO0_3;
  __IO uint32_t PIO0_4;
  __IO uint32_t PIO0_5;

  __IO uint32_t PIO0_6;			/* 0x60 */
  __IO uint32_t PIO0_7;
  __IO uint32_t PIO0_8;
  __IO uint32_t PIO0_9;
  __IO uint32_t PIO2_0;
  __IO uint32_t PIO2_1;
  __IO uint32_t PIO2_2;
  __IO uint32_t PIO2_3;

  __IO uint32_t PIO2_4;			/* 0x80 */
  __IO uint32_t PIO2_5;
  __IO uint32_t PIO2_6;
  __IO uint32_t PIO2_7;
  __IO uint32_t PIO0_10;
  __IO uint32_t PIO0_11;
  __IO uint32_t PIO0_12;
  __IO uint32_t RESET_P0_13;

  __IO uint32_t PIO0_14;		/* 0xA0 */
  __IO uint32_t PIO0_15;
  __IO uint32_t PIO0_16;
  __IO uint32_t PIO0_17;
  __IO uint32_t PIO0_18;
  __IO uint32_t PIO0_30;
  __IO uint32_t PIO0_31;
  __IO uint32_t PIO1_0;

  __IO uint32_t PIO1_1;			/* 0xC0 */
  __IO uint32_t PIO1_2;
  __IO uint32_t PIO1_3;
  __IO uint32_t PIO1_4;
  __IO uint32_t PIO1_5;
  __IO uint32_t PIO1_6;
       uint32_t RESERVED1[2];

  __IO uint32_t PIO2_8;				/* 0xE0 */
  __IO uint32_t PIO2_9;
  __IO uint32_t PIO2_10;
  __IO uint32_t PIO2_11;
#if 0
  /* LOC registers are no longer needed on LPC122x V1. */
  __IO uint32_t EZH0_LOC;
  __IO uint32_t EZH1_LOC;
  __IO uint32_t CT32B0_0_LOC;
  __IO uint32_t EZH2_LOC;
 
  __IO uint32_t CT32B0_1_LOC;		/* 0x100 */
  __IO uint32_t EZH3_LOC;
  __IO uint32_t CT32B0_2_LOC;
  __IO uint32_t EZH4_LOC;
  __IO uint32_t CT32B0_3_LOC;
  __IO uint32_t EZH5_LOC;
  __IO uint32_t EZH6_LOC;
  __IO uint32_t CT32B1_0_LOC;

  __IO uint32_t EZH7_LOC;			/* 0x120 */
  __IO uint32_t CT32B1_1_LOC;
  __IO uint32_t EZH8_LOC;
  __IO uint32_t CT32B1_2_LOC;
  __IO uint32_t EZH9_LOC;
  __IO uint32_t CT32B1_3_LOC;
  __IO uint32_t EZH10_LOC;
  __IO uint32_t EZH11_LOC;

  __IO uint32_t CT16B0_0_LOC;		/* 0x140 */
  __IO uint32_t EZH12_LOC;
  __IO uint32_t CT16B0_1_LOC;
  __IO uint32_t EZH13_LOC;
  __IO uint32_t EZH14_LOC;
  __IO uint32_t EZH15_LOC;
  __IO uint32_t CT16B1_0_LOC;
  __IO uint32_t CT16B1_1_LOC;
#endif
} LPC_IOCON_TypeDef;

/*------------- microDMA (DMA) --------------------------*/
/** @addtogroup LPC122x_DMA LPC122x microDMA
  @{
*/
typedef struct
{
  __I  uint32_t STATUS;
  __O  uint32_t CFG;
  __IO uint32_t CTRL_BASE_PTR;
  __I  uint32_t ALT_CTRL_BASE_PTR;
  __I  uint32_t WAITONREQ_STATUS;
  __O  uint32_t CHNL_SW_REQUEST;
  __IO uint32_t CHNL_USEBURST_SET;
  __O  uint32_t CHNL_USEBURST_CLR;
  __IO uint32_t CHNL_REQ_MASK_SET;
  __O  uint32_t CHNL_REQ_MASK_CLR;
  __IO uint32_t CHNL_ENABLE_SET;
  __O  uint32_t CHNL_ENABLE_CLR;
  __IO uint32_t CHNL_PRI_ALT_SET;
  __O  uint32_t CHNL_PRI_ALT_CLR;
  __IO uint32_t CHNL_PRIORITY_SET;
  __O  uint32_t CHNL_PRIORITY_CLR;
	   uint32_t RESERVE0[3];
  __IO uint32_t ERR_CLR;					/* 0x4C */
  	   uint32_t RESERVE1[12];
  __IO uint32_t CHNL_IRQ_STATUS;			/* 0x80 */
  __IO uint32_t IRQ_ERR_ENABLE;
  __IO uint32_t CHNL_IRQ_ENABLE;
} LPC_DMA_TypeDef;
/*@}*/ /* end of group LPC122x_DMA */

/*------------- Comparator (CMP) --------------------------------*/
/** @addtogroup LPC122x_CMD LPC122x Comparator
  @{
*/
typedef struct
{
  __IO uint32_t CMP;
  __IO uint32_t VLAD;
} LPC_COMP_TypeDef;
/*@}*/ /* end of group LPC122x_CMD */

/*------------- Real Timer Clock (RTC) --------------------------*/
/** @addtogroup LPC122x_RTC LPC122x Real-time Clock
  @{
*/
typedef struct
{
  __I  uint32_t DR;
  __IO uint32_t MR;
  __IO uint32_t LR;
  __IO uint32_t CR;
  __IO uint32_t IMSC;
  __I  uint32_t IRS;
  __I  uint32_t MIS;
  __IO uint32_t ICR;
} LPC_RTC_TypeDef;
/*@}*/ /* end of group LPC122x_RTC */

/*------------- Power Management Unit (PMU) --------------------------*/
/** @addtogroup LPC122x_PMU LPC122x Power Management Unit
  @{
*/
typedef struct
{
  __IO uint32_t PCON;
  __IO uint32_t GPREG0;
  __IO uint32_t GPREG1;
  __IO uint32_t GPREG2;
  __IO uint32_t GPREG3;
  __IO uint32_t GPREG4;
} LPC_PMU_TypeDef;
/*@}*/ /* end of group LPC122x_PMU */

/*------------- General Purpose Input/Output (GPIO) --------------------------*/
/** @addtogroup LPC122x_GPIO LPC122x General Purpose Input/Output 
  @{
*/
typedef struct
{
  __IO uint32_t MASK;
  __I  uint32_t PIN;
  __IO uint32_t OUT;
  __O  uint32_t SET;
  __O  uint32_t CLR;
  __O  uint32_t NOT;
  	   uint32_t RESERVE[2];
  __IO uint32_t DIR;
  __IO uint32_t IS;
  __IO uint32_t IBE;
  __IO uint32_t IEV;
  __IO uint32_t IE;
  __I  uint32_t RIS;
  __I  uint32_t MIS;
  __O  uint32_t IC;
} LPC_GPIO_TypeDef;
/*@}*/ /* end of group LPC122x_GPIO */


/*------------- Timer (TMR) --------------------------------------------------*/
/** @addtogroup LPC122x_TMR LPC122x 16/32-bit Counter/Timer 
  @{
*/
typedef struct
{
  __IO uint32_t IR;
  __IO uint32_t TCR;
  __IO uint32_t TC;
  __IO uint32_t PR;
  __IO uint32_t PC;
  __IO uint32_t MCR;
  __IO uint32_t MR0;
  __IO uint32_t MR1;
  __IO uint32_t MR2;
  __IO uint32_t MR3;
  __IO uint32_t CCR;
  __I  uint32_t CR0;
  __I  uint32_t CR1;
  __I  uint32_t CR2;
  __I  uint32_t CR3;
  __IO uint32_t EMR;
       uint32_t RESERVED2[12];
  __IO uint32_t CTCR;
  __IO uint32_t PWMC;
} LPC_TMR_TypeDef;
/*@}*/ /* end of group LPC122x_TMR */

/*------------- Universal Asynchronous Receiver Transmitter (UART) -----------*/
/** @addtogroup LPC122x_UART LPC122x Universal Asynchronous Receiver/Transmitter 
  @{
*/
typedef struct
{
  union {
  __I  uint32_t  RBR;
  __O  uint32_t  THR;
  __IO uint32_t  DLL;
  };
  union {
  __IO uint32_t  DLM;
  __IO uint32_t  IER;
  };
  union {
  __I  uint32_t  IIR;
  __O  uint32_t  FCR;
  };
  __IO uint32_t  LCR;
  __IO uint32_t  MCR;
  __I  uint32_t  LSR;
  __I  uint32_t  MSR;
  __IO uint32_t  SCR;
  __IO uint32_t  ACR;
  __IO uint32_t  ICR;
  __IO uint32_t  FDR;
       uint32_t  RESERVED0;
  __IO uint32_t  TER;
       uint32_t  RESERVED1[6];
  __IO uint32_t  RS485CTRL;
  __IO uint32_t  ADRMATCH;
  __IO uint32_t  RS485DLY;
  __I  uint32_t  FIFOLVL;
} LPC_UART_TypeDef;
/*@}*/ /* end of group LPC122x_UART */

/*------------- Synchronous Serial Communication (SSP) -----------------------*/
/** @addtogroup LPC122x_SSP LPC122x Synchronous Serial Port 
  @{
*/
typedef struct
{
  __IO uint32_t CR0;
  __IO uint32_t CR1;
  __IO uint32_t DR;
  __I  uint32_t SR;
  __IO uint32_t CPSR;
  __IO uint32_t IMSC;
  __IO uint32_t RIS;
  __IO uint32_t MIS;
  __IO uint32_t ICR;
} LPC_SSP_TypeDef;
/*@}*/ /* end of group LPC122x_SSP */

/*------------- Inter-Integrated Circuit (I2C) -------------------------------*/
/** @addtogroup LPC122x_I2C LPC122x I2C-Bus Interface 
  @{
*/
typedef struct
{
  __IO uint32_t CONSET;
  __I  uint32_t STAT;
  __IO uint32_t DAT;
  __IO uint32_t ADR0;
  __IO uint32_t SCLH;
  __IO uint32_t SCLL;
  __O  uint32_t CONCLR;
  __IO uint32_t MMCTRL;
  __IO uint32_t ADR1;
  __IO uint32_t ADR2;
  __IO uint32_t ADR3;
  __I  uint32_t DATA_BUFFER;
  __IO uint32_t MASK0;
  __IO uint32_t MASK1;
  __IO uint32_t MASK2;
  __IO uint32_t MASK3;
} LPC_I2C_TypeDef;
/*@}*/ /* end of group LPC122x_I2C */

/*------------- Watchdog Timer (WDT) -----------------------------------------*/
/** @addtogroup LPC122x_WDT LPC122x WatchDog Timer 
  @{
*/
typedef struct
{
  __IO uint32_t MOD;
  __IO uint32_t TC;
  __O  uint32_t FEED;
  __I  uint32_t TV;
  __IO uint32_t CLKSEL;
  __IO uint32_t WARNINT;
  __IO uint32_t WINDOW;
} LPC_WDT_TypeDef;
/*@}*/ /* end of group LPC122x_WDT */

/*------------- Analog-to-Digital Converter (ADC) ----------------------------*/
/** @addtogroup LPC122x_ADC LPC122x Analog-to-Digital Converter 
  @{
*/
typedef struct
{
  __IO uint32_t CR;
  __IO uint32_t GDR;
       uint32_t RESERVED0;
  __IO uint32_t INTEN;
  __IO uint32_t DR[8];
  __I  uint32_t STAT;
} LPC_ADC_TypeDef;
/*@}*/ /* end of group LPC122x_ADC */

/*------------- Flash Memory Controller (FMC) -----------------------------------*/
typedef struct
{
  __IO uint32_t TBCFG;            /* Time Base Config register  */
  __IO uint32_t FINSTR;           /* Flash Instruction register */
  __I  uint32_t INSSTA;           /* Raw Instruction Status register */
  __IO uint32_t INSSCLR;          /* Raw Instruction Clear register */
  __IO uint32_t INT_EN;           /* Interrupt Enable register */
  __I  uint32_t INT_STA;          /* Interrupt Status register */
       uint32_t RESERVED0;
  __IO uint32_t ADDRLAT;          /* Address Latch registers */
  __IO uint32_t DATALAT;          /* Data Latch register */
  __IO uint32_t FIMC;             /* Flash Manaul Operation register */
  __IO uint32_t RDCFG;            /* Read Configuration register */
  __IO uint32_t EPPCFG;           /* Flash Programming Permission Cofig register */
  __IO uint32_t EPPAA;            /* Flash Programming Permission Address A register */
  __IO uint32_t EPPAB;            /* Flash Programming Permission Address B register */
} LPC_FMC_TypeDef;

/*------------- CRC Engine (CRC) -----------------------------------------*/
typedef struct
{
  __IO uint32_t MODE;
  __IO uint32_t SEED;
  union {
  __I  uint32_t SUM;
  __O  uint32_t WR_DATA_DWORD;
  __O  uint16_t WR_DATA_WORD;
       uint16_t RESERVED_WORD;
  __O  uint8_t WR_DATA_BYTE;
       uint8_t RESERVED_BYTE[3];
  };
  __I  uint32_t ID;
} LPC_CRC_TypeDef;

#if defined ( __CC_ARM   )
#pragma no_anon_unions
#endif

/******************************************************************************/
/*                         Peripheral memory map                              */
/******************************************************************************/
/* Base addresses                                                             */
#define LPC_FLASH_BASE        (0x00000000)
#define LPC_RAM_BASE          (0x10000000)
#define LPC_APB0_BASE         (0x40000000)
#define LPC_AHB_BASE          (0x50000000)

/* APB0 peripherals                                                          */
#define LPC_I2C_BASE          (LPC_APB0_BASE + 0x00000)
#define LPC_WDT_BASE          (LPC_APB0_BASE + 0x04000)
#define LPC_UART0_BASE        (LPC_APB0_BASE + 0x08000)
#define LPC_UART1_BASE        (LPC_APB0_BASE + 0x0C000)
#define LPC_CT16B0_BASE       (LPC_APB0_BASE + 0x10000)
#define LPC_CT16B1_BASE       (LPC_APB0_BASE + 0x14000)
#define LPC_CT32B0_BASE       (LPC_APB0_BASE + 0x18000)
#define LPC_CT32B1_BASE       (LPC_APB0_BASE + 0x1C000)
#define LPC_ADC_BASE          (LPC_APB0_BASE + 0x20000)

#define LPC_PMU_BASE          (LPC_APB0_BASE + 0x38000)
#define LPC_SSP_BASE          (LPC_APB0_BASE + 0x40000)
#define LPC_IOCON_BASE        (LPC_APB0_BASE + 0x44000)
#define LPC_SYSCON_BASE       (LPC_APB0_BASE + 0x48000)
#define LPC_DMA_BASE          (LPC_APB0_BASE + 0x4C000)
#define LPC_RTC_BASE          (LPC_APB0_BASE + 0x50000)
#define LPC_COMP_BASE         (LPC_APB0_BASE + 0x54000)

/* AHB peripherals */	
#define LPC_GPIO_BASE         (LPC_AHB_BASE  + 0x00000)
#define LPC_GPIO0_BASE        (LPC_AHB_BASE  + 0x00000)
#define LPC_GPIO1_BASE        (LPC_AHB_BASE  + 0x10000)
#define LPC_GPIO2_BASE        (LPC_AHB_BASE  + 0x20000)
#define LPC_FMC_BASE          (LPC_AHB_BASE  + 0x60000)
#define LPC_CRC_BASE          (LPC_AHB_BASE  + 0x70000)

/******************************************************************************/
/*                         Peripheral declaration                             */
/******************************************************************************/
#define LPC_I2C               ((LPC_I2C_TypeDef    *) LPC_I2C_BASE   )
#define LPC_WDT               ((LPC_WDT_TypeDef    *) LPC_WDT_BASE   )
#define LPC_UART0             ((LPC_UART_TypeDef   *) LPC_UART0_BASE )
#define LPC_UART1             ((LPC_UART_TypeDef   *) LPC_UART1_BASE )
#define LPC_TMR16B0           ((LPC_TMR_TypeDef    *) LPC_CT16B0_BASE)
#define LPC_TMR16B1           ((LPC_TMR_TypeDef    *) LPC_CT16B1_BASE)
#define LPC_TMR32B0           ((LPC_TMR_TypeDef    *) LPC_CT32B0_BASE)
#define LPC_TMR32B1           ((LPC_TMR_TypeDef    *) LPC_CT32B1_BASE)
#define LPC_ADC               ((LPC_ADC_TypeDef    *) LPC_ADC_BASE   )
#define LPC_PMU               ((LPC_PMU_TypeDef    *) LPC_PMU_BASE   )
#define LPC_SSP               ((LPC_SSP_TypeDef    *) LPC_SSP_BASE   )
#define LPC_IOCON             ((LPC_IOCON_TypeDef  *) LPC_IOCON_BASE )
#define LPC_SYSCON            ((LPC_SYSCON_TypeDef *) LPC_SYSCON_BASE)
#define LPC_DMA               ((LPC_DMA_TypeDef    *) LPC_DMA_BASE   )
#define LPC_RTC               ((LPC_RTC_TypeDef    *) LPC_RTC_BASE   )
#define LPC_COMP              ((LPC_COMP_TypeDef   *) LPC_COMP_BASE  )

#define LPC_GPIO0             ((LPC_GPIO_TypeDef   *) LPC_GPIO0_BASE )
#define LPC_GPIO1             ((LPC_GPIO_TypeDef   *) LPC_GPIO1_BASE )
#define LPC_GPIO2             ((LPC_GPIO_TypeDef   *) LPC_GPIO2_BASE )
#define LPC_FMC               ((LPC_FMC_TypeDef    *) LPC_FMC_BASE   )
#define LPC_CRC               ((LPC_CRC_TypeDef    *) LPC_CRC_BASE   )

#ifdef __cplusplus
 }
#endif 

#endif  // __LPC122x_H__
