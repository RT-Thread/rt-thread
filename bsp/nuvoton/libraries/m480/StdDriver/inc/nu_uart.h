/**************************************************************************//**
 * @file     nu_uart.h
 * @version  V3.00
 * @brief    M480 series UART driver header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2016-2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __NU_UART_H__
#define __NU_UART_H__


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

#define UART0_FIFO_SIZE 16ul /*!< UART0 supports separated receive/transmit 16/16 bytes entry FIFO \hideinitializer */
#define UART1_FIFO_SIZE 16ul /*!< UART1 supports separated receive/transmit 16/16 bytes entry FIFO \hideinitializer */
#define UART2_FIFO_SIZE 16ul /*!< UART2 supports separated receive/transmit 16/16 bytes entry FIFO \hideinitializer */
#define UART3_FIFO_SIZE 16ul /*!< UART3 supports separated receive/transmit 16/16 bytes entry FIFO \hideinitializer */
#define UART4_FIFO_SIZE 16ul /*!< UART4 supports separated receive/transmit 16/16 bytes entry FIFO \hideinitializer */
#define UART5_FIFO_SIZE 16ul /*!< UART5 supports separated receive/transmit 16/16 bytes entry FIFO \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/* UART_FIFO constants definitions                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

#define UART_FIFO_RFITL_1BYTE      (0x0ul << UART_FIFO_RFITL_Pos)   /*!< UART_FIFO setting to set RX FIFO Trigger Level to 1 byte \hideinitializer */
#define UART_FIFO_RFITL_4BYTES     (0x1ul << UART_FIFO_RFITL_Pos)   /*!< UART_FIFO setting to set RX FIFO Trigger Level to 4 bytes \hideinitializer */
#define UART_FIFO_RFITL_8BYTES     (0x2ul << UART_FIFO_RFITL_Pos)   /*!< UART_FIFO setting to set RX FIFO Trigger Level to 8 bytes \hideinitializer */
#define UART_FIFO_RFITL_14BYTES    (0x3ul << UART_FIFO_RFITL_Pos)   /*!< UART_FIFO setting to set RX FIFO Trigger Level to 14 bytes \hideinitializer */

#define UART_FIFO_RTSTRGLV_1BYTE      (0x0ul << UART_FIFO_RTSTRGLV_Pos)  /*!< UART_FIFO setting to set RTS Trigger Level to 1 byte \hideinitializer */
#define UART_FIFO_RTSTRGLV_4BYTES     (0x1ul << UART_FIFO_RTSTRGLV_Pos)  /*!< UART_FIFO setting to set RTS Trigger Level to 4 bytes \hideinitializer */
#define UART_FIFO_RTSTRGLV_8BYTES     (0x2ul << UART_FIFO_RTSTRGLV_Pos)  /*!< UART_FIFO setting to set RTS Trigger Level to 8 bytes \hideinitializer */
#define UART_FIFO_RTSTRGLV_14BYTES    (0x3ul << UART_FIFO_RTSTRGLV_Pos)  /*!< UART_FIFO setting to set RTS Trigger Level to 14 bytes \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/* UART_LINE constants definitions                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#define UART_WORD_LEN_5     (0ul) /*!< UART_LINE setting to set UART word length to 5 bits \hideinitializer */
#define UART_WORD_LEN_6     (1ul) /*!< UART_LINE setting to set UART word length to 6 bits \hideinitializer */
#define UART_WORD_LEN_7     (2ul) /*!< UART_LINE setting to set UART word length to 7 bits \hideinitializer */
#define UART_WORD_LEN_8     (3ul) /*!< UART_LINE setting to set UART word length to 8 bits \hideinitializer */

#define UART_PARITY_NONE    (0x0ul << UART_LINE_PBE_Pos) /*!< UART_LINE setting to set UART as no parity   \hideinitializer */
#define UART_PARITY_ODD     (0x1ul << UART_LINE_PBE_Pos) /*!< UART_LINE setting to set UART as odd parity  \hideinitializer */
#define UART_PARITY_EVEN    (0x3ul << UART_LINE_PBE_Pos) /*!< UART_LINE setting to set UART as even parity \hideinitializer */
#define UART_PARITY_MARK    (0x5ul << UART_LINE_PBE_Pos) /*!< UART_LINE setting to keep parity bit as '1'  \hideinitializer */
#define UART_PARITY_SPACE   (0x7ul << UART_LINE_PBE_Pos) /*!< UART_LINE setting to keep parity bit as '0'  \hideinitializer */

