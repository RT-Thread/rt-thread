/**
 * \file
 *
 * \brief I2C Common Driver for SAMB
 *
 * Copyright (c) 2015-2016 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#ifndef I2C_COMMON_H_INCLUDED
#define I2C_COMMON_H_INCLUDED

#include <compiler.h>
#include <system_sam_b.h>
#include <gpio.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \if (I2C_MASTER_MODE && I2C_SLAVE_MODE)
 *   \defgroup asfdoc_samb_i2c_group SAM I2C Driver (I2C)
 * \elseif I2C_MASTER_MODE
 *   \defgroup asfdoc_samb_i2c_group SAM I2C Master Mode Driver (I2C)
 * \elseif I2C_SLAVE_MODE
 *   \defgroup asfdoc_samb_i2c_group SAM I2C Slave Mode Driver (I2C)
 * \endif
 *
 * This driver for Atmel&reg; | SMART SAM devices provides an interface for the configuration
 * and management of the device's I<SUP>2</SUP>C module, for the transfer
 * of data via an I<SUP>2</SUP>C bus. The following driver API modes are covered
 * by this manual:
 *
 * \if I2C_MASTER_MODE
 * - Master Mode Polled APIs
 * \endif
 * \if I2C_MASTER_CALLBACK_MODE
 * - Master Mode Callback APIs
 * \endif
 * \if I2C_SLAVE_MODE
 * - Slave Mode Polled APIs
 * \endif
 * \if I2C_SLAVE_CALLBACK_MODE
 * - Slave Mode Callback APIs
 * \endif
 *
 * The following peripheral is used by this module:
 * - Serial Communication Interface
 *
 * The following devices can use this module:
 *  - Atmel | SMART SAM B11
 *
 * The outline of this documentation is as follows:
 * - \ref asfdoc_samb_i2c_prerequisites
 * - \ref asfdoc_samb_i2c_overview
 * - \ref asfdoc_samb_i2c_special_considerations
 * - \ref asfdoc_samb_i2c_extra
 * - \ref asfdoc_samb_i2c_examples
 * - \ref asfdoc_samb_i2c_api_overview
 *
 * \section asfdoc_samb_i2c_prerequisites Prerequisites
 * There are no prerequisites.
 *
 * \section asfdoc_samb_i2c_overview Module Overview
 *
 * The outline of this section is as follows:
 * - \ref asfdoc_samb_i2c_functional_desc
 * - \ref asfdoc_samb_i2c_bus_topology
 * - \ref asfdoc_samb_i2c_transactions
 * - \ref asfdoc_samb_i2c_multi_master
 * - \ref asfdoc_samb_i2c_bus_states
 *
 * \subsection asfdoc_samb_i2c_functional_desc Functional Description
 * The I<SUP>2</SUP>C provides a simple two-wire bidirectional bus consisting of a
 * wired-AND type serial clock line (SCL) and a wired-AND type serial data line
 * (SDA).
 *
 * The I<SUP>2</SUP>C bus provides a simple, but efficient method of interconnecting
 * multiple master and slave devices. An arbitration mechanism is provided for
 * resolving bus ownership between masters, as only one master device may own
 * the bus at any given time. The arbitration mechanism relies on the wired-AND
 * connections to avoid bus drivers short-circuiting.
 *
 * A unique address is assigned to all slave devices connected to the bus. A
 * device can contain both master and slave logic, and can emulate multiple
 * slave devices by responding to more than one address.
 *
 * \subsection asfdoc_samb_i2c_bus_topology Bus Topology
 * The I<SUP>2</SUP>C bus topology is illustrated in
 * \ref asfdoc_samb_i2c_bus_topology_figure "the figure below". The pull-up
 * resistors (Rs) will provide a high level on the bus lines when none of the
 * I<SUP>2</SUP>C devices are driving the bus. These are optional, and can be
 * replaced with a constant current source.
 *
 * \anchor asfdoc_samb_i2c_bus_topology_figure
 * \image html bus_topology.svg "I2C Bus Topology" Width=100%
 *
 * \subsection asfdoc_samb_i2c_transactions Transactions
 * The I<SUP>2</SUP>C standard defines three fundamental transaction formats:
 * - Master Write
 *   - The master transmits data packets to the slave after addressing it
 * - Master Read
 *   - The slave transmits data packets to the master after being addressed
 * - Combined Read/Write
 *   - A combined transaction consists of several write and read transactions
 *
 * A data transfer starts with the master issuing a \b Start condition on the
 * bus, followed by the address of the slave together with a bit to indicate
 * whether the master wants to read from or write to the slave.
 * The addressed slave must respond to this by sending an \b ACK back to the
 * master.
 *
 * After this, data packets are sent from the master or slave, according to the
 * read/write bit. Each packet must be acknowledged (ACK) or not
 * acknowledged (NACK) by the receiver.
 *
 * If a slave responds with a NACK, the master must assume that the slave
 * cannot receive any more data and cancel the write operation.
 *
 * The master completes a transaction by issuing a \b Stop condition.
 *
 * A master can issue multiple \b Start conditions during a transaction; this
 * is then called a \b Repeated \b Start condition.
 *
 * \subsubsection asfdoc_samb_i2c_address_packets Address Packets
 * The slave address consists of seven bits. The 8<SUP>th</SUP> bit in the transfer
 * determines the data direction (read or write). An address packet always
 * succeeds a \b Start or \b Repeated \b Start condition. The 8<SUP>th</SUP> bit is handled
 * in the driver, and the user will only have to provide the 7-bit address.
 *
 * \subsubsection asfdoc_samb_i2c_data_packets Data Packets
 * Data packets are nine bits long, consisting of one 8-bit data byte, and an
 * acknowledgement bit. Data packets follow either an address packet or another
 * data packet on the bus.
 *
 * \subsubsection asfdoc_samb_i2c_trans_examples Transaction Examples
 * The gray bits in the following examples are sent from master to slave, and
 * the white bits are sent from slave to master.
 * Example of a read transaction is shown in
 * \ref asfdoc_samb_i2c_trans_examples_i2c_read "the figure below". Here, the
 * master first issues a \b Start condition and gets ownership of the bus. An
 * address packet with the direction flag set to read is then sent and
 * acknowledged by the slave. Then the slave sends one data packet which is
 * acknowledged by the master. The slave sends another packet, which is not
 * acknowledged by the master and indicates that the master will terminate the
 * transaction. In the end, the transaction is terminated by the master issuing
 * a \b Stop condition.
 *
 * \anchor asfdoc_samb_i2c_trans_examples_i2c_read
 * \image html i2c_read.svg "I2C Packet Read" Width=100%
 *
 * Example of a write transaction is shown in
 * \ref asfdoc_samb_i2c_trans_examples_i2c_write "the figure below". Here, the
 * master first issues a \b Start condition and gets ownership of the bus. An
 * address packet with the dir flag set to write is then sent and acknowledged
 * by the slave. Then the master sends two data packets, each acknowledged by
 * the slave. In the end, the transaction is terminated by the master issuing
 * a \b Stop condition.
 *
 * \anchor asfdoc_samb_i2c_trans_examples_i2c_write
 * \image html i2c_write.svg "I2C Packet Write" Width=100%
 *
 * \subsubsection asfdoc_samb_i2c_repeated_start Repeated Start
 * To issue a \b Repeated \b Start, the functions postfixed \c _no_stop must be
 * used.
 * These functions will not send a \b Stop condition when the transfer is done,
 * thus the next transfer will start with a \b Repeated \b Start. To end the
 * transaction, the functions without the \c _no_stop postfix must be used
 * for the last read/write.
 *
 * \subsection asfdoc_samb_i2c_multi_master Multi Master
 * In a multi master environment, arbitration of the bus is important, as only
 * one master can own the bus at any point.
 *
 * \subsubsection asfdoc_samb_i2c_arbitration Arbitration
 *
 * \par Clock stretching
 * The serial clock line is always driven by a master device. However, all
 * devices connected to the bus are allowed stretch the low period of the clock
 * to slow down the overall clock frequency or to insert wait states while
 * processing data.
 * Both master and slave can randomly stretch the clock, which will force the
 * other device into a wait-state until the clock line goes high again.
 *
 * \par Arbitration on the data line
 * If two masters start transmitting at the same time, they will both transmit
 * until one master detects that the other master is pulling the data line low.
 * When this is detected, the master not pulling the line low, will stop the
 * transmission and wait until the bus is idle.
 * As it is the master trying to contact the slave with the lowest address that
 * will get the bus ownership, this will create an arbitration scheme always
 * prioritizing the slaves with the lowest address in case of a bus collision.
 *
 * \subsubsection asfdoc_samb_i2c_clock_sync Clock Synchronization
 * In situations where more than one master is trying to control the bus clock
 * line at the same time, a clock synchronization algorithm based on the same
 * principles used for clock stretching is necessary.
 *
 *
 * \subsection asfdoc_samb_i2c_bus_states Bus States
 * As the I<SUP>2</SUP>C bus is limited to one transaction at the time,
 * a master that wants to perform a bus transaction must wait until the bus is
 * free.
 * Because of this, it is necessary for all masters in a multi-master system to
 * know the current status of the bus to be able to avoid conflicts and to
 * ensure data integrity.
 * \li \b IDLE No activity on the bus (between a \b Stop and a new \b Start
 * condition)
 * \li \b BUSY If another master is driving the bus
 *
 * \section asfdoc_samb_i2c_special_considerations Special Considerations
 * There are no special considerations related to this driver.
 *
 *
 * \section asfdoc_samb_i2c_extra Extra Information
 * For extra information, see \ref asfdoc_samb_i2c_extra_info_page.
 * This includes:
 *  - \ref asfdoc_samb_i2c_acronyms
 *  - \ref asfdoc_samb_i2c_extra_dependencies
 *  - \ref asfdoc_samb_i2c_extra_errata
 *  - \ref asfdoc_samb_i2c_extra_history
 *
 * \section asfdoc_samb_i2c_examples Examples
 *
 * For a list of examples related to this driver, see
 * \ref asfdoc_samb_i2c_exqsg.
 *
 * \section asfdoc_samb_i2c_api_overview API Overview
 * @{
 */


