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
 * @file max7310_test.c
 * @brief Test for the I/O expander MAX7310 controlled through I2C.
 */

#include "ioexpander/max7310.h"
#include "ioexpander/src/max7310_registers.h"

const char g_max7310_i2c_device_id_test_name[] = "IO Expander MAX7310 I2C Device ID Test";

/*! 
 * @note In hardware.h an array of I2C requests is created as multiple I/O expanders
 *       could be used on a board.
 *       Thanks to board_init() in hardware.c, the requests are populated with addresses.
 *       The local I2C request used in this driver should point to the request of the
 *       IO expander that needs to be accessed.
 *       e.g.     max7310_i2c_req = &max7310_i2c_req_array[slave_id];
 */
//extern struct imx_i2c_request *max7310_i2c_req;

extern uint8_t max7310_reg_read(uint8_t reg_addr);


/*!
 * The test tries to read the created device ID for all MAX7310 used on board.
 * That IC has no ID register, so one of the register is initialized with
 * a known value during init. That test should actually always pass.
 * 
 * @return TEST_PASSED or TEST_FAILED
 */
test_return_t max7310_i2c_device_id_check(void)
{
    uint32_t i, data;
    imx_i2c_request_t* max7310_i2c_req = NULL;
    test_return_t ret = TEST_NOT_STARTED, ret_all = TEST_PASSED;

    board_ioexpander_iomux_config();
    for (i = 0; i < MAX7310_NBR; i++) {
        max7310_i2c_req = &max7310_i2c_req_array[i];
        data = max7310_reg_read(timeout_reg);
        printf("data read back is 0x%x\n", data);

        if (data == 0xAC)
            ret = TEST_PASSED;
        else
            ret_all = TEST_FAILED;

        printf("I2C IO expander number %d test %s\n", i, (ret == 0) ? "passed" : "failed");
    }

    return ret_all;
}
