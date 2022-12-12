/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __HAL_SPI_H__
#define __HAL_SPI_H__

#include "hal_common.h"

/*!
 * @addtogroup SPI
 * @{
 */

/*!
 * @addtogroup SPI_STATUS
 * @{
 */
#define SPI_STATUS_TXEMPTY     SPI_I2S_CSTAT_TXEPT_MASK  /*!< Status flag when SPI transmiter buffer is empty. */
#define SPI_STATUS_RXDONE      SPI_I2S_CSTAT_RXAVL_MASK  /*!< Status flag when SPI receiving buffer is with available data. */
#define SPI_STATUS_TXFULL      SPI_I2S_CSTAT_TXFULL_MASK /*!< Status flag when SPI transmiter buffer is full. */
/*!
 * @}
 */

/*!
 * @addtogroup SPI_INT
 * @{
 */
#define SPI_INT_TXEMPTY        SPI_I2S_INTEN_TXIEN_MASK  /*!< Interrupt enable when SPI transmiter buffer is empty. */
#define SPI_INT_RXDONE         SPI_I2S_INTEN_RXIEN_MASK  /*!< Interrupt enable when UART receiving buffer is with available data. */
/*!
 * @}
 */

/*!
 * @brief SPI Polarity Phase type.
 */
typedef enum
{
    SPI_PolarityPhase_Alt0 = 0u, /*!< CPOL = 0, CPHA = 0, Clock line is low when idle. Tx data line is high when idle. Data valid when at rising edge */
    SPI_PolarityPhase_Alt1 = 1u, /*!< CPOL = 0, CPHA = 1, Clock line is low when idle. Tx data line is high when idle. Data valid when at falling edge */
    SPI_PolarityPhase_Alt2 = 2u, /*!< CPOL = 1, CPHA = 0, Clock line is high when idle. Tx data line is high when idle. Data valid when at falling edge */
    SPI_PolarityPhase_Alt3 = 3u, /*!< CPOL = 1, CPHA = 1, Clock line is high when idle. Tx data line is high when idle. Data valid when at rising edge */
} SPI_PolarityPhase_Type;

/*!
 * @brief SPI data width type.
 */
typedef enum
{
    SPI_DataWidth_0b  = 0u, /*!< Data Width 0 bits. */
    SPI_DataWidth_1b  = 1u, /*!< Data Width 1 bits. */
    SPI_DataWidth_2b  = 2u, /*!< Data Width 2 bits. */
    SPI_DataWidth_3b  = 3u, /*!< Data Width 3 bits. */
    SPI_DataWidth_4b  = 4u, /*!< Data Width 4 bits. */
    SPI_DataWidth_5b  = 5u, /*!< Data Width 5 bits. */
    SPI_DataWidth_6b  = 6u, /*!< Data Width 6 bits. */
    SPI_DataWidth_7b  = 7u, /*!< Data Width 7 bits. */
    SPI_DataWidth_8b  = 8u, /*!< Data Width 8 bits. */
    SPI_DataWidth_9b  = 9u, /*!< Data Width 9 bits. */
    SPI_DataWidth_10b = 10u, /*!< Data Width 10 bits. */
    SPI_DataWidth_11b = 11u, /*!< Data Width 11 bits. */
    SPI_DataWidth_12b = 12u, /*!< Data Width 12 bits. */
    SPI_DataWidth_13b = 13u, /*!< Data Width 13 bits. */
    SPI_DataWidth_14b = 14u, /*!< Data Width 14 bits. */
    SPI_DataWidth_15b = 15u, /*!< Data Width 15 bits. */
    SPI_DataWidth_16b = 16u, /*!< Data Width 16 bits. */
    SPI_DataWidth_17b = 17u, /*!< Data Width 17 bits. */
    SPI_DataWidth_18b = 18u, /*!< Data Width 18 bits. */
    SPI_DataWidth_19b = 19u, /*!< Data Width 19 bits. */
    SPI_DataWidth_20b = 20u, /*!< Data Width 20 bits. */
    SPI_DataWidth_21b = 21u, /*!< Data Width 21 bits. */
    SPI_DataWidth_22b = 22u, /*!< Data Width 22 bits. */
    SPI_DataWidth_23b = 23u, /*!< Data Width 23 bits. */
    SPI_DataWidth_24b = 24u, /*!< Data Width 24 bits. */
    SPI_DataWidth_25b = 25u, /*!< Data Width 25 bits. */
    SPI_DataWidth_26b = 26u, /*!< Data Width 26 bits. */
    SPI_DataWidth_27b = 27u, /*!< Data Width 27 bits. */
    SPI_DataWidth_28b = 28u, /*!< Data Width 28 bits. */
    SPI_DataWidth_29b = 29u, /*!< Data Width 29 bits. */
    SPI_DataWidth_30b = 30u, /*!< Data Width 30 bits. */
    SPI_DataWidth_31b = 31u, /*!< Data Width 31 bits. */
    SPI_DataWidth_32b = 32u, /*!< Data Width 32 bits. */
} SPI_DataWidth_Type;

/*!
 * @brief SPI xfer mode type.
 */
