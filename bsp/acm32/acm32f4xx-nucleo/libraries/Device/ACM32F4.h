/*
  ******************************************************************************
  * @file    ACM32F4.h
  * @brief   CMSIS ACM32F4 Device Peripheral Access Layer Header File.
  *
  *          This file contains:
  *           - Data structures and the address mapping for all peripherals
  *           - Peripheral's registers declarations and bits definition
  *           - Macros to access peripheral¡¯s registers hardware
  *
  ******************************************************************************
*/
#ifndef __ACM32F4_H__
#define __ACM32F4_H__

#ifdef __cplusplus
extern "C"
{
#endif

///*------------------- Interrupt Number Definition ----------------------*/
typedef enum IRQn
{
/* ----------------------------------  Cortex-M33 Processor Exceptions Numbers ----------------------------------- */
    Reset_IRQn                = -15,       /* -15 Reset Vector, invoked on Power up and warm reset                 */
    NonMaskableInt_IRQn       = -14,       /* -14 Non maskable Interrupt, cannot be stopped or preempted           */
    HardFault_IRQn            = -13,       /* -13 Hard Fault, all classes of Fault                                 */
    MemoryManagement_IRQn     = -12,       /* -12 Memory Management, MPU mismatch, including Access Violation
                                                  and No Match                                                     */
    BusFault_IRQn             = -11,       /* -11 Bus Fault, Pre-Fetch-, Memory Access Fault, other address/memory
                                                  related Fault                                                    */
    UsageFault_IRQn           = -10,       /* -10 Usage Fault, i.e. Undef Instruction, Illegal State Transition    */
    SVCall_IRQn               =  -5,       /* -5  System Service Call via SVC instruction                          */
    DebugMonitor_IRQn         =  -4,       /* -4  Debug Monitor                                                    */
    PendSV_IRQn               =  -2,       /* -2  Pendable request for system service                              */
    SysTick_IRQn              =  -1,       /* -1  System Tick Timer                                                */

/* -------------------------------------  ARMCM0 Specific Interrupt Numbers -------------------------------------- */
    WDT_IRQn                    = 0,       /* 0:  WDT_IRQHandler                                                   */
    RTC_IRQn                    = 1,       /* 1:  RTC_IRQHandler                                                   */
    EFC_IRQn                    = 2,       /* 2:  EFC_IRQHandler                                                   */
    GPIOAB_IRQn                 = 3,       /* 3:  GPIOAB_IRQHandler                                                */
    GPIOCD_IRQn                 = 4,       /* 4:  GPIOCD_IRQHandler                                                */
    EXTI_IRQn                   = 5,       /* 5:  EXTI_IRQHandler                                                  */
    SRAM_PARITY_IRQn            = 6,       /* 6:  SRAM_PARITY_IRQHandler                                           */
    CLKRDY_IRQn                 = 7,       /* 7:  CLKRDY_IRQHandler                                                */
    UART4_IRQn                  = 8,       /* 8:  UART4_IRQHandler                                                 */
    DMA_IRQn                    = 9,       /* 9:  DMA_IRQHandler                                                   */
    UART3_IRQn                  = 10,      /* 10: UART3_IRQHandler                                                 */
    ADC_IRQn                    = 12,      /* 12: ADC_IRQHandler                                                   */
    TIM1_BRK_UP_TRG_COM_IRQn    = 13,      /* 13: TIM1_BRK_UP_TRG_COM_IRQHandler                                   */
    TIM1_CC_IRQn                = 14,      /* 14: TIM1_CC_IRQHandler                                               */
    TIM2_IRQn                   = 15,      /* 15: TIM2_IRQHandler                                                  */
    TIM3_IRQn                   = 16,      /* 16: TIM3_IRQHandler                                                  */
    TIM6_IRQn                   = 17,      /* 17: TIM6_IRQHandler                                                  */
    TIM7_IRQn                   = 18,      /* 18: TIM7_IRQHandler                                                  */
    TIM14_IRQn                  = 19,      /* 19: TIM14_IRQHandler                                                 */
    TIM15_IRQn                  = 20,      /* 20: TIM15_IRQHandler                                                 */
    TIM16_IRQn                  = 21,      /* 21: TIM16_IRQHandler                                                 */
    TIM17_IRQn                  = 22,      /* 22: TIM17_IRQHandler                                                 */
    I2C1_IRQn                   = 23,      /* 23: I2C1_IRQHandler                                                  */
    I2C2_IRQn                   = 24,      /* 24: I2C2_IRQHandler                                                  */
    SPI1_IRQn                   = 25,      /* 25: SPI1_IRQHandler                                                  */
    SPI2_IRQn                   = 26,      /* 26: SPI2_IRQHandler                                                  */
    UART1_IRQn                  = 27,      /* 27: UART1_IRQHandler                                                 */
    UART2_IRQn                  = 28,      /* 28: UART2_IRQHandler                                                 */
    LPUART_IRQn                 = 29,      /* 29: LPUART_IRQHandler                                                */
    SPI3_IRQn                   = 30,      /* 30: SPI3_IRQHandler                                                  */
    AES_IRQn                    = 31,      /* 31: AES_IRQHandler                                                   */
    USB_IRQn                    = 32,      /* 32: USB_IRQHandler                                                   */
    DAC_IRQn                    = 33,      /* 33: DAC_IRQHandler                                                   */
    I2S_IRQn                    = 34,      /* 34: I2S_IRQHandler                                                   */
    GPIOEF_IRQ                  = 35,      /* 35: GPIOEF_IRQHandler                                                */
    CAN1_IRQn                   = 36,      /* 36: CAN1_IRQHandler                                                  */
    CAN2_IRQn                   = 37,      /* 37: CAN2_IRQHandler                                                  */
    FPU_IRQn                    = 38,      /* 38: FPU_IRQHandler                                                   */
    TIM4_IRQn                   = 39,      /* 39: TIM4_IRQHandler                                                  */
    SPI4_IRQn                   = 40,      /* 40: SPI4_IRQHandler                                                  */
} IRQn_Type;

/* ================================================================================ */
/* ================      Processor and Core Peripheral Section     ================ */
/* ================================================================================ */

/* Configuration of the Cortex-M33 Processor and Core Peripherals */
#define __MPU_PRESENT           1       /*!< mcu does not provide a MPU present or not       */
#define __NVIC_PRIO_BITS        3       /*!< mcu Supports 3 Bits for the Priority Levels     */
#define __Vendor_SysTickConfig  0       /*!< Set to 1 if different SysTick Config is used         */  

#define   ARM_MATH_CM4          1 
#define __TARGET_FPU_VFP        1 
#define __FPU_PRESENT           1 
#define __DSP_PRESENT           1 
#define __ARM_COMPAT_H          1 
#define __ACCELERATE_PRESENT    1  
#define __ACCELERATE_EH_PRESENT 0         

#include "core_cm33.h"         /* Processor and core peripherals */

#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"
#include "string.h"

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
    __IO uint32_t CTRL;
    __IO uint32_t SEC;
    __IO uint32_t ADCT;
    __IO uint32_t TERASE;
    __IO uint32_t TPROG;
    __IO uint32_t STATUS;
    __IO uint32_t INTSTATUS;
    __IO uint32_t INTEN;
    __IO uint32_t CONFIG;
    __IO uint32_t EDCTRL;
    __IO uint32_t RDN0;
    __IO uint32_t RDN1;
    __IO uint32_t RDN2;
    __IO uint32_t RDN3;
    __IO uint32_t TNVS;
    __IO uint32_t TMODE_SEC;
    __IO uint32_t TDOUT;
    __IO uint32_t TDIN;
    __IO uint32_t TCTRL;
}EFC_TypeDef;


