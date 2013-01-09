/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright (c) Nuvoton Technology Corp. All rights reserved.                                             */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

#ifndef __NUC1xx_H__
#define __NUC1xx_H__


/*
 * ==========================================================================
 * ---------- Interrupt Number Definition -----------------------------------
 * ==========================================================================
 */
 
typedef enum IRQn
{
/******  Cortex-M0 Processor Exceptions Numbers ***************************************************/
  NonMaskableInt_IRQn         = -14,    /*!< 2 Non Maskable Interrupt                             */
  HardFault_IRQn		      = -13,    /*!< 3 Cortex-M0 Hard Fault Interrupt                     */
  SVCall_IRQn                 = -5,     /*!< 11 Cortex-M0 SV Call Interrupt                       */
  PendSV_IRQn                 = -2,     /*!< 14 Cortex-M0 Pend SV Interrupt                       */
  SysTick_IRQn                = -1,     /*!< 15 Cortex-M0 System Tick Interrupt                   */

/******  ARMIKMCU Swift specific Interrupt Numbers ************************************************/
  BOD_IRQn                  = 0,
  WDT_IRQn                  = 1,
  EINT0_IRQn                = 2,
  EINT1_IRQn                = 3,
  GPAB_IRQn                 = 4,
  GPCDE_IRQn                = 5,
  PWMA_IRQn                 = 6,
  PWMB_IRQn                 = 7,
  TMR0_IRQn                 = 8,
  TMR1_IRQn                 = 9,
  TMR2_IRQn                 = 10,
  TMR3_IRQn                 = 11,
  UART0_IRQn                = 12,
  UART1_IRQn                = 13,
  SPI0_IRQn                 = 14,
  SPI1_IRQn                 = 15,
  SPI2_IRQn                 = 16,
  SPI3_IRQn                 = 17,
  I2C0_IRQn                 = 18,
  I2C1_IRQn                 = 19,
  CAN0_IRQn                 = 20,
  CAN1_IRQn                 = 21,
  SD_IRQn                   = 22,
  USBD_IRQn                 = 23,
  PS2_IRQn                  = 24,
  ACMP_IRQn                 = 25,
  PDMA_IRQn                 = 26,
  I2S_IRQn                  = 27,
  PWRWU_IRQn                = 28,
  ADC_IRQn                  = 29,
  DAC_IRQn                  = 30,
  RTC_IRQn                  = 31
         
                                        /*!< maximum of 32 Interrupts are possible                */
} IRQn_Type;


/*
 * ==========================================================================
 * ----------- Processor and Core Peripheral Section ------------------------
 * ==========================================================================
 */

/* Configuration of the Cortex-M0 Processor and Core Peripherals */
#define __MPU_PRESENT           0       /*!< armikcmu does not provide a MPU present or not       */
#define __NVIC_PRIO_BITS        2       /*!< armikcmu Supports 2 Bits for the Priority Levels     */
#define __Vendor_SysTickConfig  0       /*!< Set to 1 if different SysTick Config is used         */


#include "core_cm0.h"                   /* Cortex-M0 processor and core peripherals               */
#include "system_NUC1xx.h"              /* NUC1xx System                                          */
// #include "System\SysInfra.h"    


/**
 * Initialize the system clock
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system
 *         Initialize the PLL and update the SystemFrequency variable
 */
extern void SystemInit (void);


/******************************************************************************/
/*                Device Specific Peripheral registers structures             */
/******************************************************************************/

/*--------------------- General Purpose Input and Ouptut ---------------------*/
typedef struct
{
    __IO uint32_t PMD0:2;
    __IO uint32_t PMD1:2;
    __IO uint32_t PMD2:2;
    __IO uint32_t PMD3:2;
    __IO uint32_t PMD4:2;
    __IO uint32_t PMD5:2;
    __IO uint32_t PMD6:2;
    __IO uint32_t PMD7:2;
    __IO uint32_t PMD8:2;
    __IO uint32_t PMD9:2;
    __IO uint32_t PMD10:2;
    __IO uint32_t PMD11:2;
    __IO uint32_t PMD12:2;
    __IO uint32_t PMD13:2;
    __IO uint32_t PMD14:2;
    __IO uint32_t PMD15:2;
} GPIO_PMD_T;

typedef __IO uint32_t GPIO_SCH_T;

typedef __IO uint32_t GPIO_DOUT_T;

typedef __IO uint32_t GPIO_DMASK_T;

typedef __IO uint32_t GPIO_PIN_T;

typedef __IO uint32_t GPIO_DBEN_T;

typedef __IO uint32_t GPIO_IMD_T;

typedef __IO uint32_t GPIO_IEN_T;

typedef __IO uint32_t GPIO_ISRC_T;

typedef struct
{
    __IO uint32_t  DBCLKSEL:4;
    __IO uint32_t  DBCLKSRC:1;
    __IO uint32_t  ICLK_ON:1;
    __I  uint32_t  RESERVE:26;    
} GPIO_DBNCECON_T;

typedef struct
{
    GPIO_PMD_T      PMD;
    GPIO_SCH_T      SCH;
    GPIO_DOUT_T     DOUT;
    GPIO_DMASK_T    DMASK;
    GPIO_PIN_T      PIN;
    GPIO_DBEN_T     DBEN;
    GPIO_IMD_T      IMD;
    GPIO_IEN_T      IEN;
    GPIO_ISRC_T     ISRC;
    
} GPIO_T;


/*------------------------- UART Interface Controller ------------------------*/

typedef __IO uint32_t UART_DATA_T;


typedef struct
{
    __IO uint32_t  RDA_IEN:1;
    __IO uint32_t  THRE_IEN:1;
    __IO uint32_t  RLS_IEN:1;
    __IO uint32_t  MS_IEN:1;
    __IO uint32_t  RTO_IEN:1;	  
    __IO uint32_t  BUF_ERR_IEN:1;
    __IO uint32_t  WAKE_IEN:1;
    __I  uint32_t  RESERVE0:4;
    __IO uint32_t  TOC_EN:1;      /* Time-out counter enable */
    __IO uint32_t  AUTO_RTS_EN:1;
    __IO uint32_t  AUTO_CTS_EN:1;
    __IO uint32_t  DMA_TX_EN:1;
    __IO uint32_t  DMA_RX_EN:1;
    __I  uint32_t  RESERVE1:15;    
    __IO uint32_t  nDEBUGACK_EN:1;
} UART_IER_T;

typedef struct
{
    __I  uint32_t  RESERVE0:1;
    __IO uint32_t  RFR:1;
    __IO uint32_t  TFR:1;
    __I  uint32_t  RESERVE1:1;
    __IO uint32_t  RFITL:4;             /* Rx FIFO Interrupt Trigger Level */
    __I  uint32_t  RESERVE2:8;
    __IO uint32_t  RTS_TRIG_LEVEL:4;
    __I  uint32_t  RESERVE3:12;
} UART_FCR_T;

typedef struct
{
    __IO uint32_t  WLS:2;               /* Word length select */
    __IO uint32_t  NSB:1;               /* Number of STOP bit */
    __IO uint32_t  PBE:1;               /* Parity bit enable  */
    __IO uint32_t  EPE:1;               /* Even parity enable */
    __IO uint32_t  SPE:1;               /* Stick parity enable*/
    __IO uint32_t  BCB:1;               /* Break control bit  */
    __I  uint32_t  RESERVE:25;
} UART_LCR_T;

typedef struct
{
    __I  uint32_t  RESERVE0:1;
    __IO uint32_t  RTS_INV:1;
    __I  uint32_t  RESERVE1:2;
    __IO uint32_t  LBME:1;
    __I  uint32_t  RESERVE2:4;
    __IO uint32_t  RTS_ACT_LEVEL:1;
    __I  uint32_t  RESERVE3:3;
    __I  uint32_t  RTS:1;               /* RTS status */
    __I  uint32_t  RESERVE4:18;
} UART_MCR_T;

typedef struct
{
    __IO uint32_t  DCTS:1;
    __I  uint32_t  RESERVE0:3;
    __I  uint32_t  CTS:1;               /* CTS status */
    __I  uint32_t  RESERVE1:3;
    __IO uint32_t  CTS_ACT_LEVEL:1;
    __I  uint32_t  RESERVE2:23;
} UART_MSR_T;

typedef struct
{
    __IO uint32_t  RX_OVERFLOW:1;
    __I  uint32_t  RESERVE0:3;
    __IO uint32_t  PEI:1;
    __IO uint32_t  FEI:1;
    __IO uint32_t  BII:1;
    __I  uint32_t  RESERVE1:1;
    __I  uint32_t  RX_POINTER:6;
    __I  uint32_t  RX_EMPTY:1;
    __I  uint32_t  RX_FULL:1;
    __I  uint32_t  TX_POINTER:6;
    __I  uint32_t  TX_EMPTY:1;
    __I  uint32_t  TX_FULL:1;
    __IO uint32_t  TX_OVERFLOW:1;
    __I  uint32_t  RESERVE2:3;
    __I  uint32_t  TE:1;                /* Transmitter empty flag */
    __I  uint32_t  RESERVE3:3;
} UART_FSR_T;

