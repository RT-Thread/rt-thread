/*
** ###################################################################
**     Build:               b150605
**
**     Abstract:
**         Enumeration value mapping header.
**
**     Copyright (c) 2015 Freescale Semiconductor, Inc.
**     All rights reserved.
**
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
**     http:                 www.freescale.com
**     mail:                 support@freescale.com
**
**     Revisions:
**
** ###################################################################
*/

#if !defined(__FSL_DMA_REQUEST_H__)
#define __FSL_DMA_REQUEST_H__

/*!
 * @addtogroup edma_request
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @brief Structure for the DMA hardware request
 *
 * Defines the structure for the DMA hardware request collections. The user can configure the
 * hardware request into DMAMUX to trigger the DMA transfer accordingly. The index
 * of the hardware request varies according  to the to SoC.
 */
typedef enum _dma_request_source {
#if defined(CPU_MKL13Z32VFM4) || defined(CPU_MKL13Z64VFM4) || defined(CPU_MKL13Z32VFT4) || defined(CPU_MKL13Z64VFT4) || \
    defined(CPU_MKL13Z32VLH4) || defined(CPU_MKL13Z64VLH4) || defined(CPU_MKL13Z32VLK4) || defined(CPU_MKL13Z64VLK4) || \
    defined(CPU_MKL13Z32VMP4) || defined(CPU_MKL13Z64VMP4) || defined(CPU_MKL33Z32VFT4) || defined(CPU_MKL33Z64VFT4) || \
    defined(CPU_MKL33Z32VLH4) || defined(CPU_MKL33Z64VLH4) || defined(CPU_MKL33Z32VLK4) || defined(CPU_MKL33Z64VLK4) || \
    defined(CPU_MKL33Z32VMP4) || defined(CPU_MKL33Z64VMP4)
    kDmaRequestMux0Disable = 0|0x100U, /*!< Disable */
    kDmaRequestMux0Reserved1 = 1|0x100U, /*!< Reserved1 */
    kDmaRequestMux0LPUART0Rx = 2|0x100U, /*!< LPUART0 Receive. */
    kDmaRequestMux0LPUART0Tx = 3|0x100U, /*!< LPUART0 Transmit. */
    kDmaRequestMux0LPUART1Rx = 4|0x100U, /*!< LPUART1 Receive. */
    kDmaRequestMux0LPUART1Tx = 5|0x100U, /*!< LPUART1 Transmit. */
    kDmaRequestMux0UART2Rx = 6|0x100U, /*!< UART2 Receive. */
    kDmaRequestMux0UART2Tx = 7|0x100U, /*!< UART2 Transmit. */
    kDmaRequestMux0Reserved8 = 8|0x100U, /*!< Reserved8 */
    kDmaRequestMux0Reserved9 = 9|0x100U, /*!< Reserved9 */
    kDmaRequestMux0FlexIOChannel0 = 10|0x100U, /*!< FlexIO Channel 0. */
    kDmaRequestMux0FlexIOChannel1 = 11|0x100U, /*!< FlexIO Channel 0. */
    kDmaRequestMux0FlexIOChannel2 = 12|0x100U, /*!< FlexIO Channel 0. */
    kDmaRequestMux0FlexIOChannel3 = 13|0x100U, /*!< FlexIO Channel 0. */
    kDmaRequestMux0Reserved14 = 14|0x100U, /*!< Reserved14 */
    kDmaRequestMux0Reserved15 = 15|0x100U, /*!< Reserved15 */
    kDmaRequestMux0SPI0Rx = 16|0x100U, /*!< SPI0 Receive. */
    kDmaRequestMux0SPI0Tx = 17|0x100U, /*!< SPI0 Transmit. */
    kDmaRequestMux0SPI1Rx = 18|0x100U, /*!< SPI1 Receive. */
    kDmaRequestMux0SPI1Tx = 19|0x100U, /*!< SPI1 Transmit. */
    kDmaRequestMux0Reserved20 = 20|0x100U, /*!< Reserved20 */
    kDmaRequestMux0Reserved21 = 21|0x100U, /*!< Reserved21 */
    kDmaRequestMux0I2C0 = 22|0x100U, /*!< I2C0. */
    kDmaRequestMux0I2C1 = 23|0x100U, /*!< I2C1. */
    kDmaRequestMux0TPM0Channel0 = 24|0x100U, /*!< TPM0 channel 0. */
    kDmaRequestMux0TPM0Channel1 = 25|0x100U, /*!< TPM0 channel 1. */
    kDmaRequestMux0TPM0Channel2 = 26|0x100U, /*!< TPM0 channel 2. */
    kDmaRequestMux0TPM0Channel3 = 27|0x100U, /*!< TPM0 channel 3. */
    kDmaRequestMux0TPM0Channel4 = 28|0x100U, /*!< TPM0 channel 4. */
    kDmaRequestMux0TPM0Channel5 = 29|0x100U, /*!< TPM0 channel 5. */
    kDmaRequestMux0Reserved30 = 30|0x100U, /*!< Reserved30 */
    kDmaRequestMux0Reserved31 = 31|0x100U, /*!< Reserved31 */
    kDmaRequestMux0TPM1Channel0 = 32|0x100U, /*!< TPM1 channel 0. */
    kDmaRequestMux0TPM1Channel1 = 33|0x100U, /*!< TPM1 channel 1. */
    kDmaRequestMux0TPM2Channel0 = 34|0x100U, /*!< TPM2 channel 0. */
    kDmaRequestMux0TPM2Channel1 = 35|0x100U, /*!< TPM2 channel 1. */
    kDmaRequestMux0Reserved36 = 36|0x100U, /*!< Reserved36 */
    kDmaRequestMux0Reserved37 = 37|0x100U, /*!< Reserved37 */
    kDmaRequestMux0Reserved38 = 38|0x100U, /*!< Reserved38 */
    kDmaRequestMux0Reserved39 = 39|0x100U, /*!< Reserved39 */
    kDmaRequestMux0ADC0 = 40|0x100U, /*!< ADC0. */
    kDmaRequestMux0Reserved41 = 41|0x100U, /*!< Reserved41 */
    kDmaRequestMux0CMP0 = 42|0x100U, /*!< CMP0. */
    kDmaRequestMux0Reserved43 = 43|0x100U, /*!< Reserved43 */
    kDmaRequestMux0Reserved44 = 44|0x100U, /*!< Reserved44 */
    kDmaRequestMux0DAC0 = 45|0x100U, /*!< DAC0. */
    kDmaRequestMux0Reserved46 = 46|0x100U, /*!< Reserved46 */
    kDmaRequestMux0Reserved47 = 47|0x100U, /*!< Reserved47 */
    kDmaRequestMux0Reserved48 = 48|0x100U, /*!< Reserved48 */
    kDmaRequestMux0PortA = 49|0x100U, /*!< GPIO Port A. */
    kDmaRequestMux0PortB = 50|0x100U, /*!< GPIO Port B. */
    kDmaRequestMux0PortC = 51|0x100U, /*!< GPIO Port C. */
    kDmaRequestMux0PortD = 52|0x100U, /*!< GPIO Port D. */
    kDmaRequestMux0PortE = 53|0x100U, /*!< GPIO Port E. */
    kDmaRequestMux0TPM0Overflow = 54|0x100U, /*!< TPM0 overflow. */
    kDmaRequestMux0TPM1Overflow = 55|0x100U, /*!< TPM1 overflow. */
    kDmaRequestMux0TPM2Overflow = 56|0x100U, /*!< TPM2 overflow. */
    kDmaRequestMux0Reserved57 = 57|0x100U, /*!< Reserved57 */
    kDmaRequestMux0Reserved58 = 58|0x100U, /*!< Reserved58 */
    kDmaRequestMux0Reserved59 = 59|0x100U, /*!< Reserved59 */
    kDmaRequestMux0AlwaysOn60 = 60|0x100U, /*!< Always enabled. */
    kDmaRequestMux0AlwaysOn61 = 61|0x100U, /*!< Always enabled. */
    kDmaRequestMux0AlwaysOn62 = 62|0x100U, /*!< Always enabled. */
    kDmaRequestMux0AlwaysOn63 = 63|0x100U, /*!< Always enabled. */
#elif defined(CPU_MKL14Z32VFM4) || defined(CPU_MKL14Z64VFM4) || defined(CPU_MKL14Z32VFT4) || defined(CPU_MKL14Z64VFT4) || \
    defined(CPU_MKL14Z32VLH4) || defined(CPU_MKL14Z64VLH4) || defined(CPU_MKL14Z32VLK4) || defined(CPU_MKL14Z64VLK4) || \
    defined(CPU_MKL24Z32VFM4) || defined(CPU_MKL24Z64VFM4) || defined(CPU_MKL24Z32VFT4) || defined(CPU_MKL24Z64VFT4) || \
    defined(CPU_MKL24Z32VLH4) || defined(CPU_MKL24Z64VLH4) || defined(CPU_MKL24Z32VLK4) || defined(CPU_MKL24Z64VLK4)
    kDmaRequestMux0Disable = 0|0x100U, /*!< DMAMUX TriggerDisabled. */
    kDmaRequestMux0Reserved1 = 1|0x100U, /*!< Reserved1 */
    kDmaRequestMux0UART0Rx = 2|0x100U, /*!< UART0 Receive. */
    kDmaRequestMux0LPSCI0Rx = 2|0x100U, /*!< UART0 Receive. */
    kDmaRequestMux0UART0Tx = 3|0x100U, /*!< UART0 Transmit. */
    kDmaRequestMux0LPSCI0Tx = 3|0x100U, /*!< UART0 Transmit. */
    kDmaRequestMux0UART1Rx = 4|0x100U, /*!< UART1 Receive. */
    kDmaRequestMux0UART1Tx = 5|0x100U, /*!< UART1 Transmit. */
    kDmaRequestMux0UART2Rx = 6|0x100U, /*!< UART2 Receive. */
    kDmaRequestMux0UART2Tx = 7|0x100U, /*!< UART2 Transmit. */
    kDmaRequestMux0Reserved8 = 8|0x100U, /*!< Reserved8 */
    kDmaRequestMux0Reserved9 = 9|0x100U, /*!< Reserved9 */
    kDmaRequestMux0Reserved10 = 10|0x100U, /*!< Reserved10 */
    kDmaRequestMux0Reserved11 = 11|0x100U, /*!< Reserved11 */
    kDmaRequestMux0Reserved12 = 12|0x100U, /*!< Reserved12 */
    kDmaRequestMux0Reserved13 = 13|0x100U, /*!< Reserved13 */
    kDmaRequestMux0Reserved14 = 14|0x100U, /*!< Reserved14 */
    kDmaRequestMux0Reserved15 = 15|0x100U, /*!< Reserved15 */
    kDmaRequestMux0SPI0Rx = 16|0x100U, /*!< SPI0 Receive. */
    kDmaRequestMux0SPI0Tx = 17|0x100U, /*!< SPI0 Transmit. */
    kDmaRequestMux0SPI1Rx = 18|0x100U, /*!< SPI1 Receive. */
    kDmaRequestMux0SPI1Tx = 19|0x100U, /*!< SPI1 Transmit. */
    kDmaRequestMux0Reserved20 = 20|0x100U, /*!< Reserved20 */
    kDmaRequestMux0Reserved21 = 21|0x100U, /*!< Reserved21 */
    kDmaRequestMux0I2C0 = 22|0x100U, /*!< I2C0. */
    kDmaRequestMux0I2C1 = 23|0x100U, /*!< I2C1. */
    kDmaRequestMux0TPM0Channel0 = 24|0x100U, /*!< TPM0 C0V. */
    kDmaRequestMux0TPM0Channel1 = 25|0x100U, /*!< TPM0 C1V. */
    kDmaRequestMux0TPM0Channel2 = 26|0x100U, /*!< TPM0 C2V. */
    kDmaRequestMux0TPM0Channel3 = 27|0x100U, /*!< TPM0 C3V. */
    kDmaRequestMux0TPM0Channel4 = 28|0x100U, /*!< TPM0 C4V. */
    kDmaRequestMux0TPM0Channel5 = 29|0x100U, /*!< TPM0 C5V. */
    kDmaRequestMux0Reserved30 = 30|0x100U, /*!< Reserved30 */
    kDmaRequestMux0Reserved31 = 31|0x100U, /*!< Reserved31 */
    kDmaRequestMux0TPM1Channel0 = 32|0x100U, /*!< TPM1 C0V. */
    kDmaRequestMux0TPM1Channel1 = 33|0x100U, /*!< TPM1 C1V. */
    kDmaRequestMux0TPM2Channel0 = 34|0x100U, /*!< TPM2 C0V. */
    kDmaRequestMux0TPM2Channel1 = 35|0x100U, /*!< TPM2 C1V. */
    kDmaRequestMux0Reserved36 = 36|0x100U, /*!< Reserved36 */
    kDmaRequestMux0Reserved37 = 37|0x100U, /*!< Reserved37 */
    kDmaRequestMux0Reserved38 = 38|0x100U, /*!< Reserved38 */
    kDmaRequestMux0Reserved39 = 39|0x100U, /*!< Reserved39 */
    kDmaRequestMux0ADC0 = 40|0x100U, /*!< ADC0. */
    kDmaRequestMux0Reserved41 = 41|0x100U, /*!< Reserved41 */
    kDmaRequestMux0CMP0 = 42|0x100U, /*!< CMP0. */
    kDmaRequestMux0Reserved43 = 43|0x100U, /*!< Reserved43 */
    kDmaRequestMux0Reserved44 = 44|0x100U, /*!< Reserved44 */
    kDmaRequestMux0Reserved45 = 45|0x100U, /*!< Reserved45 */
    kDmaRequestMux0Reserved46 = 46|0x100U, /*!< Reserved46 */
    kDmaRequestMux0Reserved47 = 47|0x100U, /*!< Reserved47 */
    kDmaRequestMux0Reserved48 = 48|0x100U, /*!< Reserved48 */
    kDmaRequestMux0PortA = 49|0x100U, /*!< PTA. */
    kDmaRequestMux0Reserved50 = 50|0x100U, /*!< Reserved50 */
    kDmaRequestMux0Reserved51 = 51|0x100U, /*!< Reserved51 */
    kDmaRequestMux0PortD = 52|0x100U, /*!< PTD. */
    kDmaRequestMux0Reserved53 = 53|0x100U, /*!< Reserved53 */
    kDmaRequestMux0TPM0Overflow = 54|0x100U, /*!< TPM0. */
    kDmaRequestMux0TPM1Overflow = 55|0x100U, /*!< TPM1. */
    kDmaRequestMux0TPM2Overflow = 56|0x100U, /*!< TPM2. */
    kDmaRequestMux0Reserved57 = 57|0x100U, /*!< Reserved57 */
    kDmaRequestMux0Reserved58 = 58|0x100U, /*!< Reserved58 */
    kDmaRequestMux0Reserved59 = 59|0x100U, /*!< Reserved59 */
    kDmaRequestMux0AlwaysOn60 = 60|0x100U, /*!< DMAMUX Always Enabled slot. */
    kDmaRequestMux0AlwaysOn61 = 61|0x100U, /*!< DMAMUX Always Enabled slot. */
    kDmaRequestMux0AlwaysOn62 = 62|0x100U, /*!< DMAMUX Always Enabled slot. */
    kDmaRequestMux0AlwaysOn63 = 63|0x100U, /*!< DMAMUX Always Enabled slot. */
#elif defined(CPU_MKL15Z128CAD4) || defined(CPU_MKL15Z32VFM4) || defined(CPU_MKL15Z64VFM4) || defined(CPU_MKL15Z128VFM4) || \
    defined(CPU_MKL15Z32VFT4) || defined(CPU_MKL15Z64VFT4) || defined(CPU_MKL15Z128VFT4) || defined(CPU_MKL15Z32VLH4) || \
    defined(CPU_MKL15Z64VLH4) || defined(CPU_MKL15Z128VLH4) || defined(CPU_MKL15Z32VLK4) || defined(CPU_MKL15Z64VLK4) || \
    defined(CPU_MKL15Z128VLK4) || defined(CPU_MKL25Z32VFM4) || defined(CPU_MKL25Z64VFM4) || defined(CPU_MKL25Z128VFM4) || \
    defined(CPU_MKL25Z32VFT4) || defined(CPU_MKL25Z64VFT4) || defined(CPU_MKL25Z128VFT4) || defined(CPU_MKL25Z32VLH4) || \
    defined(CPU_MKL25Z64VLH4) || defined(CPU_MKL25Z128VLH4) || defined(CPU_MKL25Z32VLK4) || defined(CPU_MKL25Z64VLK4) || \
    defined(CPU_MKL25Z128VLK4)
    kDmaRequestMux0Disable = 0|0x100U, /*!< DMAMUX TriggerDisabled. */
    kDmaRequestMux0Reserved1 = 1|0x100U, /*!< Reserved1 */
    kDmaRequestMux0UART0Rx = 2|0x100U, /*!< UART0 Receive. */
    kDmaRequestMux0LPSCI0Rx = 2|0x100U, /*!< UART0 Receive. */
    kDmaRequestMux0UART0Tx = 3|0x100U, /*!< UART0 Transmit. */
    kDmaRequestMux0LPSCI0Tx = 3|0x100U, /*!< UART0 Transmit. */
    kDmaRequestMux0UART1Rx = 4|0x100U, /*!< UART1 Receive. */
    kDmaRequestMux0UART1Tx = 5|0x100U, /*!< UART1 Transmit. */
    kDmaRequestMux0UART2Rx = 6|0x100U, /*!< UART2 Receive. */
    kDmaRequestMux0UART2Tx = 7|0x100U, /*!< UART2 Transmit. */
    kDmaRequestMux0Reserved8 = 8|0x100U, /*!< Reserved8 */
    kDmaRequestMux0Reserved9 = 9|0x100U, /*!< Reserved9 */
    kDmaRequestMux0Reserved10 = 10|0x100U, /*!< Reserved10 */
    kDmaRequestMux0Reserved11 = 11|0x100U, /*!< Reserved11 */
    kDmaRequestMux0Reserved12 = 12|0x100U, /*!< Reserved12 */
    kDmaRequestMux0Reserved13 = 13|0x100U, /*!< Reserved13 */
    kDmaRequestMux0Reserved14 = 14|0x100U, /*!< Reserved14 */
    kDmaRequestMux0Reserved15 = 15|0x100U, /*!< Reserved15 */
    kDmaRequestMux0SPI0Rx = 16|0x100U, /*!< SPI0 Receive. */
    kDmaRequestMux0SPI0Tx = 17|0x100U, /*!< SPI0 Transmit. */
    kDmaRequestMux0SPI1Rx = 18|0x100U, /*!< SPI1 Receive. */
    kDmaRequestMux0SPI1Tx = 19|0x100U, /*!< SPI1 Transmit. */
    kDmaRequestMux0Reserved20 = 20|0x100U, /*!< Reserved20 */
    kDmaRequestMux0Reserved21 = 21|0x100U, /*!< Reserved21 */
    kDmaRequestMux0I2C0 = 22|0x100U, /*!< I2C0. */
    kDmaRequestMux0I2C1 = 23|0x100U, /*!< I2C1. */
    kDmaRequestMux0TPM0Channel0 = 24|0x100U, /*!< TPM0 C0V. */
    kDmaRequestMux0TPM0Channel1 = 25|0x100U, /*!< TPM0 C1V. */
    kDmaRequestMux0TPM0Channel2 = 26|0x100U, /*!< TPM0 C2V. */
    kDmaRequestMux0TPM0Channel3 = 27|0x100U, /*!< TPM0 C3V. */
    kDmaRequestMux0TPM0Channel4 = 28|0x100U, /*!< TPM0 C4V. */
    kDmaRequestMux0TPM0Channel5 = 29|0x100U, /*!< TPM0 C5V. */
    kDmaRequestMux0Reserved30 = 30|0x100U, /*!< Reserved30 */
    kDmaRequestMux0Reserved31 = 31|0x100U, /*!< Reserved31 */
    kDmaRequestMux0TPM1Channel0 = 32|0x100U, /*!< TPM1 C0V. */
    kDmaRequestMux0TPM1Channel1 = 33|0x100U, /*!< TPM1 C1V. */
    kDmaRequestMux0TPM2Channel0 = 34|0x100U, /*!< TPM2 C0V. */
    kDmaRequestMux0TPM2Channel1 = 35|0x100U, /*!< TPM2 C1V. */
    kDmaRequestMux0Reserved36 = 36|0x100U, /*!< Reserved36 */
    kDmaRequestMux0Reserved37 = 37|0x100U, /*!< Reserved37 */
    kDmaRequestMux0Reserved38 = 38|0x100U, /*!< Reserved38 */
    kDmaRequestMux0Reserved39 = 39|0x100U, /*!< Reserved39 */
    kDmaRequestMux0ADC0 = 40|0x100U, /*!< ADC0. */
    kDmaRequestMux0Reserved41 = 41|0x100U, /*!< Reserved41 */
    kDmaRequestMux0CMP0 = 42|0x100U, /*!< CMP0. */
    kDmaRequestMux0Reserved43 = 43|0x100U, /*!< Reserved43 */
    kDmaRequestMux0Reserved44 = 44|0x100U, /*!< Reserved44 */
    kDmaRequestMux0DAC0 = 45|0x100U, /*!< DAC0. */
    kDmaRequestMux0Reserved46 = 46|0x100U, /*!< Reserved46 */
    kDmaRequestMux0Reserved47 = 47|0x100U, /*!< Reserved47 */
    kDmaRequestMux0Reserved48 = 48|0x100U, /*!< Reserved48 */
    kDmaRequestMux0PortA = 49|0x100U, /*!< PTA. */
    kDmaRequestMux0Reserved50 = 50|0x100U, /*!< Reserved50 */
    kDmaRequestMux0Reserved51 = 51|0x100U, /*!< Reserved51 */
    kDmaRequestMux0PortD = 52|0x100U, /*!< PTD. */
    kDmaRequestMux0Reserved53 = 53|0x100U, /*!< Reserved53 */
    kDmaRequestMux0TPM0Overflow = 54|0x100U, /*!< TPM0. */
    kDmaRequestMux0TPM1Overflow = 55|0x100U, /*!< TPM1. */
    kDmaRequestMux0TPM2Overflow = 56|0x100U, /*!< TPM2. */
    kDmaRequestMux0TSI0 = 57|0x100U, /*!< TSI0. */
    kDmaRequestMux0Reserved58 = 58|0x100U, /*!< Reserved58 */
    kDmaRequestMux0Reserved59 = 59|0x100U, /*!< Reserved59 */
    kDmaRequestMux0AlwaysOn60 = 60|0x100U, /*!< DMAMUX Always Enabled slot. */
    kDmaRequestMux0AlwaysOn61 = 61|0x100U, /*!< DMAMUX Always Enabled slot. */
    kDmaRequestMux0AlwaysOn62 = 62|0x100U, /*!< DMAMUX Always Enabled slot. */
    kDmaRequestMux0AlwaysOn63 = 63|0x100U, /*!< DMAMUX Always Enabled slot. */
#elif defined(CPU_MKL16Z32VFM4) || defined(CPU_MKL16Z64VFM4) || defined(CPU_MKL16Z128VFM4) || defined(CPU_MKL16Z32VFT4) || \
    defined(CPU_MKL16Z64VFT4) || defined(CPU_MKL16Z128VFT4) || defined(CPU_MKL16Z32VLH4) || defined(CPU_MKL16Z64VLH4) || \
    defined(CPU_MKL16Z128VLH4) || defined(CPU_MKL26Z128CAL4) || defined(CPU_MKL26Z32VFM4) || defined(CPU_MKL26Z64VFM4) || \
    defined(CPU_MKL26Z128VFM4) || defined(CPU_MKL26Z32VFT4) || defined(CPU_MKL26Z64VFT4) || defined(CPU_MKL26Z128VFT4) || \
    defined(CPU_MKL26Z32VLH4) || defined(CPU_MKL26Z64VLH4) || defined(CPU_MKL26Z128VLH4)
    kDmaRequestMux0Disable = 0|0x100U, /*!< Disable */
    kDmaRequestMux0Reserved1 = 1|0x100U, /*!< Reserved1 */
    kDmaRequestMux0UART0Rx = 2|0x100U, /*!< UART0 receive complete */
    kDmaRequestMux0LPSCI0Rx = 2|0x100U, /*!< UART0 receive complete */
    kDmaRequestMux0UART0Tx = 3|0x100U, /*!< UART0 transmit complete */
    kDmaRequestMux0LPSCI0Tx = 3|0x100U, /*!< UART0 transmit complete */
    kDmaRequestMux0UART1Rx = 4|0x100U, /*!< UART1 receive complete */
    kDmaRequestMux0UART1Tx = 5|0x100U, /*!< UART1 transmit complete */
    kDmaRequestMux0UART2Rx = 6|0x100U, /*!< UART2 receive complete */
    kDmaRequestMux0UART2Tx = 7|0x100U, /*!< UART2 transmit complete */
    kDmaRequestMux0Reserved8 = 8|0x100U, /*!< Reserved8 */
    kDmaRequestMux0Reserved9 = 9|0x100U, /*!< Reserved9 */
    kDmaRequestMux0Reserved10 = 10|0x100U, /*!< Reserved10 */
    kDmaRequestMux0Reserved11 = 11|0x100U, /*!< Reserved11 */
    kDmaRequestMux0Reserved12 = 12|0x100U, /*!< Reserved12 */
    kDmaRequestMux0Reserved13 = 13|0x100U, /*!< Reserved13 */
    kDmaRequestMux0I2S0Rx = 14|0x100U, /*!< I2S0 receive complete */
    kDmaRequestMux0I2S0Tx = 15|0x100U, /*!< I2S0 transmit complete */
    kDmaRequestMux0SPI0Rx = 16|0x100U, /*!< SPI0 receive complete */
    kDmaRequestMux0SPI0Tx = 17|0x100U, /*!< SPI0 transmit complete */
    kDmaRequestMux0SPI1Rx = 18|0x100U, /*!< SPI1 receive complete */
    kDmaRequestMux0SPI1Tx = 19|0x100U, /*!< SPI1 transmit complete */
    kDmaRequestMux0Reserved20 = 20|0x100U, /*!< Reserved20 */
    kDmaRequestMux0Reserved21 = 21|0x100U, /*!< Reserved21 */
    kDmaRequestMux0I2C0 = 22|0x100U, /*!< I2C0 transmission complete */
    kDmaRequestMux0I2C1 = 23|0x100U, /*!< I2C1 transmission complete */
    kDmaRequestMux0TPM0Channel0 = 24|0x100U, /*!< TPM0 channel 0 event (CMP or CAP) */
    kDmaRequestMux0TPM0Channel1 = 25|0x100U, /*!< TPM0 channel 1 event (CMP or CAP) */
    kDmaRequestMux0TPM0Channel2 = 26|0x100U, /*!< TPM0 channel 2 event (CMP or CAP) */
    kDmaRequestMux0TPM0Channel3 = 27|0x100U, /*!< TPM0 channel 3 event (CMP or CAP) */
    kDmaRequestMux0TPM0Channel4 = 28|0x100U, /*!< TPM0 channel 4 event (CMP or CAP) */
    kDmaRequestMux0TPM0Channel5 = 29|0x100U, /*!< TPM0 channel 5 event (CMP or CAP) */
    kDmaRequestMux0Reserved30 = 30|0x100U, /*!< Reserved30 */
    kDmaRequestMux0Reserved31 = 31|0x100U, /*!< Reserved31 */
    kDmaRequestMux0TPM1Channel0 = 32|0x100U, /*!< TPM1 channel 0 event (CMP or CAP) */
    kDmaRequestMux0TPM1Channel1 = 33|0x100U, /*!< TPM1 channel 1 event (CMP or CAP) */
    kDmaRequestMux0TPM2Channel0 = 34|0x100U, /*!< TPM2 channel 0 event (CMP or CAP) */
    kDmaRequestMux0TPM2Channel1 = 35|0x100U, /*!< TPM2 channel 1 event (CMP or CAP) */
    kDmaRequestMux0Reserved36 = 36|0x100U, /*!< Reserved36 */
    kDmaRequestMux0Reserved37 = 37|0x100U, /*!< Reserved37 */
    kDmaRequestMux0Reserved38 = 38|0x100U, /*!< Reserved38 */
    kDmaRequestMux0Reserved39 = 39|0x100U, /*!< Reserved39 */
    kDmaRequestMux0ADC0 = 40|0x100U, /*!< ADC0 conversion complete */
    kDmaRequestMux0Reserved41 = 41|0x100U, /*!< Reserved41 */
    kDmaRequestMux0CMP0 = 42|0x100U, /*!< CMP0 Output */
    kDmaRequestMux0Reserved43 = 43|0x100U, /*!< Reserved43 */
    kDmaRequestMux0Reserved44 = 44|0x100U, /*!< Reserved44 */
    kDmaRequestMux0DAC0 = 45|0x100U, /*!< DAC0 buffer pointer reaches upper or lower limit */
    kDmaRequestMux0Reserved46 = 46|0x100U, /*!< Reserved46 */
    kDmaRequestMux0Reserved47 = 47|0x100U, /*!< Reserved47 */
    kDmaRequestMux0Reserved48 = 48|0x100U, /*!< Reserved48 */
    kDmaRequestMux0PortA = 49|0x100U, /*!< PORTA rising, falling or both edges */
    kDmaRequestMux0Reserved50 = 50|0x100U, /*!< Reserved50 */
    kDmaRequestMux0PortC = 51|0x100U, /*!< PORTC rising, falling or both edges */
    kDmaRequestMux0PortD = 52|0x100U, /*!< PORTD rising, falling or both edges */
    kDmaRequestMux0Reserved53 = 53|0x100U, /*!< Reserved53 */
    kDmaRequestMux0TPM0Overflow = 54|0x100U, /*!< TPM0 all channels output compare ORed together */
    kDmaRequestMux0TPM1Overflow = 55|0x100U, /*!< TPM1 all channels output compare ORed together */
    kDmaRequestMux0TPM2Overflow = 56|0x100U, /*!< TPM2 all channels output compare ORed together */
    kDmaRequestMux0Reserved57 = 57|0x100U, /*!< Reserved57 */
    kDmaRequestMux0Reserved58 = 58|0x100U, /*!< Reserved58 */
    kDmaRequestMux0Reserved59 = 59|0x100U, /*!< Reserved59 */
    kDmaRequestMux0AlwaysOn60 = 60|0x100U, /*!< Always enabled 60 */
    kDmaRequestMux0AlwaysOn61 = 61|0x100U, /*!< Always enabled 61 */
    kDmaRequestMux0AlwaysOn62 = 62|0x100U, /*!< Always enabled 62 */
    kDmaRequestMux0AlwaysOn63 = 63|0x100U, /*!< Always enabled 63 */
#elif defined(CPU_MKL16Z256VLH4) || defined(CPU_MKL16Z256VMP4) || defined(CPU_MKL26Z256VLH4) || defined(CPU_MKL26Z128VLL4) || \
    defined(CPU_MKL26Z256VLL4) || defined(CPU_MKL26Z128VMC4) || defined(CPU_MKL26Z256VMC4) || defined(CPU_MKL26Z256VMP4) || \
    defined(CPU_MKL36Z64VLH4) || defined(CPU_MKL36Z128VLH4) || defined(CPU_MKL36Z256VLH4) || defined(CPU_MKL36Z64VLL4) || \
    defined(CPU_MKL36Z128VLL4) || defined(CPU_MKL36Z256VLL4) || defined(CPU_MKL36Z128VMC4) || defined(CPU_MKL36Z256VMC4) || \
    defined(CPU_MKL36Z256VMP4) || defined(CPU_MKL46Z128VLH4) || defined(CPU_MKL46Z256VLH4) || defined(CPU_MKL46Z128VLL4) || \
    defined(CPU_MKL46Z256VLL4) || defined(CPU_MKL46Z128VMC4) || defined(CPU_MKL46Z256VMC4) || defined(CPU_MKL46Z256VMP4)
    kDmaRequestMux0Disable = 0|0x100U, /*!< Disable */
    kDmaRequestMux0Reserved1 = 1|0x100U, /*!< Reserved1 */
    kDmaRequestMux0UART0Rx = 2|0x100U, /*!< UART0 receive complete */
    kDmaRequestMux0LPSCI0Rx = 2|0x100U, /*!< UART0 receive complete */
    kDmaRequestMux0UART0Tx = 3|0x100U, /*!< UART0 transmit complete */
    kDmaRequestMux0LPSCI0Tx = 3|0x100U, /*!< UART0 transmit complete */
    kDmaRequestMux0UART1Rx = 4|0x100U, /*!< UART1 receive complete */
    kDmaRequestMux0UART1Tx = 5|0x100U, /*!< UART1 transmit complete */
    kDmaRequestMux0UART2Rx = 6|0x100U, /*!< UART2 receive complete */
    kDmaRequestMux0UART2Tx = 7|0x100U, /*!< UART2 transmit complete */
    kDmaRequestMux0Reserved8 = 8|0x100U, /*!< Reserved8 */
    kDmaRequestMux0Reserved9 = 9|0x100U, /*!< Reserved9 */
    kDmaRequestMux0Reserved10 = 10|0x100U, /*!< Reserved10 */
    kDmaRequestMux0Reserved11 = 11|0x100U, /*!< Reserved11 */
    kDmaRequestMux0Reserved12 = 12|0x100U, /*!< Reserved12 */
    kDmaRequestMux0Reserved13 = 13|0x100U, /*!< Reserved13 */
    kDmaRequestMux0I2S0Rx = 14|0x100U, /*!< I2S0 receive complete */
    kDmaRequestMux0I2S0Tx = 15|0x100U, /*!< I2S0 transmit complete */
    kDmaRequestMux0SPI0Rx = 16|0x100U, /*!< SPI0 receive complete */
    kDmaRequestMux0SPI0Tx = 17|0x100U, /*!< SPI0 transmit complete */
    kDmaRequestMux0SPI1Rx = 18|0x100U, /*!< SPI1 receive complete */
    kDmaRequestMux0SPI1Tx = 19|0x100U, /*!< SPI1 transmit complete */
    kDmaRequestMux0Reserved20 = 20|0x100U, /*!< Reserved20 */
    kDmaRequestMux0Reserved21 = 21|0x100U, /*!< Reserved21 */
    kDmaRequestMux0I2C0 = 22|0x100U, /*!< I2C0 transmission complete */
    kDmaRequestMux0I2C1 = 23|0x100U, /*!< I2C1 transmission complete */
    kDmaRequestMux0TPM0Channel0 = 24|0x100U, /*!< TPM0 channel 0 event (CMP or CAP) */
    kDmaRequestMux0TPM0Channel1 = 25|0x100U, /*!< TPM0 channel 1 event (CMP or CAP) */
    kDmaRequestMux0TPM0Channel2 = 26|0x100U, /*!< TPM0 channel 2 event (CMP or CAP) */
    kDmaRequestMux0TPM0Channel3 = 27|0x100U, /*!< TPM0 channel 3 event (CMP or CAP) */
    kDmaRequestMux0TPM0Channel4 = 28|0x100U, /*!< TPM0 channel 4 event (CMP or CAP) */
    kDmaRequestMux0TPM0Channel5 = 29|0x100U, /*!< TPM0 channel 5 event (CMP or CAP) */
    kDmaRequestMux0Reserved30 = 30|0x100U, /*!< Reserved30 */
    kDmaRequestMux0Reserved31 = 31|0x100U, /*!< Reserved31 */
    kDmaRequestMux0TPM1Channel0 = 32|0x100U, /*!< TPM1 channel 0 event (CMP or CAP) */
    kDmaRequestMux0TPM1Channel1 = 33|0x100U, /*!< TPM1 channel 1 event (CMP or CAP) */
    kDmaRequestMux0TPM2Channel0 = 34|0x100U, /*!< TPM2 channel 0 event (CMP or CAP) */
    kDmaRequestMux0TPM2Channel1 = 35|0x100U, /*!< TPM2 channel 1 event (CMP or CAP) */
    kDmaRequestMux0Reserved36 = 36|0x100U, /*!< Reserved36 */
    kDmaRequestMux0Reserved37 = 37|0x100U, /*!< Reserved37 */
    kDmaRequestMux0Reserved38 = 38|0x100U, /*!< Reserved38 */
    kDmaRequestMux0Reserved39 = 39|0x100U, /*!< Reserved39 */
    kDmaRequestMux0ADC0 = 40|0x100U, /*!< ADC0 conversion complete */
    kDmaRequestMux0Reserved41 = 41|0x100U, /*!< Reserved41 */
    kDmaRequestMux0CMP0 = 42|0x100U, /*!< CMP0 Output */
    kDmaRequestMux0Reserved43 = 43|0x100U, /*!< Reserved43 */
    kDmaRequestMux0Reserved44 = 44|0x100U, /*!< Reserved44 */
    kDmaRequestMux0DAC0 = 45|0x100U, /*!< DAC0 buffer pointer reaches upper or lower limit */
    kDmaRequestMux0Reserved46 = 46|0x100U, /*!< Reserved46 */
    kDmaRequestMux0Reserved47 = 47|0x100U, /*!< Reserved47 */
    kDmaRequestMux0Reserved48 = 48|0x100U, /*!< Reserved48 */
    kDmaRequestMux0PortA = 49|0x100U, /*!< PORTA rising, falling or both edges */
    kDmaRequestMux0Reserved50 = 50|0x100U, /*!< Reserved50 */
    kDmaRequestMux0PortC = 51|0x100U, /*!< PORTC rising, falling or both edges */
    kDmaRequestMux0PortD = 52|0x100U, /*!< PORTD rising, falling or both edges */
    kDmaRequestMux0Reserved53 = 53|0x100U, /*!< Reserved53 */
    kDmaRequestMux0TPM0Overflow = 54|0x100U, /*!< TPM0 overflow */
    kDmaRequestMux0TPM1Overflow = 55|0x100U, /*!< TPM1 overflow */
    kDmaRequestMux0TPM2Overflow = 56|0x100U, /*!< TPM2 overflow */
    kDmaRequestMux0TSI = 57|0x100U, /*!< TSI0 event */
    kDmaRequestMux0Reserved58 = 58|0x100U, /*!< Reserved58 */
    kDmaRequestMux0Reserved59 = 59|0x100U, /*!< Reserved59 */
    kDmaRequestMux0AlwaysOn60 = 60|0x100U, /*!< Always enabled 60 */
    kDmaRequestMux0AlwaysOn61 = 61|0x100U, /*!< Always enabled 61 */
    kDmaRequestMux0AlwaysOn62 = 62|0x100U, /*!< Always enabled 62 */
    kDmaRequestMux0AlwaysOn63 = 63|0x100U, /*!< Always enabled 63 */
#elif defined(CPU_MKL17Z128VFM4) || defined(CPU_MKL17Z256VFM4) || defined(CPU_MKL17Z128VFT4) || defined(CPU_MKL17Z256VFT4) || \
    defined(CPU_MKL17Z128VLH4) || defined(CPU_MKL17Z256VLH4) || defined(CPU_MKL17Z128VMP4) || defined(CPU_MKL17Z256VMP4) || \
    defined(CPU_MKL27Z128VFM4) || defined(CPU_MKL27Z256VFM4) || defined(CPU_MKL27Z128VFT4) || defined(CPU_MKL27Z256VFT4) || \
    defined(CPU_MKL27Z128VLH4) || defined(CPU_MKL27Z256VLH4) || defined(CPU_MKL27Z128VMP4) || defined(CPU_MKL27Z256VMP4) || \
    defined(CPU_MKL33Z128VLH4) || defined(CPU_MKL33Z256VLH4) || defined(CPU_MKL33Z128VMP4) || defined(CPU_MKL33Z256VMP4) || \
    defined(CPU_MKL43Z128VLH4) || defined(CPU_MKL43Z256VLH4) || defined(CPU_MKL43Z128VMP4) || defined(CPU_MKL43Z256VMP4)
    kDmaRequestMux0Disable = 0|0x100U, /*!< Disable */
    kDmaRequestMux0Reserved1 = 1|0x100U, /*!< Reserved1 */
    kDmaRequestMux0LPUART0Rx = 2|0x100U, /*!< LPUART0 Receive. */
    kDmaRequestMux0LPUART0Tx = 3|0x100U, /*!< LPUART0 Transmit. */
    kDmaRequestMux0LPUART1Rx = 4|0x100U, /*!< LPUART1 Receive. */
    kDmaRequestMux0LPUART1Tx = 5|0x100U, /*!< LPUART1 Transmit. */
    kDmaRequestMux0UART2Rx = 6|0x100U, /*!< UART2 Receive. */
    kDmaRequestMux0UART2Tx = 7|0x100U, /*!< UART2 Transmit. */
    kDmaRequestMux0Reserved8 = 8|0x100U, /*!< Reserved8 */
    kDmaRequestMux0Reserved9 = 9|0x100U, /*!< Reserved9 */
    kDmaRequestMux0FlexIOChannel0 = 10|0x100U, /*!< FlexIO Channel 0. */
    kDmaRequestMux0FlexIOChannel1 = 11|0x100U, /*!< FlexIO Channel 0. */
    kDmaRequestMux0FlexIOChannel2 = 12|0x100U, /*!< FlexIO Channel 0. */
    kDmaRequestMux0FlexIOChannel3 = 13|0x100U, /*!< FlexIO Channel 0. */
    kDmaRequestMux0I2S0Rx = 14|0x100U, /*!< I2S0 Receive. */
    kDmaRequestMux0I2S0Tx = 15|0x100U, /*!< I2S0 Transmit. */
    kDmaRequestMux0SPI0Rx = 16|0x100U, /*!< SPI0 Receive. */
    kDmaRequestMux0SPI0Tx = 17|0x100U, /*!< SPI0 Transmit. */
    kDmaRequestMux0SPI1Rx = 18|0x100U, /*!< SPI1 Receive. */
    kDmaRequestMux0SPI1Tx = 19|0x100U, /*!< SPI1 Transmit. */
    kDmaRequestMux0Reserved20 = 20|0x100U, /*!< Reserved20 */
    kDmaRequestMux0Reserved21 = 21|0x100U, /*!< Reserved21 */
    kDmaRequestMux0I2C0 = 22|0x100U, /*!< I2C0. */
    kDmaRequestMux0I2C1 = 23|0x100U, /*!< I2C1. */
    kDmaRequestMux0TPM0Channel0 = 24|0x100U, /*!< TPM0 channel 0. */
    kDmaRequestMux0TPM0Channel1 = 25|0x100U, /*!< TPM0 channel 1. */
    kDmaRequestMux0TPM0Channel2 = 26|0x100U, /*!< TPM0 channel 2. */
    kDmaRequestMux0TPM0Channel3 = 27|0x100U, /*!< TPM0 channel 3. */
    kDmaRequestMux0TPM0Channel4 = 28|0x100U, /*!< TPM0 channel 4. */
    kDmaRequestMux0TPM0Channel5 = 29|0x100U, /*!< TPM0 channel 5. */
    kDmaRequestMux0Reserved30 = 30|0x100U, /*!< Reserved30 */
    kDmaRequestMux0Reserved31 = 31|0x100U, /*!< Reserved31 */
    kDmaRequestMux0TPM1Channel0 = 32|0x100U, /*!< TPM1 channel 0. */
    kDmaRequestMux0TPM1Channel1 = 33|0x100U, /*!< TPM1 channel 1. */
    kDmaRequestMux0TPM2Channel0 = 34|0x100U, /*!< TPM2 channel 0. */
    kDmaRequestMux0TPM2Channel1 = 35|0x100U, /*!< TPM2 channel 1. */
    kDmaRequestMux0Reserved36 = 36|0x100U, /*!< Reserved36 */
    kDmaRequestMux0Reserved37 = 37|0x100U, /*!< Reserved37 */
    kDmaRequestMux0Reserved38 = 38|0x100U, /*!< Reserved38 */
    kDmaRequestMux0Reserved39 = 39|0x100U, /*!< Reserved39 */
    kDmaRequestMux0ADC0 = 40|0x100U, /*!< ADC0. */
    kDmaRequestMux0Reserved41 = 41|0x100U, /*!< Reserved41 */
    kDmaRequestMux0CMP0 = 42|0x100U, /*!< CMP0. */
    kDmaRequestMux0Reserved43 = 43|0x100U, /*!< Reserved43 */
    kDmaRequestMux0Reserved44 = 44|0x100U, /*!< Reserved44 */
    kDmaRequestMux0DAC0 = 45|0x100U, /*!< DAC0. */
    kDmaRequestMux0Reserved46 = 46|0x100U, /*!< Reserved46 */
    kDmaRequestMux0Reserved47 = 47|0x100U, /*!< Reserved47 */
    kDmaRequestMux0Reserved48 = 48|0x100U, /*!< Reserved48 */
    kDmaRequestMux0PortA = 49|0x100U, /*!< GPIO Port A. */
    kDmaRequestMux0Reserved50 = 50|0x100U, /*!< Reserved50 */
    kDmaRequestMux0PortC = 51|0x100U, /*!< GPIO Port C. */
    kDmaRequestMux0PortD = 52|0x100U, /*!< GPIO Port D. */
    kDmaRequestMux0Reserved53 = 53|0x100U, /*!< Reserved53 */
    kDmaRequestMux0TPM0Overflow = 54|0x100U, /*!< TPM0 overflow. */
    kDmaRequestMux0TPM1Overflow = 55|0x100U, /*!< TPM1 overflow. */
    kDmaRequestMux0TPM2Overflow = 56|0x100U, /*!< TPM2 overflow. */
    kDmaRequestMux0Reserved57 = 57|0x100U, /*!< Reserved57 */
    kDmaRequestMux0Reserved58 = 58|0x100U, /*!< Reserved58 */
    kDmaRequestMux0Reserved59 = 59|0x100U, /*!< Reserved59 */
    kDmaRequestMux0AlwaysOn60 = 60|0x100U, /*!< Always enabled. */
    kDmaRequestMux0AlwaysOn61 = 61|0x100U, /*!< Always enabled. */
    kDmaRequestMux0AlwaysOn62 = 62|0x100U, /*!< Always enabled. */
    kDmaRequestMux0AlwaysOn63 = 63|0x100U, /*!< Always enabled. */
#elif defined(CPU_MKL17Z32VDA4) || defined(CPU_MKL17Z64VDA4) || defined(CPU_MKL17Z32VFM4) || defined(CPU_MKL17Z64VFM4) || \
    defined(CPU_MKL17Z32VFT4) || defined(CPU_MKL17Z64VFT4) || defined(CPU_MKL17Z32VLH4) || defined(CPU_MKL17Z64VLH4) || \
    defined(CPU_MKL17Z32VMP4) || defined(CPU_MKL17Z64VMP4) || defined(CPU_MKL27Z32VDA4) || defined(CPU_MKL27Z64VDA4) || \
    defined(CPU_MKL27Z32VFM4) || defined(CPU_MKL27Z64VFM4) || defined(CPU_MKL27Z32VFT4) || defined(CPU_MKL27Z64VFT4) || \
    defined(CPU_MKL27Z32VLH4) || defined(CPU_MKL27Z64VLH4) || defined(CPU_MKL27Z32VMP4) || defined(CPU_MKL27Z64VMP4)
    kDmaRequestMux0Disable = 0|0x100U, /*!< DMAMUX TriggerDisabled. */
    kDmaRequestMux0Reserved1 = 1|0x100U, /*!< Reserved1 */
    kDmaRequestMux0LPUART0Rx = 2|0x100U, /*!< LPUART0 Receive. */
    kDmaRequestMux0LPUART0Tx = 3|0x100U, /*!< LPUART0 Transmit. */
    kDmaRequestMux0LPUART1Rx = 4|0x100U, /*!< LPUART1 Receive. */
    kDmaRequestMux0LPUART1Tx = 5|0x100U, /*!< LPUART1 Transmit. */
    kDmaRequestMux0UART2Rx = 6|0x100U, /*!< UART2 Receive. */
    kDmaRequestMux0UART2Tx = 7|0x100U, /*!< UART2 Transmit. */
    kDmaRequestMux0Reserved8 = 8|0x100U, /*!< Reserved8 */
    kDmaRequestMux0Reserved9 = 9|0x100U, /*!< Reserved9 */
    kDmaRequestMux0FlexIOChannel0 = 10|0x100U, /*!< FLEXIO. */
    kDmaRequestMux0FlexIOChannel1 = 11|0x100U, /*!< FLEXIO. */
    kDmaRequestMux0FlexIOChannel2 = 12|0x100U, /*!< FLEXIO. */
    kDmaRequestMux0FlexIOChannel3 = 13|0x100U, /*!< FLEXIO. */
    kDmaRequestMux0Reserved14 = 14|0x100U, /*!< Reserved14 */
    kDmaRequestMux0Reserved15 = 15|0x100U, /*!< Reserved15 */
    kDmaRequestMux0SPI0Rx = 16|0x100U, /*!< SPI0 Receive. */
    kDmaRequestMux0SPI0Tx = 17|0x100U, /*!< SPI0 Transmit. */
    kDmaRequestMux0SPI1Rx = 18|0x100U, /*!< SPI1 Receive. */
    kDmaRequestMux0SPI1Tx = 19|0x100U, /*!< SPI1 Transmit. */
    kDmaRequestMux0Reserved20 = 20|0x100U, /*!< Reserved20 */
    kDmaRequestMux0Reserved21 = 21|0x100U, /*!< Reserved21 */
    kDmaRequestMux0I2C0 = 22|0x100U, /*!< I2C0. */
    kDmaRequestMux0I2C1 = 23|0x100U, /*!< I2C1. */
    kDmaRequestMux0TPM0Channel0 = 24|0x100U, /*!< TPM0 C0V. */
    kDmaRequestMux0TPM0Channel1 = 25|0x100U, /*!< TPM0 C1V. */
    kDmaRequestMux0TPM0Channel2 = 26|0x100U, /*!< TPM0 C2V. */
    kDmaRequestMux0TPM0Channel3 = 27|0x100U, /*!< TPM0 C3V. */
    kDmaRequestMux0TPM0Channel4 = 28|0x100U, /*!< TPM0 C4V. */
    kDmaRequestMux0TPM0Channel5 = 29|0x100U, /*!< TPM0 C5V. */
    kDmaRequestMux0Reserved30 = 30|0x100U, /*!< Reserved30 */
    kDmaRequestMux0Reserved31 = 31|0x100U, /*!< Reserved31 */
    kDmaRequestMux0TPM1Channel0 = 32|0x100U, /*!< TPM1 C0V. */
    kDmaRequestMux0TPM1Channel1 = 33|0x100U, /*!< TPM1 C1V. */
    kDmaRequestMux0TPM2Channel0 = 34|0x100U, /*!< TPM2 C0V. */
    kDmaRequestMux0TPM2Channel1 = 35|0x100U, /*!< TPM2 C1V. */
    kDmaRequestMux0Reserved36 = 36|0x100U, /*!< Reserved36 */
    kDmaRequestMux0Reserved37 = 37|0x100U, /*!< Reserved37 */
    kDmaRequestMux0Reserved38 = 38|0x100U, /*!< Reserved38 */
    kDmaRequestMux0Reserved39 = 39|0x100U, /*!< Reserved39 */
    kDmaRequestMux0ADC0 = 40|0x100U, /*!< ADC0. */
    kDmaRequestMux0Reserved41 = 41|0x100U, /*!< Reserved41 */
    kDmaRequestMux0CMP0 = 42|0x100U, /*!< CMP0. */
    kDmaRequestMux0Reserved43 = 43|0x100U, /*!< Reserved43 */
    kDmaRequestMux0Reserved44 = 44|0x100U, /*!< Reserved44 */
    kDmaRequestMux0Reserved45 = 45|0x100U, /*!< Reserved45 */
    kDmaRequestMux0Reserved46 = 46|0x100U, /*!< Reserved46 */
    kDmaRequestMux0Reserved47 = 47|0x100U, /*!< Reserved47 */
    kDmaRequestMux0Reserved48 = 48|0x100U, /*!< Reserved48 */
    kDmaRequestMux0PortA = 49|0x100U, /*!< PTA. */
    kDmaRequestMux0PortB = 50|0x100U, /*!< PTB. */
    kDmaRequestMux0PortC = 51|0x100U, /*!< PTC. */
    kDmaRequestMux0PortD = 52|0x100U, /*!< PTD. */
    kDmaRequestMux0PortE = 53|0x100U, /*!< PTE. */
    kDmaRequestMux0TPM0Overflow = 54|0x100U, /*!< TPM0. */
    kDmaRequestMux0TPM1Overflow = 55|0x100U, /*!< TPM1. */
    kDmaRequestMux0TPM2Overflow = 56|0x100U, /*!< TPM2. */
    kDmaRequestMux0Reserved57 = 57|0x100U, /*!< Reserved57 */
    kDmaRequestMux0Reserved58 = 58|0x100U, /*!< Reserved58 */
    kDmaRequestMux0Reserved59 = 59|0x100U, /*!< Reserved59 */
    kDmaRequestMux0AlwaysOn60 = 60|0x100U, /*!< DMAMUX Always Enabled slot. */
    kDmaRequestMux0AlwaysOn61 = 61|0x100U, /*!< DMAMUX Always Enabled slot. */
    kDmaRequestMux0AlwaysOn62 = 62|0x100U, /*!< DMAMUX Always Enabled slot. */
    kDmaRequestMux0AlwaysOn63 = 63|0x100U, /*!< DMAMUX Always Enabled slot. */
#elif defined(CPU_MKL34Z64VLH4) || defined(CPU_MKL34Z64VLL4)
    kDmaRequestMux0Disable = 0|0x100U, /*!< Disable */
    kDmaRequestMux0Reserved1 = 1|0x100U, /*!< Reserved1 */
    kDmaRequestMux0UART0Rx = 2|0x100U, /*!< UART0 receive complete */
    kDmaRequestMux0LPSCI0Rx = 2|0x100U, /*!< UART0 receive complete */
    kDmaRequestMux0UART0Tx = 3|0x100U, /*!< UART0 transmit complete */
    kDmaRequestMux0LPSCI0Tx = 3|0x100U, /*!< UART0 transmit complete */
    kDmaRequestMux0UART1Rx = 4|0x100U, /*!< UART1 receive complete */
    kDmaRequestMux0UART1Tx = 5|0x100U, /*!< UART1 transmit complete */
    kDmaRequestMux0UART2Rx = 6|0x100U, /*!< UART2 receive complete */
    kDmaRequestMux0UART2Tx = 7|0x100U, /*!< UART2 transmit complete */
    kDmaRequestMux0Reserved8 = 8|0x100U, /*!< Reserved8 */
    kDmaRequestMux0Reserved9 = 9|0x100U, /*!< Reserved9 */
    kDmaRequestMux0Reserved10 = 10|0x100U, /*!< Reserved10 */
    kDmaRequestMux0Reserved11 = 11|0x100U, /*!< Reserved11 */
    kDmaRequestMux0Reserved12 = 12|0x100U, /*!< Reserved12 */
    kDmaRequestMux0Reserved13 = 13|0x100U, /*!< Reserved13 */
    kDmaRequestMux0Reserved14 = 14|0x100U, /*!< Reserved14 */
    kDmaRequestMux0Reserved15 = 15|0x100U, /*!< Reserved15 */
    kDmaRequestMux0SPI0Rx = 16|0x100U, /*!< SPI0 receive complete */
    kDmaRequestMux0SPI0Tx = 17|0x100U, /*!< SPI0 transmit complete */
    kDmaRequestMux0SPI1Rx = 18|0x100U, /*!< SPI1 receive complete */
    kDmaRequestMux0SPI1Tx = 19|0x100U, /*!< SPI1 transmit complete */
    kDmaRequestMux0Reserved20 = 20|0x100U, /*!< Reserved20 */
    kDmaRequestMux0Reserved21 = 21|0x100U, /*!< Reserved21 */
    kDmaRequestMux0I2C0 = 22|0x100U, /*!< I2C0 transmission complete */
    kDmaRequestMux0I2C1 = 23|0x100U, /*!< I2C1 transmission complete */
    kDmaRequestMux0TPM0Channel0 = 24|0x100U, /*!< TPM0 channel 0 event (CMP or CAP) */
    kDmaRequestMux0TPM0Channel1 = 25|0x100U, /*!< TPM0 channel 1 event (CMP or CAP) */
    kDmaRequestMux0TPM0Channel2 = 26|0x100U, /*!< TPM0 channel 2 event (CMP or CAP) */
    kDmaRequestMux0TPM0Channel3 = 27|0x100U, /*!< TPM0 channel 3 event (CMP or CAP) */
    kDmaRequestMux0TPM0Channel4 = 28|0x100U, /*!< TPM0 channel 4 event (CMP or CAP) */
    kDmaRequestMux0TPM0Channel5 = 29|0x100U, /*!< TPM0 channel 5 event (CMP or CAP) */
    kDmaRequestMux0Reserved30 = 30|0x100U, /*!< Reserved30 */
    kDmaRequestMux0Reserved31 = 31|0x100U, /*!< Reserved31 */
    kDmaRequestMux0TPM1Channel0 = 32|0x100U, /*!< TPM1 channel 0 event (CMP or CAP) */
    kDmaRequestMux0TPM1Channel1 = 33|0x100U, /*!< TPM1 channel 1 event (CMP or CAP) */
    kDmaRequestMux0TPM2Channel0 = 34|0x100U, /*!< TPM2 channel 0 event (CMP or CAP) */
    kDmaRequestMux0TPM2Channel1 = 35|0x100U, /*!< TPM2 channel 1 event (CMP or CAP) */
    kDmaRequestMux0Reserved36 = 36|0x100U, /*!< Reserved36 */
    kDmaRequestMux0Reserved37 = 37|0x100U, /*!< Reserved37 */
    kDmaRequestMux0Reserved38 = 38|0x100U, /*!< Reserved38 */
    kDmaRequestMux0Reserved39 = 39|0x100U, /*!< Reserved39 */
    kDmaRequestMux0ADC0 = 40|0x100U, /*!< ADC0 conversion complete */
    kDmaRequestMux0Reserved41 = 41|0x100U, /*!< Reserved41 */
    kDmaRequestMux0CMP0 = 42|0x100U, /*!< CMP0 Output */
    kDmaRequestMux0Reserved43 = 43|0x100U, /*!< Reserved43 */
    kDmaRequestMux0Reserved44 = 44|0x100U, /*!< Reserved44 */
    kDmaRequestMux0Reserved45 = 45|0x100U, /*!< Reserved45 */
    kDmaRequestMux0Reserved46 = 46|0x100U, /*!< Reserved46 */
    kDmaRequestMux0Reserved47 = 47|0x100U, /*!< Reserved47 */
    kDmaRequestMux0Reserved48 = 48|0x100U, /*!< Reserved48 */
    kDmaRequestMux0PortA = 49|0x100U, /*!< PORTA rising, falling or both edges */
    kDmaRequestMux0Reserved50 = 50|0x100U, /*!< Reserved50 */
    kDmaRequestMux0PortC = 51|0x100U, /*!< PORTC rising, falling or both edges */
    kDmaRequestMux0PortD = 52|0x100U, /*!< PORTD rising, falling or both edges */
    kDmaRequestMux0Reserved53 = 53|0x100U, /*!< Reserved53 */
    kDmaRequestMux0TPM0Overflow = 54|0x100U, /*!< TPM0 overflow */
    kDmaRequestMux0TPM1Overflow = 55|0x100U, /*!< TPM1 overflow */
    kDmaRequestMux0TPM2Overflow = 56|0x100U, /*!< TPM2 overflow */
    kDmaRequestMux0Reserved57 = 57|0x100U, /*!< Reserved57 */
    kDmaRequestMux0Reserved58 = 58|0x100U, /*!< Reserved58 */
    kDmaRequestMux0Reserved59 = 59|0x100U, /*!< Reserved59 */
    kDmaRequestMux0AlwaysOn60 = 60|0x100U, /*!< Always enabled 60 */
    kDmaRequestMux0AlwaysOn61 = 61|0x100U, /*!< Always enabled 61 */
    kDmaRequestMux0AlwaysOn62 = 62|0x100U, /*!< Always enabled 62 */
    kDmaRequestMux0AlwaysOn63 = 63|0x100U, /*!< Always enabled 63 */
#elif defined(CPU_MKW01Z128CHN4)
    kDmaRequestMux0Disable = 0|0x100U, /*!< DMAMUX TriggerDisabled. */
    kDmaRequestMux0Reserved1 = 1|0x100U, /*!< Reserved1 */
    kDmaRequestMux0UART0Rx = 2|0x100U, /*!< UART0 Receive. */
    kDmaRequestMux0LPSCI0Rx = 2|0x100U, /*!< UART0 Receive. */
    kDmaRequestMux0UART0Tx = 3|0x100U, /*!< UART0 Transmit. */
    kDmaRequestMux0LPSCI0Tx = 3|0x100U, /*!< UART0 Transmit. */
    kDmaRequestMux0UART1Rx = 4|0x100U, /*!< UART1 Receive. */
    kDmaRequestMux0UART1Tx = 5|0x100U, /*!< UART1 Transmit. */
    kDmaRequestMux0UART2Rx = 6|0x100U, /*!< UART2 Receive. */
    kDmaRequestMux0UART2Tx = 7|0x100U, /*!< UART2 Transmit. */
    kDmaRequestMux0Reserved8 = 8|0x100U, /*!< Reserved8 */
    kDmaRequestMux0Reserved9 = 9|0x100U, /*!< Reserved9 */
    kDmaRequestMux0Reserved10 = 10|0x100U, /*!< Reserved10 */
    kDmaRequestMux0Reserved11 = 11|0x100U, /*!< Reserved11 */
    kDmaRequestMux0Reserved12 = 12|0x100U, /*!< Reserved12 */
    kDmaRequestMux0Reserved13 = 13|0x100U, /*!< Reserved13 */
    kDmaRequestMux0Reserved14 = 14|0x100U, /*!< Reserved14 */
    kDmaRequestMux0Reserved15 = 15|0x100U, /*!< Reserved15 */
    kDmaRequestMux0SPI0Rx = 16|0x100U, /*!< SPI0 Receive. */
    kDmaRequestMux0SPI0Tx = 17|0x100U, /*!< SPI0 Transmit. */
    kDmaRequestMux0SPI1Rx = 18|0x100U, /*!< SPI1 Receive. */
    kDmaRequestMux0SPI1Tx = 19|0x100U, /*!< SPI1 Transmit. */
    kDmaRequestMux0Reserved20 = 20|0x100U, /*!< Reserved20 */
    kDmaRequestMux0Reserved21 = 21|0x100U, /*!< Reserved21 */
    kDmaRequestMux0I2C0 = 22|0x100U, /*!< I2C0. */
    kDmaRequestMux0I2C1 = 23|0x100U, /*!< I2C1. */
    kDmaRequestMux0TPM0Channel0 = 24|0x100U, /*!< TPM0 C0V. */
    kDmaRequestMux0TPM0Channel1 = 25|0x100U, /*!< TPM0 C1V. */
    kDmaRequestMux0TPM0Channel2 = 26|0x100U, /*!< TPM0 C2V. */
    kDmaRequestMux0TPM0Channel3 = 27|0x100U, /*!< TPM0 C3V. */
    kDmaRequestMux0TPM0Channel4 = 28|0x100U, /*!< TPM0 C4V. */
    kDmaRequestMux0TPM0Channel5 = 29|0x100U, /*!< TPM0 C5V. */
    kDmaRequestMux0Reserved30 = 30|0x100U, /*!< Reserved30 */
    kDmaRequestMux0Reserved31 = 31|0x100U, /*!< Reserved31 */
    kDmaRequestMux0TPM1Channel0 = 32|0x100U, /*!< TPM1 C0V. */
    kDmaRequestMux0TPM1Channel1 = 33|0x100U, /*!< TPM1 C1V. */
    kDmaRequestMux0TPM2Channel0 = 34|0x100U, /*!< TPM2 C0V. */
    kDmaRequestMux0TPM2Channel1 = 35|0x100U, /*!< TPM2 C1V. */
    kDmaRequestMux0Reserved36 = 36|0x100U, /*!< Reserved36 */
    kDmaRequestMux0Reserved37 = 37|0x100U, /*!< Reserved37 */
    kDmaRequestMux0Reserved38 = 38|0x100U, /*!< Reserved38 */
    kDmaRequestMux0Reserved39 = 39|0x100U, /*!< Reserved39 */
    kDmaRequestMux0ADC0 = 40|0x100U, /*!< ADC0. */
    kDmaRequestMux0Reserved41 = 41|0x100U, /*!< Reserved41 */
    kDmaRequestMux0CMP0 = 42|0x100U, /*!< CMP0. */
    kDmaRequestMux0Reserved43 = 43|0x100U, /*!< Reserved43 */
    kDmaRequestMux0Reserved44 = 44|0x100U, /*!< Reserved44 */
    kDmaRequestMux0DAC0 = 45|0x100U, /*!< DAC0. */
    kDmaRequestMux0Reserved46 = 46|0x100U, /*!< Reserved46 */
    kDmaRequestMux0Reserved47 = 47|0x100U, /*!< Reserved47 */
    kDmaRequestMux0Reserved48 = 48|0x100U, /*!< Reserved48 */
    kDmaRequestMux0PortA = 49|0x100U, /*!< PTA. */
    kDmaRequestMux0Reserved50 = 50|0x100U, /*!< Reserved50 */
    kDmaRequestMux0PortC = 51|0x100U, /*!< PTC. */
    kDmaRequestMux0PortD = 52|0x100U, /*!< PTD. */
    kDmaRequestMux0Reserved53 = 53|0x100U, /*!< Reserved53 */
    kDmaRequestMux0TPM0Overflow = 54|0x100U, /*!< TPM0. */
    kDmaRequestMux0TPM1Overflow = 55|0x100U, /*!< TPM1. */
    kDmaRequestMux0TPM2Overflow = 56|0x100U, /*!< TPM2. */
    kDmaRequestMux0TSI0 = 57|0x100U, /*!< TSI0. */
    kDmaRequestMux0Reserved58 = 58|0x100U, /*!< Reserved58 */
    kDmaRequestMux0Reserved59 = 59|0x100U, /*!< Reserved59 */
    kDmaRequestMux0AlwaysOn60 = 60|0x100U, /*!< DMAMUX Always Enabled slot. */
    kDmaRequestMux0AlwaysOn61 = 61|0x100U, /*!< DMAMUX Always Enabled slot. */
    kDmaRequestMux0AlwaysOn62 = 62|0x100U, /*!< DMAMUX Always Enabled slot. */
    kDmaRequestMux0AlwaysOn63 = 63|0x100U, /*!< DMAMUX Always Enabled slot. */
#elif defined(CPU_MKW20Z160VHT4) || defined(CPU_MKW30Z160VHM4) || defined(CPU_MKW40Z160VHT4)
    kDmaRequestMux0Disable = 0|0x100U, /*!< DMAMUX TriggerDisabled. */
    kDmaRequestMux0Reserved1 = 1|0x100U, /*!< Reserved1 */
    kDmaRequestMux0LPUART0Rx = 2|0x100U, /*!< LPUART0 Receive. */
    kDmaRequestMux0LPUART0Tx = 3|0x100U, /*!< LPUART0 Transmit. */
    kDmaRequestMux0Reserved4 = 4|0x100U, /*!< Reserved4 */
    kDmaRequestMux0Reserved5 = 5|0x100U, /*!< Reserved5 */
    kDmaRequestMux0Reserved6 = 6|0x100U, /*!< Reserved6 */
    kDmaRequestMux0Reserved7 = 7|0x100U, /*!< Reserved7 */
    kDmaRequestMux0Reserved8 = 8|0x100U, /*!< Reserved8 */
    kDmaRequestMux0Reserved9 = 9|0x100U, /*!< Reserved9 */
    kDmaRequestMux0Reserved10 = 10|0x100U, /*!< Reserved10 */
    kDmaRequestMux0Reserved11 = 11|0x100U, /*!< Reserved11 */
    kDmaRequestMux0Reserved12 = 12|0x100U, /*!< Reserved12 */
    kDmaRequestMux0Reserved13 = 13|0x100U, /*!< Reserved13 */
    kDmaRequestMux0Reserved14 = 14|0x100U, /*!< Reserved14 */
    kDmaRequestMux0Reserved15 = 15|0x100U, /*!< Reserved15 */
    kDmaRequestMux0SPI0Rx = 16|0x100U, /*!< SPI0 Receive. */
    kDmaRequestMux0SPI0Tx = 17|0x100U, /*!< SPI0 Transmit. */
    kDmaRequestMux0SPI1Rx = 18|0x100U, /*!< SPI1 Receive. */
    kDmaRequestMux0SPI1Tx = 19|0x100U, /*!< SPI1 Transmit. */
    kDmaRequestMux0AESAInputFIFO = 20|0x100U, /*!< AESA Input FIFO. */
    kDmaRequestMux0AESAOutputFIFO = 21|0x100U, /*!< AESA Output FIFO. */
    kDmaRequestMux0I2C0 = 22|0x100U, /*!< I2C0. */
    kDmaRequestMux0I2C1 = 23|0x100U, /*!< I2C1. */
    kDmaRequestMux0TPM0Channel0 = 24|0x100U, /*!< TPM0 C0V. */
    kDmaRequestMux0TPM0Channel1 = 25|0x100U, /*!< TPM0 C1V. */
    kDmaRequestMux0TPM0Channel2 = 26|0x100U, /*!< TPM0 C2V. */
    kDmaRequestMux0TPM0Channel3 = 27|0x100U, /*!< TPM0 C3V. */
    kDmaRequestMux0Reserved28 = 28|0x100U, /*!< Reserved28 */
    kDmaRequestMux0Reserved29 = 29|0x100U, /*!< Reserved29 */
    kDmaRequestMux0Reserved30 = 30|0x100U, /*!< Reserved30 */
    kDmaRequestMux0Reserved31 = 31|0x100U, /*!< Reserved31 */
    kDmaRequestMux0TPM1Channel0 = 32|0x100U, /*!< TPM1 C0V. */
    kDmaRequestMux0TPM1Channel1 = 33|0x100U, /*!< TPM1 C1V. */
    kDmaRequestMux0TPM2Channel0 = 34|0x100U, /*!< TPM2 C0V. */
    kDmaRequestMux0TPM2Channel1 = 35|0x100U, /*!< TPM2 C1V. */
    kDmaRequestMux0Reserved36 = 36|0x100U, /*!< Reserved36 */
    kDmaRequestMux0Reserved37 = 37|0x100U, /*!< Reserved37 */
    kDmaRequestMux0Reserved38 = 38|0x100U, /*!< Reserved38 */
    kDmaRequestMux0Reserved39 = 39|0x100U, /*!< Reserved39 */
    kDmaRequestMux0ADC0 = 40|0x100U, /*!< ADC0. */
    kDmaRequestMux0Reserved41 = 41|0x100U, /*!< Reserved41 */
    kDmaRequestMux0CMP0 = 42|0x100U, /*!< CMP0. */
    kDmaRequestMux0Reserved43 = 43|0x100U, /*!< Reserved43 */
    kDmaRequestMux0Reserved44 = 44|0x100U, /*!< Reserved44 */
    kDmaRequestMux0DAC0 = 45|0x100U, /*!< DAC0. */
    kDmaRequestMux0Reserved46 = 46|0x100U, /*!< Reserved46 */
    kDmaRequestMux0CMT = 47|0x100U, /*!< CMT. */
    kDmaRequestMux0Reserved48 = 48|0x100U, /*!< Reserved48 */
    kDmaRequestMux0PortA = 49|0x100U, /*!< PTA. */
    kDmaRequestMux0PortB = 50|0x100U, /*!< PTB. */
    kDmaRequestMux0PortC = 51|0x100U, /*!< PTC. */
    kDmaRequestMux0Reserved52 = 52|0x100U, /*!< Reserved52 */
    kDmaRequestMux0Reserved53 = 53|0x100U, /*!< Reserved53 */
    kDmaRequestMux0TPM0Overflow = 54|0x100U, /*!< TPM0. */
    kDmaRequestMux0TPM1Overflow = 55|0x100U, /*!< TPM1. */
    kDmaRequestMux0TPM2Overflow = 56|0x100U, /*!< TPM2. */
    kDmaRequestMux0TSI0 = 57|0x100U, /*!< TSI0. */
    kDmaRequestMux0Reserved58 = 58|0x100U, /*!< Reserved58 */
    kDmaRequestMux0Reserved59 = 59|0x100U, /*!< Reserved59 */
    kDmaRequestMux0AlwaysOn60 = 60|0x100U, /*!< DMAMUX Always Enabled slot. */
    kDmaRequestMux0AlwaysOn61 = 61|0x100U, /*!< DMAMUX Always Enabled slot. */
    kDmaRequestMux0AlwaysOn62 = 62|0x100U, /*!< DMAMUX Always Enabled slot. */
    kDmaRequestMux0AlwaysOn63 = 63|0x100U, /*!< DMAMUX Always Enabled slot. */
#elif defined(CPU_MKM34Z256VLL7) || defined(CPU_MKM34Z256VLQ7)
    kDmaRequestMux0Disable = 0|0x100U, /*!< Disable */
    kDmaRequestMux0Reserved1 = 1|0x100U, /*!< Reserved1 */
    kDmaRequestMux0UART0Rx = 2|0x100U, /*!< UART0 Receive */
    kDmaRequestMux0UART0Tx = 3|0x100U, /*!< UART0 Transmit */
    kDmaRequestMux0UART1Rx = 4|0x100U, /*!< UART1 Receive */
    kDmaRequestMux0UART1Tx = 5|0x100U, /*!< UART1 Transmit */
    kDmaRequestMux0UART2Rx = 6|0x100U, /*!< UART2 Receive */
    kDmaRequestMux0UART2Tx = 7|0x100U, /*!< UART2 Transmit */
    kDmaRequestMux0UART3Rx = 8|0x100U, /*!< UART3 Receive */
    kDmaRequestMux0UART3Tx = 9|0x100U, /*!< UART3 Transmit */
    kDmaRequestMux0Reserved10 = 10|0x100U, /*!< Reserved10 */
    kDmaRequestMux0Reserved11 = 11|0x100U, /*!< Reserved11 */
    kDmaRequestMux0Reserved12 = 12|0x100U, /*!< Reserved12 */
    kDmaRequestMux0Reserved13 = 13|0x100U, /*!< Reserved13 */
    kDmaRequestMux0Reserved14 = 14|0x100U, /*!< Reserved14 */
    kDmaRequestMux0Reserved15 = 15|0x100U, /*!< Reserved15 */
    kDmaRequestMux0SPI0Rx = 16|0x100U, /*!< SPI0 Receive */
    kDmaRequestMux0SPI0Tx = 17|0x100U, /*!< SPI0 Transmit */
    kDmaRequestMux0SPI1Rx = 18|0x100U, /*!< SPI1 Receive */
    kDmaRequestMux0SPI1Tx = 19|0x100U, /*!< SPI1 Transmit */
    kDmaRequestMux0Reserved20 = 20|0x100U, /*!< Reserved20 */
    kDmaRequestMux0Reserved21 = 21|0x100U, /*!< Reserved21 */
    kDmaRequestMux0I2C0 = 22|0x100U, /*!< I2C0 */
    kDmaRequestMux0I2C1 = 23|0x100U, /*!< I2C1 */
    kDmaRequestMux0TMR0Channel0 = 24|0x100U, /*!< TPMCH0 */
    kDmaRequestMux0TMR0Channel1 = 25|0x100U, /*!< TPMCH1 */
    kDmaRequestMux0TMR0Channel2 = 26|0x100U, /*!< TPMCH2 */
    kDmaRequestMux0TMR0Channel3 = 27|0x100U, /*!< TPMCH3 */
    kDmaRequestMux0XBARRequest0 = 28|0x100U, /*!< XBARCH0 */
    kDmaRequestMux0XBARRequest1 = 29|0x100U, /*!< XBARCH1 */
    kDmaRequestMux0XBARRequest2 = 30|0x100U, /*!< XBARCH2 */
    kDmaRequestMux0XBARRequest3 = 31|0x100U, /*!< XBARCH3 */
    kDmaRequestMux0AFEChannel0 = 32|0x100U, /*!< AFECH0 */
    kDmaRequestMux0AFEChannel1 = 33|0x100U, /*!< AFECH1 */
    kDmaRequestMux0AFEChannel2 = 34|0x100U, /*!< AFECH2 */
    kDmaRequestMux0AFEChannel3 = 35|0x100U, /*!< AFECH3 */
    kDmaRequestMux0PortJ = 36|0x100U, /*!< GPIO Port_J */
    kDmaRequestMux0PortK = 37|0x100U, /*!< GPIO Port_K */
    kDmaRequestMux0PortL = 38|0x100U, /*!< GPIO Port_L */
    kDmaRequestMux0PortM = 39|0x100U, /*!< GPIO Port_M */
    kDmaRequestMux0Reserved40 = 40|0x100U, /*!< Reserved40 */
    kDmaRequestMux0Reserved41 = 41|0x100U, /*!< Reserved41 */
    kDmaRequestMux0CMP0 = 42|0x100U, /*!< CMP0 */
    kDmaRequestMux0CMP1 = 43|0x100U, /*!< CMP1 */
    kDmaRequestMux0CMP2 = 44|0x100U, /*!< CMP2 */
    kDmaRequestMux0Reserved45 = 45|0x100U, /*!< Reserved45 */
    kDmaRequestMux0Reserved46 = 46|0x100U, /*!< Reserved46 */
    kDmaRequestMux0MMAU = 47|0x100U, /*!< MMAU */
    kDmaRequestMux0PDB0 = 48|0x100U, /*!< PDB0 */
    kDmaRequestMux0PORTA = 49|0x100U, /*!< GPIO Port_A */
    kDmaRequestMux0PORTB = 50|0x100U, /*!< GPIO Port_B */
    kDmaRequestMux0PORTC = 51|0x100U, /*!< GPIO Port_C */
    kDmaRequestMux0PORTD = 52|0x100U, /*!< GPIO Port_D */
    kDmaRequestMux0PORTE = 53|0x100U, /*!< GPIO Port_E */
    kDmaRequestMux0PORTF = 54|0x100U, /*!< GPIO Port_F */
    kDmaRequestMux0PORTG = 55|0x100U, /*!< GPIO Port_G */
    kDmaRequestMux0PORTH = 56|0x100U, /*!< GPIO Port_H */
    kDmaRequestMux0PORTI = 57|0x100U, /*!< GPIO Port_I */
    kDmaRequestMux0LPUART0Rx = 58|0x100U, /*!< LPUART0 Receive */
    kDmaRequestMux0LPUART0Tx = 59|0x100U, /*!< LPUART0 Transmit */
    kDmaRequestMux0AlwaysOn60 = 60|0x100U, /*!< Always enabled. */
    kDmaRequestMux0AlwaysOn61 = 61|0x100U, /*!< Always enabled. */
    kDmaRequestMux0AlwaysOn62 = 62|0x100U, /*!< Always enabled. */
    kDmaRequestMux0AlwaysOn63 = 63|0x100U, /*!< Always enabled. */
#else
    #error "No valid CPU defined!"
#endif
} dma_request_source_t;

/* @} */

#endif /* __FSL_DMA_REQUEST_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/

