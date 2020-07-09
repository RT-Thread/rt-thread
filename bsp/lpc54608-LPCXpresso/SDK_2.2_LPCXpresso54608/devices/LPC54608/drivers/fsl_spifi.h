/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef _FSL_SPIFI_H_
#define _FSL_SPIFI_H_

#include "fsl_common.h"

/*!
 * @addtogroup spifi
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief SPIFI driver version 2.0.0. */
#define FSL_SPIFI_DRIVER_VERSION (MAKE_VERSION(2, 0, 0))
/*@}*/

/*! @brief Status structure of SPIFI.*/
enum _status_t
{
    kStatus_SPIFI_Idle = MAKE_STATUS(kStatusGroup_SPIFI, 0),  /*!< SPIFI is in idle state  */
    kStatus_SPIFI_Busy = MAKE_STATUS(kStatusGroup_SPIFI, 1),  /*!< SPIFI is busy */
    kStatus_SPIFI_Error = MAKE_STATUS(kStatusGroup_SPIFI, 2), /*!< Error occurred during SPIFI transfer */
};

/*! @brief SPIFI interrupt source */
typedef enum _spifi_interrupt_enable
{
    kSPIFI_CommandFinishInterruptEnable = SPIFI_CTRL_INTEN_MASK, /*!< Interrupt while command finished */
} spifi_interrupt_enable_t;

/*! @brief SPIFI SPI mode select */
typedef enum _spifi_spi_mode
{
    kSPIFI_SPISckLow = 0x0U, /*!< SCK low after last bit of command, keeps low while CS high */
    kSPIFI_SPISckHigh = 0x1U /*!< SCK high after last bit of command and while CS high */
} spifi_spi_mode_t;

/*! @brief SPIFI dual mode select */
typedef enum _spifi_dual_mode
{
    kSPIFI_QuadMode = 0x0U, /*!< SPIFI uses IO3:0 */
    kSPIFI_DualMode = 0x1U  /*!< SPIFI uses IO1:0 */
} spifi_dual_mode_t;

/*! @brief SPIFI data direction */
typedef enum _spifi_data_direction
{
    kSPIFI_DataInput = 0x0U, /*!< Data input from serial flash. */
    kSPIFI_DataOutput = 0x1U /*!< Data output to serial flash. */
} spifi_data_direction_t;

/*! @brief SPIFI command opcode format */
typedef enum _spifi_command_format
{
    kSPIFI_CommandAllSerial = 0x0,     /*!< All fields of command are serial. */
    kSPIFI_CommandDataQuad = 0x1U,     /*!< Only data field is dual/quad, others are serial. */
    kSPIFI_CommandOpcodeSerial = 0x2U, /*!< Only opcode field is serial, others are quad/dual. */
    kSPIFI_CommandAllQuad = 0x3U       /*!< All fields of command are dual/quad mode. */
} spifi_command_format_t;

/*! @brief SPIFI command type */
typedef enum _spifi_command_type
{
    kSPIFI_CommandOpcodeOnly = 0x1U,             /*!< Command only have opcode, no address field */
    kSPIFI_CommandOpcodeAddrOneByte = 0x2U,      /*!< Command have opcode and also one byte address field */
    kSPIFI_CommandOpcodeAddrTwoBytes = 0x3U,     /*!< Command have opcode and also two bytes address field */
    kSPIFI_CommandOpcodeAddrThreeBytes = 0x4U,   /*!< Command have opcode and also three bytes address field. */
    kSPIFI_CommandOpcodeAddrFourBytes = 0x5U,    /*!< Command have opcode and also four bytes address field */
    kSPIFI_CommandNoOpcodeAddrThreeBytes = 0x6U, /*!< Command have no opcode and three bytes address field */
    kSPIFI_CommandNoOpcodeAddrFourBytes = 0x7U   /*!< Command have no opcode and four bytes address field */
} spifi_command_type_t;

