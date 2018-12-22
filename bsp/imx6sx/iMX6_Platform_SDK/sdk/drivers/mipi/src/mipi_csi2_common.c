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
 * @file  mipi_csi2_common.c
 * @brief common functions for mipi csi.
 *
 * @ingroup diag_mipi
 */

#include <stdio.h>
#include "mipi/mipi_common.h"
#include "ipu/ipu_common.h"
#include "registers/regsmipicsi.h"

#define PREVIEW 1
#define MIPI_SENSOR_ADDR 0x3C

/*!
 * @brief initialize the i2c module for mipi camera sensor -- mainly enable the i2c clock, module itself and the i2c clock prescaler.
 *
 * @param   base        base address of i2c module (also assigned for i2cx_clk)
 * @param   baud        the desired data rate in bps
 *
 * @return  0 if successful; non-zero otherwise
 */
static void mipi_sensor_i2c_init(uint32_t base, uint32_t baud)
{
    int ret = 0;
    int i2c_delay = 500 * 100;

    ret = i2c_init(base, baud);
    if (ret != 0) {
        printf("Sensor I2C initialization failed!\n");
        return;
    }
    hal_delay_us(i2c_delay);

}

/*!
 * @brief Perform I2C write operation for mipi camera sensor
 *
 * @param   i2c_base	sensor i2c master address
 * @param   reg	 		sensor i2c register address
 * @param	pval 		value write to i2c register
 *
 * @return  0 if successful; non-zero otherwise
 */
static int32_t mipi_sensor_write_reg(uint32_t i2c_base, uint16_t reg, uint8_t pval)
{
    int ret = 0;
    struct imx_i2c_request rq = {0};
//  printf("reg 0x%04x : 0x%02x\n", reg, pval);

    reg = ((reg & 0x00FF) << 8) | ((reg & 0xFF00) >> 8);    //swap MSB and LSB
    rq.ctl_addr = i2c_base;
    rq.dev_addr = MIPI_SENSOR_ADDR;
    rq.reg_addr = reg;
    rq.reg_addr_sz = 2;

    rq.buffer_sz = 1;
    rq.buffer = &pval;
    ret = i2c_xfer(&rq, I2C_WRITE);

    return ret;
}

/*!
 * @brief Perform I2C read operation for mipi camera sensor
 *
 * @param   i2c_base	sensor i2c master address
 * @param   reg	 		sensor i2c register address
 * @param	pval 		value read from i2c register
 *
 * @return  0 if successful; non-zero otherwise
 */
static int32_t mipi_sensor_read_reg(uint32_t i2c_base, uint16_t reg, uint8_t * pval)
{
    int ret = 0;
    struct imx_i2c_request rq = {0};

    reg = ((reg & 0x00FF) << 8) | ((reg & 0xFF00) >> 8);    //swap MSB and LSB
    rq.ctl_addr = i2c_base;
    rq.dev_addr = MIPI_SENSOR_ADDR;
    rq.reg_addr = reg;
    rq.reg_addr_sz = 2;

    rq.buffer_sz = 1;
    rq.buffer = pval;
    ret = i2c_xfer(&rq, I2C_READ);

    return ret;
}

/* @brief Check I2C write and read function. This funtions is used for debug purpose. 
 *
 * @param   i2c_base	sensor i2c master address
 * @param   slave_addr	sensor i2c slave device address
 * @param   reg	 		sensor i2c register address
 * @param	pval 		value read from i2c register
 *
 * @return  0 if successful; non-zero otherwise
 */
static int dev_check_reg(uint32_t i2c_base, uint32_t slave_addr, uint8_t reg,
                         uint8_t *pval)
{
    int ret = 0;
    struct imx_i2c_request rq = {0};

    rq.ctl_addr = i2c_base;
    rq.dev_addr = slave_addr >> 1;
    rq.reg_addr = reg;
    rq.reg_addr_sz = 1;

    rq.buffer_sz = 1;
    rq.buffer = pval;
    *pval = 0xAB;
    i2c_xfer(&rq, I2C_WRITE);
    *pval = 0;
    printf("baddr %x, id %x\n", reg, *pval);
    ret = i2c_xfer(&rq, I2C_READ);
    printf("aaddr %x, id %x\n", reg, *pval);

    return ret;
}

/* @brief Dump a range of sensor registers. This funtions is used for debug purpose. 
 *
 * @param   i2c_base	sensor i2c master address
 * @param   start		start of sensor i2c regigter address
 * @param   end			end of sensor i2c regigter address
 */
