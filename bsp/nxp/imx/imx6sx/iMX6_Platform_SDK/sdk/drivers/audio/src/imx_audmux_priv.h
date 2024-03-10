/*
 * Copyright (c) 2011-2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
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
 */

//! @addtogroup diag_audio
//! @{

/*! 
 * @file imx-audmux-priv.h
 * @brief imx-audmux private macros.
 */

//------------------------------------------------------------------------------
// REGISTER BIT WRITE VALUES
//------------------------------------------------------------------------------

// PTCR
#define AUDMUX_PTCR_SYN_ASYNC               0   // Asynchronous mode
#define AUDMUX_PTCR_SYN_SYNC                1   // Synchronous mode

#define AUDMUX_PTCR_RCSEL_TXCLK_PORT1       0   // RXCLK is TXCLK from port1
#define AUDMUX_PTCR_RCSEL_TXCLK_PORT2       1   // RXCLK is TXCLK from port2
#define AUDMUX_PTCR_RCSEL_TXCLK_PORT3       2   // RXCLK is TXCLK from port3
#define AUDMUX_PTCR_RCSEL_TXCLK_PORT4       3   // RXCLK is TXCLK from port4
#define AUDMUX_PTCR_RCSEL_TXCLK_PORT5       4   // RXCLK is TXCLK from port5
#define AUDMUX_PTCR_RCSEL_TXCLK_PORT6       5   // RXCLK is TXCLK from port6
#define AUDMUX_PTCR_RCSEL_TXCLK_PORT7       6   // RXCLK is TXCLK from port7
#define AUDMUX_PTCR_RCSEL_RXCLK_PORT1       8   // RXCLK is RXCLK from port1
#define AUDMUX_PTCR_RCSEL_RXCLK_PORT2       9   // RXCLK is RXCLK from port2
#define AUDMUX_PTCR_RCSEL_RXCLK_PORT3       10  // RXCLK is RXCLK from port3
#define AUDMUX_PTCR_RCSEL_RXCLK_PORT4       11  // RXCLK is RXCLK from port4
#define AUDMUX_PTCR_RCSEL_RXCLK_PORT5       12  // RXCLK is RXCLK from port5
#define AUDMUX_PTCR_RCSEL_RXCLK_PORT6       13  // RXCLK is RXCLK from port6
#define AUDMUX_PTCR_RCSEL_RXCLK_PORT7       14  // RXCLK is RXCLK from port7

#define AUDMUX_PTCR_RCLKDIR_INPUT           0   // RXCLK is an input
#define AUDMUX_PTCR_RCLKDIR_OUTPUT          1   // RXCLK is an output

#define AUDMUX_PTCR_RFSEL_TXFS_PORT1        0   // RXFS is TXFS from port1
#define AUDMUX_PTCR_RFSEL_TXFS_PORT2        1   // RXFS is TXFS from port2
#define AUDMUX_PTCR_RFSEL_TXFS_PORT3        2   // RXFS is TXFS from port3
#define AUDMUX_PTCR_RFSEL_TXFS_PORT4        3   // RXFS is TXFS from port4
#define AUDMUX_PTCR_RFSEL_TXFS_PORT5        4   // RXFS is TXFS from port5
#define AUDMUX_PTCR_RFSEL_TXFS_PORT6        5   // RXFS is TXFS from port6
#define AUDMUX_PTCR_RFSEL_TXFS_PORT7        6   // RXFS is TXFS from port7
#define AUDMUX_PTCR_RFSEL_RXFS_PORT1        8   // RXFS is RXFS from port1
#define AUDMUX_PTCR_RFSEL_RXFS_PORT2        9   // RXFS is RXFS from port2
#define AUDMUX_PTCR_RFSEL_RXFS_PORT3        10  // RXFS is RXFS from port3
#define AUDMUX_PTCR_RFSEL_RXFS_PORT4        11  // RXFS is RXFS from port4
#define AUDMUX_PTCR_RFSEL_RXFS_PORT5        12  // RXFS is RXFS from port5
#define AUDMUX_PTCR_RFSEL_RXFS_PORT6        13  // RXFS is RXFS from port6
#define AUDMUX_PTCR_RFSEL_RXFS_PORT7        14  // RXFS is RXFS from port7

#define AUDMUX_PTCR_RFSDIR_INPUT            0   // RXFS is an input
#define AUDMUX_PTCR_RFSDIR_OUTPUT           1   // RXFS is an output

