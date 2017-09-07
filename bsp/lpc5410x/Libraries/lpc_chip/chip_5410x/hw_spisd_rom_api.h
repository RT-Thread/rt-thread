/*
 * @brief SPI slave ROM API declarations and functions
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

#ifndef __HW_SPISD_ROM_API_H
#define __HW_SPISD_ROM_API_H

#include "stdint.h"		// added to define uint32_t, etc.
#include "error.h"
#include "packing.h"
#include "hw_spi_common.h"

/** @defgroup ROMAPI_SPIS SPI slave ROM driver functions and definitions
 * @ingroup ROMAPI_SPIS_WRAPPER
 * @{
 */

/** @brief SPI slave handle type */
typedef void *ROM_SPIS_HANDLE_T;

/** @brief Number of selects the SPI driver supports */
#define ROM_SPIS_MAXSELECTS (4)

/** @brief User context conversion macro
 * Macro used to extract the user defined data pointer from a SPI slave
 * handle context.<br>
 * To get a user context, simple use the macro on the drivers handle:
 * void *pUserData = (void *) ROM_SPIS_HANDLE_TOUDATA(driverHandle);
 */
#define ROM_SPIS_HANDLE_TOUDATA(p)          (void *) (*(uint32_t *) p)

/** @brief SPI slave optional transfer flags */
#define ROM_SPIS_FLAG_DMATX         (1UL << 30)		/*!< DMA will be used for TX, requires DMA setup outside of the driver */
#define ROM_SPIS_FLAG_DMARX         (1UL << 29)		/*!< DMA will be used for RX, requires DMA setup outside of the driver */
#define ROM_SPIS_FLAG_TXIGNORE      (1UL << 27)		/*!< Ignores transmit data regardless of txBuff, transmit data callback will not be called, stops when txSz = 0 */
#define ROM_SPIS_FLAG_RXIGNORE      (1UL << 26)		/*!< Ignores receive data regardless of rxBuff/rxSz, receive data callback will not be called */
#define ROM_SPIS_FLAG_USERBITS      (0xFFFF)		/*!< Application can safely use the flag bits designated by this mask */

/** @brief SPI transfer configuration structure - once of these needs to be setup for
 * each SPI select (SSEL) used on the slave. If only SSEL0 is used, it only needs to be setup
 * for that one slave select. */
typedef PRE_PACK struct POST_PACK {
	uint8_t                 mode;			/*!< Mode selection for this transfer (ROM_SPI_CLOCK_MODE_T) */
	uint8_t                 lsbFirst;		/*!< 0 for msb sent/recv first, !0 = for lsb send/recv first */
	uint8_t                 dataBits;		/*!< Data transfer size in bits, between 1 and 16, txBuff and rxBuff must be 16-bit aligned if >8 */
	uint8_t                 reserved;
} ROM_SPIS_SLAVE_T;

/** @brief SPI slave transfer descriptor */
typedef PRE_PACK struct POST_PACK {
	const void                  *txBuff;	/*!< Pointer to array of datum to be transmitted, must be 16-bit aligned if datum bits >8 */
	uint32_t                    txSz;		/*!< Size of the transmit buffer (txBuff) in items (not bytes) before transmit callback is called */
	uint32_t                    txSent;		/*!< Number of items (not bytes) sent between SSEL assertion and deassertion */
	void                        *rxBuff;	/*!< Pointer memory where datum received from SPI be stored, must be 16-bit aligned if datum bits >8 */
	uint32_t                    rxSz;		/*!< Size of the receive buffer (rxBuff) in items (not bytes) before receive callback is called */
	uint32_t                    rxRecv;		/*!< Number of items (not bytes) received between SSEL assertion and deassertion */
	uint32_t                    flags;		/*!< Optional transfer flags, may be modified by driver */
	volatile ErrorCode_t        status;		/*!< Status of the current SPI transfer (ErrorCode_t), must be 32-bits */
} ROM_SPIS_XFER_T;

