/**
 *  \file   mcasp.c
 *
 *  \brief  McASP APIs.
 *
 *   This file contains the device abstraction layer APIs for McASP.
 */

/*
* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
*/
/*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

/* HW Macros and Peripheral Defines */
#include "hw_types.h"
#include "hw_mcasp.h"

/* Driver APIs */
#include "mcasp.h"

/*******************************************************************************
*                        API FUNCTION DEFINITIONS
*******************************************************************************/
/**
 * \brief   Resets the Transmit section of the McASP
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 *
 * \return  None.
 *
 **/
void McASPTxReset(unsigned int baseAddr)
{
    HWREG(baseAddr + MCASP_XGBLCTL) = 0x0;
}

/**
 * \brief   Resets the Receive section of the McASP
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 *
 * \return  None.
 *
 **/
void McASPRxReset(unsigned int baseAddr)
{
    HWREG(baseAddr + MCASP_RGBLCTL) = 0x0;
}

/**
 * \brief   Enables the Write FIFO for McASP. This shall be done before
 *          taking McASP out of Reset. First this API sets the FIFO parameters
 *          keeping the FIFO disabled. Then it enables the FIFO
 *
 * \param   baseAddr      Base Address of the McASP FIFO Registers.
 * \param   numTxSer      Number of Transmit Serializers to be used.
 * \param   minWdPerSer   The minimum number of words per serializer 
 *                        to be available in FIFO to issue a DMA event.
 *
 * \return  None.
 *
 **/
void McASPWriteFifoEnable(unsigned int baseAddr, unsigned int numTxSer, 
                          unsigned int minWdPerSer)
{
    HWREG(baseAddr + MCASP_FIFO_WFIFOCTL) = numTxSer | 
                                            ((minWdPerSer * numTxSer)
                                             << AFIFO_WFIFOCTL_WNUMEVT_SHIFT);

    /* The configuration is done. now set the enable bit */
    HWREG(baseAddr + MCASP_FIFO_WFIFOCTL) |= AFIFO_WFIFOCTL_WENA;
}

/**
 * \brief   Enables the Read FIFO for McASP. This shall be done before
 *          taking McASP out of Reset. First this API sets the FIFO parameters
 *          keeping the FIFO disabled. Then it enables the FIFO
 *
 * \param   baseAddr      Base Address of the McASP FIFO Registers.
 * \param   numRxSer      Number of Receive Serializers to be used.
 * \param   minWdPerSer   The minimum number of words per serializer 
 *                        to be available in FIFO to issue a DMA event.
 *
 * \return  None.
 *
 **/
void McASPReadFifoEnable(unsigned int baseAddr, unsigned int numRxSer, 
                         unsigned int minWdPerSer)
{
    HWREG(baseAddr + MCASP_FIFO_RFIFOCTL) = numRxSer | 
                                            ((minWdPerSer * numRxSer)
                                             << AFIFO_RFIFOCTL_RNUMEVT_SHIFT);

    /* The configuration is done. now set the enable bit */
    HWREG(baseAddr + MCASP_FIFO_RFIFOCTL) |= AFIFO_RFIFOCTL_RENA;
}

/**
 * \brief   Sets the Format Mask for McASP Transmit section. The bits of
 *          the mask, which are set are transmitted out of McASP. The bits
 *          which are clear are padded according to the format settings.
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   mask          Mask Value to be written, corresponding bits will
 *                        be transmitted out of McASP without any change
 *
 * \return  None.
 *
 **/
void McASPTxFmtMaskSet(unsigned int baseAddr, unsigned int mask)
{
    HWREG(baseAddr + MCASP_XMASK) = mask;
}

/**
 * \brief   Sets the Format Mask for McASP Receive section. The bits of
 *          the mask, which are set are returned to the CPU/DMA. The bits
 *          which are clear are padded according to the format settings.
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   mask          Mask Value to be written, corresponding bits will
 *                        be returned to the CPU/DMA
 *
 * \return  None.
 *
 **/
void McASPRxFmtMaskSet(unsigned int baseAddr, unsigned int mask)
{
    HWREG(baseAddr + MCASP_RMASK) = mask;
}

/**
 * \brief   Sets the format for Transmit section of McASP with the format value
 *          input.  
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   formatVal     The format to be written to the transmit section
 *
 *    The formatVal shall be a logical OR combination of the parameters \n
 *     1. Transmit Sync Bit Dealy, which can take one of the values \n
 *            MCASP_TX_SYNC_DELAY_0BIT \n
 *            MCASP_TX_SYNC_DELAY_1BIT \n
 *            MCASP_TX_SYNC_DELAY_2BIT \n
 *
 *     2. Bit Stream Output, which can take one of the values \n
 *            MCASP_TX_BITSTREAM_LSB_FIRST \n
 *            MCASP_TX_BITSTREAM_MSB_FIRST \n
 *
 *     3. Padding Options, which can take one of the values \n
 *            MCASP_TX_PAD_WITH_0 \n
 *            MCASP_TX_PAD_WITH_1 \n
 *            MCASP_TX_PAD_WITH_PBIT(n) - pad the extra bytes with the 
 *                                        n-th pad bit \n
 *
 *     4. Transmit Slot Size, which can take one of the values \n
 *            MCASP_TX_SLOTSIZE_8BITS \n
 *            MCASP_TX_SLOTSIZE_12BITS \n
 *            MCASP_TX_SLOTSIZE_16BITS \n
 *            MCASP_TX_SLOTSIZE_20BITS \n
 *            MCASP_TX_SLOTSIZE_24BITS \n
 *            MCASP_TX_SLOTSIZE_28BITS \n
 *            MCASP_TX_SLOTSIZE_32BITS \n
 *
 *     5. Transmit Buffer Origin, which can take one of the values \n
 *            MCASP_TX_BUF_DMAPORT \n
 *            MCASP_TX_BUF_PERICONFIGPORT \n
 *
 *     6. Value for Transmit Rotate unit, which can take one of the values \n
 *            MCASP_TX_ROT_RIGHT_NONE \n
 *            MCASP_TX_ROT_RIGHT_4BITS \n
 *            MCASP_TX_ROT_RIGHT_8BITS \n
 *            MCASP_TX_ROT_RIGHT_12BITS \n
 *            MCASP_TX_ROT_RIGHT_16BITS \n
 *            MCASP_TX_ROT_RIGHT_20BITS \n
 *            MCASP_TX_ROT_RIGHT_24BITS \n
 *            MCASP_TX_ROT_RIGHT_28BITS \n
 *
 *     For example, the reset value is 
 *      (MCASP_TX_SYNC_DELAY_0BIT | MCASP_TX_BITSTREAM_LSB_FIRST | 
 *       MCASP_TX_PAD_WITH_0 | MCASP_TX_SLOTSIZE_8BITS | MCASP_TX_BUF_DMAPORT |
 *       MCASP_TX_ROT_RIGHT_NONE)
 *
 * \return  None.
 *
 **/