///*------------------- Timer Registers ----------------------*/
typedef struct
{
    __IO uint32_t CR1;
    __IO uint32_t CR2;
    __IO uint32_t SMCR;
    __IO uint32_t DIER;
    __IO uint32_t SR;
    __IO uint32_t EGR;
    __IO uint32_t CCMR1;
    __IO uint32_t CCMR2;
    __IO uint32_t CCER;
    __IO uint32_t CNT;
    __IO uint32_t PSC;
    __IO uint32_t ARR;
    __IO uint32_t RCR;
    __IO uint32_t CCR1;
    __IO uint32_t CCR2;
    __IO uint32_t CCR3;
    __IO uint32_t CCR4;
    __IO uint32_t BDTR;
    __IO uint32_t DCR;
    __IO uint32_t DMAR;
    __IO uint32_t RSV0[4];
    __IO uint32_t AF1;
    __IO uint32_t RSV1;
    __IO uint32_t TISEL;
    __IO uint32_t DBER;
}TIM_TypeDef;


///*------------------- RTC¡¢PMU Registers ----------------------*/
typedef struct
{
    __IO uint32_t WP;
    __IO uint32_t IE;
    __IO uint32_t SR;
    __IO uint32_t SEC;
    __IO uint32_t MIN;
    __IO uint32_t HOUR;
    __IO uint32_t DATE;
    __IO uint32_t WEEK;
    __IO uint32_t MONTH;
    __IO uint32_t YEAR;
    __IO uint32_t ALM;
    __IO uint32_t CR;
    __IO uint32_t ADJUST;
    __IO uint32_t RSV0[4];
    __IO uint32_t CLKSTAMP1_TIME;
    __IO uint32_t CALSTAMP1_DATE;
    __IO uint32_t CLKSTAMP2_TIME;
    __IO uint32_t CALSTAMP2_DATE;
    __IO uint32_t RSV2[7];
    __IO uint32_t BAKUP[5];
}RTC_TypeDef;

