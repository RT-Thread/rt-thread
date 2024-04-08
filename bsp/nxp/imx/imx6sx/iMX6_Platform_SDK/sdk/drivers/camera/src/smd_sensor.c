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
 * @file smd_sensor.c
 * @brief common functions for sensor on smd.
 * @ingroup diag_camera
 */

#include "camera/camera_def.h"

reg_param_t ov5642_strobe_on[] = {
    {0x3004, 0xff, 0, 0, 0},
    {0x3016, 0x02, 0, 0, 0},
    {0x3B00, 0x8c, 0, 0, }
};

extern void audio_codec_power_on (void);
/*!
 * @brief initialize the i2c module for camera sensor -- mainly enable the i2c clock, module itself and the i2c clock prescaler.
 *
 * @param   base        base address of i2c module (also assigned for i2cx_clk)
 * @param   baud        the desired data rate in bps
 *
 * @return  0 if successful; non-zero otherwise
 */
static int32_t sensor_i2c_init(uint32_t base, uint32_t baud)
{
    int32_t ret = 0;
    int32_t i2c_delay = 5000;

    ret = i2c_init(base, baud);
    if (ret != 0) {
        printf("I2C initialization failed!\n");
        return ret;
    }
    hal_delay_us(i2c_delay);

    return ret;
}

/*!
 * @brief Perform I2C write operation for camera sensor
 *
 * @param   dev_addr	sensor i2c slave device address
 * @param   reg_addr 	sensor i2c register address
 * @param	pval 		value write to i2c register
 * @param	is_16bits	indicate value write to i2c register is 16 bits
 *
 * @return  0 if successful; non-zero otherwise
 */
static int32_t sensor_write_reg(uint32_t dev_addr, uint16_t reg_addr, uint16_t * pval,
                                uint16_t is_16bits)
{
    int32_t ret = 0;
    struct imx_i2c_request rq = {0};

    reg_addr = ((reg_addr & 0x00FF) << 8) | ((reg_addr & 0xFF00) >> 8); //swap MSB and LSB
    rq.ctl_addr = g_camera_i2c_port;
    rq.dev_addr = dev_addr >> 1;
    rq.reg_addr = reg_addr;
    rq.reg_addr_sz = 2;

    if (is_16bits == 0) {
        uint8_t value = *pval;
        rq.buffer_sz = 1;
        rq.buffer = &value;
        ret = i2c_xfer(&rq, I2C_WRITE);
    } else {
        uint8_t value[2];
        value[0] = ((*pval) & 0xFF00) >> 8;
        value[1] = (*pval) & 0x00FF;
        rq.buffer_sz = 2;
        rq.buffer = value;
        ret = i2c_xfer(&rq, I2C_WRITE);
    }

    return ret;
}

/*!
 * @brief Perform I2C read operation for camera sensor
 *
 * @param   dev_addr	sensor i2c slave device address
 * @param   reg_addr 	sensor i2c register address
 * @param	pval 		value read from i2c register
 * @param	is_16bits	indicate value read from i2c register is 16 bits
 *
 * @return  0 if successful; non-zero otherwise
 */
static int32_t sensor_read_reg(uint32_t dev_addr, uint16_t reg_addr, uint16_t * pval,
                               uint16_t is_16bits)
{
    int32_t ret = 0;
    struct imx_i2c_request rq = {0};

    reg_addr = ((reg_addr & 0x00FF) << 8) | ((reg_addr & 0xFF00) >> 8); //swap MSB and LSB
    rq.ctl_addr = g_camera_i2c_port;
    rq.dev_addr = dev_addr >> 1;
    rq.reg_addr = reg_addr;
    rq.reg_addr_sz = 2;

    if (is_16bits == 0) {
        uint8_t value = *pval;
        rq.buffer_sz = 1;
        rq.buffer = &value;
        ret = i2c_xfer(&rq, I2C_READ);
        *pval = value;
    } else {
        uint8_t value[2];
        rq.buffer_sz = 2;
        rq.buffer = value;
        ret = i2c_xfer(&rq, I2C_READ);
        *pval = (value[0] << 8) | (value[1]);
    }

    return ret;
}


int32_t sensor_config(camera_profile_t * sensor)
{
    int32_t ret = 0;

#if defined(CHIP_MX6SL)
    csi_iomux_config();   //config csi port
#else
	csi_port0_iomux_config();
#endif
    ret = sensor_init(sensor);

    return ret;
}

