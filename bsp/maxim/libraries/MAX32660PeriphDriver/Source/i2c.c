/* ****************************************************************************
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
 * $Date: 2020-02-03 10:33:50 -0600 (Mon, 03 Feb 2020) $
 * $Revision: 51326 $
 *
 *************************************************************************** */


#include <stddef.h>
#include <stdint.h>
#include "mxc_config.h"
#include "mxc_assert.h"
#include "mxc_lock.h"
#include "mxc_sys.h"
#include "i2c.h"
#include <stdio.h>
#include "mxc_delay.h"

/* **** Definitions **** */
#define I2C_ERROR   (MXC_F_I2C_INT_FL0_ARB_ER | MXC_F_I2C_INT_FL0_TO_ER | MXC_F_I2C_INT_FL0_ADDR_NACK_ER | \
                    MXC_F_I2C_INT_FL0_DATA_ER | MXC_F_I2C_INT_FL0_DO_NOT_RESP_ER | MXC_F_I2C_INT_FL0_START_ER | \
                    MXC_F_I2C_INT_FL0_STOP_ER)
#define MASTER 1
#define SLAVE 0

/* For high speed mode, if the I2C bus capacitance is greater than 100pF, set this value to ((capacitance - 100) / 3).
   Otherwise leave it at 0. */
#define HS_SCALE_FACTOR         (0)

#define T_LOW_MIN     (160 + (160 * HS_SCALE_FACTOR / 100))   /* tLOW minimum in nanoseconds */
#define T_HIGH_MIN    (60 + (60 * HS_SCALE_FACTOR / 100))     /* tHIGH minimum in nanoseconds */
#define T_R_MAX_HS    (40 + (40 * HS_SCALE_FACTOR / 100))     /* tR maximum for high speed mode in nanoseconds */
#define T_F_MAX_HS    (40 + (40 * HS_SCALE_FACTOR / 100))     /* tF maximum for high speed mode in nanoseconds */
#define T_AF_MIN      (10 + (10 * HS_SCALE_FACTOR / 100))     /* tAF minimun in nanoseconds */

/* **** Variable Declaration **** */

// Saves the state of the non-blocking requests
typedef struct {
    i2c_req_t *req;
    i2c_state_t state;
    uint8_t num_wr;    // keep track of number of bytes loaded in the fifo during slave transmit
} i2c_req_state_t;
static i2c_req_state_t states[MXC_I2C_INSTANCES];

/* **** Function Prototypes **** */
static void I2C_MasterHandler(mxc_i2c_regs_t *i2c);
static void I2C_SlaveHandler(mxc_i2c_regs_t *i2c);
static void I2C_FreeCallback(int i2c_num, int error);
static void I2C_Recover(mxc_i2c_regs_t *i2c);

/* ************************************************************************** */
static int I2C_Setspeed(mxc_i2c_regs_t * i2c, i2c_speed_t i2cspeed)
{
    uint32_t ticks, ticks_lo, ticks_hi;

    if (i2cspeed == I2C_HS_MODE) {

        uint32_t sys_freq, tPCLK, targBusFreq, tSCLmin, cklMin, ckhMin, ckh_cklMin;

        /* Compute dividers for high speed mode. */
        sys_freq = SYS_I2C_GetFreq(i2c);
        MXC_ASSERT(sys_freq >= 1000);

        tPCLK = 1000000 / (sys_freq / 1000);
        MXC_ASSERT(tPCLK > 0)

        targBusFreq = i2cspeed - ((i2cspeed/2) * HS_SCALE_FACTOR / 100);
        if(targBusFreq < 1000) {
            return E_BAD_PARAM;
        }

        tSCLmin = 1000000 / (targBusFreq / 1000);                                
        cklMin = ((T_LOW_MIN + T_F_MAX_HS + (tPCLK - 1) - T_AF_MIN) / tPCLK) - 1;
        ckhMin = ((T_HIGH_MIN + T_R_MAX_HS + (tPCLK - 1) - T_AF_MIN) / tPCLK) - 1;
        ckh_cklMin = ((tSCLmin + (tPCLK - 1)) / tPCLK) - 2;

        ticks_lo = (cklMin > (ckh_cklMin - ckhMin)) ? (cklMin) : (ckh_cklMin - ckhMin);
        ticks_hi = ckhMin;

        if((ticks_lo > (MXC_F_I2C_HS_CLK_HS_CLK_LO >> MXC_F_I2C_HS_CLK_HS_CLK_LO_POS)) ||
           (ticks_hi > (MXC_F_I2C_HS_CLK_HS_CLK_HI >> MXC_F_I2C_HS_CLK_HS_CLK_HI_POS))) {
            return E_BAD_PARAM;
        }

        /* Write results to destination registers. */
        i2c->hs_clk = (ticks_lo << MXC_F_I2C_HS_CLK_HS_CLK_LO_POS) | (ticks_hi <<
                      MXC_F_I2C_HS_CLK_HS_CLK_HI_POS);

        /* Still need to load dividers for the preamble that each high-speed transaction starts with.
           Switch setting to fast mode and fall out of if statement. */
        i2cspeed = I2C_FAST_MODE;
    }
    
    /* Get the number of periph clocks needed to achieve selected speed. */
    ticks = SYS_I2C_GetFreq(i2c) / i2cspeed;

    /* For a 50% duty cycle, half the ticks will be spent high and half will be low. */
    ticks_hi = (ticks >> 1) - 1;
    ticks_lo = (ticks >> 1) - 1;

    /* Account for rounding error in odd tick counts. */
    if (ticks & 1) {
        ticks_hi++;
    }

    /* Will results fit into 9 bit registers?  (ticks_hi will always be >= ticks_lo.  No need to check ticks_lo.) */
    if (ticks_hi > 0x1FF) {
        return E_BAD_PARAM;
    }

    /* 0 is an invalid value for the destination registers. (ticks_hi will always be >= ticks_lo.  No need to check ticks_hi.) */
    if (ticks_lo == 0) {
        return E_BAD_PARAM;
    }

    /* Write results to destination registers. */
    i2c->clk_lo = ticks_lo;
    i2c->clk_hi = ticks_hi;

    return E_NO_ERROR;
}

