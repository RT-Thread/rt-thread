 /**
 * @file       spimss.c
 * @brief      This file contains the function implementations for the
 *             Serial Peripheral Interface (SPIMSS) peripheral module.
 */

/* *****************************************************************************
 * Copyright (C) 2017 Maxim Integrated Products, Inc., All Rights Reserved.
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
 * $Date: 2019-05-06 14:44:04 -0500 (Mon, 06 May 2019) $
 * $Revision: 43157 $
 *
 **************************************************************************** */
 
/* **** Includes **** */
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "mxc_config.h"
#include "mxc_assert.h"
#include "mxc_sys.h"
#include "spimss.h"
#include "mxc_lock.h"

/**
 * @ingroup spimss
 * @{
 */

/* **** Definitions **** */

/* **** Globals **** */
typedef struct {
    spimss_req_t *req;
} spimss_req_state_t;

static spimss_req_state_t states[MXC_SPIMSS_INSTANCES];


/* **** Functions **** */
static int SPIMSS_TransSetup(mxc_spimss_regs_t *spi, spimss_req_t *req, int master);
static uint32_t SPIMSS_MasterTransHandler(mxc_spimss_regs_t *spi, spimss_req_t *req);
static uint32_t SPIMSS_TransHandler(mxc_spimss_regs_t *spi, spimss_req_t *req);
static uint32_t SPIMSS_SlaveTransHandler(mxc_spimss_regs_t *spi, spimss_req_t *req);

/* ************************************************************************** */
int SPIMSS_Init(mxc_spimss_regs_t *spi, unsigned mode, unsigned freq, const sys_cfg_spimss_t* sys_cfg)
{
    int spi_num, error;
    unsigned int spimss_clk;
    unsigned int pol, pha;  // Polarity and phase of the clock (SPI mode)

    spi_num = MXC_SPIMSS_GET_IDX(spi);

    MXC_ASSERT(spi_num >= 0);

    if (mode > 3) {
        return E_BAD_PARAM;
    }

    if ((error = SYS_SPIMSS_Init(spi, sys_cfg)) != E_NO_ERROR) {
        return error;
    }

    states[spi_num].req = NULL;
    spi->ctrl &=  ~(MXC_F_SPIMSS_CTRL_SPIEN);  // Keep the SPI Disabled (This is the SPI Start) 

    // Check if frequency is too high
    if (freq > PeripheralClock) {
        return E_BAD_PARAM;
    }

     // Set the bit rate
    spimss_clk = PeripheralClock;
    spi->brg = (spimss_clk / freq) >> 1;

    // Set the mode
    pol = mode >> 1;  // Get the polarity out of the mode input value
    pha = mode &  1;  // Get the phase out of the mode input value

    spi->ctrl = (spi->ctrl & ~(MXC_F_SPIMSS_CTRL_CLKPOL)) | (pol << MXC_F_SPIMSS_CTRL_CLKPOL_POS);  // polarity
					  
    spi->ctrl = (spi->ctrl & ~(MXC_F_SPIMSS_CTRL_PHASE))  | (pha << MXC_F_SPIMSS_CTRL_PHASE_POS);   // phase

    spi->status &= ~(MXC_F_SPIMSS_STATUS_IRQ);

    return E_NO_ERROR;
}
/* ************************************************************************* */
int SPIMSS_Shutdown(mxc_spimss_regs_t *spi)
{
    int spi_num, err;
    spimss_req_t *temp_req;

    // Disable and turn off the SPI transaction.
    spi->ctrl = 0;    // Interrupts, SPI transaction all turned off
    spi->status = 0;
    spi->mod  = 0;

    // Reset FIFO counters
    spi->dma &= ~(MXC_F_SPIMSS_DMA_RX_FIFO_CNT|MXC_F_SPIMSS_DMA_TX_FIFO_CNT);

    // Call all of the pending callbacks for this SPI
    spi_num = MXC_SPIMSS_GET_IDX(spi);
    if (states[spi_num].req != NULL) {

        // Save the request
        temp_req = states[spi_num].req;

        // Unlock this SPI
        mxc_free_lock((uint32_t*)&states[spi_num].req);

        // Callback if not NULL
        if (temp_req->callback != NULL) {
            temp_req->callback(temp_req, E_SHUTDOWN);
        }
    }

    spi->status = 0;

    // Clear system level configurations
    if ((err = SYS_SPIMSS_Shutdown(spi)) != E_NO_ERROR) {
        return err;
    }

    return E_NO_ERROR;
}

