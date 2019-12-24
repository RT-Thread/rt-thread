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
 * \defgroup	DEVICE_HAL_IIC	IIC Device HAL Interface
 * \ingroup	DEVICE_HAL_DEF
 * \brief	definitions for iic device hardware layer (\ref dev_iic.h)
 * \details	provide interfaces for iic driver to implement
 *  Here is a diagram for the iic interface.
 *
 *  \htmlonly
 *  <div class="imagebox">
 *      <div style="width: 600px">
 *          <img src="pic/dev_iic_hal.jpg" alt="IIC Device HAL Interface Diagram"/>
 *          <p>IIC Device HAL Interface Diagram</p>
 *      </div>
 *  </div>
 *  \endhtmlonly
 *
 * @{
 *
 * \file
 * \brief	iic device hardware layer definitions
 * \details	provide common definitions for iic device,
 * 	then software developer can develop iic driver
 * 	following this definitions, and the applications
 * 	can directly call this definition to realize functions
 */

#ifndef _DEVICE_HAL_IIC_H_
#define _DEVICE_HAL_IIC_H_

#include "device/device_hal/inc/dev_common.h"

/**
 * \defgroup	DEVICE_HAL_IIC_CFG	IIC Related Configurations
 * \ingroup	DEVICE_HAL_IIC
 * \brief	Macros for IIC device related configurations.
 * @{
 */
/** IIC Bus possible speed modes */
typedef enum iic_speed_mode {
	IIC_SPEED_STANDARD = 0,	/*!< Bidirectional, Standard-mode (Sm), with a bit rate up to 100 kbit/s */
	IIC_SPEED_FAST     = 1,	/*!< Bidirectional, Fast-mode (Fm), with a bit rate up to 400 kbit/s */
	IIC_SPEED_FASTPLUS = 2,	/*!< Bidirectional, Fast-mode Plus (Fm+), with a bit rate up to 1 Mbit/s */
	IIC_SPEED_HIGH     = 3,	/*!< Bidirectional, High-speed mode (Hs-mode), with a bit rate up to 3.4 Mbit/s */
	IIC_SPEED_ULTRA    = 4	/*!< Unidirectional(Write only), Ultra Fast-mode (UFm), with a bit rate up to 5 Mbit/s */
} IIC_SPEED_MODE;

/** IIC next Condition */
typedef enum iic_next_condtion {
	IIC_MODE_STOP    = 0,	/*!< Send a STOP condition after write/read operation */
	IIC_MODE_RESTART = 1	/*!< Send a RESTART condition after write/read operation */
} IIC_NEXT_CONDTION;

/** IIC Error State */
typedef enum iic_error_state {
	IIC_ERR_NONE       = 0,	/*!< Currently in iic device free state */
	IIC_ERR_LOST_BUS   = 1,	/*!< Master or slave lost bus during operation */
	IIC_ERR_ADDR_NOACK = 2,	/*!< Slave address is sent but not addressed by any slave devices */
	IIC_ERR_DATA_NOACK = 3,	/*!< Data in transfer is not acked when it should be acked */
	IIC_ERR_TIMEOUT    = 4,	/*!< Transfer timeout, no more data is received or sent */
	IIC_ERR_MSTSTOP    = 5,	/*!< Slave received a STOP condition from master device */
	IIC_ERR_UNDEF      = 6	/*!< Undefined error cases */
} IIC_ERROR_STATE;

/** IIC Working State */
typedef enum iic_working_state {
	IIC_FREE  = 0,	/*!< Currently in iic device free state */
	IIC_IN_TX = 1,	/*!< Currently in iic master transmit state */
	IIC_IN_RX = 2	/*!< Currently in iic master receive state */
} IIC_WORKING_STATE;

/** IIC Addressing Mode */
typedef enum iic_address_mode {
	IIC_7BIT_ADDRESS  = 0,	/*!< Use 7bit address mode */
	IIC_10BIT_ADDRESS = 1	/*!< Use 10bit address mode */
} IIC_ADDRESS_MODE;

/** IIC Slave State */
typedef enum iic_slave_state {
	IIC_SLAVE_STATE_FREE     = 0,		/*!< None state, in free */
	IIC_SLAVE_STATE_START    = (1<<1),	/*!< Start or Restart condition, clear it when read */
	IIC_SLAVE_STATE_STOP     = (1<<2),	/*!< Stop condition, clear it when read */
	IIC_SLAVE_STATE_RD_REQ   = (1<<3),	/*!< Read request from master, this will trigger the slave transmit callback */
	IIC_SLAVE_STATE_RD_DONE  = (1<<4),	/*!< Read request done from master, clear it when read */
	IIC_SLAVE_STATE_WR_REQ   = (1<<5),	/*!< Write request from master, this will trigger the slave receive callback */
	IIC_SLAVE_STATE_GC_REQ   = (1<<6),	/*!< General call request from master */
	IIC_SLAVE_STATE_ERROR    = (1<<7)	/*!< Error, clear it when read */
} IIC_SLAVE_STATE;

/** 7bit IIC address mask */
#define IIC_7BIT_ADDRESS_MASK		(0x7F)
/** 10bit IIC address mask */
#define IIC_10BIT_ADDRESS_MASK		(0x3FF)
/** @} */

/**
 * \defgroup	DEVICE_HAL_IIC_CTRLCMD		IIC Device Control Commands
 * \ingroup	DEVICE_HAL_IIC
 * \brief	Definitions for iic control command, used in \ref dev_iic::iic_control "IIC IO Control"
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
 * @{
 */

/** Define IIC control commands for common usage */
#define DEV_SET_IIC_SYSCMD(cmd)		DEV_SET_SYSCMD((cmd))
/** Define IIC control commands for master usage */
#define DEV_SET_IIC_MST_SYSCMD(cmd)	DEV_SET_SYSCMD(0x00004000|(cmd))
/** Define IIC control commands for slave usage */
#define DEV_SET_IIC_SLV_SYSCMD(cmd)	DEV_SET_SYSCMD(0x00008000|(cmd))

/* ++++ Common commands for IIC Device ++++ */
/**
 * Get \ref dev_iic_info::status "current device status"
 * - Param type : uint32_t *
 * - Param usage : store result of current status
 * - Return value explanation :
 */
#define IIC_CMD_GET_STATUS			DEV_SET_IIC_SYSCMD(0)
/**
 * Set \ref dev_iic_info::addr_mode "iic addressing mode".
 * - Param type : uint32_t
 * - Param usage : iic addressing mode, possible values can be found \ref IIC_ADDRESS_MODE "here"
 * - Return value explanation :
 */
#define IIC_CMD_SET_ADDR_MODE			DEV_SET_IIC_SYSCMD(1)
/**
 * Set \ref dev_iic_cbs::tx_cb "iic transmit success callback" function
 * when all required bytes are transmitted for interrupt method
 * - Param type : \ref DEV_CALLBACK * or NULL
 * - Param usage : transmit success callback function for iic
 * - Return value explanation :
 */
#define IIC_CMD_SET_TXCB			DEV_SET_IIC_SYSCMD(2)
/**
 * Set \ref dev_iic_cbs::rx_cb "iic receive success callback" function
 * when all required bytes are received for interrupt method
 * - Param type : \ref DEV_CALLBACK * or NULL
 * - Param usage : receive success callback function for iic
 * - Return value explanation :
 */
#define IIC_CMD_SET_RXCB			DEV_SET_IIC_SYSCMD(3)
/**
 * Set \ref dev_iic_cbs::err_cb "iic transfer error callback" function
 * when something error happened for interrupt method
 * - Param type : \ref DEV_CALLBACK * or NULL
 * - Param usage : transfer error callback function for iic
 * - Return value explanation :
 */
#define IIC_CMD_SET_ERRCB			DEV_SET_IIC_SYSCMD(4)
/**
 * Set buffer for interrupt transmit, and it will set \ref dev_iic_info::tx_buf "tx_buf".
 * - IIC master mode use case  \n
 *    For master mode, if you set tx buffer to NULL, when tx interrupt is enabled and entered into tx interrupt,
 * it will automatically disable the tx interrupt, so when you want to transfer something, you need to set the
 * tx buffer to Non-NULL and enable tx interrupt, when the tx buffer is sent, it will disable the tx interrupt
 * and call tx callback function if available.
 * - IIC slave mode use case   \n
 *    For slave mode, the tx buffer is not used, only tx callback function is used, and if tx callback is not set,
 * then it will automatically disable the tx interrupt, if tx callback is set, it will call the tx callback function
 * and you need to write or read in the tx callback function, to avoid meaningless waiting, you can use control command
 * \ref IIC_CMD_GET_TXAVAIL to get how many bytes space existing in transmit fifo, and use iic_write to send the available
 * bytes.
 * - Param type : DEV_BUFFER * or NULL
 * - Param usage : buffer structure pointer, if param is NULL, then it will set tx_buf to NULL
 * - Return value explanation :
 */
#define IIC_CMD_SET_TXINT_BUF			DEV_SET_IIC_SYSCMD(5)
/**
 * Set buffer for interrupt receive, and it will set \ref dev_iic_info::rx_buf "rx_buf"
 * - IIC master mode use case  \n
 *   Similar to \ref IIC_CMD_SET_TXINT_BUF
 * - IIC slave mode use case   \n
 *   Similiar to \ref IIC_CMD_SET_TXINT_BUF
 * - Param type : DEV_BUFFER * or NULL
 * - Param usage : buffer structure pointer, if param is NULL, then it will set rx_buf to NULL
 * - Return value explanation :
 */
#define IIC_CMD_SET_RXINT_BUF			DEV_SET_IIC_SYSCMD(6)
/**
 * Enable or disable transmit interrupt,
 * for master mode, only one of tx and rx interrupt can be enabled,
 * if tx interrupt is enabled, then rx interrupt can't be changed.
 * - Param type : uint32_t
 * - Param usage : enable(none-zero) or disable(zero) flag
 * - Return value explanation :
 */
#define IIC_CMD_SET_TXINT			DEV_SET_IIC_SYSCMD(7)
/**
 * Enable or disable receive interrupt,
 * for master mode, only one of tx and rx interrupt can be enabled,
 * if rx interrupt is enabled, then tx interrupt can't be changed.
 * - Param type : uint32_t
 * - Param usage : enable(none-zero) or disable(zero) flag
 * - Return value explanation :
 */
#define IIC_CMD_SET_RXINT			DEV_SET_IIC_SYSCMD(8)
/**
 * Abort current interrupt transmit operation if tx interrupt enabled,
 * it will disable transmit interrupt, and set \ref DEV_IN_TX_ABRT
 * in \ref dev_iic_info::status "status" variable,
 * and call the transmit callback function, when tx callback is finished,
 * it will clear \ref DEV_IN_TX_ABRT and return
 * - Param type : NULL
 * - Param usage :
 * - Return value explanation :
 */
#define IIC_CMD_ABORT_TX			DEV_SET_IIC_SYSCMD(9)
/**
 * Abort current interrupt receive operation if rx interrupt enabled,
 * it will disable receive interrupt, and set \ref DEV_IN_TX_ABRT
 * in \ref dev_iic_info::status "status" variable,
 * and call the receive callback function, when rx callback is finished,
 * it will clear \ref DEV_IN_TX_ABRT and return
 * - Param type : NULL
 * - Param usage :
 * - Return value explanation :
 */
#define IIC_CMD_ABORT_RX			DEV_SET_IIC_SYSCMD(10)
/**
 * Do a software reset for IIC device, it will stop current transfer,
 * and clear error state and bring device to normal state, set next condition to STOP
 * - Param type : NULL
 * - Param usage :
 * - Return value explanation :
 */
#define IIC_CMD_RESET				DEV_SET_IIC_SYSCMD(11)
/**
 * Flush iic device transmit buffer or fifo
 * - Param type : NULL
 * - Param usage :
 * - Return value explanation :
 */
#define IIC_CMD_FLUSH_TX			DEV_SET_IIC_SYSCMD(12)
/**
 * Flush iic device receive buffer or fifo
 * - Param type : NULL
 * - Param usage :
 * - Return value explanation :
 */
#define IIC_CMD_FLUSH_RX			DEV_SET_IIC_SYSCMD(13)
/**
 * Enable iic device
 * - Param type : NULL
 * - Param usage : param is not required
 * - Return value explanation :
 */
#define IIC_CMD_ENA_DEV				DEV_SET_IIC_SYSCMD(14)
/**
 * Disable iic device, when device is disabled,
 * only \ref IIC_CMD_ENA_DEV, \ref IIC_CMD_DIS_DEV,
 * \ref IIC_CMD_GET_STATUS and \ref IIC_CMD_RESET
 * commands can be executed, other commands will return \ref E_SYS
 * - Param type : NULL
 * - Param usage : param is not required
 * - Return value explanation :
 */
#define IIC_CMD_DIS_DEV				DEV_SET_IIC_SYSCMD(15)
/**
 * Get how many bytes space in iic are available to transmit,
 * this can be used in interrupt callback functions,
 * cooperate with \ref dev_iic::iic_write "iic_write" API to realize non-blocked write
 * - Param type : int32_t *
 * - Param usage : store the write available bytes, > 0 for available bytes, 0 for not available
 * - Return value explaination :
 */
#define IIC_CMD_GET_TXAVAIL			DEV_SET_IIC_SYSCMD(16)
/**
 * Get how many bytes in iic are available to receive,
 * this can be used in interrupt callback functions,
 * cooperate with \ref dev_iic::iic_read "iic_read" API to realize non-blocked read
 * - Param type : int32_t *
 * - Param usage : store the read available bytes, > 0 for available bytes, 0 for not available
 * - Return value explanation :
 */
#define IIC_CMD_GET_RXAVAIL			DEV_SET_IIC_SYSCMD(17)

/* ++++ Master only commands for IIC Device ++++ */
/**
 * Set \ref dev_iic_info::speed_mode "iic speed mode".
 * - Param type : uint32_t
 * - Param usage : iic speed mode, possible values can be found \ref IIC_SPEED_MODE "here",
 * and if passing mode is not supported, it will choose a lower supported speed mode
 * - Return value explanation :
 */
#define IIC_CMD_MST_SET_SPEED_MODE		DEV_SET_IIC_MST_SYSCMD(0)
/**
 * Set next condition for following transmit or receive operation.
 * For example, you can change next condition before iic_read or iic_write,
 * then in iic_read/iic_write operation, it will send a STOP/RESTART condition
 * after the last byte of this operation. For interrupt, this is similar.
 * - Param type : uint32_t
 * - Param usage : next condition can be \ref IIC_NEXT_CONDTION
 * - Return value explanation :
 */
#define IIC_CMD_MST_SET_NEXT_COND		DEV_SET_IIC_MST_SYSCMD(1)
/**
 * Set target slave device address for selecting slave device
 * - Param type : uint32_t
 * - Param usage : target slave address value
 * - Return value explanation :
 */
#define IIC_CMD_MST_SET_TAR_ADDR		DEV_SET_IIC_MST_SYSCMD(2)


/* ++++ Slave only commands for IIC Device ++++ */
/**
 * Set slave address when working as slave iic device
 * - Param type : uint32_t
 * - Param usage : slave address value
 * - Return value explanation :
 */
#define IIC_CMD_SLV_SET_SLV_ADDR		DEV_SET_IIC_SLV_SYSCMD(0)
/**
 * Get \ref iic_slave_state "slave state" when working as slave iic device
 * - Param type : uint32_t *
 * - Param usage : slave state
 * - Return value explanation :
 */
#define IIC_CMD_SLV_GET_SLV_STATE		DEV_SET_IIC_SLV_SYSCMD(1)

/** @} */

/**
 * \defgroup	DEVICE_HAL_IIC_CALLBACK	IIC Interrupt callback functions
 * \ingroup	DEVICE_HAL_IIC
 * \brief	callback function structure for IIC device
 * @{
 */
typedef struct dev_iic_cbs {
	DEV_CALLBACK tx_cb;	/*!< iic data transmit success required bytes callback */
	DEV_CALLBACK rx_cb;	/*!< iic data receive success required bytes callback */
	DEV_CALLBACK err_cb;	/*!< iic error callback */
} DEV_IIC_CBS, *DEV_IIC_CBS_PTR;
/** @} */

/**
 * \defgroup	DEVICE_HAL_IIC_DEVSTRUCT	IIC Device Structure
 * \ingroup	DEVICE_HAL_IIC
 * \brief	contains definitions of iic device structure.
 * \details	this structure will be used in user implemented code, which was called
 *     Device Driver Implement Layer for iic to realize in user code.
 * @{
 */
/**
 * \brief	iic information struct definition
 * \details	informations about iic open state, working state,
 * 	baurate, iic registers, working method, interrupt number
 */
typedef struct dev_iic_info {
	void *iic_ctrl;		/*!< iic control related pointer, implemented by bsp developer, and this should be set during iic object implementation */
	uint32_t opn_cnt;	/*!< iic open count, open it will increase 1, close it will decrease 1, 0 for close, >0 for open */
	uint32_t status;	/*!< current working status, refer to \ref DEVICE_HAL_COMMON_DEVSTATUS, this should be \ref DEV_ENABLED for first open */
	uint32_t mode;		/*!< current working mode, which can be \ref DEV_MASTER_MODE "master mode" or \ref DEV_SLAVE_MODE "slave mode" */
	uint32_t speed_mode;	/*!< current working \ref IIC_SPEED_MODE "iic speed mode" */
	uint32_t cur_state;	/*!< \ref IIC_WORKING_STATE "current working state for iic device", this should be \ref IIC_FREE for first open */
	uint32_t err_state;	/*!< \ref IIC_ERROR_STATE "current error state for iic device", this should be \ref IIC_ERR_NONE for first open */
	uint32_t addr_mode;	/*!< \ref IIC_ADDRESS_MODE "current addressing mode", this should be \ref IIC_7BIT_ADDRESS for first open */
	uint32_t slv_addr;	/*!< slave address when working as slave iic device, this should be 0 for first open */
	uint32_t tar_addr;	/*!< target slave device address when addressing that slave device, this should be 0 for first open */
	uint32_t next_cond;	/*!< \ref IIC_NEXT_CONDTION "next condition for master transmit or receive", \
					possible values are STOP or RESTART, it should be STOP for first open */
	DEV_BUFFER tx_buf;	/*!< transmit buffer via interrupt, this should be all zero for first open */
	DEV_BUFFER rx_buf;	/*!< receive buffer via interrupt, this should be all zero for first open */
	DEV_IIC_CBS iic_cbs;	/*!< iic callbacks, for both master and slave mode, this should be all NULL for first open */
	void *extra;		/*!< a extra pointer to get hook to applications which should not used by bsp developer,
					this should be NULL for first open and you can \ref DEV_IIC_INFO_SET_EXTRA_OBJECT "set"
					or \ref DEV_IIC_INFO_GET_EXTRA_OBJECT "get" the extra information pointer */
} DEV_IIC_INFO, * DEV_IIC_INFO_PTR;

/** Set extra information pointer of iic info */
#define DEV_IIC_INFO_SET_EXTRA_OBJECT(iic_info_ptr, extra_info)		(iic_info_ptr)->extra = (void *)(extra_info)
/** Get extra information pointer of iic info */
#define DEV_IIC_INFO_GET_EXTRA_OBJECT(iic_info_ptr)			((iic_info_ptr)->extra)

/**
 * \brief	iic device interface definition
 * \details	define iic device interface, like iic information structure,
 * 	fuctions to get iic info, open/close/control iic, send/receive data by iic
 * \note	all this details are implemented by user in user porting code
 */
typedef struct dev_iic {
	DEV_IIC_INFO iic_info;					/*!< iic device information */
	int32_t (*iic_open) (uint32_t mode, uint32_t param);	/*!< open iic device in master/slave mode, \
									when in master mode, param stands for speed mode, \
									when in slave mode, param stands for slave address */
	int32_t (*iic_close) (void);				/*!< close iic device */
	int32_t (*iic_control) (uint32_t ctrl_cmd, void *param);/*!< control iic device */
	int32_t (*iic_write) (const void *data, uint32_t len);	/*!< send data by iic device (blocking method) */
	int32_t (*iic_read) (void *data, uint32_t len);		/*!< read data from iic device (blocking method) */
} DEV_IIC, * DEV_IIC_PTR;

/**
 * \fn		int32_t (* dev_iic::iic_open) (uint32_t mode, uint32_t param)
 * \details	open an iic device with selected mode (master or slave) with defined \ref param
 * \param[in]	mode	working mode (\ref DEV_MASTER_MODE "master" or \ref DEV_SLAVE_MODE "slave")
 * \param[in]	param	When mode is \ref DEV_MASTER_MODE, param stands for \ref dev_iic_info::speed_mode "speed mode",
 * 			when mode is \ref DEV_SLAVE_MODE, param stands for \ref dev_iic_info::slv_addr "slave device 7bit address"
 * \retval	E_OK	Open successfully without any issues
 * \retval	E_OPNED	If device was opened before with different parameters,
 *			then just increase the \ref dev_iic_info::opn_cnt "opn_cnt" and return \ref E_OPNED
 * \retval	E_OBJ	Device object is not valid
 * \retval	E_SYS	Device is opened for different mode before, if you want to open it with different mode, you need to fully close it first.
 * \retval	E_PAR	Parameter is not valid
 * \retval	E_NOSPT	Open settings are not supported
 */

/**
 * \fn		int32_t (* dev_iic::iic_close) (void)
 * \details	close an iic device, just decrease the \ref dev_iic_info::opn_cnt "opn_cnt",
 *      if \ref dev_iic_info::opn_cnt "opn_cnt" equals 0, then close the device
 * \retval	E_OK	Close successfully without any issues(including scenario that device is already closed)
 * \retval	E_OPNED	Device is still opened, the device \ref dev_iic_info::opn_cnt "opn_cnt" decreased by 1
 * \retval	E_OBJ	Device object is not valid
 */

/**
 * \fn		int32_t (* dev_iic::iic_control) (uint32_t ctrl_cmd, void *param)
 * \details	control an iic device by \ref ctrl_cmd, with passed \ref param.
 * 	you can control iic device using predefined iic control commands defined using \ref DEV_SET_SYSCMD
 * 	(which must be implemented by bsp developer), such as \ref IIC_CMD_SET_SPEED "set iic speed mode",
 * 	\ref IIC_CMD_FLUSH_TX "flush tx" and \ref DEVICE_HAL_IIC_CTRLCMD "more".
 * 	And you can also control iic device using your own specified commands defined using \ref DEV_SET_USRCMD,
 * 	but these specified commands should be defined in your own iic device driver implementation.
 * \param[in]		ctrl_cmd	\ref DEVICE_HAL_IIC_CTRLCMD "control command", to change or get some thing related to iic
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
 * \fn		int32_t (* dev_iic::iic_write) (const void *data, uint32_t len)
 * \details	send \ref data through iic with defined \ref len to slave device which slave address is \ref slv_addr.
 * \param[in]	data	pointer to data need to send by iic
 * \param[in]	len	length of data to be sent
 * \retval	>0	Byte count that was successfully sent for poll method,
 * 			it might can't send that much due to \ref \ref dev_iic_info::err_state "different error state".
 * \retval	E_OBJ	Device object is not valid or not exists
 * \retval	E_PAR	Parameter is not valid
 * \retval	E_CTX	Device is still in transfer state
 * \retval	E_SYS	Can't write data to hardware due to hardware issues, such as device is disabled
 */

/**
 * \fn		int32_t (* dev_iic::iic_read) (void *data, uint32_t len)
 * \details	receive \ref data of defined \ref len through iic from slave device which slave address is \ref slv_addr.
 * \param[out]	data	pointer to data need to received by iic
 * \param[in]	len	length of data to be received
 * \retval	>0	Byte count that was successfully received for poll method,
 * 			it might can't send that much due to \ref \ref dev_iic_info::err_state "different error state".
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
 * \brief	get an \ref dev_iic "iic device" by iic device id.
 * 	For how to use iic device hal refer to \ref DEVICE_HAL_IIC_DEVSTRUCT "Functions in iic device structure"
 * \param[in]	iic_id	id of iic, defined by user
 * \retval	!NULL	pointer to an \ref dev_iic "iic device structure"
 * \retval	NULL	failed to find the iic device by \ref iic_id
 * \note	need to implemented by user in user code
 */
extern DEV_IIC_PTR iic_get_dev(int32_t iic_id);

#ifdef __cplusplus
}
#endif

/** @} */
#endif /* _DEVICE_HAL_IIC_H_ */