#define UART_STOP_BIT_1     (0x0ul << UART_LINE_NSB_Pos) /*!< UART_LINE setting for one stop bit  \hideinitializer */
#define UART_STOP_BIT_1_5   (0x1ul << UART_LINE_NSB_Pos) /*!< UART_LINE setting for 1.5 stop bit when 5-bit word length  \hideinitializer */
#define UART_STOP_BIT_2     (0x1ul << UART_LINE_NSB_Pos) /*!< UART_LINE setting for two stop bit when 6, 7, 8-bit word length \hideinitializer */


/*---------------------------------------------------------------------------------------------------------*/
/* UART RTS ACTIVE LEVEL constants definitions                                                             */
/*---------------------------------------------------------------------------------------------------------*/
#define UART_RTS_IS_LOW_LEV_ACTIVE   (0x1ul << UART_MODEM_RTSACTLV_Pos) /*!< Set RTS is Low Level Active \hideinitializer */
#define UART_RTS_IS_HIGH_LEV_ACTIVE  (0x0ul << UART_MODEM_RTSACTLV_Pos) /*!< Set RTS is High Level Active \hideinitializer */


/*---------------------------------------------------------------------------------------------------------*/
/* UART_IRDA constants definitions                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#define UART_IRDA_TXEN      (0x1ul << UART_IRDA_TXEN_Pos) /*!< Set IrDA function Tx mode \hideinitializer */
#define UART_IRDA_RXEN      (0x0ul << UART_IRDA_TXEN_Pos) /*!< Set IrDA function Rx mode \hideinitializer */


/*---------------------------------------------------------------------------------------------------------*/
/* UART_FUNCSEL constants definitions                                                                      */
/*---------------------------------------------------------------------------------------------------------*/
#define UART_FUNCSEL_UART  (0x0ul << UART_FUNCSEL_FUNCSEL_Pos) /*!< UART_FUNCSEL setting to set UART Function  (Default) \hideinitializer */
#define UART_FUNCSEL_LIN   (0x1ul << UART_FUNCSEL_FUNCSEL_Pos) /*!< UART_FUNCSEL setting to set LIN Function             \hideinitializer */
#define UART_FUNCSEL_IrDA  (0x2ul << UART_FUNCSEL_FUNCSEL_Pos) /*!< UART_FUNCSEL setting to set IrDA Function            \hideinitializer */
#define UART_FUNCSEL_RS485 (0x3ul << UART_FUNCSEL_FUNCSEL_Pos) /*!< UART_FUNCSEL setting to set RS485 Function           \hideinitializer */


/*---------------------------------------------------------------------------------------------------------*/
/* UART_LINCTL constants definitions                                                                       */
/*---------------------------------------------------------------------------------------------------------*/
#define UART_LINCTL_BRKFL(x)    (((x)-1) << UART_LINCTL_BRKFL_Pos)  /*!< UART_LINCTL setting to set LIN Break Field Length, x = 10 ~ 15, default value is 12 \hideinitializer */
#define UART_LINCTL_BSL(x)      (((x)-1) << UART_LINCTL_BSL_Pos)    /*!< UART_LINCTL setting to set LIN Break/Sync Delimiter Length, x = 1 ~ 4 \hideinitializer */
#define UART_LINCTL_HSEL_BREAK             (0x0UL << UART_LINCTL_HSEL_Pos)    /*!< UART_LINCTL setting to set LIN Header Select to break field \hideinitializer */
#define UART_LINCTL_HSEL_BREAK_SYNC        (0x1UL << UART_LINCTL_HSEL_Pos)    /*!< UART_LINCTL setting to set LIN Header Select to break field and sync field \hideinitializer */
#define UART_LINCTL_HSEL_BREAK_SYNC_ID     (0x2UL << UART_LINCTL_HSEL_Pos)    /*!< UART_LINCTL setting to set LIN Header Select to break field, sync field and ID field \hideinitializer */
#define UART_LINCTL_PID(x)      ((x) << UART_LINCTL_PID_Pos)       /*!< UART_LINCTL setting to set LIN PID value \hideinitializer */


