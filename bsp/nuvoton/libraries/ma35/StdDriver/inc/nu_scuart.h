/**************************************************************************//**
 * @file     nu_scuart.h
 * @brief    Smartcard UART mode (SCUART) driver header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __NU_SCUART_H__
#define __NU_SCUART_H__

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
#define SCUART_CHAR_LEN_5     (0x3ul << SC_UARTCTL_WLS_Pos)     /*!< Set SCUART word length to 5 bits \hideinitializer */
#define SCUART_CHAR_LEN_6     (0x2ul << SC_UARTCTL_WLS_Pos)     /*!< Set SCUART word length to 6 bits \hideinitializer */
#define SCUART_CHAR_LEN_7     (0x1ul << SC_UARTCTL_WLS_Pos)     /*!< Set SCUART word length to 7 bits \hideinitializer */
#define SCUART_CHAR_LEN_8     (0UL)                             /*!< Set SCUART word length to 8 bits \hideinitializer */

#define SCUART_PARITY_NONE    (SC_UARTCTL_PBOFF_Msk)            /*!< Set SCUART transfer with no parity   \hideinitializer */
#define SCUART_PARITY_ODD     (SC_UARTCTL_OPE_Msk)              /*!< Set SCUART transfer with odd parity  \hideinitializer */
#define SCUART_PARITY_EVEN    (0UL)                             /*!< Set SCUART transfer with even parity \hideinitializer */

#define SCUART_STOP_BIT_1     (SC_CTL_NSB_Msk)                  /*!< Set SCUART transfer with one stop bit  \hideinitializer */
#define SCUART_STOP_BIT_2     (0UL)                             /*!< Set SCUART transfer with two stop bits \hideinitializer */


/*@}*/ /* end of group SCUART_EXPORTED_CONSTANTS */


/** @addtogroup SCUART_EXPORTED_FUNCTIONS SCUART Exported Functions
  @{
*/

/* TX Macros */
/**
  * @brief Write Data to Tx data register
  * @param[in] sc The base address of smartcard module.
  * @param[in] u8Data Data byte to transmit
  * @return None
  * \hideinitializer
  */
#define SCUART_WRITE(sc, u8Data) ((sc)->DAT = (u8Data))

/**
  * @brief Get TX FIFO empty flag status from register
  * @param[in] sc The base address of smartcard module
  * @return Transmit FIFO empty status
  * @retval 0 Transmit FIFO is not empty
  * @retval SC_STATUS_TXEMPTY_Msk Transmit FIFO is empty
  * \hideinitializer
  */
#define SCUART_GET_TX_EMPTY(sc) ((sc)->STATUS & SC_STATUS_TXEMPTY_Msk)

/**
  * @brief Get TX FIFO full flag status from register
  * @param[in] sc The base address of smartcard module
  * @return Transmit FIFO full status
  * @retval 0 Transmit FIFO is not full
  * @retval SC_STATUS_TXFULL_Msk Transmit FIFO is full
  * \hideinitializer
  */
#define SCUART_GET_TX_FULL(sc) ((sc)->STATUS & SC_STATUS_TXFULL_Msk)

/**
  * @brief Wait specified smartcard port transmission complete
  * @param[in] sc The base address of smartcard module
  * @return None
  * @note This Macro blocks until transmit complete.
  * \hideinitializer
  */
#define SCUART_WAIT_TX_EMPTY(sc) while((sc)->STATUS & SC_STATUS_TXACT_Msk)

/**
  * @brief Check specified smartcard port transmit FIFO is full or not
  * @param[in] sc The base address of smartcard module
  * @return Transmit FIFO full status
  * @retval 0 Transmit FIFO is not full
  * @retval 1 Transmit FIFO is full
  * \hideinitializer
  */
#define SCUART_IS_TX_FULL(sc) ((sc)->STATUS & SC_STATUS_TXFULL_Msk ? 1 : 0)

/**
  * @brief Check specified smartcard port transmission is over
  * @param[in] sc The base address of smartcard module
  * @return Transmit complete status
  * @retval 0 Transmit is not complete
  * @retval 1 Transmit complete
  * \hideinitializer
  */
#define SCUART_IS_TX_EMPTY(sc) ((sc)->STATUS & SC_STATUS_TXACT_Msk ? 0 : 1)

/**
  * @brief      Check specified Smartcard port Transmission Status
  * @param[in]  sc      The pointer of smartcard module.
  * @retval     0       Transmit is completed
  * @retval     1       Transmit is active
  * @details    TXACT (SC_STATUS[31]) is set by hardware when Tx transfer is in active and the STOP bit of the last byte has been transmitted.
  * \hideinitializer
  */
#define SCUART_IS_TX_ACTIVE(sc)     (((sc)->STATUS & SC_STATUS_TXACT_Msk)? 1 : 0)

/* RX Macros */

/**
  * @brief Read Rx data register
  * @param[in] sc The base address of smartcard module
  * @return The oldest data byte in RX FIFO
  * \hideinitializer
  */
#define SCUART_READ(sc) ((sc)->DAT)

/**
  * @brief Get RX FIFO empty flag status from register
  * @param[in] sc The base address of smartcard module
  * @return Receive FIFO empty status
  * @retval 0 Receive FIFO is not empty
  * @retval SC_STATUS_RXEMPTY_Msk Receive FIFO is empty
  * \hideinitializer
  */
#define SCUART_GET_RX_EMPTY(sc) ((sc)->STATUS & SC_STATUS_RXEMPTY_Msk)


/**
  * @brief Get RX FIFO full flag status from register
  * @param[in] sc The base address of smartcard module
  * @return Receive FIFO full status
  * @retval 0 Receive FIFO is not full
  * @retval SC_STATUS_RXFULLF_Msk Receive FIFO is full
  * \hideinitializer
  */
