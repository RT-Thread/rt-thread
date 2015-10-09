/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
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
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
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
#if !defined (__FSL_QSPI_HAL_H__)
#define __FSL_QSPI_HAL_H__

#include <assert.h>
#include <stdbool.h>
#include "fsl_device_registers.h"
#if FSL_FEATURE_SOC_QuadSPIO_COUNT
/*!
 * @addtogroup qspi_hal
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief QSPI read data area, from IP FIFO or AHB buffer.*/
typedef enum _qspi_read_area
{
    kQspiReadAHB = 0x0,/*!< QSPI read from AHB buffer. */
    kQspiReadIP = 0x1 /*!< QSPI read from IP FIFO. */
} qspi_read_area_t;

/*! @brief QSPI buffer type  */
typedef enum _qspi_fifo
{
    kQspiTxFifo = 0x800U,
    kQspiRxFifo = 0x400U,
    kQspiAllFifo = 0xC00U
} qspi_fifo_t;

/*! @brief QSPI command sequence type */
typedef enum _qspi_command_seq
{
    kQspiIPSeq = 0x1U,
    kQspiBufferSeq = 0x100U,
    kQspiAllSeq = 0x101U
} qspi_command_seq_t;

/*! @brief QSPI transfer endianess*/
typedef enum _qspi_endianness
{
    kQspi64BigEndian = 0x0U,
    kQspi32LittleEndian = 0x1U,
    kQspi32BigEndian = 0x2U,
    kQspi64LittleEndian = 0x3U
} qspi_endianness_t;

/*! @brief QSPI flags */
typedef enum _qspi_flag
{
    kQspiDataLearningFail = 0x80000000U,
    kQspiTxBufferFill = 0x8000000U,
    kQspiTxBufferUnderrun = 0x4000000U,
    kQspiIllegalInstruction = 0x800000U,
    kQspiRxBufferOverflow = 0x20000U,
    kQspiRxBufferDrain = 0x10000U,
    kQspiAHBSequenceError = 0x8000U,
    kQspiAHBIllegalTransaction = 0x4000U,
    kQspiAHBIllegalBurstSize = 0x2000U,
    kQspiAHBBufferOverflow = 0x1000U,
    kQspiIPCommandUsageError = 0x800U,
    kQspiIPCommandTriggerDuringAHBAccess = 0x80U,
    kQspiIPCommandTriggerDuringIPAccess = 0x40U,
    kQspiIPCommandTriggerDuringAHBGrant = 0x10U,
    kQspiIPCommandTransactionFinished = 0x1U,
    kQspiFlagAll = 0x8C83F8D1U
} qspi_flag_t;

/*! @brief QSPI DMA request flag */
typedef enum _qspi_dma_flag
{
    kQspiTxBufferFillDmaFlag = 0x2000000U,
    kQspiRxBufferDrainDmaFlag = 0x200000U,
    kQspiAllDmaFlag = 0x2200000U
} qspi_dma_flag_t;

/*! @brief QSPI state bit */
typedef enum _qspi_state_bit
{
    kQspiDataLearningSamplePoint = 0xE0000000U,
    kQspiTxBufferFull = 0x8000000U,
    kQspiTxDMA = 0x4000000U,
    kQspiTxWatermark = 0x2000000U,
    kQspiTxBufferEnoughData = 0x1000000U,
    kQspiRxDMA = 0x800000U,
    kQspiRxBufferFull = 0x80000U,
    kQspiRxWatermark = 0x10000U,
    kQspiAHB3BufferFull = 0x4000U,
    kQspiAHB2BufferFull = 0x2000U,
    kQspiAHB1BufferFull = 0x1000U,
    kQspiAHB0BufferFull = 0x800U,
    kQspiAHB3BufferNotEmpty = 0x400U,
    kQspiAHB2BufferNotEmpty = 0x200U,
    kQspiAHB1BufferNotEmpty = 0x100U,
    kQspiAHB0BufferNotEmpty = 0x80U,
    kQspiAHBTransactionPending = 0x40U,
    kQspiAHBCommandPriorityGranted = 0x20U,
    kQspiAHBAccess = 0x4U,
    kQspiIPAccess = 0x2U,
    kQspiBusy = 0x1U,
    kQspiStateAll = 0xEF897FE7U
} qspi_state_bit_t;

/*! @brief Flash timing configuration. */
typedef struct QspiFlashTiming
{
    uint32_t dataHoldTime;
    uint32_t CSHoldTime;
    uint32_t CSSetupTime;
} qspi_flash_timing_t;