/* ************************************************************************** */
int SPIMSS_TransSetup(mxc_spimss_regs_t *spi, spimss_req_t *req, int master)
{
    int spi_num;

    spi->ctrl &= ~(MXC_F_SPIMSS_CTRL_SPIEN);  // Make sure the Initiation 
	                                          // of SPI Start is disabled.

    spi->mod |= MXC_F_SPIMSS_MOD_TX_LJ;       // Making sure data is left 
	                                          // justified.

    if ((req->tx_data == NULL) && (req->rx_data == NULL)) {
        return -1;
    }

    spi_num = MXC_SPIMSS_GET_IDX(spi);
    MXC_ASSERT(spi_num >= 0);

    if (req->len == 0) {
        return 0;
    }

    req->tx_num = 0;
    req->rx_num = 0;

    if (mxc_get_lock((uint32_t*)&states[spi_num].req, (uint32_t)req) != E_NO_ERROR) {
        return E_BUSY;
    }

    if (master) { // Enable master mode
        spi->ctrl |= MXC_F_SPIMSS_CTRL_MMEN;     // SPI configured as master.
        spi->mod |= MXC_F_SPIMSS_CTRL_MMEN;       // SSEL pin is an output.		
    } else { // Enable slave mode
        spi->ctrl &= ~(MXC_F_SPIMSS_CTRL_MMEN);  // SPI configured as slave.
        spi->mod &= ~(MXC_F_SPIMSS_CTRL_MMEN);    // SSEL pin is an input.		
    }

    // Setup the character size

    if (req->bits <16) {
        MXC_SETFIELD(spi->mod, MXC_F_SPIMSS_MOD_NUMBITS , req->bits <<  MXC_F_SPIMSS_MOD_NUMBITS_POS);
		
    } else {
        MXC_SETFIELD(spi->mod, MXC_F_SPIMSS_MOD_NUMBITS , 0 <<  MXC_F_SPIMSS_MOD_NUMBITS_POS);
		
    }

    // Setup the slave select
    spi->mod |= MXC_F_SPIMSS_MOD_SSV; // Assert a high on Slave Select,
                                      // to get the line ready for active low later

    // Clear the TX and RX FIFO
    spi->dma |= (MXC_F_SPIMSS_DMA_TX_FIFO_CLEAR | MXC_F_SPIMSS_DMA_RX_FIFO_CLEAR);

    return E_NO_ERROR;
}

/* ************************************************************************** */
void SPIMSS_Handler(mxc_spimss_regs_t *spi)  // From the IRQ
{
    int spi_num;
    uint32_t flags;
    unsigned int int_enable;

    flags = spi->status;
    spi->status = flags;
    spi->status|= 0x80;    // clear interrupt

    spi_num = MXC_SPIMSS_GET_IDX(spi);

    int_enable = 0;
    if (states[spi_num].req != NULL) {
        if ((spi->ctrl  & MXC_F_SPIMSS_CTRL_MMEN) >> MXC_F_SPIMSS_CTRL_MMEN_POS) {
            int_enable = SPIMSS_MasterTransHandler(spi, states[spi_num].req);
			
        } else {
            int_enable = SPIMSS_SlaveTransHandler(spi, states[spi_num].req);			
        }
    }

    if (int_enable==1) {
        spi->ctrl |= (MXC_F_SPIMSS_CTRL_IRQE );
		
    }
}

/* ************************************************************************** */
int SPIMSS_MasterTrans(mxc_spimss_regs_t *spi, spimss_req_t *req)
{
    int error;

    if ((error = SPIMSS_TransSetup(spi, req, 1)) != E_NO_ERROR) {
        return error;
    }
	
    req->callback = NULL;

    spi->mod &= ~(MXC_F_SPIMSS_MOD_SSV);  // This will assert the Slave Select.
    spi->ctrl |= MXC_F_SPIMSS_CTRL_SPIEN;  // Enable/Start SPI
    
    while (SPIMSS_MasterTransHandler(spi,req)!=0) {
    }

    spi->mod |= MXC_F_SPIMSS_MOD_SSV;

    spi->ctrl &= ~(MXC_F_SPIMSS_CTRL_SPIEN); // Last of the SPIMSS value has been transmitted...
                                             // stop the transmission...
    return E_NO_ERROR;
}


