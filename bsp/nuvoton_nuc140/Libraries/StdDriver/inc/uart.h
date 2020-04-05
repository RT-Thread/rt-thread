/**************************************************************************//**
 * @file     UART.h
 * @version  V3.0
 * $Revision: 8 $
 * $Date: 15/06/05 11:05a $
 * @brief    UART Interface Controller Driver Header File
 *
 * @note
 * Copyright (C) 2011 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#ifndef __UART_H__
#define __UART_H__


#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup UART_Driver UART Driver
  @{
*/

/** @addtogroup UART_EXPORTED_CONSTANTS UART Exported Constants
  @{
*/
    
/*---------------------------------------------------------------------------------------------------------*/
/* UART FIFO size constants definitions                                                                    */
/*---------------------------------------------------------------------------------------------------------*/

#define UART0_FIFO_SIZE 64 /*!< UART0 supports separated receive/transmit 64/64 bytes entry FIFO */
#define UART1_FIFO_SIZE 16 /*!< UART1 supports separated receive/transmit 16/16 bytes entry FIFO */
#define UART2_FIFO_SIZE 16 /*!< UART2 supports separated receive/transmit 16/16 bytes entry FIFO */
  
/*---------------------------------------------------------------------------------------------------------*/
/* UA_FCR constants definitions                                                                            */
/*---------------------------------------------------------------------------------------------------------*/

#define UART_FCR_RFITL_1BYTE        (0x0 << UART_FCR_RFITL_Pos)   /*!< UA_FCR setting to set RX FIFO Trigger Level to 1 byte */
#define UART_FCR_RFITL_4BYTES       (0x1 << UART_FCR_RFITL_Pos)   /*!< UA_FCR setting to set RX FIFO Trigger Level to 4 bytes */
#define UART_FCR_RFITL_8BYTES       (0x2 << UART_FCR_RFITL_Pos)   /*!< UA_FCR setting to set RX FIFO Trigger Level to 8 bytes */
#define UART_FCR_RFITL_14BYTES      (0x3 << UART_FCR_RFITL_Pos)   /*!< UA_FCR setting to set RX FIFO Trigger Level to 14 bytes */
#define UART_FCR_RFITL_30BYTES      (0x4 << UART_FCR_RFITL_Pos)   /*!< UA_FCR setting to set RX FIFO Trigger Level to 30 bytes */
#define UART_FCR_RFITL_46BYTES      (0x5 << UART_FCR_RFITL_Pos)   /*!< UA_FCR setting to set RX FIFO Trigger Level to 46 bytes */
#define UART_FCR_RFITL_62BYTES      (0x6 << UART_FCR_RFITL_Pos)   /*!< UA_FCR setting to set RX FIFO Trigger Level to 62 bytes */

#define UART_FCR_RTS_TRI_LEV_1BYTE        (0x0 << UART_FCR_RTS_TRI_LEV_Pos)  /*!< UA_FCR setting to set RTS Trigger Level to 1 byte */
#define UART_FCR_RTS_TRI_LEV_4BYTES       (0x1 << UART_FCR_RTS_TRI_LEV_Pos)  /*!< UA_FCR setting to set RTS Trigger Level to 4 bytes */
#define UART_FCR_RTS_TRI_LEV_8BYTES       (0x2 << UART_FCR_RTS_TRI_LEV_Pos)  /*!< UA_FCR setting to set RTS Trigger Level to 8 bytes */
#define UART_FCR_RTS_TRI_LEV_14BYTES      (0x3 << UART_FCR_RTS_TRI_LEV_Pos)  /*!< UA_FCR setting to set RTS Trigger Level to 14 bytes */
#define UART_FCR_RTS_TRI_LEV_30BYTES      (0x4 << UART_FCR_RTS_TRI_LEV_Pos)  /*!< UA_FCR setting to set RTS Trigger Level to 30 bytes */
#define UART_FCR_RTS_TRI_LEV_46BYTES      (0x5 << UART_FCR_RTS_TRI_LEV_Pos)  /*!< UA_FCR setting to set RTS Trigger Level to 46 bytes */
#define UART_FCR_RTS_TRI_LEV_62BYTES      (0x6 << UART_FCR_RTS_TRI_LEV_Pos)  /*!< UA_FCR setting to set RTS Trigger Level to 62 bytes */