typedef struct
{
    __IO uint32_t CR1;
    __IO uint32_t SR;
    __IO uint32_t IOSEL;
    __IO uint32_t IOCR;
    __IO uint32_t ANACR;
    __IO uint32_t CR2;
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
    __IO uint32_t CMDR;
    __IO uint32_t PR;
    __IO uint32_t RLR;
    __IO uint32_t SR;
    __IO uint32_t WINR;
    __IO uint32_t WUTR;
}IWDT_TypeDef;


///*------------------- UART Registers ----------------------*/
typedef struct
{
    __IO uint32_t DR;
    __IO uint32_t RSR;
    __IO uint32_t RSV0[4];
    __IO uint32_t FR;
    __IO uint32_t RSV1;
    __IO uint32_t ILPR;
    __IO uint32_t IBRD;
    __IO uint32_t FBRD;
    __IO uint32_t LCRH;
    __IO uint32_t CR;
    __IO uint32_t IFLS;
    __IO uint32_t IE;
    __IO uint32_t RIS;
    __IO uint32_t MIS;
    __IO uint32_t ICR;
    __IO uint32_t DMACR;
    __IO uint32_t RSV2[2];
    __IO uint32_t CR2;
    __IO uint32_t BCNT;
}UART_TypeDef;


///*------------------- I2C Registers ----------------------*/
typedef struct
{
    __IO uint32_t SLAVE_ADDR1;
    __IO uint32_t CLK_DIV;
    __IO uint32_t CR;
    __IO uint32_t SR;
    __IO uint32_t DR;
    __IO uint32_t SLAVE_ADDR2_3;
    __IO uint32_t RSV[3];
    __IO uint32_t TIMEOUT;
}I2C_TypeDef;


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


///*------------------- DAC Registers ----------------------*/
typedef struct
{
    __IO uint32_t CR;
    __IO uint32_t SWTRIGR;
    __IO uint32_t DHR12R1;
    __IO uint32_t DHR12L1;
    __IO uint32_t DHR8R1;
    __IO uint32_t DHR12R2;
    __IO uint32_t DHR12L2;
    __IO uint32_t DHR8R2;
    __IO uint32_t DHR12RD;
    __IO uint32_t DHR12LD;
    __IO uint32_t DHR8RD;
    __IO uint32_t DOR1;
    __IO uint32_t DOR2;
    __IO uint32_t SR;
    __IO uint32_t CCR;
    __IO uint32_t MCR;
    __IO uint32_t SHSR1;
    __IO uint32_t SHSR2;
    __IO uint32_t SHHR;
    __IO uint32_t SHRR;
}DAC_TypeDef;