typedef struct
{
    __IO uint32_t  RDA_IF:1;
    __IO uint32_t  THRE_IF:1;
    __IO uint32_t  RLS_IF:1;
    __IO uint32_t  MODEM_IF:1;
    __IO uint32_t  TOUT_IF:1;
    __IO uint32_t  BUF_ERR_IF:1;
    __IO uint32_t  WAKE_IF:1;
    __IO uint32_t  SW_TX:1;
    __IO uint32_t  RDA_INT:1;
    __IO uint32_t  THRE_INT:1;
    __IO uint32_t  RLS_INT:1;
    __IO uint32_t  MODEM_INT:1;
    __IO uint32_t  TOUT_INT:1;
    __IO uint32_t  BUF_ERR_INT:1;
    __IO uint32_t  WAKE_INT:1;
    __IO uint32_t  SW_RX:1;
    __I  uint32_t  RESERVE0:2;
    __IO uint32_t  HW_RLS_IF:1;
    __IO uint32_t  HW_MODEM_IF:1;
    __IO uint32_t  HW_TOUT_IF:1;
    __IO uint32_t  HW_BUF_ERR_IF:1;
    __IO uint32_t  HW_WAKE_IF:1;
    __IO uint32_t  EDMA_TX:1;
    __I  uint32_t  RESERVE1:2;
    __IO uint32_t  HW_RLS_INT:1;
    __IO uint32_t  HW_MODEM_INT:1;
    __IO uint32_t  HW_TOUT_INT:1;
    __IO uint32_t  HW_BUF_ERR_INT:1;
    __IO uint32_t  HW_WAKE_INT:1;
    __IO uint32_t  EDMA_RX:1;
} UART_ISR_T;

typedef __IO uint32_t UART_TOR_T;

typedef struct
{
    __IO uint32_t  DIV:16;
    __I  uint32_t  RESERVE0:8;
    __IO uint32_t  DIVX:4;
    __IO uint32_t  DIVX1:1;            
    __IO uint32_t  DIVX_EN:1;            
    __I  uint32_t  RESERVE1:2;
} UART_BAUD_T;

typedef struct
{
    __IO uint32_t  IrDA_EN:1;
    __I  uint32_t  RESERVE0:2;
    __IO uint32_t  RX_EN:1;
    __IO uint32_t  TX_EN:1;            
    __IO uint32_t  TX_INV_EN:1;            
    __IO uint32_t  RX_INV_EN:1;
    __I  uint32_t  RESERVE1:25;
} UART_IRCR_T;

typedef struct
{
    __IO uint32_t  LINBCNT:4;
    __I  uint32_t  RESERVE0:2;
    __IO uint32_t  LINRX_EN:1;
    __IO uint32_t  LINTX_EN:1;            
    __I  uint32_t  RESERVE1:24;
} UART_LINCON_T;



typedef struct
{
    __IO uint32_t  LIN_EN:2;
	__IO uint32_t  IrDA_EN:2;
    __I  uint32_t  RESERVE0:32;

} UART_FUNSEL_T;


typedef struct
{
    UART_DATA_T     DATA;
    UART_IER_T      IER;
    UART_FCR_T      FCR;
    UART_LCR_T      LCR;
    UART_MCR_T      MCR;
    UART_MSR_T      MSR;
    UART_FSR_T      FSR;
    UART_ISR_T      ISR;
    UART_TOR_T      TOR;
    UART_BAUD_T     BAUD;
    UART_IRCR_T     IRCR;
    UART_LINCON_T   LINCON;    
	UART_FUNSEL_T   FUNSEL;    
} UART_T;

/*----------------------------- Timer Controller -----------------------------*/
typedef struct
{
    __IO uint32_t  PRESCALE:8;
    __I  uint32_t  RESERVE0:8;
    __IO uint32_t  TDR_EN:1;
    __I  uint32_t  RESERVE1:8;
    __IO uint32_t  CACT:1;
    __IO uint32_t  CRST:1;
    __IO uint32_t  MODE:2;
    __IO uint32_t  IE:1;
    __IO uint32_t  CEN:1;
    __IO uint32_t  nDBGACK_EN:1;
} TIMER_TCSR_T;

typedef __IO uint32_t TIMER_TICR_T;

typedef __IO uint32_t TIMER_TDR_T;

typedef struct
{
    __IO uint32_t  TIF:1;
    __I  uint32_t  RESERVE:31;
} TIMER_TISR_T;

typedef struct
{
    TIMER_TCSR_T     TCSR;
    TIMER_TICR_T     TICR;
    TIMER_TISR_T     TISR;    
    TIMER_TDR_T      TDR;
 } TIMER_T;


/*----------------------------- WDT Controller -----------------------------*/
typedef struct
{
    __IO uint32_t  WTR:1;
	__IO uint32_t  WTRE:1;
	__IO uint32_t  WTRF:1;
	__IO uint32_t  WTIF:1;
	__I  uint32_t  RESERVE:2;
	__IO uint32_t  WTIE:1;
	__IO uint32_t  WTE:1;
	__IO uint32_t  WTIS:3;
    __I  uint32_t  RESERVE1:21;
} WDT_WTCR_T;

typedef struct
{
    WDT_WTCR_T     WTCR;
    
 } WDT_T;

/*------------------------- SPI Interface Controller -------------------------*/
typedef struct
{
    __IO uint32_t  GO_BUSY:1;
    __IO uint32_t  RX_NEG:1;
    __IO uint32_t  TX_NEG:1;
    __IO uint32_t  TX_BIT_LEN:5;
    __IO uint32_t  TX_NUM:2;
    __IO uint32_t  LSB:1;
    __IO uint32_t  CLKP:1;
    __IO uint32_t  SLEEP:4;
    __IO uint32_t  IF:1;
    __IO uint32_t  IE:1;
    __IO uint32_t  SLAVE:1;
    __IO uint32_t  BYTE_SLEEP:1;
    __IO uint32_t  BYTE_ENDIAN:1;
    __IO uint32_t  FOURB:1;
    __IO uint32_t  TWOB:1;
    __IO uint32_t  VARCLK_EN:1;
    __I  uint32_t  RESERVE:8;
} SPI_CNTRL_T;

typedef struct
{
    __IO uint32_t  DIVIDER:16;
    __IO uint32_t  DIVIDER2:16;
} SPI_DIVIDER_T;

typedef struct
{
    __IO uint32_t  SSR:2;
    __IO uint32_t  SS_LVL:1;
    __IO uint32_t  ASS:1;
    __IO uint32_t  SS_LTRIG:1;
    __IO uint32_t  LTRIG_FLAG:1;
    __I  uint32_t  RESERVE:26;
} SPI_SSR_T;


typedef __I  uint32_t   SPI_RX_T;
typedef __O  uint32_t   SPI_TX_T;

typedef struct
{
    __IO uint32_t  JS:1;
    __I  uint32_t  RESERVE0:3;
    __IO uint32_t  JS_RW:1;
    __IO uint32_t  CS_ACT:1;
    __IO uint32_t  DATA_RDY:1;
    __IO uint32_t  CS_DEACT:1;
    __IO uint32_t  READYB:1;
    __I  uint32_t  RESERVE1:23;
} SPI_JS_T;

typedef __IO uint32_t SPI_VARCLK_T;

typedef struct
{
    __IO uint32_t  TX_DMA_GO:1;
    __IO uint32_t  RX_DMA_GO:1;
    __I  uint32_t  RESERVE:30;
} SPI_DMA_T;

typedef struct
{
    SPI_CNTRL_T     CNTRL;
    SPI_DIVIDER_T   DIVIDER;
    SPI_SSR_T       SSR;
    uint32_t        RESERVE0;
    SPI_RX_T        RX[2];
    uint32_t        RESERVE1;
    uint32_t        RESERVE2;
    SPI_TX_T        TX[2];
    uint32_t        RESERVE3;
    uint32_t        RESERVE4;
    SPI_JS_T        JS;
    SPI_VARCLK_T    VARCLK;
    SPI_DMA_T       DMA;
} SPI_T;

/*------------------------------ I2C Controller ------------------------------*/
typedef struct
{
    __I  uint32_t  RESERVE0:2;
    __IO uint32_t  AA:1;
    __IO uint32_t  SI:1;
    __IO uint32_t  STO:1;
    __IO uint32_t  STA:1;
    __IO uint32_t  ENSI:1;
   	__IO uint32_t  EI:1;
    __I  uint32_t  RESERVE1:24;
} I2C_CON_T;

typedef struct
{
    __IO uint32_t  GC:1;
    __IO uint32_t  ADDR:7;
    __I  uint32_t  RESERVE:24;
} I2C_ADDR_T;

typedef __IO uint32_t I2C_DATA_T;

typedef __I  uint32_t I2C_STATUS_T;

typedef __IO uint32_t I2C_CLK_T;

typedef struct
{
    __IO uint32_t  TIF:1;
    __IO uint32_t  DIV4:1;
    __IO uint32_t  ENTI:1;
    __I  uint32_t  RESERVE:29;
} I2C_TOC_T;

typedef struct
{
    __I  uint32_t  RESERVE0:1;
    __IO uint32_t  ADM:7;
    __I  uint32_t  RESERVE1:24;
} I2C_ADRM_T;