/** @brief SPI slave callback IDs */
typedef enum {
	ROM_SPIS_ASSERTSSEL_CB = 0,			/*!< Callback ID for SPI slave select (SSEL) assertion */
	ROM_SPIS_DATATRANSMIT_CB,			/*!< Callback ID for SPI slave transmit start */
	ROM_SPIS_DATATRECEIVE_CB,			/*!< Callback ID for SPI slave receive start */
	ROM_SPIS_DEASSERTSSEL_CB			/*!< Callback ID for SPI slave select (SSEL) de-assertion (completion callback) */
} ROM_SPIS_CALLBACK_T;

/** @brief SPI slave select assert callback
 * This callback is called from the SPI slave handler when the SPI slave
 * selects the slave (asserts SSEL). The callback is only called if it has been registered.
 */
typedef void (*spisSlaveXferCSAssertCB)(ROM_SPIS_HANDLE_T spisHandle, uint8_t slaveNum);

/** @brief SPI slave data receive start callback
 * The SPI slave state machine will call this optional function when it needs a buffer to
 * receive data. The callback can be used to setup DMA or alter the receive buffer size. The
 * callback is only called if it has been registered, the buffer has been fully used, and
 * data is pending is the receive FIFO. When using DMA, this callback must be enabled and
 * used for DMA setup.
 */
typedef void (*spisSlaveReceiveCB)(ROM_SPIS_HANDLE_T spisHandle, ROM_SPIS_XFER_T *pXfer);

/** @brief SPI slave data transmit start callback
 * The SPI slave state machine will call this optional function prior to data transfer.
 * The callback can be used to setup DMA or alter the receive buffer size. The callback
 * is only called if it has been registered, the buffer has been fully used, and data is
 * needed to populate the transmit FIFO. When using DMA, this callback must be enabled and
 * used for DMA setup.
 */
typedef void (*spisSlaveTransmitCB)(ROM_SPIS_HANDLE_T spisHandle, ROM_SPIS_XFER_T *pXfer);

/** @brief SPI slave transfer select deassert data callback
 * This callback is called from the SPI slave handler when the SPI slave
 * deasserts the slave select. The callback is only called if it has been registered.
 */
typedef void (*spisSlaveXferCSDeAssertCB)(ROM_SPIS_HANDLE_T spisHandle, ROM_SPIS_XFER_T *pXfer);

/** @brief SPI slave initialization structure */
typedef PRE_PACK struct POST_PACK {
	void        *pUserData;				/*!< Pointer to user data used by driver instance, use NULL if not used */
	uint32_t    base;					/*!< Base address of SPI peripheral to use */
	uint8_t     spiPol[4];				/*!< SPI SSEL pollarity for each slave select, 0 = active low, !0 = active high */
} ROM_SPIS_INIT_T;

/** @brief SPI slave ROM indirect function structure */
typedef PRE_PACK struct POST_PACK {
	uint32_t (*GetMemSize)(void);	/*!< Returns needed memory size required for run-time context of SPI slave driver */
	ROM_SPIS_HANDLE_T (*Init)(void *mem, const ROM_SPIS_INIT_T *pInit);	/*!< Initializes the SPI slave driver and peripheral */
	void (*RegisterCallback)(ROM_SPIS_HANDLE_T pHandle, uint32_t cbIndex, void *pCB);	/*!< Registers an SPI slave callback */
	ErrorCode_t (*SetupSlave)(ROM_SPIS_HANDLE_T pHandle, ROM_SPIS_SLAVE_T *pSlaveSetup);	/*!< Setup SPI slave transfer configuration */
	ErrorCode_t (*Transfer)(ROM_SPIS_HANDLE_T pHandle, ROM_SPIS_XFER_T *pXfer);		/*!< Prepare a SPI slave transfer */
	void (*TransferHandler)(ROM_SPIS_HANDLE_T pHandle);		/*!< SPI slave transfer (interrupt) handler */
	uint32_t (*GetDriverVersion)(void);
} ROM_SPISD_API_T;

/**
 * @}
 */

extern const ROM_SPISD_API_T spis_api;	// so application program can access	pointer to
// function table

#endif /* __HW_SPISD_ROM_API_H */
