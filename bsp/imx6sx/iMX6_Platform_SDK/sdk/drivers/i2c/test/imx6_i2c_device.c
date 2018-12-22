/*
 * Copyright (c) 2011-2012, Freescale Semiconductor, Inc.
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
 * @file imx6_i2c_device.c
 * @brief Unit test for the I2C controller configured as device.
 *
 * @ingroup diag_i2c
 */

#include "sdk.h"
#include "registers/regsi2c.h"
#include "registers/regsiomuxc.h"

// I2C3 is used to be a slave port
static uint32_t imx6_i2c_slave_port = HW_I2C3;
static imx_i2c_request_t imx6_i2c_req;

static uint8_t test_buffer[] = {'F', 'R', 'E', 'E', 'S', 'C', 'A', 'L', 'E', 'I', '2', 'C', 'T', 'E', 'S', 'T', '!', '!'};
static bool s_masterDidWrite;

/*!
 * Function that handles the received data when the i.MX is
 * used in Slave mode.
 * If the requested address size is 1 or 2 bytes, it does nothing.
 * If the requested address size is 4 bytes, then it writes to the
 * memory location of the i.MX.
 *
 * @param   rq Pointer to struct imx_i2c_request
 */
int32_t imx6_slave_receive(const imx_i2c_request_t *rq)
{
    int32_t ret = 0;
    uint32_t data_address;
    uint32_t r_data = 0;
    uint8_t addr_sz = rq->reg_addr_sz;

    s_masterDidWrite = true;

    /* 
     * Nothing to do for address size of 1 or 2 bytes, the received
     * data is only displayed at the end of the transfer.
     */

    if(addr_sz == 4)
    {
        /* make the address */
        data_address = (uint32_t) ((rq->buffer[0] << 24) | (rq->buffer[1] << 16) |
                       (rq->buffer[2] << 8) | rq->buffer[3]);
        /* make the data */
        r_data = (rq->buffer[addr_sz+3] << 24) | (rq->buffer[addr_sz+2] << 16) |
                 (rq->buffer[addr_sz+1] << 8) | rq->buffer[addr_sz];
        /* write the data */
        writel(r_data, data_address);
    }

    return ret;
}

// function when in slave mode to transmit data to the master

/*!
 * Function that prepares the data to transmit when the i.MX is
 * used in Slave mode.
 * If the requested address size is 1 or 2 bytes, it provides
 * data from test_buffer. 
 * If the requested address size is 4 bytes, then it can provides the
 * content of an i.MX memory mapped address.
 *
 * @param   rq Pointer to struct imx_i2c_request
 */
int32_t imx6_slave_transmit(const imx_i2c_request_t *rq)
{
    int32_t ret = 0;
    uint32_t data_address;
    uint32_t w_data;
    uint8_t addr_sz = rq->reg_addr_sz;

    s_masterDidWrite = false;

    switch(addr_sz) {
        case 1:
        case 2:
            /* ignore the address for that address sizes
             * and provide data from the test buffer */
            rq->buffer[addr_sz] = test_buffer[0];
            rq->buffer[addr_sz+1] = test_buffer[1];
            rq->buffer[addr_sz+2] = test_buffer[2];
            rq->buffer[addr_sz+3] = test_buffer[3];
            break;
        case 4:
            /* make the address */
            data_address = (uint32_t) ((rq->buffer[0] << 24) | (rq->buffer[1] << 16) |
                           (rq->buffer[2] << 8) | rq->buffer[3]);
            /* get the data */
            w_data = readl(data_address);
            rq->buffer[addr_sz] = w_data & 0xFF;
            rq->buffer[addr_sz+1] = (w_data >> 8) & 0xFF;
            rq->buffer[addr_sz+2] = (w_data >> 16) & 0xFF;
            rq->buffer[addr_sz+3] = (w_data >> 24) & 0xFF;
            break;
        default:
            break;
    }

    return ret;
}

/*!
 * Main test function.
 * It prepares the different settings used to define the slave behavior.
 * The number of slave ID and address cycles can be set here. Also, the
 * pointers to the functions that handle the received and transmitted are
 * provided here.
 * The transfer function initialize the I2C controller in slave mode
 * waiting for a single external transfer to read or write a data.
 *
 */