typedef struct
{
    I2C_CON_T       CON;
    I2C_ADDR_T      ADDR0;
    I2C_DATA_T      DATA;
    I2C_STATUS_T    STATUS;
    I2C_CLK_T       CLK;
    I2C_TOC_T       TOC;
	I2C_ADDR_T	    ADDR1;
	I2C_ADDR_T	    ADDR2;
	I2C_ADDR_T	    ADDR3;
	I2C_ADRM_T		ADRM0;
	I2C_ADRM_T		ADRM1;
	I2C_ADRM_T		ADRM2;
	I2C_ADRM_T	    ADRM3;        
} I2C_T;


/*----------------------------- RTC Controller -------------------------------*/

typedef __IO uint32_t RTC_INIR_T;

typedef struct
{
    __IO uint32_t  AER:16;
    __I  uint32_t  ENF:1;
    __I  uint32_t  RESERVE1:15;
} RTC_AER_T;

typedef struct
{
    __IO uint32_t  FRACTION:6;
    __I  uint32_t  RESERVE0:2;
    __IO uint32_t  INTEGER:4;
    __I  uint32_t  RESERVE1:20;
} RTC_FCR_T;

typedef struct
{
    __IO uint32_t  SEC1:4;
    __IO uint32_t  SEC10:3;
    __I  uint32_t  RESERVE0:1;
    __IO uint32_t  MIN1:4;
    __IO uint32_t  MIN10:3;
    __I  uint32_t  RESERVE1:1;
    __IO uint32_t  HR1:4;
    __IO uint32_t  HR10:2;
    __I  uint32_t  RESERVE2:10;
} RTC_TLR_T;

typedef struct
{
    __IO uint32_t  DAY1:4;
    __IO uint32_t  DAY10:2;
    __I  uint32_t  RESERVE0:2;
    __IO uint32_t  MON1:4;
    __IO uint32_t  MON10:1;
    __I  uint32_t  RESERVE1:3;
    __IO uint32_t  YEAR1:4;
    __IO uint32_t  YEAR10:4;
    __I  uint32_t  RESERVE2:8;
} RTC_CLR_T;

typedef struct
{
    __IO uint32_t  HR24:1;
    __I  uint32_t  RESERVE:31;
} RTC_TSSR_T;

typedef struct
{
    __IO uint32_t  DWR:3;
    __I  uint32_t  RESERVE:29;
} RTC_DWR_T;

typedef RTC_TLR_T   RTC_TAR_T;
typedef RTC_CLR_T   RTC_CAR_T;

typedef struct
{
    __IO uint32_t  LIR:1;
    __I  uint32_t  RESERVE:31;
} RTC_LIR_T;

typedef struct
{
    __IO uint32_t  AIER:1;
    __IO uint32_t  TIER:1;
    __I  uint32_t  RESERVE:30;
} RTC_RIER_T;


//typedef __IO uint32_t RTC_RIIR_T;

typedef struct
{
    __IO uint32_t  AI:1;
    __IO uint32_t  TI:1;
    __I  uint32_t  RESERVE:30;
} RTC_RIIR_T;

typedef struct
{
    __IO uint32_t  TTR:3;
    __I  uint32_t  RESERVE:30;
} RTC_TTR_T;

typedef struct
{
    __IO uint32_t  PTOUT:16;
    __I  uint32_t  RESERVE0:7;
    __IO uint32_t  PWROFF:1;
    __I  uint32_t  RESERVE1:8;
} RTC_PWRCON_T;

typedef struct
{
    RTC_INIR_T  INIR;
    RTC_AER_T   AER;
    RTC_FCR_T   FCR;
    RTC_TLR_T   TLR;
    RTC_CLR_T   CLR;
    RTC_TSSR_T  TSSR;
    RTC_DWR_T   DWR;
    RTC_TAR_T   TAR;
    RTC_CAR_T   CAR;
    RTC_LIR_T   LIR;
    RTC_RIER_T  RIER;
    RTC_RIIR_T  RIIR;
    RTC_TTR_T   TTR;
    RTC_PWRCON_T   PWRCON;
} RTC_T;


/*----------------------------- ADC Controller -------------------------------*/
typedef struct
{
    __IO uint32_t  RSLT:16;
    __IO uint32_t  OVERRUN:1;
    __IO uint32_t  VALID:1;
    __I  uint32_t  RESERVE1:14;
} ADC_ADDR_T;

typedef struct
{
    __IO uint32_t  ADEN:1;
    __IO uint32_t  ADIE:1;
    __IO uint32_t  ADMD:2;
    __IO uint32_t  TRGS:2;
    __IO uint32_t  TRGCOND:2;
    __IO uint32_t  TRGEN:1;
    __IO uint32_t  PTEN:1;
    __IO uint32_t  DIFF:1;
    __IO uint32_t  ADST:1;
    __I  uint32_t  RESERVE0:4;
    __IO uint32_t  ADCLKDIV:7;
    __I  uint32_t  RESERVE1:9;
} ADC_ADCR_T;



typedef struct
{
    __IO uint32_t  CHEN:8;
    __IO uint32_t  PRESEL:2;
    __I  uint32_t  RESERVE:22;
} ADC_ADCHER_T;


typedef struct
{
    __IO uint32_t  CMPEN:1;
    __IO uint32_t  CMPIE:1;
    __IO uint32_t  CMPCOND:1;
    __IO uint32_t  CMPCH:3;
    __I  uint32_t  RESERVE0:2;
    __IO uint32_t  CMPMATCNT:4;
    __I  uint32_t  RESERVE1:4;
    __IO uint32_t  CMPD:12;
    __I  uint32_t  RESERVE2:4;
} ADC_ADCMPR_T;

typedef struct
{
    __IO uint32_t  ADF:1;
    __IO uint32_t  CMPF0:1;
    __IO uint32_t  CMPF1:1;
    __IO uint32_t  BUSY:1;
    __IO uint32_t  CHANNEL:3;
    __I  uint32_t  RESERVE0:1;
    __IO uint32_t  VALID:8;
    __IO uint32_t  OVERRUN:8;
    __I  uint32_t  RESERVE1:8;
} ADC_ADSR_T;

typedef struct
{
    __IO uint32_t  CALEN:1;
    __IO uint32_t  CALDONE:1;
    __I  uint32_t  RESERVE:30;
} ADC_ADCALR_T;

typedef struct
{
    ADC_ADDR_T      ADDR[8];
    ADC_ADCR_T      ADCR;
    ADC_ADCHER_T    ADCHER;
    ADC_ADCMPR_T    ADCMPR[2];
    ADC_ADSR_T      ADSR;
    ADC_ADCALR_T    ADCALR;

} ADC_T;

/*---------------------- Analog Comparator Controller -------------------------*/
typedef struct
{
    __IO uint32_t  CMPEN:1;
    __IO uint32_t  CMPIE:1;
    __IO uint32_t  CMP_HYSEN:1;
    __IO uint32_t  CP:1;
    __IO uint32_t  CN:1;
    __IO uint32_t  COE:1;
    __I  uint32_t  RESERVE:26;
} ACMP_CMPCR_T;

typedef struct
{
    __IO uint32_t  CMPF1:1;
    __IO uint32_t  CMPF2:1;
    __IO uint32_t  CO1:1;
    __IO uint32_t  CO2:1;
    __I  uint32_t  RESERVE:28;
} ACMP_CMPSR_T;

typedef struct
{
    ACMP_CMPCR_T CMPCR[2];
    ACMP_CMPSR_T CMPSR;
} ACMP_T;

/*---------------------------- Clock Controller ------------------------------*/
typedef struct
{
    __IO uint32_t  XTL12M_EN:1;
    __IO uint32_t  XTL32K_EN:1;
    __IO uint32_t  OSC22M_EN:1;
    __IO uint32_t  OSC10K_EN:1;
    __IO uint32_t  WU_DLY:1;
    __IO uint32_t  WINT_EN:1;
    __IO uint32_t  PD_WU_STS:1;
    __IO uint32_t  PWR_DOWN:1;
    __IO uint32_t  PD_WAIT_CPU:1;
    __I  uint32_t  RESERVE:23;
} SYSCLK_PWRCON_T;

typedef struct
{
    __IO uint32_t  CPU_EN:1;
    __IO uint32_t  PDMA_EN:1;
    __IO uint32_t  ISP_EN:1;
    __I  uint32_t  RESERVE:29;
} SYSCLK_AHBCLK_T;

