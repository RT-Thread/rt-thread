
/****************************************************************************************************//**
 * @file     cmem7.h
 *
 * @brief    CMSIS Cortex-M3 Peripheral Access Layer Header File for
 *           cmem7 from <unknown Vendor>.
 *
 * @version  V1.0
 * @date     5. January 2015
 *
 * @note     Generated with SVDConv V2.75
 *           from CMSIS SVD File 'SVDConv_CME_M7.svd' Version 1.0,
 *******************************************************************************************************/



/** @addtogroup (null)
  * @{
  */

/** @addtogroup cmem7
  * @{
  */

#ifndef CMEM7_H
#define CMEM7_H

#ifdef __cplusplus
extern "C" {
#endif


/* -------------------------  Interrupt Number Definition  ------------------------ */

typedef enum {
/* -------------------  Cortex-M3 Processor Exceptions Numbers  ------------------- */
  Reset_IRQn                    = -15,              /*!<   1  Reset Vector, invoked on Power up and warm reset                 */
  NonMaskableInt_IRQn           = -14,              /*!<   2  Non maskable Interrupt, cannot be stopped or preempted           */
  HardFault_IRQn                = -13,              /*!<   3  Hard Fault, all classes of Fault                                 */
  MemoryManagement_IRQn         = -12,              /*!<   4  Memory Management, MPU mismatch, including Access Violation
                                                         and No Match                                                          */
  BusFault_IRQn                 = -11,              /*!<   5  Bus Fault, Pre-Fetch-, Memory Access Fault, other address/memory
                                                         related Fault                                                         */
  UsageFault_IRQn               = -10,              /*!<   6  Usage Fault, i.e. Undef Instruction, Illegal State Transition    */
  SVCall_IRQn                   =  -5,              /*!<  11  System Service Call via SVC instruction                          */
  DebugMonitor_IRQn             =  -4,              /*!<  12  Debug Monitor                                                    */
  PendSV_IRQn                   =  -2,              /*!<  14  Pendable request for system service                              */
  SysTick_IRQn                  =  -1,              /*!<  15  System Tick Timer                                                */
/* ----------------------  cmem7 Specific Interrupt Numbers  ---------------------- */
  ETH_INT_IRQn                  =   0,              /*!<   0  ETH_INT                                                          */
  USB_INT_IRQn                  =   1,              /*!<   1  USB_INT                                                          */
  DMA_INT_IRQn                  =   2,              /*!<   2  DMA_INT                                                          */
  CAN0_INT_IRQn                 =   3,              /*!<   3  CAN0_INT                                                         */
  CAN1_INT_IRQn                 =   4,              /*!<   4  CAN1_INT                                                         */
  FP0_INT_IRQn                  =   5,              /*!<   5  FP0_INT                                                          */
  FP1_INT_IRQn                  =   6,              /*!<   6  FP1_INT                                                          */
  FP2_INT_IRQn                  =   7,              /*!<   7  FP2_INT                                                          */
  FP3_INT_IRQn                  =   8,              /*!<   8  FP3_INT                                                          */
  FP4_INT_IRQn                  =   9,              /*!<   9  FP4_INT                                                          */
  FP5_INT_IRQn                  =  10,              /*!<  10  FP5_INT                                                          */
  FP6_INT_IRQn                  =  11,              /*!<  11  FP6_INT                                                          */
  FP7_INT_IRQn                  =  12,              /*!<  12  FP7_INT                                                          */
  FP8_INT_IRQn                  =  13,              /*!<  13  FP8_INT                                                          */
  FP9_INT_IRQn                  =  14,              /*!<  14  FP9_INT                                                          */
  FP10_INT_IRQn                 =  15,              /*!<  15  FP10_INT                                                         */
  FP11_INT_IRQn                 =  16,              /*!<  16  FP11_INT                                                         */
  FP12_INT_IRQn                 =  17,              /*!<  17  FP12_INT                                                         */
  FP13_INT_IRQn                 =  18,              /*!<  18  FP13_INT                                                         */
  FP14_INT_IRQn                 =  19,              /*!<  19  FP14_INT                                                         */
  FP15_INT_IRQn                 =  20,              /*!<  20  FP15_INT                                                         */
  UART0_INT_IRQn                =  21,              /*!<  21  UART0_INT                                                        */
  UART1_INT_IRQn                =  22,              /*!<  22  UART1_INT                                                        */
  ADC_INT_IRQn                  =  23,              /*!<  23  ADC_INT                                                          */
  GPIO_INT_IRQn                 =  24,              /*!<  24  GPIO_INT                                                         */
  SPI1_INT_IRQn                 =  25,              /*!<  25  SPI1_INT                                                         */
  I2C1_INT_IRQn                 =  26,              /*!<  26  I2C1_INT                                                         */
  SPI0_INT_IRQn                 =  27,              /*!<  27  SPI0_INT                                                         */
  I2C0_INT_IRQn                 =  28,              /*!<  28  I2C0_INT                                                         */
  RTC_1S_INT_IRQn               =  29,              /*!<  29  RTC_1S_INT                                                       */
  RTC_1MS_INT_IRQn              =  30,              /*!<  30  RTC_1MS_INT                                                      */
  WDG_INT_IRQn                  =  31,              /*!<  31  WDG_INT                                                          */
  TIMER_INT_IRQn                =  32,              /*!<  32  TIMER_INT                                                        */
  DDRC_SW_PROC_IRQn             =  33,              /*!<  33  DDRC_SW_PROC                                                     */
  ETH_PMT_INT_IRQn              =  34,              /*!<  34  ETH_PMT_INT                                                      */
  PAD_INT_IRQn                  =  35,              /*!<  35  PAD_INT                                                          */
  DDRC_LANE_SYNC_IRQn           =  36,              /*!<  36  DDRC_LANE_SYNC                                                   */
  UART2_INT_IRQn                =  37               /*!<  37  UART2_INT                                                        */
} IRQn_Type;


/** @addtogroup Configuration_of_CMSIS
  * @{
  */


/* ================================================================================ */
/* ================      Processor and Core Peripheral Section     ================ */
/* ================================================================================ */

/* ----------------Configuration of the Cortex-M3 Processor and Core Peripherals---------------- */
#define __CM3_REV                 0x0000            /*!< Cortex-M3 Core Revision                                               */
#define __MPU_PRESENT                  0            /*!< MPU present or not                                                    */
#define __NVIC_PRIO_BITS               0            /*!< Number of Bits used for Priority Levels                               */
#define __Vendor_SysTickConfig         0            /*!< Set to 1 if different SysTick Config is used                          */
/** @} */ /* End of group Configuration_of_CMSIS */

#include <core_cm3.h>                               /*!< Cortex-M3 processor and core peripherals                              */
#include "system_cmem7.h"                           /*!< cmem7 System                                                          */


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
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined(__TMS470__)
/* anonymous unions are enabled by default */
#elif defined(__TASKING__)
  #pragma warning 586
#else
  #warning Not supported compiler type
#endif



/* ================================================================================ */
/* ================                      UART0                     ================ */
/* ================================================================================ */


/**
  * @brief asynchronous serial controller 0 (UART0)
  */

typedef struct {                                    /*!< UART0 Structure                                                       */
  __IO uint16_t  BAUDRATE;                          /*!< baudrate Register                                                     */
  __I  uint16_t  RESERVED0;
  __IO uint16_t  TX_BUF;                            /*!< transmit buffer Register                                              */
  __I  uint16_t  RESERVED1;
  __I  uint16_t  RX_BUF;                            /*!< receive buffer Register                                               */
  __I  uint16_t  RESERVED2;

  union {
    __IO uint32_t  CTRL;                            /*!< control Register                                                      */

    struct {
      __IO uint32_t  MODE       :  3;               /*!< asc mode control                                                      */
      __IO uint32_t  STOP       :  2;               /*!< number of stop bits selection                                         */
      __IO uint32_t  PARITY     :  1;               /*!< parity selection                                                      */
      __IO uint32_t  LOOPBACK   :  1;               /*!< loopback mode enable bit                                              */
           uint32_t             :  1;
      __IO uint32_t  RX_EN      :  1;               /*!< receive enable bit                                                    */
           uint32_t             :  1;
      __IO uint32_t  FIFO_EN    :  1;               /*!< FIFO enable bit                                                       */
      __IO uint32_t  CTS        :  1;               /*!< Clear to send, enable signal to send                                  */
      __IO uint32_t  BAUD_MODE  :  1;               /*!< baudrate generation mode                                              */
      __IO uint32_t  RX_THRESHOLD:  5;              /*!< receive threshold                                                     */
      __IO uint32_t  RX_HALF_FULL:  5;              /*!< receive fifi half full level                                          */
    } CTRL_b;                                       /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  INT_MASK;                        /*!< interrupt mask register                                               */

    struct {
      __IO uint32_t  RNE        :  1;               /*!< Receive FIFO not empty interrupt                                      */
      __IO uint32_t  TE         :  1;               /*!< Transmitter FIFO empty interrupt                                      */
      __IO uint32_t  THE        :  1;               /*!< Transmitter FIFO at least half empty flag                             */
      __IO uint32_t  TONE       :  1;               /*!< timeout when the receiver FIFO is not empty interrupt                 */
      __IO uint32_t  TOE        :  1;               /*!< timeout when the receiver FIFO is empty interrupt                     */
      __IO uint32_t  RHF        :  1;               /*!< receiver FIFO is half full interrupt                                  */
      __IO uint32_t  TF         :  1;               /*!< transmitter FIFO full interrupt                                       */
      __IO uint32_t  PE         :  1;               /*!< parity error interrupt                                                */
      __IO uint32_t  FE         :  1;               /*!< frame error interrupt                                                 */
      __IO uint32_t  OE         :  1;               /*!< overrun error interrupt                                               */
      __IO uint32_t  RX_THRE_REACH:  1;             /*!< Receive threshold reach interrupt                                     */
    } INT_MASK_b;                                   /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  STATUS;                          /*!< status register                                                       */

    struct {
      __IO uint32_t  RNE        :  1;               /*!< receiver FIFO not empty                                               */
      __IO uint32_t  TE         :  1;               /*!< Transmitter FIFO empty                                                */
      __IO uint32_t  THE        :  1;               /*!< Transmitter FIFO at least half empty flag                             */
      __IO uint32_t  TONE       :  1;               /*!< timeout when the receiver FIFO is not empty                           */
      __IO uint32_t  TOE        :  1;               /*!< time out when the receiver FIFO is empty                              */
      __IO uint32_t  RHF        :  1;               /*!< receiver FIFO is half full                                            */
      __IO uint32_t  TF         :  1;               /*!< transmitter FIFO is full                                              */
    } STATUS_b;                                     /*!< BitSize                                                               */
  };
  __IO uint8_t   TIMEOUT;                           /*!< timeout Register                                                      */
  __I  uint8_t   RESERVED3[3];

  union {
    __IO uint32_t  TX_RESET;                        /*!< transmit reset Register                                               */

    struct {
      __IO uint32_t  EN         :  1;               /*!< enable                                                                */
    } TX_RESET_b;                                   /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  RX_RESET;                        /*!< receive reset Register                                                */

    struct {
      __IO uint32_t  EN         :  1;               /*!< enable                                                                */
    } RX_RESET_b;                                   /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  RUN;                             /*!< uart enable register                                                  */

    struct {
      __IO uint32_t  EN         :  1;               /*!< enable                                                                */
    } RUN_b;                                        /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  INT_RAW;                         /*!< raw interrupt before mask register                                    */

    struct {
      __IO uint32_t  RNE        :  1;               /*!< Receive FIFO not empty interrupt                                      */
      __IO uint32_t  TE         :  1;               /*!< Transmitter FIFO empty interrupt                                      */
      __IO uint32_t  THE        :  1;               /*!< Transmitter FIFO at least half empty flag                             */
      __IO uint32_t  TONE       :  1;               /*!< timeout when the receiver FIFO is not empty interrupt                 */
      __IO uint32_t  TOE        :  1;               /*!< timeout when the receiver FIFO is empty interrupt                     */
      __IO uint32_t  RHF        :  1;               /*!< receiver FIFO is half full interrupt                                  */
      __IO uint32_t  TF         :  1;               /*!< transmitter FIFO full interrupt                                       */
      __IO uint32_t  PE         :  1;               /*!< parity error interrupt                                                */
      __IO uint32_t  FE         :  1;               /*!< frame error interrupt                                                 */
      __IO uint32_t  OE         :  1;               /*!< overrun error interrupt                                               */
      __IO uint32_t  RX_THRE_REACH:  1;             /*!< Receive threshold reach interrupt                                     */
    } INT_RAW_b;                                    /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  INT_SEEN;                        /*!< interrupt after mask register                                         */

    struct {
      __IO uint32_t  RNE        :  1;               /*!< Receive FIFO not empty interrupt                                      */
      __IO uint32_t  TE         :  1;               /*!< Transmitter FIFO empty interrupt                                      */
      __IO uint32_t  THE        :  1;               /*!< Transmitter FIFO at least half empty flag                             */
      __IO uint32_t  TONE       :  1;               /*!< timeout when the receiver FIFO is not empty interrupt                 */
      __IO uint32_t  TOE        :  1;               /*!< timeout when the receiver FIFO is empty interrupt                     */
      __IO uint32_t  RHF        :  1;               /*!< receiver FIFO is half full interrupt                                  */
      __IO uint32_t  TF         :  1;               /*!< transmitter FIFO full interrupt                                       */
      __IO uint32_t  PE         :  1;               /*!< parity error interrupt                                                */
      __IO uint32_t  FE         :  1;               /*!< frame error interrupt                                                 */
      __IO uint32_t  OE         :  1;               /*!< overrun error interrupt                                               */
      __IO uint32_t  RX_THRE_REACH:  1;             /*!< Receive threshold reach interrupt                                     */
    } INT_SEEN_b;                                   /*!< BitSize                                                               */
  };
} UART0_Type;


/* ================================================================================ */
/* ================                       WDG                      ================ */
/* ================================================================================ */


/**
  * @brief watchdog (WDG)
  */

typedef struct {                                    /*!< WDG Structure                                                         */

  union {
    __IO uint32_t  CTRL;                            /*!< control Register                                                      */

    struct {
      __IO uint32_t  EN         :  1;               /*!< flag indicates if watchdog is enabled or not                          */
      __IO uint32_t  INT_LEN    :  1;               /*!< watchdog report interrupt when COUNTER is 1/4 or 1/2 of LENGTH        */
    } CTRL_b;                                       /*!< BitSize                                                               */
  };
  __IO uint32_t  LEN;                               /*!< Ticks decrease down to 25% or 50% to trigger an interrupt             */

  union {
    __IO uint32_t  INT_CTRL;                        /*!< interrupt control                                                     */

    struct {
      __IO uint32_t  MASK       :  1;               /*!< mask register                                                         */
      __IO uint32_t  TRIGGER_MODE:  1;              /*!< trigger mode                                                          */
    } INT_CTRL_b;                                   /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  INT_STA;                         /*!< interrupt status register                                             */

    struct {
      __IO uint32_t  STA        :  1;               /*!< interrupt status                                                      */
    } INT_STA_b;                                    /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  INT_RAW;                         /*!< interrupt raw register                                                */

    struct {
      __IO uint32_t  STA        :  1;               /*!< interrupt status                                                      */
    } INT_RAW_b;                                    /*!< BitSize                                                               */
  };
  __I  uint32_t  CNT;                               /*!< counter register                                                      */
} WDG_Type;


/* ================================================================================ */
/* ================                     TIMER0                     ================ */
/* ================================================================================ */


/**
  * @brief timer 0 (TIMER0)
  */

typedef struct {                                    /*!< TIMER0 Structure                                                      */

  union {
    __IO uint32_t  CTRL;                            /*!< control Register                                                      */

    struct {
      __IO uint32_t  EN         :  1;               /*!< flag indicates if timer is enabled or not                             */
    } CTRL_b;                                       /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  TYPE;                            /*!< type Register                                                         */

    struct {
      __IO uint32_t  SIGNLE_SHOT:  1;               /*!< indicate timer generate only one interrupt if not reload              */
    } TYPE_b;                                       /*!< BitSize                                                               */
  };
  __IO uint32_t  LEN;                               /*!< length                                                                */

  union {
    __IO uint32_t  INT_EN;                          /*!< interrupt enable                                                      */

    struct {
      __IO uint32_t  EN_REVERSE :  1;               /*!< flag indicates if timer is disable or not                             */
    } INT_EN_b;                                     /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  INT_STA;                         /*!< interrupt status                                                      */

    struct {
      __IO uint32_t  STA        :  1;               /*!< interrupt status                                                      */
    } INT_STA_b;                                    /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  INT_RAW;                         /*!< interrupt raw register                                                */

    struct {
      __IO uint32_t  STA        :  1;               /*!< interrupt status                                                      */
    } INT_RAW_b;                                    /*!< BitSize                                                               */
  };
  __I  uint32_t  CNT;                               /*!< counter register                                                      */
} TIMER0_Type;


/* ================================================================================ */
/* ================                      SPI0                      ================ */
/* ================================================================================ */


/**
  * @brief SPI 0 (SPI0)
  */

typedef struct {                                    /*!< SPI0 Structure                                                        */

  union {
    __I  uint32_t  STATUS;                          /*!< status Register                                                       */

    struct {
      __I  uint32_t  RFIFO_EMPTY:  1;               /*!< receive fifo is empty                                                 */
      __I  uint32_t  RFIFO_FULL :  1;               /*!< receive fifo is full                                                  */
      __I  uint32_t  RFIFO_ALMOST_EMPTY:  1;        /*!< receive fifo is almost empty                                          */
      __I  uint32_t  RFIFO_ALMOST_FULL:  1;         /*!< receive fifo almost full                                              */
      __I  uint32_t  TFIFO_EMPTY:  1;               /*!< transmit fifo is empty                                                */
      __I  uint32_t  TFIFO_FULL :  1;               /*!< transmit fifo is full                                                 */
      __I  uint32_t  TFIFO_ALMOST_EMPTY:  1;        /*!< transmit fifo is almost empty                                         */
      __I  uint32_t  TFIFO_ALMOST_FULL:  1;         /*!< transmit fifo almost full                                             */
      __I  uint32_t  BUSY       :  1;               /*!< indecates if SPI is idle or busy                                      */
    } STATUS_b;                                     /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  CTRL;                            /*!< control Register                                                      */

    struct {
      __IO uint32_t  EN         :  1;               /*!< indicates if SPI is enabled or not                                    */
      __IO uint32_t  RX_EN      :  1;               /*!< indicates if SPI receiver is enabled or not                           */
      __IO uint32_t  CLK_HIGH   :  1;               /*!< indicats if idle clock polarity is high level                         */
      __IO uint32_t  NEG_EDGE   :  1;               /*!< 1, indicates SPI takes sample at the rise edge and transmit
                                                         data at the trailing edge. 0, conversely.                             */
      __IO uint32_t  TX_BIT_SEQUENCE:  1;           /*!< transmit bit sequence. 0 : MSB is sent first                          */
      __IO uint32_t  RX_BIT_SEQUENCE:  1;           /*!< receive bit sequence. 0: MSB is received first                        */
    } CTRL_b;                                       /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  INT_MASK;                        /*!< interrupt mask Register                                               */

    struct {
      __IO uint32_t  RFIFO_UNDERFLOW:  1;           /*!< receive fifo underflow interrupt                                      */
      __IO uint32_t  RFIFO_OVERFLOW:  1;            /*!< receive fifo overflow interrupt                                       */
      __IO uint32_t  RFIFO_ALMOST_FULL:  1;         /*!< receive fifo almost full interrupt                                    */
      __IO uint32_t  TFIFO_UNDERFLOW:  1;           /*!< transmit fifo underflow interrupt                                     */
      __IO uint32_t  TFIFO_OVERFLOW:  1;            /*!< transmit fifo overflow interrupt                                      */
      __IO uint32_t  TFIFO_ALMOST_EMPTY:  1;        /*!< transmit fifo almost empty interrupt                                  */
      __IO uint32_t  DONE       :  1;               /*!< transmit done interrupt                                               */
    } INT_MASK_b;                                   /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  INT_STATUS;                      /*!< interrupt Register                                                    */

    struct {
      __IO uint32_t  RFIFO_UNDERFLOW:  1;           /*!< receive fifo underflow interrupt                                      */
      __IO uint32_t  RFIFO_OVERFLOW:  1;            /*!< receive fifo overflow interrupt                                       */
      __IO uint32_t  RFIFO_ALMOST_FULL:  1;         /*!< receive fifo almost full interrupt                                    */
      __IO uint32_t  TFIFO_UNDERFLOW:  1;           /*!< transmit fifo underflow interrupt                                     */
      __IO uint32_t  TFIFO_OVERFLOW:  1;            /*!< transmit fifo overflow interrupt                                      */
      __IO uint32_t  TFIFO_ALMOST_EMPTY:  1;        /*!< transmit fifo almost empty interrupt                                  */
      __IO uint32_t  DONE       :  1;               /*!< transmit done interrupt                                               */
    } INT_STATUS_b;                                 /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  INT_RAW;                         /*!< interrupt raw Register                                                */

    struct {
      __IO uint32_t  RFIFO_UNDERFLOW:  1;           /*!< receive fifo underflow interrupt                                      */
      __IO uint32_t  RFIFO_OVERFLOW:  1;            /*!< receive fifo overflow interrupt                                       */
      __IO uint32_t  RFIFO_ALMOST_FULL:  1;         /*!< receive fifo almost full interrupt                                    */
      __IO uint32_t  TFIFO_UNDERFLOW:  1;           /*!< transmit fifo underflow interrupt                                     */
      __IO uint32_t  TFIFO_OVERFLOW:  1;            /*!< transmit fifo overflow interrupt                                      */
      __IO uint32_t  TFIFO_ALMOST_EMPTY:  1;        /*!< transmit fifo almost empty interrupt                                  */
      __IO uint32_t  DONE       :  1;               /*!< transmit done interrupt                                               */
    } INT_RAW_b;                                    /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  BCNT;                            /*!< bit length while transmitting and receiving                           */

    struct {
      __IO uint32_t  CNT        :  5;               /*!< bit length while transmitting and receiving, BCNT + 1                 */
    } BCNT_b;                                       /*!< BitSize                                                               */
  };
  __IO uint8_t   GAP;                               /*!< half cycle number between continuous data frame                       */
  __I  uint8_t   RESERVED0[3];
  __IO uint16_t  DIV;                               /*!< frequency division register, fsck = fclk_io / (DIV + 1) / 2           */
  __I  uint16_t  RESERVED1;
  __IO uint32_t  TRANS_CNT;                         /*!< transmit data length, data number = TRANS_CNT + 1                     */

  union {
    __O  uint32_t  TRANS_START;                     /*!< transmit startup register, write 1 to trigger transmision once        */

    struct {
      __O  uint32_t  TX_TRIGGER :  1;               /*!< write 1 to trigger transmision once                                   */
    } TRANS_START_b;                                /*!< BitSize                                                               */
  };
  __IO uint32_t  RW_DATA;                           /*!< raw data register                                                     */
} SPI0_Type;


/* ================================================================================ */
/* ================                      I2C0                      ================ */
/* ================================================================================ */


/**
  * @brief I2C 0 (I2C0)
  */

typedef struct {                                    /*!< I2C0 Structure                                                        */

  union {
    __IO uint32_t  CTRL;                            /*!< control Register                                                      */

    struct {
      __IO uint32_t  MODE       :  1;               /*!< master or slave mode                                                  */
      __IO uint32_t  MASTER_ADDR_WIDTH:  1;         /*!< 7- or 10-bits address as a master                                     */
      __IO uint32_t  SLAVE_ADDR_WIDTH:  1;          /*!< 7- or 10-bits address width as a slave                                */
    } CTRL_b;                                       /*!< BitSize                                                               */
  };

  union {
    __IO uint16_t  TAR;                             /*!< target address Register                                               */

    struct {
      __IO uint16_t  ADDR10     : 10;               /*!< 7- or 10-bits address                                                 */
      __IO uint16_t  START_BYTE :  1;               /*!< Enable start Byte for each transfer                                   */
    } TAR_b;                                        /*!< BitSize                                                               */
  };
  __I  uint16_t  RESERVED0;

  union {
    __IO uint16_t  SAR;                             /*!< slave address Register                                                */

    struct {
      __IO uint16_t  ADDR10     : 10;               /*!< 7- or 10-bits address                                                 */
    } SAR_b;                                        /*!< BitSize                                                               */
  };
  __I  uint16_t  RESERVED1;

  union {
    __IO uint32_t  DATA_CMD;                        /*!< I2C transfer data/command entry                                       */

    struct {
      __IO uint32_t  DATA       :  8;               /*!< 8-bits data                                                           */
      __O  uint32_t  RD_CMD     :  1;               /*!< read command for master mode only, write 0 if slave mode              */
      __O  uint32_t  WR_CMD     :  1;               /*!< write command for master mode only                                    */
      __O  uint32_t  WR_RD_CMD  :  1;               /*!< write and read command for master mode only                           */
    } DATA_CMD_b;                                   /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  WRITE_READ_CNT;                  /*!< I2C write and read data byte counter Register                         */

    struct {
      __IO uint32_t  RD_BYTE_CNT:  9;               /*!< Decide the number of bytes read back as a master-receiver             */
           uint32_t             :  7;
      __IO uint32_t  WR_BYTE_CNT:  9;               /*!< Decide the number of byte to send as a master-transmitter             */
    } WRITE_READ_CNT_b;                             /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  SCL_CNT;                         /*!< I2C clk pulse counter                                                 */

    struct {
      __IO uint32_t  HIGH_LEVEL_TICK: 16;           /*!< the SCL clock high-period count                                       */
      __IO uint32_t  LOW_LEVEL_TICK: 16;            /*!< the SCL clock low-period count                                        */
    } SCL_CNT_b;                                    /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED2;

  union {
    __I  uint32_t  INT_STATUS;                      /*!< I2C interrupt sources                                                 */

    struct {
      __I  uint32_t  RX_UNDER   :  1;               /*!< receiver underflow                                                    */
      __I  uint32_t  RX_OVER    :  1;               /*!< receiver overflow                                                     */
      __I  uint32_t  RX_FULL    :  1;               /*!< receiver is full                                                      */
      __I  uint32_t  TX_OVER    :  1;               /*!< transmit overflow                                                     */
      __I  uint32_t  TX_EMPTY   :  1;               /*!< transmit is empty                                                     */
      __I  uint32_t  RD_REQ     :  1;               /*!< read request                                                          */
      __I  uint32_t  TX_ABRT    :  1;               /*!< transmit abortion                                                     */
      __I  uint32_t  RX_DONE    :  1;               /*!< receive done                                                          */
      __I  uint32_t  TX_DONE    :  1;               /*!< transmit done                                                         */
      __I  uint32_t  WR_REQ     :  1;               /*!< write request                                                         */
    } INT_STATUS_b;                                 /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  INT_MASK;                        /*!< I2C interrupt mask register                                           */

    struct {
      __I  uint32_t  RX_UNDER   :  1;               /*!< receiver underflow                                                    */
      __I  uint32_t  RX_OVER    :  1;               /*!< receiver overflow                                                     */
      __I  uint32_t  RX_FULL    :  1;               /*!< receiver is full                                                      */
      __I  uint32_t  TX_OVER    :  1;               /*!< transmit overflow                                                     */
      __I  uint32_t  TX_EMPTY   :  1;               /*!< transmit is empty                                                     */
      __I  uint32_t  RD_REQ     :  1;               /*!< read request                                                          */
      __I  uint32_t  TX_ABRT    :  1;               /*!< transmit abortion                                                     */
      __I  uint32_t  RX_DONE    :  1;               /*!< receive done                                                          */
      __I  uint32_t  TX_DONE    :  1;               /*!< transmit done                                                         */
      __I  uint32_t  WR_REQ     :  1;               /*!< write request                                                         */
    } INT_MASK_b;                                   /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED3;

  union {
    __IO uint32_t  RX_TL;                           /*!< I2C receive FIFO threshold                                            */

    struct {
      __IO uint32_t  THRESHOLD  :  5;               /*!< FIFO threashold                                                       */
    } RX_TL_b;                                      /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  TX_TL;                           /*!< I2C transmit FIFO threshold                                           */

    struct {
      __IO uint32_t  THRESHOLD  :  5;               /*!< FIFO threashold                                                       */
    } TX_TL_b;                                      /*!< BitSize                                                               */
  };

  union {
    __I  uint32_t  CLR_ALL_INT;                     /*!< I2C clear all interrupt register                                      */

    struct {
      __I  uint32_t  CLEAR      :  1;               /*!< Read this register to clear all individual interrupts                 */
    } CLR_ALL_INT_b;                                /*!< BitSize                                                               */
  };

  union {
    __I  uint32_t  CLR_RX_UNDER;                    /*!< I2C clear RX_UNDER interrupt                                          */

    struct {
      __I  uint32_t  CLEAR      :  1;               /*!< Read this register to clear the RX_UNDER interrupt (bit 19)
                                                         of the I2C_STATUS register                                            */
    } CLR_RX_UNDER_b;                               /*!< BitSize                                                               */
  };

  union {
    __I  uint32_t  CLR_RX_OVER;                     /*!< I2C clear RX_OVER interrupt                                           */

    struct {
      __I  uint32_t  CLEAR      :  1;               /*!< Read this register to clear the RX_OVER interrupt (bit 20) of
                                                         the I2C_STATUS register                                               */
    } CLR_RX_OVER_b;                                /*!< BitSize                                                               */
  };

  union {
    __I  uint32_t  CLR_TX_OVER;                     /*!< I2C clear TX_OVER interrupt                                           */

    struct {
      __I  uint32_t  CLEAR      :  1;               /*!< Read this register to clear the TX_OVER interrupt (bit 22) of
                                                         the I2C_STATUS register                                               */
    } CLR_TX_OVER_b;                                /*!< BitSize                                                               */
  };

  union {
    __I  uint32_t  CLR_RD_REQ;                      /*!< I2C clear RD_REQ interrupt                                            */

    struct {
      __I  uint32_t  CLEAR      :  1;               /*!< Read this register to clear the RD_REQ interrupt (bit 24) of
                                                         the I2C_STATUS register                                               */
    } CLR_RD_REQ_b;                                 /*!< BitSize                                                               */
  };

  union {
    __I  uint32_t  CLR_TX_ABRT;                     /*!< I2C clear TX_ABRT interrupt                                           */

    struct {
      __I  uint32_t  CLEAR      :  1;               /*!< Read this register to clear the TX_ABRT interrupts (bit 25 ,
                                                         bit 18, bit 17, bit 16 and bit 15) of the I2C_STATUS register.        */
    } CLR_TX_ABRT_b;                                /*!< BitSize                                                               */
  };

  union {
    __I  uint32_t  CLR_RX_DONE;                     /*!< I2C clear RX_DONE interrupt                                           */

    struct {
      __I  uint32_t  CLEAR      :  1;               /*!< Read this register to clear the RX_DONE interrupt (bit 26) of
                                                         the I2C_STATUS register                                               */
    } CLR_RX_DONE_b;                                /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  ENABLE;                          /*!< I2C enable register                                                   */

    struct {
      __IO uint32_t  EN         :  1;               /*!< enable device                                                         */
           uint32_t             : 30;
      __IO uint32_t  RESET      :  1;               /*!< TX and RX FIFO are held in an erased state( flushed) and all
                                                         interrupts deserted                                                   */
    } ENABLE_b;                                     /*!< BitSize                                                               */
  };

  union {
    __I  uint32_t  STATUS;                          /*!< I2C status register                                                   */

    struct {
      __I  uint32_t  BUSY       :  1;               /*!< I2C busy Status                                                       */
      __I  uint32_t  TX_FIFO_NOT_FULL:  1;          /*!< transmit FIFO is not full                                             */
      __I  uint32_t  TX_FIFO_EMPTY:  1;             /*!< transmit FIFO is empty                                                */
      __I  uint32_t  RX_FIFO_NOT_EMPTY:  1;         /*!< receive FIFO is not empty                                             */
      __I  uint32_t  RX_FIFO_FULL:  1;              /*!< receive FIFO is full                                                  */
      __I  uint32_t  EN         :  1;               /*!< I2C is enabled                                                        */
      __I  uint32_t  TX_BYTE_W_ACK:  9;             /*!< Number of bytes sent to slave with acknowledge during the last
                                                         write transaction as a master-transmitter only                        */
      __I  uint32_t  ABRT_ADDR_NOACK:  1;           /*!< the address sent was not acknowledged by any slave as a master        */
      __I  uint32_t  ABRT_TX_DATA_NOACK:  1;        /*!< the data sent was not acknowledged by any slave as a master           */
      __I  uint32_t  ABRT_SLAVE_FLUSH_TX_FIFO:  1;  /*!< Slave has received a read command and some data exists in the
                                                         TX FIFO so the slave issues a TX_ABRT interrupt to flush old
                                                          data in TX FIFO                                                      */
      __I  uint32_t  ABRT_SLAVE_RD_IN_TX:  1;       /*!< When the processor side responds to a slave mode request for
                                                         data to be transmitted to a remote master and user writes a
                                                          1 in CMD (bit 8) of I2C_DATA_CMD register                            */
      __I  uint32_t  RX_UNDER   :  1;               /*!< receiver is underflow                                                 */
      __I  uint32_t  RX_OVER    :  1;               /*!< receiver is overflow                                                  */
      __I  uint32_t  RX_FULL    :  1;               /*!< receiver is full                                                      */
      __I  uint32_t  TX_OVER    :  1;               /*!< transmit is overflow                                                  */
      __I  uint32_t  TX_EMPTY   :  1;               /*!< transmit is empty                                                     */
      __I  uint32_t  RD_REQ     :  1;               /*!< read request is received                                              */
      __I  uint32_t  TX_ABRT    :  1;               /*!< transmit is abort                                                     */
      __I  uint32_t  RX_DONE    :  1;               /*!< receive is done                                                       */
      __I  uint32_t  TX_DONE    :  1;               /*!< transmit is done                                                      */
      __I  uint32_t  WR_REQ     :  1;               /*!< write request is received                                             */
      __I  uint32_t  MST_RD_FLAG:  1;               /*!< Master is executing read command                                      */
      __I  uint32_t  MST_WR_FLAG:  1;               /*!< Master is executing read command                                      */
      __I  uint32_t  MST_WR_RD_FLAG:  1;            /*!< Master is executing write-read command                                */
    } STATUS_b;                                     /*!< BitSize                                                               */
  };

  union {
    __I  uint32_t  TX_FIFO_LEVEL;                   /*!< I2C transmit FIFO level                                               */

    struct {
      __I  uint32_t  LEVEL      :  5;               /*!< FIFO level                                                            */
    } TX_FIFO_LEVEL_b;                              /*!< BitSize                                                               */
  };

  union {
    __I  uint32_t  RX_FIFO_LEVEL;                   /*!< I2C receive FIFO level                                                */

    struct {
      __I  uint32_t  LEVEL      :  5;               /*!< FIFO level                                                            */
    } RX_FIFO_LEVEL_b;                              /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED4;

  union {
    __O  uint32_t  SLAVE_NACK;                      /*!< I2C slave send a data NACK                                            */

    struct {
      __O  uint32_t  NACK       :  1;               /*!< data NACK                                                             */
    } SLAVE_NACK_b;                                 /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED5;

  union {
    __IO uint32_t  SDA_SETUP;                       /*!< I2C SDA setup timer                                                   */

    struct {
      __IO uint32_t  TSETUP     : 10;               /*!< This counter defines the max value of the following constrains:THD:STA
                                                         TSU:STO,TSETUP: T / INPUT_CLK_PERIOD                                  */
      __IO uint32_t  TSU_DAT    :  8;               /*!< This counter defines the constrain of TSU:DAT: 250ns (or 100ns)
                                                         / INPUT_CLK_PERIOD                                                    */
    } SDA_SETUP_b;                                  /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  TSU_STA_SETUP;                   /*!< I2C Tsu_sta and Tbuf_free timer                                       */

    struct {
      __IO uint32_t  TBUF       : 10;               /*!< This counter defines the constrain of bus free interval: Tbuf,
                                                         Tbuf : Tbus_free / INPUT_CLK_PERIOD                                   */
      __IO uint32_t  TSU_STA    : 10;               /*!< This counter defines the constrain of Tsu:sta, Tsu:sta : Tsu:sta
                                                         / INPUT_CLK_PERIOD                                                    */
      __IO uint32_t  SDA_FILTER_CNT:  4;            /*!< SDA filter count                                                      */
      __IO uint32_t  SDA_FILTER_EN:  1;             /*!< SDA filter enable bit                                                 */
      __IO uint32_t  SCL_FILTER_CNT:  4;            /*!< SCL filter count                                                      */
      __IO uint32_t  SCL_FILTER_EN:  1;             /*!< SCL filter enable bit                                                 */
    } TSU_STA_SETUP_b;                              /*!< BitSize                                                               */
  };

  union {
    __I  uint32_t  CLR_TX_DONE;                     /*!< I2C clear TX_DONE interrupt                                           */

    struct {
      __I  uint32_t  CLEAR      :  1;               /*!< Read this register to clear the TX_DONE interrupt (bit 27) of
                                                         the I2C_STATUS register                                               */
    } CLR_TX_DONE_b;                                /*!< BitSize                                                               */
  };
} I2C0_Type;


/* ================================================================================ */
/* ================                       RTC                      ================ */
/* ================================================================================ */


/**
  * @brief RTC (RTC)
  */

typedef struct {                                    /*!< RTC Structure                                                         */

  union {
    __IO uint32_t  INT_STATUS;                      /*!< interrupt Register                                                    */

    struct {
      __IO uint32_t  SECOND     :  1;               /*!< 1s interrupt, write 1 clear 0                                         */
      __IO uint32_t  MILLSECOND :  1;               /*!< 1ms interrupt, write 1 clear 0                                        */
    } INT_STATUS_b;                                 /*!< BitSize                                                               */
  };
  __IO uint32_t  SECOND;                            /*!< current seconds of system time                                        */

  union {
    __IO uint16_t  MILLSECOND;                      /*!< current millseconds of system time                                    */

    struct {
      __IO uint16_t  MS         : 10;               /*!< micro seconds                                                         */
    } MILLSECOND_b;                                 /*!< BitSize                                                               */
  };
} RTC_Type;


/* ================================================================================ */
/* ================                      GPIO                      ================ */
/* ================================================================================ */


/**
  * @brief GPIO (GPIO)
  */

typedef struct {                                    /*!< GPIO Structure                                                        */
  __I  uint32_t  GPIO_IN;                           /*!< GPIO input data                                                       */
  __IO uint32_t  GPIO_OUT_UNMASK;                   /*!< GPIO output mask Register                                             */
  __IO uint32_t  GPIO_OUT_DATA;                     /*!< GPIO output data register                                             */
  __IO uint32_t  GPIO_OE;                           /*!< GPIO output driver enable                                             */
  __IO uint32_t  GPIO_INT_MASK;                     /*!< GPIO input interrupt mask                                             */
  __IO uint32_t  GPIO_INT_STATUS;                   /*!< GPIO input interrupt status                                           */
  __IO uint32_t  GPIO_INT_RAW;                      /*!< GPIO input interrupt raw                                              */
  __IO uint32_t  GPIO_POSITIVE_EDGE_INT_TRIGGER;    /*!< triggers an interrupt while a positive edge, else negitive edge       */

  union {
    __IO uint32_t  PWM_OUT_SEL;                     /*!< Select gpio output from PWM                                           */

    struct {
      __IO uint32_t  GPIO_31    :  1;               /*!< GPIO[31] is selected to output PWM                                    */
      __IO uint32_t  GPIO_H_9   :  1;               /*!< GPIO_H[9] is selected to output PWM                                   */
      __IO uint32_t  GPIO_H_19  :  1;               /*!< GPIO_H[19] is selected to output PWM                                  */
      __IO uint32_t  GPIO_H_20  :  1;               /*!< GPIO_H[20] is selected to output PWM                                  */
    } PWM_OUT_SEL_b;                                /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  PWM_OUT0_LEN;                    /*!< Pwm channel 0 paramters                                               */

    struct {
      __IO uint32_t  LOW_LEVEL_TICK: 16;            /*!< low level width = ticks + 1                                           */
      __IO uint32_t  HIGH_LEVEL_TICK: 16;           /*!< high level width = ticks + 1                                          */
    } PWM_OUT0_LEN_b;                               /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  PWM_OUT1_LEN;                    /*!< Pwm channel 1 paramters                                               */

    struct {
      __IO uint32_t  LOW_LEVEL_TICK: 16;            /*!< low level width = ticks + 1                                           */
      __IO uint32_t  HIGH_LEVEL_TICK: 16;           /*!< high level width = ticks + 1                                          */
    } PWM_OUT1_LEN_b;                               /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  PWM_OUT2_LEN;                    /*!< Pwm channel 2 paramters                                               */

    struct {
      __IO uint32_t  LOW_LEVEL_TICK: 16;            /*!< low level width = ticks + 1                                           */
      __IO uint32_t  HIGH_LEVEL_TICK: 16;           /*!< high level width = ticks + 1                                          */
    } PWM_OUT2_LEN_b;                               /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  PWM_OUT3_LEN;                    /*!< Pwm channel 3 paramters                                               */

    struct {
      __IO uint32_t  LOW_LEVEL_TICK: 16;            /*!< low level width = ticks + 1                                           */
      __IO uint32_t  HIGH_LEVEL_TICK: 16;           /*!< high level width = ticks + 1                                          */
    } PWM_OUT3_LEN_b;                               /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  PWM_OUT_EN;                      /*!< Pwm enable                                                            */

    struct {
      __IO uint32_t  GPIO_31    :  1;               /*!< GPIO[31] is selected to output PWM                                    */
      __IO uint32_t  GPIO_H_9   :  1;               /*!< GPIO_H[9] is selected to output PWM                                   */
      __IO uint32_t  GPIO_H_19  :  1;               /*!< GPIO_H[19] is selected to output PWM                                  */
      __IO uint32_t  GPIO_H_20  :  1;               /*!< GPIO_H[20] is selected to output PWM                                  */
    } PWM_OUT_EN_b;                                 /*!< BitSize                                                               */
  };
  __I  uint32_t  GPIO_H_IN;                         /*!< GPIO_H input data                                                     */
  __IO uint32_t  GPIO_H_OUT_UNMASK;                 /*!< GPIO_H output unmask Register                                         */
  __IO uint32_t  GPIO_H_OUT_DATA;                   /*!< GPIO_H output data register                                           */
  __IO uint32_t  GPIO_H_OE;                         /*!< GPIO_H output driver enable                                           */
  __IO uint32_t  GPIO_H_INT_MASK;                   /*!< GPIO_H interrupt mask                                                 */
  __IO uint32_t  GPIO_H_INT_STATUS;                 /*!< GPIO_H interrupt status                                               */
  __IO uint32_t  GPIO_H_INT_RAW;                    /*!< GPIO_H interrupt raw                                                  */
  __IO uint32_t  GPIO_H_POSITIVE_EDGE_INT_TRIGGER;  /*!< triggers an interrupt while a positive edge, else negitive edge       */
  __I  uint32_t  GPIO_N_IN;                         /*!< GPIO_N input data                                                     */
  __IO uint32_t  GPIO_N_OUT_UNMASK;                 /*!< GPIO_N output unmask Register                                         */
  __IO uint32_t  GPIO_N_OUT_DATA;                   /*!< GPIO_N output data register                                           */
  __IO uint32_t  GPIO_N_OE;                         /*!< GPIO_N output driver enable                                           */
  __IO uint32_t  GPIO_N_INT_MASK;                   /*!< GPIO_N interrupt mask                                                 */
  __IO uint32_t  GPIO_N_INT_STATUS;                 /*!< GPIO_N interrupt status                                               */
  __IO uint32_t  GPIO_N_INT_RAW;                    /*!< GPIO_N interrupt raw                                                  */
  __IO uint32_t  GPIO_N_POSITIVE_EDGE_INT_TRIGGER;  /*!< triggers an interrupt while a positive edge, else negitive edge       */
} GPIO_Type;


/* ================================================================================ */
/* ================                    NOR_FLASH                   ================ */
/* ================================================================================ */


/**
  * @brief NOR_FLASH (NOR_FLASH)
  */

typedef struct {                                    /*!< NOR_FLASH Structure                                                   */

  union {
    __IO uint32_t  CTRL0;                           /*!< control Register 0                                                    */

    struct {
      __IO uint32_t  DIV        :  8;               /*!< frequency division register, fsck = fclk_io / (DIV + 1) / 2           */
      __IO uint32_t  CS_REVALID_INTERVAL:  8;       /*!< interval from CS invalid to valid, number of half cycle of SCK        */
      __IO uint32_t  RW_BYTE_CNT: 16;               /*!< RW byte count (eliminate CMD, ADDRESS, DUMMY in normal state,
                                                         contains all in transparent state. 0 is unlimited                     */
    } CTRL0_b;                                      /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  CTRL1;                           /*!< control Register 1                                                    */

    struct {
      __IO uint32_t  CMD        :  8;               /*!< operated command                                                      */
      __IO uint32_t  ADDRESS    : 24;               /*!< RW address                                                            */
    } CTRL1_b;                                      /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  TRIGGER;                         /*!< trigger register                                                      */

    struct {
      __O  uint32_t  OP_START   :  1;               /*!< operation start.                                                      */
      __IO uint32_t  OP_CLEAN   :  1;               /*!< operation clean, stop current opration and clean FIFO                 */
      __IO uint32_t  TRSP_RD_EN :  1;               /*!< if a read operation after transparent operation                       */
      __IO uint32_t  TRSP_EN    :  1;               /*!< enable transparent operation                                          */
    } TRIGGER_b;                                    /*!< BitSize                                                               */
  };

  union {
    __I  uint32_t  STATUS;                          /*!< status register                                                       */

    struct {
      __I  uint32_t  BUSY       :  1;               /*!< reading or writting                                                   */
      __I  uint32_t  RD_FIFO_ALMOST_FULL:  1;       /*!< read FIFO is almost full                                              */
      __I  uint32_t  RD_FIFO_EMPTY:  1;             /*!< read FIFO is empty                                                    */
      __I  uint32_t  RD_FIFO_FULL:  1;              /*!< read FIFO is full                                                     */
      __I  uint32_t  WR_FIFO_ALMOST_EMPTY:  1;      /*!< write FIFO is almost empty                                            */
      __I  uint32_t  WR_FIFO_FULL:  1;              /*!< write FIFO is full                                                    */
      __I  uint32_t  WR_FIFO_EMPTY:  1;             /*!< write FIFO is empty                                                   */
    } STATUS_b;                                     /*!< BitSize                                                               */
  };
  __IO uint32_t  DATA;                              /*!< data register. lower bits are significant in read and higher
                                                         bits are significant in writting                                      */

  union {
    __IO uint32_t  BYPASS;                          /*!< bypass Register, is used for JTAG connecting FLASH directly           */

    struct {
      __IO uint32_t  EN         :  1;               /*!< enable bypass                                                         */
    } BYPASS_b;                                     /*!< BitSize                                                               */
  };
} NOR_FLASH_Type;


/* ================================================================================ */
/* ================                       ADC                      ================ */
/* ================================================================================ */


/**
  * @brief ADC (ADC)
  */

typedef struct {                                    /*!< ADC Structure                                                         */

  union {
    __IO uint32_t  POWERDOWN_RESET;                 /*!< power down and reset Register                                         */

    struct {
      __IO uint32_t  RESET_ADC2 :  1;               /*!< ADC2, reset, active high                                              */
      __IO uint32_t  RESET_ADC1 :  1;               /*!< ADC1, reset, active high                                              */
      __IO uint32_t  POWERDOWN_ADC2:  1;            /*!< ADC2, power down, active high                                         */
      __IO uint32_t  POWERDOWN_ADC1:  1;            /*!< ADC1, power down, active high                                         */
    } POWERDOWN_RESET_b;                            /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  CFG0;                            /*!< config Register                                                       */

    struct {
      __IO uint32_t  VSEN       :  3;               /*!< ADC-1 VSEN Selection                                                  */
      __IO uint32_t  PHASE_CTRL :  2;               /*!< ADC-1 and ADC-2 CLK Phase Control                                     */
    } CFG0_b;                                       /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  CFG_ADC1;                        /*!< config ADC1 register                                                  */

    struct {
      __IO uint32_t  SYSTEM_MODE:  3;               /*!< system mode selection                                                 */
      __IO uint32_t  CHANNEL_SEL:  4;               /*!< channel selection                                                     */
      __IO uint32_t  MULTI_CHANNEL_CONTINUE_SCAN:  1;/*!< If continue to scan multiply channel, else single scan               */
      __IO uint32_t  MULTI_CHANNEL_BIT:  8;         /*!< each bit represents each channel                                      */
    } CFG_ADC1_b;                                   /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  CFG_ADC2;                        /*!< config ADC1 register                                                  */

    struct {
      __IO uint32_t  SYSTEM_MODE:  3;               /*!< system mode selection                                                 */
      __IO uint32_t  CHANNEL_SEL:  4;               /*!< channel selection                                                     */
      __IO uint32_t  MULTI_CHANNEL_CONTINUE_SCAN:  1;/*!< If continue to scan multiply channel, else single scan               */
      __IO uint32_t  MULTI_CHANNEL_BIT:  8;         /*!< each bit represents each channel                                      */
    } CFG_ADC2_b;                                   /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  ADC1_FIFO_CLEAR;                 /*!< clear adc1 fifo data                                                  */

    struct {
      __IO uint32_t  CLEAR      :  1;               /*!< clear fifo data, active high                                          */
    } ADC1_FIFO_CLEAR_b;                            /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  ADC2_FIFO_CLEAR;                 /*!< clear adc2 fifo data                                                  */

    struct {
      __IO uint32_t  CLEAR      :  1;               /*!< clear fifo data, active high                                          */
    } ADC2_FIFO_CLEAR_b;                            /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  ALL_ADC_FIFO_CLEAR;              /*!< clear adc1 and adc2 fifo data                                         */

    struct {
      __IO uint32_t  CLEAR      :  1;               /*!< clear fifo data, active high                                          */
    } ALL_ADC_FIFO_CLEAR_b;                         /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  INT_MASK;                        /*!< interrupt mask register                                               */

    struct {
      __IO uint32_t  ADC1_ALMOST_FULL:  1;          /*!< ADC 1 almost full                                                     */
      __IO uint32_t  ADC1_OVERFLOW:  1;             /*!< ADC 1 is overflow                                                     */
      __IO uint32_t  ADC1_EMPTY_ERR:  1;            /*!< ADC 1 read empty error                                                */
      __IO uint32_t  ADC2_ALMOST_FULL:  1;          /*!< ADC 2 almost full                                                     */
      __IO uint32_t  ADC2_OVERFLOW:  1;             /*!< ADC 2 is overflow                                                     */
      __IO uint32_t  ADC2_EMPTY_ERR:  1;            /*!< ADC 2 read empty error                                                */
    } INT_MASK_b;                                   /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  INT_RAW;                         /*!< interrupt raw register                                                */

    struct {
      __IO uint32_t  ADC1_ALMOST_FULL:  1;          /*!< ADC 1 almost full                                                     */
      __IO uint32_t  ADC1_OVERFLOW:  1;             /*!< ADC 1 is overflow                                                     */
      __IO uint32_t  ADC1_EMPTY_ERR:  1;            /*!< ADC 1 read empty error                                                */
      __IO uint32_t  ADC2_ALMOST_FULL:  1;          /*!< ADC 2 almost full                                                     */
      __IO uint32_t  ADC2_OVERFLOW:  1;             /*!< ADC 2 is overflow                                                     */
      __IO uint32_t  ADC2_EMPTY_ERR:  1;            /*!< ADC 2 read empty error                                                */
    } INT_RAW_b;                                    /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  INT_STATUS;                      /*!< interrupt status register                                             */

    struct {
      __IO uint32_t  ADC1_ALMOST_FULL:  1;          /*!< ADC 1 almost full                                                     */
      __IO uint32_t  ADC1_OVERFLOW:  1;             /*!< ADC 1 is overflow                                                     */
      __IO uint32_t  ADC1_EMPTY_ERR:  1;            /*!< ADC 1 read empty error                                                */
      __IO uint32_t  ADC2_ALMOST_FULL:  1;          /*!< ADC 2 almost full                                                     */
      __IO uint32_t  ADC2_OVERFLOW:  1;             /*!< ADC 2 is overflow                                                     */
      __IO uint32_t  ADC2_EMPTY_ERR:  1;            /*!< ADC 2 read empty error                                                */
    } INT_STATUS_b;                                 /*!< BitSize                                                               */
  };
  __I  uint32_t  ADC1_OUT;                          /*!< ADC-1 Output data (Signed-Magnitude Format)                           */
  __I  uint32_t  ADC2_OUT;                          /*!< ADC-2 Output data (Signed-Magnitude Format)                           */
  __I  uint32_t  ADC1_OUT_OFFSET_CALIBRATION;       /*!< ADC-1 Output in offset calibration when Input=0, Ideally DAO[11:0]=000h */
  __I  uint32_t  ADC2_OUT_OFFSET_CALIBRATION;       /*!< ADC-2 Output in offset calibration when Input=0, Ideally DAO[11:0]=000h */
  __I  uint32_t  ADC1_OUT_NEGTIVE_GAIN_CALIBRATION; /*!< ADC-1 Output in gain calibration when Input=-FS, Ideally DAO[11:0]=801h */
  __I  uint32_t  ADC2_OUT_NEGTIVE_GAIN_CALIBRATION; /*!< ADC-2 Output in gain calibration when Input=-FS, Ideally DAO[11:0]=801h */
  __I  uint32_t  ADC1_OUT_POSITIVE_GAIN_CALIBRATION;/*!< ADC-1 Output in gain calibration when Input=FS, Ideally DAO[11:0]=7FFh */
  __I  uint32_t  ADC2_OUT_POSITIVE_GAIN_CALIBRATION;/*!< ADC-2 Output in gain calibration when Input=FS, Ideally DAO[11:0]=7FFh */

  union {
    __I  uint32_t  EOC;                             /*!< Conversion End Indicator                                              */

    struct {
      __I  uint32_t  ADC2_EOC_GAIN:  1;             /*!< ADC2 EOC_GAIN signal, conversion is done                              */
      __I  uint32_t  ADC2_EOC_OFF:  1;              /*!< ADC2 EOC_OFF signal, conversion is done                               */
      __I  uint32_t  ADC2_EOC   :  1;               /*!< ADC2 EOC signal, conversion is done                                   */
      __I  uint32_t  ADC1_EOC_GAIN:  1;             /*!< ADC1 EOC_GAIN signal, conversion is done                              */
      __I  uint32_t  ADC1_EOC_OFF:  1;              /*!< ADC1 EOC_OFF signal, conversion is done                               */
      __I  uint32_t  ADC1_EOC   :  1;               /*!< ADC1 EOC signal, conversion is done                                   */
    } EOC_b;                                        /*!< BitSize                                                               */
  };

  union {
    __I  uint32_t  BUSY;                            /*!< ADC is busy                                                           */

    struct {
      __I  uint32_t  ADC1_BUSY  :  1;               /*!< ADC1 is busy                                                          */
      __I  uint32_t  ADC2_BUSY  :  1;               /*!< ADC2 is busy                                                          */
    } BUSY_b;                                       /*!< BitSize                                                               */
  };

  union {
    __O  uint32_t  ADC1_START;                      /*!< ADC1 startup enable                                                   */

    struct {
      __O  uint32_t  EN         :  1;               /*!< start                                                                 */
    } ADC1_START_b;                                 /*!< BitSize                                                               */
  };

  union {
    __O  uint32_t  ADC1_STOP;                       /*!< ADC1 stop enable                                                      */

    struct {
      __O  uint32_t  EN         :  1;               /*!< start                                                                 */
    } ADC1_STOP_b;                                  /*!< BitSize                                                               */
  };

  union {
    __O  uint16_t  ADC1_FIFO_READ;                  /*!< ADC1 FIFO read data                                                   */

    struct {
      __O  uint16_t  DATA       : 12;               /*!< data                                                                  */
      __O  uint16_t  CHANNEL    :  4;               /*!< channel number                                                        */
    } ADC1_FIFO_READ_b;                             /*!< BitSize                                                               */
  };
  __I  uint16_t  RESERVED0;

  union {
    __O  uint32_t  ADC2_START;                      /*!< ADC2 startup enable, only for single-conversion                       */

    struct {
      __O  uint32_t  EN         :  1;               /*!< start                                                                 */
    } ADC2_START_b;                                 /*!< BitSize                                                               */
  };

  union {
    __O  uint32_t  ADC2_STOP;                       /*!< ADC1 stop enable, only for single-conversion                          */

    struct {
      __O  uint32_t  EN         :  1;               /*!< start                                                                 */
    } ADC2_STOP_b;                                  /*!< BitSize                                                               */
  };

  union {
    __O  uint16_t  ADC2_FIFO_READ;                  /*!< ADC2 FIFO read data                                                   */

    struct {
      __O  uint16_t  DATA       : 12;               /*!< data                                                                  */
      __O  uint16_t  CHANNEL    :  4;               /*!< channel number                                                        */
    } ADC2_FIFO_READ_b;                             /*!< BitSize                                                               */
  };
  __I  uint16_t  RESERVED1;

  union {
    __O  uint32_t  ALL_ADC_START;                   /*!< all ADCs start                                                        */

    struct {
      __O  uint32_t  EN         :  1;               /*!< start                                                                 */
    } ALL_ADC_START_b;                              /*!< BitSize                                                               */
  };

  union {
    __O  uint32_t  ALL_ADC_STOP;                    /*!< all ADCs stop                                                         */

    struct {
      __O  uint32_t  EN         :  1;               /*!< start                                                                 */
    } ALL_ADC_STOP_b;                               /*!< BitSize                                                               */
  };

  union {
    __I  uint32_t  ALL_ADC_FIFO_READ;               /*!< all ADCs FIFO read data                                               */

    struct {
      __I  uint32_t  ADC1_DATA  : 12;               /*!< ADC1 data                                                             */
      __I  uint32_t  ADC1_CHANNEL:  4;              /*!< ADC1 channel number                                                   */
      __I  uint32_t  ADC2_DATA  : 12;               /*!< ADC2 data                                                             */
      __I  uint32_t  ADC2_CHANNEL:  4;              /*!< ADC2 channel number                                                   */
    } ALL_ADC_FIFO_READ_b;                          /*!< BitSize                                                               */
  };

  union {
    __I  uint32_t  STATUS;                          /*!< status register                                                       */

    struct {
      __I  uint32_t  ADC1_READ_EMPTY:  1;           /*!< ADC1 read empty                                                       */
      __I  uint32_t  ADC2_READ_EMPTY:  1;           /*!< ADC2 read empty                                                       */
      __I  uint32_t  ADC1_READ_ALMOST_EMPTY:  1;    /*!< ADC1 read almost empty                                                */
      __I  uint32_t  ADC2_READ_ALMOST_EMPTY:  1;    /*!< ADC2 read almost empty                                                */
      __I  uint32_t  ADC1_WRITE_FULL:  1;           /*!< ADC1 write full                                                       */
      __I  uint32_t  ADC2_WRITE_FULL:  1;           /*!< ADC2 write full                                                       */
      __I  uint32_t  ADC1_WRITE_ALMOST_FULL:  1;    /*!< ADC1 write almost full                                                */
      __I  uint32_t  ADC2_WRITE_ALMOST_FULL:  1;    /*!< ADC2 write almost full                                                */
    } STATUS_b;                                     /*!< BitSize                                                               */
  };
} ADC_Type;


/* ================================================================================ */
/* ================                      EFUSE                     ================ */
/* ================================================================================ */


/**
  * @brief EFUSE (EFUSE)
  */

typedef struct {                                    /*!< EFUSE Structure                                                       */

  union {
    __IO uint32_t  USER_CTRL_LOW;                   /*!< low user region control                                               */

    struct {
      __IO uint32_t  WR_EN      :  1;               /*!< write enable. 1 : write data into EFUSE. clear 0 after read           */
      __IO uint32_t  RD_EN      :  1;               /*!< read enable. 1 : write data into EFUSE. clear 0 after read            */
      __I  uint32_t  BUSY       :  1;               /*!< reading or writting                                                   */
      __IO uint32_t  COMPARE_FAIL:  1;              /*!< data read isn't consist with EFUSE                                    */
      __I  uint32_t  RD_CRC_ERR :  1;               /*!< CRC error in reading                                                  */
      __I  uint32_t  WR_CRC_ERR :  1;               /*!< CRC error in writting                                                 */
      __I  uint32_t  LOCK       :  1;               /*!< user region in EFUSE is locked, EFUSE can't be burn                   */
      __IO uint32_t  TMRF       :  2;               /*!< Reference resistor select, 1200ohm is recommended                     */
    } USER_CTRL_LOW_b;                              /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  TIMING_0;                        /*!< timing 0                                                              */

    struct {
      __IO uint32_t  TPRS       :  7;               /*!< TPRS                                                                  */
      __IO uint32_t  TESR       :  2;               /*!< TESR                                                                  */
      __IO uint32_t  TRC        :  4;               /*!< TRC                                                                   */
      __IO uint32_t  TRPW       :  3;               /*!< TRPW                                                                  */
      __IO uint32_t  TRAH       :  2;               /*!< TRAH                                                                  */
      __IO uint32_t  TRAC       :  3;               /*!< TRAC                                                                  */
           uint32_t             :  6;
      __IO uint32_t  TPWPH      :  5;               /*!< TPWPH[6:2]                                                            */
    } TIMING_0_b;                                   /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  TIMING_1;                        /*!< timing 1                                                              */

    struct {
      __IO uint32_t  TPWPS      :  7;               /*!< TPWPS                                                                 */
      __IO uint32_t  TEPS       :  4;               /*!< TEPS                                                                  */
      __IO uint32_t  TPP        : 11;               /*!< TPP                                                                   */
      __IO uint32_t  TPIT       :  8;               /*!< TPIT                                                                  */
      __IO uint32_t  TPWPH      :  2;               /*!< TPWPS[1:0]                                                            */
    } TIMING_1_b;                                   /*!< BitSize                                                               */
  };
  __IO uint32_t  USER_DATA0_LOW;                    /*!< user data [31:0]                                                      */
  __IO uint32_t  USER_DATA1_LOW;                    /*!< user data [63:32]                                                     */
  __IO uint32_t  USER_DATA2_LOW;                    /*!< user data [95:64]                                                     */
  __IO uint32_t  USER_DATA3_LOW;                    /*!< user data [127:96]                                                    */

  union {
    __IO uint32_t  USER_DATA4_LOW;                  /*!< crc and lock bit                                                      */

    struct {
      __IO uint32_t  LOCK       :  1;               /*!< write protection if true                                              */
           uint32_t             : 23;
      __IO uint32_t  CRC        :  8;               /*!< CRC                                                                   */
    } USER_DATA4_LOW_b;                             /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED0[3];

  union {
    __IO uint32_t  USER_CTRL_HI;                    /*!< high user region control                                              */

    struct {
      __IO uint32_t  WR_EN      :  1;               /*!< write enable. 1 : write data into EFUSE. clear 0 after read           */
      __IO uint32_t  RD_EN      :  1;               /*!< read enable. 1 : write data into EFUSE. clear 0 after read            */
      __I  uint32_t  BUSY       :  1;               /*!< reading or writting                                                   */
      __IO uint32_t  COMPARE_FAIL:  1;              /*!< data read isn't consist with EFUSE                                    */
      __I  uint32_t  RD_CRC_ERR :  1;               /*!< CRC error in reading                                                  */
      __I  uint32_t  WR_CRC_ERR :  1;               /*!< CRC error in writting                                                 */
      __I  uint32_t  LOCK       :  1;               /*!< user region in EFUSE is locked, EFUSE can't be burn                   */
      __IO uint32_t  TMRF       :  2;               /*!< Reference resistor select, 1200ohm is recommended                     */
    } USER_CTRL_HI_b;                               /*!< BitSize                                                               */
  };
  __IO uint32_t  USER_DATA0_HI;                     /*!< user data [159:128]                                                   */
  __IO uint32_t  USER_DATA1_HI;                     /*!< user data [191:160]                                                   */
  __IO uint32_t  USER_DATA2_HI;                     /*!< user data [223:192]                                                   */
  __IO uint32_t  USER_DATA3_HI;                     /*!< user data [255:224]                                                   */

  union {
    __IO uint32_t  USER_DATA4_HI;                   /*!< crc and lock bit                                                      */

    struct {
      __IO uint32_t  LOCK       :  1;               /*!< write protection if true                                              */
           uint32_t             : 23;
      __IO uint32_t  CRC        :  8;               /*!< CRC                                                                   */
    } USER_DATA4_HI_b;                              /*!< BitSize                                                               */
  };
} EFUSE_Type;


/* ================================================================================ */
/* ================                      CAN0                      ================ */
/* ================================================================================ */


/**
  * @brief CAN 0 (CAN0)
  */

typedef struct {                                    /*!< CAN0 Structure                                                        */

  union {
    __IO uint8_t   MODE;                            /*!< mode Register                                                         */

    struct {
      __IO uint8_t   RM         :  1;               /*!< reset mode if 1 or operation mode                                     */
      __IO uint8_t   LOM        :  1;               /*!< Listen only mode                                                      */
      __IO uint8_t   STM        :  1;               /*!< self test mode                                                        */
      __IO uint8_t   AFM        :  1;               /*!< acceptance filter mode. Single filter if 1, dual filter if 0          */
      __IO uint8_t   SM         :  1;               /*!< sleep mode                                                            */
    } MODE_b;                                       /*!< BitSize                                                               */
  };
  __I  uint8_t   RESERVED0[3];

  union {
    __O  uint8_t   CMD;                             /*!< command Register                                                      */

    struct {
      __O  uint8_t   TR         :  1;               /*!< Set to 1 when a message is to be transmitted                          */
      __O  uint8_t   AT         :  1;               /*!< Set to 1 to cancel the next transmission request                      */
      __O  uint8_t   RRB        :  1;               /*!< Set to 1 to release the Receive Buffer                                */
      __O  uint8_t   CDO        :  1;               /*!< Set to 1 to clear the data overrun condition signaled by the
                                                         Data Overrun Status bit (SR.1).                                       */
      __O  uint8_t   SSR        :  1;               /*!< Set to 1 when a message is to be transmitted and received simultaneously */
    } CMD_b;                                        /*!< BitSize                                                               */
  };
  __I  uint8_t   RESERVED1[3];

  union {
    __I  uint8_t   STATUS;                          /*!< status Register                                                       */

    struct {
      __I  uint8_t   RBNE       :  1;               /*!< Receive Buffer not empty                                              */
      __I  uint8_t   DO         :  1;               /*!< Data Overrun Status                                                   */
      __I  uint8_t   TB_UNLOCK  :  1;               /*!< Transmit Buffer is unlocked and not in transmitting                   */
      __I  uint8_t   TC         :  1;               /*!< Transmission complete                                                 */
      __I  uint8_t   RXING      :  1;               /*!< receiving the data                                                    */
      __I  uint8_t   TXING      :  1;               /*!< transmitting the data                                                 */
      __I  uint8_t   ERR        :  1;               /*!< At least one of the error counters is more than Error Warning
                                                         Limit Register                                                        */
      __I  uint8_t   BUS_OFF    :  1;               /*!< in 'Bus Off' state                                                    */
    } STATUS_b;                                     /*!< BitSize                                                               */
  };
  __I  uint8_t   RESERVED2[3];

  union {
    __I  uint8_t   INT;                             /*!< interrupt Register                                                    */

    struct {
      __I  uint8_t   RBNF       :  1;               /*!< Receive Buffer not empty                                              */
      __I  uint8_t   TB_UNLOCK  :  1;               /*!< Transmit Buffer is unlocked and not in transmitting                   */
      __I  uint8_t   ERR        :  1;               /*!< Set on every change (set or clear) of either the Bus Status
                                                         or Error Status bits (SR.7,SR.6)                                      */
      __I  uint8_t   DO         :  1;               /*!< Data Overrun Status                                                   */
      __I  uint8_t   WAKEUP     :  1;               /*!< wake-up                                                               */
      __I  uint8_t   EP         :  1;               /*!< Set when the MCAN2 re-enters error active state after being
                                                         in error passive state or when at least one error counter exceeds
                                                          the protocol-defined level of 127                                    */
      __I  uint8_t   AL         :  1;               /*!< Set when the MCAN2 loses arbitration and becomes a receiver           */
      __I  uint8_t   BUS_ERR    :  1;               /*!< Set when the MCAN2 detects an error on the CAN-bus                    */
    } INT_b;                                        /*!< BitSize                                                               */
  };
  __I  uint8_t   RESERVED3[3];

  union {
    __IO uint8_t   INT_EN;                          /*!< interrupt enabled Register                                            */

    struct {
      __I  uint8_t   RBNF       :  1;               /*!< Receive Buffer not empty                                              */
      __I  uint8_t   TB_UNLOCK  :  1;               /*!< Transmit Buffer is unlocked and not in transmitting                   */
      __I  uint8_t   ERR        :  1;               /*!< Set on every change (set or clear) of either the Bus Status
                                                         or Error Status bits (SR.7,SR.6)                                      */
      __I  uint8_t   DO         :  1;               /*!< Data Overrun Status                                                   */
      __I  uint8_t   WAKEUP     :  1;               /*!< wake-up                                                               */
      __I  uint8_t   EP         :  1;               /*!< Set when the MCAN2 re-enters error active state after being
                                                         in error passive state or when at least one error counter exceeds
                                                          the protocol-defined level of 127                                    */
      __I  uint8_t   AL         :  1;               /*!< Set when the MCAN2 loses arbitration and becomes a receiver           */
      __I  uint8_t   BUS_ERR    :  1;               /*!< Set when the MCAN2 detects an error on the CAN-bus                    */
    } INT_EN_b;                                     /*!< BitSize                                                               */
  };
  __I  uint8_t   RESERVED4[7];

  union {
    __IO uint8_t   BTR0;                            /*!< Bus Timing 0                                                          */

    struct {
      __IO uint8_t   BRP        :  6;               /*!< TQ =2 x Txtal1 x (32 x BRP.5 + 16 x BRP.4 + 8 x BRP.3 + 4 x
                                                         BRP.2 + 2 x BRP.1 + BRP.0 + 1)                                        */
      __IO uint8_t   SJW        :  2;               /*!< the maximum number of time quanta of sync segment                     */
    } BTR0_b;                                       /*!< BitSize                                                               */
  };
  __I  uint8_t   RESERVED5[3];

  union {
    __IO uint8_t   BTR1;                            /*!< Bus Timing 1                                                          */

    struct {
      __IO uint8_t   TSEG1      :  4;               /*!< the maximum number of time quanta of propagation and 1st phase
                                                         segment                                                               */
      __IO uint8_t   TSEG2      :  3;               /*!< the maximum number of time quanta of 2nd phase segment                */
      __IO uint8_t   SAM        :  1;               /*!< sample times. Sample 3 times if 1, once if 0                          */
    } BTR1_b;                                       /*!< BitSize                                                               */
  };
  __I  uint8_t   RESERVED6[3];

  union {
    __IO uint8_t   OCR;                             /*!< Output Control Register                                               */

    struct {
      __IO uint8_t   MODE       :  2;               /*!< output control mode                                                   */
    } OCR_b;                                        /*!< BitSize                                                               */
  };
  __I  uint8_t   RESERVED7[11];

  union {
    __I  uint8_t   ALC;                             /*!< Arbitration Lost Capture                                              */

    struct {
      __I  uint8_t   BIT        :  5;               /*!< the current position of the Bit Processor when bus arbitration
                                                         lost, 1st bit (ID.28) if 0                                            */
    } ALC_b;                                        /*!< BitSize                                                               */
  };
  __I  uint8_t   RESERVED8[3];

  union {
    __I  uint8_t   ECC;                             /*!< Error Code Capture                                                    */

    struct {
      __I  uint8_t   SEGMENT    :  5;               /*!< segment code                                                          */
      __I  uint8_t   DIRECTION  :  1;               /*!< If 1, the error occurred during reception. If 0, the error occurred
                                                         during transmission                                                   */
      __I  uint8_t   ERR        :  2;               /*!< error code                                                            */
    } ECC_b;                                        /*!< BitSize                                                               */
  };
  __I  uint8_t   RESERVED9[3];
  __IO uint8_t   EWLR;                              /*!< Error Warning Limit                                                   */
  __I  uint8_t   RESERVED10[3];
  __IO uint8_t   RXERR;                             /*!< Receive Error Counter                                                 */
  __I  uint8_t   RESERVED11[3];
  __IO uint8_t   TXERR;                             /*!< Transmit Error Counter                                                */
  __I  uint8_t   RESERVED12[3];

  union {
    __IO uint8_t   FI_OR_ACR0;                      /*!< Transmit Frame Information if writting or Receive Frame Information
                                                         if reading, ACR[0] if reset mode                                      */

    struct {
      __IO uint8_t   DLC        :  4;               /*!< byte number in the data                                               */
           uint8_t              :  2;
      __IO uint8_t   RTR        :  1;               /*!< 1 indicates a remote frame; 0 indicates a data frame                  */
      __IO uint8_t   FF         :  1;               /*!< 1 selects Extended Frame Format (EFF); 0 selects Standard Frame
                                                         Format (SFF)                                                          */
    } FI_OR_ACR0_b;                                 /*!< BitSize                                                               */
  };
  __I  uint8_t   RESERVED13[3];
  __IO uint8_t   DI0_OR_ACR1;                       /*!< Transmit data Information if writting or Receive data Information
                                                         if reading, ACR[1] if reset mode                                      */
  __I  uint8_t   RESERVED14[3];
  __IO uint8_t   DI1_OR_ACR2;                       /*!< Transmit data Information if writting or Receive data Information
                                                         if reading, ACR[2] if reset mode                                      */
  __I  uint8_t   RESERVED15[3];
  __IO uint8_t   DI2_OR_ACR3;                       /*!< Transmit data Information if writting or Receive data Information
                                                         if reading, ACR[3] if reset mode                                      */
  __I  uint8_t   RESERVED16[3];
  __IO uint8_t   DI3_OR_AMR0;                       /*!< Transmit data Information if writting or Receive data Information
                                                         if reading, AMR[0] if reset mode                                      */
  __I  uint8_t   RESERVED17[3];
  __IO uint8_t   DI4_OR_AMR1;                       /*!< Transmit data Information if writting or Receive data Information
                                                         if reading, AMR[1] if reset mode                                      */
  __I  uint8_t   RESERVED18[3];
  __IO uint8_t   DI5_OR_AMR2;                       /*!< Transmit data Information if writting or Receive data Information
                                                         if reading, AMR[2] if reset mode                                      */
  __I  uint8_t   RESERVED19[3];
  __IO uint8_t   DI6_OR_AMR3;                       /*!< Transmit data Information if writting or Receive data Information
                                                         if reading, AMR[3] if reset mode                                      */
  __I  uint8_t   RESERVED20[3];
  __IO uint8_t   DI7;                               /*!< Transmit data Information if writting or Receive data Information
                                                         if reading                                                            */
  __I  uint8_t   RESERVED21[3];
  __IO uint8_t   DI8;                               /*!< Transmit data Information if writting or Receive data Information
                                                         if reading                                                            */
  __I  uint8_t   RESERVED22[3];
  __IO uint8_t   DI9;                               /*!< Transmit data Information if writting or Receive data Information
                                                         if reading                                                            */
  __I  uint8_t   RESERVED23[3];
  __IO uint8_t   DI10;                              /*!< Transmit data Information if writting or Receive data Information
                                                         if reading                                                            */
  __I  uint8_t   RESERVED24[3];
  __IO uint8_t   DI11;                              /*!< Transmit data Information if writting or Receive data Information
                                                         if reading                                                            */
  __I  uint8_t   RESERVED25[3];
  __IO uint8_t   RMC;                               /*!< Receive Message Counter                                               */
  __I  uint8_t   RESERVED26[7];

  union {
    __IO uint8_t   CDR;                             /*!< Clock Divider Register                                                */

    struct {
      __IO uint8_t   DIVIDER    :  3;               /*!< divider of XTAL1                                                      */
      __IO uint8_t   OFF        :  1;               /*!< disable XTAL1                                                         */
    } CDR_b;                                        /*!< BitSize                                                               */
  };
} CAN0_Type;


/* ================================================================================ */
/* ================                       DMA                      ================ */
/* ================================================================================ */


/**
  * @brief DMA (DMA)
  */

typedef struct {                                    /*!< DMA Structure                                                         */
  __IO uint32_t  SAR0;                              /*!< Current Source Address of DMA transfer                                */
  __I  uint32_t  RESERVED0;
  __IO uint32_t  DAR0;                              /*!< Current Destination Address of DMA transfer                           */
  __I  uint32_t  RESERVED1;

  union {
    __IO uint32_t  LLP0;                            /*!< Linked List Pointer Register for Channel                              */

    struct {
      __IO uint32_t  LMS        :  2;               /*!< Identifies the AHB layer/interface where the memory device that
                                                         stores the next linked list item resides.                             */
      __IO uint32_t  LOC        : 30;               /*!< Starting Address In Memory of next LLI if block chaining is
                                                         enabled                                                               */
    } LLP0_b;                                       /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED2;

  union {
    __IO uint32_t  CTL_LOW0;                        /*!< Lower 32-bits Control Register for Channel                            */

    struct {
      __IO uint32_t  INT_EN     :  1;               /*!< Interrupt Enable Bit                                                  */
      __IO uint32_t  DST_TR_WIDTH:  3;              /*!< Destination Transfer Width                                            */
      __IO uint32_t  SRC_TR_WIDTH:  3;              /*!< Source Transfer Width                                                 */
      __IO uint32_t  DINC       :  2;               /*!< Destination Address Increment                                         */
      __IO uint32_t  SINC       :  2;               /*!< Source Address Increment                                              */
      __IO uint32_t  DEST_MSIZE :  3;               /*!< Destination Burst Transaction Length                                  */
      __IO uint32_t  SRC_MSIZE  :  3;               /*!< Source Burst Transaction Length                                       */
      __IO uint32_t  SRC_GATHER_EN:  1;             /*!< Source gather enable bit                                              */
      __IO uint32_t  DST_SCATTER_EN:  1;            /*!< Destination scatter enable bit                                        */
           uint32_t             :  1;
      __IO uint32_t  TT_FC      :  3;               /*!< Transfer Type and Flow Control                                        */
      __IO uint32_t  DMS        :  2;               /*!< Destination Master Select                                             */
      __IO uint32_t  SMS        :  2;               /*!< Source Master Select                                                  */
      __IO uint32_t  LLP_DST_EN :  1;               /*!< Block chaining is enabled on the destination side                     */
      __IO uint32_t  LLP_SRC_EN :  1;               /*!< Block chaining is enabled on the source side                          */
    } CTL_LOW0_b;                                   /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  CTL_HI0;                         /*!< Higher 32-bits Control Register for Channel                           */

    struct {
      __IO uint32_t  BLOCK_TS   : 12;               /*!< indicates the total number of single transactions to perform
                                                         for every block transfer                                              */
      __IO uint32_t  DONE       :  1;               /*!< a block transfer is complete                                          */
    } CTL_HI0_b;                                    /*!< BitSize                                                               */
  };
  __IO uint32_t  SSTAT0;                            /*!< Source Status Register for Channel                                    */
  __I  uint32_t  RESERVED3;
  __IO uint32_t  DSTAT0;                            /*!< Destination Status Register for Channel                               */
  __I  uint32_t  RESERVED4;
  __IO uint32_t  SSTATAR0;                          /*!< Source Status Address Register for Channel                            */
  __I  uint32_t  RESERVED5;
  __IO uint32_t  DSTATAR0;                          /*!< Destination Status Address Register for Channel                       */
  __I  uint32_t  RESERVED6;

  union {
    __IO uint32_t  CFG_LOW0;                        /*!< Lower 32-bit Configuration Register for Channel                       */

    struct {
           uint32_t             :  5;
      __IO uint32_t  CH_PRIOR   :  3;               /*!< Channel priority. A priority of 7 is the highest priority             */
      __IO uint32_t  CH_SUSP    :  1;               /*!< Suspends all DMA data transfers from the source until this bit
                                                         is cleared.                                                           */
      __I  uint32_t  FIFO_EMPTY :  1;               /*!< Indicates if there is data left in the channel FIFO                   */
      __IO uint32_t  HS_SEL_DST :  1;               /*!< If Destination Software handshaking interface                         */
      __IO uint32_t  HS_SEL_SRC :  1;               /*!< If Source Software handshaking interface                              */
      __IO uint32_t  LOCK_CH_L  :  2;               /*!< Indicates the duration over which CFGx.LOCK_CH bit applies.           */
      __IO uint32_t  LOCK_B_L   :  2;               /*!< Indicates the duration over which CFGx.LOCK_B bit applies.            */
      __IO uint32_t  LOCK_CH    :  1;               /*!< Channel Lock Bit                                                      */
      __IO uint32_t  LOCK_B     :  1;               /*!< Bus Lock Bit                                                          */
      __IO uint32_t  DST_HS_POL :  1;               /*!< Destination Handshaking Interface Polarity. 0: active high            */
      __IO uint32_t  SRC_HS_POL :  1;               /*!< Source Handshaking Interface Polarity. 0: active high                 */
      __IO uint32_t  MAX_ABRST  : 10;               /*!< Maximum AMBA Burst Length                                             */
      __IO uint32_t  RELOAD_SRC :  1;               /*!< Automatic Source Reload                                               */
      __IO uint32_t  RELOAD_DST :  1;               /*!< Automatic Destination Reload                                          */
    } CFG_LOW0_b;                                   /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  CFG_HI0;                         /*!< Higher 32-bit Configuration Register for Channel                      */

    struct {
      __IO uint32_t  FCMODE     :  1;               /*!< if source transaction requests aren't serviced when the Destination
                                                         Peripheral is the flow controller.                                    */
      __IO uint32_t  FIFO_MODE  :  1;               /*!< Determines space or data needs to be available in the FIFO before
                                                         a burst transaction request is serviced.                              */
      __IO uint32_t  PROTCTL    :  3;               /*!< There is a one-to-one mapping of these register bits to the
                                                         HPROT[3:1] master interface signals                                   */
      __IO uint32_t  DS_UPD_EN  :  1;               /*!< STATx is only updated from STATARx                                    */
      __IO uint32_t  SS_UPD_EN  :  1;               /*!< STATx is only updated from STATARx                                    */
    } CFG_HI0_b;                                    /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  SGR0;                            /*!< Source Gather Register for Channel                                    */

    struct {
      __IO uint32_t  SGI        : 20;               /*!< Source gather interval                                                */
      __IO uint32_t  SGC        : 12;               /*!< Specifies the number of contiguous source transfers of CTLx.SRC_TR_WIDTH */
    } SGR0_b;                                       /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED7;

  union {
    __IO uint32_t  DSR0;                            /*!< Destination Scatter Register for Channel                              */

    struct {
      __IO uint32_t  DSI        : 20;               /*!< Destination scatter interval                                          */
      __IO uint32_t  DSC        : 12;               /*!< Specifies the number of contiguous destination transfers of
                                                         CTLx.DST_TR_WIDTH                                                     */
    } DSR0_b;                                       /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED8;
  __IO uint32_t  SAR1;                              /*!< Current Source Address of DMA transfer                                */
  __I  uint32_t  RESERVED9;
  __IO uint32_t  DAR1;                              /*!< Current Destination Address of DMA transfer                           */
  __I  uint32_t  RESERVED10;

  union {
    __IO uint32_t  LLP1;                            /*!< Linked List Pointer Register for Channel                              */

    struct {
      __IO uint32_t  LMS        :  2;               /*!< Identifies the AHB layer/interface where the memory device that
                                                         stores the next linked list item resides.                             */
      __IO uint32_t  LOC        : 30;               /*!< Starting Address In Memory of next LLI if block chaining is
                                                         enabled                                                               */
    } LLP1_b;                                       /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED11;

  union {
    __IO uint32_t  CTL_LOW1;                        /*!< Lower 32-bits Control Register for Channel                            */

    struct {
      __IO uint32_t  INT_EN     :  1;               /*!< Interrupt Enable Bit                                                  */
      __IO uint32_t  DST_TR_WIDTH:  3;              /*!< Destination Transfer Width                                            */
      __IO uint32_t  SRC_TR_WIDTH:  3;              /*!< Source Transfer Width                                                 */
      __IO uint32_t  DINC       :  2;               /*!< Destination Address Increment                                         */
      __IO uint32_t  SINC       :  2;               /*!< Source Address Increment                                              */
      __IO uint32_t  DEST_MSIZE :  3;               /*!< Destination Burst Transaction Length                                  */
      __IO uint32_t  SRC_MSIZE  :  3;               /*!< Source Burst Transaction Length                                       */
      __IO uint32_t  SRC_GATHER_EN:  1;             /*!< Source gather enable bit                                              */
      __IO uint32_t  DST_SCATTER_EN:  1;            /*!< Destination scatter enable bit                                        */
           uint32_t             :  1;
      __IO uint32_t  TT_FC      :  3;               /*!< Transfer Type and Flow Control                                        */
      __IO uint32_t  DMS        :  2;               /*!< Destination Master Select                                             */
      __IO uint32_t  SMS        :  2;               /*!< Source Master Select                                                  */
      __IO uint32_t  LLP_DST_EN :  1;               /*!< Block chaining is enabled on the destination side                     */
      __IO uint32_t  LLP_SRC_EN :  1;               /*!< Block chaining is enabled on the source side                          */
    } CTL_LOW1_b;                                   /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  CTL_HI1;                         /*!< Higher 32-bits Control Register for Channel                           */

    struct {
      __IO uint32_t  BLOCK_TS   : 12;               /*!< indicates the total number of single transactions to perform
                                                         for every block transfer                                              */
      __IO uint32_t  DONE       :  1;               /*!< a block transfer is complete                                          */
    } CTL_HI1_b;                                    /*!< BitSize                                                               */
  };
  __IO uint32_t  SSTAT1;                            /*!< Source Status Register for Channel                                    */
  __I  uint32_t  RESERVED12;
  __IO uint32_t  DSTAT1;                            /*!< Destination Status Register for Channel                               */
  __I  uint32_t  RESERVED13;
  __IO uint32_t  SSTATAR1;                          /*!< Source Status Address Register for Channel                            */
  __I  uint32_t  RESERVED14;
  __IO uint32_t  DSTATAR1;                          /*!< Destination Status Address Register for Channel                       */
  __I  uint32_t  RESERVED15;

  union {
    __IO uint32_t  CFG_LOW1;                        /*!< Lower 32-bit Configuration Register for Channel                       */

    struct {
           uint32_t             :  5;
      __IO uint32_t  CH_PRIOR   :  3;               /*!< Channel priority. A priority of 7 is the highest priority             */
      __IO uint32_t  CH_SUSP    :  1;               /*!< Suspends all DMA data transfers from the source until this bit
                                                         is cleared.                                                           */
      __I  uint32_t  FIFO_EMPTY :  1;               /*!< Indicates if there is data left in the channel FIFO                   */
      __IO uint32_t  HS_SEL_DST :  1;               /*!< If Destination Software handshaking interface                         */
      __IO uint32_t  HS_SEL_SRC :  1;               /*!< If Source Software handshaking interface                              */
      __IO uint32_t  LOCK_CH_L  :  2;               /*!< Indicates the duration over which CFGx.LOCK_CH bit applies.           */
      __IO uint32_t  LOCK_B_L   :  2;               /*!< Indicates the duration over which CFGx.LOCK_B bit applies.            */
      __IO uint32_t  LOCK_CH    :  1;               /*!< Channel Lock Bit                                                      */
      __IO uint32_t  LOCK_B     :  1;               /*!< Bus Lock Bit                                                          */
      __IO uint32_t  DST_HS_POL :  1;               /*!< Destination Handshaking Interface Polarity. 0: active high            */
      __IO uint32_t  SRC_HS_POL :  1;               /*!< Source Handshaking Interface Polarity. 0: active high                 */
      __IO uint32_t  MAX_ABRST  : 10;               /*!< Maximum AMBA Burst Length                                             */
      __IO uint32_t  RELOAD_SRC :  1;               /*!< Automatic Source Reload                                               */
      __IO uint32_t  RELOAD_DST :  1;               /*!< Automatic Destination Reload                                          */
    } CFG_LOW1_b;                                   /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  CFG_HI1;                         /*!< Higher 32-bit Configuration Register for Channel                      */

    struct {
      __IO uint32_t  FCMODE     :  1;               /*!< if source transaction requests aren't serviced when the Destination
                                                         Peripheral is the flow controller.                                    */
      __IO uint32_t  FIFO_MODE  :  1;               /*!< Determines space or data needs to be available in the FIFO before
                                                         a burst transaction request is serviced.                              */
      __IO uint32_t  PROTCTL    :  3;               /*!< There is a one-to-one mapping of these register bits to the
                                                         HPROT[3:1] master interface signals                                   */
      __IO uint32_t  DS_UPD_EN  :  1;               /*!< STATx is only updated from STATARx                                    */
      __IO uint32_t  SS_UPD_EN  :  1;               /*!< STATx is only updated from STATARx                                    */
    } CFG_HI1_b;                                    /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  SGR1;                            /*!< Source Gather Register for Channel                                    */

    struct {
      __IO uint32_t  SGI        : 20;               /*!< Source gather interval                                                */
      __IO uint32_t  SGC        : 12;               /*!< Specifies the number of contiguous source transfers of CTLx.SRC_TR_WIDTH */
    } SGR1_b;                                       /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED16;

  union {
    __IO uint32_t  DSR1;                            /*!< Destination Scatter Register for Channel                              */

    struct {
      __IO uint32_t  DSI        : 20;               /*!< Destination scatter interval                                          */
      __IO uint32_t  DSC        : 12;               /*!< Specifies the number of contiguous destination transfers of
                                                         CTLx.DST_TR_WIDTH                                                     */
    } DSR1_b;                                       /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED17;
  __IO uint32_t  SAR2;                              /*!< Current Source Address of DMA transfer                                */
  __I  uint32_t  RESERVED18;
  __IO uint32_t  DAR2;                              /*!< Current Destination Address of DMA transfer                           */
  __I  uint32_t  RESERVED19;

  union {
    __IO uint32_t  LLP2;                            /*!< Linked List Pointer Register for Channel                              */

    struct {
      __IO uint32_t  LMS        :  2;               /*!< Identifies the AHB layer/interface where the memory device that
                                                         stores the next linked list item resides.                             */
      __IO uint32_t  LOC        : 30;               /*!< Starting Address In Memory of next LLI if block chaining is
                                                         enabled                                                               */
    } LLP2_b;                                       /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED20;

  union {
    __IO uint32_t  CTL_LOW2;                        /*!< Lower 32-bits Control Register for Channel                            */

    struct {
      __IO uint32_t  INT_EN     :  1;               /*!< Interrupt Enable Bit                                                  */
      __IO uint32_t  DST_TR_WIDTH:  3;              /*!< Destination Transfer Width                                            */
      __IO uint32_t  SRC_TR_WIDTH:  3;              /*!< Source Transfer Width                                                 */
      __IO uint32_t  DINC       :  2;               /*!< Destination Address Increment                                         */
      __IO uint32_t  SINC       :  2;               /*!< Source Address Increment                                              */
      __IO uint32_t  DEST_MSIZE :  3;               /*!< Destination Burst Transaction Length                                  */
      __IO uint32_t  SRC_MSIZE  :  3;               /*!< Source Burst Transaction Length                                       */
      __IO uint32_t  SRC_GATHER_EN:  1;             /*!< Source gather enable bit                                              */
      __IO uint32_t  DST_SCATTER_EN:  1;            /*!< Destination scatter enable bit                                        */
           uint32_t             :  1;
      __IO uint32_t  TT_FC      :  3;               /*!< Transfer Type and Flow Control                                        */
      __IO uint32_t  DMS        :  2;               /*!< Destination Master Select                                             */
      __IO uint32_t  SMS        :  2;               /*!< Source Master Select                                                  */
      __IO uint32_t  LLP_DST_EN :  1;               /*!< Block chaining is enabled on the destination side                     */
      __IO uint32_t  LLP_SRC_EN :  1;               /*!< Block chaining is enabled on the source side                          */
    } CTL_LOW2_b;                                   /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  CTL_HI2;                         /*!< Higher 32-bits Control Register for Channel                           */

    struct {
      __IO uint32_t  BLOCK_TS   : 12;               /*!< indicates the total number of single transactions to perform
                                                         for every block transfer                                              */
      __IO uint32_t  DONE       :  1;               /*!< a block transfer is complete                                          */
    } CTL_HI2_b;                                    /*!< BitSize                                                               */
  };
  __IO uint32_t  SSTAT2;                            /*!< Source Status Register for Channel                                    */
  __I  uint32_t  RESERVED21;
  __IO uint32_t  DSTAT2;                            /*!< Destination Status Register for Channel                               */
  __I  uint32_t  RESERVED22;
  __IO uint32_t  SSTATAR2;                          /*!< Source Status Address Register for Channel                            */
  __I  uint32_t  RESERVED23;
  __IO uint32_t  DSTATAR2;                          /*!< Destination Status Address Register for Channel                       */
  __I  uint32_t  RESERVED24;

  union {
    __IO uint32_t  CFG_LOW2;                        /*!< Lower 32-bit Configuration Register for Channel                       */

    struct {
           uint32_t             :  5;
      __IO uint32_t  CH_PRIOR   :  3;               /*!< Channel priority. A priority of 7 is the highest priority             */
      __IO uint32_t  CH_SUSP    :  1;               /*!< Suspends all DMA data transfers from the source until this bit
                                                         is cleared.                                                           */
      __I  uint32_t  FIFO_EMPTY :  1;               /*!< Indicates if there is data left in the channel FIFO                   */
      __IO uint32_t  HS_SEL_DST :  1;               /*!< If Destination Software handshaking interface                         */
      __IO uint32_t  HS_SEL_SRC :  1;               /*!< If Source Software handshaking interface                              */
      __IO uint32_t  LOCK_CH_L  :  2;               /*!< Indicates the duration over which CFGx.LOCK_CH bit applies.           */
      __IO uint32_t  LOCK_B_L   :  2;               /*!< Indicates the duration over which CFGx.LOCK_B bit applies.            */
      __IO uint32_t  LOCK_CH    :  1;               /*!< Channel Lock Bit                                                      */
      __IO uint32_t  LOCK_B     :  1;               /*!< Bus Lock Bit                                                          */
      __IO uint32_t  DST_HS_POL :  1;               /*!< Destination Handshaking Interface Polarity. 0: active high            */
      __IO uint32_t  SRC_HS_POL :  1;               /*!< Source Handshaking Interface Polarity. 0: active high                 */
      __IO uint32_t  MAX_ABRST  : 10;               /*!< Maximum AMBA Burst Length                                             */
      __IO uint32_t  RELOAD_SRC :  1;               /*!< Automatic Source Reload                                               */
      __IO uint32_t  RELOAD_DST :  1;               /*!< Automatic Destination Reload                                          */
    } CFG_LOW2_b;                                   /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  CFG_HI2;                         /*!< Higher 32-bit Configuration Register for Channel                      */

    struct {
      __IO uint32_t  FCMODE     :  1;               /*!< if source transaction requests aren't serviced when the Destination
                                                         Peripheral is the flow controller.                                    */
      __IO uint32_t  FIFO_MODE  :  1;               /*!< Determines space or data needs to be available in the FIFO before
                                                         a burst transaction request is serviced.                              */
      __IO uint32_t  PROTCTL    :  3;               /*!< There is a one-to-one mapping of these register bits to the
                                                         HPROT[3:1] master interface signals                                   */
      __IO uint32_t  DS_UPD_EN  :  1;               /*!< STATx is only updated from STATARx                                    */
      __IO uint32_t  SS_UPD_EN  :  1;               /*!< STATx is only updated from STATARx                                    */
    } CFG_HI2_b;                                    /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  SGR2;                            /*!< Source Gather Register for Channel                                    */

    struct {
      __IO uint32_t  SGI        : 20;               /*!< Source gather interval                                                */
      __IO uint32_t  SGC        : 12;               /*!< Specifies the number of contiguous source transfers of CTLx.SRC_TR_WIDTH */
    } SGR2_b;                                       /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED25;

  union {
    __IO uint32_t  DSR2;                            /*!< Destination Scatter Register for Channel                              */

    struct {
      __IO uint32_t  DSI        : 20;               /*!< Destination scatter interval                                          */
      __IO uint32_t  DSC        : 12;               /*!< Specifies the number of contiguous destination transfers of
                                                         CTLx.DST_TR_WIDTH                                                     */
    } DSR2_b;                                       /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED26;
  __IO uint32_t  SAR3;                              /*!< Current Source Address of DMA transfer                                */
  __I  uint32_t  RESERVED27;
  __IO uint32_t  DAR3;                              /*!< Current Destination Address of DMA transfer                           */
  __I  uint32_t  RESERVED28;

  union {
    __IO uint32_t  LLP3;                            /*!< Linked List Pointer Register for Channel                              */

    struct {
      __IO uint32_t  LMS        :  2;               /*!< Identifies the AHB layer/interface where the memory device that
                                                         stores the next linked list item resides.                             */
      __IO uint32_t  LOC        : 30;               /*!< Starting Address In Memory of next LLI if block chaining is
                                                         enabled                                                               */
    } LLP3_b;                                       /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED29;

  union {
    __IO uint32_t  CTL_LOW3;                        /*!< Lower 32-bits Control Register for Channel                            */

    struct {
      __IO uint32_t  INT_EN     :  1;               /*!< Interrupt Enable Bit                                                  */
      __IO uint32_t  DST_TR_WIDTH:  3;              /*!< Destination Transfer Width                                            */
      __IO uint32_t  SRC_TR_WIDTH:  3;              /*!< Source Transfer Width                                                 */
      __IO uint32_t  DINC       :  2;               /*!< Destination Address Increment                                         */
      __IO uint32_t  SINC       :  2;               /*!< Source Address Increment                                              */
      __IO uint32_t  DEST_MSIZE :  3;               /*!< Destination Burst Transaction Length                                  */
      __IO uint32_t  SRC_MSIZE  :  3;               /*!< Source Burst Transaction Length                                       */
      __IO uint32_t  SRC_GATHER_EN:  1;             /*!< Source gather enable bit                                              */
      __IO uint32_t  DST_SCATTER_EN:  1;            /*!< Destination scatter enable bit                                        */
           uint32_t             :  1;
      __IO uint32_t  TT_FC      :  3;               /*!< Transfer Type and Flow Control                                        */
      __IO uint32_t  DMS        :  2;               /*!< Destination Master Select                                             */
      __IO uint32_t  SMS        :  2;               /*!< Source Master Select                                                  */
      __IO uint32_t  LLP_DST_EN :  1;               /*!< Block chaining is enabled on the destination side                     */
      __IO uint32_t  LLP_SRC_EN :  1;               /*!< Block chaining is enabled on the source side                          */
    } CTL_LOW3_b;                                   /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  CTL_HI3;                         /*!< Higher 32-bits Control Register for Channel                           */

    struct {
      __IO uint32_t  BLOCK_TS   : 12;               /*!< indicates the total number of single transactions to perform
                                                         for every block transfer                                              */
      __IO uint32_t  DONE       :  1;               /*!< a block transfer is complete                                          */
    } CTL_HI3_b;                                    /*!< BitSize                                                               */
  };
  __IO uint32_t  SSTAT3;                            /*!< Source Status Register for Channel                                    */
  __I  uint32_t  RESERVED30;
  __IO uint32_t  DSTAT3;                            /*!< Destination Status Register for Channel                               */
  __I  uint32_t  RESERVED31;
  __IO uint32_t  SSTATAR3;                          /*!< Source Status Address Register for Channel                            */
  __I  uint32_t  RESERVED32;
  __IO uint32_t  DSTATAR3;                          /*!< Destination Status Address Register for Channel                       */
  __I  uint32_t  RESERVED33;

  union {
    __IO uint32_t  CFG_LOW3;                        /*!< Lower 32-bit Configuration Register for Channel                       */

    struct {
           uint32_t             :  5;
      __IO uint32_t  CH_PRIOR   :  3;               /*!< Channel priority. A priority of 7 is the highest priority             */
      __IO uint32_t  CH_SUSP    :  1;               /*!< Suspends all DMA data transfers from the source until this bit
                                                         is cleared.                                                           */
      __I  uint32_t  FIFO_EMPTY :  1;               /*!< Indicates if there is data left in the channel FIFO                   */
      __IO uint32_t  HS_SEL_DST :  1;               /*!< If Destination Software handshaking interface                         */
      __IO uint32_t  HS_SEL_SRC :  1;               /*!< If Source Software handshaking interface                              */
      __IO uint32_t  LOCK_CH_L  :  2;               /*!< Indicates the duration over which CFGx.LOCK_CH bit applies.           */
      __IO uint32_t  LOCK_B_L   :  2;               /*!< Indicates the duration over which CFGx.LOCK_B bit applies.            */
      __IO uint32_t  LOCK_CH    :  1;               /*!< Channel Lock Bit                                                      */
      __IO uint32_t  LOCK_B     :  1;               /*!< Bus Lock Bit                                                          */
      __IO uint32_t  DST_HS_POL :  1;               /*!< Destination Handshaking Interface Polarity. 0: active high            */
      __IO uint32_t  SRC_HS_POL :  1;               /*!< Source Handshaking Interface Polarity. 0: active high                 */
      __IO uint32_t  MAX_ABRST  : 10;               /*!< Maximum AMBA Burst Length                                             */
      __IO uint32_t  RELOAD_SRC :  1;               /*!< Automatic Source Reload                                               */
      __IO uint32_t  RELOAD_DST :  1;               /*!< Automatic Destination Reload                                          */
    } CFG_LOW3_b;                                   /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  CFG_HI3;                         /*!< Higher 32-bit Configuration Register for Channel                      */

    struct {
      __IO uint32_t  FCMODE     :  1;               /*!< if source transaction requests aren't serviced when the Destination
                                                         Peripheral is the flow controller.                                    */
      __IO uint32_t  FIFO_MODE  :  1;               /*!< Determines space or data needs to be available in the FIFO before
                                                         a burst transaction request is serviced.                              */
      __IO uint32_t  PROTCTL    :  3;               /*!< There is a one-to-one mapping of these register bits to the
                                                         HPROT[3:1] master interface signals                                   */
      __IO uint32_t  DS_UPD_EN  :  1;               /*!< STATx is only updated from STATARx                                    */
      __IO uint32_t  SS_UPD_EN  :  1;               /*!< STATx is only updated from STATARx                                    */
    } CFG_HI3_b;                                    /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  SGR3;                            /*!< Source Gather Register for Channel                                    */

    struct {
      __IO uint32_t  SGI        : 20;               /*!< Source gather interval                                                */
      __IO uint32_t  SGC        : 12;               /*!< Specifies the number of contiguous source transfers of CTLx.SRC_TR_WIDTH */
    } SGR3_b;                                       /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED34;

  union {
    __IO uint32_t  DSR3;                            /*!< Destination Scatter Register for Channel                              */

    struct {
      __IO uint32_t  DSI        : 20;               /*!< Destination scatter interval                                          */
      __IO uint32_t  DSC        : 12;               /*!< Specifies the number of contiguous destination transfers of
                                                         CTLx.DST_TR_WIDTH                                                     */
    } DSR3_b;                                       /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED35;
  __IO uint32_t  SAR4;                              /*!< Current Source Address of DMA transfer                                */
  __I  uint32_t  RESERVED36;
  __IO uint32_t  DAR4;                              /*!< Current Destination Address of DMA transfer                           */
  __I  uint32_t  RESERVED37;

  union {
    __IO uint32_t  LLP4;                            /*!< Linked List Pointer Register for Channel                              */

    struct {
      __IO uint32_t  LMS        :  2;               /*!< Identifies the AHB layer/interface where the memory device that
                                                         stores the next linked list item resides.                             */
      __IO uint32_t  LOC        : 30;               /*!< Starting Address In Memory of next LLI if block chaining is
                                                         enabled                                                               */
    } LLP4_b;                                       /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED38;

  union {
    __IO uint32_t  CTL_LOW4;                        /*!< Lower 32-bits Control Register for Channel                            */

    struct {
      __IO uint32_t  INT_EN     :  1;               /*!< Interrupt Enable Bit                                                  */
      __IO uint32_t  DST_TR_WIDTH:  3;              /*!< Destination Transfer Width                                            */
      __IO uint32_t  SRC_TR_WIDTH:  3;              /*!< Source Transfer Width                                                 */
      __IO uint32_t  DINC       :  2;               /*!< Destination Address Increment                                         */
      __IO uint32_t  SINC       :  2;               /*!< Source Address Increment                                              */
      __IO uint32_t  DEST_MSIZE :  3;               /*!< Destination Burst Transaction Length                                  */
      __IO uint32_t  SRC_MSIZE  :  3;               /*!< Source Burst Transaction Length                                       */
      __IO uint32_t  SRC_GATHER_EN:  1;             /*!< Source gather enable bit                                              */
      __IO uint32_t  DST_SCATTER_EN:  1;            /*!< Destination scatter enable bit                                        */
           uint32_t             :  1;
      __IO uint32_t  TT_FC      :  3;               /*!< Transfer Type and Flow Control                                        */
      __IO uint32_t  DMS        :  2;               /*!< Destination Master Select                                             */
      __IO uint32_t  SMS        :  2;               /*!< Source Master Select                                                  */
      __IO uint32_t  LLP_DST_EN :  1;               /*!< Block chaining is enabled on the destination side                     */
      __IO uint32_t  LLP_SRC_EN :  1;               /*!< Block chaining is enabled on the source side                          */
    } CTL_LOW4_b;                                   /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  CTL_HI4;                         /*!< Higher 32-bits Control Register for Channel                           */

    struct {
      __IO uint32_t  BLOCK_TS   : 12;               /*!< indicates the total number of single transactions to perform
                                                         for every block transfer                                              */
      __IO uint32_t  DONE       :  1;               /*!< a block transfer is complete                                          */
    } CTL_HI4_b;                                    /*!< BitSize                                                               */
  };
  __IO uint32_t  SSTAT4;                            /*!< Source Status Register for Channel                                    */
  __I  uint32_t  RESERVED39;
  __IO uint32_t  DSTAT4;                            /*!< Destination Status Register for Channel                               */
  __I  uint32_t  RESERVED40;
  __IO uint32_t  SSTATAR4;                          /*!< Source Status Address Register for Channel                            */
  __I  uint32_t  RESERVED41;
  __IO uint32_t  DSTATAR4;                          /*!< Destination Status Address Register for Channel                       */
  __I  uint32_t  RESERVED42;

  union {
    __IO uint32_t  CFG_LOW4;                        /*!< Lower 32-bit Configuration Register for Channel                       */

    struct {
           uint32_t             :  5;
      __IO uint32_t  CH_PRIOR   :  3;               /*!< Channel priority. A priority of 7 is the highest priority             */
      __IO uint32_t  CH_SUSP    :  1;               /*!< Suspends all DMA data transfers from the source until this bit
                                                         is cleared.                                                           */
      __I  uint32_t  FIFO_EMPTY :  1;               /*!< Indicates if there is data left in the channel FIFO                   */
      __IO uint32_t  HS_SEL_DST :  1;               /*!< If Destination Software handshaking interface                         */
      __IO uint32_t  HS_SEL_SRC :  1;               /*!< If Source Software handshaking interface                              */
      __IO uint32_t  LOCK_CH_L  :  2;               /*!< Indicates the duration over which CFGx.LOCK_CH bit applies.           */
      __IO uint32_t  LOCK_B_L   :  2;               /*!< Indicates the duration over which CFGx.LOCK_B bit applies.            */
      __IO uint32_t  LOCK_CH    :  1;               /*!< Channel Lock Bit                                                      */
      __IO uint32_t  LOCK_B     :  1;               /*!< Bus Lock Bit                                                          */
      __IO uint32_t  DST_HS_POL :  1;               /*!< Destination Handshaking Interface Polarity. 0: active high            */
      __IO uint32_t  SRC_HS_POL :  1;               /*!< Source Handshaking Interface Polarity. 0: active high                 */
      __IO uint32_t  MAX_ABRST  : 10;               /*!< Maximum AMBA Burst Length                                             */
      __IO uint32_t  RELOAD_SRC :  1;               /*!< Automatic Source Reload                                               */
      __IO uint32_t  RELOAD_DST :  1;               /*!< Automatic Destination Reload                                          */
    } CFG_LOW4_b;                                   /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  CFG_HI4;                         /*!< Higher 32-bit Configuration Register for Channel                      */

    struct {
      __IO uint32_t  FCMODE     :  1;               /*!< if source transaction requests aren't serviced when the Destination
                                                         Peripheral is the flow controller.                                    */
      __IO uint32_t  FIFO_MODE  :  1;               /*!< Determines space or data needs to be available in the FIFO before
                                                         a burst transaction request is serviced.                              */
      __IO uint32_t  PROTCTL    :  3;               /*!< There is a one-to-one mapping of these register bits to the
                                                         HPROT[3:1] master interface signals                                   */
      __IO uint32_t  DS_UPD_EN  :  1;               /*!< STATx is only updated from STATARx                                    */
      __IO uint32_t  SS_UPD_EN  :  1;               /*!< STATx is only updated from STATARx                                    */
    } CFG_HI4_b;                                    /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  SGR4;                            /*!< Source Gather Register for Channel                                    */

    struct {
      __IO uint32_t  SGI        : 20;               /*!< Source gather interval                                                */
      __IO uint32_t  SGC        : 12;               /*!< Specifies the number of contiguous source transfers of CTLx.SRC_TR_WIDTH */
    } SGR4_b;                                       /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED43;

  union {
    __IO uint32_t  DSR4;                            /*!< Destination Scatter Register for Channel                              */

    struct {
      __IO uint32_t  DSI        : 20;               /*!< Destination scatter interval                                          */
      __IO uint32_t  DSC        : 12;               /*!< Specifies the number of contiguous destination transfers of
                                                         CTLx.DST_TR_WIDTH                                                     */
    } DSR4_b;                                       /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED44;
  __IO uint32_t  SAR5;                              /*!< Current Source Address of DMA transfer                                */
  __I  uint32_t  RESERVED45;
  __IO uint32_t  DAR5;                              /*!< Current Destination Address of DMA transfer                           */
  __I  uint32_t  RESERVED46;

  union {
    __IO uint32_t  LLP5;                            /*!< Linked List Pointer Register for Channel                              */

    struct {
      __IO uint32_t  LMS        :  2;               /*!< Identifies the AHB layer/interface where the memory device that
                                                         stores the next linked list item resides.                             */
      __IO uint32_t  LOC        : 30;               /*!< Starting Address In Memory of next LLI if block chaining is
                                                         enabled                                                               */
    } LLP5_b;                                       /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED47;

  union {
    __IO uint32_t  CTL_LOW5;                        /*!< Lower 32-bits Control Register for Channel                            */

    struct {
      __IO uint32_t  INT_EN     :  1;               /*!< Interrupt Enable Bit                                                  */
      __IO uint32_t  DST_TR_WIDTH:  3;              /*!< Destination Transfer Width                                            */
      __IO uint32_t  SRC_TR_WIDTH:  3;              /*!< Source Transfer Width                                                 */
      __IO uint32_t  DINC       :  2;               /*!< Destination Address Increment                                         */
      __IO uint32_t  SINC       :  2;               /*!< Source Address Increment                                              */
      __IO uint32_t  DEST_MSIZE :  3;               /*!< Destination Burst Transaction Length                                  */
      __IO uint32_t  SRC_MSIZE  :  3;               /*!< Source Burst Transaction Length                                       */
      __IO uint32_t  SRC_GATHER_EN:  1;             /*!< Source gather enable bit                                              */
      __IO uint32_t  DST_SCATTER_EN:  1;            /*!< Destination scatter enable bit                                        */
           uint32_t             :  1;
      __IO uint32_t  TT_FC      :  3;               /*!< Transfer Type and Flow Control                                        */
      __IO uint32_t  DMS        :  2;               /*!< Destination Master Select                                             */
      __IO uint32_t  SMS        :  2;               /*!< Source Master Select                                                  */
      __IO uint32_t  LLP_DST_EN :  1;               /*!< Block chaining is enabled on the destination side                     */
      __IO uint32_t  LLP_SRC_EN :  1;               /*!< Block chaining is enabled on the source side                          */
    } CTL_LOW5_b;                                   /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  CTL_HI5;                         /*!< Higher 32-bits Control Register for Channel                           */

    struct {
      __IO uint32_t  BLOCK_TS   : 12;               /*!< indicates the total number of single transactions to perform
                                                         for every block transfer                                              */
      __IO uint32_t  DONE       :  1;               /*!< a block transfer is complete                                          */
    } CTL_HI5_b;                                    /*!< BitSize                                                               */
  };
  __IO uint32_t  SSTAT5;                            /*!< Source Status Register for Channel                                    */
  __I  uint32_t  RESERVED48;
  __IO uint32_t  DSTAT5;                            /*!< Destination Status Register for Channel                               */
  __I  uint32_t  RESERVED49;
  __IO uint32_t  SSTATAR5;                          /*!< Source Status Address Register for Channel                            */
  __I  uint32_t  RESERVED50;
  __IO uint32_t  DSTATAR5;                          /*!< Destination Status Address Register for Channel                       */
  __I  uint32_t  RESERVED51;

  union {
    __IO uint32_t  CFG_LOW5;                        /*!< Lower 32-bit Configuration Register for Channel                       */

    struct {
           uint32_t             :  5;
      __IO uint32_t  CH_PRIOR   :  3;               /*!< Channel priority. A priority of 7 is the highest priority             */
      __IO uint32_t  CH_SUSP    :  1;               /*!< Suspends all DMA data transfers from the source until this bit
                                                         is cleared.                                                           */
      __I  uint32_t  FIFO_EMPTY :  1;               /*!< Indicates if there is data left in the channel FIFO                   */
      __IO uint32_t  HS_SEL_DST :  1;               /*!< If Destination Software handshaking interface                         */
      __IO uint32_t  HS_SEL_SRC :  1;               /*!< If Source Software handshaking interface                              */
      __IO uint32_t  LOCK_CH_L  :  2;               /*!< Indicates the duration over which CFGx.LOCK_CH bit applies.           */
      __IO uint32_t  LOCK_B_L   :  2;               /*!< Indicates the duration over which CFGx.LOCK_B bit applies.            */
      __IO uint32_t  LOCK_CH    :  1;               /*!< Channel Lock Bit                                                      */
      __IO uint32_t  LOCK_B     :  1;               /*!< Bus Lock Bit                                                          */
      __IO uint32_t  DST_HS_POL :  1;               /*!< Destination Handshaking Interface Polarity. 0: active high            */
      __IO uint32_t  SRC_HS_POL :  1;               /*!< Source Handshaking Interface Polarity. 0: active high                 */
      __IO uint32_t  MAX_ABRST  : 10;               /*!< Maximum AMBA Burst Length                                             */
      __IO uint32_t  RELOAD_SRC :  1;               /*!< Automatic Source Reload                                               */
      __IO uint32_t  RELOAD_DST :  1;               /*!< Automatic Destination Reload                                          */
    } CFG_LOW5_b;                                   /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  CFG_HI5;                         /*!< Higher 32-bit Configuration Register for Channel                      */

    struct {
      __IO uint32_t  FCMODE     :  1;               /*!< if source transaction requests aren't serviced when the Destination
                                                         Peripheral is the flow controller.                                    */
      __IO uint32_t  FIFO_MODE  :  1;               /*!< Determines space or data needs to be available in the FIFO before
                                                         a burst transaction request is serviced.                              */
      __IO uint32_t  PROTCTL    :  3;               /*!< There is a one-to-one mapping of these register bits to the
                                                         HPROT[3:1] master interface signals                                   */
      __IO uint32_t  DS_UPD_EN  :  1;               /*!< STATx is only updated from STATARx                                    */
      __IO uint32_t  SS_UPD_EN  :  1;               /*!< STATx is only updated from STATARx                                    */
    } CFG_HI5_b;                                    /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  SGR5;                            /*!< Source Gather Register for Channel                                    */

    struct {
      __IO uint32_t  SGI        : 20;               /*!< Source gather interval                                                */
      __IO uint32_t  SGC        : 12;               /*!< Specifies the number of contiguous source transfers of CTLx.SRC_TR_WIDTH */
    } SGR5_b;                                       /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED52;

  union {
    __IO uint32_t  DSR5;                            /*!< Destination Scatter Register for Channel                              */

    struct {
      __IO uint32_t  DSI        : 20;               /*!< Destination scatter interval                                          */
      __IO uint32_t  DSC        : 12;               /*!< Specifies the number of contiguous destination transfers of
                                                         CTLx.DST_TR_WIDTH                                                     */
    } DSR5_b;                                       /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED53;
  __IO uint32_t  SAR6;                              /*!< Current Source Address of DMA transfer                                */
  __I  uint32_t  RESERVED54;
  __IO uint32_t  DAR6;                              /*!< Current Destination Address of DMA transfer                           */
  __I  uint32_t  RESERVED55;

  union {
    __IO uint32_t  LLP6;                            /*!< Linked List Pointer Register for Channel                              */

    struct {
      __IO uint32_t  LMS        :  2;               /*!< Identifies the AHB layer/interface where the memory device that
                                                         stores the next linked list item resides.                             */
      __IO uint32_t  LOC        : 30;               /*!< Starting Address In Memory of next LLI if block chaining is
                                                         enabled                                                               */
    } LLP6_b;                                       /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED56;

  union {
    __IO uint32_t  CTL_LOW6;                        /*!< Lower 32-bits Control Register for Channel                            */

    struct {
      __IO uint32_t  INT_EN     :  1;               /*!< Interrupt Enable Bit                                                  */
      __IO uint32_t  DST_TR_WIDTH:  3;              /*!< Destination Transfer Width                                            */
      __IO uint32_t  SRC_TR_WIDTH:  3;              /*!< Source Transfer Width                                                 */
      __IO uint32_t  DINC       :  2;               /*!< Destination Address Increment                                         */
      __IO uint32_t  SINC       :  2;               /*!< Source Address Increment                                              */
      __IO uint32_t  DEST_MSIZE :  3;               /*!< Destination Burst Transaction Length                                  */
      __IO uint32_t  SRC_MSIZE  :  3;               /*!< Source Burst Transaction Length                                       */
      __IO uint32_t  SRC_GATHER_EN:  1;             /*!< Source gather enable bit                                              */
      __IO uint32_t  DST_SCATTER_EN:  1;            /*!< Destination scatter enable bit                                        */
           uint32_t             :  1;
      __IO uint32_t  TT_FC      :  3;               /*!< Transfer Type and Flow Control                                        */
      __IO uint32_t  DMS        :  2;               /*!< Destination Master Select                                             */
      __IO uint32_t  SMS        :  2;               /*!< Source Master Select                                                  */
      __IO uint32_t  LLP_DST_EN :  1;               /*!< Block chaining is enabled on the destination side                     */
      __IO uint32_t  LLP_SRC_EN :  1;               /*!< Block chaining is enabled on the source side                          */
    } CTL_LOW6_b;                                   /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  CTL_HI6;                         /*!< Higher 32-bits Control Register for Channel                           */

    struct {
      __IO uint32_t  BLOCK_TS   : 12;               /*!< indicates the total number of single transactions to perform
                                                         for every block transfer                                              */
      __IO uint32_t  DONE       :  1;               /*!< a block transfer is complete                                          */
    } CTL_HI6_b;                                    /*!< BitSize                                                               */
  };
  __IO uint32_t  SSTAT6;                            /*!< Source Status Register for Channel                                    */
  __I  uint32_t  RESERVED57;
  __IO uint32_t  DSTAT6;                            /*!< Destination Status Register for Channel                               */
  __I  uint32_t  RESERVED58;
  __IO uint32_t  SSTATAR6;                          /*!< Source Status Address Register for Channel                            */
  __I  uint32_t  RESERVED59;
  __IO uint32_t  DSTATAR6;                          /*!< Destination Status Address Register for Channel                       */
  __I  uint32_t  RESERVED60;

  union {
    __IO uint32_t  CFG_LOW6;                        /*!< Lower 32-bit Configuration Register for Channel                       */

    struct {
           uint32_t             :  5;
      __IO uint32_t  CH_PRIOR   :  3;               /*!< Channel priority. A priority of 7 is the highest priority             */
      __IO uint32_t  CH_SUSP    :  1;               /*!< Suspends all DMA data transfers from the source until this bit
                                                         is cleared.                                                           */
      __I  uint32_t  FIFO_EMPTY :  1;               /*!< Indicates if there is data left in the channel FIFO                   */
      __IO uint32_t  HS_SEL_DST :  1;               /*!< If Destination Software handshaking interface                         */
      __IO uint32_t  HS_SEL_SRC :  1;               /*!< If Source Software handshaking interface                              */
      __IO uint32_t  LOCK_CH_L  :  2;               /*!< Indicates the duration over which CFGx.LOCK_CH bit applies.           */
      __IO uint32_t  LOCK_B_L   :  2;               /*!< Indicates the duration over which CFGx.LOCK_B bit applies.            */
      __IO uint32_t  LOCK_CH    :  1;               /*!< Channel Lock Bit                                                      */
      __IO uint32_t  LOCK_B     :  1;               /*!< Bus Lock Bit                                                          */
      __IO uint32_t  DST_HS_POL :  1;               /*!< Destination Handshaking Interface Polarity. 0: active high            */
      __IO uint32_t  SRC_HS_POL :  1;               /*!< Source Handshaking Interface Polarity. 0: active high                 */
      __IO uint32_t  MAX_ABRST  : 10;               /*!< Maximum AMBA Burst Length                                             */
      __IO uint32_t  RELOAD_SRC :  1;               /*!< Automatic Source Reload                                               */
      __IO uint32_t  RELOAD_DST :  1;               /*!< Automatic Destination Reload                                          */
    } CFG_LOW6_b;                                   /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  CFG_HI6;                         /*!< Higher 32-bit Configuration Register for Channel                      */

    struct {
      __IO uint32_t  FCMODE     :  1;               /*!< if source transaction requests aren't serviced when the Destination
                                                         Peripheral is the flow controller.                                    */
      __IO uint32_t  FIFO_MODE  :  1;               /*!< Determines space or data needs to be available in the FIFO before
                                                         a burst transaction request is serviced.                              */
      __IO uint32_t  PROTCTL    :  3;               /*!< There is a one-to-one mapping of these register bits to the
                                                         HPROT[3:1] master interface signals                                   */
      __IO uint32_t  DS_UPD_EN  :  1;               /*!< STATx is only updated from STATARx                                    */
      __IO uint32_t  SS_UPD_EN  :  1;               /*!< STATx is only updated from STATARx                                    */
    } CFG_HI6_b;                                    /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  SGR6;                            /*!< Source Gather Register for Channel                                    */

    struct {
      __IO uint32_t  SGI        : 20;               /*!< Source gather interval                                                */
      __IO uint32_t  SGC        : 12;               /*!< Specifies the number of contiguous source transfers of CTLx.SRC_TR_WIDTH */
    } SGR6_b;                                       /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED61;

  union {
    __IO uint32_t  DSR6;                            /*!< Destination Scatter Register for Channel                              */

    struct {
      __IO uint32_t  DSI        : 20;               /*!< Destination scatter interval                                          */
      __IO uint32_t  DSC        : 12;               /*!< Specifies the number of contiguous destination transfers of
                                                         CTLx.DST_TR_WIDTH                                                     */
    } DSR6_b;                                       /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED62;
  __IO uint32_t  SAR7;                              /*!< Current Source Address of DMA transfer                                */
  __I  uint32_t  RESERVED63;
  __IO uint32_t  DAR7;                              /*!< Current Destination Address of DMA transfer                           */
  __I  uint32_t  RESERVED64;

  union {
    __IO uint32_t  LLP7;                            /*!< Linked List Pointer Register for Channel                              */

    struct {
      __IO uint32_t  LMS        :  2;               /*!< Identifies the AHB layer/interface where the memory device that
                                                         stores the next linked list item resides.                             */
      __IO uint32_t  LOC        : 30;               /*!< Starting Address In Memory of next LLI if block chaining is
                                                         enabled                                                               */
    } LLP7_b;                                       /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED65;

  union {
    __IO uint32_t  CTL_LOW7;                        /*!< Lower 32-bits Control Register for Channel                            */

    struct {
      __IO uint32_t  INT_EN     :  1;               /*!< Interrupt Enable Bit                                                  */
      __IO uint32_t  DST_TR_WIDTH:  3;              /*!< Destination Transfer Width                                            */
      __IO uint32_t  SRC_TR_WIDTH:  3;              /*!< Source Transfer Width                                                 */
      __IO uint32_t  DINC       :  2;               /*!< Destination Address Increment                                         */
      __IO uint32_t  SINC       :  2;               /*!< Source Address Increment                                              */
      __IO uint32_t  DEST_MSIZE :  3;               /*!< Destination Burst Transaction Length                                  */
      __IO uint32_t  SRC_MSIZE  :  3;               /*!< Source Burst Transaction Length                                       */
      __IO uint32_t  SRC_GATHER_EN:  1;             /*!< Source gather enable bit                                              */
      __IO uint32_t  DST_SCATTER_EN:  1;            /*!< Destination scatter enable bit                                        */
           uint32_t             :  1;
      __IO uint32_t  TT_FC      :  3;               /*!< Transfer Type and Flow Control                                        */
      __IO uint32_t  DMS        :  2;               /*!< Destination Master Select                                             */
      __IO uint32_t  SMS        :  2;               /*!< Source Master Select                                                  */
      __IO uint32_t  LLP_DST_EN :  1;               /*!< Block chaining is enabled on the destination side                     */
      __IO uint32_t  LLP_SRC_EN :  1;               /*!< Block chaining is enabled on the source side                          */
    } CTL_LOW7_b;                                   /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  CTL_HI7;                         /*!< Higher 32-bits Control Register for Channel                           */

    struct {
      __IO uint32_t  BLOCK_TS   : 12;               /*!< indicates the total number of single transactions to perform
                                                         for every block transfer                                              */
      __IO uint32_t  DONE       :  1;               /*!< a block transfer is complete                                          */
    } CTL_HI7_b;                                    /*!< BitSize                                                               */
  };
  __IO uint32_t  SSTAT7;                            /*!< Source Status Register for Channel                                    */
  __I  uint32_t  RESERVED66;
  __IO uint32_t  DSTAT7;                            /*!< Destination Status Register for Channel                               */
  __I  uint32_t  RESERVED67;
  __IO uint32_t  SSTATAR7;                          /*!< Source Status Address Register for Channel                            */
  __I  uint32_t  RESERVED68;
  __IO uint32_t  DSTATAR7;                          /*!< Destination Status Address Register for Channel                       */
  __I  uint32_t  RESERVED69;

  union {
    __IO uint32_t  CFG_LOW7;                        /*!< Lower 32-bit Configuration Register for Channel                       */

    struct {
           uint32_t             :  5;
      __IO uint32_t  CH_PRIOR   :  3;               /*!< Channel priority. A priority of 7 is the highest priority             */
      __IO uint32_t  CH_SUSP    :  1;               /*!< Suspends all DMA data transfers from the source until this bit
                                                         is cleared.                                                           */
      __I  uint32_t  FIFO_EMPTY :  1;               /*!< Indicates if there is data left in the channel FIFO                   */
      __IO uint32_t  HS_SEL_DST :  1;               /*!< If Destination Software handshaking interface                         */
      __IO uint32_t  HS_SEL_SRC :  1;               /*!< If Source Software handshaking interface                              */
      __IO uint32_t  LOCK_CH_L  :  2;               /*!< Indicates the duration over which CFGx.LOCK_CH bit applies.           */
      __IO uint32_t  LOCK_B_L   :  2;               /*!< Indicates the duration over which CFGx.LOCK_B bit applies.            */
      __IO uint32_t  LOCK_CH    :  1;               /*!< Channel Lock Bit                                                      */
      __IO uint32_t  LOCK_B     :  1;               /*!< Bus Lock Bit                                                          */
      __IO uint32_t  DST_HS_POL :  1;               /*!< Destination Handshaking Interface Polarity. 0: active high            */
      __IO uint32_t  SRC_HS_POL :  1;               /*!< Source Handshaking Interface Polarity. 0: active high                 */
      __IO uint32_t  MAX_ABRST  : 10;               /*!< Maximum AMBA Burst Length                                             */
      __IO uint32_t  RELOAD_SRC :  1;               /*!< Automatic Source Reload                                               */
      __IO uint32_t  RELOAD_DST :  1;               /*!< Automatic Destination Reload                                          */
    } CFG_LOW7_b;                                   /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  CFG_HI7;                         /*!< Higher 32-bit Configuration Register for Channel                      */

    struct {
      __IO uint32_t  FCMODE     :  1;               /*!< if source transaction requests aren't serviced when the Destination
                                                         Peripheral is the flow controller.                                    */
      __IO uint32_t  FIFO_MODE  :  1;               /*!< Determines space or data needs to be available in the FIFO before
                                                         a burst transaction request is serviced.                              */
      __IO uint32_t  PROTCTL    :  3;               /*!< There is a one-to-one mapping of these register bits to the
                                                         HPROT[3:1] master interface signals                                   */
      __IO uint32_t  DS_UPD_EN  :  1;               /*!< STATx is only updated from STATARx                                    */
      __IO uint32_t  SS_UPD_EN  :  1;               /*!< STATx is only updated from STATARx                                    */
    } CFG_HI7_b;                                    /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  SGR7;                            /*!< Source Gather Register for Channel                                    */

    struct {
      __IO uint32_t  SGI        : 20;               /*!< Source gather interval                                                */
      __IO uint32_t  SGC        : 12;               /*!< Specifies the number of contiguous source transfers of CTLx.SRC_TR_WIDTH */
    } SGR7_b;                                       /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED70;

  union {
    __IO uint32_t  DSR7;                            /*!< Destination Scatter Register for Channel                              */

    struct {
      __IO uint32_t  DSI        : 20;               /*!< Destination scatter interval                                          */
      __IO uint32_t  DSC        : 12;               /*!< Specifies the number of contiguous destination transfers of
                                                         CTLx.DST_TR_WIDTH                                                     */
    } DSR7_b;                                       /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED71[11];
  __I  uint8_t   INT_TFR;                           /*!< DMA Transfer Complete                                                 */
  __I  uint8_t   RESERVED72[7];
  __I  uint8_t   INT_BLOCK;                         /*!< Block Transfer Complete                                               */
  __I  uint8_t   RESERVED73[7];
  __I  uint8_t   INT_SRC_TRAN;                      /*!< Source Transaction Complete                                           */
  __I  uint8_t   RESERVED74[7];
  __I  uint8_t   INT_DST_TRAN;                      /*!< Destination Transaction Complete                                      */
  __I  uint8_t   RESERVED75[7];
  __I  uint8_t   INT_ERR;                           /*!< Error                                                                 */
  __I  uint8_t   RESERVED76[7];

  union {
    __IO uint16_t  INT_EN_TFR;                      /*!< DMA Transfer Complete                                                 */

    struct {
      __IO uint16_t  EN         :  8;               /*!< interrupt enable                                                      */
      __IO uint16_t  WE         :  8;               /*!< interrupt enable write enable                                         */
    } INT_EN_TFR_b;                                 /*!< BitSize                                                               */
  };
  __I  uint16_t  RESERVED77[3];

  union {
    __IO uint16_t  INT_EN_BLOCK;                    /*!< Block Transfer Complete                                               */

    struct {
      __IO uint16_t  EN         :  8;               /*!< interrupt enable                                                      */
      __IO uint16_t  WE         :  8;               /*!< interrupt enable write enable                                         */
    } INT_EN_BLOCK_b;                               /*!< BitSize                                                               */
  };
  __I  uint16_t  RESERVED78[3];

  union {
    __IO uint16_t  INT_EN_SRC_TRAN;                 /*!< Source Transaction Complete                                           */

    struct {
      __IO uint16_t  EN         :  8;               /*!< interrupt enable                                                      */
      __IO uint16_t  WE         :  8;               /*!< interrupt enable write enable                                         */
    } INT_EN_SRC_TRAN_b;                            /*!< BitSize                                                               */
  };
  __I  uint16_t  RESERVED79[3];

  union {
    __IO uint16_t  INT_EN_DST_TRAN;                 /*!< Destination Transaction Complete                                      */

    struct {
      __IO uint16_t  EN         :  8;               /*!< interrupt enable                                                      */
      __IO uint16_t  WE         :  8;               /*!< interrupt enable write enable                                         */
    } INT_EN_DST_TRAN_b;                            /*!< BitSize                                                               */
  };
  __I  uint16_t  RESERVED80[3];

  union {
    __IO uint16_t  INT_EN_ERR;                      /*!< Error                                                                 */

    struct {
      __IO uint16_t  EN         :  8;               /*!< interrupt enable                                                      */
      __IO uint16_t  WE         :  8;               /*!< interrupt enable write enable                                         */
    } INT_EN_ERR_b;                                 /*!< BitSize                                                               */
  };
  __I  uint16_t  RESERVED81[3];
  __O  uint8_t   INT_CLEAR_TFR;                     /*!< DMA Transfer Complete                                                 */
  __I  uint8_t   RESERVED82[7];
  __O  uint8_t   INT_CLEAR_BLOCK;                   /*!< Block Transfer Complete                                               */
  __I  uint8_t   RESERVED83[7];
  __O  uint8_t   INT_CLEAR_SRC_TRAN;                /*!< Source Transaction Complete                                           */
  __I  uint8_t   RESERVED84[7];
  __O  uint8_t   INT_CLEAR_DST_TRAN;                /*!< Destination Transaction Complete                                      */
  __I  uint8_t   RESERVED85[7];
  __O  uint8_t   INT_CLEAR_ERR;                     /*!< Error                                                                 */
  __I  uint8_t   RESERVED86[63];

  union {
    __IO uint32_t  DMA_EN;                          /*!< DW_ahb_dmac Configuration Register                                    */

    struct {
      __IO uint32_t  EN         :  1;               /*!< enable                                                                */
    } DMA_EN_b;                                     /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED87;

  union {
    __IO uint32_t  CH_EN;                           /*!< DW_ahb_dmac Channel Enable Register                                   */

    struct {
      __IO uint32_t  EN         :  8;               /*!< enable                                                                */
      __IO uint32_t  WE         :  8;               /*!< enable write enable                                                   */
    } CH_EN_b;                                      /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED88[10];

  union {
    __I  uint32_t  DMA_COMP_PARAMS_6_HI;            /*!< Component Parameters for channel 7                                    */

    struct {
      __I  uint32_t  DTW        :  3;               /*!< If this is not hardcoded, then software can program the destination
                                                         transfer width.                                                       */
      __I  uint32_t  STW        :  3;               /*!< If this is not hardcoded, then software can program the source
                                                         transfer width.                                                       */
      __I  uint32_t  STAT_DST   :  1;               /*!< If destination status load feature is on                              */
      __I  uint32_t  STAT_SRC   :  1;               /*!< If source status load feature is on                                   */
      __I  uint32_t  DST_SCA_EN :  1;               /*!< If destination scatter feature is on                                  */
      __I  uint32_t  SRC_GAT_EN :  1;               /*!< If source gather feature is on                                        */
      __I  uint32_t  LOCK_EN    :  1;               /*!< If channel lock feature is on                                         */
      __I  uint32_t  MULTI_BLK_EN:  1;              /*!< If multi blocks transfer feature is on                                */
      __I  uint32_t  CTL_WB_EN  :  1;               /*!< If write back initial values to relative registers feature is
                                                         on                                                                    */
      __I  uint32_t  HC_LLP     :  1;               /*!< If disable LLP feature is on                                          */
           uint32_t             :  2;
      __I  uint32_t  MAX_MULT_SIZE:  3;             /*!< Maximum value of burst transaction size (SRC_MSIZE and DEST_MSIZE).   */
      __I  uint32_t  DMS        :  3;               /*!< Destination AHB dma interface                                         */
      __I  uint32_t  LMS        :  3;               /*!< Linked list AHB dma interface                                         */
      __I  uint32_t  SMS        :  3;               /*!< source AHB dma interface                                              */
      __I  uint32_t  FIFO_DEPTH :  3;               /*!< FIFO depth in bytes                                                   */
    } DMA_COMP_PARAMS_6_HI_b;                       /*!< BitSize                                                               */
  };

  union {
    __I  uint32_t  DMA_COMP_PARAMS_5_LOW;           /*!< Component Parameters for channel 6                                    */

    struct {
      __I  uint32_t  DTW        :  3;               /*!< If this is not hardcoded, then software can program the destination
                                                         transfer width.                                                       */
      __I  uint32_t  STW        :  3;               /*!< If this is not hardcoded, then software can program the source
                                                         transfer width.                                                       */
      __I  uint32_t  STAT_DST   :  1;               /*!< If destination status load feature is on                              */
      __I  uint32_t  STAT_SRC   :  1;               /*!< If source status load feature is on                                   */
      __I  uint32_t  DST_SCA_EN :  1;               /*!< If destination scatter feature is on                                  */
      __I  uint32_t  SRC_GAT_EN :  1;               /*!< If source gather feature is on                                        */
      __I  uint32_t  LOCK_EN    :  1;               /*!< If channel lock feature is on                                         */
      __I  uint32_t  MULTI_BLK_EN:  1;              /*!< If multi blocks transfer feature is on                                */
      __I  uint32_t  CTL_WB_EN  :  1;               /*!< If write back initial values to relative registers feature is
                                                         on                                                                    */
      __I  uint32_t  HC_LLP     :  1;               /*!< If disable LLP feature is on                                          */
           uint32_t             :  2;
      __I  uint32_t  MAX_MULT_SIZE:  3;             /*!< Maximum value of burst transaction size (SRC_MSIZE and DEST_MSIZE).   */
      __I  uint32_t  DMS        :  3;               /*!< Destination AHB dma interface                                         */
      __I  uint32_t  LMS        :  3;               /*!< Linked list AHB dma interface                                         */
      __I  uint32_t  SMS        :  3;               /*!< source AHB dma interface                                              */
      __I  uint32_t  FIFO_DEPTH :  3;               /*!< FIFO depth in bytes                                                   */
    } DMA_COMP_PARAMS_5_LOW_b;                      /*!< BitSize                                                               */
  };

  union {
    __I  uint32_t  DMA_COMP_PARAMS_5_HI;            /*!< Component Parameters for channel 5                                    */

    struct {
      __I  uint32_t  DTW        :  3;               /*!< If this is not hardcoded, then software can program the destination
                                                         transfer width.                                                       */
      __I  uint32_t  STW        :  3;               /*!< If this is not hardcoded, then software can program the source
                                                         transfer width.                                                       */
      __I  uint32_t  STAT_DST   :  1;               /*!< If destination status load feature is on                              */
      __I  uint32_t  STAT_SRC   :  1;               /*!< If source status load feature is on                                   */
      __I  uint32_t  DST_SCA_EN :  1;               /*!< If destination scatter feature is on                                  */
      __I  uint32_t  SRC_GAT_EN :  1;               /*!< If source gather feature is on                                        */
      __I  uint32_t  LOCK_EN    :  1;               /*!< If channel lock feature is on                                         */
      __I  uint32_t  MULTI_BLK_EN:  1;              /*!< If multi blocks transfer feature is on                                */
      __I  uint32_t  CTL_WB_EN  :  1;               /*!< If write back initial values to relative registers feature is
                                                         on                                                                    */
      __I  uint32_t  HC_LLP     :  1;               /*!< If disable LLP feature is on                                          */
           uint32_t             :  2;
      __I  uint32_t  MAX_MULT_SIZE:  3;             /*!< Maximum value of burst transaction size (SRC_MSIZE and DEST_MSIZE).   */
      __I  uint32_t  DMS        :  3;               /*!< Destination AHB dma interface                                         */
      __I  uint32_t  LMS        :  3;               /*!< Linked list AHB dma interface                                         */
      __I  uint32_t  SMS        :  3;               /*!< source AHB dma interface                                              */
      __I  uint32_t  FIFO_DEPTH :  3;               /*!< FIFO depth in bytes                                                   */
    } DMA_COMP_PARAMS_5_HI_b;                       /*!< BitSize                                                               */
  };

  union {
    __I  uint32_t  DMA_COMP_PARAMS_4_LOW;           /*!< Component Parameters for channel 4                                    */

    struct {
      __I  uint32_t  DTW        :  3;               /*!< If this is not hardcoded, then software can program the destination
                                                         transfer width.                                                       */
      __I  uint32_t  STW        :  3;               /*!< If this is not hardcoded, then software can program the source
                                                         transfer width.                                                       */
      __I  uint32_t  STAT_DST   :  1;               /*!< If destination status load feature is on                              */
      __I  uint32_t  STAT_SRC   :  1;               /*!< If source status load feature is on                                   */
      __I  uint32_t  DST_SCA_EN :  1;               /*!< If destination scatter feature is on                                  */
      __I  uint32_t  SRC_GAT_EN :  1;               /*!< If source gather feature is on                                        */
      __I  uint32_t  LOCK_EN    :  1;               /*!< If channel lock feature is on                                         */
      __I  uint32_t  MULTI_BLK_EN:  1;              /*!< If multi blocks transfer feature is on                                */
      __I  uint32_t  CTL_WB_EN  :  1;               /*!< If write back initial values to relative registers feature is
                                                         on                                                                    */
      __I  uint32_t  HC_LLP     :  1;               /*!< If disable LLP feature is on                                          */
           uint32_t             :  2;
      __I  uint32_t  MAX_MULT_SIZE:  3;             /*!< Maximum value of burst transaction size (SRC_MSIZE and DEST_MSIZE).   */
      __I  uint32_t  DMS        :  3;               /*!< Destination AHB dma interface                                         */
      __I  uint32_t  LMS        :  3;               /*!< Linked list AHB dma interface                                         */
      __I  uint32_t  SMS        :  3;               /*!< source AHB dma interface                                              */
      __I  uint32_t  FIFO_DEPTH :  3;               /*!< FIFO depth in bytes                                                   */
    } DMA_COMP_PARAMS_4_LOW_b;                      /*!< BitSize                                                               */
  };

  union {
    __I  uint32_t  DMA_COMP_PARAMS_4_HI;            /*!< Component Parameters for channel 3                                    */

    struct {
      __I  uint32_t  DTW        :  3;               /*!< If this is not hardcoded, then software can program the destination
                                                         transfer width.                                                       */
      __I  uint32_t  STW        :  3;               /*!< If this is not hardcoded, then software can program the source
                                                         transfer width.                                                       */
      __I  uint32_t  STAT_DST   :  1;               /*!< If destination status load feature is on                              */
      __I  uint32_t  STAT_SRC   :  1;               /*!< If source status load feature is on                                   */
      __I  uint32_t  DST_SCA_EN :  1;               /*!< If destination scatter feature is on                                  */
      __I  uint32_t  SRC_GAT_EN :  1;               /*!< If source gather feature is on                                        */
      __I  uint32_t  LOCK_EN    :  1;               /*!< If channel lock feature is on                                         */
      __I  uint32_t  MULTI_BLK_EN:  1;              /*!< If multi blocks transfer feature is on                                */
      __I  uint32_t  CTL_WB_EN  :  1;               /*!< If write back initial values to relative registers feature is
                                                         on                                                                    */
      __I  uint32_t  HC_LLP     :  1;               /*!< If disable LLP feature is on                                          */
           uint32_t             :  2;
      __I  uint32_t  MAX_MULT_SIZE:  3;             /*!< Maximum value of burst transaction size (SRC_MSIZE and DEST_MSIZE).   */
      __I  uint32_t  DMS        :  3;               /*!< Destination AHB dma interface                                         */
      __I  uint32_t  LMS        :  3;               /*!< Linked list AHB dma interface                                         */
      __I  uint32_t  SMS        :  3;               /*!< source AHB dma interface                                              */
      __I  uint32_t  FIFO_DEPTH :  3;               /*!< FIFO depth in bytes                                                   */
    } DMA_COMP_PARAMS_4_HI_b;                       /*!< BitSize                                                               */
  };

  union {
    __I  uint32_t  DMA_COMP_PARAMS_3_LOW;           /*!< Component Parameters for channel 2                                    */

    struct {
      __I  uint32_t  DTW        :  3;               /*!< If this is not hardcoded, then software can program the destination
                                                         transfer width.                                                       */
      __I  uint32_t  STW        :  3;               /*!< If this is not hardcoded, then software can program the source
                                                         transfer width.                                                       */
      __I  uint32_t  STAT_DST   :  1;               /*!< If destination status load feature is on                              */
      __I  uint32_t  STAT_SRC   :  1;               /*!< If source status load feature is on                                   */
      __I  uint32_t  DST_SCA_EN :  1;               /*!< If destination scatter feature is on                                  */
      __I  uint32_t  SRC_GAT_EN :  1;               /*!< If source gather feature is on                                        */
      __I  uint32_t  LOCK_EN    :  1;               /*!< If channel lock feature is on                                         */
      __I  uint32_t  MULTI_BLK_EN:  1;              /*!< If multi blocks transfer feature is on                                */
      __I  uint32_t  CTL_WB_EN  :  1;               /*!< If write back initial values to relative registers feature is
                                                         on                                                                    */
      __I  uint32_t  HC_LLP     :  1;               /*!< If disable LLP feature is on                                          */
           uint32_t             :  2;
      __I  uint32_t  MAX_MULT_SIZE:  3;             /*!< Maximum value of burst transaction size (SRC_MSIZE and DEST_MSIZE).   */
      __I  uint32_t  DMS        :  3;               /*!< Destination AHB dma interface                                         */
      __I  uint32_t  LMS        :  3;               /*!< Linked list AHB dma interface                                         */
      __I  uint32_t  SMS        :  3;               /*!< source AHB dma interface                                              */
      __I  uint32_t  FIFO_DEPTH :  3;               /*!< FIFO depth in bytes                                                   */
    } DMA_COMP_PARAMS_3_LOW_b;                      /*!< BitSize                                                               */
  };

  union {
    __I  uint32_t  DMA_COMP_PARAMS_3_HI;            /*!< Component Parameters for channel 1                                    */

    struct {
      __I  uint32_t  DTW        :  3;               /*!< If this is not hardcoded, then software can program the destination
                                                         transfer width.                                                       */
      __I  uint32_t  STW        :  3;               /*!< If this is not hardcoded, then software can program the source
                                                         transfer width.                                                       */
      __I  uint32_t  STAT_DST   :  1;               /*!< If destination status load feature is on                              */
      __I  uint32_t  STAT_SRC   :  1;               /*!< If source status load feature is on                                   */
      __I  uint32_t  DST_SCA_EN :  1;               /*!< If destination scatter feature is on                                  */
      __I  uint32_t  SRC_GAT_EN :  1;               /*!< If source gather feature is on                                        */
      __I  uint32_t  LOCK_EN    :  1;               /*!< If channel lock feature is on                                         */
      __I  uint32_t  MULTI_BLK_EN:  1;              /*!< If multi blocks transfer feature is on                                */
      __I  uint32_t  CTL_WB_EN  :  1;               /*!< If write back initial values to relative registers feature is
                                                         on                                                                    */
      __I  uint32_t  HC_LLP     :  1;               /*!< If disable LLP feature is on                                          */
           uint32_t             :  2;
      __I  uint32_t  MAX_MULT_SIZE:  3;             /*!< Maximum value of burst transaction size (SRC_MSIZE and DEST_MSIZE).   */
      __I  uint32_t  DMS        :  3;               /*!< Destination AHB dma interface                                         */
      __I  uint32_t  LMS        :  3;               /*!< Linked list AHB dma interface                                         */
      __I  uint32_t  SMS        :  3;               /*!< source AHB dma interface                                              */
      __I  uint32_t  FIFO_DEPTH :  3;               /*!< FIFO depth in bytes                                                   */
    } DMA_COMP_PARAMS_3_HI_b;                       /*!< BitSize                                                               */
  };

  union {
    __I  uint32_t  DMA_COMP_PARAMS_2_LOW;           /*!< Component Parameters for channel 0                                    */

    struct {
      __I  uint32_t  DTW        :  3;               /*!< If this is not hardcoded, then software can program the destination
                                                         transfer width.                                                       */
      __I  uint32_t  STW        :  3;               /*!< If this is not hardcoded, then software can program the source
                                                         transfer width.                                                       */
      __I  uint32_t  STAT_DST   :  1;               /*!< If destination status load feature is on                              */
      __I  uint32_t  STAT_SRC   :  1;               /*!< If source status load feature is on                                   */
      __I  uint32_t  DST_SCA_EN :  1;               /*!< If destination scatter feature is on                                  */
      __I  uint32_t  SRC_GAT_EN :  1;               /*!< If source gather feature is on                                        */
      __I  uint32_t  LOCK_EN    :  1;               /*!< If channel lock feature is on                                         */
      __I  uint32_t  MULTI_BLK_EN:  1;              /*!< If multi blocks transfer feature is on                                */
      __I  uint32_t  CTL_WB_EN  :  1;               /*!< If write back initial values to relative registers feature is
                                                         on                                                                    */
      __I  uint32_t  HC_LLP     :  1;               /*!< If disable LLP feature is on                                          */
           uint32_t             :  2;
      __I  uint32_t  MAX_MULT_SIZE:  3;             /*!< Maximum value of burst transaction size (SRC_MSIZE and DEST_MSIZE).   */
      __I  uint32_t  DMS        :  3;               /*!< Destination AHB dma interface                                         */
      __I  uint32_t  LMS        :  3;               /*!< Linked list AHB dma interface                                         */
      __I  uint32_t  SMS        :  3;               /*!< source AHB dma interface                                              */
      __I  uint32_t  FIFO_DEPTH :  3;               /*!< FIFO depth in bytes                                                   */
    } DMA_COMP_PARAMS_2_LOW_b;                      /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED89;

  union {
    __I  uint32_t  DMA_COMP_PARAMS_1_LOW;           /*!< Maximum block size for channel                                        */

    struct {
      __I  uint32_t  CH0_MAX_BLK_SIZE:  4;          /*!< Maximum block size for channel 0.                                     */
      __I  uint32_t  CH1_MAX_BLK_SIZE:  4;          /*!< Maximum block size for channel 1                                      */
      __I  uint32_t  CH2_MAX_BLK_SIZE:  4;          /*!< Maximum block size for channel 2                                      */
      __I  uint32_t  CH3_MAX_BLK_SIZE:  4;          /*!< Maximum block size for channel 3                                      */
      __I  uint32_t  CH4_MAX_BLK_SIZE:  4;          /*!< Maximum block size for channel 4                                      */
      __I  uint32_t  CH5_MAX_BLK_SIZE:  4;          /*!< Maximum block size for channel 5                                      */
      __I  uint32_t  CH6_MAX_BLK_SIZE:  4;          /*!< Maximum block size for channel 6                                      */
      __I  uint32_t  CH7_MAX_BLK_SIZE:  4;          /*!< Maximum block size for channel 7                                      */
    } DMA_COMP_PARAMS_1_LOW_b;                      /*!< BitSize                                                               */
  };
} DMA_Type;


/* ================================================================================ */
/* ================                       ETH                      ================ */
/* ================================================================================ */


/**
  * @brief ETH (ETH)
  */

typedef struct {                                    /*!< ETH Structure                                                         */

  union {
    __IO uint32_t  CONFIG;                          /*!< MAC Configuration Register                                            */

    struct {
      __IO uint32_t  PRELEN     :  2;               /*!< Preamble Length for Transmit frames                                   */
      __IO uint32_t  RX_EN      :  1;               /*!< Receiver Enable                                                       */
      __IO uint32_t  TX_EN      :  1;               /*!< Transmitter Enable                                                    */
      __IO uint32_t  DC_EN      :  1;               /*!< Deferral Check Enable                                                 */
           uint32_t             :  2;
      __IO uint32_t  ACS        :  1;               /*!< Automatic Pad or CRC Stripping                                        */
      __IO uint32_t  LUD        :  1;               /*!< Link Up or Down                                                       */
           uint32_t             :  1;
      __IO uint32_t  IPC        :  1;               /*!< Checksum Offload                                                      */
      __IO uint32_t  DM         :  1;               /*!< Duplex Mode                                                           */
      __IO uint32_t  LM         :  1;               /*!< Loopback Mode                                                         */
           uint32_t             :  1;
      __IO uint32_t  FES        :  1;               /*!< Speed in XMII interface                                               */
      __IO uint32_t  PS         :  1;               /*!< the Ethernet line speed                                               */
           uint32_t             :  4;
      __IO uint32_t  JE         :  1;               /*!< Jumbo enable                                                          */
           uint32_t             :  1;
      __IO uint32_t  JD         :  1;               /*!< if 0, the MAC cuts off the transmitter if more than 2,048 bytes
                                                         of data (10,240 if JE is set high)                                    */
      __IO uint32_t  WD         :  1;               /*!< Watchdog Disable                                                      */
      __IO uint32_t  TC         :  1;               /*!< If 1, this bit enables the transmission of duplex mode, link
                                                         speed, and link up or down information to the PHY                     */
      __IO uint32_t  CST        :  1;               /*!< CRC Stripping for Type Frames                                         */
           uint32_t             :  1;
      __IO uint32_t  TWOKPE     :  1;               /*!< If 0, 1518 bytes is considered as a giant frame, 1 is 2000 bytes.     */
      __IO uint32_t  SARC       :  3;               /*!< Source Address Insertion or Replacement Control                       */
    } CONFIG_b;                                     /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  FF;                              /*!< MAC Frame Filter                                                      */

    struct {
      __IO uint32_t  PR         :  1;               /*!< Receive all frames in spite of source and destination address         */
      __IO uint32_t  HUC        :  1;               /*!< if 1, don't compare DA field in destination address filtering
                                                         of unicast frames with DA register                                    */
      __IO uint32_t  HMC        :  1;               /*!< if 1, don't compare DA field in destination address filtering
                                                         of multicast frames with DA register                                  */
      __IO uint32_t  DAIF       :  1;               /*!< if set, the Address Check block operates in inverse filtering
                                                         mode for the DA address comparison                                    */
      __IO uint32_t  PM         :  1;               /*!< Pass All Multicast                                                    */
      __IO uint32_t  DBF        :  1;               /*!< Disable Broadcast Frames                                              */
      __IO uint32_t  PCF        :  2;               /*!< Pass Control Frames                                                   */
      __IO uint32_t  SAIF       :  1;               /*!< If set, the frames whose SA matches the SA registers are marked
                                                         as failing the SA Address filter                                      */
      __IO uint32_t  SAF        :  1;               /*!< Source Address Filter Enable                                          */
      __IO uint32_t  HPF        :  1;               /*!< Hash or Perfect Filter                                                */
           uint32_t             :  5;
      __IO uint32_t  VTFE       :  1;               /*!< VLAN Tag Filter Enable                                                */
           uint32_t             :  3;
      __IO uint32_t  IPFE       :  1;               /*!< Layer 3 and Layer 4 Filter Enable                                     */
      __IO uint32_t  DNTU       :  1;               /*!< Drop non-TCP/UDP over IP Frames                                       */
           uint32_t             :  9;
      __IO uint32_t  RA         :  1;               /*!< Receive all                                                           */
    } FF_b;                                         /*!< BitSize                                                               */
  };
  __IO uint32_t  HTH;                               /*!< Hash Table High Register                                              */
  __IO uint32_t  HTL;                               /*!< Hash Table Low Register                                               */

  union {
    __IO uint32_t  GMII_ADDR;                       /*!< GMII Address Register                                                 */

    struct {
      __IO uint32_t  BUSY       :  1;               /*!< GMII Busy                                                             */
      __IO uint32_t  GW         :  1;               /*!< GMII write or read                                                    */
      __IO uint32_t  CR         :  4;               /*!< CSR Clock Range                                                       */
      __IO uint32_t  GR         :  5;               /*!< These bits select the desired GMII register in the selected
                                                         PHY device                                                            */
      __IO uint32_t  PA         :  5;               /*!< This field indicates which of the 32 possible PHY devices are
                                                         being accessed                                                        */
    } GMII_ADDR_b;                                  /*!< BitSize                                                               */
  };
  __IO uint32_t  GMII_DATA;                         /*!< GMII Data Register                                                    */

  union {
    __IO uint32_t  FC;                              /*!< Flow Control Register                                                 */

    struct {
      __IO uint32_t  FCB        :  1;               /*!< This bit initiates a Pause frame in the full-duplex mode              */
      __IO uint32_t  TFE        :  1;               /*!< MAC enables the flow control operation to transmit Pause frames       */
      __IO uint32_t  RFE        :  1;               /*!< MAC enables the flow control operation to receive Pause frames        */
      __IO uint32_t  UP         :  1;               /*!< MAC can detect Pause frames with unicast address of the station       */
    } FC_b;                                         /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  VLAN_TAG;                        /*!< VLAN Tag Register                                                     */

    struct {
      __IO uint32_t  VL         : 16;               /*!< VLAN Tag Identifier for Receive Frames                                */
      __IO uint32_t  ETV        :  1;               /*!< Enable 12-Bit VLAN Tag Comparison                                     */
      __IO uint32_t  VTIM       :  1;               /*!< If set, The frames that do not have matching VLAN Tag are marked
                                                         as matched                                                            */
      __IO uint32_t  ESVL       :  1;               /*!< If set, consider the S-VLAN (Type = 0x88A8) frames as valid
                                                         VLAN tagged frames                                                    */
      __IO uint32_t  VTHM       :  1;               /*!< When set, the most significant four bits of the VLAN tag's CRC
                                                         are used to index the content                                         */
    } VLAN_TAG_b;                                   /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED0[2];
  __IO uint32_t  RWUFFR;                            /*!< Remote Wake-Up Frame Filter Register                                  */

  union {
    __IO uint32_t  PMTCSR;                          /*!< PMT Control and Status Register                                       */

    struct {
      __IO uint32_t  PWRDWN     :  1;               /*!< Power Down                                                            */
      __IO uint32_t  MGKPKTEN   :  1;               /*!< Magic Packet Enable                                                   */
      __IO uint32_t  RWKPKTEN   :  1;               /*!< Remote Wake-Up Frame Enable                                           */
           uint32_t             :  2;
      __IO uint32_t  MGKPRCVD   :  1;               /*!< the power management event is generated because of the reception
                                                         of a magic packet                                                     */
      __IO uint32_t  RWKPRCVD   :  1;               /*!< When set, this bit indicates the power management event is generated
                                                         because of the reception of a remote wake-up frame                    */
           uint32_t             :  2;
      __IO uint32_t  GLBLUCAST  :  1;               /*!< When set, enables any unicast packet filtered by the MAC (DAF)address
                                                         recognition to be a remote wake-up frame.                             */
           uint32_t             : 14;
      __IO uint32_t  RWKPTR     :  3;               /*!< Remote Wake-up FIFO Pointer                                           */
           uint32_t             :  4;
      __IO uint32_t  RWKFILTRST :  1;               /*!< Remote Wake-Up Frame Filter Register Pointer Reset.                   */
    } PMTCSR_b;                                     /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED1[2];
  __IO uint32_t  MACISR;                            /*!< Interrupt Status Register                                             */
  __IO uint32_t  MACIMR;                            /*!< Interrupt Mask Register                                               */
  __IO uint16_t  ADDR0_HIGH;                        /*!< MAC Address0 High Register                                            */
  __I  uint16_t  RESERVED2;
  __IO uint32_t  ADDR0_LOW;                         /*!< MAC Address0 LOW Register                                             */

  union {
    __IO uint32_t  ADDR1_HIGH;                      /*!< MAC Address0 High Register                                            */

    struct {
      __IO uint32_t  ADDR       : 16;               /*!< MAC Address1 [47:32]                                                  */
           uint32_t             : 14;
      __IO uint32_t  SA         :  1;               /*!< MAC address1 is source or destination address compared with
                                                         received frame                                                        */
      __IO uint32_t  AE         :  1;               /*!< the address filter module uses the MAC address1 for filtering         */
    } ADDR1_HIGH_b;                                 /*!< BitSize                                                               */
  };
  __IO uint32_t  ADDR1_LOW;                         /*!< MAC Address1 LOW Register                                             */
  __I  uint32_t  RESERVED3[44];

  union {
    __IO uint32_t  MMCCR;                           /*!< MMC Control Register                                                  */

    struct {
      __IO uint32_t  CNTRST     :  1;               /*!< Counters Reset                                                        */
      __IO uint32_t  CNTSTOPRO  :  1;               /*!< Counter Stop Rollover                                                 */
      __IO uint32_t  RSTONRD    :  1;               /*!< Reset on Read                                                         */
      __IO uint32_t  CNTFREEZ   :  1;               /*!< MMC Counter Freeze                                                    */
      __IO uint32_t  CNTPRST    :  1;               /*!< Counters Preset                                                       */
      __IO uint32_t  CNTPRSTLVL :  1;               /*!< Counters Preset                                                       */
           uint32_t             :  2;
      __IO uint32_t  UCDBC      :  1;               /*!< Update MMC Counters for Dropped Broadcast Frames                      */
    } MMCCR_b;                                      /*!< BitSize                                                               */
  };
  __IO uint32_t  MMCRIR;                            /*!< MMC Receive Interrupt Register                                        */
  __IO uint32_t  MMCTIR;                            /*!< MMC Transmit Interrupt Register                                       */
  __IO uint32_t  MMCRIMR;                           /*!< MMC Receive interrupt mask                                            */
  __IO uint32_t  MMCTIMR;                           /*!< MMC Transmit Interrupt Mask                                           */
  __I  uint32_t  RESERVED4[59];
  __IO uint32_t  MMCIRCOIM;                         /*!< MMC IPC Receive Checksum Offload Interrupt Mask                       */
  __I  uint32_t  RESERVED5[319];

  union {
    __IO uint32_t  PTPTSCR;                         /*!< Timestamp Control Register                                            */

    struct {
      __IO uint32_t  TSENA      :  1;               /*!< Timestamp Enable                                                      */
      __IO uint32_t  TSCFUPDT   :  1;               /*!< Timestamp Fine or Coarse Update                                       */
      __IO uint32_t  TSINIT     :  1;               /*!< Timestamp Initialize                                                  */
      __IO uint32_t  TSUPDT     :  1;               /*!< Timestamp Update                                                      */
      __IO uint32_t  TSTRIG     :  1;               /*!< Timestamp Interrupt Trigger Enable                                    */
      __IO uint32_t  TSADDREG   :  1;               /*!< Addend Reg Update                                                     */
    } PTPTSCR_b;                                    /*!< BitSize                                                               */
  };
  __IO uint32_t  PTPSSIR;                           /*!< Sub-Second Increment Register                                         */
  __IO uint32_t  PTPTSHR;                           /*!< System Time Seconds Register                                          */
  __IO uint32_t  PTPTSLR;                           /*!< System Time Nanoseconds Register                                      */
  __IO uint32_t  PTPTSHUR;                          /*!< System Time Seconds Update Register                                   */
  __IO uint32_t  PTPTSLUR;                          /*!< System Time Nanoseconds Update Register                               */
  __IO uint32_t  PTPTSAR;                           /*!< Timestamp Addend Register                                             */
  __IO uint32_t  PTPTTHR;                           /*!< Target Time Seconds Register                                          */
  __IO uint32_t  PTPTTLR;                           /*!< Target Time Nanoseconds Register                                      */
  __I  uint32_t  RESERVED6[567];

  union {
    __IO uint32_t  BUS_MODE;                        /*!< Flow Control Register                                                 */

    struct {
      __IO uint32_t  SWR        :  1;               /*!< Software Reset                                                        */
      __IO uint32_t  DA         :  1;               /*!< This bit specifies the arbitration scheme between the transmit
                                                         and receive paths of Channel                                          */
      __IO uint32_t  DSL        :  5;               /*!< the byte number of bus width to skip between two unchained descriptors */
      __IO uint32_t  ATDS       :  1;               /*!< When set, the size of the alternate descriptor increases to
                                                         32 bytes                                                              */
      __IO uint32_t  PBL        :  6;               /*!< These bits indicate the maximum number of beats to be transferred
                                                         in one DMA transaction                                                */
      __IO uint32_t  PR         :  2;               /*!< The Priority Ratio is (PR + 1) : 1                                    */
      __IO uint32_t  FB         :  1;               /*!< performs fixed burst transfers or not                                 */
      __IO uint32_t  RPBL       :  6;               /*!< This field indicates the maximum number of beats to be transferred
                                                         in one Rx DMA transaction                                             */
      __IO uint32_t  USP        :  1;               /*!< If set, RPBL is same as RPBL definition                               */
      __IO uint32_t  PBLx8      :  1;               /*!< If set, all PBLs multiplies 8                                         */
      __IO uint32_t  AAL        :  1;               /*!< If set, all bursts aligned to the start address LS bits               */
      __IO uint32_t  MB         :  1;               /*!< When this bit is set high and the FB bit is low, the AHB master
                                                         interface starts all bursts of length more than 16 with INCR          */
      __IO uint32_t  TXPR       :  1;               /*!< When set, the transmit DMA has higher priority than the receive
                                                         DMA                                                                   */
      __IO uint32_t  PRWG       :  2;               /*!< The Priority weight is (PRWG + 1) : 1                                 */
           uint32_t             :  1;
      __IO uint32_t  RIB        :  1;               /*!< If set, rebuilds the pending beats of any burst transfer initiated
                                                         with INCRx                                                            */
    } BUS_MODE_b;                                   /*!< BitSize                                                               */
  };
  __IO uint32_t  TPD;                               /*!< Transmit Poll Demand                                                  */
  __IO uint32_t  RPD;                               /*!< Receive Poll Demand                                                   */
  __IO uint32_t  RDESLA;                            /*!< Receive Descriptor List Address                                       */
  __IO uint32_t  TDESLA;                            /*!< Transmit Descriptor List Address                                      */

  union {
    __IO uint32_t  STATUS;                          /*!< Status Register                                                       */

    struct {
      __IO uint32_t  TI         :  1;               /*!< This bit indicates that the frame transmission is complete            */
      __IO uint32_t  TPS        :  1;               /*!< Transmit Process Stopped                                              */
      __IO uint32_t  TU         :  1;               /*!< the host owns the Next Descriptor in the Transmit List and the
                                                         DMA cannot acquire it.                                                */
      __IO uint32_t  TJT        :  1;               /*!< Transmit Jabber Timeout                                               */
      __IO uint32_t  OVF        :  1;               /*!< Receive Overflow                                                      */
      __IO uint32_t  UNF        :  1;               /*!< Transmit Underflow                                                    */
      __IO uint32_t  RI         :  1;               /*!< the frame reception is complete                                       */
      __IO uint32_t  RU         :  1;               /*!< Receive Buffer Unavailable                                            */
      __IO uint32_t  RPS        :  1;               /*!< Receive Process Stopped                                               */
      __IO uint32_t  RWT        :  1;               /*!< Receive Watchdog Timeout                                              */
      __IO uint32_t  ETI        :  1;               /*!< the frame to be transmitted is fully transferred to the MTL
                                                         Transmit FIFO                                                         */
           uint32_t             :  2;
      __IO uint32_t  FBI        :  1;               /*!< a bus error occurred, as described in EB.                             */
      __IO uint32_t  ERI        :  1;               /*!< the DMA filled the first data buffer of the packet                    */
      __IO uint32_t  AIS        :  1;               /*!< Abnormal Interrupt Summary, must be cleared by writting               */
      __IO uint32_t  NIS        :  1;               /*!< Normal Interrupt Summary, must be cleared by writting                 */
      __I  uint32_t  RS         :  3;               /*!< Receive DMA FSM state                                                 */
      __I  uint32_t  TS         :  3;               /*!< Transmit DMA FSM state                                                */
      __I  uint32_t  EB         :  3;               /*!< Error bit                                                             */
      __I  uint32_t  GLI        :  1;               /*!< GMAC Line Interface Interrupt                                         */
      __I  uint32_t  GMI        :  1;               /*!< GMAC MMC Interrupt                                                    */
      __I  uint32_t  GPI        :  1;               /*!< GMAC PMT Interrupt                                                    */
      __I  uint32_t  TTI        :  1;               /*!< Timestamp Trigger Interrupt                                           */
    } STATUS_b;                                     /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  OPERATION;                       /*!< Operation Mode Register                                               */

    struct {
           uint32_t             :  1;
      __IO uint32_t  SR         :  1;               /*!< Start or Stop Receive                                                 */
      __IO uint32_t  OSF        :  1;               /*!< Operate on Second Frame                                               */
      __IO uint32_t  RT         :  2;               /*!< Receive Threshold Control                                             */
      __IO uint32_t  DGF        :  1;               /*!< Drop Giant Frames                                                     */
      __IO uint32_t  FUF        :  1;               /*!< Forward Undersized Good Frames                                        */
      __IO uint32_t  FEF        :  1;               /*!< Forward Error Frames                                                  */
           uint32_t             :  5;
      __IO uint32_t  ST         :  1;               /*!< Start or Stop Transmission Command                                    */
      __IO uint32_t  TT         :  3;               /*!< Transmit Threshold Control                                            */
           uint32_t             :  3;
      __IO uint32_t  FTF        :  1;               /*!< Flush Transmit FIFO                                                   */
      __IO uint32_t  TSF        :  1;               /*!< If set, transmission starts when a full frame resides in Transmit
                                                         FIFO                                                                  */
           uint32_t             :  2;
      __IO uint32_t  DFF        :  1;               /*!< Disable Flushing of Received Frames                                   */
      __IO uint32_t  RSF        :  1;               /*!< If set, the MTL reads a frame from the Rx FIFO while the complete
                                                         frame has been written to it,                                         */
    } OPERATION_b;                                  /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  INT_EN;                          /*!< Interrupt Enable Register                                             */

    struct {
      __IO uint32_t  TIE        :  1;               /*!< Transmit Interrupt Enable                                             */
      __IO uint32_t  TSE        :  1;               /*!< Transmit Stopped Enable                                               */
      __IO uint32_t  TUE        :  1;               /*!< Transmit Buffer Unavailable Enable                                    */
      __IO uint32_t  TJE        :  1;               /*!< Transmit Jabber Timeout Enable                                        */
      __IO uint32_t  OVE        :  1;               /*!< Overflow Interrupt Enable                                             */
      __IO uint32_t  UNE        :  1;               /*!< Underflow Interrupt Enable                                            */
      __IO uint32_t  RIE        :  1;               /*!< Receive Interrupt Enable                                              */
      __IO uint32_t  RUE        :  1;               /*!< Receive Buffer Unavailable Enable                                     */
      __IO uint32_t  RSE        :  1;               /*!< Receive Stopped Enable                                                */
      __IO uint32_t  RWE        :  1;               /*!< Receive Watchdog Timeout Enable                                       */
      __IO uint32_t  ETE        :  1;               /*!< Early Transmit Interrupt Enable                                       */
           uint32_t             :  2;
      __IO uint32_t  FBE        :  1;               /*!< Fatal Bus Error Enable                                                */
      __IO uint32_t  ERE        :  1;               /*!< Early Receive Interrupt Enable                                        */
      __IO uint32_t  AIE        :  1;               /*!< Abnormal Interrupt Summary Enable                                     */
      __IO uint32_t  NIE        :  1;               /*!< Normal Interrupt Summary Enable                                       */
    } INT_EN_b;                                     /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED7[3];

  union {
    __IO uint32_t  AHB_STATUS;                      /*!< AHB Status Register                                                   */

    struct {
      __IO uint32_t  BUSY       :  1;               /*!< If set, it indicates that the AHB master interface FSMs are
                                                         in the non-idle state                                                 */
    } AHB_STATUS_b;                                 /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED8[6];
  __I  uint32_t  CURTDESAPTR;                       /*!< Current Host Transmit Descriptor Register                             */
  __I  uint32_t  CURRDESAPTR;                       /*!< Current Host Receive Descriptor Register                              */
  __I  uint32_t  CURTBUFAPTR;                       /*!< Current Host Transmit Buffer Address Register                         */
  __I  uint32_t  CURRBUFAPTR;                       /*!< Current Host Receive Buffer Address Register                          */
} ETH_Type;


/* ================================================================================ */
/* ================                       USB                      ================ */
/* ================================================================================ */


/**
  * @brief USB (USB)
  */

typedef struct {                                    /*!< USB Structure                                                         */

  union {
    __IO uint32_t  GOTGCTL;                         /*!< Control and Status register                                           */

    struct {
      __I  uint32_t  SES_REQ_SCS:  1;               /*!< set when a session request initiation is successful as a device       */
      __IO uint32_t  SES_SEQ    :  1;               /*!< set to initiate a session request on the USB as a device              */
      __IO uint32_t  VB_VALID_OV_EN:  1;            /*!< enable/disable the software to override the Bvalid signal using
                                                         the GOTGCTL.VbvalidOvVal as a host                                    */
      __IO uint32_t  VB_VALID_OV_VAL:  1;           /*!< set Override value for vbusvalid signal when GOTGCTL.VbvalidOvEn
                                                         is set as a host                                                      */
      __IO uint32_t  A_VALID_OV_EN:  1;             /*!< enable/disable the software to override the Avalid signal using
                                                         the GOTGCTL.AvalidOvVal as a host                                     */
      __IO uint32_t  A_VALID_OV_VAL:  1;            /*!< set Override value for Avalid signal when GOTGCTL.AvalidOvEn
                                                         is set as a host                                                      */
      __IO uint32_t  B_VALID_OV_EN:  1;             /*!< enable/disable the software to override the Bvalid signal using
                                                         the GOTGCTL.BvalidOvVal as a device.                                  */
      __IO uint32_t  B_VALID_OV_VAL:  1;            /*!< set Override value for Bvalid signal when GOTGCTL.BvalidOvEn
                                                         is set as a device.                                                   */
      __I  uint32_t  HST_NEG_SCS:  1;               /*!< sets when host negotiation is successful as a device.                 */
      __IO uint32_t  HNP_REQ    :  1;               /*!< sets this bit to initiate an HNP request to the connected USB
                                                         host as a device                                                      */
      __IO uint32_t  HST_SET_HNP_EN:  1;            /*!< Host Set HNP Enable as a host                                         */
      __IO uint32_t  DEV_HNP_EN :  1;               /*!< Device HNP Enabled as a device                                        */
           uint32_t             :  4;
      __I  uint32_t  CON_ID_STS :  1;               /*!< Connector ID Status                                                   */
      __I  uint32_t  DBNC_TIME  :  1;               /*!< the debounce time of a detected connection as a host                  */
      __I  uint32_t  A_SES_VLD  :  1;               /*!< A-Session Valid as a host                                             */
      __I  uint32_t  B_SES_VLD  :  1;               /*!< B-Session Valid as a host                                             */
      __IO uint32_t  OTG_VER    :  1;               /*!< If 0, OTG Version 1.3. If 1, OTG Version 2.0.                         */
    } GOTGCTL_b;                                    /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  GOTGINT;                         /*!< OTG interrupt Register                                                */

    struct {
           uint32_t             :  2;
      __IO uint32_t  SES_END_DET:  1;               /*!< Set when the utmiotg_bvalid signal is deasserted                      */
           uint32_t             :  5;
      __IO uint32_t  SES_REQ_SUC_STS_CHNG:  1;      /*!< Session Request Success Status Change                                 */
      __IO uint32_t  HST_NEG_SUC_STS_CHNG:  1;      /*!< Host Negotiation Success Status Change                                */
           uint32_t             :  7;
      __IO uint32_t  HST_NEG_DET:  1;               /*!< if set, detects a host negotiation request on the USB                 */
      __IO uint32_t  A_DEV_TOUT_CHG:  1;            /*!< A-device has timed out while waiting for the B-device to connect      */
      __IO uint32_t  DBNCE_DONE :  1;               /*!< debounce is completed after the device connect as a host              */
    } GOTGINT_b;                                    /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  GAHBCFG;                         /*!< AHB Configuration Register                                            */

    struct {
      __IO uint32_t  GLBL_INTR_EN:  1;              /*!< Global Interrupt Enable                                               */
      __IO uint32_t  BST_LEN    :  4;               /*!< Burst Length/Type                                                     */
      __IO uint32_t  DMA_EN     :  1;               /*!< DMA enable                                                            */
           uint32_t             : 15;
      __IO uint32_t  REMOTE_MEM_SUPP:  1;           /*!< enable the functionality to wait for the system DMA Done Signal
                                                         for the DMA Write Transfers                                           */
      __IO uint32_t  NOTIFY_ALL_DMA_WRITE:  1;      /*!< enable the System DMA Done functionality for all the DMA write
                                                         Transactions corresponding to the Channel/Endpoint                    */
      __IO uint32_t  AHB_SINGLE :  1;               /*!< supports Single transfers for the remaining data in a transfer        */
    } GAHBCFG_b;                                    /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  GUSBCFG;                         /*!< USB Configuration Register                                            */

    struct {
           uint32_t             :  3;
      __IO uint32_t  PHY_IF     :  1;               /*!< PHY Interface                                                         */
      __IO uint32_t  ULPI_UTMI_SEL:  1;             /*!< 1, ULPI. 0, UTMI+                                                     */
      __IO uint32_t  FS_IF      :  1;               /*!< 1, 3-pin bidirectional. 0, 6-pin unidirectional                       */
      __IO uint32_t  PHY_SEL    :  1;               /*!< 0, USB 2.0 High-Speed PHY. 1, USB 1.1 full-speed serial transceiver   */
      __IO uint32_t  DDR_SEL    :  1;               /*!< 0, Single Data Rate ULPI Interface, with 8-bit-wide data bus.
                                                         1, Double Data Rate ULPI Interface, with 4-bit-wide data bus          */
      __IO uint32_t  SRP_CAP    :  1;               /*!< SRP-Capable                                                           */
      __IO uint32_t  HNP_CAP    :  1;               /*!< HNP-Capable                                                           */
      __IO uint32_t  USB_TRD_TIM:  4;               /*!< Specifies the response time for a MAC request to the Packet
                                                         FIFO Controller (PFC) to fetch data from the DFIFO (SPRAM) as
                                                          a device.                                                            */
           uint32_t             :  1;
      __IO uint32_t  PHY_LPWR_CLK_SEL:  1;          /*!< 0, 480-MHz Internal PLL clock. 1, 48-MHz External Clock               */
           uint32_t             : 12;
      __IO uint32_t  TX_END_DELAY:  1;              /*!< Tx End Delay as a device                                              */
      __IO uint32_t  FORCE_HOST_MODE:  1;           /*!< Force Host Mode                                                       */
      __IO uint32_t  FORCE_DEVICE_MODE:  1;         /*!< Force Device Mode                                                     */
    } GUSBCFG_b;                                    /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  GRSTCTL;                         /*!< Reset Register                                                        */

    struct {
      __IO uint32_t  CORE_SOFT_RST:  1;             /*!< Core Soft Reset                                                       */
           uint32_t             :  1;
      __IO uint32_t  FRM_CNT_RST:  1;               /*!< Host Frame Counter Reset                                              */
           uint32_t             :  1;
      __IO uint32_t  RX_FIFO_FLUSH:  1;             /*!< RxFIFO Flush                                                          */
      __IO uint32_t  TX_FIFO_FLUSH:  1;             /*!< TxFIFO Flush                                                          */
      __IO uint32_t  TX_FIFO_FLUSH_NUM:  4;         /*!< This field indicates which of the 32 possible PHY devices are
                                                         being accessed                                                        */
      __IO uint32_t  TX_FIFO_ALL:  1;               /*!< TxFIFO flush all FIFOs                                                */
           uint32_t             : 19;
      __I  uint32_t  DMA_REQ    :  1;               /*!< Indicates that the DMA request is in progress                         */
      __I  uint32_t  AHB_IDLE   :  1;               /*!< Indicates that the AHB Master State Machine is in the IDLE condition  */
    } GRSTCTL_b;                                    /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  GINTSTS;                         /*!< Interrupt Register                                                    */

    struct {
      __I  uint32_t  CUR_MOD    :  1;               /*!< Current Mode of Operation                                             */
      __IO uint32_t  MODE_MIS   :  1;               /*!< Mode Mismatch Interrupt                                               */
      __I  uint32_t  OTG_INT    :  1;               /*!< OTG Interrupt                                                         */
      __IO uint32_t  SOF        :  1;               /*!< Start of (micro)Frame                                                 */
      __I  uint32_t  RFNE       :  1;               /*!< RxFIFO Non-Empty                                                      */
      __I  uint32_t  NPTFE      :  1;               /*!< Non-periodic TxFIFO Empty                                             */
      __I  uint32_t  GIN_NAK_EFF:  1;               /*!< Global IN Non-periodic NAK Effective as a device                      */
      __I  uint32_t  GOUT_NAK_EFF:  1;              /*!< Global OUT NAK Effective as a device                                  */
           uint32_t             :  2;
      __IO uint32_t  EARLY_SUS  :  1;               /*!< an Idle state has been detected on the USB For 3 ms as a device       */
      __IO uint32_t  USB_SUS    :  1;               /*!< A suspend was detected on the USB as a device                         */
      __IO uint32_t  USB_RST    :  1;               /*!< A reset is detected on the USB as a device                            */
      __IO uint32_t  ENUM_DONE  :  1;               /*!< speed enumeration is complete as a device                             */
      __IO uint32_t  ISO_OUT_DROP:  1;              /*!< Drop an isochronous OUT packet while no space in RXFIFO as a
                                                         device                                                                */
      __IO uint32_t  EOPF       :  1;               /*!< End of Periodic Frame Interrupt as a device                           */
           uint32_t             :  1;
      __I  uint32_t  EP_MIS     :  1;               /*!< Endpoint Mismatch Interrupt as a device                               */
      __I  uint32_t  IEP_INT    :  1;               /*!< IN Endpoints Interrupt as a device                                    */
      __I  uint32_t  OEP_INT    :  1;               /*!< OUT Endpoints Interrupt as a device                                   */
      __IO uint32_t  INCOMP_ISO_IN:  1;             /*!< Incomplete Isochronous IN Transfer as a device                        */
      __IO uint32_t  IPT_IIOT   :  1;               /*!< OUT Incomplete Periodic Transfer as a host or Incomplete Isochronous
                                                         OUT Transfer as a device                                              */
      __IO uint32_t  DFS        :  1;               /*!< Data Fetch Suspended as a device                                      */
      __IO uint32_t  RST_DET    :  1;               /*!< reset detect as a device                                              */
      __I  uint32_t  HP         :  1;               /*!< a change in port status of one of the DWC_otg core ports as
                                                         a host                                                                */
      __I  uint32_t  HC         :  1;               /*!< an interrupt is pending on one of the channels of the core as
                                                         a host                                                                */
      __I  uint32_t  PTFE       :  1;               /*!< Periodic TxFIFO Empty as a host                                       */
      __IO uint32_t  LPM        :  1;               /*!< LPM Transaction Received Interrupt                                    */
      __IO uint32_t  CIDSC      :  1;               /*!< A change in connector ID status                                       */
      __IO uint32_t  DD         :  1;               /*!< A change in connector ID status                                       */
      __IO uint32_t  SR         :  1;               /*!< Session Request/New Session Detected Interrupt                        */
      __IO uint32_t  WAKEUP     :  1;               /*!< Resume/Remote Wakeup Detected Interrupt                               */
    } GINTSTS_b;                                    /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  GINTEN;                          /*!< Interrupt enable Register                                             */

    struct {
           uint32_t             :  1;
      __IO uint32_t  MODE_MIS   :  1;               /*!< Mode Mismatch                                                         */
      __IO uint32_t  OTG_INT    :  1;               /*!< OTG                                                                   */
      __IO uint32_t  SOF        :  1;               /*!< Start of (micro)Frame                                                 */
      __IO uint32_t  RFNE       :  1;               /*!< RxFIFO Non-Empty                                                      */
      __IO uint32_t  NPTFE      :  1;               /*!< Non-periodic TxFIFO Empty                                             */
      __IO uint32_t  GIN_NAK_EFF:  1;               /*!< Global IN Non-periodic NAK Effective as a device                      */
      __IO uint32_t  GOUT_NAK_EFF:  1;              /*!< Global OUT NAK Effective as a device                                  */
           uint32_t             :  2;
      __IO uint32_t  EARLY_SUS  :  1;               /*!< an Idle state has been detected on the USB For 3 ms as a device       */
      __IO uint32_t  USB_SUS    :  1;               /*!< A suspend was detected on the USB as a device                         */
      __IO uint32_t  USB_RST    :  1;               /*!< A reset is detected on the USB as a device                            */
      __IO uint32_t  ENUM_DONE  :  1;               /*!< speed enumeration is complete as a device                             */
      __IO uint32_t  ISO_OUT_DROP:  1;              /*!< Drop an isochronous OUT packet while no space in RXFIFO as a
                                                         device                                                                */
      __IO uint32_t  EOPF       :  1;               /*!< End of Periodic Frame Interrupt as a device                           */
           uint32_t             :  1;
      __IO uint32_t  EP_MIS     :  1;               /*!< Endpoint Mismatch Interrupt as a device                               */
      __IO uint32_t  IEP_INT    :  1;               /*!< IN Endpoints Interrupt as a device                                    */
      __IO uint32_t  OEP_INT    :  1;               /*!< OUT Endpoints Interrupt as a device                                   */
      __IO uint32_t  INCOMP_ISO_IN:  1;             /*!< Incomplete Isochronous IN Transfer as a device                        */
      __IO uint32_t  IPT_IIOT   :  1;               /*!< OUT Incomplete Periodic Transfer as a host or Incomplete Isochronous
                                                         OUT Transfer as a device                                              */
      __IO uint32_t  DFS        :  1;               /*!< Data Fetch Suspended as a device                                      */
      __IO uint32_t  RST_DET    :  1;               /*!< reset detect as a device                                              */
      __IO uint32_t  HP         :  1;               /*!< a change in port status of one of the DWC_otg core ports as
                                                         a host                                                                */
      __IO uint32_t  HC         :  1;               /*!< an interrupt is pending on one of the channels of the core as
                                                         a host                                                                */
      __IO uint32_t  PTFE       :  1;               /*!< Periodic TxFIFO Empty as a host                                       */
      __IO uint32_t  LPM        :  1;               /*!< LPM Transaction Received Interrupt                                    */
      __IO uint32_t  CIDSC      :  1;               /*!< A change in connector ID status                                       */
      __IO uint32_t  DD         :  1;               /*!< A change in connector ID status                                       */
      __IO uint32_t  SR         :  1;               /*!< Session Request/New Session Detected Interrupt                        */
      __IO uint32_t  WAKEUP     :  1;               /*!< Resume/Remote Wakeup Detected Interrupt                               */
    } GINTEN_b;                                     /*!< BitSize                                                               */
  };

  union {
    __I  uint32_t  GRXSTSR;                         /*!< Returns the contents of the top of the Receive FIFO                   */

    struct {
      __I  uint32_t  CH_EP_NUM  :  4;               /*!< channel number as a host or EP number as a device                     */
      __I  uint32_t  BCNT       : 11;               /*!< byte count of the received packet                                     */
      __I  uint32_t  DPID       :  2;               /*!< Data PID of the received packet                                       */
      __I  uint32_t  PS         :  4;               /*!< the status of the received packet                                     */
      __I  uint32_t  FN         :  4;               /*!< the least significant 4 bits of the (micro)frame number in which
                                                         the packet is received on the USB                                     */
    } GRXSTSR_b;                                    /*!< BitSize                                                               */
  };

  union {
    __I  uint32_t  GRXSTSP;                         /*!< Pop the contents of the top of the Receive FIFO                       */

    struct {
      __I  uint32_t  CH_EP_NUM  :  4;               /*!< channel number as a host or EP number as a device                     */
      __I  uint32_t  BCNT       : 11;               /*!< byte count of the received packet                                     */
      __I  uint32_t  DPID       :  2;               /*!< Data PID of the received packet                                       */
      __I  uint32_t  PS         :  4;               /*!< the status of the received packet                                     */
      __I  uint32_t  FN         :  4;               /*!< the least significant 4 bits of the (micro)frame number in which
                                                         the packet is received on the USB                                     */
    } GRXSTSP_b;                                    /*!< BitSize                                                               */
  };
  __IO uint16_t  GRXFSIZ;                           /*!< This value is in terms of 32-bit words, 16 is minimize and 32768
                                                         is max                                                                */
  __I  uint16_t  RESERVED0;

  union {
    __IO uint32_t  GNPTXFSIZ;                       /*!< Non-Periodic Transmit FIFO Size Register                              */

    struct {
      __IO uint32_t  NTRSA_INEF0TRSA: 16;           /*!< start address for Non-periodic Transmit FIFO RAM as a host or
                                                         IN Endpoint FIFO0 Transmit RAM as a device                            */
      __IO uint32_t  NTD_INEF0TD: 16;               /*!< This value is in terms of 32-bit words, 16 is minimize and 32768
                                                         is max. Non-periodic TxFIFO Depth as a host or IN Endpoint TxFIFO
                                                          0 Depth as a device                                                  */
    } GNPTXFSIZ_b;                                  /*!< BitSize                                                               */
  };

  union {
    __I  uint32_t  GNPTXSTS;                        /*!< Non-Periodic Transmit FIFO/Queue Status Register                      */

    struct {
      __I  uint32_t  NTSA       : 16;               /*!< the amount of free space available in the Non-periodic TxFIFO,
                                                         max is 32768.                                                         */
      __I  uint32_t  NTRQSA     :  8;               /*!< the amount of free space available in the Non-periodic Transmit
                                                         Request Queue, max is 8.                                              */
      __I  uint32_t  TNTRQ_LAST :  1;               /*!< last Entry in the Non-periodic Tx Request Queue that is currently
                                                         being processed by the MAC                                            */
      __I  uint32_t  TNTRQ_TYPE :  2;               /*!< type in the Non-periodic Tx Request Queue that is currently
                                                         being processed by the MAC                                            */
      __I  uint32_t  TNTRQ_CH   :  4;               /*!< Channel of top of the Non-periodic Transmit Request Queue             */
    } GNPTXSTS_b;                                   /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED1[5];

  union {
    __I  uint32_t  GHWCFG1;                         /*!< User HW Config1 Register                                              */

    struct {
      __I  uint32_t  EP0_DIR    :  2;               /*!< Endpoint 0 direction, always Bidirection                              */
      __I  uint32_t  EP1_DIR    :  2;               /*!< Endpoint 1 direction                                                  */
      __I  uint32_t  EP2_DIR    :  2;               /*!< Endpoint 2 direction                                                  */
      __I  uint32_t  EP3_DIR    :  2;               /*!< Endpoint 3 direction                                                  */
      __I  uint32_t  EP4_DIR    :  2;               /*!< Endpoint 4 direction                                                  */
      __I  uint32_t  EP5_DIR    :  2;               /*!< Endpoint 5 direction                                                  */
      __I  uint32_t  EP6_DIR    :  2;               /*!< Endpoint 6 direction                                                  */
      __I  uint32_t  EP7_DIR    :  2;               /*!< Endpoint 7 direction                                                  */
      __I  uint32_t  EP8_DIR    :  2;               /*!< Endpoint 8 direction                                                  */
      __I  uint32_t  EP9_DIR    :  2;               /*!< Endpoint 9 direction                                                  */
      __I  uint32_t  EP10_DIR   :  2;               /*!< Endpoint 10 direction                                                 */
      __I  uint32_t  EP11_DIR   :  2;               /*!< Endpoint 11 direction                                                 */
      __I  uint32_t  EP12_DIR   :  2;               /*!< Endpoint 12 direction                                                 */
      __I  uint32_t  EP13_DIR   :  2;               /*!< Endpoint 13 direction                                                 */
      __I  uint32_t  EP14_DIR   :  2;               /*!< Endpoint 14 direction                                                 */
      __I  uint32_t  EP15_DIR   :  2;               /*!< Endpoint 15 direction                                                 */
    } GHWCFG1_b;                                    /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED2[3];

  union {
    __IO uint32_t  GLPMCFG;                         /*!< Core LPM Configuration Register                                       */

    struct {
      __IO uint32_t  EP0_DIR    :  1;               /*!< LPM capability is enabled                                             */
    } GLPMCFG_b;                                    /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  GPWRDN;                          /*!< Global Power Down Register                                            */

    struct {
           uint32_t             :  1;
      __IO uint32_t  PMU_ACTIVE :  1;               /*!< PMU Active is enabled                                                 */
           uint32_t             :  1;
      __IO uint32_t  PDC        :  1;               /*!< Power Down Clamp is enabled                                           */
      __IO uint32_t  PDR        :  1;               /*!< If clear, Reset DWC_otg                                               */
      __IO uint32_t  PDS        :  1;               /*!< If 0, DWC_otg is in ON state, or OFF state                            */
      __IO uint32_t  DIS_VBUS   :  1;               /*!< Disable VBUS                                                          */
           uint32_t             :  8;
      __IO uint32_t  SRP_DETECT_INT:  1;            /*!< SRP has been detected by the PMU as a host                            */
      __IO uint32_t  SRP_DETECT_INT_EN:  1;         /*!< Enable For SRPDetect Interrupt as a host                              */
      __IO uint32_t  STATE_CHN_INT:  1;             /*!< a status change in either the IDDIG or BSessVld signal                */
      __IO uint32_t  STATE_CHN_INT_EN:  1;          /*!< Enable For Status Change Interrupt                                    */
      __I  uint32_t  LINE_STATE :  2;               /*!< the current linestate on USB as seen by the PMU module                */
      __I  uint32_t  IDDIG      :  1;               /*!< the status of the IDDIG signal. If 0, host mode. if 1, device
                                                         mode                                                                  */
      __I  uint32_t  B_SESS_VLD :  1;               /*!< B session valid status signal from the PHY                            */
      __IO uint32_t  ADP_INT    :  1;               /*!< set whenever there is a ADP event                                     */
    } GPWRDN_b;                                     /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  GDFIFOCFG;                       /*!< Global DFIFO Software Config Register                                 */

    struct {
      __IO uint32_t  GDFIFOCFG  : 16;               /*!< This field is for dynamic programming of the DFIFO Size.              */
      __IO uint32_t  EPIBA      : 16;               /*!< This field provides the start address of the EP info controller       */
    } GDFIFOCFG_b;                                  /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED3[40];

  union {
    __IO uint32_t  HPTXFSIZ;                        /*!< Host Periodic Transmit FIFO Size Register                             */

    struct {
      __IO uint32_t  HPTSA      : 16;               /*!< start address of the Periodic TxFIFO                                  */
      __IO uint32_t  EPIBA      : 16;               /*!< the size of the Periodic TxFIFO                                       */
    } HPTXFSIZ_b;                                   /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  DIEPTXF1;                        /*!< Device In Endpoint Transmit FIFO Size Register                        */

    struct {
      __IO uint32_t  INEFTRSA   : 16;               /*!< IN Endpoint FIFOn Transmit RAM Start Address                          */
      __IO uint32_t  INETFD     : 16;               /*!< IN Endpoint TxFIFO Depth                                              */
    } DIEPTXF1_b;                                   /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  DIEPTXF2;                        /*!< Device In Endpoint Transmit FIFO Size Register                        */

    struct {
      __IO uint32_t  INEFTRSA   : 16;               /*!< IN Endpoint FIFOn Transmit RAM Start Address                          */
      __IO uint32_t  INETFD     : 16;               /*!< IN Endpoint TxFIFO Depth                                              */
    } DIEPTXF2_b;                                   /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  DIEPTXF3;                        /*!< Device In Endpoint Transmit FIFO Size Register                        */

    struct {
      __IO uint32_t  INEFTRSA   : 16;               /*!< IN Endpoint FIFOn Transmit RAM Start Address                          */
      __IO uint32_t  INETFD     : 16;               /*!< IN Endpoint TxFIFO Depth                                              */
    } DIEPTXF3_b;                                   /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  DIEPTXF4;                        /*!< Device In Endpoint Transmit FIFO Size Register                        */

    struct {
      __IO uint32_t  INEFTRSA   : 16;               /*!< IN Endpoint FIFOn Transmit RAM Start Address                          */
      __IO uint32_t  INETFD     : 16;               /*!< IN Endpoint TxFIFO Depth                                              */
    } DIEPTXF4_b;                                   /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  DIEPTXF5;                        /*!< Device In Endpoint Transmit FIFO Size Register                        */

    struct {
      __IO uint32_t  INEFTRSA   : 16;               /*!< IN Endpoint FIFOn Transmit RAM Start Address                          */
      __IO uint32_t  INETFD     : 16;               /*!< IN Endpoint TxFIFO Depth                                              */
    } DIEPTXF5_b;                                   /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  DIEPTXF6;                        /*!< Device In Endpoint Transmit FIFO Size Register                        */

    struct {
      __IO uint32_t  INEFTRSA   : 16;               /*!< IN Endpoint FIFOn Transmit RAM Start Address                          */
      __IO uint32_t  INETFD     : 16;               /*!< IN Endpoint TxFIFO Depth                                              */
    } DIEPTXF6_b;                                   /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  DIEPTXF7;                        /*!< Device In Endpoint Transmit FIFO Size Register                        */

    struct {
      __IO uint32_t  INEFTRSA   : 16;               /*!< IN Endpoint FIFOn Transmit RAM Start Address                          */
      __IO uint32_t  INETFD     : 16;               /*!< IN Endpoint TxFIFO Depth                                              */
    } DIEPTXF7_b;                                   /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  DIEPTXF8;                        /*!< Device In Endpoint Transmit FIFO Size Register                        */

    struct {
      __IO uint32_t  INEFTRSA   : 16;               /*!< IN Endpoint FIFOn Transmit RAM Start Address                          */
      __IO uint32_t  INETFD     : 16;               /*!< IN Endpoint TxFIFO Depth                                              */
    } DIEPTXF8_b;                                   /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  DIEPTXF9;                        /*!< Device In Endpoint Transmit FIFO Size Register                        */

    struct {
      __IO uint32_t  INEFTRSA   : 16;               /*!< IN Endpoint FIFOn Transmit RAM Start Address                          */
      __IO uint32_t  INETFD     : 16;               /*!< IN Endpoint TxFIFO Depth                                              */
    } DIEPTXF9_b;                                   /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  DIEPTXF10;                       /*!< Device In Endpoint Transmit FIFO Size Register                        */

    struct {
      __IO uint32_t  INEFTRSA   : 16;               /*!< IN Endpoint FIFOn Transmit RAM Start Address                          */
      __IO uint32_t  INETFD     : 16;               /*!< IN Endpoint TxFIFO Depth                                              */
    } DIEPTXF10_b;                                  /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  DIEPTXF11;                       /*!< Device In Endpoint Transmit FIFO Size Register                        */

    struct {
      __IO uint32_t  INEFTRSA   : 16;               /*!< IN Endpoint FIFOn Transmit RAM Start Address                          */
      __IO uint32_t  INETFD     : 16;               /*!< IN Endpoint TxFIFO Depth                                              */
    } DIEPTXF11_b;                                  /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  DIEPTXF12;                       /*!< Device In Endpoint Transmit FIFO Size Register                        */

    struct {
      __IO uint32_t  INEFTRSA   : 16;               /*!< IN Endpoint FIFOn Transmit RAM Start Address                          */
      __IO uint32_t  INETFD     : 16;               /*!< IN Endpoint TxFIFO Depth                                              */
    } DIEPTXF12_b;                                  /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  DIEPTXF13;                       /*!< Device In Endpoint Transmit FIFO Size Register                        */

    struct {
      __IO uint32_t  INEFTRSA   : 16;               /*!< IN Endpoint FIFOn Transmit RAM Start Address                          */
      __IO uint32_t  INETFD     : 16;               /*!< IN Endpoint TxFIFO Depth                                              */
    } DIEPTXF13_b;                                  /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  DIEPTXF14;                       /*!< Device In Endpoint Transmit FIFO Size Register                        */

    struct {
      __IO uint32_t  INEFTRSA   : 16;               /*!< IN Endpoint FIFOn Transmit RAM Start Address                          */
      __IO uint32_t  INETFD     : 16;               /*!< IN Endpoint TxFIFO Depth                                              */
    } DIEPTXF14_b;                                  /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  DIEPTXF15;                       /*!< Device In Endpoint Transmit FIFO Size Register                        */

    struct {
      __IO uint32_t  INEFTRSA   : 16;               /*!< IN Endpoint FIFOn Transmit RAM Start Address                          */
      __IO uint32_t  INETFD     : 16;               /*!< IN Endpoint TxFIFO Depth                                              */
    } DIEPTXF15_b;                                  /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED4[176];

  union {
    __IO uint32_t  HCFG;                            /*!< Host Configuration Register                                           */

    struct {
      __IO uint32_t  FS_LS_PCS  :  2;               /*!< FS/LS PHY Clock Select as a host                                      */
      __IO uint32_t  FS_LS_SUPPORT:  1;             /*!< If set, FS/LS-only, even If the connected device can support
                                                         HS                                                                    */
           uint32_t             :  4;
      __IO uint32_t  EN_32K_SUS :  1;               /*!< Enable 32 KHz Suspend mode                                            */
      __IO uint32_t  RVP        :  8;               /*!< ResValid number of clock cycles to detect a valid resume              */
           uint32_t             :  7;
      __IO uint32_t  EN_SG_DMA  :  1;               /*!< Enable Scatter/gather DMA in Host mode                                */
      __IO uint32_t  FLE        :  2;               /*!< the number of entries in the Frame list. 8 times of FLE               */
      __IO uint32_t  EPS        :  1;               /*!< Enables periodic scheduling                                           */
           uint32_t             :  4;
      __IO uint32_t  MCRTE      :  1;               /*!< enable/disable the Host core to wait 200 PHY clock cycles at
                                                         the end of Resume to change the opmode signal to the PHY to
                                                          00 after Suspend or LPM.                                             */
    } HCFG_b;                                       /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  HFIR;                            /*!< Host Frame Interval Register                                          */

    struct {
      __IO uint32_t  FI         : 16;               /*!< IN Endpoint FIFOn Transmit RAM Start Address                          */
      __IO uint32_t  RC         :  1;               /*!< The HFIR can be dynamically reloaded during runtime if set            */
    } HFIR_b;                                       /*!< BitSize                                                               */
  };

  union {
    __I  uint32_t  HFNUM;                           /*!< Host Frame Number/Frame Time Remaining Register                       */

    struct {
      __I  uint32_t  FN         : 16;               /*!< This field increments when a new SOF is transmitted on the USB        */
      __I  uint32_t  FTR        : 16;               /*!< amount of time remaining in the current microframe (HS) or Frame
                                                         (FS/LS), in terms of PHY clocks                                       */
    } HFNUM_b;                                      /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED5;

  union {
    __I  uint32_t  HPTXSTS;                         /*!< Host Periodic Transmit FIFO/Queue Status Register                     */

    struct {
      __I  uint32_t  PTDFSA     : 16;               /*!< Indicates the number of free locations available to be written
                                                         to in the Periodic TxFIFO, max is 32768                               */
      __I  uint32_t  PTRQSA     :  8;               /*!< Indicates the number of free locations available to be written
                                                         in the Periodic Transmit Request Queue, max is 16                     */
      __I  uint32_t  TPTRQ_LAST :  1;               /*!< last Entry in the periodic Tx Request Queue that is currently
                                                         being processed by the MAC                                            */
      __I  uint32_t  TPTRQ_TYPE :  2;               /*!< type in the periodic Tx Request Queue that is currently being
                                                         processed by the MAC                                                  */
      __I  uint32_t  TPTRQ_CH   :  4;               /*!< Channel of top of the periodic Transmit Request Queue                 */
      __I  uint32_t  TPTRQ_ODD_FRAME:  1;           /*!< If set, send in odd (micro)Frame                                      */
    } HPTXSTS_b;                                    /*!< BitSize                                                               */
  };

  union {
    __I  uint32_t  HAINT;                           /*!< Host All Channels Interrupt Register                                  */

    struct {
      __I  uint32_t  INT        : 16;               /*!< Channel Interrupts, from 0 to 15.                                     */
    } HAINT_b;                                      /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  HAINT_EN;                        /*!< Host All Channels Interrupt Enable Register                           */

    struct {
      __IO uint32_t  EN         : 16;               /*!< Channel Interrupts Enable, from 0 to 15.                              */
    } HAINT_EN_b;                                   /*!< BitSize                                                               */
  };
  __IO uint32_t  HFLBA;                             /*!< The starting address of the Frame list                                */
  __I  uint32_t  RESERVED6[8];

  union {
    __IO uint32_t  __HPRT;                          /*!< Host Port Control and Status Register                                 */

    struct {
      __I  uint32_t  PCS        :  1;               /*!< If a device is attached to the port                                   */
      __IO uint32_t  PCD        :  1;               /*!< A device connection is detected                                       */
      __IO uint32_t  PE         :  1;               /*!< Port Enable                                                           */
      __IO uint32_t  PEDC       :  1;               /*!< Set if when the status of the Port Enable (bit 2) of this register
                                                         changes                                                               */
      __I  uint32_t  POA        :  1;               /*!< Indicates the overcurrent condition of the port                       */
      __IO uint32_t  POC        :  1;               /*!< Set if when the status of the Port Overcurrent Active bit (bit
                                                         4) in this register changes                                           */
      __IO uint32_t  PR         :  1;               /*!< Application and Core all can perform resume by setting, then
                                                         clear it whatever resume is success or not                            */
      __IO uint32_t  PS         :  1;               /*!< Sets this bit to put this port in Suspend mode                        */
      __IO uint32_t  PRESET     :  1;               /*!< sets this bit, a reset sequence is started on this port               */
           uint32_t             :  1;
      __IO uint32_t  PLSDP      :  1;               /*!< Logic level of D+                                                     */
      __IO uint32_t  PLSDN      :  1;               /*!< Logic level of D-                                                     */
      __IO uint32_t  PP         :  1;               /*!< this field to control power to this port. 1, power on                 */
      __IO uint32_t  PTC        :  4;               /*!< The application writes a nonzero value to this field to put
                                                         the port into a Test mode                                             */
      __I  uint32_t  SPEED      :  2;               /*!< Indicates the speed of the device attached to this port               */
    } __HPRT_b;                                     /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED7[47];

  union {
    __IO uint32_t  HCC0;                            /*!< Host Channel Characteristics Register                                 */

    struct {
      __IO uint32_t  MPS        : 11;               /*!< Indicates the maximum packet size of the associated endpoint          */
      __IO uint32_t  EP_NUM     :  4;               /*!< Indicates the endpoint number on the device serving as the data
                                                         source or sink.                                                       */
      __IO uint32_t  EP_DIR     :  1;               /*!< Indicates whether the transaction is IN or OUT. 0, OUT. 1, IN         */
           uint32_t             :  1;
      __IO uint32_t  LSD        :  1;               /*!< indicate that this channel is communicating to a low-speed device.    */
      __IO uint32_t  EP_TYPE    :  2;               /*!< Indicates the transfer type selected.                                 */
      __IO uint32_t  EC         :  2;               /*!< Multi Count (MC) / Error Count (EC).                                  */
      __IO uint32_t  DA         :  7;               /*!< This field selects the specific device serving as the data source
                                                         or sink.                                                              */
      __IO uint32_t  OF         :  1;               /*!< The frame is odd or even.                                             */
      __IO uint32_t  CD         :  1;               /*!< sets this bit to stop transmitting/receiving data on a channel.       */
      __IO uint32_t  CE         :  1;               /*!< If the descriptor structure and data buffer are ready or not
                                                         yet.                                                                  */
    } HCC0_b;                                       /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED8;

  union {
    __IO uint32_t  HCINT0;                          /*!< Host Channel Interrupt Register                                       */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  CH_HALT    :  1;               /*!< Indicates the endpoint number on the device serving as the data
                                                         source or sink.                                                       */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
           uint32_t             :  8;
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
      __IO uint32_t  ETE        :  1;               /*!< 3 consecutive transaction errors occurred on the USB bus              */
      __IO uint32_t  DR         :  1;               /*!< the corresponding channel's descriptor list rolls over                */
    } HCINT0_b;                                     /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  HCINT_EN0;                       /*!< Host Channel Interrupt Enable Register                                */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  CH_HALT    :  1;               /*!< Indicates the endpoint number on the device serving as the data
                                                         source or sink.                                                       */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
           uint32_t             :  8;
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
      __IO uint32_t  ETE        :  1;               /*!< 3 consecutive transaction errors occurred on the USB bus              */
      __IO uint32_t  DR         :  1;               /*!< the corresponding channel's descriptor list rolls over                */
    } HCINT_EN0_b;                                  /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  HCTSIZ0;                         /*!< Host Channel Transfer Size Register                                   */

    struct {
      __IO uint32_t  SCHED_INFO :  8;               /*!< Every bit in this 8 bit register indicates scheduling for that
                                                         microframe.Bit N indicates scheduling for Nth microframe scheduling
                                                          for 8th microframe in that frame.                                    */
      __IO uint32_t  NTD        :  8;               /*!< Number of Transfer Descriptors.                                       */
           uint32_t             : 13;
      __IO uint32_t  PID        :  2;               /*!< the type of PID to use for the initial transaction                    */
      __IO uint32_t  PING       :  1;               /*!< Setting this field to 1 directs the host to do PING protocol          */
    } HCTSIZ0_b;                                    /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  HCDMA0;                          /*!< Host Channel-n DMA Address Register                                   */

    struct {
           uint32_t             :  3;
      __IO uint32_t  CTD        :  6;               /*!< Number of Transfer Descriptors for Non-Isochronous                    */
      __IO uint32_t  ADDR       : 23;               /*!< he start address of 512 bytes page for Non-Isochronous                */
    } HCDMA0_b;                                     /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED9;
  __IO uint32_t  HCDMAB0;                           /*!< Host Channel-n DMA Buffer Address Register                            */

  union {
    __IO uint32_t  HCC1;                            /*!< Host Channel Characteristics Register                                 */

    struct {
      __IO uint32_t  MPS        : 11;               /*!< Indicates the maximum packet size of the associated endpoint          */
      __IO uint32_t  EP_NUM     :  4;               /*!< Indicates the endpoint number on the device serving as the data
                                                         source or sink.                                                       */
      __IO uint32_t  EP_DIR     :  1;               /*!< Indicates whether the transaction is IN or OUT. 0, OUT. 1, IN         */
           uint32_t             :  1;
      __IO uint32_t  LSD        :  1;               /*!< indicate that this channel is communicating to a low-speed device.    */
      __IO uint32_t  EP_TYPE    :  2;               /*!< Indicates the transfer type selected.                                 */
      __IO uint32_t  EC         :  2;               /*!< Multi Count (MC) / Error Count (EC).                                  */
      __IO uint32_t  DA         :  7;               /*!< This field selects the specific device serving as the data source
                                                         or sink.                                                              */
      __IO uint32_t  OF         :  1;               /*!< The frame is odd or even.                                             */
      __IO uint32_t  CD         :  1;               /*!< sets this bit to stop transmitting/receiving data on a channel.       */
      __IO uint32_t  CE         :  1;               /*!< If the descriptor structure and data buffer are ready or not
                                                         yet.                                                                  */
    } HCC1_b;                                       /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED10;

  union {
    __IO uint32_t  HCINT1;                          /*!< Host Channel Interrupt Register                                       */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  CH_HALT    :  1;               /*!< Indicates the endpoint number on the device serving as the data
                                                         source or sink.                                                       */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
           uint32_t             :  8;
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
      __IO uint32_t  ETE        :  1;               /*!< 3 consecutive transaction errors occurred on the USB bus              */
      __IO uint32_t  DR         :  1;               /*!< the corresponding channel's descriptor list rolls over                */
    } HCINT1_b;                                     /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  HCINT_EN1;                       /*!< Host Channel Interrupt Enable Register                                */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  CH_HALT    :  1;               /*!< Indicates the endpoint number on the device serving as the data
                                                         source or sink.                                                       */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
           uint32_t             :  8;
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
      __IO uint32_t  ETE        :  1;               /*!< 3 consecutive transaction errors occurred on the USB bus              */
      __IO uint32_t  DR         :  1;               /*!< the corresponding channel's descriptor list rolls over                */
    } HCINT_EN1_b;                                  /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  HCTSIZ1;                         /*!< Host Channel Transfer Size Register                                   */

    struct {
      __IO uint32_t  SCHED_INFO :  8;               /*!< Every bit in this 8 bit register indicates scheduling for that
                                                         microframe.Bit N indicates scheduling for Nth microframe scheduling
                                                          for 8th microframe in that frame.                                    */
      __IO uint32_t  NTD        :  8;               /*!< Number of Transfer Descriptors.                                       */
           uint32_t             : 13;
      __IO uint32_t  PID        :  2;               /*!< the type of PID to use for the initial transaction                    */
      __IO uint32_t  PING       :  1;               /*!< Setting this field to 1 directs the host to do PING protocol          */
    } HCTSIZ1_b;                                    /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  HCDMA1;                          /*!< Host Channel-n DMA Address Register                                   */

    struct {
           uint32_t             :  3;
      __IO uint32_t  CTD        :  6;               /*!< Number of Transfer Descriptors for Non-Isochronous                    */
      __IO uint32_t  ADDR       : 23;               /*!< he start address of 512 bytes page for Non-Isochronous                */
    } HCDMA1_b;                                     /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED11;
  __IO uint32_t  HCDMAB1;                           /*!< Host Channel-n DMA Buffer Address Register                            */

  union {
    __IO uint32_t  HCC2;                            /*!< Host Channel Characteristics Register                                 */

    struct {
      __IO uint32_t  MPS        : 11;               /*!< Indicates the maximum packet size of the associated endpoint          */
      __IO uint32_t  EP_NUM     :  4;               /*!< Indicates the endpoint number on the device serving as the data
                                                         source or sink.                                                       */
      __IO uint32_t  EP_DIR     :  1;               /*!< Indicates whether the transaction is IN or OUT. 0, OUT. 1, IN         */
           uint32_t             :  1;
      __IO uint32_t  LSD        :  1;               /*!< indicate that this channel is communicating to a low-speed device.    */
      __IO uint32_t  EP_TYPE    :  2;               /*!< Indicates the transfer type selected.                                 */
      __IO uint32_t  EC         :  2;               /*!< Multi Count (MC) / Error Count (EC).                                  */
      __IO uint32_t  DA         :  7;               /*!< This field selects the specific device serving as the data source
                                                         or sink.                                                              */
      __IO uint32_t  OF         :  1;               /*!< The frame is odd or even.                                             */
      __IO uint32_t  CD         :  1;               /*!< sets this bit to stop transmitting/receiving data on a channel.       */
      __IO uint32_t  CE         :  1;               /*!< If the descriptor structure and data buffer are ready or not
                                                         yet.                                                                  */
    } HCC2_b;                                       /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED12;

  union {
    __IO uint32_t  HCINT2;                          /*!< Host Channel Interrupt Register                                       */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  CH_HALT    :  1;               /*!< Indicates the endpoint number on the device serving as the data
                                                         source or sink.                                                       */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
           uint32_t             :  8;
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
      __IO uint32_t  ETE        :  1;               /*!< 3 consecutive transaction errors occurred on the USB bus              */
      __IO uint32_t  DR         :  1;               /*!< the corresponding channel's descriptor list rolls over                */
    } HCINT2_b;                                     /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  HCINT_EN2;                       /*!< Host Channel Interrupt Enable Register                                */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  CH_HALT    :  1;               /*!< Indicates the endpoint number on the device serving as the data
                                                         source or sink.                                                       */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
           uint32_t             :  8;
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
      __IO uint32_t  ETE        :  1;               /*!< 3 consecutive transaction errors occurred on the USB bus              */
      __IO uint32_t  DR         :  1;               /*!< the corresponding channel's descriptor list rolls over                */
    } HCINT_EN2_b;                                  /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  HCTSIZ2;                         /*!< Host Channel Transfer Size Register                                   */

    struct {
      __IO uint32_t  SCHED_INFO :  8;               /*!< Every bit in this 8 bit register indicates scheduling for that
                                                         microframe.Bit N indicates scheduling for Nth microframe scheduling
                                                          for 8th microframe in that frame.                                    */
      __IO uint32_t  NTD        :  8;               /*!< Number of Transfer Descriptors.                                       */
           uint32_t             : 13;
      __IO uint32_t  PID        :  2;               /*!< the type of PID to use for the initial transaction                    */
      __IO uint32_t  PING       :  1;               /*!< Setting this field to 1 directs the host to do PING protocol          */
    } HCTSIZ2_b;                                    /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  HCDMA2;                          /*!< Host Channel-n DMA Address Register                                   */

    struct {
           uint32_t             :  3;
      __IO uint32_t  CTD        :  6;               /*!< Number of Transfer Descriptors for Non-Isochronous                    */
      __IO uint32_t  ADDR       : 23;               /*!< he start address of 512 bytes page for Non-Isochronous                */
    } HCDMA2_b;                                     /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED13;
  __IO uint32_t  HCDMAB2;                           /*!< Host Channel-n DMA Buffer Address Register                            */

  union {
    __IO uint32_t  HCC3;                            /*!< Host Channel Characteristics Register                                 */

    struct {
      __IO uint32_t  MPS        : 11;               /*!< Indicates the maximum packet size of the associated endpoint          */
      __IO uint32_t  EP_NUM     :  4;               /*!< Indicates the endpoint number on the device serving as the data
                                                         source or sink.                                                       */
      __IO uint32_t  EP_DIR     :  1;               /*!< Indicates whether the transaction is IN or OUT. 0, OUT. 1, IN         */
           uint32_t             :  1;
      __IO uint32_t  LSD        :  1;               /*!< indicate that this channel is communicating to a low-speed device.    */
      __IO uint32_t  EP_TYPE    :  2;               /*!< Indicates the transfer type selected.                                 */
      __IO uint32_t  EC         :  2;               /*!< Multi Count (MC) / Error Count (EC).                                  */
      __IO uint32_t  DA         :  7;               /*!< This field selects the specific device serving as the data source
                                                         or sink.                                                              */
      __IO uint32_t  OF         :  1;               /*!< The frame is odd or even.                                             */
      __IO uint32_t  CD         :  1;               /*!< sets this bit to stop transmitting/receiving data on a channel.       */
      __IO uint32_t  CE         :  1;               /*!< If the descriptor structure and data buffer are ready or not
                                                         yet.                                                                  */
    } HCC3_b;                                       /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED14;

  union {
    __IO uint32_t  HCINT3;                          /*!< Host Channel Interrupt Register                                       */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  CH_HALT    :  1;               /*!< Indicates the endpoint number on the device serving as the data
                                                         source or sink.                                                       */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
           uint32_t             :  8;
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
      __IO uint32_t  ETE        :  1;               /*!< 3 consecutive transaction errors occurred on the USB bus              */
      __IO uint32_t  DR         :  1;               /*!< the corresponding channel's descriptor list rolls over                */
    } HCINT3_b;                                     /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  HCINT_EN3;                       /*!< Host Channel Interrupt Enable Register                                */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  CH_HALT    :  1;               /*!< Indicates the endpoint number on the device serving as the data
                                                         source or sink.                                                       */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
           uint32_t             :  8;
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
      __IO uint32_t  ETE        :  1;               /*!< 3 consecutive transaction errors occurred on the USB bus              */
      __IO uint32_t  DR         :  1;               /*!< the corresponding channel's descriptor list rolls over                */
    } HCINT_EN3_b;                                  /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  HCTSIZ3;                         /*!< Host Channel Transfer Size Register                                   */

    struct {
      __IO uint32_t  SCHED_INFO :  8;               /*!< Every bit in this 8 bit register indicates scheduling for that
                                                         microframe.Bit N indicates scheduling for Nth microframe scheduling
                                                          for 8th microframe in that frame.                                    */
      __IO uint32_t  NTD        :  8;               /*!< Number of Transfer Descriptors.                                       */
           uint32_t             : 13;
      __IO uint32_t  PID        :  2;               /*!< the type of PID to use for the initial transaction                    */
      __IO uint32_t  PING       :  1;               /*!< Setting this field to 1 directs the host to do PING protocol          */
    } HCTSIZ3_b;                                    /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  HCDMA3;                          /*!< Host Channel-n DMA Address Register                                   */

    struct {
           uint32_t             :  3;
      __IO uint32_t  CTD        :  6;               /*!< Number of Transfer Descriptors for Non-Isochronous                    */
      __IO uint32_t  ADDR       : 23;               /*!< he start address of 512 bytes page for Non-Isochronous                */
    } HCDMA3_b;                                     /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED15;
  __IO uint32_t  HCDMAB3;                           /*!< Host Channel-n DMA Buffer Address Register                            */

  union {
    __IO uint32_t  HCC4;                            /*!< Host Channel Characteristics Register                                 */

    struct {
      __IO uint32_t  MPS        : 11;               /*!< Indicates the maximum packet size of the associated endpoint          */
      __IO uint32_t  EP_NUM     :  4;               /*!< Indicates the endpoint number on the device serving as the data
                                                         source or sink.                                                       */
      __IO uint32_t  EP_DIR     :  1;               /*!< Indicates whether the transaction is IN or OUT. 0, OUT. 1, IN         */
           uint32_t             :  1;
      __IO uint32_t  LSD        :  1;               /*!< indicate that this channel is communicating to a low-speed device.    */
      __IO uint32_t  EP_TYPE    :  2;               /*!< Indicates the transfer type selected.                                 */
      __IO uint32_t  EC         :  2;               /*!< Multi Count (MC) / Error Count (EC).                                  */
      __IO uint32_t  DA         :  7;               /*!< This field selects the specific device serving as the data source
                                                         or sink.                                                              */
      __IO uint32_t  OF         :  1;               /*!< The frame is odd or even.                                             */
      __IO uint32_t  CD         :  1;               /*!< sets this bit to stop transmitting/receiving data on a channel.       */
      __IO uint32_t  CE         :  1;               /*!< If the descriptor structure and data buffer are ready or not
                                                         yet.                                                                  */
    } HCC4_b;                                       /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED16;

  union {
    __IO uint32_t  HCINT4;                          /*!< Host Channel Interrupt Register                                       */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  CH_HALT    :  1;               /*!< Indicates the endpoint number on the device serving as the data
                                                         source or sink.                                                       */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
           uint32_t             :  8;
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
      __IO uint32_t  ETE        :  1;               /*!< 3 consecutive transaction errors occurred on the USB bus              */
      __IO uint32_t  DR         :  1;               /*!< the corresponding channel's descriptor list rolls over                */
    } HCINT4_b;                                     /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  HCINT_EN4;                       /*!< Host Channel Interrupt Enable Register                                */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  CH_HALT    :  1;               /*!< Indicates the endpoint number on the device serving as the data
                                                         source or sink.                                                       */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
           uint32_t             :  8;
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
      __IO uint32_t  ETE        :  1;               /*!< 3 consecutive transaction errors occurred on the USB bus              */
      __IO uint32_t  DR         :  1;               /*!< the corresponding channel's descriptor list rolls over                */
    } HCINT_EN4_b;                                  /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  HCTSIZ4;                         /*!< Host Channel Transfer Size Register                                   */

    struct {
      __IO uint32_t  SCHED_INFO :  8;               /*!< Every bit in this 8 bit register indicates scheduling for that
                                                         microframe.Bit N indicates scheduling for Nth microframe scheduling
                                                          for 8th microframe in that frame.                                    */
      __IO uint32_t  NTD        :  8;               /*!< Number of Transfer Descriptors.                                       */
           uint32_t             : 13;
      __IO uint32_t  PID        :  2;               /*!< the type of PID to use for the initial transaction                    */
      __IO uint32_t  PING       :  1;               /*!< Setting this field to 1 directs the host to do PING protocol          */
    } HCTSIZ4_b;                                    /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  HCDMA4;                          /*!< Host Channel-n DMA Address Register                                   */

    struct {
           uint32_t             :  3;
      __IO uint32_t  CTD        :  6;               /*!< Number of Transfer Descriptors for Non-Isochronous                    */
      __IO uint32_t  ADDR       : 23;               /*!< he start address of 512 bytes page for Non-Isochronous                */
    } HCDMA4_b;                                     /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED17;
  __IO uint32_t  HCDMAB4;                           /*!< Host Channel-n DMA Buffer Address Register                            */

  union {
    __IO uint32_t  HCC5;                            /*!< Host Channel Characteristics Register                                 */

    struct {
      __IO uint32_t  MPS        : 11;               /*!< Indicates the maximum packet size of the associated endpoint          */
      __IO uint32_t  EP_NUM     :  4;               /*!< Indicates the endpoint number on the device serving as the data
                                                         source or sink.                                                       */
      __IO uint32_t  EP_DIR     :  1;               /*!< Indicates whether the transaction is IN or OUT. 0, OUT. 1, IN         */
           uint32_t             :  1;
      __IO uint32_t  LSD        :  1;               /*!< indicate that this channel is communicating to a low-speed device.    */
      __IO uint32_t  EP_TYPE    :  2;               /*!< Indicates the transfer type selected.                                 */
      __IO uint32_t  EC         :  2;               /*!< Multi Count (MC) / Error Count (EC).                                  */
      __IO uint32_t  DA         :  7;               /*!< This field selects the specific device serving as the data source
                                                         or sink.                                                              */
      __IO uint32_t  OF         :  1;               /*!< The frame is odd or even.                                             */
      __IO uint32_t  CD         :  1;               /*!< sets this bit to stop transmitting/receiving data on a channel.       */
      __IO uint32_t  CE         :  1;               /*!< If the descriptor structure and data buffer are ready or not
                                                         yet.                                                                  */
    } HCC5_b;                                       /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED18;

  union {
    __IO uint32_t  HCINT5;                          /*!< Host Channel Interrupt Register                                       */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  CH_HALT    :  1;               /*!< Indicates the endpoint number on the device serving as the data
                                                         source or sink.                                                       */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
           uint32_t             :  8;
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
      __IO uint32_t  ETE        :  1;               /*!< 3 consecutive transaction errors occurred on the USB bus              */
      __IO uint32_t  DR         :  1;               /*!< the corresponding channel's descriptor list rolls over                */
    } HCINT5_b;                                     /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  HCINT_EN5;                       /*!< Host Channel Interrupt Enable Register                                */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  CH_HALT    :  1;               /*!< Indicates the endpoint number on the device serving as the data
                                                         source or sink.                                                       */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
           uint32_t             :  8;
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
      __IO uint32_t  ETE        :  1;               /*!< 3 consecutive transaction errors occurred on the USB bus              */
      __IO uint32_t  DR         :  1;               /*!< the corresponding channel's descriptor list rolls over                */
    } HCINT_EN5_b;                                  /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  HCTSIZ5;                         /*!< Host Channel Transfer Size Register                                   */

    struct {
      __IO uint32_t  SCHED_INFO :  8;               /*!< Every bit in this 8 bit register indicates scheduling for that
                                                         microframe.Bit N indicates scheduling for Nth microframe scheduling
                                                          for 8th microframe in that frame.                                    */
      __IO uint32_t  NTD        :  8;               /*!< Number of Transfer Descriptors.                                       */
           uint32_t             : 13;
      __IO uint32_t  PID        :  2;               /*!< the type of PID to use for the initial transaction                    */
      __IO uint32_t  PING       :  1;               /*!< Setting this field to 1 directs the host to do PING protocol          */
    } HCTSIZ5_b;                                    /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  HCDMA5;                          /*!< Host Channel-n DMA Address Register                                   */

    struct {
           uint32_t             :  3;
      __IO uint32_t  CTD        :  6;               /*!< Number of Transfer Descriptors for Non-Isochronous                    */
      __IO uint32_t  ADDR       : 23;               /*!< he start address of 512 bytes page for Non-Isochronous                */
    } HCDMA5_b;                                     /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED19;
  __IO uint32_t  HCDMAB5;                           /*!< Host Channel-n DMA Buffer Address Register                            */

  union {
    __IO uint32_t  HCC6;                            /*!< Host Channel Characteristics Register                                 */

    struct {
      __IO uint32_t  MPS        : 11;               /*!< Indicates the maximum packet size of the associated endpoint          */
      __IO uint32_t  EP_NUM     :  4;               /*!< Indicates the endpoint number on the device serving as the data
                                                         source or sink.                                                       */
      __IO uint32_t  EP_DIR     :  1;               /*!< Indicates whether the transaction is IN or OUT. 0, OUT. 1, IN         */
           uint32_t             :  1;
      __IO uint32_t  LSD        :  1;               /*!< indicate that this channel is communicating to a low-speed device.    */
      __IO uint32_t  EP_TYPE    :  2;               /*!< Indicates the transfer type selected.                                 */
      __IO uint32_t  EC         :  2;               /*!< Multi Count (MC) / Error Count (EC).                                  */
      __IO uint32_t  DA         :  7;               /*!< This field selects the specific device serving as the data source
                                                         or sink.                                                              */
      __IO uint32_t  OF         :  1;               /*!< The frame is odd or even.                                             */
      __IO uint32_t  CD         :  1;               /*!< sets this bit to stop transmitting/receiving data on a channel.       */
      __IO uint32_t  CE         :  1;               /*!< If the descriptor structure and data buffer are ready or not
                                                         yet.                                                                  */
    } HCC6_b;                                       /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED20;

  union {
    __IO uint32_t  HCINT6;                          /*!< Host Channel Interrupt Register                                       */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  CH_HALT    :  1;               /*!< Indicates the endpoint number on the device serving as the data
                                                         source or sink.                                                       */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
           uint32_t             :  8;
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
      __IO uint32_t  ETE        :  1;               /*!< 3 consecutive transaction errors occurred on the USB bus              */
      __IO uint32_t  DR         :  1;               /*!< the corresponding channel's descriptor list rolls over                */
    } HCINT6_b;                                     /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  HCINT_EN6;                       /*!< Host Channel Interrupt Enable Register                                */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  CH_HALT    :  1;               /*!< Indicates the endpoint number on the device serving as the data
                                                         source or sink.                                                       */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
           uint32_t             :  8;
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
      __IO uint32_t  ETE        :  1;               /*!< 3 consecutive transaction errors occurred on the USB bus              */
      __IO uint32_t  DR         :  1;               /*!< the corresponding channel's descriptor list rolls over                */
    } HCINT_EN6_b;                                  /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  HCTSIZ6;                         /*!< Host Channel Transfer Size Register                                   */

    struct {
      __IO uint32_t  SCHED_INFO :  8;               /*!< Every bit in this 8 bit register indicates scheduling for that
                                                         microframe.Bit N indicates scheduling for Nth microframe scheduling
                                                          for 8th microframe in that frame.                                    */
      __IO uint32_t  NTD        :  8;               /*!< Number of Transfer Descriptors.                                       */
           uint32_t             : 13;
      __IO uint32_t  PID        :  2;               /*!< the type of PID to use for the initial transaction                    */
      __IO uint32_t  PING       :  1;               /*!< Setting this field to 1 directs the host to do PING protocol          */
    } HCTSIZ6_b;                                    /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  HCDMA6;                          /*!< Host Channel-n DMA Address Register                                   */

    struct {
           uint32_t             :  3;
      __IO uint32_t  CTD        :  6;               /*!< Number of Transfer Descriptors for Non-Isochronous                    */
      __IO uint32_t  ADDR       : 23;               /*!< he start address of 512 bytes page for Non-Isochronous                */
    } HCDMA6_b;                                     /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED21;
  __IO uint32_t  HCDMAB6;                           /*!< Host Channel-n DMA Buffer Address Register                            */

  union {
    __IO uint32_t  HCC7;                            /*!< Host Channel Characteristics Register                                 */

    struct {
      __IO uint32_t  MPS        : 11;               /*!< Indicates the maximum packet size of the associated endpoint          */
      __IO uint32_t  EP_NUM     :  4;               /*!< Indicates the endpoint number on the device serving as the data
                                                         source or sink.                                                       */
      __IO uint32_t  EP_DIR     :  1;               /*!< Indicates whether the transaction is IN or OUT. 0, OUT. 1, IN         */
           uint32_t             :  1;
      __IO uint32_t  LSD        :  1;               /*!< indicate that this channel is communicating to a low-speed device.    */
      __IO uint32_t  EP_TYPE    :  2;               /*!< Indicates the transfer type selected.                                 */
      __IO uint32_t  EC         :  2;               /*!< Multi Count (MC) / Error Count (EC).                                  */
      __IO uint32_t  DA         :  7;               /*!< This field selects the specific device serving as the data source
                                                         or sink.                                                              */
      __IO uint32_t  OF         :  1;               /*!< The frame is odd or even.                                             */
      __IO uint32_t  CD         :  1;               /*!< sets this bit to stop transmitting/receiving data on a channel.       */
      __IO uint32_t  CE         :  1;               /*!< If the descriptor structure and data buffer are ready or not
                                                         yet.                                                                  */
    } HCC7_b;                                       /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED22;

  union {
    __IO uint32_t  HCINT7;                          /*!< Host Channel Interrupt Register                                       */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  CH_HALT    :  1;               /*!< Indicates the endpoint number on the device serving as the data
                                                         source or sink.                                                       */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
           uint32_t             :  8;
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
      __IO uint32_t  ETE        :  1;               /*!< 3 consecutive transaction errors occurred on the USB bus              */
      __IO uint32_t  DR         :  1;               /*!< the corresponding channel's descriptor list rolls over                */
    } HCINT7_b;                                     /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  HCINT_EN7;                       /*!< Host Channel Interrupt Enable Register                                */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  CH_HALT    :  1;               /*!< Indicates the endpoint number on the device serving as the data
                                                         source or sink.                                                       */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
           uint32_t             :  8;
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
      __IO uint32_t  ETE        :  1;               /*!< 3 consecutive transaction errors occurred on the USB bus              */
      __IO uint32_t  DR         :  1;               /*!< the corresponding channel's descriptor list rolls over                */
    } HCINT_EN7_b;                                  /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  HCTSIZ7;                         /*!< Host Channel Transfer Size Register                                   */

    struct {
      __IO uint32_t  SCHED_INFO :  8;               /*!< Every bit in this 8 bit register indicates scheduling for that
                                                         microframe.Bit N indicates scheduling for Nth microframe scheduling
                                                          for 8th microframe in that frame.                                    */
      __IO uint32_t  NTD        :  8;               /*!< Number of Transfer Descriptors.                                       */
           uint32_t             : 13;
      __IO uint32_t  PID        :  2;               /*!< the type of PID to use for the initial transaction                    */
      __IO uint32_t  PING       :  1;               /*!< Setting this field to 1 directs the host to do PING protocol          */
    } HCTSIZ7_b;                                    /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  HCDMA7;                          /*!< Host Channel-n DMA Address Register                                   */

    struct {
           uint32_t             :  3;
      __IO uint32_t  CTD        :  6;               /*!< Number of Transfer Descriptors for Non-Isochronous                    */
      __IO uint32_t  ADDR       : 23;               /*!< he start address of 512 bytes page for Non-Isochronous                */
    } HCDMA7_b;                                     /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED23;
  __IO uint32_t  HCDMAB7;                           /*!< Host Channel-n DMA Buffer Address Register                            */

  union {
    __IO uint32_t  HCC8;                            /*!< Host Channel Characteristics Register                                 */

    struct {
      __IO uint32_t  MPS        : 11;               /*!< Indicates the maximum packet size of the associated endpoint          */
      __IO uint32_t  EP_NUM     :  4;               /*!< Indicates the endpoint number on the device serving as the data
                                                         source or sink.                                                       */
      __IO uint32_t  EP_DIR     :  1;               /*!< Indicates whether the transaction is IN or OUT. 0, OUT. 1, IN         */
           uint32_t             :  1;
      __IO uint32_t  LSD        :  1;               /*!< indicate that this channel is communicating to a low-speed device.    */
      __IO uint32_t  EP_TYPE    :  2;               /*!< Indicates the transfer type selected.                                 */
      __IO uint32_t  EC         :  2;               /*!< Multi Count (MC) / Error Count (EC).                                  */
      __IO uint32_t  DA         :  7;               /*!< This field selects the specific device serving as the data source
                                                         or sink.                                                              */
      __IO uint32_t  OF         :  1;               /*!< The frame is odd or even.                                             */
      __IO uint32_t  CD         :  1;               /*!< sets this bit to stop transmitting/receiving data on a channel.       */
      __IO uint32_t  CE         :  1;               /*!< If the descriptor structure and data buffer are ready or not
                                                         yet.                                                                  */
    } HCC8_b;                                       /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED24;

  union {
    __IO uint32_t  HCINT8;                          /*!< Host Channel Interrupt Register                                       */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  CH_HALT    :  1;               /*!< Indicates the endpoint number on the device serving as the data
                                                         source or sink.                                                       */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
           uint32_t             :  8;
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
      __IO uint32_t  ETE        :  1;               /*!< 3 consecutive transaction errors occurred on the USB bus              */
      __IO uint32_t  DR         :  1;               /*!< the corresponding channel's descriptor list rolls over                */
    } HCINT8_b;                                     /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  HCINT_EN8;                       /*!< Host Channel Interrupt Enable Register                                */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  CH_HALT    :  1;               /*!< Indicates the endpoint number on the device serving as the data
                                                         source or sink.                                                       */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
           uint32_t             :  8;
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
      __IO uint32_t  ETE        :  1;               /*!< 3 consecutive transaction errors occurred on the USB bus              */
      __IO uint32_t  DR         :  1;               /*!< the corresponding channel's descriptor list rolls over                */
    } HCINT_EN8_b;                                  /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  HCTSIZ8;                         /*!< Host Channel Transfer Size Register                                   */

    struct {
      __IO uint32_t  SCHED_INFO :  8;               /*!< Every bit in this 8 bit register indicates scheduling for that
                                                         microframe.Bit N indicates scheduling for Nth microframe scheduling
                                                          for 8th microframe in that frame.                                    */
      __IO uint32_t  NTD        :  8;               /*!< Number of Transfer Descriptors.                                       */
           uint32_t             : 13;
      __IO uint32_t  PID        :  2;               /*!< the type of PID to use for the initial transaction                    */
      __IO uint32_t  PING       :  1;               /*!< Setting this field to 1 directs the host to do PING protocol          */
    } HCTSIZ8_b;                                    /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  HCDMA8;                          /*!< Host Channel-n DMA Address Register                                   */

    struct {
           uint32_t             :  3;
      __IO uint32_t  CTD        :  6;               /*!< Number of Transfer Descriptors for Non-Isochronous                    */
      __IO uint32_t  ADDR       : 23;               /*!< he start address of 512 bytes page for Non-Isochronous                */
    } HCDMA8_b;                                     /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED25;
  __IO uint32_t  HCDMAB8;                           /*!< Host Channel-n DMA Buffer Address Register                            */

  union {
    __IO uint32_t  HCC9;                            /*!< Host Channel Characteristics Register                                 */

    struct {
      __IO uint32_t  MPS        : 11;               /*!< Indicates the maximum packet size of the associated endpoint          */
      __IO uint32_t  EP_NUM     :  4;               /*!< Indicates the endpoint number on the device serving as the data
                                                         source or sink.                                                       */
      __IO uint32_t  EP_DIR     :  1;               /*!< Indicates whether the transaction is IN or OUT. 0, OUT. 1, IN         */
           uint32_t             :  1;
      __IO uint32_t  LSD        :  1;               /*!< indicate that this channel is communicating to a low-speed device.    */
      __IO uint32_t  EP_TYPE    :  2;               /*!< Indicates the transfer type selected.                                 */
      __IO uint32_t  EC         :  2;               /*!< Multi Count (MC) / Error Count (EC).                                  */
      __IO uint32_t  DA         :  7;               /*!< This field selects the specific device serving as the data source
                                                         or sink.                                                              */
      __IO uint32_t  OF         :  1;               /*!< The frame is odd or even.                                             */
      __IO uint32_t  CD         :  1;               /*!< sets this bit to stop transmitting/receiving data on a channel.       */
      __IO uint32_t  CE         :  1;               /*!< If the descriptor structure and data buffer are ready or not
                                                         yet.                                                                  */
    } HCC9_b;                                       /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED26;

  union {
    __IO uint32_t  HCINT9;                          /*!< Host Channel Interrupt Register                                       */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  CH_HALT    :  1;               /*!< Indicates the endpoint number on the device serving as the data
                                                         source or sink.                                                       */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
           uint32_t             :  8;
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
      __IO uint32_t  ETE        :  1;               /*!< 3 consecutive transaction errors occurred on the USB bus              */
      __IO uint32_t  DR         :  1;               /*!< the corresponding channel's descriptor list rolls over                */
    } HCINT9_b;                                     /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  HCINT_EN9;                       /*!< Host Channel Interrupt Enable Register                                */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  CH_HALT    :  1;               /*!< Indicates the endpoint number on the device serving as the data
                                                         source or sink.                                                       */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
           uint32_t             :  8;
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
      __IO uint32_t  ETE        :  1;               /*!< 3 consecutive transaction errors occurred on the USB bus              */
      __IO uint32_t  DR         :  1;               /*!< the corresponding channel's descriptor list rolls over                */
    } HCINT_EN9_b;                                  /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  HCTSIZ9;                         /*!< Host Channel Transfer Size Register                                   */

    struct {
      __IO uint32_t  SCHED_INFO :  8;               /*!< Every bit in this 8 bit register indicates scheduling for that
                                                         microframe.Bit N indicates scheduling for Nth microframe scheduling
                                                          for 8th microframe in that frame.                                    */
      __IO uint32_t  NTD        :  8;               /*!< Number of Transfer Descriptors.                                       */
           uint32_t             : 13;
      __IO uint32_t  PID        :  2;               /*!< the type of PID to use for the initial transaction                    */
      __IO uint32_t  PING       :  1;               /*!< Setting this field to 1 directs the host to do PING protocol          */
    } HCTSIZ9_b;                                    /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  HCDMA9;                          /*!< Host Channel-n DMA Address Register                                   */

    struct {
           uint32_t             :  3;
      __IO uint32_t  CTD        :  6;               /*!< Number of Transfer Descriptors for Non-Isochronous                    */
      __IO uint32_t  ADDR       : 23;               /*!< he start address of 512 bytes page for Non-Isochronous                */
    } HCDMA9_b;                                     /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED27;
  __IO uint32_t  HCDMAB9;                           /*!< Host Channel-n DMA Buffer Address Register                            */

  union {
    __IO uint32_t  HCC10;                           /*!< Host Channel Characteristics Register                                 */

    struct {
      __IO uint32_t  MPS        : 11;               /*!< Indicates the maximum packet size of the associated endpoint          */
      __IO uint32_t  EP_NUM     :  4;               /*!< Indicates the endpoint number on the device serving as the data
                                                         source or sink.                                                       */
      __IO uint32_t  EP_DIR     :  1;               /*!< Indicates whether the transaction is IN or OUT. 0, OUT. 1, IN         */
           uint32_t             :  1;
      __IO uint32_t  LSD        :  1;               /*!< indicate that this channel is communicating to a low-speed device.    */
      __IO uint32_t  EP_TYPE    :  2;               /*!< Indicates the transfer type selected.                                 */
      __IO uint32_t  EC         :  2;               /*!< Multi Count (MC) / Error Count (EC).                                  */
      __IO uint32_t  DA         :  7;               /*!< This field selects the specific device serving as the data source
                                                         or sink.                                                              */
      __IO uint32_t  OF         :  1;               /*!< The frame is odd or even.                                             */
      __IO uint32_t  CD         :  1;               /*!< sets this bit to stop transmitting/receiving data on a channel.       */
      __IO uint32_t  CE         :  1;               /*!< If the descriptor structure and data buffer are ready or not
                                                         yet.                                                                  */
    } HCC10_b;                                      /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED28;

  union {
    __IO uint32_t  HCINT10;                         /*!< Host Channel Interrupt Register                                       */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  CH_HALT    :  1;               /*!< Indicates the endpoint number on the device serving as the data
                                                         source or sink.                                                       */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
           uint32_t             :  8;
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
      __IO uint32_t  ETE        :  1;               /*!< 3 consecutive transaction errors occurred on the USB bus              */
      __IO uint32_t  DR         :  1;               /*!< the corresponding channel's descriptor list rolls over                */
    } HCINT10_b;                                    /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  HCINT_EN10;                      /*!< Host Channel Interrupt Enable Register                                */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  CH_HALT    :  1;               /*!< Indicates the endpoint number on the device serving as the data
                                                         source or sink.                                                       */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
           uint32_t             :  8;
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
      __IO uint32_t  ETE        :  1;               /*!< 3 consecutive transaction errors occurred on the USB bus              */
      __IO uint32_t  DR         :  1;               /*!< the corresponding channel's descriptor list rolls over                */
    } HCINT_EN10_b;                                 /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  HCTSIZ10;                        /*!< Host Channel Transfer Size Register                                   */

    struct {
      __IO uint32_t  SCHED_INFO :  8;               /*!< Every bit in this 8 bit register indicates scheduling for that
                                                         microframe.Bit N indicates scheduling for Nth microframe scheduling
                                                          for 8th microframe in that frame.                                    */
      __IO uint32_t  NTD        :  8;               /*!< Number of Transfer Descriptors.                                       */
           uint32_t             : 13;
      __IO uint32_t  PID        :  2;               /*!< the type of PID to use for the initial transaction                    */
      __IO uint32_t  PING       :  1;               /*!< Setting this field to 1 directs the host to do PING protocol          */
    } HCTSIZ10_b;                                   /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  HCDMA10;                         /*!< Host Channel-n DMA Address Register                                   */

    struct {
           uint32_t             :  3;
      __IO uint32_t  CTD        :  6;               /*!< Number of Transfer Descriptors for Non-Isochronous                    */
      __IO uint32_t  ADDR       : 23;               /*!< he start address of 512 bytes page for Non-Isochronous                */
    } HCDMA10_b;                                    /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED29;
  __IO uint32_t  HCDMAB10;                          /*!< Host Channel-n DMA Buffer Address Register                            */

  union {
    __IO uint32_t  HCC11;                           /*!< Host Channel Characteristics Register                                 */

    struct {
      __IO uint32_t  MPS        : 11;               /*!< Indicates the maximum packet size of the associated endpoint          */
      __IO uint32_t  EP_NUM     :  4;               /*!< Indicates the endpoint number on the device serving as the data
                                                         source or sink.                                                       */
      __IO uint32_t  EP_DIR     :  1;               /*!< Indicates whether the transaction is IN or OUT. 0, OUT. 1, IN         */
           uint32_t             :  1;
      __IO uint32_t  LSD        :  1;               /*!< indicate that this channel is communicating to a low-speed device.    */
      __IO uint32_t  EP_TYPE    :  2;               /*!< Indicates the transfer type selected.                                 */
      __IO uint32_t  EC         :  2;               /*!< Multi Count (MC) / Error Count (EC).                                  */
      __IO uint32_t  DA         :  7;               /*!< This field selects the specific device serving as the data source
                                                         or sink.                                                              */
      __IO uint32_t  OF         :  1;               /*!< The frame is odd or even.                                             */
      __IO uint32_t  CD         :  1;               /*!< sets this bit to stop transmitting/receiving data on a channel.       */
      __IO uint32_t  CE         :  1;               /*!< If the descriptor structure and data buffer are ready or not
                                                         yet.                                                                  */
    } HCC11_b;                                      /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED30;

  union {
    __IO uint32_t  HCINT11;                         /*!< Host Channel Interrupt Register                                       */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  CH_HALT    :  1;               /*!< Indicates the endpoint number on the device serving as the data
                                                         source or sink.                                                       */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
           uint32_t             :  8;
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
      __IO uint32_t  ETE        :  1;               /*!< 3 consecutive transaction errors occurred on the USB bus              */
      __IO uint32_t  DR         :  1;               /*!< the corresponding channel's descriptor list rolls over                */
    } HCINT11_b;                                    /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  HCINT_EN11;                      /*!< Host Channel Interrupt Enable Register                                */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  CH_HALT    :  1;               /*!< Indicates the endpoint number on the device serving as the data
                                                         source or sink.                                                       */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
           uint32_t             :  8;
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
      __IO uint32_t  ETE        :  1;               /*!< 3 consecutive transaction errors occurred on the USB bus              */
      __IO uint32_t  DR         :  1;               /*!< the corresponding channel's descriptor list rolls over                */
    } HCINT_EN11_b;                                 /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  HCTSIZ11;                        /*!< Host Channel Transfer Size Register                                   */

    struct {
      __IO uint32_t  SCHED_INFO :  8;               /*!< Every bit in this 8 bit register indicates scheduling for that
                                                         microframe.Bit N indicates scheduling for Nth microframe scheduling
                                                          for 8th microframe in that frame.                                    */
      __IO uint32_t  NTD        :  8;               /*!< Number of Transfer Descriptors.                                       */
           uint32_t             : 13;
      __IO uint32_t  PID        :  2;               /*!< the type of PID to use for the initial transaction                    */
      __IO uint32_t  PING       :  1;               /*!< Setting this field to 1 directs the host to do PING protocol          */
    } HCTSIZ11_b;                                   /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  HCDMA11;                         /*!< Host Channel-n DMA Address Register                                   */

    struct {
           uint32_t             :  3;
      __IO uint32_t  CTD        :  6;               /*!< Number of Transfer Descriptors for Non-Isochronous                    */
      __IO uint32_t  ADDR       : 23;               /*!< he start address of 512 bytes page for Non-Isochronous                */
    } HCDMA11_b;                                    /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED31;
  __IO uint32_t  HCDMAB11;                          /*!< Host Channel-n DMA Buffer Address Register                            */

  union {
    __IO uint32_t  HCC12;                           /*!< Host Channel Characteristics Register                                 */

    struct {
      __IO uint32_t  MPS        : 11;               /*!< Indicates the maximum packet size of the associated endpoint          */
      __IO uint32_t  EP_NUM     :  4;               /*!< Indicates the endpoint number on the device serving as the data
                                                         source or sink.                                                       */
      __IO uint32_t  EP_DIR     :  1;               /*!< Indicates whether the transaction is IN or OUT. 0, OUT. 1, IN         */
           uint32_t             :  1;
      __IO uint32_t  LSD        :  1;               /*!< indicate that this channel is communicating to a low-speed device.    */
      __IO uint32_t  EP_TYPE    :  2;               /*!< Indicates the transfer type selected.                                 */
      __IO uint32_t  EC         :  2;               /*!< Multi Count (MC) / Error Count (EC).                                  */
      __IO uint32_t  DA         :  7;               /*!< This field selects the specific device serving as the data source
                                                         or sink.                                                              */
      __IO uint32_t  OF         :  1;               /*!< The frame is odd or even.                                             */
      __IO uint32_t  CD         :  1;               /*!< sets this bit to stop transmitting/receiving data on a channel.       */
      __IO uint32_t  CE         :  1;               /*!< If the descriptor structure and data buffer are ready or not
                                                         yet.                                                                  */
    } HCC12_b;                                      /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED32;

  union {
    __IO uint32_t  HCINT12;                         /*!< Host Channel Interrupt Register                                       */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  CH_HALT    :  1;               /*!< Indicates the endpoint number on the device serving as the data
                                                         source or sink.                                                       */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
           uint32_t             :  8;
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
      __IO uint32_t  ETE        :  1;               /*!< 3 consecutive transaction errors occurred on the USB bus              */
      __IO uint32_t  DR         :  1;               /*!< the corresponding channel's descriptor list rolls over                */
    } HCINT12_b;                                    /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  HCINT_EN12;                      /*!< Host Channel Interrupt Enable Register                                */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  CH_HALT    :  1;               /*!< Indicates the endpoint number on the device serving as the data
                                                         source or sink.                                                       */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
           uint32_t             :  8;
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
      __IO uint32_t  ETE        :  1;               /*!< 3 consecutive transaction errors occurred on the USB bus              */
      __IO uint32_t  DR         :  1;               /*!< the corresponding channel's descriptor list rolls over                */
    } HCINT_EN12_b;                                 /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  HCTSIZ12;                        /*!< Host Channel Transfer Size Register                                   */

    struct {
      __IO uint32_t  SCHED_INFO :  8;               /*!< Every bit in this 8 bit register indicates scheduling for that
                                                         microframe.Bit N indicates scheduling for Nth microframe scheduling
                                                          for 8th microframe in that frame.                                    */
      __IO uint32_t  NTD        :  8;               /*!< Number of Transfer Descriptors.                                       */
           uint32_t             : 13;
      __IO uint32_t  PID        :  2;               /*!< the type of PID to use for the initial transaction                    */
      __IO uint32_t  PING       :  1;               /*!< Setting this field to 1 directs the host to do PING protocol          */
    } HCTSIZ12_b;                                   /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  HCDMA12;                         /*!< Host Channel-n DMA Address Register                                   */

    struct {
           uint32_t             :  3;
      __IO uint32_t  CTD        :  6;               /*!< Number of Transfer Descriptors for Non-Isochronous                    */
      __IO uint32_t  ADDR       : 23;               /*!< he start address of 512 bytes page for Non-Isochronous                */
    } HCDMA12_b;                                    /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED33;
  __IO uint32_t  HCDMAB12;                          /*!< Host Channel-n DMA Buffer Address Register                            */

  union {
    __IO uint32_t  HCC13;                           /*!< Host Channel Characteristics Register                                 */

    struct {
      __IO uint32_t  MPS        : 11;               /*!< Indicates the maximum packet size of the associated endpoint          */
      __IO uint32_t  EP_NUM     :  4;               /*!< Indicates the endpoint number on the device serving as the data
                                                         source or sink.                                                       */
      __IO uint32_t  EP_DIR     :  1;               /*!< Indicates whether the transaction is IN or OUT. 0, OUT. 1, IN         */
           uint32_t             :  1;
      __IO uint32_t  LSD        :  1;               /*!< indicate that this channel is communicating to a low-speed device.    */
      __IO uint32_t  EP_TYPE    :  2;               /*!< Indicates the transfer type selected.                                 */
      __IO uint32_t  EC         :  2;               /*!< Multi Count (MC) / Error Count (EC).                                  */
      __IO uint32_t  DA         :  7;               /*!< This field selects the specific device serving as the data source
                                                         or sink.                                                              */
      __IO uint32_t  OF         :  1;               /*!< The frame is odd or even.                                             */
      __IO uint32_t  CD         :  1;               /*!< sets this bit to stop transmitting/receiving data on a channel.       */
      __IO uint32_t  CE         :  1;               /*!< If the descriptor structure and data buffer are ready or not
                                                         yet.                                                                  */
    } HCC13_b;                                      /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED34;

  union {
    __IO uint32_t  HCINT13;                         /*!< Host Channel Interrupt Register                                       */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  CH_HALT    :  1;               /*!< Indicates the endpoint number on the device serving as the data
                                                         source or sink.                                                       */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
           uint32_t             :  8;
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
      __IO uint32_t  ETE        :  1;               /*!< 3 consecutive transaction errors occurred on the USB bus              */
      __IO uint32_t  DR         :  1;               /*!< the corresponding channel's descriptor list rolls over                */
    } HCINT13_b;                                    /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  HCINT_EN13;                      /*!< Host Channel Interrupt Enable Register                                */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  CH_HALT    :  1;               /*!< Indicates the endpoint number on the device serving as the data
                                                         source or sink.                                                       */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
           uint32_t             :  8;
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
      __IO uint32_t  ETE        :  1;               /*!< 3 consecutive transaction errors occurred on the USB bus              */
      __IO uint32_t  DR         :  1;               /*!< the corresponding channel's descriptor list rolls over                */
    } HCINT_EN13_b;                                 /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  HCTSIZ13;                        /*!< Host Channel Transfer Size Register                                   */

    struct {
      __IO uint32_t  SCHED_INFO :  8;               /*!< Every bit in this 8 bit register indicates scheduling for that
                                                         microframe.Bit N indicates scheduling for Nth microframe scheduling
                                                          for 8th microframe in that frame.                                    */
      __IO uint32_t  NTD        :  8;               /*!< Number of Transfer Descriptors.                                       */
           uint32_t             : 13;
      __IO uint32_t  PID        :  2;               /*!< the type of PID to use for the initial transaction                    */
      __IO uint32_t  PING       :  1;               /*!< Setting this field to 1 directs the host to do PING protocol          */
    } HCTSIZ13_b;                                   /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  HCDMA13;                         /*!< Host Channel-n DMA Address Register                                   */

    struct {
           uint32_t             :  3;
      __IO uint32_t  CTD        :  6;               /*!< Number of Transfer Descriptors for Non-Isochronous                    */
      __IO uint32_t  ADDR       : 23;               /*!< he start address of 512 bytes page for Non-Isochronous                */
    } HCDMA13_b;                                    /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED35;
  __IO uint32_t  HCDMAB13;                          /*!< Host Channel-n DMA Buffer Address Register                            */

  union {
    __IO uint32_t  HCC14;                           /*!< Host Channel Characteristics Register                                 */

    struct {
      __IO uint32_t  MPS        : 11;               /*!< Indicates the maximum packet size of the associated endpoint          */
      __IO uint32_t  EP_NUM     :  4;               /*!< Indicates the endpoint number on the device serving as the data
                                                         source or sink.                                                       */
      __IO uint32_t  EP_DIR     :  1;               /*!< Indicates whether the transaction is IN or OUT. 0, OUT. 1, IN         */
           uint32_t             :  1;
      __IO uint32_t  LSD        :  1;               /*!< indicate that this channel is communicating to a low-speed device.    */
      __IO uint32_t  EP_TYPE    :  2;               /*!< Indicates the transfer type selected.                                 */
      __IO uint32_t  EC         :  2;               /*!< Multi Count (MC) / Error Count (EC).                                  */
      __IO uint32_t  DA         :  7;               /*!< This field selects the specific device serving as the data source
                                                         or sink.                                                              */
      __IO uint32_t  OF         :  1;               /*!< The frame is odd or even.                                             */
      __IO uint32_t  CD         :  1;               /*!< sets this bit to stop transmitting/receiving data on a channel.       */
      __IO uint32_t  CE         :  1;               /*!< If the descriptor structure and data buffer are ready or not
                                                         yet.                                                                  */
    } HCC14_b;                                      /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED36;

  union {
    __IO uint32_t  HCINT14;                         /*!< Host Channel Interrupt Register                                       */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  CH_HALT    :  1;               /*!< Indicates the endpoint number on the device serving as the data
                                                         source or sink.                                                       */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
           uint32_t             :  8;
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
      __IO uint32_t  ETE        :  1;               /*!< 3 consecutive transaction errors occurred on the USB bus              */
      __IO uint32_t  DR         :  1;               /*!< the corresponding channel's descriptor list rolls over                */
    } HCINT14_b;                                    /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  HCINT_EN14;                      /*!< Host Channel Interrupt Enable Register                                */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  CH_HALT    :  1;               /*!< Indicates the endpoint number on the device serving as the data
                                                         source or sink.                                                       */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
           uint32_t             :  8;
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
      __IO uint32_t  ETE        :  1;               /*!< 3 consecutive transaction errors occurred on the USB bus              */
      __IO uint32_t  DR         :  1;               /*!< the corresponding channel's descriptor list rolls over                */
    } HCINT_EN14_b;                                 /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  HCTSIZ14;                        /*!< Host Channel Transfer Size Register                                   */

    struct {
      __IO uint32_t  SCHED_INFO :  8;               /*!< Every bit in this 8 bit register indicates scheduling for that
                                                         microframe.Bit N indicates scheduling for Nth microframe scheduling
                                                          for 8th microframe in that frame.                                    */
      __IO uint32_t  NTD        :  8;               /*!< Number of Transfer Descriptors.                                       */
           uint32_t             : 13;
      __IO uint32_t  PID        :  2;               /*!< the type of PID to use for the initial transaction                    */
      __IO uint32_t  PING       :  1;               /*!< Setting this field to 1 directs the host to do PING protocol          */
    } HCTSIZ14_b;                                   /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  HCDMA14;                         /*!< Host Channel-n DMA Address Register                                   */

    struct {
           uint32_t             :  3;
      __IO uint32_t  CTD        :  6;               /*!< Number of Transfer Descriptors for Non-Isochronous                    */
      __IO uint32_t  ADDR       : 23;               /*!< he start address of 512 bytes page for Non-Isochronous                */
    } HCDMA14_b;                                    /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED37;
  __IO uint32_t  HCDMAB14;                          /*!< Host Channel-n DMA Buffer Address Register                            */

  union {
    __IO uint32_t  HCC15;                           /*!< Host Channel Characteristics Register                                 */

    struct {
      __IO uint32_t  MPS        : 11;               /*!< Indicates the maximum packet size of the associated endpoint          */
      __IO uint32_t  EP_NUM     :  4;               /*!< Indicates the endpoint number on the device serving as the data
                                                         source or sink.                                                       */
      __IO uint32_t  EP_DIR     :  1;               /*!< Indicates whether the transaction is IN or OUT. 0, OUT. 1, IN         */
           uint32_t             :  1;
      __IO uint32_t  LSD        :  1;               /*!< indicate that this channel is communicating to a low-speed device.    */
      __IO uint32_t  EP_TYPE    :  2;               /*!< Indicates the transfer type selected.                                 */
      __IO uint32_t  EC         :  2;               /*!< Multi Count (MC) / Error Count (EC).                                  */
      __IO uint32_t  DA         :  7;               /*!< This field selects the specific device serving as the data source
                                                         or sink.                                                              */
      __IO uint32_t  OF         :  1;               /*!< The frame is odd or even.                                             */
      __IO uint32_t  CD         :  1;               /*!< sets this bit to stop transmitting/receiving data on a channel.       */
      __IO uint32_t  CE         :  1;               /*!< If the descriptor structure and data buffer are ready or not
                                                         yet.                                                                  */
    } HCC15_b;                                      /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED38;

  union {
    __IO uint32_t  HCINT15;                         /*!< Host Channel Interrupt Register                                       */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  CH_HALT    :  1;               /*!< Indicates the endpoint number on the device serving as the data
                                                         source or sink.                                                       */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
           uint32_t             :  8;
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
      __IO uint32_t  ETE        :  1;               /*!< 3 consecutive transaction errors occurred on the USB bus              */
      __IO uint32_t  DR         :  1;               /*!< the corresponding channel's descriptor list rolls over                */
    } HCINT15_b;                                    /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  HCINT_EN15;                      /*!< Host Channel Interrupt Enable Register                                */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  CH_HALT    :  1;               /*!< Indicates the endpoint number on the device serving as the data
                                                         source or sink.                                                       */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
           uint32_t             :  8;
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
      __IO uint32_t  ETE        :  1;               /*!< 3 consecutive transaction errors occurred on the USB bus              */
      __IO uint32_t  DR         :  1;               /*!< the corresponding channel's descriptor list rolls over                */
    } HCINT_EN15_b;                                 /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  HCTSIZ15;                        /*!< Host Channel Transfer Size Register                                   */

    struct {
      __IO uint32_t  SCHED_INFO :  8;               /*!< Every bit in this 8 bit register indicates scheduling for that
                                                         microframe.Bit N indicates scheduling for Nth microframe scheduling
                                                          for 8th microframe in that frame.                                    */
      __IO uint32_t  NTD        :  8;               /*!< Number of Transfer Descriptors.                                       */
           uint32_t             : 13;
      __IO uint32_t  PID        :  2;               /*!< the type of PID to use for the initial transaction                    */
      __IO uint32_t  PING       :  1;               /*!< Setting this field to 1 directs the host to do PING protocol          */
    } HCTSIZ15_b;                                   /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  HCDMA15;                         /*!< Host Channel-n DMA Address Register                                   */

    struct {
           uint32_t             :  3;
      __IO uint32_t  CTD        :  6;               /*!< Number of Transfer Descriptors for Non-Isochronous                    */
      __IO uint32_t  ADDR       : 23;               /*!< he start address of 512 bytes page for Non-Isochronous                */
    } HCDMA15_b;                                    /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED39;
  __IO uint32_t  HCDMAB15;                          /*!< Host Channel-n DMA Buffer Address Register                            */
  __I  uint32_t  RESERVED40[64];

  union {
    __IO uint32_t  DCFG;                            /*!< Device Configuration Register                                         */

    struct {
      __IO uint32_t  DSPEED     :  2;               /*!< the maximum speed the application can support                         */
      __IO uint32_t  NZLSOH     :  1;               /*!< select the handshake the core sends on receiving a non zero-length
                                                         data packet during the OUT transaction of a control transfer's
                                                          Status stage                                                         */
      __IO uint32_t  EN_32K_SUS :  1;               /*!< Enable 32 KHz Suspend mode                                            */
      __IO uint32_t  DEVICE_ADDR:  7;               /*!< The application must program this field after every SetAddress
                                                         control command                                                       */
      __IO uint32_t  PFI        :  2;               /*!< Indicates the time within a (micro)frame at which the application
                                                         must be notified using the End Of Periodic Frame Interrupt            */
      __IO uint32_t  EDON       :  1;               /*!< If set the core sets NAK after Bulk OUT transfer complete             */
           uint32_t             :  9;
      __IO uint32_t  EN_SG_DMA  :  1;               /*!< enable the Scatter/Gather DMA operation                               */
      __IO uint32_t  PSI        :  2;               /*!< Periodic Scheduling Interval                                          */
      __IO uint32_t  RVP        :  6;               /*!< It controls the resume period when the core resumes from suspend      */
    } DCFG_b;                                       /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  DCTL;                            /*!< Device Control Register                                               */

    struct {
      __IO uint32_t  RWS        :  1;               /*!< If set, the core initiates remote signaling to wake the USB
                                                         hosts                                                                 */
      __IO uint32_t  SD         :  1;               /*!< If set, generates a device disconnect event to the USB host           */
      __I  uint32_t  GNPINS     :  1;               /*!< A NAK handshake is sent out on all non-periodic IN endpoints,
                                                         irrespective of the data availability in the transmit FIFO.           */
      __I  uint32_t  GONS       :  1;               /*!< No data is written to the RxFIFO, irrespective of space availability.. */
      __IO uint32_t  TC         :  3;               /*!< Test Control                                                          */
      __O  uint32_t  SGNPIN     :  1;               /*!< A write to this field sets the Global Non-periodic IN NAK             */
      __O  uint32_t  CGNPIN     :  1;               /*!< A write to this field clears the Global Non-periodic IN NAK           */
      __O  uint32_t  SGON       :  1;               /*!< A write to this field sets the Global OUT NAK                         */
      __O  uint32_t  CGON       :  1;               /*!< A write to this field sets the Global OUT NAK.                        */
      __IO uint32_t  POPD       :  1;               /*!< Power-On Programming Done                                             */
      __IO uint32_t  GMC        :  2;               /*!< GMC must be programmed only once after initialization. the number
                                                         of packets to be serviced for that end point before moving to
                                                          the next end point                                                   */
           uint32_t             :  1;
      __IO uint32_t  IFNIE      :  1;               /*!< Ignore frame number for isochronous endpoints                         */
      __IO uint32_t  NBE        :  1;               /*!< Set NAK automatically on babble                                       */
      __IO uint32_t  ECBNA      :  1;               /*!< After receiving BNA interrupt, the core disables the endpoint         */
    } DCTL_b;                                       /*!< BitSize                                                               */
  };

  union {
    __I  uint32_t  DSTS;                            /*!< Device Status Register                                                */

    struct {
      __I  uint32_t  SUSPEND    :  1;               /*!< this bit is set as long as a Suspend condition is detected on
                                                         the USB                                                               */
      __I  uint32_t  SPEED      :  2;               /*!< Indicates the speed at which the DWC_otg core has come up after
                                                         speed detection through a chirp sequence                              */
      __I  uint32_t  EE         :  1;               /*!< reason of suspend state                                               */
           uint32_t             :  4;
      __I  uint32_t  SOFFN      : 14;               /*!< Frame or Microframe Number of the Received SOF                        */
      __I  uint32_t  DLSDP      :  1;               /*!< Logic level of D+                                                     */
      __I  uint32_t  DLSDN      :  1;               /*!< Logic level of D-                                                     */
    } DSTS_b;                                       /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED41;

  union {
    __IO uint32_t  DIEPEN;                          /*!< Device IN Endpoint Common Interrupt Enable Register                   */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer Completed Interrupt                                          */
      __IO uint32_t  ED         :  1;               /*!< Endpoint Disabled Interrupt                                           */
      __IO uint32_t  AHB_ERR    :  1;               /*!< AHB Error Interrupt                                                   */
      __IO uint32_t  TIMEOUT    :  1;               /*!< Timeout Condition(Non-isochronous endpoints)                          */
      __IO uint32_t  ITRWTFE    :  1;               /*!< IN Token Received When TxFIFO Empty                                   */
      __IO uint32_t  ITRWEPM    :  1;               /*!< IN Token received with EP Mismatch                                    */
      __IO uint32_t  IENE       :  1;               /*!< IN Endpoint NAK Effective                                             */
           uint32_t             :  1;
      __IO uint32_t  FU         :  1;               /*!< Fifo Underrun                                                         */
      __IO uint32_t  BNA        :  1;               /*!< BNA Interrupt                                                         */
           uint32_t             :  3;
      __IO uint32_t  NAK        :  1;               /*!< NAK interrupt                                                         */
    } DIEPEN_b;                                     /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  DOEPEN;                          /*!< Device OUT Endpoint Common Interrupt Enable Register                  */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer Completed Interrupt                                          */
      __IO uint32_t  ED         :  1;               /*!< Endpoint Disabled Interrupt                                           */
      __IO uint32_t  AHB_ERR    :  1;               /*!< AHB Error Interrupt                                                   */
      __IO uint32_t  SPD        :  1;               /*!< SETUP Phase Done, Applies to control endpoints only                   */
      __IO uint32_t  OTRWED     :  1;               /*!< OUT Token Received when Endpoint Disabled, Applies to control
                                                         OUT endpoints only                                                    */
      __IO uint32_t  SPR        :  1;               /*!< Status Phase Received                                                 */
      __IO uint32_t  BTBSPR     :  1;               /*!< Back-to-Back SETUP Packets Received, Applies to control OUT
                                                         endpoints only                                                        */
           uint32_t             :  1;
      __IO uint32_t  OPE        :  1;               /*!< OUT Packet Error                                                      */
      __IO uint32_t  BNA        :  1;               /*!< BNA Interrupt                                                         */
           uint32_t             :  2;
      __IO uint32_t  BE         :  1;               /*!< Babble Error interrupt                                                */
      __IO uint32_t  NAK        :  1;               /*!< NAK interrupt                                                         */
      __IO uint32_t  NYET       :  1;               /*!< NYET interrupt                                                        */
    } DOEPEN_b;                                     /*!< BitSize                                                               */
  };

  union {
    __I  uint32_t  DAINT;                           /*!< Device All Channels Interrupt Register                                */

    struct {
      __I  uint32_t  INT        : 16;               /*!< IN Endpoint Interrupt Bits, from 0 to 15.                             */
      __I  uint32_t  OUT_INT    : 16;               /*!< OUT Endpoint Interrupt Bits, from 0 to 15.                            */
    } DAINT_b;                                      /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  DAINT_EN;                        /*!< Device All Channels Interrupt Enable Register                         */

    struct {
      __IO uint32_t  IN_EN      : 16;               /*!< IN EP Interrupt Enable, from 0 to 15.                                 */
      __IO uint32_t  OUT_EN     : 16;               /*!< OUT EP Interrupt Enable, from 0 to 15.                                */
    } DAINT_EN_b;                                   /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED42[4];

  union {
    __IO uint32_t  DTHRCTL;                         /*!< Device Threshold Control Register                                     */

    struct {
      __IO uint32_t  NISOINETE  :  1;               /*!< Non-ISO IN Endpoints Threshold Enable                                 */
      __IO uint32_t  ISOINETE   :  1;               /*!< ISO IN Endpoints Threshold Enable                                     */
      __IO uint32_t  TTL        :  9;               /*!< This field specifies Transmit thresholding size in DWORDS             */
      __IO uint32_t  ATR        :  2;               /*!< These bits define the ratio between the AHB threshold and the
                                                         MAC threshold for the transmit path only.                             */
           uint32_t             :  3;
      __IO uint32_t  RTE        :  1;               /*!< If set, the core enables thresholding in the receive direction        */
      __IO uint32_t  RTL        :  9;               /*!< This field specifies Receive thresholding size in DWORDS              */
           uint32_t             :  1;
      __IO uint32_t  APE        :  1;               /*!< This bit controls internal DMA arbiter parking for IN endpoints       */
    } DTHRCTL_b;                                    /*!< BitSize                                                               */
  };
  __IO uint16_t  DIEPEMPEN;                         /*!< Device IN Endpoint FIFO Empty Interrupt Enable Register               */
  __I  uint16_t  RESERVED43[101];

  union {
    __IO uint32_t  DIEPCTL0;                        /*!< Device Control IN Endpoint 0 Control Register                         */

    struct {
      __IO uint32_t  MPS        :  2;               /*!< Indicates the maximum packet size of the associated endpoint,
                                                         applies to IN and OUT endpoints                                       */
           uint32_t             : 13;
      __I  uint32_t  USBAE      :  1;               /*!< Always 1, indicating that control endpoint 0 is always active
                                                         in all configurations and interfaces                                  */
           uint32_t             :  1;
      __I  uint32_t  NAK        :  1;               /*!< The core is transmitting NAK handshakes on this endpoint              */
      __I  uint32_t  EP_TYPE    :  2;               /*!< Hardcoded to 00 for control                                           */
           uint32_t             :  1;
      __IO uint32_t  STALL      :  1;               /*!< The application sets this bit, and the core clears it when a
                                                         SETUP token is received for this endpoint                             */
      __IO uint32_t  TX_FIFO_NUM:  4;               /*!< TxFIFO Number                                                         */
      __O  uint32_t  CNAK       :  1;               /*!< A write to this bit clears the NAK bit for the endpoint               */
      __O  uint32_t  SNAK       :  1;               /*!< A write to this bit sets the NAK bit for the endpoint                 */
           uint32_t             :  2;
      __IO uint32_t  EPD        :  1;               /*!< The application sets this bit to stop transmitting data on an
                                                         endpoint even before the transfer for that endpoint is complete       */
      __IO uint32_t  EPE        :  1;               /*!< the descriptor structure and data buffer with data ready to
                                                         transmit is setup                                                     */
    } DIEPCTL0_b;                                   /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED44;

  union {
    __IO uint32_t  DIEPINT0;                        /*!< Device IN Endpoint-n Interrupt Register                               */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  EPD        :  1;               /*!< Endpoint Disabled Interrupt                                           */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
      __IO uint32_t  TIMEOUT    :  1;               /*!< a timeout condition on the USB for the last IN token on this
                                                         endpoint                                                              */
      __IO uint32_t  INTRWTFE   :  1;               /*!< IN Token Received When TxFIFO is Empty                                */
      __IO uint32_t  INTRWEPM   :  1;               /*!< IN Token Received with EP Mismatch                                    */
      __IO uint32_t  INEPNE     :  1;               /*!< IN Endpoint NAK Effective                                             */
      __I  uint32_t  TFE        :  1;               /*!< either half or completely empty depending on GAHBCFG.NPTxFEmpLvl      */
      __IO uint32_t  TFU        :  1;               /*!< Transmit FIFO Underrun                                                */
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
           uint32_t             :  2;
      __IO uint32_t  BE         :  1;               /*!< Babble Error                                                          */
      __IO uint32_t  NAK        :  1;               /*!< a NAK is transmitted                                                  */
      __IO uint32_t  NYET       :  1;               /*!< a NYET response is transmitted                                        */
    } DIEPINT0_b;                                   /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED45;

  union {
    __IO uint32_t  DIEPTSIZ0;                       /*!< Device IN Endpoint 0 Transfer Size Register                           */

    struct {
      __IO uint32_t  SIZE       :  7;               /*!< Indicates the transfer size in bytes for endpoint 0                   */
           uint32_t             : 12;
      __IO uint32_t  PACKET_CNT :  2;               /*!< the total number of USB packets                                       */
    } DIEPTSIZ0_b;                                  /*!< BitSize                                                               */
  };
  __IO uint32_t  DIEPDMA0;                          /*!< Device IN Endpoint-n DMA Address Register                             */
  __IO uint16_t  DTXFSA0;                           /*!< Device IN Endpoint-n Transmit FIFO Space Avail Register               */
  __I  uint16_t  RESERVED46;
  __I  uint32_t  DIEPDMAB0;                         /*!< Device IN Endpoint-n DMA Buffer Address Register                      */

  union {
    __IO uint32_t  DIEPCTL1;                        /*!< Device IN Endpoint N Control Register                                 */

    struct {
      __IO uint32_t  MPS        : 11;               /*!< Indicates the maximum packet size of the associated endpoint          */
           uint32_t             :  4;
      __IO uint32_t  UAE        :  1;               /*!< Indicates whether this endpoint is active                             */
      __I  uint32_t  DPID       :  1;               /*!< Endpoint Data PID                                                     */
      __I  uint32_t  NAK        :  1;               /*!< The core is transmitting NAK handshakes on this endpoint if
                                                         set                                                                   */
      __IO uint32_t  EP_TYPE    :  2;               /*!< Indicates the transfer type selected.                                 */
           uint32_t             :  1;
      __IO uint32_t  STALL      :  1;               /*!< To non-control, non-isochronous IN endpoints, stall all tokens.
                                                         To control endpoints, response an ACK                                 */
      __IO uint32_t  TX_FIFO_NUM:  4;               /*!< TxFIFO Number                                                         */
      __O  uint32_t  CNAK       :  1;               /*!< A write to this bit clears the NAK bit for the endpoint               */
      __O  uint32_t  SNAK       :  1;               /*!< A write to this bit sets the NAK bit for the endpoint                 */
      __O  uint32_t  SET_D0_PID :  1;               /*!< Set DATA0 PID                                                         */
      __O  uint32_t  SET_D1_PID :  1;               /*!< Set DATA1 PID                                                         */
      __IO uint32_t  EPD        :  1;               /*!< The application sets this bit to stop transmitting data on an
                                                         endpoint even before the transfer for that endpoint is complete       */
      __IO uint32_t  EPE        :  1;               /*!< the descriptor structure and data buffer with data ready to
                                                         transmit is setup                                                     */
    } DIEPCTL1_b;                                   /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED47;

  union {
    __IO uint32_t  DIEPINT1;                        /*!< Device IN Endpoint-n Interrupt Register                               */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  EPD        :  1;               /*!< Endpoint Disabled Interrupt                                           */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
      __IO uint32_t  TIMEOUT    :  1;               /*!< a timeout condition on the USB for the last IN token on this
                                                         endpoint                                                              */
      __IO uint32_t  INTRWTFE   :  1;               /*!< IN Token Received When TxFIFO is Empty                                */
      __IO uint32_t  INTRWEPM   :  1;               /*!< IN Token Received with EP Mismatch                                    */
      __IO uint32_t  INEPNE     :  1;               /*!< IN Endpoint NAK Effective                                             */
      __I  uint32_t  TFE        :  1;               /*!< either half or completely empty depending on GAHBCFG.NPTxFEmpLvl      */
      __IO uint32_t  TFU        :  1;               /*!< Transmit FIFO Underrun                                                */
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
           uint32_t             :  2;
      __IO uint32_t  BE         :  1;               /*!< Babble Error                                                          */
      __IO uint32_t  NAK        :  1;               /*!< a NAK is transmitted                                                  */
      __IO uint32_t  NYET       :  1;               /*!< a NYET response is transmitted                                        */
    } DIEPINT1_b;                                   /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED48;

  union {
    __IO uint32_t  DIEPTSIZ1;                       /*!< Device IN Endpoint-n Transfer Size Register                           */

    struct {
      __IO uint32_t  SIZE       : 19;               /*!< Indicates the transfer size in bytes for endpoint 0                   */
      __IO uint32_t  PACKET_CNT : 10;               /*!< the total number of USB packets                                       */
      __IO uint32_t  MC         :  2;               /*!< the number of packets per microframe to periodic IN endpoints.
                                                         The number of packets must be fetched per non-periodic IN endpoints   */
    } DIEPTSIZ1_b;                                  /*!< BitSize                                                               */
  };
  __IO uint32_t  DIEPDMA1;                          /*!< Device IN Endpoint-n DMA Address Register                             */
  __IO uint16_t  DTXFSA1;                           /*!< Device IN Endpoint-n Transmit FIFO Space Avail Register               */
  __I  uint16_t  RESERVED49;
  __I  uint32_t  DIEPDMAB1;                         /*!< Device IN Endpoint-n DMA Buffer Address Register                      */

  union {
    __IO uint32_t  DIEPCTL2;                        /*!< Device IN Endpoint N Control Register                                 */

    struct {
      __IO uint32_t  MPS        : 11;               /*!< Indicates the maximum packet size of the associated endpoint          */
           uint32_t             :  4;
      __IO uint32_t  UAE        :  1;               /*!< Indicates whether this endpoint is active                             */
      __I  uint32_t  DPID       :  1;               /*!< Endpoint Data PID                                                     */
      __I  uint32_t  NAK        :  1;               /*!< The core is transmitting NAK handshakes on this endpoint if
                                                         set                                                                   */
      __IO uint32_t  EP_TYPE    :  2;               /*!< Indicates the transfer type selected.                                 */
           uint32_t             :  1;
      __IO uint32_t  STALL      :  1;               /*!< To non-control, non-isochronous IN endpoints, stall all tokens.
                                                         To control endpoints, response an ACK                                 */
      __IO uint32_t  TX_FIFO_NUM:  4;               /*!< TxFIFO Number                                                         */
      __O  uint32_t  CNAK       :  1;               /*!< A write to this bit clears the NAK bit for the endpoint               */
      __O  uint32_t  SNAK       :  1;               /*!< A write to this bit sets the NAK bit for the endpoint                 */
      __O  uint32_t  SET_D0_PID :  1;               /*!< Set DATA0 PID                                                         */
      __O  uint32_t  SET_D1_PID :  1;               /*!< Set DATA1 PID                                                         */
      __IO uint32_t  EPD        :  1;               /*!< The application sets this bit to stop transmitting data on an
                                                         endpoint even before the transfer for that endpoint is complete       */
      __IO uint32_t  EPE        :  1;               /*!< the descriptor structure and data buffer with data ready to
                                                         transmit is setup                                                     */
    } DIEPCTL2_b;                                   /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED50;

  union {
    __IO uint32_t  DIEPINT2;                        /*!< Device IN Endpoint-n Interrupt Register                               */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  EPD        :  1;               /*!< Endpoint Disabled Interrupt                                           */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
      __IO uint32_t  TIMEOUT    :  1;               /*!< a timeout condition on the USB for the last IN token on this
                                                         endpoint                                                              */
      __IO uint32_t  INTRWTFE   :  1;               /*!< IN Token Received When TxFIFO is Empty                                */
      __IO uint32_t  INTRWEPM   :  1;               /*!< IN Token Received with EP Mismatch                                    */
      __IO uint32_t  INEPNE     :  1;               /*!< IN Endpoint NAK Effective                                             */
      __I  uint32_t  TFE        :  1;               /*!< either half or completely empty depending on GAHBCFG.NPTxFEmpLvl      */
      __IO uint32_t  TFU        :  1;               /*!< Transmit FIFO Underrun                                                */
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
           uint32_t             :  2;
      __IO uint32_t  BE         :  1;               /*!< Babble Error                                                          */
      __IO uint32_t  NAK        :  1;               /*!< a NAK is transmitted                                                  */
      __IO uint32_t  NYET       :  1;               /*!< a NYET response is transmitted                                        */
    } DIEPINT2_b;                                   /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED51;

  union {
    __IO uint32_t  DIEPTSIZ2;                       /*!< Device IN Endpoint-n Transfer Size Register                           */

    struct {
      __IO uint32_t  SIZE       : 19;               /*!< Indicates the transfer size in bytes for endpoint 0                   */
      __IO uint32_t  PACKET_CNT : 10;               /*!< the total number of USB packets                                       */
      __IO uint32_t  MC         :  2;               /*!< the number of packets per microframe to periodic IN endpoints.
                                                         The number of packets must be fetched per non-periodic IN endpoints   */
    } DIEPTSIZ2_b;                                  /*!< BitSize                                                               */
  };
  __IO uint32_t  DIEPDMA2;                          /*!< Device IN Endpoint-n DMA Address Register                             */
  __IO uint16_t  DTXFSA2;                           /*!< Device IN Endpoint-n Transmit FIFO Space Avail Register               */
  __I  uint16_t  RESERVED52;
  __I  uint32_t  DIEPDMAB2;                         /*!< Device IN Endpoint-n DMA Buffer Address Register                      */

  union {
    __IO uint32_t  DIEPCTL3;                        /*!< Device IN Endpoint N Control Register                                 */

    struct {
      __IO uint32_t  MPS        : 11;               /*!< Indicates the maximum packet size of the associated endpoint          */
           uint32_t             :  4;
      __IO uint32_t  UAE        :  1;               /*!< Indicates whether this endpoint is active                             */
      __I  uint32_t  DPID       :  1;               /*!< Endpoint Data PID                                                     */
      __I  uint32_t  NAK        :  1;               /*!< The core is transmitting NAK handshakes on this endpoint if
                                                         set                                                                   */
      __IO uint32_t  EP_TYPE    :  2;               /*!< Indicates the transfer type selected.                                 */
           uint32_t             :  1;
      __IO uint32_t  STALL      :  1;               /*!< To non-control, non-isochronous IN endpoints, stall all tokens.
                                                         To control endpoints, response an ACK                                 */
      __IO uint32_t  TX_FIFO_NUM:  4;               /*!< TxFIFO Number                                                         */
      __O  uint32_t  CNAK       :  1;               /*!< A write to this bit clears the NAK bit for the endpoint               */
      __O  uint32_t  SNAK       :  1;               /*!< A write to this bit sets the NAK bit for the endpoint                 */
      __O  uint32_t  SET_D0_PID :  1;               /*!< Set DATA0 PID                                                         */
      __O  uint32_t  SET_D1_PID :  1;               /*!< Set DATA1 PID                                                         */
      __IO uint32_t  EPD        :  1;               /*!< The application sets this bit to stop transmitting data on an
                                                         endpoint even before the transfer for that endpoint is complete       */
      __IO uint32_t  EPE        :  1;               /*!< the descriptor structure and data buffer with data ready to
                                                         transmit is setup                                                     */
    } DIEPCTL3_b;                                   /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED53;

  union {
    __IO uint32_t  DIEPINT3;                        /*!< Device IN Endpoint-n Interrupt Register                               */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  EPD        :  1;               /*!< Endpoint Disabled Interrupt                                           */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
      __IO uint32_t  TIMEOUT    :  1;               /*!< a timeout condition on the USB for the last IN token on this
                                                         endpoint                                                              */
      __IO uint32_t  INTRWTFE   :  1;               /*!< IN Token Received When TxFIFO is Empty                                */
      __IO uint32_t  INTRWEPM   :  1;               /*!< IN Token Received with EP Mismatch                                    */
      __IO uint32_t  INEPNE     :  1;               /*!< IN Endpoint NAK Effective                                             */
      __I  uint32_t  TFE        :  1;               /*!< either half or completely empty depending on GAHBCFG.NPTxFEmpLvl      */
      __IO uint32_t  TFU        :  1;               /*!< Transmit FIFO Underrun                                                */
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
           uint32_t             :  2;
      __IO uint32_t  BE         :  1;               /*!< Babble Error                                                          */
      __IO uint32_t  NAK        :  1;               /*!< a NAK is transmitted                                                  */
      __IO uint32_t  NYET       :  1;               /*!< a NYET response is transmitted                                        */
    } DIEPINT3_b;                                   /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED54;

  union {
    __IO uint32_t  DIEPTSIZ3;                       /*!< Device IN Endpoint-n Transfer Size Register                           */

    struct {
      __IO uint32_t  SIZE       : 19;               /*!< Indicates the transfer size in bytes for endpoint 0                   */
      __IO uint32_t  PACKET_CNT : 10;               /*!< the total number of USB packets                                       */
      __IO uint32_t  MC         :  2;               /*!< the number of packets per microframe to periodic IN endpoints.
                                                         The number of packets must be fetched per non-periodic IN endpoints   */
    } DIEPTSIZ3_b;                                  /*!< BitSize                                                               */
  };
  __IO uint32_t  DIEPDMA3;                          /*!< Device IN Endpoint-n DMA Address Register                             */
  __IO uint16_t  DTXFSA3;                           /*!< Device IN Endpoint-n Transmit FIFO Space Avail Register               */
  __I  uint16_t  RESERVED55;
  __I  uint32_t  DIEPDMAB3;                         /*!< Device IN Endpoint-n DMA Buffer Address Register                      */

  union {
    __IO uint32_t  DIEPCTL4;                        /*!< Device IN Endpoint N Control Register                                 */

    struct {
      __IO uint32_t  MPS        : 11;               /*!< Indicates the maximum packet size of the associated endpoint          */
           uint32_t             :  4;
      __IO uint32_t  UAE        :  1;               /*!< Indicates whether this endpoint is active                             */
      __I  uint32_t  DPID       :  1;               /*!< Endpoint Data PID                                                     */
      __I  uint32_t  NAK        :  1;               /*!< The core is transmitting NAK handshakes on this endpoint if
                                                         set                                                                   */
      __IO uint32_t  EP_TYPE    :  2;               /*!< Indicates the transfer type selected.                                 */
           uint32_t             :  1;
      __IO uint32_t  STALL      :  1;               /*!< To non-control, non-isochronous IN endpoints, stall all tokens.
                                                         To control endpoints, response an ACK                                 */
      __IO uint32_t  TX_FIFO_NUM:  4;               /*!< TxFIFO Number                                                         */
      __O  uint32_t  CNAK       :  1;               /*!< A write to this bit clears the NAK bit for the endpoint               */
      __O  uint32_t  SNAK       :  1;               /*!< A write to this bit sets the NAK bit for the endpoint                 */
      __O  uint32_t  SET_D0_PID :  1;               /*!< Set DATA0 PID                                                         */
      __O  uint32_t  SET_D1_PID :  1;               /*!< Set DATA1 PID                                                         */
      __IO uint32_t  EPD        :  1;               /*!< The application sets this bit to stop transmitting data on an
                                                         endpoint even before the transfer for that endpoint is complete       */
      __IO uint32_t  EPE        :  1;               /*!< the descriptor structure and data buffer with data ready to
                                                         transmit is setup                                                     */
    } DIEPCTL4_b;                                   /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED56;

  union {
    __IO uint32_t  DIEPINT4;                        /*!< Device IN Endpoint-n Interrupt Register                               */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  EPD        :  1;               /*!< Endpoint Disabled Interrupt                                           */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
      __IO uint32_t  TIMEOUT    :  1;               /*!< a timeout condition on the USB for the last IN token on this
                                                         endpoint                                                              */
      __IO uint32_t  INTRWTFE   :  1;               /*!< IN Token Received When TxFIFO is Empty                                */
      __IO uint32_t  INTRWEPM   :  1;               /*!< IN Token Received with EP Mismatch                                    */
      __IO uint32_t  INEPNE     :  1;               /*!< IN Endpoint NAK Effective                                             */
      __I  uint32_t  TFE        :  1;               /*!< either half or completely empty depending on GAHBCFG.NPTxFEmpLvl      */
      __IO uint32_t  TFU        :  1;               /*!< Transmit FIFO Underrun                                                */
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
           uint32_t             :  2;
      __IO uint32_t  BE         :  1;               /*!< Babble Error                                                          */
      __IO uint32_t  NAK        :  1;               /*!< a NAK is transmitted                                                  */
      __IO uint32_t  NYET       :  1;               /*!< a NYET response is transmitted                                        */
    } DIEPINT4_b;                                   /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED57;

  union {
    __IO uint32_t  DIEPTSIZ4;                       /*!< Device IN Endpoint-n Transfer Size Register                           */

    struct {
      __IO uint32_t  SIZE       : 19;               /*!< Indicates the transfer size in bytes for endpoint 0                   */
      __IO uint32_t  PACKET_CNT : 10;               /*!< the total number of USB packets                                       */
      __IO uint32_t  MC         :  2;               /*!< the number of packets per microframe to periodic IN endpoints.
                                                         The number of packets must be fetched per non-periodic IN endpoints   */
    } DIEPTSIZ4_b;                                  /*!< BitSize                                                               */
  };
  __IO uint32_t  DIEPDMA4;                          /*!< Device IN Endpoint-n DMA Address Register                             */
  __IO uint16_t  DTXFSA4;                           /*!< Device IN Endpoint-n Transmit FIFO Space Avail Register               */
  __I  uint16_t  RESERVED58;
  __I  uint32_t  DIEPDMAB4;                         /*!< Device IN Endpoint-n DMA Buffer Address Register                      */

  union {
    __IO uint32_t  DIEPCTL5;                        /*!< Device IN Endpoint N Control Register                                 */

    struct {
      __IO uint32_t  MPS        : 11;               /*!< Indicates the maximum packet size of the associated endpoint          */
           uint32_t             :  4;
      __IO uint32_t  UAE        :  1;               /*!< Indicates whether this endpoint is active                             */
      __I  uint32_t  DPID       :  1;               /*!< Endpoint Data PID                                                     */
      __I  uint32_t  NAK        :  1;               /*!< The core is transmitting NAK handshakes on this endpoint if
                                                         set                                                                   */
      __IO uint32_t  EP_TYPE    :  2;               /*!< Indicates the transfer type selected.                                 */
           uint32_t             :  1;
      __IO uint32_t  STALL      :  1;               /*!< To non-control, non-isochronous IN endpoints, stall all tokens.
                                                         To control endpoints, response an ACK                                 */
      __IO uint32_t  TX_FIFO_NUM:  4;               /*!< TxFIFO Number                                                         */
      __O  uint32_t  CNAK       :  1;               /*!< A write to this bit clears the NAK bit for the endpoint               */
      __O  uint32_t  SNAK       :  1;               /*!< A write to this bit sets the NAK bit for the endpoint                 */
      __O  uint32_t  SET_D0_PID :  1;               /*!< Set DATA0 PID                                                         */
      __O  uint32_t  SET_D1_PID :  1;               /*!< Set DATA1 PID                                                         */
      __IO uint32_t  EPD        :  1;               /*!< The application sets this bit to stop transmitting data on an
                                                         endpoint even before the transfer for that endpoint is complete       */
      __IO uint32_t  EPE        :  1;               /*!< the descriptor structure and data buffer with data ready to
                                                         transmit is setup                                                     */
    } DIEPCTL5_b;                                   /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED59;

  union {
    __IO uint32_t  DIEPINT5;                        /*!< Device IN Endpoint-n Interrupt Register                               */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  EPD        :  1;               /*!< Endpoint Disabled Interrupt                                           */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
      __IO uint32_t  TIMEOUT    :  1;               /*!< a timeout condition on the USB for the last IN token on this
                                                         endpoint                                                              */
      __IO uint32_t  INTRWTFE   :  1;               /*!< IN Token Received When TxFIFO is Empty                                */
      __IO uint32_t  INTRWEPM   :  1;               /*!< IN Token Received with EP Mismatch                                    */
      __IO uint32_t  INEPNE     :  1;               /*!< IN Endpoint NAK Effective                                             */
      __I  uint32_t  TFE        :  1;               /*!< either half or completely empty depending on GAHBCFG.NPTxFEmpLvl      */
      __IO uint32_t  TFU        :  1;               /*!< Transmit FIFO Underrun                                                */
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
           uint32_t             :  2;
      __IO uint32_t  BE         :  1;               /*!< Babble Error                                                          */
      __IO uint32_t  NAK        :  1;               /*!< a NAK is transmitted                                                  */
      __IO uint32_t  NYET       :  1;               /*!< a NYET response is transmitted                                        */
    } DIEPINT5_b;                                   /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED60;

  union {
    __IO uint32_t  DIEPTSIZ5;                       /*!< Device IN Endpoint-n Transfer Size Register                           */

    struct {
      __IO uint32_t  SIZE       : 19;               /*!< Indicates the transfer size in bytes for endpoint 0                   */
      __IO uint32_t  PACKET_CNT : 10;               /*!< the total number of USB packets                                       */
      __IO uint32_t  MC         :  2;               /*!< the number of packets per microframe to periodic IN endpoints.
                                                         The number of packets must be fetched per non-periodic IN endpoints   */
    } DIEPTSIZ5_b;                                  /*!< BitSize                                                               */
  };
  __IO uint32_t  DIEPDMA5;                          /*!< Device IN Endpoint-n DMA Address Register                             */
  __IO uint16_t  DTXFSA5;                           /*!< Device IN Endpoint-n Transmit FIFO Space Avail Register               */
  __I  uint16_t  RESERVED61;
  __I  uint32_t  DIEPDMAB5;                         /*!< Device IN Endpoint-n DMA Buffer Address Register                      */

  union {
    __IO uint32_t  DIEPCTL6;                        /*!< Device IN Endpoint N Control Register                                 */

    struct {
      __IO uint32_t  MPS        : 11;               /*!< Indicates the maximum packet size of the associated endpoint          */
           uint32_t             :  4;
      __IO uint32_t  UAE        :  1;               /*!< Indicates whether this endpoint is active                             */
      __I  uint32_t  DPID       :  1;               /*!< Endpoint Data PID                                                     */
      __I  uint32_t  NAK        :  1;               /*!< The core is transmitting NAK handshakes on this endpoint if
                                                         set                                                                   */
      __IO uint32_t  EP_TYPE    :  2;               /*!< Indicates the transfer type selected.                                 */
           uint32_t             :  1;
      __IO uint32_t  STALL      :  1;               /*!< To non-control, non-isochronous IN endpoints, stall all tokens.
                                                         To control endpoints, response an ACK                                 */
      __IO uint32_t  TX_FIFO_NUM:  4;               /*!< TxFIFO Number                                                         */
      __O  uint32_t  CNAK       :  1;               /*!< A write to this bit clears the NAK bit for the endpoint               */
      __O  uint32_t  SNAK       :  1;               /*!< A write to this bit sets the NAK bit for the endpoint                 */
      __O  uint32_t  SET_D0_PID :  1;               /*!< Set DATA0 PID                                                         */
      __O  uint32_t  SET_D1_PID :  1;               /*!< Set DATA1 PID                                                         */
      __IO uint32_t  EPD        :  1;               /*!< The application sets this bit to stop transmitting data on an
                                                         endpoint even before the transfer for that endpoint is complete       */
      __IO uint32_t  EPE        :  1;               /*!< the descriptor structure and data buffer with data ready to
                                                         transmit is setup                                                     */
    } DIEPCTL6_b;                                   /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED62;

  union {
    __IO uint32_t  DIEPINT6;                        /*!< Device IN Endpoint-n Interrupt Register                               */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  EPD        :  1;               /*!< Endpoint Disabled Interrupt                                           */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
      __IO uint32_t  TIMEOUT    :  1;               /*!< a timeout condition on the USB for the last IN token on this
                                                         endpoint                                                              */
      __IO uint32_t  INTRWTFE   :  1;               /*!< IN Token Received When TxFIFO is Empty                                */
      __IO uint32_t  INTRWEPM   :  1;               /*!< IN Token Received with EP Mismatch                                    */
      __IO uint32_t  INEPNE     :  1;               /*!< IN Endpoint NAK Effective                                             */
      __I  uint32_t  TFE        :  1;               /*!< either half or completely empty depending on GAHBCFG.NPTxFEmpLvl      */
      __IO uint32_t  TFU        :  1;               /*!< Transmit FIFO Underrun                                                */
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
           uint32_t             :  2;
      __IO uint32_t  BE         :  1;               /*!< Babble Error                                                          */
      __IO uint32_t  NAK        :  1;               /*!< a NAK is transmitted                                                  */
      __IO uint32_t  NYET       :  1;               /*!< a NYET response is transmitted                                        */
    } DIEPINT6_b;                                   /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED63;

  union {
    __IO uint32_t  DIEPTSIZ6;                       /*!< Device IN Endpoint-n Transfer Size Register                           */

    struct {
      __IO uint32_t  SIZE       : 19;               /*!< Indicates the transfer size in bytes for endpoint 0                   */
      __IO uint32_t  PACKET_CNT : 10;               /*!< the total number of USB packets                                       */
      __IO uint32_t  MC         :  2;               /*!< the number of packets per microframe to periodic IN endpoints.
                                                         The number of packets must be fetched per non-periodic IN endpoints   */
    } DIEPTSIZ6_b;                                  /*!< BitSize                                                               */
  };
  __IO uint32_t  DIEPDMA6;                          /*!< Device IN Endpoint-n DMA Address Register                             */
  __IO uint16_t  DTXFSA6;                           /*!< Device IN Endpoint-n Transmit FIFO Space Avail Register               */
  __I  uint16_t  RESERVED64;
  __I  uint32_t  DIEPDMAB6;                         /*!< Device IN Endpoint-n DMA Buffer Address Register                      */

  union {
    __IO uint32_t  DIEPCTL7;                        /*!< Device IN Endpoint N Control Register                                 */

    struct {
      __IO uint32_t  MPS        : 11;               /*!< Indicates the maximum packet size of the associated endpoint          */
           uint32_t             :  4;
      __IO uint32_t  UAE        :  1;               /*!< Indicates whether this endpoint is active                             */
      __I  uint32_t  DPID       :  1;               /*!< Endpoint Data PID                                                     */
      __I  uint32_t  NAK        :  1;               /*!< The core is transmitting NAK handshakes on this endpoint if
                                                         set                                                                   */
      __IO uint32_t  EP_TYPE    :  2;               /*!< Indicates the transfer type selected.                                 */
           uint32_t             :  1;
      __IO uint32_t  STALL      :  1;               /*!< To non-control, non-isochronous IN endpoints, stall all tokens.
                                                         To control endpoints, response an ACK                                 */
      __IO uint32_t  TX_FIFO_NUM:  4;               /*!< TxFIFO Number                                                         */
      __O  uint32_t  CNAK       :  1;               /*!< A write to this bit clears the NAK bit for the endpoint               */
      __O  uint32_t  SNAK       :  1;               /*!< A write to this bit sets the NAK bit for the endpoint                 */
      __O  uint32_t  SET_D0_PID :  1;               /*!< Set DATA0 PID                                                         */
      __O  uint32_t  SET_D1_PID :  1;               /*!< Set DATA1 PID                                                         */
      __IO uint32_t  EPD        :  1;               /*!< The application sets this bit to stop transmitting data on an
                                                         endpoint even before the transfer for that endpoint is complete       */
      __IO uint32_t  EPE        :  1;               /*!< the descriptor structure and data buffer with data ready to
                                                         transmit is setup                                                     */
    } DIEPCTL7_b;                                   /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED65;

  union {
    __IO uint32_t  DIEPINT7;                        /*!< Device IN Endpoint-n Interrupt Register                               */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  EPD        :  1;               /*!< Endpoint Disabled Interrupt                                           */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
      __IO uint32_t  TIMEOUT    :  1;               /*!< a timeout condition on the USB for the last IN token on this
                                                         endpoint                                                              */
      __IO uint32_t  INTRWTFE   :  1;               /*!< IN Token Received When TxFIFO is Empty                                */
      __IO uint32_t  INTRWEPM   :  1;               /*!< IN Token Received with EP Mismatch                                    */
      __IO uint32_t  INEPNE     :  1;               /*!< IN Endpoint NAK Effective                                             */
      __I  uint32_t  TFE        :  1;               /*!< either half or completely empty depending on GAHBCFG.NPTxFEmpLvl      */
      __IO uint32_t  TFU        :  1;               /*!< Transmit FIFO Underrun                                                */
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
           uint32_t             :  2;
      __IO uint32_t  BE         :  1;               /*!< Babble Error                                                          */
      __IO uint32_t  NAK        :  1;               /*!< a NAK is transmitted                                                  */
      __IO uint32_t  NYET       :  1;               /*!< a NYET response is transmitted                                        */
    } DIEPINT7_b;                                   /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED66;

  union {
    __IO uint32_t  DIEPTSIZ7;                       /*!< Device IN Endpoint-n Transfer Size Register                           */

    struct {
      __IO uint32_t  SIZE       : 19;               /*!< Indicates the transfer size in bytes for endpoint 0                   */
      __IO uint32_t  PACKET_CNT : 10;               /*!< the total number of USB packets                                       */
      __IO uint32_t  MC         :  2;               /*!< the number of packets per microframe to periodic IN endpoints.
                                                         The number of packets must be fetched per non-periodic IN endpoints   */
    } DIEPTSIZ7_b;                                  /*!< BitSize                                                               */
  };
  __IO uint32_t  DIEPDMA7;                          /*!< Device IN Endpoint-n DMA Address Register                             */
  __IO uint16_t  DTXFSA7;                           /*!< Device IN Endpoint-n Transmit FIFO Space Avail Register               */
  __I  uint16_t  RESERVED67;
  __I  uint32_t  DIEPDMAB7;                         /*!< Device IN Endpoint-n DMA Buffer Address Register                      */

  union {
    __IO uint32_t  DIEPCTL8;                        /*!< Device IN Endpoint N Control Register                                 */

    struct {
      __IO uint32_t  MPS        : 11;               /*!< Indicates the maximum packet size of the associated endpoint          */
           uint32_t             :  4;
      __IO uint32_t  UAE        :  1;               /*!< Indicates whether this endpoint is active                             */
      __I  uint32_t  DPID       :  1;               /*!< Endpoint Data PID                                                     */
      __I  uint32_t  NAK        :  1;               /*!< The core is transmitting NAK handshakes on this endpoint if
                                                         set                                                                   */
      __IO uint32_t  EP_TYPE    :  2;               /*!< Indicates the transfer type selected.                                 */
           uint32_t             :  1;
      __IO uint32_t  STALL      :  1;               /*!< To non-control, non-isochronous IN endpoints, stall all tokens.
                                                         To control endpoints, response an ACK                                 */
      __IO uint32_t  TX_FIFO_NUM:  4;               /*!< TxFIFO Number                                                         */
      __O  uint32_t  CNAK       :  1;               /*!< A write to this bit clears the NAK bit for the endpoint               */
      __O  uint32_t  SNAK       :  1;               /*!< A write to this bit sets the NAK bit for the endpoint                 */
      __O  uint32_t  SET_D0_PID :  1;               /*!< Set DATA0 PID                                                         */
      __O  uint32_t  SET_D1_PID :  1;               /*!< Set DATA1 PID                                                         */
      __IO uint32_t  EPD        :  1;               /*!< The application sets this bit to stop transmitting data on an
                                                         endpoint even before the transfer for that endpoint is complete       */
      __IO uint32_t  EPE        :  1;               /*!< the descriptor structure and data buffer with data ready to
                                                         transmit is setup                                                     */
    } DIEPCTL8_b;                                   /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED68;

  union {
    __IO uint32_t  DIEPINT8;                        /*!< Device IN Endpoint-n Interrupt Register                               */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  EPD        :  1;               /*!< Endpoint Disabled Interrupt                                           */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
      __IO uint32_t  TIMEOUT    :  1;               /*!< a timeout condition on the USB for the last IN token on this
                                                         endpoint                                                              */
      __IO uint32_t  INTRWTFE   :  1;               /*!< IN Token Received When TxFIFO is Empty                                */
      __IO uint32_t  INTRWEPM   :  1;               /*!< IN Token Received with EP Mismatch                                    */
      __IO uint32_t  INEPNE     :  1;               /*!< IN Endpoint NAK Effective                                             */
      __I  uint32_t  TFE        :  1;               /*!< either half or completely empty depending on GAHBCFG.NPTxFEmpLvl      */
      __IO uint32_t  TFU        :  1;               /*!< Transmit FIFO Underrun                                                */
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
           uint32_t             :  2;
      __IO uint32_t  BE         :  1;               /*!< Babble Error                                                          */
      __IO uint32_t  NAK        :  1;               /*!< a NAK is transmitted                                                  */
      __IO uint32_t  NYET       :  1;               /*!< a NYET response is transmitted                                        */
    } DIEPINT8_b;                                   /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED69;

  union {
    __IO uint32_t  DIEPTSIZ8;                       /*!< Device IN Endpoint-n Transfer Size Register                           */

    struct {
      __IO uint32_t  SIZE       : 19;               /*!< Indicates the transfer size in bytes for endpoint 0                   */
      __IO uint32_t  PACKET_CNT : 10;               /*!< the total number of USB packets                                       */
      __IO uint32_t  MC         :  2;               /*!< the number of packets per microframe to periodic IN endpoints.
                                                         The number of packets must be fetched per non-periodic IN endpoints   */
    } DIEPTSIZ8_b;                                  /*!< BitSize                                                               */
  };
  __IO uint32_t  DIEPDMA8;                          /*!< Device IN Endpoint-n DMA Address Register                             */
  __IO uint16_t  DTXFSA8;                           /*!< Device IN Endpoint-n Transmit FIFO Space Avail Register               */
  __I  uint16_t  RESERVED70;
  __I  uint32_t  DIEPDMAB8;                         /*!< Device IN Endpoint-n DMA Buffer Address Register                      */

  union {
    __IO uint32_t  DIEPCTL9;                        /*!< Device IN Endpoint N Control Register                                 */

    struct {
      __IO uint32_t  MPS        : 11;               /*!< Indicates the maximum packet size of the associated endpoint          */
           uint32_t             :  4;
      __IO uint32_t  UAE        :  1;               /*!< Indicates whether this endpoint is active                             */
      __I  uint32_t  DPID       :  1;               /*!< Endpoint Data PID                                                     */
      __I  uint32_t  NAK        :  1;               /*!< The core is transmitting NAK handshakes on this endpoint if
                                                         set                                                                   */
      __IO uint32_t  EP_TYPE    :  2;               /*!< Indicates the transfer type selected.                                 */
           uint32_t             :  1;
      __IO uint32_t  STALL      :  1;               /*!< To non-control, non-isochronous IN endpoints, stall all tokens.
                                                         To control endpoints, response an ACK                                 */
      __IO uint32_t  TX_FIFO_NUM:  4;               /*!< TxFIFO Number                                                         */
      __O  uint32_t  CNAK       :  1;               /*!< A write to this bit clears the NAK bit for the endpoint               */
      __O  uint32_t  SNAK       :  1;               /*!< A write to this bit sets the NAK bit for the endpoint                 */
      __O  uint32_t  SET_D0_PID :  1;               /*!< Set DATA0 PID                                                         */
      __O  uint32_t  SET_D1_PID :  1;               /*!< Set DATA1 PID                                                         */
      __IO uint32_t  EPD        :  1;               /*!< The application sets this bit to stop transmitting data on an
                                                         endpoint even before the transfer for that endpoint is complete       */
      __IO uint32_t  EPE        :  1;               /*!< the descriptor structure and data buffer with data ready to
                                                         transmit is setup                                                     */
    } DIEPCTL9_b;                                   /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED71;

  union {
    __IO uint32_t  DIEPINT9;                        /*!< Device IN Endpoint-n Interrupt Register                               */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  EPD        :  1;               /*!< Endpoint Disabled Interrupt                                           */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
      __IO uint32_t  TIMEOUT    :  1;               /*!< a timeout condition on the USB for the last IN token on this
                                                         endpoint                                                              */
      __IO uint32_t  INTRWTFE   :  1;               /*!< IN Token Received When TxFIFO is Empty                                */
      __IO uint32_t  INTRWEPM   :  1;               /*!< IN Token Received with EP Mismatch                                    */
      __IO uint32_t  INEPNE     :  1;               /*!< IN Endpoint NAK Effective                                             */
      __I  uint32_t  TFE        :  1;               /*!< either half or completely empty depending on GAHBCFG.NPTxFEmpLvl      */
      __IO uint32_t  TFU        :  1;               /*!< Transmit FIFO Underrun                                                */
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
           uint32_t             :  2;
      __IO uint32_t  BE         :  1;               /*!< Babble Error                                                          */
      __IO uint32_t  NAK        :  1;               /*!< a NAK is transmitted                                                  */
      __IO uint32_t  NYET       :  1;               /*!< a NYET response is transmitted                                        */
    } DIEPINT9_b;                                   /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED72;

  union {
    __IO uint32_t  DIEPTSIZ9;                       /*!< Device IN Endpoint-n Transfer Size Register                           */

    struct {
      __IO uint32_t  SIZE       : 19;               /*!< Indicates the transfer size in bytes for endpoint 0                   */
      __IO uint32_t  PACKET_CNT : 10;               /*!< the total number of USB packets                                       */
      __IO uint32_t  MC         :  2;               /*!< the number of packets per microframe to periodic IN endpoints.
                                                         The number of packets must be fetched per non-periodic IN endpoints   */
    } DIEPTSIZ9_b;                                  /*!< BitSize                                                               */
  };
  __IO uint32_t  DIEPDMA9;                          /*!< Device IN Endpoint-n DMA Address Register                             */
  __IO uint16_t  DTXFSA9;                           /*!< Device IN Endpoint-n Transmit FIFO Space Avail Register               */
  __I  uint16_t  RESERVED73;
  __I  uint32_t  DIEPDMAB9;                         /*!< Device IN Endpoint-n DMA Buffer Address Register                      */

  union {
    __IO uint32_t  DIEPCTL10;                       /*!< Device IN Endpoint N Control Register                                 */

    struct {
      __IO uint32_t  MPS        : 11;               /*!< Indicates the maximum packet size of the associated endpoint          */
           uint32_t             :  4;
      __IO uint32_t  UAE        :  1;               /*!< Indicates whether this endpoint is active                             */
      __I  uint32_t  DPID       :  1;               /*!< Endpoint Data PID                                                     */
      __I  uint32_t  NAK        :  1;               /*!< The core is transmitting NAK handshakes on this endpoint if
                                                         set                                                                   */
      __IO uint32_t  EP_TYPE    :  2;               /*!< Indicates the transfer type selected.                                 */
           uint32_t             :  1;
      __IO uint32_t  STALL      :  1;               /*!< To non-control, non-isochronous IN endpoints, stall all tokens.
                                                         To control endpoints, response an ACK                                 */
      __IO uint32_t  TX_FIFO_NUM:  4;               /*!< TxFIFO Number                                                         */
      __O  uint32_t  CNAK       :  1;               /*!< A write to this bit clears the NAK bit for the endpoint               */
      __O  uint32_t  SNAK       :  1;               /*!< A write to this bit sets the NAK bit for the endpoint                 */
      __O  uint32_t  SET_D0_PID :  1;               /*!< Set DATA0 PID                                                         */
      __O  uint32_t  SET_D1_PID :  1;               /*!< Set DATA1 PID                                                         */
      __IO uint32_t  EPD        :  1;               /*!< The application sets this bit to stop transmitting data on an
                                                         endpoint even before the transfer for that endpoint is complete       */
      __IO uint32_t  EPE        :  1;               /*!< the descriptor structure and data buffer with data ready to
                                                         transmit is setup                                                     */
    } DIEPCTL10_b;                                  /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED74;

  union {
    __IO uint32_t  DIEPINT10;                       /*!< Device IN Endpoint-n Interrupt Register                               */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  EPD        :  1;               /*!< Endpoint Disabled Interrupt                                           */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
      __IO uint32_t  TIMEOUT    :  1;               /*!< a timeout condition on the USB for the last IN token on this
                                                         endpoint                                                              */
      __IO uint32_t  INTRWTFE   :  1;               /*!< IN Token Received When TxFIFO is Empty                                */
      __IO uint32_t  INTRWEPM   :  1;               /*!< IN Token Received with EP Mismatch                                    */
      __IO uint32_t  INEPNE     :  1;               /*!< IN Endpoint NAK Effective                                             */
      __I  uint32_t  TFE        :  1;               /*!< either half or completely empty depending on GAHBCFG.NPTxFEmpLvl      */
      __IO uint32_t  TFU        :  1;               /*!< Transmit FIFO Underrun                                                */
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
           uint32_t             :  2;
      __IO uint32_t  BE         :  1;               /*!< Babble Error                                                          */
      __IO uint32_t  NAK        :  1;               /*!< a NAK is transmitted                                                  */
      __IO uint32_t  NYET       :  1;               /*!< a NYET response is transmitted                                        */
    } DIEPINT10_b;                                  /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED75;

  union {
    __IO uint32_t  DIEPTSIZ10;                      /*!< Device IN Endpoint-n Transfer Size Register                           */

    struct {
      __IO uint32_t  SIZE       : 19;               /*!< Indicates the transfer size in bytes for endpoint 0                   */
      __IO uint32_t  PACKET_CNT : 10;               /*!< the total number of USB packets                                       */
      __IO uint32_t  MC         :  2;               /*!< the number of packets per microframe to periodic IN endpoints.
                                                         The number of packets must be fetched per non-periodic IN endpoints   */
    } DIEPTSIZ10_b;                                 /*!< BitSize                                                               */
  };
  __IO uint32_t  DIEPDMA10;                         /*!< Device IN Endpoint-n DMA Address Register                             */
  __IO uint16_t  DTXFSA10;                          /*!< Device IN Endpoint-n Transmit FIFO Space Avail Register               */
  __I  uint16_t  RESERVED76;
  __I  uint32_t  DIEPDMAB10;                        /*!< Device IN Endpoint-n DMA Buffer Address Register                      */

  union {
    __IO uint32_t  DIEPCTL11;                       /*!< Device IN Endpoint N Control Register                                 */

    struct {
      __IO uint32_t  MPS        : 11;               /*!< Indicates the maximum packet size of the associated endpoint          */
           uint32_t             :  4;
      __IO uint32_t  UAE        :  1;               /*!< Indicates whether this endpoint is active                             */
      __I  uint32_t  DPID       :  1;               /*!< Endpoint Data PID                                                     */
      __I  uint32_t  NAK        :  1;               /*!< The core is transmitting NAK handshakes on this endpoint if
                                                         set                                                                   */
      __IO uint32_t  EP_TYPE    :  2;               /*!< Indicates the transfer type selected.                                 */
           uint32_t             :  1;
      __IO uint32_t  STALL      :  1;               /*!< To non-control, non-isochronous IN endpoints, stall all tokens.
                                                         To control endpoints, response an ACK                                 */
      __IO uint32_t  TX_FIFO_NUM:  4;               /*!< TxFIFO Number                                                         */
      __O  uint32_t  CNAK       :  1;               /*!< A write to this bit clears the NAK bit for the endpoint               */
      __O  uint32_t  SNAK       :  1;               /*!< A write to this bit sets the NAK bit for the endpoint                 */
      __O  uint32_t  SET_D0_PID :  1;               /*!< Set DATA0 PID                                                         */
      __O  uint32_t  SET_D1_PID :  1;               /*!< Set DATA1 PID                                                         */
      __IO uint32_t  EPD        :  1;               /*!< The application sets this bit to stop transmitting data on an
                                                         endpoint even before the transfer for that endpoint is complete       */
      __IO uint32_t  EPE        :  1;               /*!< the descriptor structure and data buffer with data ready to
                                                         transmit is setup                                                     */
    } DIEPCTL11_b;                                  /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED77;

  union {
    __IO uint32_t  DIEPINT11;                       /*!< Device IN Endpoint-n Interrupt Register                               */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  EPD        :  1;               /*!< Endpoint Disabled Interrupt                                           */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
      __IO uint32_t  TIMEOUT    :  1;               /*!< a timeout condition on the USB for the last IN token on this
                                                         endpoint                                                              */
      __IO uint32_t  INTRWTFE   :  1;               /*!< IN Token Received When TxFIFO is Empty                                */
      __IO uint32_t  INTRWEPM   :  1;               /*!< IN Token Received with EP Mismatch                                    */
      __IO uint32_t  INEPNE     :  1;               /*!< IN Endpoint NAK Effective                                             */
      __I  uint32_t  TFE        :  1;               /*!< either half or completely empty depending on GAHBCFG.NPTxFEmpLvl      */
      __IO uint32_t  TFU        :  1;               /*!< Transmit FIFO Underrun                                                */
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
           uint32_t             :  2;
      __IO uint32_t  BE         :  1;               /*!< Babble Error                                                          */
      __IO uint32_t  NAK        :  1;               /*!< a NAK is transmitted                                                  */
      __IO uint32_t  NYET       :  1;               /*!< a NYET response is transmitted                                        */
    } DIEPINT11_b;                                  /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED78;

  union {
    __IO uint32_t  DIEPTSIZ11;                      /*!< Device IN Endpoint-n Transfer Size Register                           */

    struct {
      __IO uint32_t  SIZE       : 19;               /*!< Indicates the transfer size in bytes for endpoint 0                   */
      __IO uint32_t  PACKET_CNT : 10;               /*!< the total number of USB packets                                       */
      __IO uint32_t  MC         :  2;               /*!< the number of packets per microframe to periodic IN endpoints.
                                                         The number of packets must be fetched per non-periodic IN endpoints   */
    } DIEPTSIZ11_b;                                 /*!< BitSize                                                               */
  };
  __IO uint32_t  DIEPDMA11;                         /*!< Device IN Endpoint-n DMA Address Register                             */
  __IO uint16_t  DTXFSA11;                          /*!< Device IN Endpoint-n Transmit FIFO Space Avail Register               */
  __I  uint16_t  RESERVED79;
  __I  uint32_t  DIEPDMAB11;                        /*!< Device IN Endpoint-n DMA Buffer Address Register                      */

  union {
    __IO uint32_t  DIEPCTL12;                       /*!< Device IN Endpoint N Control Register                                 */

    struct {
      __IO uint32_t  MPS        : 11;               /*!< Indicates the maximum packet size of the associated endpoint          */
           uint32_t             :  4;
      __IO uint32_t  UAE        :  1;               /*!< Indicates whether this endpoint is active                             */
      __I  uint32_t  DPID       :  1;               /*!< Endpoint Data PID                                                     */
      __I  uint32_t  NAK        :  1;               /*!< The core is transmitting NAK handshakes on this endpoint if
                                                         set                                                                   */
      __IO uint32_t  EP_TYPE    :  2;               /*!< Indicates the transfer type selected.                                 */
           uint32_t             :  1;
      __IO uint32_t  STALL      :  1;               /*!< To non-control, non-isochronous IN endpoints, stall all tokens.
                                                         To control endpoints, response an ACK                                 */
      __IO uint32_t  TX_FIFO_NUM:  4;               /*!< TxFIFO Number                                                         */
      __O  uint32_t  CNAK       :  1;               /*!< A write to this bit clears the NAK bit for the endpoint               */
      __O  uint32_t  SNAK       :  1;               /*!< A write to this bit sets the NAK bit for the endpoint                 */
      __O  uint32_t  SET_D0_PID :  1;               /*!< Set DATA0 PID                                                         */
      __O  uint32_t  SET_D1_PID :  1;               /*!< Set DATA1 PID                                                         */
      __IO uint32_t  EPD        :  1;               /*!< The application sets this bit to stop transmitting data on an
                                                         endpoint even before the transfer for that endpoint is complete       */
      __IO uint32_t  EPE        :  1;               /*!< the descriptor structure and data buffer with data ready to
                                                         transmit is setup                                                     */
    } DIEPCTL12_b;                                  /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED80;

  union {
    __IO uint32_t  DIEPINT12;                       /*!< Device IN Endpoint-n Interrupt Register                               */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  EPD        :  1;               /*!< Endpoint Disabled Interrupt                                           */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
      __IO uint32_t  TIMEOUT    :  1;               /*!< a timeout condition on the USB for the last IN token on this
                                                         endpoint                                                              */
      __IO uint32_t  INTRWTFE   :  1;               /*!< IN Token Received When TxFIFO is Empty                                */
      __IO uint32_t  INTRWEPM   :  1;               /*!< IN Token Received with EP Mismatch                                    */
      __IO uint32_t  INEPNE     :  1;               /*!< IN Endpoint NAK Effective                                             */
      __I  uint32_t  TFE        :  1;               /*!< either half or completely empty depending on GAHBCFG.NPTxFEmpLvl      */
      __IO uint32_t  TFU        :  1;               /*!< Transmit FIFO Underrun                                                */
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
           uint32_t             :  2;
      __IO uint32_t  BE         :  1;               /*!< Babble Error                                                          */
      __IO uint32_t  NAK        :  1;               /*!< a NAK is transmitted                                                  */
      __IO uint32_t  NYET       :  1;               /*!< a NYET response is transmitted                                        */
    } DIEPINT12_b;                                  /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED81;

  union {
    __IO uint32_t  DIEPTSIZ12;                      /*!< Device IN Endpoint-n Transfer Size Register                           */

    struct {
      __IO uint32_t  SIZE       : 19;               /*!< Indicates the transfer size in bytes for endpoint 0                   */
      __IO uint32_t  PACKET_CNT : 10;               /*!< the total number of USB packets                                       */
      __IO uint32_t  MC         :  2;               /*!< the number of packets per microframe to periodic IN endpoints.
                                                         The number of packets must be fetched per non-periodic IN endpoints   */
    } DIEPTSIZ12_b;                                 /*!< BitSize                                                               */
  };
  __IO uint32_t  DIEPDMA12;                         /*!< Device IN Endpoint-n DMA Address Register                             */
  __IO uint16_t  DTXFSA12;                          /*!< Device IN Endpoint-n Transmit FIFO Space Avail Register               */
  __I  uint16_t  RESERVED82;
  __I  uint32_t  DIEPDMAB12;                        /*!< Device IN Endpoint-n DMA Buffer Address Register                      */

  union {
    __IO uint32_t  DIEPCTL13;                       /*!< Device IN Endpoint N Control Register                                 */

    struct {
      __IO uint32_t  MPS        : 11;               /*!< Indicates the maximum packet size of the associated endpoint          */
           uint32_t             :  4;
      __IO uint32_t  UAE        :  1;               /*!< Indicates whether this endpoint is active                             */
      __I  uint32_t  DPID       :  1;               /*!< Endpoint Data PID                                                     */
      __I  uint32_t  NAK        :  1;               /*!< The core is transmitting NAK handshakes on this endpoint if
                                                         set                                                                   */
      __IO uint32_t  EP_TYPE    :  2;               /*!< Indicates the transfer type selected.                                 */
           uint32_t             :  1;
      __IO uint32_t  STALL      :  1;               /*!< To non-control, non-isochronous IN endpoints, stall all tokens.
                                                         To control endpoints, response an ACK                                 */
      __IO uint32_t  TX_FIFO_NUM:  4;               /*!< TxFIFO Number                                                         */
      __O  uint32_t  CNAK       :  1;               /*!< A write to this bit clears the NAK bit for the endpoint               */
      __O  uint32_t  SNAK       :  1;               /*!< A write to this bit sets the NAK bit for the endpoint                 */
      __O  uint32_t  SET_D0_PID :  1;               /*!< Set DATA0 PID                                                         */
      __O  uint32_t  SET_D1_PID :  1;               /*!< Set DATA1 PID                                                         */
      __IO uint32_t  EPD        :  1;               /*!< The application sets this bit to stop transmitting data on an
                                                         endpoint even before the transfer for that endpoint is complete       */
      __IO uint32_t  EPE        :  1;               /*!< the descriptor structure and data buffer with data ready to
                                                         transmit is setup                                                     */
    } DIEPCTL13_b;                                  /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED83;

  union {
    __IO uint32_t  DIEPINT13;                       /*!< Device IN Endpoint-n Interrupt Register                               */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  EPD        :  1;               /*!< Endpoint Disabled Interrupt                                           */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
      __IO uint32_t  TIMEOUT    :  1;               /*!< a timeout condition on the USB for the last IN token on this
                                                         endpoint                                                              */
      __IO uint32_t  INTRWTFE   :  1;               /*!< IN Token Received When TxFIFO is Empty                                */
      __IO uint32_t  INTRWEPM   :  1;               /*!< IN Token Received with EP Mismatch                                    */
      __IO uint32_t  INEPNE     :  1;               /*!< IN Endpoint NAK Effective                                             */
      __I  uint32_t  TFE        :  1;               /*!< either half or completely empty depending on GAHBCFG.NPTxFEmpLvl      */
      __IO uint32_t  TFU        :  1;               /*!< Transmit FIFO Underrun                                                */
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
           uint32_t             :  2;
      __IO uint32_t  BE         :  1;               /*!< Babble Error                                                          */
      __IO uint32_t  NAK        :  1;               /*!< a NAK is transmitted                                                  */
      __IO uint32_t  NYET       :  1;               /*!< a NYET response is transmitted                                        */
    } DIEPINT13_b;                                  /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED84;

  union {
    __IO uint32_t  DIEPTSIZ13;                      /*!< Device IN Endpoint-n Transfer Size Register                           */

    struct {
      __IO uint32_t  SIZE       : 19;               /*!< Indicates the transfer size in bytes for endpoint 0                   */
      __IO uint32_t  PACKET_CNT : 10;               /*!< the total number of USB packets                                       */
      __IO uint32_t  MC         :  2;               /*!< the number of packets per microframe to periodic IN endpoints.
                                                         The number of packets must be fetched per non-periodic IN endpoints   */
    } DIEPTSIZ13_b;                                 /*!< BitSize                                                               */
  };
  __IO uint32_t  DIEPDMA13;                         /*!< Device IN Endpoint-n DMA Address Register                             */
  __IO uint16_t  DTXFSA13;                          /*!< Device IN Endpoint-n Transmit FIFO Space Avail Register               */
  __I  uint16_t  RESERVED85;
  __I  uint32_t  DIEPDMAB13;                        /*!< Device IN Endpoint-n DMA Buffer Address Register                      */

  union {
    __IO uint32_t  DIEPCTL14;                       /*!< Device IN Endpoint N Control Register                                 */

    struct {
      __IO uint32_t  MPS        : 11;               /*!< Indicates the maximum packet size of the associated endpoint          */
           uint32_t             :  4;
      __IO uint32_t  UAE        :  1;               /*!< Indicates whether this endpoint is active                             */
      __I  uint32_t  DPID       :  1;               /*!< Endpoint Data PID                                                     */
      __I  uint32_t  NAK        :  1;               /*!< The core is transmitting NAK handshakes on this endpoint if
                                                         set                                                                   */
      __IO uint32_t  EP_TYPE    :  2;               /*!< Indicates the transfer type selected.                                 */
           uint32_t             :  1;
      __IO uint32_t  STALL      :  1;               /*!< To non-control, non-isochronous IN endpoints, stall all tokens.
                                                         To control endpoints, response an ACK                                 */
      __IO uint32_t  TX_FIFO_NUM:  4;               /*!< TxFIFO Number                                                         */
      __O  uint32_t  CNAK       :  1;               /*!< A write to this bit clears the NAK bit for the endpoint               */
      __O  uint32_t  SNAK       :  1;               /*!< A write to this bit sets the NAK bit for the endpoint                 */
      __O  uint32_t  SET_D0_PID :  1;               /*!< Set DATA0 PID                                                         */
      __O  uint32_t  SET_D1_PID :  1;               /*!< Set DATA1 PID                                                         */
      __IO uint32_t  EPD        :  1;               /*!< The application sets this bit to stop transmitting data on an
                                                         endpoint even before the transfer for that endpoint is complete       */
      __IO uint32_t  EPE        :  1;               /*!< the descriptor structure and data buffer with data ready to
                                                         transmit is setup                                                     */
    } DIEPCTL14_b;                                  /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED86;

  union {
    __IO uint32_t  DIEPINT14;                       /*!< Device IN Endpoint-n Interrupt Register                               */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  EPD        :  1;               /*!< Endpoint Disabled Interrupt                                           */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
      __IO uint32_t  TIMEOUT    :  1;               /*!< a timeout condition on the USB for the last IN token on this
                                                         endpoint                                                              */
      __IO uint32_t  INTRWTFE   :  1;               /*!< IN Token Received When TxFIFO is Empty                                */
      __IO uint32_t  INTRWEPM   :  1;               /*!< IN Token Received with EP Mismatch                                    */
      __IO uint32_t  INEPNE     :  1;               /*!< IN Endpoint NAK Effective                                             */
      __I  uint32_t  TFE        :  1;               /*!< either half or completely empty depending on GAHBCFG.NPTxFEmpLvl      */
      __IO uint32_t  TFU        :  1;               /*!< Transmit FIFO Underrun                                                */
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
           uint32_t             :  2;
      __IO uint32_t  BE         :  1;               /*!< Babble Error                                                          */
      __IO uint32_t  NAK        :  1;               /*!< a NAK is transmitted                                                  */
      __IO uint32_t  NYET       :  1;               /*!< a NYET response is transmitted                                        */
    } DIEPINT14_b;                                  /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED87;

  union {
    __IO uint32_t  DIEPTSIZ14;                      /*!< Device IN Endpoint-n Transfer Size Register                           */

    struct {
      __IO uint32_t  SIZE       : 19;               /*!< Indicates the transfer size in bytes for endpoint 0                   */
      __IO uint32_t  PACKET_CNT : 10;               /*!< the total number of USB packets                                       */
      __IO uint32_t  MC         :  2;               /*!< the number of packets per microframe to periodic IN endpoints.
                                                         The number of packets must be fetched per non-periodic IN endpoints   */
    } DIEPTSIZ14_b;                                 /*!< BitSize                                                               */
  };
  __IO uint32_t  DIEPDMA14;                         /*!< Device IN Endpoint-n DMA Address Register                             */
  __IO uint16_t  DTXFSA14;                          /*!< Device IN Endpoint-n Transmit FIFO Space Avail Register               */
  __I  uint16_t  RESERVED88;
  __I  uint32_t  DIEPDMAB14;                        /*!< Device IN Endpoint-n DMA Buffer Address Register                      */

  union {
    __IO uint32_t  DIEPCTL15;                       /*!< Device IN Endpoint N Control Register                                 */

    struct {
      __IO uint32_t  MPS        : 11;               /*!< Indicates the maximum packet size of the associated endpoint          */
           uint32_t             :  4;
      __IO uint32_t  UAE        :  1;               /*!< Indicates whether this endpoint is active                             */
      __I  uint32_t  DPID       :  1;               /*!< Endpoint Data PID                                                     */
      __I  uint32_t  NAK        :  1;               /*!< The core is transmitting NAK handshakes on this endpoint if
                                                         set                                                                   */
      __IO uint32_t  EP_TYPE    :  2;               /*!< Indicates the transfer type selected.                                 */
           uint32_t             :  1;
      __IO uint32_t  STALL      :  1;               /*!< To non-control, non-isochronous IN endpoints, stall all tokens.
                                                         To control endpoints, response an ACK                                 */
      __IO uint32_t  TX_FIFO_NUM:  4;               /*!< TxFIFO Number                                                         */
      __O  uint32_t  CNAK       :  1;               /*!< A write to this bit clears the NAK bit for the endpoint               */
      __O  uint32_t  SNAK       :  1;               /*!< A write to this bit sets the NAK bit for the endpoint                 */
      __O  uint32_t  SET_D0_PID :  1;               /*!< Set DATA0 PID                                                         */
      __O  uint32_t  SET_D1_PID :  1;               /*!< Set DATA1 PID                                                         */
      __IO uint32_t  EPD        :  1;               /*!< The application sets this bit to stop transmitting data on an
                                                         endpoint even before the transfer for that endpoint is complete       */
      __IO uint32_t  EPE        :  1;               /*!< the descriptor structure and data buffer with data ready to
                                                         transmit is setup                                                     */
    } DIEPCTL15_b;                                  /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED89;

  union {
    __IO uint32_t  DIEPINT15;                       /*!< Device IN Endpoint-n Interrupt Register                               */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  EPD        :  1;               /*!< Endpoint Disabled Interrupt                                           */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
      __IO uint32_t  TIMEOUT    :  1;               /*!< a timeout condition on the USB for the last IN token on this
                                                         endpoint                                                              */
      __IO uint32_t  INTRWTFE   :  1;               /*!< IN Token Received When TxFIFO is Empty                                */
      __IO uint32_t  INTRWEPM   :  1;               /*!< IN Token Received with EP Mismatch                                    */
      __IO uint32_t  INEPNE     :  1;               /*!< IN Endpoint NAK Effective                                             */
      __I  uint32_t  TFE        :  1;               /*!< either half or completely empty depending on GAHBCFG.NPTxFEmpLvl      */
      __IO uint32_t  TFU        :  1;               /*!< Transmit FIFO Underrun                                                */
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
           uint32_t             :  2;
      __IO uint32_t  BE         :  1;               /*!< Babble Error                                                          */
      __IO uint32_t  NAK        :  1;               /*!< a NAK is transmitted                                                  */
      __IO uint32_t  NYET       :  1;               /*!< a NYET response is transmitted                                        */
    } DIEPINT15_b;                                  /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED90;

  union {
    __IO uint32_t  DIEPTSIZ15;                      /*!< Device IN Endpoint-n Transfer Size Register                           */

    struct {
      __IO uint32_t  SIZE       : 19;               /*!< Indicates the transfer size in bytes for endpoint 0                   */
      __IO uint32_t  PACKET_CNT : 10;               /*!< the total number of USB packets                                       */
      __IO uint32_t  MC         :  2;               /*!< the number of packets per microframe to periodic IN endpoints.
                                                         The number of packets must be fetched per non-periodic IN endpoints   */
    } DIEPTSIZ15_b;                                 /*!< BitSize                                                               */
  };
  __IO uint32_t  DIEPDMA15;                         /*!< Device IN Endpoint-n DMA Address Register                             */
  __IO uint16_t  DTXFSA15;                          /*!< Device IN Endpoint-n Transmit FIFO Space Avail Register               */
  __I  uint16_t  RESERVED91;
  __I  uint32_t  DIEPDMAB15;                        /*!< Device IN Endpoint-n DMA Buffer Address Register                      */

  union {
    __IO uint32_t  DOEPCTL0;                        /*!< Device Control OUT Endpoint 0 Control Register                        */

    struct {
      __IO uint32_t  MPS        :  2;               /*!< Indicates the maximum packet size of the associated endpoint,
                                                         applies to IN and OUT endpoints                                       */
           uint32_t             : 13;
      __I  uint32_t  USBAE      :  1;               /*!< Always 1, indicating that control endpoint 0 is always active
                                                         in all configurations and interfaces                                  */
           uint32_t             :  1;
      __I  uint32_t  NAK        :  1;               /*!< The core is transmitting NAK handshakes on this endpoint              */
      __I  uint32_t  EP_TYPE    :  2;               /*!< Hardcoded to 00 for control                                           */
      __IO uint32_t  SNOOP      :  1;               /*!< does not check if the OUT packets are correct before transferring     */
      __IO uint32_t  STALL      :  1;               /*!< The application sets this bit, and the core clears it when a
                                                         SETUP token is received for this endpoint                             */
           uint32_t             :  4;
      __O  uint32_t  CNAK       :  1;               /*!< A write to this bit clears the NAK bit for the endpoint               */
      __O  uint32_t  SNAK       :  1;               /*!< A write to this bit sets the NAK bit for the endpoint                 */
           uint32_t             :  2;
      __I  uint32_t  EPD        :  1;               /*!< The application cannot disable control OUT endpoint 0                 */
      __IO uint32_t  EPE        :  1;               /*!< the descriptor structure and data buffer with data ready to
                                                         receive data is setup                                                 */
    } DOEPCTL0_b;                                   /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED92;

  union {
    __IO uint32_t  DOEPINT0;                        /*!< Device OUT Endpoint-n Interrupt Register                              */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  EPD        :  1;               /*!< Endpoint Disabled Interrupt                                           */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
      __IO uint32_t  SETUP      :  1;               /*!< Only for Control OUT endpoints, the SETUP phase for the control
                                                         endpoint is complete                                                  */
      __IO uint32_t  OUTTRWEPD  :  1;               /*!< OUT Token Received When Endpoint Disabled                             */
      __IO uint32_t  SPRFCW     :  1;               /*!< Only for Control OUT endpoints, the host has switched from data
                                                         phase to the status phase of a Control Write transfer                 */
      __IO uint32_t  B2BSETUPPR :  1;               /*!< to Control OUT endpoints only, received more than three back-to-back
                                                         SETUP packets for this particular endpoint                            */
      __I  uint32_t  TFE        :  1;               /*!< either half or completely empty depending on GAHBCFG.NPTxFEmpLvl      */
      __IO uint32_t  OUTPE      :  1;               /*!< an overflow or a CRC error for an OUT packet                          */
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
           uint32_t             :  2;
      __IO uint32_t  BE         :  1;               /*!< Babble Error                                                          */
      __IO uint32_t  NAK        :  1;               /*!< a NAK is transmitted                                                  */
      __IO uint32_t  NYET       :  1;               /*!< a NYET response is transmitted                                        */
    } DOEPINT0_b;                                   /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED93;

  union {
    __IO uint32_t  DOEPTSIZ0;                       /*!< Device OUT Endpoint 0 Transfer Size Register                          */

    struct {
      __IO uint32_t  SIZE       :  7;               /*!< Indicates the transfer size in bytes for endpoint 0                   */
           uint32_t             : 12;
      __IO uint32_t  PACKET_CNT :  1;               /*!< This field is decremented to zero after a packet is written
                                                         into the RxFIFO                                                       */
           uint32_t             :  9;
      __IO uint32_t  SETUP_CNT  :  2;               /*!< the number of back-to-back SETUP data packets the endpoint can
                                                         receive                                                               */
    } DOEPTSIZ0_b;                                  /*!< BitSize                                                               */
  };
  __IO uint32_t  DOEPDMA0;                          /*!< Device OUT Endpoint-n DMA Address Register                            */
  __I  uint32_t  RESERVED94;
  __I  uint32_t  DOEPDMAB0;                         /*!< Device OUT Endpoint-n DMA Buffer Address Register                     */

  union {
    __IO uint32_t  DOEPCTL1;                        /*!< Device OUT Endpoint N Control Register                                */

    struct {
      __IO uint32_t  MPS        : 11;               /*!< Indicates the maximum packet size of the associated endpoint          */
           uint32_t             :  4;
      __IO uint32_t  UAE        :  1;               /*!< Indicates whether this endpoint is active                             */
      __I  uint32_t  DPID       :  1;               /*!< Endpoint Data PID                                                     */
      __I  uint32_t  NAK        :  1;               /*!< The core is transmitting NAK handshakes on this endpoint if
                                                         set                                                                   */
      __IO uint32_t  EP_TYPE    :  2;               /*!< Indicates the transfer type selected.                                 */
      __IO uint32_t  EC         :  1;               /*!< Doesn't check the correctness of OUT packets before transferring      */
      __IO uint32_t  STALL      :  1;               /*!< To non-control, non-isochronous OUT endpoints, stall all tokens.
                                                         To control endpoints, response an ACK                                 */
           uint32_t             :  4;
      __O  uint32_t  CNAK       :  1;               /*!< A write to this bit clears the NAK bit for the endpoint               */
      __O  uint32_t  SNAK       :  1;               /*!< A write to this bit sets the NAK bit for the endpoint                 */
      __O  uint32_t  SET_D0_PID :  1;               /*!< Set DATA0 PID                                                         */
      __O  uint32_t  SET_D1_PID :  1;               /*!< Set DATA1 PID                                                         */
      __IO uint32_t  EPD        :  1;               /*!< The application sets this bit to stop receiving data on an endpoint
                                                         even before the transfer for that endpoint is complete                */
      __IO uint32_t  EPE        :  1;               /*!< the descriptor structure and data buffer with data ready to
                                                         receive data is setup                                                 */
    } DOEPCTL1_b;                                   /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED95;

  union {
    __IO uint32_t  DOEPINT1;                        /*!< Device OUT Endpoint-n Interrupt Register                              */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  EPD        :  1;               /*!< Endpoint Disabled Interrupt                                           */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
      __IO uint32_t  SETUP      :  1;               /*!< Only for Control OUT endpoints, the SETUP phase for the control
                                                         endpoint is complete                                                  */
      __IO uint32_t  OUTTRWEPD  :  1;               /*!< OUT Token Received When Endpoint Disabled                             */
      __IO uint32_t  SPRFCW     :  1;               /*!< Only for Control OUT endpoints, the host has switched from data
                                                         phase to the status phase of a Control Write transfer                 */
      __IO uint32_t  B2BSETUPPR :  1;               /*!< to Control OUT endpoints only, received more than three back-to-back
                                                         SETUP packets for this particular endpoint                            */
      __I  uint32_t  TFE        :  1;               /*!< either half or completely empty depending on GAHBCFG.NPTxFEmpLvl      */
      __IO uint32_t  OUTPE      :  1;               /*!< an overflow or a CRC error for an OUT packet                          */
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
           uint32_t             :  2;
      __IO uint32_t  BE         :  1;               /*!< Babble Error                                                          */
      __IO uint32_t  NAK        :  1;               /*!< a NAK is transmitted                                                  */
      __IO uint32_t  NYET       :  1;               /*!< a NYET response is transmitted                                        */
    } DOEPINT1_b;                                   /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED96;

  union {
    __IO uint32_t  DOEPTSIZ1;                       /*!< Device OUT Endpoint-n Transfer Size Register                          */

    struct {
      __IO uint32_t  SIZE       : 19;               /*!< Indicates the transfer size in bytes for endpoint 0                   */
      __IO uint32_t  PACKET_CNT : 10;               /*!< the total number of USB packets                                       */
      __IO uint32_t  SETUPCNT_PID:  2;              /*!< To control OUT Endpoints only, back-to-back SETUP data packets.
                                                         To isochronous OUT endpoints, data PID received in the last
                                                          packet                                                               */
    } DOEPTSIZ1_b;                                  /*!< BitSize                                                               */
  };
  __IO uint32_t  DOEPDMA1;                          /*!< Device OUT Endpoint-n DMA Address Register                            */
  __I  uint32_t  RESERVED97;
  __I  uint32_t  DOEPDMAB1;                         /*!< Device OUT Endpoint-n DMA Buffer Address Register                     */

  union {
    __IO uint32_t  DOEPCTL2;                        /*!< Device OUT Endpoint N Control Register                                */

    struct {
      __IO uint32_t  MPS        : 11;               /*!< Indicates the maximum packet size of the associated endpoint          */
           uint32_t             :  4;
      __IO uint32_t  UAE        :  1;               /*!< Indicates whether this endpoint is active                             */
      __I  uint32_t  DPID       :  1;               /*!< Endpoint Data PID                                                     */
      __I  uint32_t  NAK        :  1;               /*!< The core is transmitting NAK handshakes on this endpoint if
                                                         set                                                                   */
      __IO uint32_t  EP_TYPE    :  2;               /*!< Indicates the transfer type selected.                                 */
      __IO uint32_t  EC         :  1;               /*!< Doesn't check the correctness of OUT packets before transferring      */
      __IO uint32_t  STALL      :  1;               /*!< To non-control, non-isochronous OUT endpoints, stall all tokens.
                                                         To control endpoints, response an ACK                                 */
           uint32_t             :  4;
      __O  uint32_t  CNAK       :  1;               /*!< A write to this bit clears the NAK bit for the endpoint               */
      __O  uint32_t  SNAK       :  1;               /*!< A write to this bit sets the NAK bit for the endpoint                 */
      __O  uint32_t  SET_D0_PID :  1;               /*!< Set DATA0 PID                                                         */
      __O  uint32_t  SET_D1_PID :  1;               /*!< Set DATA1 PID                                                         */
      __IO uint32_t  EPD        :  1;               /*!< The application sets this bit to stop receiving data on an endpoint
                                                         even before the transfer for that endpoint is complete                */
      __IO uint32_t  EPE        :  1;               /*!< the descriptor structure and data buffer with data ready to
                                                         receive data is setup                                                 */
    } DOEPCTL2_b;                                   /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED98;

  union {
    __IO uint32_t  DOEPINT2;                        /*!< Device OUT Endpoint-n Interrupt Register                              */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  EPD        :  1;               /*!< Endpoint Disabled Interrupt                                           */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
      __IO uint32_t  SETUP      :  1;               /*!< Only for Control OUT endpoints, the SETUP phase for the control
                                                         endpoint is complete                                                  */
      __IO uint32_t  OUTTRWEPD  :  1;               /*!< OUT Token Received When Endpoint Disabled                             */
      __IO uint32_t  SPRFCW     :  1;               /*!< Only for Control OUT endpoints, the host has switched from data
                                                         phase to the status phase of a Control Write transfer                 */
      __IO uint32_t  B2BSETUPPR :  1;               /*!< to Control OUT endpoints only, received more than three back-to-back
                                                         SETUP packets for this particular endpoint                            */
      __I  uint32_t  TFE        :  1;               /*!< either half or completely empty depending on GAHBCFG.NPTxFEmpLvl      */
      __IO uint32_t  OUTPE      :  1;               /*!< an overflow or a CRC error for an OUT packet                          */
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
           uint32_t             :  2;
      __IO uint32_t  BE         :  1;               /*!< Babble Error                                                          */
      __IO uint32_t  NAK        :  1;               /*!< a NAK is transmitted                                                  */
      __IO uint32_t  NYET       :  1;               /*!< a NYET response is transmitted                                        */
    } DOEPINT2_b;                                   /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED99;

  union {
    __IO uint32_t  DOEPTSIZ2;                       /*!< Device OUT Endpoint-n Transfer Size Register                          */

    struct {
      __IO uint32_t  SIZE       : 19;               /*!< Indicates the transfer size in bytes for endpoint 0                   */
      __IO uint32_t  PACKET_CNT : 10;               /*!< the total number of USB packets                                       */
      __IO uint32_t  SETUPCNT_PID:  2;              /*!< To control OUT Endpoints only, back-to-back SETUP data packets.
                                                         To isochronous OUT endpoints, data PID received in the last
                                                          packet                                                               */
    } DOEPTSIZ2_b;                                  /*!< BitSize                                                               */
  };
  __IO uint32_t  DOEPDMA2;                          /*!< Device OUT Endpoint-n DMA Address Register                            */
  __I  uint32_t  RESERVED100;
  __I  uint32_t  DOEPDMAB2;                         /*!< Device OUT Endpoint-n DMA Buffer Address Register                     */

  union {
    __IO uint32_t  DOEPCTL3;                        /*!< Device OUT Endpoint N Control Register                                */

    struct {
      __IO uint32_t  MPS        : 11;               /*!< Indicates the maximum packet size of the associated endpoint          */
           uint32_t             :  4;
      __IO uint32_t  UAE        :  1;               /*!< Indicates whether this endpoint is active                             */
      __I  uint32_t  DPID       :  1;               /*!< Endpoint Data PID                                                     */
      __I  uint32_t  NAK        :  1;               /*!< The core is transmitting NAK handshakes on this endpoint if
                                                         set                                                                   */
      __IO uint32_t  EP_TYPE    :  2;               /*!< Indicates the transfer type selected.                                 */
      __IO uint32_t  EC         :  1;               /*!< Doesn't check the correctness of OUT packets before transferring      */
      __IO uint32_t  STALL      :  1;               /*!< To non-control, non-isochronous OUT endpoints, stall all tokens.
                                                         To control endpoints, response an ACK                                 */
           uint32_t             :  4;
      __O  uint32_t  CNAK       :  1;               /*!< A write to this bit clears the NAK bit for the endpoint               */
      __O  uint32_t  SNAK       :  1;               /*!< A write to this bit sets the NAK bit for the endpoint                 */
      __O  uint32_t  SET_D0_PID :  1;               /*!< Set DATA0 PID                                                         */
      __O  uint32_t  SET_D1_PID :  1;               /*!< Set DATA1 PID                                                         */
      __IO uint32_t  EPD        :  1;               /*!< The application sets this bit to stop receiving data on an endpoint
                                                         even before the transfer for that endpoint is complete                */
      __IO uint32_t  EPE        :  1;               /*!< the descriptor structure and data buffer with data ready to
                                                         receive data is setup                                                 */
    } DOEPCTL3_b;                                   /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED101;

  union {
    __IO uint32_t  DOEPINT3;                        /*!< Device OUT Endpoint-n Interrupt Register                              */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  EPD        :  1;               /*!< Endpoint Disabled Interrupt                                           */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
      __IO uint32_t  SETUP      :  1;               /*!< Only for Control OUT endpoints, the SETUP phase for the control
                                                         endpoint is complete                                                  */
      __IO uint32_t  OUTTRWEPD  :  1;               /*!< OUT Token Received When Endpoint Disabled                             */
      __IO uint32_t  SPRFCW     :  1;               /*!< Only for Control OUT endpoints, the host has switched from data
                                                         phase to the status phase of a Control Write transfer                 */
      __IO uint32_t  B2BSETUPPR :  1;               /*!< to Control OUT endpoints only, received more than three back-to-back
                                                         SETUP packets for this particular endpoint                            */
      __I  uint32_t  TFE        :  1;               /*!< either half or completely empty depending on GAHBCFG.NPTxFEmpLvl      */
      __IO uint32_t  OUTPE      :  1;               /*!< an overflow or a CRC error for an OUT packet                          */
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
           uint32_t             :  2;
      __IO uint32_t  BE         :  1;               /*!< Babble Error                                                          */
      __IO uint32_t  NAK        :  1;               /*!< a NAK is transmitted                                                  */
      __IO uint32_t  NYET       :  1;               /*!< a NYET response is transmitted                                        */
    } DOEPINT3_b;                                   /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED102;

  union {
    __IO uint32_t  DOEPTSIZ3;                       /*!< Device OUT Endpoint-n Transfer Size Register                          */

    struct {
      __IO uint32_t  SIZE       : 19;               /*!< Indicates the transfer size in bytes for endpoint 0                   */
      __IO uint32_t  PACKET_CNT : 10;               /*!< the total number of USB packets                                       */
      __IO uint32_t  SETUPCNT_PID:  2;              /*!< To control OUT Endpoints only, back-to-back SETUP data packets.
                                                         To isochronous OUT endpoints, data PID received in the last
                                                          packet                                                               */
    } DOEPTSIZ3_b;                                  /*!< BitSize                                                               */
  };
  __IO uint32_t  DOEPDMA3;                          /*!< Device OUT Endpoint-n DMA Address Register                            */
  __I  uint32_t  RESERVED103;
  __I  uint32_t  DOEPDMAB3;                         /*!< Device OUT Endpoint-n DMA Buffer Address Register                     */

  union {
    __IO uint32_t  DOEPCTL4;                        /*!< Device OUT Endpoint N Control Register                                */

    struct {
      __IO uint32_t  MPS        : 11;               /*!< Indicates the maximum packet size of the associated endpoint          */
           uint32_t             :  4;
      __IO uint32_t  UAE        :  1;               /*!< Indicates whether this endpoint is active                             */
      __I  uint32_t  DPID       :  1;               /*!< Endpoint Data PID                                                     */
      __I  uint32_t  NAK        :  1;               /*!< The core is transmitting NAK handshakes on this endpoint if
                                                         set                                                                   */
      __IO uint32_t  EP_TYPE    :  2;               /*!< Indicates the transfer type selected.                                 */
      __IO uint32_t  EC         :  1;               /*!< Doesn't check the correctness of OUT packets before transferring      */
      __IO uint32_t  STALL      :  1;               /*!< To non-control, non-isochronous OUT endpoints, stall all tokens.
                                                         To control endpoints, response an ACK                                 */
           uint32_t             :  4;
      __O  uint32_t  CNAK       :  1;               /*!< A write to this bit clears the NAK bit for the endpoint               */
      __O  uint32_t  SNAK       :  1;               /*!< A write to this bit sets the NAK bit for the endpoint                 */
      __O  uint32_t  SET_D0_PID :  1;               /*!< Set DATA0 PID                                                         */
      __O  uint32_t  SET_D1_PID :  1;               /*!< Set DATA1 PID                                                         */
      __IO uint32_t  EPD        :  1;               /*!< The application sets this bit to stop receiving data on an endpoint
                                                         even before the transfer for that endpoint is complete                */
      __IO uint32_t  EPE        :  1;               /*!< the descriptor structure and data buffer with data ready to
                                                         receive data is setup                                                 */
    } DOEPCTL4_b;                                   /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED104;

  union {
    __IO uint32_t  DOEPINT4;                        /*!< Device OUT Endpoint-n Interrupt Register                              */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  EPD        :  1;               /*!< Endpoint Disabled Interrupt                                           */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
      __IO uint32_t  SETUP      :  1;               /*!< Only for Control OUT endpoints, the SETUP phase for the control
                                                         endpoint is complete                                                  */
      __IO uint32_t  OUTTRWEPD  :  1;               /*!< OUT Token Received When Endpoint Disabled                             */
      __IO uint32_t  SPRFCW     :  1;               /*!< Only for Control OUT endpoints, the host has switched from data
                                                         phase to the status phase of a Control Write transfer                 */
      __IO uint32_t  B2BSETUPPR :  1;               /*!< to Control OUT endpoints only, received more than three back-to-back
                                                         SETUP packets for this particular endpoint                            */
      __I  uint32_t  TFE        :  1;               /*!< either half or completely empty depending on GAHBCFG.NPTxFEmpLvl      */
      __IO uint32_t  OUTPE      :  1;               /*!< an overflow or a CRC error for an OUT packet                          */
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
           uint32_t             :  2;
      __IO uint32_t  BE         :  1;               /*!< Babble Error                                                          */
      __IO uint32_t  NAK        :  1;               /*!< a NAK is transmitted                                                  */
      __IO uint32_t  NYET       :  1;               /*!< a NYET response is transmitted                                        */
    } DOEPINT4_b;                                   /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED105;

  union {
    __IO uint32_t  DOEPTSIZ4;                       /*!< Device OUT Endpoint-n Transfer Size Register                          */

    struct {
      __IO uint32_t  SIZE       : 19;               /*!< Indicates the transfer size in bytes for endpoint 0                   */
      __IO uint32_t  PACKET_CNT : 10;               /*!< the total number of USB packets                                       */
      __IO uint32_t  SETUPCNT_PID:  2;              /*!< To control OUT Endpoints only, back-to-back SETUP data packets.
                                                         To isochronous OUT endpoints, data PID received in the last
                                                          packet                                                               */
    } DOEPTSIZ4_b;                                  /*!< BitSize                                                               */
  };
  __IO uint32_t  DOEPDMA4;                          /*!< Device OUT Endpoint-n DMA Address Register                            */
  __I  uint32_t  RESERVED106;
  __I  uint32_t  DOEPDMAB4;                         /*!< Device OUT Endpoint-n DMA Buffer Address Register                     */

  union {
    __IO uint32_t  DOEPCTL5;                        /*!< Device OUT Endpoint N Control Register                                */

    struct {
      __IO uint32_t  MPS        : 11;               /*!< Indicates the maximum packet size of the associated endpoint          */
           uint32_t             :  4;
      __IO uint32_t  UAE        :  1;               /*!< Indicates whether this endpoint is active                             */
      __I  uint32_t  DPID       :  1;               /*!< Endpoint Data PID                                                     */
      __I  uint32_t  NAK        :  1;               /*!< The core is transmitting NAK handshakes on this endpoint if
                                                         set                                                                   */
      __IO uint32_t  EP_TYPE    :  2;               /*!< Indicates the transfer type selected.                                 */
      __IO uint32_t  EC         :  1;               /*!< Doesn't check the correctness of OUT packets before transferring      */
      __IO uint32_t  STALL      :  1;               /*!< To non-control, non-isochronous OUT endpoints, stall all tokens.
                                                         To control endpoints, response an ACK                                 */
           uint32_t             :  4;
      __O  uint32_t  CNAK       :  1;               /*!< A write to this bit clears the NAK bit for the endpoint               */
      __O  uint32_t  SNAK       :  1;               /*!< A write to this bit sets the NAK bit for the endpoint                 */
      __O  uint32_t  SET_D0_PID :  1;               /*!< Set DATA0 PID                                                         */
      __O  uint32_t  SET_D1_PID :  1;               /*!< Set DATA1 PID                                                         */
      __IO uint32_t  EPD        :  1;               /*!< The application sets this bit to stop receiving data on an endpoint
                                                         even before the transfer for that endpoint is complete                */
      __IO uint32_t  EPE        :  1;               /*!< the descriptor structure and data buffer with data ready to
                                                         receive data is setup                                                 */
    } DOEPCTL5_b;                                   /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED107;

  union {
    __IO uint32_t  DOEPINT5;                        /*!< Device OUT Endpoint-n Interrupt Register                              */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  EPD        :  1;               /*!< Endpoint Disabled Interrupt                                           */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
      __IO uint32_t  SETUP      :  1;               /*!< Only for Control OUT endpoints, the SETUP phase for the control
                                                         endpoint is complete                                                  */
      __IO uint32_t  OUTTRWEPD  :  1;               /*!< OUT Token Received When Endpoint Disabled                             */
      __IO uint32_t  SPRFCW     :  1;               /*!< Only for Control OUT endpoints, the host has switched from data
                                                         phase to the status phase of a Control Write transfer                 */
      __IO uint32_t  B2BSETUPPR :  1;               /*!< to Control OUT endpoints only, received more than three back-to-back
                                                         SETUP packets for this particular endpoint                            */
      __I  uint32_t  TFE        :  1;               /*!< either half or completely empty depending on GAHBCFG.NPTxFEmpLvl      */
      __IO uint32_t  OUTPE      :  1;               /*!< an overflow or a CRC error for an OUT packet                          */
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
           uint32_t             :  2;
      __IO uint32_t  BE         :  1;               /*!< Babble Error                                                          */
      __IO uint32_t  NAK        :  1;               /*!< a NAK is transmitted                                                  */
      __IO uint32_t  NYET       :  1;               /*!< a NYET response is transmitted                                        */
    } DOEPINT5_b;                                   /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED108;

  union {
    __IO uint32_t  DOEPTSIZ5;                       /*!< Device OUT Endpoint-n Transfer Size Register                          */

    struct {
      __IO uint32_t  SIZE       : 19;               /*!< Indicates the transfer size in bytes for endpoint 0                   */
      __IO uint32_t  PACKET_CNT : 10;               /*!< the total number of USB packets                                       */
      __IO uint32_t  SETUPCNT_PID:  2;              /*!< To control OUT Endpoints only, back-to-back SETUP data packets.
                                                         To isochronous OUT endpoints, data PID received in the last
                                                          packet                                                               */
    } DOEPTSIZ5_b;                                  /*!< BitSize                                                               */
  };
  __IO uint32_t  DOEPDMA5;                          /*!< Device OUT Endpoint-n DMA Address Register                            */
  __I  uint32_t  RESERVED109;
  __I  uint32_t  DOEPDMAB5;                         /*!< Device OUT Endpoint-n DMA Buffer Address Register                     */

  union {
    __IO uint32_t  DOEPCTL6;                        /*!< Device OUT Endpoint N Control Register                                */

    struct {
      __IO uint32_t  MPS        : 11;               /*!< Indicates the maximum packet size of the associated endpoint          */
           uint32_t             :  4;
      __IO uint32_t  UAE        :  1;               /*!< Indicates whether this endpoint is active                             */
      __I  uint32_t  DPID       :  1;               /*!< Endpoint Data PID                                                     */
      __I  uint32_t  NAK        :  1;               /*!< The core is transmitting NAK handshakes on this endpoint if
                                                         set                                                                   */
      __IO uint32_t  EP_TYPE    :  2;               /*!< Indicates the transfer type selected.                                 */
      __IO uint32_t  EC         :  1;               /*!< Doesn't check the correctness of OUT packets before transferring      */
      __IO uint32_t  STALL      :  1;               /*!< To non-control, non-isochronous OUT endpoints, stall all tokens.
                                                         To control endpoints, response an ACK                                 */
           uint32_t             :  4;
      __O  uint32_t  CNAK       :  1;               /*!< A write to this bit clears the NAK bit for the endpoint               */
      __O  uint32_t  SNAK       :  1;               /*!< A write to this bit sets the NAK bit for the endpoint                 */
      __O  uint32_t  SET_D0_PID :  1;               /*!< Set DATA0 PID                                                         */
      __O  uint32_t  SET_D1_PID :  1;               /*!< Set DATA1 PID                                                         */
      __IO uint32_t  EPD        :  1;               /*!< The application sets this bit to stop receiving data on an endpoint
                                                         even before the transfer for that endpoint is complete                */
      __IO uint32_t  EPE        :  1;               /*!< the descriptor structure and data buffer with data ready to
                                                         receive data is setup                                                 */
    } DOEPCTL6_b;                                   /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED110;

  union {
    __IO uint32_t  DOEPINT6;                        /*!< Device OUT Endpoint-n Interrupt Register                              */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  EPD        :  1;               /*!< Endpoint Disabled Interrupt                                           */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
      __IO uint32_t  SETUP      :  1;               /*!< Only for Control OUT endpoints, the SETUP phase for the control
                                                         endpoint is complete                                                  */
      __IO uint32_t  OUTTRWEPD  :  1;               /*!< OUT Token Received When Endpoint Disabled                             */
      __IO uint32_t  SPRFCW     :  1;               /*!< Only for Control OUT endpoints, the host has switched from data
                                                         phase to the status phase of a Control Write transfer                 */
      __IO uint32_t  B2BSETUPPR :  1;               /*!< to Control OUT endpoints only, received more than three back-to-back
                                                         SETUP packets for this particular endpoint                            */
      __I  uint32_t  TFE        :  1;               /*!< either half or completely empty depending on GAHBCFG.NPTxFEmpLvl      */
      __IO uint32_t  OUTPE      :  1;               /*!< an overflow or a CRC error for an OUT packet                          */
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
           uint32_t             :  2;
      __IO uint32_t  BE         :  1;               /*!< Babble Error                                                          */
      __IO uint32_t  NAK        :  1;               /*!< a NAK is transmitted                                                  */
      __IO uint32_t  NYET       :  1;               /*!< a NYET response is transmitted                                        */
    } DOEPINT6_b;                                   /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED111;

  union {
    __IO uint32_t  DOEPTSIZ6;                       /*!< Device OUT Endpoint-n Transfer Size Register                          */

    struct {
      __IO uint32_t  SIZE       : 19;               /*!< Indicates the transfer size in bytes for endpoint 0                   */
      __IO uint32_t  PACKET_CNT : 10;               /*!< the total number of USB packets                                       */
      __IO uint32_t  SETUPCNT_PID:  2;              /*!< To control OUT Endpoints only, back-to-back SETUP data packets.
                                                         To isochronous OUT endpoints, data PID received in the last
                                                          packet                                                               */
    } DOEPTSIZ6_b;                                  /*!< BitSize                                                               */
  };
  __IO uint32_t  DOEPDMA6;                          /*!< Device OUT Endpoint-n DMA Address Register                            */
  __I  uint32_t  RESERVED112;
  __I  uint32_t  DOEPDMAB6;                         /*!< Device OUT Endpoint-n DMA Buffer Address Register                     */

  union {
    __IO uint32_t  DOEPCTL7;                        /*!< Device OUT Endpoint N Control Register                                */

    struct {
      __IO uint32_t  MPS        : 11;               /*!< Indicates the maximum packet size of the associated endpoint          */
           uint32_t             :  4;
      __IO uint32_t  UAE        :  1;               /*!< Indicates whether this endpoint is active                             */
      __I  uint32_t  DPID       :  1;               /*!< Endpoint Data PID                                                     */
      __I  uint32_t  NAK        :  1;               /*!< The core is transmitting NAK handshakes on this endpoint if
                                                         set                                                                   */
      __IO uint32_t  EP_TYPE    :  2;               /*!< Indicates the transfer type selected.                                 */
      __IO uint32_t  EC         :  1;               /*!< Doesn't check the correctness of OUT packets before transferring      */
      __IO uint32_t  STALL      :  1;               /*!< To non-control, non-isochronous OUT endpoints, stall all tokens.
                                                         To control endpoints, response an ACK                                 */
           uint32_t             :  4;
      __O  uint32_t  CNAK       :  1;               /*!< A write to this bit clears the NAK bit for the endpoint               */
      __O  uint32_t  SNAK       :  1;               /*!< A write to this bit sets the NAK bit for the endpoint                 */
      __O  uint32_t  SET_D0_PID :  1;               /*!< Set DATA0 PID                                                         */
      __O  uint32_t  SET_D1_PID :  1;               /*!< Set DATA1 PID                                                         */
      __IO uint32_t  EPD        :  1;               /*!< The application sets this bit to stop receiving data on an endpoint
                                                         even before the transfer for that endpoint is complete                */
      __IO uint32_t  EPE        :  1;               /*!< the descriptor structure and data buffer with data ready to
                                                         receive data is setup                                                 */
    } DOEPCTL7_b;                                   /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED113;

  union {
    __IO uint32_t  DOEPINT7;                        /*!< Device OUT Endpoint-n Interrupt Register                              */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  EPD        :  1;               /*!< Endpoint Disabled Interrupt                                           */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
      __IO uint32_t  SETUP      :  1;               /*!< Only for Control OUT endpoints, the SETUP phase for the control
                                                         endpoint is complete                                                  */
      __IO uint32_t  OUTTRWEPD  :  1;               /*!< OUT Token Received When Endpoint Disabled                             */
      __IO uint32_t  SPRFCW     :  1;               /*!< Only for Control OUT endpoints, the host has switched from data
                                                         phase to the status phase of a Control Write transfer                 */
      __IO uint32_t  B2BSETUPPR :  1;               /*!< to Control OUT endpoints only, received more than three back-to-back
                                                         SETUP packets for this particular endpoint                            */
      __I  uint32_t  TFE        :  1;               /*!< either half or completely empty depending on GAHBCFG.NPTxFEmpLvl      */
      __IO uint32_t  OUTPE      :  1;               /*!< an overflow or a CRC error for an OUT packet                          */
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
           uint32_t             :  2;
      __IO uint32_t  BE         :  1;               /*!< Babble Error                                                          */
      __IO uint32_t  NAK        :  1;               /*!< a NAK is transmitted                                                  */
      __IO uint32_t  NYET       :  1;               /*!< a NYET response is transmitted                                        */
    } DOEPINT7_b;                                   /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED114;

  union {
    __IO uint32_t  DOEPTSIZ7;                       /*!< Device OUT Endpoint-n Transfer Size Register                          */

    struct {
      __IO uint32_t  SIZE       : 19;               /*!< Indicates the transfer size in bytes for endpoint 0                   */
      __IO uint32_t  PACKET_CNT : 10;               /*!< the total number of USB packets                                       */
      __IO uint32_t  SETUPCNT_PID:  2;              /*!< To control OUT Endpoints only, back-to-back SETUP data packets.
                                                         To isochronous OUT endpoints, data PID received in the last
                                                          packet                                                               */
    } DOEPTSIZ7_b;                                  /*!< BitSize                                                               */
  };
  __IO uint32_t  DOEPDMA7;                          /*!< Device OUT Endpoint-n DMA Address Register                            */
  __I  uint32_t  RESERVED115;
  __I  uint32_t  DOEPDMAB7;                         /*!< Device OUT Endpoint-n DMA Buffer Address Register                     */

  union {
    __IO uint32_t  DOEPCTL8;                        /*!< Device OUT Endpoint N Control Register                                */

    struct {
      __IO uint32_t  MPS        : 11;               /*!< Indicates the maximum packet size of the associated endpoint          */
           uint32_t             :  4;
      __IO uint32_t  UAE        :  1;               /*!< Indicates whether this endpoint is active                             */
      __I  uint32_t  DPID       :  1;               /*!< Endpoint Data PID                                                     */
      __I  uint32_t  NAK        :  1;               /*!< The core is transmitting NAK handshakes on this endpoint if
                                                         set                                                                   */
      __IO uint32_t  EP_TYPE    :  2;               /*!< Indicates the transfer type selected.                                 */
      __IO uint32_t  EC         :  1;               /*!< Doesn't check the correctness of OUT packets before transferring      */
      __IO uint32_t  STALL      :  1;               /*!< To non-control, non-isochronous OUT endpoints, stall all tokens.
                                                         To control endpoints, response an ACK                                 */
           uint32_t             :  4;
      __O  uint32_t  CNAK       :  1;               /*!< A write to this bit clears the NAK bit for the endpoint               */
      __O  uint32_t  SNAK       :  1;               /*!< A write to this bit sets the NAK bit for the endpoint                 */
      __O  uint32_t  SET_D0_PID :  1;               /*!< Set DATA0 PID                                                         */
      __O  uint32_t  SET_D1_PID :  1;               /*!< Set DATA1 PID                                                         */
      __IO uint32_t  EPD        :  1;               /*!< The application sets this bit to stop receiving data on an endpoint
                                                         even before the transfer for that endpoint is complete                */
      __IO uint32_t  EPE        :  1;               /*!< the descriptor structure and data buffer with data ready to
                                                         receive data is setup                                                 */
    } DOEPCTL8_b;                                   /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED116;

  union {
    __IO uint32_t  DOEPINT8;                        /*!< Device OUT Endpoint-n Interrupt Register                              */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  EPD        :  1;               /*!< Endpoint Disabled Interrupt                                           */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
      __IO uint32_t  SETUP      :  1;               /*!< Only for Control OUT endpoints, the SETUP phase for the control
                                                         endpoint is complete                                                  */
      __IO uint32_t  OUTTRWEPD  :  1;               /*!< OUT Token Received When Endpoint Disabled                             */
      __IO uint32_t  SPRFCW     :  1;               /*!< Only for Control OUT endpoints, the host has switched from data
                                                         phase to the status phase of a Control Write transfer                 */
      __IO uint32_t  B2BSETUPPR :  1;               /*!< to Control OUT endpoints only, received more than three back-to-back
                                                         SETUP packets for this particular endpoint                            */
      __I  uint32_t  TFE        :  1;               /*!< either half or completely empty depending on GAHBCFG.NPTxFEmpLvl      */
      __IO uint32_t  OUTPE      :  1;               /*!< an overflow or a CRC error for an OUT packet                          */
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
           uint32_t             :  2;
      __IO uint32_t  BE         :  1;               /*!< Babble Error                                                          */
      __IO uint32_t  NAK        :  1;               /*!< a NAK is transmitted                                                  */
      __IO uint32_t  NYET       :  1;               /*!< a NYET response is transmitted                                        */
    } DOEPINT8_b;                                   /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED117;

  union {
    __IO uint32_t  DOEPTSIZ8;                       /*!< Device OUT Endpoint-n Transfer Size Register                          */

    struct {
      __IO uint32_t  SIZE       : 19;               /*!< Indicates the transfer size in bytes for endpoint 0                   */
      __IO uint32_t  PACKET_CNT : 10;               /*!< the total number of USB packets                                       */
      __IO uint32_t  SETUPCNT_PID:  2;              /*!< To control OUT Endpoints only, back-to-back SETUP data packets.
                                                         To isochronous OUT endpoints, data PID received in the last
                                                          packet                                                               */
    } DOEPTSIZ8_b;                                  /*!< BitSize                                                               */
  };
  __IO uint32_t  DOEPDMA8;                          /*!< Device OUT Endpoint-n DMA Address Register                            */
  __I  uint32_t  RESERVED118;
  __I  uint32_t  DOEPDMAB8;                         /*!< Device OUT Endpoint-n DMA Buffer Address Register                     */

  union {
    __IO uint32_t  DOEPCTL9;                        /*!< Device OUT Endpoint N Control Register                                */

    struct {
      __IO uint32_t  MPS        : 11;               /*!< Indicates the maximum packet size of the associated endpoint          */
           uint32_t             :  4;
      __IO uint32_t  UAE        :  1;               /*!< Indicates whether this endpoint is active                             */
      __I  uint32_t  DPID       :  1;               /*!< Endpoint Data PID                                                     */
      __I  uint32_t  NAK        :  1;               /*!< The core is transmitting NAK handshakes on this endpoint if
                                                         set                                                                   */
      __IO uint32_t  EP_TYPE    :  2;               /*!< Indicates the transfer type selected.                                 */
      __IO uint32_t  EC         :  1;               /*!< Doesn't check the correctness of OUT packets before transferring      */
      __IO uint32_t  STALL      :  1;               /*!< To non-control, non-isochronous OUT endpoints, stall all tokens.
                                                         To control endpoints, response an ACK                                 */
           uint32_t             :  4;
      __O  uint32_t  CNAK       :  1;               /*!< A write to this bit clears the NAK bit for the endpoint               */
      __O  uint32_t  SNAK       :  1;               /*!< A write to this bit sets the NAK bit for the endpoint                 */
      __O  uint32_t  SET_D0_PID :  1;               /*!< Set DATA0 PID                                                         */
      __O  uint32_t  SET_D1_PID :  1;               /*!< Set DATA1 PID                                                         */
      __IO uint32_t  EPD        :  1;               /*!< The application sets this bit to stop receiving data on an endpoint
                                                         even before the transfer for that endpoint is complete                */
      __IO uint32_t  EPE        :  1;               /*!< the descriptor structure and data buffer with data ready to
                                                         receive data is setup                                                 */
    } DOEPCTL9_b;                                   /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED119;

  union {
    __IO uint32_t  DOEPINT9;                        /*!< Device OUT Endpoint-n Interrupt Register                              */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  EPD        :  1;               /*!< Endpoint Disabled Interrupt                                           */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
      __IO uint32_t  SETUP      :  1;               /*!< Only for Control OUT endpoints, the SETUP phase for the control
                                                         endpoint is complete                                                  */
      __IO uint32_t  OUTTRWEPD  :  1;               /*!< OUT Token Received When Endpoint Disabled                             */
      __IO uint32_t  SPRFCW     :  1;               /*!< Only for Control OUT endpoints, the host has switched from data
                                                         phase to the status phase of a Control Write transfer                 */
      __IO uint32_t  B2BSETUPPR :  1;               /*!< to Control OUT endpoints only, received more than three back-to-back
                                                         SETUP packets for this particular endpoint                            */
      __I  uint32_t  TFE        :  1;               /*!< either half or completely empty depending on GAHBCFG.NPTxFEmpLvl      */
      __IO uint32_t  OUTPE      :  1;               /*!< an overflow or a CRC error for an OUT packet                          */
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
           uint32_t             :  2;
      __IO uint32_t  BE         :  1;               /*!< Babble Error                                                          */
      __IO uint32_t  NAK        :  1;               /*!< a NAK is transmitted                                                  */
      __IO uint32_t  NYET       :  1;               /*!< a NYET response is transmitted                                        */
    } DOEPINT9_b;                                   /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED120;

  union {
    __IO uint32_t  DOEPTSIZ9;                       /*!< Device OUT Endpoint-n Transfer Size Register                          */

    struct {
      __IO uint32_t  SIZE       : 19;               /*!< Indicates the transfer size in bytes for endpoint 0                   */
      __IO uint32_t  PACKET_CNT : 10;               /*!< the total number of USB packets                                       */
      __IO uint32_t  SETUPCNT_PID:  2;              /*!< To control OUT Endpoints only, back-to-back SETUP data packets.
                                                         To isochronous OUT endpoints, data PID received in the last
                                                          packet                                                               */
    } DOEPTSIZ9_b;                                  /*!< BitSize                                                               */
  };
  __IO uint32_t  DOEPDMA9;                          /*!< Device OUT Endpoint-n DMA Address Register                            */
  __I  uint32_t  RESERVED121;
  __I  uint32_t  DOEPDMAB9;                         /*!< Device OUT Endpoint-n DMA Buffer Address Register                     */

  union {
    __IO uint32_t  DOEPCTL10;                       /*!< Device OUT Endpoint N Control Register                                */

    struct {
      __IO uint32_t  MPS        : 11;               /*!< Indicates the maximum packet size of the associated endpoint          */
           uint32_t             :  4;
      __IO uint32_t  UAE        :  1;               /*!< Indicates whether this endpoint is active                             */
      __I  uint32_t  DPID       :  1;               /*!< Endpoint Data PID                                                     */
      __I  uint32_t  NAK        :  1;               /*!< The core is transmitting NAK handshakes on this endpoint if
                                                         set                                                                   */
      __IO uint32_t  EP_TYPE    :  2;               /*!< Indicates the transfer type selected.                                 */
      __IO uint32_t  EC         :  1;               /*!< Doesn't check the correctness of OUT packets before transferring      */
      __IO uint32_t  STALL      :  1;               /*!< To non-control, non-isochronous OUT endpoints, stall all tokens.
                                                         To control endpoints, response an ACK                                 */
           uint32_t             :  4;
      __O  uint32_t  CNAK       :  1;               /*!< A write to this bit clears the NAK bit for the endpoint               */
      __O  uint32_t  SNAK       :  1;               /*!< A write to this bit sets the NAK bit for the endpoint                 */
      __O  uint32_t  SET_D0_PID :  1;               /*!< Set DATA0 PID                                                         */
      __O  uint32_t  SET_D1_PID :  1;               /*!< Set DATA1 PID                                                         */
      __IO uint32_t  EPD        :  1;               /*!< The application sets this bit to stop receiving data on an endpoint
                                                         even before the transfer for that endpoint is complete                */
      __IO uint32_t  EPE        :  1;               /*!< the descriptor structure and data buffer with data ready to
                                                         receive data is setup                                                 */
    } DOEPCTL10_b;                                  /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED122;

  union {
    __IO uint32_t  DOEPINT10;                       /*!< Device OUT Endpoint-n Interrupt Register                              */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  EPD        :  1;               /*!< Endpoint Disabled Interrupt                                           */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
      __IO uint32_t  SETUP      :  1;               /*!< Only for Control OUT endpoints, the SETUP phase for the control
                                                         endpoint is complete                                                  */
      __IO uint32_t  OUTTRWEPD  :  1;               /*!< OUT Token Received When Endpoint Disabled                             */
      __IO uint32_t  SPRFCW     :  1;               /*!< Only for Control OUT endpoints, the host has switched from data
                                                         phase to the status phase of a Control Write transfer                 */
      __IO uint32_t  B2BSETUPPR :  1;               /*!< to Control OUT endpoints only, received more than three back-to-back
                                                         SETUP packets for this particular endpoint                            */
      __I  uint32_t  TFE        :  1;               /*!< either half or completely empty depending on GAHBCFG.NPTxFEmpLvl      */
      __IO uint32_t  OUTPE      :  1;               /*!< an overflow or a CRC error for an OUT packet                          */
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
           uint32_t             :  2;
      __IO uint32_t  BE         :  1;               /*!< Babble Error                                                          */
      __IO uint32_t  NAK        :  1;               /*!< a NAK is transmitted                                                  */
      __IO uint32_t  NYET       :  1;               /*!< a NYET response is transmitted                                        */
    } DOEPINT10_b;                                  /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED123;

  union {
    __IO uint32_t  DOEPTSIZ10;                      /*!< Device OUT Endpoint-n Transfer Size Register                          */

    struct {
      __IO uint32_t  SIZE       : 19;               /*!< Indicates the transfer size in bytes for endpoint 0                   */
      __IO uint32_t  PACKET_CNT : 10;               /*!< the total number of USB packets                                       */
      __IO uint32_t  SETUPCNT_PID:  2;              /*!< To control OUT Endpoints only, back-to-back SETUP data packets.
                                                         To isochronous OUT endpoints, data PID received in the last
                                                          packet                                                               */
    } DOEPTSIZ10_b;                                 /*!< BitSize                                                               */
  };
  __IO uint32_t  DOEPDMA10;                         /*!< Device OUT Endpoint-n DMA Address Register                            */
  __I  uint32_t  RESERVED124;
  __I  uint32_t  DOEPDMAB10;                        /*!< Device OUT Endpoint-n DMA Buffer Address Register                     */

  union {
    __IO uint32_t  DOEPCTL11;                       /*!< Device OUT Endpoint N Control Register                                */

    struct {
      __IO uint32_t  MPS        : 11;               /*!< Indicates the maximum packet size of the associated endpoint          */
           uint32_t             :  4;
      __IO uint32_t  UAE        :  1;               /*!< Indicates whether this endpoint is active                             */
      __I  uint32_t  DPID       :  1;               /*!< Endpoint Data PID                                                     */
      __I  uint32_t  NAK        :  1;               /*!< The core is transmitting NAK handshakes on this endpoint if
                                                         set                                                                   */
      __IO uint32_t  EP_TYPE    :  2;               /*!< Indicates the transfer type selected.                                 */
      __IO uint32_t  EC         :  1;               /*!< Doesn't check the correctness of OUT packets before transferring      */
      __IO uint32_t  STALL      :  1;               /*!< To non-control, non-isochronous OUT endpoints, stall all tokens.
                                                         To control endpoints, response an ACK                                 */
           uint32_t             :  4;
      __O  uint32_t  CNAK       :  1;               /*!< A write to this bit clears the NAK bit for the endpoint               */
      __O  uint32_t  SNAK       :  1;               /*!< A write to this bit sets the NAK bit for the endpoint                 */
      __O  uint32_t  SET_D0_PID :  1;               /*!< Set DATA0 PID                                                         */
      __O  uint32_t  SET_D1_PID :  1;               /*!< Set DATA1 PID                                                         */
      __IO uint32_t  EPD        :  1;               /*!< The application sets this bit to stop receiving data on an endpoint
                                                         even before the transfer for that endpoint is complete                */
      __IO uint32_t  EPE        :  1;               /*!< the descriptor structure and data buffer with data ready to
                                                         receive data is setup                                                 */
    } DOEPCTL11_b;                                  /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED125;

  union {
    __IO uint32_t  DOEPINT11;                       /*!< Device OUT Endpoint-n Interrupt Register                              */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  EPD        :  1;               /*!< Endpoint Disabled Interrupt                                           */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
      __IO uint32_t  SETUP      :  1;               /*!< Only for Control OUT endpoints, the SETUP phase for the control
                                                         endpoint is complete                                                  */
      __IO uint32_t  OUTTRWEPD  :  1;               /*!< OUT Token Received When Endpoint Disabled                             */
      __IO uint32_t  SPRFCW     :  1;               /*!< Only for Control OUT endpoints, the host has switched from data
                                                         phase to the status phase of a Control Write transfer                 */
      __IO uint32_t  B2BSETUPPR :  1;               /*!< to Control OUT endpoints only, received more than three back-to-back
                                                         SETUP packets for this particular endpoint                            */
      __I  uint32_t  TFE        :  1;               /*!< either half or completely empty depending on GAHBCFG.NPTxFEmpLvl      */
      __IO uint32_t  OUTPE      :  1;               /*!< an overflow or a CRC error for an OUT packet                          */
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
           uint32_t             :  2;
      __IO uint32_t  BE         :  1;               /*!< Babble Error                                                          */
      __IO uint32_t  NAK        :  1;               /*!< a NAK is transmitted                                                  */
      __IO uint32_t  NYET       :  1;               /*!< a NYET response is transmitted                                        */
    } DOEPINT11_b;                                  /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED126;

  union {
    __IO uint32_t  DOEPTSIZ11;                      /*!< Device OUT Endpoint-n Transfer Size Register                          */

    struct {
      __IO uint32_t  SIZE       : 19;               /*!< Indicates the transfer size in bytes for endpoint 0                   */
      __IO uint32_t  PACKET_CNT : 10;               /*!< the total number of USB packets                                       */
      __IO uint32_t  SETUPCNT_PID:  2;              /*!< To control OUT Endpoints only, back-to-back SETUP data packets.
                                                         To isochronous OUT endpoints, data PID received in the last
                                                          packet                                                               */
    } DOEPTSIZ11_b;                                 /*!< BitSize                                                               */
  };
  __IO uint32_t  DOEPDMA11;                         /*!< Device OUT Endpoint-n DMA Address Register                            */
  __I  uint32_t  RESERVED127;
  __I  uint32_t  DOEPDMAB11;                        /*!< Device OUT Endpoint-n DMA Buffer Address Register                     */

  union {
    __IO uint32_t  DOEPCTL12;                       /*!< Device OUT Endpoint N Control Register                                */

    struct {
      __IO uint32_t  MPS        : 11;               /*!< Indicates the maximum packet size of the associated endpoint          */
           uint32_t             :  4;
      __IO uint32_t  UAE        :  1;               /*!< Indicates whether this endpoint is active                             */
      __I  uint32_t  DPID       :  1;               /*!< Endpoint Data PID                                                     */
      __I  uint32_t  NAK        :  1;               /*!< The core is transmitting NAK handshakes on this endpoint if
                                                         set                                                                   */
      __IO uint32_t  EP_TYPE    :  2;               /*!< Indicates the transfer type selected.                                 */
      __IO uint32_t  EC         :  1;               /*!< Doesn't check the correctness of OUT packets before transferring      */
      __IO uint32_t  STALL      :  1;               /*!< To non-control, non-isochronous OUT endpoints, stall all tokens.
                                                         To control endpoints, response an ACK                                 */
           uint32_t             :  4;
      __O  uint32_t  CNAK       :  1;               /*!< A write to this bit clears the NAK bit for the endpoint               */
      __O  uint32_t  SNAK       :  1;               /*!< A write to this bit sets the NAK bit for the endpoint                 */
      __O  uint32_t  SET_D0_PID :  1;               /*!< Set DATA0 PID                                                         */
      __O  uint32_t  SET_D1_PID :  1;               /*!< Set DATA1 PID                                                         */
      __IO uint32_t  EPD        :  1;               /*!< The application sets this bit to stop receiving data on an endpoint
                                                         even before the transfer for that endpoint is complete                */
      __IO uint32_t  EPE        :  1;               /*!< the descriptor structure and data buffer with data ready to
                                                         receive data is setup                                                 */
    } DOEPCTL12_b;                                  /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED128;

  union {
    __IO uint32_t  DOEPINT12;                       /*!< Device OUT Endpoint-n Interrupt Register                              */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  EPD        :  1;               /*!< Endpoint Disabled Interrupt                                           */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
      __IO uint32_t  SETUP      :  1;               /*!< Only for Control OUT endpoints, the SETUP phase for the control
                                                         endpoint is complete                                                  */
      __IO uint32_t  OUTTRWEPD  :  1;               /*!< OUT Token Received When Endpoint Disabled                             */
      __IO uint32_t  SPRFCW     :  1;               /*!< Only for Control OUT endpoints, the host has switched from data
                                                         phase to the status phase of a Control Write transfer                 */
      __IO uint32_t  B2BSETUPPR :  1;               /*!< to Control OUT endpoints only, received more than three back-to-back
                                                         SETUP packets for this particular endpoint                            */
      __I  uint32_t  TFE        :  1;               /*!< either half or completely empty depending on GAHBCFG.NPTxFEmpLvl      */
      __IO uint32_t  OUTPE      :  1;               /*!< an overflow or a CRC error for an OUT packet                          */
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
           uint32_t             :  2;
      __IO uint32_t  BE         :  1;               /*!< Babble Error                                                          */
      __IO uint32_t  NAK        :  1;               /*!< a NAK is transmitted                                                  */
      __IO uint32_t  NYET       :  1;               /*!< a NYET response is transmitted                                        */
    } DOEPINT12_b;                                  /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED129;

  union {
    __IO uint32_t  DOEPTSIZ12;                      /*!< Device OUT Endpoint-n Transfer Size Register                          */

    struct {
      __IO uint32_t  SIZE       : 19;               /*!< Indicates the transfer size in bytes for endpoint 0                   */
      __IO uint32_t  PACKET_CNT : 10;               /*!< the total number of USB packets                                       */
      __IO uint32_t  SETUPCNT_PID:  2;              /*!< To control OUT Endpoints only, back-to-back SETUP data packets.
                                                         To isochronous OUT endpoints, data PID received in the last
                                                          packet                                                               */
    } DOEPTSIZ12_b;                                 /*!< BitSize                                                               */
  };
  __IO uint32_t  DOEPDMA12;                         /*!< Device OUT Endpoint-n DMA Address Register                            */
  __I  uint32_t  RESERVED130;
  __I  uint32_t  DOEPDMAB12;                        /*!< Device OUT Endpoint-n DMA Buffer Address Register                     */

  union {
    __IO uint32_t  DOEPCTL13;                       /*!< Device OUT Endpoint N Control Register                                */

    struct {
      __IO uint32_t  MPS        : 11;               /*!< Indicates the maximum packet size of the associated endpoint          */
           uint32_t             :  4;
      __IO uint32_t  UAE        :  1;               /*!< Indicates whether this endpoint is active                             */
      __I  uint32_t  DPID       :  1;               /*!< Endpoint Data PID                                                     */
      __I  uint32_t  NAK        :  1;               /*!< The core is transmitting NAK handshakes on this endpoint if
                                                         set                                                                   */
      __IO uint32_t  EP_TYPE    :  2;               /*!< Indicates the transfer type selected.                                 */
      __IO uint32_t  EC         :  1;               /*!< Doesn't check the correctness of OUT packets before transferring      */
      __IO uint32_t  STALL      :  1;               /*!< To non-control, non-isochronous OUT endpoints, stall all tokens.
                                                         To control endpoints, response an ACK                                 */
           uint32_t             :  4;
      __O  uint32_t  CNAK       :  1;               /*!< A write to this bit clears the NAK bit for the endpoint               */
      __O  uint32_t  SNAK       :  1;               /*!< A write to this bit sets the NAK bit for the endpoint                 */
      __O  uint32_t  SET_D0_PID :  1;               /*!< Set DATA0 PID                                                         */
      __O  uint32_t  SET_D1_PID :  1;               /*!< Set DATA1 PID                                                         */
      __IO uint32_t  EPD        :  1;               /*!< The application sets this bit to stop receiving data on an endpoint
                                                         even before the transfer for that endpoint is complete                */
      __IO uint32_t  EPE        :  1;               /*!< the descriptor structure and data buffer with data ready to
                                                         receive data is setup                                                 */
    } DOEPCTL13_b;                                  /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED131;

  union {
    __IO uint32_t  DOEPINT13;                       /*!< Device OUT Endpoint-n Interrupt Register                              */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  EPD        :  1;               /*!< Endpoint Disabled Interrupt                                           */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
      __IO uint32_t  SETUP      :  1;               /*!< Only for Control OUT endpoints, the SETUP phase for the control
                                                         endpoint is complete                                                  */
      __IO uint32_t  OUTTRWEPD  :  1;               /*!< OUT Token Received When Endpoint Disabled                             */
      __IO uint32_t  SPRFCW     :  1;               /*!< Only for Control OUT endpoints, the host has switched from data
                                                         phase to the status phase of a Control Write transfer                 */
      __IO uint32_t  B2BSETUPPR :  1;               /*!< to Control OUT endpoints only, received more than three back-to-back
                                                         SETUP packets for this particular endpoint                            */
      __I  uint32_t  TFE        :  1;               /*!< either half or completely empty depending on GAHBCFG.NPTxFEmpLvl      */
      __IO uint32_t  OUTPE      :  1;               /*!< an overflow or a CRC error for an OUT packet                          */
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
           uint32_t             :  2;
      __IO uint32_t  BE         :  1;               /*!< Babble Error                                                          */
      __IO uint32_t  NAK        :  1;               /*!< a NAK is transmitted                                                  */
      __IO uint32_t  NYET       :  1;               /*!< a NYET response is transmitted                                        */
    } DOEPINT13_b;                                  /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED132;

  union {
    __IO uint32_t  DOEPTSIZ13;                      /*!< Device OUT Endpoint-n Transfer Size Register                          */

    struct {
      __IO uint32_t  SIZE       : 19;               /*!< Indicates the transfer size in bytes for endpoint 0                   */
      __IO uint32_t  PACKET_CNT : 10;               /*!< the total number of USB packets                                       */
      __IO uint32_t  SETUPCNT_PID:  2;              /*!< To control OUT Endpoints only, back-to-back SETUP data packets.
                                                         To isochronous OUT endpoints, data PID received in the last
                                                          packet                                                               */
    } DOEPTSIZ13_b;                                 /*!< BitSize                                                               */
  };
  __IO uint32_t  DOEPDMA13;                         /*!< Device OUT Endpoint-n DMA Address Register                            */
  __I  uint32_t  RESERVED133;
  __I  uint32_t  DOEPDMAB13;                        /*!< Device OUT Endpoint-n DMA Buffer Address Register                     */

  union {
    __IO uint32_t  DOEPCTL14;                       /*!< Device OUT Endpoint N Control Register                                */

    struct {
      __IO uint32_t  MPS        : 11;               /*!< Indicates the maximum packet size of the associated endpoint          */
           uint32_t             :  4;
      __IO uint32_t  UAE        :  1;               /*!< Indicates whether this endpoint is active                             */
      __I  uint32_t  DPID       :  1;               /*!< Endpoint Data PID                                                     */
      __I  uint32_t  NAK        :  1;               /*!< The core is transmitting NAK handshakes on this endpoint if
                                                         set                                                                   */
      __IO uint32_t  EP_TYPE    :  2;               /*!< Indicates the transfer type selected.                                 */
      __IO uint32_t  EC         :  1;               /*!< Doesn't check the correctness of OUT packets before transferring      */
      __IO uint32_t  STALL      :  1;               /*!< To non-control, non-isochronous OUT endpoints, stall all tokens.
                                                         To control endpoints, response an ACK                                 */
           uint32_t             :  4;
      __O  uint32_t  CNAK       :  1;               /*!< A write to this bit clears the NAK bit for the endpoint               */
      __O  uint32_t  SNAK       :  1;               /*!< A write to this bit sets the NAK bit for the endpoint                 */
      __O  uint32_t  SET_D0_PID :  1;               /*!< Set DATA0 PID                                                         */
      __O  uint32_t  SET_D1_PID :  1;               /*!< Set DATA1 PID                                                         */
      __IO uint32_t  EPD        :  1;               /*!< The application sets this bit to stop receiving data on an endpoint
                                                         even before the transfer for that endpoint is complete                */
      __IO uint32_t  EPE        :  1;               /*!< the descriptor structure and data buffer with data ready to
                                                         receive data is setup                                                 */
    } DOEPCTL14_b;                                  /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED134;

  union {
    __IO uint32_t  DOEPINT14;                       /*!< Device OUT Endpoint-n Interrupt Register                              */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  EPD        :  1;               /*!< Endpoint Disabled Interrupt                                           */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
      __IO uint32_t  SETUP      :  1;               /*!< Only for Control OUT endpoints, the SETUP phase for the control
                                                         endpoint is complete                                                  */
      __IO uint32_t  OUTTRWEPD  :  1;               /*!< OUT Token Received When Endpoint Disabled                             */
      __IO uint32_t  SPRFCW     :  1;               /*!< Only for Control OUT endpoints, the host has switched from data
                                                         phase to the status phase of a Control Write transfer                 */
      __IO uint32_t  B2BSETUPPR :  1;               /*!< to Control OUT endpoints only, received more than three back-to-back
                                                         SETUP packets for this particular endpoint                            */
      __I  uint32_t  TFE        :  1;               /*!< either half or completely empty depending on GAHBCFG.NPTxFEmpLvl      */
      __IO uint32_t  OUTPE      :  1;               /*!< an overflow or a CRC error for an OUT packet                          */
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
           uint32_t             :  2;
      __IO uint32_t  BE         :  1;               /*!< Babble Error                                                          */
      __IO uint32_t  NAK        :  1;               /*!< a NAK is transmitted                                                  */
      __IO uint32_t  NYET       :  1;               /*!< a NYET response is transmitted                                        */
    } DOEPINT14_b;                                  /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED135;

  union {
    __IO uint32_t  DOEPTSIZ14;                      /*!< Device OUT Endpoint-n Transfer Size Register                          */

    struct {
      __IO uint32_t  SIZE       : 19;               /*!< Indicates the transfer size in bytes for endpoint 0                   */
      __IO uint32_t  PACKET_CNT : 10;               /*!< the total number of USB packets                                       */
      __IO uint32_t  SETUPCNT_PID:  2;              /*!< To control OUT Endpoints only, back-to-back SETUP data packets.
                                                         To isochronous OUT endpoints, data PID received in the last
                                                          packet                                                               */
    } DOEPTSIZ14_b;                                 /*!< BitSize                                                               */
  };
  __IO uint32_t  DOEPDMA14;                         /*!< Device OUT Endpoint-n DMA Address Register                            */
  __I  uint32_t  RESERVED136;
  __I  uint32_t  DOEPDMAB14;                        /*!< Device OUT Endpoint-n DMA Buffer Address Register                     */

  union {
    __IO uint32_t  DOEPCTL15;                       /*!< Device OUT Endpoint N Control Register                                */

    struct {
      __IO uint32_t  MPS        : 11;               /*!< Indicates the maximum packet size of the associated endpoint          */
           uint32_t             :  4;
      __IO uint32_t  UAE        :  1;               /*!< Indicates whether this endpoint is active                             */
      __I  uint32_t  DPID       :  1;               /*!< Endpoint Data PID                                                     */
      __I  uint32_t  NAK        :  1;               /*!< The core is transmitting NAK handshakes on this endpoint if
                                                         set                                                                   */
      __IO uint32_t  EP_TYPE    :  2;               /*!< Indicates the transfer type selected.                                 */
      __IO uint32_t  EC         :  1;               /*!< Doesn't check the correctness of OUT packets before transferring      */
      __IO uint32_t  STALL      :  1;               /*!< To non-control, non-isochronous OUT endpoints, stall all tokens.
                                                         To control endpoints, response an ACK                                 */
           uint32_t             :  4;
      __O  uint32_t  CNAK       :  1;               /*!< A write to this bit clears the NAK bit for the endpoint               */
      __O  uint32_t  SNAK       :  1;               /*!< A write to this bit sets the NAK bit for the endpoint                 */
      __O  uint32_t  SET_D0_PID :  1;               /*!< Set DATA0 PID                                                         */
      __O  uint32_t  SET_D1_PID :  1;               /*!< Set DATA1 PID                                                         */
      __IO uint32_t  EPD        :  1;               /*!< The application sets this bit to stop receiving data on an endpoint
                                                         even before the transfer for that endpoint is complete                */
      __IO uint32_t  EPE        :  1;               /*!< the descriptor structure and data buffer with data ready to
                                                         receive data is setup                                                 */
    } DOEPCTL15_b;                                  /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED137;

  union {
    __IO uint32_t  DOEPINT15;                       /*!< Device OUT Endpoint-n Interrupt Register                              */

    struct {
      __IO uint32_t  TC         :  1;               /*!< Transfer completed normally without any errors                        */
      __IO uint32_t  EPD        :  1;               /*!< Endpoint Disabled Interrupt                                           */
      __IO uint32_t  AHB_ERR    :  1;               /*!< there is an AHB error during AHB read/write                           */
      __IO uint32_t  SETUP      :  1;               /*!< Only for Control OUT endpoints, the SETUP phase for the control
                                                         endpoint is complete                                                  */
      __IO uint32_t  OUTTRWEPD  :  1;               /*!< OUT Token Received When Endpoint Disabled                             */
      __IO uint32_t  SPRFCW     :  1;               /*!< Only for Control OUT endpoints, the host has switched from data
                                                         phase to the status phase of a Control Write transfer                 */
      __IO uint32_t  B2BSETUPPR :  1;               /*!< to Control OUT endpoints only, received more than three back-to-back
                                                         SETUP packets for this particular endpoint                            */
      __I  uint32_t  TFE        :  1;               /*!< either half or completely empty depending on GAHBCFG.NPTxFEmpLvl      */
      __IO uint32_t  OUTPE      :  1;               /*!< an overflow or a CRC error for an OUT packet                          */
      __IO uint32_t  BNA        :  1;               /*!< Buffer Not Available                                                  */
           uint32_t             :  2;
      __IO uint32_t  BE         :  1;               /*!< Babble Error                                                          */
      __IO uint32_t  NAK        :  1;               /*!< a NAK is transmitted                                                  */
      __IO uint32_t  NYET       :  1;               /*!< a NYET response is transmitted                                        */
    } DOEPINT15_b;                                  /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED138;

  union {
    __IO uint32_t  DOEPTSIZ15;                      /*!< Device OUT Endpoint-n Transfer Size Register                          */

    struct {
      __IO uint32_t  SIZE       : 19;               /*!< Indicates the transfer size in bytes for endpoint 0                   */
      __IO uint32_t  PACKET_CNT : 10;               /*!< the total number of USB packets                                       */
      __IO uint32_t  SETUPCNT_PID:  2;              /*!< To control OUT Endpoints only, back-to-back SETUP data packets.
                                                         To isochronous OUT endpoints, data PID received in the last
                                                          packet                                                               */
    } DOEPTSIZ15_b;                                 /*!< BitSize                                                               */
  };
  __IO uint32_t  DOEPDMA15;                         /*!< Device OUT Endpoint-n DMA Address Register                            */
  __I  uint32_t  RESERVED139;
  __I  uint32_t  DOEPDMAB15;                        /*!< Device OUT Endpoint-n DMA Buffer Address Register                     */
} USB_Type;


/* ================================================================================ */
/* ================                   GLOBAL_CTRL                  ================ */
/* ================================================================================ */


/**
  * @brief GLOBAL_CTRL (GLOBAL_CTRL)
  */

typedef struct {                                    /*!< GLOBAL_CTRL Structure                                                 */

  union {
    __I  uint32_t  AES_STATUS;                      /*!< AES status                                                            */

    struct {
      __I  uint32_t  RD_ALMOST_EMPTY:  1;           /*!< FIFO read almost empty                                                */
      __I  uint32_t  RD_EMPTY   :  1;               /*!< FIFO read empty                                                       */
      __I  uint32_t  WR_FULL_ALMOST:  1;            /*!< FIFO write almost full                                                */
      __I  uint32_t  WR_FULL    :  1;               /*!< FIFO write full                                                       */
      __I  uint32_t  IDLE       :  1;               /*!< decryption finish                                                     */
    } AES_STATUS_b;                                 /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED0[253];

  union {
    __IO uint32_t  CLK_SEL_0;                       /*!< clock select 0                                                        */

    struct {
      __IO uint32_t  CAN1_CLK   :  2;               /*!< CAN1 clock frequency dividor based on system clock, which should
                                                         be 1/32, 1/4, 1/8, 1/16 from 0 to 3                                   */
      __IO uint32_t  CAN0_CLK   :  2;               /*!< CAN0 clock frequency dividor based on system clock, which should
                                                         be 1/32, 1/4, 1/8, 1/16 from 0 to 3                                   */
      __IO uint32_t  I2C1_CLK   :  2;               /*!< I2C1 clock frequency dividor based on system clock, which should
                                                         be 1/2, 1/4, 1/8, 1/16 from 0 to 3                                    */
      __IO uint32_t  I2C0_CLK   :  2;               /*!< I2C0 clock frequency dividor based on system clock, which should
                                                         be 1/2, 1/4, 1/8, 1/16 from 0 to 3                                    */
      __IO uint32_t  SPI1_CLK   :  2;               /*!< SPI1 clock frequency dividor based on system clock, which should
                                                         be 1/2, 1/4, 1/8, 1/16 from 0 to 3                                    */
      __IO uint32_t  SPI0_CLK   :  2;               /*!< SPI0 clock frequency dividor based on system clock, which should
                                                         be 1/2, 1/4, 1/8, 1/16 from 0 to 3                                    */
      __IO uint32_t  UART1_CLK  :  2;               /*!< UART1 clock frequency dividor based on system clock, which should
                                                         be 1/2, 1/4, 1/8, 1/16 from 0 to 3                                    */
      __IO uint32_t  UART0_CLK  :  2;               /*!< UART0 clock frequency dividor based on system clock, which should
                                                         be 1/2, 1/4, 1/8, 1/16 from 0 to 3                                    */
      __IO uint32_t  RTC_CLK    :  2;               /*!< RTC clock frequency dividor based on system clock, which should
                                                         be 1/2, 1/4, 1/8, 1/16 from 0 to 3                                    */
      __IO uint32_t  GPIO_CLK   :  2;               /*!< GPIO clock frequency dividor based on system clock, which should
                                                         be 1/2, 1/4, 1/8, 1/16 from 0 to 3                                    */
      __IO uint32_t  TIMER_CLK  :  2;               /*!< TIMER clock frequency dividor based on system clock, which should
                                                         be 1/2, 1/4, 1/8, 1/16 from 0 to 3                                    */
      __IO uint32_t  WDG_CLK    :  2;               /*!< watchdog clock frequency dividor based on system clock, which
                                                         should be 1/2, 1/4, 1/8, 1/16 from 0 to 3                             */
           uint32_t             :  2;
      __IO uint32_t  FLASH_CLK  :  2;               /*!< FLASH clock frequency dividor based on system clock, which should
                                                         be 1/1, 1/2, 1/4, 1/8 from 0 to 3                                     */
      __IO uint32_t  DMA_AHB_CLK:  2;               /*!< DMA AHB bus clock frequency dividor based on system clock, which
                                                         should be 1/1, 1/2, 1/4, 1/8 from 0 to 3                              */
      __IO uint32_t  USB_AHB_CLK:  2;               /*!< USB AHB bus clock frequency dividor based on system clock, which
                                                         should be 1/1, 1/2, 1/4, 1/8 from 0 to 3                              */
    } CLK_SEL_0_b;                                  /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  CLK_SEL_1;                       /*!< clock select 1                                                        */

    struct {
      __IO uint32_t  ETH_AHB_CLK:  2;               /*!< ETH_AHB clock frequency dividor based on system clock, which
                                                         should be 1/1, 1/2, 1/4, 1/8 from 0 to 3                              */
      __IO uint32_t  DDR_CLK    :  2;               /*!< DDR clock frequency dividor based on system clock, which should
                                                         be 1/1, 1/2, 1/4, 1/8 from 0 to 3                                     */
           uint32_t             :  4;
      __IO uint32_t  ADC_CLK    :  2;               /*!< ADC clock frequency dividor based on system clock, which should
                                                         be 1/8, 1/16, 1/32, external from 0 to 3                              */
      __IO uint32_t  EFUSE_CLK  :  2;               /*!< EFUSE clock frequency dividor based on system clock, which should
                                                         be 1/2, 1/4, 1/8, 1/16 from 0 to 3                                    */
      __IO uint32_t  SYS_CLK    :  4;               /*!< system clock clock frequency dividor based on system clock,
                                                         which should be oscillator(0), DLL(1), crystal(2), external(3),
                                                          JTAG(4), PS(8)                                                       */
      __IO uint32_t  UART2_CLK  :  2;               /*!< UART2 clock frequency dividor based on system clock, which should
                                                         be 1/2, 1/4, 1/8, 1/16 from 0 to 3                                    */
      __IO uint32_t  UTMI_CLK   :  1;               /*!< UTMI clock came from on-chip usb phy(0) or off-chip usb phy(1)        */
    } CLK_SEL_1_b;                                  /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  USB_PHY_CTRL;                    /*!< USB Phy Control Register                                              */

    struct {
      __IO uint32_t  BITSTUFF   :  1;               /*!< 0: No bit stuff                                                       */
      __IO uint32_t  XTLSEL     :  1;               /*!< 0: 12MHz                                                              */
      __IO uint32_t  PLL        :  1;               /*!< PLL mode                                                              */
      __IO uint32_t  VOLDET     :  1;               /*!< Voltage Detector Enable, 0: Disable                                   */
      __IO uint32_t  IDUP       :  1;               /*!< 0: ID is uplled up through 33k Ohm resister                           */
      __IO uint32_t  CKISEL     :  1;               /*!< Clock selection, 0: Crystal, 1: Internal Clock                        */
      __IO uint32_t  FMOD       :  1;               /*!< 1: Normal                                                             */
      __IO uint32_t  SQUELCH    :  3;               /*!< Squelch Reference Voltage, 000: 27.5mV, 001: 137.5mV, 111: 220mV      */
      __IO uint32_t  HDISCDT    :  3;               /*!< Host Disconnect Detection Reference Voltage, 000: 500mV, 100:
                                                         588mV, 111: 654mV                                                     */
      __IO uint32_t  PRTSEL     :  1;               /*!< 0: Internal OTG PHY, 1: UTMI to External PHY                          */
      __IO uint32_t  RSTPRT     :  1;               /*!< 0: The reverse of usb_rst_n will reset, 1: Reset OTG PHY              */
    } USB_PHY_CTRL_b;                               /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  RTC_INT_EN;                      /*!< RTC interrupt enable Register                                         */

    struct {
      __IO uint32_t  SECOND     :  1;               /*!< 1s interrupt enable                                                   */
      __IO uint32_t  MILLSECOND :  1;               /*!< 1ms interrupt enable                                                  */
    } RTC_INT_EN_b;                                 /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED1;

  union {
    __IO uint32_t  NMI_SEL;                         /*!< nmi interrupt selection                                               */

    struct {
      __IO uint32_t  NMI        :  7;               /*!< NMI interrupt ID                                                      */
    } NMI_SEL_b;                                    /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED2;
  __IO uint32_t  AES_TARGET_ADDR;                   /*!< AES target address, default is frame decoder address(0x41800000)      */

  union {
    __IO uint32_t  AES_BURST_TYPE;                  /*!< AES burst type                                                        */

    struct {
      __IO uint32_t  TYPE       :  2;               /*!< burst type, fixed(0), incr(1)                                         */
    } AES_BURST_TYPE_b;                             /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED3[3];

  union {
    __IO uint32_t  ICACHE;                          /*!< ICACHE Enable                                                         */

    struct {
      __IO uint32_t  EN         :  1;               /*!< ICACHE Enable                                                         */
    } ICACHE_b;                                     /*!< BitSize                                                               */
  };
  __IO uint32_t  IBUSOFF;                           /*!< Code Bus Offset                                                       */
  __IO uint32_t  DBUSOFF;                           /*!< Data Bus Offset                                                       */
  __IO uint32_t  EXTADDR;                           /*!< Bus Ext Addr                                                          */
} GLOBAL_CTRL_Type;


/* ================================================================================ */
/* ================                       AES                      ================ */
/* ================================================================================ */


/**
  * @brief AES (AES)
  */

typedef struct {                                    /*!< AES Structure                                                         */
  __IO uint32_t  FIFO;                              /*!< data FIFO to be decoded                                               */

  union {
    __O  uint32_t  FIFO_CLEAR;                      /*!< clear data FIFO                                                       */

    struct {
      __O  uint32_t  CLEAR      :  1;               /*!< clear after write 1 and write 0                                       */
    } FIFO_CLEAR_b;                                 /*!< BitSize                                                               */
  };
} AES_Type;


/* ================================================================================ */
/* ================                      DDRC                      ================ */
/* ================================================================================ */


/**
  * @brief DDR_CFG (DDRC)
  */

typedef struct {                                    /*!< DDRC Structure                                                        */
  __IO uint32_t  CMD;                               /*!< DDR commands to program                                               */

  union {
    __IO uint32_t  CTRL;                            /*!< DDR Control                                                           */

    struct {
      __IO uint32_t  TO         :  1;               /*!< Take over DDRC siggen                                                 */
      __IO uint32_t  CLR        :  1;               /*!< Clear commands in FIFO                                                */
      __O  uint32_t  STR        :  1;               /*!< Start to execute the commands in FIFO                                 */
    } CTRL_b;                                       /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  MODE;                            /*!< DDR mode                                                              */

    struct {
      __IO uint32_t  MODE       :  6;               /*!< DDRC Mode                                                             */
           uint32_t             :  2;
      __IO uint32_t  LANE       :  1;               /*!< LANE synchronization logic bypass                                     */
           uint32_t             :  3;
      __IO uint32_t  ADEC       :  1;               /*!< address decoder mapping                                               */
           uint32_t             :  3;
      __IO uint32_t  B16        :  2;               /*!< Active 16 bit DQ position when the unmber of DQ IO is 16              */
           uint32_t             :  6;
      __IO uint32_t  CLKPOL     :  2;               /*!< DQS clkpol set by user on the PHY                                     */
    } MODE_b;                                       /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  QUE;                             /*!< DDRC queue depth                                                      */

    struct {
      __IO uint32_t  DEPTH      :  1;               /*!< DDRC queue depth                                                      */
    } QUE_b;                                        /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  REF;                             /*!< Refresh control                                                       */

    struct {
      __IO uint32_t  THRD       :  5;               /*!< Number of refresh requests which can be postponed                     */
           uint32_t             :  3;
      __IO uint32_t  TRIG       :  4;               /*!< Number of refresh requests every dl_refi                              */
           uint32_t             :  4;
      __IO uint32_t  TIME       : 16;               /*!< Refresh interval time                                                 */
    } REF_b;                                        /*!< BitSize                                                               */
  };

  union {
    __O  uint32_t  REF_TRIG;                        /*!< Refresh trigger                                                       */

    struct {
      __O  uint32_t  GO         :  1;               /*!< Write 1 to trigger one refresh request by cbus                        */
    } REF_TRIG_b;                                   /*!< BitSize                                                               */
  };

  union {
    __O  uint32_t  ZQ_TRIG;                         /*!< ZQCTL trigger                                                         */

    struct {
      __O  uint32_t  CS         :  1;               /*!< Write 1 to trigger one ZQCS request by cbus                           */
      __O  uint32_t  CL         :  1;               /*!< Write 1 to trigger one ZQCL request by cbus                           */
    } ZQ_TRIG_b;                                    /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  ZQCSR;                           /*!< ZQCSR                                                                 */

    struct {
      __IO uint32_t  EN         :  1;               /*!< Enable ZQCS request                                                   */
      __IO uint32_t  PRI        :  1;               /*!< 0: DMA access prior to ZQCS, 1: ZQCS prior to DMA access              */
    } ZQCSR_b;                                      /*!< BitSize                                                               */
  };
  __IO uint32_t  ZQCSI;                             /*!< ZQCS interval time                                                    */

  union {
    __IO uint32_t  RCD;                             /*!< t(RCD)                                                                */

    struct {
      __IO uint32_t  DI         :  5;               /*!< t(RCD), delay from ACT command to RW command of same bank             */
    } RCD_b;                                        /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  RAS;                             /*!< t(RAS)                                                                */

    struct {
      __IO uint32_t  DI         :  6;               /*!< t(RAS), delay from ACT command to PRE command of same bank            */
    } RAS_b;                                        /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  RP;                              /*!< t(RP)                                                                 */

    struct {
      __IO uint32_t  DI         :  5;               /*!< t(RP), delay from PRE command to ACT/REF/ZQ command                   */
           uint32_t             :  3;
      __IO uint32_t  RPA        :  1;               /*!< 0: t(RP) delay for PREA command; 1: t(RP)+1 delay for PREA command    */
    } RP_b;                                         /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  RC;                              /*!< t(RC)                                                                 */

    struct {
      __IO uint32_t  DI         :  7;               /*!< t(RC), delay from ACT command to ACT command of same bank             */
    } RC_b;                                         /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  RRD;                             /*!< t(RRD)                                                                */

    struct {
      __IO uint32_t  DI         :  4;               /*!< t(RRD), delay from ACT command to ACT command                         */
    } RRD_b;                                        /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  CCD;                             /*!< t(CCD)                                                                */

    struct {
      __IO uint32_t  DI         :  3;               /*!< t(CCD), delay from RW command to RW command                           */
    } CCD_b;                                        /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  RTW;                             /*!< t(RTW)                                                                */

    struct {
      __IO uint32_t  DI         :  5;               /*!< t(RTW), delay from RD command to WR command                           */
    } RTW_b;                                        /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  WTR;                             /*!< t(WTR)                                                                */

    struct {
      __IO uint32_t  DI         :  5;               /*!< t(WTR), delay from WR command to RD command                           */
    } WTR_b;                                        /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  RTP;                             /*!< t(RTP)                                                                */

    struct {
      __IO uint32_t  DI         :  3;               /*!< t(RTP), delay from RD command to PRE command of same bank             */
    } RTP_b;                                        /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  WTP;                             /*!< t(WTP)                                                                */

    struct {
      __IO uint32_t  DI         :  6;               /*!< t(WTP), delay from WR command to PRE command of same bank             */
    } WTP_b;                                        /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  RFC;                             /*!< t(RFC)                                                                */

    struct {
      __IO uint32_t  DI         :  8;               /*!< t(WTP), delay from WR command to PRE command of same bank             */
    } RFC_b;                                        /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  ZQCL;                            /*!< t(ZQoper)                                                             */

    struct {
      __IO uint32_t  DI         :  9;               /*!< t(ZQoper), delay from ZQCL command to REF/ZQ/ACT command              */
    } ZQCL_b;                                       /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  ZQCS;                            /*!< t(ZQCS)                                                               */

    struct {
      __IO uint32_t  DI         :  7;               /*!< t(ZQCS), delay from ZQCS command to REF/ZQ/ACT command                */
    } ZQCS_b;                                       /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  FAW;                             /*!< t(FAW)                                                                */

    struct {
      __IO uint32_t  DI         :  6;               /*!< t(FAW), 4 act command window time                                     */
    } FAW_b;                                        /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  BURST;                           /*!< BURST                                                                 */

    struct {
      __IO uint32_t  LEN        :  1;               /*!< 0: length 8, 1: length 4                                              */
    } BURST_b;                                      /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  PHUNG;                           /*!< PHUNG                                                                 */

    struct {
      __IO uint32_t  MODE       :  1;               /*!< 0: normal mode, 1: prevent read hang mode                             */
      __IO uint32_t  LPM        :  1;               /*!< 1: stop the IO clk                                                    */
    } PHUNG_b;                                      /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  RL;                              /*!< READ Latency                                                          */

    struct {
      __IO uint32_t  VAL        :  5;               /*!< READ Latency                                                          */
    } RL_b;                                         /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  WL;                              /*!< WRITE Latency                                                         */

    struct {
      __IO uint32_t  VAL        :  5;               /*!< WRITE Latency                                                         */
    } WL_b;                                         /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  TRAIN;                           /*!< TRAIN                                                                 */

    struct {
      __IO uint32_t  EN         :  4;               /*!< Enable lane N training mode                                           */
    } TRAIN_b;                                      /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  DQSEN0;                          /*!< Delay cycles of dqsen of byte lane 0                                  */

    struct {
      __IO uint32_t  DL         :  3;               /*!< Delay cycles of dqsen of byte lane 0                                  */
    } DQSEN0_b;                                     /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  DQSEN1;                          /*!< Delay cycles of dqsen of byte lane 1                                  */

    struct {
      __IO uint32_t  DL         :  3;               /*!< Delay cycles of dqsen of byte lane 1                                  */
    } DQSEN1_b;                                     /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  DQSEN2;                          /*!< Delay cycles of dqsen of byte lane 2                                  */

    struct {
      __IO uint32_t  DL         :  3;               /*!< Delay cycles of dqsen of byte lane 2                                  */
    } DQSEN2_b;                                     /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  DQSEN3;                          /*!< Delay cycles of dqsen of byte lane 0                                  */

    struct {
      __IO uint32_t  DL         :  3;               /*!< Delay cycles of dqsen of byte lane 3                                  */
    } DQSEN3_b;                                     /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  ODTH;                            /*!< Delay from WR command to odt high transition                          */

    struct {
      __IO uint32_t  DL         :  5;               /*!< Delay from WR command to odt high transition                          */
    } ODTH_b;                                       /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  ODTL;                            /*!< Delay from WR command to odt low transition                           */

    struct {
      __IO uint32_t  DL         :  5;               /*!< Delay from WR command to odt low transition                           */
    } ODTL_b;                                       /*!< BitSize                                                               */
  };

  union {
    __O  uint32_t  ODT;                             /*!< Used in write leveling mode                                           */

    struct {
      __O  uint32_t  TRIG       :  1;               /*!< 0: trigger odt low, 1: trigger odt high                               */
    } ODT_b;                                        /*!< BitSize                                                               */
  };

  union {
    __O  uint32_t  DQS;                             /*!< Used in write leveling mode                                           */

    struct {
      __O  uint32_t  TRIG       :  1;               /*!< Writing 1 to this register triggers a dqs pulse                       */
    } DQS_b;                                        /*!< BitSize                                                               */
  };

  union {
    __I  uint32_t  STA;                             /*!< Commands FIFO                                                         */

    struct {
      __I  uint32_t  MODE       :  1;               /*!< DDRC in sw_proc mode                                                  */
      __I  uint32_t  EMPTY      :  1;               /*!< Sw_proc command fifo empty                                            */
      __I  uint32_t  FULL       :  1;               /*!< Sw_proc command fifo full                                             */
    } STA_b;                                        /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  INTCTL;                          /*!< Interrupt Control                                                     */

    struct {
      __IO uint32_t  DONE       :  1;               /*!< 0: the sw_proc_done int will not be masked, 1: the sw_proc_done
                                                         int will be masked                                                    */
      __IO uint32_t  ERR        :  1;               /*!< mask of the lane_sync_error interrupt                                 */
           uint32_t             : 14;
      __IO uint32_t  MODE       :  1;               /*!< Interrupt mode: 0: int level active, write 1 to clear; 1: int
                                                         edge active                                                           */
    } INTCTL_b;                                     /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  INTRAW;                          /*!< Interrupt RAW                                                         */

    struct {
      __IO uint32_t  DONE       :  1;               /*!< Int register of sw_proc_done before mask                              */
      __IO uint32_t  ERR        :  1;               /*!< int reg of the lane sync error before masked                          */
    } INTRAW_b;                                     /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  INTSTA;                          /*!< Interrupt STA                                                         */

    struct {
      __IO uint32_t  DONE       :  1;               /*!< Int register of sw_proc_done after mask                               */
      __IO uint32_t  ERR        :  1;               /*!< int register of lane sync error after masked                          */
    } INTSTA_b;                                     /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  PHY;                             /*!< PHY                                                                   */

    struct {
      __IO uint32_t  RST        :  1;               /*!< FPGA version, reset read dq fifo. Low active                          */
    } PHY_b;                                        /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  RDQ;                             /*!< FPGA version, read dq delay of byte lane N                            */

    struct {
      __IO uint32_t  L3         :  6;               /*!< FPGA version, read dq delay of byte lane3                             */
           uint32_t             :  2;
      __IO uint32_t  L2         :  6;               /*!< FPGA version, read dq delay of byte lane2                             */
           uint32_t             :  2;
      __IO uint32_t  L1         :  6;               /*!< FPGA version, read dq delay of byte lane3                             */
           uint32_t             :  2;
      __IO uint32_t  L0         :  7;               /*!< FPGA version, read dq delay of byte lane0                             */
    } RDQ_b;                                        /*!< BitSize                                                               */
  };

  union {
    __I  uint32_t  CALIB;                           /*!< calibration                                                           */

    struct {
      __I  uint32_t  TPU        :  8;               /*!< calibration result values, if fail then 0x40                          */
      __I  uint32_t  TPD        :  8;               /*!< calibration result values, if fail then 0x40                          */
      __I  uint32_t  PDR        :  5;               /*!< calibration result values, if fail then 0x40                          */
      __I  uint32_t  NDR        :  5;               /*!< calibration result values, if fail then 0x40                          */
           uint32_t             :  5;
      __IO uint32_t  EN         :  1;               /*!< trigger the calibration processing which is sensitive to the
                                                         positive edge                                                         */
    } CALIB_b;                                      /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  ITMDLY;                          /*!< "itmdly" is the fine delay trim to the read path "dq", "itmsdly"
                                                         is to the read path of "dqs". From 000 to 111 increasingly,
                                                          each step is about 40ps                                              */

    struct {
      __IO uint32_t  I0         :  4;               /*!< itmdly0                                                               */
      __IO uint32_t  IS0        :  4;               /*!< itmsdly0                                                              */
      __IO uint32_t  I1         :  4;               /*!< itmdly1                                                               */
      __IO uint32_t  IS1        :  4;               /*!< itmsdly1                                                              */
      __IO uint32_t  I2         :  4;               /*!< itmdly2                                                               */
      __IO uint32_t  IS2        :  4;               /*!< itmsdly2                                                              */
      __IO uint32_t  I3         :  4;               /*!< itmdly3                                                               */
      __IO uint32_t  IS3        :  4;               /*!< itmsdly3                                                              */
    } ITMDLY_b;                                     /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  TUNE;                            /*!< CALIB_TUNE                                                            */

    struct {
      __IO uint32_t  TPU        :  4;               /*!< tpu_tune, finial val = tune[3] ? val - tune : val + tune              */
      __IO uint32_t  TPD        :  4;               /*!< tpd_tune, tune[3:0] for TPD/TPU, [2:0] is the tune val                */
      __IO uint32_t  PDR        :  4;               /*!< pdr_tune, inial val = tune[2] ? val - tune : val + tune               */
      __IO uint32_t  NDR        :  4;               /*!< ndr_tune, tune[2:0] for NDR/PDR, [1:0] is the tune val                */
    } TUNE_b;                                       /*!< BitSize                                                               */
  };

  union {
    __IO uint32_t  RD_SEL;                          /*!< RD_WINDOWS_SEL                                                        */

    struct {
      __IO uint32_t  PHY_SEL    :  3;               /*!< To fix the phy read valid issue, this is to adjust the read
                                                         data valid window to match the phy read valid by cycle level          */
    } RD_SEL_b;                                     /*!< BitSize                                                               */
  };
} DDRC_Type;


/* ================================================================================ */
/* ================                     PDLOCK                     ================ */
/* ================================================================================ */


/**
  * @brief PLL DLL LOCK (PDLOCK)
  */

typedef struct {                                    /*!< PDLOCK Structure                                                      */

  union {
    __I  uint32_t  GCLK;                            /*!< GCLK                                                                  */

    struct {
      __I  uint32_t  C1R2P      :  1;               /*!< gclk_c1r2_pll_lock                                                    */
      __I  uint32_t  C1R1P      :  1;               /*!< gclk_c1r1_pll_lock                                                    */
      __I  uint32_t  C2R1P      :  1;               /*!< gclk_c2r1_pll_lock                                                    */
      __I  uint32_t  C2R2P      :  1;               /*!< gclk_c2r2_pll_lock                                                    */
      __I  uint32_t  C1R2D      :  1;               /*!< gclk_c1r2_dll_lock                                                    */
      __I  uint32_t  C1R1D      :  1;               /*!< gclk_c1r1_dll_lock                                                    */
      __I  uint32_t  C2R1D      :  1;               /*!< gclk_c2r1_dll_lock                                                    */
      __I  uint32_t  C2R2D      :  1;               /*!< gclk_c2r2_dll_lock                                                    */
    } GCLK_b;                                       /*!< BitSize                                                               */
  };
} PDLOCK_Type;


/* ================================================================================ */
/* ================                     PDPROT                     ================ */
/* ================================================================================ */


/**
  * @brief PLL DLL PROTECT (PDPROT)
  */

typedef struct {                                    /*!< PDPROT Structure                                                      */

  union {
    __O  uint32_t  LOCK;                            /*!< LOCK                                                                  */

    struct {
      __O  uint32_t  EN         :  1;               /*!< Enable the PLL DLL Lock to Protect it                                 */
    } LOCK_b;                                       /*!< BitSize                                                               */
  };
} PDPROT_Type;


/* ================================================================================ */
/* ================                    CFG_CTRL                    ================ */
/* ================================================================================ */


/**
  * @brief CFG_CTRL (CFG_CTRL)
  */

typedef struct {                                    /*!< CFG_CTRL Structure                                                    */
  __I  uint32_t  RESERVED0[3];

  union {
    __IO uint32_t  DONE;                            /*!< DONE CFG                                                              */

    struct {
      __IO uint32_t  CMD        :  1;               /*!< Write 1 indicate all chain data write over                            */
      __IO uint32_t  STA        :  1;               /*!< 1= all chain config process over, chip is in user mode                */
    } DONE_b;                                       /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED1[34];

  union {
    __IO uint32_t  PDLLSTR;                         /*!< PLL DLL RESET                                                         */

    struct {
      __IO uint32_t  C1R1P      :  1;               /*!< C1r1_rstpll_n, low active                                             */
      __IO uint32_t  C1R2P      :  1;               /*!< C1r2_rstpll_n, low active                                             */
      __IO uint32_t  C2R1P      :  1;               /*!< C2r1_rstpll_n, low active                                             */
      __IO uint32_t  C2R2P      :  1;               /*!< C2r2_rstpll_n, low active                                             */
      __IO uint32_t  C1R1D      :  1;               /*!< C1r1_rstdll_n, low active                                             */
      __IO uint32_t  C1R2D      :  1;               /*!< C1r2_rstdll_n, low active                                             */
      __IO uint32_t  C2R1D      :  1;               /*!< C2r1_rstdll_n, low active                                             */
      __IO uint32_t  C2R2D      :  1;               /*!< C2r2_rstdll_n, low active                                             */
    } PDLLSTR_b;                                    /*!< BitSize                                                               */
  };
} CFG_CTRL_Type;


/* ================================================================================ */
/* ================                   SOFT_RESET                   ================ */
/* ================================================================================ */


/**
  * @brief SUB SOFT RESET (SOFT_RESET)
  */

typedef struct {                                    /*!< SOFT_RESET Structure                                                  */

  union {
    __IO uint32_t  SOFTRST;                         /*!< SOFTRST                                                               */

    struct {
      __IO uint32_t  CAN1_n     :  1;               /*!< soft_rst_can1_n                                                       */
      __IO uint32_t  CAN0_n     :  1;               /*!< soft_rst_can0_n                                                       */
      __IO uint32_t  I2C1_n     :  1;               /*!< soft_rst_i2c1_n                                                       */
      __IO uint32_t  I2C0_n     :  1;               /*!< soft_rst_i2c0_n                                                       */
      __IO uint32_t  SPI1_n     :  1;               /*!< soft_rst_spi1_n                                                       */
      __IO uint32_t  SPI0_n     :  1;               /*!< soft_rst_spi0_n                                                       */
      __IO uint32_t  UART1_n    :  1;               /*!< soft_rst_uart1_n                                                      */
      __IO uint32_t  UART0_n    :  1;               /*!< soft_rst_uart0_n                                                      */
      __IO uint32_t  RTC_n      :  1;               /*!< soft_rst_rtc_n                                                        */
      __IO uint32_t  GPIO_n     :  1;               /*!< soft_rst_gpio_n                                                       */
      __IO uint32_t  TIMER_n    :  1;               /*!< soft_rst_timer_n                                                      */
      __IO uint32_t  WDT_n      :  1;               /*!< soft_rst_wdt_n                                                        */
      __IO uint32_t  LVDS_n     :  1;               /*!< soft_rst_lvds_n                                                       */
      __IO uint32_t  FLS_n      :  1;               /*!< soft_rst_fls_n                                                        */
      __IO uint32_t  DMAC_AHB_n :  1;               /*!< soft_rst_dmac_ahb_n                                                   */
      __IO uint32_t  USB_AHB_n  :  1;               /*!< soft_rst_usb_ahb_n                                                    */
      __IO uint32_t  ETH_AHB_n  :  1;               /*!< soft_rst_eth_ahb_n                                                    */
      __IO uint32_t  DDRC_n     :  1;               /*!< soft_rst_ddrc_n                                                       */
      __IO uint32_t  ARM_HCLK_n :  1;               /*!< soft_rst_arm_HCLK_n                                                   */
      __IO uint32_t  _48_n      :  1;               /*!< soft_rst_48_n                                                         */
      __IO uint32_t  UTM_n      :  1;               /*!< soft_rst_utmi_n                                                       */
      __IO uint32_t  CACHE_n    :  1;               /*!< soft_rst_cache_n                                                      */
      __IO uint32_t  USB_n      :  1;               /*!< soft_rst_cache_n                                                      */
      __IO uint32_t  ETH_RX_n   :  1;               /*!< soft_rst_eth_rx_i_n                                                   */
      __IO uint32_t  ETH_TX_n   :  1;               /*!< soft_rst_eth_tx_i_n                                                   */
      __IO uint32_t  ADC_n      :  1;               /*!< soft_rst_adc_n                                                        */
      __IO uint32_t  EFUSE_n    :  1;               /*!< soft_rst_efuse_n                                                      */
      __IO uint32_t  Reserved1_n:  1;               /*!< Reserved11                                                            */
      __IO uint32_t  AES_n      :  1;               /*!< soft_rst_aes_n                                                        */
      __IO uint32_t  UART2_n    :  1;               /*!< soft_rst_uart2_n                                                      */
      __IO uint32_t  AS_n       :  1;               /*!< soft_rst_as_n                                                         */
      __IO uint32_t  FDCD_n     :  1;               /*!< soft_rst_fdcd_n                                                       */
    } SOFTRST_b;                                    /*!< BitSize                                                               */
  };
} SOFT_RESET_Type;


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
/* ================              Peripheral memory map             ================ */
/* ================================================================================ */

#define UART0_BASE                      0x41005000UL
#define UART1_BASE                      0x4100C000UL
#define UART2_BASE                      0x4100E000UL
#define WDG_BASE                        0x41001000UL
#define TIMER0_BASE                     0x41000000UL
#define TIMER1_BASE                     0x41000020UL
#define TIMER2_BASE                     0x41000040UL
#define TIMER3_BASE                     0x41000060UL
#define SPI0_BASE                       0x41004000UL
#define SPI1_BASE                       0x4100B000UL
#define I2C0_BASE                       0x41003000UL
#define I2C1_BASE                       0x4100A000UL
#define RTC_BASE                        0x41007004UL
#define GPIO_BASE                       0x41002000UL
#define NOR_FLASH_BASE                  0x40800000UL
#define ADC_BASE                        0x41006000UL
#define EFUSE_BASE                      0x41008000UL
#define CAN0_BASE                       0x41009000UL
#define CAN1_BASE                       0x4100D000UL
#define DMA_BASE                        0x41500000UL
#define ETH_BASE                        0x41200000UL
#define USB_BASE                        0x41300000UL
#define GLOBAL_CTRL_BASE                0x41007010UL
#define AES_BASE                        0x41600000UL
#define DDRC_BASE                       0x41400000UL
#define PDLOCK_BASE                     0x41007000UL
#define PDPROT_BASE                     0x41007C00UL
#define CFG_CTRL_BASE                   0x41700000UL
#define SOFT_RESET_BASE                 0x41007400UL


/* ================================================================================ */
/* ================             Peripheral declaration             ================ */
/* ================================================================================ */

#define UART0                           ((UART0_Type              *) UART0_BASE)
#define UART1                           ((UART0_Type              *) UART1_BASE)
#define UART2                           ((UART0_Type              *) UART2_BASE)
#define WDG                             ((WDG_Type                *) WDG_BASE)
#define TIMER0                          ((TIMER0_Type             *) TIMER0_BASE)
#define TIMER1                          ((TIMER0_Type             *) TIMER1_BASE)
#define TIMER2                          ((TIMER0_Type             *) TIMER2_BASE)
#define TIMER3                          ((TIMER0_Type             *) TIMER3_BASE)
#define SPI0                            ((SPI0_Type               *) SPI0_BASE)
#define SPI1                            ((SPI0_Type               *) SPI1_BASE)
#define I2C0                            ((I2C0_Type               *) I2C0_BASE)
#define I2C1                            ((I2C0_Type               *) I2C1_BASE)
#define RTC                             ((RTC_Type                *) RTC_BASE)
#define GPIO                            ((GPIO_Type               *) GPIO_BASE)
#define NOR_FLASH                       ((NOR_FLASH_Type          *) NOR_FLASH_BASE)
#define ADC                             ((ADC_Type                *) ADC_BASE)
#define EFUSE                           ((EFUSE_Type              *) EFUSE_BASE)
#define CAN0                            ((CAN0_Type               *) CAN0_BASE)
#define CAN1                            ((CAN0_Type               *) CAN1_BASE)
#define DMA                             ((DMA_Type                *) DMA_BASE)
#define ETH                             ((ETH_Type                *) ETH_BASE)
#define USB                             ((USB_Type                *) USB_BASE)
#define GLOBAL_CTRL                     ((GLOBAL_CTRL_Type        *) GLOBAL_CTRL_BASE)
#define AES                             ((AES_Type                *) AES_BASE)
#define DDRC                            ((DDRC_Type               *) DDRC_BASE)
#define PDLOCK                          ((PDLOCK_Type             *) PDLOCK_BASE)
#define PDPROT                          ((PDPROT_Type             *) PDPROT_BASE)
#define CFG_CTRL                        ((CFG_CTRL_Type           *) CFG_CTRL_BASE)
#define SOFT_RESET                      ((SOFT_RESET_Type         *) SOFT_RESET_BASE)


/** @} */ /* End of group Device_Peripheral_Registers */
/** @} */ /* End of group cmem7 */
/** @} */ /* End of group (null) */

#ifdef __cplusplus
}
#endif


#endif  /* cmem7_H */