void McASPTxFmtSet(unsigned int baseAddr, unsigned int formatVal)
{
    HWREG(baseAddr + MCASP_XFMT) = formatVal;
} 

/**
 * \brief   Sets the format for Receive section of McASP with the format value
 *          input.  
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   formatVal     The format to be written to the Receive section
 *
 *    The formatVal shall be a logical OR combination of the parameters \n
 *     1. Receive Bit Dealy, which can take one of the values \n
 *            MCASP_RX_SYNC_DELAY_0BIT \n
 *            MCASP_RX_SYNC_DELAY_1BIT \n
 *            MCASP_RX_SYNC_DELAY_2BIT \n
 *
 *     2. Receive serial bit stream order, which can take one of the values \n
 *            MCASP_RX_BITSTREAM_LSB_FIRST \n
 *            MCASP_RX_BITSTREAM_MSB_FIRST \n
 *
 *     3. Padding Options, which can take one of the values \n
 *            MCASP_RX_PAD_WITH_0 \n
 *            MCASP_RX_PAD_WITH_1 \n
 *            MCASP_RX_PAD_WITH_RPBIT(n) - pad the extra bytes with the 
 *                                         n-th pad bit \n
 *
 *     4. Receive Slot Size, which can take one of the values \n
 *            MCASP_RX_SLOTSIZE_8BITS \n
 *            MCASP_RX_SLOTSIZE_12BITS \n
 *            MCASP_RX_SLOTSIZE_16BITS \n
 *            MCASP_RX_SLOTSIZE_20BITS \n
 *            MCASP_RX_SLOTSIZE_24BITS \n
 *            MCASP_RX_SLOTSIZE_28BITS \n
 *            MCASP_RX_SLOTSIZE_32BITS \n
 *
 *     5. Receive Buffer Origin, which can take one of the values \n
 *            MCASP_RX_BUF_DMAPORT \n
 *            MCASP_RX_BUF_PERICONFIGPORT \n
 *
 *     6. Value for Receive Rotate unit, which can take one of the values \n
 *            MCASP_RX_ROT_RIGHT_NONE \n
 *            MCASP_RX_ROT_RIGHT_4BITS \n
 *            MCASP_RX_ROT_RIGHT_8BITS \n
 *            MCASP_RX_ROT_RIGHT_12BITS \n
 *            MCASP_RX_ROT_RIGHT_16BITS \n
 *            MCASP_RX_ROT_RIGHT_20BITS \n
 *            MCASP_RX_ROT_RIGHT_24BITS \n
 *            MCASP_RX_ROT_RIGHT_28BITS \n
 *
 *     For example, the reset value is 
 *      (MCASP_RX_SYNC_DELAY_0BIT | MCASP_RX_BITSTREAM_LSB_FIRST | 
 *       MCASP_RX_PAD_WITH_0 | MCASP_RX_SLOTSIZE_8BITS | MCASP_RX_BUF_DMAPORT |
 *       MCASP_RX_ROT_RIGHT_NONE)
 *
 * \return  None.
 *
 **/
void McASPRxFmtSet(unsigned int baseAddr, unsigned int formatVal)
{
    HWREG(baseAddr + MCASP_RFMT) = formatVal;
} 

/**
 * \brief   Sets the I2S format in the Transmit Format unit. 
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   wordSize      The word size in bits.
 * \param   slotSize      Slot size in bits.
 * \param   txMode        The mode of Transmission.
 *             txMode can take one of the values \n
 *                  MCASP_TX_MODE_NON_DMA - transmission without using DMA \n
 *                  MCASP_TX_MODE_DMA - DMA is used for transmission 
 *
 * \return  None.
 * 
 *  Note : The Frame Sync shall be separately configured for I2S.
 *         It is assumed that the word size is a multiple of 8.
 *
 **/
void McASPTxFmtI2SSet(unsigned int baseAddr, unsigned int wordSize, 
                      unsigned int slotSize, unsigned int txMode)
{  
    /* Set the mask assuming integer format */
    McASPTxFmtMaskSet(baseAddr, (1 << wordSize) - 1);

    /* Set the transmit format unit for I2S */
    McASPTxFmtSet(baseAddr, (MCASP_TX_PAD_WITH_0 | MCASP_TX_BITSTREAM_MSB_FIRST 
                             | MCASP_TX_SYNC_DELAY_1BIT
                             | ((wordSize >> 2) & MCASP_XFMT_XROT)
                             | ((slotSize/2 -1) << MCASP_XFMT_XSSZ_SHIFT)
                             | txMode));
}

/**
 * \brief   Sets the I2S format in the Receive Format unit. 
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   wordSize      The word size in bits.
 * \param   slotSize      Slot size in bits.
 * \param   rxMode        The mode of reception.
 *             rxMode can take one of the values \n
 *                  MCASP_RX_MODE_NON_DMA - reception without using DMA \n
 *                  MCASP_RX_MODE_DMA - DMA is used for reception
 *
 * \return  None.
 * 
 *  Note : The Frame Sync shall be separately configured for I2S.
 *         It is assumed that the word size is a multiple of 8.
 *
 **/
void McASPRxFmtI2SSet(unsigned int baseAddr, unsigned int wordSize, 
                      unsigned int slotSize, unsigned int rxMode)
{  
    /* Set the mask assuming integer format */
    McASPRxFmtMaskSet(baseAddr, (1 << wordSize) - 1);

    /* Set the receive format unit for I2S */
    McASPRxFmtSet(baseAddr, (MCASP_RX_PAD_WITH_0 | MCASP_RX_BITSTREAM_MSB_FIRST 
                             | MCASP_RX_SYNC_DELAY_1BIT
                             | (((slotSize - wordSize) >> 2) & MCASP_RFMT_RROT)
                             | ((slotSize/2 -1) << MCASP_RFMT_RSSZ_SHIFT)
                             | rxMode));
}