/* ************************************************************************** */
int I2C_Init(mxc_i2c_regs_t *i2c, i2c_speed_t i2cspeed, const sys_cfg_i2c_t* sys_cfg)
{
    int err;
    int idx = MXC_I2C_GET_IDX(i2c);
    // Check the base pointer
    MXC_ASSERT(idx >= 0);

    // Set system level configurations
    if ((err = SYS_I2C_Init(i2c, sys_cfg)) != E_NO_ERROR) {
        return err;
    }

    // Always disable the HW autoflush on data NACK and let the SW handle the flushing.
    i2c->tx_ctrl0 |= 0x20;

    states[idx].num_wr = 0;

    i2c->ctrl = 0;   // clear configuration bits
    i2c->ctrl = MXC_F_I2C_CTRL_I2C_EN;       // Enable I2C
    i2c->master_ctrl = 0;  // clear master configuration bits
    i2c->status = 0;   // clear status bits

    /* If either SDA or SCL is already low, there is a problem.
     * Try reclaiming the bus by sending clocks until we have control of the SDA line.
     * Follow procedure defined in i2c spec.
     */
    if ((i2c->ctrl & (MXC_F_I2C_CTRL_SCL | MXC_F_I2C_CTRL_SDA)) !=
            (MXC_F_I2C_CTRL_SCL | MXC_F_I2C_CTRL_SDA)) {

        int i, have_control;

        // Set SCL/SDA as software controlled.
        i2c->ctrl |= MXC_F_I2C_CTRL_SW_OUT_EN;

        // Try to get control of SDA.
        for (i = 0; i < 16; i++) {
            have_control = 1;

            // Drive SCL low and check its state.
            i2c->ctrl &= ~(MXC_F_I2C_CTRL_SCL_OUT);
            mxc_delay(MXC_DELAY_USEC(5));
            if ((i2c->ctrl & MXC_F_I2C_CTRL_SCL) == MXC_F_I2C_CTRL_SCL) {
                have_control = 0;
            }

            // Drive SDA low and check its state.
            i2c->ctrl &= ~(MXC_F_I2C_CTRL_SDA_OUT);
            mxc_delay(MXC_DELAY_USEC(5));
            if ((i2c->ctrl & MXC_F_I2C_CTRL_SDA) == MXC_F_I2C_CTRL_SDA) {
                have_control = 0;
            }

            // Release SDA and check its state.
            i2c->ctrl |= (MXC_F_I2C_CTRL_SDA_OUT);
            mxc_delay(MXC_DELAY_USEC(5));
            if ((i2c->ctrl & MXC_F_I2C_CTRL_SDA) != MXC_F_I2C_CTRL_SDA) {
                have_control = 0;
            }

            // Release SCL and check its state.
            i2c->ctrl |= (MXC_F_I2C_CTRL_SCL_OUT);
            mxc_delay(MXC_DELAY_USEC(5));
            if ((i2c->ctrl & MXC_F_I2C_CTRL_SCL) != MXC_F_I2C_CTRL_SCL) {
                have_control = 0;
            }

            if (have_control) {
                // Issue stop
                // Drive SDA low.
                i2c->ctrl &= ~(MXC_F_I2C_CTRL_SDA_OUT);
                mxc_delay(MXC_DELAY_USEC(5));
                // Release SDA.
                i2c->ctrl |= (MXC_F_I2C_CTRL_SDA_OUT);
                mxc_delay(MXC_DELAY_USEC(5));
                break;
            }
        }

        if (!have_control) {
            return E_COMM_ERR;
        }
    }

    i2c->ctrl = 0;   // clear configuration bits
    i2c->ctrl = MXC_F_I2C_CTRL_I2C_EN;       // Enable I2C
    i2c->master_ctrl = 0;  // clear master configuration bits
    i2c->status= 0;   // clear status bits

    // Check for HS mode
    if (i2cspeed == I2C_HS_MODE) {
        i2c->ctrl |= MXC_F_I2C_CTRL_HS_MODE;    // Enable HS mode
    }

    // Disable and clear interrupts
    i2c->int_en0 = 0;
    i2c->int_en1 = 0;
    i2c->int_fl0 = i2c->int_fl0;
    i2c->int_fl1 = i2c->int_fl1;

    i2c->timeout = 0x0;   // set timeout
    i2c->rx_ctrl0 |= MXC_F_I2C_RX_CTRL0_RX_FLUSH; // clear the RX FIFO
    i2c->tx_ctrl0 |= MXC_F_I2C_TX_CTRL0_TX_FLUSH; // clear the TX FIFO

    return I2C_Setspeed(i2c, i2cspeed);
}
/* ************************************************************************** */
int I2C_Shutdown(mxc_i2c_regs_t *i2c)
{
    int i2c_num, err;

    // Check the base pointer
    i2c_num = MXC_I2C_GET_IDX(i2c);
    MXC_ASSERT(i2c_num >= 0);

    // Disable and clear interrupts
    i2c->int_en0 = 0;
    i2c->int_en1 = 0;
    i2c->int_fl0 = i2c->int_fl0;
    i2c->int_fl1 = i2c->int_fl1;

    i2c->rx_ctrl0 |= MXC_F_I2C_RX_CTRL0_RX_FLUSH; // clear the RX FIFO
    i2c->tx_ctrl0 |= MXC_F_I2C_TX_CTRL0_TX_FLUSH; // clear the TX FIFO

    // Call all of the pending callbacks for this I2C
    if (states[i2c_num].req != NULL) {
        I2C_Recover(i2c);
        I2C_FreeCallback(i2c_num, E_SHUTDOWN);
    }

    i2c->ctrl = 0;
    
    // Clears system level configurations
    if ((err = SYS_I2C_Shutdown(i2c)) != E_NO_ERROR) {
        return err;
    }

    return E_NO_ERROR;
}