/*---------------------------------------------------------------------------------------------------------*/
/* UA_LCR constants definitions                                                                            */
/*---------------------------------------------------------------------------------------------------------*/
#define UART_WORD_LEN_5        (0) /*!< UA_LCR setting to set UART word length to 5 bits */
#define UART_WORD_LEN_6        (1) /*!< UA_LCR setting to set UART word length to 6 bits */
#define UART_WORD_LEN_7        (2) /*!< UA_LCR setting to set UART word length to 7 bits */
#define UART_WORD_LEN_8        (3) /*!< UA_LCR setting to set UART word length to 8 bits */

#define UART_PARITY_NONE    (0x0 << UART_LCR_PBE_Pos) /*!< UA_LCR setting to set UART as no parity   */
#define UART_PARITY_ODD     (0x1 << UART_LCR_PBE_Pos) /*!< UA_LCR setting to set UART as odd parity  */
#define UART_PARITY_EVEN    (0x3 << UART_LCR_PBE_Pos) /*!< UA_LCR setting to set UART as even parity */
#define UART_PARITY_MARK    (0x5 << UART_LCR_PBE_Pos) /*!< UA_LCR setting to keep parity bit as '1'  */
#define UART_PARITY_SPACE   (0x7 << UART_LCR_PBE_Pos) /*!< UA_LCR setting to keep parity bit as '0'  */

#define UART_STOP_BIT_1     (0x0 << UART_LCR_NSB_Pos) /*!< UA_LCR setting for one stop bit  */
#define UART_STOP_BIT_1_5   (0x1 << UART_LCR_NSB_Pos) /*!< UA_LCR setting for 1.5 stop bit when 5-bit word length  */
#define UART_STOP_BIT_2     (0x1 << UART_LCR_NSB_Pos) /*!< UA_LCR setting for two stop bit when 6, 7, 8-bit word length */


/*---------------------------------------------------------------------------------------------------------*/
/* UART RTS LEVEL TRIGGER constants definitions                                                            */
/*---------------------------------------------------------------------------------------------------------*/
#define UART_RTS_IS_LOW_LEV_ACTIVE      (0x1 << UART_MCR_LEV_RTS_Pos) /*!< Set RTS is Low Level Active */
#define UART_RTS_IS_HIGH_LEV_ACTIVE     (0x0 << UART_MCR_LEV_RTS_Pos) /*!< Set RTS is High Level Active */

/*---------------------------------------------------------------------------------------------------------*/
/* UA_IRCR constants definitions                                                                           */
/*---------------------------------------------------------------------------------------------------------*/
#define UART_IRCR_TX_SELECT         (0x1 << UART_IRCR_TX_SELECT_Pos) /*!< Set IrDA function Tx mode */
#define UART_IRCR_RX_SELECT         (0x0 << UART_IRCR_TX_SELECT_Pos) /*!< Set IrDA function Rx mode */

/*---------------------------------------------------------------------------------------------------------*/
/* UA_FUNC_SEL constants definitions                                                                       */
/*---------------------------------------------------------------------------------------------------------*/
#define UART_FUNC_SEL_UART    (0x0 << UART_FUN_SEL_FUN_SEL_Pos) /*!< UA_FUNC_SEL setting to set UART Function  (Default) */
#define UART_FUNC_SEL_LIN     (0x1 << UART_FUN_SEL_FUN_SEL_Pos) /*!< UA_FUNC_SEL setting to set LIN Function             */
#define UART_FUNC_SEL_IrDA    (0x2 << UART_FUN_SEL_FUN_SEL_Pos) /*!< UA_FUNC_SEL setting to set IrDA Function            */
#define UART_FUNC_SEL_RS485   (0x3 << UART_FUN_SEL_FUN_SEL_Pos) /*!< UA_FUNC_SEL setting to set RS485 Function           */