/*! @brief SPIFI status flags */
enum _spifi_status_flags
{
    kSPIFI_MemoryCommandWriteFinished = SPIFI_STAT_MCINIT_MASK, /*!< Memory command write finished */
    kSPIFI_CommandWriteFinished = SPIFI_STAT_CMD_MASK,          /*!< Command write finished */
    kSPIFI_InterruptRequest = SPIFI_STAT_INTRQ_MASK /*!< CMD flag from 1 to 0, means command execute finished */
};

/*! @brief SPIFI command structure */
typedef struct _spifi_command
{
    uint16_t dataLen;                 /*!< How many data bytes are needed in this command. */
    bool isPollMode;                  /*!< For command need to read data from serial flash */
    spifi_data_direction_t direction; /*!< Data direction of this command. */
    uint8_t intermediateBytes;        /*!< How many intermediate bytes needed */
    spifi_command_format_t format;    /*!< Command format */
    spifi_command_type_t type;        /*!< Command type */
    uint8_t opcode;                   /*!< Command opcode value */
} spifi_command_t;

/*!
 * @brief SPIFI region configuration structure.
 */
typedef struct _spifi_config
{
    uint16_t timeout;           /*!< SPI transfer timeout, the unit is SCK cycles */
    uint8_t csHighTime;         /*!< CS high time cycles */
    bool disablePrefetch;       /*!< True means SPIFI will not attempt a speculative prefetch. */
    bool disableCachePrefech;   /*!< Disable prefetch of cache line */
    bool isFeedbackClock;       /*!< Is data sample uses feedback clock. */
    spifi_spi_mode_t spiMode;   /*!< SPIFI spi mode select */
    bool isReadFullClockCycle;  /*!< If enable read full clock cycle. */
    spifi_dual_mode_t dualMode; /*!< SPIFI dual mode, dual or quad. */
} spifi_config_t;

/*! @brief Transfer structure for SPIFI */
typedef struct _spifi_transfer
{
    uint8_t *data;   /*!< Pointer to data to transmit */
    size_t dataSize; /*!< Bytes to be transmit */
} spifi_transfer_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* _cplusplus */

/*!
 * @name Initialization and deinitialization
 * @{
 */

/*!
 * @brief Initializes the SPIFI with the user configuration structure.
 *
 * This function configures the SPIFI module with the user-defined configuration.
 *
 * @param base     SPIFI peripheral base address.
 * @param config   The pointer to the configuration structure.
 */
void SPIFI_Init(SPIFI_Type *base, const spifi_config_t *config);

/*!
 * @brief Get SPIFI default configure settings.
 *
 * @param config  SPIFI config structure pointer.
 */
void SPIFI_GetDefaultConfig(spifi_config_t *config);

/*!
 * @brief Deinitializes the SPIFI regions.
 *
 * @param base     SPIFI peripheral base address.
 */
void SPIFI_Deinit(SPIFI_Type *base);

/* @}*/

/*!
 * @name Basic Control Operations
 * @{
 */

/*!
 * @brief Set SPIFI flash command.
 *
 * @param base     SPIFI peripheral base address.
 * @param cmd      SPIFI command structure pointer.
 */
void SPIFI_SetCommand(SPIFI_Type *base, spifi_command_t *cmd);

/*!
 * @brief Set SPIFI command address.
 *
 * @param base     SPIFI peripheral base address.
 * @param addr     Address value for the command.
 */
static inline void SPIFI_SetCommandAddress(SPIFI_Type *base, uint32_t addr)
{
    base->ADDR = addr;
}

/*!
 * @brief Set SPIFI intermediate data.
 *
 * Before writing a command wihch needs specific intermediate value, users shall call this function to write it.
 * The main use of this function for current serial flash is to select no-opcode mode and cancelling this mode. As
 * dummy cycle do not care about the value, no need to call this function.
 *
 * @param base     SPIFI peripheral base address.
 * @param val      Intermediate data.
 */
static inline void SPIFI_SetIntermediateData(SPIFI_Type *base, uint32_t val)
{
    base->IDATA = val;
}

/*!
 * @brief Set SPIFI Cache limit value.
 *
 * SPIFI includes caching of prevously-accessed data to improve performance. Software can write an address to this
 * function, to prevent such caching at and above the address.
 *
 * @param base     SPIFI peripheral base address.
 * @param val     Zero-based upper limit of cacheable memory.
 */
