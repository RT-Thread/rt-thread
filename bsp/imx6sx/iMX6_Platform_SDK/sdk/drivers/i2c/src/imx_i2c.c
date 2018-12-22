/*
 * Copyright (c) 2010-2012, Freescale Semiconductor, Inc.
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

/*!
 * @file imx_i2c.c
 * @brief Main driver for the I2C controller. It initializes the controller
 *        and handles the master mode.
 *
 * @ingroup diag_i2c
 */

#include "sdk.h"
#include "i2c/imx_i2c.h"
#include "imx_i2c_internal.h"
#include "registers/regsi2c.h"
#include "core/ccm_pll.h"
#include "core/interrupt.h"

//! Set this macro to 1 to enable tracing of data send and receive.
#define TRACE_I2C 0

//! @brief Get the irq id of I2C by instance number.
//! @param x I2C instance number, from 1 through 3.
#define I2C_IRQS(x) ( (x) == HW_I2C1 ? IMX_INT_I2C1 : (x) == HW_I2C2 ? IMX_INT_I2C2 : (x) == HW_I2C3 ? IMX_INT_I2C3 : 0xFFFFFFFF)

////////////////////////////////////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////////////////////////////////////

static const uint16_t i2c_freq_div[50][2] = {
        { 22,   0x20 }, { 24,   0x21 }, { 26,   0x22 }, { 28,   0x23 },
        { 30,   0x00 }, { 32,   0x24 }, { 36,   0x25 }, { 40,   0x26 },
        { 42,   0x03 }, { 44,   0x27 }, { 48,   0x28 }, { 52,   0x05 },
        { 56,   0x29 }, { 60,   0x06 }, { 64,   0x2A }, { 72,   0x2B },
        { 80,   0x2C }, { 88,   0x09 }, { 96,   0x2D }, { 104,  0x0A },
        { 112,  0x2E }, { 128,  0x2F }, { 144,  0x0C }, { 160,  0x30 },
        { 192,  0x31 }, { 224,  0x32 }, { 240,  0x0F }, { 256,  0x33 },
        { 288,  0x10 }, { 320,  0x34 }, { 384,  0x35 }, { 448,  0x36 },
        { 480,  0x13 }, { 512,  0x37 }, { 576,  0x14 }, { 640,  0x38 },
        { 768,  0x39 }, { 896,  0x3A }, { 960,  0x17 }, { 1024, 0x3B },
        { 1152, 0x18 }, { 1280, 0x3C }, { 1536, 0x3D }, { 1792, 0x3E },
        { 1920, 0x1B }, { 2048, 0x3F }, { 2304, 0x1C }, { 2560, 0x1D },
        { 3072, 0x1E }, { 3840, 0x1F }
};

////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////

static inline int is_bus_free(unsigned int instance);
static int wait_till_busy(uint32_t instance);
static inline void imx_send_stop(unsigned int instance);
static int wait_op_done(uint32_t instance, int is_tx);
static int tx_byte(uint8_t * data, uint32_t instance);
static int rx_bytes(uint8_t * data, uint32_t instance, int sz);
static void set_i2c_clock(uint32_t instance, uint32_t baud);

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

unsigned i2c_get_request_instance(const imx_i2c_request_t * rq)
{
    // First see if there device info is set.
    if (rq->device)
    {
        // Use the instance number in the device info.
        return rq->device->port;
    }
    
    // Check if the ctl_addr is within the range of instances.
    if (rq->ctl_addr >= 1 && rq->ctl_addr <= HW_I2C_INSTANCE_COUNT)
    {
        // Valid instance number, so use it directly.
        return rq->ctl_addr;
    }
    else
    {
        // Not a valid instance, so treat it as a base address.
        return REGS_I2C_INSTANCE(rq->ctl_addr);
    }
}

/*!
 * @brief Loop status register for IBB to go 0.
 *
 * The loop also breaks on max number of iterations.
 *
 * @param instance Instance number of the I2C module.
 *
 * @return  0 if successful; -1 otherwise
 */