/*---------------------------------------------------------------------------------------------------------*/
/* UART BAUDRATE MODE constants definitions                                                                */
/*---------------------------------------------------------------------------------------------------------*/
#define UART_BAUD_MODE0     (0ul) /*!< Set UART Baudrate Mode is Mode0 \hideinitializer */
#define UART_BAUD_MODE2     (UART_BAUD_BAUDM1_Msk | UART_BAUD_BAUDM0_Msk) /*!< Set UART Baudrate Mode is Mode2 \hideinitializer */


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
 *    \hideinitializer
 */
#define UART_BAUD_MODE0_DIVIDER(u32SrcFreq, u32BaudRate)    ((((u32SrcFreq) + ((u32BaudRate)*8ul)) / (u32BaudRate) >> 4ul)-2ul)


/**
 *    @brief        Calculate UART baudrate mode2 divider
 *
 *    @param[in]    u32SrcFreq      UART clock frequency
 *    @param[in]    u32BaudRate     Baudrate of UART module
 *
 *    @return       UART baudrate mode2 divider
 *
 *    @details      This macro calculate UART baudrate mode2 divider.
 *    \hideinitializer
 */
#define UART_BAUD_MODE2_DIVIDER(u32SrcFreq, u32BaudRate)    ((((u32SrcFreq) + ((u32BaudRate)/2ul)) / (u32BaudRate))-2ul)


/**
 *    @brief        Write UART data
 *
 *    @param[in]    uart    The pointer of the specified UART module
 *    @param[in]    u8Data  Data byte to transmit.
 *
 *    @return       None
 *
 *    @details      This macro write Data to Tx data register.
 *    \hideinitializer
 */
#define UART_WRITE(uart, u8Data)    ((uart)->DAT = (u8Data))


/**
 *    @brief        Read UART data
 *
 *    @param[in]    uart    The pointer of the specified UART module
 *
 *    @return       The oldest data byte in RX FIFO.
 *
 *    @details      This macro read Rx data register.
 *    \hideinitializer
 */
#define UART_READ(uart)    ((uart)->DAT)


/**
 *    @brief        Get Tx empty
 *
 *    @param[in]    uart    The pointer of the specified UART module
 *
 *    @retval       0   Tx FIFO is not empty
 *    @retval       >=1 Tx FIFO is empty
 *
 *    @details      This macro get Transmitter FIFO empty register value.
 *    \hideinitializer
 */
#define UART_GET_TX_EMPTY(uart)    ((uart)->FIFOSTS & UART_FIFOSTS_TXEMPTY_Msk)


/**
 *    @brief        Get Rx empty
 *
 *    @param[in]    uart    The pointer of the specified UART module
 *
 *    @retval       0   Rx FIFO is not empty
 *    @retval       >=1 Rx FIFO is empty
 *
 *    @details      This macro get Receiver FIFO empty register value.
 *    \hideinitializer
 */
#define UART_GET_RX_EMPTY(uart)    ((uart)->FIFOSTS & UART_FIFOSTS_RXEMPTY_Msk)


/**
 *    @brief        Check specified UART port transmission is over.
 *
 *    @param[in]    uart    The pointer of the specified UART module
 *
 *    @retval       0 Tx transmission is not over
 *    @retval       1 Tx transmission is over
 *
 *    @details      This macro return Transmitter Empty Flag register bit value.
 *                  It indicates if specified UART port transmission is over nor not.
 *    \hideinitializer
 */
#define UART_IS_TX_EMPTY(uart)    (((uart)->FIFOSTS & UART_FIFOSTS_TXEMPTYF_Msk) >> UART_FIFOSTS_TXEMPTYF_Pos)


/**
 *    @brief        Wait specified UART port transmission is over
 *
 *    @param[in]    uart    The pointer of the specified UART module
 *
 *    @return       None
 *
 *    @details      This macro wait specified UART port transmission is over.
 *    \hideinitializer
 */
#define UART_WAIT_TX_EMPTY(uart)    while(!((((uart)->FIFOSTS) & UART_FIFOSTS_TXEMPTYF_Msk) >> UART_FIFOSTS_TXEMPTYF_Pos))


