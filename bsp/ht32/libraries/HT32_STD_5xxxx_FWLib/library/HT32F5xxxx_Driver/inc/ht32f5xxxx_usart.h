/*********************************************************************************************************//**
 * @file    ht32f5xxxx_usart.h
 * @version $Rev:: 7107         $
 * @date    $Date:: 2023-08-08 #$
 * @brief   The header file of the USART library.
 *************************************************************************************************************
 * @attention
 *
 * Firmware Disclaimer Information
 *
 * 1. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
 *    proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
 *    other intellectual property laws.
 *
 * 2. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
 *    other than HOLTEK and the customer.
 *
 * 3. The program technical documentation, including the code, is provided "as is" and for customer reference
 *    only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
 *    the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
 *    the warranties of merchantability, satisfactory quality and fitness for a particular purpose.
 *
 * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
 ************************************************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __HT32F5XXXX_USART_H
#define __HT32F5XXXX_USART_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"

/** @addtogroup HT32F5xxxx_Peripheral_Driver HT32F5xxxx Peripheral Driver
  * @{
  */

/** @addtogroup USART
  * @{
  */


/* Exported types ------------------------------------------------------------------------------------------*/
/** @defgroup USART_Exported_Types USART exported types
  * @{
  */
/* Definition of USART Init Structure  ---------------------------------------------------------------------*/
typedef struct
{
  u32 USART_BaudRate;
  u16 USART_WordLength;
  u16 USART_StopBits;
  u16 USART_Parity;
  u32 USART_Mode;
} USART_InitTypeDef;

typedef struct
{
  u16 USART_ClockEnable;
  u16 USART_ClockPhase;
  u16 USART_ClockPolarity;
  u16 USART_TransferSelectMode;
} USART_SynClock_InitTypeDef;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------------------------------------*/
/** @defgroup USART_Exported_Constants USART exported constants
  * @{
  */

#define USART_CMD_TX                  (0)
#define USART_CMD_RX                  (1)

#define USART_CMD_OUT                 (0)
#define USART_CMD_IN                  (1)

/* USART Word Length ---------------------------------------------------------------------------------------*/
/** @defgroup USART_Word_Length Definitions of USART word length
  * @{
  */
#define USART_WORDLENGTH_7B           ((u32)0x00000000)
#define USART_WORDLENGTH_8B           ((u32)0x00000100)
#define USART_WORDLENGTH_9B           ((u32)0x00000200)

#define IS_USART_WORD_LENGTH(LENGTH)  ((LENGTH == USART_WORDLENGTH_9B) || \
                                       (LENGTH == USART_WORDLENGTH_8B) || \
                                       (LENGTH == USART_WORDLENGTH_7B))
/**
  * @}
  */

/* USART Stop Bits -----------------------------------------------------------------------------------------*/
/** @defgroup USART_Stop_Bit Definitions of USART stop bit
  * @{
  */
#define USART_STOPBITS_1              ((u32)0x00000000)
#define USART_STOPBITS_2              ((u32)0x00000400)


#define IS_USART_STOPBITS(STOPBITS)   ((STOPBITS == USART_STOPBITS_1) || \
                                       (STOPBITS == USART_STOPBITS_2))
/**
  * @}
  */

/* USART Parity --------------------------------------------------------------------------------------------*/
/** @defgroup USART_Parity Definitions of USART parity
  * @{
  */
#define USART_PARITY_NO               ((u32)0x00000000)
#define USART_PARITY_EVEN             ((u32)0x00001800)
#define USART_PARITY_ODD              ((u32)0x00000800)
#define USART_PARITY_MARK             ((u32)0x00002800)
#define USART_PARITY_SPACE            ((u32)0x00003800)

#define IS_USART_PARITY(PARITY)       ((PARITY == USART_PARITY_NO)   || \
                                       (PARITY == USART_PARITY_EVEN) || \
                                       (PARITY == USART_PARITY_ODD))
/**
  * @}
  */

/* USART Mode ----------------------------------------------------------------------------------------------*/
/** @defgroup USART_Mode Definitions of USART mode
  * @{
  */
