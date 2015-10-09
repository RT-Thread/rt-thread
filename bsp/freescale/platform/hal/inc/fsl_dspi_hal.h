/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
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
#if !defined(__FSL_DSPI_HAL_H__)
#define __FSL_DSPI_HAL_H__

#include <stdint.h>
#include <stdbool.h>
#include "fsl_device_registers.h"

#if FSL_FEATURE_SOC_DSPI_COUNT

/*!
 * @addtogroup dspi_hal
 * @{
 */

/*! @file*/

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Defines constant value arrays for the baud rate pre-scalar and scalar divider values.*/
static const uint32_t s_baudratePrescaler[] = { 2, 3, 5, 7 };
static const uint32_t s_baudrateScaler[] = { 2, 4, 6, 8, 16, 32, 64, 128, 256, 512, 1024, 2048,
                                           4096, 8192, 16384, 32768 };

static const uint32_t s_delayPrescaler[] = { 1, 3, 5, 7 };
static const uint32_t s_delayScaler[] = { 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048,
                                           4096, 8192, 16384, 32768, 65536 };


/*! @brief Error codes for the DSPI driver.*/
typedef enum _dspi_status
{
    kStatus_DSPI_Success = 0,
    kStatus_DSPI_SlaveTxUnderrun,           /*!< DSPI Slave Tx Under run error*/
    kStatus_DSPI_SlaveRxOverrun,            /*!< DSPI Slave Rx Overrun error*/
    kStatus_DSPI_Timeout,                   /*!< DSPI transfer timed out*/
    kStatus_DSPI_Busy,                      /*!< DSPI instance is already busy performing a
                                                 transfer.*/
    kStatus_DSPI_NoTransferInProgress,      /*!< Attempt to abort a transfer when no transfer
                                                 was in progress*/
    kStatus_DSPI_InvalidBitCount,           /*!< bits-per-frame value not valid*/
    kStatus_DSPI_InvalidInstanceNumber,     /*!< DSPI instance number does not match current count*/
    kStatus_DSPI_OutOfRange,                /*!< DSPI out-of-range error  */
    kStatus_DSPI_InvalidParameter,          /*!< DSPI invalid parameter error */
    kStatus_DSPI_NonInit,                   /*!< DSPI driver does not initialize, not ready */
    kStatus_DSPI_Initialized,               /*!< DSPI driver has initialized, cannot re-initialize*/
    kStatus_DSPI_DMAChannelInvalid,         /*!< DSPI driver could not request DMA channel(s) */
    kStatus_DSPI_Error,                     /*!< DSPI driver error */
    kStatus_DSPI_EdmaStcdUnaligned32Error   /*!< DSPI Edma driver STCD unaligned to 32byte error */
} dspi_status_t;

/*! @brief DSPI master or slave configuration*/
typedef enum _dspi_master_slave_mode {
    kDspiMaster = 1,     /*!< DSPI peripheral operates in master mode*/
    kDspiSlave = 0       /*!< DSPI peripheral operates in slave mode*/
} dspi_master_slave_mode_t;

/*! @brief DSPI clock polarity configuration for a given CTAR*/
typedef enum _dspi_clock_polarity {
    kDspiClockPolarity_ActiveHigh = 0,   /*!< Active-high DSPI clock (idles low)*/
    kDspiClockPolarity_ActiveLow = 1     /*!< Active-low DSPI clock (idles high)*/
} dspi_clock_polarity_t;

/*! @brief DSPI clock phase configuration for a given CTAR*/
typedef enum _dspi_clock_phase {
    kDspiClockPhase_FirstEdge = 0,       /*!< Data is captured on the leading edge of the SCK and
                                              changed on the following edge.*/
    kDspiClockPhase_SecondEdge = 1       /*!< Data is changed on the leading edge of the SCK and
                                              captured on the following edge.*/
} dspi_clock_phase_t;

/*! @brief DSPI data shifter direction options for a given CTAR*/
typedef enum _dspi_shift_direction {
    kDspiMsbFirst = 0,   /*!< Data transfers start with most significant bit.*/
    kDspiLsbFirst = 1    /*!< Data transfers start with least significant bit.*/
} dspi_shift_direction_t;

/*! @brief DSPI Clock and Transfer Attributes Register (CTAR) selection*/
typedef enum _dspi_ctar_selection {
    kDspiCtar0 = 0,   /*!< CTAR0 selection option for master or slave mode @internal gui name="CTAR0" */
    kDspiCtar1 = 1    /*!< CTAR1 selection option for master mode only @internal gui name="CTAR1" */
} dspi_ctar_selection_t;

/*! @brief DSPI Peripheral Chip Select (PCS) Polarity configuration.*/
typedef enum _dspi_pcs_polarity_config {
    kDspiPcs_ActiveHigh = 0, /*!< PCS Active High (idles low) @internal gui name="Active high" */
    kDspiPcs_ActiveLow  = 1 /*!< PCS Active Low (idles high) @internal gui name="Active low" */
} dspi_pcs_polarity_config_t;