/* ************************************************************************** */
int I2C_MasterWrite(mxc_i2c_regs_t *i2c, uint8_t addr, const uint8_t* data, int len, int restart)
{
    int save_len = len;

    if (len == 0) {
        return E_NO_ERROR;
    }

    // Clear the lock out bit (W1C) in case it is set.
    i2c->int_fl0 = MXC_F_I2C_INT_FL0_TX_LOCK_OUT;
    i2c->int_fl0 = i2c->int_fl0;

    // Enable master mode
    i2c->ctrl |= MXC_F_I2C_CTRL_MST;

    // Load FIFO with slave address for WRITE and as much data as we can
    while (i2c->status & MXC_F_I2C_STATUS_TX_FULL) {}
    i2c->fifo = addr & ~(0x1);

    while ((len > 0) && !(i2c->status & MXC_F_I2C_STATUS_TX_FULL)) {
        i2c->fifo = *data++;
        len--;
    }

    i2c->master_ctrl |= MXC_F_I2C_MASTER_CTRL_START;

    // Write remaining data to FIFO
    while (len > 0) {

        // Check for errors
        if (i2c->int_fl0 & I2C_ERROR) {
            // Set the stop bit
            i2c->master_ctrl &= ~(MXC_F_I2C_MASTER_CTRL_RESTART);
            i2c->master_ctrl |= MXC_F_I2C_MASTER_CTRL_STOP;
             while (!(i2c->int_fl0 & (MXC_F_I2C_INT_FL0_STOP))) {}    

            return E_COMM_ERR;
        }

        if (!(i2c->status & MXC_F_I2C_STATUS_TX_FULL)) {
            i2c->fifo = *data++;
            len--;
        }
    }

    if (restart)  {
        i2c->master_ctrl |= MXC_F_I2C_MASTER_CTRL_RESTART;
    } else {
        i2c->master_ctrl |= MXC_F_I2C_MASTER_CTRL_STOP;
    }

    // Wait for Done or time out if enabled
    while (!(i2c->int_fl0 & (MXC_F_I2C_INT_FL0_DONE | I2C_ERROR ))) {}    

    i2c->int_fl0 = MXC_F_I2C_INT_FL0_DONE;

    // Wait for Stop
    if (!restart) {
        while (!(i2c->int_fl0 & (MXC_F_I2C_INT_FL0_STOP ))) {}
        
        i2c->int_fl0 = MXC_F_I2C_INT_FL0_STOP;
    }

    // Check for errors
    if (i2c->int_fl0 & I2C_ERROR) {
        return E_COMM_ERR;
    }

    return save_len;
}