#define USART_MODE_NORMAL             ((u32)0x00000000)
#define USART_MODE_IRDA               ((u32)0x00000001)
#define USART_MODE_RS485              ((u32)0x00000002)
#define USART_MODE_SYNCHRONOUS        ((u32)0x00000003)
#if (LIBCFG_USART_LIN)
#define USART_MODE_LIN                ((u32)0x00010000)
#define IS_MODE_LIN(x)                (x == USART_MODE_LIN)
#else
#define IS_MODE_LIN(x)                (0)
#endif
#if (LIBCFG_USART_SINGLE_WIRE)
#define USART_MODE_SINGLE_WIRE        ((u32)0x00010001)
#define IS_MODE_SINGLE_WIRE(x)        (x == USART_MODE_SINGLE_WIRE)
#else
#define IS_MODE_SINGLE_WIRE(x)        (0)
#endif
#define IS_USART_MODE(MODE)           ((MODE == USART_MODE_NORMAL)      || \
                                       (MODE == USART_MODE_IRDA)        || \
                                       (MODE == USART_MODE_RS485)       || \
                                       (MODE == USART_MODE_SYNCHRONOUS) || \
                                       IS_MODE_LIN(MODE)                || \
                                       IS_MODE_SINGLE_WIRE(MODE))
/**
  * @}
  */

/* USART Transfer Select Mode ------------------------------------------------------------------------------*/
/** @defgroup USART_LSB Definitions of USART LSB
  * @{
  */
#define USART_LSB_FIRST               ((u32)0x00000000)
#define USART_MSB_FIRST               ((u32)0x00000004)

#define IS_USART_TRANSFER_MODE(TMODE) ((TMODE == USART_LSB_FIRST) || \
                                       (TMODE == USART_MSB_FIRST))
/**
  * @}
  */


/* USART Synchronous Clock ---------------------------------------------------------------------------------*/
/** @defgroup USART_Synchronous_Clock Definitions of USART synchronous clock
  * @{
  */
#define USART_SYN_CLOCK_DISABLE                 ((u32)0x00000000)
#define USART_SYN_CLOCK_ENABLE                  ((u32)0x00000001)

#define IS_USART_SYNCHRONOUS_CLOCK(SYNCLOCK)    ((SYNCLOCK == USART_SYN_CLOCK_DISABLE) || \
                                                 (SYNCLOCK == USART_SYN_CLOCK_ENABLE))
/**
  * @}
  */

/* USART Synchronous Clock Phase ---------------------------------------------------------------------------*/
/** @defgroup USART_Synchronous_Clock_Phase Definitions of USART Synchronous clock phase
  * @{
  */
#define USART_SYN_CLOCK_PHASE_FIRST             ((u32)0x00000000)
#define USART_SYN_CLOCK_PHASE_SECOND            ((u32)0x00000004)

#define IS_USART_SYNCHRONOUS_PHASE(PHASE)       ((PHASE == USART_SYN_CLOCK_PHASE_FIRST) || \
                                                 (PHASE == USART_SYN_CLOCK_PHASE_SECOND))
/**
  * @}
  */

/* USART Clock Polarity ------------------------------------------------------------------------------------*/
/** @defgroup USART_Clock_Polarity Definitions of USART clock polarity
  * @{
  */
#define USART_SYN_CLOCK_POLARITY_LOW            ((u32)0x00000000)
#define USART_SYN_CLOCK_POLARITY_HIGH           ((u32)0x00000008)

#define IS_USART_SYNCHRONOUS_POLARITY(POLARITY) ((POLARITY == USART_SYN_CLOCK_POLARITY_LOW) || \
                                                 (POLARITY == USART_SYN_CLOCK_POLARITY_HIGH))
/**
  * @}
  */

/* USART IrDA  ---------------------------------------------------------------------------------------------*/
/** @defgroup USART_IrDA Definitions of USART IrDA
  * @{
  */
#define USART_IRDA_LOWPOWER                     ((u32)0x00000002)
#define USART_IRDA_NORMAL                       ((u32)0xFFFFFFFD)

#define IS_USART_IRDA_MODE(MODE)                ((MODE == USART_IRDA_LOWPOWER) || \
                                                 (MODE == USART_IRDA_NORMAL))

#define USART_IRDA_TX                           ((u32)0x00000004)
#define USART_IRDA_RX                           ((u32)0xFFFFFFFB)

#define IS_USART_IRDA_DIRECTION(DIRECTION)      ((DIRECTION == USART_IRDA_TX) || \
                                                 (DIRECTION == USART_IRDA_RX))
/**
  * @}
  */

#define IS_USART_TL(x)                (IS_USART_RXTL(x) || IS_USART_TXTL(x))

/* USART Rx FIFO Interrupt Trigger Level -------------------------------------------------------------------*/
/** @defgroup USART_RX_FIFO_Trigger_Level Definitions of USART Rx FIFO interrupts
  * @{
  */
#define USART_RXTL_01                 ((u32)0x00000000)
#define USART_RXTL_02                 ((u32)0x00000010)
#define USART_RXTL_04                 ((u32)0x00000020)
#define USART_RXTL_06                 ((u32)0x00000030)

