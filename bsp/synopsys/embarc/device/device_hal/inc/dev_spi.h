/* ------------------------------------------
 * Copyright (c) 2017, Synopsys, Inc. All rights reserved.

 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:

 * 1) Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.

 * 2) Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.

 * 3) Neither the name of the Synopsys, Inc., nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.

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
 *
 * \version 2017.03
 * \date 2014-06-16
 * \author Huaqi Fang(Huaqi.Fang@synopsys.com)
--------------------------------------------- */

/**
 * \defgroup	DEVICE_HAL_SPI	SPI Device HAL Interface
 * \ingroup	DEVICE_HAL_DEF
 * \brief	definitions for spi device hardware layer (\ref dev_spi.h)
 * \details	provide interfaces for spi driver to implement
 *  Here is a diagram for the spi interface.
 *
 *  \htmlonly
 *  <div class="imagebox">
 *      <div style="width: 600px">
 *          <img src="pic/dev_spi_hal.jpg" alt="SPI Device HAL Interface Diagram"/>
 *          <p>SPI Device HAL Interface Diagram</p>
 *      </div>
 *  </div>
 *  \endhtmlonly
 *
 * @{
 *
 * \file
 * \brief	spi device hardware layer definitions
 * \details	provide common definitions for spi device,
 * 	then software developer can develop spi driver
 * 	following this definitions, and the applications
 * 	can directly call this definition to realize functions
 */

#ifndef _DEVICE_HAL_SPI_H_
#define _DEVICE_HAL_SPI_H_

#include "device/device_hal/inc/dev_common.h"


/**
 * \defgroup	DEVICE_HAL_SPI_CTRLCMD		SPI Device Control Commands
 * \ingroup	DEVICE_HAL_SPI
 * \brief	Definitions for spi control command, used in \ref dev_spi::spi_control "SPI IO Control"
 * \details	These commands defined here can be used in user code directly.
 * - Parameters Usage
 *   - For passing parameters like integer, just use uint32_t/int32_t to directly pass values
 *   - For passing parameters for a structure, please use pointer to pass values
 *   - For getting some data, please use pointer to store the return data
 * - Common Return Values
 *   - \ref E_OK,	Control device successfully
 *   - \ref E_CLSED,	Device is not opened
 *   - \ref E_OBJ,	Device object is not valid or not exists
 *   - \ref E_PAR,	Parameter is not valid for current control command
 *   - \ref E_SYS,	Control device failed, due to hardware issues such as device is disabled
 *   - \ref E_CTX,	Control device failed, due to different reasons like in transfer state
 *   - \ref E_NOSPT,	Control command is not supported or not valid
 * - Usage Comment
 *   - For SPI poll or interrupt read/write/transfer operations, only 1 operation can be triggered.
 *     If there is a operation is running, any other operation will return \ref E_CTX
 *   - If SPI is in transfer, then the following operations may return \ref E_CTX. Like
 *     \ref SPI_CMD_SET_CLK_MODE, \ref SPI_CMD_SET_TXINT_BUF, \ref SPI_CMD_SET_RXINT_BUF,
 *     \ref SPI_CMD_SET_TXINT, \ref SPI_CMD_SET_RXINT, \ref SPI_CMD_ABORT_TX, \ref SPI_CMD_ABORT_RX,
 *     \ref SPI_CMD_FLUSH_TX, \ref SPI_CMD_FLUSH_RX, \ref SPI_CMD_SET_DFS, \ref SPI_CMD_TRANSFER_POLLING,
 *     \ref SPI_CMD_TRANSFER_INT, \ref SPI_CMD_ABORT_XFER, \ref SPI_CMD_MST_SEL_DEV, \ref SPI_CMD_MST_DSEL_DEV,
 *     \ref SPI_CMD_MST_SET_FREQ and \ref dev_spi::spi_write "SPI Poll Write" or \ref dev_spi::spi_read "SPI Poll Read".
 * @{
 */

/** Define SPI control commands for common usage */
#define DEV_SET_SPI_SYSCMD(cmd)		DEV_SET_SYSCMD((cmd))
/** Define SPI control commands for master usage */
#define DEV_SET_SPI_MST_SYSCMD(cmd)	DEV_SET_SYSCMD(0x00001000|(cmd))
/** Define SPI control commands for slave usage */
#define DEV_SET_SPI_SLV_SYSCMD(cmd)	DEV_SET_SYSCMD(0x00002000|(cmd))


