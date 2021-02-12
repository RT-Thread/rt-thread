/* *****************************************************************************
 * Copyright (C) 2016 Maxim Integrated Products, Inc., All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of Maxim Integrated
 * Products, Inc. shall not be used except as stated in the Maxim Integrated
 * Products, Inc. Branding Policy.
 *
 * The mere transfer of this software does not imply any licenses
 * of trade secrets, proprietary technology, copyrights, patents,
 * trademarks, maskwork rights, or any other form of intellectual
 * property whatsoever. Maxim Integrated Products, Inc. retains all
 * ownership rights.
 *
 * $Date: 2019-06-25 10:15:10 -0500 (Tue, 25 Jun 2019) $
 * $Revision: 44277 $
 *
 **************************************************************************** */

/* **** Includes **** */
#include <string.h>
#include "mxc_config.h"
#include "mxc_assert.h"
#include "mxc_sys.h"
#include "tmr_utils.h"
#include "mxc_lock.h"
#include "spi17y.h"

/* **** Definitions **** */

/* **** Globals **** */


typedef struct {
    spi17y_req_t *req;
    int started;
    unsigned last_size;
    unsigned deass;
} spi17y_req_state_t;

static spi17y_req_state_t states[MXC_SPI17Y_INSTANCES];

/* **** Functions **** */
static int SPI17Y_TransSetup(mxc_spi17y_regs_t *spi, spi17y_req_t *req, int master);
static int SPI17Y_MasterTransHandler(mxc_spi17y_regs_t *spi, spi17y_req_t *req, uint8_t async);
static int SPI17Y_TransHandler(mxc_spi17y_regs_t *spi, spi17y_req_t *req, uint8_t async);
static int SPI17Y_SlaveTransHandler(mxc_spi17y_regs_t *spi, spi17y_req_t *req, uint8_t async);

/* ************************************************************************** */
int SPI17Y_Init(mxc_spi17y_regs_t *spi, unsigned int mode, unsigned int freq,
                const sys_cfg_spi17y_t* sys_cfg)
{
    uint32_t freq_div;
    int spi_num, error, hi_clk, lo_clk, scale;
    
    spi_num = MXC_SPI17Y_GET_IDX(spi);
    MXC_ASSERT(spi_num >= 0);
    
    if (mode > 3) {
        return E_BAD_PARAM;
    }
    
    if ((error = SYS_SPI17Y_Init(spi, sys_cfg)) != E_NO_ERROR) {
        return error;
    }
    
    states[spi_num].req = NULL;
    states[spi_num].last_size = 0;
    states[spi_num].deass = 1;
    
    // Enable SPI17Y
    spi->ctrl0 = (MXC_F_SPI17Y_CTRL0_EN);
    spi->ss_time = ((0x1 << MXC_F_SPI17Y_SS_TIME_PRE_POS) |
                    (0x1 << MXC_F_SPI17Y_SS_TIME_POST_POS) |
                    (0x1 << MXC_F_SPI17Y_SS_TIME_INACT_POS));
                    
    // Check if frequency is too high
    if (freq > PeripheralClock) {
        return E_BAD_PARAM;
    }
    
    // Set the clock high and low
    freq_div = PeripheralClock/ (freq);
    hi_clk = freq_div/2;
    lo_clk = freq_div/2;
    scale = 0;
    
    if (freq_div %2) {
        hi_clk +=1;
    }
    
    while (hi_clk > 16 && scale < 9) {
        hi_clk /= 2;
        lo_clk /=2;
        scale ++;
    }
    
    spi->clk_cfg = ((lo_clk << MXC_F_SPI17Y_CLK_CFG_LO_POS) |
                    (hi_clk << MXC_F_SPI17Y_CLK_CFG_HI_POS));
                    
    MXC_SETFIELD(spi->clk_cfg, MXC_F_SPI17Y_CLK_CFG_SCALE, (scale << MXC_F_SPI17Y_CLK_CFG_SCALE_POS));
    
    // Set the mode
    spi->ctrl2 = (mode << MXC_F_SPI17Y_CTRL2_CPHA_POS);
    
    // Clear the interrupts
    spi->int_fl = spi->int_fl;
    
    return E_NO_ERROR;
}