/** \brief Transfer direction
 *
 * For master: transfer direction or setting direction bit in address.
 * For slave: direction of request from master.
 */
enum i2c_transfer_direction {
	/** Master write operation is in progress */
	I2C_TRANSFER_WRITE = 0,
	/** Master read operation is in progress */
	I2C_TRANSFER_READ  = 1,
};

/**
 * \brief I2C module clock input 
 *
 * I2C module clock.
 *
 */
enum i2c_clock_input {
	/** source from clock input 0: 26MHz */
	I2C_CLK_INPUT_0 = 0,
	/** source from clock input 1: 13MHz */
	I2C_CLK_INPUT_1,
	/** source from clock input 2: 6.5MHz */
	I2C_CLK_INPUT_2,
	/** source from clock input 3: 3MHz */
	I2C_CLK_INPUT_3,
};

/**
 * \brief Wait for idle
 *
 * Wait for hardware module to sync
 *
 * \param[in]  i2c_module  Pointer to software module structure
 */
static inline void i2c_wait_for_idle(I2c *const i2c_module)
{
	while (i2c_module->I2C_STATUS.bit.I2C_ACTIVE) {
		/* Wait for I2C module to sync. */
	}
}

/**
 * \brief Enable driver instance
 *
 * This function enable driver instance
 *
 * \param[in,out] module Pointer to the driver instance to enable
 *
 */
