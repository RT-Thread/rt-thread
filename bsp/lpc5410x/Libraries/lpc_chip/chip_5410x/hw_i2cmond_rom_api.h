/*
 * @brief I2C monitor ROM API declarations and functions
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

#ifndef __HW_I2CMOND_ROM_API_H
#define __HW_I2CMOND_ROM_API_H

#include "stdint.h"		// added to define uint32_t, etc.
#include "error.h"
#include "packing.h"
#include "hw_i2c_common.h"

/** @defgroup ROMAPI_I2CMON I2C monitor ROM driver functions and definitions
 * @ingroup ROMAPI_I2CMON_WRAPPER
 * @{
 */

/** @brief I2C monitor handle type */
typedef void *ROM_I2CMON_HANDLE_T;

/** @brief User context conversion macro
 * Macro used to extract the user defined data pointer from a I2C monitor
 * handle context.<br>
 * To get a user context, simple use the macro on the drivers handle:
 * void *pUserData = (void *) ROM_I2CMON_HANDLE_TOUDATA(driverHandle);
 */
#define ROM_I2CMON_HANDLE_TOUDATA(p)            (void *) (*(uint32_t *) p)

/** @brief I2C monitor optional transfer flags */
#define ROM_I2CMON_FLAG_BLOCKING    (1UL << 31)		/*!< Capture function will block until complete */
#define ROM_I2CMON_FLAG_DMARX       (1UL << 29)		/*!< DMA will be used for RX, requires DMA setup outside of the driver */
#define ROM_I2CMON_FLAG_FLUSH       (1UL << 25)		/*!< Force monitor FIFO flush */
#define ROM_I2CMON_FLAG_USERBITS    (0xFFFF)		/*!< Application can safely use the flag bits designated by this mask */

/** @brief Monitor transfer descriptor */
typedef PRE_PACK struct POST_PACK {
	const void      *startBuff;			/*!< Pointer to a buffer for capturing data after start, msy be 16-bit aligned */
	uint16_t        startBuffSz;		/*!< Number of bytes in startBuff buffer, data will be tossed if not big enough */
	uint16_t        capStartBuffSz;		/*!< Number of bytes captured in startBuff buffer */
	uint32_t        flags;				/*!< Optional transfer flags of type ROM_I2CMON_FLAG_* */
	volatile ErrorCode_t status;		/*!< LPC_OK, busy status, or error code */
} ROM_I2CMON_CAP_T;

/** I2C monitor callback IDs */
typedef enum {
	ROM_I2CMON_CAPTUREREADY_CB = 0,		/*!< Callback ID for I2C monitor capture ready */
	ROM_I2CMON_DMASETUP_CB				/*!< Callback for DMA setup */
} ROM_I2CMON_CALLBACK_T;

/** @brief I2C monitor capture complete callback prototype
 * The I2C monitor state machine will call this function when it captures an I2C transfer.
 */
typedef void (*i2cMonCapReadyCB)(ROM_I2CMON_HANDLE_T i2cmonHandle, ROM_I2CMON_CAP_T *pCap);

/** @brief I2C monitor capture DMA setup callback prototype
 * The I2C monitor state machine will call this function when DMA needs to be setup for
 * the capture oeprations.
 */
typedef void (*i2cMonSetupDMACB)(ROM_I2CMON_HANDLE_T i2cmonHandle, ROM_I2CMON_CAP_T *pCap);

/** @brief I2C monitor initialization structure */
typedef PRE_PACK struct POST_PACK {
	void        *pUserData;			/*!< Pointer to user data used by driver instance, use NULL if not used */
	uint32_t    base;				/*!< Base address of I2C peripheral to use */
	uint8_t     stretch;			/*!< 0 = disable monitor clock stretching, !0 = enable */
} ROM_I2CMON_INIT_T;

/** @brief I2C monitor ROM indirect function structure */
typedef PRE_PACK struct POST_PACK {
	uint32_t (*GetMemSize)(void);	/*!< Returns needed memory size required for run-time context of I2C monitor driver */
	ROM_I2CMON_HANDLE_T (*Init)(void *mem, const ROM_I2CMON_INIT_T *pInit);	/*!< Initializes the I2C monitor driver and peripheral */
	void (*RegisterCallback)(ROM_I2CMON_HANDLE_T pHandle, uint32_t cbIndex, void *pCB);	/*!< Registers an I2C monitor callback */
	ErrorCode_t (*StartLog)(ROM_I2CMON_HANDLE_T pHandle, ROM_I2CMON_CAP_T *pCap);	/*!< Start/queue a log descriptor */
	void (*TransferHandler)(ROM_I2CMON_HANDLE_T pHandle);		/*!< I2C monitor transfer (interrupt) handler */
	uint32_t (*GetDriverVersion)(void);
} ROM_I2CMOND_API_T;

/**
 * @}
 */

extern const ROM_I2CMOND_API_T i2cmon_api;	// so application program can access	pointer to
// function table

#endif /* __HW_I2CMOND_ROM_API_H */
