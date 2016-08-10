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

#ifndef __FSL_FXOS_8700_DRIVER_H__
#define __FSL_FXOS_8700_DRIVER_H__

#include "fsl_i2c_master_driver.h"

/*!
 * @addtogroup fxos8700
 * @{
 */

/*! @file */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief FXOS8700 I2C address. */
#ifndef FXOS8700_I2C_ADDR
#define FXOS8700_I2C_ADDR 0x1D
#endif
#define FXOS8700_I2C_BAUDRATE 100
#define FXOS8700_I2C_TIMEOUT_MS 100

/*
 * Field Definitions.
 */

/*! @brief fxos8700 output data rate selection. */
typedef enum _fxos_ODR_selection
{
    kFxosODR0 = 0x0,
    kFxosODR1 = 0x1,
    kFxosODR2 = 0x2,
    kFxosODR3 = 0x3,
    kFxosODR4 = 0x4,
    kFxosODR5 = 0x5,
    kFxosODR6 = 0x6,
    kFxosODR7 = 0x7
} fxos_odr_selection_t;

/*! @brief fxos8700 oversample ratio selection. */
typedef enum _fxos_OSR_cfg
{
    kFxosOSR0 = 0x0,
    kFxosOSR1 = 0x1,
    kFxosOSR2 = 0x2,
    kFxosOSR3 = 0x3,
    kFxosOSR4 = 0x4,
    kFxosOSR5 = 0x5,
    kFxosOSR6 = 0x6,
    kFxosOSR7 = 0x7
} fxos_osr_cfg_t;

/*! @brief fxos8700 accelerometer/magnetometer selection. */
typedef enum _fxos_HMS_cfg_
{
    kFxosAccelerometerOnly = 0x0, /*!< accelerometer only */
    kFxosMagnetometerOnly = 0x1,  /*!< magnetometer only */
    kFxosBoth = 0x2               /*!< select both accelerometer and magnetometer */
} fxos_hms_cfg_t;


/*! @brief fxos accelerometer full-scale range */
typedef enum _fxos_data_cfg_
{
    kFxos2gMode = 0x0, /*!< 2g mode */
    kFxos4gMode = 0x1, /*!< 4g mode */
    kFxos8gMode = 0x2  /*!< 8g mode */
} fxos_data_cfg_t;

/*! @brief fxos8700 return status. */
typedef enum _fxos8700_status
{
    kStatus_FXOS_Success = 0x0, /*!< success */
    kStatus_FXOS_I2CFail = 0x1, /*!< I2C failure */
    kStatus_FXOS_Fail = 0x2     /*!< fail */
} fxos_status_t;

/*! @brief fxos configure definition. */
typedef struct fxos_handler
{
    /* I2C revelant definition. */
    uint32_t i2cInstance; /*!< I2C instance. */
    i2c_device_t device; /*!< I2C device setting */
    i2c_master_state_t state; /*!< I2C intenal state space. */
} fxos_handler_t;

/*! @brief Initailize structure of fxos8700 */
typedef struct fxos_init
{
    fxos_odr_selection_t odr; /*!< Output data rate selection */
    fxos_osr_cfg_t osr;       /*!< Over sample ratio selection */
    fxos_hms_cfg_t hms;       /*!< Accelerometer/Magnetometer selection */
    fxos_data_cfg_t range;    /*!< Accelerometer full scale range selection */
} fxos_init_t;

/*! @brief fxos accelerometer and magnetometer data struct */
typedef struct fxos_data
{
    uint8_t accelXMSB;
    uint8_t accelXLSB;
    uint8_t accelYMSB;
    uint8_t accelYLSB;
    uint8_t accelZMSB;
    uint8_t accelZLSB;
    uint8_t magXMSB;
    uint8_t magXLSB;
    uint8_t magYMSB;
    uint8_t magYLSB;
    uint8_t magZMSB;
    uint8_t magZLSB;
} fxos_data_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief fxos8700 initialize function.
 *
 * This function would call fxos_i2c_init(), and in this function, some configurations
 * are fixed. The second parameter is NULL to fxos8700 in this version. If users want
 * to change the settings, they have to use fxos_write_reg() or fxos_modify_reg()
 * to set the register value of fxos8700.
 * Note: If the fxos_config is NULL, it would initialize fxos8700 using default settings.
 * The default setting:
 * fxos_config->odr = kFxosODR1,
 * fxos_config->osr = kFxosOSR7,
 * fxos_config->hms = kFxosBoth,
 * fxos_config->range = kFxos4gMode,
 * @param handler fxos8700 handler structure.
 * @param fxos_config fxos8700 configuration structure.
 */
fxos_status_t FXOS_Init(fxos_handler_t *handler, const fxos_init_t *fxos_config);

/*!
 * @brief Deinit the fxos8700 codec. Mainly used to close the I2C controller.
 * @param handler fxos8700 handler structure pointer.
 */
fxos_status_t FXOS_Deinit(fxos_handler_t *handler);

/*!
 * @brief Write register to fxos using I2C.
 * @param handler fxos8700 handler structure.
 * @param reg The register address in fxos.
 * @param val Value needs to write into the register.
 */
fxos_status_t FXOS_WriteReg(fxos_handler_t *handler, uint8_t reg, uint8_t val);

/*!
 * @brief Read register from fxos using I2C.
 * @param handler fxos8700 handler structure.
 * @param reg The register address in fxos.
 * @param val Value written to.
 */
fxos_status_t FXOS_ReadReg(fxos_handler_t * handler, uint8_t reg, uint8_t *val);

/*!
 * @brief Modify some bits in the register using I2C.
 * @param handler fxos8700 handler structure.
 * @param reg The register address in fxos.
 * @param clr_mask The mask code for the bits want to write. The bit you want to write should be 0.
 * @param val Value needs to write into the register.
 */
fxos_status_t FXOS_ModifyReg(fxos_handler_t * handler, uint8_t reg,  uint8_t clr_mask, uint8_t val);

/*!
 * @brief Read sensor data from fxos using I2C
 * @param handler fxos8700 handler structure.
 * @param val Sensor data read from fxos.
 */
fxos_status_t FXOS_ReadData(fxos_handler_t * handler, fxos_data_t *val);

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif/* __FSL_FXOS_8700_DRIVER_H__ */

/*******************************************************************************
 * API
 ******************************************************************************/

