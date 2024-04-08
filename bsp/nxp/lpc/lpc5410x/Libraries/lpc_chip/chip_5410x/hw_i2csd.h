/*
 * @brief I2C slave ROM API declarations and functions
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2014
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#ifndef __HW_I2CSD_H
#define __HW_I2CSD_H

#include "error.h"
#include "hw_i2csd_rom_api.h"

// *** I2C functions called by Application Program ***
uint32_t i2cs_get_mem_size(void);

ROM_I2CS_HANDLE_T i2cs_init(void *mem, const ROM_I2CS_INIT_T *pInit);

void i2cs_setup_slave(ROM_I2CS_HANDLE_T pHandle, ROM_I2CS_SLAVE_T *pSlaveSetup);

void i2cs_register_callback(ROM_I2CS_HANDLE_T pHandle, uint32_t cbIndex, void *pCB);

ErrorCode_t i2cs_transfer(ROM_I2CS_HANDLE_T pHandle, ROM_I2CS_XFER_T *pXfer);

void i2cs_transfer_handler(ROM_I2CS_HANDLE_T pHandle);

uint32_t i2cs_get_driver_version(void);

// ***

#endif /* __HW_I2CSD_H */
