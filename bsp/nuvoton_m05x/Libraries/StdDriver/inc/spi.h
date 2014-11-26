/**************************************************************************//**
 * @file     spi.h
 * @version  V3.00
 * $Revision: 4 $
 * $Date: 14/01/28 10:49a $
 * @brief    M051 series SPI driver header file
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __SPI_H__
#define __SPI_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup M051_Device_Driver M051 Device Driver
  @{
*/

/** @addtogroup M051_SPI_Driver SPI Driver
  @{
*/

/** @addtogroup M051_SPI_EXPORTED_CONSTANTS SPI Exported Constants
  @{
*/

#define SPI_MODE_0        (SPI_CNTRL_TX_NEG_Msk)                          /*!< CLKP=0; RX_NEG=0; TX_NEG=1 */
#define SPI_MODE_1        (SPI_CNTRL_RX_NEG_Msk)                          /*!< CLKP=0; RX_NEG=1; TX_NEG=0 */
#define SPI_MODE_2        (SPI_CNTRL_CLKP_Msk | SPI_CNTRL_RX_NEG_Msk)     /*!< CLKP=1; RX_NEG=1; TX_NEG=0 */
#define SPI_MODE_3        (SPI_CNTRL_CLKP_Msk | SPI_CNTRL_TX_NEG_Msk)     /*!< CLKP=1; RX_NEG=0; TX_NEG=1 */

#define SPI_SLAVE         (SPI_CNTRL_SLAVE_Msk)                           /*!< Set as slave */
#define SPI_MASTER        (0x0)                                           /*!< Set as master */

#define SPI_SS                (SPI_SSR_SSR_Msk)                           /*!< Set SS */
#define SPI_SS_ACTIVE_HIGH    (SPI_SSR_SS_LVL_Msk)                        /*!< SS active high */
#define SPI_SS_ACTIVE_LOW     (0x0)                                       /*!< SS active low */

#define SPI_UNIT_INT_MASK                (0x01)                           /*!< Unit transfer interrupt mask */
#define SPI_SSTA_INT_MASK                (0x02)                           /*!< Slave 3-Wire mode start interrupt mask */
#define SPI_FIFO_TX_INT_MASK             (0x04)                           /*!< FIFO TX interrupt mask */
#define SPI_FIFO_RX_INT_MASK             (0x08)                           /*!< FIFO RX interrupt mask */
#define SPI_FIFO_RXOV_INT_MASK           (0x10)                           /*!< FIFO RX overrun interrupt mask */
#define SPI_FIFO_TIMEOUT_INT_MASK        (0x20)                           /*!< FIFO RX timeout interrupt mask */

#define SPI_BUSY_MASK                    (0x01)                           /*!< Busy status mask */
#define SPI_RX_EMPTY_MASK                (0x02)                           /*!< RX empty status mask */
#define SPI_RX_FULL_MASK                 (0x04)                           /*!< RX full status mask */
#define SPI_TX_EMPTY_MASK                (0x08)                           /*!< TX empty status mask */
#define SPI_TX_FULL_MASK                 (0x10)                           /*!< TX full status mask */

/*@}*/ /* end of group M051_SPI_EXPORTED_CONSTANTS */


/** @addtogroup M051_SPI_EXPORTED_FUNCTIONS SPI Exported Functions
  @{
*/

/**
  * @brief      Abort the current transfer in slave 3-wire mode.
  * @param[in]  spi is the base address of SPI module.
  * @return     None
  */
#define SPI_ABORT_3WIRE_TRANSFER(spi)   ((spi)->CNTRL2 |= SPI_CNTRL2_SLV_ABORT_Msk)

/**
  * @brief      Clear the slave 3-wire mode start interrupt flag.
  * @param[in]  spi is the base address of SPI module.
  * @return     None
  */
#define SPI_CLR_3WIRE_START_INT_FLAG(spi)   ((spi)->CNTRL2 |= SPI_CNTRL2_SLV_START_INTSTS_Msk)

/**
  * @brief      Clear the unit transfer interrupt flag.
  * @param[in]  spi is the base address of SPI module.
  * @return     None
  */
#define SPI_CLR_UNIT_TRANS_INT_FLAG(spi)   ((spi)->CNTRL |= SPI_CNTRL_IF_Msk))

/**
  * @brief      Disable slave 3-wire mode.
  * @param[in]  spi is the base address of SPI module.
  * @return     None
  */
