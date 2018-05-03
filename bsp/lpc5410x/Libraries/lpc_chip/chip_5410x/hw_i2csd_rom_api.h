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

#ifndef __HW_I2CSD_ROM_API_H
#define __HW_I2CSD_ROM_API_H

#include "stdint.h"		// added to define uint32_t, etc.
#include "error.h"
#include "packing.h"
#include "hw_i2c_common.h"

/** @defgroup ROMAPI_I2CS I2C slave ROM driver functions and definitions
 * @ingroup ROMAPI_I2CS_WRAPPER
 * @{
 */

/** @brief I2C slave handle type */
typedef void *ROM_I2CS_HANDLE_T;

/** @brief Maximum number of slave addresses supported by this driver */
#define ROM_I2CS_MAX_SLAVES         4

/** @brief User context conversion macro
 * Macro used to extract the user defined data pointer from a I2C master
 * handle context.<br>
 * To get a user context, simple use the macro on the drivers handle:
 * void *pUserData = (void *) ROM_I2CS_HANDLE_TOUDATA(driverHandle);
 */
#define ROM_I2CS_HANDLE_TOUDATA(p)          (void *) (*(uint32_t *) p)

/** @brief I2C master optional transfer flags */
#define ROM_I2CS_FLAG_USERBITS  (0xFFFF)		/*!< Application can safely use the flag bits designated by this mask */

/** @brief slave transfer descriptor */
typedef PRE_PACK struct POST_PACK {
	const void              *txBuff;		/*!< Pointer to array of bytes to be transmitted */
	void                    *rxBuff;		/*!< Pointer memory where bytes received from I2C be stored */
	volatile ErrorCode_t    status;			/*!< Packed status of the current I2C transfer (ErrorCode_t), must be 32-bits */
	uint32_t                flags;			/*!< Reserved, set to 0 */
	uint16_t                txSz;			/*!< Number of bytes in transmit array, if 0 only receive transfer will be performed */
	uint16_t                rxSz;			/*!< Number of bytes to receive, if 0 only transmission will be performed */
	uint16_t                bytesSent;		/*!< Number of bytes sent */
	uint16_t                bytesRecv;		/*!< Number of bytes recevied */
} ROM_I2CS_XFER_T;

/** I2C slave callback IDs */
typedef enum {
	ROM_I2CS_START_CB = 0,				/*!< Callback ID for I2C slave service start callback */
	ROM_I2CS_XFERSEND_CB,				/*!< Callback ID for I2C slave send data callback */
	ROM_I2CS_XFERRECV_CB,				/*!< Callback ID for I2C slave receive data callback */
	ROM_I2CS_DONE_CB,					/*!< Callback ID for I2C slave service done callback */
} ROM_I2CS_CALLBACK_T;

/** @brief I2C slave state machine transfer control */
typedef enum {
	ROM_I2CS_CONTINUE = 0,				/*!< Continue transfer */
	ROM_I2CS_NAK,						/*!< Will NAK master at next opportunity */
	ROM_I2CS_DMA						/*!< Tell I2C handler DMA is handling the data */
} ROM_I2CS_TRANCTRL_T;

/** @brief I2C slave transfer start callback
 * This callback is called from the I2C slave handler when an I2C slave address supported
 * by the controller is addressed.
 */
typedef void (*i2cSlaveStartCB)(ROM_I2CS_HANDLE_T i2csHandle, uint16_t addr);

/** @brief I2C slave send data callback
 * This callback is called from the I2C slave handler when an I2C slave address needs
 * data to send in the transfer descriptor. It is called on demand only when transmit
 * data is needed for the transmit FIFO and the descriptor buffer is empty.<br>
 * If you want to NAK the master, return ROM_I2CS_NAK to the caller.
 * Return ROM_I2CS_CONTINUE or 0 to the caller for normal non-DMA data transfer.
 * If you've setup a DMA descriptor for the transfer, return ROM_I2CS_DMA to the caller.<br>
 */
typedef ROM_I2CS_TRANCTRL_T (*i2cSlaveTransmitCB)(ROM_I2CS_HANDLE_T i2csHandle, ROM_I2CS_XFER_T *pXfer);

/** @brief I2C slave receive data callback
 * This callback is called from the I2C slave handler when an I2C slave address has
 * receive data and the receive buffer is full.<br>
 * If you want to NAK the master, return ROM_I2CS_NAK to the caller.
 * Return ROM_I2CS_CONTINUE or 0 to the caller for normal non-DMA data transfer.
 * If you've setup a DMA descriptor for the transfer, return ROM_I2CS_DMA to the caller.<br>
 */
typedef ROM_I2CS_TRANCTRL_T (*i2cSlaveReceiveCB)(ROM_I2CS_HANDLE_T i2csHandle, ROM_I2CS_XFER_T *pXfer);

/** @brief I2C slave service done callback
 * This callback is called from the I2C slave handler when an I2C slave transfer is
 * completed. It's used to indicate the end of a slave transfer.
 */
typedef void (*i2cSlaveCompleteCB)(ROM_I2CS_HANDLE_T i2csHandle, ROM_I2CS_XFER_T *pXfer);

/** @brief I2C slave initialization structure */
typedef PRE_PACK struct POST_PACK {
	void        *pUserData;			/*!< Pointer to user data used by driver instance, use NULL if not used */
	uint32_t    base;				/*!< Base address of I2C peripheral to use */
} ROM_I2CS_INIT_T;

/** @brief I2C slave address setup structure */
typedef PRE_PACK struct POST_PACK {
	uint16_t    slaveAddr;			/*!< Slave address used for this index in the controller */
	uint8_t     SlaveIndex;			/*!< Slave index to use, 0 is first index */
	uint8_t     EnableSlave;		/*!< Set to 0 to disable this slave index, or non-0 to enable */
} ROM_I2CS_SLAVE_T;

/** @brief I2C slave ROM indirect function structure */
typedef PRE_PACK struct POST_PACK {
	uint32_t (*GetMemSize)(void);	/*!< Returns needed memory size required for run-time context of I2C slave driver */
	ROM_I2CS_HANDLE_T (*Init)(void *mem, const ROM_I2CS_INIT_T *pInit);	/*!< Initializes the I2C slave driver and peripheral */
	void (*SetupSlave)(ROM_I2CS_HANDLE_T pHandle, ROM_I2CS_SLAVE_T *pSlaveSetup);	/*!< Sets up a slave address to use with the I2C controller */
	void (*RegisterCallback)(ROM_I2CS_HANDLE_T pHandle, uint32_t cbIndex, void *pCB);	/*!< Registers an I2C slave callback */
	ErrorCode_t (*Transfer)(ROM_I2CS_HANDLE_T pHandle, ROM_I2CS_XFER_T *pXfer);		/*!< Queues an I2C slave transfer */
	void (*TransferHandler)(ROM_I2CS_HANDLE_T pHandle);		/*!< I2C slave transfer (interrupt) handler */
	uint32_t (*GetDriverVersion)(void);
} ROM_I2CSD_API_T;

/**
 * @}
 */

extern const ROM_I2CSD_API_T i2cs_api;	// so application program can access	pointer to
// function table

#endif /* __HW_I2CSD_ROM_API_H */