/* ++++ Common commands for SPI Device ++++ */
/**
 * Get \ref dev_spi_info::status "current device status"
 * - Param type : uint32_t *
 * - Param usage : store result of current status
 * - Return value explanation :
 */
#define SPI_CMD_GET_STATUS			DEV_SET_SPI_SYSCMD(0)
/**
 * set the \ref dev_spi_info::clk_mode "clock mode" of spi transfer
 * - Param type : uint32_t
 * - Param usage : spi clock mode to choose clock phase and clock polarity
 * - Return value explanation :
 */
#define SPI_CMD_SET_CLK_MODE			DEV_SET_SPI_SYSCMD(1)
/**
 * set spi \ref dev_spi_info::dfs "data frame size"
 * - Param type : uint32_t
 * - Param usage : should > 0
 * - Return value explanation : If dfs is not supported, then return \ref E_SYS
 */
#define SPI_CMD_SET_DFS				DEV_SET_SPI_SYSCMD(2)
/**
 * set the \ref dev_spi_info::dummy "dummy data" during spi transfer
 * - Param type : uint32_t
 * - Param usage : dummy data to transfer
 * - Return value explanation :
 */
#define SPI_CMD_SET_DUMMY_DATA			DEV_SET_SPI_SYSCMD(3)
/**
 * Set \ref dev_spi_cbs::tx_cb "spi transmit success callback" function
 * when all required bytes are transmitted for interrupt method
 * - Param type : \ref DEV_CALLBACK * or NULL
 * - Param usage : transmit success callback function for spi
 * - Return value explanation :
 */
#define SPI_CMD_SET_TXCB			DEV_SET_SPI_SYSCMD(4)
/**
 * Set \ref dev_spi_cbs::rx_cb "spi receive success callback" function
 * when all required bytes are received for interrupt method
 * - Param type : \ref DEV_CALLBACK * or NULL
 * - Param usage : receive success callback function for spi
 * - Return value explanation :
 */
#define SPI_CMD_SET_RXCB			DEV_SET_SPI_SYSCMD(5)
/**
 * Set \ref dev_spi_cbs::xfer_cb "spi transfer success callback" function
 * when all required transfer are done for interrupt method
 * - Param type : \ref DEV_CALLBACK * or NULL
 * - Param usage : transfer success callback function for spi
 * - Return value explanation :
 */
#define SPI_CMD_SET_XFERCB			DEV_SET_SPI_SYSCMD(6)
/**
 * Set \ref dev_spi_cbs::err_cb "spi transfer error callback" function
 * when something error happened for interrupt method
 * - Param type : \ref DEV_CALLBACK * or NULL
 * - Param usage : transfer error callback function for spi
 * - Return value explanation :
 */
#define SPI_CMD_SET_ERRCB			DEV_SET_SPI_SYSCMD(7)
/**
 * Set buffer in interrupt transmit, and it will set \ref dev_spi_info::xfer "spi tranfer".
 * - SPI master and slave mode use case  \n
 *    For both master and slave mode, if you set tx buffer to NULL, when tx interrupt is enabled and entered into tx interrupt,
 * it will automatically disable the tx interrupt, so when you want to transfer something, you need to set the
 * tx buffer to Non-NULL and enable tx interrupt, when the tx buffer is sent, it will disable the tx interrupt
 * and call tx callback function if available.
 * - Param type : DEV_BUFFER * or NULL
 * - Param usage : buffer structure pointer, if param is NULL, then it will set xfer to empty
 * - Return value explanation :
 */
#define SPI_CMD_SET_TXINT_BUF			DEV_SET_SPI_SYSCMD(8)
/**
 * Set buffer in interrupt receive, and it will set \ref dev_spi_info::xfer "spi tranfer".
 * - SPI master mode use case  \n
 *   Similar to \ref SPI_CMD_SET_TXINT_BUF
 * - SPI slave mode use case   \n
 *   Similiar to \ref SPI_CMD_SET_TXINT_BUF
 * - Param type : DEV_BUFFER * or NULL
 * - Param usage : buffer structure pointer, if param is NULL, then it will set xfer to empty
 * - Return value explanation :
 */