/* ************************************************************************** */
int SPIMSS_SlaveTrans(mxc_spimss_regs_t *spi, spimss_req_t *req)
{
    int error;
 
    if ((error = SPIMSS_TransSetup(spi, req,0)) != E_NO_ERROR) {
        return error;
    }

    while (SPIMSS_SlaveTransHandler(spi,req)!=0) {
        spi->ctrl |= MXC_F_SPIMSS_CTRL_SPIEN;  // Enable/Start SPI
        while ((spi->status & MXC_F_SPIMSS_STATUS_TXST) == MXC_F_SPIMSS_STATUS_TXST) {}		
     }

    spi->ctrl &= ~(MXC_F_SPIMSS_CTRL_SPIEN);  // Last of the SPIMSS value has been transmitted...
                                              // stop the transmission...
    return E_NO_ERROR;
}

/* ************************************************************************** */
int SPIMSS_MasterTransAsync(mxc_spimss_regs_t *spi, spimss_req_t *req)
{
    int error;
    uint8_t int_enable;
    if ((error = SPIMSS_TransSetup(spi, req, 1) )!= E_NO_ERROR) {
        return error;		
    }

    int_enable = SPIMSS_MasterTransHandler(spi,req);

    spi->mod ^= MXC_F_SPIMSS_MOD_SSV;      // This will assert the Slave Select.

    spi->ctrl |= MXC_F_SPIMSS_CTRL_SPIEN;  // Enable/Start SPI

    if (int_enable==1) {
        spi->ctrl |= (MXC_F_SPIMSS_CTRL_IRQE | MXC_F_SPIMSS_CTRL_STR);
    }

    return E_NO_ERROR;
}

/* ************************************************************************** */
int SPIMSS_SlaveTransAsync(mxc_spimss_regs_t *spi, spimss_req_t *req)
{
    int error;
    uint8_t int_enable;
    if ((error = SPIMSS_TransSetup(spi, req, 0)) != E_NO_ERROR) {
        return error;
    }

    int_enable = SPIMSS_SlaveTransHandler(spi,req);

    spi->ctrl |= MXC_F_SPIMSS_CTRL_SPIEN;  // Enable/Start SPI

    if (int_enable==1) {                   // Trigger a SPI Interrupt
        spi->ctrl |= (MXC_F_SPIMSS_CTRL_IRQE );
    }

    return E_NO_ERROR;
}

/* ************************************************************************** */
uint32_t SPIMSS_MasterTransHandler(mxc_spimss_regs_t *spi, spimss_req_t *req)
{
    unsigned start_set = 0;
    uint32_t retval;

    if (!start_set) {
    start_set = 1;
    retval = SPIMSS_TransHandler(spi,req);
    }

    return retval;
}

/* ************************************************************************** */
uint32_t SPIMSS_SlaveTransHandler(mxc_spimss_regs_t *spi, spimss_req_t *req)
{
    return SPIMSS_TransHandler(spi,req);
}

