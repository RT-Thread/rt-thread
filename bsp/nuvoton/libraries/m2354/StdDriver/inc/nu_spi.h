/******************************************************************************
 * @file     nu_spi.h
 * @version  V3.00
 * @brief    M2354 series SPI driver header file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __NU_SPI_H__
#define __NU_SPI_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup SPI_Driver SPI Driver
  @{
*/

/** @addtogroup SPI_EXPORTED_CONSTANTS SPI Exported Constants
  @{
*/

#define SPI_MODE_0        (SPI_CTL_TXNEG_Msk)                             /*!< CLKPOL=0; RXNEG=0; TXNEG=1 */
#define SPI_MODE_1        (SPI_CTL_RXNEG_Msk)                             /*!< CLKPOL=0; RXNEG=1; TXNEG=0 */
#define SPI_MODE_2        (SPI_CTL_CLKPOL_Msk | SPI_CTL_RXNEG_Msk)        /*!< CLKPOL=1; RXNEG=1; TXNEG=0 */
#define SPI_MODE_3        (SPI_CTL_CLKPOL_Msk | SPI_CTL_TXNEG_Msk)        /*!< CLKPOL=1; RXNEG=0; TXNEG=1 */

#define SPI_SLAVE         (SPI_CTL_SLAVE_Msk)                             /*!< Set as slave */
#define SPI_MASTER        (0x0UL)                                         /*!< Set as master */

#define SPI_SS                (SPI_SSCTL_SS_Msk)                          /*!< Set SS */
#define SPI_SS_ACTIVE_HIGH    (SPI_SSCTL_SSACTPOL_Msk)                    /*!< SS active high */
#define SPI_SS_ACTIVE_LOW     (0x0UL)                                     /*!< SS active low */

/* SPI Interrupt Mask */
#define SPI_UNIT_INT_MASK                (0x001UL)                        /*!< Unit transfer interrupt mask */
#define SPI_SSACT_INT_MASK               (0x002UL)                        /*!< Slave selection signal active interrupt mask */
#define SPI_SSINACT_INT_MASK             (0x004UL)                        /*!< Slave selection signal inactive interrupt mask */
#define SPI_SLVUR_INT_MASK               (0x008UL)                        /*!< Slave under run interrupt mask */
#define SPI_SLVBE_INT_MASK               (0x010UL)                        /*!< Slave bit count error interrupt mask */
#define SPI_TXUF_INT_MASK                (0x040UL)                        /*!< Slave TX underflow interrupt mask */
#define SPI_FIFO_TXTH_INT_MASK           (0x080UL)                        /*!< FIFO TX threshold interrupt mask */
#define SPI_FIFO_RXTH_INT_MASK           (0x100UL)                        /*!< FIFO RX threshold interrupt mask */
#define SPI_FIFO_RXOV_INT_MASK           (0x200UL)                        /*!< FIFO RX overrun interrupt mask */
#define SPI_FIFO_RXTO_INT_MASK           (0x400UL)                        /*!< FIFO RX time-out interrupt mask */

/* SPI Status Mask */
#define SPI_BUSY_MASK                    (0x01UL)                         /*!< Busy status mask */
#define SPI_RX_EMPTY_MASK                (0x02UL)                         /*!< RX empty status mask */
#define SPI_RX_FULL_MASK                 (0x04UL)                         /*!< RX full status mask */
#define SPI_TX_EMPTY_MASK                (0x08UL)                         /*!< TX empty status mask */
#define SPI_TX_FULL_MASK                 (0x10UL)                         /*!< TX full status mask */
#define SPI_TXRX_RESET_MASK              (0x20UL)                         /*!< TX or RX reset status mask */
#define SPI_SPIEN_STS_MASK               (0x40UL)                         /*!< SPIEN status mask */
#define SPI_SSLINE_STS_MASK              (0x80UL)                         /*!< SPIx_SS line status mask */

/* SPI Status2 Mask */
#define SPI_SLVBENUM_MASK                (0x01UL)                         /*!< Effective bit number of uncompleted RX data status mask */