#define SPI_CMD_SET_RXINT_BUF			DEV_SET_SPI_SYSCMD(9)
/**
 * Enable or disable transmit interrupt,
 * for master mode, only one of tx and rx interrupt can be enabled,
 * if tx interrupt is enabled, then rx interrupt can't be enabled.
 * - Param type : uint32_t
 * - Param usage : enable(none-zero) or disable(zero) flag
 * - Return value explanation :
 */
#define SPI_CMD_SET_TXINT			DEV_SET_SPI_SYSCMD(10)
/**
 * Enable or disable receive interrupt,
 * for master mode, only one of tx and rx interrupt can be enabled,
 * if rx interrupt is enabled, then tx interrupt can't be enabled.
 * - Param type : uint32_t
 * - Param usage : enable(none-zero) or disable(zero) flag
 * - Return value explanation :
 */
#define SPI_CMD_SET_RXINT			DEV_SET_SPI_SYSCMD(11)
/**
 * start the transfer by polling
 * - Param type : \ref DEV_SPI_TRANSFER *
 * - Param usage :
 * - Return value explanation :
 */
#define SPI_CMD_TRANSFER_POLLING		DEV_SET_SPI_SYSCMD(12)
/**
 * start the transfer by interrupt
 * - Param type : \ref DEV_SPI_TRANSFER * or NULL
 * - Param usage : If NULL, it will disable transfer interrupt, if not NULL, it will enable transfer interrupt
 * - Return value explanation :
 */
#define SPI_CMD_TRANSFER_INT			DEV_SET_SPI_SYSCMD(13)
/**
 * Abort current interrupt transmit operation if tx interrupt enabled,
 * it will disable transmit interrupt, and set \ref DEV_IN_TX_ABRT
 * in \ref dev_spi_info::status "status" variable,
 * and call the transmit callback function, when tx callback is finished,
 * it will clear \ref DEV_IN_TX_ABRT and return
 * - Param type : NULL
 * - Param usage :
 * - Return value explanation :
 */
#define SPI_CMD_ABORT_TX			DEV_SET_SPI_SYSCMD(14)
/**
 * Abort current interrupt receive operation if rx interrupt enabled,
 * it will disable receive interrupt, and set \ref DEV_IN_TX_ABRT
 * in \ref dev_spi_info::status "status" variable,
 * and call the receive callback function, when rx callback is finished,
 * it will clear \ref DEV_IN_TX_ABRT and return
 * - Param type : NULL
 * - Param usage :
 * - Return value explanation :
 */
#define SPI_CMD_ABORT_RX			DEV_SET_SPI_SYSCMD(15)
/**
 * Abort current interrupt transfer operation if transfer is issued,
 * it will disable transfer interrupt, and set \ref DEV_IN_XFER_ABRT
 * in \ref dev_spi_info::status "status" variable,
 * and call the transfer callback function, when xfer callback is finished,
 * it will clear \ref DEV_IN_XFER_ABRT and return
 * - Param type : NULL
 * - Param usage :
 * - Return value explanation :
 */
#define SPI_CMD_ABORT_XFER			DEV_SET_SPI_SYSCMD(16)
/**
 * Do a software reset for SPI device, it will stop current transfer,
 * and clear error state and bring device to normal state, set next condition to STOP
 * - Param type : NULL
 * - Param usage :
 * - Return value explanation :
 */
#define SPI_CMD_RESET				DEV_SET_SPI_SYSCMD(17)
/**
 * Flush spi tx fifo, this will clear the data in tx fifo
 * - Param type : NULL
 * - Param usage :
 * - Return value explanation :
 */
#define SPI_CMD_FLUSH_TX			DEV_SET_SPI_SYSCMD(18)
/**
 * Flush spi rx fifo, this will clear the data in rx fifo
 * - Param type : NULL
 * - Param usage :
 * - Return value explanation :
 */
#define SPI_CMD_FLUSH_RX			DEV_SET_SPI_SYSCMD(19)
/**
 * Enable spi device
 * - Param type : NULL
 * - Param usage : param is not required
 * - Return value explanation :
 */