/**
 * \brief   Configures the Transmit Frame Sync signal.
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   fsMode        The mode of Transmission
 * \param   fsWidth       The width of frame sync signal
 * \param   fsSetting     The signal settings for frame sync
 *
 *    fsMode is 0 for burst mode \n
 *    0x1 < fsMode < 0x21 for TDM mode with fsMode number of slots.
 *    Hence, fsMode = 2 for I2S mode \n
 *    fsMode is 384 for 384 slot DIT mode \n
 *
 *    fsWidth can take the values \n
 *         MCASP_TX_FS_WIDTH_BIT \n
 *         MCASP_TX_FS_WIDTH_WORD \n
 *
 *    fsSetting can take the values \n
 *         MCASP_TX_FS_INT_BEGIN_ON_RIS_EDGE - fs source is internal \n
 *         MCASP_TX_FS_INT_BEGIN_ON_FALL_EDGE - fs source is internal \n
 *         MCASP_TX_FS_EXT_BEGIN_ON_RIS_EDGE - fs source is external \n
 *         MCASP_TX_FS_EXT_BEGIN_ON_FALL_EDGE - fs source is external \n
 *   
 * \return  None.
 *
 **/
void McASPTxFrameSyncCfg(unsigned int baseAddr, unsigned int fsMode, 
                         unsigned int fsWidth, unsigned int fsSetting)
{
    HWREG(baseAddr + MCASP_AFSXCTL) = ((fsMode << MCASP_AFSXCTL_XMOD_SHIFT) 
                                       | fsWidth | fsSetting);
}

/**
 * \brief   Configures the Receive Frame Sync signal.
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   fsMode        The mode of Reception
 * \param   fsWidth       The width of frame sync signal
 * \param   fsSetting     The signal settings for frame sync
 *
 *    fsMode is 0 for burst mode \n
 *    0x1 < fsMode < 0x21 for TDM mode with fsMode number of slots.
 *    Hence, fsMode = 2 for I2S mode \n
 *    fsMode is 384 for 384 slot DIR mode \n
 *
 *    fsWidth can take the values \n
 *         MCASP_RX_FS_WIDTH_BIT \n
 *         MCASP_RX_FS_WIDTH_WORD \n
 *
 *    fsSetting can take the values \n
 *         MCASP_RX_FS_INT_BEGIN_ON_RIS_EDGE - fs source is internal \n
 *         MCASP_RX_FS_INT_BEGIN_ON_FALL_EDGE - fs source is internal \n
 *         MCASP_RX_FS_EXT_BEGIN_ON_RIS_EDGE - fs source is external \n
 *         MCASP_RX_FS_EXT_BEGIN_ON_FALL_EDGE - fs source is external \n
 *   
 * \return  None.
 *
 **/
void McASPRxFrameSyncCfg(unsigned int baseAddr, unsigned int fsMode, 
                         unsigned int fsWidth, unsigned int fsSetting)
{
    HWREG(baseAddr + MCASP_AFSRCTL) = ((fsMode << MCASP_AFSRCTL_RMOD_SHIFT) 
                                       | fsWidth | fsSetting);
}

/**
 * \brief   Configures the clock for the Transmit Section for outputing bits.
 *          The source and divide values shall be pre-determined. 
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   clkSrc        The source of the clock 
 * \param   mixClkDiv     Value which divides the mixed clock
 * \param   auxClkDiv     Value which divides the internal high frequency clock
 *
 *    clkSrc can take the values \n
 *         MCASP_TX_CLK_INTERNAL \n
 *         MCASP_TX_CLK_EXTERNAL \n
 *         MCASP_TX_CLK_MIXED \n
 *
 * \return  None.
 *
 * Note: If external clock is selected, the divide values will not be used. \n
 *       If mixed clock is selected, the clock divide mixClkDiv only 
 *       will be used. \n
 *       If internal clock is selected, both the divide values will be used.
 *
 **/
void McASPTxClkCfg(unsigned int baseAddr, unsigned int clkSrc,
                   unsigned int mixClkDiv, unsigned int auxClkDiv)
{
    HWREG(baseAddr + MCASP_ACLKXCTL) &= ~(MCASP_ACLKXCTL_CLKXM 
                                          | MCASP_ACLKXCTL_CLKXDIV);
    HWREG(baseAddr + MCASP_AHCLKXCTL) &= ~(MCASP_AHCLKXCTL_HCLKXM
                                           | MCASP_AHCLKXCTL_HCLKXDIV);
 
    /* Set the clock source to chose internal/external with clkdiv */
    HWREG(baseAddr + MCASP_ACLKXCTL) |= ((clkSrc & MCASP_ACLKXCTL_CLKXM)
                                          | mixClkDiv);
    HWREG(baseAddr + MCASP_AHCLKXCTL) |= ((clkSrc & MCASP_AHCLKXCTL_HCLKXM)
                                          | auxClkDiv);
}

/**
 * \brief   Configures the clock for the Receive Section for receiving bits.
 *          The source and divide values shall be pre-determined. 
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   clkSrc        The source of the clock 
 * \param   mixClkDiv     Value which divides the mixed clock
 * \param   auxClkDiv     Value which divides the internal high frequency clock
 *
 *    clkSrc can take the values \n
 *         MCASP_RX_CLK_INTERNAL \n
 *         MCASP_RX_CLK_EXTERNAL \n
 *         MCASP_RX_CLK_MIXED \n
 *
 * \return  None.
 *
 * Note: If external clock is selected, the divide values will not be used. \n
 *       If mixed clock is selected, the clock divide mixClkDiv only 
 *       will be used. \n
 *       If internal clock is selected, both the divide values will be used.
 *
 **/
void McASPRxClkCfg(unsigned int baseAddr, unsigned int clkSrc,
                   unsigned int mixClkDiv, unsigned int auxClkDiv)
{
    HWREG(baseAddr + MCASP_ACLKRCTL) &= ~(MCASP_ACLKRCTL_CLKRM 
                                          | MCASP_ACLKRCTL_CLKRDIV);
    HWREG(baseAddr + MCASP_AHCLKRCTL) &= ~(MCASP_AHCLKRCTL_HCLKRM
                                           | MCASP_AHCLKRCTL_HCLKRDIV);
 
    /* Set the clock source to chose internal/external with clkdiv */
    HWREG(baseAddr + MCASP_ACLKRCTL) |= ((clkSrc & MCASP_ACLKRCTL_CLKRM)
                                          | mixClkDiv);
    HWREG(baseAddr + MCASP_AHCLKRCTL) |= ((clkSrc & MCASP_AHCLKRCTL_HCLKRM)
                                          | auxClkDiv);
}

/**
 * \brief   Sets the polarity of the Transmitter Clock. If an external receiver
 *          samples data on the falling edge of the serial clock,  the 
 *          transmitter  must shift data out on the rising edge of the 
 *          serial clock and vice versa.
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   polarity      Polarity to be chosen
 *
 *    polarity can take the values \n
 *         MCASP_TX_CLK_POL_RIS_EDGE \n
 *         MCASP_TX_CLK_POL_FALL_EDGE \n
 *
 * \return  None.
 *
 **/