/* I2S Data Width */
#define SPII2S_DATABIT_8           (0UL << SPI_I2SCTL_WDWIDTH_Pos)        /*!< I2S data width is 8-bit */
#define SPII2S_DATABIT_16          (1UL << SPI_I2SCTL_WDWIDTH_Pos)        /*!< I2S data width is 16-bit */
#define SPII2S_DATABIT_24          (2UL << SPI_I2SCTL_WDWIDTH_Pos)        /*!< I2S data width is 24-bit */
#define SPII2S_DATABIT_32          (3UL << SPI_I2SCTL_WDWIDTH_Pos)        /*!< I2S data width is 32-bit */

/* I2S Audio Format */
#define SPII2S_MONO                SPI_I2SCTL_MONO_Msk                    /*!< Monaural channel */
#define SPII2S_STEREO              (0UL)                                  /*!< Stereo channel */

/* I2S Data Format */
#define SPII2S_FORMAT_I2S          (0UL << SPI_I2SCTL_FORMAT_Pos)         /*!< I2S data format */
#define SPII2S_FORMAT_MSB          (1UL << SPI_I2SCTL_FORMAT_Pos)         /*!< MSB justified data format */
#define SPII2S_FORMAT_PCMA         (2UL << SPI_I2SCTL_FORMAT_Pos)         /*!< PCM mode A data format */
#define SPII2S_FORMAT_PCMB         (3UL << SPI_I2SCTL_FORMAT_Pos)         /*!< PCM mode B data format */

/* I2S Operation mode */
#define SPII2S_MODE_SLAVE          SPI_I2SCTL_SLAVE_Msk                   /*!< As slave mode */
#define SPII2S_MODE_MASTER         (0UL)                                  /*!< As master mode */

/* I2S TX FIFO Threshold */
#define SPII2S_FIFO_TX_LEVEL_WORD_0    (0UL)                              /*!< TX threshold is 0 word */
#define SPII2S_FIFO_TX_LEVEL_WORD_1    (1UL << SPI_FIFOCTL_TXTH_Pos)      /*!< TX threshold is 1 word */
#define SPII2S_FIFO_TX_LEVEL_WORD_2    (2UL << SPI_FIFOCTL_TXTH_Pos)      /*!< TX threshold is 2 words */
#define SPII2S_FIFO_TX_LEVEL_WORD_3    (3UL << SPI_FIFOCTL_TXTH_Pos)      /*!< TX threshold is 3 words */
/* I2S RX FIFO Threshold */
#define SPII2S_FIFO_RX_LEVEL_WORD_1    (0UL)                              /*!< RX threshold is 1 word */
#define SPII2S_FIFO_RX_LEVEL_WORD_2    (1UL << SPI_FIFOCTL_RXTH_Pos)      /*!< RX threshold is 2 words */
#define SPII2S_FIFO_RX_LEVEL_WORD_3    (2UL << SPI_FIFOCTL_RXTH_Pos)      /*!< RX threshold is 3 words */
#define SPII2S_FIFO_RX_LEVEL_WORD_4    (3UL << SPI_FIFOCTL_RXTH_Pos)      /*!< RX threshold is 4 words */

/* I2S Record Channel */
#define SPII2S_MONO_RIGHT          (0UL)                                  /*!< Record mono right channel */
#define SPII2S_MONO_LEFT           SPI_I2SCTL_RXLCH_Msk                   /*!< Record mono left channel */

/* I2S Channel */
#define SPII2S_RIGHT               (0UL)                                  /*!< Select right channel */
#define SPII2S_LEFT                (1UL)                                  /*!< Select left channel */

/* I2S Interrupt Mask */
#define SPII2S_FIFO_TXTH_INT_MASK           (0x01UL)                      /*!< TX FIFO threshold interrupt mask */
#define SPII2S_FIFO_RXTH_INT_MASK           (0x02UL)                      /*!< RX FIFO threshold interrupt mask */
#define SPII2S_FIFO_RXOV_INT_MASK           (0x04UL)                      /*!< RX FIFO overrun interrupt mask */
#define SPII2S_FIFO_RXTO_INT_MASK           (0x08UL)                      /*!< RX FIFO time-out interrupt mask */
#define SPII2S_TXUF_INT_MASK                (0x10UL)                      /*!< TX FIFO underflow interrupt mask */
#define SPII2S_RIGHT_ZC_INT_MASK            (0x20UL)                      /*!< Right channel zero cross interrupt mask */
#define SPII2S_LEFT_ZC_INT_MASK             (0x40UL)                      /*!< Left channel zero cross interrupt mask */
#define SPII2S_SLAVE_ERR_INT_MASK           (0x80UL)                      /*!< Bit clock loss interrupt mask */