/* ************************************************************************* */
int SPI17Y_Shutdown(mxc_spi17y_regs_t *spi)
{
    int spi_num, err;
    spi17y_req_t *temp_req;
    
    // Disable and clear interrupts
    spi->int_en = 0;
    spi->int_fl = spi->int_fl;
    
    // Disable SPI17Y and FIFOS
    spi->ctrl0 &= ~(MXC_F_SPI17Y_CTRL0_EN);
    spi->dma &= ~(MXC_F_SPI17Y_DMA_TX_FIFO_EN | MXC_F_SPI17Y_DMA_RX_FIFO_EN);
    
    // Call all of the pending callbacks for this SPI17Y
    spi_num = MXC_SPI17Y_GET_IDX(spi);
    if (states[spi_num].req != NULL) {
    
        // Save the request
        temp_req = states[spi_num].req;
        
        // Unlock this SPI17Y
        mxc_free_lock((uint32_t*)&states[spi_num].req);
        
        // Callback if not NULL
        if (temp_req->callback != NULL) {
            temp_req->callback(temp_req, E_SHUTDOWN);
        }
    }
    
    // Clear registers
    spi->ctrl0 = 0;
    spi->ctrl1 = 0;
    spi->ctrl2 = 0;
    spi->ss_time = 0;
    
    // Clear system level configurations
    if ((err = SYS_SPI17Y_Shutdown(spi)) != E_NO_ERROR) {
        return err;
    }
    
    return E_NO_ERROR;
}

