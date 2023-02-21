/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __HAL_DMA_H__
#define __HAL_DMA_H__

#include "hal_common.h"

/*!
 * @addtogroup DMA
 * @{
 */

/*!
 * @addtogroup DMA_CHANNEL_INT
 * @{
 */
#define DMA_CHN_INT_XFER_GLOBAL      (0x1u << 0u) /*!< DMA global interrupt channel. */
#define DMA_CHN_INT_XFER_DONE        (0x1u << 1u) /*!< DMA end of transfer interrupt channel. */
#define DMA_CHN_INT_XFER_HALF_DONE   (0x1u << 2u) /*!< DMA half transfer interrupt channel. */
#define DMA_CHN_INT_XFER_ERR         (0x1u << 3u) /*!< DMA transfer error interrupt channel. */
/*!
 * @}
 */


/*!
 * @brief Define the enum type of DMA_XferMode_Type.
 */
typedef enum
{
    DMA_XferMode_PeriphToMemory = 0u,      /*!< memory to memory mode, from periph addr to memory addr. */
    DMA_XferMode_MemoryToPeriph = 1u,      /*!< memory to memory mode, from periph addr to memory addr. */
    DMA_XferMode_PeriphToMemoryBurst = 2u, /*!< memory to memory mode, from periph addr to memory addr. */
    DMA_XferMode_MemoryToPeriphBurst = 3u, /*!< memory to memory mode, from memory addr to periph addr. */
} DMA_XferMode_Type;

/*!
 * @brief Define the enum type of DMA_ReloadMode_Type.
 */
typedef enum
{
    DMA_ReloadMode_OneTime    = 0u, /*!< the count is exhausted after the xfer is done.  */
    DMA_ReloadMode_AutoReload = 1u, /*!< auto reload the count for the new xfer. */
    DMA_ReloadMode_AutoReloadContinuous = 2u, /*!< auto reload the count for the next xfer, and always run. */
} DMA_ReloadMode_Type;

/*!
 * @brief Incremental mode of peripherals and memories.
 */
typedef enum
{
    DMA_AddrIncMode_StayAfterXfer = 0u, /*!< Peripheral access address accumulation. */
    DMA_AddrIncMode_IncAfterXfer  = 1u, /*!< Memory access address accumulation. */
} DMA_AddrIncMode_Type;

/*!
 * @brief Define the enum type of DMA xfer width type.
 */
typedef enum
{
    DMA_XferWidth_8b  = 0u, /*!< Xfer width 8 bits. */
    DMA_XferWidth_16b = 1u, /*!< Xfer width 16 bits. */
    DMA_XferWidth_32b = 2u, /*!< Xfer width 32 bits. */
} DMA_XferWidth_Type;

/*!
 * @brief Configure DMA Priority.
 */
typedef enum
{
    DMA_Priority_Low     = 0u, /*!< Low Priority. */
    DMA_Priority_Middle  = 1u, /*!< Middle Priority. */
    DMA_Priority_High    = 2u, /*!< High Priority. */
    DMA_Priority_Highest = 3u, /*!< Highest Priority. */
} DMA_Priority_Type;

/*!
 * @brief This type of structure instance is used to keep the settings when calling the @ref DMA_InitChannel() to initialize the DMA module.
 */
typedef struct
{
    DMA_XferMode_Type     XferMode;             /*!< Specify whether the Receive or Transmit mode is enabled or not. */
    DMA_ReloadMode_Type   ReloadMode;           /*!< Specify whether to automatically reload the next transfer count when the count is exhausted. */
    DMA_AddrIncMode_Type  PeriphAddrIncMode;    /*!< Specify peripheral Address Inc Mode. */
    DMA_AddrIncMode_Type  MemAddrIncMode;       /*!< Specify Memory Address Inc Mode. */
    DMA_XferWidth_Type    XferWidth;            /*!< Specify the transmission data width. */
    DMA_Priority_Type     Priority;             /*!< Specify priority mode. */
    uint32_t              XferCount;            /*!< Specify CircularMode's count. */
    uint32_t              MemAddr;              /*!< Specify Memory Address. */
    uint32_t              PeriphAddr;           /*!< Specify Periph Address. */
} DMA_Channel_Init_Type;

/*!
 * @brief Initialize the DMA module.
 *
 * @param DMAx DMA instance.
 * @param channel Channel corresponding to DMA controller.
 * @param init  Pointer to the initialization structure. See to @ref DMA_Channel_Init_Type.
 * @return None.
 */
uint32_t DMA_InitChannel(DMA_Type * DMAx, uint32_t channel, DMA_Channel_Init_Type * init);

/*!
 * @brief enable the DMA channel interrupts of the DMA module.
 *
 * @param DMAx DMA instance.
 * @param channel Channel corresponding to DMA controller.
 * @param interrupts Interrupt code masks. See to @ref DMA_CHANNEL_INT.
 * @param enable 'true' to enable the DMA channel interrupts, 'false' to disable the DMA channel interrupts.
 * @return None.
 */
void     DMA_EnableChannelInterrupts(DMA_Type * DMAx, uint32_t channel, uint32_t interrupts, bool enable);

/*!
 * @brief Get the channel interrupts status flags of the DMA module.
 *
 * @param DMAx DMA instance.
 * @param channel Channel corresponding to DMA controller in DMA. See to @ref DMA_CHANNEL_INT.
 * @return Interrupt status flags.
 */
uint32_t DMA_GetChannelInterruptStatus(DMA_Type * DMAx, uint32_t channel);

/*!
 * @brief Clear the channel interrupts status flags of the DMA module.
 *
 * @param DMAx DMA instance.
 * @param channel Channel corresponding to DMA controller. See to @ref DMA_CHANNEL_INT.
 * @param interrupts Interrupt code masks.
 * @return None.
 */
void     DMA_ClearChannelInterruptStatus(DMA_Type * DMAx, uint32_t channel, uint32_t interrupts);

/*!
 * @brief Enable the channel of the DMA module.
 *
 * @param DMAx DMA instance.
 * @param channel Channel corresponding to DMA controller. See to @ref DMA_CHANNEL_INT.
 * @param enable 'true' to enable the DMA controller sends a reply signal to the peripheral, 'false' to disable the DMA controller sends a reply signal to the peripheral.
 * @return None.
 */
void     DMA_EnableChannel(DMA_Type * DMAx, uint32_t channel, bool enable);

/*!
 *@}
 */

#endif /* __HAL_DMA_H__ */