void McASPTxClkPolaritySet(unsigned int baseAddr, unsigned int polarity)
{
    HWREG(baseAddr + MCASP_ACLKXCTL) &= ~MCASP_ACLKXCTL_CLKXP;
    HWREG(baseAddr + MCASP_ACLKXCTL) |= polarity;
}

/**
 * \brief   Sets the polarity of the Rceiver Clock. If an external receiver
 *          shifts data on the falling edge of the serial clock,  the 
 *          receiver  must sample the data on the rising edge of the 
 *          serial clock and vice versa.
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   polarity      Polarity to be chosen
 *
 *    polarity can take the values \n
 *         MCASP_RX_CLK_POL_RIS_EDGE \n
 *         MCASP_RX_CLK_POL_FALL_EDGE \n
 *
 * \return  None.
 *
 **/
void McASPRxClkPolaritySet(unsigned int baseAddr, unsigned int polarity)
{
    HWREG(baseAddr + MCASP_ACLKRCTL) &= ~MCASP_ACLKRCTL_CLKRP;
    HWREG(baseAddr + MCASP_ACLKRCTL) |= polarity;
}

/**
 * \brief   Sets the polarity/inversion of the  High Frequency clock. This is
 *          valid if the transmitter clock source is internal or mixed.
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   polarity      polarity to be chosen
 *
 *    polarity can take the values \n
 *         MCASP_TX_HI_FREQ_CLK_INVERT \n
 *         MCASP_TX_HI_FREQ_CLK_NO_INVERT \n
 *     
 * \return  None.
 *
 **/
void McASPTxHFClkPolaritySet(unsigned int baseAddr, unsigned int polarity)
{
    HWREG(baseAddr + MCASP_AHCLKXCTL) &= ~MCASP_AHCLKXCTL_HCLKXP;
    HWREG(baseAddr + MCASP_AHCLKXCTL) |= polarity;
}

/**
 * \brief   Sets the polarity/inversion of the  High Frequency clock. This is
 *          valid if the receiver clock source is internal or mixed.
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   polarity      polarity to be chosen
 *
 *    polarity can take the values \n
 *         MCASP_RX_HI_FREQ_CLK_INVERT \n
 *         MCASP_RX_HI_FREQ_CLK_NO_INVERT \n
 *     
 * \return  None.
 *
 **/
void McASPRxHFClkPolaritySet(unsigned int baseAddr, unsigned int polarity)
{
    HWREG(baseAddr + MCASP_AHCLKRCTL) &= ~MCASP_AHCLKRCTL_HCLKRP;
    HWREG(baseAddr + MCASP_AHCLKRCTL) |= polarity;
}

/**
 * \brief   Synchronizes the transmitter and receiver Clocks 
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 *
 * \return  None.
 *
 **/
void McASPTxRxClkSyncEnable(unsigned int baseAddr)
{
    HWREG(baseAddr + MCASP_ACLKXCTL) &= ~MCASP_ACLKXCTL_ASYNC;
}

/**
 * \brief   Disable synchronization of the transmitter and receiver Clocks
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 *
 * \return  None.
 *
 **/
void McASPTxRxClkSyncDisable(unsigned int baseAddr)
{
    HWREG(baseAddr + MCASP_ACLKXCTL) |= MCASP_ACLKXCTL_ASYNC;
}

/**
 * \brief   Sets a serializer as transmitter
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   serNum        Serializer which is to be used as Transmitter.
 *
 * \return  None.
 *
 **/
void McASPSerializerTxSet(unsigned int baseAddr, unsigned int serNum)
{
    HWREG(baseAddr + MCASP_SRCTL(serNum)) &=  ~MCASP_SRCTL0_SRMOD;
    HWREG(baseAddr + MCASP_SRCTL(serNum)) |=  MCASP_SRCTL_SRMOD_TX;
 
}

/**
 * \brief   Sets a serializer as receiver
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   serNum        Serializer which is to be used as Receiver.
 *
 * \return  None.
 *
 **/
void McASPSerializerRxSet(unsigned int baseAddr, unsigned int serNum)
{
    HWREG(baseAddr + MCASP_SRCTL(serNum)) &=  ~MCASP_SRCTL0_SRMOD;
    HWREG(baseAddr + MCASP_SRCTL(serNum)) |=  MCASP_SRCTL_SRMOD_RX;

}

/**
 * \brief   Inactivates a serializer.
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   serNum        Serializer which is to be inactivated.
 *
 * \return  None.
 *
 **/
void McASPSerializerInactivate(unsigned int baseAddr, unsigned int serNum)
{
    HWREG(baseAddr + MCASP_SRCTL(serNum)) &=  ~MCASP_SRCTL0_SRMOD;
}

/**
 * \brief   Sets McASP pins as GPIO for general purpose use
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   pinMask       Mask of the pins to be configured as GPIO.
 *            pinMask can be a combination of the below values \n
 *                MCASP_PIN_AFSR  \n
 *                MCASP_PIN_AHCLKR \n                                       
 *                MCASP_PIN_ACLKR \n                                       
 *                MCASP_PIN_AFSX \n                                       
 *                MCASP_PIN_AHCLKX \n                                       
 *                MCASP_PIN_ACLKX \n                                        
 *                MCASP_PIN_AMUTE \n                                       
 *                MCASP_PIN_AXR(n) - For serializer 'n'           
 *    
 * \return  None.
 *
 **/
void McASPPinGPIOSet(unsigned int baseAddr, unsigned int pinMask)
{
     HWREG(baseAddr + MCASP_PFUNC) |= pinMask; 
}

/**
 * \brief   Sets McASP pins to use for McASP functionality
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   pinMask       Mask of the pins to be configured for McASP.
 *            pinMask can be a combination of the below values \n
 *                MCASP_PIN_AFSR  \n
 *                MCASP_PIN_AHCLKR \n                                       
 *                MCASP_PIN_ACLKR \n                                       
 *                MCASP_PIN_AFSX \n                                       
 *                MCASP_PIN_AHCLKX \n                                       
 *                MCASP_PIN_ACLKX \n                                        
 *                MCASP_PIN_AMUTE \n                                       
 *                MCASP_PIN_AXR(n) - For serializer 'n'           
 *
 * \return  None.
 *
 **/
void McASPPinMcASPSet(unsigned int baseAddr, unsigned int pinMask)
{
     HWREG(baseAddr + MCASP_PFUNC) &= ~pinMask; 
}