/* ************************************************************************** */
int SPI17Y_TransSetup(mxc_spi17y_regs_t *spi, spi17y_req_t *req, int master)
{
    int spi_num;
    if ((req->tx_data == NULL) && (req->rx_data == NULL)) {
        return E_BAD_PARAM;
    }
    
    if ((req->width > SPI17Y_WIDTH_1) && (req->tx_data != NULL) && (req->rx_data != NULL)) {
        return E_BAD_PARAM;
    }
    
    // HW has problem with these two character sizes
    if (req->bits == 1 || req->bits == 9) {
        return E_BAD_PARAM;
    }
    spi_num = MXC_SPI17Y_GET_IDX(spi);
    MXC_ASSERT(spi_num >= 0);
    MXC_ASSERT(req->ssel < MXC_SPI17Y_SS_INSTANCES);
    
    req->tx_num = 0;
    req->rx_num = 0;
    
    if (req->len == 0) {
        return E_NO_ERROR;
    }
    
    states[spi_num].req = req;
    states[spi_num].started = 0;
    
    // HW requires disabling/renabling SPI block at end of each transaction (when SS is inactive).
    if (states[spi_num].deass == 1) {
        spi->ctrl0 &= ~(MXC_F_SPI17Y_CTRL0_EN);
    }
    
    if (master) {
        // Enable master mode
        
        spi->ctrl0 |= MXC_F_SPI17Y_CTRL0_MASTER;
        
        // Setup the slave select
        MXC_SETFIELD(spi->ctrl0, MXC_F_SPI17Y_CTRL0_SS, ((0x1 << req->ssel) << MXC_F_SPI17Y_CTRL0_SS_POS));
        spi->ctrl2 |= ((req->ssel_pol << req->ssel)<<MXC_F_SPI17Y_CTRL2_SS_POL_POS);
    } else {
        // Enable slave mode
        spi->ctrl0 &= ~MXC_F_SPI17Y_CTRL0_MASTER;
        // Setup the slave select
        spi->ctrl2 |= ((req->ssel_pol << 0)<<MXC_F_SPI17Y_CTRL2_SS_POL_POS);
    }
    
    if ((req->bits != states[spi_num].last_size)) {
        // Setup the character size
        // Master should only change character size at the end of a transaction.  No restrictions on when slave can change.
        if (!master || (!(spi->stat & MXC_F_SPI17Y_STAT_BUSY) && (states[spi_num].deass == 1)) || !(spi->ctrl0 & MXC_F_SPI17Y_CTRL0_EN)) {
            //disable spi to change transfer size
            spi->ctrl0 &= ~(MXC_F_SPI17Y_CTRL0_EN);
            // set bit size
            states[spi_num].last_size = req->bits;
            if (req->bits <16) {
                MXC_SETFIELD(spi->ctrl2, MXC_F_SPI17Y_CTRL2_NUMBITS, req->bits << MXC_F_SPI17Y_CTRL2_NUMBITS_POS);
            } else {
                MXC_SETFIELD(spi->ctrl2, MXC_F_SPI17Y_CTRL2_NUMBITS, 0 << MXC_F_SPI17Y_CTRL2_NUMBITS_POS);
            }
        } else {
            // cant change transfer size while spi is busy
            return E_BAD_STATE;
        }
    }
    
    // Setup the data width
    if (req->width == SPI17Y_WIDTH_4) {
        MXC_SETFIELD(spi->ctrl2, MXC_F_SPI17Y_CTRL2_DATA_WIDTH, MXC_S_SPI17Y_CTRL2_DATA_WIDTH_QUAD);
    } else if (req->width == SPI17Y_WIDTH_2) {
        MXC_SETFIELD(spi->ctrl2, MXC_F_SPI17Y_CTRL2_DATA_WIDTH, MXC_S_SPI17Y_CTRL2_DATA_WIDTH_DUAL);
    } else {
        MXC_SETFIELD(spi->ctrl2, MXC_F_SPI17Y_CTRL2_DATA_WIDTH, MXC_S_SPI17Y_CTRL2_DATA_WIDTH_MONO);
    }
    
    // Setup the number of characters to transact
    if (req->len > (MXC_F_SPI17Y_CTRL1_TX_NUM_CHAR >> MXC_F_SPI17Y_CTRL1_TX_NUM_CHAR_POS)) {
        return E_BAD_PARAM;
    }
    
    if (req->rx_data != NULL) {
        // The TX_NUM field is used for both RX and TX length when in 4-wire mode.
        if(req->width == SPI17Y_WIDTH_1) {
            MXC_SETFIELD(spi->ctrl1, MXC_F_SPI17Y_CTRL1_TX_NUM_CHAR,
                        req->len << MXC_F_SPI17Y_CTRL1_TX_NUM_CHAR_POS);
        } else {
            MXC_SETFIELD(spi->ctrl1, MXC_F_SPI17Y_CTRL1_RX_NUM_CHAR,
                        req->len << MXC_F_SPI17Y_CTRL1_RX_NUM_CHAR_POS);
        }
        spi->dma |= MXC_F_SPI17Y_DMA_RX_FIFO_EN;
    } else {
        spi->ctrl1 &= ~(MXC_F_SPI17Y_CTRL1_RX_NUM_CHAR);
        spi->dma &= ~(MXC_F_SPI17Y_DMA_RX_FIFO_EN);
    }

    // Must use TXFIFO and NUM in full duplex
    if (req->width == SPI17Y_WIDTH_1
            && !((spi->ctrl2 & MXC_F_SPI17Y_CTRL2_THREE_WIRE)>> MXC_F_SPI17Y_CTRL2_THREE_WIRE_POS)) {
        
        if (req->tx_data == NULL) {
            // Must have something to send, so we'll use the rx_data buffer initialized to 0.
            memset(req->rx_data, 0, (req->bits > 8 ? req->len << 1 : req->len));
            req->tx_data = req->rx_data;
            req->tx_num = 0;
        }
    }
    
    if(req->tx_data != NULL) {
        MXC_SETFIELD(spi->ctrl1, MXC_F_SPI17Y_CTRL1_TX_NUM_CHAR,
                     req->len << MXC_F_SPI17Y_CTRL1_TX_NUM_CHAR_POS);
        spi->dma |= MXC_F_SPI17Y_DMA_TX_FIFO_EN;
    } else {
        spi->dma &= ~(MXC_F_SPI17Y_DMA_TX_FIFO_EN);
    }
    
    spi->dma |= MXC_F_SPI17Y_DMA_TX_FIFO_CLEAR | MXC_F_SPI17Y_DMA_RX_FIFO_CLEAR;
    spi->ctrl0 |= (MXC_F_SPI17Y_CTRL0_EN);
    
    states[spi_num].deass = req->deass;
    // Clear master done flag
    spi->int_fl = MXC_F_SPI17Y_INT_FL_M_DONE;
    return E_NO_ERROR;
}