/*! @brief DSPI Peripheral Chip Select (PCS) configuration (which PCS to configure)*/
typedef enum _dspi_which_pcs_config {
    kDspiPcs0 = 1 << 0, /*!< PCS[0] @internal gui name="PCS0" */
    kDspiPcs1 = 1 << 1, /*!< PCS[1] @internal gui name="PCS1" */
    kDspiPcs2 = 1 << 2, /*!< PCS[2] @internal gui name="PCS2" */
    kDspiPcs3 = 1 << 3, /*!< PCS[3] @internal gui name="PCS3" */
    kDspiPcs4 = 1 << 4, /*!< PCS[4] @internal gui name="PCS4" */
    kDspiPcs5 = 1 << 5  /*!< PCS[5] @internal gui name="PCS5" */
} dspi_which_pcs_config_t;

/*!
 * @brief DSPI Sample Point: Controls when the DSPI master samples SIN in Modified Transfer
 *  Format. This field is valid only when CPHA bit in CTAR register is 0.
 */
typedef enum _dspi_master_sample_point {
    kDspiSckToSin_0Clock = 0,  /*!< 0 system clocks between SCK edge and SIN sample*/
    kDspiSckToSin_1Clock = 1,  /*!< 1 system clock between SCK edge and SIN sample*/
    kDspiSckToSin_2Clock = 2   /*!< 2 system clocks between SCK edge and SIN sample*/
} dspi_master_sample_point_t;

/*! @brief DSPI Tx FIFO Fill and Rx FIFO Drain DMA or Interrupt configuration */
typedef enum _dspi_dma_or_int_mode {
    kDspiGenerateIntReq = 0, /*!< Desired flag generates an Interrupt request */
    kDspiGenerateDmaReq = 1  /*!< Desired flag generates a DMA request */
} dspi_dma_or_int_mode_t;

/*! @brief DSPI status flags and interrupt request enable*/
typedef enum _dspi_status_and_interrupt_request {
    kDspiTxComplete = SPI_RSER_TCF_RE_SHIFT,  /*!< TCF status/interrupt enable */
    kDspiTxAndRxStatus = SPI_SR_TXRXS_SHIFT,  /*!< TXRXS status only, no interrupt*/
    kDspiEndOfQueue = SPI_RSER_EOQF_RE_SHIFT, /*!< EOQF status/interrupt enable*/
    kDspiTxFifoUnderflow = SPI_RSER_TFUF_RE_SHIFT, /*!< TFUF status/interrupt enable*/
    kDspiTxFifoFillRequest = SPI_RSER_TFFF_RE_SHIFT, /*!< TFFF status/interrupt enable*/
    kDspiRxFifoOverflow = SPI_RSER_RFOF_RE_SHIFT, /*!< RFOF status/interrupt enable*/
    kDspiRxFifoDrainRequest = SPI_RSER_RFDF_RE_SHIFT /*!< RFDF status/interrupt enable*/
} dspi_status_and_interrupt_request_t;

/*! @brief DSPI delay type selection*/
typedef enum _dspi_delay_type {
    kDspiPcsToSck = 1,      /*!< PCS-to-SCK delay */
    kDspiLastSckToPcs = 2,  /*!< Last SCK edge to PCS delay */
    kDspiAfterTransfer = 3, /*!< Delay between transfers */
} dspi_delay_type_t;

/*!
 * @brief DSPI data format settings configuration structure
 *
 * This structure contains the data format settings.  These settings apply to a specific
 * CTARn register, which the user must provide in this structure.
 */
typedef struct DspiDataFormatConfig {
    uint32_t bitsPerFrame;        /*!< Bits per frame, minimum 4, maximum 16 */
    dspi_clock_polarity_t clkPolarity;   /*!< Active high or low clock polarity*/
    dspi_clock_phase_t clkPhase;     /*!< Clock phase setting to change and capture data*/
    dspi_shift_direction_t direction; /*!< MSB or LSB data shift direction
                                           This setting relevant only in master mode and
                                           can be ignored in slave  mode */
} dspi_data_format_config_t;

/*!
 * @brief DSPI baud rate divisors settings configuration structure.
 *
 * Note: These settings are relevant only in master mode.
 * This structure contains the baud rate divisor settings, which provides the user with the option
 * to explicitly set these baud rate divisors. In addition, the user must also set the
 * CTARn register  with the divisor settings.
 */
typedef struct DspiBaudRateDivisors {
    bool doubleBaudRate;          /*!< Double Baud rate parameter setting */
    uint32_t prescaleDivisor;     /*!< Baud Rate Pre-scalar parameter setting*/
    uint32_t baudRateDivisor;     /*!< Baud Rate scaler parameter setting */
} dspi_baud_rate_divisors_t;

/*!
 * @brief DSPI command and data configuration structure
 *
 * Note: This structure is used  with the PUSHR register, which
 * provides the means to write to the Tx FIFO. Data written to this register is
 * transferred to the Tx FIFO. Eight or sixteen-bit write accesses to the PUSHR transfer all
 * 32 register bits to the Tx FIFO. The register structure is different in master and slave
 * modes. In master mode, the register provides 16-bit command and 16-bit data to the Tx
 * FIFO. In slave mode only 16-bit data may be written (this may be contrary to some
 * older documentation which erroneously states that a 32-bit value may be written).
 */
