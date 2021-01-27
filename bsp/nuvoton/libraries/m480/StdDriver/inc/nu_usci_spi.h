/****************************************************************************//**
 * @file     nu_usci_spi.h
 * @version  V3.00
 * @brief    M480 series USCI_SPI driver header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2016-2020 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#ifndef __NU_USCI_SPI_H__
#define __NU_USCI_SPI_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup USCI_SPI_Driver USCI_SPI Driver
  @{
*/

/** @addtogroup USCI_SPI_EXPORTED_CONSTANTS USCI_SPI Exported Constants
  @{
*/

#define USPI_MODE_0        (0x0 << USPI_PROTCTL_SCLKMODE_Pos)        /*!< SCLK idle low; data transmit with falling edge and receive with rising edge \hideinitializer */
#define USPI_MODE_1        (0x1 << USPI_PROTCTL_SCLKMODE_Pos)        /*!< SCLK idle low; data transmit with rising edge and receive with falling edge \hideinitializer */
#define USPI_MODE_2        (0x2 << USPI_PROTCTL_SCLKMODE_Pos)        /*!< SCLK idle high; data transmit with rising edge and receive with falling edge \hideinitializer */
#define USPI_MODE_3        (0x3 << USPI_PROTCTL_SCLKMODE_Pos)        /*!< SCLK idle high; data transmit with falling edge and receive with rising edge \hideinitializer */

#define USPI_SLAVE         (USPI_PROTCTL_SLAVE_Msk)                  /*!< Set as slave \hideinitializer */
#define USPI_MASTER        (0x0ul)                                     /*!< Set as master \hideinitializer */

#define USPI_SS                (USPI_PROTCTL_SS_Msk)                 /*!< Set SS \hideinitializer */
#define USPI_SS_ACTIVE_HIGH    (0x0ul)                                 /*!< SS active high \hideinitializer */
#define USPI_SS_ACTIVE_LOW     (USPI_LINECTL_CTLOINV_Msk)            /*!< SS active low \hideinitializer */

/* USCI_SPI Interrupt Mask */
#define USPI_SSINACT_INT_MASK        (0x001ul)                         /*!< Slave Slave Inactive interrupt mask \hideinitializer */
#define USPI_SSACT_INT_MASK          (0x002ul)                         /*!< Slave Slave Active interrupt mask \hideinitializer */
#define USPI_SLVTO_INT_MASK          (0x004ul)                         /*!< Slave Mode Time-out interrupt mask \hideinitializer */
#define USPI_SLVBE_INT_MASK          (0x008ul)                         /*!< Slave Mode Bit Count Error interrupt mask \hideinitializer */
#define USPI_TXUDR_INT_MASK          (0x010ul)                         /*!< Slave Transmit Under Run interrupt mask \hideinitializer */
#define USPI_RXOV_INT_MASK           (0x020ul)                         /*!< Receive Buffer Overrun interrupt mask \hideinitializer */
#define USPI_TXST_INT_MASK           (0x040ul)                         /*!< Transmit Start interrupt mask \hideinitializer */
#define USPI_TXEND_INT_MASK          (0x080ul)                         /*!< Transmit End interrupt mask \hideinitializer */
#define USPI_RXST_INT_MASK           (0x100ul)                         /*!< Receive Start interrupt mask \hideinitializer */
#define USPI_RXEND_INT_MASK          (0x200ul)                         /*!< Receive End interrupt mask \hideinitializer */

/* USCI_SPI Status Mask */
#define USPI_BUSY_MASK               (0x01ul)                          /*!< Busy status mask \hideinitializer */
#define USPI_RX_EMPTY_MASK           (0x02ul)                          /*!< RX empty status mask \hideinitializer */
#define USPI_RX_FULL_MASK            (0x04ul)                          /*!< RX full status mask \hideinitializer */
#define USPI_TX_EMPTY_MASK           (0x08ul)                          /*!< TX empty status mask \hideinitializer */
#define USPI_TX_FULL_MASK            (0x10ul)                          /*!< TX full status mask \hideinitializer */
#define USPI_SSLINE_STS_MASK         (0x20ul)                          /*!< USCI_SPI_SS line status mask \hideinitializer */

/*@}*/ /* end of group USCI_SPI_EXPORTED_CONSTANTS */


/** @addtogroup USCI_SPI_EXPORTED_FUNCTIONS USCI_SPI Exported Functions
  @{
*/

/**
  * @brief  Disable slave 3-wire mode.
  * @param[in]  uspi The pointer of the specified USCI_SPI module.
  * @return None
  * \hideinitializer
  */