/* ************************************************************************** */
void SPI17Y_Handler(mxc_spi17y_regs_t *spi)
{
    int spi_num, rx_avail;
    uint32_t flags;
    
    // Clear the interrupt flags
    spi->int_en = 0;
    flags = spi->int_fl;
    spi->int_fl = flags;
    
    spi_num = MXC_SPI17Y_GET_IDX(spi);
    // Figure out if this SPI17Y has an active request
    if ((states[spi_num].req != NULL) && (flags)) {
        if ((spi->ctrl0 & MXC_F_SPI17Y_CTRL0_MASTER)>> MXC_F_SPI17Y_CTRL0_MASTER_POS) {
            do {
                SPI17Y_MasterTransHandler(spi,  states[spi_num].req, 1);
                rx_avail = (spi->dma & MXC_F_SPI17Y_DMA_RX_FIFO_CNT) >> MXC_F_SPI17Y_DMA_RX_FIFO_CNT_POS;
            } while ((states[spi_num].req->rx_data != NULL) && (rx_avail > (spi->dma & MXC_F_SPI17Y_DMA_RX_FIFO_LEVEL)
                     >>MXC_F_SPI17Y_DMA_RX_FIFO_LEVEL_POS));
                     
        } else {
            do {
                SPI17Y_SlaveTransHandler(spi, states[spi_num].req, 1);
                rx_avail = (spi->dma & MXC_F_SPI17Y_DMA_RX_FIFO_CNT) >> MXC_F_SPI17Y_DMA_RX_FIFO_CNT_POS;
            } while ((states[spi_num].req->rx_data != NULL) && (rx_avail > (spi->dma & MXC_F_SPI17Y_DMA_RX_FIFO_LEVEL)
                     >>MXC_F_SPI17Y_DMA_RX_FIFO_LEVEL_POS));
                     
        }
    }
    
}

/* ************************************************************************** */
int SPI17Y_MasterTrans(mxc_spi17y_regs_t *spi,spi17y_req_t *req)
{
    int error;
    if ((error =SPI17Y_TransSetup(spi, req, 1)) != E_NO_ERROR) {
        return error;
    }
    req->callback = NULL;
    
    while (SPI17Y_MasterTransHandler(spi,req,0)==0) {
    }
    
    while (!(spi->int_fl & MXC_F_SPI17Y_INT_FL_M_DONE)) {
        
    }
    
    return E_NO_ERROR;
}


/* ************************************************************************** */
int SPI17Y_SlaveTrans(mxc_spi17y_regs_t *spi, spi17y_req_t *req)
{
    int error;
    if ((error =SPI17Y_TransSetup(spi, req,0)) != E_NO_ERROR) {
        return error;
    }
    req->callback = NULL;
    
    while (SPI17Y_SlaveTransHandler(spi,req,0)==0) {
        
    }
    
    return E_NO_ERROR;
}

/* ************************************************************************** */
int SPI17Y_MasterTransAsync(mxc_spi17y_regs_t *spi, spi17y_req_t *req)
{
    int error;
    if ((error =SPI17Y_TransSetup(spi, req, 1))!= E_NO_ERROR) {
        return error;
    }
    
    SPI17Y_MasterTransHandler(spi,req, 1);
    
    return E_NO_ERROR;
}

/* ************************************************************************** */
int SPI17Y_SlaveTransAsync(mxc_spi17y_regs_t *spi, spi17y_req_t *req)
{
    int error;
    if ((error =SPI17Y_TransSetup(spi, req, 0)) != E_NO_ERROR) {
        return error;
    }
    
    SPI17Y_SlaveTransHandler(spi,req, 1);
    
    
    return E_NO_ERROR;
}

/* ************************************************************************** */
int SPI17Y_MasterTransHandler(mxc_spi17y_regs_t *spi, spi17y_req_t *req,uint8_t async)
{
    int retval;
    int spi_num;
    
    spi_num = MXC_SPI17Y_GET_IDX(spi);
    
    // Leave slave select asserted at the end of the transaction
    if (!req->deass) {
        spi->ctrl0 |= MXC_F_SPI17Y_CTRL0_SS_CTRL;
    }
    
    retval = SPI17Y_TransHandler(spi,req, async);
    
    if (!states[spi_num].started) {
        spi->ctrl0 |= MXC_F_SPI17Y_CTRL0_START;
        states[spi_num].started = 1;
    }
    
    // Deassert slave select at the end of the transaction
    if (req->deass) {
        spi->ctrl0 &= ~MXC_F_SPI17Y_CTRL0_SS_CTRL;
    }
    
    return retval;
}