camera_profile_t *sensor_search(void)
{
    int32_t i, j;
    uint16_t read_value, error;
    camera_profile_t *sensor_on;

    camera_power_on();
    /* For some mx6sdl board, if audio isn't power_en, the i2c voltage is 1.2V,
     * I2C will lost arbitration.
     * Add fix here, by open audio power_en
     */
    audio_codec_power_on();

    sensor_reset();
    sensor_clock_setting();
    sensor_i2c_init(g_camera_i2c_port, 170000);

    for (i = 0; i < SENSOR_NUM; i++) {
        error = 0;
        sensor_on = &g_camera_profiles[i];
		hal_delay_us(10000);

        for (j = 0; j < sensor_on->sensor_detection_size; ++j) {
            reg_param_t *setting = &sensor_on->sensor_detection[j];
            sensor_read_reg(sensor_on->i2c_dev_addr, setting->addr, &read_value,
                            setting->is_16bits);
            if (setting->delay_ms != 0)
                hal_delay_us(setting->delay_ms * 1000);
            if (read_value != setting->value) {
                //printf("read_value %08x.Setting value %08x\n", read_value, setting->value);
                error = 1;
                break;
            }
        }
        if (error == 0) {
            printf("Sensor %s detected.\n", sensor_on->sensor_name);
            break;
        }
    }

    if (i == SENSOR_NUM) {
        printf("No valid sensor can be found.\n");
        return NULL;
    }

    return sensor_on;
}

int32_t sensor_init(camera_profile_t * sensor)
{
    int32_t i;
    uint16_t read_value;
	int32_t ret = 0;

    ret = sensor_i2c_init(g_camera_i2c_port, 170000);
    camera_mode_t *preview_mode = &sensor->modes[sensor->mode_id];

    for (i = 0; i < preview_mode->size; ++i) {
        reg_param_t *setting = &preview_mode->setting[i];
        sensor_write_reg(sensor->i2c_dev_addr, setting->addr, &setting->value, setting->is_16bits);
        if (setting->delay_ms != 0)
            hal_delay_us(setting->delay_ms * 1000);

        if (setting->verify) {
            sensor_read_reg(sensor->i2c_dev_addr, setting->addr, &read_value, setting->is_16bits);
            if (read_value != setting->value) {
                printf("reg[0x%x]=0x%x, but expected=0x%x\n", setting->addr, read_value,
                       setting->value);
				return -1;
            } else {
                //printf ("I2C RIGHT: [reg 0x%x], real = 0x%x, expected = 0x%x\n", regAddr, tmpVal, regVal);
            }
        }
    }

    return ret;
}

int32_t sensor_af_trigger(camera_profile_t * sensor)
{
    int32_t ret = 0, i;
    reg_param_t *setting;

    ret = sensor_i2c_init(g_camera_i2c_port, 170000);

    for (i = 0; i < sensor->af_trigger_size; ++i) {
        setting = &sensor->af_trigger[i];
        sensor_write_reg(sensor->i2c_dev_addr, setting->addr, &setting->value, setting->is_16bits);
        if (setting->delay_ms != 0)
            hal_delay_us(setting->delay_ms * 1000);
    }

    return ret;
}

int32_t sensor_autofocus_init(camera_profile_t * sensor)
{
    int32_t ret = 0, i;
    uint16_t read_value;

    if (sensor->auto_focus_enable) {
        printf("Download auto-focus firmware......\n");

        ret = sensor_i2c_init(g_camera_i2c_port, 170000);

        for (i = 0; i < sensor->af_firmware_size; ++i) {
            reg_param_t *setting = &sensor->af_firmware[i];
            sensor_write_reg(sensor->i2c_dev_addr, setting->addr, &setting->value,
                             setting->is_16bits);
            if (setting->delay_ms != 0)
                hal_delay_us(setting->delay_ms * 1000);

            if (setting->verify) {
                sensor_read_reg(sensor->i2c_dev_addr, setting->addr, &read_value,
                                setting->is_16bits);
                if (read_value != setting->value) {
                    printf("reg[0x%x]=0x%x, but expected=0x%x\n", setting->addr, read_value,
                           setting->value);
					return -1;
                } else {
                    //printf ("I2C RIGHT: [reg 0x%x], real = 0x%x, expected = 0x%x\n", regAddr, tmpVal, regVal);
                }
            }
        }
        printf("Auto-focus ready\n");
    }

    return ret;
}

int camera_strobeflash_on(uint32_t i2cbase)
{
    int ret, i;
    reg_param_t *setting;

    sensor_i2c_init(i2cbase, 170000);

    for (i = 0; i < ARRAY_SIZE(ov5642_strobe_on); i++) {
       setting = &ov5642_strobe_on[i];
        ret = sensor_write_reg(i2cbase, setting->addr, &setting->value, setting->is_16bits);
        if (ret != 0) {
            printf("I2C write error.\n");
            return ret;
        }
        if (setting->delay_ms != 0)
            hal_delay_us(setting->delay_ms * 1000);
    }

    return ret;
}

int camera_strobeflash_off(uint32_t i2cbase)
{
    int ret = 0;

    sensor_i2c_init(i2cbase, 170000);

    ret = sensor_write_reg(i2cbase, 0x3B00, 0x00, 0);
    if (ret != 0) {
        printf("I2C write error.\n");
        return ret;
    }

    return ret;
}