typedef enum
{
    SPI_XferMode_Disabled = 0u, /*!< Disable both Tx and Rx. */
    SPI_XferMode_RxOnly   = 1u, /*!< Enable Rx only. */
    SPI_XferMode_TxRx     = 2u, /*!< Enable both Tx and Rx. */
} SPI_XferMode_Type;

/*!
 * @brief This type of structure instance is used to keep the settings when calling the @ref SPI_InitMaster() to initialize the SPI module.
 */
typedef struct
{
    uint32_t                ClockFreqHz;    /*!< Bus Clock Freq. */
    uint32_t                BaudRate;       /*!< This member configures the UART communication baud rate. */
    SPI_PolarityPhase_Type  PolarityPhase;  /*!< Specifies different communication modes. */
    SPI_DataWidth_Type      DataWidth;      /*!< Specifies the number of bits of data to be transmitted. */
    SPI_XferMode_Type       XferMode;       /*!< Specifies whether the Receive or Transmit mode is enable or not. */
    bool                    AutoCS;         /*!< Specifies whether the chip selection signal is controlled by SPI or not. */
    bool                    LSB;            /*!< Specifies whether the current state is Thumb or ARM mode. */
} SPI_Master_Init_Type;

/*!
 * @brief Initialize the SPI Master module.
 *
 * @param SPIx SPI instance.
 * @param init  Pointer to the initialization structure. See to @ref SPI_Master_Init_Type.
 * @return None.
 */
void SPI_InitMaster(SPI_Type * SPIx, SPI_Master_Init_Type * init);

/*!
 * @brief Enable the SPI module.
 *
 * The SPI module should be enabled before sending or receiving data.
 *
 * @param SPIx SPI instance.
 * @param enable 'true' to enable the module, 'false' to disable the module.
 * @return None.
 */
void SPI_Enable(SPI_Type * SPIx, bool enable);

/*!
 * @brief Get the current status flags of the SPI module.
 *
 * @param SPIx SPI instance.
 * @return Status flags. See to @ref SPI_STATUS.
 */
uint32_t SPI_GetStatus(SPI_Type * SPIx);

/*!
 * @brief Enable interrupts of the SPI module.
 *
 * @param SPIx SPI instance.
 * @param interrupts Interrupt code masks. See to @ref SPI_INT.
 * @param enable 'true' to enable the indicated interrupts, 'false' to disable the indicated interrupts.
 * @return None.
 */
void SPI_EnableInterrupts(SPI_Type * SPIx, uint32_t interrupts, bool enable);

/*!
 * @brief Get the interrupts status flags of the SPI module.
 *
 * @param SPIx SPI instance.
 * @return Interrupt status flags. See to @ref SPI_INT.
 */
uint32_t SPI_GetInterruptStatus(SPI_Type * SPIx);

/*!
 * @brief Clear the interrupts status flags of the SPI module.
 *
 * @param SPIx SPI instance.
 * @param interrupts The mask codes of the indicated interrupt flags to be cleared.
 * @return Interrupt status flags. See to @ref SPI_INT.
 */
void SPI_ClearInterruptStatus(SPI_Type * SPIx, uint32_t interrupts);

/*!
 * @brief Put the data into transmiter buffer of the SPI module.
 *
 * @param SPIx SPI instance.
 * @param dat Data value to be send through the transmiter.
 * @return None.
 */
void SPI_PutData(SPI_Type * SPIx, uint32_t dat);

/*!
 * @brief Get the data from receiver buffer of the SPI module.
 *
 * @param SPIx SPI instance.
 * @return The data value received from the receiver.
 * @return None.
 */
uint32_t SPI_GetData(SPI_Type * SPIx);

/*!
 * @brief Enable the DMA trigger from the SPI module.
 *
 * The DMA trigger events are the same as the intertupts.
 *
 * @param SPIx SPI instance.
 * @param enable 'true' to enable the DMA trigger, 'false' to disable the DMA trigger.
 * @return None.
 */
void SPI_EnableDMA(SPI_Type * SPIx, bool enable);

/*!
 * @brief Read the current enabled interrupts the SPI module.
 *
 * @param SPIx SPI instance.
 * @return The mask codes enabled interrupts. See to ref@ SPI_INT
 */
uint32_t SPI_GetEnabledInterrupts(SPI_Type * SPIx);

/*!
 * @brief Get the hardware Rx data buffer's address the SPI module.
 *
 * The return value of the address is most used with DMA module.
 *
 * @param SPIx SPI instance.
 * @return The value of the address for SPI module's hardware Rx data buffer.
 */
uint32_t SPI_GetRxDataRegAddr(SPI_Type * SPIx);

/*!
 * @brief Get the hardware Tx data buffer's address the SPI module.
 *
 * The return value of the address is most used with DMA module.
 *
 * @param SPIx SPI instance.
 * @return The value of the address for SPI module's hardware Tx data buffer.
 */
uint32_t SPI_GetTxDataRegAddr(SPI_Type * SPIx);

/*!
 * @brief Enable the SPI CS module.
 *
 * @param SPIx SPI instance.
 * @param cs_mask Code mask of whether the chip selection signal is controlled by SPI
 * @return None.
 */
void SPI_EnableCS(SPI_Type * SPIx, uint32_t cs_mask);

/*!
 *@}
 */

#endif /* __HAL_SPI_H__ */