/*! @brief Serial flash size; if there is no such pad,  set to 0.*/
typedef struct QspiFlashSize
{
    uint32_t flashA1Size;
    uint32_t flashA2Size;
    uint32_t flashB1Size;
    uint32_t flashB2Size;
} qspi_sflash_size_t;

/*! @brief Phrase shift number for DQS mode. */
typedef enum _qspi_dqs_phrase_shift
{
    kQspiDQSNoPhraseShift = 0x0U,
    kQspiDQSPhraseShift45Degree = 0x1U,
    kQspiDQSPhraseShift90Degree = 0x2U,
    kQspiDQSPhraseShift135Degree = 0x3U
} qspi_dqs_phrase_shift_t;

/*! @brief DQS configure features*/
typedef struct QspiDQSConfig
{
    uint32_t portADelayTapNum;
    uint32_t portBDelayTapNum;
    qspi_dqs_phrase_shift_t shift;
    bool DQSClkInverse;
    bool DQSPadLoopback;
    bool DQSLoopback;
} qspi_dqs_config_t;

/*! @brief External flash configuration items*/
typedef struct QspiFlashConfig
{
    uint32_t flashA1Size; /*!< Flash A1 size */
    uint32_t flashA2Size; /*!< Flash A2 size */
    uint32_t flashB1Size; /*!< Flash B1 size */
    uint32_t flashB2Size; /*!< Flash B2 size */
    uint32_t lookuptable[FSL_FEATURE_QSPI_LUT_DEPTH]; /*!< Flash command in LUT */
    uint32_t dataHoldTime; /*!< Data line hold time. */
    uint32_t CSHoldTime; /*!< CS line hold time */
    uint32_t CSSetupTime; /*!< CS line setup time*/
    uint32_t cloumnspace; /*!< Column space size */
    uint32_t dataLearnValue;/*!< Data Learn value if enable data learn */
    qspi_endianness_t endian; /*!< Flash data endianess. */
    bool parallelmode; /*!< If enable parallel mode. */
    bool wordaddress; /*!< If enable word address.*/
    bool DQSEnable; /*!< If enable DQS mode. */
    qspi_dqs_config_t dqs_config; /*!< DQS configuration; If not supported, set to NULL */
    bool DDREnable; /*!< If enable DDR mode. */
    bool octalmode; /*!< If enable octal mode. */
} qspi_flash_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 *@brief Initializes the QSPI module.
 *
 * This function sets all QSPI registers to a known state.
 * @param base QSPI base address.
 */
void QSPI_HAL_Init(QuadSPI_Type * base);

/*!
 *@brief  Software reset for the QSPI.
 *
 * This function resets both AHB and serial flash domin. This function does not reset
 * the QSPI configuration registers.
 * @param base QSPI base address.
 */
void QSPI_HAL_SoftwareReset(QuadSPI_Type * base);

/*!
 *@brief Disables the QSPI module.
 *
 * @param base QSPI base address.
 */
static inline void QSPI_HAL_DisableModule(QuadSPI_Type * base)
{
    QuadSPI_BWR_MCR_MDIS(base, true);
}

/*!
 *@brief Enables the QSPI module.
 *
 * @param base QSPI base address.
 */
static inline void QSPI_HAL_EnableModule(QuadSPI_Type * base)
{
    QuadSPI_BWR_MCR_MDIS(base,false);
}

/*!
 *@brief Sets the QSPI SCLK frequency.
 *
 * The SCLK frequency controls the data transfer speed of the QSPI. This function sets the clock divide 
 * parameter in the QSPI.
 * @param base QSPI base address.
 * @param srcfreq QSPI sclk source frequency.
 * @param sclk SCLK frequency.
 */
static inline void QSPI_HAL_SetSCLK(QuadSPI_Type * base, uint32_t srcfreq, uint32_t sclk)
{
    QuadSPI_BWR_MCR_SCLKCFG(base, srcfreq/sclk - 1);
}

/*!
 *@brief Sets the QSPI SCLK frequency.
 *
 * The SCLK frequency controls the data transfer speed of the QSPI. This function sets the clock divide 
 * parameter in the QSPI.
 * @param base QSPI base address.
 * @param clockSrc QSPI source clock index.
 */
static inline void QSPI_HAL_SetClockSrc(QuadSPI_Type * base, uint32_t clockSrc)
{
    QuadSPI_WR_SOCCR(base,clockSrc);
}

/*!
 *@brief Enables/disables the QSPI DDR mode.
 *
 * @param base QSPI base address.
 * @param enable Enable or disable DDR mode.
 */