/**@}*/ /* end of group SPI_EXPORTED_CONSTANTS */


/** @addtogroup SPI_EXPORTED_FUNCTIONS SPI Exported Functions
  @{
*/

/**
  * @brief      Clear the unit transfer interrupt flag.
  * @param[in]  spi The pointer of the specified SPI module.
  * @return     None.
  * @details    Write 1 to UNITIF bit of SPI_STATUS register to clear the unit transfer interrupt flag.
  */
#define SPI_CLR_UNIT_TRANS_INT_FLAG(spi)   ( (spi)->STATUS = SPI_STATUS_UNITIF_Msk )

/**
  * @brief      Disable Slave 3-wire mode.
  * @param[in]  spi The pointer of the specified SPI module.
  * @return     None.
  * @details    Clear SLV3WIRE bit of SPI_SSCTL register to disable Slave 3-wire mode.
  */
#define SPI_DISABLE_3WIRE_MODE(spi)   ( (spi)->SSCTL &= ~SPI_SSCTL_SLV3WIRE_Msk )

/**
  * @brief      Enable Slave 3-wire mode.
  * @param[in]  spi The pointer of the specified SPI module.
  * @return     None.
  * @details    Set SLV3WIRE bit of SPI_SSCTL register to enable Slave 3-wire mode.
  */
#define SPI_ENABLE_3WIRE_MODE(spi)   ( (spi)->SSCTL |= SPI_SSCTL_SLV3WIRE_Msk )

/**
  * @brief      Trigger RX PDMA function.
  * @param[in]  spi The pointer of the specified SPI module.
  * @return     None.
  * @details    Set RXPDMAEN bit of SPI_PDMACTL register to enable RX PDMA transfer function.
  */
#define SPI_TRIGGER_RX_PDMA(spi)   ( (spi)->PDMACTL |= SPI_PDMACTL_RXPDMAEN_Msk )

/**
  * @brief      Trigger TX PDMA function.
  * @param[in]  spi The pointer of the specified SPI module.
  * @return     None.
  * @details    Set TXPDMAEN bit of SPI_PDMACTL register to enable TX PDMA transfer function.
  */
#define SPI_TRIGGER_TX_PDMA(spi)   ( (spi)->PDMACTL |= SPI_PDMACTL_TXPDMAEN_Msk )

/**
  * @brief      Trigger TX and RX PDMA function.
  * @param[in]  spi The pointer of the specified SPI module.
  * @return     None.
  * @details    Set TXPDMAEN bit and RXPDMAEN bit of SPI_PDMACTL register to enable TX and RX PDMA transfer function.
  */
#define SPI_TRIGGER_TX_RX_PDMA(spi)   ( (spi)->PDMACTL |= (SPI_PDMACTL_TXPDMAEN_Msk | SPI_PDMACTL_RXPDMAEN_Msk) )

/**
  * @brief      Disable RX PDMA transfer.
  * @param[in]  spi The pointer of the specified SPI module.
  * @return     None.
  * @details    Clear RXPDMAEN bit of SPI_PDMACTL register to disable RX PDMA transfer function.
  */
#define SPI_DISABLE_RX_PDMA(spi) ( (spi)->PDMACTL &= ~SPI_PDMACTL_RXPDMAEN_Msk )

/**
  * @brief      Disable TX PDMA transfer.
  * @param[in]  spi The pointer of the specified SPI module.
  * @return     None.
  * @details    Clear TXPDMAEN bit of SPI_PDMACTL register to disable TX PDMA transfer function.
  */
