/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
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
#if !defined(__FSL_SPI_HAL_H__)
#define __FSL_SPI_HAL_H__

#include "fsl_device_registers.h"
#include <stdint.h>
#include <stdbool.h>

#if FSL_FEATURE_SOC_SPI_COUNT

/*! @addtogroup spi_hal*/
/*! @{*/

/*! @file*/

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Error codes for the SPI driver.*/
typedef enum _spi_errors
{
    kStatus_SPI_Success = 0,
    kStatus_SPI_SlaveTxUnderrun,        /*!< SPI Slave TX Underrun error.*/
    kStatus_SPI_SlaveRxOverrun,         /*!< SPI Slave RX Overrun error.*/
    kStatus_SPI_Timeout,                /*!< SPI transfer timed out.*/
    kStatus_SPI_Busy,                   /*!< SPI instance is already busy performing a transfer.*/
    kStatus_SPI_NoTransferInProgress,   /*!< Attempt to abort a transfer when no transfer
                                             was in progress.*/
    kStatus_SPI_OutOfRange,             /*!< SPI out-of-range error used in slave callback */
    kStatus_SPI_TxBufferNotEmpty,       /*!< SPI TX buffer register is not empty */
    kStatus_SPI_InvalidParameter,       /*!< Parameter is invalid */
    kStatus_SPI_NonInit,                /*!< SPI driver is not initialized */
    kStatus_SPI_AlreadyInitialized,     /*!< SPI driver already initialized */
    kStatus_SPI_DMAChannelInvalid,      /*!< SPI driver cannot requests DMA channel */
    kStatus_SPI_Error,                  /*!< SPI driver error */
} spi_status_t;

/*! @brief SPI master or slave configuration.*/
typedef enum _spi_master_slave_mode {
    kSpiMaster = 1,     /*!< SPI peripheral operates in master mode.*/
    kSpiSlave = 0       /*!< SPI peripheral operates in slave mode.*/
} spi_master_slave_mode_t;

/*! @brief SPI clock polarity configuration.*/
typedef enum _spi_clock_polarity {
    kSpiClockPolarity_ActiveHigh = 0,   /*!< Active-high SPI clock (idles low). @internal gui name="Active high" */
    kSpiClockPolarity_ActiveLow = 1     /*!< Active-low SPI clock (idles high).@internal gui name="Active low" */
} spi_clock_polarity_t;

/*! @brief SPI clock phase configuration.*/
typedef enum _spi_clock_phase {
    kSpiClockPhase_FirstEdge = 0,       /*!< First edge on SPSCK occurs at the middle of the first
                                         *   cycle of a data transfer. @internal gui name="First edge" */
    kSpiClockPhase_SecondEdge = 1       /*!< First edge on SPSCK occurs at the start of the
                                         *   first cycle of a data transfer.@internal gui name="Second edge" */
} spi_clock_phase_t;

/*! @brief SPI data shifter direction options.*/
typedef enum _spi_shift_direction {
    kSpiMsbFirst = 0,    /*!< Data transfers start with most significant bit. @internal gui name="Msb first" */
    kSpiLsbFirst = 1    /*!< Data transfers start with least significant bit. @internal gui name="Lsb first" */
} spi_shift_direction_t;

/*! @brief SPI slave select output mode options.*/
typedef enum _spi_ss_output_mode {
    kSpiSlaveSelect_AsGpio = 0,         /*!< Slave select pin configured as GPIO.*/
    kSpiSlaveSelect_FaultInput = 2,     /*!< Slave select pin configured for fault detection.*/
    kSpiSlaveSelect_AutomaticOutput = 3 /*!< Slave select pin configured for automatic SPI output.*/
} spi_ss_output_mode_t;

/*! @brief SPI pin mode options.*/
typedef enum _spi_pin_mode {
    kSpiPinMode_Normal = 0,     /*!< Pins operate in normal, single-direction mode.*/
    kSpiPinMode_Input = 1,      /*!< Bidirectional mode. Master: MOSI pin is input;
                                 *   Slave: MISO pin is input*/
    kSpiPinMode_Output = 3      /*!< Bidirectional mode. Master: MOSI pin is output;
                                 *   Slave: MISO pin is output*/
} spi_pin_mode_t;