#define USPI_DISABLE_3WIRE_MODE(uspi) ( (uspi)->PROTCTL &= ~USPI_PROTCTL_SLV3WIRE_Msk )

/**
  * @brief  Enable slave 3-wire mode.
  * @param[in]  uspi The pointer of the specified USCI_SPI module.
  * @return None
  * \hideinitializer
  */
#define USPI_ENABLE_3WIRE_MODE(uspi) ( (uspi)->PROTCTL |= USPI_PROTCTL_SLV3WIRE_Msk )

/**
  * @brief  Get the Rx buffer empty flag.
  * @param[in]  uspi The pointer of the specified USCI_SPI module.
  * @return Rx buffer flag
  * @retval 0: Rx buffer is not empty
  * @retval 1: Rx buffer is empty
  * \hideinitializer
  */
#define USPI_GET_RX_EMPTY_FLAG(uspi) ( ((uspi)->BUFSTS & USPI_BUFSTS_RXEMPTY_Msk) == USPI_BUFSTS_RXEMPTY_Msk ? 1:0 )

/**
  * @brief  Get the Tx buffer empty flag.
  * @param[in]  uspi The pointer of the specified USCI_SPI module.
  * @return Tx buffer flag
  * @retval 0: Tx buffer is not empty
  * @retval 1: Tx buffer is empty
  * \hideinitializer
  */
#define USPI_GET_TX_EMPTY_FLAG(uspi) ( ((uspi)->BUFSTS & USPI_BUFSTS_TXEMPTY_Msk) == USPI_BUFSTS_TXEMPTY_Msk ? 1:0 )

/**
  * @brief  Get the Tx buffer full flag.
  * @param[in]  uspi The pointer of the specified USCI_SPI module.
  * @return Tx buffer flag
  * @retval 0: Tx buffer is not full
  * @retval 1: Tx buffer is full
  * \hideinitializer
  */
#define USPI_GET_TX_FULL_FLAG(uspi) ( ((uspi)->BUFSTS & USPI_BUFSTS_TXFULL_Msk) == USPI_BUFSTS_TXFULL_Msk ? 1:0 )

/**
  * @brief  Get the datum read from RX register.
  * @param[in]  uspi The pointer of the specified USCI_SPI module.
  * @return data in Rx register
  * \hideinitializer
  */
#define USPI_READ_RX(uspi) ((uspi)->RXDAT)

/**
  * @brief  Write datum to TX register.
  * @param[in]  uspi The pointer of the specified USCI_SPI module.
  * @param[in]  u32TxData The datum which user attempt to transfer through USCI_SPI bus.
  * @return None
  * \hideinitializer
  */
#define USPI_WRITE_TX(uspi, u32TxData) ( (uspi)->TXDAT = (u32TxData) )

/**
  * @brief      Set USCI_SPI_SS pin to high state.
  * @param[in]  uspi The pointer of the specified USCI_SPI module.
  * @return     None.
  * @details    Disable automatic slave selection function and set USCI_SPI_SS pin to high state. Only available in Master mode.
  * \hideinitializer
  */
#define USPI_SET_SS_HIGH(uspi) \
    do{ \
        (uspi)->LINECTL &= ~(USPI_LINECTL_CTLOINV_Msk); \
        (uspi)->PROTCTL = ((uspi)->PROTCTL & ~(USPI_PROTCTL_AUTOSS_Msk | USPI_PROTCTL_SS_Msk)); \
    }while(0)

/**
  * @brief      Set USCI_SPI_SS pin to low state.
  * @param[in]  uspi The pointer of the specified USCI_SPI module.
  * @return     None.
  * @details    Disable automatic slave selection function and set USCI_SPI_SS pin to low state. Only available in Master mode.
  * \hideinitializer
  */
#define USPI_SET_SS_LOW(uspi) \
    do{ \
        (uspi)->LINECTL |= (USPI_LINECTL_CTLOINV_Msk); \
        (uspi)->PROTCTL = (((uspi)->PROTCTL & ~USPI_PROTCTL_AUTOSS_Msk) | USPI_PROTCTL_SS_Msk); \
    }while(0)

/**
  * @brief  Set the length of suspend interval.
  * @param[in]  uspi The pointer of the specified USCI_SPI module.
  * @param[in]  u32SuspCycle Decide the length of suspend interval.
  * @return None
  * \hideinitializer
  */
#define USPI_SET_SUSPEND_CYCLE(uspi, u32SuspCycle) ( (uspi)->PROTCTL = ((uspi)->PROTCTL & ~USPI_PROTCTL_SUSPITV_Msk) | ((u32SuspCycle) << USPI_PROTCTL_SUSPITV_Pos) )