#define SPI_CMD_ENA_DEV				DEV_SET_SPI_SYSCMD(20)
/**
 * Disable spi device, when device is disabled,
 * only \ref SPI_CMD_ENA_DEV, \ref SPI_CMD_DIS_DEV,
 * \ref SPI_CMD_GET_STATUS and \ref SPI_CMD_RESET
 * commands can be executed, other commands will return \ref E_SYS
 * - Param type : NULL
 * - Param usage : param is not required
 * - Return value explanation :
 */
#define SPI_CMD_DIS_DEV				DEV_SET_SPI_SYSCMD(21)
/**
 * Get how many bytes space in spi are available to transmit,
 * this can be used in interrupt callback functions,
 * cooperate with \ref dev_spi::spi_write "spi_write" API to realize non-blocked write
 * - Param type : int32_t *
 * - Param usage : store the write available bytes, > 0 for available bytes, 0 for not available
 * - Return value explanation :
 */
#define SPI_CMD_GET_TXAVAIL			DEV_SET_SPI_SYSCMD(22)
/**
 * Get how many bytes in spi are available to receive,
 * this can be used in interrupt callback functions,
 * cooperate with \ref dev_spi::spi_read "spi_read" API to realize non-blocked read
 * - Param type : int32_t *
 * - Param usage : store the read available bytes, > 0 for available bytes, 0 for not available
 * - Return value explanation :
 */
#define SPI_CMD_GET_RXAVAIL			DEV_SET_SPI_SYSCMD(23)


/* ++++ Master only commands for SPI Device ++++ */
/**
 *  select spi slave device
 * - Param type : uint32_t
 * - Param usage : the number of spi slave device to select
 * - Return value explanation : return \ref E_SYS when selection can't be done, return \ref E_CTX during transfer
 */
#define SPI_CMD_MST_SEL_DEV			DEV_SET_SPI_MST_SYSCMD(0)
/**
 *  de-select spi slave device
 * - Param type : uint32_t
 * - Param usage : the number of spi slave device to de-select
 * - Return value explanation : return \ref E_SYS when selection can't be done, return \ref E_CTX during transfer
 */
#define SPI_CMD_MST_DSEL_DEV			DEV_SET_SPI_MST_SYSCMD(1)
 /**
 * Set \ref dev_spi_info::freq "spi frequency".
 * - Param type : uint32_t
 * - Param usage : spi freq
 * - Return value explanation : no return
 */
#define SPI_CMD_MST_SET_FREQ			DEV_SET_SPI_MST_SYSCMD(2)


/* ++++ Slave only commands for SPI Device ++++ */

/* \todo add spi slave related CMDs */

/** @} */

/**
 * \defgroup	DEVICE_HAL_SPI_CALLBACK	SPI Interrupt callback functions
 * \ingroup	DEVICE_HAL_SPI
 * \brief	callback function structure for SPI device
 * @{
 */
typedef struct dev_spi_cbs {
	DEV_CALLBACK tx_cb;	/*!< spi data transmit success required bytes callback */
	DEV_CALLBACK rx_cb;	/*!< spi data receive success required bytes callback */
	DEV_CALLBACK err_cb;	/*!< spi error callback */
	DEV_CALLBACK xfer_cb;	/*!< transfer callback */
} DEV_SPI_CBS, *DEV_SPI_CBS_PTR;
/** @} */

/** SPI Clock Mode */
typedef enum spi_clk_mode {
	SPI_CPOL_0_CPHA_0 = 0,	/*!< Inactive state of serial clock is low, serial clock toggles in middle of first data bit */
	SPI_CPOL_0_CPHA_1 = 1,	/*!< Inactive state of serial clock is low, serial clock toggles at start of first data bit  */
	SPI_CPOL_1_CPHA_0 = 2,	/*!< Inactive state of serial clock is high, serial clock toggles in middle of first data bit */
	SPI_CPOL_1_CPHA_1 = 3,	/*!< Inactive state of serial clock is high, serial clock toggles at start of first data bit */

	SPI_CLK_MODE_0    = SPI_CPOL_0_CPHA_0,	/*!< Equal to \ref SPI_CPOL_0_CPHA_0 */
	SPI_CLK_MODE_1    = SPI_CPOL_0_CPHA_1,	/*!< Equal to \ref SPI_CPOL_0_CPHA_1 */
	SPI_CLK_MODE_2    = SPI_CPOL_1_CPHA_0,	/*!< Equal to \ref SPI_CPOL_1_CPHA_0 */
	SPI_CLK_MODE_3    = SPI_CPOL_1_CPHA_1	/*!< Equal to \ref SPI_CPOL_1_CPHA_1 */
} SPI_CLK_MODE;