#define SPI_DISABLE_3WIRE_MODE(spi)   ((spi)->CNTRL2 &= ~SPI_CNTRL2_NOSLVSEL_Msk)

/**
  * @brief      Enable slave 3-wire mode.
  * @param[in]  spi is the base address of SPI module.
  * @return     None
  */
#define SPI_ENABLE_3WIRE_MODE(spi)   ((spi)->CNTRL2 |= SPI_CNTRL2_NOSLVSEL_Msk)

/**
  * @brief      Get the count of available data in RX FIFO.
  * @param[in]  spi is the base address of SPI module.
  * @return     The count of available data in RX FIFO.
  */
#define SPI_GET_RX_FIFO_COUNT(spi)   (((spi)->STATUS & SPI_STATUS_RX_FIFO_COUNT_Msk) >> SPI_STATUS_RX_FIFO_COUNT_Pos)

/**
  * @brief      Get the RX FIFO empty flag.
  * @param[in]  spi is the base address of SPI module.
  * @return     RX FIFO empty flag
  * @retval     0: RX FIFO is not empty
  * @retval     1: RX FIFO is empty
  */
#define SPI_GET_RX_FIFO_EMPTY_FLAG(spi)   (((spi)->STATUS & SPI_STATUS_RX_EMPTY_Msk)>>SPI_STATUS_RX_EMPTY_Pos)

/**
  * @brief      Get the TX FIFO empty flag.
  * @param[in]  spi is the base address of SPI module.
  * @return     Tx FIFO empty flag
  * @retval     0: TX FIFO is not empty
  * @retval     1: TX FIFO is empty
  */
#define SPI_GET_TX_FIFO_EMPTY_FLAG(spi)   (((spi)->STATUS & SPI_STATUS_TX_EMPTY_Msk)>>SPI_STATUS_TX_EMPTY_Pos)

/**
  * @brief      Get the TX FIFO full flag.
  * @param[in]  spi is the base address of SPI module.
  * @return     TX FIFO full flag
  * @retval     0: TX FIFO is not full
  * @retval     1: TX FIFO is full
  */
#define SPI_GET_TX_FIFO_FULL_FLAG(spi)   (((spi)->STATUS & SPI_STATUS_TX_FULL_Msk)>>SPI_STATUS_TX_FULL_Pos)

/**
  * @brief      Get the datum read from RX0 register.
  * @param[in]  spi is the base address of SPI module.
  * @return     Data in RX0 register
  */
#define SPI_READ_RX0(spi)   ((spi)->RX0)

/**
  * @brief      Get the datum read from RX1 register.
  * @param[in]  spi is the base address of SPI module.
  * @return     Data in RX1 register
  */
#define SPI_READ_RX1(spi)   ((spi)->RX1)

/**
  * @brief      Write datum to TX0 register.
  * @param[in]  spi is the base address of SPI module.
  * @param[in]  u32TxData is the datum which user attempt to transfer through SPI bus.
  * @return     None
  */
#define SPI_WRITE_TX0(spi, u32TxData)   ((spi)->TX0 = (u32TxData))

/**
  * @brief      Write datum to TX1 register.
  * @param[in]  spi is the base address of SPI module.
  * @param[in]  u32TxData is the datum which user attempt to transfer through SPI bus.
  * @return     None
  */
#define SPI_WRITE_TX1(spi, u32TxData)   ((spi)->TX1 = (u32TxData))

/**
  * @brief      Disable automatic slave select function and set SPI_SS pin to high state.
  * @param[in]  spi is the base address of SPI module.
  * @return     None
  */
#define SPI_SET_SS_HIGH(spi)   ((spi)->SSR = ((spi)->SSR & (~SPI_SSR_AUTOSS_Msk)) | (SPI_SSR_SS_LVL_Msk | SPI_SSR_SSR_Msk))

/**
  * @brief      Disable automatic slave select function and set SPI_SS pin to low state.
  * @param[in]  spi is the base address of SPI module.
  * @return     None
  */
#define SPI_SET_SS_LOW(spi)   ((spi)->SSR = ((spi)->SSR & (~(SPI_SSR_AUTOSS_Msk|SPI_SSR_SS_LVL_Msk))) | SPI_SSR_SSR_Msk)

/**
  * @brief      Enable byte reorder function.
  * @param[in]  spi is the base address of SPI module.
  * @return     None
  */