/**
  * @brief  Set the USCI_SPI transfer sequence with LSB first.
  * @param[in]  uspi The pointer of the specified USCI_SPI module.
  * @return None
  * \hideinitializer
  */
#define USPI_SET_LSB_FIRST(uspi) ( (uspi)->LINECTL |= USPI_LINECTL_LSB_Msk )

/**
  * @brief  Set the USCI_SPI transfer sequence with MSB first.
  * @param[in]  uspi The pointer of the specified USCI_SPI module.
  * @return None
  * \hideinitializer
  */
#define USPI_SET_MSB_FIRST(uspi) ( (uspi)->LINECTL &= ~USPI_LINECTL_LSB_Msk )

/**
  * @brief  Set the data width of a USCI_SPI transaction.
  * @param[in]  uspi The pointer of the specified USCI_SPI module.
  * @param[in]  u32Width The data width
  * @return None
  * \hideinitializer
  */
#define USPI_SET_DATA_WIDTH(uspi,u32Width) \
    do{ \
      if((u32Width) == 16ul){ \
        (uspi)->LINECTL = ((uspi)->LINECTL & ~USPI_LINECTL_DWIDTH_Msk) | (0 << USPI_LINECTL_DWIDTH_Pos); \
      }else { \
        (uspi)->LINECTL = ((uspi)->LINECTL & ~USPI_LINECTL_DWIDTH_Msk) | ((u32Width) << USPI_LINECTL_DWIDTH_Pos); \
      } \
    }while(0)

/**
  * @brief  Get the USCI_SPI busy state.
  * @param[in]  uspi The pointer of the specified USCI_SPI module.
  * @return USCI_SPI busy status
  * @retval 0: USCI_SPI module is not busy
  * @retval 1: USCI_SPI module is busy
  * \hideinitializer
  */
#define USPI_IS_BUSY(uspi) ( ((uspi)->PROTSTS & USPI_PROTSTS_BUSY_Msk) == USPI_PROTSTS_BUSY_Msk ? 1:0 )

/**
  * @brief Get the USCI_SPI wakeup flag.
  * @param[in] uspi The pointer of the specified USCI_SPI module.
  * @return Wakeup status.
  * @retval 0 Flag is not set.
  * @retval 1 Flag is set.
  * \hideinitializer
  */
#define USPI_GET_WAKEUP_FLAG(uspi) ( ((uspi)->WKSTS & USPI_WKSTS_WKF_Msk) == USPI_WKSTS_WKF_Msk ? 1:0)

/**
  * @brief Clear the USCI_SPI wakeup flag.
  * @param[in] uspi The pointer of the specified USCI_SPI module.
  * @return None
  * \hideinitializer
  */
#define USPI_CLR_WAKEUP_FLAG(uspi)  ( (uspi)->WKSTS |= USPI_WKSTS_WKF_Msk)

/**
  * @brief Get protocol interrupt flag/status.
  * @param[in] uspi The pointer of the specified USCI_SPI module.
  * @return The interrupt flag/status of protocol status register.
  * \hideinitializer
  */
#define USPI_GET_PROT_STATUS(uspi)    ( (uspi)->PROTSTS)

/**
  * @brief Clear specified protocol interrupt flag.
  * @param[in] uspi The pointer of the specified USCI_SPI module.
  * @param[in] u32IntTypeFlag Interrupt Type Flag, should be
  *                                  - \ref USPI_PROTSTS_SSACTIF_Msk
  *                                  - \ref USPI_PROTSTS_SSINAIF_Msk
  *                                  - \ref USPI_PROTSTS_SLVBEIF_Msk
  *                                  - \ref USPI_PROTSTS_SLVTOIF_Msk
  *                                  - \ref USPI_PROTSTS_RXENDIF_Msk
  *                                  - \ref USPI_PROTSTS_RXSTIF_Msk
  *                                  - \ref USPI_PROTSTS_TXENDIF_Msk
  *                                  - \ref USPI_PROTSTS_TXSTIF_Msk
  * @return None
  * \hideinitializer
  */
#define USPI_CLR_PROT_INT_FLAG(uspi,u32IntTypeFlag)    ( (uspi)->PROTSTS = (u32IntTypeFlag))

/**
  * @brief Get buffer interrupt flag/status.
  * @param[in] uspi The pointer of the specified USCI_SPI module.
  * @return The interrupt flag/status of buffer status register.
  * \hideinitializer
  */