#define SCUART_GET_RX_FULL(sc) ((sc)->STATUS & SC_STATUS_RXFULL_Msk)

/**
  * @brief Check if receive data number in FIFO reach FIFO trigger level or not
  * @param[in] sc The base address of smartcard module
  * @return Receive FIFO data status
  * @retval 0 The number of bytes in receive FIFO is less than trigger level
  * @retval 1 The number of bytes in receive FIFO equals or larger than trigger level
  * @note If receive trigger level is \b not 1 byte, this macro return 0 does not necessary indicates there is \b no data in FIFO
  * \hideinitializer
  */
#define SCUART_IS_RX_READY(sc) ((sc)->INTSTS & SC_INTSTS_RDAIF_Msk ? 1 : 0)

/**
  * @brief Check specified smartcard port receive FIFO is full or not
  * @param[in] sc The base address of smartcard module
  * @return Receive FIFO full status
  * @retval 0 Receive FIFO is not full
  * @retval 1 Receive FIFO is full
  * \hideinitializer
  */
#define SCUART_IS_RX_FULL(sc) ((sc)->STATUS & SC_STATUS_RXFULL_Msk ? 1 : 0)

/* Interrupt Macros */

/**
  * @brief Enable specified interrupts
  * @param[in] sc The base address of smartcard module
  * @param[in] u32Mask Interrupt masks to enable, a combination of following bits
  *             - \ref SC_INTEN_RXTOIEN_Msk
  *             - \ref SC_INTEN_TERRIEN_Msk
  *             - \ref SC_INTEN_TBEIEN_Msk
  *             - \ref SC_INTEN_RDAIEN_Msk
  * @return    None
  * \hideinitializer
  */
#define SCUART_ENABLE_INT(sc, u32Mask) ((sc)->INTEN |= (u32Mask))

/**
  * @brief Disable specified interrupts
  * @param[in] sc The base address of smartcard module
  * @param[in] u32Mask Interrupt masks to disable, a combination of following bits
  *             - \ref SC_INTEN_RXTOIEN_Msk
  *             - \ref SC_INTEN_TERRIEN_Msk
  *             - \ref SC_INTEN_TBEIEN_Msk
  *             - \ref SC_INTEN_RDAIEN_Msk
  * @return    None
  * \hideinitializer
  */
#define SCUART_DISABLE_INT(sc, u32Mask) ((sc)->INTEN &= ~(u32Mask))

/**
  * @brief Get specified interrupt flag/status
  * @param[in] sc The base address of smartcard module
  * @param[in] u32Type Interrupt flag/status to check, could be one of following value
  *             - \ref SC_INTSTS_RXTOIF_Msk
  *             - \ref SC_INTSTS_TERRIF_Msk
  *             - \ref SC_INTSTS_TBEIF_Msk
  *             - \ref SC_INTSTS_RDAIF_Msk
  * @return The status of specified interrupt
  * @retval 0 Specified interrupt does not happened
  * @retval 1 Specified interrupt happened
  * \hideinitializer
  */
#define SCUART_GET_INT_FLAG(sc, u32Type) ((sc)->INTSTS & (u32Type) ? 1 : 0)

/**
  * @brief Clear specified interrupt flag/status
  * @param[in] sc The base address of smartcard module
  * @param[in] u32Type Interrupt flag/status to clear, could be the combination of following values
  *             - \ref SC_INTSTS_RXTOIF_Msk
  *             - \ref SC_INTSTS_TERRIF_Msk
  *             - \ref SC_INTSTS_TBEIF_Msk
  * @return None
  * \hideinitializer
  */
#define SCUART_CLR_INT_FLAG(sc, u32Type) ((sc)->INTSTS = (u32Type))

/**
  * @brief Get receive error flag/status
  * @param[in] sc The base address of smartcard module
  * @return Current receive error status, could one of following errors:
  * @retval SC_STATUS_PEF_Msk Parity error
  * @retval SC_STATUS_FEF_Msk Frame error
  * @retval SC_STATUS_BEF_Msk Break error
  * \hideinitializer
  */
#define SCUART_GET_ERR_FLAG(sc) ((sc)->STATUS & (SC_STATUS_PEF_Msk | SC_STATUS_FEF_Msk | SC_STATUS_BEF_Msk))

/**
  * @brief Clear specified receive error flag/status
  * @param[in] sc The base address of smartcard module
  * @param[in] u32Mask Receive error flag/status to clear, combination following values
  *             - \ref SC_STATUS_PEF_Msk
  *             - \ref SC_STATUS_FEF_Msk
  *             - \ref SC_STATUS_BEF_Msk
  * @return None
  * \hideinitializer
  */
#define SCUART_CLR_ERR_FLAG(sc, u32Mask) ((sc)->STATUS = (u32Mask))

void SCUART_Close(SC_T *sc);
uint32_t SCUART_Open(SC_T *sc, uint32_t u32baudrate);
uint32_t SCUART_Read(SC_T *sc, uint8_t pu8RxBuf[], uint32_t u32ReadBytes);
uint32_t SCUART_SetLineConfig(SC_T *sc, uint32_t u32Baudrate, uint32_t u32DataWidth, uint32_t u32Parity, uint32_t  u32StopBits);
void SCUART_SetTimeoutCnt(SC_T *sc, uint32_t u32TOC);
void SCUART_Write(SC_T *sc, uint8_t pu8TxBuf[], uint32_t u32WriteBytes);

/*@}*/ /* end of group SCUART_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group SCUART_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif /* __NU_SCUART_H__ */