typedef struct
{
    __IO uint32_t  WDG_EN:1;
    __IO uint32_t  RTC_EN:1;
    __IO uint32_t  TMR0_EN:1;
    __IO uint32_t  TMR1_EN:1;
    __IO uint32_t  TMR2_EN:1;
    __IO uint32_t  TMR3_EN:1;
    __I  uint32_t  RESERVE0:2;
    __IO uint32_t  I2C0_EN:1;
    __IO uint32_t  I2C1_EN:1;
    __I  uint32_t  RESERVE1:2;
    __IO uint32_t  SPI0_EN:1;
    __IO uint32_t  SPI1_EN:1;
    __IO uint32_t  SPI2_EN:1;
    __IO uint32_t  SPI3_EN:1;
    __IO uint32_t  UART0_EN:1;
    __IO uint32_t  UART1_EN:1;
    __I  uint32_t  RESERVE2:2;
    __IO uint32_t  PWM01_EN:1;
    __IO uint32_t  PWM23_EN:1;
    __I  uint32_t  RESERVE3:2;
    __IO uint32_t  CAN0_EN:1;
    __IO uint32_t  CAN1_EN:1;
    __I  uint32_t  RESERVE4:1;
    __IO uint32_t  USBD_EN:1;
    __IO uint32_t  ADC_EN:1;
    __I  uint32_t  RESERVE5:1;
    __IO uint32_t  ACMP_EN:1;
    __IO uint32_t  PS2_EN:1;
} SYSCLK_APBCLK_T;

typedef struct
{
    __IO uint32_t  HCLK_S:3;
    __IO uint32_t  STCLK_S:3;
    __I  uint32_t  RESERVE:26;
} SYSCLK_CLKSEL0_T;


typedef struct
{
    __IO uint32_t  WDG_S:2;
    __IO uint32_t  ADC_S:2;
    __I  uint32_t  RESERVE1:4;
    __IO uint32_t  TMR0_S:3;
    __I  uint32_t  RESERVE2:1;
    __IO uint32_t  TMR1_S:3;
    __I  uint32_t  RESERVE3:1;
    __IO uint32_t  TMR2_S:3;
    __I  uint32_t  RESERVE4:1;
    __IO uint32_t  TMR3_S:3;
    __I  uint32_t  RESERVE5:1;
    __IO uint32_t  UART_S:2;
    __IO uint32_t  CAN_S:2;
    __IO uint32_t  PWM10_S:2;
    __IO uint32_t  PWM32_S:2;
} SYSCLK_CLKSEL1_T;

typedef struct
{
    __IO uint32_t  HCLK_N:4;
    __IO uint32_t  USB_N:4;
    __IO uint32_t  UART_N:4;
    __IO uint32_t  CAN_N:4;
    __IO uint32_t  ADC_N:8;
    __I  uint32_t  RESERVE:8;
} SYSCLK_CLKDIV_T;

typedef struct
{
    __IO uint32_t  FB_DV:9;
    __IO uint32_t  IN_DV:5;
    __IO uint32_t  OUT_DV:2;
    __IO uint32_t  PD:1;
    __IO uint32_t  BP:1;
    __IO uint32_t  OE:1;
    __IO uint32_t  PLL_SRC:1;
    __I  uint32_t  RESERVE:12;
} SYSCLK_PLLCON_T;

typedef struct
{    
    __IO uint32_t  TEST_SEL:8;
    __I  uint32_t  RESERVE:24;
} SYSCLK_TREG_T;

typedef struct
{
    SYSCLK_PWRCON_T    PWRCON;
    SYSCLK_AHBCLK_T    AHBCLK;
    SYSCLK_APBCLK_T    APBCLK;
    uint32_t           RESERVED0;
    SYSCLK_CLKSEL0_T   CLKSEL0;
    SYSCLK_CLKSEL1_T   CLKSEL1;
    SYSCLK_CLKDIV_T    CLKDIV;
    uint32_t           RESERVED1;
	SYSCLK_PLLCON_T    PLLCON;
    
} SYSCLK_T;

/*---------------------------- Global Controller -----------------------------*/
typedef __I uint32_t GCR_PDID_T;  

typedef struct
{
    __IO uint32_t  RSTS_POR:1;
	__IO uint32_t  RSTS_PAD:1;
	__IO uint32_t  RSTS_WDG:1;
	__IO uint32_t  RSTS_LVR:1;
	__IO uint32_t  RSTS_BOD:1;
	__IO uint32_t  RSTS_MCU:1;
	__IO uint32_t  RSTS_PMU:1;    
	__I  uint32_t  RESERVE:25;
} GCR_RSTSRC_T;


typedef struct
{
    __IO uint32_t  CHIP_RST:1;
    __IO uint32_t  CPU_RST:1;
    __IO uint32_t  PDMA_RST:1;
    __I  uint32_t  RESERVE:29;
} GCR_IPRSTC1_T;

typedef struct
{
    __I  uint32_t  RESERVE0:1;
    __IO uint32_t  GPIO_RST:1;
    __IO uint32_t  TMR0_RST:1;
    __IO uint32_t  TMR1_RST:1;
    __IO uint32_t  TMR2_RST:1;
    __IO uint32_t  TMR3_RST:1;
    __I  uint32_t  RESERVE1:2;
    __IO uint32_t  I2C0_RST:1;
    __IO uint32_t  I2C1_RST:1;
    __I  uint32_t  RESERVE2:2;
    __IO uint32_t  SPI0_RST:1;
    __IO uint32_t  SPI1_RST:1;
    __IO uint32_t  SPI2_RST:1;
    __IO uint32_t  SPI3_RST:1;
    __IO uint32_t  UART0_RST:1;
    __IO uint32_t  UART1_RST:1;
    __I  uint32_t  RESERVE3:2;
    __IO uint32_t  PWM_RST:1;
    __I  uint32_t  RESERVE4:1;
    __IO uint32_t  ACMP_RST:1;
    __IO uint32_t  PS2_RST:1;
    __IO uint32_t  CAN0_RST:1;
    __IO uint32_t  CAN1_RST:1;
    __I  uint32_t  RESERVE5:1;
    __IO uint32_t  USBD_RST:1;
    __IO uint32_t  ADC_RST:1;
    __I  uint32_t  RESERVE6:3;
} GCR_IPRSTC2_T;

typedef __IO uint32_t GCR_MISCR_T; 


typedef struct
{
    __IO uint32_t  BOD_EN:1;
    __IO uint32_t  BOD_VL:2;
    __IO uint32_t  BOD_RSTEN:1;
    __IO uint32_t  BOD_BYP_EN:1;
    __IO uint32_t  BOD_LPM:1;
    __IO uint32_t  BOD_OUT:1;
	__IO uint32_t  LVR_EN:1;
	__IO uint32_t  VTEMP_EN:1;
	__IO uint32_t  LDO_BYP:1;
    __I  uint32_t  RESERVE1:22;
} GCR_BODCR_T;

typedef __IO uint32_t GCR_PORCR_T; 


typedef struct
{
    __IO uint32_t ADC0:1;
    __IO uint32_t ADC1:1;
    __IO uint32_t ADC2:1;
    __IO uint32_t ADC3:1;
    __IO uint32_t ADC4:1;
    __IO uint32_t ADC5:1;
    __IO uint32_t ADC6:1;
    __IO uint32_t ADC7:1;
    __IO uint32_t I2C0_SDA:1;
    __IO uint32_t I2C0_SCL:1;
    __IO uint32_t I2C1_SDA:1;
    __IO uint32_t I2C1_SCL:1;
    __IO uint32_t PWM0:1;
    __IO uint32_t PWM1:1;
    __IO uint32_t PWM2:1;
    __IO uint32_t PWM3:1;
    __IO uint32_t SCHMITT:16;    
} GCR_GPAMFP_T;

typedef struct
{
    __IO uint32_t UART0_RX:1;
    __IO uint32_t UART0_TX:1;
    __IO uint32_t UART0_nRTS:1;
    __IO uint32_t UART0_nCTS:1;
    __IO uint32_t UART1_RX:1;
    __IO uint32_t UART1_TX:1;
    __IO uint32_t UART1_nRTS:1;
    __IO uint32_t UART1_nCTS:1;
    __IO uint32_t TM0:1;
    __IO uint32_t TM1:1;
    __IO uint32_t TM2:1;
    __IO uint32_t TM3:1;
    __IO uint32_t CPO0:1;
    __IO uint32_t CPO1:1;
    __IO uint32_t INT0:1;
    __IO uint32_t INT1:1;
    __IO uint32_t SCHMITT:16;    
} GCR_GPBMFP_T;

typedef struct
{
    __IO uint32_t SPI0_SS0:1;
    __IO uint32_t SPI0_CLK:1;
    __IO uint32_t SPI0_MISO0:1;
    __IO uint32_t SPI0_MOSI0:1;
    __IO uint32_t SPI0_MISO1:1;
    __IO uint32_t SPI0_MOSI1:1;
    __IO uint32_t CPP0:1;
    __IO uint32_t CPN0:1;
    __IO uint32_t SPI1_SS0:1;
    __IO uint32_t SPI1_CLK:1;
    __IO uint32_t SPI1_MISO0:1;
    __IO uint32_t SPI1_MOSI0:1;
    __IO uint32_t SPI1_MISO1:1;
    __IO uint32_t SPI1_MOSI1:1;
    __IO uint32_t CPP1:1;
    __IO uint32_t CPN1:1;
    __IO uint32_t SCHMITT:16;    
} GCR_GPCMFP_T;

