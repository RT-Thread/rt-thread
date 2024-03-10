/*
 * Copyright (c) 2012, Freescale Semiconductor, Inc.
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
 * @file imx_i2c_slave.c
 * @brief Slave mode driver for the I2C controller.
 *
 * @ingroup diag_i2c
 */

#include "sdk.h"
#include "imx_i2c_internal.h"

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

/*!
 * @brief State of the current I2C driver slave mode transfer.
 */
typedef struct _i2c_slave_state {
    volatile uint8_t waitForIrq;
    volatile uint16_t statusRegister;
    uint32_t slavePortInstance;
    uint8_t addressCycle;
    uint8_t dataCycle;
    uint8_t readAccess;
} i2c_slave_state_t;

//! State of the current I2C driver slave mode transfer.
static i2c_slave_state_t s_slaveState;

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

void i2c_slave_interrupt_routine(void)
{
    s_slaveState.statusRegister = HW_I2C_I2SR_RD(s_slaveState.slavePortInstance);
    
    // clear the status register 
    HW_I2C_I2SR_WR(s_slaveState.slavePortInstance, 0);

    s_slaveState.waitForIrq = 0;
}

void i2c_slave_handler(const imx_i2c_request_t *rq)
{
    uint16_t i2cr;
    uint16_t i2sr;
    uint8_t data, offset;
    uint32_t instance = i2c_get_request_instance(rq);

    // use a local version of the status updated during the last interrupt 
    i2sr = s_slaveState.statusRegister;
    s_slaveState.statusRegister = 0;

    // if I2SR is cleared, there's nothing to do 
    if (!i2sr)
    {
        return;
    }

    // read the current state of the control register 
    i2cr = HW_I2C_I2CR_RD(instance);

    // was the i.MX6 slave address matched <=> IAAS=1? 
    if (i2sr & BM_I2C_I2SR_IAAS)
    {
        // IAAS=1, so enter in an address cycle 
        // is it a master read access <=> SRW=1? 
        if (i2sr & BM_I2C_I2SR_SRW)
        {
            // SRW=1, so this is a master read access 
            // set transmit mode 
            i2cr |= BM_I2C_I2CR_MTX;
            HW_I2C_I2CR_WR(instance, i2cr);

            // set a flag to notify that this is a read from master 
            s_slaveState.readAccess = BM_I2C_I2SR_SRW;

            // get the data from the application 
            rq->slave_transmit(rq);
            
            // first sent byte 
            data = rq->buffer[s_slaveState.addressCycle];
            s_slaveState.dataCycle++;
            
            // transmit the data 
            HW_I2C_I2DR_WR(instance, data);
       }
        else
        {
            // SRW=0, this is a master write access 
            // set receive mode 
            i2cr &= ~BM_I2C_I2CR_MTX;
            HW_I2C_I2CR_WR(instance, i2cr);
            
            // dummy read of the received slave address 
            data = HW_I2C_I2DR_RD(instance);
        }
    }
    else
    {
        // IAAS=0, so enter in a data cycle 
        // is it in transmit mode? 
        if (i2cr & BM_I2C_I2CR_MTX)
        {
            // MTX=1, so this is in transmit mode 
            // is ACK received <=> RXAK=0? 
            if (!(i2sr & BM_I2C_I2SR_RXAK))
            {
                // RXAK=0, an acknowledge was received 
                // get data from the application if not done 
                // already during the first data access above
                // following sent bytes 
                data = rq->buffer[s_slaveState.dataCycle + s_slaveState.addressCycle];
                s_slaveState.dataCycle++;
                
                // transmit the data 
                HW_I2C_I2DR_WR(instance, data);
            }
            else
            {
                // RXAK=1, no acknowledge was received 
                // set receive mode 
                i2cr &= ~BM_I2C_I2CR_MTX;
                HW_I2C_I2CR_WR(instance, i2cr);
                
                // dummy read of the received data 
                data = HW_I2C_I2DR_RD(instance);
            }
        }
        else
        {
            // MTX=0, so this is in receive mode 
            if (s_slaveState.addressCycle < rq->reg_addr_sz)
            {
                // this is an address that is read 
                offset = s_slaveState.addressCycle;
                s_slaveState.addressCycle++;
            }
            else
            {
                //this is a data that is read 
                offset = s_slaveState.addressCycle + s_slaveState.dataCycle;               
                s_slaveState.dataCycle++;
            }
            
            // read the received data 
            rq->buffer[offset] = HW_I2C_I2DR_RD(instance);
        }
    }
}

void i2c_slave_xfer(imx_i2c_request_t *rq)
{
    uint32_t instance = i2c_get_request_instance(rq);

    // enable the I2C controller 
    HW_I2C_I2CR_WR(instance, BM_I2C_I2CR_IEN);
    
    // initialize the number of addr and data cycles for the transfer 
    s_slaveState.addressCycle = 0;
    s_slaveState.dataCycle = 0;
    s_slaveState.readAccess = 0;

    // set the chosen I2C slave address 
    HW_I2C_IADR_WR(instance, (rq->device ? rq->device->address : rq->dev_addr));

    s_slaveState.slavePortInstance = instance;

    // Enable the interrupts for the I2C controller 
    i2c_setup_interrupt(instance, &i2c_slave_interrupt_routine, true);

    // The slave behaves like a EEPROM of rq.reg_addr_sz bytes for 
    // and g_data_cycle bytes for data

    // wait for the first 1 interrupt that should make the bus busy 
    s_slaveState.waitForIrq = 1;
    while (s_slaveState.waitForIrq == 1);

    do {
        i2c_slave_handler(rq);

        s_slaveState.waitForIrq = 1;
        while (s_slaveState.waitForIrq == 1)
        {
            // the STOP condition can arrive late after the last transfer 
            if (!HW_I2C_I2SR(instance).B.IBB)
            {
                break;
            }
        }
    } while (HW_I2C_I2SR(instance).B.IBB);

    // Provide to the application the data written by the master 
    if (s_slaveState.readAccess & BM_I2C_I2SR_SRW)
    {
        // set the number of transmitted data 
        rq->buffer_sz = s_slaveState.dataCycle;

#ifdef DEBUG
        uint8_t i;
        printf("Master did a read access at address 0x");
        for(i=0;i<s_slaveState.addressCycle;i++)
            printf("%02X", rq->buffer[i]);
        printf(" of %dbytes.\n", s_slaveState.dataCycle);
        printf("The transmitted data is: 0x");
        for(i=s_slaveState.dataCycle;i>0;i--)
            printf("%02X", rq->buffer[i-1+s_slaveState.addressCycle]);
        printf("\n");
#endif
    }
    else
    {
        // set the number of received data 
        rq->buffer_sz = s_slaveState.dataCycle;
        
        // send the received data to the application
        if (rq->slave_receive)
        {
            rq->slave_receive(rq);
        }

#ifdef DEBUG
        uint8_t i;
        printf("Master did a write access at address 0x");
        for(i=0;i<s_slaveState.addressCycle;i++)
            printf("%02X", rq->buffer[i]);
        printf(" of %dbytes.\n", s_slaveState.dataCycle);
        printf("The received data is: 0x");
        for(i=s_slaveState.dataCycle;i>0;i--)
            printf("%02X", rq->buffer[i-1+s_slaveState.addressCycle]);
        printf("\n");
#endif
    }

    // Disable the interrupts for the I2C controller 
    i2c_setup_interrupt(instance, NULL, false);

    // disable the controller 
    HW_I2C_I2CR_WR(instance, 0);
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