#define SPI_ENABLE_BYTE_REORDER(spi)   ((spi)->CNTRL = ((spi)->CNTRL & (~SPI_CNTRL_REORDER_Msk)) | (1<<SPI_CNTRL_REORDER_Pos))

/**
  * @brief      Disable byte reorder function.
  * @param[in]  spi is the base address of SPI module.
  * @return     None
  */
#define SPI_DISABLE_BYTE_REORDER(spi)   ((spi)->CNTRL &= ~SPI_CNTRL_REORDER_Msk)

/**
  * @brief      Set the length of suspend interval.
  * @param[in]  spi is the base address of SPI module.
  * @param[in]  u32SuspCycle decides the length of suspend interval.
  * @return     None
  */
#define SPI_SET_SUSPEND_CYCLE(spi, u32SuspCycle)   ((spi)->CNTRL = ((spi)->CNTRL & ~SPI_CNTRL_SP_CYCLE_Msk) | ((u32SuspCycle) << SPI_CNTRL_SP_CYCLE_Pos))

/**
  * @brief      Set the SPI transfer sequence with LSB first.
  * @param[in]  spi is the base address of SPI module.
  * @return     None
  */
#define SPI_SET_LSB_FIRST(spi)   ((spi)->CNTRL |= SPI_CNTRL_LSB_Msk)

/**
  * @brief      Set the SPI transfer sequence with MSB first.
  * @param[in]  spi is the base address of SPI module.
  * @return     None
  */
#define SPI_SET_MSB_FIRST(spi)   ((spi)->CNTRL &= ~SPI_CNTRL_LSB_Msk)

/**
  * @brief      Set the data width of a SPI transaction.
  * @param[in]  spi is the base address of SPI module.
  * @param[in]  u32Width is the bit width of transfer data.
  * @return     None
  */
#define SPI_SET_DATA_WIDTH(spi, u32Width)   ((spi)->CNTRL = ((spi)->CNTRL & ~SPI_CNTRL_TX_BIT_LEN_Msk) | (((u32Width)&0x1F) << SPI_CNTRL_TX_BIT_LEN_Pos))

/**
  * @brief      Get the SPI busy state.
  * @param[in]  spi is the base address of SPI module.
  * @return     SPI busy status
  * @retval     0: SPI module is not busy
  * @retval     1: SPI module is busy
  */
#define SPI_IS_BUSY(spi)   ( ((spi)->CNTRL & SPI_CNTRL_GO_BUSY_Msk)>>SPI_CNTRL_GO_BUSY_Pos )

/**
  * @brief      Set the GO_BUSY bit to trigger SPI transfer.
  * @param[in]  spi is the base address of SPI module.
  * @return     None
  */
#define SPI_TRIGGER(spi)   ((spi)->CNTRL |= SPI_CNTRL_GO_BUSY_Msk)


/* Function prototype declaration */
uint32_t SPI_Open(SPI_T *spi, uint32_t u32MasterSlave, uint32_t u32SPIMode, uint32_t u32DataWidth, uint32_t u32BusClock);
void SPI_Close(SPI_T *spi);
void SPI_ClearRxFIFO(SPI_T *spi);
void SPI_ClearTxFIFO(SPI_T *spi);
void SPI_DisableAutoSS(SPI_T *spi);
void SPI_EnableAutoSS(SPI_T *spi, uint32_t u32SSPinMask, uint32_t u32ActiveLevel);
uint32_t SPI_SetBusClock(SPI_T *spi, uint32_t u32BusClock);
void SPI_EnableFIFO(SPI_T *spi, uint32_t u32TxThreshold, uint32_t u32RxThreshold);
void SPI_DisableFIFO(SPI_T *spi);
uint32_t SPI_GetBusClock(SPI_T *spi);
void SPI_EnableInt(SPI_T *spi, uint32_t u32Mask);
void SPI_DisableInt(SPI_T *spi, uint32_t u32Mask);
uint32_t SPI_GetIntFlag(SPI_T *spi, uint32_t u32Mask);
void SPI_ClearIntFlag(SPI_T *spi, uint32_t u32Mask);
uint32_t SPI_GetStatus(SPI_T *spi, uint32_t u32Mask);

/*@}*/ /* end of group M051_SPI_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group M051_SPI_Driver */

/*@}*/ /* end of group M051_Device_Driver */

#ifdef __cplusplus
}
#endif

#endif //__SPI_H__

/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/