typedef struct
{
    __IO uint32_t SPI2_SS0:1;
    __IO uint32_t SPI2_CLK:1;
    __IO uint32_t SPI2_MISO0:1;
    __IO uint32_t SPI2_MOSI0:1;
    __IO uint32_t SPI2_MISO1:1;
    __IO uint32_t SPI2_MOSI1:1;
    __IO uint32_t CAN0_RX:1;
    __IO uint32_t CAN0_TX:1;
    __IO uint32_t SPI3_SS0:1;
    __IO uint32_t SPI3_CLK:1;
    __IO uint32_t SPI3_MISO0:1;
    __IO uint32_t SPI3_MOSI0:1;
    __IO uint32_t SPI3_MISO1:1;
    __IO uint32_t SPI3_MOSI1:1;
    __IO uint32_t CAN1_RX:1;
    __IO uint32_t CAN1_TX:1;
    __IO uint32_t SCHMITT:16;    
} GCR_GPDMFP_T;


typedef struct
{
    __I  uint32_t  RESERVE:16;
    __IO uint32_t  SCHMITT:16;
} GCR_GPEMFP_T;

typedef struct
{
    __IO uint32_t  SPI0_SS1:1;  /* GPB10 */
    __IO uint32_t  SPI1_SS1:1;  /* GPB9  */
    __IO uint32_t  SPI2_SS1:1;  /* GPA7  */
    __IO uint32_t  SPI3_SS1:1;  /* GPB14 */
    __I  uint32_t  RESERVE:28;
    
} GCR_USPIMFP_T;

typedef __IO uint32_t GCR_REGLOCK_T;
typedef __IO uint32_t GCR_RCADJ_T;


typedef struct
{
    __IO uint32_t  INTSRC:3;
    __I  uint32_t  RESERVE:29;
} GCR_INTSRC_T;

typedef struct
{
    __IO uint32_t  NMISEL:5;
    __I  uint32_t  RESERVE0:2;
    __IO uint32_t  INT_TEST:1;
    __I  uint32_t  RESERVE1:24;
} GCR_NMISEL_T;


typedef __IO uint32_t GCR_MCUIRQ_T;

typedef struct
{
    GCR_PDID_T      PDID;
    GCR_RSTSRC_T    RSTSRC;
    GCR_IPRSTC1_T   IPRSTC1;
    GCR_IPRSTC2_T   IPRSTC2;
    uint32_t        RESERVE0;
	GCR_MISCR_T     MISCR;
    GCR_BODCR_T     BODCR;
    GCR_PORCR_T		PORCR;
	uint32_t        RESERVE1[4];
    GCR_GPAMFP_T    GPAMFP;
    GCR_GPBMFP_T    GPBMFP;
    GCR_GPCMFP_T    GPCMFP;
    GCR_GPDMFP_T    GPDMFP;
    GCR_GPEMFP_T    GPEMFP;
    uint32_t        RESERVE2[3];
	GCR_USPIMFP_T   USPIMFP;
    uint32_t        RESERVE3[43];
    GCR_REGLOCK_T   REGLOCK;
	uint32_t        RESERVE4[3];
	GCR_RCADJ_T		RCADJ;
} GCR_T;



typedef struct
{
    GCR_INTSRC_T    INTSRC;
    GCR_NMISEL_T    NMISEL;
    GCR_MCUIRQ_T    MCUIRQ;   
} GCR_INT_T;

/*-------------------------- FLASH Memory Controller -------------------------*/
typedef struct
{
    __IO uint32_t  ISPEN:1;
    __IO uint32_t  BS:1;
    __I  uint32_t  RESERVE0:3;
    __IO uint32_t  LDUEN:1;
    __IO uint32_t  ISPFF:1;
    __IO uint32_t  SWRST:1;
    __IO uint32_t  PT:3;
	__I  uint32_t  RESERVE1:1;
	__IO uint32_t  ET:3;
    __I  uint32_t  RESERVE2:17;

} FMC_ISPCON_T;

typedef __IO uint32_t FMC_ISPADR_T;
typedef __IO uint32_t FMC_ISPDAT_T;

typedef struct
{
    __IO uint32_t  FCTRL:4;
    __IO uint32_t  FCEN:1;
    __IO uint32_t  FOEN:1;
    __I  uint32_t  RESERVE:26;
} FMC_ISPCMD_T;

typedef struct
{
    __IO uint32_t  ISPGO:1;
    __I  uint32_t  RESERVE:31;
} FMC_ISPTRG_T;

typedef __I uint32_t FMC_DFBADR_T;

typedef struct
{
    __IO uint32_t  FPSEN:1;
    __IO uint32_t  FATS:3;
    __I  uint32_t  RESERVE:28;
} FMC_FATCON_T;

typedef struct
{
    FMC_ISPCON_T ISPCON;
    FMC_ISPADR_T ISPADR;
    FMC_ISPDAT_T ISPDAT;
    FMC_ISPCMD_T ISPCMD;
    FMC_ISPTRG_T ISPTRG;
    FMC_DFBADR_T DFBADR;
    FMC_FATCON_T FATCON;
} FMC_T;


/*------------------------ PS2 Device Interface Controller -------------------*/
typedef struct
{
    __IO uint32_t  PS2EN:1;
    __IO uint32_t  TXINTEN:1;
    __IO uint32_t  RXINTEN:1;
    __IO uint32_t  TXFIFO_DEPTH:4;
    __IO uint32_t  ACK:1;
    __IO uint32_t  CLRFIFO:1;
    __IO uint32_t  OVERRIDE:1;
    __IO uint32_t  FPS2CLK:1;
    __IO uint32_t  FPS2DAT:1;
    __I  uint32_t  RESERVE:20;
} PS2_CON_T;

typedef __IO uint32_t PS2_DATA_T;

typedef struct
{
    __IO uint32_t  PS2CLK:1;
    __IO uint32_t  PS2DATA:1;
    __IO uint32_t  FRAMERR:1;
    __IO uint32_t  RXPARTY:1;
    __IO uint32_t  RXBUSY:1;
    __IO uint32_t  TXBUSY:1;
    __IO uint32_t  RXOVF:1;
    __IO uint32_t  TXEMPTY:1;
    __IO uint32_t  BYTEIDX:4;
    __I  uint32_t  RESERVE:20;
} PS2_STATUS_T;

typedef __IO uint32_t PS2_INTID_T;

typedef struct
{
    PS2_CON_T       PS2CON;
    PS2_DATA_T      TXDATA[4];
    PS2_DATA_T      RXDATA;
    PS2_STATUS_T    STATUS;
    PS2_INTID_T     INTID;
} PS2_T;

/*---------------------------- CAN Bus Controller ----------------------------*/
typedef struct
{
    __IO uint32_t  RSTM:1;
	__IO uint32_t  LOM:1;
    __I  uint32_t  RESERVE:30;
    
} CAN_OPMODE_T;

typedef struct
{
    __IO uint32_t  TR:1;
	__IO uint32_t  ABRT:1;
    __I  uint32_t  RESERVE2:3;
	__IO uint32_t  OVERFLOAD_EN:1;
	__IO uint32_t  WAKEUP_EN:1;
    __IO uint32_t  CAN_EN:1;
    __I  uint32_t  RESERVE:24;
} CAN_CMD_T;

typedef struct
{
    __I  uint32_t  RESERVE0:3;
    __IO uint32_t  TCS:1;
    __IO uint32_t  RS:1;
    __IO uint32_t  TS:1;
    __IO uint32_t  BS:1;
    __IO uint32_t  BS2:1;
    __IO uint32_t  EAS:1;
    __IO uint32_t  EPS:1;
    __I  uint32_t  RESERVE1:22;
} CAN_BSR_T;

typedef struct
{
    __IO uint32_t  RI:1;
    __IO uint32_t  TI:1;
    __I  uint32_t  RESERVE0:2;
    __IO uint32_t  WUI:1;
    __I  uint32_t  RESERVE1:1;
    __IO uint32_t  ALI:1;
    __IO uint32_t  BEI:1;
    __I  uint32_t  RESERVE2:24;
} CAN_INTR_T;

typedef struct
{
    __IO uint32_t  RIE:1;
    __IO uint32_t  TIE:1;
    __I  uint32_t  RESERVE0:2;
    __IO uint32_t  WUIE:1;
    __I  uint32_t  RESERVE1:1;
    __IO uint32_t  ALIE:1;
    __IO uint32_t  BEIE:1;
    __I  uint32_t  RESERVE2:24;
} CAN_INTEN_T;

typedef struct
{
    __IO uint32_t  BRP:4;
    __IO uint32_t  SJW:2;
    __IO uint32_t  TSEG1:5;
    __IO uint32_t  TSEG2:4;
    __IO uint32_t  SAMP:1;
    __I  uint32_t  RESERVE2:16;
} CAN_BTIMR_T;

typedef struct
{
    __IO uint32_t  BIT_ERR:4;
    __IO uint32_t  ACK_ERR:2;
    __IO uint32_t  CRC_ERR:5;
    __IO uint32_t  FORM_ERR:4;
    __IO uint32_t  STUFF_ERR:1;
    __I  uint32_t  RESERVE:16;
} CAN_ERRCR_T;

typedef struct
{
    __IO uint32_t  RECNT:8;
    __I  uint32_t  RESERVE:24;
} CAN_RECNTR_T;

typedef struct
{
    __IO uint32_t  TECNT:8;
    __I  uint32_t  RESERVE:24;
} CAN_TECNTR_T;

