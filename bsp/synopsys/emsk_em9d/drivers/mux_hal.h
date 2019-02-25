/*
 * Copyright (c) 2018, Synopsys, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef _MUX_HAL_H_
#define _MUX_HAL_H_

/**
 * \name	Mux Control Register Index
 * @{
 */
#define PMOD_MUX_CTRL	0	/*!< 32-bits, offset 0x0,
					This register controls mapping of the peripheral device signals on Pmod connectors */

#define I2C_MAP_CTRL	1	/*!< 32-bits, offset 0x4 */

#define SPI_MAP_CTRL	2	/*!< 32-bits, offset 0x8,
					SPI_MAP_CTRL[0] selects the mode of operation of the SPI Slave:
					- Normal operation, SPI_MAP_CTRL[0]=0: SPI Slave is connected to Pmod1 at connector J1.
					- Loop-back mode, SPI_MAP_CTRL[0]=1: SPI Slave is connected to the SPI Master inside the FPGA using CS4.
							 */

#define UART_MAP_CTRL	3	/*!< 32-bits, offset 0x8,
					This register controls the mapping of the UART signals on the Pmod1 connector. */
/** @} end of name */


#endif	/* _MUX_HAL_H_ */