#define SPI_DISABLE_TX_PDMA(spi) ( (spi)->PDMACTL &= ~SPI_PDMACTL_TXPDMAEN_Msk )

/**
  * @brief      Disable TX and RX PDMA transfer.
  * @param[in]  spi The pointer of the specified SPI module.
  * @return     None.
  * @details    Clear TXPDMAEN bit and RXPDMAEN bit of SPI_PDMACTL register to disable TX and RX PDMA transfer function.
  */
#define SPI_DISABLE_TX_RX_PDMA(spi)   ( (spi)->PDMACTL &= ~(SPI_PDMACTL_TXPDMAEN_Msk | SPI_PDMACTL_RXPDMAEN_Msk) )

/**
  * @brief      Get the count of available data in RX FIFO.
  * @param[in]  spi The pointer of the specified SPI module.
  * @return     The count of available data in RX FIFO.
  * @details    Read RXCNT (SPI_STATUS[27:24]) to get the count of available data in RX FIFO.
  */
#define SPI_GET_RX_FIFO_COUNT(spi)   ( ((spi)->STATUS & SPI_STATUS_RXCNT_Msk) >> SPI_STATUS_RXCNT_Pos )

/**
  * @brief      Get the RX FIFO empty flag.
  * @param[in]  spi The pointer of the specified SPI module.
  * @retval     0 RX FIFO is not empty.
  * @retval     1 RX FIFO is empty.
  * @details    Read RXEMPTY bit of SPI_STATUS register to get the RX FIFO empty flag.
  */
#define SPI_GET_RX_FIFO_EMPTY_FLAG(spi)   ( ((spi)->STATUS & SPI_STATUS_RXEMPTY_Msk) >> SPI_STATUS_RXEMPTY_Pos )

/**
  * @brief      Get the TX FIFO empty flag.
  * @param[in]  spi The pointer of the specified SPI module.
  * @retval     0 TX FIFO is not empty.
  * @retval     1 TX FIFO is empty.
  * @details    Read TXEMPTY bit of SPI_STATUS register to get the TX FIFO empty flag.
  */
#define SPI_GET_TX_FIFO_EMPTY_FLAG(spi)   ( ((spi)->STATUS & SPI_STATUS_TXEMPTY_Msk) >> SPI_STATUS_TXEMPTY_Pos )

/**
  * @brief      Get the TX FIFO full flag.
  * @param[in]  spi The pointer of the specified SPI module.
  * @retval     0 TX FIFO is not full.
  * @retval     1 TX FIFO is full.
  * @details    Read TXFULL bit of SPI_STATUS register to get the TX FIFO full flag.
  */
#define SPI_GET_TX_FIFO_FULL_FLAG(spi)   ( ((spi)->STATUS & SPI_STATUS_TXFULL_Msk) >> SPI_STATUS_TXFULL_Pos )

/**
  * @brief      Get the datum read from RX register.
  * @param[in]  spi The pointer of the specified SPI module.
  * @return     Data in RX register.
  * @details    Read SPI_RX register to get the received datum.
  */
#define SPI_READ_RX(spi)   ( (spi)->RX )

/**
  * @brief      Write datum to TX register.
  * @param[in]  spi The pointer of the specified SPI module.
  * @param[in]  u32TxData The datum which user attempt to transfer through SPI bus.
  * @return     None.
  * @details    Write u32TxData to SPI_TX register.
  */
#define SPI_WRITE_TX(spi, u32TxData)   ( (spi)->TX = (u32TxData) )

/**
  * @brief      Set SPIx_SS pin to high state.
  * @param[in]  spi The pointer of the specified SPI module.
  * @return     None.
  * @details    Disable automatic slave selection function and set SPIx_SS pin to high state.
  */
#define SPI_SET_SS_HIGH(spi)   ( (spi)->SSCTL = ((spi)->SSCTL & (~SPI_SSCTL_AUTOSS_Msk)) | (SPI_SSCTL_SSACTPOL_Msk | SPI_SSCTL_SS_Msk) )

/**
  * @brief      Set SPIx_SS pin to low state.
  * @param[in]  spi The pointer of the specified SPI module.
  * @return     None.
  * @details    Disable automatic slave selection function and set SPIx_SS pin to low state.
  */