/*---------------------------------------------------------------------------------------------------------*/
/* UA_LIN_CTL constants definitions                                                                       */
/*---------------------------------------------------------------------------------------------------------*/
#define UART_LIN_CTL_LINS_EN        (0x1UL << UART_LIN_CTL_LINS_EN_Pos)       /*!< UA_LIN_CTL setting to set LIN Slave Mode Enable */
#define UART_LIN_CTL_LINS_HDET_EN   (0x1UL << UART_LIN_CTL_LINS_HDET_EN_Pos)  /*!< UA_LIN_CTL setting to set LIN Slave Header Detection Enable */
#define UART_LIN_CTL_LINS_ARS_EN    (0x1UL << UART_LIN_CTL_LINS_ARS_EN_Pos)   /*!< UA_LIN_CTL setting to set LIN Slave Automatic Resynchronization Mode Enable */
#define UART_LIN_CTL_LINS_DUM_EN    (0x1UL << UART_LIN_CTL_LINS_DUM_EN_Pos)   /*!< UA_LIN_CTL setting to set LIN Slave Divider Update Method Enable */
#define UART_LIN_CTL_LIN_MUTE_EN    (0x1UL << UART_LIN_CTL_LIN_MUTE_EN_Pos)   /*!< UA_LIN_CTL setting to set LIN Mute Mode Enable */
#define UART_LIN_CTL_LIN_SHD        (0x1UL << UART_LIN_CTL_LIN_SHD_Pos)       /*!< UA_LIN_CTL setting to set LIN TX Send Header Enable */
#define UART_LIN_CTL_LIN_IDPEN      (0x1UL << UART_LIN_CTL_LIN_IDPEN_Pos)     /*!< UA_LIN_CTL setting to set LIN ID Parity Enable */
#define UART_LIN_CTL_LIN_BKDET_EN   (0x1UL << UART_LIN_CTL_LIN_BKDET_EN_Pos)  /*!< UA_LIN_CTL setting to set LIN Break Detection Enable */
#define UART_LIN_CTL_LIN_RX_DIS     (0x1UL << UART_LIN_CTL_LIN_RX_DIS_Pos)    /*!< UA_LIN_CTL setting to set LIN Receiver Disable */
#define UART_LIN_CTL_BIT_ERR_EN     (0x1UL << UART_LIN_CTL_BIT_ERR_EN_Pos)    /*!< UA_LIN_CTL setting to set Bit Error Detect Enable */
#define UART_LIN_CTL_LIN_BKFL(x)    (((x)-1) << UART_LIN_CTL_LIN_BKFL_Pos)  /*!< UA_LIN_CTL setting to set LIN Break Field Length, x = 10 ~ 15, default value is 12 */
#define UART_LIN_CTL_LIN_BS_LEN(x)  (((x)-1) << UART_LIN_CTL_LIN_BS_LEN_Pos)/*!< UA_LIN_CTL setting to set LIN Break/Sync Delimiter Length, x = 1 ~ 4 */
#define UART_LIN_CTL_LIN_HEAD_SEL_BREAK             (0x0UL << UART_LIN_CTL_LIN_HEAD_SEL_Pos)    /*!< UA_LIN_CTL setting to set LIN Header Select to break field */
#define UART_LIN_CTL_LIN_HEAD_SEL_BREAK_SYNC        (0x1UL << UART_LIN_CTL_LIN_HEAD_SEL_Pos)    /*!< UA_LIN_CTL setting to set LIN Header Select to break field and sync field */
#define UART_LIN_CTL_LIN_HEAD_SEL_BREAK_SYNC_ID     (0x2UL << UART_LIN_CTL_LIN_HEAD_SEL_Pos)    /*!< UA_LIN_CTL setting to set LIN Header Select to break field, sync field and ID field*/
#define UART_LIN_CTL_LIN_LIN_PID(x) ((x) << UART_LIN_CTL_LIN_PID_Pos)       /*!< UA_LIN_CTL setting to set LIN PID value */