//! todo Move the BOARD_EVB code out of driver.
int32_t i2c_imx6_slave_test(void)
{
    uint8_t sel, i;
    uint8_t data_buffer[16];    

    printf("  Starting i.MX6DQ/SDL slave test...\n");

    // Initialize the request
    imx6_i2c_req.ctl_addr = imx6_i2c_slave_port;   /* the I2C controller instance */
    imx6_i2c_req.dev_addr = IMX6_DEFAULT_SLAVE_ID;  /* the I2C DEVICE address - keep default */
    imx6_i2c_req.reg_addr = 0;          /* not used in slave mode */
    imx6_i2c_req.reg_addr_sz = 1;       /* used to set the address size of this slave */
    imx6_i2c_req.buffer = data_buffer;  /* buffer used by the driver during read/write accesses */
    imx6_i2c_req.buffer_sz = 0;         /* is used to count the number of data cycles in the driver */
    imx6_i2c_req.slave_receive = &imx6_slave_receive;   /* slave receive data from master */
    imx6_i2c_req.slave_transmit = &imx6_slave_transmit; /* slave transmit data to master */
    /* initialize the buffer with known data */
    memset(imx6_i2c_req.buffer, 0, sizeof(imx6_i2c_req.buffer));

    i2c_init(imx6_i2c_slave_port, 170000);

#if defined(BOARD_EVB)
    /*Set iomux and daisy chain for eeprom test */
    HW_IOMUXC_SW_MUX_CTL_PAD_EIM_DATA17_WR(
            BF_IOMUXC_SW_MUX_CTL_PAD_EIM_DATA17_SION_V(ENABLED) |
            BF_IOMUXC_SW_MUX_CTL_PAD_EIM_DATA17_MUX_MODE_V(ALT6));
    HW_IOMUXC_I2C3_SCL_IN_SELECT_INPUT_WR(
            BF_IOMUXC_I2C3_SCL_IN_SELECT_INPUT_DAISY_V(EIM_DATA17_ALT6));
    HW_IOMUXC_SW_PAD_CTL_PAD_EIM_DATA17_WR(
            BF_IOMUXC_SW_PAD_CTL_PAD_EIM_DATA17_HYS_V(ENABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_EIM_DATA17_PUS_V(100K_OHM_PU) |
            BF_IOMUXC_SW_PAD_CTL_PAD_EIM_DATA17_PUE_V(PULL) |
            BF_IOMUXC_SW_PAD_CTL_PAD_EIM_DATA17_PKE_V(ENABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_EIM_DATA17_ODE_V(ENABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_EIM_DATA17_SPEED_V(100MHZ) |
            BF_IOMUXC_SW_PAD_CTL_PAD_EIM_DATA17_DSE_V(40_OHM) |
            BF_IOMUXC_SW_PAD_CTL_PAD_EIM_DATA17_SRE_V(SLOW));

    HW_IOMUXC_SW_MUX_CTL_PAD_EIM_DATA18_WR(
            BF_IOMUXC_SW_MUX_CTL_PAD_EIM_DATA18_SION_V(ENABLED) |
            BF_IOMUXC_SW_MUX_CTL_PAD_EIM_DATA18_MUX_MODE_V(ALT6));
    HW_IOMUXC_I2C3_SDA_IN_SELECT_INPUT_WR(
            BF_IOMUXC_I2C3_SDA_IN_SELECT_INPUT_DAISY_V(EIM_DATA18_ALT6));
    HW_IOMUXC_SW_PAD_CTL_PAD_EIM_DATA18_WR(
            BF_IOMUXC_SW_PAD_CTL_PAD_EIM_DATA18_HYS_V(ENABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_EIM_DATA18_PUS_V(100K_OHM_PU) |
            BF_IOMUXC_SW_PAD_CTL_PAD_EIM_DATA18_PUE_V(PULL) |
            BF_IOMUXC_SW_PAD_CTL_PAD_EIM_DATA18_PKE_V(ENABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_EIM_DATA18_ODE_V(ENABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_EIM_DATA18_SPEED_V(100MHZ) |
            BF_IOMUXC_SW_PAD_CTL_PAD_EIM_DATA18_DSE_V(40_OHM) |
            BF_IOMUXC_SW_PAD_CTL_PAD_EIM_DATA18_SRE_V(SLOW));
#endif

    do {
        printf("\n    1 - to perform an access from the external master.\n");
        printf("    2 - to change the address size (default is %d bytes per address).\n", imx6_i2c_req.reg_addr_sz);
        printf("    x - to exit.\n\n");

        do {
            sel = getchar();
        } while (sel == NONE_CHAR);

        if (sel == '1')
        {
            printf("    Waiting for the access from the master...\n");

            i2c_slave_xfer(&imx6_i2c_req);

            if (!s_masterDidWrite)
            {
                printf("Master did a read access at address 0x");
                for(i=0;i<imx6_i2c_req.reg_addr_sz;i++)
                    printf("%02X", imx6_i2c_req.buffer[i]);
                printf(" of %dbytes.\n", imx6_i2c_req.buffer_sz);
                printf("The transmitted data is: 0x");
                for(i=imx6_i2c_req.buffer_sz;i>0;i--)
                    printf("%02X", imx6_i2c_req.buffer[i-1+imx6_i2c_req.reg_addr_sz]);
                printf("\n");
            }
            else
            {
                printf("Master did a write access at address 0x");
                for(i=0;i<imx6_i2c_req.reg_addr_sz;i++)
                    printf("%02X", imx6_i2c_req.buffer[i]);
                printf(" of %dbytes.\n", imx6_i2c_req.buffer_sz);
                printf("The received data is: 0x");
                for(i=imx6_i2c_req.buffer_sz;i>0;i--)
                    printf("%02X", imx6_i2c_req.buffer[i-1+imx6_i2c_req.reg_addr_sz]);
                printf("\n");
            }
        }
        else if (sel == '2')
        {
            printf("    Set the address size to 1,2, or 4 bytes.\n");
            do {
                sel = getchar();
            } while (sel == NONE_CHAR);

            if((sel != '1') && (sel != '2') && (sel != '4'))
                printf("    Size is out of 1,2 or 4 bytes => keep current.\n");
            else
            {
                /* get an ASCII hex code so move it to integer */
                imx6_i2c_req.reg_addr_sz = sel - 0x30;
                printf("    Address size set to %d bytes\n", imx6_i2c_req.reg_addr_sz);
                if(sel == '4')
                    printf("Warning: when using a 4 bytes address, the master reads or writes"
                           " data to a valid i.MX6 address. Therefore, the address must be"
                           " valid, word aligned, and a 4 bytes data is recommended.\n");
            }
        }
        else if (sel == 'x') {
            printf("\nTest exit.\n");
            break;
        }

    } while(1);

    printf("i.MX6 as I2C slave test pass.\n");
    return TEST_PASSED;
 }