static inline void QSPI_HAL_SetDDRModeCmd(QuadSPI_Type * base, bool enable)
{
    QuadSPI_BWR_MCR_DDR_EN(base, enable);
}

/*!
 *@brief Sets the flash timing settings for the QSPI to meet.
 *
 * @param base QSPI base address.
 * @param TimingConfig Flash timing configuration.
 */
void QSPI_HAL_ConfigFlash(QuadSPI_Type * base, qspi_flash_config_t *config);

/*!
 * @brief Sets the QSPI buffer size.
 *
 * There are 4 QSPI AHB buffers. The size of each buffer can be set, but users should ensure that the size of
 * one buffer is no more than the overall size. There is no hardware check for this. 
 * @param base QSPI base address.
 * @param buffer_index Buffer index number.
 * @param size Buffer size bytes.
 */
void QSPI_HAL_SetAHBBufferSize(QuadSPI_Type * base, uint32_t buff_index, uint32_t size);

/*!@ brief Sets the master ID connected.
 *
 * There are 4 AHB buffers for QSPI. An AHB buffer can be accessed by one master except for the buffer3.
 * @param base QSPI base address.
 * @param buff_index AHB buffer index, it can be 0 ~3.
 * @param master_id AHB master id, it can be ARM core, DMA and so on.
 */
void QSPI_HAL_SetAHBBufferMaster(QuadSPI_Type * base, uint32_t buff_index, uint32_t master_id);

/*!@ brief Sets the AHB buffer 0 with high priority.
 *
 * There are 4 AHB buffers for QSPI. The buffer 0 can be used as the highest priority buffer, which means that it
 * delays access to other AHB buffers until accessing buffer0 is complete.
 * @param base QSPI base address.
 * @param enable True means enable high priority, false means disable.
 */
static inline void QSPI_HAL_SetBuf0HighPriority(QuadSPI_Type * base, bool enable)
{
    QuadSPI_BWR_BUF0CR_HP_EN(base,enable);
}

/*!@ brief Sets the AHB buffer 3 to be accessed by all masters.
 *
 * There are 4 AHB buffers for QSPI. Each buffer can be accessed by a master. If this feature is enabled, all masters which
 * have not been connected to AHB buffers can access the buffer3.
 * @param base QSPI base address.
 * @param enable True means enable all master feature, false means disable.
 */
static inline void QSPI_HAL_SetBuf3AllMaster(QuadSPI_Type * base, bool enable)
{
    QuadSPI_BWR_BUF3CR_ALLMST(base,enable);
}

/*!@ brief Sets endianess of the QSPI.
 *
 * @param base QSPI base address.
 * @param endian Endianess type for QSPI.
 */
static inline void QSPI_HAL_SetEndianness(QuadSPI_Type * base, qspi_endianness_t endian)
{
    QuadSPI_BWR_MCR_END_CFG(base,endian);
}

/*!@ brief Enables or disables parallel mode.
 *
 * @param base QSPI base address.
 * @param command Which kind of command need to be parallel mode.
 * @param enable True means enable, false means disable.
 */
void QSPI_HAL_SetParallelModeCmd(QuadSPI_Type * base, qspi_command_seq_t command, bool enable);

/*!@ brief Sets the LUT index for the IP command sequence. This function triggers an IP command.
 *
 * An IP command connects to a LUT index. While users set the LUT index, it triggers an IP command.
 * An application should ensure that a correct sequence is written in the LUT index.
 * @param base QSPI base address.
 * @param seq_index Sequence index for the IP command.
 */
static inline void QSPI_HAL_SetIPCommandSeqIndex(QuadSPI_Type * base, uint32_t seq_index)
{
    QuadSPI_BWR_IPCR_SEQID(base,seq_index);
}

/*!@brief Sets the data transfer size in bytes for the IP command.
 *
 * @param base QSPI base address
 * @param size Data transfer size in bytes.
 */
static inline void QSPI_HAL_SetIPCommandSize(QuadSPI_Type * base, uint32_t size)
{
    QuadSPI_BWR_IPCR_IDATSZ(base,size);
}

 /*!@ brief Sets  address data for the IP command sequence to use.
 *
 * An IP command connects to an LUT index. While users set the LUT index, it triggers an IP command.
 * An application should ensure that a correct sequence is written in the LUT index.
 * @param base QSPI base address.
 * @param seq_index Sequence index for the IP command.
 */
static inline void QSPI_HAL_SetIPCommandAddr(QuadSPI_Type * base,uint32_t addr)
{
    QuadSPI_WR_SFAR(base,addr);
}