/*---------------------------------------------------------------------------------------------------------*/
/* UART BAUDRATE MODE constants definitions                                                                       */
/*---------------------------------------------------------------------------------------------------------*/
#define UART_BAUD_MODE0     (0) /*!< Set UART Baudrate Mode is Mode0 */
#define UART_BAUD_MODE2     (UART_BAUD_DIV_X_EN_Msk | UART_BAUD_DIV_X_ONE_Msk) /*!< Set UART Baudrate Mode is Mode2 */


/*@}*/ /* end of group UART_EXPORTED_CONSTANTS */


/** @addtogroup UART_EXPORTED_FUNCTIONS UART Exported Functions
  @{
*/


/**
 *    @brief        Calculate UART baudrate mode0 divider
 *
 *    @param[in]    u32SrcFreq      UART clock frequency
 *    @param[in]    u32BaudRate     Baudrate of UART module
 *
 *    @return       UART baudrate mode0 divider
 *
 *    @details      This macro calculate UART baudrate mode0 divider.
 */
#define UART_BAUD_MODE0_DIVIDER(u32SrcFreq, u32BaudRate)    ((((u32SrcFreq) + ((u32BaudRate)*8)) / (u32BaudRate) >> 4)-2)

/**
 *    @brief        Calculate UART baudrate mode2 divider
 *
 *    @param[in]    u32SrcFreq      UART clock frequency
 *    @param[in]    u32BaudRate     Baudrate of UART module
 *
 *    @return       UART baudrate mode2 divider
 *
 *    @details      This macro calculate UART baudrate mode2 divider.
 */
#define UART_BAUD_MODE2_DIVIDER(u32SrcFreq, u32BaudRate)    ((((u32SrcFreq) + ((u32BaudRate)/2)) / (u32BaudRate))-2)


/**
 *    @brief        Write data
 *
 *    @param[in]    uart    The pointer of the specified UART module.
 *    @param[in]    u8Data  Data byte to transmit.
 *
 *    @return       None
 *
 *    @details      This macro write Data to Tx data register.
 */
#define UART_WRITE(uart, u8Data)    ((uart)->THR = (u8Data))

/**
 *    @brief        Read data
 *
 *    @param[in]    uart    The pointer of the specified UART module.
 *
 *    @return       The oldest data byte in RX FIFO.
 *
 *    @details      This macro read Rx data register.
 */
#define UART_READ(uart)    ((uart)->RBR)


/**
 *    @brief        Get Tx empty
 *
 *    @param[in]    uart    The pointer of the specified UART module.
 *
 *    @retval       0   Tx FIFO is not empty
 *    @retval       >=1 Tx FIFO is empty
 *
 *    @details      This macro get Tx empty register value.
 */
#define UART_GET_TX_EMPTY(uart)    ((uart)->FSR & UART_FSR_TX_EMPTY_Msk)


/**
 *    @brief        Get Rx empty
 *
 *    @param[in]    uart    The pointer of the specified UART module.
 *
 *    @retval       0   Rx FIFO is not empty
 *    @retval       >=1 Rx FIFO is empty
 *
 *    @details      This macro get Rx empty register value.
 */
#define UART_GET_RX_EMPTY(uart)    ((uart)->FSR & UART_FSR_RX_EMPTY_Msk)

/**
 *    @brief        Check specified uart port transmission is over.
 *
 *    @param[in]    uart    The pointer of the specified UART module.
 *
 *    @retval       0   Transmission is not over.
 *    @retval       1   Transmission is over.
 *
 *    @details      This macro return if Tx FIFO is empty and specified uart port transmission is over nor not.
 */
