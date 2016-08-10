/*
 * Copyright (c) 2013-2015, Freescale Semiconductor, Inc.
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

#include "fxos_api.h"
#include "fxos_def.h"
#include "fsl_debug_console.h"
#include <stdio.h>

/*!
 * @brief Verify and initialize device: Hybrid mode with ODR=50Hz, Mag OSR=32, Acc OSR=Normal.
 *
 * @param[in]  dev - FXOS Device pointer to the communications interface.
 *
 * @return int32_t   True if all initializations are completed without.
 */

int32_t fxos_init(accel_dev_t *dev)
{
    uint8_t writeVal = RST_MASK;
    uint8_t tmp;
    uint32_t i;

    /* initialise device */
    PRINTF("Initializing FXOS...\r\n");

    /* reset part */
    PRINTF("Resetting FXOS...\r\n");
    accel_write_reg(dev, CTRL_REG2, writeVal);

    /* wait for a bit */
    for(i = 0; i < 0xFFFF; i++)
    {
        __asm("NOP");
    }

    /* setup auto sleep with FFMT trigger */
    /* go to standby */
    tmp = accel_read_reg(dev, CTRL_REG1);
    accel_write_reg(dev, CTRL_REG1, tmp & (uint8_t)~ACTIVE_MASK );

    /* Read again to make sure we are in standby mode. */
    tmp = accel_read_reg(dev, CTRL_REG1);
    if((tmp & ACTIVE_MASK) == ACTIVE_MASK)
    {
        PRINTF("Unable to move to Standby mode\n\n\r");
        return 1;
    }

    /* Disable the FIFO */
    accel_write_reg(dev, F_SETUP_REG, F_MODE_DISABLED);

#ifdef LPSLEEP_HIRES
    /* enable auto-sleep, low power in sleep, high res in wake */
    accel_write_reg(dev, CTRL_REG2, SLPE_MASK | SMOD_LOW_POWER | MOD_HIGH_RES);
#else
        /* enable auto-sleep, low power in sleep, high res in wake */
    accel_write_reg(dev, CTRL_REG2, MOD_HIGH_RES);
#endif

    /* set up Mag OSR and Hybrid mode using M_CTRL_REG1, use default for Acc */
    accel_write_reg(dev, M_CTRL_REG1, (M_RST_MASK | M_OSR_MASK | M_HMS_MASK));

    /* Enable hyrid mode auto increment using M_CTRL_REG2 */
    accel_write_reg(dev, M_CTRL_REG2, (M_HYB_AUTOINC_MASK));

#ifdef EN_FFMT
    /* enable FFMT for motion detect for X and Y axes, latch enable */
    accel_write_reg(dev, FF_MT_CFG_REG, XEFE_MASK | YEFE_MASK | ELE_MASK | OAE_MASK);
#endif

#ifdef SET_THRESHOLD
    /* set threshold to about 0.25g */
    accel_write_reg(dev, FT_MT_THS_REG, 0x04);
#endif

#ifdef SET_DEBOUNCE
    /* set debounce to zero */
    accel_write_reg(dev, FF_MT_COUNT_REG, 0x00);
#endif

#ifdef EN_AUTO_SLEEP
    /* set auto-sleep wait period to 5s (=5/0.64=~8) */
    accel_write_reg(dev, ASLP_COUNT_REG, 8);
#endif
    /* default set to 4g mode */
        accel_write_reg(dev, XYZ_DATA_CFG_REG, FULL_SCALE_4G);
#ifdef EN_INTERRUPTS
    /* enable data-ready, auto-sleep and motion detection interrupts */
    /* FXOS1_WriteRegister(CTRL_REG4, INT_EN_DRDY_MASK | INT_EN_ASLP_MASK | INT_EN_FF_MT_MASK); */
    accel_write_reg(dev, CTRL_REG4, 0x0);

    /* route data-ready interrupts to INT1, others INT2 (default) */
    accel_write_reg(dev, CTRL_REG5, INT_CFG_DRDY_MASK);

    /* enable ffmt as a wake-up source */
    accel_write_reg(dev, CTRL_REG3, WAKE_FF_MT_MASK);

    /* finally activate device with ASLP ODR=0.8Hz, ODR=100Hz, FSR=2g */
    accel_write_reg(dev, CTRL_REG1,
                        HYB_ASLP_RATE_0_8HZ | HYB_DATA_RATE_100HZ | ACTIVE_MASK);

#else
        // Setup the ODR for 50 Hz and activate the accelerometer
        accel_write_reg(dev, CTRL_REG1, (HYB_DATA_RATE_200HZ | ACTIVE_MASK));
#endif

    /* Read Control register again to ensure we are in active mode */
    tmp = accel_read_reg(dev, CTRL_REG1);
    if((tmp & ACTIVE_MASK) != ACTIVE_MASK)
    {
        PRINTF("Unable to move to Active mode\n\n\r");
        return 1;
    }

    return 0;
}