#define SPI_SET_SS_LOW(spi)   ( (spi)->SSCTL = ((spi)->SSCTL & (~(SPI_SSCTL_AUTOSS_Msk | SPI_SSCTL_SSACTPOL_Msk))) | SPI_SSCTL_SS_Msk )

/**
  * @brief      Enable Byte Reorder function.
  * @param[in]  spi The pointer of the specified SPI module.
  * @return     None.
  * @details    Enable Byte Reorder function. The suspend interval depends on the setting of SUSPITV (SPI_CTL[7:4]).
  */
#define SPI_ENABLE_BYTE_REORDER(spi)   ( (spi)->CTL |=  SPI_CTL_REORDER_Msk )

/**
  * @brief      Disable Byte Reorder function.
  * @param[in]  spi The pointer of the specified SPI module.
  * @return     None.
  * @details    Clear REORDER bit field of SPI_CTL register to disable Byte Reorder function.
  */
#define SPI_DISABLE_BYTE_REORDER(spi)   ( (spi)->CTL &= ~SPI_CTL_REORDER_Msk )

/**
  * @brief      Set the length of suspend interval.
  * @param[in]  spi The pointer of the specified SPI module.
  * @param[in]  u32SuspCycle Decides the length of suspend interval. It could be 0 ~ 15.
  * @return     None.
  * @details    Set the length of suspend interval according to u32SuspCycle.
  *             The length of suspend interval is ((u32SuspCycle + 0.5) * the length of one SPI bus clock cycle).
  */
#define SPI_SET_SUSPEND_CYCLE(spi, u32SuspCycle)   ( (spi)->CTL = ((spi)->CTL & ~SPI_CTL_SUSPITV_Msk) | ((u32SuspCycle) << SPI_CTL_SUSPITV_Pos) )

/**
  * @brief      Set the SPI transfer sequence with LSB first.
  * @param[in]  spi The pointer of the specified SPI module.
  * @return     None.
  * @details    Set LSB bit of SPI_CTL register to set the SPI transfer sequence with LSB first.
  */
#define SPI_SET_LSB_FIRST(spi)   ( (spi)->CTL |= SPI_CTL_LSB_Msk )

/**
  * @brief      Set the SPI transfer sequence with MSB first.
  * @param[in]  spi The pointer of the specified SPI module.
  * @return     None.
  * @details    Clear LSB bit of SPI_CTL register to set the SPI transfer sequence with MSB first.
  */
#define SPI_SET_MSB_FIRST(spi)   ( (spi)->CTL &= ~SPI_CTL_LSB_Msk )

/**
  * @brief      Set the data width of a SPI transaction.
  * @param[in]  spi The pointer of the specified SPI module.
  * @param[in]  u32Width The bit width of one transaction.
  * @return     None.
  * @details    The data width can be 8 ~ 32 bits.
  */
#define SPI_SET_DATA_WIDTH(spi, u32Width)   ( (spi)->CTL = ((spi)->CTL & ~SPI_CTL_DWIDTH_Msk) | (((u32Width) & 0x1F) << SPI_CTL_DWIDTH_Pos) )

/**
  * @brief      Get the SPI busy state.
  * @param[in]  spi The pointer of the specified SPI module.
  * @retval     0 SPI controller is not busy.
  * @retval     1 SPI controller is busy.
  * @details    This macro will return the busy state of SPI controller.
  */
#define SPI_IS_BUSY(spi)   ( ((spi)->STATUS & SPI_STATUS_BUSY_Msk) >> SPI_STATUS_BUSY_Pos )

/**
  * @brief      Enable SPI controller.
  * @param[in]  spi The pointer of the specified SPI module.
  * @return     None.
  * @details    Set SPIEN (SPI_CTL[0]) to enable SPI controller.
  */
#define SPI_ENABLE(spi)   ( (spi)->CTL |= SPI_CTL_SPIEN_Msk )

/**
  * @brief      Disable SPI controller.
  * @param[in]  spi The pointer of the specified SPI module.
  * @return     None.
  * @details    Clear SPIEN (SPI_CTL[0]) to disable SPI controller.
  */