/* ************************************************************************** */
uint32_t SPIMSS_TransHandler(mxc_spimss_regs_t *spi, spimss_req_t *req)
{
    unsigned tx_avail, rx_avail;
    int remain, spi_num;
    uint32_t int_en =0;
    uint32_t length =req->len;


    spi_num = MXC_SPIMSS_GET_IDX(spi);

    // Read the RX FIFO
   if (req->rx_data != NULL) {
        // Wait for there to be data in the RX FIFO
        rx_avail = ((spi->dma & MXC_F_SPIMSS_DMA_RX_FIFO_CNT) >> MXC_F_SPIMSS_DMA_RX_FIFO_CNT_POS);
        if ((length - req->rx_num) < rx_avail) {
            rx_avail = (length - req->rx_num);
        }

       // Read from the FIFO
        while (rx_avail) {

            // Don't read less than 2 bytes if we are using greater than 8 bit characters
            if (req->bits>8) {
                ((uint16_t*)req->rx_data)[req->rx_num++] = spi->data16;
                rx_avail -= 1;

            } else {
                ((uint8_t*)req->rx_data)[req->rx_num++] = spi->data8[0];
                rx_avail -= 1;
            }
            rx_avail = ((spi->dma & MXC_F_SPIMSS_DMA_RX_FIFO_CNT) >> MXC_F_SPIMSS_DMA_RX_FIFO_CNT_POS);
            if ((length - req->rx_num) < rx_avail) {
                rx_avail = (length - req->rx_num);
            }
        }
        
        remain = length - req->rx_num;

        if (remain) {
            if (remain > MXC_SPIMSS_FIFO_DEPTH) {
                spi->dma = ((spi->dma & ~MXC_F_SPIMSS_DMA_RX_FIFO_CNT) | ((2) << MXC_F_SPIMSS_DMA_RX_FIFO_CNT_POS));
            } else {
                spi->dma = ((spi->dma & ~MXC_F_SPIMSS_DMA_RX_FIFO_CNT) | ((remain-1) << MXC_F_SPIMSS_DMA_RX_FIFO_CNT_POS));
            }
            
            int_en = 1;
        }

        // Break out if we've received all the bytes and we're not transmitting
        if ((req->tx_data == NULL) && (req->rx_num == length)) {
            spi->ctrl &= ~(MXC_F_SPIMSS_CTRL_IRQE | MXC_F_SPIMSS_CTRL_STR);
            int_en = 0;
            mxc_free_lock((uint32_t*)&states[spi_num].req);
            // Callback if not NULL
            if (req->callback != NULL) {
                req->callback(req, E_NO_ERROR);
            }
        }
    }
    // Note:- spi->dma shows the FIFO TX count and FIFO RX count in
    // Words, while the calculation below is in bytes.
    if (req->tx_data != NULL) {

        if (req->tx_num < length) {

            // Calculate how many bytes we can write to the FIFO (tx_avail holds that value)
            tx_avail = MXC_SPIMSS_FIFO_DEPTH - (((spi->dma & MXC_F_SPIMSS_DMA_TX_FIFO_CNT) >> MXC_F_SPIMSS_DMA_TX_FIFO_CNT_POS));  // in bytes

            if ((length - req->tx_num) < tx_avail) {
                tx_avail = (length - req->tx_num);   // This is for the last spin
            }
            if (req->bits > 8) {
                tx_avail &= ~(unsigned)0x1;
            }
            // Write the FIFO
            while (tx_avail) {
                if (req->bits >8) {
                        spi->data16 = ((uint16_t*)req->tx_data)[req->tx_num++];

                        tx_avail -= 1;
                } else {
                    spi->data8[0] = ((uint8_t*)req->tx_data)[req->tx_num++];
                    tx_avail -=1;
                }

            }
        }

        remain = length - req->tx_num;

        // If there are values remaining to be transmitted, this portion will get
        // executed and int_en set, to indicate that this must spin and come back again...
        if (remain) {
            if (remain > MXC_SPIMSS_FIFO_DEPTH) {  //  more tx rounds will happen... Transfer the maximum,
                spi->dma = ((spi->dma & ~MXC_F_SPIMSS_DMA_TX_FIFO_CNT) | ((MXC_SPIMSS_FIFO_DEPTH) << MXC_F_SPIMSS_DMA_TX_FIFO_CNT_POS));
            } else {  // only one more tx round will be done... Transfer whatever remains,
                spi->dma = ((spi->dma & ~MXC_F_SPIMSS_DMA_TX_FIFO_CNT) | ((remain) << MXC_F_SPIMSS_DMA_TX_FIFO_CNT_POS));
            }
            int_en = 1; // This will act as a trigger for the next round...
        }

        // Break out if we've transmitted all the bytes and not receiving
        if ((req->rx_data == NULL) && (req->tx_num == length)) {
            spi->ctrl &= ~(MXC_F_SPIMSS_CTRL_IRQE | MXC_F_SPIMSS_CTRL_STR);
            int_en = 0;
            mxc_free_lock((uint32_t*)&states[spi_num].req);
            // Callback if not NULL
            if (req->callback != NULL) {
                req->callback(req, E_NO_ERROR);
            }
        }
    }


    // Break out once we've transmitted and received all of the data
    if ((req->rx_num == length) && (req->tx_num == length)) {
        spi->ctrl &= ~(MXC_F_SPIMSS_CTRL_IRQE | MXC_F_SPIMSS_CTRL_STR);
        int_en = 0;
        mxc_free_lock((uint32_t*)&states[spi_num].req);
        // Callback if not NULL
        if (req->callback != NULL) {
            req->callback(req, E_NO_ERROR);
        }
    }

    return int_en;
}

/* ************************************************************************* */
int SPIMSS_AbortAsync(spimss_req_t *req)
{
    int spi_num;
    mxc_spimss_regs_t *spi;

    // Check the input parameters
    if (req == NULL) {
        return E_BAD_PARAM;
    }

    // Find the request, set to NULL
    for (spi_num = 0; spi_num < MXC_SPIMSS_INSTANCES; spi_num++) {
        if (req == states[spi_num].req) {

            spi = MXC_SPIMSS_GET_SPI(spi_num);

            // Disable interrupts, clear the flags
            spi->ctrl &= ~(MXC_F_SPIMSS_CTRL_IRQE | MXC_F_SPIMSS_CTRL_STR);

            // Disable and turn off the SPI transaction.
        	spi->ctrl &= ~(MXC_F_SPIMSS_CTRL_SPIEN);

            // Unlock this SPI
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
/**@} end of group spimss */