static void mipi_sensor_regs_dump(uint32_t i2c_base, uint16_t start, uint16_t end)
{
    unsigned char data;
    unsigned short i = start;
    while (i <= end) {
        mipi_sensor_read_reg(i2c_base, i, &data);
        printf("reg@0x%04x:  0x%02x\n", i, data);
        i++;
    }
}


/* @brief Check mipi sensor id throught I2C interface.
 *
 * Only mipi ov5640 is support currently. So the expect mipi id is 5640.
 *
 * @param   i2c_base	sensor i2c master address
 */
static void mipi_sensor_id_check(uint32_t i2c_base)
{
    unsigned char data_high, data_low;
    char revchar;
    do {
        mipi_sensor_read_reg(i2c_base, 0x300b, &data_low);
        mipi_sensor_read_reg(i2c_base, 0x300a, &data_high);
        printf("The sensor chip id is 0x%04x\n", (data_high << 8) | data_low);
        if (((data_high << 8) | data_low) == 0x5640)
            break;
        printf("please re-connect the camera, now re-check? y for yes, n for no\n");

        do {
            revchar = getchar();
        } while (revchar == (uint8_t) 0xFF);

        if (revchar == 'n') {
            break;
        }
    } while (1);
}

/* @brief Download firmware mipi setting array into mipi sensor.
 *
 * @param   i2c_base	sensor i2c master address
 * @param	mipi_cam_fm	sensor mode register settings  
 */
static void mipi_sensor_load_firmware(uint32_t i2c_base, mipi_cam_mode_t * mipi_cam_fm)
{
    int i = 0;
    unsigned char val = 0;

    while (i < mipi_cam_fm->size) {
        mipi_sensor_write_reg(i2c_base,
                              (mipi_cam_fm->setting + i)->addr, (mipi_cam_fm->setting + i)->value);
        if ((mipi_cam_fm->setting + i)->delay_us)
            hal_delay_us((mipi_cam_fm->setting + i)->delay_us * 1000);
        if ((mipi_cam_fm->setting + i)->verify) {
            mipi_sensor_read_reg(i2c_base, (mipi_cam_fm->setting + i)->addr, &val);
            if ((mipi_cam_fm->setting + i)->value != val) {
                printf("Sensor configuation failed! expected 0x%x, actual 0x%x",
                       (mipi_cam_fm->setting + i)->value, val);
            }
        }

        i++;
    }
}

/*!
 * @brief Configure and initialize mipi camera sensor
 *
 * @param   i2c_base	sensor i2c master address
 */
static void mipi_sensor_config(uint32_t i2c_base)
{
    mipi_cam_mode_t *mipi_cam_fm = NULL;

    mipi_sensor_i2c_init(i2c_base, 170000);
    mipi_sensor_id_check(i2c_base);

    /*init mipi camera */
    mipi_cam_fm = &mipi_cam_modes[OV5640_MODE_VGA_640X480_30FPS_YUV422];
    mipi_sensor_load_firmware(i2c_base, mipi_cam_fm);

    printf("Download mipi sensor firmware done!\n");
}

/*!
 * @brief Turn mipi sensor into sleep mode through I2C
 *
 * @param   i2c_base	sensor i2c master address
 */
static void i2c2_sensor_off(uint32_t i2c_base)
{
    mipi_sensor_write_reg(i2c_base, 0x3008, 0x42);  //sleep;   
    mipi_sensor_write_reg(i2c_base, 0x3503, 0x7);
    mipi_sensor_write_reg(i2c_base, 0x483b, 0xff);  //sleep;
    mipi_sensor_write_reg(i2c_base, 0x3007, 0xf7);  //sleep;   

}

/*!
 * @brief Wake up mipi sensor through I2C
 *
 * @param   i2c_base	sensor i2c master address
 */
static void i2c2_sensor_on(uint32_t i2c_base)
{
    mipi_sensor_write_reg(i2c_base, 0x3008, 0x42);  //sleep;   
    mipi_sensor_write_reg(i2c_base, 0x3503, 0x7);
    mipi_sensor_write_reg(i2c_base, 0x483b, 0xff);  //sleep;
    mipi_sensor_write_reg(i2c_base, 0x3007, 0xf7);  //sleep;   
    mipi_sensor_write_reg(i2c_base, 0x3008, 0x02);
    mipi_sensor_write_reg(i2c_base, 0x3503, 0x0);
    mipi_sensor_write_reg(i2c_base, 0x483b, 0x33);  //mipi  reset;
    mipi_sensor_write_reg(i2c_base, 0x3007, 0xff);  //sleep;

}