/* ************************************************************************** */
int I2C_MasterRead(mxc_i2c_regs_t *i2c, uint8_t addr, uint8_t* data, int len, int restart)
{
    int save_len = len;

    if (len == 0) {
        return E_NO_ERROR;
    }

    if (len > 256) {
        return E_BAD_PARAM;
    }

    i2c->int_fl0 = MXC_F_I2C_INT_FL0_TX_LOCK_OUT;
    i2c->int_fl0 = i2c->int_fl0;

    // Make sure the I2C has been initialized
    if (!(i2c->ctrl & MXC_F_I2C_CTRL_I2C_EN)) {
        return E_UNINITIALIZED;
    }

    // Enable master mode
    i2c->ctrl |= MXC_F_I2C_CTRL_MST;

    // Set receive count
    i2c->rx_ctrl1= len;

    i2c->master_ctrl |= MXC_F_I2C_MASTER_CTRL_START;

    // Load FIFO with slave address
    while (i2c->status & MXC_F_I2C_STATUS_TX_FULL) {}
    i2c->fifo = (addr | 1);


    // Wait for all data to be received or error
    while (len > 0) {

        // Check for errors
        if (i2c->int_fl0 & I2C_ERROR) {
            // Set the stop bit
            i2c->master_ctrl |= MXC_F_I2C_MASTER_CTRL_STOP;
            return E_COMM_ERR;
        }

        if (!(i2c->status & MXC_F_I2C_STATUS_RX_EMPTY)) {
            *data++ = i2c->fifo;
            len--;
        }
    }

    if (i2c->int_fl0 & I2C_ERROR) {
        // Set the stop bit
        i2c->master_ctrl |= MXC_F_I2C_MASTER_CTRL_STOP;
        return E_COMM_ERR;
    }

    if (restart)  {
        i2c->master_ctrl |= MXC_F_I2C_MASTER_CTRL_RESTART;
    } else {
        i2c->master_ctrl |= MXC_F_I2C_MASTER_CTRL_STOP;
    }

    // Wait for Done or time out if enabled
    while (!(i2c->int_fl0 & (MXC_F_I2C_INT_FL0_DONE | I2C_ERROR ))) {}    
  
    i2c->int_fl0 = MXC_F_I2C_INT_FL0_DONE;

    // Wait for Stop
    if (!restart) {
        while (!(i2c->int_fl0 & (MXC_F_I2C_INT_FL0_STOP | I2C_ERROR))) {
            
        }
        
        i2c->int_fl0 = MXC_F_I2C_INT_FL0_STOP;
    }

    // Check for errors
    if (i2c->int_fl0 & I2C_ERROR) {
        return E_COMM_ERR;
    }

    return save_len;
}

/* ************************************************************************** */
int I2C_Slave(mxc_i2c_regs_t *i2c, uint8_t addr, const uint8_t* read_data, int read_len,
              uint8_t* write_data, int write_len, int* tx_num, int* rx_num,
              i2c_autoflush_disable_t sw_autoflush_disable)
{
    int i2c_num;

    i2c_num = MXC_I2C_GET_IDX(i2c);
    if ((read_data == NULL) && (write_data == NULL)) {
        return E_NULL_PTR;
    }

    // Make sure the I2C has been initialized
    if (!(i2c->ctrl & MXC_F_I2C_CTRL_I2C_EN)) {
        return E_UNINITIALIZED;
    }

    if ((read_len == 0) && (write_len == 0)) {
        return E_NO_ERROR;
    }

    if (mxc_get_lock((uint32_t*)&states[i2c_num].req, 1) != E_NO_ERROR) {
        return E_BUSY;
    }
    // Disable master mode
    i2c->ctrl &= ~MXC_F_I2C_CTRL_MST;

    // Clear any previous errors
    i2c->int_fl0 = i2c->int_fl0;
    i2c->int_fl1 = i2c->int_fl1;

    // Set the slave address
    i2c->slave_addr = (addr >> 1);

    // Wait for address match
    while (!(i2c->int_fl0 & MXC_F_I2C_INT_FL0_ADDR_MATCH) && !(i2c->int_fl0 & I2C_ERROR)) {
                
    }
    
    i2c->int_fl0 = MXC_F_I2C_INT_FL0_ADDR_MATCH;
    i2c->int_fl0 = MXC_F_I2C_INT_FL0_TX_LOCK_OUT;

    if (i2c->int_fl0 & I2C_ERROR) {
        if (!sw_autoflush_disable) {
            i2c->tx_ctrl0 |= MXC_F_I2C_TX_CTRL0_TX_FLUSH;
            i2c->rx_ctrl0 |= MXC_F_I2C_RX_CTRL0_RX_FLUSH;
        }
        mxc_free_lock((uint32_t*)&states[i2c_num]);
        return E_COMM_ERR;
    }

    // See if we're reading or writing
    if (i2c->ctrl & MXC_F_I2C_CTRL_READ) {
        // This is the master read/slave write case
        if (read_data == NULL || read_len == 0) {
            mxc_free_lock((uint32_t*)&states[i2c_num]);
            return E_NULL_PTR;
        }

        // Wait for all data to be received or error
        while (read_len > 0) {

            // Check for errors
            if (i2c->int_fl0 & I2C_ERROR) {
                *tx_num = states[i2c_num].num_wr - ((i2c->tx_ctrl1 & MXC_F_I2C_TX_CTRL1_TX_FIFO) >> MXC_F_I2C_TX_CTRL1_TX_FIFO_POS);
                states[i2c_num].num_wr = 0;
                if (!sw_autoflush_disable) {
                    i2c->tx_ctrl0 |= MXC_F_I2C_TX_CTRL0_TX_FLUSH;
                }
                mxc_free_lock((uint32_t*)&states[i2c_num]);
                return E_COMM_ERR;
            }

            // Check for nack from master
            if (i2c->int_fl0 & MXC_F_I2C_INT_FL0_TX_LOCK_OUT) {
                break;
            }

            // Check for done bit
            if (i2c->int_fl0 & MXC_F_I2C_INT_FL0_DONE) {
                break;
            }

            if (!(i2c->status & MXC_F_I2C_STATUS_TX_FULL)) {
                i2c->fifo = *read_data++;
                states[i2c_num].num_wr++;
                read_len--;
            }
        }

        // Wait for Done
        while (!(i2c->int_fl0 & MXC_F_I2C_INT_FL0_DONE)) {}

        // Calculate number of bytes sent by the slave
        *tx_num = states[i2c_num].num_wr - ((i2c->tx_ctrl1 & MXC_F_I2C_TX_CTRL1_TX_FIFO) >> MXC_F_I2C_TX_CTRL1_TX_FIFO_POS);
        states[i2c_num].num_wr = 0;
        if (!sw_autoflush_disable) {
            // Flush the TX FIFO
            i2c->tx_ctrl0 |= MXC_F_I2C_TX_CTRL0_TX_FLUSH;
        }

    } else {
        // This is the master write/slave read case
        if (write_data == NULL || write_len == 0) {
            mxc_free_lock((uint32_t*)&states[i2c_num]);
            return E_NULL_PTR;
        }

        // Wait for all data to be written or error
        while (write_len > 0) {

            // Check for errors
            if (i2c->int_fl0 & I2C_ERROR) {
                if (!sw_autoflush_disable) {
                    i2c->rx_ctrl0 |= MXC_F_I2C_RX_CTRL0_RX_FLUSH;
                }
                mxc_free_lock((uint32_t*)&states[i2c_num]);
                return E_COMM_ERR;
            }

            // Check for done bit
            if (i2c->int_fl0 & MXC_F_I2C_INT_FL0_DONE) {
                break;
            }

            if (!(i2c->status & MXC_F_I2C_STATUS_RX_EMPTY)) {
                *write_data++ = i2c->fifo;
                (*rx_num)++;
                write_len--;
            }
        }

        // Wait for Done
        while (!(i2c->int_fl0 & MXC_F_I2C_INT_FL0_DONE)) {
            
        }
        // Flush the FIFO
        if (!sw_autoflush_disable) {
            i2c->rx_ctrl0 |= MXC_F_I2C_RX_CTRL0_RX_FLUSH;
        }
    }

    // Check for errors
    if (i2c->int_fl0 & I2C_ERROR) {
        // Flush the FIFO
        if (!sw_autoflush_disable) {
            i2c->tx_ctrl0 |= MXC_F_I2C_TX_CTRL0_TX_FLUSH;
            i2c->rx_ctrl0 |= MXC_F_I2C_RX_CTRL0_RX_FLUSH;
        }
        mxc_free_lock((uint32_t*)&states[i2c_num]);
        return E_COMM_ERR;
    }
    mxc_free_lock((uint32_t*)&states[i2c_num]);
    return E_NO_ERROR;
}