#define AUDMUX_PTCR_TCSEL_TXCLK_PORT1       0   // TXCLK is TXCLK from port1
#define AUDMUX_PTCR_TCSEL_TXCLK_PORT2       1   // TXCLK is TXCLK from port2
#define AUDMUX_PTCR_TCSEL_TXCLK_PORT3       2   // TXCLK is TXCLK from port3
#define AUDMUX_PTCR_TCSEL_TXCLK_PORT4       3   // TXCLK is TXCLK from port4
#define AUDMUX_PTCR_TCSEL_TXCLK_PORT5       4   // TXCLK is TXCLK from port5
#define AUDMUX_PTCR_TCSEL_TXCLK_PORT6       5   // TXCLK is TXCLK from port6
#define AUDMUX_PTCR_TCSEL_TXCLK_PORT7       6   // TXCLK is TXCLK from port7
#define AUDMUX_PTCR_TCSEL_RXCLK_PORT1       8   // TXCLK is RXCLK from port1
#define AUDMUX_PTCR_TCSEL_RXCLK_PORT2       9   // TXCLK is RXCLK from port2
#define AUDMUX_PTCR_TCSEL_RXCLK_PORT3       10  // TXCLK is RXCLK from port3
#define AUDMUX_PTCR_TCSEL_RXCLK_PORT4       11  // TXCLK is RXCLK from port4
#define AUDMUX_PTCR_TCSEL_RXCLK_PORT5       12  // TXCLK is RXCLK from port5
#define AUDMUX_PTCR_TCSEL_RXCLK_PORT6       13  // TXCLK is RXCLK from port6
#define AUDMUX_PTCR_TCSEL_RXCLK_PORT7       14  // TXCLK is RXCLK from port7

#define AUDMUX_PTCR_TCLKDIR_INPUT           0   // TXCLK is an input
#define AUDMUX_PTCR_TCLKDIR_OUTPUT          1   // TXCLK is an output

#define AUDMUX_PTCR_TFSEL_TXFS_PORT1        0   // TXFS is TXFS from port1
#define AUDMUX_PTCR_TFSEL_TXFS_PORT2        1   // TXFS is TXFS from port2
#define AUDMUX_PTCR_TFSEL_TXFS_PORT3        2   // TXFS is TXFS from port3
#define AUDMUX_PTCR_TFSEL_TXFS_PORT4        3   // TXFS is TXFS from port4
#define AUDMUX_PTCR_TFSEL_TXFS_PORT5        4   // TXFS is TXFS from port5
#define AUDMUX_PTCR_TFSEL_TXFS_PORT6        5   // TXFS is TXFS from port6
#define AUDMUX_PTCR_TFSEL_TXFS_PORT7        6   // TXFS is TXFS from port7
#define AUDMUX_PTCR_TFSEL_RXFS_PORT1        8   // TXFS is RXFS from port1
#define AUDMUX_PTCR_TFSEL_RXFS_PORT2        9   // TXFS is RXFS from port2
#define AUDMUX_PTCR_TFSEL_RXFS_PORT3        10  // TXFS is RXFS from port3
#define AUDMUX_PTCR_TFSEL_RXFS_PORT4        11  // TXFS is RXFS from port4
#define AUDMUX_PTCR_TFSEL_RXFS_PORT5        12  // TXFS is RXFS from port5
#define AUDMUX_PTCR_TFSEL_RXFS_PORT6        13  // TXFS is RXFS from port6
#define AUDMUX_PTCR_TFSEL_RXFS_PORT7        14  // TXFS is RXFS from port7

#define AUDMUX_PTCR_TFSDIR_INPUT            0   // TXFS is an input
#define AUDMUX_PTCR_TFSDIR_OUTPUT           1   // TXFS is an output

// PDCR
#define AUDMUX_PDCR_INMMASK_EXC_RXD1     0x01   // Exclude port1 RXD from network
#define AUDMUX_PDCR_INMMASK_EXC_RXD2     0x02   // Exclude port1 RXD from network
#define AUDMUX_PDCR_INMMASK_EXC_RXD3     0x04   // Exclude port1 RXD from network
#define AUDMUX_PDCR_INMMASK_EXC_RXD4     0x08   // Exclude port1 RXD from network
#define AUDMUX_PDCR_INMMASK_EXC_RXD5     0x10   // Exclude port1 RXD from network
#define AUDMUX_PDCR_INMMASK_EXC_RXD6     0x20   // Exclude port1 RXD from network
#define AUDMUX_PDCR_INMMASK_EXC_RXD7     0x40   // Exclude port1 RXD from network