static inline int is_bus_free(unsigned int instance)
{
    int i = WAIT_RXAK_LOOPS;

    while (HW_I2C_I2SR(instance).B.IBB && (--i > 0));

    if (i <= 0) {
        debug_printf("Error: I2C Bus not free!\n");
        return -1;
    }

    return 0;
}

/*!
 * @brief Loop status register for IBB to go 1.
 *
 * It breaks the loop if there's an arbitration lost occurred or the maximum
 * number of iterations has been reached.
 *
 * @param instance Instance number of the I2C module.
 *
 * @return  0 if successful; -1 otherwise
 */
static int wait_till_busy(uint32_t instance)
{
    int i = WAIT_BUSY_LOOPS;

    while (!HW_I2C_I2SR(instance).B.IBB && (--i > 0)) {
        if (HW_I2C_I2SR(instance).B.IAL) {
            debug_printf("Error: arbitration lost!\n");
            return -1;
        }
    }

    if (i <= 0) {
        debug_printf("I2C Error: timeout in %s; %d\n", __FUNCTION__, __LINE__);
        return -1;
    }

    return 0;
}

/*!
 * Generates a STOP signal, called by rx and tx routines
 *
 * @param instance Instance number of the I2C module.
 *
 * @return  none
 */
static inline void imx_send_stop(unsigned int instance)
{
    HW_I2C_I2CR(instance).B.MSTA = 0;
}

/*!
 * @brief Wait for operation done.
 *
 * This function loops until we get an interrupt. On timeout it returns -1.
 * It reports arbitration lost if IAL bit of I2SR register is set
 * Clears the interrupt
 * If operation is transfer byte function will make sure we received an ack
 *
 * @param instance Instance number of the I2C module.
 * @param   is_tx       Pass 1 for transfering, 0 for receiving 
 *
 * @return  0 if successful; negative integer otherwise
 */
static int wait_op_done(uint32_t instance, int is_tx)
{
    hw_i2c_i2sr_t v;
    int i = WAIT_RXAK_LOOPS;

    // Loop until we get an interrupt 
    do {
        v.U = HW_I2C_I2SR_RD(instance);
    } while (!v.B.IIF && (--i > 0));

    // If timeout error occurred return error 
    if (i <= 0) {
        debug_printf("I2C Error: timeout unexpected\n");
        return -1;
    }

    // Clear the interrupts 
    HW_I2C_I2SR_WR(instance, 0);

    // Check for arbitration lost 
    if (v.B.IAL) {
        debug_printf("Error %d: Arbitration lost\n", __LINE__);
        return ERR_ARB_LOST;
    }

    // Check for ACK received in transmit mode 
    if (is_tx) {
        if (v.B.RXAK) {
            // No ACK received, generate STOP by clearing MSTA bit 
            debug_printf("Error %d: no ack received\n", __LINE__);
            
            // Generate a STOP signal 
            imx_send_stop(instance);
            return ERR_NO_ACK;
        }
    }

    return 0;
}

/*!
 * @brief Implements a loop to send a byte to I2C slave.
 *
 * For master transmit. Always expect a RXAK signal to be set!
 *
 * @param   data        return buffer for data
 * @param instance Instance number of the I2C module.
 *
 * @return  0 if successful; -1 otherwise
 */
static int tx_byte(uint8_t * data, uint32_t instance)
{
#if TRACE_I2C
    debug_printf("%s(data=0x%02x, instance=%d)\n", __FUNCTION__, *data, instance);
#endif // TRACE_I2C

    // clear both IAL and IIF bits 
    HW_I2C_I2SR_WR(instance, 0);

    // write to data register 
    HW_I2C_I2DR_WR(instance, *data);

    // wait for transfer of byte to complete 
    return wait_op_done(instance, 1);
}

/*!
 * @brief Implements a loop to receive bytes from I2C slave.
 *
 * For master receive.
 *
 * @param   data        return buffer for data
 * @param instance Instance number of the I2C module.
 * @param   sz          number of bytes to receive
 *
 * @return  0 if successful; -1 otherwise
 */