#define SPI_DISABLE(spi)   ( (spi)->CTL &= ~SPI_CTL_SPIEN_Msk )

/**
  * @brief  Enable zero cross detection function.
  * @param[in] i2s The pointer of the specified I2S module.
  * @param[in] u32ChMask The mask for left or right channel. Valid values are:
  *                    - \ref SPII2S_RIGHT
  *                    - \ref SPII2S_LEFT
  * @return None
  * @details This function will set RZCEN or LZCEN bit of SPI_I2SCTL register to enable zero cross detection function.
  */
__STATIC_INLINE void SPII2S_ENABLE_TX_ZCD(SPI_T *i2s, uint32_t u32ChMask)
{
    if(u32ChMask == SPII2S_RIGHT)
    {
        i2s->I2SCTL |= SPI_I2SCTL_RZCEN_Msk;
    }
    else
    {
        i2s->I2SCTL |= SPI_I2SCTL_LZCEN_Msk;
    }
}

/**
  * @brief  Disable zero cross detection function.
  * @param[in] i2s The pointer of the specified I2S module.
  * @param[in] u32ChMask The mask for left or right channel. Valid values are:
  *                    - \ref SPII2S_RIGHT
  *                    - \ref SPII2S_LEFT
  * @return None
  * @details This function will clear RZCEN or LZCEN bit of SPI_I2SCTL register to disable zero cross detection function.
  */
__STATIC_INLINE void SPII2S_DISABLE_TX_ZCD(SPI_T *i2s, uint32_t u32ChMask)
{
    if(u32ChMask == SPII2S_RIGHT)
    {
        i2s->I2SCTL &= ~SPI_I2SCTL_RZCEN_Msk;
    }
    else
    {
        i2s->I2SCTL &= ~SPI_I2SCTL_LZCEN_Msk;
    }
}

/**
  * @brief  Enable I2S TX DMA function.
  * @param[in] i2s The pointer of the specified I2S module.
  * @return None
  * @details This macro will set TXPDMAEN bit of SPI_PDMACTL register to transmit data with PDMA.
  */
#define SPII2S_ENABLE_TXDMA(i2s)  ( (i2s)->PDMACTL |= SPI_PDMACTL_TXPDMAEN_Msk )

/**
  * @brief  Disable I2S TX DMA function.
  * @param[in] i2s The pointer of the specified I2S module.
  * @return None
  * @details This macro will clear TXPDMAEN bit of SPI_PDMACTL register to disable TX DMA function.
  */
#define SPII2S_DISABLE_TXDMA(i2s) ( (i2s)->PDMACTL &= ~SPI_PDMACTL_TXPDMAEN_Msk )

/**
  * @brief  Enable I2S RX DMA function.
  * @param[in] i2s The pointer of the specified I2S module.
  * @return None
  * @details This macro will set RXPDMAEN bit of SPI_PDMACTL register to receive data with PDMA.
  */
#define SPII2S_ENABLE_RXDMA(i2s) ( (i2s)->PDMACTL |= SPI_PDMACTL_RXPDMAEN_Msk )

/**
  * @brief  Disable I2S RX DMA function.
  * @param[in] i2s The pointer of the specified I2S module.
  * @return None
  * @details This macro will clear RXPDMAEN bit of SPI_PDMACTL register to disable RX DMA function.
  */
#define SPII2S_DISABLE_RXDMA(i2s) ( (i2s)->PDMACTL &= ~SPI_PDMACTL_RXPDMAEN_Msk )

/**
  * @brief  Enable I2S TX function.
  * @param[in] i2s The pointer of the specified I2S module.
  * @return None
  * @details This macro will set TXEN bit of SPI_I2SCTL register to enable I2S TX function.
  */
#define SPII2S_ENABLE_TX(i2s) ( (i2s)->I2SCTL |= SPI_I2SCTL_TXEN_Msk )

/**
  * @brief  Disable I2S TX function.
  * @param[in] i2s The pointer of the specified I2S module.
  * @return None
  * @details This macro will clear TXEN bit of SPI_I2SCTL register to disable I2S TX function.
  */
