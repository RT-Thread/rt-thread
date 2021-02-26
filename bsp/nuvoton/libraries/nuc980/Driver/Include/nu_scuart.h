/**************************************************************************//**
 * @file     scuart.h
 * @brief    NUC980 series Smartcard UART mode (SCUART) driver header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __NU_SCUART_H__
#define __NU_SCUART_H__
#include "nuc980.h"
#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup SCUART_Driver SCUART Driver
  @{
*/

/** @addtogroup SCUART_EXPORTED_CONSTANTS SCUART Exported Constants
  @{
*/
#define SCUART_CHAR_LEN_5     (0x3ul << 4)  /*!< Set SCUART word length to 5 bits */
#define SCUART_CHAR_LEN_6     (0x2ul << 4)  /*!< Set SCUART word length to 6 bits */
#define SCUART_CHAR_LEN_7     (0x1ul << 4)  /*!< Set SCUART word length to 7 bits */
#define SCUART_CHAR_LEN_8     (0)                            /*!< Set SCUART word length to 8 bits */

#define SCUART_PARITY_NONE    (0x00000040)                   /*!< Set SCUART transfer with no parity   */
#define SCUART_PARITY_ODD     (0x00000080)                   /*!< Set SCUART transfer with odd parity  */
#define SCUART_PARITY_EVEN    (0)                            /*!< Set SCUART transfer with even parity */

#define SCUART_STOP_BIT_1     (0x00008000)                   /*!< Set SCUART transfer with one stop bit  */
#define SCUART_STOP_BIT_2     (0)                            /*!< Set SCUART transfer with two stop bits */

#define SC_STATUS_RXEMPTY_Msk   0x00000002
#define SC_STATUS_RXFULL_Msk    0x00000004
#define SC_STATUS_PEF_Msk       0x00000010
#define SC_STATUS_FEF_Msk       0x00000020
#define SC_STATUS_BEF_Msk       0x00000040
#define SC_STATUS_TXEMPTY_Msk   0x00000200
#define SC_STATUS_TXFULL_Msk    0x00000400
#define SC_STATUS_TXACT_Msk     0x80000000

#define SC_INTEN_RXTOIEN_Msk    0x00000200
#define SC_INTEN_TERRIEN_Msk    0x00000004
#define SC_INTEN_TBEIEN_Msk     0x00000002
#define SC_INTEN_RDAIEN_Msk     0x00000001

#define SC_INTSTS_RBTOIF_Msk    0x00000200
#define SC_INTSTS_TERRIF_Msk    0x00000004
#define SC_INTSTS_TBEIF_Msk     0x00000002
#define SC_INTSTS_RDAIF_Msk     0x00000001

#define SC_CTL_SCEN_Msk         0x00000001
#define SC_CTL_NSB_Msk          0x00008000

#define SC_UARTCTL_UARTEN_Msk   0x00000001

/*@}*/ /* end of group SCUART_EXPORTED_CONSTANTS */


/** @addtogroup SCUART_EXPORTED_FUNCTIONS SCUART Exported Functions
  @{
*/

/* TX Macros */
/**
  * @brief Write Data to Tx data register.
  * @param[in] sc Smartcard module number
  * @param[in] u8Data Data byte to transmit.
  * @return None
  * @details By writing data to DAT register, the SC will send out an 8-bit data.
  * \hideinitializer
  */
#define SCUART_WRITE(sc, u8Data) \
do {\
    if(sc == 0)\
        outpw(REG_SC0_DAT, u8Data);\
    else\
        outpw(REG_SC1_DAT, u8Data);\
}while(0)

/**
  * @brief Get TX FIFO empty flag status from register.
  * @param[in] sc Smartcard module number
  * @return Transmit FIFO empty status.
  * @retval 0 Transmit FIFO is not empty.
  * @retval SC_STATUS_TXEMPTY_Msk Transmit FIFO is empty.
  * @details When the last byte of TX buffer has been transferred to Transmitter Shift Register, hardware sets TXEMPTY bit (SC_STATUS[9]) high.
  *          It will be cleared when writing data into DAT (SC_DAT[7:0]).
  * \hideinitializer
  */