/*!
 * @brief Set number of active data lanes for MIPI-CSI2 controller
 *
 * @param   lanes	number of active data lanes
 */
static int32_t mipi_csi2_set_lanes(uint32_t lanes)
{
    if (lanes > 4 || lanes < 1)
        return FALSE;
	BW_MIPI_CSI_N_LANES_N_LANES(lanes - 1);
    return TRUE;
}

/*!
 * @brief Setup MIPI-CSI2 controller.
 *
 * Read the PHY status register to confirm that the D-PHY is receiving a clock
 * on the D-PHY clock lane;
 *
 */
static void mipi_csi2_controller_program(void)
{
    //ov5640 support 2 lanes. (using lane 0 and lane 1)
    mipi_csi2_set_lanes(2);

    /*PHY loopback test */
	//{phy_testclk,phy_testclr} = {0,1}
	BW_MIPI_CSI_PHY_TST_CRTL0_PHY_TESTCLK(0);
	BW_MIPI_CSI_PHY_TST_CRTL0_PHY_TESTCLR(1);

	//{phy_testen,phy_testdout,phy_testdin}
	HW_MIPI_CSI_PHY_TST_CTRL1_CLR(
			BM_MIPI_CSI_PHY_TST_CTRL1_PHY_TESTEN |
			BM_MIPI_CSI_PHY_TST_CTRL1_PHY_TESTDOUT |
			BM_MIPI_CSI_PHY_TST_CTRL1_PHY_TESTDIN);

	//{phy_testclk,phy_testclr} = {0,1} --> {0,0}
	BW_MIPI_CSI_PHY_TST_CRTL0_PHY_TESTCLR(0);
	//{phy_testclk,phy_testclr} = {0,0} --> {1,0}
	BW_MIPI_CSI_PHY_TST_CRTL0_PHY_TESTCLK(1);

	//{phy_testen,phy_testdout,phy_testdin}
	BW_MIPI_CSI_PHY_TST_CTRL1_PHY_TESTDIN(0x44);
	BW_MIPI_CSI_PHY_TST_CTRL1_PHY_TESTEN(1);

	//{phy_testclk,phy_testclr} = {1,0} --> {0,0}
	BW_MIPI_CSI_PHY_TST_CRTL0_PHY_TESTCLK(0);

	//{phy_testen,phy_testdout,phy_testdin}
	BW_MIPI_CSI_PHY_TST_CTRL1_PHY_TESTEN(0);
	BW_MIPI_CSI_PHY_TST_CTRL1_PHY_TESTDIN(0x14);

	//{phy_testclk,phy_testclr} = {0,0} --> {1,0}
	BW_MIPI_CSI_PHY_TST_CRTL0_PHY_TESTCLK(1);

	//{phy_testclk,phy_testclr} = {1,0} --> {0,0}
	BW_MIPI_CSI_PHY_TST_CRTL0_PHY_TESTCLK(0);

    // raise phy shutdown
	BW_MIPI_CSI_PHY_SHUTDOWNZ_PHY_SHUTDOWNZ(1);

    //raise phy reset
	BW_MIPI_CSI_DPHY_RSTZ_DPHY_RSTZ(1);

    //raise csi2 reset
	BW_MIPI_CSI_CSI2_RESETN_CSI2_RESETN(1);
}

void mipi_csi2_config(void)
{
    int32_t timeout = 0x100000;

    /*D-PHY initialize */
    mipi_csi2_clock_set();
    mipi_cam_power_on();

    /*CSI2 controller program */
    mipi_csi2_controller_program();

    /*check if D-PHY is ready to receive: clock lane and data lane in stop state */
    timeout = 0x100000;
	while(HW_MIPI_CSI_PHY_STATE.B.PHY_RXULPSCLKNOT &&
		  HW_MIPI_CSI_PHY_STATE.B.PHY_STOPSTATEDATA_1 &&
		  HW_MIPI_CSI_PHY_STATE.B.PHY_STOPSTATEDATA_0) {
        if (timeout-- < 0) {
            printf("Waiting for PHY ready timeout!!\n");
            return;
        }
    }

    /*config mipi camera sensor */
    mipi_sensor_config(I2C2_BASE_ADDR);

    /*check if ddr clock is received */
    timeout = 0x100000;
	while(!HW_MIPI_CSI_PHY_STATE.B.PHY_RXCLKACTIVEHS) {
		if (timeout-- < 0) {
			printf("Waiting for DDR clock ready timeout!!\n");
			return;
		}
	}
}