#define IS_USART_RXTL(RXTL)           ((RXTL == USART_RXTL_01) || \
                                       (RXTL == USART_RXTL_02) || \
                                       (RXTL == USART_RXTL_04) || \
                                       (RXTL == USART_RXTL_06))
/**
  * @}
  */

/* USART Tx FIFO Interrupt Trigger Level -------------------------------------------------------------------*/
/** @defgroup USART_TX_FIFO_Trigger_Level Definitions of USART Tx FIFO interrupts
  * @{
  */
#define USART_TXTL_00                 ((u32)0x00000000)
#define USART_TXTL_02                 ((u32)0x00000010)
#define USART_TXTL_04                 ((u32)0x00000020)
#define USART_TXTL_06                 ((u32)0x00000030)

#define IS_USART_TXTL(TXTL)           ((TXTL == USART_TXTL_00) || \
                                       (TXTL == USART_TXTL_02) || \
                                       (TXTL == USART_TXTL_04) || \
                                       (TXTL == USART_TXTL_06))
/**
  * @}
  */

/* USART Interrupt definition ------------------------------------------------------------------------------*/
/** @defgroup USART_Interrupt_Enable Definitions of USART interrupt Enable bits
  * @{
  */
#define USART_INT_RXDR                ((u32)0x00000001)
#define USART_INT_TXDE                ((u32)0x00000002)
#define USART_INT_TXC                 ((u32)0x00000004)
#define USART_INT_OE                  ((u32)0x00000008)
#define USART_INT_PE                  ((u32)0x00000010)
#define USART_INT_FE                  ((u32)0x00000020)
#define USART_INT_BI                  ((u32)0x00000040)
#define USART_INT_RSADD               ((u32)0x00000080)
#define USART_INT_TOUT                ((u32)0x00000100)
#define USART_INT_CTS                 ((u32)0x00000200)
#if (LIBCFG_USART_LIN)
#define USART_INT_LBD                 ((u32)0x00000400)
#endif

#if (LIBCFG_USART_LIN)
#define IS_USART_INT(INT)             ((((INT) & 0xFFFFF800) == 0) && ((INT) != 0))
#else
#define IS_USART_INT(INT)             ((((INT) & 0xFFFFFC00) == 0) && ((INT) != 0))
#endif
/**
  * @}
  */

/* USART Flags ---------------------------------------------------------------------------------------------*/
/** @defgroup USART_Flag Definitions of USART flags
  * @{
  */
#define USART_FLAG_RXDNE              ((u32)0x00000001)
#define USART_FLAG_OE                 ((u32)0x00000002)
#define USART_FLAG_PE                 ((u32)0x00000004)
#define USART_FLAG_FE                 ((u32)0x00000008)
#define USART_FLAG_BI                 ((u32)0x00000010)
#define USART_FLAG_RXDR               ((u32)0x00000020)
#define USART_FLAG_TOUT               ((u32)0x00000040)
#define USART_FLAG_TXDE               ((u32)0x00000080)
#define USART_FLAG_TXC                ((u32)0x00000100)
#define USART_FLAG_RSADD              ((u32)0x00000200)
#define USART_FLAG_CTSC               ((u32)0x00000400)
#define USART_FLAG_CTSS               ((u32)0x00000800)
#if (LIBCFG_USART_LIN)
#define USART_FLAG_LBD                ((u32)0x00001000)
#define IS_FLAG_LBD(x)                (x == USART_FLAG_LBD)
#else
#define IS_FLAG_LBD(x)                (0)
#endif

#define IS_USART_FLAG(FLAG)           ((FLAG == USART_FLAG_RXDNE) || (FLAG == USART_FLAG_OE)    || \
                                       (FLAG == USART_FLAG_PE)    || (FLAG == USART_FLAG_FE)    || \
                                       (FLAG == USART_FLAG_BI)    || (FLAG == USART_FLAG_RXDR)  || \
                                       (FLAG == USART_FLAG_TOUT)  || (FLAG == USART_FLAG_TXDE)  || \
                                       (FLAG == USART_FLAG_TXC)   || (FLAG == USART_FLAG_RSADD) || \
                                       (FLAG == USART_FLAG_CTSC)  || (FLAG == USART_FLAG_CTSS)  || \
                                       IS_FLAG_LBD(FLAG))

#define IS_USART_CLEAR_FLAG(FLAG)     ((FLAG == USART_FLAG_OE)    || (FLAG == USART_FLAG_PE)    || \
                                       (FLAG == USART_FLAG_FE)    || (FLAG == USART_FLAG_BI)    || \
                                       (FLAG == USART_FLAG_TOUT)  || (FLAG == USART_FLAG_RSADD) || \
                                       (FLAG == USART_FLAG_CTSC)  || IS_FLAG_LBD(FLAG))
