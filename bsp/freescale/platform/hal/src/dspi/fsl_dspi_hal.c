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

#include "fsl_dspi_hal.h"

#if FSL_FEATURE_SOC_DSPI_COUNT

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_HAL_Init
 * Description   : Restore DSPI to reset configuration.
 * This function basically resets all of the DSPI registers to their default setting including
 * disabling the module.
 *
 *END**************************************************************************/
void DSPI_HAL_Init(SPI_Type * base)
{
    /* first, make sure the module is enabled to allow writes to certain registers*/
    SPI_BWR_MCR_MDIS(base, 0);

    /* Halt all transfers*/
    SPI_BWR_MCR_HALT(base, 1);

    /* set the registers to their default states*/
    /* clear the status bits (write-1-to-clear)*/
    SPI_WR_SR(base, SPI_SR_TCF_MASK | SPI_SR_EOQF_MASK | SPI_SR_TFUF_MASK | SPI_SR_TFFF_MASK |
              SPI_SR_RFOF_MASK | SPI_SR_RFDF_MASK);

    SPI_WR_TCR(base, 0);
    SPI_WR_CTAR(base, 0, 0x78000000); /* CTAR0 */
    SPI_WR_CTAR(base, 1, 0x78000000); /* CTAR1 */
    SPI_WR_RSER(base, 0);

    /* Clear out PUSHR register. Since DSPI is halted, nothing should be transmitted. Be
     * sure the flush the FIFOs afterwards
     */
    SPI_WR_PUSHR(base, 0);

    /* flush the fifos*/
    SPI_BWR_MCR_CLR_TXF(base, true);
    SPI_BWR_MCR_CLR_RXF(base, true);

    /* Now set MCR to default value, which disables module: set MDIS and HALT, clear other bits */
    SPI_WR_MCR(base, SPI_MCR_MDIS_MASK | SPI_MCR_HALT_MASK);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_HAL_SetBaudRate
 * Description   : Set the DSPI baud rate in bits per second.
 * This function will take in the desired bitsPerSec (baud rate) and will calculate the nearest
 * possible baud rate without exceeding the desired baud rate, and will return the calculated
 * baud rate in bits-per-second. It requires that the caller also provide the frequency of the
 * module source clock (in Hz).
 *
 *END**************************************************************************/
uint32_t DSPI_HAL_SetBaudRate(SPI_Type * base, dspi_ctar_selection_t whichCtar,
                              uint32_t bitsPerSec, uint32_t sourceClockInHz)
{
    /* for master mode configuration, if slave mode detected, return 0*/
    if (!DSPI_HAL_IsMaster(base))
    {
        return 0;
    }

    uint32_t prescaler, bestPrescaler;
    uint32_t scaler, bestScaler;
    uint32_t dbr, bestDbr;
    uint32_t realBaudrate, bestBaudrate;
    uint32_t diff, min_diff;
    uint32_t baudrate = bitsPerSec;

    /* find combination of prescaler and scaler resulting in baudrate closest to the
     * requested value
     */
    min_diff = 0xFFFFFFFFU;
    bestPrescaler = 0;
    bestScaler = 0;
    bestDbr = 1;
    bestBaudrate = 0; /* required to avoid compilation warning */

    /* In all for loops, if min_diff = 0, the exit for loop*/
    for (prescaler = 0; (prescaler < 4) && min_diff; prescaler++)
    {
        for (scaler = 0; (scaler < 16) && min_diff; scaler++)
        {
            for (dbr = 1; (dbr < 3) && min_diff; dbr++)
            {
                realBaudrate = ((sourceClockInHz * dbr) /
                                (s_baudratePrescaler[prescaler] * (s_baudrateScaler[scaler])));

                /* calculate the baud rate difference based on the conditional statement
                 * that states that the calculated baud rate must not exceed the desired baud rate
                 */
                if (baudrate >= realBaudrate)
                {
                    diff = baudrate-realBaudrate;
                    if (min_diff > diff)
                    {
                        /* a better match found */
                        min_diff = diff;
                        bestPrescaler = prescaler;
                        bestScaler = scaler;
                        bestBaudrate = realBaudrate;
                        bestDbr = dbr;
                    }
                }
            }
        }
    }

    /* write the best dbr, prescalar, and baud rate scalar to the CTAR */
    SPI_BWR_CTAR_DBR(base, whichCtar, (bestDbr - 1));
    SPI_BWR_CTAR_PBR(base, whichCtar, bestPrescaler);
    SPI_BWR_CTAR_BR(base, whichCtar, bestScaler);

    /* return the actual calculated baud rate */
    return bestBaudrate;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_HAL_SetBaudDivisors
 * Description   : Configure the baud rate divisors manually.
 * This function allows the caller to manually set the baud rate divisors in the event that
 * these dividers are known and the caller does not wish to call the DSPI_HAL_SetBaudRate function.
 *
 *END**************************************************************************/
void DSPI_HAL_SetBaudDivisors(SPI_Type * base,
                              dspi_ctar_selection_t whichCtar,
                              const dspi_baud_rate_divisors_t * divisors)
{
    /* these settings are only relevant in master mode */
    if (DSPI_HAL_IsMaster(base))
    {
        SPI_BWR_CTAR_DBR(base, whichCtar, divisors->doubleBaudRate);
        SPI_BWR_CTAR_PBR(base, whichCtar, divisors->prescaleDivisor);
        SPI_BWR_CTAR_BR(base, whichCtar, divisors->baudRateDivisor);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_HAL_SetPcsPolarityMode
 * Description   : Configure DSPI peripheral chip select polarity.
 * This function will take in the desired peripheral chip select (PCS) and it's
 * corresponding desired polarity and will configure the PCS signal to operate with the
 * desired characteristic.
 *
 *END**************************************************************************/
void DSPI_HAL_SetPcsPolarityMode(SPI_Type * base, dspi_which_pcs_config_t pcs,
                                 dspi_pcs_polarity_config_t activeLowOrHigh)
{
    uint32_t temp;

    temp = SPI_RD_MCR_PCSIS(base);

    if (activeLowOrHigh == kDspiPcs_ActiveLow)
    {
        temp |= pcs;
    }
    else  /* kDspiPcsPolarity_ActiveHigh */
    {
        temp &= ~(unsigned)pcs;
    }

    SPI_BWR_MCR_PCSIS(base, temp);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_HAL_SetFifoCmd
 * Description   : Enables (or disables) the DSPI FIFOs.
 * This function with allow the caller to disable/enable the TX and RX FIFOs (independently).
 * Note that to disable, the caller must pass in a logic 0 (false) for the particular FIFO
 * configuration.  To enable, the caller must pass in a logic 1 (true).
 *
 *END**************************************************************************/
void DSPI_HAL_SetFifoCmd(SPI_Type * base, bool enableTxFifo, bool enableRxFifo)
{
    /* first see if MDIS is set or cleared */
    uint32_t isMdisSet = SPI_RD_MCR_MDIS(base);

    if (isMdisSet)
    {
        /* clear the MDIS bit (enable DSPI) to allow us to write to the fifo disables */
        DSPI_HAL_Enable(base);
    }

    /* Note, the bit definition is "disable FIFO", so a "1" would disable. If user wants to enable
     * the FIFOs, they pass in true, which we must logically negate (turn to false) to enable the
     * FIFO
     */
    SPI_BWR_MCR_DIS_TXF(base, !(enableTxFifo == true));
    SPI_BWR_MCR_DIS_RXF(base, !(enableRxFifo == true));

    /* set MDIS (disable DSPI) if it was set to begin with */
    if (isMdisSet)
    {
        DSPI_HAL_Disable(base);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_HAL_SetFlushFifoCmd
 * Description   : Flush DSPI fifos.
 *
 *END**************************************************************************/
void DSPI_HAL_SetFlushFifoCmd(SPI_Type * base, bool enableFlushTxFifo, bool enableFlushRxFifo)
{
    SPI_BWR_MCR_CLR_TXF(base, (enableFlushTxFifo == true));
    SPI_BWR_MCR_CLR_RXF(base, (enableFlushRxFifo == true));
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_HAL_SetDataFormat
 * Description   : Configure the data format for a particular CTAR.
 * This function configures the bits-per-frame, polarity, phase, and shift direction for a
 * particular CTAR. An example use case is as follows:
 *    dspi_data_format_config_t dataFormat;
 *    dataFormat.bitsPerFrame = 16;
 *    dataFormat.clkPolarity = kDspiClockPolarity_ActiveLow;
 *    dataFormat.clkPhase = kDspiClockPhase_FirstEdge;
 *    dataFormat.direction = kDspiMsbFirst;
 *    DSPI_HAL_SetDataFormat(base, kDspiCtar0, &dataFormat);
 *
 *END**************************************************************************/
dspi_status_t DSPI_HAL_SetDataFormat(SPI_Type * base,
                                     dspi_ctar_selection_t whichCtar,
                                     const dspi_data_format_config_t * config)
{
    /* check bits-per-frame value to make sure it it within the proper range
     * in either master or slave mode
     */
    if ((config->bitsPerFrame < 4) ||
        ((config->bitsPerFrame > 16) && (SPI_RD_MCR_MSTR(base) == 1)) ||
#if FSL_FEATURE_DSPI_HAS_SEPARATE_TXDATA_CMD_FIFO
        ((config->bitsPerFrame > 16) && (SPI_RD_MCR_MSTR(base) == 0)))
#else
        ((config->bitsPerFrame > 32) && (SPI_RD_MCR_MSTR(base) == 0)))
#endif
    {
        return kStatus_DSPI_InvalidBitCount;
    }

    /* for master mode configuration */
    if (DSPI_HAL_IsMaster(base))
    {
        SPI_BWR_CTAR_FMSZ(base, whichCtar, (config->bitsPerFrame - 1));
        SPI_BWR_CTAR_CPOL(base, whichCtar, config->clkPolarity);
        SPI_BWR_CTAR_CPHA(base, whichCtar, config->clkPhase);
        SPI_BWR_CTAR_LSBFE(base, whichCtar, config->direction);
    }
    else /* for slave mode configuration */
    {
        SPI_BWR_CTAR_SLAVE_FMSZ(base, whichCtar, (config->bitsPerFrame - 1));
        SPI_BWR_CTAR_SLAVE_CPOL(base, whichCtar, config->clkPolarity);
        SPI_BWR_CTAR_SLAVE_CPHA(base, whichCtar, config->clkPhase);
    }
    return kStatus_DSPI_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_HAL_SetDelay
 * Description   : Manually configures the delay prescaler and scaler for a particular CTAR.
 * This function configures the:
 * PCS to SCK delay pre-scalar (PCSSCK) and scalar (CSSCK),
 * After SCK delay pre-scalar (PASC) and scalar (ASC),
 * Delay after transfer pre-scalar (PDT)and scalar (DT).
 *
 * These delay names are available in type dspi_delay_type_t.
 *
 * The user passes which delay they want to configure along with the prescaler and scaler value.
 * This basically allows the user to directly set the prescaler/scaler values if they have
 * pre-calculated them or if they simply wish to manually increment either value.
 *END**************************************************************************/
void DSPI_HAL_SetDelay(SPI_Type * base, dspi_ctar_selection_t whichCtar, uint32_t prescaler,
                       uint32_t scaler, dspi_delay_type_t whichDelay)
{
    /* these settings are only relevant in master mode */
    if ((bool)SPI_RD_MCR_MSTR(base))
    {
        if (whichDelay == kDspiPcsToSck)
        {
            SPI_BWR_CTAR_PCSSCK(base, whichCtar, prescaler);
            SPI_BWR_CTAR_CSSCK(base, whichCtar, scaler);
        }

        if (whichDelay == kDspiLastSckToPcs)
        {
            SPI_BWR_CTAR_PASC(base, whichCtar, prescaler);
            SPI_BWR_CTAR_ASC(base, whichCtar, scaler);
        }

        if (whichDelay == kDspiAfterTransfer)
        {
            SPI_BWR_CTAR_PDT(base, whichCtar, prescaler);
            SPI_BWR_CTAR_DT(base, whichCtar, scaler);
        }
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_HAL_CalculateDelay
 * Description   : Calculates the delay prescaler and scaler based on desired delay input in
 *                 nano-seconds.
 *
 * This function calculates the values for:
 * PCS to SCK delay pre-scalar (PCSSCK) and scalar (CSSCK), or
 * After SCK delay pre-scalar (PASC) and scalar (ASC), or
 * Delay after transfer pre-scalar (PDT)and scalar (DT).
 *
 * These delay names are available in type dspi_delay_type_t.
 *
 * The user passes which delay they want to configure along with the desired delay value in
 * nano-seconds.  The function will calculate the values needed for the prescaler and scaler and
 * will return the actual calculated delay as an exact delay match may not be acheivable. In this
 * case, the closest match will be calculated without going below the desired delay value input.
 * It is possible to input a very large delay value that exceeds the capability of the part, in
 * which case the maximum supported delay will be returned. It will be up to the higher level
 * peripheral driver to alert the user of an out of range delay input.
 *END**************************************************************************/
uint32_t DSPI_HAL_CalculateDelay(SPI_Type * base, dspi_ctar_selection_t whichCtar,
                                 dspi_delay_type_t whichDelay, uint32_t sourceClockInHz,
                                 uint32_t delayInNanoSec)
{
    /* for master mode configuration, if slave mode detected, return 0 */
    if (!(bool)SPI_RD_MCR_MSTR(base))
    {
        return 0;
    }

    uint32_t prescaler, bestPrescaler;
    uint32_t scaler, bestScaler;
    uint32_t realDelay, bestDelay;
    uint32_t diff, min_diff;
    uint32_t initialDelayNanoSec;

    /* find combination of prescaler and scaler resulting in the delay closest to the
     * requested value
     */
    min_diff = 0xFFFFFFFFU;
    /* Initialize prescaler and scaler to their max values to generate the max delay */
    bestPrescaler = 0x3;
    bestScaler = 0xF;
    bestDelay = (1000000000/sourceClockInHz) * s_delayPrescaler[bestPrescaler] *
                 s_delayScaler[bestScaler];

    /* First calculate the initial, default delay */
    initialDelayNanoSec = 1000000000/sourceClockInHz * 2;

    /* If the initial, default delay is already greater than the desired delay, then
     * set the delays to their initial value (0) and return the delay. In other words,
     * there is no way to decrease the delay value further.
     */
    if (initialDelayNanoSec >= delayInNanoSec)
    {
        DSPI_HAL_SetDelay(base, whichCtar, 0, 0, whichDelay);
        return initialDelayNanoSec;
    }


    /* In all for loops, if min_diff = 0, the exit for loop */
    for (prescaler = 0; (prescaler < 4) && min_diff; prescaler++)
    {
        for (scaler = 0; (scaler < 16) && min_diff; scaler++)
        {
            realDelay = (1000000000/sourceClockInHz) * s_delayPrescaler[prescaler] *
                         s_delayScaler[scaler];

            /* calculate the delay difference based on the conditional statement
             * that states that the calculated delay must not be less then the desired delay
             */
            if (realDelay >= delayInNanoSec)
            {
                diff = realDelay-delayInNanoSec;
                if (min_diff > diff)
                {
                    /* a better match found */
                    min_diff = diff;
                    bestPrescaler = prescaler;
                    bestScaler = scaler;
                    bestDelay = realDelay;
                }
            }
        }
    }

    /* write the best dbr, prescalar, and baud rate scalar to the CTAR */
    DSPI_HAL_SetDelay(base, whichCtar, bestPrescaler, bestScaler, whichDelay);

    /* return the actual calculated baud rate */
    return bestDelay;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_HAL_SetTxFifoFillDmaIntMode
 * Description   : Configures the DSPI Tx FIFO Fill request to generate DMA or interrupt requests.
 * This function configures the DSPI Tx FIFO Fill flag to generate either
 * an interrupt or DMA request.  The user passes in which request they'd like to generate
 * of type dspi_dma_or_int_mode_t and whether or not they wish to enable this request.
 * Note, when disabling the request, the request type is don't care.
 *
 *  DSPI_HAL_SetTxFifoFillDmaIntMode(base, kDspiGenerateDmaReq, true); <- to enable DMA
 *  DSPI_HAL_SetTxFifoFillDmaIntMode(base, kDspiGenerateIntReq, true); <- to enable Interrupt
 *  DSPI_HAL_SetTxFifoFillDmaIntMode(base, kDspiGenerateIntReq, false); <- to disable
 *
 *END**************************************************************************/
void DSPI_HAL_SetTxFifoFillDmaIntMode(SPI_Type * base, dspi_dma_or_int_mode_t mode, bool enable)
{
    SPI_BWR_RSER_TFFF_DIRS(base, mode);  /* Configure as DMA or interrupt */
    SPI_BWR_RSER_TFFF_RE(base, (enable == true));  /* Enable or disable the request */
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_HAL_SetRxFifoDrainDmaIntMode
 * Description   : Configures the DSPI Rx FIFO Drain request to generate DMA or interrupt requests.
 * This function configures the DSPI Rx FIFO Drain flag to generate either
 * an interrupt or DMA request.  The user passes in which request they'd like to generate
 * of type dspi_dma_or_int_mode_t and whether or not they wish to enable this request.
 * Note, when disabling the request, the request type is don't care.
 *
 *  DSPI_HAL_SetRxFifoDrainDmaIntMode(base, kDspiGenerateDmaReq, true); <- to enable DMA
 *  DSPI_HAL_SetRxFifoDrainDmaIntMode(base, kDspiGenerateIntReq, true); <- to enable Interrupt
 *  DSPI_HAL_SetRxFifoDrainDmaIntMode(base, kDspiGenerateIntReq, false); <- to disable
 *
 *END**************************************************************************/
void DSPI_HAL_SetRxFifoDrainDmaIntMode(SPI_Type * base, dspi_dma_or_int_mode_t mode, bool enable)
{
    SPI_BWR_RSER_RFDF_DIRS(base, mode);  /* Configure as DMA or interrupt */
    SPI_BWR_RSER_RFDF_RE(base, (enable == true));  /* Enable or disable the request */
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_HAL_SetIntMode
 * Description   : Configure DSPI interrupts.
 * This function configures the various interrupt sources of the DSPI.  The parameters are
 * base, interrupt source, and enable/disable setting.
 * The interrupt source is a typedef enum whose value is the bit position of the
 * interrupt source setting within the RSER register.  In the DSPI, all interrupt
 * configuration settings are in  one register.  The typedef enum  equates each
 * interrupt source to the bit position defined in the device header file.
 * The function  uses these bit positions in its algorithm to enable/disable the
 * interrupt source, where interrupt source is the dspi_status_and_interrupt_request_t type.
 * Note, for Tx FIFO Fill and Rx FIFO Drain requests, use the functions:
 * DSPI_HAL_SetTxFifoFillDmaIntMode and DSPI_HAL_SetRxFifoDrainDmaIntMode respectively as
 * these requests can generate either an interrupt or DMA request.
 *
 *   DSPI_HAL_SetIntMode(base, kDspiTxComplete, true); <- example use-case
 *
 *END**************************************************************************/
void DSPI_HAL_SetIntMode(SPI_Type * base,
                                  dspi_status_and_interrupt_request_t interruptSrc,
                                  bool enable)
{
    uint32_t temp;

    temp = (SPI_RD_RSER(base) & ~(0x1U << interruptSrc)) | ((uint32_t)enable << interruptSrc);
    SPI_WR_RSER(base, temp);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_HAL_WriteDataMastermode
 * Description   : Write data into the data buffer, master mode.
 * In master mode, the 16-bit data is appended with the 16-bit command info. The command portion
 * provides characteristics of the data being sent such as: optional continuous chip select
 * operation between transfers, the desired Clock and Transfer Attributes register to use for the
 * associated SPI frame, the desired PCS signal to use for the data transfer, whether the current
 * transfer is the last in the queue, and whether to clear the transfer count (normally needed when
 * sending the first frame of a data packet). An example use case is as follows:
 *    dspi_command_config_t commandConfig;
 *    commandConfig.isChipSelectContinuous = true;
 *    commandConfig.whichCtar = kDspiCtar0;
 *    commandConfig.whichPcs = kDspiPcs1;
 *    commandConfig.clearTransferCount = false;
 *    commandConfig.isEndOfQueue = false;
 *    DSPI_HAL_WriteDataMastermode(base, &commandConfig, dataWord);
 *
 *END**************************************************************************/
void DSPI_HAL_WriteDataMastermode(SPI_Type * base,
                                  dspi_command_config_t * command,
                                  uint16_t data)
{
    uint32_t temp;

    /* First, build up the 32-bit word then write it to the PUSHR.
     * Note, to work around MISRA warnings typecast each variable before the shift
     */
    temp = ((uint32_t)(command->isChipSelectContinuous) << SPI_PUSHR_CONT_SHIFT) |
           ((uint32_t)(command->whichCtar) << SPI_PUSHR_CTAS_SHIFT) |
           ((uint32_t)(command->whichPcs) << SPI_PUSHR_PCS_SHIFT) |
           ((uint32_t)(command->isEndOfQueue) << SPI_PUSHR_EOQ_SHIFT) |
           ((uint32_t)(command->clearTransferCount) << SPI_PUSHR_CTCNT_SHIFT) |
           ((uint32_t)(data) << SPI_PUSHR_TXDATA_SHIFT);

    SPI_WR_PUSHR(base, temp);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_HAL_WriteDataSlavemodeBlocking
 * Description   : Writes data into the data buffer, slave mode and waits till data was transmitted
 *                 and return.
 *
 * In slave mode, up to 16-bit words may be written. The function first clears transmit complete
 * flag then writes data into data register, and finally wait tills the data is transmitted.
 *
 *END**************************************************************************/
void DSPI_HAL_WriteDataSlavemodeBlocking(SPI_Type * base, uint32_t data)
{
    /* Firstly, clear transmit complete flag */
    SPI_BWR_SR_TCF(base, 1);
    /* Write data into register */
    SPI_WR_PUSHR_SLAVE(base, data);
    /* Wait tills the data is transmitted */
    while(SPI_RD_SR_TCF(base) == 0) { }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_HAL_WriteDataMastermodeBlocking
 * Description   : Write data into the data buffer, master mode and waits till complete to return.
 * In master mode, the 16-bit data is appended with the 16-bit command info. The command portion
 * provides characteristics of the data being sent such as: optional continuous chip select
 * operation between transfers, the desired Clock and Transfer Attributes register to use for the
 * associated SPI frame, the desired PCS signal to use for the data transfer, whether the current
 * transfer is the last in the queue, and whether to clear the transfer count (normally needed when
 * sending the first frame of a data packet). An example use case is as follows:
 *    dspi_command_config_t commandConfig;
 *    commandConfig.isChipSelectContinuous = true;
 *    commandConfig.whichCtar = kDspiCtar0;
 *    commandConfig.whichPcs = kDspiPcs1;
 *    commandConfig.clearTransferCount = false;
 *    commandConfig.isEndOfQueue = false;
 *    DSPI_HAL_WriteDataMastermodeBlocking(base, &commandConfig, dataWord);
 *
 * Note that this function will not return until after the transmit is complete. Also note that
 * the DSPI must be enabled and running in order to transmit data (MCR[MDIS] & [HALT] = 0).
 * Since the SPI is a synchronous protocol, receive data will be available when transmit completes.
 *
 *END**************************************************************************/
void DSPI_HAL_WriteDataMastermodeBlocking(SPI_Type * base,
                                          dspi_command_config_t * command,
                                          uint16_t data)
{
    uint32_t temp;

    /* First, clear Transmit Complete Flag (TCF) */
    SPI_BWR_SR_TCF(base, 1);

    /* First, build up the 32-bit word then write it to the PUSHR
     * Note, to work around MISRA warnings typecast each variable before the shift
     */
    temp = ((uint32_t)(command->isChipSelectContinuous) << SPI_PUSHR_CONT_SHIFT) |
           ((uint32_t)(command->whichCtar) << SPI_PUSHR_CTAS_SHIFT) |
           ((uint32_t)(command->whichPcs) << SPI_PUSHR_PCS_SHIFT) |
           ((uint32_t)(command->isEndOfQueue) << SPI_PUSHR_EOQ_SHIFT) |
           ((uint32_t)(command->clearTransferCount) << SPI_PUSHR_CTCNT_SHIFT) |
           ((uint32_t)(data) << SPI_PUSHR_TXDATA_SHIFT);

    SPI_WR_PUSHR(base, temp);

    /* Wait till TCF sets */
    while(SPI_RD_SR_TCF(base) == 0) { }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_HAL_WriteCmdDataMastermodeBlocking
 * Description   : Writes a 32-bit data word (16-bit command appended with 16-bit data) into the
 *                 data buffer, master mode and waits till complete to return.
 * In this function, the user must append the 16-bit data to the 16-bit command info then
 * provide the total 32-bit word as the data to send.
 * The command portion provides characteristics of the data such as: optional continuous chip select
 * operation between transfers, the desired Clock and Transfer Attributes register to use for the
 * associated SPI frame, the desired PCS signal to use for the data transfer, whether the current
 * transfer is the last in the queue, and whether to clear the transfer count (normally needed when
 * sending the first frame of a data packet). The user is responsible for appending this command
 * with the data to send.  This is an example:
 *
 *   dataWord = <16-bit command> | <16-bit data>;
 *   DSPI_HAL_WriteCmdDataMastermodeBlocking(base, dataWord);
 *
 *
 * Note that this function does not return until after the transmit is complete. Also note that
 * the DSPI must be enabled and running in order to transmit data (MCR[MDIS] & [HALT] = 0).
 * Since the SPI is a synchronous protocol, receive data is available when transmit completes.
 *
 *END**************************************************************************/
void DSPI_HAL_WriteCmdDataMastermodeBlocking(SPI_Type * base, uint32_t data)
{
    /* First, clear Transmit Complete Flag (TCF) */
    SPI_BWR_SR_TCF(base, 1);

    SPI_WR_PUSHR(base, data);

    /* Wait till TCF sets */
    while(SPI_RD_SR_TCF(base) == 0) { }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_HAL_GetFormattedCommand
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
 *END**************************************************************************/
uint32_t DSPI_HAL_GetFormattedCommand(SPI_Type * base, dspi_command_config_t * command)
{
    uint32_t temp;

    /* Format the 16-bit command word according to the PUSHR data register bit field
     * Note, to work around MISRA warnings typecast each variable before the shift
     */
    temp = ((uint32_t)(command->isChipSelectContinuous) << SPI_PUSHR_CONT_SHIFT) |
           ((uint32_t)(command->whichCtar) << SPI_PUSHR_CTAS_SHIFT) |
           ((uint32_t)(command->whichPcs) << SPI_PUSHR_PCS_SHIFT) |
           ((uint32_t)(command->isEndOfQueue) << SPI_PUSHR_EOQ_SHIFT) |
           ((uint32_t)(command->clearTransferCount) << SPI_PUSHR_CTCNT_SHIFT);

    return temp;
}

#endif /* FSL_FEATURE_SOC_DSPI_COUNT */
/*******************************************************************************
 * EOF
 ******************************************************************************/

