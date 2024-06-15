/*
 * @brief SPI master ROM API declarations and functions
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

#ifndef __HW_SPIMD_ROM_API_H
#define __HW_SPIMD_ROM_API_H

#include "stdint.h"		// added to define uint32_t, etc.
#include "error.h"
#include "packing.h"
#include "hw_spi_common.h"

/** @defgroup ROMAPI_SPIM SPI master ROM driver functions and definitions
 * @ingroup ROMAPI_SPIM_WRAPPER
 * @{
 */

/** @brief SPI master handle type */
typedef void *ROM_SPIM_HANDLE_T;

/* Number of selects the SPI driver supports */
#define ROM_SPIM_MAXSELECTS (4)

/** @brief User context conversion macro
 * Macro used to extract the user defined data pointer from a SPI master
 * handle context.<br>
 * To get a user context, simple use the macro on the drivers handle:
 * void *pUserData = (void *) ROM_SPIM_HANDLE_TOUDATA(driverHandle);
 */
#define ROM_SPIM_HANDLE_TOUDATA(p)          (void *) (*(uint32_t *) p)

/** @brief SPI master optional transfer flags */
#define ROM_SPIM_FLAG_BLOCKING  (1UL << 31)		/*!< Transfer function will block until complete */
#define ROM_SPIM_FLAG_DMATX         (1UL << 30)		/*!< DMA will be used for TX, requires DMA setup outside of the driver */
#define ROM_SPIM_FLAG_DMARX         (1UL << 29)		/*!< DMA will be used for RX, requires DMA setup outside of the driver */
#define ROM_SPIM_FLAG_LOOPBACK      (1UL << 28)		/*!< Enables loopback mode for the transfer, useful for testing only */
#define ROM_SPIM_FLAG_TXIGNORE      (1UL << 27)		/*!< Ignores receive data regardless of txBuff, transmit data callback will not be called, stops when txSz = 0 */
#define ROM_SPIM_FLAG_RXIGNORE      (1UL << 26)		/*!< Ignores receive data regardless of rxBuff/rxSz, receive data callback will not be called */
#define ROM_SPIM_FLAG_USERBITS      (0xFFFF)		/*!< Application can safely use the flag bits designated by this mask */

/** @brief SPI transfer configuration structure - once of these needs to be setup for
 * each SPI select (SSEL) used on the master. If only SSEL0 is used, it only needs to be setup
 * for that one slave select. This structure must be statically allocated for use with the
 * driver and should not be created on the program stack. If anything in this structure
 * changes, SetupSSEL() must be called again with the structure reference. */
typedef PRE_PACK struct POST_PACK {
	uint32_t                dXferBitRate;	/*!< Desired bit transfer rate (SPI clock) in Hz */
	uint32_t                rXferBitRate;	/*!< Real bit transfer rate (SPI clock) in Hz, modified by driver to actual rate */
	uint8_t                 mode;			/*!< Mode selection for this transfer (ROM_SPI_CLOCK_MODE_T) */
	uint8_t                 lsbFirst;		/*!< 0 for msb sent/recv first, !0 = for lsb send/recv first */
	uint8_t                 dataBits;		/*!< Data transfer size in bits, between 1 and 16, txBuff and rxBuff must be 16-bit aligned if >8 */
	/* The time delays are based in SPI clocks (rXferBitRate). These values are used to configure the
	   SPI delays when a transfer is started, so these values do not need to be populated for the
	   SetupSSEL() function. The actual (rXferBitRate) and desired (dXferBitRate) SPI clocks may differ,
	   and the actual clock won't be known until after SetupSSEL() is called, so it's best to setup
	   these values after the call to SetupSSEL(). */
	uint8_t                 PreDelay;		/*!< Pre-delay value in (rXferBitRate) SPI clocks, 0 - 15 */
	uint8_t                 PostDelay;		/*!< Post-delay value in (rXferBitRate) SPI clocks, 0 - 15 */
	uint8_t                 FrameDelay;		/*!< Delay value between frames of a transfer in (rXferBitRate) SPI clocks, 0 - 15 */
	uint8_t                 TransferDelay;	/*!< Delay value between transfers in (rXferBitRate) SPI clocks, 1 - 16 */
	uint8_t                 reserved;
} ROM_SPIM_XFER_CONFIG_T;

/** @brief SPI Master transfer descriptor */
typedef PRE_PACK struct POST_PACK {
	const void                  *txBuff;	/*!< Pointer to array of datum to be transmitted, use NULL for receive only, must be 16-bit aligned if datum bits >8 */
	uint32_t                    txSz;		/*!< Size of the transmit buffer (txBuff) in items (not bytes) before transmit callback is called */
	void                        *rxBuff;	/*!< Pointer memory where datum received from SPI be stored, use NULL for transmit only, must be 16-bit aligned if datum bits >8 */
	uint32_t                    rxSz;		/*!< Size of the receive buffer (rxBuff) in items (not bytes) before receive callback is called */
	uint32_t                    flags;		/*!< Optional transfer flags, may be modified by driver */
	volatile ErrorCode_t        status;		/*!< Status of the current SPI transfer (ErrorCode_t), must be 32-bits */
	uint8_t                     sselNum;	/*!< SPI master SSEL number for this transfer, 0 - 3 */
	uint8_t                     reserved1[3];
} ROM_SPIM_XFER_T;