/**
  * @}
  */

/* USART RS485 definition ----------------------------------------------------------------------------------*/
/** @defgroup USART_RS485 Definitions of USART RS485
  * @{
  */
#define USART_RS485POLARITY_LOW                 ((u32)0x00000001)
#define USART_RS485POLARITY_HIGH                ((u32)0xFFFFFFFE)

#define IS_USART_RS485_POLARITY(POLARITY)       ((POLARITY == USART_RS485POLARITY_LOW) || \
                                                 (POLARITY == USART_RS485POLARITY_HIGH))
/**
  * @}
  */

/*  USART LIN definition -----------------------------------------------------------------------------------*/
/** @defgroup USART_LIN Definitions of USART LIN
  * @{
  */
#if (LIBCFG_USART_LIN)
#define USART_LINSENDBREAK                      ((u32)0x00020000)

#define USART_LINLENGTH_10BIT                   ((u32)0xFFFBFFFF)
#define USART_LINLENGTH_11BIT                   ((u32)0x00040000)

#define IS_USART_LINLENGTH(LENGTH)              ((LENGTH == USART_LINLENGTH_10BIT) || \
                                                 (LENGTH == USART_LINLENGTH_11BIT))
#endif
/**
  * @}
  */

#define USART_FIFO_TX                           ((u32)0x00000001)
#define USART_FIFO_RX                           ((u32)0x00000002)

#define IS_USART_FIFO_DIRECTION(DIRECTION)      ((DIRECTION == USART_FIFO_TX) || \
                                                 (DIRECTION == USART_FIFO_RX))

#define USART_STICK_LOW                         ((u32)0x00001000)
#define USART_STICK_HIGH                        ((u32)0xFFFFEFFF)

#define IS_USART_STICK_PARITY(PARITY)           ((PARITY == USART_STICK_LOW) || (PARITY == USART_STICK_HIGH))

#if (LIBCFG_PDMA)
#define USART_PDMAREQ_TX                        ((u32)0x00000040)
#define USART_PDMAREQ_RX                        ((u32)0x00000080)

#define IS_USART_PDMA_REQ(REQ)                  (((REQ & 0xFFFFFF3F) == 0x0) && (REQ != 0x0))
#endif

#define IS_USART(x)                             (IS_USART0(x) || \
                                                 IS_USART1(x) || \
                                                 IS_UART0(x)  || \
                                                 IS_UART1(x)  || \
                                                 IS_UART2(x)  || \
                                                 IS_UART3(x))
#if (LIBCFG_NO_USART0)
#define IS_USART0(x)    (0)
#else
#define IS_USART0(x)    (x == HT_USART0)
#endif
#define IS_UART0(x)     (x == HT_UART0)
#if (LIBCFG_USART1)
#define IS_USART1(x)    (x == HT_USART1)
#else
#define IS_USART1(x)    (0)
#endif
#if (LIBCFG_UART1)
#define IS_UART1(x)     (x == HT_UART1)
#else
#define IS_UART1(x)     (0)
#endif
#if (LIBCFG_UART2)
#define IS_UART2(x)     (x == HT_UART2)
#else
#define IS_UART2(x)     (0)
#endif
#if (LIBCFG_UART3)
#define IS_UART3(x)     (x == HT_UART3)
#else
#define IS_UART3(x)     (0)
#endif
#define IS_USART_BAUDRATE(BAUDRATE)             ((BAUDRATE > 0) && (BAUDRATE < 0x0044AA21))
#define IS_USART_DATA(DATA)                     (DATA <= 0x1FF)
#define IS_USART_GUARD_TIME(TIME)               (TIME <= 0xFF)
#define IS_USART_IRDA_PRESCALER(PRESCALER)      (PRESCALER <= 0xFF)
#define IS_USART_TIMEOUT(TIMEOUT)               (TIMEOUT <= 0x7F)
#define IS_USART_ADDRESS_MATCH_VALUE(VALUE)     (VALUE <= 0xFF)
/**
  * @}
  */

/* Exported functions --------------------------------------------------------------------------------------*/
/** @defgroup USART_Exported_Functions USART exported functions
  * @{
  */
#define USART_TxCmd(USARTx, NewState)              USART_TxRxCmd(USARTx, USART_CMD_TX, NewState)
#define USART_RxCmd(USARTx, NewState)              USART_TxRxCmd(USARTx, USART_CMD_RX, NewState)