/**
 *    @brief        Check RX is ready or not
 *
 *    @param[in]    uart    The pointer of the specified UART module
 *
 *    @retval       0 The number of bytes in the RX FIFO is less than the RFITL
 *    @retval       1 The number of bytes in the RX FIFO equals or larger than RFITL
 *
 *    @details      This macro check receive data available interrupt flag is set or not.
 *    \hideinitializer
 */
#define UART_IS_RX_READY(uart)    (((uart)->INTSTS & UART_INTSTS_RDAIF_Msk)>>UART_INTSTS_RDAIF_Pos)


/**
 *    @brief        Check TX FIFO is full or not
 *
 *    @param[in]    uart    The pointer of the specified UART module
 *
 *    @retval       1 TX FIFO is full
 *    @retval       0 TX FIFO is not full
 *
 *    @details      This macro check TX FIFO is full or not.
 *    \hideinitializer
 */
#define UART_IS_TX_FULL(uart)    (((uart)->FIFOSTS & UART_FIFOSTS_TXFULL_Msk)>>UART_FIFOSTS_TXFULL_Pos)


/**
 *    @brief        Check RX FIFO is full or not
 *
 *    @param[in]    uart    The pointer of the specified UART module
 *
 *    @retval       1 RX FIFO is full
 *    @retval       0 RX FIFO is not full
 *
 *    @details      This macro check RX FIFO is full or not.
 *    \hideinitializer
 */
#define UART_IS_RX_FULL(uart)    (((uart)->FIFOSTS & UART_FIFOSTS_RXFULL_Msk)>>UART_FIFOSTS_RXFULL_Pos)


/**
 *    @brief        Get Tx full register value
 *
 *    @param[in]    uart    The pointer of the specified UART module
 *
 *    @retval       0   Tx FIFO is not full.
 *    @retval       >=1 Tx FIFO is full.
 *
 *    @details      This macro get Tx full register value.
 *    \hideinitializer
 */
#define UART_GET_TX_FULL(uart)    ((uart)->FIFOSTS & UART_FIFOSTS_TXFULL_Msk)


/**
 *    @brief        Get Rx full register value
 *
 *    @param[in]    uart    The pointer of the specified UART module
 *
 *    @retval       0   Rx FIFO is not full.
 *    @retval       >=1 Rx FIFO is full.
 *
 *    @details      This macro get Rx full register value.
 *    \hideinitializer
 */
#define UART_GET_RX_FULL(uart)    ((uart)->FIFOSTS & UART_FIFOSTS_RXFULL_Msk)


/**
 *    @brief        Enable specified UART interrupt
 *
 *    @param[in]    uart        The pointer of the specified UART module
 *    @param[in]    u32eIntSel  Interrupt type select
 *                              - \ref UART_INTEN_ABRIEN_Msk     : Auto baud rate interrupt
 *                              - \ref UART_INTEN_WKIEN_Msk      : Wakeup interrupt
 *                              - \ref UART_INTEN_LINIEN_Msk     : Lin bus interrupt
 *                              - \ref UART_INTEN_BUFERRIEN_Msk  : Buffer Error interrupt
 *                              - \ref UART_INTEN_RXTOIEN_Msk    : Rx time-out interrupt
 *                              - \ref UART_INTEN_MODEMIEN_Msk   : Modem interrupt
 *                              - \ref UART_INTEN_RLSIEN_Msk     : Rx Line status interrupt
 *                              - \ref UART_INTEN_THREIEN_Msk    : Tx empty interrupt
 *                              - \ref UART_INTEN_RDAIEN_Msk     : Rx ready interrupt
 *
 *    @return       None
 *
 *    @details      This macro enable specified UART interrupt.
 *    \hideinitializer
 */
#define UART_ENABLE_INT(uart, u32eIntSel)    ((uart)->INTEN |= (u32eIntSel))


/**
 *    @brief        Disable specified UART interrupt
 *
 *    @param[in]    uart        The pointer of the specified UART module
 *    @param[in]    u32eIntSel  Interrupt type select
 *                              - \ref UART_INTEN_ABRIEN_Msk     : Auto baud rate interrupt
 *                              - \ref UART_INTEN_WKIEN_Msk      : Wakeup interrupt
 *                              - \ref UART_INTEN_LINIEN_Msk     : Lin bus interrupt
 *                              - \ref UART_INTEN_BUFERRIEN_Msk  : Buffer Error interrupt
 *                              - \ref UART_INTEN_RXTOIEN_Msk    : Rx time-out interrupt
 *                              - \ref UART_INTEN_MODEMIEN_Msk   : Modem status interrupt
 *                              - \ref UART_INTEN_RLSIEN_Msk     : Receive Line status interrupt
 *                              - \ref UART_INTEN_THREIEN_Msk    : Tx empty interrupt
 *                              - \ref UART_INTEN_RDAIEN_Msk     : Rx ready interrupt
 *
 *    @return       None
 *
 *    @details      This macro enable specified UART interrupt.
 *    \hideinitializer
 */