typedef struct DspiCommandDataConfig {
    bool isChipSelectContinuous;  /*!< Option to enable the continuous assertion of chip select
                                       between transfers*/
    dspi_ctar_selection_t whichCtar; /*!< The desired Clock and Transfer Attributes
                                          Register (CTAR) to use for CTAS*/
    dspi_which_pcs_config_t whichPcs;   /*!< The desired PCS signal to use for the data transfer*/
    bool isEndOfQueue;            /*!< Signals that the current transfer is the last in the queue*/
    bool clearTransferCount;      /*!< Clears SPI_TCNT field; cleared before transmission starts*/
} dspi_command_config_t;

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
 * @brief Restores the DSPI to reset the configuration.
 *
 * This function basically resets all of the DSPI registers to their default setting including
 * disabling the module.
 *
 * @param base Module base pointer of type SPI_Type.
 */
void DSPI_HAL_Init(SPI_Type * base);

/*!
 * @brief Enables the DSPI peripheral and sets the MCR MDIS to 0.
 *
 * @param base Module base pointer of type SPI_Type.
 */
static inline void DSPI_HAL_Enable(SPI_Type * base)
{
    SPI_BWR_MCR_MDIS(base, 0);
}

/*!
 * @brief Disables the DSPI peripheral, sets MCR MDIS to 1.
 *
 * @param base Module base pointer of type SPI_Type.
 */
static inline void DSPI_HAL_Disable(SPI_Type * base)
{
    SPI_BWR_MCR_MDIS(base, 1);
}

/*!
 * @brief Sets the DSPI baud rate in bits per second.
 *
 * This function  takes in the desired bitsPerSec (baud rate) and  calculates the nearest
 * possible baud rate without exceeding the desired baud rate, and  returns the calculated
 * baud rate in bits-per-second. It requires that the caller also provide the frequency of the
 * module source clock (in Hertz).
 *
 * @param base Module base pointer of type SPI_Type.
 * @param whichCtar The desired Clock and Transfer Attributes Register (CTAR) of the type
 *                  dspi_ctar_selection_t
 * @param bitsPerSec The desired baud rate in bits per second
 * @param sourceClockInHz Module source input clock in Hertz
 * @return  The actual calculated baud rate
 */
uint32_t DSPI_HAL_SetBaudRate(SPI_Type * base, dspi_ctar_selection_t whichCtar,
                              uint32_t bitsPerSec, uint32_t sourceClockInHz);

/*!
 * @brief Configures the baud rate divisors manually.
 *
 * This function allows the caller to manually set the baud rate divisors in the event that
 * these dividers are known and the caller does not wish to call the DSPI_HAL_SetBaudRate function.
 *
 * @param base Module base pointer of type SPI_Type.
 * @param whichCtar The desired Clock and Transfer Attributes Register (CTAR) of type
 *                  dspi_ctar_selection_t
 * @param divisors Pointer to a structure containing the user defined baud rate divisor settings
 */
void DSPI_HAL_SetBaudDivisors(SPI_Type * base,
                              dspi_ctar_selection_t whichCtar,
                              const dspi_baud_rate_divisors_t * divisors);

/*!
 * @brief Configures the DSPI for master or slave.
 *
 * @param base Module base pointer of type SPI_Type.
 * @param mode Mode setting (master or slave) of type dspi_master_slave_mode_t
 */
static inline void DSPI_HAL_SetMasterSlaveMode(SPI_Type * base, dspi_master_slave_mode_t mode)
{
    SPI_BWR_MCR_MSTR(base, (uint32_t)mode);
}

/*!
 * @brief Returns whether the DSPI module is in master mode.
 *
 * @param base Module base pointer of type SPI_Type.
 * @return Returns true if the module is in master mode or false if the module is in slave mode.
 */
static inline bool DSPI_HAL_IsMaster(SPI_Type * base)
{
    return (bool)SPI_RD_MCR_MSTR(base);
}

/*!
 * @brief Configures the DSPI for the continuous SCK operation.
 *
 * @param base Module base pointer of type SPI_Type.
 * @param enable Enables (true) or disables(false) continuous SCK operation.
 */
static inline void DSPI_HAL_SetContinuousSckCmd(SPI_Type * base, bool enable)
{
    SPI_BWR_MCR_CONT_SCKE(base, (enable == true));
}

#if FSL_FEATURE_DSPI_HAS_CHIP_SELECT_STROBE
/*!
 * @brief Configures the DSPI peripheral chip select strobe enable. Configures the PCS[5] to be the
 *        active-low PCS Strobe output.
 *
 * PCS[5] is a special case that can be configured as an active low PCS strobe or as a Peripheral
 * Chip Select in master mode. When configured as a strobe, it provides a signal to an external
 * demultiplexer to decode PCS[0] to PCS[4] signals into as many as 128 glitch-free PCS signals.
 *
 * @param base Module base pointer of type SPI_Type.
 * @param enable Enable (true) PCS[5] to operate as the peripheral chip select (PCS) strobe
 *               If disable (false), PCS[5] operates as a peripheral chip select
 */