/* ************************************************************************** */
int I2C_MasterAsync(mxc_i2c_regs_t *i2c, i2c_req_t *req)
{
    int i2c_num;

    i2c_num = MXC_I2C_GET_IDX(i2c);
    if (req->state == I2C_STATE_READING) {
        // Check the parameters
        if (req->rx_len == 0) {
            return E_NO_ERROR;
        }
        if (req->rx_data == NULL) {
            return E_NULL_PTR;
        }

    } else {
        // Check the parameters
        if (req->tx_len == 0) {
            return E_NO_ERROR;
        }
        if (req->tx_data == NULL) {
            return E_NULL_PTR;
        }
    }

    // Make sure the I2C has been initialized
    if (!(i2c->ctrl & MXC_F_I2C_CTRL_I2C_EN)) {
        return E_UNINITIALIZED;
    }

    // Attempt to register this request
    if (mxc_get_lock((uint32_t*)&states[i2c_num].req, (uint32_t)req) != E_NO_ERROR) {
        return E_BUSY;
    }
    states[i2c_num].state = req->state;
    states[i2c_num].req = req;

    // Enable master mode
    i2c->ctrl |= MXC_F_I2C_CTRL_MST;

    // Clear the byte counters
    req->tx_num = 0;
    req->rx_num = 0;

    // Disable and clear the interrupts
    i2c->int_en0 = 0;
    i2c->int_en1 = 0;
    i2c->int_fl0 = i2c->int_fl0;
    i2c->int_fl1 = i2c->int_fl1;

    // Start the transaction
    I2C_MasterHandler(i2c);
    return E_NO_ERROR;
}