static inline void SPIFI_SetCacheLimit(SPIFI_Type *base, uint32_t val)
{
    base->CLIMIT = val;
}

/*!
 * @brief Reset the command field of SPIFI.
 *
 * This function is used to abort the current command or memory mode.
 *
 * @param base     SPIFI peripheral base address.
 */
static inline void SPIFI_ResetCommand(SPIFI_Type *base)
{
    base->STAT = SPIFI_STAT_RESET_MASK;
    /* Wait for the RESET flag cleared by HW */
    while (base->STAT & SPIFI_STAT_RESET_MASK)
    {
    }
}

/*!
 * @brief Set SPIFI flash AHB read command.
 *
 * Call this function means SPIFI enters to memory mode, while users need to use command, a SPIFI_ResetCommand shall
 * be called.
 *
 * @param base     SPIFI peripheral base address.
 * @param cmd      SPIFI command structure pointer.
 */
void SPIFI_SetMemoryCommand(SPIFI_Type *base, spifi_command_t *cmd);

/*!
 * @brief Enable SPIFI interrupt.
 *
 * The interrupt is triggered only in command mode, and it means the command now is finished.
 *
 * @param base     SPIFI peripheral base address.
 * @param mask     SPIFI interrupt enable mask. It is a logic OR of members the
 *                 enumeration :: spifi_interrupt_enable_t
 */
static inline void SPIFI_EnableInterrupt(SPIFI_Type *base, uint32_t mask)
{
    base->CTRL |= mask;
}

/*!
 * @brief Disable SPIFI interrupt.
 *
 * The interrupt is triggered only in command mode, and it means the command now is finished.
 *
 * @param base     SPIFI peripheral base address.
 * @param mask     SPIFI interrupt enable mask. It is a logic OR of members the
 *                 enumeration :: spifi_interrupt_enable_t
 */
static inline void SPIFI_DisableInterrupt(SPIFI_Type *base, uint32_t mask)
{
    base->CTRL &= ~mask;
}

/*!
 * @name Status
 * @{
 */

/*!
 * @brief Get the status of all interrupt flags for SPIFI.
 *
 * @param base     SPIFI peripheral base address.
 * @return SPIFI flag status
 */
static inline uint32_t SPIFI_GetStatusFlag(SPIFI_Type *base)
{
    return base->STAT;
}

/* @}*/

/*!
 * @brief Enable or disable DMA request for SPIFI.
 *
 * @param base     SPIFI peripheral base address.
 * @param enable   True means enable DMA and false means disable DMA.
 */
static inline void SPIFI_EnableDMA(SPIFI_Type *base, bool enable)
{
    if (enable)
    {
        base->CTRL |= SPIFI_CTRL_DMAEN_MASK;
    }
    else
    {
        base->CTRL &= ~SPIFI_CTRL_DMAEN_MASK;
    }
}

/*!
 * @brief  Gets the SPIFI data register address.
 *
 * This API is used to provide a transfer address for the SPIFI DMA transfer configuration.
 *
 * @param base SPIFI base pointer
 * @return data register address
 */
static inline uint32_t SPIFI_GetDataRegisterAddress(SPIFI_Type *base)
{
    return (uint32_t)(&(base->DATA));
}

/*!
 * @brief Write a word data in address of SPIFI.
 *
 * Users can write a page or at least a word data into SPIFI address.
 *
 * @param base     SPIFI peripheral base address.
 * @param data     Data need be write.
 */
static inline void SPIFI_WriteData(SPIFI_Type *base, uint32_t data)
{
    base->DATA = data;
}

/*!
 * @brief Read data from serial flash.
 *
 * Users should notice before call this function, the data length field in command register shall larger
 * than 4, otherwise a hardfault will happen.
 *
 * @param base     SPIFI peripheral base address.
 * @return Data input from flash.
 */
static inline uint32_t SPIFI_ReadData(SPIFI_Type *base)
{
    return base->DATA;
}

/* @} */

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* _FSL_SPIFI_H_ */