/**
 * \brief   Configures a McASP pin as an output pin.
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   pinMask       Mask of the pins to be configured as output
 *            pinMask can be a combination of the below values \n
 *                MCASP_PIN_AFSR  \n
 *                MCASP_PIN_AHCLKR \n                                       
 *                MCASP_PIN_ACLKR \n                                       
 *                MCASP_PIN_AFSX \n                                       
 *                MCASP_PIN_AHCLKX \n                                       
 *                MCASP_PIN_ACLKX \n                                        
 *                MCASP_PIN_AMUTE \n                                       
 *                MCASP_PIN_AXR(n) - For serializer 'n'           
 *
 * \return  None.
 *
 **/
void McASPPinDirOutputSet(unsigned int baseAddr, unsigned int pinMask)
{
     HWREG(baseAddr + MCASP_PDIR) |= pinMask; 
}

/**
 * \brief   Configures a McASP pin as an input pin.
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   pinMask       Mask of the pins to be configured as input
 *            pinMask can be a combination of the below values \n
 *                MCASP_PIN_AFSR  \n
 *                MCASP_PIN_AHCLKR \n                                       
 *                MCASP_PIN_ACLKR \n                                       
 *                MCASP_PIN_AFSX \n                                       
 *                MCASP_PIN_AHCLKX \n                                       
 *                MCASP_PIN_ACLKX \n                                        
 *                MCASP_PIN_AMUTE \n                                       
 *                MCASP_PIN_AXR(n) - For serializer 'n'           
 *
 * \return  None.
 *
 **/
void McASPPinDirInputSet(unsigned int baseAddr, unsigned int pinMask)
{
     HWREG(baseAddr + MCASP_PDIR) &= ~pinMask; 
}

/**
 * \brief   Sets the active time slot for the Transmitter section. The
 *          bit which is set in the mask will indicate that data will be
 *          transmitted during that time slot. 
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   slotMask      The time slot mask. 
 *
 * \return  None.
 *
 **/
void McASPTxTimeSlotSet(unsigned int baseAddr, unsigned int slotMask)
{
     HWREG(baseAddr + MCASP_XTDM) = slotMask; 
}

/**
 * \brief   Sets the active time slot for the receiver section. The
 *          bit which is set in the mask will indicate that data will be
 *          shifted in during that time slot. 
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   slotMask      The time slot mask. 
 *
 * \return  None.
 *
 **/
void McASPRxTimeSlotSet(unsigned int baseAddr, unsigned int slotMask)
{
     HWREG(baseAddr + MCASP_RTDM) = slotMask; 
}


/**
 * \brief   Enables Audio Mute on detecting the specified errors.
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   errFlags      Errors for which AMUTE to be enabled
 * \param   pinState      State of AMUTE pin to be driven if enabled.
 *            errFlags can be a combination of the following macros \n
 *                MCASP_AMUTE_TX_DMAERROR \n
 *                MCASP_AMUTE_TX_CLKFAIL \n
 *                MCASP_AMUTE_TX_SYNCERROR \n
 *                MCASP_AMUTE_TX_UNDERRUN \n
 *                MCASP_AMUTE_RX_DMAERROR \n
 *                MCASP_AMUTE_RX_CLKFAIL \n
 *                MCASP_AMUTE_RX_SYNCERROR \n
 *                MCASP_AMUTE_RX_OVERRUN \n
 *            pinState can take one of the values \n
 *                MCASP_AMUTE_PIN_HIGH \n
 *                MCASP_AMUTE_PIN_LOW 
 *
 * \return  None.
 *
 **/
void McASPAMuteEnable(unsigned int baseAddr, unsigned int errFlags,
                        unsigned int pinState)
{
    HWREG(baseAddr + MCASP_AMUTE) = errFlags | (MCASP_AMUTE_MUTEN & pinState); 
}

/**
 * \brief   Disables Audio Mute on detecting error
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 *
 * \return  None.
 *
 **/
void McASPAMuteDisable(unsigned int baseAddr)
{
    HWREG(baseAddr + MCASP_AMUTE) &= ~MCASP_AMUTE_MUTEN;
}

/**
 * \brief   Configures the transmitter clock check circuit.
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   clkDiv        Divide value for the McASP system clock. The McASP
 *                        system clock is divided with this value before passing
 *                        to the clock check circuit
 * \param   boundMin      Transmit clock minimum boundary
 * \param   boundMax      Transmit clock maximum boundary
 *            clkDiv can take one of the following values \n
 *               MCASP_TX_CLKCHCK_DIV1 \n  
 *               MCASP_TX_CLKCHCK_DIV2 \n  
 *               MCASP_TX_CLKCHCK_DIV4 \n  
 *               MCASP_TX_CLKCHCK_DIV8 \n  
 *               MCASP_TX_CLKCHCK_DIV16 \n  
 *               MCASP_TX_CLKCHCK_DIV32 \n  
 *               MCASP_TX_CLKCHCK_DIV64 \n  
 *               MCASP_TX_CLKCHCK_DIV128 \n  
 *               MCASP_TX_CLKCHCK_DIV256  
 *
 * \return  None.
 *
 **/
void McASPTxClkCheckConfig(unsigned int baseAddr, unsigned int clkDiv,
                           unsigned char boundMin, unsigned char boundMax)
{
    HWREG(baseAddr + MCASP_XCLKCHK) = clkDiv
                                      | boundMin << MCASP_XCLKCHK_XMIN_SHIFT 
                                      | boundMax << MCASP_XCLKCHK_XMAX_SHIFT ;
}

/**
 * \brief   Configures the receiver clock check circuit.
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   clkDiv        Divide value for the McASP system clock. The McASP
 *                        system clock is divided with this value prior to passing
 *                        to the clock check circuit
 * \param   boundMin      Receive clock minimum boundary
 * \param   boundMax      Receive clock maximum boundary
 *            clkDiv can take one of the following values \n
 *               MCASP_RX_CLKCHCK_DIV1 \n  
 *               MCASP_RX_CLKCHCK_DIV2 \n  
 *               MCASP_RX_CLKCHCK_DIV4 \n  
 *               MCASP_RX_CLKCHCK_DIV8 \n  
 *               MCASP_RX_CLKCHCK_DIV16 \n  
 *               MCASP_RX_CLKCHCK_DIV32 \n  
 *               MCASP_RX_CLKCHCK_DIV64 \n  
 *               MCASP_RX_CLKCHCK_DIV128 \n  
 *               MCASP_RX_CLKCHCK_DIV256  
 *
 * \return  None.
 *
 **/