static inline void DSPI_HAL_SetPcsStrobeCmd(SPI_Type * base, bool enable)
{
    SPI_BWR_MCR_PCSSE(base, (enable == true));
}
#endif

/*!
 * @brief Configures the DSPI received FIFO overflow overwrite enable.
 *
 * When enabled, this function allows incoming receive data to overwrite the existing data in the
 * receive shift register when the Rx FIFO is full.  Otherwise when disabled, the incoming data
 * is ignored when the RX FIFO is full.
 *
 * @param base Module base pointer of type SPI_Type.
 * @param enable If enabled (true), allows incoming data to overwrite Rx FIFO contents when full,
 *               else incoming data is ignored.
 */
static inline void DSPI_HAL_SetRxFifoOverwriteCmd(SPI_Type * base, bool enable)
{
    SPI_BWR_MCR_ROOE(base, (enable == true));
}

/*!
 * @brief Configures the DSPI peripheral chip select polarity.
 *
 * This function  takes in the desired peripheral chip select (PCS) and it's
 * corresponding desired polarity and  configures the PCS signal to operate with the
 * desired characteristic.
 *
 * @param base Module base pointer of type SPI_Type.
 * @param pcs The particular peripheral chip select (parameter value is of type
 *            dspi_which_pcs_config_t) for which we wish to apply the active high or active
 *            low characteristic.
 * @param activeLowOrHigh The setting for either "active high, inactive low (0)"  or
 *                        "active low, inactive high(1)" of type dspi_pcs_polarity_config_t.
 */
void DSPI_HAL_SetPcsPolarityMode(SPI_Type * base, dspi_which_pcs_config_t pcs,
                                 dspi_pcs_polarity_config_t activeLowOrHigh);

/*!
 * @brief Enables (or disables) the DSPI FIFOs.
 *
 * This function  allows the caller to disable/enable the Tx and Rx FIFOs (independently).
 * Note that to disable, the caller must pass in a logic 0 (false) for the particular FIFO
 * configuration.  To enable, the caller must pass in a logic 1 (true).
 *
 * @param base Module base pointer of type SPI_Type.
 * @param enableTxFifo Disables (false) the TX FIFO, else enables (true) the TX FIFO
 * @param enableRxFifo Disables (false) the RX FIFO, else enables (true) the RX FIFO
 */
void DSPI_HAL_SetFifoCmd(SPI_Type * base, bool enableTxFifo, bool enableRxFifo);

/*!
 * @brief Flushes the DSPI FIFOs.
 *
 * @param base Module base pointer of type SPI_Type.
 * @param enableFlushTxFifo Flushes (true) the Tx FIFO, else do not flush (false) the Tx FIFO
 * @param enableFlushRxFifo Flushes (true) the Rx FIFO, else do not flush (false) the Rx FIFO
 */
void DSPI_HAL_SetFlushFifoCmd(SPI_Type * base, bool enableFlushTxFifo, bool enableFlushRxFifo);


/*!
 * @brief Configures the time when the DSPI master samples SIN in the Modified Transfer Format.
 *
 * This function controls when the DSPI master samples SIN (data in) in the Modified Transfer
 * Format.  Note that this is valid only when the CPHA bit in the CTAR register is 0.
 *
 * @param base Module base pointer of type SPI_Type.
 * @param samplePnt selects when the data in (SIN) is sampled, of type dspi_master_sample_point_t.
 *                  This value selects either 0, 1, or 2 system clocks between the SCK edge
 *                  and the SIN (data in) sample.
 */
static inline void DSPI_HAL_SetDatainSamplepointMode(SPI_Type * base,
                                                   dspi_master_sample_point_t samplePnt)
{
    SPI_BWR_MCR_SMPL_PT(base, samplePnt);
}

/*!
 * @brief Starts the DSPI transfers, clears HALT bit in MCR.
 *
 * This function call called whenever the module is ready to begin data transfers in either master
 * or slave mode.
 *
 * @param base Module base pointer of type SPI_Type.
 */
static inline void DSPI_HAL_StartTransfer(SPI_Type * base)
{
    SPI_BWR_MCR_HALT(base, 0);
}

/*!
 * @brief Stops (halts) DSPI transfers, sets HALT bit in MCR.
 *
 * This function call  stops data transfers in either master or slave mode.
 *
 * @param base Module base pointer of type SPI_Type.
 */
static inline void DSPI_HAL_StopTransfer(SPI_Type * base)
{
    SPI_BWR_MCR_HALT(base, 1);
}