#define USPI_GET_BUF_STATUS(uspi)    ( (uspi)->BUFSTS)

/**
  * @brief Clear specified buffer interrupt flag.
  * @param[in] uspi The pointer of the specified USCI_SPI module.
  * @param[in] u32IntTypeFlag Interrupt Type Flag, should be
  *                                  - \ref USPI_BUFSTS_TXUDRIF_Msk
  *                                  - \ref USPI_BUFSTS_RXOVIF_Msk
  * @return None
  * \hideinitializer
  */
#define USPI_CLR_BUF_INT_FLAG(uspi,u32IntTypeFlag)    ( (uspi)->BUFSTS = (u32IntTypeFlag))

/**
  * @brief Enable specified protocol interrupt.
  * @param[in] uspi The pointer of the specified USCI_SPI module.
  * @param[in] u32IntSel Interrupt Type, should be
  *                                  - \ref USPI_PROTIEN_SLVBEIEN_Msk
  *                                  - \ref USPI_PROTIEN_SLVTOIEN_Msk
  *                                  - \ref USPI_PROTIEN_SSACTIEN_Msk
  *                                  - \ref USPI_PROTIEN_SSINAIEN_Msk
  * @return None
  * \hideinitializer
  */
#define USPI_ENABLE_PROT_INT(uspi, u32IntSel)    ((uspi)->PROTIEN |= (u32IntSel))

/**
  * @brief Disable specified protocol interrupt.
  * @param[in] uspi The pointer of the specified USCI_SPI module.
  * @param[in] u32IntSel Interrupt Type, should be
  *                                  - \ref USPI_PROTIEN_SLVBEIEN_Msk
  *                                  - \ref USPI_PROTIEN_SLVTOIEN_Msk
  *                                  - \ref USPI_PROTIEN_SSACTIEN_Msk
  *                                  - \ref USPI_PROTIEN_SSINAIEN_Msk
  * @return None
  * \hideinitializer
  */
#define USPI_DISABLE_PROT_INT(uspi, u32IntSel)    ((uspi)->PROTIEN &= ~ (u32IntSel))

/**
  * @brief Enable specified buffer interrupt.
  * @param[in] uspi The pointer of the specified USCI_SPI module.
  * @param[in] u32IntSel Interrupt Type, should be
  *                                  - \ref USPI_BUFCTL_RXOVIEN_Msk
  *                                  - \ref USPI_BUFCTL_TXUDRIEN_Msk
  * @return None
  * \hideinitializer
  */
#define USPI_ENABLE_BUF_INT(uspi, u32IntSel)    ((uspi)->BUFCTL |= (u32IntSel))

/**
  * @brief Disable specified buffer interrupt.
  * @param[in] uspi The pointer of the specified USCI_SPI module.
  * @param[in] u32IntSel Interrupt Type, should be
  *                                  - \ref USPI_BUFCTL_RXOVIEN_Msk
  *                                  - \ref USPI_BUFCTL_TXUDRIEN_Msk
  * @return None
  * \hideinitializer
  */
#define USPI_DISABLE_BUF_INT(uspi, u32IntSel)    ((uspi)->BUFCTL &= ~ (u32IntSel))

/**
  * @brief Enable specified transfer interrupt.
  * @param[in] uspi The pointer of the specified USCI_SPI module.
  * @param[in] u32IntSel Interrupt Type, should be
  *                                  - \ref USPI_INTEN_RXENDIEN_Msk
  *                                  - \ref USPI_INTEN_RXSTIEN_Msk
  *                                  - \ref USPI_INTEN_TXENDIEN_Msk
  *                                  - \ref USPI_INTEN_TXSTIEN_Msk
  * @return None
  * \hideinitializer
  */
#define USPI_ENABLE_TRANS_INT(uspi, u32IntSel)    ((uspi)->INTEN |= (u32IntSel))

/**
  * @brief Disable specified transfer interrupt.
  * @param[in] uspi The pointer of the specified USCI_SPI module.
  * @param[in] u32IntSel Interrupt Type, should be
  *                                  - \ref USPI_INTEN_RXENDIEN_Msk
  *                                  - \ref USPI_INTEN_RXSTIEN_Msk
  *                                  - \ref USPI_INTEN_TXENDIEN_Msk
  *                                  - \ref USPI_INTEN_TXSTIEN_Msk
  * @return None
  * \hideinitializer
  */
#define USPI_DISABLE_TRANS_INT(uspi, u32IntSel)    ((uspi)->INTEN &= ~ (u32IntSel))