/* ************************************************************************** */
static void I2C_MasterHandler(mxc_i2c_regs_t *i2c)
{

    uint32_t int0, inten0 = 0;
    int rx_remain, tx_remain, i2c_num;
    i2c_req_t *req;

    i2c_num = MXC_I2C_GET_IDX(i2c);
    req = states[i2c_num].req;

    // Check for errors
    int0 = i2c->int_fl0;
    if (int0 & I2C_ERROR) {

        // Set the done bit
        i2c->master_ctrl &= ~(MXC_F_I2C_MASTER_CTRL_RESTART);
        i2c->master_ctrl |= MXC_F_I2C_MASTER_CTRL_STOP;

        i2c->int_en0 = 0;
        if (req->callback != NULL) {
            I2C_Recover(i2c);
            I2C_FreeCallback(i2c_num, E_COMM_ERR);
        }
        return;
    }

    rx_remain = req->rx_len - req->rx_num;
    tx_remain = req->tx_len - req->tx_num;
    if (req->restart) {
        //  Check for DONE interrupt
        if ((int0 & MXC_F_I2C_INT_FL0_DONE)) {
            // Read out any data in the RX FIFO
            while (rx_remain && !(i2c->status & MXC_F_I2C_STATUS_RX_EMPTY)) {
                *(req->rx_data)++ = i2c->fifo;
                req->rx_num++;
                rx_remain--;
            }
            i2c->int_en0 = 0;
            if (req->callback != NULL) {
                I2C_Recover(i2c);
                I2C_FreeCallback(i2c_num, E_NO_ERROR);
            }
            return;
        }
    } else {
        // Check for STOP interrupt
        if ((int0 & MXC_F_I2C_INT_FL0_STOP)) {
            i2c->int_en0 = 0;
            if (req->callback != NULL) {
                I2C_Recover(i2c);
                I2C_FreeCallback(i2c_num, E_NO_ERROR);
            }

            return;
        }

        // Check for DONE interrupt
        if ((int0 & MXC_F_I2C_INT_FL0_DONE)) {
            // Read out any data in the RX FIFO
            while (rx_remain && !(i2c->status & MXC_F_I2C_STATUS_RX_EMPTY)) {
                *(req->rx_data)++ = i2c->fifo;
                req->rx_num++;
                rx_remain--;
            }

            return;
        }
    }

    // Clear the interrupts
    i2c->int_fl0 = int0;

    if (states[i2c_num].state == I2C_STATE_READING) {


        // Read out any data in the RX FIFO
        while (rx_remain && !(i2c->status & MXC_F_I2C_STATUS_RX_EMPTY)) {
            *(req->rx_data)++ = i2c->fifo;
            req->rx_num++;
            rx_remain--;
        }

        // Load the slave address if we haven't already started reading the data
        if (rx_remain == req->rx_len) {
            i2c->fifo = (req->addr | 1);

            // Set the RX Count
            i2c->rx_ctrl1 = req->rx_len;

            // Start transmission if idle
            if (!(i2c->status & MXC_F_I2C_STATUS_BUS)) {
                i2c->master_ctrl |= MXC_F_I2C_MASTER_CTRL_START;
            }

            // Set restart or stop
            if (req->restart)  {
                i2c->master_ctrl |= MXC_F_I2C_MASTER_CTRL_RESTART;
            } else {
                i2c->master_ctrl |= MXC_F_I2C_MASTER_CTRL_STOP;
                inten0 |= MXC_F_I2C_INT_EN0_STOP;
            }
        }

        // Set the RX threshold interrupt level
        if (rx_remain >= (MXC_I2C_FIFO_DEPTH - 1)) {
            i2c->rx_ctrl1 = ((i2c->rx_ctrl1 & ~(MXC_F_I2C_RX_CTRL0_RX_THRESH)) |
                             (MXC_I2C_FIFO_DEPTH - 1) << MXC_F_I2C_RX_CTRL0_RX_THRESH_POS);

            inten0 |= MXC_F_I2C_INT_EN0_RX_THRESH;
        }else{
            i2c->rx_ctrl1 = ((i2c->rx_ctrl1 & ~(MXC_F_I2C_RX_CTRL0_RX_THRESH)) |
                             (rx_remain) << MXC_F_I2C_RX_CTRL0_RX_THRESH_POS);

            inten0 |= MXC_F_I2C_INT_EN0_RX_THRESH;
        }

    } else {

        // Load the slave address if we haven't already started writing the data
        if (tx_remain == req->tx_len) {
            i2c->fifo = req->addr;
            // Start transmission if idle
            if (!(i2c->status &  MXC_F_I2C_STATUS_BUS)) {
                i2c->master_ctrl |= MXC_F_I2C_MASTER_CTRL_START;
            }
        }

        // Fill the FIFO
        while ((tx_remain > 0) && !(i2c->status & MXC_F_I2C_STATUS_TX_FULL)) {
            i2c->fifo = *(req->tx_data)++;
            req->tx_num++;
            tx_remain--;
        }

        // Set the TX threshold interrupt level, or restart/stop
        if (tx_remain) {
            i2c->tx_ctrl1 = ((i2c->tx_ctrl1 & ~(MXC_F_I2C_TX_CTRL0_TX_THRESH)) | (1 << MXC_F_I2C_TX_CTRL0_TX_THRESH_POS));
            inten0 |= MXC_F_I2C_INT_EN0_TX_THRESH;
        }
        // Set restart or stop if at the end of the transaction since these actions happen at the moment the bit is set.
        else if (req->restart)  {
            i2c->master_ctrl |= MXC_F_I2C_MASTER_CTRL_RESTART;
        } else {
            i2c->master_ctrl |= MXC_F_I2C_MASTER_CTRL_STOP;
            inten0 |= MXC_F_I2C_INT_EN0_STOP;
        }
    }

    inten0 |= (MXC_F_I2C_INT_EN0_DONE | I2C_ERROR);
    i2c->int_en0 = inten0;
}