#define UART_DISABLE_INT(uart, u32eIntSel)    ((uart)->INTEN &= ~ (u32eIntSel))


/**
 *    @brief        Get specified interrupt flag/status
 *
 *    @param[in]    uart            The pointer of the specified UART module
 *    @param[in]    u32eIntTypeFlag Interrupt Type Flag, should be
 *                                  - \ref UART_INTSTS_HWBUFEINT_Msk : In DMA Mode, Buffer Error Interrupt Indicator
 *                                  - \ref UART_INTSTS_HWTOINT_Msk   : In DMA Mode, Time-out Interrupt Indicator
 *                                  - \ref UART_INTSTS_HWMODINT_Msk  : In DMA Mode, MODEM Status Interrupt Indicator
 *                                  - \ref UART_INTSTS_HWRLSINT_Msk  : In DMA Mode, Receive Line Status Interrupt Indicator
 *                                  - \ref UART_INTSTS_HWBUFEIF_Msk  : In DMA Mode, Buffer Error Interrupt Flag
 *                                  - \ref UART_INTSTS_HWTOIF_Msk    : In DMA Mode, Time-out Interrupt Flag
 *                                  - \ref UART_INTSTS_HWMODIF_Msk   : In DMA Mode, MODEM Interrupt Flag
 *                                  - \ref UART_INTSTS_HWRLSIF_Msk   : In DMA Mode, Receive Line Status Flag
 *                                  - \ref UART_INTSTS_LININT_Msk    : LIN Bus Interrupt Indicator
 *                                  - \ref UART_INTSTS_BUFERRINT_Msk : Buffer Error Interrupt Indicator
 *                                  - \ref UART_INTSTS_RXTOINT_Msk   : Time-out Interrupt Indicator
 *                                  - \ref UART_INTSTS_MODEMINT_Msk  : Modem Status Interrupt Indicator
 *                                  - \ref UART_INTSTS_RLSINT_Msk    : Receive Line Status Interrupt Indicator
 *                                  - \ref UART_INTSTS_THREINT_Msk   : Transmit Holding Register Empty Interrupt Indicator
 *                                  - \ref UART_INTSTS_RDAINT_Msk    : Receive Data Available Interrupt Indicator
 *                                  - \ref UART_INTSTS_LINIF_Msk     : LIN Bus Flag
 *                                  - \ref UART_INTSTS_BUFERRIF_Msk  : Buffer Error Interrupt Flag
 *                                  - \ref UART_INTSTS_RXTOIF_Msk    : Rx Time-out Interrupt Flag
 *                                  - \ref UART_INTSTS_MODEMIF_Msk   : Modem Interrupt Flag
 *                                  - \ref UART_INTSTS_RLSIF_Msk     : Receive Line Status Interrupt Flag
 *                                  - \ref UART_INTSTS_THREIF_Msk    : Tx Empty Interrupt Flag
 *                                  - \ref UART_INTSTS_RDAIF_Msk     : Rx Ready Interrupt Flag
 *
 *    @retval       0 The specified interrupt is not happened.
 *                  1 The specified interrupt is happened.
 *
 *    @details      This macro get specified interrupt flag or interrupt indicator status.
 *    \hideinitializer
 */
#define UART_GET_INT_FLAG(uart,u32eIntTypeFlag)    (((uart)->INTSTS & (u32eIntTypeFlag))?1:0)


/**
 *    @brief        Clear RS-485 Address Byte Detection Flag
 *
 *    @param[in]    uart    The pointer of the specified UART module
 *
 *    @return       None
 *
 *    @details      This macro clear RS-485 address byte detection flag.
 *    \hideinitializer
 */
#define UART_RS485_CLEAR_ADDR_FLAG(uart)    ((uart)->FIFOSTS = UART_FIFOSTS_ADDRDETF_Msk)