/*!
 * @brief Configures the data format for a particular CTAR.
 *
 * This function configures the bits-per-frame, polarity, phase, and shift direction for a
 * particular CTAR. An example use case is as follows:
   @code
    dspi_data_format_config_t dataFormat;
    dataFormat.bitsPerFrame = 16;
    dataFormat.clkPolarity = kDspiClockPolarity_ActiveLow;
    dataFormat.clkPhase = kDspiClockPhase_FirstEdge;
    dataFormat.direction = kDspiMsbFirst;
    DSPI_HAL_SetDataFormat(instance, kDspiCtar0, &dataFormat);
   @endcode
 *
 * @param base Module base pointer of type SPI_Type.
 * @param whichCtar The desired Clock and Transfer Attributes Register (CTAR) of type
 *                  dspi_ctar_selection_t.
 * @param config Pointer to structure containing user defined data format configuration settings.
 * @return  An error code or kStatus_DSPI_Success
 */
dspi_status_t DSPI_HAL_SetDataFormat(SPI_Type * base,
                                     dspi_ctar_selection_t whichCtar,
                                     const dspi_data_format_config_t * config);

/*!
 * @brief Manually configures the delay prescaler and scaler for a particular CTAR.
 *
 * This function configures the PCS to SCK delay pre-scalar (PCSSCK) and scalar (CSSCK),
 * after SCK delay pre-scalar (PASC) and scalar (ASC), and the delay
 * after transfer pre-scalar (PDT)and scalar (DT).
 *
 * These delay names are available in type dspi_delay_type_t.
 *
 * The user passes which delay they want to configure along with the prescaler and scaler value.
 * This  allows the user to directly set the prescaler/scaler values if they have
 * pre-calculated them or if they simply wish to manually increment either value.
 *
 * @param base Module base pointer of type SPI_Type.
 * @param whichCtar The desired Clock and Transfer Attributes Register (CTAR) of type
 *                  dspi_ctar_selection_t.
 * @param prescaler The prescaler delay value (can be an integer 0, 1, 2, or 3).
 * @param scaler The scaler delay value (can be any integer between 0 to 15).
 * @param whichDelay The desired delay to configure, must be of type dspi_delay_type_t
 */
void DSPI_HAL_SetDelay(SPI_Type * base, dspi_ctar_selection_t whichCtar, uint32_t prescaler,
                       uint32_t scaler, dspi_delay_type_t whichDelay);

/*!
 * @brief Calculates the delay prescaler and scaler based on the desired delay input in nanoseconds.
 *
 * This function calculates the values for:
 * PCS to SCK delay pre-scalar (PCSSCK) and scalar (CSSCK), or
 * After SCK delay pre-scalar (PASC) and scalar (ASC), or
 * Delay after transfer pre-scalar (PDT)and scalar (DT).
 *
 * These delay names are available in type dspi_delay_type_t.
 *
 * The user passes which delay they want to configure along with the desired delay value in
 * nanoseconds.  The function calculates the values needed for the prescaler and scaler and
 * returning the actual calculated delay as an exact delay match may not be possible. In this
 * case, the closest match is calculated without going below the desired delay value input.
 * It is possible to input a very large delay value that exceeds the capability of the part, in
 * which case the maximum supported delay is returned. It is to the higher level
 * peripheral driver to alert the user of an out of range delay input.
 *
 * @param base Module base pointer of type SPI_Type.
 * @param whichCtar The desired Clock and Transfer Attributes Register (CTAR) of type
 *                  dspi_ctar_selection_t.
 * @param whichDelay The desired delay to configure, must be of type dspi_delay_type_t
 * @param sourceClockInHz Module source input clock in Hertz
 * @param delayInNanoSec The desired delay value in nanoseconds.
 * @return The actual calculated delay value.
 */
uint32_t DSPI_HAL_CalculateDelay(SPI_Type * base, dspi_ctar_selection_t whichCtar,
                                 dspi_delay_type_t whichDelay, uint32_t sourceClockInHz,
                                 uint32_t delayInNanoSec);

/*!
 * @brief Gets the DSPI master PUSHR data register address for DMA operation.
 *
 * This function gets the DSPI master PUSHR data register address as this value is needed for
 * DMA operation.
 *
 * @param base Module base pointer of type SPI_Type.
 * @return The DSPI master PUSHR data register address.
 */
static inline uint32_t DSPI_HAL_GetMasterPushrRegAddr(SPI_Type * base)
{
    return (uint32_t)(&SPI_PUSHR_REG(base));
}

/*!
 * @brief Gets the DSPI slave PUSHR data register address for DMA operation.
 *
 * This function gets the DSPI slave PUSHR data register address as this value is needed for
 * DMA operation.
 *
 * @param base Module base pointer of type SPI_Type.
 * @return The DSPI slave PUSHR data register address.
 */
static inline uint32_t DSPI_HAL_GetSlavePushrRegAddr(SPI_Type * base)
{
    return (uint32_t)(&SPI_PUSHR_SLAVE_REG(base));
}

/*!
 * @brief Gets the DSPI POPR data register address for DMA operation.
 *
 * This function gets the DSPI POPR data register address as this value is needed for
 * DMA operation.
 *
 * @param base Module base pointer of type SPI_Type.
 * @return The DSPI POPR data register address.
 */
static inline uint32_t DSPI_HAL_GetPoprRegAddr(SPI_Type * base)
{
    return (uint32_t)(&SPI_POPR_REG(base));
}
/*@}*/

/*!
 * @name Interrupts
 * @{
 */