typedef struct
{
    __IO uint32_t  TXDLC:6;
    __IO uint32_t  TXRTR:1;
    __IO uint32_t  TXFF:1;
    __I  uint32_t  RESERVE:24;
} CAN_TXFINFO_T;

typedef struct
{
    __I  uint32_t  RESERVE:3;
    __IO uint32_t  TXID:29;
} CAN_TXID_T;

typedef __IO uint32_t CAN_TXDATA_T;

typedef struct
{
    __IO uint32_t  RXDLC:4;
    __I  uint32_t  RESERVE0:2;
    __IO uint32_t  RXRTR:1;
    __IO uint32_t  RXIDE:1;
    __I  uint32_t  RESERVE1:24;
} CAN_RXFINFO_T;

typedef struct
{
    __I  uint32_t  RESERVE:3;
    __IO uint32_t  RXID:29;
} CAN_RXID_T;

typedef __IO uint32_t CAN_RXDATA_T;

typedef struct
{
    __I  uint32_t  RESERVE:3;
    __IO uint32_t  ACR:29;
} CAN_ACR_T;

typedef struct
{
    __I  uint32_t  RESERVE:3;
    __IO uint32_t  AMR:29;
} CAN_AMR_T;


typedef struct
{
    __I  uint32_t  RESERVE:32;
} CAN_RESERVE_T;

typedef struct
{
    CAN_OPMODE_T    OPMODE;
    CAN_CMD_T       CMD;
	CAN_BSR_T       BSR;    
	CAN_INTR_T      INTR;

    CAN_INTEN_T     INTEN;
    CAN_BTIMR_T     BTIMR;
	CAN_RESERVE_T	PROTECT[2];

    CAN_ERRCR_T     ERRCR;
	CAN_RESERVE_T	PROTECT1;
    CAN_RECNTR_T    RECNTR;
    CAN_TECNTR_T    TECNTR;

    CAN_TXFINFO_T   TXFINFO;
    CAN_TXID_T      TXID;
    CAN_TXDATA_T    TXDATA[2];

    CAN_RXFINFO_T   RXFINFO;
    CAN_RXID_T      RXID;
    CAN_RXDATA_T    RX_DATA[2];
    CAN_ACR_T       ACR;
    CAN_AMR_T       AMR;    
} CAN_T;


/*--------------------------- USB Device Controller --------------------------*/
typedef struct
{
    __IO uint32_t  BUS:1;
    __IO uint32_t  USB:1;
    __IO uint32_t  FLD:1;
    __IO uint32_t  WAKEUP:1;
    __I  uint32_t  RESERVE0:4;
    __IO uint32_t  WAKEUP_EN:1;
    __I  uint32_t  RESERVE1:6;
    __IO uint32_t  INNAK_EN:1;
    __I  uint32_t  RESERVE2:16;
} USBD_IEF_T;

typedef struct
{
    __IO uint32_t  BUS:1;
    __IO uint32_t  USB:1;
    __IO uint32_t  FLD:1;
    __IO uint32_t  WAKEUP:1;
    __I  uint32_t  RESERVE0:12;
    __IO uint32_t  EPTF:6;
    __I  uint32_t  RESERVE1:9;
    __IO uint32_t  SETUP:1;
} USBD_EVF_T;

typedef struct
{
    __IO uint32_t  FADDR:7;
    __I  uint32_t  RESERVE:25;
} USBD_FADDR_T;

typedef struct
{
    __I  uint32_t  RESERVE0:7;
    __IO uint32_t  OVERRUN:1;
    __IO uint32_t  STS0:3;
    __IO uint32_t  STS1:3;
    __IO uint32_t  STS2:3;
    __IO uint32_t  STS3:3;
    __IO uint32_t  STS4:3;
    __IO uint32_t  STS5:3;
    __I  uint32_t  RESERVE1:6;
} USBD_STS_T;



typedef struct
{
    __IO uint32_t  USBRST:1;
    __IO uint32_t  SUSPEND:1;
    __IO uint32_t  RESUME:1;
    __IO uint32_t  TIMEOUT:1;
    __IO uint32_t  PHY_EN:1;
    __IO uint32_t  RWAKEUP:1;
    __I  uint32_t  RESERVE0:1;
    __IO uint32_t  USB_EN:1;
	__IO uint32_t  DPPU_EN:1;
	__IO uint32_t  PDB:1;
    __I  uint32_t  RESERVE1:22;
} USBD_ATTR_T;



typedef struct
{
    __IO uint32_t  FLODET:1;
    __I  uint32_t  RESERVE:31;
} USBD_FLODET_T;

typedef struct
{
    __I  uint32_t  RESERVE0:3;
    __IO uint32_t  BUFSEG:6;
    __I  uint32_t  RESERVE:23;
} USBD_BUFSEG_T;

typedef struct
{
    __IO uint32_t  MXPLD:9;
    __I  uint32_t  RESERVE:23;
} USBD_MXPLD_T;

typedef struct
{
    __IO uint32_t  EPT:4;
    __IO uint32_t  ISOCH:1;
    __IO uint32_t  STATE:2;
    __IO uint32_t  DSQ:1;
    __I  uint32_t  RESERVE0:1;
    __IO uint32_t  STALL_CTL:1;
    __I  uint32_t  RESERVE1:22;
} USBD_CFG_T;

typedef struct
{
    __IO uint32_t  CFGP:1;
    __IO uint32_t  STALL:1;
    __I  uint32_t  RESERVE:30;
} USBD_CFGP_T;

typedef struct
{
    __IO uint32_t  DRVSE0:1;
    __I  uint32_t  RESERVE:31;
} USBD_DRVSE0_T;

typedef struct
{
    __IO uint32_t  BISTEN:1;
    __IO uint32_t  FINISH:1;
    __IO uint32_t  BISTFAIL:1;
    __I  uint32_t  RESERVE:29;
} USBD_BIST_T;

typedef struct
{
    __IO uint32_t  PDMA_RW:1;
    __IO uint32_t  PDMA_EN:1;
    __I  uint32_t  RESERVE:30;
} USBD_PDMA_T;


typedef struct
{
    USBD_BUFSEG_T   BUFSEG;
    USBD_MXPLD_T    MXPLD;
    USBD_CFG_T      CFG;
    USBD_CFGP_T     CFGP;
} USBD_EP_T;

typedef struct
{
    USBD_IEF_T      IEF;
    USBD_EVF_T      EVF;
    USBD_FADDR_T    FADDR;
    USBD_STS_T      STS;
    USBD_ATTR_T     ATTR;
    USBD_FLODET_T   FLODET;
    USBD_BUFSEG_T   BUFSEG;
    uint32_t        RESERVE0;
	USBD_EP_T       EP[6];
    uint32_t        RESERVE1[4];
	USBD_DRVSE0_T   DRVSE0;
    uint32_t        RESERVE2[3];
	USBD_BIST_T     BIST;
    USBD_PDMA_T     PDMA;
} USBD_T;


/*------------------------------ PDMA Controller -----------------------------*/
typedef struct
{
    __IO uint32_t  PDMACEN:1;
    __IO uint32_t  SW_RST:1;
    __IO uint32_t  MODE_SEL:2;
    __IO uint32_t  SAD_SEL:2;
    __IO uint32_t  DAD_SEL:2;
    __I  uint32_t  RESERVE0:4;
    __IO uint32_t  WAR_BCR_SEL:4;
    __I  uint32_t  RESERVE1:3;
    __IO uint32_t  APB_TWS:2;
    __I  uint32_t  RESERVE2:2;
    __IO uint32_t  TRIG_EN:1;
    __I  uint32_t  RESERVE3:8;
} PDMA_CSR_T;

typedef __IO uint32_t PDMA_SAR_T;
typedef __IO uint32_t PDMA_DAR_T;

typedef __IO uint32_t PDMA_BCR_T;

typedef __IO uint32_t PDMA_CSAR_T;
typedef __IO uint32_t PDMA_CDAR_T;

typedef struct
{
    __IO uint32_t  CBCR:24;
    __I  uint32_t  RESERVE:8;
} PDMA_CBCR_T;

typedef struct
{
    __IO uint32_t  TABORT_IE:1;
    __IO uint32_t  BLKD_IE:1;
    __IO uint32_t  WAR_IE:1;
    __I  uint32_t  RESERVE:29;
} PDMA_IER_T;

//typedef __IO uint32_t PDMA_ISR_T;

typedef struct
{
    __IO uint32_t  TABORT_IF:1;
    __IO uint32_t  BLKD_IF:1;
    __I  uint32_t  RESERVE:6;
	__IO uint32_t  WAR_IF:4;
    __I  uint32_t  RESERVE1:3;
	__IO uint32_t  BUSY:1;
	__I  uint32_t  RESERVE2:15;
	__IO uint32_t  INTR:1;
} PDMA_ISR_T;

typedef __IO uint32_t PDMA_SBUF_T;