///*------------------- LPUART Registers ----------------------*/
typedef struct
{
    __IO uint32_t RXDR;
    __IO uint32_t TXDR;
    __IO uint32_t LCR;
    __IO uint32_t CR;
    __IO uint32_t IBAUD;
    __IO uint32_t FBAUD;
    __IO uint32_t IE;
    __IO uint32_t SR;
    __IO uint32_t ADDR;
}LPUART_TypeDef;


///*------------------- COMP Registers ----------------------*/
typedef struct
{
    __IO uint32_t CR1;
    __IO uint32_t CR2;
    __IO uint32_t SR;
}COMP_TypeDef;


///*------------------- OPA Registers ----------------------*/
typedef struct
{
    __IO uint32_t OPA1_CSR;
    __IO uint32_t OPA2_CSR;
    __IO uint32_t OPA3_CSR;
}OPA_TypeDef;


///*------------------- EXTI Registers ----------------------*/
typedef struct
{
    __IO uint32_t IENR;
    __IO uint32_t EENR;
    __IO uint32_t RTENR;
    __IO uint32_t FTENR;
    __IO uint32_t SWIER;
    __IO uint32_t PDR;
    __IO uint32_t EXTICR1;
    __IO uint32_t EXTICR2;
}EXTI_TypeDef;


///*------------------- SCU Registers ----------------------*/
typedef struct
{
    __IO uint32_t RCR;
    __IO uint32_t RSR;
    __IO uint32_t IPRST2;
    __IO uint32_t IPRST1;
    __IO uint32_t CCR1;
    __IO uint32_t CCR2;
    __IO uint32_t CIR;
    __IO uint32_t IPCKENR1;
    __IO uint32_t IPCKENR2;
    __IO uint32_t RCHCR;
    __IO uint32_t XTHCR;
    __IO uint32_t PLLCR;
    __IO uint32_t LDOCR;
    __IO uint32_t RSV0;
    __IO uint32_t WMR;
    __IO uint32_t CLKOCR;
    __IO uint32_t VER;
    __IO uint32_t SYSCFG1;
    __IO uint32_t LVDCFG;
    __IO uint32_t STOPCFG;
    __IO uint32_t RSV1;
    __IO uint32_t PHYCR;
    __IO uint32_t MEMCFG;
    __IO uint32_t DUMMY;
    __IO uint32_t PASEL1;
    __IO uint32_t PASEL2;
    __IO uint32_t PBSEL1;
    __IO uint32_t PBSEL2;
    __IO uint32_t PABPUR;
    __IO uint32_t PABPDR;
    __IO uint32_t PASTR;
    __IO uint32_t PBSTR;
    __IO uint32_t PABSMTR;
    __IO uint32_t PABODR;
    __IO uint32_t PABADS;
    __IO uint32_t RSV2;
    __IO uint32_t PCSEL1;
    __IO uint32_t PCSEL2;
    __IO uint32_t PDSEL1;
    __IO uint32_t PDSEL2;
    __IO uint32_t PCDPUR;
    __IO uint32_t PCDPDR;
    __IO uint32_t PCSTR;
    __IO uint32_t PDSTR;
    __IO uint32_t PCDSMTR;
    __IO uint32_t PCDODR;
    __IO uint32_t PCDADS;
    __IO uint32_t RSV3;
    __IO uint32_t PESEL1;
    __IO uint32_t PESEL2;
    __IO uint32_t PFSEL1;
    __IO uint32_t RSV4;
    __IO uint32_t PEFPUR;
    __IO uint32_t PEFPDR;
    __IO uint32_t PESTR;
    __IO uint32_t PFSTR;
    __IO uint32_t PEFSMTR;
    __IO uint32_t PEFODR;
    __IO uint32_t PEFADS;
}SCU_TypeDef;