/** @brief SPI master callback IDs */
typedef enum {
	ROM_SPIM_ASSERTSSEL_CB = 0,			/*!< Callback ID for SPI master SSEL assertion */
	ROM_SPIM_DATATRANSMIT_CB,			/*!< Callback ID for SPI master transmit start */
	ROM_SPIM_DATATRECEIVE_CB,			/*!< Callback ID for SPI master receive start */
	ROM_SPIM_DEASSERTSSEL_CB			/*!< Callback ID for SPI master SSEL de-assertion */
} ROM_SPIM_CALLBACK_T;

/** @brief SPI master select assert callback
 * This callback is called from the SPI master handler when the SPI master
 * selects the slave (asserts SSEL). The callback is only called if it has been registered.<br>
 */
typedef void (*spiMasterXferCSAssertCB)(ROM_SPIM_HANDLE_T spimHandle, ROM_SPIM_XFER_T *pXfer);

/** @brief SPI master data receive start callback
 * The SPI master state machine will call this optional function when it needs a buffer to
 * receive data. The callback can be used to setup DMA or alter the receive buffer size. The
 * callback is only called if it has been registered, the buffer has been fully used, and
 * data is needed to populate the transmit FIFO. When using DMA, this callback must be enabled
 * and used for DMA setup.
 */
typedef void (*spiMasterReceiveCB)(ROM_SPIM_HANDLE_T spimHandle, ROM_SPIM_XFER_T *pXfer);

/** @brief SPI master data transmit start callback
 * The SPI master state machine will call this optional function for data transfer.
 * The callback can be used to setup DMA or alter the receive buffer size. The callback is
 * only called if it has been registered, the buffer has been fully used, and data is pending
 * is the receive FIFO. When using DMA, this callback must be enabled and used for DMA setup.
 */
typedef void (*spiMasterTransmitCB)(ROM_SPIM_HANDLE_T spimHandle, ROM_SPIM_XFER_T *pXfer);

/** @brief SPI master transfer select deassert data callback
 * This callback is called from the SPI master handler when the SPI master
 * deasserts the slave select. The callback is only called if it has been registered.<br>
 */
typedef void (*spiMMasterXferCSDeAssertCB)(ROM_SPIM_HANDLE_T spimHandle, ROM_SPIM_XFER_T *pXfer);

/** @brief SPI master initialization structure */
typedef PRE_PACK struct POST_PACK {
	void        *pUserData;				/*!< Pointer to user data used by driver instance, use NULL if not used */
	uint32_t    base;					/*!< Base address of SPI peripheral to use */
	uint32_t    baseClockRate;			/*!< SPI base clock rate in Hz, call Init() again if this rate changes */
	uint8_t     spiPol[4];				/*!< SPI SSEL pollarity for each slave select, 0 = active low, !0 = active high */
} ROM_SPIM_INIT_T;

/** @brief SPI master ROM indirect function structure */
typedef PRE_PACK struct POST_PACK {
	uint32_t (*GetMemSize)(void);	/*!< Returns needed memory size required for run-time context of SPI master driver */
	ROM_SPIM_HANDLE_T (*Init)(void *mem, const ROM_SPIM_INIT_T *pInit);	/*!< Initializes the SPI master driver and peripheral */
	void (*RegisterCallback)(ROM_SPIM_HANDLE_T pHandle, uint32_t cbIndex, void *pCB);	/*!< Registers an SPI master callback */
	ErrorCode_t (*SetupTransfer)(ROM_SPIM_HANDLE_T pHandle, ROM_SPIM_XFER_CONFIG_T *pCfg);	/*!< Sets up a master select's transfer configuration, should be called when the transfer configuration changes */
	ErrorCode_t (*Transfer)(ROM_SPIM_HANDLE_T pHandle, ROM_SPIM_XFER_T *pXfer);		/*!< Perform or start and SPI master transfer */
	void (*TransferHandler)(ROM_SPIM_HANDLE_T pHandle);		/*!< SPI master transfer (interrupt) handler */
	void (*ClosePendingTransfer)(ROM_SPIM_HANDLE_T pHandle);		/*!< Immediately terminates the current transfer */
	uint32_t (*GetDriverVersion)(void);
} ROM_SPIMD_API_T;

/**
 * @}
 */

extern const ROM_SPIMD_API_T spim_api;	// so application program can access	pointer to
// function table

#endif /* __HW_SPIMD_ROM_API_H */