/**
 *    @brief        Get RS-485 Address Byte Detection Flag
 *
 *    @param[in]    uart    The pointer of the specified UART module
 *
 *    @retval       0 Receiver detects a data that is not an address bit.
 *    @retval       1 Receiver detects a data that is an address bit.
 *
 *    @details      This macro get RS-485 address byte detection flag.
 *    \hideinitializer
 */
#define UART_RS485_GET_ADDR_FLAG(uart)    (((uart)->FIFOSTS  & UART_FIFOSTS_ADDRDETF_Msk) >> UART_FIFOSTS_ADDRDETF_Pos)

/* Declare these inline functions here to avoid MISRA C 2004 rule 8.1 error */
__STATIC_INLINE void UART_CLEAR_RTS(UART_T* uart);
__STATIC_INLINE void UART_SET_RTS(UART_T* uart);


/**
 *    @brief        Set RTS pin to low
 *
 *    @param[in]    uart    The pointer of the specified UART module
 *
 *    @return       None
 *
 *    @details      This macro set RTS pin to low.
 */
__STATIC_INLINE void UART_CLEAR_RTS(UART_T* uart)
{
    uart->MODEM |= UART_MODEM_RTSACTLV_Msk;
    uart->MODEM &= ~UART_MODEM_RTS_Msk;
}


/**
 *    @brief        Set RTS pin to high
 *
 *    @param[in]    uart    The pointer of the specified UART module
 *
 *    @return       None
 *
 *    @details      This macro set RTS pin to high.
 */
__STATIC_INLINE void UART_SET_RTS(UART_T* uart)
{
    uart->MODEM |= UART_MODEM_RTSACTLV_Msk | UART_MODEM_RTS_Msk;
}

/**
 *    @brief        Enable specified UART PDMA function
 *
 *    @param[in]    uart        The pointer of the specified UART module
 *    @param[in]    u32FuncSel  Combination of following functions
 *                             - \ref UART_INTEN_TXPDMAEN_Msk
 *                             - \ref UART_INTEN_RXPDMAEN_Msk
 *
 *    @return       None
 *
 *    \hideinitializer
 */
#define UART_PDMA_ENABLE(uart, u32FuncSel)    ((uart)->INTEN |= (u32FuncSel))
/**
 *    @brief        Disable specified UART PDMA function
 *
 *    @param[in]    uart        The pointer of the specified UART module
 *    @param[in]    u32FuncSel  Combination of following functions
 *                             - \ref UART_INTEN_TXPDMAEN_Msk
 *                             - \ref UART_INTEN_RXPDMAEN_Msk
 *
 *    @return       None
 *
 *    \hideinitializer
 */
#define UART_PDMA_DISABLE(uart, u32FuncSel)    ((uart)->INTEN &= ~(u32FuncSel))


void UART_ClearIntFlag(UART_T* uart, uint32_t u32InterruptFlag);
void UART_Close(UART_T* uart);
void UART_DisableFlowCtrl(UART_T* uart);
void UART_DisableInt(UART_T*  uart, uint32_t u32InterruptFlag);
void UART_EnableFlowCtrl(UART_T* uart);
void UART_EnableInt(UART_T*  uart, uint32_t u32InterruptFlag);
void UART_Open(UART_T* uart, uint32_t u32baudrate);
uint32_t UART_Read(UART_T* uart, uint8_t pu8RxBuf[], uint32_t u32ReadBytes);
void UART_SetLineConfig(UART_T* uart, uint32_t u32baudrate, uint32_t u32data_width, uint32_t u32parity, uint32_t  u32stop_bits);
void UART_SetTimeoutCnt(UART_T* uart, uint32_t u32TOC);
void UART_SelectIrDAMode(UART_T* uart, uint32_t u32Buadrate, uint32_t u32Direction);
void UART_SelectRS485Mode(UART_T* uart, uint32_t u32Mode, uint32_t u32Addr);
void UART_SelectLINMode(UART_T* uart, uint32_t u32Mode, uint32_t u32BreakLength);
uint32_t UART_Write(UART_T* uart, uint8_t pu8TxBuf[], uint32_t u32WriteBytes);




/*@}*/ /* end of group UART_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group UART_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif /*__NU_UART_H__*/

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