void McASPRxClkCheckConfig(unsigned int baseAddr, unsigned int clkDiv,
                           unsigned char boundMin, unsigned char boundMax)
{
    HWREG(baseAddr + MCASP_RCLKCHK) = clkDiv
                                      | boundMin << MCASP_RCLKCHK_RMIN_SHIFT 
                                      | boundMax << MCASP_RCLKCHK_RMAX_SHIFT ;
}

/**
 * \brief   Activates the AMUTEIN pin and drives the AMUTE active.
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   polarity      polarity of AMUTEIN which shall drive the 
 *                        AMUTE active. 
 *            polarity can take one of the following values. \n
 *                MCASP_AMUTEIN_POL_HIGH - high on AMUTEIN pin  \n
 *                MCASP_AMUTEIN_POL_LOW - low on AMUTEIN pin 
 *             
 * \return  None.
 *
 **/
void McASPAMUTEINActivate(unsigned int baseAddr, unsigned int polarity)
{
    HWREG(baseAddr + MCASP_AMUTE) &= ~MCASP_AMUTE_INPOL;

    HWREG(baseAddr + MCASP_AMUTE) |= (MCASP_AMUTE_INSTAT | MCASP_AMUTE_INEN
                                      |(polarity & MCASP_AMUTE_INPOL)); 
}

/**
 * \brief   Enables the specified Transmitter interrupts.
 *
 * \param   baseAddr     Base Address of the McASP Module Registers.
 * \param   intMask      The transmitter interrupts to be enabled 
 *            intMask can be a logical OR combination of the values \n
 *                 MCASP_TX_STARTOFFRAME \n
 *                 MCASP_TX_DATAREADY \n
 *                 MCASP_TX_LASTSLOT \n
 *                 MCASP_TX_DMAERROR \n
 *                 MCASP_TX_CLKFAIL \n
 *                 MCASP_TX_SYNCERROR \n
 *                 MCASP_TX_UNDERRUN
 *
 * \return  None.
 *
 **/
void McASPTxIntEnable(unsigned int baseAddr, unsigned int intMask)
{
    HWREG(baseAddr + MCASP_XINTCTL) |= intMask; 
}

/**
 * \brief   Enables the specified Receiver interrupts.
 *
 * \param   baseAddr     Base Address of the McASP Module Registers.
 * \param   intMask      The receive interrupts to be enabled 
 *            intMask can be a logical OR combination of the values \n
 *                 MCASP_RX_STARTOFFRAME \n
 *                 MCASP_RX_DATAREADY \n
 *                 MCASP_RX_LASTSLOT \n
 *                 MCASP_RX_DMAERROR \n
 *                 MCASP_RX_CLKFAIL \n
 *                 MCASP_RX_SYNCERROR \n
 *                 MCASP_RX_OVERRUN
 *
 * \return  None.
 *
 **/
void McASPRxIntEnable(unsigned int baseAddr, unsigned int intMask)
{
    HWREG(baseAddr + MCASP_RINTCTL) |= intMask; 
}

/**
 * \brief   Disables the specified Transmitter interrupts.
 *
 * \param   baseAddr     Base Address of the McASP Module Registers.
 * \param   intMask      The transmitter interrupts to be disabled 
 *            intMask can be a logical OR combination of the values \n
 *                 MCASP_TX_STARTOFFRAME \n
 *                 MCASP_TX_DATAREADY \n
 *                 MCASP_TX_LASTSLOT \n
 *                 MCASP_TX_DMAERROR \n
 *                 MCASP_TX_CLKFAIL \n
 *                 MCASP_TX_SYNCERROR \n
 *                 MCASP_TX_UNDERRUN
 *
 * \return  None.
 *
 **/
void McASPTxIntDisable(unsigned int baseAddr, unsigned int intMask)
{
    HWREG(baseAddr + MCASP_XINTCTL) &= ~intMask; 
}

/**
 * \brief   Disables the specified Receiver interrupts.
 *
 * \param   baseAddr     Base Address of the McASP Module Registers.
 * \param   intMask      The receive interrupts to be disabled 
 *            intMask can be a logical OR combination of the values \n
 *                 MCASP_RX_STARTOFFRAME \n
 *                 MCASP_RX_DATAREADY \n
 *                 MCASP_RX_LASTSLOT \n
 *                 MCASP_RX_DMAERROR \n
 *                 MCASP_RX_CLKFAIL \n
 *                 MCASP_RX_SYNCERROR \n
 *                 MCASP_RX_OVERRUN
 *
 * \return  None.
 *
 **/
void McASPRxIntDisable(unsigned int baseAddr, unsigned int intMask)
{
    HWREG(baseAddr + MCASP_RINTCTL) &= ~intMask; 
}

/**
 * \brief   Activates the Transmit Serializers
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 *
 * \return  None.
 *
 **/
void McASPTxSerActivate(unsigned int baseAddr)
{
    HWREG(baseAddr + MCASP_XSTAT) = 0xFFFF;

    /* Release transmit serializers from reset*/
    HWREG(baseAddr + MCASP_GBLCTL) |= MCASP_GBLCTL_XSRCLR; 
    while((HWREG(baseAddr + MCASP_GBLCTL) & MCASP_GBLCTL_XSRCLR) 
          != MCASP_GBLCTL_XSRCLR) ;
}

/**
 * \brief   Activates the Receive Serializers
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 *
 * \return  None.
 *
 **/
void McASPRxSerActivate(unsigned int baseAddr)
{
    HWREG(baseAddr + MCASP_RSTAT) = 0xFFFF;

    /* Release transmit serializers from reset*/
    HWREG(baseAddr + MCASP_GBLCTL) |= MCASP_GBLCTL_RSRCLR; 
    while((HWREG(baseAddr + MCASP_GBLCTL) & MCASP_GBLCTL_RSRCLR) 
          != MCASP_GBLCTL_RSRCLR) ;
}

/**
 * \brief   Starts the McASP Transmitter Clock. 
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   clkSrc        The transmitter clock source.
 *
 *    clkSrc can take the values \n
 *         MCASP_TX_CLK_INTERNAL \n
 *         MCASP_TX_CLK_EXTERNAL \n
 *         MCASP_TX_CLK_MIXED \n
 *
 * \return  None.
 *
 **/