/**
  * @brief      Trigger RX PDMA function.
  * @param[in]  uspi The pointer of the specified USCI_SPI module.
  * @return     None.
  * @details    Set RXPDMAEN bit of USPI_PDMACTL register to enable RX PDMA transfer function.
  * \hideinitializer
  */
#define USPI_TRIGGER_RX_PDMA(uspi)   ((uspi)->PDMACTL |= USPI_PDMACTL_RXPDMAEN_Msk|USPI_PDMACTL_PDMAEN_Msk)

/**
  * @brief      Trigger TX PDMA function.
  * @param[in]  uspi The pointer of the specified USCI_SPI module.
  * @return     None.
  * @details    Set TXPDMAEN bit of USPI_PDMACTL register to enable TX PDMA transfer function.
  * \hideinitializer
  */
#define USPI_TRIGGER_TX_PDMA(uspi)   ((uspi)->PDMACTL |= USPI_PDMACTL_TXPDMAEN_Msk|USPI_PDMACTL_PDMAEN_Msk)

/**
  * @brief      Trigger TX and RX PDMA function.
  * @param[in]  uspi The pointer of the specified USCI_SPI module.
  * @return     None.
  * @details    Set TXPDMAEN bit and RXPDMAEN bit of USPI_PDMACTL register to enable TX and RX PDMA transfer function.
  * \hideinitializer
  */
#define USPI_TRIGGER_TX_RX_PDMA(uspi)   ((uspi)->PDMACTL |= USPI_PDMACTL_TXPDMAEN_Msk|USPI_PDMACTL_RXPDMAEN_Msk|USPI_PDMACTL_PDMAEN_Msk)

/**
  * @brief      Disable RX PDMA transfer.
  * @param[in]  uspi The pointer of the specified USCI_SPI module.
  * @return     None.
  * @details    Clear RXPDMAEN bit of USPI_PDMACTL register to disable RX PDMA transfer function.
  * \hideinitializer
  */
#define USPI_DISABLE_RX_PDMA(uspi) ( (uspi)->PDMACTL &= ~USPI_PDMACTL_RXPDMAEN_Msk )

/**
  * @brief      Disable TX PDMA transfer.
  * @param[in]  uspi The pointer of the specified USCI_SPI module.
  * @return     None.
  * @details    Clear TXPDMAEN bit of USPI_PDMACTL register to disable TX PDMA transfer function.
  * \hideinitializer
  */
#define USPI_DISABLE_TX_PDMA(uspi) ( (uspi)->PDMACTL &= ~USPI_PDMACTL_TXPDMAEN_Msk )

/**
  * @brief      Disable TX and RX PDMA transfer.
  * @param[in]  uspi The pointer of the specified USCI_SPI module.
  * @return     None.
  * @details    Clear TXPDMAEN bit and RXPDMAEN bit of USPI_PDMACTL register to disable TX and RX PDMA transfer function.
  * \hideinitializer
  */
#define USPI_DISABLE_TX_RX_PDMA(uspi) ( (uspi)->PDMACTL &= ~(USPI_PDMACTL_TXPDMAEN_Msk | USPI_PDMACTL_RXPDMAEN_Msk))

uint32_t USPI_Open(USPI_T *uspi, uint32_t u32MasterSlave, uint32_t u32SPIMode,  uint32_t u32DataWidth, uint32_t u32BusClock);
void USPI_Close(USPI_T *uspi);
void USPI_ClearRxBuf(USPI_T *uspi);
void USPI_ClearTxBuf(USPI_T *uspi);
void USPI_DisableAutoSS(USPI_T *uspi);
void USPI_EnableAutoSS(USPI_T *uspi, uint32_t u32SSPinMask, uint32_t u32ActiveLevel);
uint32_t USPI_SetBusClock(USPI_T *uspi, uint32_t u32BusClock);
uint32_t USPI_GetBusClock(USPI_T *uspi);
void USPI_EnableInt(USPI_T *uspi, uint32_t u32Mask);
void USPI_DisableInt(USPI_T *uspi, uint32_t u32Mask);
uint32_t USPI_GetIntFlag(USPI_T *uspi, uint32_t u32Mask);
void USPI_ClearIntFlag(USPI_T *uspi, uint32_t u32Mask);
uint32_t USPI_GetStatus(USPI_T *uspi, uint32_t u32Mask);
void USPI_EnableWakeup(USPI_T *uspi);
void USPI_DisableWakeup(USPI_T *uspi);


/*@}*/ /* end of group USCI_SPI_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group USCI_SPI_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif /* __NU_USCI_SPI_H__ */

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