static int rx_bytes(uint8_t * data, uint32_t instance, int sz)
{
    int i;

    for (i = 0; sz > 0; sz--, i++) {
        if (wait_op_done(instance, 0) != 0) {
            return -1;
        }

        // the next two if-statements setup for the next read control register value 
        if (sz == 1) {
            // last byte --> generate STOP 
            // generate STOP by clearing MSTA bit 
            imx_send_stop(instance);
        }

        if (sz == 2) {
            // 2nd last byte --> set TXAK bit to NOT generate ACK 
            HW_I2C_I2CR(instance).B.TXAK = 1;
        }
        
        // read the true data 
        data[i] = HW_I2C_I2DR_RD(instance);
#if TRACE_I2C

        debug_printf("OK 0x%02x\n", data[i]);
#endif // TRACE_I2C
    }

    return 0;
}

static void set_i2c_clock(uint32_t instance, uint32_t baud)
{
    // Adjust the divider to get the closest SCL frequency to baud rate 
    uint32_t src_clk = get_main_clock(IPG_PER_CLK);
    uint32_t divider = src_clk / baud;
    uint8_t index = 0;
    
    if (divider < i2c_freq_div[0][0])
    {
        divider = i2c_freq_div[0][0];
        index = 0;
        debug_printf("Warning :can't find a smaller divider than %d.\n", divider);
        debug_printf("SCL frequency is set at %d - expected was %d.\n", src_clk/divider, baud);
    }
    else if (divider > i2c_freq_div[49][0])
    {
        divider = i2c_freq_div[49][0];
        index = 49;
        debug_printf("Warning: can't find a bigger divider than %d.\n", divider);
        debug_printf("SCL frequency is set at %d - expected was %d.\n", src_clk/divider, baud);
    }
    else
    {
        for (index = 0; i2c_freq_div[index][0] < divider; index++);
        divider = i2c_freq_div[index][0];
    }
    
    HW_I2C_IFDR_WR(instance, BF_I2C_IFDR_IC(i2c_freq_div[index][1]));
}

int i2c_xfer(const imx_i2c_request_t *rq, int dir)
{
    uint32_t reg;
    uint32_t ret = 0;
    uint16_t i2cr;
    uint8_t i;
    uint8_t data;
    uint32_t instance = i2c_get_request_instance(rq);
    uint8_t address = (rq->device ? rq->device->address : rq->dev_addr) << 1;

    if (rq->buffer_sz == 0 || rq->buffer == NULL) {
        debug_printf("Invalid register address size=%x, buffer size=%x, buffer=%x\n",
               rq->reg_addr_sz, rq->buffer_sz, (unsigned int)rq->buffer);
        return ERR_INVALID_REQUEST;
    }

    // clear the status register 
    HW_I2C_I2SR_WR(instance, 0);

    // enable the I2C controller 
    HW_I2C_I2CR_WR(instance, BM_I2C_I2CR_IEN);

    // Check if bus is free, if not return error 
    if (is_bus_free(instance) != 0) {
        return -1;
    }
    
    // If the request has device info attached and it has a non-zero bit rate, then
    // change the clock to the specified rate.
    if (rq->device && rq->device->freq)
    {
        set_i2c_clock(instance, rq->device->freq);
    }

    // Step 1: Select master mode, assert START signal and also indicate TX mode 
    HW_I2C_I2CR_WR(instance, BM_I2C_I2CR_IEN | BM_I2C_I2CR_MSTA | BM_I2C_I2CR_MTX);

    // make sure bus is busy after the START signal 
    if (wait_till_busy(instance) != 0) {
        debug_printf("1\n");
        return -1;
    }
    
    // Step 2: send slave address + read/write at the LSB 
    data = address | I2C_WRITE;

    if ((ret = tx_byte(&data, instance)) != 0) {
        debug_printf("START TX ERR %d\n", ret);

        if (ret == ERR_NO_ACK) {
            return ERR_NO_ACK_ON_START;
        } else {
            return ret;
        }
    }
    
    // Step 3: send I2C device register address 
    if (rq->reg_addr_sz > 4) {
        debug_printf("Warning register address size %d should less than 4\n", rq->reg_addr_sz);
        return ERR_INVALID_REQUEST;
    }

    reg = rq->reg_addr;

    for (i = 0; i < rq->reg_addr_sz; i++, reg >>= 8) {
        data = reg & 0xFF;
        
#if TRACE_I2C
        debug_printf("sending I2C=%d device register: data=0x%x, byte %d\n", instance, data, i);
#endif // TRACE_I2C

        if (tx_byte(&data, instance) != 0) {
            return -1;
        }
    }

    // Step 4: read/write data 
    if (dir == I2C_READ) {
        // do repeat-start 
        HW_I2C_I2CR(instance).B.RSTA = 1;

        // make sure bus is busy after the REPEATED START signal 
        if (wait_till_busy(instance) != 0) {
            return ERR_TX;
        }
        
        // send slave address again, but indicate read operation 
        data = address | I2C_READ;

        if (tx_byte(&data, instance) != 0) {
            return -1;
        }

        // change to receive mode 
        i2cr = HW_I2C_I2CR_RD(instance) & ~BM_I2C_I2CR_MTX;
        
        // if only one byte to read, make sure don't send ack 
        if (rq->buffer_sz == 1) {
            i2cr |= BM_I2C_I2CR_TXAK;
        }
        HW_I2C_I2CR_WR(instance, i2cr);

        // dummy read 
        data = HW_I2C_I2DR_RD(instance);

        // now reading ... 
        if (rx_bytes(rq->buffer, instance, rq->buffer_sz) != 0) {
            return -1;
        }
    } else {
        // I2C_WRITE 
        for (i = 0; i < rq->buffer_sz; i++) {
            // send device register value 
            data = rq->buffer[i];

            if ((ret = tx_byte(&data, instance)) != 0) {
                break;
            }
        }
    }

    // generate STOP by clearing MSTA bit 
    imx_send_stop(instance);

    // Check if bus is free, if not return error 
    if (is_bus_free(instance) != 0) {
        debug_printf("WARNING: bus is not free\n");
    }
    
    // disable the controller 
    HW_I2C_I2CR_WR(instance, 0);

    return ret;
}

