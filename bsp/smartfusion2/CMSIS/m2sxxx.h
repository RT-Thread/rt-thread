/*******************************************************************************
 * (c) Copyright 2010-2013 Microsemi SoC Products Group. All rights reserved.
 *
 *  Microsemi SmartFusion2 Cortex Microcontroller Software Interface - Peripheral
 *  Access Layer.
 *
 *  This file describes the interrupt assignment and peripheral registers for
 *  the SmartFusion2 familly of devices.
 *
 * SVN $Revision: 6526 $
 * SVN $Date: 2014-06-05 16:07:40 +0100 (Thu, 05 Jun 2014) $
 */
#ifndef __SMARTFUSION2_CMSIS_PAL_H__
#define __SMARTFUSION2_CMSIS_PAL_H__

#ifdef __cplusplus
extern "C" {
#endif

/*
 * ==========================================================================
 * ---------- Interrupt Number Definition -----------------------------------
 * ==========================================================================
 */

typedef enum IRQn
{
/******  Cortex-M3 Processor Exceptions Numbers *********************************************************/
  NonMaskableInt_IRQn             = -14,      /*!< 2 Non Maskable Interrupt - Watchdog timeout interrupt*/
  HardFault_IRQn                  = -13,      /*!< 2 Hard Fault Interrupt                               */
  MemoryManagement_IRQn           = -12,      /*!< 4 Cortex-M3 Memory Management Interrupt              */
  BusFault_IRQn                   = -11,      /*!< 5 Cortex-M3 Bus Fault Interrupt                      */
  UsageFault_IRQn                 = -10,      /*!< 6 Cortex-M3 Usage Fault Interrupt                    */
  SVCall_IRQn                     = -5,       /*!< 11 Cortex-M3 SV Call Interrupt                       */
  DebugMonitor_IRQn               = -4,       /*!< 12 Cortex-M3 Debug Monitor Interrupt                 */
  PendSV_IRQn                     = -2,       /*!< 14 Cortex-M3 Pend SV Interrupt                       */
  SysTick_IRQn                    = -1,       /*!< 15 Cortex-M3 System Tick Interrupt                   */

/******  SmartFusion2 specific Interrupt Numbers *********************************************************/
  WdogWakeup_IRQn                 = 0,        /*!< WatchDog wakeup interrupt                            */
  RTC_Wakeup_IRQn                 = 1,        /*!< RTC wakeup interrupt                                 */
  SPI0_IRQn                       = 2,        /*!< SPI0 interrupt                                       */
  SPI1_IRQn                       = 3,        /*!< SPI1 interrupt                                       */
  I2C0_IRQn                       = 4,        /*!< I2C0 interrupt                                       */
  I2C0_SMBAlert_IRQn              = 5,        /*!< I2C0 SMBus Alert interrupt                           */
  I2C0_SMBus_IRQn                 = 6,        /*!< I2C0 SMBus Suspend interrupt                         */
  I2C1_IRQn                       = 7,        /*!< I2C1 interrupt                                       */
  I2C1_SMBAlert_IRQn              = 8,        /*!< I2C1 SMBus Alert interrupt                           */
  I2C1_SMBus_IRQn                 = 9,        /*!< I2C1 SMBus Suspend interrupt                         */
  UART0_IRQn                      = 10,       /*!< UART0 interrupt                                      */
  UART1_IRQn                      = 11,       /*!< UART1 interrupt                                      */
  EthernetMAC_IRQn                = 12,       /*!< Ethernet MAC interrupt                               */
  DMA_IRQn                        = 13,       /*!< Peripheral DMA interrupt                             */
  Timer1_IRQn                     = 14,       /*!< Timer1 interrupt                                     */
  Timer2_IRQn                     = 15,       /*!< Timer2 interrupt                                     */
  CAN_IRQn                        = 16,       /*!< CAN controller interrupt                             */
  ENVM0_IRQn                      = 17,       /*!< eNVM0 operation completion interrupt                 */
  ENVM1_IRQn                      = 18,       /*!< eNVM1 operation completion interrupt                 */
  ComBlk_IRQn                     = 19,       /*!< COM block interrupt                                  */
  USB_IRQn                        = 20,       /*!< USB interrupt                                        */
  USB_DMA_IRQn                    = 21,       /*!< USB DMA interrupt                                    */
  PLL_Lock_IRQn                   = 22,       /*!< PLL lock interrupt                                   */
  PLL_LockLost_IRQn               = 23,       /*!< PLL loss of lock interrupt                           */
  CommSwitchError_IR              = 24,       /*!< Communications Switch error interrupt                */
  CacheError_IRQn                 = 25,       /*!< Cache error interrupt                                */
  DDR_IRQn                        = 26,       /*!< DDR controller interrupt                             */
  HPDMA_Complete_IRQn             = 27,       /*!< High speed DMA transfer complete interrupt           */
  HPDMA_Error_IRQn                = 28,       /*!< High speed DMA transfer error interrupt              */
  ECC_Error_IRQn                  = 29,       /*!< ECC error detected                                   */
  MDDR_IOCalib_IRQn               = 30,       /*!< MDDR Calibration finished interrupt                  */
  FAB_PLL_Lock_IRQn               = 31,       /*!< MSSDDR Fabric PLL lock interrupt                   */
  FAB_PLL_LockLost_IRQn           = 32,       /*!< MSSDDR Fabric PLL lock lost interrupt              */
  FIC64_IRQn                      = 33,       /*!< FIC64 interrupt                                      */
  FabricIrq0_IRQn                 = 34,       /*!< FPGA fabric interrupt 0                              */
  FabricIrq1_IRQn                 = 35,       /*!< FPGA fabric interrupt 1                              */
  FabricIrq2_IRQn                 = 36,       /*!< FPGA fabric interrupt 2                              */
  FabricIrq3_IRQn                 = 37,       /*!< FPGA fabric interrupt 3                              */
  FabricIrq4_IRQn                 = 38,       /*!< FPGA fabric interrupt 4                              */
  FabricIrq5_IRQn                 = 39,       /*!< FPGA fabric interrupt 5                              */
  FabricIrq6_IRQn                 = 40,       /*!< FPGA fabric interrupt 6                              */
  FabricIrq7_IRQn                 = 41,       /*!< FPGA fabric interrupt 7                              */
  FabricIrq8_IRQn                 = 42,       /*!< FPGA fabric interrupt 8                              */
  FabricIrq9_IRQn                 = 43,       /*!< FPGA fabric interrupt 9                              */
  FabricIrq10_IRQn                = 44,       /*!< FPGA fabric interrupt 10                             */
  FabricIrq11_IRQn                = 45,       /*!< FPGA fabric interrupt 11                             */
  FabricIrq12_IRQn                = 46,       /*!< FPGA fabric interrupt 12                             */
  FabricIrq13_IRQn                = 47,       /*!< FPGA fabric interrupt 13                             */
  FabricIrq14_IRQn                = 48,       /*!< FPGA fabric interrupt 14                             */
  FabricIrq15_IRQn                = 49,       /*!< FPGA fabric interrupt 15                             */  
  GPIO0_IRQn                      = 50,       /*!< GPIO 0 interrupt                                     */
  GPIO1_IRQn                      = 51,       /*!< GPIO 1 interrupt                                     */
  GPIO2_IRQn                      = 52,       /*!< GPIO 2 interrupt                                     */
  GPIO3_IRQn                      = 53,       /*!< GPIO 3 interrupt                                     */
  GPIO4_IRQn                      = 54,       /*!< GPIO 4 interrupt                                     */
  GPIO5_IRQn                      = 55,       /*!< GPIO 5 interrupt                                     */
  GPIO6_IRQn                      = 56,       /*!< GPIO 6 interrupt                                     */
  GPIO7_IRQn                      = 57,       /*!< GPIO 7 interrupt                                     */
  GPIO8_IRQn                      = 58,       /*!< GPIO 8 interrupt                                     */
  GPIO9_IRQn                      = 59,       /*!< GPIO 9 interrupt                                     */
  GPIO10_IRQn                     = 60,       /*!< GPIO 10 interrupt                                    */
  GPIO11_IRQn                     = 61,       /*!< GPIO 11 interrupt                                    */
  GPIO12_IRQn                     = 62,       /*!< GPIO 12 interrupt                                    */
  GPIO13_IRQn                     = 63,       /*!< GPIO 13 interrupt                                    */
  GPIO14_IRQn                     = 64,       /*!< GPIO 14 interrupt                                    */
  GPIO15_IRQn                     = 65,       /*!< GPIO 15 interrupt                                    */
  GPIO16_IRQn                     = 66,       /*!< GPIO 16 interrupt                                    */
  GPIO17_IRQn                     = 67,       /*!< GPIO 17 interrupt                                    */
  GPIO18_IRQn                     = 68,       /*!< GPIO 18 interrupt                                    */
  GPIO19_IRQn                     = 69,       /*!< GPIO 19 interrupt                                    */
  GPIO20_IRQn                     = 70,       /*!< GPIO 20 interrupt                                    */
  GPIO21_IRQn                     = 71,       /*!< GPIO 21 interrupt                                    */
  GPIO22_IRQn                     = 72,       /*!< GPIO 22 interrupt                                    */
  GPIO23_IRQn                     = 73,       /*!< GPIO 23 interrupt                                    */
  GPIO24_IRQn                     = 74,       /*!< GPIO 24 interrupt                                    */
  GPIO25_IRQn                     = 75,       /*!< GPIO 25 interrupt                                    */ 
  GPIO26_IRQn                     = 76,       /*!< GPIO 26 interrupt                                    */
  GPIO27_IRQn                     = 77,       /*!< GPIO 27 interrupt                                    */
  GPIO28_IRQn                     = 78,       /*!< GPIO 28 interrupt                                    */
  GPIO29_IRQn                     = 79,       /*!< GPIO 29 interrupt                                    */
  GPIO30_IRQn                     = 80,       /*!< GPIO 30 interrupt                                    */
  GPIO31_IRQn                     = 81        /*!< GPIO 31 interrupt                                    */
} IRQn_Type;

/*
 * ==========================================================================
 * ----------- Processor and Core Peripheral Section ------------------------
 * ==========================================================================
 */
#define __CM3_REV                 0x0201    /*!< Core revision r2p1                              */
#define __MPU_PRESENT             1         /*!< MPU present or not                              */
#define __NVIC_PRIO_BITS          4         /*!< Number of Bits used for Priority Levels         */
#define __Vendor_SysTickConfig    0         /*!< Set to 1 if different SysTick Config is used    */

#include <core_cm3.h>   /* Cortex-M3 processor and core peripherals           */

/******************************************************************************/
/*                Device Specific Peripheral registers structures             */
/******************************************************************************/
#if defined   ( __CC_ARM   )
  /* Enable anonymous unions when building using Keil-MDK */
  #pragma anon_unions
#endif

/*----------------------------------------------------------------------------*/
/*----------------------------------- UART -----------------------------------*/
/*----------------------------------------------------------------------------*/
typedef struct
{
    union
    {
        __I  uint8_t    RBR;
        __O  uint8_t    THR;
        __IO uint8_t    DLR;
             uint32_t   RESERVED0;
    };

    union
    {
        __IO uint8_t  DMR;
        __IO uint8_t  IER;
             uint32_t RESERVED1;
    };

    union
    {
        __IO uint8_t  IIR;
        __IO uint8_t  FCR;
             uint32_t RESERVED2;
    };

    __IO uint8_t  LCR;
         uint8_t  RESERVED3[3];

    __IO uint8_t  MCR;
         uint8_t  RESERVED4[3];

    __I  uint8_t  LSR;
         uint8_t  RESERVED5[3];

    __I  uint8_t  MSR;
         uint8_t  RESERVED6[3];

    __IO uint8_t  SR;
         uint8_t  RESERVED7[7];

    __IO uint8_t  IEM;
         uint8_t  RESERVED8[3];

    __IO uint8_t  IIM;
         uint8_t  RESERVED9[7];

    __IO uint8_t  MM0;
         uint8_t  RESERVED10[3];

    __IO uint8_t  MM1;
         uint8_t  RESERVED11[3];

    __IO uint8_t  MM2;
         uint8_t  RESERVED12[3];

    __IO uint8_t  DFR;
         uint8_t  RESERVED13[7];

     __IO uint8_t GFR;
         uint8_t  RESERVED14[3];

     __IO uint8_t TTG;
         uint8_t  RESERVED15[3];

     __IO uint8_t RTO;
         uint8_t  RESERVED16[3];

     __IO uint8_t ADR;
         uint8_t  RESERVED17[3];

} UART_TypeDef;

/*----------------------------------------------------------------------------*/
/*----------------------------------- I2C ------------------------------------*/
/*----------------------------------------------------------------------------*/
typedef struct
{
    __IO uint8_t  CTRL;
         uint8_t  RESERVED0;
         uint16_t RESERVED1;
         uint8_t  STATUS;
         uint8_t  RESERVED2;
         uint16_t RESERVED3;
    __IO uint8_t  DATA;
         uint8_t  RESERVED4;
         uint16_t RESERVED5;
    __IO uint8_t  ADDR;
         uint8_t  RESERVED6;
         uint16_t RESERVED7;
    __IO uint8_t  SMBUS;
         uint8_t  RESERVED8;
         uint16_t RESERVED9;
    __IO uint8_t  FREQ;
         uint8_t  RESERVED10;
         uint16_t RESERVED11;
    __IO uint8_t  GLITCHREG;
         uint8_t  RESERVED12;
         uint16_t RESERVED13;
    __IO uint8_t  SLAVE1_ADDR;
         uint8_t  RESERVED14;
         uint16_t RESERVED15;
} I2C_TypeDef;

/*------------------------------------------------------------------------------
 * I2C bit band
 */
typedef struct
{
    __IO uint32_t CTRL_CR0;
    __IO uint32_t CTRL_CR1;
    __IO uint32_t CTRL_AA;
    __IO uint32_t CTRL_SI;
    __IO uint32_t CTRL_STO;
    __IO uint32_t CTRL_STA;
    __IO uint32_t CTRL_ENS1;
    __IO uint32_t CTRL_CR2;
         uint32_t RESERVED0[56];
    __IO uint32_t DATA_DIR;
         uint32_t RESERVED1[31];
    __IO uint32_t ADDR_GC;
} I2C_BitBand_TypeDef;

/*----------------------------------------------------------------------------*/
/*----------------------------------- SPI ------------------------------------*/
/*----------------------------------------------------------------------------*/
typedef struct
{
    __IO uint32_t CONTROL;
    __IO uint32_t TXRXDF_SIZE;
    __I  uint32_t STATUS;
    __O  uint32_t INT_CLEAR;
    __I  uint32_t RX_DATA;
    __O  uint32_t TX_DATA;
    __IO uint32_t CLK_GEN;
    __IO uint32_t SLAVE_SELECT;
    __I  uint32_t MIS;
    __I  uint32_t RIS;
    __IO uint32_t CONTROL2;
    __IO uint32_t COMMAND;
    __IO uint32_t PKTSIZE;
    __IO uint32_t CMDSIZE;
    __IO uint32_t HWSTATUS;
    __IO uint32_t STAT8;
    __IO uint32_t CTRL0;
    __IO uint32_t CTRL1;
    __IO uint32_t CTRL2;
    __IO uint32_t CTRL3;
} SPI_TypeDef;

/*----------------------------------------------------------------------------*/
/*----------------------------------- GPIO -----------------------------------*/
/*----------------------------------------------------------------------------*/
typedef struct
{
    __IO uint32_t GPIO_0_CFG;
    __IO uint32_t GPIO_1_CFG;
    __IO uint32_t GPIO_2_CFG;
    __IO uint32_t GPIO_3_CFG;
    __IO uint32_t GPIO_4_CFG;
    __IO uint32_t GPIO_5_CFG;
    __IO uint32_t GPIO_6_CFG;
    __IO uint32_t GPIO_7_CFG;
    __IO uint32_t GPIO_8_CFG;
    __IO uint32_t GPIO_9_CFG;
    __IO uint32_t GPIO_10_CFG;
    __IO uint32_t GPIO_11_CFG;
    __IO uint32_t GPIO_12_CFG;
    __IO uint32_t GPIO_13_CFG;
    __IO uint32_t GPIO_14_CFG;
    __IO uint32_t GPIO_15_CFG;
    __IO uint32_t GPIO_16_CFG;
    __IO uint32_t GPIO_17_CFG;
    __IO uint32_t GPIO_18_CFG;
    __IO uint32_t GPIO_19_CFG;
    __IO uint32_t GPIO_20_CFG;
    __IO uint32_t GPIO_21_CFG;
    __IO uint32_t GPIO_22_CFG;
    __IO uint32_t GPIO_23_CFG;
    __IO uint32_t GPIO_24_CFG;
    __IO uint32_t GPIO_25_CFG;
    __IO uint32_t GPIO_26_CFG;
    __IO uint32_t GPIO_27_CFG;
    __IO uint32_t GPIO_28_CFG;
    __IO uint32_t GPIO_29_CFG;
    __IO uint32_t GPIO_30_CFG;
    __IO uint32_t GPIO_31_CFG;
    __IO uint32_t GPIO_IRQ;
    __I  uint32_t GPIO_IN;
    __IO uint32_t GPIO_OUT;
} GPIO_TypeDef;

/*------------------------------------------------------------------------------
 * GPIO bit band
 */
typedef struct
{
    __IO uint32_t GPIO_0_CFG[32];
    __IO uint32_t GPIO_1_CFG[32];
    __IO uint32_t GPIO_2_CFG[32];
    __IO uint32_t GPIO_3_CFG[32];
    __IO uint32_t GPIO_4_CFG[32];
    __IO uint32_t GPIO_5_CFG[32];
    __IO uint32_t GPIO_6_CFG[32];
    __IO uint32_t GPIO_7_CFG[32];
    __IO uint32_t GPIO_8_CFG[32];
    __IO uint32_t GPIO_9_CFG[32];
    __IO uint32_t GPIO_10_CFG[32];
    __IO uint32_t GPIO_11_CFG[32];
    __IO uint32_t GPIO_12_CFG[32];
    __IO uint32_t GPIO_13_CFG[32];
    __IO uint32_t GPIO_14_CFG[32];
    __IO uint32_t GPIO_15_CFG[32];
    __IO uint32_t GPIO_16_CFG[32];
    __IO uint32_t GPIO_17_CFG[32];
    __IO uint32_t GPIO_18_CFG[32];
    __IO uint32_t GPIO_19_CFG[32];
    __IO uint32_t GPIO_20_CFG[32];
    __IO uint32_t GPIO_21_CFG[32];
    __IO uint32_t GPIO_22_CFG[32];
    __IO uint32_t GPIO_23_CFG[32];
    __IO uint32_t GPIO_24_CFG[32];
    __IO uint32_t GPIO_25_CFG[32];
    __IO uint32_t GPIO_26_CFG[32];
    __IO uint32_t GPIO_27_CFG[32];
    __IO uint32_t GPIO_28_CFG[32];
    __IO uint32_t GPIO_29_CFG[32];
    __IO uint32_t GPIO_30_CFG[32];
    __IO uint32_t GPIO_31_CFG[32];
    __IO uint32_t GPIO_IRQ[32];
    __I  uint32_t GPIO_IN[32];
    __IO uint32_t GPIO_OUT[32];
} GPIO_BitBand_TypeDef;


/*----------------------------------------------------------------------------*/
/*--------------------------------- HPDMA ------------------------------------*/
/*----------------------------------------------------------------------------*/

typedef struct
{
    __IO uint32_t HPDMASAR_REG              ;
    __IO uint32_t HPDMADAR_REG              ;
    __IO uint32_t HPDMACR_REG               ;
    __I  uint32_t HPDMASR_REG               ;
    __I  uint32_t HPDMAPTR_REG              ;
}HPDMA_Descriptor_TypeDef;

typedef struct
{
    __I  uint32_t HPDMAEDR_REG              ;
    HPDMA_Descriptor_TypeDef  Descriptor[4] ;
    __O  uint32_t HPDMAICR_REG              ;
    __I  uint32_t HPDMADR_REG               ;
} HPDMA_TypeDef;

typedef struct
{
         uint32_t RESERVED0[64];
    __IO uint32_t HPDMACR_XFR_SIZE[16]     ;
    __IO uint32_t HPDMACR_DCP_VALID        ;
    __IO uint32_t HPDMACR_DCP_XFR_DIR      ;
    __IO uint32_t HPDMACR_DCP_CLR          ;
    __IO uint32_t HPDMACR_DCP_PAUSE        ;
    __IO uint32_t HPDMACR_XFR_CMP_INT      ;
    __IO uint32_t HPDMACR_XFR_ERR_INT      ;
    __IO uint32_t HPDMACR_NON_WORD_INT     ;
         uint32_t RESERVED1[9];

    __I  uint32_t HPDMASR_DCP_ACTIVE       ;
    __I  uint32_t HPDMASR_DCP_CMPLET       ;
    __I  uint32_t HPDMASR_DCP_SERR         ;
    __I  uint32_t HPDMASR_DCP_DERR         ;
         uint32_t RESERVED2[60]            ;
}HPDMA_Descriptor_BitBand_TypeDef;

/*------------------------------------------------------------------------------
 * HPDMA bit band
 */
typedef struct
{
    __I  uint32_t HPDMAEDR_DCP_EMPTY[4]           ;
    __I  uint32_t HPDMAEDR_DCP_CMPLET[4]          ;
    __I  uint32_t HPDMAEDR_DCP_ERR[4]             ;
    __I  uint32_t HPDMAEDR_DCP_NON_WORD_ERR[4]    ;
         uint32_t RESERVED0[16]                   ;

    HPDMA_Descriptor_BitBand_TypeDef Descriptor[4];

    __O  uint32_t HPDMAICR_CLR_XFR_INT[4]         ;
    __O  uint32_t HPDMAICR_NON_WORD_INT[4]        ;
         uint32_t RESERVED1[16]                   ;

    __I  uint32_t HPDMADR_BFR_EMPTY               ;
    __I  uint32_t HPDMADR_BFR_FULL                ;
    __I  uint32_t HPDMADR_BFR_RD_PNTR[3]          ;
    __I  uint32_t HPDMADR_BFR_WR_PNTR [3]         ;
    __I  uint32_t HPDMADR_AHM1_CST_DBG[4]         ;
    __I  uint32_t HPDMADR_AHM2_CST_DBG[4]         ;
    __I  uint32_t HPDMADR_WBC_CST_DBG[3]          ;
    __I  uint32_t HPDMADR_RBC_CST_DBG[3]          ;
    __I  uint32_t HPDMADR_RRBN_CST_DBG[4]         ;
    __I  uint32_t HPDMADR_DMA_CST_DBG[4]          ;

         uint32_t RESERVED2[4]                    ;
}HPDMA_BitBand_TypeDef;

/*----------------------------------------------------------------------------*/
/*----------------------------------- RTC ------------------------------------*/
/*----------------------------------------------------------------------------*/
typedef struct
{
    __IO uint32_t CONTROL_REG             ;
    __IO uint32_t MODE_REG                ;
    __IO uint32_t PRESCALER_REG           ;
    __IO uint32_t ALARM_LOWER_REG         ;
    __IO uint32_t ALARM_UPPER_REG         ;
    __IO uint32_t COMPARE_LOWER_REG       ;
    __IO uint32_t COMPARE_UPPER_REG       ;
         uint32_t RESERVED0               ;
    __IO uint32_t DATE_TIME_LOWER_REG     ;
    __IO uint32_t DATE_TIME_UPPER_REG     ;

         uint32_t RESERVED1[2]            ;
    __IO uint32_t SECONDS_REG             ;
    __IO uint32_t MINUTES_REG             ;
    __IO uint32_t HOURS_REG               ;
    __IO uint32_t DAY_REG                 ;
    __IO uint32_t MONTH_REG               ;
    __IO uint32_t YEAR_REG                ;
    __IO uint32_t WEEKDAY_REG             ;
    __IO uint32_t WEEK_REG                ;

    __IO uint32_t SECONDS_CNT_REG         ;
    __IO uint32_t MINUTES_CNT_REG         ;
    __IO uint32_t HOURS_CNT_REG           ;
    __IO uint32_t DAY_CNT_REG             ;
    __IO uint32_t MONTH_CNT_REG           ;
    __IO uint32_t YEAR_CNT_REG            ;
    __IO uint32_t WEEKDAY_CNT_REG         ;
    __IO uint32_t WEEK_CNT_REG            ;
} RTC_TypeDef;

/*----------------------------------------------------------------------------*/
/*---------------------------------- Timer -----------------------------------*/
/*----------------------------------------------------------------------------*/
typedef struct
{
    __I  uint32_t TIM1_VAL;
    __IO uint32_t TIM1_LOADVAL;
    __IO uint32_t TIM1_BGLOADVAL;
    __IO uint32_t TIM1_CTRL;
    __IO uint32_t TIM1_RIS;
    __I  uint32_t TIM1_MIS;

    __I  uint32_t TIM2_VAL;
    __IO uint32_t TIM2_LOADVAL;
    __IO uint32_t TIM2_BGLOADVAL;
    __IO uint32_t TIM2_CTRL;
    __IO uint32_t TIM2_RIS;
    __I  uint32_t TIM2_MIS;

    __I  uint32_t TIM64_VAL_U;
    __I  uint32_t TIM64_VAL_L;
    __IO uint32_t TIM64_LOADVAL_U;
    __IO uint32_t TIM64_LOADVAL_L;
    __IO uint32_t TIM64_BGLOADVAL_U;
    __IO uint32_t TIM64_BGLOADVAL_L;
    __IO uint32_t TIM64_CTRL;
    __IO uint32_t TIM64_RIS;
    __I  uint32_t TIM64_MIS;
    __IO uint32_t TIM64_MODE;
} TIMER_TypeDef;

/*------------------------------------------------------------------------------
 * Timer bit band
 */
typedef struct
{
    __I  uint32_t TIM1_VALUE_BIT[32];
    __IO uint32_t TIM1_LOADVAL[32];
    __IO uint32_t TIM1_BGLOADVAL[32];

    __IO uint32_t TIM1ENABLE;
    __IO uint32_t TIM1MODE;
    __IO uint32_t TIM1INTEN;
    __IO uint32_t TIM1_CTRL_RESERVED[29];
    __IO uint32_t TIM1_RIS[32];
    __I  uint32_t TIM1_MIS[32];

    __I  uint32_t TIM2_VALUE[32];
    __IO uint32_t TIM2_LOADVAL[32];
    __IO uint32_t TIM2_BGLOADVAL[32];

    __IO uint32_t TIM2ENABLE;
    __IO uint32_t TIM2MODE;
    __IO uint32_t TIM2INTEN;
    __IO uint32_t TIM2_CTRL[29];
    __IO uint32_t TIM2_RIS[32];
    __I  uint32_t TIM2_MIS[32];

    __I  uint32_t TIM64VALUEU[32];
    __I  uint32_t TIM64VALUEL[32];
    __IO uint32_t TIM64LOADVALUEU[32];
    __IO uint32_t TIM64LOADVALUEL[32];
    __IO uint32_t TIM64BGLOADVALUEU[32];
    __IO uint32_t TIM64BGLOADVALUEL[32];
    __IO uint32_t TIM64ENABLE;
    __IO uint32_t TIM64MODE;
    __IO uint32_t TIM64INTEN;
    __IO uint32_t TIM64_CTRL[29];
    __IO uint32_t TIM64_RIS[32];
    __I  uint32_t TIM64_MIS[32];
    __IO uint32_t TIM64_MODE[32];
} TIMER_BitBand_TypeDef;

/*----------------------------------------------------------------------------*/
/*--------------------------------- Watchdog ---------------------------------*/
/*----------------------------------------------------------------------------*/
typedef struct
{
    __I  uint32_t WDOGVALUE;
    __I  uint32_t WDOGLOAD;
    __I  uint32_t WDOGMVRP;
    __O  uint32_t WDOGREFRESH;
    __I  uint32_t WDOGENABLE;
    __IO uint32_t WDOGCONTROL;
    __I  uint32_t WDOGSTATUS;
    __IO uint32_t WDOGRIS;
    __I  uint32_t WDOGMIS;
} WATCHDOG_TypeDef;

/*----------------------------------------------------------------------------*/
/*----------------------------- Real Time Clock ------------------------------*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*----------------------------- Peripherals DMA ------------------------------*/
/*----------------------------------------------------------------------------*/
typedef struct
{
    __IO uint32_t CRTL;
    __IO uint32_t STATUS;
    __IO uint32_t BUFFER_A_SRC_ADDR;
    __IO uint32_t BUFFER_A_DEST_ADDR;
    __IO uint32_t BUFFER_A_TRANSFER_COUNT;
    __IO uint32_t BUFFER_B_SRC_ADDR;
    __IO uint32_t BUFFER_B_DEST_ADDR;
    __IO uint32_t BUFFER_B_TRANSFER_COUNT;
} PDMA_Channel_TypeDef;

typedef struct
{
    __IO uint32_t RATIO_HIGH_LOW;
    __IO uint32_t BUFFER_STATUS;
         uint32_t RESERVED[6];
    PDMA_Channel_TypeDef CHANNEL[8];
} PDMA_TypeDef;

/*----------------------------------------------------------------------------*/
/*------------------------------ Ethernet MAC --------------------------------*/
/*----------------------------------------------------------------------------*/
typedef struct
{
	/* 
     * MAC registers (MCXMAC)
     */
    __IO uint32_t CFG1;
    __IO uint32_t CFG2;
    __IO uint32_t IFG;
    __IO uint32_t HALF_DUPLEX;
    __IO uint32_t MAX_FRAME_LENGTH;
         uint32_t RESERVED0[2];
    __IO uint32_t TEST;
    __IO uint32_t MII_CONFIG;
    __IO uint32_t MII_COMMAND;
    __IO uint32_t MII_ADDRESS;
    __O  uint32_t MII_CTRL;
    __I  uint32_t MII_STATUS;
    __I  uint32_t MII_INDICATORS;
    __IO uint32_t INTERFACE_CTRL;
    __I  uint32_t INTERFACE_STATUS;
    __IO uint32_t STATION_ADDRESS1;
    __IO uint32_t STATION_ADDRESS2;
    /* 
     * FIFO Configuration / Access registers (MCXFIF)
     */
    __IO uint32_t FIFO_CFG0;
    __IO uint32_t FIFO_CFG1;
    __IO uint32_t FIFO_CFG2;
    __IO uint32_t FIFO_CFG3;
    __IO uint32_t FIFO_CFG4;
    __IO uint32_t FIFO_CFG5;
    __IO uint32_t FIFO_RAM_ACCESS0;
    __IO uint32_t FIFO_RAM_ACCESS1;
    __IO uint32_t FIFO_RAM_ACCESS2;
    __I  uint32_t FIFO_RAM_ACCESS3;
    __IO uint32_t FIFO_RAM_ACCESS4;
    __IO uint32_t FIFO_RAM_ACCESS5;
    __IO uint32_t FIFO_RAM_ACCESS6;
    __I  uint32_t FIFO_RAM_ACCESS7;
    /*
     * Statistics registers (MSTAT)
     */
    __IO uint32_t TR64;
    __IO uint32_t TR127;
    __IO uint32_t TR255;
    __IO uint32_t TR511;
    __IO uint32_t TR1K;
    __IO uint32_t TRMAX;
    __IO uint32_t TRMGV;
    __IO uint32_t RBYT;
    __IO uint32_t PPKT;
    __IO uint32_t RFCS;
    __IO uint32_t RMCA;
    __IO uint32_t RBCA;
    __IO uint32_t RXCF;
    __IO uint32_t RXPF;
    __IO uint32_t RXUO;
    __IO uint32_t RALN;
    __IO uint32_t RFLR;
    __IO uint32_t RCDE;
    __IO uint32_t RCSE;
    __IO uint32_t RUND;
    __IO uint32_t ROVR;
    __IO uint32_t RFRG;
    __IO uint32_t RJBR;
    __IO uint32_t RDRP;
    __IO uint32_t TBYT;
    __IO uint32_t TPKT;
    __IO uint32_t TMCA;
    __IO uint32_t TBCA;
    __IO uint32_t TXPF;
    __IO uint32_t TDFR;
    __IO uint32_t TEDF;
    __IO uint32_t TSCL;
    __IO uint32_t TMCL;
    __IO uint32_t TLCL;
    __IO uint32_t TXCL;
    __IO uint32_t TNCL;
    __IO uint32_t TPFH;
    __IO uint32_t TDRP;
    __IO uint32_t TJBR;
    __IO uint32_t TFCS;
    __IO uint32_t TXCF;
    __IO uint32_t TOVR;
    __IO uint32_t TUND;
    __IO uint32_t TFRG;
    __I  uint32_t CAR1;
    __I  uint32_t CAR2;
    __IO uint32_t CAM1;
    __IO uint32_t CAM2;
     uint32_t RESERVED1[16];
    /*
     * DMA registers (MAHBE)
     */
    __IO uint32_t DMA_TX_CTRL;
    __IO uint32_t DMA_TX_DESC;
    __IO uint32_t DMA_TX_STATUS;
    __IO uint32_t DMA_RX_CTRL;
    __IO uint32_t DMA_RX_DESC;
    __IO uint32_t DMA_RX_STATUS;
    __IO uint32_t DMA_IRQ_MASK;
    __I  uint32_t DMA_IRQ;
} MAC_TypeDef;

/*----------------------------------------------------------------------------*/
/*------------------------------ USB --------------------------------*/
/*----------------------------------------------------------------------------*/
typedef struct
{
    __IO uint16_t   TX_MAX_P;
    __IO uint16_t   TX_CSR;  
    __IO uint16_t   RX_MAX_P;
    __IO uint16_t   RX_CSR;  
    __IO uint16_t   RX_COUNT;
    __IO uint8_t    TX_TYPE; 
    __IO uint8_t    TX_INTERVAL;
    __IO uint8_t    RX_TYPE;    
    __IO uint8_t    RX_INTERVAL;
    __IO uint8_t    RESERVED;
    __IO uint8_t    FIFO_SIZE;  
} USB_endpoint_regs_t;

typedef struct
{
    __IO uint8_t    TX_FUNC_ADDR;
    __IO uint8_t    UNUSED0;
    __IO uint8_t    TX_HUB_ADDR;
    __IO uint8_t    TX_HUB_PORT;
    __IO uint8_t    RX_FUNC_ADDR;
    __IO uint8_t    UNUSED1;
    __IO uint8_t    RX_HUB_ADDR;
    __IO uint8_t    RX_HUB_PORT;
} USB_tar_t;

typedef union
{
    struct
    {
        __IO uint32_t   VALUE;
    } WORD;

    struct
    {
        __IO uint8_t    VALUE;
        __IO uint8_t    RESERVED1;
        __IO uint8_t    RESERVED2;
        __IO uint8_t    RESERVED3;
    } BYTE;

    struct
    {
        __IO uint16_t   VALUE;
        __IO uint16_t   RESERVED;
    } HALFWORD;
} USB_fifo_t;

typedef union
{
    struct                          
    {
        __IO uint16_t   TX_MAX_P;   
        __IO uint16_t   CSR0;       
        __IO uint16_t   RX_MAX_P;   
        __IO uint16_t   RX_CSR;     
        __IO uint16_t   COUNT0;     
        __IO uint8_t    RESERVED0;
        __IO uint8_t    RESERVED1;
        __IO uint8_t    RESERVED2;
        __IO uint8_t    RESERVED3;
        __IO uint8_t    RESERVED4;
        __IO uint8_t    CONFIG_DATA;  
    } DEVICE_EP0;

    struct                            
    {
        __IO uint16_t   TX_MAX_P;
        __IO uint16_t   TX_CSR;
        __IO uint16_t   RX_MAX_P;
        __IO uint16_t   RX_CSR;
        __IO uint16_t   RX_COUNT;
        __IO uint8_t    RESERVED0;
        __IO uint8_t    RESERVED1;
        __IO uint8_t    RESERVED2;
        __IO uint8_t    RESERVED3;
        __IO uint8_t    RESERVED4;
        __IO uint8_t    FIFO_SIZE;
    } DEVICE_EPN;

    struct                          
    {
        __IO uint16_t   TX_MAX_P;
        __IO uint16_t   CSR0;
        __IO uint16_t   RX_MAX_P;
        __IO uint16_t   RX_CSR;
        __IO uint16_t   COUNT0;
        __IO uint8_t    TYPE0;
        __IO uint8_t    NAK_LIMIT0;
        __IO uint8_t    RX_TYPE;
        __IO uint8_t    RX_INTERVAL;
        __IO uint8_t    RESERVED0;
        __IO uint8_t    CONFIG_DATA;
    } HOST_EP0;

    struct                          
    {
        __IO uint16_t   TX_MAX_P;
        __IO uint16_t   TX_CSR;
        __IO uint16_t   RX_MAX_P;
        __IO uint16_t   RX_CSR;
        __IO uint16_t   RX_COUNT;
        __IO uint8_t    TX_TYPE;
        __IO uint8_t    TX_INTERVAL;
        __IO uint8_t    RX_TYPE;
        __IO uint8_t    RX_INTERVAL;
        __IO uint8_t    RESERVED0;
        __IO uint8_t    FIFO_SIZE;
    } HOST_EPN;

} USB_indexed_csr_t;

typedef struct {
    __IO uint32_t   IRQ;    
    __IO uint32_t   CNTL;
    __IO uint32_t   ADDR;
    __IO uint32_t   COUNT;
} USB_DMA_channel;

typedef struct
{
    /* 
    * Common USB Registers 
    */
    __IO uint8_t    FADDR;            
    __IO uint8_t    POWER;            
    __IO uint16_t   TX_IRQ;           
    __IO uint16_t   RX_IRQ;           
    __IO uint16_t   TX_IRQ_ENABLE;    
    __IO uint16_t   RX_IRQ_ENABLE;    
    __IO uint8_t    USB_IRQ;          
    __IO uint8_t    USB_ENABLE;       
    __IO uint16_t   FRAME;            
    __IO uint8_t    INDEX;            
    __IO uint8_t    TEST_MODE;        

    /*
    * Indexed CSR
    */
    USB_indexed_csr_t   INDEXED_CSR;

    /*
    * Endpoint FIFOs 
    */
    USB_fifo_t      FIFO[16];         

    /*
    * OTG, dynamic FIFO and version 
    */
    __IO uint8_t    DEV_CTRL;         
    __IO uint8_t    MISC;             
    __IO uint8_t    TX_FIFO_SIZE;     
    __IO uint8_t    RX_FIFO_SIZE;     
    __IO uint16_t   TX_FIFO_ADDR;     
    __IO uint16_t   RX_FIFO_ADDR;     
    __IO uint32_t   VBUS_CSR;         
    __IO uint16_t   HW_VERSION;       
    __IO uint16_t   RESERVED;         

    /* 
    * ULPI and configuration registers 
    */
    __IO uint8_t    ULPI_VBUS_CTRL;   
    __IO uint8_t    ULPI_CARKIT_CTRL; 
    __IO uint8_t    ULPI_IRQ_MASK;    
    __IO uint8_t    ULPI_IRQ_SRC;     
    __IO uint8_t    ULPI_DATA_REG;    
    __IO uint8_t    ULPI_ADDR_REG;    
    __IO uint8_t    ULPI_CTRL_REG;    
    __IO uint8_t    ULPI_RAW_DATA;    
    __IO uint8_t    EP_INFO;          
    __IO uint8_t    RAM_INFO;         
    __IO uint8_t    LINK_INFO;        
    __IO uint8_t    VP_LEN;           
    __IO uint8_t    HS_EOF1;          
    __IO uint8_t    FS_EOF1;          
    __IO uint8_t    LS_EOF1;          
    __IO uint8_t    SOFT_RST;         

    /* 
    * Target Address registers 
    */
    USB_tar_t       TAR[16];          

    /* 
    * Endpoints CSR 
    */
    USB_endpoint_regs_t ENDPOINT[16]; 

    /* 
    * DMA 
    */
    USB_DMA_channel DMA_CHANNEL[8];
	
    __IO uint32_t   RESERVED_EXT[32];
    __IO uint32_t   RQ_PKT_CNT[16];   
    __IO uint16_t   RX_DPBUF_DIS;
    __IO uint16_t   TX_DPBUF_DIS;
    __IO uint16_t   C_T_UCH;
    __IO uint16_t   C_T_HHSRTN;
    __IO uint16_t   C_T_HSBT;

} MSS_USB_TypeDef;

/*----------------------------------------------------------------------------*/
/*---------------------- eNVM Special Function Registers ---------------------*/
/*----------------------------------------------------------------------------*/
typedef struct
{
    __I  uint8_t  AB[128];
    __IO uint8_t  WD[128];
    __I  uint8_t  RESERVED0[32];
    __I  uint32_t STATUS;
    __IO uint32_t RESERVED1;
    __IO uint32_t NV_PAGE_STATUS;
    __I  uint32_t NV_FREQRNG;
    __I  uint32_t NV_DPD;
    __IO uint32_t NV_CE;
         uint32_t RESERVED2;
    __IO uint32_t RESERVED3;
    __IO uint32_t PAGE_LOCK;
    __IO uint32_t DWSIZE;
    __IO uint32_t CMD;
    __IO uint32_t RESERVED4;
    __I  uint32_t RESERVED5;
    __IO uint32_t INTEN;
    __IO uint32_t CLRHINT;
         uint32_t RESERVED6[40];
    __IO uint32_t REQ_ACCESS;
} NVM_TypeDef;

typedef struct
{
    __I  uint32_t AB[32];
    __IO uint32_t WD[32];
    __I  uint32_t RESERVED0[8];
    __I  uint32_t STATUS;
    __IO uint32_t RESERVED1;
    __IO uint32_t NV_PAGE_STATUS;
    __I  uint32_t NV_FREQRNG;
    __I  uint32_t NV_DPD;
    __IO uint32_t NV_CE;
         uint32_t RESERVED2;
    __IO uint32_t RESERVED3;
    __IO uint32_t PAGE_LOCK;
    __IO uint32_t DWSIZE;
    __IO uint32_t CMD;
    __IO uint32_t RESERVED4;
    __I  uint32_t RESERVED5;
    __IO uint32_t INTEN;
    __IO uint32_t CLRHINT;
         uint32_t RESERVED6[40];
    __IO uint32_t REQ_ACCESS;
} NVM32_TypeDef;

/*----------------------------------------------------------------------------*/
/*---------------------------------- COMBLK ----------------------------------*/
/*----------------------------------------------------------------------------*/
typedef struct
{
    __IO uint32_t CONTROL;
    __IO uint32_t STATUS;
    __IO uint32_t INT_ENABLE;
    __IO uint32_t RESERVED;
    __IO uint32_t DATA8;
    __IO uint32_t DATA32;
    __IO uint32_t FRAME_START8;
    __IO uint32_t FRAME_START32;
} COMBLK_TypeDef;

/*----------------------------------------------------------------------------*/
/*--------------------- FPGA Fabric Interrupt Controller ---------------------*/
/*----------------------------------------------------------------------------*/
/*
 * Please refer to the SmartFusion2 Interrupt Controller User's Guide for a
 * description of the following registers.
 * The registers defined below can be accessed using INTERRUPT_CTRL as follows:
 *      uint32_t reason0;
 *      INTERRUPT_CTRL->INTERRUPT_MODE = 0;
 *      reason0 = INTERRUPT_CTRL->INTERRUPT_REASON0;
 */
typedef struct
{
    __IO uint32_t INTERRUPT_ENABLE0;
    __IO uint32_t INTERRUPT_ENABLE1;
    __IO uint32_t INTERRUPT_REASON0;
    __IO uint32_t INTERRUPT_REASON1;
    __IO uint32_t INTERRUPT_MODE;
} INTERRUPT_CTRL_TypeDef;

/*
 * Please refer to the SmartFusion2 Interrupt Controller User's Guide for a
 * description of the following register bits.
 * The register bits defined below can be accessed using INTERRUPT_CTRL_BITBAND
 * as follows:
 *  setting/clearing a bit:
 *      INTERRUPT_CTRL_BITBAND->MAC_INT_ENBL = 1;
 *      INTERRUPT_CTRL_BITBAND->PDMAINTERRUPT_ENBL = 0;
 *  reading a bit value:
 *      uint32_t timer1_interrupt;
 *      timer1_interrupt = INTERRUPT_CTRL_BITBAND->TIMER1_INTR_STATUS;
 */
typedef struct
{
    /*
     * INTERRUPT_ENABLE0 register bitband definitions.
     */
    __IO uint32_t SPIINT0_ENBL;
    __IO uint32_t SPIINT1_ENBL;
    __IO uint32_t I2C_INT0_ENBL;
    __IO uint32_t I2C_INT1_ENBL;
    __IO uint32_t MMUART0_INTR_ENBL;
    __IO uint32_t MMUART1_INTR_ENBL;
    __IO uint32_t MAC_INT_ENBL;
    __IO uint32_t USB_MC_INT_ENBL;
    __IO uint32_t PDMAINTERRUPT_ENBL;
    __IO uint32_t HPD_XFR_CMP_INT_ENBL;
    __IO uint32_t TIMER1_INTR_ENBL;
    __IO uint32_t TIMER2_INTR_ENBL;
    __IO uint32_t CAN_INTR_ENBL;
    __IO uint32_t RTC_WAKEUP_INTR_ENBL;
    __IO uint32_t WDOGWAKEUPINT_ENBL;
    __IO uint32_t MSSDDR_PLL_LOCKLOST_INT_ENBL;
    __IO uint32_t ENVM_INT0_ENBL;
    __IO uint32_t ENVM_INT1_ENBL;
    __IO uint32_t I2C_SMBALERT0_ENBL;
    __IO uint32_t I2C_SMBSUS0_ENBL;
    __IO uint32_t I2C_SMBALERT1_ENBL;
    __IO uint32_t I2C_SMBSUS1_ENBL;
    __IO uint32_t HPD_XFR_ERR_INT_ENBL;
    __IO uint32_t MSSDDR_PLL_LOCK_INT_ENBL;
    __IO uint32_t SW_ERRORINTERRUPT_ENBL;
    __IO uint32_t DDRB_INTR_ENBL;
    __IO uint32_t ECCINTR_ENBL;
    __IO uint32_t CACHE_ERRINTR_ENBL;
    __IO uint32_t SOFTINTERRUPT_ENBL;
    __IO uint32_t COMBLK_INTR_ENBL;
    __IO uint32_t USB_DMA_INT_ENBL;
    __IO uint32_t RESERVED0;
    
    /*
     * INTERRUPT_ENABLE1 register bitband definitions.
     */
    __IO uint32_t RESERVED1[3];
    __IO uint32_t MDDR_IO_CALIB_INT_ENBL;
    __IO uint32_t RESERVED2;
    __IO uint32_t FAB_PLL_LOCK_INT_ENBL;
    __IO uint32_t FAB_PLL_LOCKLOST_INT_ENBL;
    __IO uint32_t FIC64_INT_ENBL;
    __IO uint32_t RESERVED3[24];
    
    /*
     * INTERRUPT_REASON0 register bitband definitions.
     */
    __IO uint32_t SPIINT0_STATUS;
    __IO uint32_t SPIINT1_STATUS;
    __IO uint32_t I2C_INT0_STATUS;
    __IO uint32_t I2C_INT1_STATUS;
    __IO uint32_t MMUART0_INTR_STATUS;
    __IO uint32_t MMUART1_INTR_STATUS;
    __IO uint32_t MAC_INT_STATUS;
    __IO uint32_t USB_MC_INT_STATUS;
    __IO uint32_t PDMAINTERRUPT_STATUS;
    __IO uint32_t HPD_XFR_CMP_INT_STATUS;
    __IO uint32_t TIMER1_INTR_STATUS;
    __IO uint32_t TIMER2_INTR_STATUS;
    __IO uint32_t CAN_INTR_STATUS;
    __IO uint32_t RTC_WAKEUP_INTR_STATUS;
    __IO uint32_t WDOGWAKEUPINT_STATUS;
    __IO uint32_t MSSDDR_PLL_LOCKLOST_INT_STATUS;
    __IO uint32_t ENVM_INT0_STATUS;
    __IO uint32_t ENVM_INT1_STATUS;
    __IO uint32_t I2C_SMBALERT0_STATUS;
    __IO uint32_t I2C_SMBSUS0_STATUS;
    __IO uint32_t I2C_SMBALERT1_STATUS;
    __IO uint32_t I2C_SMBSUS1_STATUS;
    __IO uint32_t HPD_XFR_ERR_INT_STATUS;
    __IO uint32_t MSSDDR_PLL_LOCK_INT_STATUS;
    __IO uint32_t SW_ERRORINTERRUPT_STATUS;
    __IO uint32_t DDRB_INTR_STATUS;
    __IO uint32_t ECCINTR_STATUS;
    __IO uint32_t CACHE_ERRINTR_STATUS;
    __IO uint32_t SOFTINTERRUPT_STATUS;
    __IO uint32_t COMBLK_INTR_STATUS;
    __IO uint32_t USB_DMA_INT_STATUS;
    __IO uint32_t RESERVED4;
    
    /*
     * INTERRUPT_REASON1 register bitband definitions.
     */
    __IO uint32_t RESERVED5[3];
    __IO uint32_t MDDR_IO_CALIB_INT_STATUS;
    __IO uint32_t RESERVED6;
    __IO uint32_t FAB_PLL_LOCK_INT_STATUS;
    __IO uint32_t FAB_PLL_LOCKLOST_INT_STATUS;
    __IO uint32_t FIC64_INT_STATUS;
    __IO uint32_t RESERVED7[24];
    
    /*
     * INTERRUPT_MODE register bitband definitions.
     */
    __IO uint32_t SELECT_MODE;
    __IO uint32_t RESERVED8[31];
    
} INTERRUPT_CTRL_BitBand_TypeDef;

/*----------------------------------------------------------------------------*/
/*------------------------ DDR Controller APB Registers ----------------------*/
/*----------------------------------------------------------------------------*/
typedef struct
{
    /*--------------------------------------------------------------------------
     * DDR Controller registers.
     * All registers are 16-bit wide unless mentioned beside the definition.
     */
    struct
    {
        __IO uint32_t DYN_SOFT_RESET_CR;
        __IO uint32_t RESERVED0;
        __IO uint32_t DYN_REFRESH_1_CR;
        __IO uint32_t DYN_REFRESH_2_CR;
        __IO uint32_t DYN_POWERDOWN_CR;
        __IO uint32_t DYN_DEBUG_CR;
        __IO uint32_t MODE_CR;
        __IO uint32_t ADDR_MAP_BANK_CR;
        __IO uint32_t ECC_DATA_MASK_CR;
        __IO uint32_t ADDR_MAP_COL_1_CR;
        __IO uint32_t ADDR_MAP_COL_2_CR;
        __IO uint32_t ADDR_MAP_ROW_1_CR;
        __IO uint32_t ADDR_MAP_ROW_2_CR;
        __IO uint32_t INIT_1_CR;
        __IO uint32_t CKE_RSTN_CYCLES_CR[2];     /* 0:27 bits are valid */
        __IO uint32_t INIT_MR_CR;
        __IO uint32_t INIT_EMR_CR;
        __IO uint32_t INIT_EMR2_CR;
        __IO uint32_t INIT_EMR3_CR;
        __IO uint32_t DRAM_BANK_TIMING_PARAM_CR;
        __IO uint32_t DRAM_RD_WR_LATENCY_CR;
        __IO uint32_t DRAM_RD_WR_PRE_CR;
        __IO uint32_t DRAM_MR_TIMING_PARAM_CR;
        __IO uint32_t DRAM_RAS_TIMING_CR;
        __IO uint32_t DRAM_RD_WR_TRNARND_TIME_CR;
        __IO uint32_t DRAM_T_PD_CR;
        __IO uint32_t DRAM_BANK_ACT_TIMING_CR;
        __IO uint32_t ODT_PARAM_1_CR;
        __IO uint32_t ODT_PARAM_2_CR;
        __IO uint32_t ADDR_MAP_COL_3_CR;
        __IO uint32_t MODE_REG_RD_WR_CR;
        __IO uint32_t MODE_REG_DATA_CR;
        __IO uint32_t PWR_SAVE_1_CR;
        __IO uint32_t PWR_SAVE_2_CR;
        __IO uint32_t ZQ_LONG_TIME_CR;
        __IO uint32_t ZQ_SHORT_TIME_CR;
        __IO uint32_t ZQ_SHORT_INT_REFRESH_MARGIN_CR[2];
        __IO uint32_t PERF_PARAM_1_CR;
        __IO uint32_t HPR_QUEUE_PARAM_CR[2];
        __IO uint32_t LPR_QUEUE_PARAM_CR[2];
        __IO uint32_t WR_QUEUE_PARAM_CR;
        __IO uint32_t PERF_PARAM_2_CR;
        __IO uint32_t PERF_PARAM_3_CR;
        __IO uint32_t DFI_RDDATA_EN_CR;
        __IO uint32_t DFI_MIN_CTRLUPD_TIMING_CR;
        __IO uint32_t DFI_MAX_CTRLUPD_TIMING_CR;
        __IO uint32_t DFI_WR_LVL_CONTROL_CR[2];
        __IO uint32_t DFI_RD_LVL_CONTROL_CR[2];
        __IO uint32_t DFI_CTRLUPD_TIME_INTERVAL_CR;
        __IO uint32_t DYN_SOFT_RESET_CR2;
        __IO uint32_t AXI_FABRIC_PRI_ID_CR;
        __I  uint32_t DDRC_SR;
        __I  uint32_t SINGLE_ERR_CNT_SR;
        __I  uint32_t DOUBLE_ERR_CNT_SR;
        __I  uint32_t LUE_SYNDROME_SR[5];       /* LUE : Last Uncorrected Error */
        __I  uint32_t LUE_ADDRESS_SR[2];        
        __I  uint32_t LCE_SYNDROME_SR[5];       /* LCE : Last Corrected Error */
        __I  uint32_t LCE_ADDRESS_SR[2];
        __I  uint32_t LCB_NUMBER_SR;            /* LCB : Last Corrected Bit */
        __I  uint32_t LCB_MASK_SR[4];          
        __I  uint32_t ECC_INT_SR;
        __O  uint32_t ECC_INT_CLR_REG;
        __I  uint32_t ECC_OUTPUT_DATA_SR;
        __IO uint32_t RESERVED1[46];
    } ddrc;
    
    /*--------------------------------------------------------------------------
     * DDR PHY configuration registers
     */
    struct 
    {
        __IO uint32_t DYN_BIST_TEST_CR;
        __IO uint32_t DYN_BIST_TEST_ERRCLR_CR[3];
        __IO uint32_t BIST_TEST_SHIFT_PATTERN_CR[3];
        __IO uint32_t LOOPBACK_TEST_CR;
        __IO uint32_t BOARD_LOOPBACK_CR;
        __IO uint32_t CTRL_SLAVE_RATIO_CR;
        __IO uint32_t CTRL_SLAVE_FORCE_CR;
        __IO uint32_t CTRL_SLAVE_DELAY_CR;
        __IO uint32_t DATA_SLICE_IN_USE_CR;
        __IO uint32_t LVL_NUM_OF_DQ0_CR;
        __IO uint32_t DQ_OFFSET_CR[3];
        __IO uint32_t DIS_CALIB_RST_CR;
        __IO uint32_t DLL_LOCK_DIFF_CR;
        __IO uint32_t FIFO_WE_IN_DELAY_CR[3];
        __IO uint32_t FIFO_WE_IN_FORCE_CR;
        __IO uint32_t FIFO_WE_SLAVE_RATIO_CR[4];
        __IO uint32_t GATELVL_INIT_MODE_CR;
        __IO uint32_t GATELVL_INIT_RATIO_CR[4];
        __IO uint32_t LOCAL_ODT_CR;
        __IO uint32_t INVERT_CLKOUT_CR;
        __IO uint32_t RD_DQS_SLAVE_DELAY_CR[3];
        __IO uint32_t RD_DQS_SLAVE_FORCE_CR;
        __IO uint32_t RD_DQS_SLAVE_RATIO_CR[4];
        __IO uint32_t WR_DQS_SLAVE_DELAY_CR[3];
        __IO uint32_t WR_DQS_SLAVE_FORCE_CR;
        __IO uint32_t WR_DQS_SLAVE_RATIO_CR[4];
        __IO uint32_t WR_DATA_SLAVE_DELAY_CR[3];
        __IO uint32_t WR_DATA_SLAVE_FORCE_CR;
        __IO uint32_t WR_DATA_SLAVE_RATIO_CR[4];
        __IO uint32_t WRLVL_INIT_MODE_CR;
        __IO uint32_t WRLVL_INIT_RATIO_CR[4];
        __IO uint32_t WR_RD_RL_CR;
        __IO uint32_t RDC_FIFO_RST_ERRCNTCLR_CR;
        __IO uint32_t RDC_WE_TO_RE_DELAY_CR;
        __IO uint32_t USE_FIXED_RE_CR;
        __IO uint32_t USE_RANK0_DELAYS_CR;
        __IO uint32_t USE_LVL_TRNG_LEVEL_CR;
        __IO uint32_t CONFIG_CR;
        __IO uint32_t RD_WR_GATE_LVL_CR;
        __IO uint32_t DYN_RESET_CR;

        /*----------------------------------------------------------------------
         * DDR PHY status registers
         */    
        __I  uint32_t LEVELLING_FAILURE_SR;
        __I  uint32_t BIST_ERROR_SR[3];
        __I  uint32_t WRLVL_DQS_RATIO_SR[4];
        __I  uint32_t WRLVL_DQ_RATIO_SR[4];
        __I  uint32_t RDLVL_DQS_RATIO_SR[4];
        __I  uint32_t FIFO_SR[4];
        __I  uint32_t MASTER_DLL_SR;
        __I  uint32_t DLL_SLAVE_VALUE_SR[2];
        __I  uint32_t STATUS_OF_IN_DELAY_VAL_SR[2];
        __I  uint32_t STATUS_OF_OUT_DELAY_VAL_SR[2];
        __I  uint32_t DLL_LOCK_AND_SLAVE_VAL_SR;
        __I  uint32_t CTRL_OUTPUT_FILTER_SR;
        __I  uint32_t CTRL_OF_OUTPUT_DELAY_SR;
        __I  uint32_t RD_DQS_SLAVE_DLL_VAL_SR[3];
        __I  uint32_t WR_DATA_SLAVE_DLL_VAL_SR[3];
        __I  uint32_t FIFO_WE_SLAVE_DLL_VAL_SR[3];
        __I  uint32_t WR_DQS_SLAVE_DLL_VAL_SR[3];
        __I  uint32_t CTRL_SLAVE_DLL_VAL_SR; 
        __IO uint32_t RESERVED2[13];
    } phy;
    
    /*--------------------------------------------------------------------------
     * FIC-64 registers
     * These registers are 16-bit wide and 32-bit aligned.
     */
    struct 
    {
        __IO uint32_t NB_ADDR_CR;
        __IO uint32_t NBRWB_SIZE_CR;
        __IO uint32_t WB_TIMEOUT_CR;
        __IO uint32_t HPD_SW_RW_EN_CR;
        __IO uint32_t HPD_SW_RW_INVAL_CR;
        __IO uint32_t SW_WR_ERCLR_CR;
        __IO uint32_t ERR_INT_ENABLE_CR;
        __IO uint32_t NUM_AHB_MASTERS_CR;
        __I  uint32_t HPB_ERR_ADDR_SR[2];
        __I  uint32_t SW_ERR_ADDR_SR[2];
        __I  uint32_t HPD_SW_WRB_EMPTY_SR;
        __I  uint32_t SW_HPB_LOCKOUT_SR;
        __I  uint32_t SW_HPD_WERR_SR;
             uint32_t RESERVED0;
        __IO uint32_t LOCK_TIMEOUTVAL_CR[2];
        __IO uint32_t LOCK_TIMEOUT_EN_CR;
             uint32_t RESERVED1[5];
        __IO uint32_t RDWR_ERR_SR;
    } fic;
} DDRCore_TypeDef;

/*----------------------------------------------------------------------------*/
/*--------------------- MDDR APB Configuration Registers ---------------------*/
/*----------------------------------------------------------------------------*/
typedef struct
{
    /*--------------------------------------------------------------------------
     * MDDR core configuration registers.
     * These registers are to be accessed as:
     * MDDR->core.fic.<regname> = <value>;
     * MDDR->core.phy.<regname> = <value>;
     * MDDR->core.ddrc.<regname> = <value>;
     */
    DDRCore_TypeDef core;
    
} MDDR_TypeDef;


/*----------------------------------------------------------------------------*/
/*--------------------- FDDR APB Configuration Registers ---------------------*/
/*----------------------------------------------------------------------------*/
typedef struct 
{
    /*--------------------------------------------------------------------------
     * FDDR core configuration registers. These are same as corresponding 
     * MDDR registers. 
     * These registers are to be accessed as:
     * FDDR->core.fic.<regname> = <value>;
     * FDDR->core.phy.<regname> = <value>;
     * FDDR->core.ddrc.<regname> = <value>;
     */
    DDRCore_TypeDef core;
    __IO uint32_t RESERVED[39];
    
    /*--------------------------------------------------------------------------
     * FDDR system registers
     * These registers are to be accessed as:
     * FDDR->sysreg.PLL_CONFIG_LOW_2 = 0x04u;
     */
    struct 
    {
        __IO uint32_t PLL_CONFIG_LOW_1;
        __IO uint32_t PLL_CONFIG_LOW_2;
        __IO uint32_t PLL_CONFIG_HIGH;
        __IO uint32_t FACC_CLK_EN;
        __IO uint32_t FACC_MUX_CONFIG;
        __IO uint32_t FACC_DIVISOR_RATIO;
        __IO uint32_t PLL_DELAY_LINE_SEL;
        __IO uint32_t SOFT_RESET; 
        __IO uint32_t IO_CALIB;
        __IO uint32_t INTERRUPT_ENABLE;
        __IO uint32_t AXI_AHB_MODE_SEL;
        __IO uint32_t PHY_SELF_REF_EN;
        __IO uint32_t FAB_PLL_CLK_SR;
        __IO uint32_t FPLL_CLK_SR;
        __IO uint32_t CLK_CALIB_STATUS;
        __IO uint32_t INTERRUPT_SR;
        __IO uint32_t CLK_CALIB_CONFIG;
        __IO uint32_t IO_CALIB_SR;
        __IO uint32_t FATC_RESET;
    } sysreg;
} FDDR_TypeDef;

/*----------------------------------------------------------------------------*/
/*------------------------------ SERDES Interface ----------------------------*/
/*----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
  AXI window
 */
typedef struct
{
    __IO    uint32_t    base;
    __IO    uint32_t    size;
    __IO    uint32_t    window_lsb;
    __IO    uint32_t    window_msb;
} axi_window_TypeDef;

/*------------------------------------------------------------------------------
  PCI Express Bridge Core registers.
  
  This data structure is used to access to the registers of the PCI Express
  Bridge Core.
 */
typedef struct
{
    /*======================= Information registers ======================*/
    /**
      Information register: vendor_id & device_id
      bits [15:0]   vendor_id
      bits [31:16]  device_id
     */
    /* 0x000 */
    __IO    uint32_t    VID_DEVID;

    /**
      PCI Express Control & Status Register: cfg_prmscr
     */
    /* 0x004 */
    __IO    uint32_t    CFG_PRMSCR;
    
    /**
      Information register: class_code
     */
    /* 0x008 */
    __IO    uint32_t    CLASS_CODE;
    
    __IO    uint32_t    RESERVED0;
    
    /**
      Bridge Configuration Register: bar0
     */
    /* 0x010 */
    __IO    uint32_t    BAR0;
    
    /**
      Bridge Configuration Register: bar1
     */
    /* 0x014 */
    __IO    uint32_t    BAR1;
    
    /**
      Bridge Configuration Register: bar2
     */
    /* 0x018 */
    __IO    uint32_t    BAR2;
    
    /**
      Bridge Configuration Register: bar3
     */
    /* 0x01C */
    __IO    uint32_t    BAR3;
    
    /**
      Bridge Configuration Register: bar4
     */
    /* 0x020 */
    __IO    uint32_t    BAR4;
    
    /**
      Bridge Configuration Register: bar5
     */
    /* 0x024 */
    __IO    uint32_t    BAR5;
    
    __IO    uint32_t    RESERVED1;
    
    /**
      Information register: subsystem_id
     */
    /* 0x02C */
    __IO    uint32_t    SUBSYSTEM_ID;
    
    /**
      PCI Express Control & Status Register: pcie_devscr
     */
    /* 0x030 */
    __IO    uint32_t    PCIE_DEVSCR;
    
    /**
      PCI Express Control & Status Register: pcie_linkscr
     */
    /* 0x034 */
    __IO    uint32_t    PCIE_LINKSCR;
    
    /**
      Bridge Configuration Register: tc_vc_mapping
     */
    /* 0x038 */
    __IO    uint32_t    TC_VC_MAPPING;
    
    /**
      Information register: captured_bus_device_nb
     */
    /* 0x03C */
    __IO    uint32_t    CAPTURED_BUS_DEVICE_NB;
    
    /**
      Endpoint Interrupt register: msi_ctrl_status
     */
    /* 0x040 */
    __IO    uint32_t    MSI_CTRL_STATUS;
    
    /**
      Power Management register: ltssm
     */
    /* 0x044 */
    __IO    uint32_t    LTSSM;
    
    /**
      Power Management register: power_mgt_capability
     */
    /* 0x048 */
    __IO    uint32_t    POWER_MGT_CAPABILITY;
    
    /**
      PCI Express Control & Status Register: cfg_pmscr
     */
    /* 0x04C */
    __IO    uint32_t    CFG_PMSCR;
    
    /**
      Bridge Configuration Register: aer_ecrc_capability
     */
    /* 0x050 */
    __IO    uint32_t    AER_ECRC_CAPABILITY;
    
    /**
      Bridge Configuration Register: vc1_capability
     */
    /* 0x054 */
    __IO    uint32_t    VC1_CAPABILITY;
    
    /**
      Bridge Configuration Register: max_payload_size
     */
    /* 0x058 */
    __IO    uint32_t    MAX_PAYLOAD_SIZE;
    
    /**
      Bridge Configuration Register: clkreq
     */
    /* 0x05C */
    __IO    uint32_t    CLKREQ;
    
    /**
      Power Management register: aspm_l0s_capability
     */
    /* 0x060 */
    __IO    uint32_t    ASPM_L0S_CAPABILITY;
    
    /**
      Power Management register: aspm_l1_capability
     */
    /* 0x064 */
    __IO    uint32_t    ASPM_L1_CAPABILITY;
    
    /**
      Power Management register: timeout_completion
     */
    /* 0x068 */
    __IO    uint32_t    TIMEOUT_COMPLETION;

    __IO    uint32_t    RESERVED2;
    
    /**
      Power Management register: pm_data_scale
     */
    /* 0x070 */
    __IO    uint32_t    PM_DATA_SCALE[4];
    
    /**
      Endpoint Interrupt register: msi
     */
    /* 0x080 */
    __IO    uint32_t    MSI[8];
    
    /**
      Bridge Configuration Register: error_counter
     */
    /* 0x0A0 */
    __IO    uint32_t    ERROR_COUNTER[4];
    
    /**
      Bridge Configuration Register: credit_allocation
     */
    /* 0x0B0 */
    __IO    uint32_t    CREDIT_ALLOCATION[4];
    
    /**
      Address Mapping register: axi_slave_window
     */
    /* 0x0C0 */
    axi_window_TypeDef      AXI_SLAVE_WINDOW[4];
    
    /**
      Address Mapping register: axi_master_window
     */
    /* 0x100 */
    axi_window_TypeDef      AXI_MASTER_WINDOW[4];
    
    /**
      Rootport Interrupt register: imask
     */
    /* 0x140 */
    __IO    uint32_t    IMASK;
    
    /**
      Rootport Interrupt register: istatus
     */
    /* 0x144 */
    __IO    uint32_t    ISTATUS;
    
    /**
      Rootport Interrupt register: icmd
     */
    /* 0x148 */
    __IO    uint32_t    ICMD;
    
    /**
      Rootport Interrupt register: irstatus
     */
    /* 0x14C */
    __IO    uint32_t    IRSTATUS;
    
    /**
      Rootport Interrupt register: imsiaddr
     */
    /* 0x150 */
    __IO    uint32_t    IMSIADDR;
    
    /**
      PCI Express Control & Status Register: slotcap
     */
    /* 0x154 */
    __IO    uint32_t    SLOTCAP;
    
    /**
      PCI Express Control & Status Register: slotcsr
     */
    /* 0x158 */
    __IO    uint32_t    SLOTCSR;
    
    /**
      PCI Express Control & Status Register: rootcsr
     */
    /* 0x15C */
    __IO    uint32_t    ROOTCSR;
    
    /**
      Configuration Register: cfg_control
     */
    /* 0x160 */
    __IO    uint32_t    CFG_CONTROL;
    
    /**
      Configuration Register: cfg_write_data
     */
    /* 0x164 */
    __IO    uint32_t    CFG_WRITE_DATA;
    
    /**
      Configuration Register: cfg_read_data
     */
    /* 0x168 */
    __IO    uint32_t    CFG_READ_DATA;
    
    /**
      Information register: info
     */
    /* 0x16C */
    __IO    uint32_t    INFO;
    
    /**
      Input/Output Control Register: io_control
     */
    /* 0x170 */
    __IO    uint32_t    IO_CONTROL;
    
    /**
      Input/Output Control Register: io_addr
     */
    /* 0x174 */
    __IO    uint32_t    IO_ADDR;
    
    /**
      Input/Output Control Register: io_write_data
     */
    /* 0x178 */
    __IO    uint32_t    IO_WRITE_DATA;
    
    /**
      Input/Output Control Register: io_read_data
     */
    /* 0x17C */
    __IO    uint32_t    IO_READ_DATA;
    
    /**
      Configuration Register: cfg_fbe
     */
    /* 0x180 */
    __IO    uint32_t    CFG_FBE;
    
    /**
      Address Mapping register: prefetch_io_window
     */
    /* 0x184 */
    __IO    uint32_t    PREFETCH_IO_WINDOW;
    
    __IO    uint32_t    RESERVED4[31];
    
    /**
      Bridge Configuration Register: pcie_config
     */
    /* 0x204 */
    __IO    uint32_t    PCIE_CONFIG;
    
    __IO    uint32_t    RESERVED5[10];
    
    /**
      PCI Express Control & Status Register: pcie_dev2scr
     */
    /* 0x230 */
    __IO    uint32_t    PCIE_DEV2SCR;
    
    /**
      PCI Express Control & Status Register: pcie_link2scr
     */
    /* 0x234 */
    __IO    uint32_t    PCIE_LINK2SCR;
    
    __IO    uint32_t    RESERVED6[10];
    
    /**
      Power Management register: aspm_l0s_gen2 capability
     */
    /* 0x260 */
    __IO    uint32_t    ASPM_L0S_GEN2;
    
    __IO    uint32_t    RESERVED7[39];
    
    /**
      Bridge Configuration Register: k_cnt_config
     */
    /* 0x300 */
    __IO    uint32_t    K_CNT_CONFIG[6];
    
    __IO    uint32_t    RESERVED8[826];
    
} PCIE_TypeDef;
 
/*------------------------------------------------------------------------------
  SERDESIF System Registers.
 */
typedef struct
{
    __IO    uint32_t    SER_PLL_CONFIG_LOW;
    __IO    uint32_t    SER_PLL_CONFIG_HIGH;
    __IO    uint32_t    SERDESIF_SOFT_RESET;
    __IO    uint32_t    SER_INTERRUPT_ENABLE;
    __IO    uint32_t    CONFIG_AXI_AHB_BRIDGE;
    __IO    uint32_t    CONFIG_ECC_INTR_ENABLE;
    __IO    uint32_t    CONFIG_TEST_IN;
    __IO    uint32_t    TEST_OUT_READ_ADDR;
    __IO    uint32_t    CONFIG_PCIE_PM;
    __IO    uint32_t    CONFIG_PHY_MODE_0;
    __IO    uint32_t    CONFIG_PHY_MODE_1;
    __IO    uint32_t    CONFIG_PHY_MODE_2;
    __IO    uint32_t    CONFIG_PCIE_0;
    __IO    uint32_t    CONFIG_PCIE_1;
    __IO    uint32_t    CONFIG_PCIE_2;
    __IO    uint32_t    CONFIG_PCIE_3;
    __IO    uint32_t    CONFIG_BAR_SIZE_0_1;
    __IO    uint32_t    CONFIG_BAR_SIZE_2_3;
    __IO    uint32_t    CONFIG_BAR_SIZE_3_4;
    __IO    uint32_t    SER_CLK_STATUS;
    __IO    uint32_t    SER_CLK_CALIB_STATUS;
    __IO    uint32_t    TEST_OUT_READ_DATA;
    __IO    uint32_t    SER_INTERRUPT;
    __IO    uint32_t    SERDESIF_INTR_STATUS;
    __IO    uint32_t    SER_CLK_CALIB_CONFIG;
    __IO    uint32_t    REFCLK_SEL;
    __IO    uint32_t    PCLK_SEL;
    __IO    uint32_t    EPCS_RSTN_SEL;
    __IO    uint32_t    CHIP_ENABLES;
    __IO    uint32_t    SERDES_TEST_OUT;
    __IO    uint32_t    SERDES_FATC_RESET;
    __IO    uint32_t    RC_OSC_SPLL_REFCLK_SEL;
    __IO    uint32_t    SPREAD_SPECTRUM_CLK;
    __IO    uint32_t    CONF_AXI_MSTR_WNDW_0;
    __IO    uint32_t    CONF_AXI_MSTR_WNDW_1;
    __IO    uint32_t    CONF_AXI_MSTR_WNDW_2;
    __IO    uint32_t    CONF_AXI_MSTR_WNDW_3;
    __IO    uint32_t    CONF_AXI_SLV_WNDW_0;
    __IO    uint32_t    CONF_AXI_SLV_WNDW_1;
    __IO    uint32_t    CONF_AXI_SLV_WNDW_2;
    __IO    uint32_t    CONF_AXI_SLV_WNDW_3;
    __IO    uint32_t    DESKEW_CONFIG;
    __IO    uint32_t    DEBUG_MODE_KEY;
    __IO    uint32_t    RESERVED0;
    /*
     * The following registers are only available on the M2S090.
     */
    __IO    uint32_t    IDDQ;
    __IO    uint32_t    ADVCONFIG;
    __IO    uint32_t    ADVSTATUS;
    __IO    uint32_t    ECC_ERR_INJECT;
    __IO    uint32_t    RESERVED2;
    __IO    uint32_t    RESERVED3;
    __IO    uint32_t    ENHANCEMENT;
    __IO    uint32_t    RESERVED4;
    __IO    uint32_t    RESERVED5;
    __IO    uint32_t    RESERVED6;
    __IO    uint32_t    RESERVED7;
    __IO    uint32_t    RESERVED8;
    __IO    uint32_t    RESERVED9;
    __IO    uint32_t    RESERVED10;
    __IO    uint32_t    RESERVED11;
    __IO    uint32_t    RESERVED12;
    __IO    uint32_t    RESERVED13;
    __IO    uint32_t    RESERVED14;
    __IO    uint32_t    RESERVED15;
    __IO    uint32_t    RESERVED16;
    __IO    uint32_t    RESERVED17;
    __IO    uint32_t    RESERVED18;
    __IO    uint32_t    RESERVED19;
    __IO    uint32_t    RESERVED20;
    __IO    uint32_t    CONFIG2_AXI_AHB_BRIDGE;
    __IO    uint32_t    CONFIG2_ECC_INTR_ENABLE;
    __IO    uint32_t    CONFIG2_TEST_IN;
    __IO    uint32_t    TEST2_OUT_READ_ADDR;
    __IO    uint32_t    CONFIG2_PCIE_PM;
    __IO    uint32_t    RESERVED21;
    __IO    uint32_t    RESERVED22;
    __IO    uint32_t    RESERVED23;
    __IO    uint32_t    CONFIG2_PCIE_0;
    __IO    uint32_t    CONFIG2_PCIE_1;
    __IO    uint32_t    CONFIG2_PCIE_2;
    __IO    uint32_t    CONFIG2_PCIE_3;
    __IO    uint32_t    CONFIG2_BAR_SIZE_0_1;
    __IO    uint32_t    CONFIG2_BAR_SIZE_2_3;
    __IO    uint32_t    CONFIG2_BAR_SIZE_3_4;
    __IO    uint32_t    RESERVED24;
    __IO    uint32_t    RESERVED25;
    __IO    uint32_t    TEST2_OUT_READ_DATA;
    __IO    uint32_t    RESERVED26;
    __IO    uint32_t    SERDESIF2_INTR_STATUS;
    __IO    uint32_t    RESERVED27;
    __IO    uint32_t    RESERVED28;
    __IO    uint32_t    RESERVED29;
    __IO    uint32_t    RESERVED30;
    __IO    uint32_t    RESERVED31;
    __IO    uint32_t    RESERVED32;
    __IO    uint32_t    RESERVED33;
    __IO    uint32_t    RESERVED34;
    __IO    uint32_t    RESERVED35;
    __IO    uint32_t    CONF2_AXI_MSTR_WNDW_0;
    __IO    uint32_t    CONF2_AXI_MSTR_WNDW_1;
    __IO    uint32_t    CONF2_AXI_MSTR_WNDW_2;
    __IO    uint32_t    CONF2_AXI_MSTR_WNDW_3;
    __IO    uint32_t    CONF2_AXI_SLV_WNDW_0;
    __IO    uint32_t    CONF2_AXI_SLV_WNDW_1;
    __IO    uint32_t    CONF2_AXI_SLV_WNDW_2;
    __IO    uint32_t    CONF2_AXI_SLV_WNDW_3;
    __IO    uint32_t    RESERVED36;
    __IO    uint32_t    RESERVED37;
    __IO    uint32_t    RESERVED38;
    __IO    uint32_t    RESERVED39;
    __IO    uint32_t    ADVCONFIG2;
    __IO    uint32_t    ADVSTATUS2;
    __IO    uint32_t    ECC_ERR_INJECT2;
} SERDES_INTF_SYSREG_TypeDef;

/*------------------------------------------------------------------------------
  SERDES PHY registers
 */
typedef struct
{
    /**
      Control register 0
     */
    __IO    uint32_t    CR0;
    
    /**
      Clock count for error counter decrement
     */
    __IO    uint32_t    ERRCNT_DEC;
    
    /**
      Error counter threshold - Rx idle detect max latency
     */
    __IO    uint32_t    RXIDLE_MAX_ERRCNT_THR;
    
    /**
      Tx Impedance ratio
     */
    __IO    uint32_t    IMPED_RATIO;
    
    /**
      PLL F settings and PCLK ratio
     */
    __IO    uint32_t    PLL_F_PCLK_RATIO;
    
    /**
      PLL M & N settings
     */
    __IO    uint32_t    PLL_M_N;
    
    /**
      250ns timer base count
     */
    __IO    uint32_t    CNT250NS_MAX;
    
    /**
      Rx Equalization amplitude ratio
     */
    __IO    uint32_t    RE_AMP_RATIO;
    
    /**
      Rx Equalization Cut frequency
     */
    __IO    uint32_t    RE_CUT_RATIO;
    
    /**
      Tx Amplitude ratio
     */
    __IO    uint32_t    TX_AMP_RATIO;
    
    /**
      Tx Post-Cursor ratio
     */
    __IO    uint32_t    TX_PST_RATIO;
    
    /**
      Tx Pre-Cursor ratio
     */
    __IO    uint32_t    TX_PRE_RATIO;
    
    /**
      End of calibration counter
     */
    __IO    uint32_t    ENDCALIB_MAX;
    
    /**
      Calibration stability counter
     */
    __IO    uint32_t    CALIB_STABILITY_COUNT;
    
    /**
      Power down feature
     */
    __IO    uint32_t    POWER_DOWN;
    
    /**
      Rx offset counter
     */
    __IO    uint32_t    RX_OFFSET_COUNT;
    
    /**
      PLL F settings and PCLK ratio (in PCIe 5 Gbps speed)
     */
    __IO    uint32_t    PLL_F_PCLK_RATIO_5GBPS;
    
    /**
      PLL M & N sttings (in PCIe 5 Gbps spped)
     */
    __IO    uint32_t    PLL_M_N_5GBPS;
    
    /**
      250ns timer base count (in PCIe 5 Gbps speed)
     */
    __IO    uint32_t    CNT250NS_MAX_5GBPS;
    
    /**
      reserved
     */
    __IO    uint32_t    RESERVED;
    
    /**
      Tx Post-Cursor ratio with TxDeemp=0, Full swing
     */
    __IO    uint32_t    TX_PST_RATIO_DEEMP0_FULL;
    
    /**
      Tx Pre-Cursor ratio TxDeemp=0, full swing
     */
    __IO    uint32_t    TX_PRE_RATIO_DEEMP0_FULL;
    
    /**
      Tx Post-Cursor ratio with TxDeemp=1, Full swing
     */
    __IO    uint32_t    TX_PST_RATIO_DEEMP1_FULL;
    
    /**
      Tx Pre-Cursor ratio TxDeemp=1, full swing
     */
    __IO    uint32_t    TX_PRE_RATIO_DEEMP1_FULL;
    
    /**
      Tx Amplitude ratio TxMargin=0, full swing
     */
    __IO    uint32_t    TX_AMP_RATIO_MARGIN0_FULL;
    
    /**
      Tx Amplitude ratio TxMargin=1, full swing
     */
    __IO    uint32_t    TX_AMP_RATIO_MARGIN1_FULL;
    
    /**
      Tx Amplitude ratio TxMargin=2, full swing
     */
    __IO    uint32_t    TX_AMP_RATIO_MARGIN2_FULL;
    
    /**
      Tx Amplitude ratio TxMargin=3, full swing
     */
    __IO    uint32_t    TX_AMP_RATIO_MARGIN3_FULL;
    
    /**
      Tx Amplitude ratio TxMargin=4, full swing
     */
    __IO    uint32_t    TX_AMP_RATIO_MARGIN4_FULL;
    
    /**
      Tx Amplitude ratio TxMargin=5, full swing
     */
    __IO    uint32_t    TX_AMP_RATIO_MARGIN5_FULL;
    
    /**
      Tx Amplitude ratio TxMargin=6, full swing
     */
    __IO    uint32_t    TX_AMP_RATIO_MARGIN6_FULL;
    
    /**
      Tx Amplitude ratio TxMargin=7, full swing
     */
    __IO    uint32_t    TX_AMP_RATIO_MARGIN7_FULL;
    
    /**
      Rx Equalization amplitude ratio TxDeemp=0
     */
    __IO    uint32_t    RE_AMP_RATIO_DEEMP0;
    
    /**
      Rx Equalization Cut frequency TxDeemp=0
     */
    __IO    uint32_t    RE_CUT_RATIO_DEEMP0;
    
    /**
      Rx Equalization amplitude ratio TxDeemp=1
     */
    __IO    uint32_t    RE_AMP_RATIO_DEEMP1;
    
    /**
      Rx Equalization Cut frequency TxDeemp=1
     */
    __IO    uint32_t    RE_CUT_RATIO_DEEMP1;
    
    /**
      Tx Post-Cursor ratio with TxDeemp=0, Half swing
     */
    __IO    uint32_t    TX_PST_RATIO_DEEMP0_HALF;
    
    /**
      Tx Pre-Cursor ratio TxDeemp=0, Half swing
     */
    __IO    uint32_t    TX_PRE_RATIO_DEEMP0_HALF;
    
    /**
      Tx Post-Cursor ratio with TxDeemp=1, Half swing
     */
    __IO    uint32_t    TX_PST_RATIO_DEEMP1_HALF;
    
    /**
      Tx Pre-Cursor ratio TxDeemp=1, Half swing
     */
    __IO    uint32_t    TX_PRE_RATIO_DEEMP1_HALF;
    
    /**
      Tx Amplitude ratio TxMargin=0, Half swing
     */
    __IO    uint32_t    TX_AMP_RATIO_MARGIN0_HALF;
    
    /**
      Tx Amplitude ratio TxMargin=1, Half swing
     */
    __IO    uint32_t    TX_AMP_RATIO_MARGIN1_HALF;
    
    /**
      Tx Amplitude ratio TxMargin=2, Half swing
     */
    __IO    uint32_t    TX_AMP_RATIO_MARGIN2_HALF;
    
    /**
      Tx Amplitude ratio TxMargin=3, Half swing
     */
    __IO    uint32_t    TX_AMP_RATIO_MARGIN3_HALF;
    
    /**
      Tx Amplitude ratio TxMargin=4, Half swing
     */
    __IO    uint32_t    TX_AMP_RATIO_MARGIN4_HALF;
    
    /**
      Tx Amplitude ratio TxMargin=5, Half swing
     */
    __IO    uint32_t    TX_AMP_RATIO_MARGIN5_HALF;
    
    /**
      Tx Amplitude ratio TxMargin=6, Half swing
     */
    __IO    uint32_t    TX_AMP_RATIO_MARGIN6_HALF;
    
    /**
      Tx Amplitude ratio TxMargin=7, Half swing
     */
    __IO    uint32_t    TX_AMP_RATIO_MARGIN7_HALF;
    
    /**
      PMA status
     */
    __IO    uint32_t    PMA_STATUS;
    
    /**
      Tx sweep center (RO)
     */
    __IO    uint32_t    TX_SWEEP_CENTER;
    
    /**
      Rx seep center (RO)
     */
    __IO    uint32_t    RX_SWEEP_CENTER;
    
    /**
      Rx Equalization sweep center (RO)
     */
    __IO    uint32_t    RE_SWEEP_CENTER;
    
    /**
      Receiver Shift Loader parameter 0 (RO)
     */
    __IO    uint32_t    ATXDRR_7_0;
    
    /**
      Receiver Shift Loader parameter 1 (RO)
     */
    __IO    uint32_t    ATXDRR_14_8;
    
    /**
      Transmitter P Shift Loader parameter0-0
     */
    __IO    uint32_t    ATXDRP_DYN_7_0;
    
    /**
      Transmitter P Shift Loader parameter0-1
     */
    __IO    uint32_t    ATXDRP_DYN_15_8;
    
    /**
      Transmitter P Shift Loader parameter0-2
     */
    __IO    uint32_t    ATXDRP_DYN_20_16;
    
    /**
      Transmitter A Shift Loader parameter0-0
     */
    __IO    uint32_t    ATXDRA_DYN_7_0;
    
    /**
      Transmitter A Shift Loader parameter0-1
     */
    __IO    uint32_t    ATXDRA_DYN_15_8;
    
    /**
      Transmitter A Shift Loader parameter0-2
     */
    __IO    uint32_t    ATXDRA_DYN_20_16;
    
    /**
      Transmitter T Shift Loader parameter0-0
     */
    __IO    uint32_t    ATXDRT_DYN_7_0;
    
    /**
      Transmitter T Shift Loader parameter0-1
     */
    __IO    uint32_t    ATXDRT_DYN_15_8;
    
    /**
      Transmitter T Shift Loader parameter0-2
     */
    __IO    uint32_t    ATXDRT_DYN_20_16;
    
    /**
      Transmitter P Shift Loader parameter 1-0 (RO)
     */
    __IO    uint32_t    ATXDRP_EI1_7_0;
    
    /**
      Transmitter P Shift Loader parameter 1-1 (RO)
     */
    __IO    uint32_t    ATXDRP_EI1_15_8;
    
    /**
      Transmitter P Shift Loader parameter 1-2 (RO)
     */
    __IO    uint32_t    ATXDRP_EI1_20_16;
    
    /**
      Transmitter A Shift Loader parameter 1-0 (RO)
     */
    __IO    uint32_t    ATXDRA_EI1_7_0;
    
    /**
      Transmitter A Shift Loader parameter 1-1 (RO)
     */
    __IO    uint32_t    ATXDRA_EI1_15_8;
    
    /**
      Transmitter A Shift Loader parameter 1-2 (RO)
     */
    __IO    uint32_t    ATXDRA_EI1_20_16;
    
    /**
      Transmitter T Shift Loader parameter 1-0 (RO)
     */
    __IO    uint32_t    ATXDRT_EI1_7_0;
    
    /**
      Transmitter T Shift Loader parameter 1-1 (RO)
     */
    __IO    uint32_t    ATXDRT_EI1_15_8;
    
    /**
      Transmitter T Shift Loader parameter 1-2 (RO)
     */
    __IO    uint32_t    ATXDRT_EI1_20_16;
    
    /**
      Transmitter P shift Loader parameter 2-0 (RO)
     */
    __IO    uint32_t    ATXDRP_EI2_7_0;
    
    /**
      Transmitter P shift Loader parameter 2-1 (RO)
     */
    __IO    uint32_t    ATXDRP_EI2_15_8;
    
    /**
      Transmitter P shift Loader parameter 2-2 (RO)
     */
    __IO    uint32_t    ATXDRP_EI2_20_16;
    
    /**
      Transmitter A Shift parametr 2-0 (RO)
     */
    __IO    uint32_t    ATXDRA_EI2_7_0;
    
    /**
      Transmitter A Shift parametr 2-1 (RO)
     */
    __IO    uint32_t    ATXDRA_EI2_15_8;
    
    /**
      Transmitter A Shift parametr 2-2 (RO)
     */
    __IO    uint32_t    ATXDRA_EI2_20_16;
    
    /**
      Transmitter T Shift parametr 2-0 (RO)
     */
    __IO    uint32_t    ATXDRT_EI2_7_0;
    
    /**
      Transmitter T Shift parametr 2-1 (RO)
     */
    __IO    uint32_t    ATXDRT_EI2_15_8;
    
    /**
      Transmitter T Shift parametr 2-2 (RO)
     */
    __IO    uint32_t    ATXDRT_EI2_20_16;
    
    /**
      Override calibration register (RW)
     */
    __IO    uint32_t    OVERRIDE_CALIB;
    
    /**
      Force Receiver Shift Loader parameter 0 (RW)
     */
    __IO    uint32_t    FORCE_ATXDRR_7_0;
    
    /**
      Force Receiver Shift Loader parameter 1 (RW)
     */
    __IO    uint32_t    FORCE_ATXDRR_15_8;
    
    /**
      Force Receiver Shift Loader parameter 2 (RW)
     */
    __IO    uint32_t    FORCE_ATXDRR_20_16;
    
    /**
      Force Transmitter P Shift Loader parameter 0 (RW)
     */
    __IO    uint32_t    FORCE_ATXDRP_7_0;
    
    /**
      Force Transmitter P Shift Loader parameter 1 (RW)
     */
    __IO    uint32_t    FORCE_ATXDRP_15_8;
    
    /**
      Force Transmitter P Shift Loader parameter 2 (RW)
     */
    __IO    uint32_t    FORCE_ATXDRP_20_16;
    
    /**
      Force Transmitter A Shift Loader parameter 0 (RW)
     */
    __IO    uint32_t    FORCE_ATXDRA_7_0;
    
    /**
      Force Transmitter A Shift Loader parameter 1 (RW)
     */
    __IO    uint32_t    FORCE_ATXDRA_15_8;
    
    /**
      Force Transmitter A Shift Loader parameter 2 (RW)
     */
    __IO    uint32_t    FORCE_ATXDRA_20_16;
    
    /**
      Force Transmitter T Shift parameter 0-0 (RO)
     */
    __IO    uint32_t    FORCE_ATXDRT_7_0;
    
    /**
      Force Transmitter T Shift parameter 0-1 (RO)
     */
    __IO    uint32_t    FORCE_ATXDRT_15_8;
    
    /**
      Force Transmitter T Shift parameter 0-2 (RO)
     */
    __IO    uint32_t    FORCE_ATXDRT_20_16;
    
    /**
      RxD offset calibration result (RO)
     */
    __IO    uint32_t    RXD_OFFSET_CALIB_RESULT;
    
    /**
      RxT offset calibration result (RO)
     */
    __IO    uint32_t    RXT_OFFSET_CALIB_RESULT;
    
    /**
      Schmitt trigger calibration result (RO)
     */
    __IO    uint32_t    SCHMITT_TRIG_CALIB_RESULT;
    
    /**
      Force RxD offset calibration settings (RW)
     */
    __IO    uint32_t    FORCE_RXD_OFFSET_CALIB;
    
    /**
      Force RxT offset calibration settings (RW)
     */
    __IO    uint32_t    FORCE_RXT_OFFSET_CALIB;
    
    /**
      Force Schmitt trigger calibration settings (RW)
     */
    __IO    uint32_t    FORCE_SCHMITT_TRIG_CALIB;
    
    /**
      PRBS control register (RW)
     */
    __IO    uint32_t    PRBS_CTRL;
    
    /**
      PRBS error counter register (RO)
     */
    __IO    uint32_t    PRBS_ERRCNT;
    
    /**
      PHY reset override register (RW)
     */
    __IO    uint32_t    PHY_RESET_OVERRIDE;
    
    /**
      PHY power override register (RW)
     */
    __IO    uint32_t    PHY_POWER_OVERRIDE;
    
    /**
      Custom Pattern Byte 0 (RW)
     */
    __IO    uint32_t    CUSTOM_PATTERN_7_0;
    
    /**
      Custom Pattern Byte 1 (RW)
     */
    __IO    uint32_t    CUSTOM_PATTERN_15_8;
    
    /**
      Custom Pattern Byte 2 (RW)
     */
    __IO    uint32_t    CUSTOM_PATTERN_23_16;
    
    /**
      Custom Pattern Byte 3 (RW)
     */
    __IO    uint32_t    CUSTOM_PATTERN_31_24;
    
    /**
      Custom Pattern Byte 4 (RW)
     */
    __IO    uint32_t    CUSTOM_PATTERN_39_32;
    
    /**
      Custom Pattern Byte 5 (RW)
     */
    __IO    uint32_t    CUSTOM_PATTERN_47_40;
    
    /**
      Custom Pattern Byte 6 (RW)
     */
    __IO    uint32_t    CUSTOM_PATTERN55_48;
    
    /**
      Custom Pattern Byte 7 (RW)
     */
    __IO    uint32_t    CUSTOM_PATTERN_63_56;
    
    /**
      Custom Pattern Byte 8 (RW)
     */
    __IO    uint32_t    CUSTOM_PATTERN_71_64;
    
    /**
      Custom Pattern Byte 9 (RW)
     */
    __IO    uint32_t    CUSTOM_PATTERN_79_72;
    
    /**
      Custom Pattern Control (RW)
     */
    __IO    uint32_t    CUSTOM_PATTERN_CTRL;
    
    /**
      Custom Pattern Status register (RO)
     */
    __IO    uint32_t    CUSTOM_PATTERN_STATUS;
    
    /**
      PCS Loopback Control (RW)
     */
    __IO    uint32_t    PCS_LOOPBBACK_CTRL;
    
    /**
      Gen1 Transmit PLL Current Charge Pump (RW)
     */
    __IO    uint32_t    GEN1_TX_PLL_CCP;
    
    /**
      Gen1 Receive PLL Current Charge Pump (RW)
     */
    __IO    uint32_t    GEN1_RX_PLL_CCP;
    
    /**
      Gen2 Transmit PLL Current Charge Pump (RW)
     */
    __IO    uint32_t    GEN2_TX_PLL_CCP;
    
    /**
      Gen2 Receive PLL Current Charge Pump (RW)
     */
    __IO    uint32_t    GEN2_RX_PLL_CCP;
    
    /**
      CDR PLL manual control
     */
    __IO    uint32_t    CDR_PLL_MANUAL_CR;
    
    /**
      Reserved0
     */
    __IO    uint32_t    RESERVED0[6];
    
    /**
      Update settings command register
     */
    __IO    uint32_t    UPDATE_SETTINGS;
    
    /**
      Reserved1
     */
    __IO    uint32_t    RESERVED1[31];
    
    /**
      PRBS first error cycle counter bits [7:0]
     */
    __IO    uint32_t    PRBS_ERR_CYC_FIRST_7_0;
    
    /**
      PRBS first error cycle counter bits [15:8]
     */
    __IO    uint32_t    PRBS_ERR_CYC_FIRST_15_8;
    
    /**
      PRBS first error cycle counter bits [23:16]
     */
    __IO    uint32_t    PRBS_ERR_CYC_FIRST_23_16;
    
    /**
      PRBS first error cycle counter bits [31:24]
     */
    __IO    uint32_t    PRBS_ERR_CYC_FIRST_31_24;
    
    /**
      PRBS first error cycle counter bits [39:32]
     */
    __IO    uint32_t    PRBS_ERR_CYC_FIRST_39_32;
    
    /**
      PRBS first error cycle counter bits [47:40]
     */
    __IO    uint32_t    PRBS_ERR_CYC_FIRST_47_40;
    
    /**
      PRBS first error cycle counter bits [49:48]
     */
    __IO    uint32_t    PRBS_ERR_CYC_FIRST_49_48;
    
    /**
      Reserved2
     */
    __IO    uint32_t    RESERVED2;
    
    /**
      PRBS last error cycle counter bits [7:0]
     */
    __IO    uint32_t    PRBS_ERR_CYC_LAST_7_0;
    
    /**
      PRBS last error cycle counter bits [15:8]
     */
    __IO    uint32_t    PRBS_ERR_CYC_LAST_15_8;
    
    /**
      PRBS last error cycle counter bits [23:16]
     */
    __IO    uint32_t    PRBS_ERR_CYC_LAST_23_16;
    
    /**
      PRBS last error cycle counter bits [31:24]
     */
    __IO    uint32_t    PRBS_ERR_CYC_LAST_31_24;
    
    /**
      PRBS last error cycle counter bits [39:32]
     */
    __IO    uint32_t    PRBS_ERR_CYC_LAST_39_32;
    
    /**
      PRBS last error cycle counter bits [47:40]
     */
    __IO    uint32_t    PRBS_ERR_CYC_LAST_47_40;
    
    /**
      PRBS last error cycle counter bits [49:48]
     */
    __IO    uint32_t    PRBS_ERR_CYC_LAST_49_48;
    
    /**
      Reserved3
     */
    __IO    uint32_t    RESERVED3[81];
    
} SERDES_TypeDef;
 
/*-------------------------------------------------------------------------*//**
  The serdesif_regs_t data structure provides access to the complete set of the
  SERDES Interface hardware block configuration registers. These registers are
  accessed through the APB interface of the SERDES Interface hardware block.
 */
typedef struct
{
    /**
      PCIe core registers.
     */
    PCIE_TypeDef                core;
    
    /**
      SERDES macro registers.
     */
    SERDES_TypeDef              lane[4];
    
    /**
      SERDESIF system registers.
     */
    SERDES_INTF_SYSREG_TypeDef     sys_regs;
    
} SERDESIF_TypeDef;


/*----------------------------------------------------------------------------*/
/*------------------------------ System Registers ----------------------------*/
/*----------------------------------------------------------------------------*/
typedef struct
{
    __IO     uint32_t    ESRAM_CR;                                 /*0X0   */
    __IO     uint32_t    ESRAM_MAX_LAT_CR;                         /*0X4   */
    __IO     uint32_t    DDR_CR;                                   /*0X8   */
    __IO     uint32_t    ENVM_CR;                                  /*0XC   */
    __IO     uint32_t    ENVM_REMAP_BASE_CR;                       /*0X10  */
    __IO     uint32_t    ENVM_REMAP_FAB_CR;                        /*0X14  */
    __IO     uint32_t    CC_CR;                                    /*0X18  */
    __IO     uint32_t    CC_REGION_CR;                             /*0X1C  */
    __IO     uint32_t    CC_LOCK_BASE_ADDR_CR;                     /*0X20  */
    __IO     uint32_t    CC_FLUSH_INDX_CR;                         /*0X24  */
    __IO     uint32_t    DDRB_BUF_TIMER_CR;                        /*0X28  */
    __IO     uint32_t    DDRB_NB_ADDR_CR;                          /*0X2C  */
    __IO     uint32_t    DDRB_NB_SIZE_CR;                          /*0X30  */
    __IO     uint32_t    DDRB_CR;                                  /*0X34  */
    __IO     uint32_t    EDAC_CR;                                  /*0X38  */
    __IO     uint32_t    MASTER_WEIGHT0_CR;                        /*0X3C  */
    __IO     uint32_t    MASTER_WEIGHT1_CR;                        /*0X40  */
    __IO     uint32_t    SOFT_IRQ_CR;                              /*0X44  */
    __IO     uint32_t    SOFT_RST_CR;                              /*0X48  */
    __IO     uint32_t    M3_CR;                                    /*0X4C  */
    __IO     uint32_t    FAB_IF_CR;                                /*0X50  */
    __IO     uint32_t    LOOPBACK_CR;                              /*0X54  */
    __IO     uint32_t    GPIO_SYSRESET_SEL_CR;                     /*0X58  */
    __IO     uint32_t    GPIN_SRC_SEL_CR;                          /*0X5C  */
    __IO     uint32_t    MDDR_CR;                                  /*0X60  */
    __IO     uint32_t    USB_IO_INPUT_SEL_CR;                      /*0X64  */
    __IO     uint32_t    PERIPH_CLK_MUX_SEL_CR;                    /*0X68  */
    __IO     uint32_t    WDOG_CR;                                  /*0X6C  */
    __IO     uint32_t    MDDR_IO_CALIB_CR;                         /*0X70  */
    __IO     uint32_t    SPARE_OUT_CR;                             /*0X74  */
    __IO     uint32_t    EDAC_IRQ_ENABLE_CR;                       /*0X78  */
    __IO     uint32_t    USB_CR;                                   /*0X7C  */
    __IO     uint32_t    ESRAM_PIPELINE_CR;                        /*0X80  */
    __IO     uint32_t    MSS_IRQ_ENABLE_CR;                        /*0X84  */
    __IO     uint32_t    RTC_WAKEUP_CR;                            /*0X88  */
    __IO     uint32_t    MAC_CR;                                   /*0X8C  */
    __IO     uint32_t    MSSDDR_PLL_STATUS_LOW_CR;                 /*0X90  */
    __IO     uint32_t    MSSDDR_PLL_STATUS_HIGH_CR;                /*0X94  */
    __IO     uint32_t    MSSDDR_FACC1_CR;                          /*0X98  */
    __IO     uint32_t    MSSDDR_FACC2_CR;                          /*0X9C  */
    __IO     uint32_t    PLL_LOCK_EN_CR;                           /*0XA0  */
    __IO     uint32_t    MSSDDR_CLK_CALIB_CR;                      /*0XA4  */
    __IO     uint32_t    PLL_DELAY_LINE_SEL_CR;                    /*0XA8  */
    __IO     uint32_t    MAC_STAT_CLRONRD_CR;                      /*0XAC  */
    __IO     uint32_t    RESET_SOURCE_CR;                          /*0XB0  */
    __I      uint32_t    CC_DC_ERR_ADDR_SR;                        /*0XB4  */
    __I      uint32_t    CC_IC_ERR_ADDR_SR;                        /*0XB8  */
    __I      uint32_t    CC_SB_ERR_ADDR_SR;                        /*0XBC  */
    __I      uint32_t    CC_DECC_ERR_ADDR_SR;                      /*0XC0  */
    __I      uint32_t    CC_IC_MISS_CNT_SR;                        /*0XC4  */
    __I      uint32_t    CC_IC_HIT_CNT_SR;                         /*0XC8  */
    __I      uint32_t    CC_DC_MISS_CNT_SR;                        /*0XCC  */
    __I      uint32_t    CC_DC_HIT_CNT_SR;                         /*0XD0  */
    __I      uint32_t    CC_IC_TRANS_CNT_SR;                       /*0XD4  */
    __I      uint32_t    CC_DC_TRANS_CNT_SR;                       /*0XD8  */
    __I      uint32_t    DDRB_DS_ERR_ADR_SR;                       /*0XDC  */
    __I      uint32_t    DDRB_HPD_ERR_ADR_SR;                      /*0XE0  */
    __I      uint32_t    DDRB_SW_ERR_ADR_SR;                       /*0XE4  */
    __I      uint32_t    DDRB_BUF_EMPTY_SR;                        /*0XE8  */
    __I      uint32_t    DDRB_DSBL_DN_SR;                          /*0XEC  */
    __I      uint32_t    ESRAM0_EDAC_CNT;                          /*0XF0  */
    __I      uint32_t    ESRAM1_EDAC_CNT;                          /*0XF4  */
    __I      uint32_t    CC_EDAC_CNT;                              /*0XF8  */
    __I      uint32_t    MAC_EDAC_TX_CNT;                          /*0XFC  */
    __I      uint32_t    MAC_EDAC_RX_CNT;                          /*0X100 */
    __I      uint32_t    USB_EDAC_CNT;                             /*0X104 */
    __I      uint32_t    CAN_EDAC_CNT;                             /*0X108 */
    __I      uint32_t    ESRAM0_EDAC_ADR;                          /*0X10C */
    __I      uint32_t    ESRAM1_EDAC_ADR;                          /*0X110 */
    __I      uint32_t    MAC_EDAC_RX_ADR;                          /*0X114 */
    __I      uint32_t    MAC_EDAC_TX_ADR;                          /*0X118 */
    __I      uint32_t    CAN_EDAC_ADR;                             /*0X11C */
    __I      uint32_t    USB_EDAC_ADR;                             /*0X120 */
    __I      uint32_t    MM0_1_2_SECURITY;                         /*0X124 */
    __I      uint32_t    MM4_5_FIC64_SECURITY;                     /*0X128 */
    __I      uint32_t    MM3_6_7_8_SECURITY;                       /*0X12C */
    __I      uint32_t    MM9_SECURITY;                             /*0X130 */
    __I      uint32_t    M3_SR;                                    /*0X134 */
    __I      uint32_t    ETM_COUNT_LOW;                            /*0X138 */
    __I      uint32_t    ETM_COUNT_HIGH;                           /*0X13C */
    __I      uint32_t    DEVICE_SR;                                /*0X140 */
    __I      uint32_t    ENVM_PROTECT_USER;                        /*0X144 */
    __I      uint32_t    ENVM_STATUS;                              /*0X148 */
    __I      uint32_t    DEVICE_VERSION;                           /*0X14C */
    __I      uint32_t    MSSDDR_PLL_STATUS;                        /*0X150 */
    __I      uint32_t    USB_SR;                                   /*0X154 */
    __I      uint32_t    ENVM_SR;                                  /*0X158 */
    __I      uint32_t    SPARE_IN;                                 /*0X15C */
    __I      uint32_t    DDRB_STATUS;                              /*0X160 */
    __I      uint32_t    MDDR_IO_CALIB_STATUS;                     /*0X164 */
    __I      uint32_t    MSSDDR_CLK_CALIB_STATUS;                  /*0X168 */
    __I      uint32_t    WDOGLOAD;                                 /*0X16C */
    __I      uint32_t    WDOGMVRP;                                 /*0X170 */
    __I      uint32_t    USERCONFIG0;                              /*0X174 */
    __I      uint32_t    USERCONFIG1;                              /*0X178 */
    __I      uint32_t    USERCONFIG2;                              /*0X17C */
    __I      uint32_t    USERCONFIG3;                              /*0X180 */
    __I      uint32_t    FAB_PROT_SIZE;                            /*0X184 */
    __I      uint32_t    FAB_PROT_BASE;                            /*0X188 */
    __I      uint32_t    MSS_GPIO_DEF;                             /*0X18C */
    __IO     uint32_t    EDAC_SR;                                  /*0X190 */
    __IO     uint32_t    MSS_INTERNAL_SR;                          /*0X194 */
    __IO     uint32_t    MSS_EXTERNAL_SR;                          /*0X198 */
    __IO     uint32_t    WDOGTIMEOUTEVENT;                         /*0X19C */
    __IO     uint32_t    CLR_MSS_COUNTERS;                         /*0X1A0 */
    __IO     uint32_t    CLR_EDAC_COUNTERS;                        /*0X1A4 */
    __IO     uint32_t    FLUSH_CR;                                 /*0X1A8 */
    __IO     uint32_t    MAC_STAT_CLR_CR;                          /*0X1AC */
    __IO     uint32_t    IOMUXCELL_CONFIG[57];                     /*0X1B0 */
    __I      uint32_t    NVM_PROTECT_FACTORY;                      /*0X294 */
    __I      uint32_t    DEVICE_STATUS_FIXED;                      /*0X298 */
    __I      uint32_t    MBIST_ES0;                                /*0X29C */
    __I      uint32_t    MBIST_ES1;                                /*0X2A0 */
    __IO     uint32_t    MSDDR_PLL_STAUS_1;                        /*0X2A4 */
    __I      uint32_t    REDUNDANCY_ESRAM0;                        /*0X2A8 */
    __I      uint32_t    REDUNDANCY_ESRAM1;                        /*0X2AC */
    __I      uint32_t    SERDESIF;                                 /*0X2B0 */

} SYSREG_TypeDef;

#define SYSREG_ENVM0_SOFTRESET_MASK         ( (uint32_t)0x01u << 0u )
#define SYSREG_ENVM1_SOFTRESET_MASK         ( (uint32_t)0x01u << 1u )
#define SYSREG_ESRAM0_SOFTRESET_MASK        ( (uint32_t)0x01u << 2u )
#define SYSREG_ESRAM1_SOFTRESET_MASK        ( (uint32_t)0x01u << 3u )
#define SYSREG_MAC_SOFTRESET_MASK           ( (uint32_t)0x01u << 4u )
#define SYSREG_PDMA_SOFTRESET_MASK          ( (uint32_t)0x01u << 5u )
#define SYSREG_TIMER_SOFTRESET_MASK         ( (uint32_t)0x01u << 6u )
#define SYSREG_MMUART0_SOFTRESET_MASK       ( (uint32_t)0x01u << 7u )
#define SYSREG_MMUART1_SOFTRESET_MASK       ( (uint32_t)0x01u << 8u )
#define SYSREG_SPI0_SOFTRESET_MASK          ( (uint32_t)0x01u << 9u )
#define SYSREG_SPI1_SOFTRESET_MASK          ( (uint32_t)0x01u << 10u )
#define SYSREG_I2C0_SOFTRESET_MASK          ( (uint32_t)0x01u << 11u )
#define SYSREG_I2C1_SOFTRESET_MASK          ( (uint32_t)0x01u << 12u )
#define SYSREG_CAN_SOFTRESET_MASK           ( (uint32_t)0x01u << 13u )
#define SYSREG_USB_SOFTRESET_MASK           ( (uint32_t)0x01u << 14u )
#define SYSREG_COMBLK_SOFTRESET_MASK        ( (uint32_t)0x01u << 15u )
#define SYSREG_FPGA_SOFTRESET_MASK          ( (uint32_t)0x01u << 16u )
#define SYSREG_HPDMA_SOFTRESET_MASK         ( (uint32_t)0x01u << 17u )
#define SYSREG_FIC32_0_SOFTRESET_MASK       ( (uint32_t)0x01u << 18u )
#define SYSREG_FIC32_1_SOFTRESET_MASK       ( (uint32_t)0x01u << 19u )
#define SYSREG_GPIO_SOFTRESET_MASK          ( (uint32_t)0x01u << 20u )
#define SYSREG_GPIO_7_0_SOFTRESET_MASK      ( (uint32_t)0x01u << 21u )
#define SYSREG_GPIO_15_8_SOFTRESET_MASK     ( (uint32_t)0x01u << 22u )
#define SYSREG_GPIO_23_16_SOFTRESET_MASK    ( (uint32_t)0x01u << 23u )
#define SYSREG_GPIO_31_24_SOFTRESET_MASK    ( (uint32_t)0x01u << 24u )
#define SYSREG_MDDR_SOFTRESET_MASK          ( (uint32_t)0x01u << 25u )
#define SYSREG_FIC64_SOFTRESET_MASK         ( (uint32_t)0x01u << 26u )

/*----------------------------------------------------------------------------*/
/*-------------------------- CoreSF2Config Registers -------------------------*/
/*----------------------------------------------------------------------------*/
typedef struct {
    __IO     uint32_t   CONFIG_DONE;
    __I      uint32_t   INIT_DONE;
    __IO     uint32_t   CLR_INIT_DONE;
    __I      uint32_t   CONFIG_SR;
    __IO     uint32_t   SOFT_RESET_CR;
    __I      uint32_t   IP_VERSION_SR;
} CoreSF2Config_TypeDef;

/******************************************************************************/
/*                         Peripheral memory map                              */
/******************************************************************************/
#define UART0_BASE              0x40000000u
#define SPI0_BASE               0x40001000u
#define I2C0_BASE               0x40002000u
#define PDMA_BASE               0x40003000u
#define TIMER_BASE              0x40004000u
#define WATCHDOG_BASE           0x40005000u
#define H2F_IRQ_CTRL_BASE       0x40006000u
#define UART1_BASE              0x40010000u
#define SPI1_BASE               0x40011000u
#define I2C1_BASE               0x40012000u
#define GPIO_BASE               0x40013000u
#define HPDMA_BASE              0x40014000u
#define CAN_BASE                0x40015000u
#define COMBLK_BASE             0x40016000u
#define RTC_BASE                0x40017000u
#define DDR0_CFG_BASE           0x40020800u
#define DDR1_CFG_BASE           0x40021000u
#define CORE_SF2_CFG_BASE       0x40022000u
#define SERDES0_CFG_BASE        0x40028000u
#define SERDES1_CFG_BASE        0x4002C000u
#define SERDES2_CFG_BASE        0x40030000u
#define SERDES3_CFG_BASE        0x40034000u
#define SYSREG_BASE             0x40038000u
#define ETHERNET_BASE           0x40041000u
#define USB_BASE                0x40043000u
#define ENVM1_BASE              0x60080000u
#define ENVM2_BASE              0x600C0000u

/******************************************************************************/
/* bitband address calculation macro                             */
/******************************************************************************/
#define BITBAND_ADDRESS(X)  ((X & 0xF0000000U) + 0x02000000U + ((X & 0xFFFFFU) << 5))

/******************************************************************************/
/*                         Peripheral declaration                             */
/******************************************************************************/
#define UART0                   ((UART_TypeDef *) UART0_BASE)
#define SPI0                    ((SPI_TypeDef *) SPI0_BASE)
#define I2C0                    ((I2C_TypeDef *) I2C0_BASE)
#define I2C0_BITBAND            ((I2C_BitBand_TypeDef *) BITBAND_ADDRESS(I2C0_BASE))
#define MAC                     ((MAC_TypeDef *) ETHERNET_BASE)
#define PDMA                    ((PDMA_TypeDef *) PDMA_BASE)
#define TIMER                   ((TIMER_TypeDef *) TIMER_BASE)
#define TIMER_BITBAND           ((TIMER_BitBand_TypeDef *) BITBAND_ADDRESS(TIMER_BASE))
#define WATCHDOG                ((WATCHDOG_TypeDef *) WATCHDOG_BASE)
#define INTERRUPT_CTRL          ((INTERRUPT_CTRL_TypeDef *) H2F_IRQ_CTRL_BASE)
#define INTERRUPT_CTRL_BITBAND  ((INTERRUPT_CTRL_BitBand_TypeDef *) BITBAND_ADDRESS(H2F_IRQ_CTRL_BASE))
#define UART1                   ((UART_TypeDef *) UART1_BASE)
#define SPI1                    ((SPI_TypeDef *) SPI1_BASE)
#define I2C1                    ((I2C_TypeDef *) I2C1_BASE)
#define I2C1_BITBAND            ((I2C_BitBand_TypeDef *) BITBAND_ADDRESS(I2C1_BASE))
#define GPIO                    ((GPIO_TypeDef *) GPIO_BASE)
#define GPIO_BITBAND            ((GPIO_BitBand_TypeDef *) BITBAND_ADDRESS(GPIO_BASE))
#define HPDMA                   ((HPDMA_TypeDef *) HPDMA_BASE)
#define HPDMA_BITBAND           ((HPDMA_BitBand_TypeDef *) BITBAND_ADDRESS(HPDMA_BASE))
#define COMBLK                  ((COMBLK_TypeDef *) COMBLK_BASE)
#define RTC                     ((RTC_TypeDef *) RTC_BASE)
#define ENVM_1                  ((NVM_TypeDef *) ENVM1_BASE)
#define ENVM_2                  ((NVM_TypeDef *) ENVM2_BASE)
#define SYSREG                  ((SYSREG_TypeDef *) SYSREG_BASE)
#define MDDR                    ((MDDR_TypeDef *) DDR0_CFG_BASE)
#define FDDR                    ((FDDR_TypeDef *) DDR1_CFG_BASE) 
#define USB                     ((MSS_USB_TypeDef *) USB_BASE)
#define SERDES0                 ((SERDESIF_TypeDef *) SERDES0_CFG_BASE)
#define SERDES1                 ((SERDESIF_TypeDef *) SERDES1_CFG_BASE)
#define SERDES2                 ((SERDESIF_TypeDef *) SERDES2_CFG_BASE)
#define SERDES3                 ((SERDESIF_TypeDef *) SERDES3_CFG_BASE)
#define CORE_SF2_CFG            ((CoreSF2Config_TypeDef *) CORE_SF2_CFG_BASE)

#ifdef __cplusplus
}
#endif

#endif  /* __SMARTFUSION2_CMSIS_PAL_H__ */