/*!
 * @brief Configures the DSPI Tx FIFO fill request to generate DMA or interrupt requests.
 *
 * This function configures the DSPI Tx FIFO Fill flag to generate either
 * an interrupt or DMA request.  The user passes in which request they'd like to generate
 * of type dspi_dma_or_int_mode_t and whether or not they wish to enable this request.
 * Note, when disabling the request, the request type is don't care.
   @code
    DSPI_HAL_SetTxFifoFillDmaIntMode(base, kDspiGenerateDmaReq, true); <- to enable DMA
    DSPI_HAL_SetTxFifoFillDmaIntMode(base, kDspiGenerateIntReq, true); <- to enable Interrupt
    DSPI_HAL_SetTxFifoFillDmaIntMode(base, kDspiGenerateIntReq, false); <- to disable
   @endcode
 * @param base Module base pointer of type SPI_Type.
 * @param mode Configures the DSPI Tx FIFO Fill to generate an interrupt or DMA request
 * @param enable Enable (true) or disable (false) the DSPI Tx FIFO Fill flag to generate requests
 */
void DSPI_HAL_SetTxFifoFillDmaIntMode(SPI_Type * base, dspi_dma_or_int_mode_t mode, bool enable);

/*!
 * @brief Configures the DSPI Rx FIFO Drain request to generate DMA or interrupt requests.
 *
 * This function configures the DSPI Rx FIFO Drain flag to generate either
 * an interrupt or a DMA request.  The user passes in which request they'd like to generate
 * of type dspi_dma_or_int_mode_t and whether or not they wish to enable this request.
 * Note, when disabling the request, the request type is don't care.
   @code
    DSPI_HAL_SetRxFifoDrainDmaIntMode(base, kDspiGenerateDmaReq, true); <- to enable DMA
    DSPI_HAL_SetRxFifoDrainDmaIntMode(base, kDspiGenerateIntReq, true); <- to enable Interrupt
    DSPI_HAL_SetRxFifoDrainDmaIntMode(base, kDspiGenerateIntReq, false); <- to disable
   @endcode
 * @param base Module base pointer of type SPI_Type.
 * @param mode Configures the Rx FIFO Drain to generate an interrupt or DMA request
 * @param enable Enable (true) or disable (false) the Rx FIFO Drain flag to generate requests
 */
void DSPI_HAL_SetRxFifoDrainDmaIntMode(SPI_Type * base, dspi_dma_or_int_mode_t mode, bool enable);

/*!
 * @brief Configures the DSPI interrupts.
 *
 * This function configures the various interrupt sources of the DSPI.  The parameters are
 * base, interrupt source, and enable/disable setting.
 * The interrupt source is a typedef enumeration whose value is the bit position of the
 * interrupt source setting within the RSER register.  In the DSPI, all interrupt
 * configuration settings are in  one register.  The typedef enum  equates each
 * interrupt source to the bit position defined in the device header file.
 * The function  uses these bit positions in its algorithm to enable/disable the
 * interrupt source, where interrupt source is the dspi_status_and_interrupt_request_t type.
 * Note, for Tx FIFO Fill and Rx FIFO Drain requests, use the functions:
 * DSPI_HAL_SetTxFifoFillDmaIntMode and DSPI_HAL_SetRxFifoDrainDmaIntMode respectively as
 * these requests can generate either an interrupt or DMA request.
   @code
    DSPI_HAL_SetIntMode(base, kDspiTxComplete, true); <- example use-case
   @endcode
 *
 * @param base Module base pointer of type SPI_Type.
 * @param interruptSrc The interrupt source, of type dspi_status_and_interrupt_request_t
 * @param enable Enable (true) or disable (false) the interrupt source to generate requests
 */
void DSPI_HAL_SetIntMode(SPI_Type * base,
                         dspi_status_and_interrupt_request_t interruptSrc,
                         bool enable);

/*!
 * @brief Gets DSPI interrupt configuration, returns if interrupt request is enabled or disabled.
 *
 * This function  returns the requested interrupt source setting (enabled or disabled, of
 * type bool).  The parameters to pass in are base and interrupt source.  It utilizes the
 * same enumeration definitions for the interrupt sources as described in the interrupt config
 * function. The function uses these bit positions in its algorithm to obtain the desired
 * interrupt source setting.
 * Note, for Tx FIFO Fill and Rx FIFO Drain requests, this returns whether or not their
 * requests are enabled.
   @code
   getInterruptSetting = DSPI_HAL_GetIntMode(base, kDspiTxComplete);
   @endcode
 *
 * @param base Module base pointer of type SPI_Type.
 * @param interruptSrc The interrupt source, of type dspi_status_and_interrupt_request_t
 * @return Configuration of interrupt request: enable (true) or disable (false).
 */
static inline bool DSPI_HAL_GetIntMode(SPI_Type * base,
                                             dspi_status_and_interrupt_request_t interruptSrc)
{
    return ((SPI_RD_RSER(base) >> interruptSrc) & 0x1);
}

/*@}*/

/*!
 * @name Status
 * @{
 */