#define UART_IS_TX_EMPTY(uart)    (((uart)->FSR & UART_FSR_TE_FLAG_Msk) >> UART_FSR_TE_FLAG_Pos)


/**
 *    @brief        Wait specified uart port transmission is over
 *
 *    @param[in]    uart    The pointer of the specified UART module.
 *
 *    @return       None
 *
 *    @details      This macro wait specified uart port transmission is over.
 */
#define UART_WAIT_TX_EMPTY(uart)    while(!((((uart)->FSR) & UART_FSR_TE_FLAG_Msk) >> UART_FSR_TE_FLAG_Pos))

/**
 *    @brief        Check RX is ready or not
 *
 *    @param[in]    uart    The pointer of the specified UART module.
 *
 *    @retval       0 The number of bytes in the RX FIFO is less than the RFITL
 *    @retval       1 The number of bytes in the RX FIFO equals or larger than RFITL
 *
 *    @details      This macro check receive data available interrupt flag is set or not.
 */
#define UART_IS_RX_READY(uart)    (((uart)->ISR & UART_ISR_RDA_IF_Msk)>>UART_ISR_RDA_IF_Pos)


/**
 *    @brief        Check TX FIFO is full or not
 *
 *    @param[in]    uart    The pointer of the specified UART module.
 *
 *    @retval       1 TX FIFO is full
 *    @retval       0 TX FIFO is not full
 *
 *    @details      This macro check TX FIFO is full or not.
 */
#define UART_IS_TX_FULL(uart)    (((uart)->FSR & UART_FSR_TX_FULL_Msk)>>UART_FSR_TX_FULL_Pos)

/**
 *    @brief        Check RX FIFO is full or not
 *
 *    @param[in]    uart    The pointer of the specified UART module.
 *
 *    @retval       1 RX FIFO is full
 *    @retval       0 RX FIFO is not full
 *
 *    @details      This macro check RX FIFO is full or not.
 */
#define UART_IS_RX_FULL(uart)    (((uart)->FSR & UART_FSR_RX_FULL_Msk)>>UART_FSR_RX_FULL_Pos)


/**
 *    @brief        Get Tx full register value
 *
 *    @param[in]    uart    The pointer of the specified UART module.
 *
 *    @retval       0   Tx FIFO is not full.
 *    @retval       >=1 Tx FIFO is full.
 *
 *    @details      This macro get Tx full register value.
 */
#define UART_GET_TX_FULL(uart)    ((uart)->FSR & UART_FSR_TX_FULL_Msk)


/**
 *    @brief        Get Rx full register value
 *
 *    @param[in]    uart   The pointer of the specified UART module.
 *
 *    @retval       0   Rx FIFO is not full.
 *    @retval       >=1 Rx FIFO is full.
 *
 *    @details      This macro get Rx full register value.
 */
#define UART_GET_RX_FULL(uart)    ((uart)->FSR & UART_FSR_RX_FULL_Msk)


/**
 *    @brief        Enable specified UART interrupt
 *
 *    @param[in]    uart        The pointer of the specified UART module.
 *    @param[in]    u32eIntSel  Interrupt type select
 *                              - UART_IER_LIN_IEN_Msk      : Lin bus interrupt
 *                              - UART_IER_WAKE_EN_Msk      : Wakeup interrupt
 *                              - UART_IER_BUF_ERR_IEN_Msk  : Buffer Error interrupt
 *                              - UART_IER_TOUT_IEN_Msk     : Rx time-out interrupt
 *                              - UART_IER_MODEM_IEN_Msk    : Modem interrupt
 *                              - UART_IER_RLS_IEN_Msk      : Rx Line status interrupt
 *                              - UART_IER_THRE_IEN_Msk     : Tx empty interrupt
 *                              - UART_IER_RDA_IEN_Msk      : Rx ready interrupt
 *
 *    @return       None
 *
 *    @details      This macro enable specified UART interrupt.
 */