/* ************************************************************************** */
int SPI17Y_SlaveTransHandler(mxc_spi17y_regs_t *spi, spi17y_req_t *req, uint8_t async)
{
    return SPI17Y_TransHandler(spi,req, async);
}

/* ************************************************************************** */
// Returns non-zero if transactions is complete, or 0 if not.
int SPI17Y_TransHandler(mxc_spi17y_regs_t *spi, spi17y_req_t *req, uint8_t async)
{

    unsigned tx_avail, rx_avail;
    int remain, spi_num;
    uint32_t int_en =0;
    uint32_t length =0;
    spi_num = MXC_SPI17Y_GET_IDX(spi);
    
    // Read/write 2x number of bytes if larger character size
    if (req->bits > 8) {
        length = req->len*2;
    } else {
        length = req->len;
    }
    
    if (req->tx_data != NULL) {
        // Need to know when all bytes are transmitted, so the callback can be triggered.
        int_en |= MXC_F_SPI17Y_INT_EN_TX_EMPTY;
    
        // Calculate how many bytes we can write to the FIFO
        tx_avail = MXC_SPI17Y_FIFO_DEPTH - ((spi->dma & MXC_F_SPI17Y_DMA_TX_FIFO_CNT) >>
                                            MXC_F_SPI17Y_DMA_TX_FIFO_CNT_POS);
        if ((length - req->tx_num) < tx_avail) {
            tx_avail = (length - req->tx_num);
        }
        if (req->bits > 8) {
            tx_avail &= ~(unsigned)0x1;
        }
        // Write the FIFO
        while (tx_avail) {
            if (tx_avail > 3) {
                memcpy((void*)&spi->data32,&((uint8_t*)req->tx_data)[req->tx_num], 4);
                
                tx_avail -= 4;
                req->tx_num += 4;
                
            } else if (tx_avail > 1) {
                memcpy((void*)&spi->data16[0],&((uint8_t*)req->tx_data)[req->tx_num], 2);
                
                tx_avail -= 2;
                req->tx_num += 2;
                
            } else if (req->bits<=8) {
                spi->data8[0] = ((uint8_t*)req->tx_data)[req->tx_num++];
                
                tx_avail -= 1;
            }
        }
    }
    
    remain = length - req->tx_num;
    
    // Set the TX interrupts
    if (remain) {
        if (remain > MXC_SPI17Y_FIFO_DEPTH) {
            // Set the TX FIFO almost empty interrupt if we have to refill
            spi->dma = ((spi->dma & ~MXC_F_SPI17Y_DMA_TX_FIFO_LEVEL) |
                        ((MXC_SPI17Y_FIFO_DEPTH) << MXC_F_SPI17Y_DMA_TX_FIFO_LEVEL_POS));
        } else {
        
            spi->dma = ((spi->dma & ~MXC_F_SPI17Y_DMA_TX_FIFO_LEVEL) |
                        ((remain) << MXC_F_SPI17Y_DMA_TX_FIFO_LEVEL_POS));
        }
        int_en |= MXC_F_SPI17Y_INT_EN_TX_THRESH;
        
    }
    // Break out if we've transmitted all the bytes and not receiving
    if ((req->rx_data == NULL) && (req->tx_num == length) && ((spi->dma & MXC_F_SPI17Y_DMA_TX_FIFO_CNT) == 0)) {
        spi->int_en = 0;
        int_en = 0;
        mxc_free_lock((uint32_t*)&states[spi_num].req);
        // Callback if not NULL
        if (req->callback != NULL) {
            req->callback(req, E_NO_ERROR);
        }
        return 1;
    }
    
    
    // Read the RX FIFO
    if (req->rx_data != NULL) {
    
        // Wait for there to be data in the RX FIFO
        rx_avail = (spi->dma & MXC_F_SPI17Y_DMA_RX_FIFO_CNT) >> MXC_F_SPI17Y_DMA_RX_FIFO_CNT_POS;
        if ((length - req->rx_num) < rx_avail) {
            rx_avail = (length - req->rx_num);
        }
        if (req->bits <= 8 || rx_avail >= 2) {
            // Read from the FIFO
            while (rx_avail) {
                if (rx_avail > 3) {
                    memcpy(&((uint8_t*)req->rx_data)[req->rx_num], (void*)&spi->data32, 4);
                    rx_avail -= 4;
                    req->rx_num += 4;
                    
                } else if (rx_avail > 1) {
                    memcpy(&((uint8_t*)req->rx_data)[req->rx_num], (void*)&spi->data16[0], 2);
                    rx_avail -= 2;
                    req->rx_num += 2;
                    
                } else {
                    ((uint8_t*)req->rx_data)[req->rx_num++] = spi->data8[0];
                    rx_avail -= 1;
                }
                // Don't read less than 2 bytes if we are using greater than 8 bit characters
                if (rx_avail == 1 && req->bits > 8) {
                    break;
                }
            }
        }
        remain = length - req->rx_num;
        if (remain) {
            if (remain > MXC_SPI17Y_FIFO_DEPTH) {
                spi->dma = ((spi->dma & ~MXC_F_SPI17Y_DMA_RX_FIFO_LEVEL) |
                            ((2) << MXC_F_SPI17Y_DMA_RX_FIFO_LEVEL_POS));
            } else {
                spi->dma = ((spi->dma & ~MXC_F_SPI17Y_DMA_RX_FIFO_LEVEL) |
                            ((remain-1) << MXC_F_SPI17Y_DMA_RX_FIFO_LEVEL_POS));
            }
            int_en |= MXC_F_SPI17Y_INT_EN_RX_THRESH;
        }
        
        // Break out if we've received all the bytes and we're not transmitting
        if ((req->tx_data == NULL) && (req->rx_num == length)) {
            spi->int_en = 0;
            int_en = 0;
            mxc_free_lock((uint32_t*)&states[spi_num].req);
            // Callback if not NULL
            if (req->callback != NULL) {
                req->callback(req, E_NO_ERROR);
            }
            return 1;
        }
    }
    
    // Break out once we've transmitted and received all of the data
    if ((req->rx_num == length) && (req->tx_num == length) && ((spi->dma & MXC_F_SPI17Y_DMA_TX_FIFO_CNT) == 0)) {
        spi->int_en = 0;
        int_en = 0;
        mxc_free_lock((uint32_t*)&states[spi_num].req);
        // Callback if not NULL
        if (req->callback != NULL) {
            req->callback(req, E_NO_ERROR);
        }
        return 1;
    }
    if(async){
        spi->int_en = int_en;
    }
    return 0;
}