/*!@ brief Sets the LUT index for the buffer command. This function triggers a buffer command.
 *
 * A buffer command connects to an LUT index. While users set the LUT index, it triggers a buffer command.
 * An application should ensure that a correct sequence is written in the LUT index.
 * @param base QSPI base address.
 * @param seq_index Sequence index for the buffer command.
 */
static inline void QSPI_HAL_SetBufferCommandSeqIndex(QuadSPI_Type * base,uint32_t seq_index)
{
    QuadSPI_BWR_BFGENCR_SEQID(base,seq_index);
}

/*!@ brief Clears the buffer FIFO status.
 *
 * This function resets the transmit/receive the FIFO pointer and the FIFO counter.
 * @param base QSPI base address.
 * @param buffer Which FIFO needs to be reset, TX, RX or both.
 */
void QSPI_HAL_ClearFifo(QuadSPI_Type * base, qspi_fifo_t fifo);

/*!@ brief Clears the command sequence for the IP/buffer command.
 *
 * This function can reset the command sequence.
 * @param base QSPI base address.
 * @param seq Which command sequence need to reset, IP command, buffer command or both.
 */
static inline void QSPI_HAL_ClearSeqId(QuadSPI_Type * base, qspi_command_seq_t seq)
{
    QuadSPI_WR_SPTRCLR(base, seq); /* Clear both IP and buffer pointer */
}

/*! @brief Unlocks the lookup table.
 *
 * The lookup table is a table for sequences of flash instructions. This function unlocks the lookup
 * table so that software can write new instructions.
 * @param base QSPI base address.
 */
void QSPI_HAL_UnlockLUT(QuadSPI_Type * base);

/*! @brief Locks the lookup table.
 *
 * Lookup table is a table for sequences of flash instructions. This function locks the lookup
 * table. Users cannot write to the lookup table after it is locked.
 * @param base QSPI base address.
 */
void QSPI_HAL_LockLUT(QuadSPI_Type * base);

/*! @brief Sets the serial flash command into the LUT.
 *
 * There are two instructions in each LUT register and 4 LUT registers make an LUT sequence, which
 * means a serial flash command.
 * @param base QSPI base address.
 * @param index LUT sequence index.
 * @param command Serial flash command.
 */
void QSPI_HAL_SetLUT(QuadSPI_Type * base, uint32_t index, uint32_t command);

/*! @brief Sets the receive buffer watermark to trigger an interrupt or the DMA request.
 *
 * @param base QSPI base address.
 * @param watermark Number of 4 bytes. 1 means 4 bytes, 2 means 8 bytes, and so on.
 */
static inline void QSPI_HAL_SetRxWatermark(QuadSPI_Type * base, uint32_t watermark)
{
    QuadSPI_BWR_RBCT_WMRK(base,watermark-1);
}

/*! @brief Sets the transmit buffer watermark to trigger an interrupt or the DMA request.
 *
 * @param base QSPI base address.
 * @param watermark Number of 4 bytes. 1 means 4 bytes, 2 means 8 bytes, and so on.
 */
static inline void QSPI_HAL_SetTxWatermark(QuadSPI_Type * base, uint32_t watermark)
{
    QuadSPI_BWR_TBCT_WMRK(base,watermark -1);
}

/*! @brief Enables/disables the QSPI interrupt. 
 *
 * @param base QSPI base address.
 * @param IntFlag Indicate which interrupt need to set. It can be a combination of qspi_flag_t.
 * @param enable True means enable interrupt, false means disable.
 */
void QSPI_HAL_SetIntCmd(QuadSPI_Type * base, uint32_t IntFlag, bool enable);

/*! @brief Enables/disables the QSPI DMA.
 *
 * @param base QSPI base address.
 * @param DmaFlag The DMA flag can only be the choice of the qspi_dma_flag_t.
 * @param enable True means enable DMA request, false means disable.
 */
void QSPI_HAL_SetDmaCmd(QuadSPI_Type * base, qspi_dma_flag_t DmaFlag, bool enable);

/*! @brief Clears the QSPI state flags.
 *
 * @param base QSPI base address.
 * @param flag QSPI flag type, it can be one of or combinations of qspi_flag_t.
 */
static inline void QSPI_HAL_ClearStateFlag(QuadSPI_Type * base, uint32_t flag)
{
    QuadSPI_WR_FR(base,flag);
}

/*! @brief Gets the QSPI state flags.
 *
 * @param base QSPI base address.
 * @param flag QSPI flag type, it can be one of or combinations of qspi_flag_t.
 */
static inline uint32_t QSPI_HAL_GetStateFlag(QuadSPI_Type * base, uint32_t flag)
{
    return QuadSPI_RD_FR(base) & flag;
}