/*!
 * @brief Gets the DSPI status flag state.
 *
 * The status flag is defined in the same enumeration as the interrupt source enable because the bit
 * position of the interrupt source and corresponding status flag are the same in the RSER and
 * SR registers.  The function  uses these bit positions in its algorithm to obtain the desired
 * flag state, similar to the dspi_get_interrupt_config function.
   @code
    getStatus = DSPI_HAL_GetStatusFlag(base, kDspiTxComplete);
   @endcode
 *
 * @param base Module base pointer of type SPI_Type.
 * @param statusFlag The status flag, of type dspi_status_and_interrupt_request_t
 * @return State of the status flag: asserted (true) or not-asserted (false)
 */
static inline bool DSPI_HAL_GetStatusFlag(SPI_Type * base,
                                        dspi_status_and_interrupt_request_t statusFlag)
{
    return ((SPI_RD_SR(base) >> statusFlag) & 0x1);
}

/*!
 * @brief Clears the DSPI status flag.
 *
 * This function  clears the desired status bit by using a write-1-to-clear.  The user passes in
 * the base and the desired status bit to clear.  The list of status bits is defined in the
 * dspi_status_and_interrupt_request_t.  The function  uses these bit positions in its algorithm
 * to clear the desired flag state. Example usage:
   @code
    DSPI_HAL_ClearStatusFlag(base, kDspiTxComplete);
   @endcode
 *
 * @param base Module base pointer of type SPI_Type.
 * @param statusFlag The status flag, of type dspi_status_and_interrupt_request_t
 */
static inline void DSPI_HAL_ClearStatusFlag(SPI_Type * base,
                                              dspi_status_and_interrupt_request_t statusFlag)
{
    SPI_WR_SR(base, (0x1U << statusFlag));
}

/*@}*/

/*!
 * @name Data transfer
 * @{
 */

/*!
 * @brief Reads data from the data buffer.
 *
 * @param base Module base pointer of type SPI_Type.
 * @return The data from the read data buffer
 */
static inline uint32_t DSPI_HAL_ReadData(SPI_Type * base)
{
    return SPI_RD_POPR(base);
}

/*!
 * @brief Writes data into the data buffer, slave mode.
 *
 * In slave mode, up to 16-bit words may be written.
 *
 * @param base Module base pointer of type SPI_Type.
 * @param data The data to send
 */
static inline void DSPI_HAL_WriteDataSlavemode(SPI_Type * base, uint32_t data)
{
    SPI_WR_PUSHR_SLAVE(base, data);
}

/*!
 * @brief Writes data into the data buffer, slave mode and waits till data was transmitted and
 *        return.
 *
 * In slave mode, up to 16-bit words may be written. The function first clears transmit complete
 * flag then writes data into data register, and finally wait tills the data is transmitted.
 *
 * @param base Module base pointer of type SPI_Type.
 * @param data The data to send
 */
void DSPI_HAL_WriteDataSlavemodeBlocking(SPI_Type * base, uint32_t data);

/*!
 * @brief Writes data into the data buffer, master mode.
 *
 * In master mode, the 16-bit data is appended to the 16-bit command info. The command portion
 * provides characteristics of the data such as: optional continuous chip select
 * operation between transfers, the desired Clock and Transfer Attributes register to use for the
 * associated SPI frame, the desired PCS signal to use for the data transfer, whether the current
 * transfer is the last in the queue, and whether to clear the transfer count (normally needed when
 * sending the first frame of a data packet). This is an example:
   @code
    dspi_command_config_t commandConfig;
    commandConfig.isChipSelectContinuous = true;
    commandConfig.whichCtar = kDspiCtar0;
    commandConfig.whichPcs = kDspiPcs1;
    commandConfig.clearTransferCount = false;
    commandConfig.isEndOfQueue = false;
    DSPI_HAL_WriteDataMastermode(base, &commandConfig, dataWord);
   @endcode
 *
 * @param base Module base pointer of type SPI_Type.
 * @param command Pointer to command structure
 * @param data The data word to be sent
 */
void DSPI_HAL_WriteDataMastermode(SPI_Type * base,
                                  dspi_command_config_t * command,
                                  uint16_t data);

/*!
 * @brief Writes data into the data buffer, master mode and waits till complete to return.
 *
 * In master mode, the 16-bit data is appended to the 16-bit command info. The command portion
 * provides characteristics of the data such as: optional continuous chip select
 * operation between transfers, the desired Clock and Transfer Attributes register to use for the
 * associated SPI frame, the desired PCS signal to use for the data transfer, whether the current
 * transfer is the last in the queue, and whether to clear the transfer count (normally needed when
 * sending the first frame of a data packet). This is an example:
   @code
    dspi_command_config_t commandConfig;
    commandConfig.isChipSelectContinuous = true;
    commandConfig.whichCtar = kDspiCtar0;
    commandConfig.whichPcs = kDspiPcs1;
    commandConfig.clearTransferCount = false;
    commandConfig.isEndOfQueue = false;
    DSPI_HAL_WriteDataMastermodeBlocking(base, &commandConfig, dataWord);
   @endcode
 *
 * Note that this function does not return until after the transmit is complete. Also note that
 * the DSPI must be enabled and running in order to transmit data (MCR[MDIS] & [HALT] = 0).
 * Since the SPI is a synchronous protocol, receive data is available when transmit completes.
 *
 * @param base Module base pointer of type SPI_Type.
 * @param command Pointer to command structure
 * @param data The data word to be sent
 */