#define SPI_CLK_MODE_DEFAULT	SPI_CPOL_0_CPHA_0	/*!< Default SPI device clock mode */

/**
 * \defgroup	DEVICE_HAL_SPI_DEVSTRUCT	SPI Device Structure
 * \ingroup	DEVICE_HAL_SPI
 * \brief	contains definitions of spi device structure.
 * \details	this structure will be used in user implemented code, which was called
 * 	Device Driver Implement Layer for spi to realize in user code.
 * @{
 */
typedef struct dev_spi_transfer DEV_SPI_TRANSFER, *DEV_SPI_TRANSFER_PTR;
/**
 * \brief	spi read and write data structure used by \ref SPI_CMD_TRANSFER
 * 	spi write then read data
 *
 */
struct dev_spi_transfer {
	DEV_SPI_TRANSFER *next;
	/* Calc by software */
	/** tot_len = (tx_totlen>rx_totlen)?tx_totlen:rx_totlen */
	uint32_t tot_len;
	/* Set by user */
	uint8_t *tx_buf;
	uint32_t tx_ofs;
	uint32_t tx_len;
	uint8_t *rx_buf;
	uint32_t rx_ofs;
	uint32_t rx_len;
	/* Should auto set to proper value during set buffer value */
	uint32_t tx_idx;
	uint32_t tx_totlen;	/** tx_totlen = tx_len + tx_ofs */
	uint32_t rx_idx;
	uint32_t rx_totlen;	/** rx_totlen = rx_len + rx_ofs */
};

/** Set tx buffer of device spi transfer */
#define DEV_SPI_XFER_SET_TXBUF(xfer, buf, ofs, len)		{		\
					(xfer)->tx_buf = (uint8_t *)(buf);	\
					(xfer)->tx_len = (uint32_t)(len);	\
					(xfer)->tx_ofs = (uint32_t)(ofs);	\
					(xfer)->tx_idx = 0;			\
					(xfer)->tx_totlen = ( (uint32_t)(len) 	\
							+ (uint32_t)(ofs) ) ;	\
				}

/** Set rx buffer of device spi transfer */
#define DEV_SPI_XFER_SET_RXBUF(xfer, buf, ofs, len)		{		\
					(xfer)->rx_buf = (uint8_t *)(buf);	\
					(xfer)->rx_len = (uint32_t)(len);	\
					(xfer)->rx_ofs = (uint32_t)(ofs);	\
					(xfer)->rx_idx = 0;			\
					(xfer)->rx_totlen = ( (uint32_t)(len) 	\
							+ (uint32_t)(ofs) ) ;	\
				}

/** Calculate total length of current transfer without next transfer */
#define DEV_SPI_XFER_CALC_TOTLEN(xfer)		(xfer)->tot_len =	\
				((xfer)->tx_totlen > (xfer)->rx_totlen) ? (xfer)->tx_totlen : (xfer)->rx_totlen ;

/** Set next SPI transfer */
#define DEV_SPI_XFER_SET_NEXT(xfer, next_xfer)	(xfer)->next = (next_xfer);

/** Init spi transfer */
#define DEV_SPI_XFER_INIT(xfer)					{		\
					(xfer)->tx_idx = 0;			\
					(xfer)->rx_idx = 0;			\
					(xfer)->tx_totlen = ((xfer)->tx_len  	\
							+ (xfer)->tx_ofs) ;	\
					(xfer)->rx_totlen = ((xfer)->rx_len  	\
							+ (xfer)->rx_ofs) ;	\
					DEV_SPI_XFER_CALC_TOTLEN(xfer);		\
				}