/*! @brief Gets  the QSPI state.
 *
 * @param base QSPI base address.
 * @param state QSPI state type, it can be one of or combinations of qspi_state_bit_t.
 * @return State value. 
 */
static inline uint32_t QSPI_HAL_GetState(QuadSPI_Type * base, uint32_t state)
{
    return (QuadSPI_RD_SR(base) & state);
}

/*! @brief Gets data which have been into transmit FIFO in bytes.
 *
 * @param base QSPI base address.
 * @return Data Size in bytes, how many data have transferred into transmit FIFO. 
 */
static inline uint32_t QSPI_HAL_GetTransferBytes(QuadSPI_Type * base)
{
    return QuadSPI_BRD_TBSR_TRCTR(base) * 4;
}

/*! @brief Gets data which is still in transmit FIFO in bytes.
 *
 * @param base QSPI base address.
 * @return Data Size in bytes, how many data now still in transmit FIFO. 
 */
static inline uint32_t QSPI_HAL_GetTxFifoLevel(QuadSPI_Type * base)
{
    return QuadSPI_BRD_TBSR_TRBFL(base) * 4;
}

/*! @brief Gets data which have be removed from receive buffer/FIFO in bytes.
 *
 * @param base QSPI base address.
 * @return Data Size in bytes, how many data have removed form receive buffer/FIFO. 
 */
static inline uint32_t QSPI_HAL_GetReadBytes(QuadSPI_Type * base)
{
    return QuadSPI_BRD_RBSR_RDCTR(base) * 4;
}

/*! @brief Gets data which is still in receive buffer/FIFO in bytes.
 *
 * @param base QSPI base address.
 * @return Data Size in bytes, how many data now still in receive buffer/FIFO. 
 */
static inline uint32_t QSPI_HAL_GetRxFifoLevel(QuadSPI_Type * base)
{
    return QuadSPI_BRD_RBSR_RDBFL(base) * 4;
}

/*! @brief Gets the transmit FIFO address. This function gets the DMA transfer.
 *
 * @param base QSPI base address.
 */
static inline uint32_t QSPI_HAL_GetTxFifoAddr(QuadSPI_Type * base)
{
    return (uint32_t)(&QuadSPI_TBDR_REG(base));
}

/*! @brief Gets the receive buffer/FIFO address. This function is used in the DMA transfer.
 *
 * @param base QSPI base address.
 * @index Rx FIFO index.
 */
uint32_t QSPI_HAL_GetRxFifoAddr(QuadSPI_Type * base);

/*! @brief Set the area of Rx readout data.
 *
 * @param base QSPI base address.
 * @param area From IP bus register or AHB bus buffer. 
 */
static inline void QSPI_HAL_SetReadDataArea(QuadSPI_Type * base, qspi_read_area_t area)
{
    QuadSPI_BWR_RBCT_RXBRD(base, area);
}

/*! @brief Reads data to an address using a blocking method.
 *
 * This function is a blocking function. It waits until the buffer has data and then moves it out.
 * @param base QSPI base address.
 * @param addr Address which put data into.
 * @param size Data Size in bytes, how many data need to read out. It should be integrated divided by 4. 
 */
void QSPI_HAL_ReadDataBlocking(QuadSPI_Type * base, uint32_t * addr, uint32_t size);


/*! @brief Reads data out.
 *
 * This function is a non-blocking function. Software should ensure that there is valid data in the index.
 * @param base QSPI base address.
 * @param index Rx buffer/FIFO index which data located.
 * @return Data in that index. 
 */
uint32_t QSPI_HAL_ReadData(QuadSPI_Type * base, uint32_t index);

/*! @brief Writes a data series to the QSPI transmit FIFO using a blocking method.
 *
 * This function is a blocking function. It waits until there is space in the transmit FIFO to write data in.
 * @param base QSPI base address.
 * @param addr Source data address.
 * @param size Data Size in bytes, how many data need to write. It should be integrated divided by 4. 
 */
void QSPI_HAL_WriteDataBlocking(QuadSPI_Type * base, uint32_t * addr, uint32_t size);

/*! @brief Writes data into the transmit FIFO.
 *
 * This function is a non-blocking function. Software should ensure that there is space in the transmit FIFO.
 * @param base QSPI base address.
 * @param data Which data need to be write in. 
 */
static inline void QSPI_HAL_WriteData(QuadSPI_Type * base, uint32_t data)
{
    QuadSPI_WR_TBDR(base, data);
}

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif
#endif /* __FSL_QSPI_HAL_H__ */