int i2c_read(const imx_i2c_request_t *rq)
{
    return i2c_xfer(rq, I2C_READ);
}

int i2c_write(const imx_i2c_request_t *rq)
{
    return i2c_xfer(rq, I2C_WRITE);
}

void i2c_setup_interrupt(uint32_t instance, void (*irq_subroutine)(void), bool state)
{
    uint32_t irq_id = I2C_IRQS(instance);

    if (state) {
        // register the IRQ sub-routine 
        register_interrupt_routine(irq_id, irq_subroutine);
        
        // enable the IRQ at the ARM core level 
        enable_interrupt(irq_id, CPU_0, 0);
        
        // clear the status register 
        HW_I2C_I2SR_WR(instance, 0);
        
        // and enable the interrupts in the I2C controller 
        HW_I2C_I2CR(instance).B.IIEN = 1;
    } else {
        // disable the IRQ at the ARM core level 
        disable_interrupt(irq_id, CPU_0);
        
        // and disable the interrupts in the I2C controller 
        HW_I2C_I2CR(instance).B.IIEN = 0;
        
        // clear the status register 
        HW_I2C_I2SR_WR(instance, 0);
    }
}

int i2c_init(uint32_t base, uint32_t baud)
{
    int instance;
    
    // Accept either an instance or base address for the base param.
    if (base >= 1 && base <= HW_I2C_INSTANCE_COUNT)
    {
        instance = base;
    }
    else
    {
        instance = REGS_I2C_INSTANCE(base);
    }
    
    // enable the source clocks to the I2C port 
    clock_gating_config(REGS_I2C_BASE(instance), CLOCK_ON);

    // Set iomux configuration 
    i2c_iomux_config(instance);

    // reset I2C 
    HW_I2C_I2CR_WR(instance, 0);

    // Set clock.
    set_i2c_clock(instance, baud);

    // set an I2C slave address 
    HW_I2C_IADR_WR(instance, IMX6_DEFAULT_SLAVE_ID);

    // clear the status register 
    HW_I2C_I2SR_WR(instance, 0);

    // enable the I2C controller 
    HW_I2C_I2CR_WR(instance, BM_I2C_I2CR_IEN);

    return 0;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
