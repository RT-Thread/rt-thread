/*
 * Copyright (c) 2014, Freescale Semiconductor, Inc.
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
#include "fxos_def.h"
#include "fsl_fxos8700_driver.h"

/*******************************************************************************
 *Code
 ******************************************************************************/
 static volatile uint32_t i2c_state = 0;
 static fxos_status_t FXOS_I2CInit(fxos_handler_t *handler);

/*FUNCTION**********************************************************************
 *
 * Function Name : FXOS_Init
 * Description   : Initialize the fxos8700 board.
 * This function has configured the fxos8700 board. If the codec_config is NULL,
 * use default setting.
 *END**************************************************************************/
fxos_status_t FXOS_Init(fxos_handler_t *handler, const fxos_init_t *fxos_config)
{
    if(i2c_state == 0)
    {
        FXOS_I2CInit(handler);
        i2c_state ++;
    }
    else
    {
        return kStatus_FXOS_Fail;
    }

    /* NULL pointer means default setting. */
    if(fxos_config == NULL)
    {
        /* Reset Device */
        FXOS_WriteReg(handler, CTRL_REG2, RST_MASK);

        /* wait for a bit */
        OSA_TimeDelay(500); /* 50ms */

        /* go to standby */
        FXOS_ModifyReg(handler, CTRL_REG1, ACTIVE_MASK, ~ACTIVE_MASK);

        /* set up Mag OSR and Hybrid mode using M_CTRL_REG1 */
        FXOS_WriteReg(handler, M_CTRL_REG1, (M_RST_MASK | M_OSR_MASK | M_HMS_MASK));

        /* Enable hyrid mode auto increment using M_CTRL_REG2 */
        FXOS_WriteReg(handler, M_CTRL_REG2, (M_HYB_AUTOINC_MASK));

        /* default set to 4g mode */
        FXOS_WriteReg(handler, XYZ_DATA_CFG_REG, FULL_SCALE_4G);

        /* Setup the ODR for 200 Hz and activate the accelerometer */
        FXOS_WriteReg(handler, CTRL_REG1, (LNOISE_MASK | HYB_DATA_RATE_200HZ | ACTIVE_MASK));
    }
    else
    {
        /* config fxos8700 according to fxos_config */
	if ((fxos_config->odr <= kFxosODR7) && (fxos_config->odr >= kFxosODR0))
	{
            FXOS_ModifyReg(handler, CTRL_REG1, DR_MASK, fxos_config->odr);
	}
	else
	{
	    return kStatus_FXOS_Fail;
	}

	if ((fxos_config->osr <= kFxosOSR7) && (fxos_config->osr >= kFxosOSR0))
	{
            FXOS_ModifyReg(handler, M_CTRL_REG1, M_OSR_MASK, fxos_config->osr);
	}
	else
	{
	    return kStatus_FXOS_Fail;
	}

	if ((fxos_config->hms <= kFxosBoth) && (fxos_config->hms >= kFxosAccelerometerOnly))
	{
            FXOS_ModifyReg(handler, M_CTRL_REG1, M_HMS_MASK, fxos_config->hms);
	}
	else
	{
	    return kStatus_FXOS_Fail;
	}

	if ((fxos_config->range <= kFxos8gMode) &&(fxos_config->range >= kFxos2gMode))
	{
            FXOS_ModifyReg(handler, XYZ_DATA_CFG_REG, FS_MASK, fxos_config->range);
        }
	else
	{
	    return kStatus_FXOS_Fail;
        }
        /* activate fxos8700 */
        FXOS_ModifyReg(handler, CTRL_REG1, ACTIVE_MASK, ACTIVE_MASK);
    }
    return kStatus_FXOS_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FXOS_I2CInit
 * Description   : Initialize the I2C transfer.
 * The fxos8700 codec is controlled by I2C, using I2C transfer can access the fxos register.
 *END**************************************************************************/
static fxos_status_t FXOS_I2CInit(fxos_handler_t *handler)
{
    /* The master structure initialize */
    I2C_DRV_MasterInit(handler->i2cInstance, &handler->state);
    /* Configure the device info of I2C */
    handler->device.baudRate_kbps = FXOS8700_I2C_BAUDRATE;
    handler->device.address = FXOS8700_I2C_ADDR;
    I2C_DRV_MasterSetBaudRate(handler->i2cInstance, &handler->device);
    return kStatus_FXOS_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FXOS_Deinit
 * Description   : Deinit the fxos8700 board.
 * This function would free the i2c source applied.
 *END**************************************************************************/
fxos_status_t FXOS_Deinit(fxos_handler_t *handler)
{
    i2c_state --;
    if(i2c_state == 0)
    {
        I2C_DRV_MasterDeinit(handler->i2cInstance);
    }
    return kStatus_FXOS_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FXOS_WriteReg
 * Description   : Write the specified register of fxos8700.
 * The writing process is through I2C.
 *END**************************************************************************/
fxos_status_t FXOS_WriteReg(fxos_handler_t *handler, uint8_t reg, uint8_t val)
{
    i2c_device_t *device = &(handler->device);
    uint8_t cmd[1],buff[1];
    uint8_t retval = 0;
    /* The register address */
    cmd[0] = reg;
    /* Data */
    buff[0] = val;
    retval = I2C_DRV_MasterSendDataBlocking(handler->i2cInstance,device,cmd,1,buff,1,FXOS8700_I2C_TIMEOUT_MS);
    if(retval != kStatus_I2C_Success)
    {
        return kStatus_FXOS_I2CFail;
    }
    return kStatus_FXOS_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FXOS_ReadReg
 * Description   : Read the specified register value of fxos8700.
 * The reading process is through I2C.
 *END**************************************************************************/
fxos_status_t FXOS_ReadReg(fxos_handler_t *handler, uint8_t reg, uint8_t *val)
{
    i2c_device_t *device = &(handler->device);
    uint8_t buff[1];
    uint8_t data[1];
    uint8_t retval = 0;
    buff[0] = reg;
    retval = I2C_DRV_MasterReceiveDataBlocking(handler->i2cInstance,device,buff,1,data,1,FXOS8700_I2C_TIMEOUT_MS);
    if(retval != kStatus_I2C_Success)
    {
        return kStatus_FXOS_I2CFail;
    }
    *val = data[0];
    return kStatus_FXOS_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FXOS_ModifyReg
 * Description   : Modify the specified register value of fxos8700.
 * The modify process is through I2C.
 *END**************************************************************************/
fxos_status_t FXOS_ModifyReg(fxos_handler_t *handler, uint8_t reg, uint8_t clr_mask, uint8_t val)
{
    uint8_t retval = 0;
    uint8_t reg_val;
    retval = FXOS_ReadReg(handler, reg, &reg_val);
    if(retval != kStatus_FXOS_Success)
    {
        return kStatus_FXOS_Fail;
    }
    reg_val &= clr_mask;
    reg_val |= val;
    retval = FXOS_WriteReg(handler, reg, reg_val);
    if(retval != kStatus_FXOS_Success)
    {
        return kStatus_FXOS_Fail;
    }
    return kStatus_FXOS_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FXOS_ReadData
 * Description   : Read sensor data value from fxos8700.
 * The reading process is through I2C.
 *END**************************************************************************/
fxos_status_t FXOS_ReadData(fxos_handler_t *handler, fxos_data_t *val)
{
    i2c_device_t *device = &(handler->device);
    uint8_t buff[1];
    uint8_t retval = 0;
    buff[0] = OUT_X_MSB_REG;
    retval = I2C_DRV_MasterReceiveDataBlocking(handler->i2cInstance,device,buff,1,(uint8_t *)val,12,FXOS8700_I2C_TIMEOUT_MS);
    if(retval != kStatus_I2C_Success)
    {
        return kStatus_FXOS_I2CFail;
    }
    return kStatus_FXOS_Success;
}
/*******************************************************************************
 *EOF
 ******************************************************************************/