void McASPTxClkStart(unsigned int baseAddr, unsigned int clkSrc)
{
    /* Release the high frequency clock from reset*/
    HWREG(baseAddr + MCASP_GBLCTL) |= MCASP_GBLCTL_XHCLKRST; 
    while((HWREG(baseAddr + MCASP_GBLCTL) & MCASP_GBLCTL_XHCLKRST) 
          != MCASP_GBLCTL_XHCLKRST) ;
     
    if(clkSrc != MCASP_TX_CLK_EXTERNAL)
    {
       /* Release the clock from reset*/
        HWREG(baseAddr + MCASP_GBLCTL) |= MCASP_GBLCTL_XCLKRST; 
        while((HWREG(baseAddr + MCASP_GBLCTL) & MCASP_GBLCTL_XCLKRST) 
              != MCASP_GBLCTL_XCLKRST) ;
    }
}

/**
 * \brief   Starts the McASP Receiver Clock. 
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   clkSrc        The receiver clock source.
 *
 *    clkSrc can take the values \n
 *         MCASP_RX_CLK_INTERNAL \n
 *         MCASP_RX_CLK_EXTERNAL \n
 *         MCASP_RX_CLK_MIXED \n
 *
 * \return  None.
 *
 **/
void McASPRxClkStart(unsigned int baseAddr, unsigned int clkSrc)
{
    /* Release the high frequency clock from reset*/
    HWREG(baseAddr + MCASP_GBLCTL) |= MCASP_GBLCTL_RHCLKRST; 
    while((HWREG(baseAddr + MCASP_GBLCTL) & MCASP_GBLCTL_RHCLKRST) 
          != MCASP_GBLCTL_RHCLKRST) ;
     
    if(clkSrc != MCASP_RX_CLK_EXTERNAL)
    {
        /* Release the clock from reset*/
        HWREG(baseAddr + MCASP_GBLCTL) |= MCASP_GBLCTL_RCLKRST; 
        while((HWREG(baseAddr + MCASP_GBLCTL) & MCASP_GBLCTL_RCLKRST)
              != MCASP_GBLCTL_RCLKRST) ;
    }
}

/**
 * \brief   Enables the McASP Transmission. When this API is called, 
 *          The transmit state machine and the frame sync generators are 
 *          released from reset. The McASP starts transmission on the
 *          first frame sync after this.
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 *
 * \return  None.
 *
 **/
void McASPTxEnable(unsigned int baseAddr)
{
    /* Release the Transmit State machine from reset*/
    HWREG(baseAddr + MCASP_GBLCTL) |= MCASP_GBLCTL_XSMRST; 
    while((HWREG(baseAddr + MCASP_GBLCTL) & MCASP_GBLCTL_XSMRST) 
          != MCASP_GBLCTL_XSMRST) ;
     
    /* Release the frame sync generator from reset*/
    HWREG(baseAddr + MCASP_GBLCTL) |= MCASP_GBLCTL_XFRST; 
    while((HWREG(baseAddr + MCASP_GBLCTL) & MCASP_GBLCTL_XFRST) 
          != MCASP_GBLCTL_XFRST) ;
}

/**
 * \brief   Enables the McASP Reception. When this API is called, 
 *          The receive state machine and the frame sync generators are 
 *          released from reset. The McASP starts reception on the
 *          first frame sync after this.
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 *
 * \return  None.
 *
 **/
void McASPRxEnable(unsigned int baseAddr)
{
    /* Release the Receive State machine from reset*/
    HWREG(baseAddr + MCASP_GBLCTL) |= MCASP_GBLCTL_RSMRST; 
    while((HWREG(baseAddr + MCASP_GBLCTL) & MCASP_GBLCTL_RSMRST) 
          != MCASP_GBLCTL_RSMRST) ;
     
    /* Release the frame sync generator from reset*/
    HWREG(baseAddr + MCASP_GBLCTL) |= MCASP_GBLCTL_RFRST; 
    while((HWREG(baseAddr + MCASP_GBLCTL) & MCASP_GBLCTL_RFRST) 
          != MCASP_GBLCTL_RFRST) ;
}

/**
 * \brief   Reads a receive buffer through peripheral configuration port. 
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   serNum        Serializer number
 *
 * \return  Buffer contents
 *
 **/
unsigned int McASPRxBufRead(unsigned int baseAddr, unsigned int serNum)
{
    return(HWREG(baseAddr + MCASP_RBUF(serNum)));
}

/**
 * \brief   Writes to a transmit buffer through peripheral configuration port. 
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   serNum        Serializer number
 * \param   data          Data to be written
 *
 * \return  None.
 *
 **/
void McASPTxBufWrite(unsigned int baseAddr, unsigned int serNum, 
                     unsigned int data)
{
    HWREG(baseAddr + MCASP_XBUF(serNum)) = data;
}

/**
 * \brief   Gets the status of McASP transmission.
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 *
 * \return  Status of McASP Transmission. This is the contents of the 
 *          register XSTAT. \n
 *          The below tokens can be used for each status bits returned. \n
 *              MCASP_TX_STAT_ERR  \n                    
 *              MCASP_TX_STAT_DMAERR \n                  
 *              MCASP_TX_STAT_STARTOFFRAME \n             
 *              MCASP_TX_STAT_DATAREADY \n            
 *              MCASP_TX_STAT_LASTSLOT \n                
 *              MCASP_TX_STAT_CURRSLOT_EVEN \n           
 *              MCASP_TX_STAT_CURRSLOT_ODD \n             
 *              MCASP_TX_STAT_CLKFAIL \n                 
 *              MCASP_TX_STAT_SYNCERR \n                
 *              MCASP_TX_STAT_UNDERRUN               
 *
 **/
unsigned int McASPTxStatusGet(unsigned int baseAddr)
{
    return (HWREG(baseAddr + MCASP_XSTAT));
}

/**
 * \brief   Gets the status of McASP reception
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 *
 * \return  Status of McASP reception. This is the contents of the
 *          register RSTAT. \n
 *          The below tokens can be used for each status bits returned. \n
 *              MCASP_RX_STAT_ERR  \n
 *              MCASP_RX_STAT_DMAERR \n
 *              MCASP_RX_STAT_STARTOFFRAME \n
 *              MCASP_RX_STAT_DATAREADY \n
 *              MCASP_RX_STAT_LASTSLOT \n
 *              MCASP_RX_STAT_CURRSLOT_EVEN \n
 *              MCASP_RX_STAT_CURRSLOT_ODD \n
 *              MCASP_RX_STAT_CLKFAIL \n
 *              MCASP_RX_STAT_SYNCERR \n
 *              MCASP_RX_STAT_OVERRUN
 *
 **/
unsigned int McASPRxStatusGet(unsigned int baseAddr)
{
    return (HWREG(baseAddr + MCASP_RSTAT));
}