/* ************************************************************************** */
int I2C_SlaveAsync(mxc_i2c_regs_t *i2c, i2c_req_t *req)
{
    int i2c_num;

    i2c_num = MXC_I2C_GET_IDX(i2c);

    // Make sure the I2C has been initialized
    if (!(i2c->ctrl & MXC_F_I2C_CTRL_I2C_EN)) {
        return E_UNINITIALIZED;
    }

    // Attempt to register this request
    if (mxc_get_lock((uint32_t*)&states[i2c_num].req, (uint32_t)req) != E_NO_ERROR) {
        return E_BUSY;
    }

    states[i2c_num].req = req;

    // Set Slave Address
    i2c->slave_addr = (req->addr >> 1);

    // Clear the byte counters
    req->tx_num = 0;
    req->rx_num = 0;

    // Disable and clear the interrupts
    i2c->int_en0 = 0;
    i2c->int_en1 = 0;
    i2c->int_fl0 = i2c->int_fl0;
    i2c->int_fl1 = i2c->int_fl1;
    i2c->int_en0 |= MXC_F_I2C_INT_EN0_ADDR_MATCH;

    return E_NO_ERROR;
}
/* ************************************************************************** */
static void I2C_SlaveHandler(mxc_i2c_regs_t *i2c)
{
    uint32_t int0, inten0 = 0;
    int rx_remain, tx_remain, i2c_num;
    i2c_req_t *req;

    i2c_num = MXC_I2C_GET_IDX(i2c);
    req = states[i2c_num].req;

    if ( i2c->int_fl0 & MXC_F_I2C_INT_FL0_ADDR_MATCH ) {
        i2c->int_fl0 |=MXC_F_I2C_INT_EN0_STOP;
    }

    // Check for errors
    int0 = i2c->int_fl0;
    if (int0 & I2C_ERROR) {
        i2c->int_en0 = 0;
        // Calculate the number of bytes sent by the slave
        req->tx_num = states[i2c_num].num_wr - ((i2c->tx_ctrl1 & MXC_F_I2C_TX_CTRL1_TX_FIFO) >> MXC_F_I2C_TX_CTRL1_TX_FIFO_POS);

        if (!req->sw_autoflush_disable) {
            // Manually clear the TXFIFO
            i2c->tx_ctrl0 |= MXC_F_I2C_TX_CTRL0_TX_FLUSH;
        }
        states[i2c_num].num_wr = 0;
        if (req->callback != NULL) {
            I2C_Recover(i2c);
            I2C_FreeCallback(i2c_num, E_COMM_ERR);
        }
        return;
    }

    rx_remain = req->rx_len - req->rx_num;
    tx_remain = req->tx_len - states[i2c_num].num_wr;

    //Check if Master Write has been called and if there is a rx_data buffer
    if ((i2c->int_fl0 & MXC_F_I2C_INT_FL0_TX_LOCK_OUT) && !(i2c->ctrl & MXC_F_I2C_CTRL_READ)) {

        i2c->int_en0 = 0;
        if (req->rx_data == NULL) {
            I2C_Recover(i2c);
            I2C_FreeCallback(i2c_num, E_NULL_PTR);
            return;
        }
    }

    // Check for DONE interrupt
    if (int0 & MXC_F_I2C_INT_EN0_DONE) {
        // Read out any data in the RX FIFO
        while (rx_remain && !(i2c->status & MXC_F_I2C_STATUS_RX_EMPTY)) {
            *(req->rx_data)++ = i2c->fifo;
            req->rx_num++;
            rx_remain--;
        }

        // Calculate the number of bytes sent by the slave
        req->tx_num = states[i2c_num].num_wr - ((i2c->tx_ctrl1 & MXC_F_I2C_TX_CTRL1_TX_FIFO) >> MXC_F_I2C_TX_CTRL1_TX_FIFO_POS);

        if (!req->sw_autoflush_disable) {
            // Manually clear the TXFIFO
            i2c->tx_ctrl0 |= MXC_F_I2C_TX_CTRL0_TX_FLUSH;
        }
        states[i2c_num].num_wr = 0;
        i2c->int_en0 = 0;
        if (req->callback != NULL) {
            if (i2c->int_fl0 & MXC_F_I2C_INT_FL0_STOP) {
                I2C_Recover(i2c);
            } else {    
                i2c->int_fl0 = i2c->int_fl0;
                i2c->int_fl1 = i2c->int_fl1;
            }
            I2C_FreeCallback(i2c_num, E_NO_ERROR);
        }
        return;
    }

    // Clear the interrupts
    i2c->int_fl0 = int0;
    if (i2c->ctrl & MXC_F_I2C_CTRL_READ) {

        i2c->int_en0 = 0;
        if (req->tx_data == NULL) {
            I2C_Recover(i2c);
            I2C_FreeCallback(i2c_num, E_NULL_PTR);
            return;
        }
        // Fill the FIFO
        while ((tx_remain > 0) && !(i2c->status & MXC_F_I2C_STATUS_TX_FULL)) {
            i2c->fifo = *(req->tx_data)++;
            states[i2c_num].num_wr++;
            tx_remain--;
        }

        // Set the TX threshold interrupt level
        if (tx_remain) {
            i2c->tx_ctrl0 = ((i2c->tx_ctrl0 & ~(MXC_F_I2C_TX_CTRL0_TX_THRESH)) | (1 << MXC_F_I2C_TX_CTRL0_TX_THRESH_POS));
            inten0 |= MXC_F_I2C_INT_EN0_TX_THRESH;
        }

    } else {
        // Read out any data in the RX FIFO
        while (rx_remain && !(i2c->status & MXC_F_I2C_STATUS_RX_EMPTY)) {
            *(req->rx_data)++ = i2c->fifo;
            req->rx_num++;
            rx_remain--;
        }

        // Set the RX threshold interrupt level
        if (rx_remain >= (MXC_I2C_FIFO_DEPTH - 1)) {
            i2c->rx_ctrl0 = ((i2c->rx_ctrl0 & ~(MXC_F_I2C_RX_CTRL0_RX_THRESH)) |
                             (MXC_I2C_FIFO_DEPTH - 1) << MXC_F_I2C_RX_CTRL0_RX_THRESH_POS);

            inten0 |= MXC_F_I2C_INT_EN0_RX_THRESH;
        }else{
            i2c->rx_ctrl0 = ((i2c->rx_ctrl0 & ~(MXC_F_I2C_RX_CTRL0_RX_THRESH)) |
                 (rx_remain) << MXC_F_I2C_RX_CTRL0_RX_THRESH_POS);

            inten0 |= MXC_F_I2C_INT_EN0_RX_THRESH;
        }

    }
    inten0 |= (MXC_F_I2C_INT_EN0_DONE | I2C_ERROR | MXC_F_I2C_INT_EN0_TX_LOCK_OUT);
    i2c->int_en0 = inten0;
}