typedef struct
{
    __IO uint32_t  PDMA_RST:1;
    __I  uint32_t  RESERVE0:7;
    __IO uint32_t  HCLK0_EN:1;
    __IO uint32_t  HCLK1_EN:1;
    __IO uint32_t  HCLK2_EN:1;
    __IO uint32_t  HCLK3_EN:1;
    __IO uint32_t  HCLK4_EN:1;
    __IO uint32_t  HCLK5_EN:1;
    __IO uint32_t  HCLK6_EN:1;
    __IO uint32_t  HCLK7_EN:1;
    __IO uint32_t  HCLK8_EN:1;
    __IO uint32_t  HCLK9_EN:1;
    __IO uint32_t  HCLK10_EN:1;
    __IO uint32_t  HCLK11_EN:1;
    __I  uint32_t  RESERVE1:12;
} PDMA_GCRCSR_T;

typedef struct
{
    __IO uint32_t  UART0_RXSEL:4;
    __IO uint32_t  UART0_TXSEL:4;
    __IO uint32_t  UART1_RXSEL:4;
    __IO uint32_t  UART1_TXSEL:4;
    __IO uint32_t  USBD_RXSEL:4;
    __IO uint32_t  USBD_TXSEL:4;
    __IO uint32_t  ADC_RXSEL:4;
    __IO uint32_t  ADC_TXSEL:4;
} PDMA_PDSSR1_T;
                                                        

typedef struct
{
    __IO uint32_t  SPI0_RXSEL:4;
    __IO uint32_t  SPI0_TXSEL:4;
    __IO uint32_t  SPI1_RXSEL:4;
    __IO uint32_t  SPI1_TXSEL:4;
    __IO uint32_t  SPI2_RXSEL:4;
    __IO uint32_t  SPI2_TXSEL:4;
    __IO uint32_t  SPI3_RXSEL:4;
    __IO uint32_t  SPI3_TXSEL:4;
} PDMA_PDSSR0_T;

typedef __IO uint32_t PDMA_GCRISR_T;

typedef struct
{
    PDMA_GCRCSR_T   GCRCSR;
    PDMA_PDSSR0_T   PDSSR0;
    PDMA_PDSSR1_T   PDSSR1;  
    PDMA_GCRISR_T   GCRISR;  
} PDMA_GCR_T;

typedef struct 
{
    PDMA_CSR_T      CSR;
    PDMA_SAR_T      SAR;
    PDMA_DAR_T      DAR;
    PDMA_BCR_T      BCR;
    uint32_t        POINT;
    PDMA_CSAR_T     CSAR;
    PDMA_CDAR_T     CDAR;
    PDMA_CBCR_T     CBCR;
    PDMA_IER_T      IER;
    PDMA_ISR_T      ISR;
    PDMA_SBUF_T     SBUF[4];
} PDMA_T;

/*----------------------------- PWM Controller -------------------------------*/
typedef struct
{
    __IO uint32_t  CP0:8;
    __IO uint32_t  CP1:8;
    __IO uint32_t  DZI0:8;
    __IO uint32_t  DZI1:8;
} PWM_PPR_T;

typedef struct
{
    __IO uint32_t  CSR0:3;
    __I  uint32_t  RESERVE0:1;
    __IO uint32_t  CSR1:3;
    __I  uint32_t  RESERVE1:1;
    __IO uint32_t  CSR2:3;
    __I  uint32_t  RESERVE2:1;
    __IO uint32_t  CSR3:3;
    __I  uint32_t  RESERVE:17;
} PWM_CSR_T;

typedef struct
{
    __IO uint32_t  CH0EN:1;
    __I  uint32_t  RESERVE0:1;
    __IO uint32_t  CH0INV:1;
    __IO uint32_t  CH0MOD:1;
    __IO uint32_t  DZEN0:1;
    __IO uint32_t  DZEN1:1;
    __I  uint32_t  RESERVE1:2;
    __IO uint32_t  CH1EN:1;
    __I  uint32_t  RESERVE2:1;
    __IO uint32_t  CH1INV:1;
    __IO uint32_t  CH1MOD:1;
    __I  uint32_t  RESERVE3:4;
    __IO uint32_t  CH2EN:1;
    __I  uint32_t  RESERVE4:1;
    __IO uint32_t  CH2INV:1;
    __IO uint32_t  CH2MOD:1;
    __I  uint32_t  RESERVE5:4;
    __IO uint32_t  CH3EN:1;
    __I  uint32_t  RESERVE6:1;
    __IO uint32_t  CH3INV:1;
    __IO uint32_t  CH3MOD:1;
    __I  uint32_t  RESERVE7:4;   
} PWM_PCR_T;

typedef __IO uint32_t PWM_CNR_T;

typedef __IO uint32_t PWM_CMR_T;

typedef __IO uint32_t PWM_PDR_T;

typedef struct
{
    __IO uint32_t  PWMIE0:1;
    __IO uint32_t  PWMIE1:1;
    __IO uint32_t  PWMIE2:1;
    __IO uint32_t  PWMIE3:1;
	__I  uint32_t  RESERVE:28;
} PWM_PIER_T;


typedef struct
{
    __IO uint32_t  PWMIF0:1;
    __IO uint32_t  PWMIF1:1;
    __IO uint32_t  PWMIF2:1;
    __IO uint32_t  PWMIF3:1;
	__I  uint32_t  RESERVE:28;
} PWM_PIIR_T;


typedef struct
{
    __IO uint32_t  INV0:1;
    __IO uint32_t  CRL_IE0:1;
    __IO uint32_t  CFL_IE0:1;
    __IO uint32_t  CAPCH0EN:1;
    __IO uint32_t  CAPIF0:1;
    __I  uint32_t  RESERVE0:1;
    __IO uint32_t  CRLRI0:1;
    __IO uint32_t  CFLRI0:1;
    __I  uint32_t  RESERVE1:8;
    __IO uint32_t  INV1:1;
    __IO uint32_t  CRL_IE1:1;
    __IO uint32_t  CFL_IE1:1;
    __IO uint32_t  CAPCH1EN:1;
    __IO uint32_t  CAPIF1:1;
    __I  uint32_t  RESERVE2:1;
    __IO uint32_t  CRLRI1:1;
    __IO uint32_t  CFLRI1:1;
    __I  uint32_t  RESERVE3:8;
} PWM_CCR0_T;


typedef struct
{
    __IO uint32_t  INV2:1;
    __IO uint32_t  CRL_IE2:1;
    __IO uint32_t  CFL_IE2:1;
    __IO uint32_t  CAPCH2EN:1;
    __IO uint32_t  CAPIF2:1;
    __I  uint32_t  RESERVE0:1;
    __IO uint32_t  CRLRI2:1;
    __IO uint32_t  CFLRI2:1;
    __I  uint32_t  RESERVE1:8;
    __IO uint32_t  INV3:1;
    __IO uint32_t  CRL_IE3:1;
    __IO uint32_t  CFL_IE3:1;
    __IO uint32_t  CAPCH3EN:1;
    __IO uint32_t  CAPIF3:1;
    __I  uint32_t  RESERVE2:1;
    __IO uint32_t  CRLRI3:1;
    __IO uint32_t  CFLRI3:1;
    __I  uint32_t  RESERVE3:8;
} PWM_CCR1_T;


typedef __IO uint32_t PWM_CRLR_T;

typedef __IO uint32_t PWM_CFLR_T;

typedef __IO uint32_t PWM_CAPENR_T;

typedef struct
{
    __IO uint32_t  PWM0:1;
    __IO uint32_t  PWM1:1;
    __IO uint32_t  PWM2:1;
    __IO uint32_t  PWM3:1;
	__I  uint32_t  RESERVE:28;
} PWM_POE_T;


typedef struct
{
    PWM_PPR_T       PPR;
    PWM_CSR_T       CSR;
    PWM_PCR_T       PCR;
    PWM_CNR_T       CNR0;
    PWM_CMR_T       CMR0;
    PWM_PDR_T       PDR0;
    PWM_CNR_T       CNR1;
    PWM_CMR_T       CMR1;
    PWM_PDR_T       PDR1;
    PWM_CNR_T       CNR2;
    PWM_CMR_T       CMR2;
    PWM_PDR_T       PDR2;
    PWM_CNR_T       CNR3;
    PWM_CMR_T       CMR3;
    PWM_PDR_T       PDR3;
    __I uint32_t    RESERVE0;
    PWM_PIER_T      PIER;
    PWM_PIIR_T      PIIR;
    __I uint32_t    RESERVE1[2];
    PWM_CCR0_T      CCR0;
    PWM_CCR1_T      CCR1;
    PWM_CRLR_T      CRLR0;
    PWM_CFLR_T      CFLR0;
    PWM_CRLR_T      CRLR1;
    PWM_CFLR_T      CFLR1;
    PWM_CRLR_T      CRLR2;
    PWM_CFLR_T      CFLR2;
    PWM_CRLR_T      CRLR3;
    PWM_CFLR_T      CFLR3;
    PWM_CAPENR_T    CAPENR;
    PWM_POE_T       POE;    
        
    
} PWM_T;




/******************************************************************************/
/*                         Peripheral memory map                              */
/******************************************************************************/
/* Peripheral and SRAM base address */
#define FLASH_BASE          ((     uint32_t)0x00000000)
#define SRAM_BASE           ((     uint32_t)0x20000000)
#define AHB_BASE            ((     uint32_t)0x50000000)
#define APB1_BASE           ((     uint32_t)0x40000000)
#define APB2_BASE           ((     uint32_t)0x40100000)