#define SCUART_GET_TX_EMPTY(sc) (sc == 0 ? (inpw(REG_SC0_STATUS) & SC_STATUS_TXEMPTY_Msk) : (inpw(REG_SC1_STATUS) & SC_STATUS_TXEMPTY_Msk))

/**
  * @brief Get TX FIFO full flag status from register.
  * @param[in] sc Smartcard module number
  * @retval 0 Transmit FIFO is not full.
  * @retval SC_STATUS_TXFULL_Msk Transmit FIFO is full.
  * @details TXFULL(SC_STATUS[10]) is set when TX pointer is equal to 4, otherwise is cleared by hardware.
  * \hideinitializer
  */
#define SCUART_GET_TX_FULL(sc) (sc == 0 ? (inpw(REG_SC0_STATUS) & SC_STATUS_TXFULL_Msk) : (inpw(REG_SC1_STATUS) & SC_STATUS_TXFULL_Msk))

/**
  * @brief Wait specified smartcard port transmission complete.
  * @param[in] sc Smartcard module number
  * @return None
  * @details TXACT (SC_STATUS[31]) is cleared automatically when TX transfer is finished or the last byte transmission has completed.
  * @note This macro blocks until transmit complete.
  * \hideinitializer
  */
#define SCUART_WAIT_TX_EMPTY(sc)\
do {\
    if(sc == 0)\
        while(inpw(REG_SC0_STATUS) & SC_STATUS_TXACT_Msk);\
    else\
        while(inpw(REG_SC1_STATUS) & SC_STATUS_TXACT_Msk);\
}while(0)

/**
  * @brief Check specified smartcard port transmit FIFO is full or not.
  * @param[in] sc Smartcard module number
  * @retval 0 Transmit FIFO is not full.
  * @retval 1 Transmit FIFO is full.
  * @details TXFULL(SC_STATUS[10]) indicates TX buffer full or not.
  *          This is set when TX pointer is equal to 4, otherwise is cleared by hardware.
  * \hideinitializer
  */
#define SCUART_IS_TX_FULL(sc) (sc == 0 ? (inpw(REG_SC0_STATUS) & SC_STATUS_TXFULL_Msk ? 1 : 0) : (inpw(REG_SC1_STATUS) & SC_STATUS_TXFULL_Msk ? 1 : 0))

/**
  * @brief Check specified smartcard port transmission is over.
  * @param[in] sc Smartcard module number
  * @retval 0 Transmit is not complete.
  * @retval 1 Transmit complete.
  * @details TXACT (SC_STATUS[31]) is set by hardware when TX transfer is in active and the STOP bit of the last byte has been transmitted.
  * \hideinitializer
  */
#define SCUART_IS_TX_EMPTY(sc) (sc == 0 ? (inpw(REG_SC0_STATUS) & SC_STATUS_TXACT_Msk ? 1 : 0) : (inpw(REG_SC1_STATUS) & SC_STATUS_TXACT_Msk ? 1 : 0))

/* RX Macros */

/**
  * @brief Read Rx data register.
  * @param[in] sc Smartcard module number
  * @return The oldest data byte in RX FIFO.
  * @details By reading DAT register, the SC will return an 8-bit received data.
  * \hideinitializer
  */
#define SCUART_READ(sc) (sc == 0 ? inpw(REG_SC0_DAT) : inpw(REG_SC1_DAT))

/**
  * @brief Get RX FIFO empty flag status from register.
  * @param[in] sc Smartcard module number
  * @retval 0 Receive FIFO is not empty.
  * @retval SC_STATUS_RXEMPTY_Msk Receive FIFO is empty.
  * @details When the last byte of Rx buffer has been read by CPU, hardware sets RXEMPTY(SC_STATUS[1]) high.
  *          It will be cleared when SC receives any new data.
  * \hideinitializer
  */
#define SCUART_GET_RX_EMPTY(sc) (sc == 0 ? (inpw(REG_SC0_STATUS) & SC_STATUS_RXEMPTY_Msk) : (inpw(REG_SC1_STATUS) & SC_STATUS_RXEMPTY_Msk))