/* ************************************************************************* */
int SPI17Y_AbortAsync(spi17y_req_t *req)
{
    int spi_num;
    mxc_spi17y_regs_t *spi;
    
    // Check the input parameters
    if (req == NULL) {
        return E_BAD_PARAM;
    }
    
    // Find the request, set to NULL
    for (spi_num = 0; spi_num < MXC_SPI17Y_INSTANCES; spi_num++) {
        if (req == states[spi_num].req) {
        
            spi = MXC_SPI17Y_GET_SPI17Y(spi_num);
            
            // Disable interrupts, clear the flags
            spi->int_en = 0;
            spi->int_fl = spi->int_fl;
            
            // Reset the SPI17Y to cancel the on ongoing transaction
            spi->ctrl0 &= ~(MXC_F_SPI17Y_CTRL0_EN);
            spi->ctrl0 |= (MXC_F_SPI17Y_CTRL0_EN);
            
            // Unlock this SPI17Y
            mxc_free_lock((uint32_t*)&states[spi_num].req);
            
            // Callback if not NULL
            if (req->callback != NULL) {
                req->callback(req, E_ABORT);
            }
            
            return E_NO_ERROR;
        }
    }
    
    return E_BAD_PARAM;
}

// *****************************************************************************
void SPI17Y_Enable(mxc_spi17y_regs_t* spi)
{
    spi->ctrl0 |= (MXC_F_SPI17Y_CTRL0_EN);
}

// *****************************************************************************
void SPI17Y_Disable(mxc_spi17y_regs_t* spi)
{
    spi->ctrl0 &= ~(MXC_F_SPI17Y_CTRL0_EN);
}

// *****************************************************************************
void SPI17Y_Clear_fifo(mxc_spi17y_regs_t* spi)
{
    spi->dma |= MXC_F_SPI17Y_DMA_TX_FIFO_CLEAR | MXC_F_SPI17Y_DMA_RX_FIFO_CLEAR;
}