///*------------------- CRC Registers ----------------------*/
typedef struct
{
    __IO uint32_t DATA;
    __IO uint32_t CTRL;
    __IO uint32_t INIT;
    __IO uint32_t RSV0;
    __IO uint32_t OUTXOR;
    __IO uint32_t POLY;
    __IO uint32_t FDATA;
}CRC_TypeDef;


///*------------------- ADC Registers ----------------------*/
typedef struct
{
    __IO uint32_t SR;
    __IO uint32_t IE;
    __IO uint32_t CR1;
    __IO uint32_t CR2;
    __IO uint32_t SMPR1;
    __IO uint32_t SMPR2;
    __IO uint32_t HTR;
    __IO uint32_t LTR;
    __IO uint32_t SQR1;
    __IO uint32_t SQR2;
    __IO uint32_t SQR3;
    __IO uint32_t JSQR;
    __IO uint32_t JDR;
    __IO uint32_t DR;
    __IO uint32_t DIFF;
    __IO uint32_t SIGN;
    __IO uint32_t TSREF;
    __IO uint32_t SMPR3;
}ADC_TypeDef;


///*------------------- I2S Registers ----------------------*/
typedef struct
{
    __IO uint32_t DAT;
    __IO uint32_t CTL;
    __IO uint32_t PSC;
    __IO uint32_t IE;
    __IO uint32_t STATUS;
}I2S_TypeDef;


///*------------------- GPIO Registers ----------------------*/
typedef struct
{
    __IO uint32_t DIR;
    __IO uint32_t RSV0; 
    __IO uint32_t SET;
    __IO uint32_t CLR;
    __IO uint32_t ODATA;
    __IO uint32_t IDATA;
    __IO uint32_t IEN;
    __IO uint32_t IS;
    __IO uint32_t IBE;
    __IO uint32_t IEV;
    __IO uint32_t IC;
    __IO uint32_t RIS;
    __IO uint32_t MIS;
}GPIO_TypeDef;


///*------------------- SPI Registers ----------------------*/
typedef struct
{
    __IO uint32_t DAT;
    __IO uint32_t BAUD;
    __IO uint32_t CTL;
    __IO uint32_t TX_CTL;
    __IO uint32_t RX_CTL;
    __IO uint32_t IE;
    __IO uint32_t STATUS;
    __IO uint32_t TX_DELAY;
    __IO uint32_t BATCH;
    __IO uint32_t CS;
    __IO uint32_t OUT_EN;
    __IO uint32_t MEMO_ACC;
    __IO uint32_t CMD;
    __IO uint32_t PARA;
}SPI_TypeDef;


///*------------------- DMA Registers ----------------------*/
typedef struct
{
    __IO uint32_t INT_STATUS;
    __IO uint32_t INT_TC_STATUS;
    __IO uint32_t INT_TC_CLR;
    __IO uint32_t INT_ERR_STATUS;
    __IO uint32_t INT_ERR_CLR;
    __IO uint32_t RAW_INT_TC_STATUS;
    __IO uint32_t RAW_INT_ERR_STATUS;
    __IO uint32_t EN_CH_STATUS;
    __IO uint32_t RSV0[4];
    __IO uint32_t CONFIG;
    __IO uint32_t SYNCLO;
    __IO uint32_t SYNCHI;
}DMA_TypeDef;

typedef struct
{
    __IO uint32_t SRC_ADDR;
    __IO uint32_t DEST_ADDR;
    __IO uint32_t LLI;
    __IO uint32_t CTRL;
    __IO uint32_t CONFIG;
}DMA_Channel_TypeDef;


///*------------------- AES Registers ----------------------*/
typedef struct
{
    __IO uint32_t DATAIN;
    __IO uint32_t KEYIN;
    __IO uint32_t RSV0;
    __IO uint32_t CONTROL;
    __IO uint32_t STATE;
    __IO uint32_t DATAOUT;
}AES_TypeDef;


///*------------------- FAU Registers ----------------------*/
typedef struct
{
	__IO uint32_t CTRL1;            //0x00
	__IO uint32_t STAUTS;           //0x04

	__IO uint32_t CORDIC_X_DATAIN;  //0x08  
	__IO uint32_t CORDIC_Y_DATAIN;  //0x0c	
	__IO uint32_t RESULT1;          //0x10  
	__IO uint32_t RESULT2;          //0x14  
}FAU_TypeDef;