/**
 * \brief	spi information struct definition
 * \details	informations about spi open state, working state,
 * 	frequency, spi registers, working method, interrupt number
 */
typedef struct dev_spi_info {
	void *spi_ctrl;		/*!< spi control related */
	uint32_t status;	/*!< current working status, refer to \ref DEVICE_HAL_COMMON_DEVSTATUS, this should be \ref DEV_ENABLED for first open */
	uint32_t freq;		/*!< spi working baudrate */
	uint8_t mode;		/*!< spi working mode (master/slave) */
	uint8_t clk_mode;	/*!< spi clock phase and polarity, this should be \ref SPI_CLK_MODE_DEFAULT for first open */
	uint8_t opn_cnt;	/*!< spi open count, open it will increase 1, close it will decrease 1, 0 for close, >0 for open */
	uint8_t slave;		/*!< current selected slave device no, start from 0, this should be \ref SPI_SLAVE_NOT_SELECTED for first open */
	uint8_t dfs;		/*!< data frame size, this should be \ref SPI_DFS_DEFAULT for first open */

	DEV_SPI_TRANSFER xfer;	/*!< spi transfer, this should be set to all zero for first open */
	DEV_SPI_CBS spi_cbs;	/*!< spi callbacks, for both master and slave mode, this should be all NULL for first open */
	void *extra;		/*!< a extra pointer to get hook to applications which should not used by bsp developer,
					this should be NULL for first open and you can \ref DEV_SPI_INFO_SET_EXTRA_OBJECT "set"
					or \ref DEV_SPI_INFO_GET_EXTRA_OBJECT "get" the extra information pointer */
	uint32_t dummy;		/*!< dummy write data when send and receive, this should be \ref SPI_DUMMY_DEFAULT for first open */
} DEV_SPI_INFO, * DEV_SPI_INFO_PTR;

/** Set extra information pointer of spi info */
#define DEV_SPI_INFO_SET_EXTRA_OBJECT(spi_info_ptr, extra_info)		(spi_info_ptr)->extra = (void *)(extra_info)
/** Get extra information pointer of spi info */
#define DEV_SPI_INFO_GET_EXTRA_OBJECT(spi_info_ptr)			((spi_info_ptr)->extra)

#define SPI_DFS_DEFAULT				8		/*!< Default spi data frame size */
#define SPI_SLAVE_NOT_SELECTED			(0xFF)		/*!< Slave is not selected */
#define SPI_DUMMY_DEFAULT			(0xFF)		/*!< default dummy value for first open */

/**
 * \brief	spi device interface definition
 * \details	define spi device interface, like spi information structure,
 * 	fuctions to get spi info, open/close/control spi, send/receive data by spi
 * \note	all this details are implemented by user in user porting code
 */
typedef struct dev_spi {
	DEV_SPI_INFO spi_info;						/*!< spi device information */
	int32_t (*spi_open) (uint32_t mode, uint32_t param);		/*!< open spi device in master/slave mode, \
									when in master mode, param stands for frequency, \
									when in slave mode, param stands for clock mode */
	int32_t (*spi_close) (void);					/*!< close spi device */
	int32_t (*spi_control) (uint32_t ctrl_cmd, void *param);	/*!< control spi device */
	int32_t (*spi_write) (const void *data, uint32_t len);		/*!< send data to spi device (blocking method) */
	int32_t (*spi_read) (void *data, uint32_t len);			/*!< read data from spi device (blocking method) */
} DEV_SPI, * DEV_SPI_PTR;

/**
 * \fn		int32_t (* dev_spi::spi_open) (uint32_t mode, uint32_t param)
 * \details	open an spi device with selected mode (master or slave) with defined \ref param
 * \param[in]	mode	working mode (\ref DEV_MASTER_MODE "master" or \ref DEV_SLAVE_MODE "slave")
 * \param[in]	param	When mode is \ref DEV_MASTER_MODE, param stands for \ref dev_spi_info::freq "frequency",
 * 			when mode is \ref DEV_SLAVE_MODE, param stands for \ref dev_spi_info::clk_mode "slave clock mode"
 * \retval	E_OK	Open successfully without any issues
 * \retval	E_OPNED	If device was opened before with different parameters,
 *			then just increase the \ref dev_spi_info::opn_cnt "opn_cnt" and return \ref E_OPNED
 * \retval	E_OBJ	Device object is not valid
 * \retval	E_SYS	Device is opened for different mode before, if you want to open it with different mode, you need to fully close it first.
 * \retval	E_PAR	Parameter is not valid
 * \retval	E_NOSPT	Open settings are not supported
 */

