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
#include "fsl_spi_hal.h"
#include "fsl_device_registers.h"

#if FSL_FEATURE_SOC_SPI_COUNT

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Bit offsets for bits encoded in enum values.*/
enum _spi_pin_bit_encodings
{
    kSpiSsoeBit = 0U,    /*!< SSOE is bit 0 of #spi_ss_output_mode_t.*/
    kSpiModfenBit = 1U,  /*!< MODFEN is bit 1 of #spi_ss_output_mode_t.*/
    kSpiSpc0Bit = 0U,    /*!< SPC0 is bit 0 of #spi_pin_mode_t.*/
    kSpiBidiroeBit = 1U  /*!< BIDIROE is bit 1 of #spi_pin_mode_t.*/
};

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : SPI_HAL_Init
 * Description   : RestoreS SPI to reset configuration.
 * This function basically resets all of the SPI registers to their default setting including
 * disabling the module.
 *
 *END**************************************************************************/
void SPI_HAL_Init(SPI_Type * base)
{
    SPI_WR_C1(base, SPI_C1_CPHA_MASK);
    SPI_WR_C2(base, 0);
    SPI_WR_BR(base, 0);

#if FSL_FEATURE_SPI_16BIT_TRANSFERS
    SPI_WR_MH(base, 0);
    SPI_WR_ML(base, 0);
#else
    SPI_WR_M(base, 0);
#endif
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SPI_HAL_SetBaud
 * This function takes in the desired bitsPerSec (baud rate) and calculates the nearest
 * possible baud rate without exceeding the desired baud rate unless the baud rate requested is
 * less than the absolute minimum in which case the minimum baud rate will be returned. The returned
 * baud rate is in bits-per-second. It requires that the caller also provide the frequency of the
 * module source clock (in Hertz).
 *
 *END**************************************************************************/
uint32_t SPI_HAL_SetBaud(SPI_Type * base, uint32_t bitsPerSec, uint32_t sourceClockInHz)
{
    uint32_t prescaler, bestPrescaler;
    uint32_t rateDivisor, bestDivisor;
    uint32_t rateDivisorValue;
    uint32_t realBaudrate, bestBaudrate;
    uint32_t diff, min_diff;
    uint32_t baudrate = bitsPerSec;

    /* find combination of prescaler and scaler resulting in baudrate closest to the
     * requested value
     */
    min_diff = 0xFFFFFFFFU;

    /* Set the maximum divisor bit settings for each of the following divisors */
    bestPrescaler = 7;
    bestDivisor = 8;

    /* Set baud rate to minimum baud rate possible, adjust prescale divisor and divisor
     * bit settings in acutal divisor values
     */
    bestBaudrate = sourceClockInHz / ((bestPrescaler + 1) * (bestDivisor * 64));

    /* In all for loops, if min_diff = 0, the exit for loop*/
    for (prescaler = 0; (prescaler <= 7) && min_diff; prescaler++)
    {
        rateDivisorValue = 2U;  /* Initialize to div-by-2 */

        for (rateDivisor = 0; (rateDivisor <= 8U) && min_diff; rateDivisor++)
        {
            /* calculate actual baud rate, note need to add 1 to prescaler */
            realBaudrate = ((sourceClockInHz) /
                            ((prescaler + 1) * rateDivisorValue));

            /* calculate the baud rate difference based on the conditional statement*/
            /* that states that the calculated baud rate must not exceed the desired baud rate*/
            if (baudrate >= realBaudrate)
            {
                diff = baudrate-realBaudrate;
                if (min_diff > diff)
                {
                    /* a better match found */
                    min_diff = diff;
                    bestPrescaler = prescaler; /* Prescale divisor SPIx_BR register bit setting */
                    bestDivisor = rateDivisor; /* baud rate divisor SPIx_BR register bit setting */
                    bestBaudrate = realBaudrate;
                }
            }
            /* Multiply by 2 for each iteration, possible divisor values: 2, 4, 8, 16, ... 512 */
            rateDivisorValue *= 2U;
        }
    }

    /* write the best prescalar and baud rate scalar */
    SPI_WR_BR(base, SPI_BR_SPR(bestDivisor) | SPI_BR_SPPR(bestPrescaler));

    /* return the actual calculated baud rate*/
    return bestBaudrate;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SPI_HAL_SetSlaveSelectOutputMode
 * This function allows the user to configure the slave select in one of the three operational
 * modes: as GPIO, as a fault input, or as an automatic output for standard SPI modes.
 *
 *END**************************************************************************/
void SPI_HAL_SetSlaveSelectOutputMode(SPI_Type * base, spi_ss_output_mode_t mode)
{
    /* The mode enum values encode the SSOE and MODFEN bit values.*/
    /* Bit 0: SSOE*/
    /* Bit 1: MODFEN*/
    SPI_BWR_C1_SSOE(base, ((uint32_t)mode & (1U << kSpiSsoeBit)) >> kSpiSsoeBit);
    SPI_BWR_C2_MODFEN(base, ((uint32_t)mode & (1U << kSpiModfenBit)) >> kSpiModfenBit);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SPI_HAL_SetDataFormat
 * This function configures the clock polarity, clock phase, and data shift direction.
 *
 *END**************************************************************************/
void SPI_HAL_SetDataFormat(SPI_Type * base,
                           spi_clock_polarity_t polarity,
                           spi_clock_phase_t phase,
                           spi_shift_direction_t direction)
{
    SPI_BWR_C1_CPOL(base, (uint32_t)polarity);
    SPI_BWR_C1_CPHA(base, (uint32_t)phase);
    SPI_BWR_C1_LSBFE(base, (uint32_t)direction);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SPI_HAL_SetPinMode
 * This function configures the SPI data pins to one of three modes (of type spi_pin_mode_t):
 * Single direction mdoe: MOSI and MISO pins operate in normal, single direction mode.
 * Birectional mode: Master: MOSI configured as input, Slave: MISO configured as input.
 * Birectional mode: Master: MOSI configured as output, Slave: MISO configured as output.
 *END**************************************************************************/
void SPI_HAL_SetPinMode(SPI_Type * base, spi_pin_mode_t mode)
{
    /* The mode enum values encode the SPC0 and BIDIROE bit values.*/
    /* Bit 0: SPC0*/
    /* Bit 1: BIDIROE*/
    SPI_BWR_C2_SPC0(base, ((uint32_t)mode & (1U << kSpiSpc0Bit)) >> kSpiSpc0Bit);
    SPI_BWR_C2_BIDIROE(base, ((uint32_t)mode & (1U << kSpiBidiroeBit)) >> kSpiBidiroeBit);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SPI_HAL_SetIntMode
 * This function enables or disables the
 * SPI receive buffer (or FIFO if the module supports a FIFO) full and mode fault interrupt
 * SPI transmit buffer (or FIFO if the module supports a FIFO) empty interrupt
 * SPI match interrupt
 *
 * Example, to set the receive and mode fault interrupt:
 * SPI_HAL_SetIntMode(base, kSpiRxFullAndModfInt, true);
 *
 *END**************************************************************************/
void SPI_HAL_SetIntMode(SPI_Type * base, spi_interrupt_source_t interrupt, bool enable)
{
    if (interrupt == kSpiMatchInt)
    {
        SPI_BWR_C2_SPMIE(base, (enable == true));
    }
    else if (interrupt == kSpiRxFullAndModfInt)
    {
        SPI_BWR_C1_SPIE(base, (enable == true));
    }
    else /* kSpiTxEmptyInt */
    {
        SPI_BWR_C1_SPTIE(base, (enable == true));
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SPI_HAL_ClearModeFaultFlag
 * This function clears the mode fault flag.
 *END**************************************************************************/
void SPI_HAL_ClearModeFaultFlag(SPI_Type * base)
{
    /* Must make sure we read from the status register first. Then, if set,
     * we must write to SPI_C1 (per the reference manual).
     */
    if (SPI_RD_S_MODF(base))
    {
        /* Then we have to write to C1.*/
        SPI_WR_C1(base, SPI_RD_C1(base));
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SPI_HAL_ClearMatchFlag
 * This function clears the match flag.
 *END**************************************************************************/
void SPI_HAL_ClearMatchFlag(SPI_Type * base)
{
    /* Check that the match flag is set before writing 1 to clear it. This read*/
    /* is required in order to clear the flag.*/
    if (SPI_RD_S_SPMF(base))
    {
        /* We have to hack this to write to the register because it is incorrectly
         * defined as a read-only register, even though the SPI_S.SPMF bitfield documentation
         * states you must write a 1 to the bitfield to clear it.
         */
        *((uint8_t*)(base)) |= SPI_S_SPMF_MASK;
    }
}

#if FSL_FEATURE_SPI_16BIT_TRANSFERS

/*FUNCTION**********************************************************************
 *
 * Function Name : SPI_HAL_WriteDataBlocking
 * This function writes data to the SPI data registers and waits until the
 * TX is empty to return.  For 16-bit data, the lower byte is written to dataLow while
 * the upper byte is written to dataHigh.  The paramter bitCount is used to
 * distinguish between 8- and 16-bit writes.
 *
 * Note, for 16-bit data writes, make sure that function SPI_HAL_Set8or16BitMode is set to
 * kSpi16BitMode.
 *END**************************************************************************/
void SPI_HAL_WriteDataBlocking(SPI_Type * base, spi_data_bitcount_mode_t bitCount,
                               uint8_t dataHigh, uint8_t dataLow)
{
    /* Since this is a blocking write, it is assume the user will call this function
     * directly. Per the ref manual, the status register must first be read with the
     * SPTEF bit set.  So wait until SPTEF gets set to make sure the buffer is empty.
     */
    while(SPI_RD_S_SPTEF(base) == 0) { }

    if (bitCount == kSpi16BitMode)
    {
        SPI_WR_DH(base, dataHigh);
        SPI_WR_DL(base, dataLow);
    }

    else
    {
        SPI_WR_DL(base, dataLow);
    }

    /* Wait until TX empty is set before return */
    while(SPI_RD_S_SPTEF(base) == 0) { }
}

#else

/*FUNCTION**********************************************************************
 *
 * Function Name : SPI_HAL_WriteDataBlocking
 * This function writes data to the SPI data register and waits until
 * TX empty to return.
 *END**************************************************************************/
void SPI_HAL_WriteDataBlocking(SPI_Type * base, uint8_t data)
{
    /* Since this is a blocking write, it is assume the user will call this function
     * directly. Per the ref manual, the status register must first be read with the
     * SPTEF bit set.  So wait until SPTEF gets set to make sure the buffer is empty.
     */
    while(SPI_RD_S_SPTEF(base) == 0) { }

    SPI_WR_D(base, data);

    /* Wait until TX empty is set before return */
    while(SPI_RD_S_SPTEF(base) == 0) { }

}

#endif /* FSL_FEATURE_SPI_16BIT_TRANSFERS */

#if FSL_FEATURE_SPI_FIFO_SIZE
/*FUNCTION**********************************************************************
 *
 * Function Name : SPI_HAL_SetFifoMode
 * This all-in-one function will do the following:
 * Configure the TX FIFO empty watermark to be 16bits (1/4) or 32bits (1/2)
 * Configure the RX FIFO full watermark to be 48bits (3/4) or 32bits (1/2)
 * Enable/disable the FIFO
 *END**************************************************************************/
void SPI_HAL_SetFifoMode(SPI_Type * base, bool enable,
                         spi_txfifo_watermark_t txWaterMark,
                         spi_rxfifo_watermark_t rxWaterMark)
{
    SPI_BWR_C3_FIFOMODE(base, (enable == true));
    SPI_BWR_C3_TNEAREF_MARK(base, (uint32_t)txWaterMark);
    SPI_BWR_C3_RNFULLF_MARK(base, (uint32_t)rxWaterMark);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SPI_HAL_SetFifoIntCmd
 * This function enables or disables the SPI FIFO interrupts.  These FIFO interrupts are the TX
 * FIFO nearly empty and the RX FIFO nearly full.  Note, there are separate HAL functions
 * to enable/disable receive buffer/FIFO full interrupt and the transmit buffer/FIFO empty
 * interrupt.
 *END**************************************************************************/
void SPI_HAL_SetFifoIntCmd(SPI_Type * base, spi_fifo_interrupt_source_t intSrc,
                                         bool enable)
{
    if (intSrc == kSpiRxFifoNearFullInt)
    {
        SPI_BWR_C3_RNFULLIEN(base, (enable == true));
    }
    else
    {
        SPI_BWR_C3_TNEARIEN(base, (enable == true));
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SPI_HAL_GetFifoIntMode
 * This function returns the specific SPI FIFO interrupt setting: enable (true) or disable (false).
 * These FIFO interrupts are the TX FIFO nearly empty and the RX FIFO nearly full.
 *END**************************************************************************/
bool SPI_HAL_GetFifoIntMode(SPI_Type * base, spi_fifo_interrupt_source_t intSrc)
{
    if (intSrc == kSpiRxFifoNearFullInt)
    {
        return SPI_RD_C3_RNFULLIEN(base);
    }
    else
    {
        return SPI_RD_C3_TNEARIEN(base);
    }
 }

/*FUNCTION**********************************************************************
 *
 * Function Name : SPI_HAL_ClearFifoIntUsingBitWrite
 * This function allows the user to clear particular FIFO interrupt sources using the
 * write-1-to-clear feature. The function first determines if SPIx_C3[INTCLR] is enabled
 * as needs to first be set in order to enable the write to clear mode. If not enabled, the
 * function enables this bit, performs the interrupt source clear, then disables the write to
 * clear mode.  The FIFO related interrupt sources that can be cleared using this function are:
 * Receive FIFO full interrupt
 * Receive FIFO nearly full interrupt
 * Transmit FIFO empty interrupt
 * Transmit FIFO nearly empty interrupt
 *END**************************************************************************/
void SPI_HAL_ClearFifoIntUsingBitWrite(SPI_Type * base, spi_w1c_interrupt_t intSrc)
{
    /* First see if SPIx_C3[INTCLR] is set.  This needs to first be set in order
     * to enable the write to clear mode.
     */
    if (!(SPI_RD_C3_INTCLR(base)))
    {
        /* If SPIx_C3[INTCLR] is not set, set it than clear later */
        SPI_BWR_C3_INTCLR(base, true);
        /* Write to the desired clear bit */
        SPI_WR_CI(base, 1U << intSrc);
        /* clear SPIx_C3[INTCLR] */
        SPI_BWR_C3_INTCLR(base, false);
    }
    else
    {
        /* Write to the desired clear bit */
        SPI_WR_CI(base, 1U << intSrc);
    }
 }

#endif /* FSL_FEATURE_SPI_FIFO_SIZE */

#endif /* FSL_FEATURE_SOC_SPI_COUNT */
/*******************************************************************************
 * EOF
 ******************************************************************************/