///*------------------- HRNG Registers ----------------------*/
typedef struct
{
    __IO uint32_t CTRL;
    __IO uint32_t LFSR;
}HRNG_TypeDef;


///*------------------- HASH Registers ----------------------*/
typedef struct
{
    __IO uint32_t DATAIN;
    __IO uint32_t MIDDATA;
    __IO uint32_t CTRL;
    __IO uint32_t DATAOUT;
}HASH_TypeDef;


///*------------------- USB Registers ----------------------*/
typedef struct
{
    __IO uint32_t WORKING_MODE;
    __IO uint32_t EPxCSR[5]; 
    __IO uint32_t USB_ADDR;
    __IO uint32_t SETIP_0_3_DATA;
    __IO uint32_t SETIP_4_7_DATA;
    __IO uint32_t EPADDR_CFG;
    __IO uint32_t CURRENT_PID;
    __IO uint32_t CURRENT_FRAME_NUMBER;
    __IO uint32_t CRC_ERROR_CNT;
    __IO uint32_t USB_STATUS_DETECT_CNT;
    __IO uint32_t RSV0;
    __IO uint32_t RSV1;
    __IO uint32_t EPxSENDBN[5];
}USB_CTRLTypeDef;

///*------------------- USB interrupt access Registers ----------------------*/
typedef struct
{
    __IO uint32_t INT_STAT_RAW;    
    __IO uint32_t INT_EN;  
    __IO uint32_t RSV;  
    __IO uint32_t INT_CLR;       
}USB_INTTypeDef;  

/**
  * @}
  */



/** @addtogroup Peripheral_memory_map
  * @{
  */

///*------------------- Peripheral memory map ----------------------*/
#define EFLASH_BASE        (0x00000000UL)
#define SRAM_BASE          (0x20000000UL)
#define PERIPH_BASE        (0x40000000UL)
#define QSPI_BASE          (0x90000000UL)

#define APB1PERIPH_BASE       (PERIPH_BASE)
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x00010000UL)
#define AHBPERIPH_BASE        (PERIPH_BASE + 0x00020000UL)

///*---------------------- EFC peripherals ------------------------*/
#define EFLASH_REG_BASE   (EFLASH_BASE + 0x00100000)

///*---------------------- APB1 peripherals ------------------------*/
#define TIM2_BASE         (APB1PERIPH_BASE + 0x00000000UL) 
#define TIM3_BASE         (APB1PERIPH_BASE + 0x00000400UL) 
#define TIM4_BASE         (APB1PERIPH_BASE + 0x00000800UL) 
#define TIM6_BASE         (APB1PERIPH_BASE + 0x00001000UL) 
#define TIM7_BASE         (APB1PERIPH_BASE + 0x00001400UL) 
#define TIM14_BASE        (APB1PERIPH_BASE + 0x00002000UL) 
#define PMU_BASE          (APB1PERIPH_BASE + 0x00002400UL) 
#define RTC_BASE          (APB1PERIPH_BASE + 0x00002800UL) 
#define WDT_BASE          (APB1PERIPH_BASE + 0x00002C00UL) 
#define IWDT_BASE         (APB1PERIPH_BASE + 0x00003000UL) 
#define UART2_BASE        (APB1PERIPH_BASE + 0x00004400UL) 
#define UART3_BASE        (APB1PERIPH_BASE + 0x00004800UL) 
#define UART4_BASE        (APB1PERIPH_BASE + 0x00004C00UL) 
#define I2C1_BASE         (APB1PERIPH_BASE + 0x00005400UL) 
#define I2C2_BASE         (APB1PERIPH_BASE + 0x00005800UL) 
#define CAN1_BASE         (APB1PERIPH_BASE + 0x00006400UL) 
#define CAN2_BASE         (APB1PERIPH_BASE + 0x00006800UL) 
#define DAC_BASE          (APB1PERIPH_BASE + 0x00007400UL) 
#define LPUART_BASE       (APB1PERIPH_BASE + 0x00008000UL) 