#define AUDMUX_PDCR_MODE_NORMAL             0   // Normal mode
#define AUDMUX_PDCR_MODE_INT_NET            1   // Internal network mode
#define AUDMUX_PDCR_MODE_CEBUS_NET          1   // CE Bus network mode

#define AUDMUX_PDCR_TXRXEN_NO_SWAP          0   // No swapping of RX/TX signals
#define AUDMUX_PDCR_TXRXEN_SWAP             1   // Swap RX/TX signals

#define AUDMUX_PDCR_RXDSEL_PORT1            0   // Port1 is source for RxD data
#define AUDMUX_PDCR_RXDSEL_PORT2            1   // Port2 is source for RxD data
#define AUDMUX_PDCR_RXDSEL_PORT3            2   // Port3 is source for RxD data
#define AUDMUX_PDCR_RXDSEL_PORT4            3   // Port4 is source for RxD data
#define AUDMUX_PDCR_RXDSEL_PORT5            4   // Port5 is source for RxD data
#define AUDMUX_PDCR_RXDSEL_PORT6            5   // Port6 is source for RxD data
#define AUDMUX_PDCR_RXDSEL_PORT7            6   // Port7 is source for RxD data

#define AUDMUX_PORT_INDEX_MIN		1
#define AUDMUX_PORT_INDEX_MAX		7

//! Macro for PTCR reading
#define HW_AUDMUX_PTCR_RD(port)		(port) == AUDMUX_PORT_1 ? HW_AUDMUX_PTCR1_RD() : \
					(port) == AUDMUX_PORT_2 ? HW_AUDMUX_PTCR2_RD() : \
					(port) == AUDMUX_PORT_3 ? HW_AUDMUX_PTCR3_RD() : \
					(port) == AUDMUX_PORT_4 ? HW_AUDMUX_PTCR4_RD() : \
					(port) == AUDMUX_PORT_5 ? HW_AUDMUX_PTCR5_RD() : \
					(port) == AUDMUX_PORT_6 ? HW_AUDMUX_PTCR6_RD() : \
					HW_AUDMUX_PTCR7_RD()

//! Macro for PTCR writting
#define HW_AUDMUX_PTCR_WR(port, v)	(port) == AUDMUX_PORT_1 ? HW_AUDMUX_PTCR1_WR((v)) : \
					(port) == AUDMUX_PORT_2 ? HW_AUDMUX_PTCR2_WR((v)) : \
					(port) == AUDMUX_PORT_3 ? HW_AUDMUX_PTCR3_WR((v)) : \
					(port) == AUDMUX_PORT_4 ? HW_AUDMUX_PTCR4_WR((v)) : \
					(port) == AUDMUX_PORT_5 ? HW_AUDMUX_PTCR5_WR((v)) : \
					(port) == AUDMUX_PORT_6 ? HW_AUDMUX_PTCR6_WR((v)) : \
					HW_AUDMUX_PTCR7_WR((v))

//! Macro for PDCR reading
#define HW_AUDMUX_PDCR_RD(port)		(port) == AUDMUX_PORT_1 ? HW_AUDMUX_PDCR1_RD() : \
					(port) == AUDMUX_PORT_2 ? HW_AUDMUX_PDCR2_RD() : \
					(port) == AUDMUX_PORT_3 ? HW_AUDMUX_PDCR3_RD() : \
					(port) == AUDMUX_PORT_4 ? HW_AUDMUX_PDCR4_RD() : \
					(port) == AUDMUX_PORT_5 ? HW_AUDMUX_PDCR5_RD() : \
					(port) == AUDMUX_PORT_6 ? HW_AUDMUX_PDCR6_RD() : \
					HW_AUDMUX_PDCR7_RD()

//! Macro for PDCR writting
#define HW_AUDMUX_PDCR_WR(port, v)	(port) == AUDMUX_PORT_1 ? HW_AUDMUX_PDCR1_WR((v)) : \
					(port) == AUDMUX_PORT_2 ? HW_AUDMUX_PDCR2_WR((v)) : \
					(port) == AUDMUX_PORT_3 ? HW_AUDMUX_PDCR3_WR((v)) : \
					(port) == AUDMUX_PORT_4 ? HW_AUDMUX_PDCR4_WR((v)) : \
					(port) == AUDMUX_PORT_5 ? HW_AUDMUX_PDCR5_WR((v)) : \
					(port) == AUDMUX_PORT_6 ? HW_AUDMUX_PDCR6_WR((v)) : \
					HW_AUDMUX_PDCR7_WR((v))