#define UART_ENABLE_INT(uart, u32eIntSel)    ((uart)->IER |= (u32eIntSel))


/**
 *    @brief        Disable specified UART interrupt
 *
 *    @param[in]    uart        The pointer of the specified UART module.
 *    @param[in]    u32eIntSel  Interrupt type select
 *                              - UART_IER_LIN_IEN_Msk      : Lin bus interrupt
 *                              - UART_IER_WAKE_EN_Msk      : Wakeup interrupt
 *                              - UART_IER_BUF_ERR_IEN_Msk  : Buffer Error interrupt
 *                              - UART_IER_TOUT_IEN_Msk     : Rx time-out interrupt
 *                              - UART_IER_MODEM_IEN_Msk    : Modem interrupt
 *                              - UART_IER_RLS_IEN_Msk      : Rx Line status interrupt
 *                              - UART_IER_THRE_IEN_Msk     : Tx empty interrupt
 *                              - UART_IER_RDA_IEN_Msk      : Rx ready interrupt
 *    @return       None
 *
 *    @details      This macro enable specified UART interrupt.
 */
#define UART_DISABLE_INT(uart, u32eIntSel)    ((uart)->IER &= ~ (u32eIntSel))


/**
 *    @brief        Get specified interrupt indicator status
 *
 *    @param[in]    uart            The pointer of the specified UART module.
 *    @param[in]    u32eIntTypeFlag Interrupt Type Flag, should be
 *                                  - UART_ISR_HW_BUF_ERR_INT_Msk   : In DMA Mode, Buffer Error Interrupt Indicator
 *                                  - UART_ISR_HW_TOUT_INT_Msk      : In DMA Mode, Rx Time-out Interrupt Indicator
 *                                  - UART_ISR_HW_MODEM_INT_Msk     : In DMA Mode, MODEM Status Interrupt Indicator
 *                                  - UART_ISR_HW_RLS_INT_Msk       : In DMA Mode, Rx Line Status Interrupt Indicator
 *                                  - UART_ISR_HW_BUF_ERR_IF_Msk    : In DMA Mode, Buffer Error Interrupt Flag
 *                                  - UART_ISR_HW_TOUT_IF_Msk       : In DMA Mode, Rx Time-out Interrupt Flag
 *                                  - UART_ISR_HW_MODEM_IF_Msk      : In DMA Mode, MODEM Status Interrupt Flag
 *                                  - UART_ISR_HW_RLS_IF_Msk        : In DMA Mode, Rx Line Status Interrupt Flag
 *                                  - UART_ISR_LIN_INT_Msk          : LIN Bus Interrupt Indicator
 *                                  - UART_ISR_BUF_ERR_INT_Msk      : Buffer Error Interrupt Indicator
 *                                  - UART_ISR_TOUT_INT_Msk         : Rx Time-out Interrupt Indicator
 *                                  - UART_ISR_MODEM_INT_Msk        : MODEM Status Interrupt Indicator
 *                                  - UART_ISR_RLS_INT_Msk          : Rx Line Status Interrupt Indicator
 *                                  - UART_ISR_THRE_INT_Msk         : Tx Empty Interrupt Indicator
 *                                  - UART_ISR_RDA_INT_Msk          : Rx Ready Interrupt Indicator
 *                                  - UART_ISR_LIN_IF_Msk           : LIN Bus Interrupt Flag
 *                                  - UART_ISR_BUF_ERR_IF_Msk       : Buffer Error Interrupt Flag
 *                                  - UART_ISR_TOUT_IF_Msk          : Rx Time-out Interrupt Flag
 *                                  - UART_ISR_MODEM_IF_Msk         : MODEM Status Interrupt Flag
 *                                  - UART_ISR_RLS_IF_Msk           : Rx Line Status Interrupt Flag
 *                                  - UART_ISR_THRE_IF_Msk          : Tx Empty Interrupt Flag
 *                                  - UART_ISR_RDA_IF_Msk           : Rx Ready Interrupt Flag
 *
 *    @retval       0 The specified interrupt is not happened.
 *    @retval       1 The specified interrupt is happened.
 *
 *    @details      This macro get specified interrupt flag or interrupt indicator status.
 */