/**
  * @brief Get RX FIFO full flag status from register.
  * @param[in] sc Smartcard module number
  * @retval 0 Receive FIFO is not full.
  * @retval SC_STATUS_RXFULL_Msk Receive FIFO is full.
  * @details RXFULLF(SC_STATUS[2]) is set when RX pointer is equal to 4, otherwise it is cleared by hardware.
  * \hideinitializer
  */
#define SCUART_GET_RX_FULL(sc) (sc == 0 ? (inpw(REG_SC0_STATUS) & SC_STATUS_RXFULL_Msk) : (inpw(REG_SC1_STATUS) & SC_STATUS_RXFULL_Msk))

/**
  * @brief Check if receive data number in FIFO reach FIFO trigger level or not.
  * @param[in] sc Smartcard module number
  * @retval 0 The number of bytes in receive FIFO is less than trigger level.
  * @retval 1 The number of bytes in receive FIFO equals or larger than trigger level.
  * @details RDAIF(SC_INTSTS[0]) is used for received data reaching trigger level RXTRGLV (SC_CTL[7:6]) interrupt status flag.
  * @note If receive trigger level is \b not 1 byte, this macro return 0 does not necessary indicates there is no data in FIFO.
  * \hideinitializer
  */
#define SCUART_IS_RX_READY(sc) (sc == 0 ? (inpw(REG_SC0_INTSTS) & SC_INTSTS_RDAIF_Msk ? 1 : 0) : (inpw(REG_SC1_INTSTS) & SC_INTSTS_RDAIF_Msk ? 1 : 0))

/**
  * @brief Check specified smartcard port receive FIFO is full or not.
  * @param[in] sc Smartcard module number
  * @retval 0 Receive FIFO is not full.
  * @retval 1 Receive FIFO is full.
  * @details RXFULLF(SC_STATUS[2]) is set when RX pointer is equal to 4, otherwise it is cleared by hardware.
  * \hideinitializer
  */
#define SCUART_IS_RX_FULL(sc) (sc == 0 ? (inpw(REG_SC0_STATUS) & SC_STATUS_RXFULL_Msk ? 1 : 0) : (inpw(REG_SC1_STATUS) & SC_STATUS_RXFULL_Msk ? 1 : 0))

/* Interrupt Macros */

/**
  * @brief Enable specified interrupts.
  * @param[in] sc Smartcard module number
  * @param[in] u32Mask Interrupt masks to enable, a combination of following bits.
  *             - \ref SC_INTEN_RXTOIEN_Msk
  *             - \ref SC_INTEN_TERRIEN_Msk
  *             - \ref SC_INTEN_TBEIEN_Msk
  *             - \ref SC_INTEN_RDAIEN_Msk
  * @return None
  * @details The macro is used to enable receiver buffer time-out interrupt, transfer error interrupt,
  *          transmit buffer empty interrupt or receive data reach trigger level interrupt.
  * \hideinitializer
  */
#define SCUART_ENABLE_INT(sc, u32Mask)\
do {\
    if(sc == 0)\
        outpw(REG_SC0_INTEN, inpw(REG_SC0_INTEN) | (u32Mask));\
    else\
        outpw(REG_SC1_INTEN, inpw(REG_SC1_INTEN) | (u32Mask));\
}while(0)

/**
  * @brief Disable specified interrupts.
  * @param[in] sc Smartcard module number
  * @param[in] u32Mask Interrupt masks to disable, a combination of following bits.
  *             - \ref SC_INTEN_RXTOIEN_Msk
  *             - \ref SC_INTEN_TERRIEN_Msk
  *             - \ref SC_INTEN_TBEIEN_Msk
  *             - \ref SC_INTEN_RDAIEN_Msk
  * @return None
  * @details The macro is used to disable receiver buffer time-out interrupt, transfer error interrupt,
  *          transmit buffer empty interrupt or receive data reach trigger level interrupt.
  * \hideinitializer
  */
#define SCUART_DISABLE_INT(sc, u32Mask)\
do {\
    if(sc == 0)\
        outpw(REG_SC0_INTEN, inpw(REG_SC0_INTEN) & ~(u32Mask));\
    else\
        outpw(REG_SC1_INTEN, inpw(REG_SC1_INTEN) & ~(u32Mask));\
}while(0)