static inline void i2c_enable(I2c *const i2c_module)
{
	/* Wait for module to sync. */
	i2c_wait_for_idle(i2c_module);
	/* Enable module. */
	i2c_module->I2C_MODULE_ENABLE.reg = (1 << I2C_MODULE_ENABLE_ENABLE_Pos);
}

/**
 * \brief Disable driver instance
 *
 * This function disable driver instance
 *
 * \param[in,out] i2c_module Pointer to the driver instance to disable
 *
 */
static inline void i2c_disable(I2c *const i2c_module)
{
	i2c_wait_for_idle(i2c_module);
	i2c_module->I2C_MODULE_ENABLE.reg = 0;
}

/**
 * \brief Flush the contents of both the Tx and Rx FIFOs
 *
 * This function flushes the contents of both the Tx and Rx FIFOs.
 *
 * \param[in,out] i2c_module Pointer to the driver instance
 *
 */
static inline void i2c_slave_flush_fifo(I2c *const i2c_module)
{
	i2c_wait_for_idle(i2c_module);
	i2c_module->I2C_FLUSH.reg = 1;
}

/**
 * \brief Enable or Disable slave rx interrupt
 *
 * This function enables or disables slave rx interrupt.
 *
 * \param[in,out] i2c_module Pointer to the driver
 * \param[in]     enable     Enable or Disable
 *
 */
static inline void i2c_slave_rx_interrupt(I2c *const i2c_module, bool enable)
{
	if (enable) {
		i2c_module->RX_INTERRUPT_MASK.bit.RX_FIFO_NOT_EMPTY_MASK = 1;
	} else {
		i2c_module->RX_INTERRUPT_MASK.bit.RX_FIFO_NOT_EMPTY_MASK = 0;
	}
}