#define SPII2S_DISABLE_TX(i2s) ( (i2s)->I2SCTL &= ~SPI_I2SCTL_TXEN_Msk )

/**
  * @brief  Enable I2S RX function.
  * @param[in] i2s The pointer of the specified I2S module.
  * @return None
  * @details This macro will set RXEN bit of SPI_I2SCTL register to enable I2S RX function.
  */
#define SPII2S_ENABLE_RX(i2s) ( (i2s)->I2SCTL |= SPI_I2SCTL_RXEN_Msk )

/**
  * @brief  Disable I2S RX function.
  * @param[in] i2s The pointer of the specified I2S module.
  * @return None
  * @details This macro will clear RXEN bit of SPI_I2SCTL register to disable I2S RX function.
  */
#define SPII2S_DISABLE_RX(i2s) ( (i2s)->I2SCTL &= ~SPI_I2SCTL_RXEN_Msk )

/**
  * @brief  Enable TX Mute function.
  * @param[in] i2s The pointer of the specified I2S module.
  * @return None
  * @details This macro will set MUTE bit of SPI_I2SCTL register to enable I2S TX mute function.
  */
#define SPII2S_ENABLE_TX_MUTE(i2s)  ( (i2s)->I2SCTL |= SPI_I2SCTL_MUTE_Msk )

/**
  * @brief  Disable TX Mute function.
  * @param[in] i2s The pointer of the specified I2S module.
  * @return None
  * @details This macro will clear MUTE bit of SPI_I2SCTL register to disable I2S TX mute function.
  */
#define SPII2S_DISABLE_TX_MUTE(i2s) ( (i2s)->I2SCTL &= ~SPI_I2SCTL_MUTE_Msk )

/**
  * @brief  Clear TX FIFO.
  * @param[in] i2s The pointer of the specified I2S module.
  * @return None
  * @details This macro will clear TX FIFO. The internal TX FIFO pointer will be reset to FIFO start point.
  */
#define SPII2S_CLR_TX_FIFO(i2s) ( (i2s)->FIFOCTL |= SPI_FIFOCTL_TXFBCLR_Msk )

/**
  * @brief  Clear RX FIFO.
  * @param[in] i2s The pointer of the specified I2S module.
  * @return None
  * @details This macro will clear RX FIFO. The internal RX FIFO pointer will be reset to FIFO start point.
  */
#define SPII2S_CLR_RX_FIFO(i2s) ( (i2s)->FIFOCTL |= SPI_FIFOCTL_RXFBCLR_Msk )

/**
  * @brief  This function sets the recording source channel when mono mode is used.
  * @param[in] i2s The pointer of the specified I2S module.
  * @param[in] u32Ch left or right channel. Valid values are:
  *                - \ref SPII2S_MONO_LEFT
  *                - \ref SPII2S_MONO_RIGHT
  * @return None
  * @details This function selects the recording source channel of monaural mode.
  */
__STATIC_INLINE void SPII2S_SET_MONO_RX_CHANNEL(SPI_T *i2s, uint32_t u32Ch)
{
    u32Ch == SPII2S_MONO_LEFT ?
    (i2s->I2SCTL |= SPI_I2SCTL_RXLCH_Msk) :
    (i2s->I2SCTL &= ~SPI_I2SCTL_RXLCH_Msk);
}

/**
  * @brief  Write data to I2S TX FIFO.
  * @param[in] i2s The pointer of the specified I2S module.
  * @param[in] u32Data The value written to TX FIFO.
  * @return None
  * @details This macro will write a value to TX FIFO.
  */
#define SPII2S_WRITE_TX_FIFO(i2s, u32Data)  ( (i2s)->TX = (u32Data) )

/**
  * @brief  Read RX FIFO.
  * @param[in] i2s The pointer of the specified I2S module.
  * @return The value read from RX FIFO.
  * @details This function will return a value read from RX FIFO.
  */
#define SPII2S_READ_RX_FIFO(i2s) ( (i2s)->RX )