/* Peripheral memory map */
#define GPIO_BASE           (AHB_BASE        + 0x4000)

#define GPIOA_BASE          (GPIO_BASE               )
#define GPIOB_BASE          (GPIO_BASE       + 0x0040)
#define GPIOC_BASE          (GPIO_BASE       + 0x0080)
#define GPIOD_BASE          (GPIO_BASE       + 0x00C0)
#define GPIOE_BASE          (GPIO_BASE       + 0x0100)
#define GPIO_DBNCECON_BASE  (GPIO_BASE       + 0x0180)

#define UART0_BASE           (APB1_BASE      + 0x50000)
#define UART1_BASE           (APB2_BASE      + 0x50000)

#define TIMER0_BASE          (APB1_BASE      + 0x10000)  
#define TIMER1_BASE          (APB1_BASE      + 0x10020)  
#define TIMER2_BASE          (APB2_BASE      + 0x10000)  
#define TIMER3_BASE          (APB2_BASE      + 0x10020)  

#define WDT_BASE       	     (APB1_BASE      + 0x4000)  

#define SPI0_BASE            (APB1_BASE      + 0x30000)
#define SPI1_BASE            (APB1_BASE      + 0x34000)
#define SPI2_BASE            (APB2_BASE      + 0x30000)
#define SPI3_BASE            (APB2_BASE      + 0x34000)

#define I2C0_BASE            (APB1_BASE      + 0x20000)
#define I2C1_BASE            (APB2_BASE      + 0x20000)

#define RTC_BASE             (APB1_BASE      + 0x08000)

#define ADC_BASE             (APB1_BASE      + 0xE0000)
#define ADC_ADSR             (ADC_BASE       + 0x30)

#define ACMP_BASE            (APB1_BASE      + 0xD0000)   

#define SYSCLK_BASE          (AHB_BASE       + 0x00200)

#define GCR_BASE             (AHB_BASE       + 0x00000)

#define INT_BASE             (AHB_BASE       + 0x00300)

#define FMC_BASE             (AHB_BASE       + 0x0C000)

#define PS2_BASE             (APB2_BASE      + 0x00000)

#define CAN0_BASE            (APB2_BASE      + 0x80000)
#define CAN1_BASE            (APB2_BASE      + 0x84000)

#define USBD_BASE            (APB1_BASE      + 0x60000)

#define PDMA0_BASE           (AHB_BASE       + 0x08000)
#define PDMA1_BASE           (AHB_BASE       + 0x08100)
#define PDMA2_BASE           (AHB_BASE       + 0x08200)
#define PDMA3_BASE           (AHB_BASE       + 0x08300)
#define PDMA4_BASE           (AHB_BASE       + 0x08400)
#define PDMA5_BASE           (AHB_BASE       + 0x08500)
#define PDMA6_BASE           (AHB_BASE       + 0x08600)
#define PDMA7_BASE           (AHB_BASE       + 0x08700)
#define PDMA8_BASE           (AHB_BASE       + 0x08800)
#define PDMA9_BASE           (AHB_BASE       + 0x08900)
#define PDMA10_BASE          (AHB_BASE       + 0x08A00)
#define PDMA11_BASE          (AHB_BASE       + 0x08B00)
#define PDMA_GCR_BASE        (AHB_BASE       + 0x08F00)

#define PWM_BASE             (APB1_BASE      + 0x40000)

/******************************************************************************/
/*                         Peripheral declaration                             */
/******************************************************************************/
#define GPIOA               ((GPIO_T *) GPIOA_BASE)
#define GPIOB               ((GPIO_T *) GPIOB_BASE)
#define GPIOC               ((GPIO_T *) GPIOC_BASE)
#define GPIOD               ((GPIO_T *) GPIOD_BASE)
#define GPIOE               ((GPIO_T *) GPIOE_BASE)
#define GPIO_DBNCECON       ((GPIO_DBNCECON_T *) GPIO_DBNCECON_BASE)

#define UART0               ((UART_T *) UART0_BASE)
#define UART1               ((UART_T *) UART1_BASE)

#define TIMER0              ((TIMER_T *) TIMER0_BASE)
#define TIMER1              ((TIMER_T *) TIMER1_BASE)
#define TIMER2              ((TIMER_T *) TIMER2_BASE)
#define TIMER3              ((TIMER_T *) TIMER3_BASE)

#define WDT                 ((WDT_T *) WDT_BASE)

#define SPI0                ((SPI_T *) SPI0_BASE)
#define SPI1                ((SPI_T *) SPI1_BASE)
#define SPI2                ((SPI_T *) SPI2_BASE)
#define SPI3                ((SPI_T *) SPI3_BASE)

#define I2C0                ((I2C_T *) I2C0_BASE)
#define I2C1                ((I2C_T *) I2C1_BASE)

#define RTC                 ((RTC_T *) RTC_BASE)

#define ADC                 ((ADC_T *) ADC_BASE)

#define ACMP                ((ACMP_T *) ACMP_BASE)

#define SYSCLK              ((SYSCLK_T *) SYSCLK_BASE)

#define SYS                 ((GCR_T *) GCR_BASE)

#define SYSINT              ((GCR_INT_T *) INT_BASE)

#define FMC                 ((FMC_T *) FMC_BASE)

#define PS2                 ((PS2_T *) PS2_BASE)

#define CAN0                ((CAN_T *) CAN0_BASE)
#define CAN1                ((CAN_T *) CAN1_BASE)

#define USBD                ((USBD_T *) USBD_BASE)

#define PDMA0               ((PDMA_T *) PDMA0_BASE)
#define PDMA1               ((PDMA_T *) PDMA1_BASE)
#define PDMA2               ((PDMA_T *) PDMA2_BASE)
#define PDMA3               ((PDMA_T *) PDMA3_BASE)
#define PDMA4               ((PDMA_T *) PDMA4_BASE)
#define PDMA5               ((PDMA_T *) PDMA5_BASE)
#define PDMA6               ((PDMA_T *) PDMA6_BASE)
#define PDMA7               ((PDMA_T *) PDMA7_BASE)
#define PDMA8               ((PDMA_T *) PDMA8_BASE)
#define PDMA9               ((PDMA_T *) PDMA9_BASE)
#define PDMA10              ((PDMA_T *) PDMA10_BASE)
#define PDMA11              ((PDMA_T *) PDMA11_BASE)
#define PDMA_GCR            ((PDMA_GCR_T *) PDMA_GCR_BASE)

#define PWM                 ((PWM_T *) PWM_BASE)

#define UNLOCKREG(x)        *((__IO uint32_t *)(GCR_BASE + 0x100)) = 0x59;*((__IO uint32_t *)(GCR_BASE + 0x100)) = 0x16;*((__IO uint32_t *)(GCR_BASE + 0x100)) = 0x88
#define LOCKREG(x)          *((__IO uint32_t *)(GCR_BASE + 0x100)) = 0x00;     

#define REGCOPY(dest, src)  *((uint32_t *)&(dest)) = *((uint32_t *)&(src))
#define CLEAR(dest) 		*((uint32_t *)&(dest)) = 0

//=============================================================================
typedef volatile unsigned char  vu8;
typedef volatile unsigned long  vu32;
typedef volatile unsigned short vu16;
#define M8(adr)  (*((vu8  *) (adr)))
#define M16(adr) (*((vu16 *) (adr)))
#define M32(adr) (*((vu32 *) (adr)))

#define outpw(port,value)	*((volatile unsigned int *)(port))=value
#define inpw(port)			(*((volatile unsigned int *)(port)))
#define outpb(port,value)	*((volatile unsigned char *)(port))=value
#define inpb(port)			(*((volatile unsigned char *)(port)))
#define outps(port,value)	*((volatile unsigned short *)(port))=value
#define inps(port)			(*((volatile unsigned short *)(port)))

#define E_SUCCESS 	0
#define NULL         0

#define TRUE	   	1
#define FALSE   	0

#define ENABLE     1
#define DISABLE    0

// Define one bit mask
#define BIT0	0x00000001
#define BIT1	0x00000002
#define BIT2	0x00000004
#define BIT3	0x00000008
#define BIT4	0x00000010
#define BIT5	0x00000020
#define BIT6	0x00000040
#define BIT7	0x00000080
#define BIT8	0x00000100
#define BIT9	0x00000200
#define BIT10	0x00000400
#define BIT11	0x00000800
#define BIT12	0x00001000
#define BIT13	0x00002000
#define BIT14	0x00004000
#define BIT15	0x00008000
#define BIT16	0x00010000
#define BIT17	0x00020000
#define BIT18	0x00040000
#define BIT19	0x00080000
#define BIT20	0x00100000
#define BIT21	0x00200000
#define BIT22	0x00400000
#define BIT23	0x00800000
#define BIT24	0x01000000
#define BIT25	0x02000000
#define BIT26	0x04000000
#define BIT27	0x08000000
#define BIT28	0x10000000
#define BIT29	0x20000000
#define BIT30	0x40000000
#define BIT31	0x80000000

#endif
                                                                                                 