/**
 * \brief Enable or Disable slave tx interrupt
 *
 * This function enables or disables slave tx interrupt.
 *
 * \param[in,out] i2c_module Pointer to the driver
 * \param[in]     enable     Enable or Disable
 *
 */
static inline void i2c_slave_tx_interrupt(I2c *const i2c_module, bool enable)
{
	if (enable) {
		i2c_module->TX_INTERRUPT_MASK.bit.TX_FIFO_NOT_FULL_MASK = 1;
		i2c_module->RX_INTERRUPT_MASK.bit.NAK_MASK = 1;
	} else {
		i2c_module->TX_INTERRUPT_MASK.bit.TX_FIFO_NOT_FULL_MASK = 0;
		i2c_module->RX_INTERRUPT_MASK.bit.NAK_MASK = 0;
	}
}
/** @} */

#ifdef __cplusplus
}
#endif

/**
 * \page asfdoc_samb_i2c_extra_info_page  Extra Information for I2C Driver
 *
 * \section asfdoc_samb_i2c_acronyms Acronyms
 * \ref asfdoc_samb_i2c_acronyms_table "Below" is a table listing the acronyms
 * used in this module, along with their intended meanings.
 *
 * \anchor asfdoc_samb_i2c_acronyms_table
 * <table>
 *  <caption>Acronyms</caption>
 *	<tr>
 *		<th>Acronym</th>
 *		<th>Description</th>
 *	</tr>
 *	<tr>
 *		<td>SDA</td>
 *		<td>Serial Data Line</td>
 *	</tr>
 *	<tr>
 *		<td>SCL</td>
 *		<td>Serial Clock Line</td>
 *	</tr>
 * </table>
 *
 * \section asfdoc_samb_i2c_extra_dependencies Dependencies
 * There are no dependencies related to this driver.
 *
 *
 * \section asfdoc_samb_i2c_extra_errata Errata
 * There are no errata related to this driver.
 *
 * \section asfdoc_samb_i2c_extra_history Module History
 * \ref asfdoc_samb_i2c_extra_history_table "Below" is an overview of the
 * module history, detailing enhancements and fixes made to the module since
 * its first release. The current version of this corresponds to the newest
 * version listed in
 * \ref asfdoc_samb_i2c_extra_history_table "the table below".
 *
 * \anchor asfdoc_samb_i2c_extra_history_table
 * <table>
 *  <caption>Module History</caption>
 *	<tr>
 *		<th>Changelog</th>
 *	</tr>
 *	<tr>
 *		<td>Initial Release</td>
 *	</tr>
 * </table>
 */

/**
 * \page asfdoc_samb_i2c_exqsg Examples for I2C Driver
 *
 * This is a list of the available Quick Start guides (QSGs) and example
 * applications for \ref asfdoc_samb_i2c_group. QSGs are simple examples with
 * step-by-step instructions to configure and use this driver in a selection of
 * use cases. Note that QSGs can be compiled as a standalone application or be
 * added to the user application.
 *
 * \if I2C_MASTER_MODE
 * - \subpage asfdoc_samb_i2c_master_basic_use_case "Quick Start Guide for the I2C Master module - Basic Use Case"
 * \endif
 * \if I2C_MASTER_CALLBACK_MODE
 * - \subpage asfdoc_samb_i2c_master_callback_use_case "Quick Start Guide for the I2C Master module - Callback Use Case"
 * \endif
 * \if I2C_SLAVE_MODE
 * - \subpage asfdoc_samb_i2c_slave_basic_use_case "Quick Start Guide for the I2C Slave module - Basic Use Case"
 * \endif
 * \if I2C_SLAVE_CALLBACK_MODE
 * - \subpage asfdoc_samb_i2c_slave_callback_use_case "Quick Start Guide for the I2C Slave module - Callback Use Case"
 * \endif
 *
 * \page asfdoc_samb_i2c_document_revision_history Document Revision History
 *
 * <table>
 *	<tr>
 *		<th>Doc. Rev.</td>
 *		<th>Date</td>
 *		<th>Comments</td>
 *	</tr>
 *	<tr>
 *		<td>A</td>
 *		<td>09/2015</td>
 *		<td>Initial release</td>
 *	</tr>
 * </table>
 */

#endif /* I2C_COMMON_H_INCLUDED */