///*---------------------- APB2 peripherals ------------------------*/
#define COMP_BASE         (APB2PERIPH_BASE + 0x00000200UL) 
#define OPA_BASE          (APB2PERIPH_BASE + 0x00000300UL) 
#define EXTI_BASE         (APB2PERIPH_BASE + 0x00000400UL) 
#define SCU_BASE          (APB2PERIPH_BASE + 0x00000800UL) 
#define CRC_BASE          (APB2PERIPH_BASE + 0x00000C00UL) 
#define ADC_BASE          (APB2PERIPH_BASE + 0x00002400UL) 
#define TIM1_BASE         (APB2PERIPH_BASE + 0x00002C00UL) 
#define I2S1_BASE         (APB2PERIPH_BASE + 0x00003000UL) 
#define UART1_BASE        (APB2PERIPH_BASE + 0x00003800UL) 
#define TIM15_BASE        (APB2PERIPH_BASE + 0x00004000UL) 
#define TIM16_BASE        (APB2PERIPH_BASE + 0x00004400UL) 
#define TIM17_BASE        (APB2PERIPH_BASE + 0x00004800UL) 
#define GPIOAB_BASE       (APB2PERIPH_BASE + 0x0000F000UL) 
#define GPIOCD_BASE       (APB2PERIPH_BASE + 0x0000F400UL) 
#define GPIOEF_BASE       (APB2PERIPH_BASE + 0x0000F800UL) 

///*---------------------- AHB peripherals ------------------------*/
#define SPI1_BASE            (AHBPERIPH_BASE)
#define SPI2_BASE            (AHBPERIPH_BASE + 0x00000400UL)
#define SPI3_BASE            (AHBPERIPH_BASE + 0x00000800UL)
#define SPI4_BASE            (AHBPERIPH_BASE + 0x00000C00UL)
#define DMA_BASE             (AHBPERIPH_BASE + 0x00001000UL)
#define DMA_Channel0_BASE    (AHBPERIPH_BASE + 0x00001100UL)
#define DMA_Channel1_BASE    (AHBPERIPH_BASE + 0x00001120UL)
#define DMA_Channel2_BASE    (AHBPERIPH_BASE + 0x00001140UL)
#define DMA_Channel3_BASE    (AHBPERIPH_BASE + 0x00001160UL)
#define DMA_Channel4_BASE    (AHBPERIPH_BASE + 0x00001180UL)
#define DMA_Channel5_BASE    (AHBPERIPH_BASE + 0x000011A0UL)
#define DMA_Channel6_BASE    (AHBPERIPH_BASE + 0x000011C0UL)
#define DMA_Channel7_BASE    (AHBPERIPH_BASE + 0x000011E0UL)
#define AES_BASE             (AHBPERIPH_BASE + 0x00010000UL)
#define FAU_BASE             (AHBPERIPH_BASE + 0x00010400UL)
#define HRNG_BASE            (AHBPERIPH_BASE + 0x00010800UL)
#define HASH_BASE            (AHBPERIPH_BASE + 0x00010C00UL)
#define USB_BASE             (AHBPERIPH_BASE + 0x00020000UL)   

///*---------------------- QSPI Memory ------------------------*/
#define QSPI3_BASE           (QSPI_BASE)

/**
  * @}
  */



/** @addtogroup Peripheral_declaration
  * @{
  */  
