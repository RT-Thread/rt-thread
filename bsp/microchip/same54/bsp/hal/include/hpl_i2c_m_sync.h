/**
 * \file
 *
 * \brief I2C Master Hardware Proxy Layer(HPL) declaration.
 *
 * Copyright (c) 2014-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */
#ifndef _HPL_I2C_M_SYNC_H_INCLUDED
#define _HPL_I2C_M_SYNC_H_INCLUDED

#include <compiler.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief i2c flags
 */
#define I2C_M_RD 0x0001 /* read data, from slave to master */
#define I2C_M_BUSY 0x0100
#define I2C_M_TEN 0x0400   /* this is a ten bit chip address */
#define I2C_M_SEVEN 0x0800 /* this is a seven bit chip address */
#define I2C_M_FAIL 0x1000
#define I2C_M_STOP 0x8000 /* if I2C_FUNC_PROTOCOL_MANGLING */

/**
 * \brief i2c Return codes
 */
#define I2C_OK 0                     /* Operation successful */
#define I2C_ACK -1                   /* Received ACK from device on I2C bus */
#define I2C_NACK -2                  /* Received NACK from device on I2C bus */
#define I2C_ERR_ARBLOST -3           /* Arbitration lost */
#define I2C_ERR_BAD_ADDRESS -4       /* Bad address */
#define I2C_ERR_BUS -5               /* Bus error */
#define I2C_ERR_BUSY -6              /* Device busy */
#define I2c_ERR_PACKAGE_COLLISION -7 /* Package collision */

/**
 * \brief i2c I2C Modes
 */
#define I2C_STANDARD_MODE 0x00
#define I2C_FASTMODE 0x01
#define I2C_HIGHSPEED_MODE 0x02

/**
 * \brief i2c master message structure
 */
struct _i2c_m_msg {
	uint16_t          addr;
	volatile uint16_t flags;
	int32_t           len;
	uint8_t *         buffer;
};

/**
 * \brief i2c master service
 */
struct _i2c_m_service {
	struct _i2c_m_msg msg;
	uint16_t          mode;
	uint16_t          trise;
};

/**
 * \brief i2c sync master device structure
 */
struct _i2c_m_sync_device {
	struct _i2c_m_service service;
	void *                hw;
};

/**
 * \name HPL functions
 */

/**
 * \brief Initialize I2C
 *
 * This function does low level I2C configuration.
 *
 * \param[in] i2c_dev The pointer to i2c device structure
 * \param[in] hw The pointer to hardware instance
 *
 * \return Return 0 for success and negative value for error
 */
int32_t _i2c_m_sync_init(struct _i2c_m_sync_device *const i2c_dev, void *const hw);

/**
 * \brief Deinitialize I2C
 *
 * \param[in] i2c_dev The pointer to i2c device structure
 *
 * \return Return 0 for success and negative value for error
 */
int32_t _i2c_m_sync_deinit(struct _i2c_m_sync_device *const i2c_dev);

/**
 * \brief Enable I2C module
 *
 * This function does low level I2C enable.
 *
 * \param[in] i2c_dev The pointer to i2c device structure
 *
 * \return Return 0 for success and negative value for error
 */
int32_t _i2c_m_sync_enable(struct _i2c_m_sync_device *const i2c_dev);

/**
 * \brief Disable I2C module
 *
 * This function does low level I2C disable.
 *
 * \param[in] i2c_dev The pointer to i2c device structure
 *
 * \return Return 0 for success and negative value for error
 */
int32_t _i2c_m_sync_disable(struct _i2c_m_sync_device *const i2c_dev);

/**
 * \brief Transfer data by I2C
 *
 * This function does low level I2C data transfer.
 *
 * \param[in] i2c_dev The pointer to i2c device structure
 * \param[in] msg The pointer to i2c msg structure
 *
 * \return Return 0 for success and negative value for error
 */
int32_t _i2c_m_sync_transfer(struct _i2c_m_sync_device *const i2c_dev, struct _i2c_m_msg *msg);

/**
 * \brief Set baud rate of I2C
 *
 * This function does low level I2C set baud rate.
 *
 * \param[in] i2c_dev The pointer to i2c device structure
 * \param[in] clkrate The clock rate(KHz) input to i2c module
 * \param[in] baudrate The demand baud rate(KHz) of i2c module
 *
 * \return Return 0 for success and negative value for error
 */
int32_t _i2c_m_sync_set_baudrate(struct _i2c_m_sync_device *const i2c_dev, uint32_t clkrate, uint32_t baudrate);

/**
 * \brief Send send condition on the I2C bus
 *
 * This function will generate a stop condition on the I2C bus
 *
 * \param[in] i2c_dev The pointer to i2c device struct
 *
 * \return Return 0 for success and negative value for error
 */
int32_t _i2c_m_sync_send_stop(struct _i2c_m_sync_device *const i2c_dev);

#ifdef __cplusplus
}
#endif

#endif