/*! @brief SPI data length mode options.*/
typedef enum _spi_data_bitcount_mode  {
    kSpi8BitMode = 0,  /*!< 8-bit data transmission mode @internal gui name="8-bit" */
    kSpi16BitMode = 1, /*!< 16-bit data transmission mode @internal gui name="16-bit" */
} spi_data_bitcount_mode_t;

/*! @brief SPI interrupt sources.*/
typedef enum _spi_interrupt_source  {
    kSpiRxFullAndModfInt = 1, /*!< Receive buffer full (SPRF) and mode fault (MODF) interrupt */
    kSpiTxEmptyInt = 2,       /*!< Transmit buffer empty interrupt */
    kSpiMatchInt = 3,         /*!< Match interrupt */
} spi_interrupt_source_t;

/*! @brief SPI interrupt status flags.*/
typedef enum _spi_int_status_flag  {
    kSpiRxBufferFullFlag = SPI_S_SPRF_SHIFT,   /*!< Read buffer full flag */
    kSpiMatchFlag = SPI_S_SPMF_SHIFT,          /*!< Match flag */
    kSpiTxBufferEmptyFlag = SPI_S_SPTEF_SHIFT, /*!< Transmit buffer empty flag */
    kSpiModeFaultFlag = SPI_S_MODF_SHIFT,      /*!< Mode fault flag */
} spi_int_status_flag_t ;

/*! @brief SPI FIFO interrupt sources.*/
typedef enum _spi_fifo_interrupt_source  {
    kSpiRxFifoNearFullInt = 1, /*!< Receive FIFO nearly full interrupt */
    kSpiTxFifoNearEmptyInt = 2,  /*!< Transmit FIFO nearly empty interrupt */
} spi_fifo_interrupt_source_t ;

/*! @brief SPI FIFO write-1-to-clear interrupt flags.*/
typedef enum _spi_w1c_interrupt {
    kSpiRxFifoFullClearInt = 0, /*!< Receive FIFO full interrupt */
    kSpiTxFifoEmptyClearInt = 1, /*!< Transmit FIFO empty interrupt */
    kSpiRxNearFullClearInt = 2, /*!< Receive FIFO nearly full interrupt */
    kSpiTxNearEmptyClearInt = 3, /*!< Transmit FIFO nearly empty interrupt */
} spi_w1c_interrupt_t;

/*! @brief SPI TX FIFO watermark settings.*/
typedef enum _spi_txfifo_watermark {
    kSpiTxFifoOneFourthEmpty = 0,
    kSpiTxFifoOneHalfEmpty = 1
} spi_txfifo_watermark_t;

/*! @brief SPI RX FIFO watermark settings.*/
typedef enum _spi_rxfifo_watermark {
    kSpiRxFifoThreeFourthsFull = 0,
    kSpiRxFifoOneHalfFull = 1
} spi_rxfifo_watermark_t;

/*! @brief SPI status flags.*/
typedef enum _spi_fifo_status_flag {
    kSpiRxFifoEmpty = 0,
    kSpiTxFifoFull = 1,
    kSpiTxNearEmpty = 2,
    kSpiRxNearFull = 3
} spi_fifo_status_flag_t;