/**
 * \fn		int32_t (* dev_spi::spi_close) (void)
 * \details	close an spi device, just decrease the \ref dev_spi_info::opn_cnt "opn_cnt",
 *      if \ref dev_spi_info::opn_cnt "opn_cnt" equals 0, then close the device
 * \retval	E_OK	Close successfully without any issues(including scenario that device is already closed)
 * \retval	E_OPNED	Device is still opened, the device \ref dev_spi_info::opn_cnt "opn_cnt" decreased by 1
 * \retval	E_OBJ	Device object is not valid
 */

/**
 * \fn		int32_t (* dev_spi::spi_control) (uint32_t ctrl_cmd, void *param)
 * \details	control an spi device by \ref ctrl_cmd, with passed \ref param.
 * 	you can control spi device using predefined spi control commands defined using \ref DEV_SET_SYSCMD
 * 	(which must be implemented by bsp developer), such as \ref SPI_CMD_MST_SET_FREQ "set spi master frequency",
 * 	\ref SPI_CMD_FLUSH_TX "flush tx" and \ref DEVICE_HAL_SPI_CTRLCMD "more".
 * 	And you can also control spi device using your own specified commands defined using \ref DEV_SET_USRCMD,
 * 	but these specified commands should be defined in your own spi device driver implementation.
 * \param[in]		ctrl_cmd	\ref DEVICE_HAL_SPI_CTRLCMD "control command", to change or get some thing related to spi
 * \param[in,out]	param		parameters that maybe argument of the command,
 * 					or return values of the command, must not be NULL
 * \retval	E_OK	Control device successfully
 * \retval	E_CLSED	Device is not opened
 * \retval	E_OBJ	Device object is not valid or not exists
 * \retval	E_PAR	Parameter is not valid for current control command
 * \retval	E_SYS	Control device failed, due to hardware issues, such as device is disabled
 * \retval	E_CTX	Control device failed, due to different reasons like in transfer state
 * \retval	E_NOSPT	Control command is not supported or not valid
 */

/**
 * \fn		int32_t (* dev_spi::spi_write) (const void *data, uint32_t len)
 * \details	send \ref data through spi with defined \ref len to slave device .
 * \param[in]	data	pointer to data need to send by spi
 * \param[in]	len	length of data to be sent
 * \retval	>0	Byte count that was successfully sent for poll method
 * \retval	E_OBJ	Device object is not valid or not exists
 * \retval	E_PAR	Parameter is not valid
 * \retval	E_CTX	Device is still in transfer state
 * \retval	E_SYS	Can't write data to hardware due to hardware issues, such as device is disabled
 */

/**
 * \fn		int32_t (* dev_spi::spi_read) (void *data, uint32_t len)
 * \details	receive \ref data of defined \ref len through spi from slave device .
 * \param[out]	data	pointer to data need to received by spi
 * \param[in]	len	length of data to be received
 * \retval	>0	Byte count that was successfully received for poll method
 * \retval	E_OBJ	Device object is not valid or not exists
 * \retval	E_CTX	Device is still in transfer state
 * \retval	E_PAR	Parameter is not valid
 * \retval	E_SYS	Can't receive data from hardware due to hardware issues, such as device is disabled
 */
/** @} */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief	get an \ref dev_spi "spi device" by spi device id.
 * 	For how to use spi device hal refer to \ref dev_spi "Functions in spi device structure"
 * \param[in]	spi_id	id of spi, defined by user
 * \retval	!NULL	pointer to an \ref dev_spi "spi device structure"
 * \retval	NULL	failed to find the spi device by \ref spi_id
 * \note	need to implemented by user in user code
 */
extern DEV_SPI_PTR spi_get_dev(int32_t spi_id);

#ifdef __cplusplus
}
#endif

/** @} */
#endif /* _DEVICE_HAL_SPI_H_ */