void DSPI_HAL_WriteDataMastermodeBlocking(SPI_Type * base,
                                          dspi_command_config_t * command,
                                          uint16_t data);

/*!
 * @brief Writes a 32-bit data word (16-bit command appended with 16-bit data) into the data
 *        buffer, master mode.
 *
 * In this function, the user must append the 16-bit data to the 16-bit command info then
 * provide the total 32-bit word as the data to send.
 * The command portion provides characteristics of the data such as: optional continuous chip select
 * operation between transfers, the desired Clock and Transfer Attributes register to use for the
 * associated SPI frame, the desired PCS signal to use for the data transfer, whether the current
 * transfer is the last in the queue, and whether to clear the transfer count (normally needed when
 * sending the first frame of a data packet). The user is responsible for appending this command
 * with the data to send.  This is an example:
   @code
    dataWord = <16-bit command> | <16-bit data>;
    DSPI_HAL_WriteCmdDataMastermode(base, dataWord);
   @endcode
 *
 * @param base Module base pointer of type SPI_Type.
 * @param data The data word (command and data combined) to be sent
 */
static inline void DSPI_HAL_WriteCmdDataMastermode(SPI_Type * base, uint32_t data)
{
    SPI_WR_PUSHR(base, data);
}

/*!
 * @brief Writes a 32-bit data word (16-bit command appended with 16-bit data) into the data
 *        buffer, master mode and waits till complete to return.
 *
 * In this function, the user must append the 16-bit data to the 16-bit command info then
 * provide the total 32-bit word as the data to send.
 * The command portion provides characteristics of the data such as: optional continuous chip select
 * operation between transfers, the desired Clock and Transfer Attributes register to use for the
 * associated SPI frame, the desired PCS signal to use for the data transfer, whether the current
 * transfer is the last in the queue, and whether to clear the transfer count (normally needed when
 * sending the first frame of a data packet). The user is responsible for appending this command
 * with the data to send.  This is an example:
   @code
    dataWord = <16-bit command> | <16-bit data>;
    DSPI_HAL_WriteCmdDataMastermodeBlocking(base, dataWord);
   @endcode
 *
 * Note that this function does not return until after the transmit is complete. Also note that
 * the DSPI must be enabled and running in order to transmit data (MCR[MDIS] & [HALT] = 0).
 * Since the SPI is a synchronous protocol, receive data is available when transmit completes.
 *
 * @param base Module base pointer of type SPI_Type.
 * @param data The data word (command and data combined) to be sent
 */
void DSPI_HAL_WriteCmdDataMastermodeBlocking(SPI_Type * base, uint32_t data);

/*!
 * @brief Gets the transfer count.
 *
 * This function returns the current value of the DSPI Transfer Count Register.
 *
 * @param base Module base pointer of type SPI_Type.
 * @return The current transfer count
 */
static inline uint32_t DSPI_HAL_GetTransferCount(SPI_Type * base)
{
    return SPI_RD_TCR_SPI_TCNT(base);
}

/*!
 * @brief Pre-sets the transfer count.
 *
 * This function allows the caller to pre-set the DSI Transfer Count Register to a desired value up
 * to 65535; Incrementing past this resets the counter back to 0.
 *
 * @param base Module base pointer of type SPI_Type.
 * @param presetValue The desired pre-set value for the transfer counter
 */
static inline void DSPI_HAL_PresetTransferCount(SPI_Type * base, uint16_t presetValue)
{
    SPI_BWR_TCR_SPI_TCNT(base, presetValue);
}

/*!
 * @brief Returns the DSPI command word formatted to the PUSHR data register bit field.
 *
 * This function allows the caller to pass in the data command structure and returns the command
 * word formatted according to the DSPI PUSHR register bit field placement. The user can then
 * "OR" the returned command word with the desired data to send and use the function
 * DSPI_HAL_WriteCmdDataMastermode or DSPI_HAL_WriteCmdDataMastermodeBlocking to write the
 * entire 32-bit command data word to the PUSHR.
 * This helps improve performance in cases where the command structure is constant.
 * For example, the user calls this function before starting a transfer to generate the
 * command word.  When they are ready to transmit the data, they would OR this formatted command
 * word with the desired data to transmit.
 * This process increases transmit performance when compared to calling send functions such as
 * DSPI_HAL_WriteDataMastermode which format the command word each time a data word is
 * to be sent.
 *
 * @param base Module base pointer of type SPI_Type.
 * @param command Pointer to command structure
 * @return The command word formatted to the PUSHR data register bit field
 */
uint32_t DSPI_HAL_GetFormattedCommand(SPI_Type * base, dspi_command_config_t * command);

/*@}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* FSL_FEATURE_SOC_DSPI_COUNT */
#endif /* __FSL_DSPI_HAL_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/

