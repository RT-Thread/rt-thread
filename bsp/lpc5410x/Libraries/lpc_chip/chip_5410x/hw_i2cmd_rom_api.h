/*
 * @brief I2C master ROM API declarations and functions
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

#ifndef __HW_I2CMD_ROM_API_H
#define __HW_I2CMD_ROM_API_H

#include "stdint.h"		// added to define uint32_t, etc.
#include "error.h"
#include "packing.h"
#include "hw_i2c_common.h"

/** @defgroup ROMAPI_I2CM I2C master ROM driver functions and definitions
 * @ingroup ROMAPI_I2CM_WRAPPER
 * @{
 */

/** @brief I2C master handle type */
typedef void *ROM_I2CM_HANDLE_T;

/** @brief User context conversion macro
 * Macro used to extract the user defined data pointer from a I2C master
 * handle context.<br>
 * To get a user context, simple use the macro on the drivers handle:
 * void *pUserData = (void *) ROM_I2CM_HANDLE_TOUDATA(driverHandle);
 */
#define ROM_I2CM_HANDLE_TOUDATA(p)          (void *) (*(uint32_t *) p)

/** @brief I2C master optional transfer flags */
#define ROM_I2CM_FLAG_BLOCKING  (1UL << 31)		/*!< Transfer function will block until complete */
#define ROM_I2CM_FLAG_DMATX     (1UL << 30)		/*!< DMA will be used for TX, requires DMA setup outside of the driver */
#define ROM_I2CM_FLAG_DMARX     (1UL << 29)		/*!< DMA will be used for RX, requires DMA setup outside of the driver */
#define ROM_I2CM_FLAG_USERBITS  (0xFFFF)		/*!< Application can safely use the flag bits designated by this mask */

/** @brief Master transfer descriptor */
typedef PRE_PACK struct POST_PACK {
	const void              *txBuff;	/*!< Pointer to array of bytes to be transmitted */
	void                    *rxBuff;	/*!< Pointer memory where bytes received from I2C be stored */
	volatile ErrorCode_t    status;		/*!< Packed status of the current I2C transfer (ErrorCode_t), must be 32-bits */
	uint32_t                flags;		/*!< Optional transfer flags */
	uint16_t                txSz;		/*!< Number of bytes in transmit array, if 0 only receive transfer will be performed */
	uint16_t                rxSz;		/*!< Number of bytes to receive, if 0 only transmission we be performed */
	uint16_t                slaveAddr;	/*!< 7-bit I2C Slave address */
	uint16_t                reserved;	/*!< Reserved for alignment */
} ROM_I2CM_XFER_T;

/** I2C master callback IDs */
typedef enum {
	ROM_I2CM_DATACOMPLETE_CB = 0,		/*!< Callback ID for I2C master data transfer complete */
	ROM_I2CM_DATATRANSMITSTART_CB,		/*!< Callback ID for I2C master transmit start */
	ROM_I2CM_DATATRECEIVESTART_CB		/*!< Callback ID for I2C master receive start */
} ROM_I2CM_CALLBACK_T;

/** @brief I2C master transfer complete callback prototype
 * The I2C master state machine will call this function when the transfer completes normally
 * or due to an error (NAK, arbitration, etc.).
 */
typedef void (*i2cMasterCompleteCB)(ROM_I2CM_HANDLE_T i2cmHandle, ROM_I2CM_XFER_T *pXfer);

/** @brief I2C master data receive start callback
 * The I2C master state machine will call this optional function prior to data transfer.
 * The callback can be used to setup DMA or alter the receive buffer size. The callback is
 * only called if it has been registered and the receive size (rxSz) in the transfer descriptor
 * is 0.
 */
typedef void (*i2cMasterReceiveStartCB)(ROM_I2CM_HANDLE_T i2cmHandle, ROM_I2CM_XFER_T *pXfer);

/** @brief I2C master data transmit start callback
 * The I2C master state machine will call this optional function prior to data transfer.
 * The callback can be used to setup DMA or alter the transmit buffer size. The callback is
 * only called if it has been registered and the transmit size (txSz) in the transfer descriptor
 * is 0.
 */
typedef void (*i2cMasterTransmitStartCB)(ROM_I2CM_HANDLE_T i2cmHandle, ROM_I2CM_XFER_T *pXfer);

/** @brief I2C master initialization structure */
typedef PRE_PACK struct POST_PACK {
	void        *pUserData;			/*!< Pointer to user data used by driver instance, use NULL if not used */
	uint32_t    base;				/*!< Base address of I2C peripheral to use */
} ROM_I2CM_INIT_T;

/** @brief I2C master ROM indirect function structure */
typedef PRE_PACK struct POST_PACK {
	uint32_t (*GetMemSize)(void);	/*!< Returns needed memory size required for run-time context of I2C master driver */
	ROM_I2CM_HANDLE_T (*Init)(void *mem, const ROM_I2CM_INIT_T *pInit);	/*!< Initializes the I2C master driver and peripheral */
	uint32_t (*SetClockRate)(ROM_I2CM_HANDLE_T pHandle, uint32_t inRate, uint32_t i2cRate);		/*!< Sets the I2C master clock rate */
	void (*RegisterCallback)(ROM_I2CM_HANDLE_T pHandle, uint32_t cbIndex, void *pCB);	/*!< Registers an I2C master callback */
	ErrorCode_t (*Transfer)(ROM_I2CM_HANDLE_T pHandle, ROM_I2CM_XFER_T *pXfer);		/*!< Perform or start and I2C master transfer */
	void (*TransferHandler)(ROM_I2CM_HANDLE_T pHandle);		/*!< I2C master transfer (interrupt) handler */
	uint32_t (*GetDriverVersion)(void);
} ROM_I2CMD_API_T;

/**
 * @}
 */

extern const ROM_I2CMD_API_T i2cm_api;	// so application program can access	pointer to
// function table

#endif /* __HW_I2CMD_ROM_API_H */