/*! @brief SPI error flags.*/
typedef enum _spi_fifo_error_flag {
    kSpiNoFifoError = 0,  /*!< No error is detected */
    kSpiRxfof = 1, /*!< Receive FIFO Overflow */
    kSpiTxfof = 2, /*!< Transmit FIFO Overflow */
    kSpiRxfofTxfof = 3, /*!< Receive FIFO Overflow, Transmit FIFO Overflow */
    kSpiRxferr = 4,  /*!< Receive FIFO Error */
    kSpiRxfofRxferr = 5, /*!< Receive FIFO Overflow, Receive FIFO Error */
    kSpiTxfofRxferr = 6, /*!< Transmit FIFO Overflow, Receive FIFO Error */
    kSpiRxfofTxfofRxferr = 7,  /*!< Receive FIFO Overflow, Transmit FIFO Overflow, Receive FIFO Error */
    kSpiTxferr = 8, /*!< Transmit FIFO Error */
    kSpiRxfofTxferr = 9, /*!< Receive FIFO Overflow, Transmit FIFO Error */
    kSpiTxfofTxferr = 10, /*!< Transmit FIFO Overflow, Transmit FIFO Error */
    kSpiRxfofTxfofTxferr = 11, /*!< Receive FIFO Overflow, Transmit FIFO Overflow, Transmit FIFO Error */
    kSpiRxferrTxferr = 12, /*!< Receive FIFO Error, Transmit FIFO Error */
    kSpiRxfofRxferrTxferr = 13, /*!< Receive FIFO Overflow, Receive FIFO Error, Transmit FIFO Error */
    kSpiTxfofRxferrTxferr = 14, /*!< Transmit FIFO Overflow, Receive FIFO Error, Transmit FIFO Error */
    kSpiRxfofTxfofRxferrTxferr =15 /*!< Receive FIFO Overflow, Transmit FIFO Overflow
                                    * Receive FIFO Error, Transmit FIFO Error */
} spi_fifo_error_flag_t;

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Configuration
 * @{
 */

/*!
 * @brief Restores the SPI to the reset configuration.
 *
 * This function basically resets all of the SPI registers to their default setting including
 * disabling the module.
 *
 * @param base Module base pointer of type SPI_Type.
 */
void SPI_HAL_Init(SPI_Type * base);

/*!
 * @brief Enables the SPI peripheral.
 *
 * @param base Module base pointer of type SPI_Type.
 */
static inline void SPI_HAL_Enable(SPI_Type * base)
{
    SPI_BWR_C1_SPE(base, 1);
}

/*!
 * @brief Disables the SPI peripheral.
 *
 * @param base Module base pointer of type SPI_Type.
 */
static inline void SPI_HAL_Disable(SPI_Type * base)
{
    SPI_BWR_C1_SPE(base, 0);
}

/*!
 * @brief Sets the SPI baud rate in bits per second.
 *
 * This function takes in the desired bitsPerSec (baud rate) and calculates the nearest
 * possible baud rate without exceeding the desired baud rate unless the baud rate requested is
 * less than the absolute minimum in which case the minimum baud rate is returned. The returned
 * baud rate is in bits-per-second. It requires that the caller also provide the frequency of the
 * module source clock (in Hertz).
 *
 * @param base Module base pointer of type SPI_Type.
 * @param bitsPerSec The desired baud rate in bits per second.
 * @param sourceClockInHz Module source input clock in Hertz.
 * @return  The actual calculated baud rate in Hz.
 */
uint32_t SPI_HAL_SetBaud(SPI_Type * base, uint32_t bitsPerSec, uint32_t sourceClockInHz);

/*!
 * @brief Configures the baud rate divisors manually.
 *
 * This function allows the caller to manually set the baud rate divisors in the event that
 * these dividers are known and the caller does not wish to call the SPI_HAL_SetBaudRate function.
 *
 * @param base Module base pointer of type SPI_Type.
 * @param prescaleDivisor baud rate prescale divisor setting.
 * @param rateDivisor baud rate divisor setting.
 */
static inline void SPI_HAL_SetBaudDivisors(SPI_Type * base, uint32_t prescaleDivisor,
                                            uint32_t rateDivisor)
{
    SPI_WR_BR(base, SPI_BR_SPR(rateDivisor) | SPI_BR_SPPR(prescaleDivisor));
}

/*!
 * @brief Configures the SPI for master or slave.
 *
 * @param base Module base pointer of type SPI_Type.
 * @param mode Mode setting (master or slave) of type dspi_master_slave_mode_t.
 */
static inline void SPI_HAL_SetMasterSlave(SPI_Type * base, spi_master_slave_mode_t mode)
{
    SPI_BWR_C1_MSTR(base, (uint32_t)mode);
}

/*!
 * @brief Returns whether the SPI module is in master mode.
 *
 * @param base Module base pointer of type SPI_Type.
 * @return true The module is in master mode.
 *         false The module is in slave mode.
 */
static inline bool SPI_HAL_IsMaster(SPI_Type * base)
{
    return (bool)SPI_RD_C1_MSTR(base);
}

/*!
 * @brief Sets how the slave select output operates.
 *
 * This function allows the user to configure the slave select in one of the three operational
 * modes: as GPIO, as a fault input, or as an automatic output for standard SPI modes.
 *
 * @param base Module base pointer of type SPI_Type.
 * @param mode Selection input of one of three modes of type spi_ss_output_mode_t.
 */
void SPI_HAL_SetSlaveSelectOutputMode(SPI_Type * base, spi_ss_output_mode_t mode);

/*!
 * @brief Sets the polarity, phase, and shift direction.
 *
 * This function configures the clock polarity, clock phase, and data shift direction.
 *
 * @param base Module base pointer of type SPI_Type.
 * @param polarity Clock polarity setting of type spi_clock_polarity_t.
 * @param phase Clock phase setting of type spi_clock_phase_t.
 * @param direction Data shift direction (MSB or LSB) of type spi_shift_direction_t.
 */
void SPI_HAL_SetDataFormat(SPI_Type * base,
    spi_clock_polarity_t polarity,
    spi_clock_phase_t phase,
    spi_shift_direction_t direction);


#if FSL_FEATURE_SPI_16BIT_TRANSFERS

/*!
 * @brief Sets the SPI data length to 8-bit or 16-bit.
 *
 * This function configures the SPI data length to 8-bit or 16-bit.
 *
 * @param base Module base pointer of type SPI_Type.
 * @param mode The SPI data length (8- or 16-bit) of type spi_data_bitcount_t.
 */
static inline void SPI_HAL_Set8or16BitMode(SPI_Type * base, spi_data_bitcount_mode_t mode)
{
    SPI_BWR_C2_SPIMODE(base, (uint32_t)mode);
}

/*!
 * @brief Gets the SPI data length to 8-bit or 16-bit.
 *
 * This function gets the SPI data length (8-bit or 16-bit) configuration.
 *
 * @param base Module base pointer of type SPI_Type.
 * @return The SPI data length (8- or 16-bit) setting of type spi_data_bitcount_t.
 */
static inline spi_data_bitcount_mode_t SPI_HAL_Get8or16BitMode(SPI_Type * base)
{
    return (spi_data_bitcount_mode_t)SPI_RD_C2_SPIMODE(base);
}

/*!
 * @brief Gets the SPI data register address for DMA operation.
 *
 * This function gets the SPI data register address as this value is needed for
 * DMA operation.  In the case of 16-bit transfers, return the SPI_DL as SPI_DH is
 * implied for 16-bit accesses.
 *
 * @param base Module base pointer of type SPI_Type.
 * @return The SPI data data register address.
 */
static inline uint32_t SPI_HAL_GetDataRegAddr(SPI_Type * base)
{
    return (uint32_t)(&SPI_DL_REG(base));
}

#else

/*!
 * @brief Gets the SPI data register address for DMA operation.
 *
 * This function gets the SPI data register address as this value is needed for
 * DMA operation.
 *
 * @param base Module base pointer of type SPI_Type.
 * @return The SPI data register address.
 */
static inline uint32_t SPI_HAL_GetDataRegAddr(SPI_Type * base)
{
    return (uint32_t)(&SPI_D_REG(base));
}

#endif

/*!
 * @brief Sets the SPI pin mode.
 *
 * This function configures the SPI data pins to one of three modes (of type spi_pin_mode_t):
 * Single direction mode: MOSI and MISO pins operate in normal, single direction mode.
 * Bidirectional mode: Master: MOSI configured as input, Slave: MISO configured as input.
 * Bidirectional mode: Master: MOSI configured as output, Slave: MISO configured as output.
 *
 * @param base Module base pointer of type SPI_Type.
 * @param mode Operational of SPI pins of type spi_pin_mode_t.
 */
void SPI_HAL_SetPinMode(SPI_Type * base, spi_pin_mode_t mode);

/*@}*/

/*!
 * @name DMA
 * @{
 */
#if FSL_FEATURE_SPI_HAS_DMA_SUPPORT
/*!
 * @brief Configures the transmit DMA request.
 *
 * This function enables or disables the SPI transmit DMA request.  When the transmit DMA is enabled
 * it disables the transmit interrupt.
 *
 * @param base Module base pointer of type SPI_Type.
 * @param enableTransmit Enable (true) or disable (false) the transmit DMA request.
 */
static inline void SPI_HAL_SetTxDmaCmd(SPI_Type * base, bool enableTransmit)
{
    SPI_BWR_C2_TXDMAE(base, (enableTransmit == true));
}

/*!
 * @brief Configures the receive DMA requests.
 *
 * This function enables or disables the SPI receive DMA request.  When the receive DMA is enabled
 * it disables the receive interrupt.
 *
 * @param base Module base pointer of type SPI_Type.
 * @param enableReceive Enable (true) or disable (false) the receive DMA request.
 */
static inline void SPI_HAL_SetRxDmaCmd(SPI_Type * base, bool enableReceive)
{
    SPI_BWR_C2_RXDMAE(base, (enableReceive == true));
}
#endif
/*@}*/

/*!
 * @name Interrupts
 * @{
 */

/*!
 * @brief Enables or disables the SPI interrupts.
 *
 * This function enables or disables the
 * SPI receive buffer (or FIFO if the module supports a FIFO) full and mode fault interrupt,
 * SPI transmit buffer (or FIFO if the module supports a FIFO) empty interrupt, and the
 * SPI match interrupt.
 *
 * Example, to set the receive and mode fault interrupt:
 * SPI_HAL_SetIntMode(base, kSpiRxFullAndModfInt, true);
 *
 * @param base Module base pointer of type SPI_Type.
 * @param interrupt SPI interrupt source to configure of type spi_interrupt_source_t.
 * @param enable Enable (true) or disable (false) the receive buffer full and mode fault interrupt.
 */
void SPI_HAL_SetIntMode(SPI_Type * base, spi_interrupt_source_t interrupt, bool enable);

/*!
 * @brief Enables or disables the SPI receive buffer/FIFO full and mode fault interrupt.
 *
 * This function enables or disables the SPI receive buffer (or FIFO if the module supports a
 * FIFO) full and mode fault interrupt.
 *
 * @param base Module base pointer of type SPI_Type.
 * @param enable Enable (true) or disable (false) the receive buffer full and mode fault interrupt.
 */
static inline void SPI_HAL_SetReceiveAndFaultIntCmd(SPI_Type * base, bool enable)
{
    SPI_BWR_C1_SPIE(base, (enable == true));
}

/*!
 * @brief Enables or disables the SPI transmit buffer/FIFO empty interrupt.
 *
 * This function enables or disables the SPI transmit buffer (or FIFO if the module supports a
 * FIFO) empty interrupt.
 *
 * @param base Module base pointer of type SPI_Type.
 * @param enable Enable (true) or disable (false) the transmit buffer empty interrupt.
 */
static inline void SPI_HAL_SetTransmitIntCmd(SPI_Type * base, bool enable)
{
    SPI_BWR_C1_SPTIE(base, (enable == true));
}

/*!
 * @brief Enables or disables the SPI match interrupt.
 *
 * This function enables or disables the SPI match interrupt.
 *
 * @param base Module base pointer of type SPI_Type.
 * @param enable Enable (true) or disable (false) the match interrupt.
 */
static inline void SPI_HAL_SetMatchIntCmd(SPI_Type * base, bool enable)
{
    SPI_BWR_C2_SPMIE(base, (enable == true));
}

/*@}*/

/*!
 * @name Status
 * @{
 */

/*!
 * @brief Gets the SPI interrupt status flag state..
 *
 * This function returns the state (set or cleared) of the SPI interrupt status flag.
 *
 * @param base Module base pointer of type SPI_Type.
 * @param flag The requested interrupt status flag of type spi_int_status_flag_t.
 * @return Current setting of the requested interrupt status flag.
 */
static inline bool SPI_HAL_GetIntStatusFlag(SPI_Type * base, spi_int_status_flag_t flag)
{
    return (SPI_RD_S(base) >> flag) & 1U;
}

/*!
 * @brief Checks whether the read buffer/FIFO is full.
 *
 * The read buffer (or FIFO if the module supports a FIFO) full flag is only cleared by reading
 * it when it is set, then reading the data register by calling the SPI_HAL_ReadData().
 * This example code demonstrates how to check the flag, read data, and clear the flag.
   @code
        // Check read buffer flag.
        if (SPI_HAL_IsReadBuffFullPending(base))
        {
            // Read the data in the buffer, which also clears the flag.
            byte = SPI_HAL_ReadData(base);
        }
   @endcode
 *
 * @param base Module base pointer of type SPI_Type.
 * @return Current setting of the read buffer full flag.
 */
static inline bool SPI_HAL_IsReadBuffFullPending(SPI_Type * base)
{
    return SPI_RD_S_SPRF(base);
}

/*!
 * @brief Checks whether the transmit buffer/FIFO is empty.
 *
 * To clear the transmit buffer (or FIFO if the module supports a FIFO) empty flag,
 * read the flag when it is set. Then, write a new data value into the transmit buffer with a call
 * to the SPI_HAL_WriteData(). The example code shows how to do this.
   @code
        // Check if transmit buffer is empty.
        if (SPI_HAL_IsTxBuffEmptyPending(base))
        {
            // Buffer has room, so write the next data value.
            SPI_HAL_WriteData(base, byte);
        }
   @endcode
 *
 * @param base Module base pointer of type SPI_Type.
 * @return Current setting of the transmit buffer empty flag.
 */
static inline bool SPI_HAL_IsTxBuffEmptyPending(SPI_Type * base)
{
    return SPI_RD_S_SPTEF(base);
}

/*!
 * @brief Checks whether a mode fault occurred.
 *
 * @param base Module base pointer of type SPI_Type.
 * @return Current setting of the mode fault flag.
 */
static inline bool SPI_HAL_IsModeFaultPending(SPI_Type * base)
{
    return SPI_RD_S_MODF(base);
}

/*!
 * @brief Clears the mode fault flag.
 *
 * @param base Module base pointer of type SPI_Type
 */
void SPI_HAL_ClearModeFaultFlag(SPI_Type * base);

/*!
 * @brief Checks whether the data received matches the previously-set match value.
 *
 * @param base Module base pointer of type SPI_Type.
 * @return Current setting of the match flag.
 */
static inline bool SPI_HAL_IsMatchPending(SPI_Type * base)
{
    return SPI_RD_S_SPMF(base);
}

/*!
 * @brief Clears the match flag.
 *
 * @param base Module base pointer of type SPI_Type.
 */
void SPI_HAL_ClearMatchFlag(SPI_Type * base);

/*@}*/

/*!
 * @name Data transfer
 *@{
 */

#if FSL_FEATURE_SPI_16BIT_TRANSFERS

/*!
 * @brief Reads a byte from the high (upper 8-bits) data buffer.
 *
 * @param base Module base pointer of type SPI_Type.
 * @return The data read from the upper 8-bit data buffer.
 */
static inline uint8_t SPI_HAL_ReadDataHigh(SPI_Type * base)
{
    return SPI_RD_DH(base);
}

/*!
 * @brief Reads a byte from the low (lower 8-bits) data buffer.
 *
 * @param base Module base pointer of type SPI_Type.
 * @return The data read from the lower 8-bit data buffer.
 */
static inline uint8_t SPI_HAL_ReadDataLow(SPI_Type * base)
{
    return SPI_RD_DL(base);
}

/*!
 * @brief Writes a byte into the high (upper 8-bits) data buffer.
 *
 * @param base Module base pointer of type SPI_Type.
 * @param data The data to send, upper 8-bits.
 */
static inline void SPI_HAL_WriteDataHigh(SPI_Type * base, uint8_t data)
{
    SPI_WR_DH(base, data);
}

/*!
 * @brief Writes a byte into the low (lower 8-bits) data buffer.
 *
 * @param base Module base pointer of type SPI_Type.
 * @param data The data to send, lower 8-bits.
 */
static inline void SPI_HAL_WriteDataLow(SPI_Type * base, uint8_t data)
{
    SPI_WR_DL(base, data);
}

/*!
 * @brief Writes a byte into the data buffer and waits till complete to return.
 *
 * This function writes data to the SPI data registers and waits until the
 * transmit is empty to return.  For 16-bit data, the lower byte is written to dataLow while
 * the upper byte is written to dataHigh.  The parameter bitCount is used to
 * distinguish between 8- and 16-bit writes.
 *
 * Note, for 16-bit data writes, make sure that function SPI_HAL_Set8or16BitMode is set to
 * kSpi16BitMode.
 *
 * @param base Module base pointer of type SPI_Type.
 * @param bitCount the number of data bits to send, 8 or 16, of type spi_data_bitcount_mode_t.
 * @param dataHigh The upper 8-bit data to send, set to 0 if only sending 8-bits.
 * @param dataLow The lower 8-bit data to send, if only sending 8-bits, then use this parameter.
 */
void SPI_HAL_WriteDataBlocking(SPI_Type * base, spi_data_bitcount_mode_t bitCount,
                               uint8_t dataHigh, uint8_t dataLow);

#else

/*!
 * @brief Reads a byte from the data buffer.
 *
 * @param base Module base pointer of type SPI_Type.
 * @return The data read from the data buffer.
 */
static inline uint8_t SPI_HAL_ReadData(SPI_Type * base)
{
    return SPI_RD_D(base);
}

/*!
 * @brief Writes a byte into the data buffer.
 *
 * @param base Module base pointer of type SPI_Type.
 * @param data The data to send.
 */
static inline void SPI_HAL_WriteData(SPI_Type * base, uint8_t data)
{
    SPI_WR_D(base, data);
}

/*!
 * @brief Writes a byte into the data buffer and waits till complete to return.
 *
 * This function writes data to the SPI data register and waits until the
 * TX is empty to return.
 *
 * @param base Module base pointer of type SPI_Type.
 * @param data The data to send.
 */
void SPI_HAL_WriteDataBlocking(SPI_Type * base, uint8_t data);

#endif

/*@}*/

/*! @name Match byte*/
/*@{*/

#if FSL_FEATURE_SPI_16BIT_TRANSFERS
/*!
 * @brief Sets the upper 8-bit value which triggers the match interrupt.
 *
 * @param base Module base pointer of type SPI_Type.
 * @param matchByte The upper 8-bit value which triggers the match interrupt.
 */
static inline void SPI_HAL_SetMatchValueHigh(SPI_Type * base, uint8_t matchByte)
{
    SPI_WR_MH(base, matchByte);
}

/*!
 * @brief Sets the lower 8-bit value which triggers the match interrupt.
 *
 * @param base Module base pointer of type SPI_Type.
 * @param matchByte The lower 8-bit value which triggers the match interrupt.
 */
static inline void SPI_HAL_SetMatchValueLow(SPI_Type * base, uint8_t matchByte)
{
    SPI_WR_ML(base, matchByte);
}
#else
/*!
 * @brief Sets the value which triggers the match interrupt.
 *
 * @param base Module base pointer of type SPI_Type.
 * @param matchByte The value which triggers the match interrupt.
 */
static inline void SPI_HAL_SetMatchValue(SPI_Type * base, uint8_t matchByte)
{
    SPI_WR_M(base, matchByte);
}
#endif

/*@}*/

#if FSL_FEATURE_SPI_FIFO_SIZE
/*!
 * @name FIFO support
 *@{
 */

/*!
 * @brief Enables or disables the SPI write-1-to-clear interrupt clearing mechanism.
 *
 * This function enables or disables the SPI write-1-to-clear interrupt clearing mechanism.
 * When enabled, it allows the user to clear certain interrupts using bit writes.
 *
 * @param base Module base pointer of type SPI_Type.
 * @param enable Enable (true) or disable (false) the write-1-to-clear interrupt clearing mechanism.
 */
static inline void SPI_HAL_SetIntClearCmd(SPI_Type * base, bool enable)
{
    SPI_BWR_C3_INTCLR(base, (enable == true));
}

/*!
 * @brief Enables or disables the SPI FIFO and configures the transmit/receive FIFO watermarks.
 *
 * This all-in-one function does the following:
 * Configures the TX FIFO empty watermark to be 16bits (1/4) or 32bits (1/2)
 * Configures the RX FIFO full watermark to be 48bits (3/4) or 32bits (1/2)
 * Enables/disables the FIFO
 *
 * @param base Module base pointer of type SPI_Type.
 * @param enable Enable (true) or disable (false) the FIFO.
 * @param txWaterMark The TX watermark setting of type spi_txfifo_watermark_t.
 * @param rxWaterMark The RX watermark setting of type spi_rxfifo_watermark_t.
 */
void SPI_HAL_SetFifoMode(SPI_Type * base, bool enable,
                         spi_txfifo_watermark_t txWaterMark,
                         spi_rxfifo_watermark_t rxWaterMark);

/*!
 * @brief Returns the setting of the SPI FIFO mode (enable or disable).
 *
 * This function returns the setting of the SPI FIFO mode (enable or disable).
 *
 * @param base Module base address.
 * @return The setting, enable (true) or disable (false), of the FIFO mode.
 */
static inline bool SPI_HAL_GetFifoCmd(SPI_Type * base)
{
    return SPI_RD_C3_FIFOMODE(base);
}

/*!
 * @brief Enables or disables the SPI FIFO specific interrupts.
 *
 * This function enables or disables the SPI FIFO interrupts.  These FIFO interrupts are the transmit
 * FIFO nearly empty and the RX FIFO nearly full.  Note, there are separate HAL functions
 * to enable/disable receive buffer/FIFO full interrupt and the transmit buffer/FIFO empty
 * interrupt.
 *
 * @param base Module base pointer of type SPI_Type.
 * @param intSrc The FIFO interrupt source of type spi_fifo_interrupt_source_t.
 * @param enable Enable (true) or disable (false) the specific FIFO interrupt.
 */
void SPI_HAL_SetFifoIntCmd(SPI_Type * base, spi_fifo_interrupt_source_t intSrc,
                                         bool enable);

/*!
 * @brief Clears the FIFO related interrupt sources using write-1-to-clear feature.
 *
 * This function allows the user to clear particular FIFO interrupt sources using the
 * write-1-to-clear feature. The function first determines if SPIx_C3[INTCLR] is enabled
 * as needs to first be set in order to enable the write to clear mode. If not enabled, the
 * function enables this bit, performs the interrupt source clear, then disables the write to
 * clear mode.  The FIFO related interrupt sources that can be cleared using this function are:
 * Receive FIFO full interrupt
 * Receive FIFO nearly full interrupt
 * Transmit FIFO empty interrupt
 * Transmit FIFO nearly empty interrupt
 *
 * @param base Module base pointer of type SPI_Type.
 * @param intSrc The FIFO interrupt source to clear of type spi_w1c_interrupt_t.
 */
void SPI_HAL_ClearFifoIntUsingBitWrite(SPI_Type * base, spi_w1c_interrupt_t intSrc);

/*!
 * @brief Returns the desired FIFO related status flag.
 *
 * This function allows the user to ascertain the state of a FIFO related status flag. The user
 * passes in the desired status flag and the function returns its current value.
 * The status flags are as follows:
 *  Rx Fifo Empty
 *  Tx Fifo Full
 *  Tx Near Empty (based on SPI_C3[TNEAREF_MARK] setting)
 *  Rx Near Full (based on SPI_C3[RNFULLF_MARK] setting)
 *
 * @param base Module base pointer of type SPI_Type.
 * @param status The FIFO related status flag of type spi_fifo_status_flag_t.
 * @return Current setting of the desired status flag.
 */
static inline bool SPI_HAL_GetFifoStatusFlag(SPI_Type * base, spi_fifo_status_flag_t status)
{
    return ((SPI_RD_S(base) >> status) & 0x1U);
}

/*!
 * @brief Returns the FIFO related error flags.
 *
 * This function returns the consummate value of all four FIFO error flags.
 * Note that simply reading the SPI_CI register clears all of the error flags that are set.
 * Hence it is important to read them all at once and return the consummate value.
 * This consummate value is typecast as type spi_fifo_error_flag_t and provides the details
 * of which flags are set.
 * The combination of error flags are as follows:
 *  Rx FIFO Overflow
 *  Tx FIFO Overflow
 *  Rx FIFO Error
 *  Tx FIFO Error
 * @param base Module base pointer of type SPI_Type.
 * @return The consummate value of all four FIFO error flags of type spi_fifo_error_flag_t.
 */
static inline spi_fifo_error_flag_t SPI_HAL_GetFifoErrorFlag(SPI_Type * base)
{
    return (spi_fifo_error_flag_t)((SPI_RD_CI(base) >> 4) & 0xFU);
}

/*@}*/
#endif

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* FSL_FEATURE_SOC_SPI_COUNT */
#endif /* __FSL_SPI_HAL_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/