/* ************************************************************************** */
void I2C_Handler(mxc_i2c_regs_t *i2c)
{
    if (i2c->ctrl & MXC_F_I2C_CTRL_MST && i2c->int_fl0) {
        // Service master interrupts if we're in master mode
        I2C_MasterHandler(i2c);
    } else if (i2c->int_fl0 || i2c->int_fl1) {
        // Service the slave interrupts
        I2C_SlaveHandler(i2c);
    }
}

/* ************************************************************************** */
void I2C_DrainRX(mxc_i2c_regs_t *i2c)
{
    i2c->rx_ctrl0 |= MXC_F_I2C_RX_CTRL0_RX_FLUSH;
}

/* ************************************************************************** */
void I2C_DrainTX(mxc_i2c_regs_t *i2c)
{
    i2c->tx_ctrl0 |= MXC_F_I2C_TX_CTRL0_TX_FLUSH;
}
/* ************************************************************************* */
static void I2C_FreeCallback(int i2c_num, int error)
{
    // Save the request
    i2c_req_t *temp_req = states[i2c_num].req;

    mxc_free_lock((uint32_t*)&states[i2c_num].req);

    // Callback if not NULL
    if (temp_req->callback != NULL) {
        temp_req->callback(temp_req, error);
    }
}

/* ************************************************************************* */
static void I2C_Recover(mxc_i2c_regs_t *i2c)
{
    // Disable and clear interrupts
    i2c->int_en0 = 0;
    i2c->int_en1 = 0;
    i2c->int_fl0 = i2c->int_fl0;
    i2c->int_fl1 = i2c->int_fl1;
    i2c->ctrl = 0;
    i2c->ctrl = MXC_F_I2C_CTRL_I2C_EN;
}

/* ************************************************************************* */
int I2C_AbortAsync(i2c_req_t *req)
{
    int i2c_num;
    mxc_i2c_regs_t *i2c;

    // Find the request, set to NULL
    for (i2c_num = 0; i2c_num < MXC_I2C_INSTANCES; i2c_num++) {
        if (req == states[i2c_num].req) {

            i2c = MXC_I2C_GET_I2C(i2c_num);
            I2C_Recover(i2c);
            I2C_FreeCallback(i2c_num, E_ABORT);

            return E_NO_ERROR;
        }
    }

    return E_BAD_PARAM;
}

/* ************************************************************************* */
int I2C_SetTimeout(mxc_i2c_regs_t *i2c, int us){
    uint32_t timeout;
    timeout = (PeripheralClock/1000000) * us;
    if(timeout > 0xFFFF){
        return E_BAD_PARAM;
    }
    i2c->timeout = timeout;
    return E_NO_ERROR;
}

/* ************************************************************************* */
void I2C_ClearTimeout (mxc_i2c_regs_t *i2c)
{
    i2c->timeout = 0;
}