/*!
 * @brief Read data from sensors, assumes hyb_autoinc_mode is set in M_CTRL_REG2
 *
 * @param[in]  dev - FXOS Device pointer to the communications interface.
 * @param[in] sensorData_t* sensorData    pointer to the buffer to hold sensor data
 *
 * @return     Init successfully or not.
 */
int32_t fxos_read_sensor_data(const accel_dev_t *dev, accel_sensor_data_t *sensorData)
{
    /* Read array of 12 bytes beginning from OUT_X_MSB_REG */
    return fxos_read_register_array_fast(dev, OUT_X_MSB_REG, (uint8_t *)sensorData, 12u);
}

/*!
 * @brief Read data from sensors, assumes hyb_autoinc_mode is set in M_CTRL_REG2
 * and the fast-read mode is set in CTRL_REG1
 *
 * @param[in]  dev - FXOS Device pointer to the communications interface.
 * @param[in] sensorData_t* sensorData    pointer to the buffer to hold sensor data
 *
 * @return     Init successfully or not.
 */
uint8_t fxos_read_sensor_data_fast(const accel_dev_t *dev, accel_sensor_data_t *sensorData)
{
    uint8_t buf[6];

    /* Read array of 6 bytes beginning from OUT_X_MSB_REG */
    if (fxos_read_register_array_fast(dev, OUT_X_MSB_REG, buf, 6u))
    {
        return 1;
    }
    else
    {
        /* Populate real data */
        sensorData->fxos_data.accelXMSB = buf[0];
        sensorData->fxos_data.accelYMSB = buf[1];
        sensorData->fxos_data.accelZMSB = buf[2];
        sensorData->fxos_data.magXMSB   = buf[3];
        sensorData->fxos_data.magYMSB   = buf[4];
        sensorData->fxos_data.magZMSB   = buf[5];

        /* Pad LSBs with 0s as we just did a fast read */
        sensorData->fxos_data.accelXLSB = 0;
        sensorData->fxos_data.accelYLSB = 0;
        sensorData->fxos_data.accelZLSB = 0;
        sensorData->fxos_data.magXLSB   = 0;
        sensorData->fxos_data.magYLSB   = 0;
        sensorData->fxos_data.magZLSB   = 0;

        /* Return successful transaction */
        return 0;
    }
}

/*!
 * @brief Read an array of registers
 *
 * @param[in]  dev - FXOS Device pointer to the communications interface.
 * @param[in]  uint8_t  startRegAddr    Address of the device register to start reading from
 * @param[out] uint8_t* readBuf         Read buffer to read the data into, pass in by reference
 * @param[in]  uint8_t  len             Number of registers to be read
 *
* @return     uint8_t Return 1 if successful, 0 if an error occurred.
*/
uint8_t fxos_read_register_array(const accel_dev_t *dev, uint8_t startRegAddr, uint8_t *readBuf, uint8_t len)
{
    int32_t i = 0;

    for (i = 0; i < len; i ++)
    {
        readBuf[i] = accel_read_reg(dev, startRegAddr + i);
        if (readBuf[i] < 0)
        {
            PRINTF("Read reg failed @0x%x\r\n", (unsigned int)(startRegAddr + i));
            return 1;
        }
    }

    return 0;
}

/*!
 * @brief Read an array of registers
 *
 * @param[in]  uint8_t  startRegAddr    Address of the device register to start reading from
 * @param[out] uint8_t* readBuf         Read buffer to read the data into, pass in by reference
 * @param[in]  uint8_t  len             Number of registers to be read
 *
* @return     uint8_t Return 1 if successful, 0 if an error occurred.
*/
uint8_t fxos_read_register_array_fast(const accel_dev_t *dev, uint8_t startRegAddr, uint8_t *readBuf, uint8_t len)
{

    if (dev->i2c->i2c_read(dev->bus, &dev->slave, &startRegAddr, 1,
                   readBuf, len, 200) == kStatus_I2C_Success)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