/**
  * @brief  Get the interrupt flag.
  * @param[in] i2s The pointer of the specified I2S module.
  * @param[in] u32Mask The mask value for all interrupt flags.
  * @return The interrupt flags specified by the u32mask parameter.
  * @details This macro will return the combination interrupt flags of SPI_I2SSTS register. The flags are specified by the u32mask parameter.
  */
#define SPII2S_GET_INT_FLAG(i2s, u32Mask) ( (i2s)->I2SSTS & (u32Mask) )

/**
  * @brief  Clear the interrupt flag.
  * @param[in] i2s The pointer of the specified I2S module.
  * @param[in] u32Mask The mask value for all interrupt flags.
  * @return None
  * @details This macro will clear the interrupt flags specified by the u32mask parameter.
  * @note Except TX and RX FIFO threshold interrupt flags, the other interrupt flags can be cleared by writing 1 to itself.
  */
#define SPII2S_CLR_INT_FLAG(i2s, u32Mask) ( (i2s)->I2SSTS = (u32Mask) )

/**
  * @brief  Get transmit FIFO level
  * @param[in] i2s The pointer of the specified I2S module.
  * @return TX FIFO level
  * @details This macro will return the number of available words in TX FIFO.
  */
#define SPII2S_GET_TX_FIFO_LEVEL(i2s) ( ((i2s)->I2SSTS & SPI_I2SSTS_TXCNT_Msk) >> SPI_I2SSTS_TXCNT_Pos )

/**
  * @brief  Get receive FIFO level
  * @param[in] i2s The pointer of the specified I2S module.
  * @return RX FIFO level
  * @details This macro will return the number of available words in RX FIFO.
  */
#define SPII2S_GET_RX_FIFO_LEVEL(i2s) ( ((i2s)->I2SSTS & SPI_I2SSTS_RXCNT_Msk) >> SPI_I2SSTS_RXCNT_Pos )

/* Function prototype declaration */
uint32_t SPI_Open(SPI_T *spi, uint32_t u32MasterSlave, uint32_t u32SPIMode, uint32_t u32DataWidth, uint32_t u32BusClock);
void SPI_Close(SPI_T *spi);
void SPI_ClearRxFIFO(SPI_T *spi);
void SPI_ClearTxFIFO(SPI_T *spi);
void SPI_DisableAutoSS(SPI_T *spi);
void SPI_EnableAutoSS(SPI_T *spi, uint32_t u32SSPinMask, uint32_t u32ActiveLevel);
uint32_t SPI_SetBusClock(SPI_T *spi, uint32_t u32BusClock);
void SPI_SetFIFO(SPI_T *spi, uint32_t u32TxThreshold, uint32_t u32RxThreshold);
uint32_t SPI_GetBusClock(SPI_T *spi);
void SPI_EnableInt(SPI_T *spi, uint32_t u32Mask);
void SPI_DisableInt(SPI_T *spi, uint32_t u32Mask);
uint32_t SPI_GetIntFlag(SPI_T *spi, uint32_t u32Mask);
void SPI_ClearIntFlag(SPI_T *spi, uint32_t u32Mask);
uint32_t SPI_GetStatus(SPI_T *spi, uint32_t u32Mask);
uint32_t SPI_GetStatus2(SPI_T *spi, uint32_t u32Mask);

uint32_t SPII2S_Open(SPI_T *i2s, uint32_t u32MasterSlave, uint32_t u32SampleRate, uint32_t u32WordWidth, uint32_t u32Channels, uint32_t u32DataFormat);
void SPII2S_Close(SPI_T *i2s);
void SPII2S_EnableInt(SPI_T *i2s, uint32_t u32Mask);
void SPII2S_DisableInt(SPI_T *i2s, uint32_t u32Mask);
uint32_t SPII2S_EnableMCLK(SPI_T *i2s, uint32_t u32BusClock);
void SPII2S_DisableMCLK(SPI_T *i2s);
void SPII2S_SetFIFO(SPI_T *i2s, uint32_t u32TxThreshold, uint32_t u32RxThreshold);


/**@}*/ /* end of group SPI_EXPORTED_FUNCTIONS */

/**@}*/ /* end of group SPI_Driver */

/**@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif /* __NU_SPI_H__ */