#define UART_GET_INT_FLAG(uart,u32eIntTypeFlag)    (((uart)->ISR & (u32eIntTypeFlag))?1:0)


/**
 *    @brief        Set RTS pin to low
 *
 *    @param[in]    uart    The pointer of the specified UART module.
 *
 *    @return       None
 *
 *    @details      This macro set RTS pin to low.
 */
__STATIC_INLINE void UART_CLEAR_RTS(UART_T* uart)
{
    (uart)->MCR |= UART_MCR_LEV_RTS_Msk;
    (uart)->MCR &= ~UART_MCR_RTS_Msk;
}

/**
 *    @brief        Set RTS pin to high
 *
 *    @param[in]    uart    The pointer of the specified UART module.
 *
 *    @return       None
 *
 *    @details      This macro set RTS pin to high.
 */
__STATIC_INLINE void UART_SET_RTS(UART_T* uart)
{
    (uart)->MCR |= UART_MCR_LEV_RTS_Msk | UART_MCR_RTS_Msk;
}


/**
 *    @brief        Clear RS-485 Address Byte Detection Flag
 *
 *    @param[in]    uart    The pointer of the specified UART module.
 *
 *    @return       None
 *
 *    @details      This macro clear RS-485 address byte detection flag.
 */
#define UART_RS485_CLEAR_ADDR_FLAG(uart)    ((uart)->FSR = UART_FSR_RS485_ADD_DETF_Msk)


/**
 *    @brief        Get RS-485 Address Byte Detection Flag
 *
 *    @param[in]    uart    The pointer of the specified UART module.
 *
 *    @retval       0 Receiver detects a data that is not an address bit.
 *    @retval       1 Receiver detects a data that is an address bit.
 *
 *    @details      This macro get RS-485 address byte detection flag.
 */
#define UART_RS485_GET_ADDR_FLAG(uart)    (((uart)->FSR  & UART_FSR_RS485_ADD_DETF_Msk) >> UART_FSR_RS485_ADD_DETF_Pos)


void UART_ClearIntFlag(UART_T* uart , uint32_t u32InterruptFlag);
void UART_Close(UART_T* uart);
void UART_DisableFlowCtrl(UART_T* uart);
void UART_DisableInt(UART_T*  uart, uint32_t u32InterruptFlag);
void UART_EnableFlowCtrl(UART_T* uart);
void UART_EnableInt(UART_T*  uart, uint32_t u32InterruptFlag);
void UART_Open(UART_T* uart, uint32_t u32baudrate);
uint32_t UART_Read(UART_T* uart, uint8_t *pu8RxBuf, uint32_t u32ReadBytes);
void UART_SetLine_Config(UART_T* uart, uint32_t u32baudrate, uint32_t u32data_width, uint32_t u32parity, uint32_t  u32stop_bits);
void UART_SetTimeoutCnt(UART_T* uart, uint32_t u32TOC);
void UART_SelectIrDAMode(UART_T* uart, uint32_t u32Buadrate, uint32_t u32Direction);
void UART_SelectRS485Mode(UART_T* uart, uint32_t u32Mode, uint32_t u32Addr);
void UART_SelectLINMode(UART_T* uart, uint32_t u32Mode, uint32_t u32BreakLength);
uint32_t UART_Write(UART_T* uart, uint8_t *pu8TxBuf, uint32_t u32WriteBytes);


/*@}*/ /* end of group UART_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group UART_Driver */

/*@}*/ /* end of group Device_Driver */

#ifdef __cplusplus
}
#endif

#endif //__UART_H__

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/