/**
  * @brief Get specified interrupt flag/status.
  * @param[in] sc Smartcard module number
  * @param[in] u32Type Interrupt flag/status to check, could be one of following value:
  *             - \ref SC_INTSTS_RBTOIF_Msk
  *             - \ref SC_INTSTS_TERRIF_Msk
  *             - \ref SC_INTSTS_TBEIF_Msk
  *             - \ref SC_INTSTS_RDAIF_Msk
  * @return The status of specified interrupt.
  * @retval 0 Specified interrupt does not happened.
  * @retval 1 Specified interrupt happened.
  * @details The macro is used to get receiver buffer time-out interrupt status, transfer error interrupt status,
  *          transmit buffer empty interrupt status or receive data reach interrupt status.
  * \hideinitializer
  */
#define SCUART_GET_INT_FLAG(sc, u32Type) (sc == 0 ? (inpw(REG_SC0_INTSTS) & (u32Type) ? 1 : 0) : (inpw(REG_SC1_INTSTS) & (u32Type) ? 1 : 0))

/**
  * @brief Clear specified interrupt flag/status.
  * @param[in] sc Smartcard module number
  * @param[in] u32Type Interrupt flag/status to clear, could be the combination of following values:
  *             - \ref SC_INTSTS_RBTOIF_Msk
  *             - \ref SC_INTSTS_TERRIF_Msk
  *             - \ref SC_INTSTS_TBEIF_Msk
  * @return None
  * @details The macro is used to clear receiver buffer time-out interrupt flag, transfer error interrupt flag or
  *          transmit buffer empty interrupt flag.
  * \hideinitializer
  */
#define SCUART_CLR_INT_FLAG(sc, u32Type) \
do {\
    if(sc == 0)\
        outpw(REG_SC0_INTSTS, (u32Type));\
    else\
        outpw(REG_SC1_INTSTS, (u32Type));\
}while(0)

/**
  * @brief Get receive error flag/status.
  * @param[in] sc Smartcard module number
  * @return Current receive error status, could one of following errors:
  * @retval SC_STATUS_PEF_Msk Parity error.
  * @retval SC_STATUS_FEF_Msk Frame error.
  * @retval SC_STATUS_BEF_Msk Break error.
  * @details The macro is used to get receiver parity error status, receiver frame error status or
  *          receiver break error status.
  * \hideinitializer
  */
#define SCUART_GET_ERR_FLAG(sc) (sc == 0 ? (inpw(REG_SC0_STATUS) & (SC_STATUS_PEF_Msk | SC_STATUS_FEF_Msk | SC_STATUS_BEF_Msk)) : (inpw(REG_SC1_STATUS) & (SC_STATUS_PEF_Msk | SC_STATUS_FEF_Msk | SC_STATUS_BEF_Msk)))

/**
  * @brief Clear specified receive error flag/status.
  * @param[in] sc Smartcard module number
  * @param[in] u32Mask Receive error flag/status to clear, combination following values:
  *             - \ref SC_STATUS_PEF_Msk
  *             - \ref SC_STATUS_FEF_Msk
  *             - \ref SC_STATUS_BEF_Msk
  * @return None
  * @details The macro is used to clear receiver parity error flag, receiver frame error flag or
  *          receiver break error flag.
  * \hideinitializer
  */
#define SCUART_CLR_ERR_FLAG(sc, u32Mask)\
do {\
    if(sc == 0)\
        outpw(REG_SC0_STATUS, (u32Mask));\
    else\
        outpw(REG_SC1_STATUS, (u32Mask));\
}while(0)

void SCUART_Close(UINT sc);
UINT SCUART_Open(UINT sc, UINT u32baudrate);
UINT SCUART_Read(UINT sc, char *pu8RxBuf, UINT u32ReadBytes);
UINT SCUART_SetLineConfig(UINT sc, UINT u32Baudrate, UINT u32DataWidth, UINT u32Parity, UINT  u32StopBits);
void SCUART_SetTimeoutCnt(UINT sc, UINT u32TOC);
void SCUART_Write(UINT sc, char *pu8TxBuf, UINT u32WriteBytes);

/*@}*/ /* end of group SCUART_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group SCUART_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif //__NU_SCUART_H__