#define EFC                 ((EFC_TypeDef *)EFLASH_REG_BASE)
#define TIM2                ((TIM_TypeDef *)TIM2_BASE)
#define TIM3                ((TIM_TypeDef *)TIM3_BASE)
#define TIM4                ((TIM_TypeDef *)TIM4_BASE)
#define TIM6                ((TIM_TypeDef *)TIM6_BASE)
#define TIM7                ((TIM_TypeDef *)TIM7_BASE)
#define TIM14               ((TIM_TypeDef *)TIM14_BASE)
#define PMU                 ((PMU_TypeDef *)PMU_BASE)
#define RTC                 ((RTC_TypeDef *)RTC_BASE)
#define WDT                 ((WDT_TypeDef *)WDT_BASE)
#define IWDT                ((IWDT_TypeDef *)IWDT_BASE)
#define UART2               ((UART_TypeDef *)UART2_BASE)
#define UART3               ((UART_TypeDef *)UART3_BASE)
#define UART4               ((UART_TypeDef *)UART4_BASE)
#define I2C1                ((I2C_TypeDef *)I2C1_BASE)
#define I2C2                ((I2C_TypeDef *)I2C2_BASE)
#define CAN1                ((CAN_TypeDef *)CAN1_BASE)
#define CAN2                ((CAN_TypeDef *)CAN2_BASE)
#define DAC                 ((DAC_TypeDef *)DAC_BASE)
#define LPUART              ((LPUART_TypeDef *)LPUART_BASE)
#define COMP                ((COMP_TypeDef *)COMP_BASE)
#define OPA                 ((OPA_TypeDef *)OPA_BASE)
#define EXTI                ((EXTI_TypeDef *)EXTI_BASE)
#define SCU                 ((SCU_TypeDef *)SCU_BASE)
#define CRC                 ((CRC_TypeDef *)CRC_BASE)
#define ADC                 ((ADC_TypeDef *)ADC_BASE)
#define TIM1                ((TIM_TypeDef *)TIM1_BASE)
#define I2S1                ((I2S_TypeDef *)I2S1_BASE)
#define UART1               ((UART_TypeDef *)UART1_BASE)
#define TIM15               ((TIM_TypeDef *)TIM15_BASE)
#define TIM16               ((TIM_TypeDef *)TIM16_BASE) 
#define TIM17               ((TIM_TypeDef *)TIM17_BASE)    
#define GPIOAB              ((GPIO_TypeDef *)GPIOAB_BASE)
#define GPIOCD              ((GPIO_TypeDef *)GPIOCD_BASE)
#define GPIOEF              ((GPIO_TypeDef *)GPIOEF_BASE)
#define SPI1                ((SPI_TypeDef *)SPI1_BASE)
#define SPI2                ((SPI_TypeDef *)SPI2_BASE)
#define SPI3                ((SPI_TypeDef *)SPI3_BASE)
#define SPI4                ((SPI_TypeDef *)SPI4_BASE)
#define DMA                 ((DMA_TypeDef *)DMA_BASE)
#define DMA_Channel0        ((DMA_Channel_TypeDef *)DMA_Channel0_BASE)
#define DMA_Channel1        ((DMA_Channel_TypeDef *)DMA_Channel1_BASE)
#define DMA_Channel2        ((DMA_Channel_TypeDef *)DMA_Channel2_BASE)
#define DMA_Channel3        ((DMA_Channel_TypeDef *)DMA_Channel3_BASE)
#define DMA_Channel4        ((DMA_Channel_TypeDef *)DMA_Channel4_BASE)
#define DMA_Channel5        ((DMA_Channel_TypeDef *)DMA_Channel5_BASE)
#define DMA_Channel6        ((DMA_Channel_TypeDef *)DMA_Channel6_BASE)
#define DMA_Channel7        ((DMA_Channel_TypeDef *)DMA_Channel7_BASE)
#define AES                 ((AES_TypeDef *)AES_BASE)
#define FAU                 ((FAU_TypeDef *)FAU_BASE)
#define HRNG                ((HRNG_TypeDef *)HRNG_BASE)
#define HASH                ((HASH_TypeDef *)HASH_BASE)
#define USBCTRL             ((USB_CTRLTypeDef *)USB_BASE)
#define USBINT              ((USB_INTTypeDef *)(USB_BASE+0xFFE4))
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

typedef   signed           char INT8;
typedef   signed short     int  INT16;
typedef   signed           int  INT32;

    /* exact-width unsigned integer types */
typedef unsigned           char UINT8;
typedef unsigned short     int  UINT16;
typedef unsigned           int  UINT32;  

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif  /* ACM32F4_H */
