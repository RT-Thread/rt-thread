/*
  ******************************************************************************
  * @file    ACM32F0x0.h
  * @brief   CMSIS ACM32F0x0 Device Peripheral Access Layer Header File.
  *
  *          This file contains:
  *           - Data structures and the address mapping for all peripherals
  *           - Peripheral's registers declarations and bits definition
  *           - Macros to access peripheral’s registers hardware
  *
  ******************************************************************************
*/
#ifndef __ACM32F0x0_H__
#define __ACM32F0x0_H__

#ifdef __cplusplus
extern "C"
{
#endif

///*------------------- Interrupt Number Definition ----------------------*/
typedef enum IRQn
{
/* ----------------------  SC000 Processor Exceptions Numbers  --------------------- */
    NonMaskableInt_IRQn           = -14,      /*  2 Non Maskable Interrupt */
    HardFault_IRQn                = -13,      /*  3 HardFault Interrupt */
    MemManage_IRQn                = -12,      /*  4 MemManage Interrupt */

    SVCall_IRQn                   = -5,       /* 11 SV Call Interrupt */

    PendSV_IRQn                   = -2,       /* 14 Pend SV Interrupt */
    SysTick_IRQn                  = -1,       /* 15 System Tick Interrupt */

/* ----------------------  ARMCM0 Specific Interrupt Numbers  --------------------- */
    WDT_IRQn                      = 0,        // 0:  WDT_IRQHandler
    RTC_IRQn                      = 1,        // 1:  RTC_IRQHandler
    EFC_IRQn                      = 2,        // 2:  EFC_IRQHandler
    GPIOAB_IRQn                   = 3,        // 3:  GPIOAB_IRQHandler
    GPIOCD_IRQn                   = 4,        // 4:  GPIOCD_IRQHandler
    EXTI_IRQn                     = 5,        // 5:  EXTI_IRQHandler
    SRAM_PARITY_IRQn              = 6,        // 6:  SRAM_PARITY_IRQHandler
    CLKRDY_IRQn                   = 7,        // 7:  CLKRDY_IRQHandler
    LCD_IRQn                      = 8,        // 8:  LCD_IRQHandler
    DMA_IRQn                      = 9,        // 9:  DMA_IRQHandler
    UART3_IRQn                    = 10,       // 10: UART3_IRQHandler
    TKEY_IRQn                     = 11,       // 11: TKEY_IRQHandler
    ADC_IRQn                      = 12,       // 12: ADC_IRQHandler
    TIM1_BRK_UP_TRG_COM_IRQn      = 13,       // 13: TIM1_BRK_UP_TRG_COM_IRQHandler
    TIM1_CC_IRQn                  = 14,       // 14: TIM1_CC_IRQHandler
    TIM3_IRQn                     = 16,       // 16: TIM3_IRQHandler
    TIM6_IRQn                     = 17,       // 17: TIM6_IRQHandler
    TIM14_IRQn                    = 19,       // 19: TIM14_IRQHandler
    TIM15_IRQn                    = 20,       // 20: TIM15_IRQHandler
    TIM16_IRQn                    = 21,       // 21: TIM16_IRQHandler
    TIM17_IRQn                    = 22,       // 22: TIM17_IRQHandler
    I2C1_IRQn                     = 23,       // 23: I2C1_IRQHandler
    I2C2_IRQn                     = 24,       // 24: I2C2_IRQHandler
    SPI1_IRQn                     = 25,       // 25: SPI1_IRQHandler
    SPI2_IRQn                     = 26,       // 26: SPI2_IRQHandler
    UART1_IRQn                    = 27,       // 27: UART1_IRQHandler
    UART2_IRQn                    = 28,       // 28: UART2_IRQHandler
    LPUART_IRQn                   = 29,       // 29: LPUART_IRQHandler
    CAN1_IRQn                     = 30,       // 30: CAN1_IRQHandler
    AES_IRQn                      = 31,       // 31: AES_IRQhandler
} IRQn_Type;

/* ================================================================================ */
/* ================      Processor and Core Peripheral Section     ================ */
/* ================================================================================ */

/* Configuration of the SC000 Processor and Core Peripherals */
#define __CM0_REV                 0x0000U   /* Core revision r0p0 */
#define __NVIC_PRIO_BITS          2         /* Number of Bits used for Priority Levels */
#define __Vendor_SysTickConfig    0         /* Set to 1 if different SysTick Config is used */

#include "core_cm0.h"    /* Processor and core peripherals */

#include "stdio.h"
#include "string.h"

#include "stdint.h"
#include "stdbool.h"

///*------------------- Bit Opertions ----------------------*/
#define BIT0            (1U << 0)
#define BIT1            (1U << 1)
#define BIT2            (1U << 2)
#define BIT3            (1U << 3)
#define BIT4            (1U << 4)
#define BIT5            (1U << 5)
#define BIT6            (1U << 6)
#define BIT7            (1U << 7)
#define BIT8            (1U << 8)
#define BIT9            (1U << 9)
#define BIT10           (1U << 10)
#define BIT11           (1U << 11)
#define BIT12           (1U << 12)
#define BIT13           (1U << 13)
#define BIT14           (1U << 14)
#define BIT15           (1U << 15)
#define BIT16           (1U << 16)
#define BIT17           (1U << 17)
#define BIT18           (1U << 18)
#define BIT19           (1U << 19)
#define BIT20           (1U << 20)
#define BIT21           (1U << 21)
#define BIT22           (1U << 22)
#define BIT23           (1U << 23)
#define BIT24           (1U << 24)
#define BIT25           (1U << 25)
#define BIT26           (1U << 26)
#define BIT27           (1U << 27)
#define BIT28           (1U << 28)
#define BIT29           (1U << 29)
#define BIT30           (1U << 30)
#define BIT31           (1U << 31)

/** @Addtogroup Peripheral_Registers_Structures
  * @{
  */

///*------------------- FLASH Registers ----------------------*/
typedef struct
{
    __IO uint32_t CTRL;             // 0x00
    __IO uint32_t SEC;              // 0x04
    __IO uint32_t ADCT;             // 0x08
    __IO uint32_t TERASE;           // 0x0C
    __IO uint32_t TPROG;            // 0x10
    __IO uint32_t STATUS;           // 0x14
    __IO uint32_t INTSTATUS;        // 0x18
    __IO uint32_t INTEN;            // 0x1C
    __IO uint32_t RSV0[6];          // 0x20-0x34
    __IO uint32_t NVS;              // 0x38
}EFC_TypeDef;


///*------------------- Timer Registers ----------------------*/
typedef struct
{
    __IO uint32_t CR1;      // 0x00
    __IO uint32_t CR2;      // 0x04
    __IO uint32_t SMCR;     // 0x08
    __IO uint32_t DIER;     // 0x0C
    __IO uint32_t SR;       // 0x10
    __IO uint32_t EGR;      // 0x14
    __IO uint32_t CCMR1;    // 0x18
    __IO uint32_t CCMR2;    // 0x1C
    __IO uint32_t CCER;     // 0x20
    __IO uint32_t CNT;      // 0x24
    __IO uint32_t PSC;      // 0x28
    __IO uint32_t ARR;      // 0x2C
    __IO uint32_t RCR;      // 0x30
    __IO uint32_t CCR1;     // 0x34
    __IO uint32_t CCR2;     // 0x38
    __IO uint32_t CCR3;     // 0x3C
    __IO uint32_t CCR4;     // 0x40
    __IO uint32_t BDTR;     // 0x44
    __IO uint32_t DCR;      // 0x48
    __IO uint32_t DMAR;     // 0x4C
    __IO uint32_t RSV0[4];  // 0x50-0x5C
    __IO uint32_t AF1;      // 0x60
    __IO uint32_t RSV1;     // 0x64
    __IO uint32_t TISEL;    // 0x68
    __IO uint32_t DBER;     // 0x6C
}TIM_TypeDef;


///*------------------- RTC、PMU Registers ----------------------*/
typedef struct
{
    __IO uint32_t WP;                // 0x00
    __IO uint32_t IE;                // 0x04
    __IO uint32_t SR;                // 0x08
    __IO uint32_t SEC;               // 0x0C
    __IO uint32_t MIN;               // 0x10
    __IO uint32_t HOUR;              // 0x14
    __IO uint32_t DATE;              // 0x18
    __IO uint32_t WEEK;              // 0x1C
    __IO uint32_t MONTH;             // 0x20
    __IO uint32_t YEAR;              // 0x24
    __IO uint32_t ALM;               // 0x28
    __IO uint32_t CR;                // 0x2C
    __IO uint32_t ADJUST;            // 0x30
    __IO uint32_t RSV0[4];           // 0x34 ~ 0x40
    __IO uint32_t CLKSTAMP1_TIME;    // 0x44
    __IO uint32_t CALSTAMP1_DATE;    // 0x48
    __IO uint32_t CLKSTAMP2_TIME;    // 0x4C
    __IO uint32_t CALSTAMP2_DATE;    // 0x50
    __IO uint32_t RSV1[7];           // 0x54-0x6C
    __IO uint32_t BACKUP[5];         // 0x70 ~ 0x80
}RTC_TypeDef;

typedef struct
{
    __IO uint32_t CR1;      // 0x00
    __IO uint32_t SR;       // 0x04
    __IO uint32_t IOSEL;    // 0x08
    __IO uint32_t IOCR;     // 0x0C
    __IO uint32_t ANACR;    // 0x10
    __IO uint32_t CR2;      // 0x14
}PMU_TypeDef;


///*------------------- WDT Registers ----------------------*/
typedef struct
{
    __IO uint32_t LOAD;
    __IO uint32_t COUNT;
    __IO uint32_t CTRL;
    __IO uint32_t FEED;
    __IO uint32_t INTCLRTIME;
    __IO uint32_t RIS;
}WDT_TypeDef;


///*------------------- IWDT Registers ----------------------*/
typedef struct
{
    __IO uint32_t CMDR;     // 0x00
    __IO uint32_t PR;       // 0x04
    __IO uint32_t RLR;      // 0x08
    __IO uint32_t SR;       // 0x0C
    __IO uint32_t WINR;     // 0x10
    __IO uint32_t WUTR;     // 0x14
}IWDT_TypeDef;


///*------------------- LCD Registers ----------------------*/
typedef struct
{
    __IO uint32_t CR0;     // 0x00
    __IO uint32_t CR1;       // 0x04
    __IO uint32_t INTCLR;      // 0x08
    __IO uint32_t LCD_POEN0;       // 0x0C
    __IO uint32_t LCD_POEN1;     // 0x10
    __IO uint32_t RSV[11];
    __IO uint32_t LCD_RAM[16];   /*!< LCD display memory,                Address offset: 0x40-0x7c */
}LCD_TypeDef;


///*------------------- UART Registers ----------------------*/
typedef struct
{
    __IO uint32_t DR;       // 0x00
    __IO uint32_t RSR;      // 0x04
    __IO uint32_t RSV0[4];  // 0x08-0x14
    __IO uint32_t FR;       // 0x18
    __IO uint32_t RSV1;     // 0x1C
    __IO uint32_t ILPR;     // 0x20
    __IO uint32_t IBRD;     // 0x24
    __IO uint32_t FBRD;     // 0x28
    __IO uint32_t LCRH;     // 0x2C
    __IO uint32_t CR;       // 0x30
    __IO uint32_t IFLS;     // 0x34
    __IO uint32_t IE;       // 0x38
    __IO uint32_t RIS;      // 0x3C
    __IO uint32_t MIS;      // 0x40
    __IO uint32_t ICR;      // 0x44
    __IO uint32_t DMACR;    // 0x48
    __IO uint32_t RSV2[2];  // 0x4C-0x50
    __IO uint32_t CR2;      // 0x54
    __IO uint32_t BCNT;     // 0x58
}UART_TypeDef;

///*------------------- CAN Registers ----------------------*/
typedef struct
{
    __IO uint32_t ACR[4];
    __IO uint32_t AMR[4];
    __IO uint32_t RSV[5];
}Filter_typedef;

typedef union
{
    __IO uint32_t  DATABUF[13];
    Filter_typedef FILTER;
}DF_typedef;

typedef struct
{
    __IO uint32_t MOD;
    __IO uint32_t CMR;
    __IO uint32_t SR;
    __IO uint32_t IR;
    __IO uint32_t IER;
    __IO uint32_t RSV0;
    __IO uint32_t BTR0;
    __IO uint32_t BTR1;
    __IO uint32_t OCR;
    __IO uint32_t RSV1;
    __IO uint32_t RSV2;
    __IO uint32_t ALC;
    __IO uint32_t ECC;
    __IO uint32_t EWLR;
    __IO uint32_t RXERR;
    __IO uint32_t TXERR;
    __IO DF_typedef    DF;
    __IO uint32_t RMC;
    __IO uint32_t RBSA;
    __IO uint32_t CDR;
    __IO uint32_t RXFIFO[64];
    __IO uint32_t TXFIFO[13];
}CAN_TypeDef;

///*------------------- I2C Registers ----------------------*/
typedef struct
{
    __IO uint32_t SLAVE_ADDR1;     // 0x00
    __IO uint32_t CLK_DIV;         // 0x04
    __IO uint32_t CR;              // 0x08
    __IO uint32_t SR;              // 0x0C
    __IO uint32_t DR;              // 0x10
    __IO uint32_t SLAVE_ADDR23;    // 0x14
    __IO uint32_t RSV0[3];         // 0x18-0x20
    __IO uint32_t TIMEOUT;         // 0x24
}I2C_TypeDef;


///*------------------- LPUART Registers ----------------------*/
typedef struct
{
    __IO uint32_t RXDR;     // 0x00
    __IO uint32_t TXDR;     // 0x04
    __IO uint32_t LCR;      // 0x08
    __IO uint32_t CR;       // 0x0C
    __IO uint32_t IBAUD;    // 0x10
    __IO uint32_t FBAUD;    // 0x14
    __IO uint32_t IE;       // 0x18
    __IO uint32_t SR;       // 0x1C
    __IO uint32_t ADDR;     // 0x20
}LPUART_TypeDef;


///*------------------- COMP Registers ----------------------*/
typedef struct
{
    __IO uint32_t CR1;  // 0x00
    __IO uint32_t CR2;  // 0x04
    __IO uint32_t SR;   // 0x08
}COMP_TypeDef;


///*------------------- OPA Registers ----------------------*/
typedef struct
{
    __IO uint32_t OPA1_CSR; // 0x00
    __IO uint32_t OPA2_CSR; // 0x04
    __IO uint32_t OPA3_CSR; // 0x08
}OPA_TypeDef;


///*------------------- EXTI Registers ----------------------*/
typedef struct
{
    __IO uint32_t IENR;         // 0x00
    __IO uint32_t EENR;         // 0x04
    __IO uint32_t RTENR;        // 0x08
    __IO uint32_t FTENR;        // 0x0C
    __IO uint32_t SWIER;        // 0x10
    __IO uint32_t PDR;          // 0x14
    __IO uint32_t EXTICR1;      // 0x18
    __IO uint32_t EXTICR2;      // 0x1C
}EXTI_TypeDef;


///*------------------- SCU Registers ----------------------*/
typedef struct
{
    __IO uint32_t RCR;              // 0x00
    __IO uint32_t RSR;              // 0x04
    __IO uint32_t RSV0;             // 0x08
    __IO uint32_t IPRST;            // 0x0C
    __IO uint32_t CCR1;             // 0x10
    __IO uint32_t CCR2;             // 0x14
    __IO uint32_t CIR;              // 0x18
    __IO uint32_t IPCKENR1;          // 0x1C
    __IO uint32_t IPCKENR2;         // 0x20
    __IO uint32_t RCHCR;            // 0x24
    __IO uint32_t XTHCR;            // 0x28
    __IO uint32_t PLLCR;            // 0x2C
    __IO uint32_t LDOCR;            // 0x30
    __IO uint32_t RSV1;             // 0x34
    __IO uint32_t WMR;              // 0x38
    __IO uint32_t CLKOCR;           // 0x3C
    __IO uint32_t VER;              // 0x40
    __IO uint32_t SYSCFG1;          // 0x44
    __IO uint32_t LVDCFG;           // 0x48
    __IO uint32_t STOPCFG;          // 0x4C
    __IO uint32_t VECTOROFFSET;     // 0x50
    __IO uint32_t RSV2;             // 0x54
    __IO uint32_t MEMCFG;           // 0x58
    __IO uint32_t RSV3;             // 0x5C
    __IO uint32_t PASEL1;           // 0x60
    __IO uint32_t PASEL2;           // 0x64
    __IO uint32_t PBSEL1;           // 0x68
    __IO uint32_t PBSEL2;           // 0x6C
    __IO uint32_t PABPUR;           // 0x70
    __IO uint32_t PABPDR;           // 0x74
    __IO uint32_t PASTR;            // 0x78
    __IO uint32_t PBSTR;            // 0x7C
    __IO uint32_t PABSMTR;          // 0x80
    __IO uint32_t PABODR;           // 0x84
    __IO uint32_t PABADS;           // 0x88
    __IO uint32_t RSV4;             // 0x8C
    __IO uint32_t PCSEL1;           // 0x90
    __IO uint32_t PCSEL2;           // 0x94
    __IO uint32_t PDSEL1;           // 0x98
    __IO uint32_t RSV5;             // 0x9C
    __IO uint32_t PCDPUR;           // 0xA0
    __IO uint32_t PCDPDR;           // 0xA4
    __IO uint32_t PCSTR;            // 0xA8
    __IO uint32_t PDSTR;            // 0xAC
    __IO uint32_t PCDSMTR;          // 0xB0
    __IO uint32_t PCDODR;           // 0xB4
    __IO uint32_t PCDADS;           // 0xB8
}SCU_TypeDef;


///*------------------- CRC Registers ----------------------*/
typedef struct
{
    __IO uint32_t DATA;     // 0x00
    __IO uint32_t CTRL;     // 0x04
    __IO uint32_t INIT;     // 0x08
    __IO uint32_t RSV0;     // 0x0C
    __IO uint32_t OUTXOR;   // 0x10
    __IO uint32_t POLY;     // 0x14
    __IO uint32_t FDATA;    // 0x18
}CRC_TypeDef;


///*------------------- ADC Registers ----------------------*/
typedef struct
{
    __IO uint32_t SR;       // 0x00
    __IO uint32_t IE;       // 0x04
    __IO uint32_t CR1;      // 0x08
    __IO uint32_t CR2;      // 0x0C
    __IO uint32_t SMPR1;    // 0x10
    __IO uint32_t SMPR2;    // 0x14
    __IO uint32_t HTR;      // 0x18
    __IO uint32_t LTR;      // 0x1C
    __IO uint32_t SQR1;     // 0x20
    __IO uint32_t SQR2;     // 0x24
    __IO uint32_t SQR3;     // 0x28
    __IO uint32_t JSQR;     // 0x2C
    __IO uint32_t JDR;      // 0x30
    __IO uint32_t DR;       // 0x34
    __IO uint32_t DIFF;     // 0x38
    __IO uint32_t SIGN;     // 0x3C
    __IO uint32_t TSREF;    // 0x40
    __IO uint32_t SMPR3;    // 0x44
}ADC_TypeDef;


///*-----------------------TKEY------------------------*/
typedef struct
{
    __IO uint32_t ISR;          // 0x00
    __IO uint32_t IER;          // 0x04
    __IO uint32_t CR;           // 0x08
    __IO uint32_t SMPR;         // 0x0C
    __IO uint32_t SOFR;         // 0x10
    __IO uint32_t CXSELR;       // 0x14
    __IO uint32_t CRSELR;       // 0x18
    __IO uint32_t DR;           // 0x1C
    __IO uint32_t TH0;          // 0x20
    __IO uint32_t TH1;          // 0x24
    __IO uint32_t TH2;          // 0x28
    __IO uint32_t TH3;          // 0x2C
    __IO uint32_t TH4;          // 0x30
    __IO uint32_t TH5;          // 0x34
    __IO uint32_t TH6;          // 0x38
    __IO uint32_t TH7;          // 0x3C
    __IO uint32_t TH8;          // 0x40
    __IO uint32_t TH9;          // 0x44
    __IO uint32_t TH10;         // 0x48
    __IO uint32_t TH11;         // 0x4C
    __IO uint32_t TH12;         // 0x50
    __IO uint32_t TH13;         // 0x54
    __IO uint32_t TH14;         // 0x58
    __IO uint32_t TH15;         // 0x5C
    __IO uint32_t CH0;          // 0x60
    __IO uint32_t CH1;          // 0x64
    __IO uint32_t CH2;          // 0x68
    __IO uint32_t CH3;          // 0x6C
    __IO uint32_t CH4;          // 0x70
    __IO uint32_t CH5;          // 0x74
    __IO uint32_t CH6;          // 0x78
    __IO uint32_t CH7;          // 0x7C
    __IO uint32_t CH8;          // 0x80
    __IO uint32_t CH9;          // 0x84
    __IO uint32_t CH10;         // 0x88
    __IO uint32_t CH11;         // 0x8C
    __IO uint32_t CH12;         // 0x90
    __IO uint32_t CH13;         // 0x94
    __IO uint32_t CH14;         // 0x98
    __IO uint32_t CH15;         // 0x9C
}TKEY_TypeDef;


///*------------------- GPIO Registers ----------------------*/
typedef struct
{
    __IO uint32_t DIR;      // 0x00
    __IO uint32_t RSV0;     // 0x04
    __IO uint32_t SET;      // 0x08
    __IO uint32_t CLR;      // 0x0C
    __IO uint32_t ODATA;    // 0x10
    __IO uint32_t IDATA;    // 0x14
    __IO uint32_t IEN;      // 0x18
    __IO uint32_t IS;       // 0x1C
    __IO uint32_t IBE;      // 0x20
    __IO uint32_t IEV;      // 0x24
    __IO uint32_t IC;       // 0x28
    __IO uint32_t RIS;      // 0x2C
    __IO uint32_t MIS;      // 0x30
}GPIO_TypeDef;


///*------------------- SPI Registers ----------------------*/
typedef struct
{
    __IO uint32_t DAT;          // 0x00
    __IO uint32_t BAUD;         // 0x04
    __IO uint32_t CTL;          // 0x08
    __IO uint32_t TX_CTL;       // 0x0C
    __IO uint32_t RX_CTL;       // 0x10
    __IO uint32_t IE;           // 0x14
    __IO uint32_t STATUS;       // 0x18
    __IO uint32_t TXDELAY;      // 0x1C
    __IO uint32_t BATCH;        // 0x20
    __IO uint32_t CS;           // 0x24
    __IO uint32_t OUT_EN;       // 0x28
}SPI_TypeDef;


///*------------------- DMA Registers ----------------------*/
typedef struct
{
    __IO uint32_t INT_STATUS;            // 0x00
    __IO uint32_t INT_TC_STATUS;         // 0x04
    __IO uint32_t INT_TC_CLR;            // 0x08
    __IO uint32_t INT_ERR_STATUS;        // 0x0C
    __IO uint32_t INT_ERR_CLR;           // 0x10
    __IO uint32_t RAW_INT_TC_STATUS;     // 0x14
    __IO uint32_t RAW_INT_ERR_STATUS;    // 0x18
    __IO uint32_t EN_CH_STATUS;          // 0x1C
    __IO uint32_t RSV0[4];               // 0x20-0x2C
    __IO uint32_t CONFIG;                // 0x30
    __IO uint32_t SYNC;                  // 0x34
}DMA_TypeDef;

typedef struct
{
    __IO uint32_t SRC_ADDR;
    __IO uint32_t DEST_ADDR;
    __IO uint32_t LLI;
    __IO uint32_t CTRL;
    __IO uint32_t CONFIG;
}DMA_Channel_TypeDef;

typedef struct
{
    __IO uint32_t REG_AESDATAIN;            //0x00
    __IO uint32_t REG_AESKEYIN;             //0x04
    __IO uint32_t REG_AESIVIN;              //0x08
    __IO uint32_t REG_AESCTRL;              //0x0C
    __IO uint32_t REG_AESSTATE;             //0x10
    __IO uint32_t REG_AESDATAOUT;           //0x14
}AES_TypeDef;

typedef struct
{
    __IO uint32_t CTRL;      //0x00
    __IO uint32_t LFSR;      //0x04
}HRNG_TypeDef;

typedef struct
{
    __IO uint32_t DIVIDENED;     //0x00
    __IO uint32_t DIVISOR;       //0x04
    __IO uint32_t REMAIN;        //0x08
    __IO uint32_t QUOTIENT;      //0x0c
    __IO uint32_t STATUS;        //0x10

}DIV_TypeDef;

/**
  * @}
  */



/** @addtogroup Peripheral_memory_map
  * @{
  */
#define EFLASH_BASE        (0x00000000UL)
#define EFC_BASE           (0x00100000UL)
#define SRAM_BASE          (0x20000000UL)
#define PERIPH_BASE        (0x40000000UL)

#define APB1PERIPH_BASE    (PERIPH_BASE)
#define APB2PERIPH_BASE    (PERIPH_BASE + 0x10000UL)
#define AHB1PERIPH_BASE    (PERIPH_BASE + 0x20000UL)
#define AHB2PERIPH_BASE    (PERIPH_BASE + 0x30000UL)

///*----------------------APB1 peripherals------------------------*/
#define TIM3_BASE              (APB1PERIPH_BASE + 0x00000400UL)
#define TIM6_BASE              (APB1PERIPH_BASE + 0x00001000UL)
#define TIM14_BASE             (APB1PERIPH_BASE + 0x00002000UL)
#define PMU_BASE               (APB1PERIPH_BASE + 0x00002400UL)
#define RTC_BASE               (APB1PERIPH_BASE + 0x00002800UL)
#define WDT_BASE               (APB1PERIPH_BASE + 0x00002C00UL)
#define IWDT_BASE              (APB1PERIPH_BASE + 0x00003000UL)
#define UART2_BASE             (APB1PERIPH_BASE + 0x00004400UL)
#define UART3_BASE             (APB1PERIPH_BASE + 0x00004800UL)
#define I2C1_BASE              (APB1PERIPH_BASE + 0x00005400UL)
#define I2C2_BASE              (APB1PERIPH_BASE + 0x00005800UL)
#define CAN1_BASE              (APB1PERIPH_BASE + 0x00006400UL)
#define LPUART_BASE            (APB1PERIPH_BASE + 0x00008000UL)
#define LCD_BASE               (APB1PERIPH_BASE + 0x0000F000UL)

///*----------------------APB2 peripherals------------------------*/
#define COMP_BASE              (APB2PERIPH_BASE + 0x00000200UL)
#define OPA_BASE               (APB2PERIPH_BASE + 0x00000300UL)
#define EXTI_BASE              (APB2PERIPH_BASE + 0x00000400UL)
#define SCU_BASE               (APB2PERIPH_BASE + 0x00000800UL)
#define CRC_BASE               (APB2PERIPH_BASE + 0x00000C00UL)
#define ADC_BASE               (APB2PERIPH_BASE + 0x00002400UL)
#define TIM1_BASE              (APB2PERIPH_BASE + 0x00002C00UL)
#define UART1_BASE             (APB2PERIPH_BASE + 0x00003800UL)
#define TIM15_BASE             (APB2PERIPH_BASE + 0x00004000UL)
#define TIM16_BASE             (APB2PERIPH_BASE + 0x00004400UL)
#define TIM17_BASE             (APB2PERIPH_BASE + 0x00004800UL)
#define TKEY_BASE              (APB2PERIPH_BASE + 0x00006400UL)
#define GPIOAB_BASE            (APB2PERIPH_BASE + 0x0000F000UL)
#define GPIOCD_BASE            (APB2PERIPH_BASE + 0x0000F400UL)

//#define ACM32F0X0_VER_0
#ifdef ACM32F0X0_VER_0
#undef GPIOAB_BASE
#undef GPIOCD_BASE
#undef UART3_BASE
#undef PMU_BASE
#undef RTC_BASE
#undef COMP_BASE
#undef OPA_BASE

#define GPIOAB_BASE  0x40006800
#define GPIOCD_BASE  0x40016800
#define UART3_BASE   0x40004800
#define PMU_BASE     0x40002400
#define RTC_BASE     0x40002800
#define COMP_BASE    0x40010200
#define OPA_BASE     0x40010300
#endif

///*----------------------AHB1 peripherals------------------------*/
#define SPI1_BASE              (AHB1PERIPH_BASE)
#define SPI2_BASE              (AHB1PERIPH_BASE + 0x00000400UL)
#define DMAC_BASE              (AHB1PERIPH_BASE + 0x00001000UL)
#define DMA_Channel0_BASE      (AHB1PERIPH_BASE + 0x00001100UL)
#define DMA_Channel1_BASE      (AHB1PERIPH_BASE + 0x00001120UL)
#define DMA_Channel2_BASE      (AHB1PERIPH_BASE + 0x00001140UL)
#define DMA_Channel3_BASE      (AHB1PERIPH_BASE + 0x00001160UL)
#define DMA_Channel4_BASE      (AHB1PERIPH_BASE + 0x00001180UL)

///*----------------------AHB2 peripherals------------------------*/
#define AES_BASE               (AHB2PERIPH_BASE)
#define DIV_BASE               (AHB2PERIPH_BASE + 0x00000400UL)
#define HRNG_BASE              (AHB2PERIPH_BASE + 0x00000800UL)
/**
  * @}
  */



/** @addtogroup Peripheral_declaration
  * @{
  */
#define EFC                    ((EFC_TypeDef *)EFC_BASE)
#define TIM3                   ((TIM_TypeDef *)TIM3_BASE)
#define TIM6                   ((TIM_TypeDef *)TIM6_BASE)
#define TIM14                  ((TIM_TypeDef *)TIM14_BASE)
#define PMU                    ((PMU_TypeDef *)PMU_BASE)
#define RTC                    ((RTC_TypeDef *)RTC_BASE)
#define WDT                    ((WDT_TypeDef *)WDT_BASE)
#define IWDT                   ((IWDT_TypeDef *)IWDT_BASE)
#define LCD                     ((LCD_TypeDef *)LCD_BASE)
#define UART2                  ((UART_TypeDef *)UART2_BASE)
#define UART3                  ((UART_TypeDef *)UART3_BASE)
#define I2C1                   ((I2C_TypeDef *)I2C1_BASE)
#define I2C2                   ((I2C_TypeDef *)I2C2_BASE)
#define CAN1                  ((CAN_TypeDef *)CAN1_BASE)
#define LPUART                 ((LPUART_TypeDef *)LPUART_BASE)
#define GPIOAB                 ((GPIO_TypeDef *)GPIOAB_BASE)
#define EXTI                   ((EXTI_TypeDef *)EXTI_BASE)
#define SCU                    ((SCU_TypeDef *)SCU_BASE)
#define CRC                    ((CRC_TypeDef *)CRC_BASE)
#define COMP                   ((COMP_TypeDef *)COMP_BASE)
#define OPA                    ((OPA_TypeDef *)OPA_BASE)
#define ADC                    ((ADC_TypeDef *)ADC_BASE)
#define TIM1                   ((TIM_TypeDef *)TIM1_BASE)
#define UART1                  ((UART_TypeDef *)UART1_BASE)
#define TIM15                  ((TIM_TypeDef *)TIM15_BASE)
#define TIM16                  ((TIM_TypeDef *)TIM16_BASE)
#define TIM17                  ((TIM_TypeDef *)TIM17_BASE)
#define TKEY                   ((TKEY_TypeDef *)TKEY_BASE)
#define GPIOCD                 ((GPIO_TypeDef *)GPIOCD_BASE)
#define SPI1                   ((SPI_TypeDef *)SPI1_BASE)
#define SPI2                   ((SPI_TypeDef *)SPI2_BASE)
#define DMA                    ((DMA_TypeDef *)DMAC_BASE)
#define DMA_Channel0           ((DMA_Channel_TypeDef *)DMA_Channel0_BASE)
#define DMA_Channel1           ((DMA_Channel_TypeDef *)DMA_Channel1_BASE)
#define DMA_Channel2           ((DMA_Channel_TypeDef *)DMA_Channel2_BASE)
#define DMA_Channel3           ((DMA_Channel_TypeDef *)DMA_Channel3_BASE)
#define DMA_Channel4           ((DMA_Channel_TypeDef *)DMA_Channel4_BASE)
#define HRNG                   ((HRNG_TypeDef *)HRNG_BASE)
#define AES                    ((AES_TypeDef *)AES_BASE)
#define DIV                    ((DIV_TypeDef *)DIV_BASE)

/**
  * @}
  */


/** @addtogroup Exported_macros
  * @{
  */
#define SET_BIT(REG, BIT)            ((REG) |= (BIT))

#define CLEAR_BIT(REG, BIT)          ((REG) &= ~(BIT))

#define READ_BIT(REG, BIT)           ((REG) & (BIT))

#define CLEAR_REG(REG)               ((REG) = (0x0))

#define WRITE_REG(REG, VAL)          ((REG) = (VAL))

#define READ_REG(REG)                ((REG))

#define MODIFY_REG(REG,MASK,BITS)    ((REG) = (((REG)&(~(MASK)))|((BITS)&(MASK))))
/**
  * @}
  */

/* Compatible with old code */
typedef   signed       char    INT8;
typedef   signed short int     INT16;
typedef   signed       int     INT32;

typedef unsigned       char    UINT8;
typedef unsigned short int     UINT16;
typedef unsigned       int     UINT32;

#ifdef __cplusplus
}
#endif

#endif  /* ACM32F0x0_H */