/**
* \brief  This function saves the context of McASP registers.
*         This is useful in power management, where the power supply to McASP
*         controller will be cut off.
*
* \param  baseAddrCtrl     Base Address of the McASP Module Control Registers.
* \param  baseAddrFifo     Base Address of the McASP FIFO Registers.
* \param  contextPtr       The pointer to structure where McASP context is saved
* \param  sectFlag         Sections for saving context
*           sectFlag can take the following values \n
*                McASP_CONTEXT_TX - Context of Transmit section will be saved
*                McASP_CONTEXT_RX - Context of Receive section will be saved
*                McASP_CONTEXT_BOTH - Both section contexts will be saved
*
* \return  None
**/
void McASPContextSave(unsigned int baseAddrCtrl, unsigned int baseAddrFifo,
                      MCASPCONTEXT *contextPtr, unsigned int sectFlag)
{
    unsigned int idx;

    /* Check if Transmit section context needs to be saved */
    if(McASP_CONTEXT_TX & sectFlag)
    {
        contextPtr->fifoWfifoCtl = HWREG(baseAddrFifo + MCASP_FIFO_WFIFOCTL); 
        contextPtr->xmask = HWREG(baseAddrCtrl + MCASP_XMASK);
        contextPtr->xfmt = HWREG(baseAddrCtrl + MCASP_XFMT);
        contextPtr->afsxctl = HWREG(baseAddrCtrl + MCASP_AFSXCTL);
        contextPtr->aclkxctl = HWREG(baseAddrCtrl + MCASP_ACLKXCTL);
        contextPtr->ahclkxctl = HWREG(baseAddrCtrl + MCASP_AHCLKXCTL);
        contextPtr->xclkchk = HWREG(baseAddrCtrl + MCASP_XCLKCHK);
        contextPtr->xtdm = HWREG(baseAddrCtrl + MCASP_XTDM);
    }

    /* Check if receive section context needs to be saved */
    if(McASP_CONTEXT_RX & sectFlag)
    {
        contextPtr->fifoRfifoCtl = HWREG(baseAddrFifo + MCASP_FIFO_RFIFOCTL); 
        contextPtr->rmask = HWREG(baseAddrCtrl + MCASP_RMASK);
        contextPtr->rfmt = HWREG(baseAddrCtrl + MCASP_RFMT);
        contextPtr->afsrctl = HWREG(baseAddrCtrl + MCASP_AFSRCTL);
        contextPtr->aclkrctl = HWREG(baseAddrCtrl + MCASP_ACLKRCTL);
        contextPtr->ahclkrctl = HWREG(baseAddrCtrl + MCASP_AHCLKRCTL);
        contextPtr->rclkchk = HWREG(baseAddrCtrl + MCASP_RCLKCHK);
        contextPtr->rtdm = HWREG(baseAddrCtrl + MCASP_RTDM);
    }

    for(idx = 0; idx < 15; idx++)
    {
        contextPtr->srctl[idx] = HWREG(baseAddrCtrl + MCASP_SRCTL(idx));
    }

    contextPtr->pfunc = HWREG(baseAddrCtrl + MCASP_PFUNC);
    contextPtr->pdir = HWREG(baseAddrCtrl + MCASP_PDIR);
    contextPtr->gblctl = HWREG(baseAddrCtrl + MCASP_GBLCTL);
}

/**
* \brief  This function restores the context of McASP registers.
*         This is useful in power management, where the power supply to McASP
*         controller will be cut off. Note that this API does not enable McASP 
*         clocks. Also McASP state machine shall be brought out of reset 
*         separately.
*
* \param  baseAddrCtrl     Base Address of the McASP Module Control Registers.
* \param  baseAddrFifo     Base Address of the McASP FIFO Registers.
* \param  contextPtr       The pointer to structure where McASP context is saved
* \param  sectFlag         Sections for saving context
*           sectFlag can take the following values \n
*                McASP_CONTEXT_TX - Context of Transmit section will be saved
*                McASP_CONTEXT_RX - Context of Receive section will be saved
*                McASP_CONTEXT_BOTH - Both section contexts will be saved
*
* \return  None
**/
void McASPContextRestore(unsigned int baseAddrCtrl, unsigned int baseAddrFifo,
                         MCASPCONTEXT *contextPtr, unsigned int sectFlag)
{
    unsigned int idx;

    if(McASP_CONTEXT_TX & sectFlag)
    {
        HWREG(baseAddrCtrl + MCASP_XGBLCTL) = 0x0;
        HWREG(baseAddrFifo + MCASP_FIFO_WFIFOCTL) = contextPtr->fifoWfifoCtl;
        HWREG(baseAddrCtrl + MCASP_XMASK) = contextPtr->xmask;
        HWREG(baseAddrCtrl + MCASP_XFMT) = contextPtr->xfmt;
        HWREG(baseAddrCtrl + MCASP_AFSXCTL) = contextPtr->afsxctl;
        HWREG(baseAddrCtrl + MCASP_ACLKXCTL) = contextPtr->aclkxctl;
        HWREG(baseAddrCtrl + MCASP_AHCLKXCTL) = contextPtr->ahclkxctl;
        HWREG(baseAddrCtrl + MCASP_XCLKCHK) = contextPtr->xclkchk;
        HWREG(baseAddrCtrl + MCASP_XTDM) = contextPtr->xtdm;
    }

    if(McASP_CONTEXT_RX & sectFlag)
    {
        HWREG(baseAddrCtrl + MCASP_RGBLCTL) = 0x0;
        HWREG(baseAddrFifo + MCASP_FIFO_RFIFOCTL) = contextPtr->fifoRfifoCtl;
        HWREG(baseAddrCtrl + MCASP_RMASK) = contextPtr->rmask;
        HWREG(baseAddrCtrl + MCASP_RFMT) = contextPtr->rfmt;
        HWREG(baseAddrCtrl + MCASP_AFSRCTL) = contextPtr->afsrctl;
        HWREG(baseAddrCtrl + MCASP_ACLKRCTL) = contextPtr->aclkrctl;
        HWREG(baseAddrCtrl + MCASP_AHCLKRCTL) = contextPtr->ahclkrctl;
        HWREG(baseAddrCtrl + MCASP_RCLKCHK) = contextPtr->rclkchk;
        HWREG(baseAddrCtrl + MCASP_RTDM) = contextPtr->rtdm;
    }

    for(idx = 0; idx < 15; idx++)
    {
        HWREG(baseAddrCtrl + MCASP_SRCTL(idx)) = contextPtr->srctl[idx] ;
    }

    HWREG(baseAddrCtrl + MCASP_PFUNC) = contextPtr->pfunc;
    HWREG(baseAddrCtrl + MCASP_PDIR) = contextPtr->pdir;
}

/***************************** End Of File ***********************************/