#define USART_TxPDMACmd(USARTx, NewState)          USART_PDMACmd(USARTx, USART_PDMAREQ_TX, NewState)
#define USART_RxPDMACmd(USARTx, NewState)          USART_PDMACmd(USARTx, USART_PDMAREQ_RX, NewState)

#define USART_RXTLConfig(USARTx, USART_tl)         USART_TXRXTLConfig(USARTx, USART_CMD_RX, USART_tl)
#define USART_TXTLConfig(USARTx, USART_tl)         USART_TXRXTLConfig(USARTx, USART_CMD_TX, USART_tl)

#define USART_IrDAInvtOutputCmd(USARTx, NewState)  USART_IrDAInvtCmd(USARTx, USART_CMD_OUT, NewState)
#define USART_IrDAInvtInputCmd(USARTx, NewState)   USART_IrDAInvtCmd(USARTx, USART_CMD_IN, NewState)

void USART_DeInit(HT_USART_TypeDef* USARTx);
void USART_Init(HT_USART_TypeDef* USARTx, USART_InitTypeDef* USART_InitStructure);
void USART_StructInit(USART_InitTypeDef* USART_InitStructure);
void USART_SendData(HT_USART_TypeDef* USARTx, u16 Data);
u16 USART_ReceiveData(HT_USART_TypeDef* USARTx);
FlagStatus USART_GetFlagStatus(HT_USART_TypeDef* USARTx, u32 USART_FLAG_x);
FlagStatus USART_GetIntStatus(HT_USART_TypeDef* USARTx, u32 USART_FLAG_x);
void USART_ClearFlag(HT_USART_TypeDef* USARTx, u32 USART_Flag);
void USART_IntConfig(HT_USART_TypeDef* USARTx, u32 USART_INT_x, ControlStatus NewState);
void USART_TxRxCmd(HT_USART_TypeDef* USARTx,u32 TxRx, ControlStatus NewState);
#if (LIBCFG_PDMA)
void USART_PDMACmd(HT_USART_TypeDef* USARTx, u32 USART_PDMAREQ, ControlStatus NewState);
#endif
void USART_ForceBreakCmd(HT_USART_TypeDef* USARTx, ControlStatus NewState);
void USART_StickParityCmd(HT_USART_TypeDef* USARTx, ControlStatus NewState);
void USART_StickParityConfig(HT_USART_TypeDef* USARTx, u32 USART_StickParity);

void USART_SetGuardTime(HT_USART_TypeDef* USARTx, u32 USART_GuardTime);
void USART_TXRXTLConfig(HT_USART_TypeDef* USARTx, u32 TxRx, u32 USART_tl);
void USART_SetTimeOutValue(HT_USART_TypeDef* USARTx, u32 USART_TimeOut);
void USART_FIFOReset(HT_USART_TypeDef* USARTx, u32 USART_FIFODirection);
u8 USART_GetFIFOStatus(HT_USART_TypeDef* USARTx, u32 USART_FIFODirection);
void USART_HardwareFlowControlCmd(HT_USART_TypeDef* USARTx, ControlStatus NewState);

void USART_IrDACmd(HT_USART_TypeDef* USARTx, ControlStatus NewState);
void USART_IrDAConfig(HT_USART_TypeDef* USARTx, u32 USART_IrDAMode);
void USART_SetIrDAPrescaler(HT_USART_TypeDef* USARTx, u32 USART_IrDAPrescaler);
void USART_IrDADirectionConfig(HT_USART_TypeDef* USARTx, u32 USART_IrDADirection);
void USART_IrDAInvtCmd(HT_USART_TypeDef* USARTx, u32 inout, ControlStatus NewState);

void USART_RS485TxEnablePolarityConfig(HT_USART_TypeDef* USARTx, u32 USART_RS485Polarity);
void USART_RS485NMMCmd(HT_USART_TypeDef* USARTx, ControlStatus NewState);
void USART_RS485AADCmd(HT_USART_TypeDef* USARTx, ControlStatus NewState);
void USART_SetAddressMatchValue(HT_USART_TypeDef* USARTx, u32 USART_AddressMatchValue);

void USART_SynClockInit(HT_USART_TypeDef* USARTx, USART_SynClock_InitTypeDef* USART_SynClock_InitStruct);
void USART_SynClockStructInit(USART_SynClock_InitTypeDef* USART_SynClock_InitStruct);

#if (LIBCFG_USART_LIN)
void USART_LIN_SendBreak(HT_USART_TypeDef* USARTx);
void USART_LIN_LengthSelect(HT_USART_TypeDef* USARTx, u32 USART_LIN_Length);
#endif
/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif
