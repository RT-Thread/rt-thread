/***************************************************************************//**
* \file cyip_eth.h
*
* \brief
* ETH IP definitions
*
********************************************************************************
* \copyright
* (c) (2016-2022), Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.
*
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#ifndef _CYIP_ETH_H_
#define _CYIP_ETH_H_

#include "cyip_headers.h"

/*******************************************************************************
*                                     ETH
*******************************************************************************/

#define ETH_SECTION_SIZE                        0x00010000UL

/**
  * \brief Ethernet Interface (ETH)
  */
typedef struct {
  __IOM uint32_t CTL;                           /*!< 0x00000000 MXETH Control Register */
   __IM uint32_t STATUS;                        /*!< 0x00000004 MXETH Status Register */
   __IM uint32_t RESERVED[1022];
  __IOM uint32_t NETWORK_CONTROL;               /*!< 0x00001000 The network control register contains general MAC control
                                                                functions for both receiver and transmitter. */
  __IOM uint32_t NETWORK_CONFIG;                /*!< 0x00001004 The network configuration register contains functions for
                                                                setting the mode of operation for the Gigabit Ethernet MAC. */
   __IM uint32_t NETWORK_STATUS;                /*!< 0x00001008 The network status register returns status information with
                                                                respect to the PHY management interface. */
   __IM uint32_t USER_IO_REGISTER;              /*!< 0x0000100C Not presents. Access to the register will return AHB error. */
  __IOM uint32_t DMA_CONFIG;                    /*!< 0x00001010 DMA Configuration Register */
  __IOM uint32_t TRANSMIT_STATUS;               /*!< 0x00001014 This register, when read, provides details of the status of a
                                                                transmit. Once read, individual bits may be cleared by writing 1
                                                                to them. It is not possible to set a bit to 1 by writing to the
                                                                register. */
  __IOM uint32_t RECEIVE_Q_PTR;                 /*!< 0x00001018 This register holds the start address of the receive buffer
                                                                queue (receive buffers descriptor list). The receive buffer
                                                                queue base address must be initialized before receive is enabled
                                                                through bit 2 of the network control register. Once reception is
                                                                enabled, any write to the receive buffer queue base address
                                                                register is ignored. Reading this register returns the location
                                                                of the descriptor currently being accessed. This value
                                                                increments as buffers are used. Software should not use this
                                                                register for determining where to remove received frames from
                                                                the queue as it constantly changes as new frames are received.
                                                                Software should instead work its way through the buffer
                                                                descriptor queue checking the used bits. In terms of AMBA (AXI)
                                                                operation, the receive descriptors are read from memory using a
                                                                single 32bit AXI access. When the datapath is configured at
                                                                64bit, the receive descriptors should be aligned at 64-bit
                                                                boundaries and each pair of 32-bit descriptors is written to
                                                                using a single 64bit AXI access. */
  __IOM uint32_t TRANSMIT_Q_PTR;                /*!< 0x0000101C This register holds the start address of the transmit buffer
                                                                queue (transmit buffers descriptor list). The transmit buffer
                                                                queue base address register must be initialized before transmit
                                                                is started through bit 9 of the network control register. Once
                                                                transmission has started, any write to the transmit buffer queue
                                                                base address register is illegal and therefore ignored. Note
                                                                that due to clock boundary synchronization, it takes a maximum
                                                                of four pclk cycles from the writing of the transmit start bit
                                                                before the transmitter is active. Writing to the transmit buffer
                                                                queue base address register during this time may produce
                                                                unpredictable results. Reading this register returns the
                                                                location of the descriptor currently being accessed. Because the
                                                                DMA can store data for multiple frames at once, this may not
                                                                necessarily be pointing to the current frame being transmitted.
                                                                In terms of AMBA AXI operation, the transmit descriptors are
                                                                written to memory using a single 32bit AHB access. When the
                                                                datapath is configured as 64bit, the transmit descriptors should
                                                                be aligned at 64-bit boundaries and each pair of 32-bit
                                                                descriptors is read from memory using a single AXI access. */
  __IOM uint32_t RECEIVE_STATUS;                /*!< 0x00001020 This register, when read provides details of the status of a
                                                                receive. Once read, individual bits may be cleared by writing 1
                                                                to them. It is not possible to set a bit to 1 by writing to the
                                                                register. */
  __IOM uint32_t INT_STATUS;                    /*!< 0x00001024 If not configured for priority queueing, the GEM generates a
                                                                single interrupt. This register indicates the source of this
                                                                interrupt. The corresponding bit in the mask register must be
                                                                clear for a bit to be set. If any bit is set in this register
                                                                the ethernet_int signal will be asserted. For test purposes each
                                                                bit can be set or reset by writing to the interrupt mask
                                                                register. The default configuration is shown below whereby all
                                                                bits are reset to zero on read. Changing the validity of the
                                                                `gem_irq_read_clear define will instead require a one to be
                                                                written to the appropriate bit in order to clear it. In this
                                                                mode reading has no affect on the status of the bit. */
   __OM uint32_t INT_ENABLE;                    /*!< 0x00001028 At reset all interrupts are disabled. Writing a one to the
                                                                relevant bit location enables the required interrupt. This
                                                                register is write only and when read will return zero. */
  __IOM uint32_t INT_DISABLE;                   /*!< 0x0000102C Writing a 1 to the relevant bit location disables that
                                                                particular interrupt. This register is write only and when read
                                                                will return zero. */
   __IM uint32_t INT_MASK;                      /*!< 0x00001030 The interrupt mask register is a read only register indicating
                                                                which interrupts are masked. All bits are set at reset and can
                                                                be reset individually by writing to the interrupt enable
                                                                register or set individually by writing to the interrupt disable
                                                                register. Having separate address locations for enable and
                                                                disable saves the need for performing a read modify write when
                                                                updating the interrupt mask register. For test purposes there is
                                                                a write-only function to this register that allows the bits in
                                                                the interrupt status register to be set or cleared, regardless
                                                                of the state of the mask register. */
  __IOM uint32_t PHY_MANAGEMENT;                /*!< 0x00001034 The PHY maintenance register is implemented as a shift
                                                                register. Writing to the register starts a shift operation which
                                                                is signalled as complete when bit-2 is set in the network status
                                                                register. It takes about 2000 pclk cycles to complete, when MDC
                                                                is set for pclk divide by 32 in the network configuration
                                                                register. An interrupt is generated upon completion. During this
                                                                time, the MSB of the register is output on the MDIO pin and the
                                                                LSB updated from the MDIO pin with each MDC cycle. This causes
                                                                transmission of a PHY management frame on MDIO. See Section
                                                                22.2.4.5 of the IEEE 802.3 standard. Reading during the shift
                                                                operation will return the current contents of the shift
                                                                register. At the end of management operation, the bits will have
                                                                shifted back to their original locations. For a read operation,
                                                                the data bits will be updated with data read from the PHY. It is
                                                                important to write the correct values to the register to ensure
                                                                a valid PHY management frame is produced. The MDIO interface can
                                                                read IEEE 802.3 clause 45 PHYs as well as clause 22 PHYs. To
                                                                read clause 45 PHYs, bit 30 should be written with a 0 rather
                                                                than a 1. For a description of MDC generation, see Network
                                                                Configuration Register. */
   __IM uint32_t PAUSE_TIME;                    /*!< 0x00001038 Received Pause Quantum Register */
  __IOM uint32_t TX_PAUSE_QUANTUM;              /*!< 0x0000103C Transmit Pause Quantum Register */
  __IOM uint32_t PBUF_TXCUTTHRU;                /*!< 0x00001040 Partial store and forward is only applicable when using the DMA
                                                                configured in SRAM based packet buffer mode. It is also not
                                                                available when using multi buffer frames. TX Partial Store and
                                                                Forward */
  __IOM uint32_t PBUF_RXCUTTHRU;                /*!< 0x00001044 RX Partial Store and Forward */
  __IOM uint32_t JUMBO_MAX_LENGTH;              /*!< 0x00001048 Maximum Jumbo Frame Size. */
   __IM uint32_t EXTERNAL_FIFO_INTERFACE;       /*!< 0x0000104C Not presents. */
   __IM uint32_t RESERVED1;
  __IOM uint32_t AXI_MAX_PIPELINE;              /*!< 0x00001054 Used to set the maximum amount of outstanding transactions on
                                                                the AXI bus between AR / R channels and AW / W channels. Cannot
                                                                be more than the depth of the configured AXI pipeline FIFO
                                                                (defined in verilog defs.v) */
   __IM uint32_t RSC_CONTROL;                   /*!< 0x00001058 Not presents. Access to the register will return AHB error. */
  __IOM uint32_t INT_MODERATION;                /*!< 0x0000105C Used to moderate the number of transmit and receive complete
                                                                interrupts issued. With interrupt moderation enabled receive and
                                                                transmit interrupts are not generated immediately a frame is
                                                                transmitted or received. Instead when a receive or transmit
                                                                event occurs a timer is started and the interrupt is asserted
                                                                after it times out. This limits the frequency with which the CPU
                                                                receives interrupts. When interrupt moderation is enabled
                                                                interrupt status bit one is always used for receive and bit 7 is
                                                                always used for transmit even when priority queuing is enabled.
                                                                With interrupt moderation 800ns periods are counted. GEM
                                                                determines what constitutes an 800ns period by looking at the
                                                                tbi (bit 11), gigabit bit (10) and speed (bit 0) bits in the
                                                                network configuration register and counting tx_clk cycles. Bit 0
                                                                needs to be set to 1 for 100M operation. */
  __IOM uint32_t SYS_WAKE_TIME;                 /*!< 0x00001060 Used to pause transmission after deassertion of tx_lpi_en. Each
                                                                unit in this register corresponds to 64ns in gigabit mode, 320ns
                                                                in 100M mode and 3200ns at 10M. After tx_lpi_en is deasserted
                                                                transmission will pause for the set time. */
   __IM uint32_t RESERVED2[7];
  __IOM uint32_t HASH_BOTTOM;                   /*!< 0x00001080 The unicast hash enable and the multicast hash enable bits in
                                                                the network configuration register enable the reception of hash
                                                                matched frames. Hash Register Bottom (31 to 0 bits) */
  __IOM uint32_t HASH_TOP;                      /*!< 0x00001084 Hash Register Top (63 to 32 bits) */
  __IOM uint32_t SPEC_ADD1_BOTTOM;              /*!< 0x00001088 The addresses stored in the specific address registers are
                                                                deactivated at reset or when their corresponding specific
                                                                address register bottom is written. They are activated when
                                                                specific address register top is written. */
  __IOM uint32_t SPEC_ADD1_TOP;                 /*!< 0x0000108C Specific Address Top */
  __IOM uint32_t SPEC_ADD2_BOTTOM;              /*!< 0x00001090 The addresses stored in the specific address registers are
                                                                deactivated at reset or when their corresponding specific
                                                                address register bottom is written. They are activated when
                                                                specific address register top is written. */
  __IOM uint32_t SPEC_ADD2_TOP;                 /*!< 0x00001094 Specific Address Top */
  __IOM uint32_t SPEC_ADD3_BOTTOM;              /*!< 0x00001098 The addresses stored in the specific address registers are
                                                                deactivated at reset or when their corresponding specific
                                                                address register bottom is written. They are activated when
                                                                specific address register top is written. */
  __IOM uint32_t SPEC_ADD3_TOP;                 /*!< 0x0000109C Specific Address Top */
  __IOM uint32_t SPEC_ADD4_BOTTOM;              /*!< 0x000010A0 The addresses stored in the specific address registers are
                                                                deactivated at reset or when their corresponding specific
                                                                address register bottom is written. They are activated when
                                                                specific address register top is written. */
  __IOM uint32_t SPEC_ADD4_TOP;                 /*!< 0x000010A4 Specific Address Top */
  __IOM uint32_t SPEC_TYPE1;                    /*!< 0x000010A8 Type ID Match 1 */
  __IOM uint32_t SPEC_TYPE2;                    /*!< 0x000010AC Type ID Match 2 */
  __IOM uint32_t SPEC_TYPE3;                    /*!< 0x000010B0 Type ID Match 3 */
  __IOM uint32_t SPEC_TYPE4;                    /*!< 0x000010B4 Type ID Match 4 */
  __IOM uint32_t WOL_REGISTER;                  /*!< 0x000010B8 Wake on LAN Register. Presents in design, but feature is not
                                                                supported. */
  __IOM uint32_t STRETCH_RATIO;                 /*!< 0x000010BC IPG stretch register */
  __IOM uint32_t STACKED_VLAN;                  /*!< 0x000010C0 Stacked VLAN Register */
  __IOM uint32_t TX_PFC_PAUSE;                  /*!< 0x000010C4 Transmit PFC Pause Register */
  __IOM uint32_t MASK_ADD1_BOTTOM;              /*!< 0x000010C8 Specific Address Mask 1 Bottom (31 to 0 bits) */
  __IOM uint32_t MASK_ADD1_TOP;                 /*!< 0x000010CC Specific Address Mask 1 Top (47 to 32 bits) */
  __IOM uint32_t DMA_ADDR_OR_MASK;              /*!< 0x000010D0 Receive DMA Data Buffer Address Mask */
  __IOM uint32_t RX_PTP_UNICAST;                /*!< 0x000010D4 PTP RX unicast IP destination address */
  __IOM uint32_t TX_PTP_UNICAST;                /*!< 0x000010D8 PTP TX unicast IP destination address */
  __IOM uint32_t TSU_NSEC_CMP;                  /*!< 0x000010DC TSU timer comparison value nanoseconds */
  __IOM uint32_t TSU_SEC_CMP;                   /*!< 0x000010E0 TSU timer comparison value seconds (31 to 0 bits) */
  __IOM uint32_t TSU_MSB_SEC_CMP;               /*!< 0x000010E4 TSU timer comparison value seconds (47 to 32 bits) */
   __IM uint32_t TSU_PTP_TX_MSB_SEC;            /*!< 0x000010E8 PTP Event Frame Transmitted Seconds Register (47 to 32 bits) */
   __IM uint32_t TSU_PTP_RX_MSB_SEC;            /*!< 0x000010EC PTP Event Frame Received Seconds Register (47 to 32 bits) */
   __IM uint32_t TSU_PEER_TX_MSB_SEC;           /*!< 0x000010F0 PTP Peer Event Frame Transmitted Seconds Register (47 to 32
                                                                bits) */
   __IM uint32_t TSU_PEER_RX_MSB_SEC;           /*!< 0x000010F4 PTP Peer Event Frame Received Seconds Register (47 to 32 bits) */
  __IOM uint32_t DPRAM_FILL_DBG;                /*!< 0x000010F8 The fill levels for the TX & RX packet buffers can be read
                                                                using this register, including the fill level for each queue in
                                                                the TX direction. */
   __IM uint32_t REVISION_REG;                  /*!< 0x000010FC This register indicates a Cadence module identification number
                                                                and module revision. The value of this register is read only as
                                                                defined by `gem_revision_reg_value */
   __IM uint32_t OCTETS_TXED_BOTTOM;            /*!< 0x00001100 Octets Transmitted lower bits (31 to 0 bits) */
   __IM uint32_t OCTETS_TXED_TOP;               /*!< 0x00001104 Octets Transmitted higher bits (47 to 32 bits) */
   __IM uint32_t FRAMES_TXED_OK;                /*!< 0x00001108 Frames Transmitted */
   __IM uint32_t BROADCAST_TXED;                /*!< 0x0000110C Broadcast Frames Transmitted */
   __IM uint32_t MULTICAST_TXED;                /*!< 0x00001110 Multicast Frames Transmitted */
   __IM uint32_t PAUSE_FRAMES_TXED;             /*!< 0x00001114 Pause Frames Transmitted */
   __IM uint32_t FRAMES_TXED_64;                /*!< 0x00001118 64 Byte Frames Transmitted */
   __IM uint32_t FRAMES_TXED_65;                /*!< 0x0000111C 65 to 127 Byte Frames Transmitted */
   __IM uint32_t FRAMES_TXED_128;               /*!< 0x00001120 128 to 255 Byte Frames Transmitted */
   __IM uint32_t FRAMES_TXED_256;               /*!< 0x00001124 256 to 511 Byte Frames Transmitted */
   __IM uint32_t FRAMES_TXED_512;               /*!< 0x00001128 512 to 1023 Byte Frames Transmitted */
   __IM uint32_t FRAMES_TXED_1024;              /*!< 0x0000112C 1024 to 1518 Byte Frames Transmitted */
   __IM uint32_t FRAMES_TXED_1519;              /*!< 0x00001130 Greater Than 1518 Byte Frames Transmitted */
   __IM uint32_t TX_UNDERRUNS;                  /*!< 0x00001134 Transmit Under Runs */
   __IM uint32_t SINGLE_COLLISIONS;             /*!< 0x00001138 Single Collision Frames. Presents in design but not support. */
   __IM uint32_t MULTIPLE_COLLISIONS;           /*!< 0x0000113C Multiple Collision Frames. Presents in design but not support. */
   __IM uint32_t EXCESSIVE_COLLISIONS;          /*!< 0x00001140 Excessive Collisions.  Presents in design but not support. */
   __IM uint32_t LATE_COLLISIONS;               /*!< 0x00001144 Late Collisions.  Presents in design but not support. */
   __IM uint32_t DEFERRED_FRAMES;               /*!< 0x00001148 Deferred Transmission Frames. Presents in design but not
                                                                support. */
   __IM uint32_t CRS_ERRORS;                    /*!< 0x0000114C Carrier Sense Errors.  Presents in design but not support. */
   __IM uint32_t OCTETS_RXED_BOTTOM;            /*!< 0x00001150 Octets Received (31 to 0 bits) */
   __IM uint32_t OCTETS_RXED_TOP;               /*!< 0x00001154 Octets Received (47 to 32 bits) */
   __IM uint32_t FRAMES_RXED_OK;                /*!< 0x00001158 Frames Received */
   __IM uint32_t BROADCAST_RXED;                /*!< 0x0000115C Broadcast Frames Received */
   __IM uint32_t MULTICAST_RXED;                /*!< 0x00001160 Multicast Frames Received */
   __IM uint32_t PAUSE_FRAMES_RXED;             /*!< 0x00001164 Pause Frames Received */
   __IM uint32_t FRAMES_RXED_64;                /*!< 0x00001168 64 Byte Frames Received */
   __IM uint32_t FRAMES_RXED_65;                /*!< 0x0000116C 65 to 127 Byte Frames Received */
   __IM uint32_t FRAMES_RXED_128;               /*!< 0x00001170 128 to 255 Byte Frames Received */
   __IM uint32_t FRAMES_RXED_256;               /*!< 0x00001174 256 to 511 Byte Frames Received */
   __IM uint32_t FRAMES_RXED_512;               /*!< 0x00001178 512 to 1023 Byte Frames Received */
   __IM uint32_t FRAMES_RXED_1024;              /*!< 0x0000117C 1024 to 1518 Byte Frames Received */
   __IM uint32_t FRAMES_RXED_1519;              /*!< 0x00001180 1519 to maximum Byte Frames Received */
   __IM uint32_t UNDERSIZE_FRAMES;              /*!< 0x00001184 Undersized Frames Received */
   __IM uint32_t EXCESSIVE_RX_LENGTH;           /*!< 0x00001188 Oversize Frames Received */
   __IM uint32_t RX_JABBERS;                    /*!< 0x0000118C Jabbers Received */
   __IM uint32_t FCS_ERRORS;                    /*!< 0x00001190 Frame Check Sequence Errors */
   __IM uint32_t RX_LENGTH_ERRORS;              /*!< 0x00001194 Length Field Frame Errors */
   __IM uint32_t RX_SYMBOL_ERRORS;              /*!< 0x00001198 Receive Symbol Errors */
   __IM uint32_t ALIGNMENT_ERRORS;              /*!< 0x0000119C Alignment Errors */
   __IM uint32_t RX_RESOURCE_ERRORS;            /*!< 0x000011A0 Receive Resource Errors */
   __IM uint32_t RX_OVERRUNS;                   /*!< 0x000011A4 Receive Overruns */
   __IM uint32_t RX_IP_CK_ERRORS;               /*!< 0x000011A8 IP Header Checksum Errors */
   __IM uint32_t RX_TCP_CK_ERRORS;              /*!< 0x000011AC TCP Checksum Errors */
   __IM uint32_t RX_UDP_CK_ERRORS;              /*!< 0x000011B0 UDP Checksum Errors */
   __IM uint32_t AUTO_FLUSHED_PKTS;             /*!< 0x000011B4 Receive DMA Flushed Packets */
   __IM uint32_t RESERVED3;
  __IOM uint32_t TSU_TIMER_INCR_SUB_NSEC;       /*!< 0x000011BC 1588 Timer Increment Register sub nsec */
  __IOM uint32_t TSU_TIMER_MSB_SEC;             /*!< 0x000011C0 1588 Timer Seconds Register (47 to 32 bits) */
   __IM uint32_t TSU_STROBE_MSB_SEC;            /*!< 0x000011C4 1588 Timer Sync Strobe Seconds Register (47 to 32 bits) */
   __IM uint32_t TSU_STROBE_SEC;                /*!< 0x000011C8 1588 Timer Sync Strobe Seconds Register (31 to 0 bits) */
   __IM uint32_t TSU_STROBE_NSEC;               /*!< 0x000011CC 1588 Timer Sync Strobe Nanoseconds Register */
  __IOM uint32_t TSU_TIMER_SEC;                 /*!< 0x000011D0 1588 Timer Seconds Register (31 to 0 bits) */
  __IOM uint32_t TSU_TIMER_NSEC;                /*!< 0x000011D4 1588 Timer Nanoseconds Register */
   __OM uint32_t TSU_TIMER_ADJUST;              /*!< 0x000011D8 This register is used to adjust the value of the timer in the
                                                                TSU. It allows an integral number of nanoseconds to be added or
                                                                subtracted from the timer in a one-off operation. This register
                                                                returns all zeroes when read. */
  __IOM uint32_t TSU_TIMER_INCR;                /*!< 0x000011DC 1588 Timer Increment Register */
   __IM uint32_t TSU_PTP_TX_SEC;                /*!< 0x000011E0 PTP Event Frame Transmitted Seconds Register (31 to 0 bits) */
   __IM uint32_t TSU_PTP_TX_NSEC;               /*!< 0x000011E4 PTP Event Frame Transmitted Nanoseconds Register */
   __IM uint32_t TSU_PTP_RX_SEC;                /*!< 0x000011E8 PTP Event Frame Received Seconds Register (31 to 0 bits) */
   __IM uint32_t TSU_PTP_RX_NSEC;               /*!< 0x000011EC PTP Event Frame Received Nanoseconds Register */
   __IM uint32_t TSU_PEER_TX_SEC;               /*!< 0x000011F0 PTP Peer Event Frame Transmitted Seconds Register (31 to 0
                                                                bits) */
   __IM uint32_t TSU_PEER_TX_NSEC;              /*!< 0x000011F4 PTP Peer Event Frame Transmitted Nanoseconds Register */
   __IM uint32_t TSU_PEER_RX_SEC;               /*!< 0x000011F8 PTP Peer Event Frame Received Seconds Register (31 to 0 bits) */
   __IM uint32_t TSU_PEER_RX_NSEC;              /*!< 0x000011FC PTP Peer Event Frame Received Nanoseconds Register */
   __IM uint32_t PCS_CONTROL;                   /*!< 0x00001200 Not presents. Access to the register returns AHB error. */
   __IM uint32_t PCS_STATUS;                    /*!< 0x00001204 Not presents. Access to the register returns AHB error. */
   __IM uint32_t RESERVED4[2];
   __IM uint32_t PCS_AN_ADV;                    /*!< 0x00001210 Not presents. Access to the register returns AHB error. */
   __IM uint32_t PCS_AN_LP_BASE;                /*!< 0x00001214 Not presents. Access to the register returns AHB error. */
   __IM uint32_t PCS_AN_EXP;                    /*!< 0x00001218 Not presents. Access to the register returns AHB error. */
   __IM uint32_t PCS_AN_NP_TX;                  /*!< 0x0000121C Not presents. Access to the register returns AHB error. */
   __IM uint32_t PCS_AN_LP_NP;                  /*!< 0x00001220 Not presents. Access to the register returns AHB error. */
   __IM uint32_t RESERVED5[6];
   __IM uint32_t PCS_AN_EXT_STATUS;             /*!< 0x0000123C Not presents. Access to the register returns AHB error. */
   __IM uint32_t RESERVED6[8];
  __IOM uint32_t TX_PAUSE_QUANTUM1;             /*!< 0x00001260 Transmit Pause Quantum Register 1 */
  __IOM uint32_t TX_PAUSE_QUANTUM2;             /*!< 0x00001264 Transmit Pause Quantum Register 2 */
  __IOM uint32_t TX_PAUSE_QUANTUM3;             /*!< 0x00001268 Transmit Pause Quantum Register 3 */
   __IM uint32_t RESERVED7;
   __IM uint32_t RX_LPI;                        /*!< 0x00001270 Received LPI transitions */
   __IM uint32_t RX_LPI_TIME;                   /*!< 0x00001274 Received LPI time */
   __IM uint32_t TX_LPI;                        /*!< 0x00001278 Transmit LPI transitions */
   __IM uint32_t TX_LPI_TIME;                   /*!< 0x0000127C Transmit LPI time */
   __IM uint32_t DESIGNCFG_DEBUG1;              /*!< 0x00001280 The GEM_GXL(3PIP) has many parameterisation options to
                                                                configure the IP during compilation stage. This is achieved
                                                                using Verilog define compiler directives in an include file
                                                                called mxeth_defs.v. */
   __IM uint32_t DESIGNCFG_DEBUG2;              /*!< 0x00001284 Design Configuration Register 2 */
   __IM uint32_t DESIGNCFG_DEBUG3;              /*!< 0x00001288 Design Configuration Register 3 */
   __IM uint32_t DESIGNCFG_DEBUG4;              /*!< 0x0000128C Design Configuration Register 4 */
   __IM uint32_t DESIGNCFG_DEBUG5;              /*!< 0x00001290 Design Configuration Register 5 */
   __IM uint32_t DESIGNCFG_DEBUG6;              /*!< 0x00001294 Design Configuration Register 6 */
   __IM uint32_t DESIGNCFG_DEBUG7;              /*!< 0x00001298 Design Configuration Register 7 */
   __IM uint32_t DESIGNCFG_DEBUG8;              /*!< 0x0000129C Design Configuration Register 8 */
   __IM uint32_t DESIGNCFG_DEBUG9;              /*!< 0x000012A0 Design Configuration Register 9 */
   __IM uint32_t DESIGNCFG_DEBUG10;             /*!< 0x000012A4 Design Configuration Register 10 */
   __IM uint32_t RESERVED8[22];
   __IM uint32_t SPEC_ADD5_BOTTOM;              /*!< 0x00001300 Specific address registers 5 ~ 36 doesn't present. Access to
                                                                the register returns AHB error. */
   __IM uint32_t SPEC_ADD5_TOP;                 /*!< 0x00001304 Specific address registers 5 ~ 36 doesn't present. Access to
                                                                the register returns AHB error. */
   __IM uint32_t RESERVED9[60];
   __IM uint32_t SPEC_ADD36_BOTTOM;             /*!< 0x000013F8 Not presents. */
   __IM uint32_t SPEC_ADD36_TOP;                /*!< 0x000013FC Not presents. */
   __IM uint32_t INT_Q1_STATUS;                 /*!< 0x00001400 Priority queue Interrupt Status Register */
   __IM uint32_t INT_Q2_STATUS;                 /*!< 0x00001404 Priority queue Interrupt Status Register */
   __IM uint32_t INT_Q3_STATUS;                 /*!< 0x00001408 int_q3_status to int_q15_status doesn't present. Access to the
                                                                register returns AHB error. */
   __IM uint32_t RESERVED10[11];
   __IM uint32_t INT_Q15_STATUS;                /*!< 0x00001438 Not presents. */
   __IM uint32_t RESERVED11;
  __IOM uint32_t TRANSMIT_Q1_PTR;               /*!< 0x00001440 This register holds the start address of the transmit buffer
                                                                queue (transmit buffers descriptor list). The transmit buffer
                                                                queue base address register must be initialized before transmit
                                                                is started through bit 9 of the network control register. Once
                                                                transmission has started, any write to the transmit buffer queue
                                                                base address register is illegal and therefore ignored. Note
                                                                that due to clock boundary synchronization, it takes a maximum
                                                                of four pclk cycles from the writing of the transmit start bit
                                                                before the transmitter is active. Writing to the transmit buffer
                                                                queue base address register during this time may produce
                                                                unpredictable results. Reading this register returns the
                                                                location of the descriptor currently being accessed. Because the
                                                                DMA can store data for multiple frames at once, this may not
                                                                necessarily be pointing to the current frame being transmitted.
                                                                In terms of AMBA AXI operation, the transmit descriptors are
                                                                written to memory using a single 32bit AHB access. When the
                                                                datapath is configured as 64bit , the transmit descriptors
                                                                should be aligned at 64-bit boundaries and each pair of 32-bit
                                                                descriptors is read from memory using a single AXI access. */
  __IOM uint32_t TRANSMIT_Q2_PTR;               /*!< 0x00001444 This register holds the start address of the transmit buffer
                                                                queue (transmit buffers descriptor list). The transmit buffer
                                                                queue base address register must be initialized before transmit
                                                                is started through bit 9 of the network control register. Once
                                                                transmission has started, any write to the transmit buffer queue
                                                                base address register is illegal and therefore ignored. Note
                                                                that due to clock boundary synchronization, it takes a maximum
                                                                of four pclk cycles from the writing of the transmit start bit
                                                                before the transmitter is active. Writing to the transmit buffer
                                                                queue base address register during this time may produce
                                                                unpredictable results. Reading this register returns the
                                                                location of the descriptor currently being accessed. Because the
                                                                DMA can store data for multiple frames at once, this may not
                                                                necessarily be pointing to the current frame being transmitted.
                                                                In terms of AMBA AXI operation, the transmit descriptors are
                                                                written to memory using a single 32bit AHB access. When the
                                                                datapath is configured as 64bit , the transmit descriptors
                                                                should be aligned at 64-bit boundaries and each pair of 32-bit
                                                                descriptors is read from memory using a single AXI access. */
   __IM uint32_t TRANSMIT_Q3_PTR;               /*!< 0x00001448 transmit_q3_ptr to transmit_q15_ptr doesn't present. Access to
                                                                the register returns AHB error. */
   __IM uint32_t RESERVED12[11];
   __IM uint32_t TRANSMIT_Q15_PTR;              /*!< 0x00001478 Not presents. */
   __IM uint32_t RESERVED13;
  __IOM uint32_t RECEIVE_Q1_PTR;                /*!< 0x00001480 This register holds the start address of the transmit buffer
                                                                queue (transmit buffers descriptor list). The transmit buffer
                                                                queue base address register must be initialized before transmit
                                                                is started through bit 9 of the network control register. Once
                                                                transmission has started, any write to the transmit buffer queue
                                                                base address register is illegal and therefore ignored. Note
                                                                that due to clock boundary synchronization, it takes a maximum
                                                                of four pclk cycles from the writing of the transmit start bit
                                                                before the transmitter is active. Writing to the transmit buffer
                                                                queue base address register during this time may produce
                                                                unpredictable results. Reading this register returns the
                                                                location of the descriptor currently being accessed. Because the
                                                                DMA can store data for multiple frames at once, this may not
                                                                necessarily be pointing to the current frame being transmitted.
                                                                In terms of AMBA AXI operation, the transmit descriptors are
                                                                written to memory using a single 32bit AHB access. When the
                                                                datapath is configured as 64bit , the transmit descriptors
                                                                should be aligned at 64-bit boundaries and each pair of 32-bit
                                                                descriptors is read from memory using a single AXI access. */
  __IOM uint32_t RECEIVE_Q2_PTR;                /*!< 0x00001484 This register holds the start address of the transmit buffer
                                                                queue (transmit buffers descriptor list). The transmit buffer
                                                                queue base address register must be initialized before transmit
                                                                is started through bit 9 of the network control register. Once
                                                                transmission has started, any write to the transmit buffer queue
                                                                base address register is illegal and therefore ignored. Note
                                                                that due to clock boundary synchronization, it takes a maximum
                                                                of four pclk cycles from the writing of the transmit start bit
                                                                before the transmitter is active. Writing to the transmit buffer
                                                                queue base address register during this time may produce
                                                                unpredictable results. Reading this register returns the
                                                                location of the descriptor currently being accessed. Because the
                                                                DMA can store data for multiple frames at once, this may not
                                                                necessarily be pointing to the current frame being transmitted.
                                                                In terms of AMBA AXI operation, the transmit descriptors are
                                                                written to memory using a single 32bit AHB access. When the
                                                                datapath is configured as 64bit , the transmit descriptors
                                                                should be aligned at 64-bit boundaries and each pair of 32-bit
                                                                descriptors is read from memory using a single AXI access. */
   __IM uint32_t RECEIVE_Q3_PTR;                /*!< 0x00001488 Not presents. Start address register doesn't present for queue3
                                                                ~ queue7. */
   __IM uint32_t RESERVED14[3];
   __IM uint32_t RECEIVE_Q7_PTR;                /*!< 0x00001498 Not presents. */
   __IM uint32_t RESERVED15;
  __IOM uint32_t DMA_RXBUF_SIZE_Q1;             /*!< 0x000014A0 Receive Buffer queue 1 Size */
  __IOM uint32_t DMA_RXBUF_SIZE_Q2;             /*!< 0x000014A4 Receive Buffer queue 2 Size */
   __IM uint32_t DMA_RXBUF_SIZE_Q3;             /*!< 0x000014A8 dma_rxbuf_size_q3 to dma_rxbuf_size_q7 doesn't present. */
   __IM uint32_t RESERVED16[3];
   __IM uint32_t DMA_RXBUF_SIZE_Q7;             /*!< 0x000014B8 Not presents. */
  __IOM uint32_t CBS_CONTROL;                   /*!< 0x000014BC The IdleSlope value is defined as the rate of change of credit
                                                                when a packet is waiting to be sent. This must not exceed the
                                                                portTransmitRate which is dependent on the speed of operation,
                                                                eg, portTranmsitRate. 1Gb/s = 32'h07735940 (125 Mbytes/s),
                                                                100Mb/sec = 32'h017D7840 (25 Mnibbles/s), 10Mb/sec =
                                                                32'h002625A0 (2.5 Mnibbles/s). If 50 percent of bandwidth was to
                                                                be allocated to a particular queue in 1Gb/sec mode then the
                                                                IdleSlope value for that queue would be calculated as
                                                                32'h07735940/2. Note that Credit-Based Shaping should be
                                                                disabled prior to updating the IdleSlope values. As another
                                                                example, for a 1722 audio packet with a payload of 6 samples per
                                                                channel, the packet size would be 7 (preamble) + 1 (SFD) + 50
                                                                (packet header) + 6x4x2(payload) + 4 (CRC) = 110 bytes. For a
                                                                rate of 8000 packets per second, the desired rate would 110 x
                                                                8000 bytes per second, so the programmed idleSlope value would
                                                                be 880000 for a 1Gb/s connection, or 1760000 for a 100Mb/s or
                                                                10Mbs connection. See Figure 6.3 in the IEEE 1722 standard. In
                                                                practice, the actual transmission rate will be vary slightly
                                                                from that calculated. In this case, the idleSlope value should
                                                                be recalibrated based on the variance between the measured and
                                                                expected rate, and in this case very accurate transmission rates
                                                                can be achieved. */
  __IOM uint32_t CBS_IDLESLOPE_Q_A;             /*!< 0x000014C0 queue A is the highest priority queue. This would be queue 8 in
                                                                an 8 queue configuration. */
  __IOM uint32_t CBS_IDLESLOPE_Q_B;             /*!< 0x000014C4 queue B is the 2nd highest priority queue. This would be queue
                                                                7 in an 8 queue configuration. */
  __IOM uint32_t UPPER_TX_Q_BASE_ADDR;          /*!< 0x000014C8 Upper 32 bits of transmit buffer descriptor queue base address. */
  __IOM uint32_t TX_BD_CONTROL;                 /*!< 0x000014CC TX BD control register */
  __IOM uint32_t RX_BD_CONTROL;                 /*!< 0x000014D0 RX BD control register */
  __IOM uint32_t UPPER_RX_Q_BASE_ADDR;          /*!< 0x000014D4 Upper 32 bits of receive buffer descriptor queue base address. */
   __IM uint32_t RESERVED17[2];
  __IOM uint32_t HIDDEN_REG0;                   /*!< 0x000014E0 Hidden registers defined in edma_defs.v '`define
                                                                gem_cbs_port_tx_rate_10m 12'h4e0 // 10M Port TX Rate *** HIDDEN
                                                                Register ***'. Default value of cbs related hidden registers
                                                                (0x14E0~0x14E8) are depicted in cbs_control register. */
  __IOM uint32_t HIDDEN_REG1;                   /*!< 0x000014E4 Hidden registers defined in edma_defs.v '`define
                                                                gem_cbs_port_tx_rate_100m 12'h4e4 // 100M Port TX Rate ***
                                                                HIDDEN Register ***' */
  __IOM uint32_t HIDDEN_REG2;                   /*!< 0x000014E8 Hidden registers defined in edma_defs.v '`define
                                                                gem_cbs_port_tx_rate_1g 12'h4e8 // 1G Port TX Rate *** HIDDEN
                                                                Register ***' */
  __IOM uint32_t HIDDEN_REG3;                   /*!< 0x000014EC Hidden registers defined in edma_defs.v '`define gem_wd_counter
                                                                12'h4ec // *** HIDDEN Register ***'. */
   __IM uint32_t RESERVED18[2];
  __IOM uint32_t HIDDEN_REG4;                   /*!< 0x000014F8 Hidden registers defined in edma_defs.v '`define
                                                                gem_axi_tx_full_threshold0 12'h4f8 // AXI full threshold setting
                                                                *** HIDDEN Register ***'. Note. When using AXI mode with a
                                                                single port ram ( gem_spram == 1) mode and a 32b dma bus width (
                                                                gem_dma_bus_width == 32 or bits 22 to 21 of the network_config
                                                                register are set to 0) the AXI hidden registers (0x14F8 and
                                                                0x14FC) need to be updated (these registers are used for fine
                                                                tuning AXI dma bursts and normally should not be touched). */
  __IOM uint32_t HIDDEN_REG5;                   /*!< 0x000014FC Hidden registers defined in edma_defs.v '`define
                                                                gem_axi_tx_full_threshold1 12'h4fc // AXI full threshold setting
                                                                *** HIDDEN Register ***'. */
  __IOM uint32_t SCREENING_TYPE_1_REGISTER_0;   /*!< 0x00001500 Screening type 1 registers are used to allocate up to 16
                                                                priority queues to received frames based on certain IP or UDP
                                                                fields of incoming frames. Firstly, when DS/TC match enable is
                                                                set (bit 28), the DS (Differentiated Services) field of the
                                                                received IPv4 header or TCfield (traffic class) of IPv6 headers
                                                                are matched against bits 11 to 4. Secondly, when UDP port match
                                                                enable is set (bit 29), the UDP Destination Port of the received
                                                                UDP frame is matched against bits 27 to 12. Both UDP and DS/TC
                                                                matching can be enabled simultaneously or individually. If a
                                                                match is successful, then the queue value programmed in bits 2
                                                                to 0 is allocated to the frame. The required number of Type 1
                                                                screening registers is configured in the gem defines file. Up to
                                                                16 type 1 screening registers have been allocated APB address
                                                                space between 0x500 and 0x53C. */
  __IOM uint32_t SCREENING_TYPE_1_REGISTER_1;   /*!< 0x00001504 screening type 1 register 1, same as
                                                                screening_type_1_register_0 */
  __IOM uint32_t SCREENING_TYPE_1_REGISTER_2;   /*!< 0x00001508 screening type 1 register 2, same as
                                                                screening_type_1_register_0 */
  __IOM uint32_t SCREENING_TYPE_1_REGISTER_3;   /*!< 0x0000150C screening type 1 register 3, same as
                                                                screening_type_1_register_0 */
  __IOM uint32_t SCREENING_TYPE_1_REGISTER_4;   /*!< 0x00001510 screening type 1 register 4, same as
                                                                screening_type_1_register_0 */
  __IOM uint32_t SCREENING_TYPE_1_REGISTER_5;   /*!< 0x00001514 screening type 1 register 5, same as
                                                                screening_type_1_register_0 */
  __IOM uint32_t SCREENING_TYPE_1_REGISTER_6;   /*!< 0x00001518 screening type 1 register 6, same as
                                                                screening_type_1_register_0 */
  __IOM uint32_t SCREENING_TYPE_1_REGISTER_7;   /*!< 0x0000151C screening type 1 register 7, same as
                                                                screening_type_1_register_0 */
  __IOM uint32_t SCREENING_TYPE_1_REGISTER_8;   /*!< 0x00001520 screening type 1 register 8, same as
                                                                screening_type_1_register_0 */
  __IOM uint32_t SCREENING_TYPE_1_REGISTER_9;   /*!< 0x00001524 screening type 1 register 9, same as
                                                                screening_type_1_register_0 */
  __IOM uint32_t SCREENING_TYPE_1_REGISTER_10;  /*!< 0x00001528 screening type 1 register 10, same as
                                                                screening_type_1_register_0 */
  __IOM uint32_t SCREENING_TYPE_1_REGISTER_11;  /*!< 0x0000152C screening type 1 register 11, same as
                                                                screening_type_1_register_0 */
  __IOM uint32_t SCREENING_TYPE_1_REGISTER_12;  /*!< 0x00001530 screening type 1 register 12, same as
                                                                screening_type_1_register_0 */
  __IOM uint32_t SCREENING_TYPE_1_REGISTER_13;  /*!< 0x00001534 screening type 1 register 13, same as
                                                                screening_type_1_register_0 */
  __IOM uint32_t SCREENING_TYPE_1_REGISTER_14;  /*!< 0x00001538 screening type 1 register 14, same as
                                                                screening_type_1_register_0 */
  __IOM uint32_t SCREENING_TYPE_1_REGISTER_15;  /*!< 0x0000153C screening type 1 register 15, same as
                                                                screening_type_1_register_0 */
  __IOM uint32_t SCREENING_TYPE_2_REGISTER_0;   /*!< 0x00001540 Screener Type 2 match registers operate independently of
                                                                screener type 1 registers and offer additional match
                                                                capabilities, extending the capabilities into vendor specific
                                                                protocols. */
  __IOM uint32_t SCREENING_TYPE_2_REGISTER_1;   /*!< 0x00001544 screening type 2 register 1, same as
                                                                screening_type_2_register_0 */
  __IOM uint32_t SCREENING_TYPE_2_REGISTER_2;   /*!< 0x00001548 screening type 2 register 2, same as
                                                                screening_type_2_register_0 */
  __IOM uint32_t SCREENING_TYPE_2_REGISTER_3;   /*!< 0x0000154C screening type 2 register 3, same as
                                                                screening_type_2_register_0 */
  __IOM uint32_t SCREENING_TYPE_2_REGISTER_4;   /*!< 0x00001550 screening type 2 register 4, same as
                                                                screening_type_2_register_0 */
  __IOM uint32_t SCREENING_TYPE_2_REGISTER_5;   /*!< 0x00001554 screening type 2 register 5, same as
                                                                screening_type_2_register_0 */
  __IOM uint32_t SCREENING_TYPE_2_REGISTER_6;   /*!< 0x00001558 screening type 2 register 6, same as
                                                                screening_type_2_register_0 */
  __IOM uint32_t SCREENING_TYPE_2_REGISTER_7;   /*!< 0x0000155C screening type 2 register 7, same as
                                                                screening_type_2_register_0 */
  __IOM uint32_t SCREENING_TYPE_2_REGISTER_8;   /*!< 0x00001560 screening type 2 register 8, same as
                                                                screening_type_2_register_0 */
  __IOM uint32_t SCREENING_TYPE_2_REGISTER_9;   /*!< 0x00001564 screening type 2 register 9, same as
                                                                screening_type_2_register_0 */
  __IOM uint32_t SCREENING_TYPE_2_REGISTER_10;  /*!< 0x00001568 screening type 2 register 10, same as
                                                                screening_type_2_register_0 */
  __IOM uint32_t SCREENING_TYPE_2_REGISTER_11;  /*!< 0x0000156C screening type 2 register 11, same as
                                                                screening_type_2_register_0 */
  __IOM uint32_t SCREENING_TYPE_2_REGISTER_12;  /*!< 0x00001570 screening type 2 register 12, same as
                                                                screening_type_2_register_0 */
  __IOM uint32_t SCREENING_TYPE_2_REGISTER_13;  /*!< 0x00001574 screening type 2 register 13, same as
                                                                screening_type_2_register_0 */
  __IOM uint32_t SCREENING_TYPE_2_REGISTER_14;  /*!< 0x00001578 screening type 2 register 14, same as
                                                                screening_type_2_register_0 */
  __IOM uint32_t SCREENING_TYPE_2_REGISTER_15;  /*!< 0x0000157C screening type 2 register 15, same as
                                                                screening_type_2_register_0 */
  __IOM uint32_t TX_SCHED_CTRL;                 /*!< 0x00001580 This register controls the transmit scheduling algorithm the
                                                                user can select for each active transmit queue. By default all
                                                                queues are initialized to fixed priority, with the top indexed
                                                                queue having overall priority */
   __IM uint32_t RESERVED19[3];
  __IOM uint32_t BW_RATE_LIMIT_Q0TO3;           /*!< 0x00001590 This register holds the DWRR weighting value or the ETS
                                                                bandwidth percentage value used by the transmit scheduler for
                                                                queues 0 to 3. */
  __IOM uint32_t BW_RATE_LIMIT_Q4TO7;           /*!< 0x00001594 Not presents. MXETH has only 3 queues. Access to the register
                                                                returns AHB error. */
   __IM uint32_t BW_RATE_LIMIT_Q8TO11;          /*!< 0x00001598 Not presents. MXETH has only 3 queues. Access to the register
                                                                returns AHB error. */
   __IM uint32_t BW_RATE_LIMIT_Q12TO15;         /*!< 0x0000159C Not presents. MXETH has only 3 queues. Access to the register
                                                                returns AHB error. */
  __IOM uint32_t TX_Q_SEG_ALLOC_Q0TO7;          /*!< 0x000015A0 This register allows the user to distribute the Transmit SRAM
                                                                used by the DMA across the priority queues, for queues 0 to 7.
                                                                The SRAM itself is split into a number of evenly sized segments
                                                                (this is defined in the verilog configuration defs file - for
                                                                the configuration used to generate this register description,
                                                                the total number of segments was set to '16'). Those segments
                                                                can then be freely distributed across the active queues, in
                                                                powers of 2. I.e. a value of 0 would mean 1 segment has been
                                                                allocated to the queue. A value of 1 would mean 2 segments, a
                                                                value of 2 means 4 segments and so on. The reset values of these
                                                                registers are defined in the configuration defs file. */
   __IM uint32_t TX_Q_SEG_ALLOC_Q8TO15;         /*!< 0x000015A4 Not presents.  Access to the register returns AHB error. */
   __IM uint32_t RESERVED20[6];
   __IM uint32_t RECEIVE_Q8_PTR;                /*!< 0x000015C0 receive_q8_ptr to receive_q15_ptr doesn't present. Access to
                                                                the register returns AHB error. */
   __IM uint32_t RESERVED21[6];
   __IM uint32_t RECEIVE_Q15_PTR;               /*!< 0x000015DC Not presents. */
   __IM uint32_t DMA_RXBUF_SIZE_Q8;             /*!< 0x000015E0 dma_rxbuf_size_q8 to dma_rxbuf_size_q15 doesn't present. Access
                                                                to the register returns AHB error. */
   __IM uint32_t RESERVED22[6];
   __IM uint32_t DMA_RXBUF_SIZE_Q15;            /*!< 0x000015FC Not presents. */
   __OM uint32_t INT_Q1_ENABLE;                 /*!< 0x00001600 At reset all interrupts are disabled. Writing a one to the
                                                                relevant bit location enables the required interrupt. This
                                                                register is write only and when read will return zero. */
   __OM uint32_t INT_Q2_ENABLE;                 /*!< 0x00001604 At reset all interrupts are disabled. Writing a one to the
                                                                relevant bit location enables the required interrupt. This
                                                                register is write only and when read will return zero. */
   __IM uint32_t INT_Q3_ENABLE;                 /*!< 0x00001608 int_q3_enable to int_q7_enable doesn't present. Access to the
                                                                register returns AHB error. */
   __IM uint32_t RESERVED23[3];
   __IM uint32_t INT_Q7_ENABLE;                 /*!< 0x00001618 Not presents. */
   __IM uint32_t RESERVED24;
   __OM uint32_t INT_Q1_DISABLE;                /*!< 0x00001620 Writing a 1 to the relevant bit location disables that
                                                                particular interrupt. This register is write only and when read
                                                                will return zero. */
   __OM uint32_t INT_Q2_DISABLE;                /*!< 0x00001624 Writing a 1 to the relevant bit location disables that
                                                                particular interrupt. This register is write only and when read
                                                                will return zero. */
   __IM uint32_t INT_Q3_DISABLE;                /*!< 0x00001628 int_q3_disable to int_q7_disable doesn't present. Access to the
                                                                register returns AHB error. */
   __IM uint32_t RESERVED25[3];
   __IM uint32_t INT_Q7_DISABLE;                /*!< 0x00001638 Not presents. */
   __IM uint32_t RESERVED26;
   __IM uint32_t INT_Q1_MASK;                   /*!< 0x00001640 The interrupt mask register is a read only register indicating
                                                                which interrupts are masked. All bits are set at reset and can
                                                                be reset individually by writing to the interrupt enable
                                                                register or set individually by writing to the interrupt disable
                                                                register. Having separate address locations for enable and
                                                                disable saves the need for performing a read modify write when
                                                                updating the interrupt mask register. For test purposes there is
                                                                a write-only function to this register that allows the bits in
                                                                the interrupt status register to be set or cleared, regardless
                                                                of the state of the mask register. */
   __IM uint32_t INT_Q2_MASK;                   /*!< 0x00001644 The interrupt mask register is a read only register indicating
                                                                which interrupts are masked. All bits are set at reset and can
                                                                be reset individually by writing to the interrupt enable
                                                                register or set individually by writing to the interrupt disable
                                                                register. Having separate address locations for enable and
                                                                disable saves the need for performing a read modify write when
                                                                updating the interrupt mask register. For test purposes there is
                                                                a write-only function to this register that allows the bits in
                                                                the interrupt status register to be set or cleared, regardless
                                                                of the state of the mask register. */
   __IM uint32_t INT_Q3_MASK;                   /*!< 0x00001648 int_q3_mask to int_q7_mask doesn't present. Access to the
                                                                register returns AHB error. */
   __IM uint32_t RESERVED27[3];
   __IM uint32_t INT_Q7_MASK;                   /*!< 0x00001658 Not presents. */
   __IM uint32_t RESERVED28;
   __IM uint32_t INT_Q8_ENABLE;                 /*!< 0x00001660 int_q8_enable to int_q15_enable doesn't present. Access to the
                                                                register returns AHB error. */
   __IM uint32_t RESERVED29[6];
   __IM uint32_t INT_Q15_ENABLE;                /*!< 0x0000167C Not presents. */
   __IM uint32_t INT_Q8_DISABLE;                /*!< 0x00001680 int_q8_disable to int_q15_disable doesn't present. Access to
                                                                the register returns AHB error. */
   __IM uint32_t RESERVED30[6];
   __IM uint32_t INT_Q15_DISABLE;               /*!< 0x0000169C Not presents. */
   __IM uint32_t INT_Q8_MASK;                   /*!< 0x000016A0 int_q8_mask to int_q15_mask doesn't present. Access to the
                                                                register returns AHB error. */
   __IM uint32_t RESERVED31[6];
   __IM uint32_t INT_Q15_MASK;                  /*!< 0x000016BC Not presents. */
   __IM uint32_t RESERVED32[8];
  __IOM uint32_t SCREENING_TYPE_2_ETHERTYPE_REG_0; /*!< 0x000016E0 Ethertype Register */
  __IOM uint32_t SCREENING_TYPE_2_ETHERTYPE_REG_1; /*!< 0x000016E4 Ethertype Register */
  __IOM uint32_t SCREENING_TYPE_2_ETHERTYPE_REG_2; /*!< 0x000016E8 Ethertype Register */
  __IOM uint32_t SCREENING_TYPE_2_ETHERTYPE_REG_3; /*!< 0x000016EC Ethertype Register */
  __IOM uint32_t SCREENING_TYPE_2_ETHERTYPE_REG_4; /*!< 0x000016F0 Ethertype Register */
  __IOM uint32_t SCREENING_TYPE_2_ETHERTYPE_REG_5; /*!< 0x000016F4 Ethertype Register */
  __IOM uint32_t SCREENING_TYPE_2_ETHERTYPE_REG_6; /*!< 0x000016F8 Ethertype Register */
  __IOM uint32_t SCREENING_TYPE_2_ETHERTYPE_REG_7; /*!< 0x000016FC Ethertype Register */
  __IOM uint32_t TYPE2_COMPARE_0_WORD_0;        /*!< 0x00001700 'Compare A, B and C fields of the screener type 2 match
                                                                register are pointers to a pool of up to 32 compare registers.
                                                                If enabled the compare is true if the data at the OFFSET into
                                                                the frame, ANDed with the MASK Value if the mask is enabled, is
                                                                equal to the COMPARE Value. Either a 16 bit comparison or a 32
                                                                bit comparison is done. This selection is made via the
                                                                associated compare word1 register bit 9. If a 16 bit comparison
                                                                is selected, then a 16 bit mask is also available to the user to
                                                                select which bits should be compared. If the 32 bit compare
                                                                option is selected, then no mask is available. The byte at the
                                                                OFFSET number of bytes from the index start is compared thru
                                                                bits 7 to 0 of the configured VALUE. The byte at the OFFSET
                                                                number of bytes + 1 from the index start is compared thru bits
                                                                15 to 8 of the configured VALUE and so on. The OFFSET can be
                                                                configured to be from 0 to 127 bytes from either the start of
                                                                the frame, the byte following the therType field (last EtherType
                                                                in the header if the frame is VLAN tagged), the byte following
                                                                the IP header (IPv4 or IPv6) or from the byte following the
                                                                start of the TCP/UDP header. The required number of Type 2
                                                                screening registers up to a maximum of 32 is configurable in the
                                                                gem defines file and have been allocated APB address space
                                                                between 0x700 and 0x7fc. Note. when using RX Partial Store and
                                                                Forward mode and priority queues, the frame offset must be less
                                                                than the Partial Store and Forward watermark. If the offset is
                                                                higher than the watermark value it's not possible to identify
                                                                the priority queue before the frame is sent to the AMBA
                                                                interface, and an incorrect priority queue may be used. ' */
  __IOM uint32_t TYPE2_COMPARE_0_WORD_1;        /*!< 0x00001704 'Type2 Compare Word 1' */
  __IOM uint32_t TYPE2_COMPARE_1_WORD_0;        /*!< 0x00001708 same as type2_compare_0_word_0 */
  __IOM uint32_t TYPE2_COMPARE_1_WORD_1;        /*!< 0x0000170C same as type2_compare_0_word_1 */
  __IOM uint32_t TYPE2_COMPARE_2_WORD_0;        /*!< 0x00001710 same as type2_compare_0_word_0 */
  __IOM uint32_t TYPE2_COMPARE_2_WORD_1;        /*!< 0x00001714 same as type2_compare_0_word_1 */
  __IOM uint32_t TYPE2_COMPARE_3_WORD_0;        /*!< 0x00001718 same as type2_compare_0_word_0 */
  __IOM uint32_t TYPE2_COMPARE_3_WORD_1;        /*!< 0x0000171C same as type2_compare_0_word_1 */
  __IOM uint32_t TYPE2_COMPARE_4_WORD_0;        /*!< 0x00001720 same as type2_compare_0_word_0 */
  __IOM uint32_t TYPE2_COMPARE_4_WORD_1;        /*!< 0x00001724 same as type2_compare_0_word_1 */
  __IOM uint32_t TYPE2_COMPARE_5_WORD_0;        /*!< 0x00001728 same as type2_compare_0_word_0 */
  __IOM uint32_t TYPE2_COMPARE_5_WORD_1;        /*!< 0x0000172C same as type2_compare_0_word_1 */
  __IOM uint32_t TYPE2_COMPARE_6_WORD_0;        /*!< 0x00001730 same as type2_compare_0_word_0 */
  __IOM uint32_t TYPE2_COMPARE_6_WORD_1;        /*!< 0x00001734 same as type2_compare_0_word_1 */
  __IOM uint32_t TYPE2_COMPARE_7_WORD_0;        /*!< 0x00001738 same as type2_compare_0_word_0 */
  __IOM uint32_t TYPE2_COMPARE_7_WORD_1;        /*!< 0x0000173C same as type2_compare_0_word_1 */
  __IOM uint32_t TYPE2_COMPARE_8_WORD_0;        /*!< 0x00001740 same as type2_compare_0_word_0 */
  __IOM uint32_t TYPE2_COMPARE_8_WORD_1;        /*!< 0x00001744 same as type2_compare_0_word_1 */
  __IOM uint32_t TYPE2_COMPARE_9_WORD_0;        /*!< 0x00001748 same as type2_compare_0_word_0 */
  __IOM uint32_t TYPE2_COMPARE_9_WORD_1;        /*!< 0x0000174C same as type2_compare_0_word_1 */
  __IOM uint32_t TYPE2_COMPARE_10_WORD_0;       /*!< 0x00001750 same as type2_compare_0_word_0 */
  __IOM uint32_t TYPE2_COMPARE_10_WORD_1;       /*!< 0x00001754 same as type2_compare_0_word_1 */
  __IOM uint32_t TYPE2_COMPARE_11_WORD_0;       /*!< 0x00001758 same as type2_compare_0_word_0 */
  __IOM uint32_t TYPE2_COMPARE_11_WORD_1;       /*!< 0x0000175C same as type2_compare_0_word_1 */
  __IOM uint32_t TYPE2_COMPARE_12_WORD_0;       /*!< 0x00001760 same as type2_compare_0_word_0 */
  __IOM uint32_t TYPE2_COMPARE_12_WORD_1;       /*!< 0x00001764 same as type2_compare_0_word_1 */
  __IOM uint32_t TYPE2_COMPARE_13_WORD_0;       /*!< 0x00001768 same as type2_compare_0_word_0 */
  __IOM uint32_t TYPE2_COMPARE_13_WORD_1;       /*!< 0x0000176C same as type2_compare_0_word_1 */
  __IOM uint32_t TYPE2_COMPARE_14_WORD_0;       /*!< 0x00001770 same as type2_compare_0_word_0 */
  __IOM uint32_t TYPE2_COMPARE_14_WORD_1;       /*!< 0x00001774 same as type2_compare_0_word_1 */
  __IOM uint32_t TYPE2_COMPARE_15_WORD_0;       /*!< 0x00001778 same as type2_compare_0_word_0 */
  __IOM uint32_t TYPE2_COMPARE_15_WORD_1;       /*!< 0x0000177C same as type2_compare_0_word_1 */
  __IOM uint32_t TYPE2_COMPARE_16_WORD_0;       /*!< 0x00001780 same as type2_compare_0_word_0 */
  __IOM uint32_t TYPE2_COMPARE_16_WORD_1;       /*!< 0x00001784 same as type2_compare_0_word_1 */
  __IOM uint32_t TYPE2_COMPARE_17_WORD_0;       /*!< 0x00001788 same as type2_compare_0_word_0 */
  __IOM uint32_t TYPE2_COMPARE_17_WORD_1;       /*!< 0x0000178C same as type2_compare_0_word_1 */
  __IOM uint32_t TYPE2_COMPARE_18_WORD_0;       /*!< 0x00001790 same as type2_compare_0_word_0 */
  __IOM uint32_t TYPE2_COMPARE_18_WORD_1;       /*!< 0x00001794 same as type2_compare_0_word_1 */
  __IOM uint32_t TYPE2_COMPARE_19_WORD_0;       /*!< 0x00001798 same as type2_compare_0_word_0 */
  __IOM uint32_t TYPE2_COMPARE_19_WORD_1;       /*!< 0x0000179C same as type2_compare_0_word_1 */
  __IOM uint32_t TYPE2_COMPARE_20_WORD_0;       /*!< 0x000017A0 same as type2_compare_0_word_0 */
  __IOM uint32_t TYPE2_COMPARE_20_WORD_1;       /*!< 0x000017A4 same as type2_compare_0_word_1 */
  __IOM uint32_t TYPE2_COMPARE_21_WORD_0;       /*!< 0x000017A8 same as type2_compare_0_word_0 */
  __IOM uint32_t TYPE2_COMPARE_21_WORD_1;       /*!< 0x000017AC same as type2_compare_0_word_1 */
  __IOM uint32_t TYPE2_COMPARE_22_WORD_0;       /*!< 0x000017B0 same as type2_compare_0_word_0 */
  __IOM uint32_t TYPE2_COMPARE_22_WORD_1;       /*!< 0x000017B4 same as type2_compare_0_word_1 */
  __IOM uint32_t TYPE2_COMPARE_23_WORD_0;       /*!< 0x000017B8 same as type2_compare_0_word_0 */
  __IOM uint32_t TYPE2_COMPARE_23_WORD_1;       /*!< 0x000017BC same as type2_compare_0_word_1 */
  __IOM uint32_t TYPE2_COMPARE_24_WORD_0;       /*!< 0x000017C0 same as type2_compare_0_word_0 */
  __IOM uint32_t TYPE2_COMPARE_24_WORD_1;       /*!< 0x000017C4 same as type2_compare_0_word_1 */
  __IOM uint32_t TYPE2_COMPARE_25_WORD_0;       /*!< 0x000017C8 same as type2_compare_0_word_0 */
  __IOM uint32_t TYPE2_COMPARE_25_WORD_1;       /*!< 0x000017CC same as type2_compare_0_word_1 */
  __IOM uint32_t TYPE2_COMPARE_26_WORD_0;       /*!< 0x000017D0 same as type2_compare_0_word_0 */
  __IOM uint32_t TYPE2_COMPARE_26_WORD_1;       /*!< 0x000017D4 same as type2_compare_0_word_1 */
  __IOM uint32_t TYPE2_COMPARE_27_WORD_0;       /*!< 0x000017D8 same as type2_compare_0_word_0 */
  __IOM uint32_t TYPE2_COMPARE_27_WORD_1;       /*!< 0x000017DC same as type2_compare_0_word_1 */
  __IOM uint32_t TYPE2_COMPARE_28_WORD_0;       /*!< 0x000017E0 same as type2_compare_0_word_0 */
  __IOM uint32_t TYPE2_COMPARE_28_WORD_1;       /*!< 0x000017E4 same as type2_compare_0_word_1 */
  __IOM uint32_t TYPE2_COMPARE_29_WORD_0;       /*!< 0x000017E8 same as type2_compare_0_word_0 */
  __IOM uint32_t TYPE2_COMPARE_29_WORD_1;       /*!< 0x000017EC same as type2_compare_0_word_1 */
  __IOM uint32_t TYPE2_COMPARE_30_WORD_0;       /*!< 0x000017F0 same as type2_compare_0_word_0 */
  __IOM uint32_t TYPE2_COMPARE_30_WORD_1;       /*!< 0x000017F4 same as type2_compare_0_word_1 */
  __IOM uint32_t TYPE2_COMPARE_31_WORD_0;       /*!< 0x000017F8 same as type2_compare_0_word_0 */
  __IOM uint32_t TYPE2_COMPARE_31_WORD_1;       /*!< 0x000017FC same as type2_compare_0_word_1 */
} ETH_Type;                                     /*!< Size = 6144 (0x1800) */


/* ETH.CTL */
#define ETH_CTL_ETH_MODE_Pos                    0UL
#define ETH_CTL_ETH_MODE_Msk                    0x3UL
#define ETH_CTL_REFCLK_SRC_SEL_Pos              2UL
#define ETH_CTL_REFCLK_SRC_SEL_Msk              0x4UL
#define ETH_CTL_REFCLK_DIV_Pos                  8UL
#define ETH_CTL_REFCLK_DIV_Msk                  0xFF00UL
#define ETH_CTL_ENABLED_Pos                     31UL
#define ETH_CTL_ENABLED_Msk                     0x80000000UL
/* ETH.STATUS */
#define ETH_STATUS_PFC_NEGOTIATE_Pos            0UL
#define ETH_STATUS_PFC_NEGOTIATE_Msk            0x1UL
#define ETH_STATUS_RX_PFC_PAUSED_Pos            8UL
#define ETH_STATUS_RX_PFC_PAUSED_Msk            0xFF00UL
/* ETH.NETWORK_CONTROL */
#define ETH_NETWORK_CONTROL_LOOPBACK_Pos        0UL
#define ETH_NETWORK_CONTROL_LOOPBACK_Msk        0x1UL
#define ETH_NETWORK_CONTROL_LOOPBACK_LOCAL_Pos  1UL
#define ETH_NETWORK_CONTROL_LOOPBACK_LOCAL_Msk  0x2UL
#define ETH_NETWORK_CONTROL_ENABLE_RECEIVE_Pos  2UL
#define ETH_NETWORK_CONTROL_ENABLE_RECEIVE_Msk  0x4UL
#define ETH_NETWORK_CONTROL_ENABLE_TRANSMIT_Pos 3UL
#define ETH_NETWORK_CONTROL_ENABLE_TRANSMIT_Msk 0x8UL
#define ETH_NETWORK_CONTROL_MAN_PORT_EN_Pos     4UL
#define ETH_NETWORK_CONTROL_MAN_PORT_EN_Msk     0x10UL
#define ETH_NETWORK_CONTROL_CLEAR_ALL_STATS_REGS_Pos 5UL
#define ETH_NETWORK_CONTROL_CLEAR_ALL_STATS_REGS_Msk 0x20UL
#define ETH_NETWORK_CONTROL_INC_ALL_STATS_REGS_Pos 6UL
#define ETH_NETWORK_CONTROL_INC_ALL_STATS_REGS_Msk 0x40UL
#define ETH_NETWORK_CONTROL_STATS_WRITE_EN_Pos  7UL
#define ETH_NETWORK_CONTROL_STATS_WRITE_EN_Msk  0x80UL
#define ETH_NETWORK_CONTROL_BACK_PRESSURE_Pos   8UL
#define ETH_NETWORK_CONTROL_BACK_PRESSURE_Msk   0x100UL
#define ETH_NETWORK_CONTROL_TX_START_PCLK_Pos   9UL
#define ETH_NETWORK_CONTROL_TX_START_PCLK_Msk   0x200UL
#define ETH_NETWORK_CONTROL_TX_HALT_PCLK_Pos    10UL
#define ETH_NETWORK_CONTROL_TX_HALT_PCLK_Msk    0x400UL
#define ETH_NETWORK_CONTROL_TX_PAUSE_FRAME_REQ_Pos 11UL
#define ETH_NETWORK_CONTROL_TX_PAUSE_FRAME_REQ_Msk 0x800UL
#define ETH_NETWORK_CONTROL_TX_PAUSE_FRAME_ZERO_Pos 12UL
#define ETH_NETWORK_CONTROL_TX_PAUSE_FRAME_ZERO_Msk 0x1000UL
#define ETH_NETWORK_CONTROL_REMOVED_13_Pos      13UL
#define ETH_NETWORK_CONTROL_REMOVED_13_Msk      0x2000UL
#define ETH_NETWORK_CONTROL_REMOVED_14_Pos      14UL
#define ETH_NETWORK_CONTROL_REMOVED_14_Msk      0x4000UL
#define ETH_NETWORK_CONTROL_STORE_RX_TS_Pos     15UL
#define ETH_NETWORK_CONTROL_STORE_RX_TS_Msk     0x8000UL
#define ETH_NETWORK_CONTROL_PFC_ENABLE_Pos      16UL
#define ETH_NETWORK_CONTROL_PFC_ENABLE_Msk      0x10000UL
#define ETH_NETWORK_CONTROL_TRANSMIT_PFC_PRIORITY_BASED_PAUSE_FRAME_Pos 17UL
#define ETH_NETWORK_CONTROL_TRANSMIT_PFC_PRIORITY_BASED_PAUSE_FRAME_Msk 0x20000UL
#define ETH_NETWORK_CONTROL_FLUSH_RX_PKT_PCLK_Pos 18UL
#define ETH_NETWORK_CONTROL_FLUSH_RX_PKT_PCLK_Msk 0x40000UL
#define ETH_NETWORK_CONTROL_TX_LPI_EN_Pos       19UL
#define ETH_NETWORK_CONTROL_TX_LPI_EN_Msk       0x80000UL
#define ETH_NETWORK_CONTROL_PTP_UNICAST_ENA_Pos 20UL
#define ETH_NETWORK_CONTROL_PTP_UNICAST_ENA_Msk 0x100000UL
#define ETH_NETWORK_CONTROL_ALT_SGMII_MODE_Pos  21UL
#define ETH_NETWORK_CONTROL_ALT_SGMII_MODE_Msk  0x200000UL
#define ETH_NETWORK_CONTROL_STORE_UDP_OFFSET_Pos 22UL
#define ETH_NETWORK_CONTROL_STORE_UDP_OFFSET_Msk 0x400000UL
#define ETH_NETWORK_CONTROL_EXT_TSU_PORT_ENABLE_Pos 23UL
#define ETH_NETWORK_CONTROL_EXT_TSU_PORT_ENABLE_Msk 0x800000UL
#define ETH_NETWORK_CONTROL_ONE_STEP_SYNC_MODE_Pos 24UL
#define ETH_NETWORK_CONTROL_ONE_STEP_SYNC_MODE_Msk 0x1000000UL
#define ETH_NETWORK_CONTROL_PFC_CTRL_Pos        25UL
#define ETH_NETWORK_CONTROL_PFC_CTRL_Msk        0x2000000UL
#define ETH_NETWORK_CONTROL_EXT_RXQ_SEL_EN_Pos  26UL
#define ETH_NETWORK_CONTROL_EXT_RXQ_SEL_EN_Msk  0x4000000UL
#define ETH_NETWORK_CONTROL_OSS_CORRECTION_FIELD_Pos 27UL
#define ETH_NETWORK_CONTROL_OSS_CORRECTION_FIELD_Msk 0x8000000UL
#define ETH_NETWORK_CONTROL_SEL_MII_ON_RGMII_Pos 28UL
#define ETH_NETWORK_CONTROL_SEL_MII_ON_RGMII_Msk 0x10000000UL
#define ETH_NETWORK_CONTROL_TWO_PT_FIVE_GIG_Pos 29UL
#define ETH_NETWORK_CONTROL_TWO_PT_FIVE_GIG_Msk 0x20000000UL
#define ETH_NETWORK_CONTROL_IFG_EATS_QAV_CREDIT_Pos 30UL
#define ETH_NETWORK_CONTROL_IFG_EATS_QAV_CREDIT_Msk 0x40000000UL
#define ETH_NETWORK_CONTROL_EXT_RXQ_RESERVED_31_Pos 31UL
#define ETH_NETWORK_CONTROL_EXT_RXQ_RESERVED_31_Msk 0x80000000UL
/* ETH.NETWORK_CONFIG */
#define ETH_NETWORK_CONFIG_SPEED_Pos            0UL
#define ETH_NETWORK_CONFIG_SPEED_Msk            0x1UL
#define ETH_NETWORK_CONFIG_FULL_DUPLEX_Pos      1UL
#define ETH_NETWORK_CONFIG_FULL_DUPLEX_Msk      0x2UL
#define ETH_NETWORK_CONFIG_DISCARD_NON_VLAN_FRAMES_Pos 2UL
#define ETH_NETWORK_CONFIG_DISCARD_NON_VLAN_FRAMES_Msk 0x4UL
#define ETH_NETWORK_CONFIG_JUMBO_FRAMES_Pos     3UL
#define ETH_NETWORK_CONFIG_JUMBO_FRAMES_Msk     0x8UL
#define ETH_NETWORK_CONFIG_COPY_ALL_FRAMES_Pos  4UL
#define ETH_NETWORK_CONFIG_COPY_ALL_FRAMES_Msk  0x10UL
#define ETH_NETWORK_CONFIG_NO_BROADCAST_Pos     5UL
#define ETH_NETWORK_CONFIG_NO_BROADCAST_Msk     0x20UL
#define ETH_NETWORK_CONFIG_MULTICAST_HASH_ENABLE_Pos 6UL
#define ETH_NETWORK_CONFIG_MULTICAST_HASH_ENABLE_Msk 0x40UL
#define ETH_NETWORK_CONFIG_UNICAST_HASH_ENABLE_Pos 7UL
#define ETH_NETWORK_CONFIG_UNICAST_HASH_ENABLE_Msk 0x80UL
#define ETH_NETWORK_CONFIG_RECEIVE_1536_BYTE_FRAMES_Pos 8UL
#define ETH_NETWORK_CONFIG_RECEIVE_1536_BYTE_FRAMES_Msk 0x100UL
#define ETH_NETWORK_CONFIG_EXTERNAL_ADDRESS_MATCH_ENABLE_Pos 9UL
#define ETH_NETWORK_CONFIG_EXTERNAL_ADDRESS_MATCH_ENABLE_Msk 0x200UL
#define ETH_NETWORK_CONFIG_GIGABIT_MODE_ENABLE_Pos 10UL
#define ETH_NETWORK_CONFIG_GIGABIT_MODE_ENABLE_Msk 0x400UL
#define ETH_NETWORK_CONFIG_PCS_SELECT_Pos       11UL
#define ETH_NETWORK_CONFIG_PCS_SELECT_Msk       0x800UL
#define ETH_NETWORK_CONFIG_RETRY_TEST_Pos       12UL
#define ETH_NETWORK_CONFIG_RETRY_TEST_Msk       0x1000UL
#define ETH_NETWORK_CONFIG_PAUSE_ENABLE_Pos     13UL
#define ETH_NETWORK_CONFIG_PAUSE_ENABLE_Msk     0x2000UL
#define ETH_NETWORK_CONFIG_RECEIVE_BUFFER_OFFSET_Pos 14UL
#define ETH_NETWORK_CONFIG_RECEIVE_BUFFER_OFFSET_Msk 0xC000UL
#define ETH_NETWORK_CONFIG_LENGTH_FIELD_ERROR_FRAME_DISCARD_Pos 16UL
#define ETH_NETWORK_CONFIG_LENGTH_FIELD_ERROR_FRAME_DISCARD_Msk 0x10000UL
#define ETH_NETWORK_CONFIG_FCS_REMOVE_Pos       17UL
#define ETH_NETWORK_CONFIG_FCS_REMOVE_Msk       0x20000UL
#define ETH_NETWORK_CONFIG_MDC_CLOCK_DIVISION_Pos 18UL
#define ETH_NETWORK_CONFIG_MDC_CLOCK_DIVISION_Msk 0x1C0000UL
#define ETH_NETWORK_CONFIG_DATA_BUS_WIDTH_Pos   21UL
#define ETH_NETWORK_CONFIG_DATA_BUS_WIDTH_Msk   0x600000UL
#define ETH_NETWORK_CONFIG_DISABLE_COPY_OF_PAUSE_FRAMES_Pos 23UL
#define ETH_NETWORK_CONFIG_DISABLE_COPY_OF_PAUSE_FRAMES_Msk 0x800000UL
#define ETH_NETWORK_CONFIG_RECEIVE_CHECKSUM_OFFLOAD_ENABLE_Pos 24UL
#define ETH_NETWORK_CONFIG_RECEIVE_CHECKSUM_OFFLOAD_ENABLE_Msk 0x1000000UL
#define ETH_NETWORK_CONFIG_EN_HALF_DUPLEX_RX_Pos 25UL
#define ETH_NETWORK_CONFIG_EN_HALF_DUPLEX_RX_Msk 0x2000000UL
#define ETH_NETWORK_CONFIG_IGNORE_RX_FCS_Pos    26UL
#define ETH_NETWORK_CONFIG_IGNORE_RX_FCS_Msk    0x4000000UL
#define ETH_NETWORK_CONFIG_SGMII_MODE_ENABLE_Pos 27UL
#define ETH_NETWORK_CONFIG_SGMII_MODE_ENABLE_Msk 0x8000000UL
#define ETH_NETWORK_CONFIG_IPG_STRETCH_ENABLE_Pos 28UL
#define ETH_NETWORK_CONFIG_IPG_STRETCH_ENABLE_Msk 0x10000000UL
#define ETH_NETWORK_CONFIG_NSP_CHANGE_Pos       29UL
#define ETH_NETWORK_CONFIG_NSP_CHANGE_Msk       0x20000000UL
#define ETH_NETWORK_CONFIG_IGNORE_IPG_RX_ER_Pos 30UL
#define ETH_NETWORK_CONFIG_IGNORE_IPG_RX_ER_Msk 0x40000000UL
#define ETH_NETWORK_CONFIG_RESERVED_31_Pos      31UL
#define ETH_NETWORK_CONFIG_RESERVED_31_Msk      0x80000000UL
/* ETH.NETWORK_STATUS */
#define ETH_NETWORK_STATUS_PCS_LINK_STATE_Pos   0UL
#define ETH_NETWORK_STATUS_PCS_LINK_STATE_Msk   0x1UL
#define ETH_NETWORK_STATUS_MDIO_IN_Pos          1UL
#define ETH_NETWORK_STATUS_MDIO_IN_Msk          0x2UL
#define ETH_NETWORK_STATUS_MAN_DONE_Pos         2UL
#define ETH_NETWORK_STATUS_MAN_DONE_Msk         0x4UL
#define ETH_NETWORK_STATUS_MAC_FULL_DUPLEX_Pos  3UL
#define ETH_NETWORK_STATUS_MAC_FULL_DUPLEX_Msk  0x8UL
#define ETH_NETWORK_STATUS_REMOVED_5_4_Pos      4UL
#define ETH_NETWORK_STATUS_REMOVED_5_4_Msk      0x30UL
#define ETH_NETWORK_STATUS_PFC_NEGOTIATE_PCLK_Pos 6UL
#define ETH_NETWORK_STATUS_PFC_NEGOTIATE_PCLK_Msk 0x40UL
#define ETH_NETWORK_STATUS_LPI_INDICATE_PCLK_Pos 7UL
#define ETH_NETWORK_STATUS_LPI_INDICATE_PCLK_Msk 0x80UL
/* ETH.USER_IO_REGISTER */
#define ETH_USER_IO_REGISTER_RESERVED_31_0_Pos  0UL
#define ETH_USER_IO_REGISTER_RESERVED_31_0_Msk  0xFFFFFFFFUL
/* ETH.DMA_CONFIG */
#define ETH_DMA_CONFIG_AMBA_BURST_LENGTH_Pos    0UL
#define ETH_DMA_CONFIG_AMBA_BURST_LENGTH_Msk    0x1FUL
#define ETH_DMA_CONFIG_HDR_DATA_SPLITTING_EN_Pos 5UL
#define ETH_DMA_CONFIG_HDR_DATA_SPLITTING_EN_Msk 0x20UL
#define ETH_DMA_CONFIG_ENDIAN_SWAP_MANAGEMENT_Pos 6UL
#define ETH_DMA_CONFIG_ENDIAN_SWAP_MANAGEMENT_Msk 0x40UL
#define ETH_DMA_CONFIG_ENDIAN_SWAP_PACKET_Pos   7UL
#define ETH_DMA_CONFIG_ENDIAN_SWAP_PACKET_Msk   0x80UL
#define ETH_DMA_CONFIG_RX_PBUF_SIZE_Pos         8UL
#define ETH_DMA_CONFIG_RX_PBUF_SIZE_Msk         0x300UL
#define ETH_DMA_CONFIG_TX_PBUF_SIZE_Pos         10UL
#define ETH_DMA_CONFIG_TX_PBUF_SIZE_Msk         0x400UL
#define ETH_DMA_CONFIG_TX_PBUF_TCP_EN_Pos       11UL
#define ETH_DMA_CONFIG_TX_PBUF_TCP_EN_Msk       0x800UL
#define ETH_DMA_CONFIG_INFINITE_LAST_DBUF_SIZE_EN_Pos 12UL
#define ETH_DMA_CONFIG_INFINITE_LAST_DBUF_SIZE_EN_Msk 0x1000UL
#define ETH_DMA_CONFIG_CRC_ERROR_REPORT_Pos     13UL
#define ETH_DMA_CONFIG_CRC_ERROR_REPORT_Msk     0x2000UL
#define ETH_DMA_CONFIG_RX_BUF_SIZE_Pos          16UL
#define ETH_DMA_CONFIG_RX_BUF_SIZE_Msk          0xFF0000UL
#define ETH_DMA_CONFIG_FORCE_DISCARD_ON_ERR_Pos 24UL
#define ETH_DMA_CONFIG_FORCE_DISCARD_ON_ERR_Msk 0x1000000UL
#define ETH_DMA_CONFIG_FORCE_MAX_AMBA_BURST_RX_Pos 25UL
#define ETH_DMA_CONFIG_FORCE_MAX_AMBA_BURST_RX_Msk 0x2000000UL
#define ETH_DMA_CONFIG_FORCE_MAX_AMBA_BURST_TX_Pos 26UL
#define ETH_DMA_CONFIG_FORCE_MAX_AMBA_BURST_TX_Msk 0x4000000UL
#define ETH_DMA_CONFIG_RX_BD_EXTENDED_MODE_EN_Pos 28UL
#define ETH_DMA_CONFIG_RX_BD_EXTENDED_MODE_EN_Msk 0x10000000UL
#define ETH_DMA_CONFIG_TX_BD_EXTENDED_MODE_EN_Pos 29UL
#define ETH_DMA_CONFIG_TX_BD_EXTENDED_MODE_EN_Msk 0x20000000UL
#define ETH_DMA_CONFIG_DMA_ADDR_BUS_WIDTH_1_Pos 30UL
#define ETH_DMA_CONFIG_DMA_ADDR_BUS_WIDTH_1_Msk 0x40000000UL
/* ETH.TRANSMIT_STATUS */
#define ETH_TRANSMIT_STATUS_USED_BIT_READ_Pos   0UL
#define ETH_TRANSMIT_STATUS_USED_BIT_READ_Msk   0x1UL
#define ETH_TRANSMIT_STATUS_COLLISION_OCCURRED_Pos 1UL
#define ETH_TRANSMIT_STATUS_COLLISION_OCCURRED_Msk 0x2UL
#define ETH_TRANSMIT_STATUS_RETRY_LIMIT_EXCEEDED_Pos 2UL
#define ETH_TRANSMIT_STATUS_RETRY_LIMIT_EXCEEDED_Msk 0x4UL
#define ETH_TRANSMIT_STATUS_TRANSMIT_GO_Pos     3UL
#define ETH_TRANSMIT_STATUS_TRANSMIT_GO_Msk     0x8UL
#define ETH_TRANSMIT_STATUS_AMBA_ERROR123_Pos   4UL
#define ETH_TRANSMIT_STATUS_AMBA_ERROR123_Msk   0x10UL
#define ETH_TRANSMIT_STATUS_TRANSMIT_COMPLETE123_Pos 5UL
#define ETH_TRANSMIT_STATUS_TRANSMIT_COMPLETE123_Msk 0x20UL
#define ETH_TRANSMIT_STATUS_TRANSMIT_UNDER_RUN123_Pos 6UL
#define ETH_TRANSMIT_STATUS_TRANSMIT_UNDER_RUN123_Msk 0x40UL
#define ETH_TRANSMIT_STATUS_LATE_COLLISION_OCCURRED_Pos 7UL
#define ETH_TRANSMIT_STATUS_LATE_COLLISION_OCCURRED_Msk 0x80UL
#define ETH_TRANSMIT_STATUS_RESP_NOT_OK123_Pos  8UL
#define ETH_TRANSMIT_STATUS_RESP_NOT_OK123_Msk  0x100UL
/* ETH.RECEIVE_Q_PTR */
#define ETH_RECEIVE_Q_PTR_DMA_RX_DIS_Q_Pos      0UL
#define ETH_RECEIVE_Q_PTR_DMA_RX_DIS_Q_Msk      0x1UL
#define ETH_RECEIVE_Q_PTR_DMA_RX_Q_PTR_Pos      2UL
#define ETH_RECEIVE_Q_PTR_DMA_RX_Q_PTR_Msk      0xFFFFFFFCUL
/* ETH.TRANSMIT_Q_PTR */
#define ETH_TRANSMIT_Q_PTR_DMA_TX_DIS_Q_Pos     0UL
#define ETH_TRANSMIT_Q_PTR_DMA_TX_DIS_Q_Msk     0x1UL
#define ETH_TRANSMIT_Q_PTR_DMA_TX_Q_PTR_Pos     2UL
#define ETH_TRANSMIT_Q_PTR_DMA_TX_Q_PTR_Msk     0xFFFFFFFCUL
/* ETH.RECEIVE_STATUS */
#define ETH_RECEIVE_STATUS_BUFFER_NOT_AVAILABLE_Pos 0UL
#define ETH_RECEIVE_STATUS_BUFFER_NOT_AVAILABLE_Msk 0x1UL
#define ETH_RECEIVE_STATUS_FRAME_RECEIVED_Pos   1UL
#define ETH_RECEIVE_STATUS_FRAME_RECEIVED_Msk   0x2UL
#define ETH_RECEIVE_STATUS_RECEIVE_OVERRUN123_Pos 2UL
#define ETH_RECEIVE_STATUS_RECEIVE_OVERRUN123_Msk 0x4UL
#define ETH_RECEIVE_STATUS_RESP_NOT_OK1234_Pos  3UL
#define ETH_RECEIVE_STATUS_RESP_NOT_OK1234_Msk  0x8UL
/* ETH.INT_STATUS */
#define ETH_INT_STATUS_MANAGEMENT_FRAME_SENT_Pos 0UL
#define ETH_INT_STATUS_MANAGEMENT_FRAME_SENT_Msk 0x1UL
#define ETH_INT_STATUS_RECEIVE_COMPLETE_Pos     1UL
#define ETH_INT_STATUS_RECEIVE_COMPLETE_Msk     0x2UL
#define ETH_INT_STATUS_RX_USED_BIT_READ_Pos     2UL
#define ETH_INT_STATUS_RX_USED_BIT_READ_Msk     0x4UL
#define ETH_INT_STATUS_TX_USED_BIT_READ_Pos     3UL
#define ETH_INT_STATUS_TX_USED_BIT_READ_Msk     0x8UL
#define ETH_INT_STATUS_TRANSMIT_UNDER_RUN_Pos   4UL
#define ETH_INT_STATUS_TRANSMIT_UNDER_RUN_Msk   0x10UL
#define ETH_INT_STATUS_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_Pos 5UL
#define ETH_INT_STATUS_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_Msk 0x20UL
#define ETH_INT_STATUS_AMBA_ERROR_Pos           6UL
#define ETH_INT_STATUS_AMBA_ERROR_Msk           0x40UL
#define ETH_INT_STATUS_TRANSMIT_COMPLETE_Pos    7UL
#define ETH_INT_STATUS_TRANSMIT_COMPLETE_Msk    0x80UL
#define ETH_INT_STATUS_REMOVED_9_Pos            9UL
#define ETH_INT_STATUS_REMOVED_9_Msk            0x200UL
#define ETH_INT_STATUS_RECEIVE_OVERRUN_Pos      10UL
#define ETH_INT_STATUS_RECEIVE_OVERRUN_Msk      0x400UL
#define ETH_INT_STATUS_RESP_NOT_OK_Pos          11UL
#define ETH_INT_STATUS_RESP_NOT_OK_Msk          0x800UL
#define ETH_INT_STATUS_PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_RECEIVED_Pos 12UL
#define ETH_INT_STATUS_PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_RECEIVED_Msk 0x1000UL
#define ETH_INT_STATUS_PAUSE_TIME_ELAPSED_Pos   13UL
#define ETH_INT_STATUS_PAUSE_TIME_ELAPSED_Msk   0x2000UL
#define ETH_INT_STATUS_PAUSE_FRAME_TRANSMITTED_Pos 14UL
#define ETH_INT_STATUS_PAUSE_FRAME_TRANSMITTED_Msk 0x4000UL
#define ETH_INT_STATUS_REMOVED_15_Pos           15UL
#define ETH_INT_STATUS_REMOVED_15_Msk           0x8000UL
#define ETH_INT_STATUS_REMOVED_16_Pos           16UL
#define ETH_INT_STATUS_REMOVED_16_Msk           0x10000UL
#define ETH_INT_STATUS_REMOVED_17_Pos           17UL
#define ETH_INT_STATUS_REMOVED_17_Msk           0x20000UL
#define ETH_INT_STATUS_PTP_DELAY_REQ_FRAME_RECEIVED_Pos 18UL
#define ETH_INT_STATUS_PTP_DELAY_REQ_FRAME_RECEIVED_Msk 0x40000UL
#define ETH_INT_STATUS_PTP_SYNC_FRAME_RECEIVED_Pos 19UL
#define ETH_INT_STATUS_PTP_SYNC_FRAME_RECEIVED_Msk 0x80000UL
#define ETH_INT_STATUS_PTP_DELAY_REQ_FRAME_TRANSMITTED_Pos 20UL
#define ETH_INT_STATUS_PTP_DELAY_REQ_FRAME_TRANSMITTED_Msk 0x100000UL
#define ETH_INT_STATUS_PTP_SYNC_FRAME_TRANSMITTED_Pos 21UL
#define ETH_INT_STATUS_PTP_SYNC_FRAME_TRANSMITTED_Msk 0x200000UL
#define ETH_INT_STATUS_PTP_PDELAY_REQ_FRAME_RECEIVED_Pos 22UL
#define ETH_INT_STATUS_PTP_PDELAY_REQ_FRAME_RECEIVED_Msk 0x400000UL
#define ETH_INT_STATUS_PTP_PDELAY_RESP_FRAME_RECEIVED_Pos 23UL
#define ETH_INT_STATUS_PTP_PDELAY_RESP_FRAME_RECEIVED_Msk 0x800000UL
#define ETH_INT_STATUS_PTP_PDELAY_REQ_FRAME_TRANSMITTED_Pos 24UL
#define ETH_INT_STATUS_PTP_PDELAY_REQ_FRAME_TRANSMITTED_Msk 0x1000000UL
#define ETH_INT_STATUS_PTP_PDELAY_RESP_FRAME_TRANSMITTED_Pos 25UL
#define ETH_INT_STATUS_PTP_PDELAY_RESP_FRAME_TRANSMITTED_Msk 0x2000000UL
#define ETH_INT_STATUS_TSU_SECONDS_REGISTER_INCREMENT_Pos 26UL
#define ETH_INT_STATUS_TSU_SECONDS_REGISTER_INCREMENT_Msk 0x4000000UL
#define ETH_INT_STATUS_RECEIVE_LPI_INDICATION_STATUS_BIT_CHANGE_Pos 27UL
#define ETH_INT_STATUS_RECEIVE_LPI_INDICATION_STATUS_BIT_CHANGE_Msk 0x8000000UL
#define ETH_INT_STATUS_REMOVED_28_Pos           28UL
#define ETH_INT_STATUS_REMOVED_28_Msk           0x10000000UL
#define ETH_INT_STATUS_TSU_TIMER_COMPARISON_INTERRUPT_Pos 29UL
#define ETH_INT_STATUS_TSU_TIMER_COMPARISON_INTERRUPT_Msk 0x20000000UL
/* ETH.INT_ENABLE */
#define ETH_INT_ENABLE_ENABLE_MANAGEMENT_DONE_INTERRUPT_Pos 0UL
#define ETH_INT_ENABLE_ENABLE_MANAGEMENT_DONE_INTERRUPT_Msk 0x1UL
#define ETH_INT_ENABLE_ENABLE_RECEIVE_COMPLETE_INTERRUPT_Pos 1UL
#define ETH_INT_ENABLE_ENABLE_RECEIVE_COMPLETE_INTERRUPT_Msk 0x2UL
#define ETH_INT_ENABLE_ENABLE_RECEIVE_USED_BIT_READ_INTERRUPT_Pos 2UL
#define ETH_INT_ENABLE_ENABLE_RECEIVE_USED_BIT_READ_INTERRUPT_Msk 0x4UL
#define ETH_INT_ENABLE_ENABLE_TRANSMIT_USED_BIT_READ_INTERRUPT_Pos 3UL
#define ETH_INT_ENABLE_ENABLE_TRANSMIT_USED_BIT_READ_INTERRUPT_Msk 0x8UL
#define ETH_INT_ENABLE_ENABLE_TRANSMIT_BUFFER_UNDER_RUN_INTERRUPT_Pos 4UL
#define ETH_INT_ENABLE_ENABLE_TRANSMIT_BUFFER_UNDER_RUN_INTERRUPT_Msk 0x10UL
#define ETH_INT_ENABLE_ENABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT_Pos 5UL
#define ETH_INT_ENABLE_ENABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT_Msk 0x20UL
#define ETH_INT_ENABLE_ENABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT_Pos 6UL
#define ETH_INT_ENABLE_ENABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT_Msk 0x40UL
#define ETH_INT_ENABLE_ENABLE_TRANSMIT_COMPLETE_INTERRUPT_Pos 7UL
#define ETH_INT_ENABLE_ENABLE_TRANSMIT_COMPLETE_INTERRUPT_Msk 0x80UL
#define ETH_INT_ENABLE_UNUSED_8_Pos             8UL
#define ETH_INT_ENABLE_UNUSED_8_Msk             0x100UL
#define ETH_INT_ENABLE_UNUSED_9_Pos             9UL
#define ETH_INT_ENABLE_UNUSED_9_Msk             0x200UL
#define ETH_INT_ENABLE_ENABLE_RECEIVE_OVERRUN_INTERRUPT_Pos 10UL
#define ETH_INT_ENABLE_ENABLE_RECEIVE_OVERRUN_INTERRUPT_Msk 0x400UL
#define ETH_INT_ENABLE_ENABLE_RESP_NOT_OK_INTERRUPT_Pos 11UL
#define ETH_INT_ENABLE_ENABLE_RESP_NOT_OK_INTERRUPT_Msk 0x800UL
#define ETH_INT_ENABLE_ENABLE_PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_INTERRUPT_Pos 12UL
#define ETH_INT_ENABLE_ENABLE_PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_INTERRUPT_Msk 0x1000UL
#define ETH_INT_ENABLE_ENABLE_PAUSE_TIME_ZERO_INTERRUPT_Pos 13UL
#define ETH_INT_ENABLE_ENABLE_PAUSE_TIME_ZERO_INTERRUPT_Msk 0x2000UL
#define ETH_INT_ENABLE_ENABLE_PAUSE_FRAME_TRANSMITTED_INTERRUPT_Pos 14UL
#define ETH_INT_ENABLE_ENABLE_PAUSE_FRAME_TRANSMITTED_INTERRUPT_Msk 0x4000UL
#define ETH_INT_ENABLE_UNUSED_15_Pos            15UL
#define ETH_INT_ENABLE_UNUSED_15_Msk            0x8000UL
#define ETH_INT_ENABLE_UNUSED_16_Pos            16UL
#define ETH_INT_ENABLE_UNUSED_16_Msk            0x10000UL
#define ETH_INT_ENABLE_UNUSED_17_Pos            17UL
#define ETH_INT_ENABLE_UNUSED_17_Msk            0x20000UL
#define ETH_INT_ENABLE_ENABLE_PTP_DELAY_REQ_FRAME_RECEIVED_Pos 18UL
#define ETH_INT_ENABLE_ENABLE_PTP_DELAY_REQ_FRAME_RECEIVED_Msk 0x40000UL
#define ETH_INT_ENABLE_ENABLE_PTP_SYNC_FRAME_RECEIVED_Pos 19UL
#define ETH_INT_ENABLE_ENABLE_PTP_SYNC_FRAME_RECEIVED_Msk 0x80000UL
#define ETH_INT_ENABLE_ENABLE_PTP_DELAY_REQ_FRAME_TRANSMITTED_Pos 20UL
#define ETH_INT_ENABLE_ENABLE_PTP_DELAY_REQ_FRAME_TRANSMITTED_Msk 0x100000UL
#define ETH_INT_ENABLE_ENABLE_PTP_SYNC_FRAME_TRANSMITTED_Pos 21UL
#define ETH_INT_ENABLE_ENABLE_PTP_SYNC_FRAME_TRANSMITTED_Msk 0x200000UL
#define ETH_INT_ENABLE_ENABLE_PTP_PDELAY_REQ_FRAME_RECEIVED_Pos 22UL
#define ETH_INT_ENABLE_ENABLE_PTP_PDELAY_REQ_FRAME_RECEIVED_Msk 0x400000UL
#define ETH_INT_ENABLE_ENABLE_PTP_PDELAY_RESP_FRAME_RECEIVED_Pos 23UL
#define ETH_INT_ENABLE_ENABLE_PTP_PDELAY_RESP_FRAME_RECEIVED_Msk 0x800000UL
#define ETH_INT_ENABLE_ENABLE_PTP_PDELAY_REQ_FRAME_TRANSMITTED_Pos 24UL
#define ETH_INT_ENABLE_ENABLE_PTP_PDELAY_REQ_FRAME_TRANSMITTED_Msk 0x1000000UL
#define ETH_INT_ENABLE_ENABLE_PTP_PDELAY_RESP_FRAME_TRANSMITTED_Pos 25UL
#define ETH_INT_ENABLE_ENABLE_PTP_PDELAY_RESP_FRAME_TRANSMITTED_Msk 0x2000000UL
#define ETH_INT_ENABLE_ENABLE_TSU_SECONDS_REGISTER_INCREMENT_Pos 26UL
#define ETH_INT_ENABLE_ENABLE_TSU_SECONDS_REGISTER_INCREMENT_Msk 0x4000000UL
#define ETH_INT_ENABLE_ENABLE_RX_LPI_INDICATION_INTERRUPT_Pos 27UL
#define ETH_INT_ENABLE_ENABLE_RX_LPI_INDICATION_INTERRUPT_Msk 0x8000000UL
#define ETH_INT_ENABLE_UNUSED_28_Pos            28UL
#define ETH_INT_ENABLE_UNUSED_28_Msk            0x10000000UL
#define ETH_INT_ENABLE_ENABLE_TSU_TIMER_COMPARISON_INTERRUPT_Pos 29UL
#define ETH_INT_ENABLE_ENABLE_TSU_TIMER_COMPARISON_INTERRUPT_Msk 0x20000000UL
/* ETH.INT_DISABLE */
#define ETH_INT_DISABLE_DISABLE_MANAGEMENT_DONE_INTERRUPT_Pos 0UL
#define ETH_INT_DISABLE_DISABLE_MANAGEMENT_DONE_INTERRUPT_Msk 0x1UL
#define ETH_INT_DISABLE_DISABLE_RECEIVE_COMPLETE_INTERRUPT_Pos 1UL
#define ETH_INT_DISABLE_DISABLE_RECEIVE_COMPLETE_INTERRUPT_Msk 0x2UL
#define ETH_INT_DISABLE_DISABLE_RECEIVE_USED_BIT_READ_INTERRUPT_Pos 2UL
#define ETH_INT_DISABLE_DISABLE_RECEIVE_USED_BIT_READ_INTERRUPT_Msk 0x4UL
#define ETH_INT_DISABLE_DISABLE_TRANSMIT_USED_BIT_READ_INTERRUPT_Pos 3UL
#define ETH_INT_DISABLE_DISABLE_TRANSMIT_USED_BIT_READ_INTERRUPT_Msk 0x8UL
#define ETH_INT_DISABLE_DISABLE_TRANSMIT_BUFFER_UNDER_RUN_INTERRUPT_Pos 4UL
#define ETH_INT_DISABLE_DISABLE_TRANSMIT_BUFFER_UNDER_RUN_INTERRUPT_Msk 0x10UL
#define ETH_INT_DISABLE_DISABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT_Pos 5UL
#define ETH_INT_DISABLE_DISABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT_Msk 0x20UL
#define ETH_INT_DISABLE_DISABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT_Pos 6UL
#define ETH_INT_DISABLE_DISABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT_Msk 0x40UL
#define ETH_INT_DISABLE_DISABLE_TRANSMIT_COMPLETE_INTERRUPT_Pos 7UL
#define ETH_INT_DISABLE_DISABLE_TRANSMIT_COMPLETE_INTERRUPT_Msk 0x80UL
#define ETH_INT_DISABLE_UNUSED_8_Pos            8UL
#define ETH_INT_DISABLE_UNUSED_8_Msk            0x100UL
#define ETH_INT_DISABLE_UNUSED_9_Pos            9UL
#define ETH_INT_DISABLE_UNUSED_9_Msk            0x200UL
#define ETH_INT_DISABLE_DISABLE_RECEIVE_OVERRUN_INTERRUPT_Pos 10UL
#define ETH_INT_DISABLE_DISABLE_RECEIVE_OVERRUN_INTERRUPT_Msk 0x400UL
#define ETH_INT_DISABLE_DISABLE_RESP_NOT_OK_INTERRUPT_Pos 11UL
#define ETH_INT_DISABLE_DISABLE_RESP_NOT_OK_INTERRUPT_Msk 0x800UL
#define ETH_INT_DISABLE_DISABLE_PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_INTERRUPT_Pos 12UL
#define ETH_INT_DISABLE_DISABLE_PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_INTERRUPT_Msk 0x1000UL
#define ETH_INT_DISABLE_DISABLE_PAUSE_TIME_ZERO_INTERRUPT_Pos 13UL
#define ETH_INT_DISABLE_DISABLE_PAUSE_TIME_ZERO_INTERRUPT_Msk 0x2000UL
#define ETH_INT_DISABLE_DISABLE_PAUSE_FRAME_TRANSMITTED_INTERRUPT_Pos 14UL
#define ETH_INT_DISABLE_DISABLE_PAUSE_FRAME_TRANSMITTED_INTERRUPT_Msk 0x4000UL
#define ETH_INT_DISABLE_UNUSED_15_Pos           15UL
#define ETH_INT_DISABLE_UNUSED_15_Msk           0x8000UL
#define ETH_INT_DISABLE_UNUSED_16_Pos           16UL
#define ETH_INT_DISABLE_UNUSED_16_Msk           0x10000UL
#define ETH_INT_DISABLE_UNUSED_17_Pos           17UL
#define ETH_INT_DISABLE_UNUSED_17_Msk           0x20000UL
#define ETH_INT_DISABLE_DISABLE_PTP_DELAY_REQ_FRAME_RECEIVED_Pos 18UL
#define ETH_INT_DISABLE_DISABLE_PTP_DELAY_REQ_FRAME_RECEIVED_Msk 0x40000UL
#define ETH_INT_DISABLE_DISABLE_PTP_SYNC_FRAME_RECEIVED_Pos 19UL
#define ETH_INT_DISABLE_DISABLE_PTP_SYNC_FRAME_RECEIVED_Msk 0x80000UL
#define ETH_INT_DISABLE_DISABLE_PTP_DELAY_REQ_FRAME_TRANSMITTED_Pos 20UL
#define ETH_INT_DISABLE_DISABLE_PTP_DELAY_REQ_FRAME_TRANSMITTED_Msk 0x100000UL
#define ETH_INT_DISABLE_DISABLE_PTP_SYNC_FRAME_TRANSMITTED_Pos 21UL
#define ETH_INT_DISABLE_DISABLE_PTP_SYNC_FRAME_TRANSMITTED_Msk 0x200000UL
#define ETH_INT_DISABLE_DISABLE_PTP_PDELAY_REQ_FRAME_RECEIVED_Pos 22UL
#define ETH_INT_DISABLE_DISABLE_PTP_PDELAY_REQ_FRAME_RECEIVED_Msk 0x400000UL
#define ETH_INT_DISABLE_DISABLE_PTP_PDELAY_RESP_FRAME_RECEIVED_Pos 23UL
#define ETH_INT_DISABLE_DISABLE_PTP_PDELAY_RESP_FRAME_RECEIVED_Msk 0x800000UL
#define ETH_INT_DISABLE_DISABLE_PTP_PDELAY_REQ_FRAME_TRANSMITTED_Pos 24UL
#define ETH_INT_DISABLE_DISABLE_PTP_PDELAY_REQ_FRAME_TRANSMITTED_Msk 0x1000000UL
#define ETH_INT_DISABLE_DISABLE_PTP_PDELAY_RESP_FRAME_TRANSMITTED_Pos 25UL
#define ETH_INT_DISABLE_DISABLE_PTP_PDELAY_RESP_FRAME_TRANSMITTED_Msk 0x2000000UL
#define ETH_INT_DISABLE_DISABLE_TSU_SECONDS_REGISTER_INCREMENT_Pos 26UL
#define ETH_INT_DISABLE_DISABLE_TSU_SECONDS_REGISTER_INCREMENT_Msk 0x4000000UL
#define ETH_INT_DISABLE_DISABLE_RX_LPI_INDICATION_INTERRUPT_Pos 27UL
#define ETH_INT_DISABLE_DISABLE_RX_LPI_INDICATION_INTERRUPT_Msk 0x8000000UL
#define ETH_INT_DISABLE_UNUSED_28_Pos           28UL
#define ETH_INT_DISABLE_UNUSED_28_Msk           0x10000000UL
#define ETH_INT_DISABLE_DISABLE_TSU_TIMER_COMPARISON_INTERRUPT_Pos 29UL
#define ETH_INT_DISABLE_DISABLE_TSU_TIMER_COMPARISON_INTERRUPT_Msk 0x20000000UL
#define ETH_INT_DISABLE_RESERVED_30_30_Pos      30UL
#define ETH_INT_DISABLE_RESERVED_30_30_Msk      0x40000000UL
#define ETH_INT_DISABLE_RESERVED_31_31_Pos      31UL
#define ETH_INT_DISABLE_RESERVED_31_31_Msk      0x80000000UL
/* ETH.INT_MASK */
#define ETH_INT_MASK_MANAGEMENT_DONE_INTERRUPT_MASK_Pos 0UL
#define ETH_INT_MASK_MANAGEMENT_DONE_INTERRUPT_MASK_Msk 0x1UL
#define ETH_INT_MASK_RECEIVE_COMPLETE_INTERRUPT_MASK_Pos 1UL
#define ETH_INT_MASK_RECEIVE_COMPLETE_INTERRUPT_MASK_Msk 0x2UL
#define ETH_INT_MASK_RECEIVE_USED_BIT_READ_INTERRUPT_MASK_Pos 2UL
#define ETH_INT_MASK_RECEIVE_USED_BIT_READ_INTERRUPT_MASK_Msk 0x4UL
#define ETH_INT_MASK_TRANSMIT_USED_BIT_READ_INTERRUPT_MASK_Pos 3UL
#define ETH_INT_MASK_TRANSMIT_USED_BIT_READ_INTERRUPT_MASK_Msk 0x8UL
#define ETH_INT_MASK_TRANSMIT_BUFFER_UNDER_RUN_INTERRUPT_MASK_Pos 4UL
#define ETH_INT_MASK_TRANSMIT_BUFFER_UNDER_RUN_INTERRUPT_MASK_Msk 0x10UL
#define ETH_INT_MASK_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_MASK_Pos 5UL
#define ETH_INT_MASK_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_MASK_Msk 0x20UL
#define ETH_INT_MASK_AMBA_ERROR_INTERRUPT_MASK_Pos 6UL
#define ETH_INT_MASK_AMBA_ERROR_INTERRUPT_MASK_Msk 0x40UL
#define ETH_INT_MASK_TRANSMIT_COMPLETE_INTERRUPT_MASK_Pos 7UL
#define ETH_INT_MASK_TRANSMIT_COMPLETE_INTERRUPT_MASK_Msk 0x80UL
#define ETH_INT_MASK_UNUSED_8_Pos               8UL
#define ETH_INT_MASK_UNUSED_8_Msk               0x100UL
#define ETH_INT_MASK_UNUSED_9_Pos               9UL
#define ETH_INT_MASK_UNUSED_9_Msk               0x200UL
#define ETH_INT_MASK_RECEIVE_OVERRUN_INTERRUPT_MASK_Pos 10UL
#define ETH_INT_MASK_RECEIVE_OVERRUN_INTERRUPT_MASK_Msk 0x400UL
#define ETH_INT_MASK_RESP_NOT_OK_INTERRUPT_MASK_Pos 11UL
#define ETH_INT_MASK_RESP_NOT_OK_INTERRUPT_MASK_Msk 0x800UL
#define ETH_INT_MASK_PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_INTERRUPT_MASK_Pos 12UL
#define ETH_INT_MASK_PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_INTERRUPT_MASK_Msk 0x1000UL
#define ETH_INT_MASK_PAUSE_TIME_ZERO_INTERRUPT_MASK_Pos 13UL
#define ETH_INT_MASK_PAUSE_TIME_ZERO_INTERRUPT_MASK_Msk 0x2000UL
#define ETH_INT_MASK_PAUSE_FRAME_TRANSMITTED_INTERRUPT_MASK_Pos 14UL
#define ETH_INT_MASK_PAUSE_FRAME_TRANSMITTED_INTERRUPT_MASK_Msk 0x4000UL
#define ETH_INT_MASK_UNUSED_15_Pos              15UL
#define ETH_INT_MASK_UNUSED_15_Msk              0x8000UL
#define ETH_INT_MASK_UNUSED_16_Pos              16UL
#define ETH_INT_MASK_UNUSED_16_Msk              0x10000UL
#define ETH_INT_MASK_UNUSED_17_Pos              17UL
#define ETH_INT_MASK_UNUSED_17_Msk              0x20000UL
#define ETH_INT_MASK_PTP_DELAY_REQ_FRAME_RECEIVED_MASK_Pos 18UL
#define ETH_INT_MASK_PTP_DELAY_REQ_FRAME_RECEIVED_MASK_Msk 0x40000UL
#define ETH_INT_MASK_PTP_SYNC_FRAME_RECEIVED_MASK_Pos 19UL
#define ETH_INT_MASK_PTP_SYNC_FRAME_RECEIVED_MASK_Msk 0x80000UL
#define ETH_INT_MASK_PTP_DELAY_REQ_FRAME_TRANSMITTED_MASK_Pos 20UL
#define ETH_INT_MASK_PTP_DELAY_REQ_FRAME_TRANSMITTED_MASK_Msk 0x100000UL
#define ETH_INT_MASK_PTP_SYNC_FRAME_TRANSMITTED_MASK_Pos 21UL
#define ETH_INT_MASK_PTP_SYNC_FRAME_TRANSMITTED_MASK_Msk 0x200000UL
#define ETH_INT_MASK_PTP_PDELAY_REQ_FRAME_RECEIVED_MASK_Pos 22UL
#define ETH_INT_MASK_PTP_PDELAY_REQ_FRAME_RECEIVED_MASK_Msk 0x400000UL
#define ETH_INT_MASK_PTP_PDELAY_RESP_FRAME_RECEIVED_MASK_Pos 23UL
#define ETH_INT_MASK_PTP_PDELAY_RESP_FRAME_RECEIVED_MASK_Msk 0x800000UL
#define ETH_INT_MASK_PTP_PDELAY_REQ_FRAME_TRANSMITTED_MASK_Pos 24UL
#define ETH_INT_MASK_PTP_PDELAY_REQ_FRAME_TRANSMITTED_MASK_Msk 0x1000000UL
#define ETH_INT_MASK_PTP_PDELAY_RESP_FRAME_TRANSMITTED_MASK_Pos 25UL
#define ETH_INT_MASK_PTP_PDELAY_RESP_FRAME_TRANSMITTED_MASK_Msk 0x2000000UL
#define ETH_INT_MASK_TSU_SECONDS_REGISTER_INCREMENT_MASK_Pos 26UL
#define ETH_INT_MASK_TSU_SECONDS_REGISTER_INCREMENT_MASK_Msk 0x4000000UL
#define ETH_INT_MASK_RX_LPI_INDICATION_MASK_Pos 27UL
#define ETH_INT_MASK_RX_LPI_INDICATION_MASK_Msk 0x8000000UL
#define ETH_INT_MASK_UNUSED_28_Pos              28UL
#define ETH_INT_MASK_UNUSED_28_Msk              0x10000000UL
#define ETH_INT_MASK_TSU_TIMER_COMPARISON_MASK_Pos 29UL
#define ETH_INT_MASK_TSU_TIMER_COMPARISON_MASK_Msk 0x20000000UL
/* ETH.PHY_MANAGEMENT */
#define ETH_PHY_MANAGEMENT_PHY_WRITE_READ_DATA_Pos 0UL
#define ETH_PHY_MANAGEMENT_PHY_WRITE_READ_DATA_Msk 0xFFFFUL
#define ETH_PHY_MANAGEMENT_WRITE10_Pos          16UL
#define ETH_PHY_MANAGEMENT_WRITE10_Msk          0x30000UL
#define ETH_PHY_MANAGEMENT_REGISTER_ADDRESS_Pos 18UL
#define ETH_PHY_MANAGEMENT_REGISTER_ADDRESS_Msk 0x7C0000UL
#define ETH_PHY_MANAGEMENT_PHY_ADDRESS_Pos      23UL
#define ETH_PHY_MANAGEMENT_PHY_ADDRESS_Msk      0xF800000UL
#define ETH_PHY_MANAGEMENT_OPERATION_Pos        28UL
#define ETH_PHY_MANAGEMENT_OPERATION_Msk        0x30000000UL
#define ETH_PHY_MANAGEMENT_WRITE1_Pos           30UL
#define ETH_PHY_MANAGEMENT_WRITE1_Msk           0x40000000UL
#define ETH_PHY_MANAGEMENT_WRITE0_Pos           31UL
#define ETH_PHY_MANAGEMENT_WRITE0_Msk           0x80000000UL
/* ETH.PAUSE_TIME */
#define ETH_PAUSE_TIME_QUANTUM_Pos              0UL
#define ETH_PAUSE_TIME_QUANTUM_Msk              0xFFFFUL
/* ETH.TX_PAUSE_QUANTUM */
#define ETH_TX_PAUSE_QUANTUM_QUANTUM_Pos        0UL
#define ETH_TX_PAUSE_QUANTUM_QUANTUM_Msk        0xFFFFUL
#define ETH_TX_PAUSE_QUANTUM_QUANTUM_P1_Pos     16UL
#define ETH_TX_PAUSE_QUANTUM_QUANTUM_P1_Msk     0xFFFF0000UL
/* ETH.PBUF_TXCUTTHRU */
#define ETH_PBUF_TXCUTTHRU_DMA_TX_CUTTHRU_THRESHOLD_Pos 0UL
#define ETH_PBUF_TXCUTTHRU_DMA_TX_CUTTHRU_THRESHOLD_Msk 0x1FFUL
#define ETH_PBUF_TXCUTTHRU_DMA_TX_CUTTHRU_Pos   31UL
#define ETH_PBUF_TXCUTTHRU_DMA_TX_CUTTHRU_Msk   0x80000000UL
/* ETH.PBUF_RXCUTTHRU */
#define ETH_PBUF_RXCUTTHRU_DMA_RX_CUTTHRU_THRESHOLD_Pos 0UL
#define ETH_PBUF_RXCUTTHRU_DMA_RX_CUTTHRU_THRESHOLD_Msk 0xFFUL
#define ETH_PBUF_RXCUTTHRU_DMA_RX_CUTTHRU_Pos   31UL
#define ETH_PBUF_RXCUTTHRU_DMA_RX_CUTTHRU_Msk   0x80000000UL
/* ETH.JUMBO_MAX_LENGTH */
#define ETH_JUMBO_MAX_LENGTH_JUMBO_MAX_LENGTH_Pos 0UL
#define ETH_JUMBO_MAX_LENGTH_JUMBO_MAX_LENGTH_Msk 0x3FFFUL
/* ETH.EXTERNAL_FIFO_INTERFACE */
#define ETH_EXTERNAL_FIFO_INTERFACE_REMOVED_31_0_Pos 0UL
#define ETH_EXTERNAL_FIFO_INTERFACE_REMOVED_31_0_Msk 0xFFFFFFFFUL
/* ETH.AXI_MAX_PIPELINE */
#define ETH_AXI_MAX_PIPELINE_AR2R_MAX_PIPELINE_Pos 0UL
#define ETH_AXI_MAX_PIPELINE_AR2R_MAX_PIPELINE_Msk 0xFFUL
#define ETH_AXI_MAX_PIPELINE_AW2W_MAX_PIPELINE_Pos 8UL
#define ETH_AXI_MAX_PIPELINE_AW2W_MAX_PIPELINE_Msk 0xFF00UL
#define ETH_AXI_MAX_PIPELINE_USE_AW2B_FILL_Pos  16UL
#define ETH_AXI_MAX_PIPELINE_USE_AW2B_FILL_Msk  0x10000UL
/* ETH.RSC_CONTROL */
#define ETH_RSC_CONTROL_REMOVED_31_0_Pos        0UL
#define ETH_RSC_CONTROL_REMOVED_31_0_Msk        0xFFFFFFFFUL
/* ETH.INT_MODERATION */
#define ETH_INT_MODERATION_RX_INT_MODERATION_Pos 0UL
#define ETH_INT_MODERATION_RX_INT_MODERATION_Msk 0xFFUL
#define ETH_INT_MODERATION_TX_INT_MODERATION_Pos 16UL
#define ETH_INT_MODERATION_TX_INT_MODERATION_Msk 0xFF0000UL
/* ETH.SYS_WAKE_TIME */
#define ETH_SYS_WAKE_TIME_SYS_WAKE_TIME_Pos     0UL
#define ETH_SYS_WAKE_TIME_SYS_WAKE_TIME_Msk     0xFFFFUL
/* ETH.HASH_BOTTOM */
#define ETH_HASH_BOTTOM_ADDRESS_HASH_B_Pos      0UL
#define ETH_HASH_BOTTOM_ADDRESS_HASH_B_Msk      0xFFFFFFFFUL
/* ETH.HASH_TOP */
#define ETH_HASH_TOP_ADDRESS_HASH_T_Pos         0UL
#define ETH_HASH_TOP_ADDRESS_HASH_T_Msk         0xFFFFFFFFUL
/* ETH.SPEC_ADD1_BOTTOM */
#define ETH_SPEC_ADD1_BOTTOM_ADDRESS_ADD1_B_Pos 0UL
#define ETH_SPEC_ADD1_BOTTOM_ADDRESS_ADD1_B_Msk 0xFFFFFFFFUL
/* ETH.SPEC_ADD1_TOP */
#define ETH_SPEC_ADD1_TOP_ADDRESS_TOP_Pos       0UL
#define ETH_SPEC_ADD1_TOP_ADDRESS_TOP_Msk       0xFFFFUL
#define ETH_SPEC_ADD1_TOP_FILTER_TYPE_Pos       16UL
#define ETH_SPEC_ADD1_TOP_FILTER_TYPE_Msk       0x10000UL
/* ETH.SPEC_ADD2_BOTTOM */
#define ETH_SPEC_ADD2_BOTTOM_ADDRESS_BOTTOM_Pos 0UL
#define ETH_SPEC_ADD2_BOTTOM_ADDRESS_BOTTOM_Msk 0xFFFFFFFFUL
/* ETH.SPEC_ADD2_TOP */
#define ETH_SPEC_ADD2_TOP_ADDRESS_TOP_Pos       0UL
#define ETH_SPEC_ADD2_TOP_ADDRESS_TOP_Msk       0xFFFFUL
#define ETH_SPEC_ADD2_TOP_FILTER_TYPE_Pos       16UL
#define ETH_SPEC_ADD2_TOP_FILTER_TYPE_Msk       0x10000UL
#define ETH_SPEC_ADD2_TOP_FILTER_BYTE_MASK_Pos  24UL
#define ETH_SPEC_ADD2_TOP_FILTER_BYTE_MASK_Msk  0x3F000000UL
/* ETH.SPEC_ADD3_BOTTOM */
#define ETH_SPEC_ADD3_BOTTOM_ADDRESS_BOTTOM_Pos 0UL
#define ETH_SPEC_ADD3_BOTTOM_ADDRESS_BOTTOM_Msk 0xFFFFFFFFUL
/* ETH.SPEC_ADD3_TOP */
#define ETH_SPEC_ADD3_TOP_ADDRESS_TOP_Pos       0UL
#define ETH_SPEC_ADD3_TOP_ADDRESS_TOP_Msk       0xFFFFUL
#define ETH_SPEC_ADD3_TOP_FILTER_TYPE_Pos       16UL
#define ETH_SPEC_ADD3_TOP_FILTER_TYPE_Msk       0x10000UL
#define ETH_SPEC_ADD3_TOP_FILTER_BYTE_MASK_Pos  24UL
#define ETH_SPEC_ADD3_TOP_FILTER_BYTE_MASK_Msk  0x3F000000UL
/* ETH.SPEC_ADD4_BOTTOM */
#define ETH_SPEC_ADD4_BOTTOM_ADDRESS_BOTTOM_Pos 0UL
#define ETH_SPEC_ADD4_BOTTOM_ADDRESS_BOTTOM_Msk 0xFFFFFFFFUL
/* ETH.SPEC_ADD4_TOP */
#define ETH_SPEC_ADD4_TOP_ADDRESS_TOP_Pos       0UL
#define ETH_SPEC_ADD4_TOP_ADDRESS_TOP_Msk       0xFFFFUL
#define ETH_SPEC_ADD4_TOP_FILTER_TYPE_Pos       16UL
#define ETH_SPEC_ADD4_TOP_FILTER_TYPE_Msk       0x10000UL
#define ETH_SPEC_ADD4_TOP_FILTER_BYTE_MASK_Pos  24UL
#define ETH_SPEC_ADD4_TOP_FILTER_BYTE_MASK_Msk  0x3F000000UL
/* ETH.SPEC_TYPE1 */
#define ETH_SPEC_TYPE1_MATCH_Pos                0UL
#define ETH_SPEC_TYPE1_MATCH_Msk                0xFFFFUL
#define ETH_SPEC_TYPE1_ENABLE_COPY_Pos          31UL
#define ETH_SPEC_TYPE1_ENABLE_COPY_Msk          0x80000000UL
/* ETH.SPEC_TYPE2 */
#define ETH_SPEC_TYPE2_MATCH_Pos                0UL
#define ETH_SPEC_TYPE2_MATCH_Msk                0xFFFFUL
#define ETH_SPEC_TYPE2_ENABLE_COPY_Pos          31UL
#define ETH_SPEC_TYPE2_ENABLE_COPY_Msk          0x80000000UL
/* ETH.SPEC_TYPE3 */
#define ETH_SPEC_TYPE3_MATCH_Pos                0UL
#define ETH_SPEC_TYPE3_MATCH_Msk                0xFFFFUL
#define ETH_SPEC_TYPE3_ENABLE_COPY_Pos          31UL
#define ETH_SPEC_TYPE3_ENABLE_COPY_Msk          0x80000000UL
/* ETH.SPEC_TYPE4 */
#define ETH_SPEC_TYPE4_MATCH_Pos                0UL
#define ETH_SPEC_TYPE4_MATCH_Msk                0xFFFFUL
#define ETH_SPEC_TYPE4_ENABLE_COPY_Pos          31UL
#define ETH_SPEC_TYPE4_ENABLE_COPY_Msk          0x80000000UL
/* ETH.WOL_REGISTER */
#define ETH_WOL_REGISTER_ADDR_Pos               0UL
#define ETH_WOL_REGISTER_ADDR_Msk               0xFFFFUL
#define ETH_WOL_REGISTER_WOL_MASK_0_Pos         16UL
#define ETH_WOL_REGISTER_WOL_MASK_0_Msk         0x10000UL
#define ETH_WOL_REGISTER_WOL_MASK_1_Pos         17UL
#define ETH_WOL_REGISTER_WOL_MASK_1_Msk         0x20000UL
#define ETH_WOL_REGISTER_WOL_MASK_2_Pos         18UL
#define ETH_WOL_REGISTER_WOL_MASK_2_Msk         0x40000UL
#define ETH_WOL_REGISTER_WOL_MASK_3_Pos         19UL
#define ETH_WOL_REGISTER_WOL_MASK_3_Msk         0x80000UL
/* ETH.STRETCH_RATIO */
#define ETH_STRETCH_RATIO_IPG_STRETCH_Pos       0UL
#define ETH_STRETCH_RATIO_IPG_STRETCH_Msk       0xFFFFUL
/* ETH.STACKED_VLAN */
#define ETH_STACKED_VLAN_MATCH_Pos              0UL
#define ETH_STACKED_VLAN_MATCH_Msk              0xFFFFUL
#define ETH_STACKED_VLAN_ENABLE_PROCESSING_Pos  31UL
#define ETH_STACKED_VLAN_ENABLE_PROCESSING_Msk  0x80000000UL
/* ETH.TX_PFC_PAUSE */
#define ETH_TX_PFC_PAUSE_VECTOR_ENABLE_Pos      0UL
#define ETH_TX_PFC_PAUSE_VECTOR_ENABLE_Msk      0xFFUL
#define ETH_TX_PFC_PAUSE_VECTOR_Pos             8UL
#define ETH_TX_PFC_PAUSE_VECTOR_Msk             0xFF00UL
/* ETH.MASK_ADD1_BOTTOM */
#define ETH_MASK_ADD1_BOTTOM_ADDRESS_MASK_BOTTOM_Pos 0UL
#define ETH_MASK_ADD1_BOTTOM_ADDRESS_MASK_BOTTOM_Msk 0xFFFFFFFFUL
/* ETH.MASK_ADD1_TOP */
#define ETH_MASK_ADD1_TOP_ADDRESS_MASK_TOP_Pos  0UL
#define ETH_MASK_ADD1_TOP_ADDRESS_MASK_TOP_Msk  0xFFFFUL
/* ETH.DMA_ADDR_OR_MASK */
#define ETH_DMA_ADDR_OR_MASK_MASK_ENABLE_Pos    0UL
#define ETH_DMA_ADDR_OR_MASK_MASK_ENABLE_Msk    0xFUL
#define ETH_DMA_ADDR_OR_MASK_MASK_VALUE_DA_Pos  28UL
#define ETH_DMA_ADDR_OR_MASK_MASK_VALUE_DA_Msk  0xF0000000UL
/* ETH.RX_PTP_UNICAST */
#define ETH_RX_PTP_UNICAST_ADDRESS_UNICAST_Pos  0UL
#define ETH_RX_PTP_UNICAST_ADDRESS_UNICAST_Msk  0xFFFFFFFFUL
/* ETH.TX_PTP_UNICAST */
#define ETH_TX_PTP_UNICAST_ADDRESS_UNICAST_Pos  0UL
#define ETH_TX_PTP_UNICAST_ADDRESS_UNICAST_Msk  0xFFFFFFFFUL
/* ETH.TSU_NSEC_CMP */
#define ETH_TSU_NSEC_CMP_COMPARISON_NSEC_Pos    0UL
#define ETH_TSU_NSEC_CMP_COMPARISON_NSEC_Msk    0x3FFFFFUL
/* ETH.TSU_SEC_CMP */
#define ETH_TSU_SEC_CMP_COMPARISON_SEC_Pos      0UL
#define ETH_TSU_SEC_CMP_COMPARISON_SEC_Msk      0xFFFFFFFFUL
/* ETH.TSU_MSB_SEC_CMP */
#define ETH_TSU_MSB_SEC_CMP_COMPARISON_MSB_SEC_Pos 0UL
#define ETH_TSU_MSB_SEC_CMP_COMPARISON_MSB_SEC_Msk 0xFFFFUL
/* ETH.TSU_PTP_TX_MSB_SEC */
#define ETH_TSU_PTP_TX_MSB_SEC_TIMER_SECONDS_Pos 0UL
#define ETH_TSU_PTP_TX_MSB_SEC_TIMER_SECONDS_Msk 0xFFFFUL
/* ETH.TSU_PTP_RX_MSB_SEC */
#define ETH_TSU_PTP_RX_MSB_SEC_TIMER_SECONDS_Pos 0UL
#define ETH_TSU_PTP_RX_MSB_SEC_TIMER_SECONDS_Msk 0xFFFFUL
/* ETH.TSU_PEER_TX_MSB_SEC */
#define ETH_TSU_PEER_TX_MSB_SEC_TIMER_SECONDS_Pos 0UL
#define ETH_TSU_PEER_TX_MSB_SEC_TIMER_SECONDS_Msk 0xFFFFUL
/* ETH.TSU_PEER_RX_MSB_SEC */
#define ETH_TSU_PEER_RX_MSB_SEC_TIMER_SECONDS_Pos 0UL
#define ETH_TSU_PEER_RX_MSB_SEC_TIMER_SECONDS_Msk 0xFFFFUL
/* ETH.DPRAM_FILL_DBG */
#define ETH_DPRAM_FILL_DBG_DMA_TX_RX_FILL_LEVEL_SELECT_Pos 0UL
#define ETH_DPRAM_FILL_DBG_DMA_TX_RX_FILL_LEVEL_SELECT_Msk 0x1UL
#define ETH_DPRAM_FILL_DBG_DMA_TX_Q_FILL_LEVEL_SELECT_Pos 4UL
#define ETH_DPRAM_FILL_DBG_DMA_TX_Q_FILL_LEVEL_SELECT_Msk 0xF0UL
#define ETH_DPRAM_FILL_DBG_DMA_TX_RX_FILL_LEVEL_Pos 16UL
#define ETH_DPRAM_FILL_DBG_DMA_TX_RX_FILL_LEVEL_Msk 0xFFFF0000UL
/* ETH.REVISION_REG */
#define ETH_REVISION_REG_MODULE_REVISION_Pos    0UL
#define ETH_REVISION_REG_MODULE_REVISION_Msk    0xFFFFUL
#define ETH_REVISION_REG_MODULE_IDENTIFICATION_NUMBER_Pos 16UL
#define ETH_REVISION_REG_MODULE_IDENTIFICATION_NUMBER_Msk 0xFFF0000UL
#define ETH_REVISION_REG_FIX_NUMBER_Pos         28UL
#define ETH_REVISION_REG_FIX_NUMBER_Msk         0xF0000000UL
/* ETH.OCTETS_TXED_BOTTOM */
#define ETH_OCTETS_TXED_BOTTOM_COUNT_BOTTOM_Pos 0UL
#define ETH_OCTETS_TXED_BOTTOM_COUNT_BOTTOM_Msk 0xFFFFFFFFUL
/* ETH.OCTETS_TXED_TOP */
#define ETH_OCTETS_TXED_TOP_COUNT_TOP_Pos       0UL
#define ETH_OCTETS_TXED_TOP_COUNT_TOP_Msk       0xFFFFUL
/* ETH.FRAMES_TXED_OK */
#define ETH_FRAMES_TXED_OK_COUNT_OK_Pos         0UL
#define ETH_FRAMES_TXED_OK_COUNT_OK_Msk         0xFFFFFFFFUL
/* ETH.BROADCAST_TXED */
#define ETH_BROADCAST_TXED_COUNT_BROADCAST_Pos  0UL
#define ETH_BROADCAST_TXED_COUNT_BROADCAST_Msk  0xFFFFFFFFUL
/* ETH.MULTICAST_TXED */
#define ETH_MULTICAST_TXED_COUNT_MULTICAST_Pos  0UL
#define ETH_MULTICAST_TXED_COUNT_MULTICAST_Msk  0xFFFFFFFFUL
/* ETH.PAUSE_FRAMES_TXED */
#define ETH_PAUSE_FRAMES_TXED_COUNT_PAUSE_Pos   0UL
#define ETH_PAUSE_FRAMES_TXED_COUNT_PAUSE_Msk   0xFFFFUL
/* ETH.FRAMES_TXED_64 */
#define ETH_FRAMES_TXED_64_COUNT_64_Pos         0UL
#define ETH_FRAMES_TXED_64_COUNT_64_Msk         0xFFFFFFFFUL
/* ETH.FRAMES_TXED_65 */
#define ETH_FRAMES_TXED_65_COUNT_65_Pos         0UL
#define ETH_FRAMES_TXED_65_COUNT_65_Msk         0xFFFFFFFFUL
/* ETH.FRAMES_TXED_128 */
#define ETH_FRAMES_TXED_128_COUNT_128_Pos       0UL
#define ETH_FRAMES_TXED_128_COUNT_128_Msk       0xFFFFFFFFUL
/* ETH.FRAMES_TXED_256 */
#define ETH_FRAMES_TXED_256_COUNT_256_Pos       0UL
#define ETH_FRAMES_TXED_256_COUNT_256_Msk       0xFFFFFFFFUL
/* ETH.FRAMES_TXED_512 */
#define ETH_FRAMES_TXED_512_COUNT_512_Pos       0UL
#define ETH_FRAMES_TXED_512_COUNT_512_Msk       0xFFFFFFFFUL
/* ETH.FRAMES_TXED_1024 */
#define ETH_FRAMES_TXED_1024_COUNT_1024_Pos     0UL
#define ETH_FRAMES_TXED_1024_COUNT_1024_Msk     0xFFFFFFFFUL
/* ETH.FRAMES_TXED_1519 */
#define ETH_FRAMES_TXED_1519_COUNT_1519_Pos     0UL
#define ETH_FRAMES_TXED_1519_COUNT_1519_Msk     0xFFFFFFFFUL
/* ETH.TX_UNDERRUNS */
#define ETH_TX_UNDERRUNS_COUNT_UN_Pos           0UL
#define ETH_TX_UNDERRUNS_COUNT_UN_Msk           0x3FFUL
/* ETH.SINGLE_COLLISIONS */
#define ETH_SINGLE_COLLISIONS_COUNT14_Pos       0UL
#define ETH_SINGLE_COLLISIONS_COUNT14_Msk       0x3FFFFUL
/* ETH.MULTIPLE_COLLISIONS */
#define ETH_MULTIPLE_COLLISIONS_COUNT15_Pos     0UL
#define ETH_MULTIPLE_COLLISIONS_COUNT15_Msk     0x3FFFFUL
/* ETH.EXCESSIVE_COLLISIONS */
#define ETH_EXCESSIVE_COLLISIONS_COUNT16_Pos    0UL
#define ETH_EXCESSIVE_COLLISIONS_COUNT16_Msk    0x3FFUL
/* ETH.LATE_COLLISIONS */
#define ETH_LATE_COLLISIONS_COUNT17_Pos         0UL
#define ETH_LATE_COLLISIONS_COUNT17_Msk         0x3FFUL
/* ETH.DEFERRED_FRAMES */
#define ETH_DEFERRED_FRAMES_COUNT18_Pos         0UL
#define ETH_DEFERRED_FRAMES_COUNT18_Msk         0x3FFFFUL
/* ETH.CRS_ERRORS */
#define ETH_CRS_ERRORS_COUNT19_Pos              0UL
#define ETH_CRS_ERRORS_COUNT19_Msk              0x3FFUL
/* ETH.OCTETS_RXED_BOTTOM */
#define ETH_OCTETS_RXED_BOTTOM_COUNT_BOTTOM_Pos 0UL
#define ETH_OCTETS_RXED_BOTTOM_COUNT_BOTTOM_Msk 0xFFFFFFFFUL
/* ETH.OCTETS_RXED_TOP */
#define ETH_OCTETS_RXED_TOP_COUNT_TOP_Pos       0UL
#define ETH_OCTETS_RXED_TOP_COUNT_TOP_Msk       0xFFFFUL
/* ETH.FRAMES_RXED_OK */
#define ETH_FRAMES_RXED_OK_COUNT_OK_Pos         0UL
#define ETH_FRAMES_RXED_OK_COUNT_OK_Msk         0xFFFFFFFFUL
/* ETH.BROADCAST_RXED */
#define ETH_BROADCAST_RXED_COUNT_BROADCAST_Pos  0UL
#define ETH_BROADCAST_RXED_COUNT_BROADCAST_Msk  0xFFFFFFFFUL
/* ETH.MULTICAST_RXED */
#define ETH_MULTICAST_RXED_COUNT_MULTICAST_Pos  0UL
#define ETH_MULTICAST_RXED_COUNT_MULTICAST_Msk  0xFFFFFFFFUL
/* ETH.PAUSE_FRAMES_RXED */
#define ETH_PAUSE_FRAMES_RXED_COUNT_PAUSE_Pos   0UL
#define ETH_PAUSE_FRAMES_RXED_COUNT_PAUSE_Msk   0xFFFFUL
/* ETH.FRAMES_RXED_64 */
#define ETH_FRAMES_RXED_64_COUNT_64_Pos         0UL
#define ETH_FRAMES_RXED_64_COUNT_64_Msk         0xFFFFFFFFUL
/* ETH.FRAMES_RXED_65 */
#define ETH_FRAMES_RXED_65_COUNT_65_Pos         0UL
#define ETH_FRAMES_RXED_65_COUNT_65_Msk         0xFFFFFFFFUL
/* ETH.FRAMES_RXED_128 */
#define ETH_FRAMES_RXED_128_COUNT_128_Pos       0UL
#define ETH_FRAMES_RXED_128_COUNT_128_Msk       0xFFFFFFFFUL
/* ETH.FRAMES_RXED_256 */
#define ETH_FRAMES_RXED_256_COUNT_256_Pos       0UL
#define ETH_FRAMES_RXED_256_COUNT_256_Msk       0xFFFFFFFFUL
/* ETH.FRAMES_RXED_512 */
#define ETH_FRAMES_RXED_512_COUNT_512_Pos       0UL
#define ETH_FRAMES_RXED_512_COUNT_512_Msk       0xFFFFFFFFUL
/* ETH.FRAMES_RXED_1024 */
#define ETH_FRAMES_RXED_1024_COUNT_1024_Pos     0UL
#define ETH_FRAMES_RXED_1024_COUNT_1024_Msk     0xFFFFFFFFUL
/* ETH.FRAMES_RXED_1519 */
#define ETH_FRAMES_RXED_1519_COUNT_1519_Pos     0UL
#define ETH_FRAMES_RXED_1519_COUNT_1519_Msk     0xFFFFFFFFUL
/* ETH.UNDERSIZE_FRAMES */
#define ETH_UNDERSIZE_FRAMES_COUNT_UNDERSIZE_Pos 0UL
#define ETH_UNDERSIZE_FRAMES_COUNT_UNDERSIZE_Msk 0x3FFUL
/* ETH.EXCESSIVE_RX_LENGTH */
#define ETH_EXCESSIVE_RX_LENGTH_COUNT_OVERSIZE_Pos 0UL
#define ETH_EXCESSIVE_RX_LENGTH_COUNT_OVERSIZE_Msk 0x3FFUL
/* ETH.RX_JABBERS */
#define ETH_RX_JABBERS_COUNT_JABBERS_Pos        0UL
#define ETH_RX_JABBERS_COUNT_JABBERS_Msk        0x3FFUL
/* ETH.FCS_ERRORS */
#define ETH_FCS_ERRORS_COUNT_FCS_ERR_Pos        0UL
#define ETH_FCS_ERRORS_COUNT_FCS_ERR_Msk        0x3FFUL
/* ETH.RX_LENGTH_ERRORS */
#define ETH_RX_LENGTH_ERRORS_COUNT_LENGTH_ERR_Pos 0UL
#define ETH_RX_LENGTH_ERRORS_COUNT_LENGTH_ERR_Msk 0x3FFUL
/* ETH.RX_SYMBOL_ERRORS */
#define ETH_RX_SYMBOL_ERRORS_COUNT_SYMBOL_ERR_Pos 0UL
#define ETH_RX_SYMBOL_ERRORS_COUNT_SYMBOL_ERR_Msk 0x3FFUL
/* ETH.ALIGNMENT_ERRORS */
#define ETH_ALIGNMENT_ERRORS_COUNT_ALIGNMENT_ERROR_Pos 0UL
#define ETH_ALIGNMENT_ERRORS_COUNT_ALIGNMENT_ERROR_Msk 0x3FFUL
/* ETH.RX_RESOURCE_ERRORS */
#define ETH_RX_RESOURCE_ERRORS_COUNT_RESOURCE_ERR_Pos 0UL
#define ETH_RX_RESOURCE_ERRORS_COUNT_RESOURCE_ERR_Msk 0x3FFFFUL
/* ETH.RX_OVERRUNS */
#define ETH_RX_OVERRUNS_COUNT_OVERRUN_Pos       0UL
#define ETH_RX_OVERRUNS_COUNT_OVERRUN_Msk       0x3FFUL
/* ETH.RX_IP_CK_ERRORS */
#define ETH_RX_IP_CK_ERRORS_COUNT_IPCK_ERR_Pos  0UL
#define ETH_RX_IP_CK_ERRORS_COUNT_IPCK_ERR_Msk  0xFFUL
/* ETH.RX_TCP_CK_ERRORS */
#define ETH_RX_TCP_CK_ERRORS_COUNT_TCPCK_ERR_Pos 0UL
#define ETH_RX_TCP_CK_ERRORS_COUNT_TCPCK_ERR_Msk 0xFFUL
/* ETH.RX_UDP_CK_ERRORS */
#define ETH_RX_UDP_CK_ERRORS_COUNT_UDPCK_ERR_Pos 0UL
#define ETH_RX_UDP_CK_ERRORS_COUNT_UDPCK_ERR_Msk 0xFFUL
/* ETH.AUTO_FLUSHED_PKTS */
#define ETH_AUTO_FLUSHED_PKTS_COUNT_FLUSHED_Pos 0UL
#define ETH_AUTO_FLUSHED_PKTS_COUNT_FLUSHED_Msk 0xFFFFUL
/* ETH.TSU_TIMER_INCR_SUB_NSEC */
#define ETH_TSU_TIMER_INCR_SUB_NSEC_SUB_NS_INCR_Pos 0UL
#define ETH_TSU_TIMER_INCR_SUB_NSEC_SUB_NS_INCR_Msk 0xFFFFUL
#define ETH_TSU_TIMER_INCR_SUB_NSEC_SUB_NS_INCR_LSB_Pos 24UL
#define ETH_TSU_TIMER_INCR_SUB_NSEC_SUB_NS_INCR_LSB_Msk 0xFF000000UL
/* ETH.TSU_TIMER_MSB_SEC */
#define ETH_TSU_TIMER_MSB_SEC_TIMER_MSB_SEC_Pos 0UL
#define ETH_TSU_TIMER_MSB_SEC_TIMER_MSB_SEC_Msk 0xFFFFUL
/* ETH.TSU_STROBE_MSB_SEC */
#define ETH_TSU_STROBE_MSB_SEC_STROBE_MSB_SEC_Pos 0UL
#define ETH_TSU_STROBE_MSB_SEC_STROBE_MSB_SEC_Msk 0xFFFFUL
/* ETH.TSU_STROBE_SEC */
#define ETH_TSU_STROBE_SEC_STROBE_SEC_Pos       0UL
#define ETH_TSU_STROBE_SEC_STROBE_SEC_Msk       0xFFFFFFFFUL
/* ETH.TSU_STROBE_NSEC */
#define ETH_TSU_STROBE_NSEC_STROBE_NSEC_Pos     0UL
#define ETH_TSU_STROBE_NSEC_STROBE_NSEC_Msk     0x3FFFFFFFUL
/* ETH.TSU_TIMER_SEC */
#define ETH_TSU_TIMER_SEC_TIMER_SEC_Pos         0UL
#define ETH_TSU_TIMER_SEC_TIMER_SEC_Msk         0xFFFFFFFFUL
/* ETH.TSU_TIMER_NSEC */
#define ETH_TSU_TIMER_NSEC_TIMER_NSEC_Pos       0UL
#define ETH_TSU_TIMER_NSEC_TIMER_NSEC_Msk       0x3FFFFFFFUL
/* ETH.TSU_TIMER_ADJUST */
#define ETH_TSU_TIMER_ADJUST_INCREMENT_VALUE_Pos 0UL
#define ETH_TSU_TIMER_ADJUST_INCREMENT_VALUE_Msk 0x3FFFFFFFUL
#define ETH_TSU_TIMER_ADJUST_ADD_SUBTRACT_Pos   31UL
#define ETH_TSU_TIMER_ADJUST_ADD_SUBTRACT_Msk   0x80000000UL
/* ETH.TSU_TIMER_INCR */
#define ETH_TSU_TIMER_INCR_NS_INCREMENT_Pos     0UL
#define ETH_TSU_TIMER_INCR_NS_INCREMENT_Msk     0xFFUL
#define ETH_TSU_TIMER_INCR_ALT_NS_INCR_Pos      8UL
#define ETH_TSU_TIMER_INCR_ALT_NS_INCR_Msk      0xFF00UL
#define ETH_TSU_TIMER_INCR_NUM_INCS_Pos         16UL
#define ETH_TSU_TIMER_INCR_NUM_INCS_Msk         0xFF0000UL
/* ETH.TSU_PTP_TX_SEC */
#define ETH_TSU_PTP_TX_SEC_TIMER_PTP_SEC_Pos    0UL
#define ETH_TSU_PTP_TX_SEC_TIMER_PTP_SEC_Msk    0xFFFFFFFFUL
/* ETH.TSU_PTP_TX_NSEC */
#define ETH_TSU_PTP_TX_NSEC_TIMER_PTP_NSEC_Pos  0UL
#define ETH_TSU_PTP_TX_NSEC_TIMER_PTP_NSEC_Msk  0x3FFFFFFFUL
/* ETH.TSU_PTP_RX_SEC */
#define ETH_TSU_PTP_RX_SEC_TIMER_PTP_SEC_Pos    0UL
#define ETH_TSU_PTP_RX_SEC_TIMER_PTP_SEC_Msk    0xFFFFFFFFUL
/* ETH.TSU_PTP_RX_NSEC */
#define ETH_TSU_PTP_RX_NSEC_TIMER_PTP_NSEC_Pos  0UL
#define ETH_TSU_PTP_RX_NSEC_TIMER_PTP_NSEC_Msk  0x3FFFFFFFUL
/* ETH.TSU_PEER_TX_SEC */
#define ETH_TSU_PEER_TX_SEC_TIMER_PEER_SEC_Pos  0UL
#define ETH_TSU_PEER_TX_SEC_TIMER_PEER_SEC_Msk  0xFFFFFFFFUL
/* ETH.TSU_PEER_TX_NSEC */
#define ETH_TSU_PEER_TX_NSEC_TIMER_PEER_NSEC_Pos 0UL
#define ETH_TSU_PEER_TX_NSEC_TIMER_PEER_NSEC_Msk 0x3FFFFFFFUL
/* ETH.TSU_PEER_RX_SEC */
#define ETH_TSU_PEER_RX_SEC_TIMER_PEER_SEC_Pos  0UL
#define ETH_TSU_PEER_RX_SEC_TIMER_PEER_SEC_Msk  0xFFFFFFFFUL
/* ETH.TSU_PEER_RX_NSEC */
#define ETH_TSU_PEER_RX_NSEC_TIMER_PEER_NSEC_Pos 0UL
#define ETH_TSU_PEER_RX_NSEC_TIMER_PEER_NSEC_Msk 0x3FFFFFFFUL
/* ETH.PCS_CONTROL */
#define ETH_PCS_CONTROL_REMOVED_31_0_Pos        0UL
#define ETH_PCS_CONTROL_REMOVED_31_0_Msk        0xFFFFFFFFUL
/* ETH.PCS_STATUS */
#define ETH_PCS_STATUS_REMOVED_31_0_Pos         0UL
#define ETH_PCS_STATUS_REMOVED_31_0_Msk         0xFFFFFFFFUL
/* ETH.PCS_AN_ADV */
#define ETH_PCS_AN_ADV_REMOVED_31_0_Pos         0UL
#define ETH_PCS_AN_ADV_REMOVED_31_0_Msk         0xFFFFFFFFUL
/* ETH.PCS_AN_LP_BASE */
#define ETH_PCS_AN_LP_BASE_REMOVED_31_0_Pos     0UL
#define ETH_PCS_AN_LP_BASE_REMOVED_31_0_Msk     0xFFFFFFFFUL
/* ETH.PCS_AN_EXP */
#define ETH_PCS_AN_EXP_REMOVED_31_0_Pos         0UL
#define ETH_PCS_AN_EXP_REMOVED_31_0_Msk         0xFFFFFFFFUL
/* ETH.PCS_AN_NP_TX */
#define ETH_PCS_AN_NP_TX_REMOVED_31_0_Pos       0UL
#define ETH_PCS_AN_NP_TX_REMOVED_31_0_Msk       0xFFFFFFFFUL
/* ETH.PCS_AN_LP_NP */
#define ETH_PCS_AN_LP_NP_REMOVED_31_0_Pos       0UL
#define ETH_PCS_AN_LP_NP_REMOVED_31_0_Msk       0xFFFFFFFFUL
/* ETH.PCS_AN_EXT_STATUS */
#define ETH_PCS_AN_EXT_STATUS_REMOVED_31_0_Pos  0UL
#define ETH_PCS_AN_EXT_STATUS_REMOVED_31_0_Msk  0xFFFFFFFFUL
/* ETH.TX_PAUSE_QUANTUM1 */
#define ETH_TX_PAUSE_QUANTUM1_QUANTUM_P2_Pos    0UL
#define ETH_TX_PAUSE_QUANTUM1_QUANTUM_P2_Msk    0xFFFFUL
#define ETH_TX_PAUSE_QUANTUM1_QUANTUM_P3_Pos    16UL
#define ETH_TX_PAUSE_QUANTUM1_QUANTUM_P3_Msk    0xFFFF0000UL
/* ETH.TX_PAUSE_QUANTUM2 */
#define ETH_TX_PAUSE_QUANTUM2_QUANTUM_P4_Pos    0UL
#define ETH_TX_PAUSE_QUANTUM2_QUANTUM_P4_Msk    0xFFFFUL
#define ETH_TX_PAUSE_QUANTUM2_QUANTUM_P5_Pos    16UL
#define ETH_TX_PAUSE_QUANTUM2_QUANTUM_P5_Msk    0xFFFF0000UL
/* ETH.TX_PAUSE_QUANTUM3 */
#define ETH_TX_PAUSE_QUANTUM3_QUANTUM_P6_Pos    0UL
#define ETH_TX_PAUSE_QUANTUM3_QUANTUM_P6_Msk    0xFFFFUL
#define ETH_TX_PAUSE_QUANTUM3_QUANTUM_P7_Pos    16UL
#define ETH_TX_PAUSE_QUANTUM3_QUANTUM_P7_Msk    0xFFFF0000UL
/* ETH.RX_LPI */
#define ETH_RX_LPI_COUNT_LPI_Pos                0UL
#define ETH_RX_LPI_COUNT_LPI_Msk                0xFFFFUL
/* ETH.RX_LPI_TIME */
#define ETH_RX_LPI_TIME_LPI_TIME_Pos            0UL
#define ETH_RX_LPI_TIME_LPI_TIME_Msk            0xFFFFFFUL
/* ETH.TX_LPI */
#define ETH_TX_LPI_COUNT_LPI_Pos                0UL
#define ETH_TX_LPI_COUNT_LPI_Msk                0xFFFFUL
/* ETH.TX_LPI_TIME */
#define ETH_TX_LPI_TIME_LPI_TIME_Pos            0UL
#define ETH_TX_LPI_TIME_LPI_TIME_Msk            0xFFFFFFUL
/* ETH.DESIGNCFG_DEBUG1 */
#define ETH_DESIGNCFG_DEBUG1_NO_PCS_Pos         0UL
#define ETH_DESIGNCFG_DEBUG1_NO_PCS_Msk         0x1UL
#define ETH_DESIGNCFG_DEBUG1_EXCLUDE_QBV_Pos    1UL
#define ETH_DESIGNCFG_DEBUG1_EXCLUDE_QBV_Msk    0x2UL
#define ETH_DESIGNCFG_DEBUG1_RESERVED_2_Pos     2UL
#define ETH_DESIGNCFG_DEBUG1_RESERVED_2_Msk     0xCUL
#define ETH_DESIGNCFG_DEBUG1_INT_LOOPBACK_Pos   4UL
#define ETH_DESIGNCFG_DEBUG1_INT_LOOPBACK_Msk   0x10UL
#define ETH_DESIGNCFG_DEBUG1_RESERVED_5_Pos     5UL
#define ETH_DESIGNCFG_DEBUG1_RESERVED_5_Msk     0x20UL
#define ETH_DESIGNCFG_DEBUG1_EXT_FIFO_INTERFACE_Pos 6UL
#define ETH_DESIGNCFG_DEBUG1_EXT_FIFO_INTERFACE_Msk 0x40UL
#define ETH_DESIGNCFG_DEBUG1_RESERVED_7_Pos     7UL
#define ETH_DESIGNCFG_DEBUG1_RESERVED_7_Msk     0x80UL
#define ETH_DESIGNCFG_DEBUG1_RESERVED_8_Pos     8UL
#define ETH_DESIGNCFG_DEBUG1_RESERVED_8_Msk     0x100UL
#define ETH_DESIGNCFG_DEBUG1_USER_IO_Pos        9UL
#define ETH_DESIGNCFG_DEBUG1_USER_IO_Msk        0x200UL
#define ETH_DESIGNCFG_DEBUG1_USER_OUT_WIDTH_Pos 10UL
#define ETH_DESIGNCFG_DEBUG1_USER_OUT_WIDTH_Msk 0x7C00UL
#define ETH_DESIGNCFG_DEBUG1_USER_IN_WIDTH_Pos  15UL
#define ETH_DESIGNCFG_DEBUG1_USER_IN_WIDTH_Msk  0xF8000UL
#define ETH_DESIGNCFG_DEBUG1_RESERVED_20_Pos    20UL
#define ETH_DESIGNCFG_DEBUG1_RESERVED_20_Msk    0x100000UL
#define ETH_DESIGNCFG_DEBUG1_NO_STATS_Pos       21UL
#define ETH_DESIGNCFG_DEBUG1_NO_STATS_Msk       0x200000UL
#define ETH_DESIGNCFG_DEBUG1_NO_SNAPSHOT_Pos    22UL
#define ETH_DESIGNCFG_DEBUG1_NO_SNAPSHOT_Msk    0x400000UL
#define ETH_DESIGNCFG_DEBUG1_IRQ_READ_CLEAR_Pos 23UL
#define ETH_DESIGNCFG_DEBUG1_IRQ_READ_CLEAR_Msk 0x800000UL
#define ETH_DESIGNCFG_DEBUG1_EXCLUDE_CBS_Pos    24UL
#define ETH_DESIGNCFG_DEBUG1_EXCLUDE_CBS_Msk    0x1000000UL
#define ETH_DESIGNCFG_DEBUG1_DMA_BUS_WIDTH_Pos  25UL
#define ETH_DESIGNCFG_DEBUG1_DMA_BUS_WIDTH_Msk  0xE000000UL
#define ETH_DESIGNCFG_DEBUG1_AXI_CACHE_VALUE_Pos 28UL
#define ETH_DESIGNCFG_DEBUG1_AXI_CACHE_VALUE_Msk 0xF0000000UL
/* ETH.DESIGNCFG_DEBUG2 */
#define ETH_DESIGNCFG_DEBUG2_JUMBO_MAX_LENGTH_Pos 0UL
#define ETH_DESIGNCFG_DEBUG2_JUMBO_MAX_LENGTH_Msk 0x3FFFUL
#define ETH_DESIGNCFG_DEBUG2_HPROT_VALUE_Pos    16UL
#define ETH_DESIGNCFG_DEBUG2_HPROT_VALUE_Msk    0xF0000UL
#define ETH_DESIGNCFG_DEBUG2_RX_PKT_BUFFER_Pos  20UL
#define ETH_DESIGNCFG_DEBUG2_RX_PKT_BUFFER_Msk  0x100000UL
#define ETH_DESIGNCFG_DEBUG2_TX_PKT_BUFFER_Pos  21UL
#define ETH_DESIGNCFG_DEBUG2_TX_PKT_BUFFER_Msk  0x200000UL
#define ETH_DESIGNCFG_DEBUG2_RX_PBUF_ADDR_Pos   22UL
#define ETH_DESIGNCFG_DEBUG2_RX_PBUF_ADDR_Msk   0x3C00000UL
#define ETH_DESIGNCFG_DEBUG2_TX_PBUF_ADDR_Pos   26UL
#define ETH_DESIGNCFG_DEBUG2_TX_PBUF_ADDR_Msk   0x3C000000UL
#define ETH_DESIGNCFG_DEBUG2_AXI_Pos            30UL
#define ETH_DESIGNCFG_DEBUG2_AXI_Msk            0x40000000UL
#define ETH_DESIGNCFG_DEBUG2_SPRAM_Pos          31UL
#define ETH_DESIGNCFG_DEBUG2_SPRAM_Msk          0x80000000UL
/* ETH.DESIGNCFG_DEBUG3 */
#define ETH_DESIGNCFG_DEBUG3_NUM_SPEC_ADD_FILTERS_Pos 24UL
#define ETH_DESIGNCFG_DEBUG3_NUM_SPEC_ADD_FILTERS_Msk 0x3F000000UL
/* ETH.DESIGNCFG_DEBUG4 */
#define ETH_DESIGNCFG_DEBUG4_RESERVED_31_0_Pos  0UL
#define ETH_DESIGNCFG_DEBUG4_RESERVED_31_0_Msk  0xFFFFFFFFUL
/* ETH.DESIGNCFG_DEBUG5 */
#define ETH_DESIGNCFG_DEBUG5_RX_FIFO_CNT_WIDTH_Pos 0UL
#define ETH_DESIGNCFG_DEBUG5_RX_FIFO_CNT_WIDTH_Msk 0xFUL
#define ETH_DESIGNCFG_DEBUG5_TX_FIFO_CNT_WIDTH_Pos 4UL
#define ETH_DESIGNCFG_DEBUG5_TX_FIFO_CNT_WIDTH_Msk 0xF0UL
#define ETH_DESIGNCFG_DEBUG5_TSU_Pos            8UL
#define ETH_DESIGNCFG_DEBUG5_TSU_Msk            0x100UL
#define ETH_DESIGNCFG_DEBUG5_PHY_IDENT_Pos      9UL
#define ETH_DESIGNCFG_DEBUG5_PHY_IDENT_Msk      0x200UL
#define ETH_DESIGNCFG_DEBUG5_DMA_BUS_WIDTH_DEF_Pos 10UL
#define ETH_DESIGNCFG_DEBUG5_DMA_BUS_WIDTH_DEF_Msk 0xC00UL
#define ETH_DESIGNCFG_DEBUG5_MDC_CLOCK_DIV_Pos  12UL
#define ETH_DESIGNCFG_DEBUG5_MDC_CLOCK_DIV_Msk  0x7000UL
#define ETH_DESIGNCFG_DEBUG5_ENDIAN_SWAP_DEF_Pos 15UL
#define ETH_DESIGNCFG_DEBUG5_ENDIAN_SWAP_DEF_Msk 0x18000UL
#define ETH_DESIGNCFG_DEBUG5_RX_PBUF_SIZE_DEF_Pos 17UL
#define ETH_DESIGNCFG_DEBUG5_RX_PBUF_SIZE_DEF_Msk 0x60000UL
#define ETH_DESIGNCFG_DEBUG5_TX_PBUF_SIZE_DEF_Pos 19UL
#define ETH_DESIGNCFG_DEBUG5_TX_PBUF_SIZE_DEF_Msk 0x80000UL
#define ETH_DESIGNCFG_DEBUG5_RX_BUFFER_LENGTH_DEF_Pos 20UL
#define ETH_DESIGNCFG_DEBUG5_RX_BUFFER_LENGTH_DEF_Msk 0xFF00000UL
#define ETH_DESIGNCFG_DEBUG5_TSU_CLK_Pos        28UL
#define ETH_DESIGNCFG_DEBUG5_TSU_CLK_Msk        0x10000000UL
#define ETH_DESIGNCFG_DEBUG5_AXI_PROT_VALUE_Pos 29UL
#define ETH_DESIGNCFG_DEBUG5_AXI_PROT_VALUE_Msk 0xE0000000UL
/* ETH.DESIGNCFG_DEBUG6 */
#define ETH_DESIGNCFG_DEBUG6_DMA_PRIORITY_QUEUE1_Pos 1UL
#define ETH_DESIGNCFG_DEBUG6_DMA_PRIORITY_QUEUE1_Msk 0x2UL
#define ETH_DESIGNCFG_DEBUG6_DMA_PRIORITY_QUEUE2_Pos 2UL
#define ETH_DESIGNCFG_DEBUG6_DMA_PRIORITY_QUEUE2_Msk 0x4UL
#define ETH_DESIGNCFG_DEBUG6_DMA_PRIORITY_QUEUE3_Pos 3UL
#define ETH_DESIGNCFG_DEBUG6_DMA_PRIORITY_QUEUE3_Msk 0x8UL
#define ETH_DESIGNCFG_DEBUG6_DMA_PRIORITY_QUEUE4_Pos 4UL
#define ETH_DESIGNCFG_DEBUG6_DMA_PRIORITY_QUEUE4_Msk 0x10UL
#define ETH_DESIGNCFG_DEBUG6_DMA_PRIORITY_QUEUE5_Pos 5UL
#define ETH_DESIGNCFG_DEBUG6_DMA_PRIORITY_QUEUE5_Msk 0x20UL
#define ETH_DESIGNCFG_DEBUG6_DMA_PRIORITY_QUEUE6_Pos 6UL
#define ETH_DESIGNCFG_DEBUG6_DMA_PRIORITY_QUEUE6_Msk 0x40UL
#define ETH_DESIGNCFG_DEBUG6_DMA_PRIORITY_QUEUE7_Pos 7UL
#define ETH_DESIGNCFG_DEBUG6_DMA_PRIORITY_QUEUE7_Msk 0x80UL
#define ETH_DESIGNCFG_DEBUG6_DMA_PRIORITY_QUEUE8_Pos 8UL
#define ETH_DESIGNCFG_DEBUG6_DMA_PRIORITY_QUEUE8_Msk 0x100UL
#define ETH_DESIGNCFG_DEBUG6_DMA_PRIORITY_QUEUE9_Pos 9UL
#define ETH_DESIGNCFG_DEBUG6_DMA_PRIORITY_QUEUE9_Msk 0x200UL
#define ETH_DESIGNCFG_DEBUG6_DMA_PRIORITY_QUEUE10_Pos 10UL
#define ETH_DESIGNCFG_DEBUG6_DMA_PRIORITY_QUEUE10_Msk 0x400UL
#define ETH_DESIGNCFG_DEBUG6_DMA_PRIORITY_QUEUE11_Pos 11UL
#define ETH_DESIGNCFG_DEBUG6_DMA_PRIORITY_QUEUE11_Msk 0x800UL
#define ETH_DESIGNCFG_DEBUG6_DMA_PRIORITY_QUEUE12_Pos 12UL
#define ETH_DESIGNCFG_DEBUG6_DMA_PRIORITY_QUEUE12_Msk 0x1000UL
#define ETH_DESIGNCFG_DEBUG6_DMA_PRIORITY_QUEUE13_Pos 13UL
#define ETH_DESIGNCFG_DEBUG6_DMA_PRIORITY_QUEUE13_Msk 0x2000UL
#define ETH_DESIGNCFG_DEBUG6_DMA_PRIORITY_QUEUE14_Pos 14UL
#define ETH_DESIGNCFG_DEBUG6_DMA_PRIORITY_QUEUE14_Msk 0x4000UL
#define ETH_DESIGNCFG_DEBUG6_DMA_PRIORITY_QUEUE15_Pos 15UL
#define ETH_DESIGNCFG_DEBUG6_DMA_PRIORITY_QUEUE15_Msk 0x8000UL
#define ETH_DESIGNCFG_DEBUG6_TX_PBUF_QUEUE_SEGMENT_SIZE_Pos 16UL
#define ETH_DESIGNCFG_DEBUG6_TX_PBUF_QUEUE_SEGMENT_SIZE_Msk 0xF0000UL
#define ETH_DESIGNCFG_DEBUG6_EXT_TSU_TIMER_Pos  20UL
#define ETH_DESIGNCFG_DEBUG6_EXT_TSU_TIMER_Msk  0x100000UL
#define ETH_DESIGNCFG_DEBUG6_TX_ADD_FIFO_IF_Pos 21UL
#define ETH_DESIGNCFG_DEBUG6_TX_ADD_FIFO_IF_Msk 0x200000UL
#define ETH_DESIGNCFG_DEBUG6_HOST_IF_SOFT_SELECT_Pos 22UL
#define ETH_DESIGNCFG_DEBUG6_HOST_IF_SOFT_SELECT_Msk 0x400000UL
#define ETH_DESIGNCFG_DEBUG6_DMA_ADDR_WIDTH_IS_64B_Pos 23UL
#define ETH_DESIGNCFG_DEBUG6_DMA_ADDR_WIDTH_IS_64B_Msk 0x800000UL
#define ETH_DESIGNCFG_DEBUG6_PFC_MULTI_QUANTUM_Pos 24UL
#define ETH_DESIGNCFG_DEBUG6_PFC_MULTI_QUANTUM_Msk 0x1000000UL
#define ETH_DESIGNCFG_DEBUG6_PBUF_CUTTHRU_Pos   25UL
#define ETH_DESIGNCFG_DEBUG6_PBUF_CUTTHRU_Msk   0x2000000UL
#define ETH_DESIGNCFG_DEBUG6_PBUF_RSC_Pos       26UL
#define ETH_DESIGNCFG_DEBUG6_PBUF_RSC_Msk       0x4000000UL
#define ETH_DESIGNCFG_DEBUG6_PBUF_LSO_Pos       27UL
#define ETH_DESIGNCFG_DEBUG6_PBUF_LSO_Msk       0x8000000UL
/* ETH.DESIGNCFG_DEBUG7 */
#define ETH_DESIGNCFG_DEBUG7_X_PBUF_NUM_SEGMENTS_Q0_Pos 0UL
#define ETH_DESIGNCFG_DEBUG7_X_PBUF_NUM_SEGMENTS_Q0_Msk 0xFUL
#define ETH_DESIGNCFG_DEBUG7_X_PBUF_NUM_SEGMENTS_Q1_Pos 4UL
#define ETH_DESIGNCFG_DEBUG7_X_PBUF_NUM_SEGMENTS_Q1_Msk 0xF0UL
#define ETH_DESIGNCFG_DEBUG7_X_PBUF_NUM_SEGMENTS_Q2_Pos 8UL
#define ETH_DESIGNCFG_DEBUG7_X_PBUF_NUM_SEGMENTS_Q2_Msk 0xF00UL
#define ETH_DESIGNCFG_DEBUG7_X_PBUF_NUM_SEGMENTS_Q3_Pos 12UL
#define ETH_DESIGNCFG_DEBUG7_X_PBUF_NUM_SEGMENTS_Q3_Msk 0xF000UL
#define ETH_DESIGNCFG_DEBUG7_X_PBUF_NUM_SEGMENTS_Q4_Pos 16UL
#define ETH_DESIGNCFG_DEBUG7_X_PBUF_NUM_SEGMENTS_Q4_Msk 0xF0000UL
#define ETH_DESIGNCFG_DEBUG7_X_PBUF_NUM_SEGMENTS_Q5_Pos 20UL
#define ETH_DESIGNCFG_DEBUG7_X_PBUF_NUM_SEGMENTS_Q5_Msk 0xF00000UL
#define ETH_DESIGNCFG_DEBUG7_X_PBUF_NUM_SEGMENTS_Q6_Pos 24UL
#define ETH_DESIGNCFG_DEBUG7_X_PBUF_NUM_SEGMENTS_Q6_Msk 0xF000000UL
#define ETH_DESIGNCFG_DEBUG7_X_PBUF_NUM_SEGMENTS_Q7_Pos 28UL
#define ETH_DESIGNCFG_DEBUG7_X_PBUF_NUM_SEGMENTS_Q7_Msk 0xF0000000UL
/* ETH.DESIGNCFG_DEBUG8 */
#define ETH_DESIGNCFG_DEBUG8_NUM_SCR2_COMPARE_REGS_Pos 0UL
#define ETH_DESIGNCFG_DEBUG8_NUM_SCR2_COMPARE_REGS_Msk 0xFFUL
#define ETH_DESIGNCFG_DEBUG8_NUM_SCR2_ETHTYPE_REGS_Pos 8UL
#define ETH_DESIGNCFG_DEBUG8_NUM_SCR2_ETHTYPE_REGS_Msk 0xFF00UL
#define ETH_DESIGNCFG_DEBUG8_NUM_TYPE2_SCREENERS_Pos 16UL
#define ETH_DESIGNCFG_DEBUG8_NUM_TYPE2_SCREENERS_Msk 0xFF0000UL
#define ETH_DESIGNCFG_DEBUG8_NUM_TYPE1_SCREENERS_Pos 24UL
#define ETH_DESIGNCFG_DEBUG8_NUM_TYPE1_SCREENERS_Msk 0xFF000000UL
/* ETH.DESIGNCFG_DEBUG9 */
#define ETH_DESIGNCFG_DEBUG9_TX_PBUF_NUM_SEGMENTS_Q8_Pos 0UL
#define ETH_DESIGNCFG_DEBUG9_TX_PBUF_NUM_SEGMENTS_Q8_Msk 0xFUL
#define ETH_DESIGNCFG_DEBUG9_TX_PBUF_NUM_SEGMENTS_Q9_Pos 4UL
#define ETH_DESIGNCFG_DEBUG9_TX_PBUF_NUM_SEGMENTS_Q9_Msk 0xF0UL
#define ETH_DESIGNCFG_DEBUG9_TX_PBUF_NUM_SEGMENTS_Q10_Pos 8UL
#define ETH_DESIGNCFG_DEBUG9_TX_PBUF_NUM_SEGMENTS_Q10_Msk 0xF00UL
#define ETH_DESIGNCFG_DEBUG9_TX_PBUF_NUM_SEGMENTS_Q11_Pos 12UL
#define ETH_DESIGNCFG_DEBUG9_TX_PBUF_NUM_SEGMENTS_Q11_Msk 0xF000UL
#define ETH_DESIGNCFG_DEBUG9_TX_PBUF_NUM_SEGMENTS_Q12_Pos 16UL
#define ETH_DESIGNCFG_DEBUG9_TX_PBUF_NUM_SEGMENTS_Q12_Msk 0xF0000UL
#define ETH_DESIGNCFG_DEBUG9_TX_PBUF_NUM_SEGMENTS_Q13_Pos 20UL
#define ETH_DESIGNCFG_DEBUG9_TX_PBUF_NUM_SEGMENTS_Q13_Msk 0xF00000UL
#define ETH_DESIGNCFG_DEBUG9_TX_PBUF_NUM_SEGMENTS_Q14_Pos 24UL
#define ETH_DESIGNCFG_DEBUG9_TX_PBUF_NUM_SEGMENTS_Q14_Msk 0xF000000UL
#define ETH_DESIGNCFG_DEBUG9_TX_PBUF_NUM_SEGMENTS_Q15_Pos 28UL
#define ETH_DESIGNCFG_DEBUG9_TX_PBUF_NUM_SEGMENTS_Q15_Msk 0xF0000000UL
/* ETH.DESIGNCFG_DEBUG10 */
#define ETH_DESIGNCFG_DEBUG10_AXI_RX_DESCR_WR_BUFF_BITS_Pos 0UL
#define ETH_DESIGNCFG_DEBUG10_AXI_RX_DESCR_WR_BUFF_BITS_Msk 0xFUL
#define ETH_DESIGNCFG_DEBUG10_AXI_TX_DESCR_WR_BUFF_BITS_Pos 4UL
#define ETH_DESIGNCFG_DEBUG10_AXI_TX_DESCR_WR_BUFF_BITS_Msk 0xF0UL
#define ETH_DESIGNCFG_DEBUG10_AXI_RX_DESCR_RD_BUFF_BITS_Pos 8UL
#define ETH_DESIGNCFG_DEBUG10_AXI_RX_DESCR_RD_BUFF_BITS_Msk 0xF00UL
#define ETH_DESIGNCFG_DEBUG10_AXI_TX_DESCR_RD_BUFF_BITS_Pos 12UL
#define ETH_DESIGNCFG_DEBUG10_AXI_TX_DESCR_RD_BUFF_BITS_Msk 0xF000UL
#define ETH_DESIGNCFG_DEBUG10_AXI_ACCESS_PIPELINE_BITS_Pos 16UL
#define ETH_DESIGNCFG_DEBUG10_AXI_ACCESS_PIPELINE_BITS_Msk 0xF0000UL
#define ETH_DESIGNCFG_DEBUG10_RX_PBUF_DATA_Pos  20UL
#define ETH_DESIGNCFG_DEBUG10_RX_PBUF_DATA_Msk  0xF00000UL
#define ETH_DESIGNCFG_DEBUG10_TX_PBUF_DATA_Pos  24UL
#define ETH_DESIGNCFG_DEBUG10_TX_PBUF_DATA_Msk  0xF000000UL
#define ETH_DESIGNCFG_DEBUG10_EMAC_BUS_WIDTH_Pos 28UL
#define ETH_DESIGNCFG_DEBUG10_EMAC_BUS_WIDTH_Msk 0xF0000000UL
/* ETH.SPEC_ADD5_BOTTOM */
#define ETH_SPEC_ADD5_BOTTOM_RESERVED_31_0_Pos  0UL
#define ETH_SPEC_ADD5_BOTTOM_RESERVED_31_0_Msk  0xFFFFFFFFUL
/* ETH.SPEC_ADD5_TOP */
#define ETH_SPEC_ADD5_TOP_RESERVED_31_0_Pos     0UL
#define ETH_SPEC_ADD5_TOP_RESERVED_31_0_Msk     0xFFFFFFFFUL
/* ETH.SPEC_ADD36_BOTTOM */
#define ETH_SPEC_ADD36_BOTTOM_RESERVED_31_0_Pos 0UL
#define ETH_SPEC_ADD36_BOTTOM_RESERVED_31_0_Msk 0xFFFFFFFFUL
/* ETH.SPEC_ADD36_TOP */
#define ETH_SPEC_ADD36_TOP_RESERVED_31_0_Pos    0UL
#define ETH_SPEC_ADD36_TOP_RESERVED_31_0_Msk    0xFFFFFFFFUL
/* ETH.INT_Q1_STATUS */
#define ETH_INT_Q1_STATUS_RECEIVE_COMPLETE_Pos  1UL
#define ETH_INT_Q1_STATUS_RECEIVE_COMPLETE_Msk  0x2UL
#define ETH_INT_Q1_STATUS_RX_USED_BIT_READ_Pos  2UL
#define ETH_INT_Q1_STATUS_RX_USED_BIT_READ_Msk  0x4UL
#define ETH_INT_Q1_STATUS_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_Pos 5UL
#define ETH_INT_Q1_STATUS_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_Msk 0x20UL
#define ETH_INT_Q1_STATUS_AMBA_ERROR_Pos        6UL
#define ETH_INT_Q1_STATUS_AMBA_ERROR_Msk        0x40UL
#define ETH_INT_Q1_STATUS_TRANSMIT_COMPLETE_Pos 7UL
#define ETH_INT_Q1_STATUS_TRANSMIT_COMPLETE_Msk 0x80UL
#define ETH_INT_Q1_STATUS_RESP_NOT_OK_Pos       11UL
#define ETH_INT_Q1_STATUS_RESP_NOT_OK_Msk       0x800UL
/* ETH.INT_Q2_STATUS */
#define ETH_INT_Q2_STATUS_RECEIVE_COMPLETE_Pos  1UL
#define ETH_INT_Q2_STATUS_RECEIVE_COMPLETE_Msk  0x2UL
#define ETH_INT_Q2_STATUS_RX_USED_BIT_READ_Pos  2UL
#define ETH_INT_Q2_STATUS_RX_USED_BIT_READ_Msk  0x4UL
#define ETH_INT_Q2_STATUS_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_Pos 5UL
#define ETH_INT_Q2_STATUS_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_Msk 0x20UL
#define ETH_INT_Q2_STATUS_AMBA_ERROR_Pos        6UL
#define ETH_INT_Q2_STATUS_AMBA_ERROR_Msk        0x40UL
#define ETH_INT_Q2_STATUS_TRANSMIT_COMPLETE_Pos 7UL
#define ETH_INT_Q2_STATUS_TRANSMIT_COMPLETE_Msk 0x80UL
#define ETH_INT_Q2_STATUS_RESP_NOT_OK_Pos       11UL
#define ETH_INT_Q2_STATUS_RESP_NOT_OK_Msk       0x800UL
/* ETH.INT_Q3_STATUS */
#define ETH_INT_Q3_STATUS_REMOVED_31_0_Pos      0UL
#define ETH_INT_Q3_STATUS_REMOVED_31_0_Msk      0xFFFFFFFFUL
/* ETH.INT_Q15_STATUS */
#define ETH_INT_Q15_STATUS_REMOVED_31_0_Pos     0UL
#define ETH_INT_Q15_STATUS_REMOVED_31_0_Msk     0xFFFFFFFFUL
/* ETH.TRANSMIT_Q1_PTR */
#define ETH_TRANSMIT_Q1_PTR_DMA_TX_DIS_Q_Pos    0UL
#define ETH_TRANSMIT_Q1_PTR_DMA_TX_DIS_Q_Msk    0x1UL
#define ETH_TRANSMIT_Q1_PTR_DMA_TX_Q_PTR_Pos    2UL
#define ETH_TRANSMIT_Q1_PTR_DMA_TX_Q_PTR_Msk    0xFFFFFFFCUL
/* ETH.TRANSMIT_Q2_PTR */
#define ETH_TRANSMIT_Q2_PTR_DMA_TX_DIS_Q_Pos    0UL
#define ETH_TRANSMIT_Q2_PTR_DMA_TX_DIS_Q_Msk    0x1UL
#define ETH_TRANSMIT_Q2_PTR_DMA_TX_Q_PTR_Pos    2UL
#define ETH_TRANSMIT_Q2_PTR_DMA_TX_Q_PTR_Msk    0xFFFFFFFCUL
/* ETH.TRANSMIT_Q3_PTR */
#define ETH_TRANSMIT_Q3_PTR_REMOVED_31_0_Pos    0UL
#define ETH_TRANSMIT_Q3_PTR_REMOVED_31_0_Msk    0xFFFFFFFFUL
/* ETH.TRANSMIT_Q15_PTR */
#define ETH_TRANSMIT_Q15_PTR_REMOVED_31_0_Pos   0UL
#define ETH_TRANSMIT_Q15_PTR_REMOVED_31_0_Msk   0xFFFFFFFFUL
/* ETH.RECEIVE_Q1_PTR */
#define ETH_RECEIVE_Q1_PTR_DMA_RX_DIS_Q_Pos     0UL
#define ETH_RECEIVE_Q1_PTR_DMA_RX_DIS_Q_Msk     0x1UL
#define ETH_RECEIVE_Q1_PTR_DMA_RX_Q_PTR_Pos     2UL
#define ETH_RECEIVE_Q1_PTR_DMA_RX_Q_PTR_Msk     0xFFFFFFFCUL
/* ETH.RECEIVE_Q2_PTR */
#define ETH_RECEIVE_Q2_PTR_DMA_RX_DIS_Q_Pos     0UL
#define ETH_RECEIVE_Q2_PTR_DMA_RX_DIS_Q_Msk     0x1UL
#define ETH_RECEIVE_Q2_PTR_DMA_RX_Q_PTR_Pos     2UL
#define ETH_RECEIVE_Q2_PTR_DMA_RX_Q_PTR_Msk     0xFFFFFFFCUL
/* ETH.RECEIVE_Q3_PTR */
#define ETH_RECEIVE_Q3_PTR_REMOVED_31_0_Pos     0UL
#define ETH_RECEIVE_Q3_PTR_REMOVED_31_0_Msk     0xFFFFFFFFUL
/* ETH.RECEIVE_Q7_PTR */
#define ETH_RECEIVE_Q7_PTR_REMOVED_31_0_Pos     0UL
#define ETH_RECEIVE_Q7_PTR_REMOVED_31_0_Msk     0xFFFFFFFFUL
/* ETH.DMA_RXBUF_SIZE_Q1 */
#define ETH_DMA_RXBUF_SIZE_Q1_DMA_RX_Q_BUF_SIZE_Pos 0UL
#define ETH_DMA_RXBUF_SIZE_Q1_DMA_RX_Q_BUF_SIZE_Msk 0xFFUL
/* ETH.DMA_RXBUF_SIZE_Q2 */
#define ETH_DMA_RXBUF_SIZE_Q2_DMA_RX_Q_BUF_SIZE_Pos 0UL
#define ETH_DMA_RXBUF_SIZE_Q2_DMA_RX_Q_BUF_SIZE_Msk 0xFFUL
/* ETH.DMA_RXBUF_SIZE_Q3 */
#define ETH_DMA_RXBUF_SIZE_Q3_REMOVED_31_0_Pos  0UL
#define ETH_DMA_RXBUF_SIZE_Q3_REMOVED_31_0_Msk  0xFFFFFFFFUL
/* ETH.DMA_RXBUF_SIZE_Q7 */
#define ETH_DMA_RXBUF_SIZE_Q7_REMOVED_31_0_Pos  0UL
#define ETH_DMA_RXBUF_SIZE_Q7_REMOVED_31_0_Msk  0xFFFFFFFFUL
/* ETH.CBS_CONTROL */
#define ETH_CBS_CONTROL_CBS_ENABLE_QUEUE_A_Pos  0UL
#define ETH_CBS_CONTROL_CBS_ENABLE_QUEUE_A_Msk  0x1UL
#define ETH_CBS_CONTROL_CBS_ENABLE_QUEUE_B_Pos  1UL
#define ETH_CBS_CONTROL_CBS_ENABLE_QUEUE_B_Msk  0x2UL
/* ETH.CBS_IDLESLOPE_Q_A */
#define ETH_CBS_IDLESLOPE_Q_A_IDLESLOPE_A_Pos   0UL
#define ETH_CBS_IDLESLOPE_Q_A_IDLESLOPE_A_Msk   0xFFFFFFFFUL
/* ETH.CBS_IDLESLOPE_Q_B */
#define ETH_CBS_IDLESLOPE_Q_B_IDLESLOPE_B_Pos   0UL
#define ETH_CBS_IDLESLOPE_Q_B_IDLESLOPE_B_Msk   0xFFFFFFFFUL
/* ETH.UPPER_TX_Q_BASE_ADDR */
#define ETH_UPPER_TX_Q_BASE_ADDR_UPPER_TX_Q_BASE_ADDR_Pos 0UL
#define ETH_UPPER_TX_Q_BASE_ADDR_UPPER_TX_Q_BASE_ADDR_Msk 0xFFFFFFFFUL
/* ETH.TX_BD_CONTROL */
#define ETH_TX_BD_CONTROL_TX_BD_TS_MODE_Pos     4UL
#define ETH_TX_BD_CONTROL_TX_BD_TS_MODE_Msk     0x30UL
/* ETH.RX_BD_CONTROL */
#define ETH_RX_BD_CONTROL_RX_BD_TS_MODE_Pos     4UL
#define ETH_RX_BD_CONTROL_RX_BD_TS_MODE_Msk     0x30UL
/* ETH.UPPER_RX_Q_BASE_ADDR */
#define ETH_UPPER_RX_Q_BASE_ADDR_UPPER_RX_Q_BASE_ADDR_Pos 0UL
#define ETH_UPPER_RX_Q_BASE_ADDR_UPPER_RX_Q_BASE_ADDR_Msk 0xFFFFFFFFUL
/* ETH.HIDDEN_REG0 */
#define ETH_HIDDEN_REG0_HIDDEN0_FIELD_Pos       0UL
#define ETH_HIDDEN_REG0_HIDDEN0_FIELD_Msk       0xFFFFFFFFUL
/* ETH.HIDDEN_REG1 */
#define ETH_HIDDEN_REG1_HIDDEN1_FIELD_Pos       0UL
#define ETH_HIDDEN_REG1_HIDDEN1_FIELD_Msk       0xFFFFFFFFUL
/* ETH.HIDDEN_REG2 */
#define ETH_HIDDEN_REG2_HIDDEN2_FIELD_Pos       0UL
#define ETH_HIDDEN_REG2_HIDDEN2_FIELD_Msk       0xFFFFFFFFUL
/* ETH.HIDDEN_REG3 */
#define ETH_HIDDEN_REG3_HIDDEN3_FIELD_Pos       0UL
#define ETH_HIDDEN_REG3_HIDDEN3_FIELD_Msk       0xFUL
/* ETH.HIDDEN_REG4 */
#define ETH_HIDDEN_REG4_HIDDEN4_FIELD_L_Pos     0UL
#define ETH_HIDDEN_REG4_HIDDEN4_FIELD_L_Msk     0x1FFUL
#define ETH_HIDDEN_REG4_HIDDEN4_FIELD_H_Pos     16UL
#define ETH_HIDDEN_REG4_HIDDEN4_FIELD_H_Msk     0x1FF0000UL
/* ETH.HIDDEN_REG5 */
#define ETH_HIDDEN_REG5_HIDDEN5_FIELD_L_Pos     0UL
#define ETH_HIDDEN_REG5_HIDDEN5_FIELD_L_Msk     0x1FFUL
#define ETH_HIDDEN_REG5_HIDDEN5_FIELD_H_Pos     16UL
#define ETH_HIDDEN_REG5_HIDDEN5_FIELD_H_Msk     0x1FF0000UL
/* ETH.SCREENING_TYPE_1_REGISTER_0 */
#define ETH_SCREENING_TYPE_1_REGISTER_0_QUEUE_NUMBER_Pos 0UL
#define ETH_SCREENING_TYPE_1_REGISTER_0_QUEUE_NUMBER_Msk 0xFUL
#define ETH_SCREENING_TYPE_1_REGISTER_0_DSTC_MATCH_Pos 4UL
#define ETH_SCREENING_TYPE_1_REGISTER_0_DSTC_MATCH_Msk 0xFF0UL
#define ETH_SCREENING_TYPE_1_REGISTER_0_UDP_PORT_MATCH_Pos 12UL
#define ETH_SCREENING_TYPE_1_REGISTER_0_UDP_PORT_MATCH_Msk 0xFFFF000UL
#define ETH_SCREENING_TYPE_1_REGISTER_0_DSTC_ENABLE_Pos 28UL
#define ETH_SCREENING_TYPE_1_REGISTER_0_DSTC_ENABLE_Msk 0x10000000UL
#define ETH_SCREENING_TYPE_1_REGISTER_0_UDP_PORT_MATCH_ENABLE_Pos 29UL
#define ETH_SCREENING_TYPE_1_REGISTER_0_UDP_PORT_MATCH_ENABLE_Msk 0x20000000UL
/* ETH.SCREENING_TYPE_1_REGISTER_1 */
#define ETH_SCREENING_TYPE_1_REGISTER_1_QUEUE_NUMBER_Pos 0UL
#define ETH_SCREENING_TYPE_1_REGISTER_1_QUEUE_NUMBER_Msk 0xFUL
#define ETH_SCREENING_TYPE_1_REGISTER_1_DSTC_MATCH_Pos 4UL
#define ETH_SCREENING_TYPE_1_REGISTER_1_DSTC_MATCH_Msk 0xFF0UL
#define ETH_SCREENING_TYPE_1_REGISTER_1_UDP_PORT_MATCH_Pos 12UL
#define ETH_SCREENING_TYPE_1_REGISTER_1_UDP_PORT_MATCH_Msk 0xFFFF000UL
#define ETH_SCREENING_TYPE_1_REGISTER_1_DSTC_ENABLE_Pos 28UL
#define ETH_SCREENING_TYPE_1_REGISTER_1_DSTC_ENABLE_Msk 0x10000000UL
#define ETH_SCREENING_TYPE_1_REGISTER_1_UDP_PORT_MATCH_ENABLE_Pos 29UL
#define ETH_SCREENING_TYPE_1_REGISTER_1_UDP_PORT_MATCH_ENABLE_Msk 0x20000000UL
/* ETH.SCREENING_TYPE_1_REGISTER_2 */
#define ETH_SCREENING_TYPE_1_REGISTER_2_QUEUE_NUMBER_Pos 0UL
#define ETH_SCREENING_TYPE_1_REGISTER_2_QUEUE_NUMBER_Msk 0xFUL
#define ETH_SCREENING_TYPE_1_REGISTER_2_DSTC_MATCH_Pos 4UL
#define ETH_SCREENING_TYPE_1_REGISTER_2_DSTC_MATCH_Msk 0xFF0UL
#define ETH_SCREENING_TYPE_1_REGISTER_2_UDP_PORT_MATCH_Pos 12UL
#define ETH_SCREENING_TYPE_1_REGISTER_2_UDP_PORT_MATCH_Msk 0xFFFF000UL
#define ETH_SCREENING_TYPE_1_REGISTER_2_DSTC_ENABLE_Pos 28UL
#define ETH_SCREENING_TYPE_1_REGISTER_2_DSTC_ENABLE_Msk 0x10000000UL
#define ETH_SCREENING_TYPE_1_REGISTER_2_UDP_PORT_MATCH_ENABLE_Pos 29UL
#define ETH_SCREENING_TYPE_1_REGISTER_2_UDP_PORT_MATCH_ENABLE_Msk 0x20000000UL
/* ETH.SCREENING_TYPE_1_REGISTER_3 */
#define ETH_SCREENING_TYPE_1_REGISTER_3_QUEUE_NUMBER_Pos 0UL
#define ETH_SCREENING_TYPE_1_REGISTER_3_QUEUE_NUMBER_Msk 0xFUL
#define ETH_SCREENING_TYPE_1_REGISTER_3_DSTC_MATCH_Pos 4UL
#define ETH_SCREENING_TYPE_1_REGISTER_3_DSTC_MATCH_Msk 0xFF0UL
#define ETH_SCREENING_TYPE_1_REGISTER_3_UDP_PORT_MATCH_Pos 12UL
#define ETH_SCREENING_TYPE_1_REGISTER_3_UDP_PORT_MATCH_Msk 0xFFFF000UL
#define ETH_SCREENING_TYPE_1_REGISTER_3_DSTC_ENABLE_Pos 28UL
#define ETH_SCREENING_TYPE_1_REGISTER_3_DSTC_ENABLE_Msk 0x10000000UL
#define ETH_SCREENING_TYPE_1_REGISTER_3_UDP_PORT_MATCH_ENABLE_Pos 29UL
#define ETH_SCREENING_TYPE_1_REGISTER_3_UDP_PORT_MATCH_ENABLE_Msk 0x20000000UL
/* ETH.SCREENING_TYPE_1_REGISTER_4 */
#define ETH_SCREENING_TYPE_1_REGISTER_4_QUEUE_NUMBER_Pos 0UL
#define ETH_SCREENING_TYPE_1_REGISTER_4_QUEUE_NUMBER_Msk 0xFUL
#define ETH_SCREENING_TYPE_1_REGISTER_4_DSTC_MATCH_Pos 4UL
#define ETH_SCREENING_TYPE_1_REGISTER_4_DSTC_MATCH_Msk 0xFF0UL
#define ETH_SCREENING_TYPE_1_REGISTER_4_UDP_PORT_MATCH_Pos 12UL
#define ETH_SCREENING_TYPE_1_REGISTER_4_UDP_PORT_MATCH_Msk 0xFFFF000UL
#define ETH_SCREENING_TYPE_1_REGISTER_4_DSTC_ENABLE_Pos 28UL
#define ETH_SCREENING_TYPE_1_REGISTER_4_DSTC_ENABLE_Msk 0x10000000UL
#define ETH_SCREENING_TYPE_1_REGISTER_4_UDP_PORT_MATCH_ENABLE_Pos 29UL
#define ETH_SCREENING_TYPE_1_REGISTER_4_UDP_PORT_MATCH_ENABLE_Msk 0x20000000UL
/* ETH.SCREENING_TYPE_1_REGISTER_5 */
#define ETH_SCREENING_TYPE_1_REGISTER_5_QUEUE_NUMBER_Pos 0UL
#define ETH_SCREENING_TYPE_1_REGISTER_5_QUEUE_NUMBER_Msk 0xFUL
#define ETH_SCREENING_TYPE_1_REGISTER_5_DSTC_MATCH_Pos 4UL
#define ETH_SCREENING_TYPE_1_REGISTER_5_DSTC_MATCH_Msk 0xFF0UL
#define ETH_SCREENING_TYPE_1_REGISTER_5_UDP_PORT_MATCH_Pos 12UL
#define ETH_SCREENING_TYPE_1_REGISTER_5_UDP_PORT_MATCH_Msk 0xFFFF000UL
#define ETH_SCREENING_TYPE_1_REGISTER_5_DSTC_ENABLE_Pos 28UL
#define ETH_SCREENING_TYPE_1_REGISTER_5_DSTC_ENABLE_Msk 0x10000000UL
#define ETH_SCREENING_TYPE_1_REGISTER_5_UDP_PORT_MATCH_ENABLE_Pos 29UL
#define ETH_SCREENING_TYPE_1_REGISTER_5_UDP_PORT_MATCH_ENABLE_Msk 0x20000000UL
/* ETH.SCREENING_TYPE_1_REGISTER_6 */
#define ETH_SCREENING_TYPE_1_REGISTER_6_QUEUE_NUMBER_Pos 0UL
#define ETH_SCREENING_TYPE_1_REGISTER_6_QUEUE_NUMBER_Msk 0xFUL
#define ETH_SCREENING_TYPE_1_REGISTER_6_DSTC_MATCH_Pos 4UL
#define ETH_SCREENING_TYPE_1_REGISTER_6_DSTC_MATCH_Msk 0xFF0UL
#define ETH_SCREENING_TYPE_1_REGISTER_6_UDP_PORT_MATCH_Pos 12UL
#define ETH_SCREENING_TYPE_1_REGISTER_6_UDP_PORT_MATCH_Msk 0xFFFF000UL
#define ETH_SCREENING_TYPE_1_REGISTER_6_DSTC_ENABLE_Pos 28UL
#define ETH_SCREENING_TYPE_1_REGISTER_6_DSTC_ENABLE_Msk 0x10000000UL
#define ETH_SCREENING_TYPE_1_REGISTER_6_UDP_PORT_MATCH_ENABLE_Pos 29UL
#define ETH_SCREENING_TYPE_1_REGISTER_6_UDP_PORT_MATCH_ENABLE_Msk 0x20000000UL
/* ETH.SCREENING_TYPE_1_REGISTER_7 */
#define ETH_SCREENING_TYPE_1_REGISTER_7_QUEUE_NUMBER_Pos 0UL
#define ETH_SCREENING_TYPE_1_REGISTER_7_QUEUE_NUMBER_Msk 0xFUL
#define ETH_SCREENING_TYPE_1_REGISTER_7_DSTC_MATCH_Pos 4UL
#define ETH_SCREENING_TYPE_1_REGISTER_7_DSTC_MATCH_Msk 0xFF0UL
#define ETH_SCREENING_TYPE_1_REGISTER_7_UDP_PORT_MATCH_Pos 12UL
#define ETH_SCREENING_TYPE_1_REGISTER_7_UDP_PORT_MATCH_Msk 0xFFFF000UL
#define ETH_SCREENING_TYPE_1_REGISTER_7_DSTC_ENABLE_Pos 28UL
#define ETH_SCREENING_TYPE_1_REGISTER_7_DSTC_ENABLE_Msk 0x10000000UL
#define ETH_SCREENING_TYPE_1_REGISTER_7_UDP_PORT_MATCH_ENABLE_Pos 29UL
#define ETH_SCREENING_TYPE_1_REGISTER_7_UDP_PORT_MATCH_ENABLE_Msk 0x20000000UL
/* ETH.SCREENING_TYPE_1_REGISTER_8 */
#define ETH_SCREENING_TYPE_1_REGISTER_8_QUEUE_NUMBER_Pos 0UL
#define ETH_SCREENING_TYPE_1_REGISTER_8_QUEUE_NUMBER_Msk 0xFUL
#define ETH_SCREENING_TYPE_1_REGISTER_8_DSTC_MATCH_Pos 4UL
#define ETH_SCREENING_TYPE_1_REGISTER_8_DSTC_MATCH_Msk 0xFF0UL
#define ETH_SCREENING_TYPE_1_REGISTER_8_UDP_PORT_MATCH_Pos 12UL
#define ETH_SCREENING_TYPE_1_REGISTER_8_UDP_PORT_MATCH_Msk 0xFFFF000UL
#define ETH_SCREENING_TYPE_1_REGISTER_8_DSTC_ENABLE_Pos 28UL
#define ETH_SCREENING_TYPE_1_REGISTER_8_DSTC_ENABLE_Msk 0x10000000UL
#define ETH_SCREENING_TYPE_1_REGISTER_8_UDP_PORT_MATCH_ENABLE_Pos 29UL
#define ETH_SCREENING_TYPE_1_REGISTER_8_UDP_PORT_MATCH_ENABLE_Msk 0x20000000UL
/* ETH.SCREENING_TYPE_1_REGISTER_9 */
#define ETH_SCREENING_TYPE_1_REGISTER_9_QUEUE_NUMBER_Pos 0UL
#define ETH_SCREENING_TYPE_1_REGISTER_9_QUEUE_NUMBER_Msk 0xFUL
#define ETH_SCREENING_TYPE_1_REGISTER_9_DSTC_MATCH_Pos 4UL
#define ETH_SCREENING_TYPE_1_REGISTER_9_DSTC_MATCH_Msk 0xFF0UL
#define ETH_SCREENING_TYPE_1_REGISTER_9_UDP_PORT_MATCH_Pos 12UL
#define ETH_SCREENING_TYPE_1_REGISTER_9_UDP_PORT_MATCH_Msk 0xFFFF000UL
#define ETH_SCREENING_TYPE_1_REGISTER_9_DSTC_ENABLE_Pos 28UL
#define ETH_SCREENING_TYPE_1_REGISTER_9_DSTC_ENABLE_Msk 0x10000000UL
#define ETH_SCREENING_TYPE_1_REGISTER_9_UDP_PORT_MATCH_ENABLE_Pos 29UL
#define ETH_SCREENING_TYPE_1_REGISTER_9_UDP_PORT_MATCH_ENABLE_Msk 0x20000000UL
/* ETH.SCREENING_TYPE_1_REGISTER_10 */
#define ETH_SCREENING_TYPE_1_REGISTER_10_QUEUE_NUMBER_Pos 0UL
#define ETH_SCREENING_TYPE_1_REGISTER_10_QUEUE_NUMBER_Msk 0xFUL
#define ETH_SCREENING_TYPE_1_REGISTER_10_DSTC_MATCH_Pos 4UL
#define ETH_SCREENING_TYPE_1_REGISTER_10_DSTC_MATCH_Msk 0xFF0UL
#define ETH_SCREENING_TYPE_1_REGISTER_10_UDP_PORT_MATCH_Pos 12UL
#define ETH_SCREENING_TYPE_1_REGISTER_10_UDP_PORT_MATCH_Msk 0xFFFF000UL
#define ETH_SCREENING_TYPE_1_REGISTER_10_DSTC_ENABLE_Pos 28UL
#define ETH_SCREENING_TYPE_1_REGISTER_10_DSTC_ENABLE_Msk 0x10000000UL
#define ETH_SCREENING_TYPE_1_REGISTER_10_UDP_PORT_MATCH_ENABLE_Pos 29UL
#define ETH_SCREENING_TYPE_1_REGISTER_10_UDP_PORT_MATCH_ENABLE_Msk 0x20000000UL
/* ETH.SCREENING_TYPE_1_REGISTER_11 */
#define ETH_SCREENING_TYPE_1_REGISTER_11_QUEUE_NUMBER_Pos 0UL
#define ETH_SCREENING_TYPE_1_REGISTER_11_QUEUE_NUMBER_Msk 0xFUL
#define ETH_SCREENING_TYPE_1_REGISTER_11_DSTC_MATCH_Pos 4UL
#define ETH_SCREENING_TYPE_1_REGISTER_11_DSTC_MATCH_Msk 0xFF0UL
#define ETH_SCREENING_TYPE_1_REGISTER_11_UDP_PORT_MATCH_Pos 12UL
#define ETH_SCREENING_TYPE_1_REGISTER_11_UDP_PORT_MATCH_Msk 0xFFFF000UL
#define ETH_SCREENING_TYPE_1_REGISTER_11_DSTC_ENABLE_Pos 28UL
#define ETH_SCREENING_TYPE_1_REGISTER_11_DSTC_ENABLE_Msk 0x10000000UL
#define ETH_SCREENING_TYPE_1_REGISTER_11_UDP_PORT_MATCH_ENABLE_Pos 29UL
#define ETH_SCREENING_TYPE_1_REGISTER_11_UDP_PORT_MATCH_ENABLE_Msk 0x20000000UL
/* ETH.SCREENING_TYPE_1_REGISTER_12 */
#define ETH_SCREENING_TYPE_1_REGISTER_12_QUEUE_NUMBER_Pos 0UL
#define ETH_SCREENING_TYPE_1_REGISTER_12_QUEUE_NUMBER_Msk 0xFUL
#define ETH_SCREENING_TYPE_1_REGISTER_12_DSTC_MATCH_Pos 4UL
#define ETH_SCREENING_TYPE_1_REGISTER_12_DSTC_MATCH_Msk 0xFF0UL
#define ETH_SCREENING_TYPE_1_REGISTER_12_UDP_PORT_MATCH_Pos 12UL
#define ETH_SCREENING_TYPE_1_REGISTER_12_UDP_PORT_MATCH_Msk 0xFFFF000UL
#define ETH_SCREENING_TYPE_1_REGISTER_12_DSTC_ENABLE_Pos 28UL
#define ETH_SCREENING_TYPE_1_REGISTER_12_DSTC_ENABLE_Msk 0x10000000UL
#define ETH_SCREENING_TYPE_1_REGISTER_12_UDP_PORT_MATCH_ENABLE_Pos 29UL
#define ETH_SCREENING_TYPE_1_REGISTER_12_UDP_PORT_MATCH_ENABLE_Msk 0x20000000UL
/* ETH.SCREENING_TYPE_1_REGISTER_13 */
#define ETH_SCREENING_TYPE_1_REGISTER_13_QUEUE_NUMBER_Pos 0UL
#define ETH_SCREENING_TYPE_1_REGISTER_13_QUEUE_NUMBER_Msk 0xFUL
#define ETH_SCREENING_TYPE_1_REGISTER_13_DSTC_MATCH_Pos 4UL
#define ETH_SCREENING_TYPE_1_REGISTER_13_DSTC_MATCH_Msk 0xFF0UL
#define ETH_SCREENING_TYPE_1_REGISTER_13_UDP_PORT_MATCH_Pos 12UL
#define ETH_SCREENING_TYPE_1_REGISTER_13_UDP_PORT_MATCH_Msk 0xFFFF000UL
#define ETH_SCREENING_TYPE_1_REGISTER_13_DSTC_ENABLE_Pos 28UL
#define ETH_SCREENING_TYPE_1_REGISTER_13_DSTC_ENABLE_Msk 0x10000000UL
#define ETH_SCREENING_TYPE_1_REGISTER_13_UDP_PORT_MATCH_ENABLE_Pos 29UL
#define ETH_SCREENING_TYPE_1_REGISTER_13_UDP_PORT_MATCH_ENABLE_Msk 0x20000000UL
/* ETH.SCREENING_TYPE_1_REGISTER_14 */
#define ETH_SCREENING_TYPE_1_REGISTER_14_QUEUE_NUMBER_Pos 0UL
#define ETH_SCREENING_TYPE_1_REGISTER_14_QUEUE_NUMBER_Msk 0xFUL
#define ETH_SCREENING_TYPE_1_REGISTER_14_DSTC_MATCH_Pos 4UL
#define ETH_SCREENING_TYPE_1_REGISTER_14_DSTC_MATCH_Msk 0xFF0UL
#define ETH_SCREENING_TYPE_1_REGISTER_14_UDP_PORT_MATCH_Pos 12UL
#define ETH_SCREENING_TYPE_1_REGISTER_14_UDP_PORT_MATCH_Msk 0xFFFF000UL
#define ETH_SCREENING_TYPE_1_REGISTER_14_DSTC_ENABLE_Pos 28UL
#define ETH_SCREENING_TYPE_1_REGISTER_14_DSTC_ENABLE_Msk 0x10000000UL
#define ETH_SCREENING_TYPE_1_REGISTER_14_UDP_PORT_MATCH_ENABLE_Pos 29UL
#define ETH_SCREENING_TYPE_1_REGISTER_14_UDP_PORT_MATCH_ENABLE_Msk 0x20000000UL
/* ETH.SCREENING_TYPE_1_REGISTER_15 */
#define ETH_SCREENING_TYPE_1_REGISTER_15_QUEUE_NUMBER_Pos 0UL
#define ETH_SCREENING_TYPE_1_REGISTER_15_QUEUE_NUMBER_Msk 0xFUL
#define ETH_SCREENING_TYPE_1_REGISTER_15_DSTC_MATCH_Pos 4UL
#define ETH_SCREENING_TYPE_1_REGISTER_15_DSTC_MATCH_Msk 0xFF0UL
#define ETH_SCREENING_TYPE_1_REGISTER_15_UDP_PORT_MATCH_Pos 12UL
#define ETH_SCREENING_TYPE_1_REGISTER_15_UDP_PORT_MATCH_Msk 0xFFFF000UL
#define ETH_SCREENING_TYPE_1_REGISTER_15_DSTC_ENABLE_Pos 28UL
#define ETH_SCREENING_TYPE_1_REGISTER_15_DSTC_ENABLE_Msk 0x10000000UL
#define ETH_SCREENING_TYPE_1_REGISTER_15_UDP_PORT_MATCH_ENABLE_Pos 29UL
#define ETH_SCREENING_TYPE_1_REGISTER_15_UDP_PORT_MATCH_ENABLE_Msk 0x20000000UL
/* ETH.SCREENING_TYPE_2_REGISTER_0 */
#define ETH_SCREENING_TYPE_2_REGISTER_0_QUEUE_NUMBER_Pos 0UL
#define ETH_SCREENING_TYPE_2_REGISTER_0_QUEUE_NUMBER_Msk 0xFUL
#define ETH_SCREENING_TYPE_2_REGISTER_0_VLAN_PRIORITY_Pos 4UL
#define ETH_SCREENING_TYPE_2_REGISTER_0_VLAN_PRIORITY_Msk 0x70UL
#define ETH_SCREENING_TYPE_2_REGISTER_0_RESERVED_7_Pos 7UL
#define ETH_SCREENING_TYPE_2_REGISTER_0_RESERVED_7_Msk 0x80UL
#define ETH_SCREENING_TYPE_2_REGISTER_0_VLAN_ENABLE_Pos 8UL
#define ETH_SCREENING_TYPE_2_REGISTER_0_VLAN_ENABLE_Msk 0x100UL
#define ETH_SCREENING_TYPE_2_REGISTER_0_INDEX_Pos 9UL
#define ETH_SCREENING_TYPE_2_REGISTER_0_INDEX_Msk 0xE00UL
#define ETH_SCREENING_TYPE_2_REGISTER_0_ETHERTYPE_ENABLE_Pos 12UL
#define ETH_SCREENING_TYPE_2_REGISTER_0_ETHERTYPE_ENABLE_Msk 0x1000UL
#define ETH_SCREENING_TYPE_2_REGISTER_0_COMPARE_A_Pos 13UL
#define ETH_SCREENING_TYPE_2_REGISTER_0_COMPARE_A_Msk 0x3E000UL
#define ETH_SCREENING_TYPE_2_REGISTER_0_COMPARE_A_ENABLE_Pos 18UL
#define ETH_SCREENING_TYPE_2_REGISTER_0_COMPARE_A_ENABLE_Msk 0x40000UL
#define ETH_SCREENING_TYPE_2_REGISTER_0_COMPARE_B_Pos 19UL
#define ETH_SCREENING_TYPE_2_REGISTER_0_COMPARE_B_Msk 0xF80000UL
#define ETH_SCREENING_TYPE_2_REGISTER_0_COMPARE_B_ENABLE_Pos 24UL
#define ETH_SCREENING_TYPE_2_REGISTER_0_COMPARE_B_ENABLE_Msk 0x1000000UL
#define ETH_SCREENING_TYPE_2_REGISTER_0_COMPARE_C_Pos 25UL
#define ETH_SCREENING_TYPE_2_REGISTER_0_COMPARE_C_Msk 0x3E000000UL
#define ETH_SCREENING_TYPE_2_REGISTER_0_COMPARE_C_ENABLE_Pos 30UL
#define ETH_SCREENING_TYPE_2_REGISTER_0_COMPARE_C_ENABLE_Msk 0x40000000UL
#define ETH_SCREENING_TYPE_2_REGISTER_0_RESERVED_31_Pos 31UL
#define ETH_SCREENING_TYPE_2_REGISTER_0_RESERVED_31_Msk 0x80000000UL
/* ETH.SCREENING_TYPE_2_REGISTER_1 */
#define ETH_SCREENING_TYPE_2_REGISTER_1_QUEUE_NUMBER_Pos 0UL
#define ETH_SCREENING_TYPE_2_REGISTER_1_QUEUE_NUMBER_Msk 0xFUL
#define ETH_SCREENING_TYPE_2_REGISTER_1_VLAN_PRIORITY_Pos 4UL
#define ETH_SCREENING_TYPE_2_REGISTER_1_VLAN_PRIORITY_Msk 0x70UL
#define ETH_SCREENING_TYPE_2_REGISTER_1_RESERVED_7_Pos 7UL
#define ETH_SCREENING_TYPE_2_REGISTER_1_RESERVED_7_Msk 0x80UL
#define ETH_SCREENING_TYPE_2_REGISTER_1_VLAN_ENABLE_Pos 8UL
#define ETH_SCREENING_TYPE_2_REGISTER_1_VLAN_ENABLE_Msk 0x100UL
#define ETH_SCREENING_TYPE_2_REGISTER_1_INDEX_Pos 9UL
#define ETH_SCREENING_TYPE_2_REGISTER_1_INDEX_Msk 0xE00UL
#define ETH_SCREENING_TYPE_2_REGISTER_1_ETHERTYPE_ENABLE_Pos 12UL
#define ETH_SCREENING_TYPE_2_REGISTER_1_ETHERTYPE_ENABLE_Msk 0x1000UL
#define ETH_SCREENING_TYPE_2_REGISTER_1_COMPARE_A_Pos 13UL
#define ETH_SCREENING_TYPE_2_REGISTER_1_COMPARE_A_Msk 0x3E000UL
#define ETH_SCREENING_TYPE_2_REGISTER_1_COMPARE_A_ENABLE_Pos 18UL
#define ETH_SCREENING_TYPE_2_REGISTER_1_COMPARE_A_ENABLE_Msk 0x40000UL
#define ETH_SCREENING_TYPE_2_REGISTER_1_COMPARE_B_Pos 19UL
#define ETH_SCREENING_TYPE_2_REGISTER_1_COMPARE_B_Msk 0xF80000UL
#define ETH_SCREENING_TYPE_2_REGISTER_1_COMPARE_B_ENABLE_Pos 24UL
#define ETH_SCREENING_TYPE_2_REGISTER_1_COMPARE_B_ENABLE_Msk 0x1000000UL
#define ETH_SCREENING_TYPE_2_REGISTER_1_COMPARE_C_Pos 25UL
#define ETH_SCREENING_TYPE_2_REGISTER_1_COMPARE_C_Msk 0x3E000000UL
#define ETH_SCREENING_TYPE_2_REGISTER_1_COMPARE_C_ENABLE_Pos 30UL
#define ETH_SCREENING_TYPE_2_REGISTER_1_COMPARE_C_ENABLE_Msk 0x40000000UL
#define ETH_SCREENING_TYPE_2_REGISTER_1_RESERVED_31_Pos 31UL
#define ETH_SCREENING_TYPE_2_REGISTER_1_RESERVED_31_Msk 0x80000000UL
/* ETH.SCREENING_TYPE_2_REGISTER_2 */
#define ETH_SCREENING_TYPE_2_REGISTER_2_QUEUE_NUMBER_Pos 0UL
#define ETH_SCREENING_TYPE_2_REGISTER_2_QUEUE_NUMBER_Msk 0xFUL
#define ETH_SCREENING_TYPE_2_REGISTER_2_VLAN_PRIORITY_Pos 4UL
#define ETH_SCREENING_TYPE_2_REGISTER_2_VLAN_PRIORITY_Msk 0x70UL
#define ETH_SCREENING_TYPE_2_REGISTER_2_RESERVED_7_Pos 7UL
#define ETH_SCREENING_TYPE_2_REGISTER_2_RESERVED_7_Msk 0x80UL
#define ETH_SCREENING_TYPE_2_REGISTER_2_VLAN_ENABLE_Pos 8UL
#define ETH_SCREENING_TYPE_2_REGISTER_2_VLAN_ENABLE_Msk 0x100UL
#define ETH_SCREENING_TYPE_2_REGISTER_2_INDEX_Pos 9UL
#define ETH_SCREENING_TYPE_2_REGISTER_2_INDEX_Msk 0xE00UL
#define ETH_SCREENING_TYPE_2_REGISTER_2_ETHERTYPE_ENABLE_Pos 12UL
#define ETH_SCREENING_TYPE_2_REGISTER_2_ETHERTYPE_ENABLE_Msk 0x1000UL
#define ETH_SCREENING_TYPE_2_REGISTER_2_COMPARE_A_Pos 13UL
#define ETH_SCREENING_TYPE_2_REGISTER_2_COMPARE_A_Msk 0x3E000UL
#define ETH_SCREENING_TYPE_2_REGISTER_2_COMPARE_A_ENABLE_Pos 18UL
#define ETH_SCREENING_TYPE_2_REGISTER_2_COMPARE_A_ENABLE_Msk 0x40000UL
#define ETH_SCREENING_TYPE_2_REGISTER_2_COMPARE_B_Pos 19UL
#define ETH_SCREENING_TYPE_2_REGISTER_2_COMPARE_B_Msk 0xF80000UL
#define ETH_SCREENING_TYPE_2_REGISTER_2_COMPARE_B_ENABLE_Pos 24UL
#define ETH_SCREENING_TYPE_2_REGISTER_2_COMPARE_B_ENABLE_Msk 0x1000000UL
#define ETH_SCREENING_TYPE_2_REGISTER_2_COMPARE_C_Pos 25UL
#define ETH_SCREENING_TYPE_2_REGISTER_2_COMPARE_C_Msk 0x3E000000UL
#define ETH_SCREENING_TYPE_2_REGISTER_2_COMPARE_C_ENABLE_Pos 30UL
#define ETH_SCREENING_TYPE_2_REGISTER_2_COMPARE_C_ENABLE_Msk 0x40000000UL
#define ETH_SCREENING_TYPE_2_REGISTER_2_RESERVED_31_Pos 31UL
#define ETH_SCREENING_TYPE_2_REGISTER_2_RESERVED_31_Msk 0x80000000UL
/* ETH.SCREENING_TYPE_2_REGISTER_3 */
#define ETH_SCREENING_TYPE_2_REGISTER_3_QUEUE_NUMBER_Pos 0UL
#define ETH_SCREENING_TYPE_2_REGISTER_3_QUEUE_NUMBER_Msk 0xFUL
#define ETH_SCREENING_TYPE_2_REGISTER_3_VLAN_PRIORITY_Pos 4UL
#define ETH_SCREENING_TYPE_2_REGISTER_3_VLAN_PRIORITY_Msk 0x70UL
#define ETH_SCREENING_TYPE_2_REGISTER_3_RESERVED_7_Pos 7UL
#define ETH_SCREENING_TYPE_2_REGISTER_3_RESERVED_7_Msk 0x80UL
#define ETH_SCREENING_TYPE_2_REGISTER_3_VLAN_ENABLE_Pos 8UL
#define ETH_SCREENING_TYPE_2_REGISTER_3_VLAN_ENABLE_Msk 0x100UL
#define ETH_SCREENING_TYPE_2_REGISTER_3_INDEX_Pos 9UL
#define ETH_SCREENING_TYPE_2_REGISTER_3_INDEX_Msk 0xE00UL
#define ETH_SCREENING_TYPE_2_REGISTER_3_ETHERTYPE_ENABLE_Pos 12UL
#define ETH_SCREENING_TYPE_2_REGISTER_3_ETHERTYPE_ENABLE_Msk 0x1000UL
#define ETH_SCREENING_TYPE_2_REGISTER_3_COMPARE_A_Pos 13UL
#define ETH_SCREENING_TYPE_2_REGISTER_3_COMPARE_A_Msk 0x3E000UL
#define ETH_SCREENING_TYPE_2_REGISTER_3_COMPARE_A_ENABLE_Pos 18UL
#define ETH_SCREENING_TYPE_2_REGISTER_3_COMPARE_A_ENABLE_Msk 0x40000UL
#define ETH_SCREENING_TYPE_2_REGISTER_3_COMPARE_B_Pos 19UL
#define ETH_SCREENING_TYPE_2_REGISTER_3_COMPARE_B_Msk 0xF80000UL
#define ETH_SCREENING_TYPE_2_REGISTER_3_COMPARE_B_ENABLE_Pos 24UL
#define ETH_SCREENING_TYPE_2_REGISTER_3_COMPARE_B_ENABLE_Msk 0x1000000UL
#define ETH_SCREENING_TYPE_2_REGISTER_3_COMPARE_C_Pos 25UL
#define ETH_SCREENING_TYPE_2_REGISTER_3_COMPARE_C_Msk 0x3E000000UL
#define ETH_SCREENING_TYPE_2_REGISTER_3_COMPARE_C_ENABLE_Pos 30UL
#define ETH_SCREENING_TYPE_2_REGISTER_3_COMPARE_C_ENABLE_Msk 0x40000000UL
#define ETH_SCREENING_TYPE_2_REGISTER_3_RESERVED_31_Pos 31UL
#define ETH_SCREENING_TYPE_2_REGISTER_3_RESERVED_31_Msk 0x80000000UL
/* ETH.SCREENING_TYPE_2_REGISTER_4 */
#define ETH_SCREENING_TYPE_2_REGISTER_4_QUEUE_NUMBER_Pos 0UL
#define ETH_SCREENING_TYPE_2_REGISTER_4_QUEUE_NUMBER_Msk 0xFUL
#define ETH_SCREENING_TYPE_2_REGISTER_4_VLAN_PRIORITY_Pos 4UL
#define ETH_SCREENING_TYPE_2_REGISTER_4_VLAN_PRIORITY_Msk 0x70UL
#define ETH_SCREENING_TYPE_2_REGISTER_4_RESERVED_7_Pos 7UL
#define ETH_SCREENING_TYPE_2_REGISTER_4_RESERVED_7_Msk 0x80UL
#define ETH_SCREENING_TYPE_2_REGISTER_4_VLAN_ENABLE_Pos 8UL
#define ETH_SCREENING_TYPE_2_REGISTER_4_VLAN_ENABLE_Msk 0x100UL
#define ETH_SCREENING_TYPE_2_REGISTER_4_INDEX_Pos 9UL
#define ETH_SCREENING_TYPE_2_REGISTER_4_INDEX_Msk 0xE00UL
#define ETH_SCREENING_TYPE_2_REGISTER_4_ETHERTYPE_ENABLE_Pos 12UL
#define ETH_SCREENING_TYPE_2_REGISTER_4_ETHERTYPE_ENABLE_Msk 0x1000UL
#define ETH_SCREENING_TYPE_2_REGISTER_4_COMPARE_A_Pos 13UL
#define ETH_SCREENING_TYPE_2_REGISTER_4_COMPARE_A_Msk 0x3E000UL
#define ETH_SCREENING_TYPE_2_REGISTER_4_COMPARE_A_ENABLE_Pos 18UL
#define ETH_SCREENING_TYPE_2_REGISTER_4_COMPARE_A_ENABLE_Msk 0x40000UL
#define ETH_SCREENING_TYPE_2_REGISTER_4_COMPARE_B_Pos 19UL
#define ETH_SCREENING_TYPE_2_REGISTER_4_COMPARE_B_Msk 0xF80000UL
#define ETH_SCREENING_TYPE_2_REGISTER_4_COMPARE_B_ENABLE_Pos 24UL
#define ETH_SCREENING_TYPE_2_REGISTER_4_COMPARE_B_ENABLE_Msk 0x1000000UL
#define ETH_SCREENING_TYPE_2_REGISTER_4_COMPARE_C_Pos 25UL
#define ETH_SCREENING_TYPE_2_REGISTER_4_COMPARE_C_Msk 0x3E000000UL
#define ETH_SCREENING_TYPE_2_REGISTER_4_COMPARE_C_ENABLE_Pos 30UL
#define ETH_SCREENING_TYPE_2_REGISTER_4_COMPARE_C_ENABLE_Msk 0x40000000UL
#define ETH_SCREENING_TYPE_2_REGISTER_4_RESERVED_31_Pos 31UL
#define ETH_SCREENING_TYPE_2_REGISTER_4_RESERVED_31_Msk 0x80000000UL
/* ETH.SCREENING_TYPE_2_REGISTER_5 */
#define ETH_SCREENING_TYPE_2_REGISTER_5_QUEUE_NUMBER_Pos 0UL
#define ETH_SCREENING_TYPE_2_REGISTER_5_QUEUE_NUMBER_Msk 0xFUL
#define ETH_SCREENING_TYPE_2_REGISTER_5_VLAN_PRIORITY_Pos 4UL
#define ETH_SCREENING_TYPE_2_REGISTER_5_VLAN_PRIORITY_Msk 0x70UL
#define ETH_SCREENING_TYPE_2_REGISTER_5_RESERVED_7_Pos 7UL
#define ETH_SCREENING_TYPE_2_REGISTER_5_RESERVED_7_Msk 0x80UL
#define ETH_SCREENING_TYPE_2_REGISTER_5_VLAN_ENABLE_Pos 8UL
#define ETH_SCREENING_TYPE_2_REGISTER_5_VLAN_ENABLE_Msk 0x100UL
#define ETH_SCREENING_TYPE_2_REGISTER_5_INDEX_Pos 9UL
#define ETH_SCREENING_TYPE_2_REGISTER_5_INDEX_Msk 0xE00UL
#define ETH_SCREENING_TYPE_2_REGISTER_5_ETHERTYPE_ENABLE_Pos 12UL
#define ETH_SCREENING_TYPE_2_REGISTER_5_ETHERTYPE_ENABLE_Msk 0x1000UL
#define ETH_SCREENING_TYPE_2_REGISTER_5_COMPARE_A_Pos 13UL
#define ETH_SCREENING_TYPE_2_REGISTER_5_COMPARE_A_Msk 0x3E000UL
#define ETH_SCREENING_TYPE_2_REGISTER_5_COMPARE_A_ENABLE_Pos 18UL
#define ETH_SCREENING_TYPE_2_REGISTER_5_COMPARE_A_ENABLE_Msk 0x40000UL
#define ETH_SCREENING_TYPE_2_REGISTER_5_COMPARE_B_Pos 19UL
#define ETH_SCREENING_TYPE_2_REGISTER_5_COMPARE_B_Msk 0xF80000UL
#define ETH_SCREENING_TYPE_2_REGISTER_5_COMPARE_B_ENABLE_Pos 24UL
#define ETH_SCREENING_TYPE_2_REGISTER_5_COMPARE_B_ENABLE_Msk 0x1000000UL
#define ETH_SCREENING_TYPE_2_REGISTER_5_COMPARE_C_Pos 25UL
#define ETH_SCREENING_TYPE_2_REGISTER_5_COMPARE_C_Msk 0x3E000000UL
#define ETH_SCREENING_TYPE_2_REGISTER_5_COMPARE_C_ENABLE_Pos 30UL
#define ETH_SCREENING_TYPE_2_REGISTER_5_COMPARE_C_ENABLE_Msk 0x40000000UL
#define ETH_SCREENING_TYPE_2_REGISTER_5_RESERVED_31_Pos 31UL
#define ETH_SCREENING_TYPE_2_REGISTER_5_RESERVED_31_Msk 0x80000000UL
/* ETH.SCREENING_TYPE_2_REGISTER_6 */
#define ETH_SCREENING_TYPE_2_REGISTER_6_QUEUE_NUMBER_Pos 0UL
#define ETH_SCREENING_TYPE_2_REGISTER_6_QUEUE_NUMBER_Msk 0xFUL
#define ETH_SCREENING_TYPE_2_REGISTER_6_VLAN_PRIORITY_Pos 4UL
#define ETH_SCREENING_TYPE_2_REGISTER_6_VLAN_PRIORITY_Msk 0x70UL
#define ETH_SCREENING_TYPE_2_REGISTER_6_RESERVED_7_Pos 7UL
#define ETH_SCREENING_TYPE_2_REGISTER_6_RESERVED_7_Msk 0x80UL
#define ETH_SCREENING_TYPE_2_REGISTER_6_VLAN_ENABLE_Pos 8UL
#define ETH_SCREENING_TYPE_2_REGISTER_6_VLAN_ENABLE_Msk 0x100UL
#define ETH_SCREENING_TYPE_2_REGISTER_6_INDEX_Pos 9UL
#define ETH_SCREENING_TYPE_2_REGISTER_6_INDEX_Msk 0xE00UL
#define ETH_SCREENING_TYPE_2_REGISTER_6_ETHERTYPE_ENABLE_Pos 12UL
#define ETH_SCREENING_TYPE_2_REGISTER_6_ETHERTYPE_ENABLE_Msk 0x1000UL
#define ETH_SCREENING_TYPE_2_REGISTER_6_COMPARE_A_Pos 13UL
#define ETH_SCREENING_TYPE_2_REGISTER_6_COMPARE_A_Msk 0x3E000UL
#define ETH_SCREENING_TYPE_2_REGISTER_6_COMPARE_A_ENABLE_Pos 18UL
#define ETH_SCREENING_TYPE_2_REGISTER_6_COMPARE_A_ENABLE_Msk 0x40000UL
#define ETH_SCREENING_TYPE_2_REGISTER_6_COMPARE_B_Pos 19UL
#define ETH_SCREENING_TYPE_2_REGISTER_6_COMPARE_B_Msk 0xF80000UL
#define ETH_SCREENING_TYPE_2_REGISTER_6_COMPARE_B_ENABLE_Pos 24UL
#define ETH_SCREENING_TYPE_2_REGISTER_6_COMPARE_B_ENABLE_Msk 0x1000000UL
#define ETH_SCREENING_TYPE_2_REGISTER_6_COMPARE_C_Pos 25UL
#define ETH_SCREENING_TYPE_2_REGISTER_6_COMPARE_C_Msk 0x3E000000UL
#define ETH_SCREENING_TYPE_2_REGISTER_6_COMPARE_C_ENABLE_Pos 30UL
#define ETH_SCREENING_TYPE_2_REGISTER_6_COMPARE_C_ENABLE_Msk 0x40000000UL
#define ETH_SCREENING_TYPE_2_REGISTER_6_RESERVED_31_Pos 31UL
#define ETH_SCREENING_TYPE_2_REGISTER_6_RESERVED_31_Msk 0x80000000UL
/* ETH.SCREENING_TYPE_2_REGISTER_7 */
#define ETH_SCREENING_TYPE_2_REGISTER_7_QUEUE_NUMBER_Pos 0UL
#define ETH_SCREENING_TYPE_2_REGISTER_7_QUEUE_NUMBER_Msk 0xFUL
#define ETH_SCREENING_TYPE_2_REGISTER_7_VLAN_PRIORITY_Pos 4UL
#define ETH_SCREENING_TYPE_2_REGISTER_7_VLAN_PRIORITY_Msk 0x70UL
#define ETH_SCREENING_TYPE_2_REGISTER_7_RESERVED_7_Pos 7UL
#define ETH_SCREENING_TYPE_2_REGISTER_7_RESERVED_7_Msk 0x80UL
#define ETH_SCREENING_TYPE_2_REGISTER_7_VLAN_ENABLE_Pos 8UL
#define ETH_SCREENING_TYPE_2_REGISTER_7_VLAN_ENABLE_Msk 0x100UL
#define ETH_SCREENING_TYPE_2_REGISTER_7_INDEX_Pos 9UL
#define ETH_SCREENING_TYPE_2_REGISTER_7_INDEX_Msk 0xE00UL
#define ETH_SCREENING_TYPE_2_REGISTER_7_ETHERTYPE_ENABLE_Pos 12UL
#define ETH_SCREENING_TYPE_2_REGISTER_7_ETHERTYPE_ENABLE_Msk 0x1000UL
#define ETH_SCREENING_TYPE_2_REGISTER_7_COMPARE_A_Pos 13UL
#define ETH_SCREENING_TYPE_2_REGISTER_7_COMPARE_A_Msk 0x3E000UL
#define ETH_SCREENING_TYPE_2_REGISTER_7_COMPARE_A_ENABLE_Pos 18UL
#define ETH_SCREENING_TYPE_2_REGISTER_7_COMPARE_A_ENABLE_Msk 0x40000UL
#define ETH_SCREENING_TYPE_2_REGISTER_7_COMPARE_B_Pos 19UL
#define ETH_SCREENING_TYPE_2_REGISTER_7_COMPARE_B_Msk 0xF80000UL
#define ETH_SCREENING_TYPE_2_REGISTER_7_COMPARE_B_ENABLE_Pos 24UL
#define ETH_SCREENING_TYPE_2_REGISTER_7_COMPARE_B_ENABLE_Msk 0x1000000UL
#define ETH_SCREENING_TYPE_2_REGISTER_7_COMPARE_C_Pos 25UL
#define ETH_SCREENING_TYPE_2_REGISTER_7_COMPARE_C_Msk 0x3E000000UL
#define ETH_SCREENING_TYPE_2_REGISTER_7_COMPARE_C_ENABLE_Pos 30UL
#define ETH_SCREENING_TYPE_2_REGISTER_7_COMPARE_C_ENABLE_Msk 0x40000000UL
#define ETH_SCREENING_TYPE_2_REGISTER_7_RESERVED_31_Pos 31UL
#define ETH_SCREENING_TYPE_2_REGISTER_7_RESERVED_31_Msk 0x80000000UL
/* ETH.SCREENING_TYPE_2_REGISTER_8 */
#define ETH_SCREENING_TYPE_2_REGISTER_8_QUEUE_NUMBER_Pos 0UL
#define ETH_SCREENING_TYPE_2_REGISTER_8_QUEUE_NUMBER_Msk 0xFUL
#define ETH_SCREENING_TYPE_2_REGISTER_8_VLAN_PRIORITY_Pos 4UL
#define ETH_SCREENING_TYPE_2_REGISTER_8_VLAN_PRIORITY_Msk 0x70UL
#define ETH_SCREENING_TYPE_2_REGISTER_8_RESERVED_7_Pos 7UL
#define ETH_SCREENING_TYPE_2_REGISTER_8_RESERVED_7_Msk 0x80UL
#define ETH_SCREENING_TYPE_2_REGISTER_8_VLAN_ENABLE_Pos 8UL
#define ETH_SCREENING_TYPE_2_REGISTER_8_VLAN_ENABLE_Msk 0x100UL
#define ETH_SCREENING_TYPE_2_REGISTER_8_INDEX_Pos 9UL
#define ETH_SCREENING_TYPE_2_REGISTER_8_INDEX_Msk 0xE00UL
#define ETH_SCREENING_TYPE_2_REGISTER_8_ETHERTYPE_ENABLE_Pos 12UL
#define ETH_SCREENING_TYPE_2_REGISTER_8_ETHERTYPE_ENABLE_Msk 0x1000UL
#define ETH_SCREENING_TYPE_2_REGISTER_8_COMPARE_A_Pos 13UL
#define ETH_SCREENING_TYPE_2_REGISTER_8_COMPARE_A_Msk 0x3E000UL
#define ETH_SCREENING_TYPE_2_REGISTER_8_COMPARE_A_ENABLE_Pos 18UL
#define ETH_SCREENING_TYPE_2_REGISTER_8_COMPARE_A_ENABLE_Msk 0x40000UL
#define ETH_SCREENING_TYPE_2_REGISTER_8_COMPARE_B_Pos 19UL
#define ETH_SCREENING_TYPE_2_REGISTER_8_COMPARE_B_Msk 0xF80000UL
#define ETH_SCREENING_TYPE_2_REGISTER_8_COMPARE_B_ENABLE_Pos 24UL
#define ETH_SCREENING_TYPE_2_REGISTER_8_COMPARE_B_ENABLE_Msk 0x1000000UL
#define ETH_SCREENING_TYPE_2_REGISTER_8_COMPARE_C_Pos 25UL
#define ETH_SCREENING_TYPE_2_REGISTER_8_COMPARE_C_Msk 0x3E000000UL
#define ETH_SCREENING_TYPE_2_REGISTER_8_COMPARE_C_ENABLE_Pos 30UL
#define ETH_SCREENING_TYPE_2_REGISTER_8_COMPARE_C_ENABLE_Msk 0x40000000UL
#define ETH_SCREENING_TYPE_2_REGISTER_8_RESERVED_31_Pos 31UL
#define ETH_SCREENING_TYPE_2_REGISTER_8_RESERVED_31_Msk 0x80000000UL
/* ETH.SCREENING_TYPE_2_REGISTER_9 */
#define ETH_SCREENING_TYPE_2_REGISTER_9_QUEUE_NUMBER_Pos 0UL
#define ETH_SCREENING_TYPE_2_REGISTER_9_QUEUE_NUMBER_Msk 0xFUL
#define ETH_SCREENING_TYPE_2_REGISTER_9_VLAN_PRIORITY_Pos 4UL
#define ETH_SCREENING_TYPE_2_REGISTER_9_VLAN_PRIORITY_Msk 0x70UL
#define ETH_SCREENING_TYPE_2_REGISTER_9_RESERVED_7_Pos 7UL
#define ETH_SCREENING_TYPE_2_REGISTER_9_RESERVED_7_Msk 0x80UL
#define ETH_SCREENING_TYPE_2_REGISTER_9_VLAN_ENABLE_Pos 8UL
#define ETH_SCREENING_TYPE_2_REGISTER_9_VLAN_ENABLE_Msk 0x100UL
#define ETH_SCREENING_TYPE_2_REGISTER_9_INDEX_Pos 9UL
#define ETH_SCREENING_TYPE_2_REGISTER_9_INDEX_Msk 0xE00UL
#define ETH_SCREENING_TYPE_2_REGISTER_9_ETHERTYPE_ENABLE_Pos 12UL
#define ETH_SCREENING_TYPE_2_REGISTER_9_ETHERTYPE_ENABLE_Msk 0x1000UL
#define ETH_SCREENING_TYPE_2_REGISTER_9_COMPARE_A_Pos 13UL
#define ETH_SCREENING_TYPE_2_REGISTER_9_COMPARE_A_Msk 0x3E000UL
#define ETH_SCREENING_TYPE_2_REGISTER_9_COMPARE_A_ENABLE_Pos 18UL
#define ETH_SCREENING_TYPE_2_REGISTER_9_COMPARE_A_ENABLE_Msk 0x40000UL
#define ETH_SCREENING_TYPE_2_REGISTER_9_COMPARE_B_Pos 19UL
#define ETH_SCREENING_TYPE_2_REGISTER_9_COMPARE_B_Msk 0xF80000UL
#define ETH_SCREENING_TYPE_2_REGISTER_9_COMPARE_B_ENABLE_Pos 24UL
#define ETH_SCREENING_TYPE_2_REGISTER_9_COMPARE_B_ENABLE_Msk 0x1000000UL
#define ETH_SCREENING_TYPE_2_REGISTER_9_COMPARE_C_Pos 25UL
#define ETH_SCREENING_TYPE_2_REGISTER_9_COMPARE_C_Msk 0x3E000000UL
#define ETH_SCREENING_TYPE_2_REGISTER_9_COMPARE_C_ENABLE_Pos 30UL
#define ETH_SCREENING_TYPE_2_REGISTER_9_COMPARE_C_ENABLE_Msk 0x40000000UL
#define ETH_SCREENING_TYPE_2_REGISTER_9_RESERVED_31_Pos 31UL
#define ETH_SCREENING_TYPE_2_REGISTER_9_RESERVED_31_Msk 0x80000000UL
/* ETH.SCREENING_TYPE_2_REGISTER_10 */
#define ETH_SCREENING_TYPE_2_REGISTER_10_QUEUE_NUMBER_Pos 0UL
#define ETH_SCREENING_TYPE_2_REGISTER_10_QUEUE_NUMBER_Msk 0xFUL
#define ETH_SCREENING_TYPE_2_REGISTER_10_VLAN_PRIORITY_Pos 4UL
#define ETH_SCREENING_TYPE_2_REGISTER_10_VLAN_PRIORITY_Msk 0x70UL
#define ETH_SCREENING_TYPE_2_REGISTER_10_RESERVED_7_Pos 7UL
#define ETH_SCREENING_TYPE_2_REGISTER_10_RESERVED_7_Msk 0x80UL
#define ETH_SCREENING_TYPE_2_REGISTER_10_VLAN_ENABLE_Pos 8UL
#define ETH_SCREENING_TYPE_2_REGISTER_10_VLAN_ENABLE_Msk 0x100UL
#define ETH_SCREENING_TYPE_2_REGISTER_10_INDEX_Pos 9UL
#define ETH_SCREENING_TYPE_2_REGISTER_10_INDEX_Msk 0xE00UL
#define ETH_SCREENING_TYPE_2_REGISTER_10_ETHERTYPE_ENABLE_Pos 12UL
#define ETH_SCREENING_TYPE_2_REGISTER_10_ETHERTYPE_ENABLE_Msk 0x1000UL
#define ETH_SCREENING_TYPE_2_REGISTER_10_COMPARE_A_Pos 13UL
#define ETH_SCREENING_TYPE_2_REGISTER_10_COMPARE_A_Msk 0x3E000UL
#define ETH_SCREENING_TYPE_2_REGISTER_10_COMPARE_A_ENABLE_Pos 18UL
#define ETH_SCREENING_TYPE_2_REGISTER_10_COMPARE_A_ENABLE_Msk 0x40000UL
#define ETH_SCREENING_TYPE_2_REGISTER_10_COMPARE_B_Pos 19UL
#define ETH_SCREENING_TYPE_2_REGISTER_10_COMPARE_B_Msk 0xF80000UL
#define ETH_SCREENING_TYPE_2_REGISTER_10_COMPARE_B_ENABLE_Pos 24UL
#define ETH_SCREENING_TYPE_2_REGISTER_10_COMPARE_B_ENABLE_Msk 0x1000000UL
#define ETH_SCREENING_TYPE_2_REGISTER_10_COMPARE_C_Pos 25UL
#define ETH_SCREENING_TYPE_2_REGISTER_10_COMPARE_C_Msk 0x3E000000UL
#define ETH_SCREENING_TYPE_2_REGISTER_10_COMPARE_C_ENABLE_Pos 30UL
#define ETH_SCREENING_TYPE_2_REGISTER_10_COMPARE_C_ENABLE_Msk 0x40000000UL
#define ETH_SCREENING_TYPE_2_REGISTER_10_RESERVED_31_Pos 31UL
#define ETH_SCREENING_TYPE_2_REGISTER_10_RESERVED_31_Msk 0x80000000UL
/* ETH.SCREENING_TYPE_2_REGISTER_11 */
#define ETH_SCREENING_TYPE_2_REGISTER_11_QUEUE_NUMBER_Pos 0UL
#define ETH_SCREENING_TYPE_2_REGISTER_11_QUEUE_NUMBER_Msk 0xFUL
#define ETH_SCREENING_TYPE_2_REGISTER_11_VLAN_PRIORITY_Pos 4UL
#define ETH_SCREENING_TYPE_2_REGISTER_11_VLAN_PRIORITY_Msk 0x70UL
#define ETH_SCREENING_TYPE_2_REGISTER_11_RESERVED_7_Pos 7UL
#define ETH_SCREENING_TYPE_2_REGISTER_11_RESERVED_7_Msk 0x80UL
#define ETH_SCREENING_TYPE_2_REGISTER_11_VLAN_ENABLE_Pos 8UL
#define ETH_SCREENING_TYPE_2_REGISTER_11_VLAN_ENABLE_Msk 0x100UL
#define ETH_SCREENING_TYPE_2_REGISTER_11_INDEX_Pos 9UL
#define ETH_SCREENING_TYPE_2_REGISTER_11_INDEX_Msk 0xE00UL
#define ETH_SCREENING_TYPE_2_REGISTER_11_ETHERTYPE_ENABLE_Pos 12UL
#define ETH_SCREENING_TYPE_2_REGISTER_11_ETHERTYPE_ENABLE_Msk 0x1000UL
#define ETH_SCREENING_TYPE_2_REGISTER_11_COMPARE_A_Pos 13UL
#define ETH_SCREENING_TYPE_2_REGISTER_11_COMPARE_A_Msk 0x3E000UL
#define ETH_SCREENING_TYPE_2_REGISTER_11_COMPARE_A_ENABLE_Pos 18UL
#define ETH_SCREENING_TYPE_2_REGISTER_11_COMPARE_A_ENABLE_Msk 0x40000UL
#define ETH_SCREENING_TYPE_2_REGISTER_11_COMPARE_B_Pos 19UL
#define ETH_SCREENING_TYPE_2_REGISTER_11_COMPARE_B_Msk 0xF80000UL
#define ETH_SCREENING_TYPE_2_REGISTER_11_COMPARE_B_ENABLE_Pos 24UL
#define ETH_SCREENING_TYPE_2_REGISTER_11_COMPARE_B_ENABLE_Msk 0x1000000UL
#define ETH_SCREENING_TYPE_2_REGISTER_11_COMPARE_C_Pos 25UL
#define ETH_SCREENING_TYPE_2_REGISTER_11_COMPARE_C_Msk 0x3E000000UL
#define ETH_SCREENING_TYPE_2_REGISTER_11_COMPARE_C_ENABLE_Pos 30UL
#define ETH_SCREENING_TYPE_2_REGISTER_11_COMPARE_C_ENABLE_Msk 0x40000000UL
#define ETH_SCREENING_TYPE_2_REGISTER_11_RESERVED_31_Pos 31UL
#define ETH_SCREENING_TYPE_2_REGISTER_11_RESERVED_31_Msk 0x80000000UL
/* ETH.SCREENING_TYPE_2_REGISTER_12 */
#define ETH_SCREENING_TYPE_2_REGISTER_12_QUEUE_NUMBER_Pos 0UL
#define ETH_SCREENING_TYPE_2_REGISTER_12_QUEUE_NUMBER_Msk 0xFUL
#define ETH_SCREENING_TYPE_2_REGISTER_12_VLAN_PRIORITY_Pos 4UL
#define ETH_SCREENING_TYPE_2_REGISTER_12_VLAN_PRIORITY_Msk 0x70UL
#define ETH_SCREENING_TYPE_2_REGISTER_12_RESERVED_7_Pos 7UL
#define ETH_SCREENING_TYPE_2_REGISTER_12_RESERVED_7_Msk 0x80UL
#define ETH_SCREENING_TYPE_2_REGISTER_12_VLAN_ENABLE_Pos 8UL
#define ETH_SCREENING_TYPE_2_REGISTER_12_VLAN_ENABLE_Msk 0x100UL
#define ETH_SCREENING_TYPE_2_REGISTER_12_INDEX_Pos 9UL
#define ETH_SCREENING_TYPE_2_REGISTER_12_INDEX_Msk 0xE00UL
#define ETH_SCREENING_TYPE_2_REGISTER_12_ETHERTYPE_ENABLE_Pos 12UL
#define ETH_SCREENING_TYPE_2_REGISTER_12_ETHERTYPE_ENABLE_Msk 0x1000UL
#define ETH_SCREENING_TYPE_2_REGISTER_12_COMPARE_A_Pos 13UL
#define ETH_SCREENING_TYPE_2_REGISTER_12_COMPARE_A_Msk 0x3E000UL
#define ETH_SCREENING_TYPE_2_REGISTER_12_COMPARE_A_ENABLE_Pos 18UL
#define ETH_SCREENING_TYPE_2_REGISTER_12_COMPARE_A_ENABLE_Msk 0x40000UL
#define ETH_SCREENING_TYPE_2_REGISTER_12_COMPARE_B_Pos 19UL
#define ETH_SCREENING_TYPE_2_REGISTER_12_COMPARE_B_Msk 0xF80000UL
#define ETH_SCREENING_TYPE_2_REGISTER_12_COMPARE_B_ENABLE_Pos 24UL
#define ETH_SCREENING_TYPE_2_REGISTER_12_COMPARE_B_ENABLE_Msk 0x1000000UL
#define ETH_SCREENING_TYPE_2_REGISTER_12_COMPARE_C_Pos 25UL
#define ETH_SCREENING_TYPE_2_REGISTER_12_COMPARE_C_Msk 0x3E000000UL
#define ETH_SCREENING_TYPE_2_REGISTER_12_COMPARE_C_ENABLE_Pos 30UL
#define ETH_SCREENING_TYPE_2_REGISTER_12_COMPARE_C_ENABLE_Msk 0x40000000UL
#define ETH_SCREENING_TYPE_2_REGISTER_12_RESERVED_31_Pos 31UL
#define ETH_SCREENING_TYPE_2_REGISTER_12_RESERVED_31_Msk 0x80000000UL
/* ETH.SCREENING_TYPE_2_REGISTER_13 */
#define ETH_SCREENING_TYPE_2_REGISTER_13_QUEUE_NUMBER_Pos 0UL
#define ETH_SCREENING_TYPE_2_REGISTER_13_QUEUE_NUMBER_Msk 0xFUL
#define ETH_SCREENING_TYPE_2_REGISTER_13_VLAN_PRIORITY_Pos 4UL
#define ETH_SCREENING_TYPE_2_REGISTER_13_VLAN_PRIORITY_Msk 0x70UL
#define ETH_SCREENING_TYPE_2_REGISTER_13_RESERVED_7_Pos 7UL
#define ETH_SCREENING_TYPE_2_REGISTER_13_RESERVED_7_Msk 0x80UL
#define ETH_SCREENING_TYPE_2_REGISTER_13_VLAN_ENABLE_Pos 8UL
#define ETH_SCREENING_TYPE_2_REGISTER_13_VLAN_ENABLE_Msk 0x100UL
#define ETH_SCREENING_TYPE_2_REGISTER_13_INDEX_Pos 9UL
#define ETH_SCREENING_TYPE_2_REGISTER_13_INDEX_Msk 0xE00UL
#define ETH_SCREENING_TYPE_2_REGISTER_13_ETHERTYPE_ENABLE_Pos 12UL
#define ETH_SCREENING_TYPE_2_REGISTER_13_ETHERTYPE_ENABLE_Msk 0x1000UL
#define ETH_SCREENING_TYPE_2_REGISTER_13_COMPARE_A_Pos 13UL
#define ETH_SCREENING_TYPE_2_REGISTER_13_COMPARE_A_Msk 0x3E000UL
#define ETH_SCREENING_TYPE_2_REGISTER_13_COMPARE_A_ENABLE_Pos 18UL
#define ETH_SCREENING_TYPE_2_REGISTER_13_COMPARE_A_ENABLE_Msk 0x40000UL
#define ETH_SCREENING_TYPE_2_REGISTER_13_COMPARE_B_Pos 19UL
#define ETH_SCREENING_TYPE_2_REGISTER_13_COMPARE_B_Msk 0xF80000UL
#define ETH_SCREENING_TYPE_2_REGISTER_13_COMPARE_B_ENABLE_Pos 24UL
#define ETH_SCREENING_TYPE_2_REGISTER_13_COMPARE_B_ENABLE_Msk 0x1000000UL
#define ETH_SCREENING_TYPE_2_REGISTER_13_COMPARE_C_Pos 25UL
#define ETH_SCREENING_TYPE_2_REGISTER_13_COMPARE_C_Msk 0x3E000000UL
#define ETH_SCREENING_TYPE_2_REGISTER_13_COMPARE_C_ENABLE_Pos 30UL
#define ETH_SCREENING_TYPE_2_REGISTER_13_COMPARE_C_ENABLE_Msk 0x40000000UL
#define ETH_SCREENING_TYPE_2_REGISTER_13_RESERVED_31_Pos 31UL
#define ETH_SCREENING_TYPE_2_REGISTER_13_RESERVED_31_Msk 0x80000000UL
/* ETH.SCREENING_TYPE_2_REGISTER_14 */
#define ETH_SCREENING_TYPE_2_REGISTER_14_QUEUE_NUMBER_Pos 0UL
#define ETH_SCREENING_TYPE_2_REGISTER_14_QUEUE_NUMBER_Msk 0xFUL
#define ETH_SCREENING_TYPE_2_REGISTER_14_VLAN_PRIORITY_Pos 4UL
#define ETH_SCREENING_TYPE_2_REGISTER_14_VLAN_PRIORITY_Msk 0x70UL
#define ETH_SCREENING_TYPE_2_REGISTER_14_RESERVED_7_Pos 7UL
#define ETH_SCREENING_TYPE_2_REGISTER_14_RESERVED_7_Msk 0x80UL
#define ETH_SCREENING_TYPE_2_REGISTER_14_VLAN_ENABLE_Pos 8UL
#define ETH_SCREENING_TYPE_2_REGISTER_14_VLAN_ENABLE_Msk 0x100UL
#define ETH_SCREENING_TYPE_2_REGISTER_14_INDEX_Pos 9UL
#define ETH_SCREENING_TYPE_2_REGISTER_14_INDEX_Msk 0xE00UL
#define ETH_SCREENING_TYPE_2_REGISTER_14_ETHERTYPE_ENABLE_Pos 12UL
#define ETH_SCREENING_TYPE_2_REGISTER_14_ETHERTYPE_ENABLE_Msk 0x1000UL
#define ETH_SCREENING_TYPE_2_REGISTER_14_COMPARE_A_Pos 13UL
#define ETH_SCREENING_TYPE_2_REGISTER_14_COMPARE_A_Msk 0x3E000UL
#define ETH_SCREENING_TYPE_2_REGISTER_14_COMPARE_A_ENABLE_Pos 18UL
#define ETH_SCREENING_TYPE_2_REGISTER_14_COMPARE_A_ENABLE_Msk 0x40000UL
#define ETH_SCREENING_TYPE_2_REGISTER_14_COMPARE_B_Pos 19UL
#define ETH_SCREENING_TYPE_2_REGISTER_14_COMPARE_B_Msk 0xF80000UL
#define ETH_SCREENING_TYPE_2_REGISTER_14_COMPARE_B_ENABLE_Pos 24UL
#define ETH_SCREENING_TYPE_2_REGISTER_14_COMPARE_B_ENABLE_Msk 0x1000000UL
#define ETH_SCREENING_TYPE_2_REGISTER_14_COMPARE_C_Pos 25UL
#define ETH_SCREENING_TYPE_2_REGISTER_14_COMPARE_C_Msk 0x3E000000UL
#define ETH_SCREENING_TYPE_2_REGISTER_14_COMPARE_C_ENABLE_Pos 30UL
#define ETH_SCREENING_TYPE_2_REGISTER_14_COMPARE_C_ENABLE_Msk 0x40000000UL
#define ETH_SCREENING_TYPE_2_REGISTER_14_RESERVED_31_Pos 31UL
#define ETH_SCREENING_TYPE_2_REGISTER_14_RESERVED_31_Msk 0x80000000UL
/* ETH.SCREENING_TYPE_2_REGISTER_15 */
#define ETH_SCREENING_TYPE_2_REGISTER_15_QUEUE_NUMBER_Pos 0UL
#define ETH_SCREENING_TYPE_2_REGISTER_15_QUEUE_NUMBER_Msk 0xFUL
#define ETH_SCREENING_TYPE_2_REGISTER_15_VLAN_PRIORITY_Pos 4UL
#define ETH_SCREENING_TYPE_2_REGISTER_15_VLAN_PRIORITY_Msk 0x70UL
#define ETH_SCREENING_TYPE_2_REGISTER_15_RESERVED_7_Pos 7UL
#define ETH_SCREENING_TYPE_2_REGISTER_15_RESERVED_7_Msk 0x80UL
#define ETH_SCREENING_TYPE_2_REGISTER_15_VLAN_ENABLE_Pos 8UL
#define ETH_SCREENING_TYPE_2_REGISTER_15_VLAN_ENABLE_Msk 0x100UL
#define ETH_SCREENING_TYPE_2_REGISTER_15_INDEX_Pos 9UL
#define ETH_SCREENING_TYPE_2_REGISTER_15_INDEX_Msk 0xE00UL
#define ETH_SCREENING_TYPE_2_REGISTER_15_ETHERTYPE_ENABLE_Pos 12UL
#define ETH_SCREENING_TYPE_2_REGISTER_15_ETHERTYPE_ENABLE_Msk 0x1000UL
#define ETH_SCREENING_TYPE_2_REGISTER_15_COMPARE_A_Pos 13UL
#define ETH_SCREENING_TYPE_2_REGISTER_15_COMPARE_A_Msk 0x3E000UL
#define ETH_SCREENING_TYPE_2_REGISTER_15_COMPARE_A_ENABLE_Pos 18UL
#define ETH_SCREENING_TYPE_2_REGISTER_15_COMPARE_A_ENABLE_Msk 0x40000UL
#define ETH_SCREENING_TYPE_2_REGISTER_15_COMPARE_B_Pos 19UL
#define ETH_SCREENING_TYPE_2_REGISTER_15_COMPARE_B_Msk 0xF80000UL
#define ETH_SCREENING_TYPE_2_REGISTER_15_COMPARE_B_ENABLE_Pos 24UL
#define ETH_SCREENING_TYPE_2_REGISTER_15_COMPARE_B_ENABLE_Msk 0x1000000UL
#define ETH_SCREENING_TYPE_2_REGISTER_15_COMPARE_C_Pos 25UL
#define ETH_SCREENING_TYPE_2_REGISTER_15_COMPARE_C_Msk 0x3E000000UL
#define ETH_SCREENING_TYPE_2_REGISTER_15_COMPARE_C_ENABLE_Pos 30UL
#define ETH_SCREENING_TYPE_2_REGISTER_15_COMPARE_C_ENABLE_Msk 0x40000000UL
#define ETH_SCREENING_TYPE_2_REGISTER_15_RESERVED_31_Pos 31UL
#define ETH_SCREENING_TYPE_2_REGISTER_15_RESERVED_31_Msk 0x80000000UL
/* ETH.TX_SCHED_CTRL */
#define ETH_TX_SCHED_CTRL_TX_SCHED_Q0_Pos       0UL
#define ETH_TX_SCHED_CTRL_TX_SCHED_Q0_Msk       0x3UL
#define ETH_TX_SCHED_CTRL_TX_SCHED_Q1_Pos       2UL
#define ETH_TX_SCHED_CTRL_TX_SCHED_Q1_Msk       0xCUL
#define ETH_TX_SCHED_CTRL_TX_SCHED_Q2_Pos       4UL
#define ETH_TX_SCHED_CTRL_TX_SCHED_Q2_Msk       0x30UL
#define ETH_TX_SCHED_CTRL_TX_SCHED_Q3_Pos       6UL
#define ETH_TX_SCHED_CTRL_TX_SCHED_Q3_Msk       0xC0UL
#define ETH_TX_SCHED_CTRL_REMOVED_31_8_Pos      8UL
#define ETH_TX_SCHED_CTRL_REMOVED_31_8_Msk      0xFFFFFF00UL
/* ETH.BW_RATE_LIMIT_Q0TO3 */
#define ETH_BW_RATE_LIMIT_Q0TO3_DWRR_ETS_WEIGHT_Q0_Pos 0UL
#define ETH_BW_RATE_LIMIT_Q0TO3_DWRR_ETS_WEIGHT_Q0_Msk 0xFFUL
#define ETH_BW_RATE_LIMIT_Q0TO3_DWRR_ETS_WEIGHT_Q1_Pos 8UL
#define ETH_BW_RATE_LIMIT_Q0TO3_DWRR_ETS_WEIGHT_Q1_Msk 0xFF00UL
#define ETH_BW_RATE_LIMIT_Q0TO3_DWRR_ETS_WEIGHT_Q2_Pos 16UL
#define ETH_BW_RATE_LIMIT_Q0TO3_DWRR_ETS_WEIGHT_Q2_Msk 0xFF0000UL
#define ETH_BW_RATE_LIMIT_Q0TO3_DWRR_ETS_WEIGHT_Q3_Pos 24UL
#define ETH_BW_RATE_LIMIT_Q0TO3_DWRR_ETS_WEIGHT_Q3_Msk 0xFF000000UL
/* ETH.BW_RATE_LIMIT_Q4TO7 */
#define ETH_BW_RATE_LIMIT_Q4TO7_REMOVED_31_0_Pos 0UL
#define ETH_BW_RATE_LIMIT_Q4TO7_REMOVED_31_0_Msk 0xFFFFFFFFUL
/* ETH.BW_RATE_LIMIT_Q8TO11 */
#define ETH_BW_RATE_LIMIT_Q8TO11_REMOVED_31_0_Pos 0UL
#define ETH_BW_RATE_LIMIT_Q8TO11_REMOVED_31_0_Msk 0xFFFFFFFFUL
/* ETH.BW_RATE_LIMIT_Q12TO15 */
#define ETH_BW_RATE_LIMIT_Q12TO15_REMOVED_31_0_Pos 0UL
#define ETH_BW_RATE_LIMIT_Q12TO15_REMOVED_31_0_Msk 0xFFFFFFFFUL
/* ETH.TX_Q_SEG_ALLOC_Q0TO7 */
#define ETH_TX_Q_SEG_ALLOC_Q0TO7_SEGMENT_ALLOC_Q0_Pos 0UL
#define ETH_TX_Q_SEG_ALLOC_Q0TO7_SEGMENT_ALLOC_Q0_Msk 0x7UL
#define ETH_TX_Q_SEG_ALLOC_Q0TO7_RESERVED_3_3_Pos 3UL
#define ETH_TX_Q_SEG_ALLOC_Q0TO7_RESERVED_3_3_Msk 0x8UL
#define ETH_TX_Q_SEG_ALLOC_Q0TO7_SEGMENT_ALLOC_Q1_Pos 4UL
#define ETH_TX_Q_SEG_ALLOC_Q0TO7_SEGMENT_ALLOC_Q1_Msk 0x70UL
#define ETH_TX_Q_SEG_ALLOC_Q0TO7_RESERVED_7_7_Pos 7UL
#define ETH_TX_Q_SEG_ALLOC_Q0TO7_RESERVED_7_7_Msk 0x80UL
#define ETH_TX_Q_SEG_ALLOC_Q0TO7_SEGMENT_ALLOC_Q2_Pos 8UL
#define ETH_TX_Q_SEG_ALLOC_Q0TO7_SEGMENT_ALLOC_Q2_Msk 0x700UL
#define ETH_TX_Q_SEG_ALLOC_Q0TO7_RESERVED_11_11_Pos 11UL
#define ETH_TX_Q_SEG_ALLOC_Q0TO7_RESERVED_11_11_Msk 0x800UL
#define ETH_TX_Q_SEG_ALLOC_Q0TO7_REMOVED_14_12_Pos 12UL
#define ETH_TX_Q_SEG_ALLOC_Q0TO7_REMOVED_14_12_Msk 0x7000UL
#define ETH_TX_Q_SEG_ALLOC_Q0TO7_RESERVED_15_15_Pos 15UL
#define ETH_TX_Q_SEG_ALLOC_Q0TO7_RESERVED_15_15_Msk 0x8000UL
#define ETH_TX_Q_SEG_ALLOC_Q0TO7_REMOVED_18_16_Pos 16UL
#define ETH_TX_Q_SEG_ALLOC_Q0TO7_REMOVED_18_16_Msk 0x70000UL
#define ETH_TX_Q_SEG_ALLOC_Q0TO7_RESERVED_19_19_Pos 19UL
#define ETH_TX_Q_SEG_ALLOC_Q0TO7_RESERVED_19_19_Msk 0x80000UL
#define ETH_TX_Q_SEG_ALLOC_Q0TO7_REMOVED_22_20_Pos 20UL
#define ETH_TX_Q_SEG_ALLOC_Q0TO7_REMOVED_22_20_Msk 0x700000UL
#define ETH_TX_Q_SEG_ALLOC_Q0TO7_RESERVED_23_Pos 23UL
#define ETH_TX_Q_SEG_ALLOC_Q0TO7_RESERVED_23_Msk 0x800000UL
#define ETH_TX_Q_SEG_ALLOC_Q0TO7_REMOVED_26_24_Pos 24UL
#define ETH_TX_Q_SEG_ALLOC_Q0TO7_REMOVED_26_24_Msk 0x7000000UL
#define ETH_TX_Q_SEG_ALLOC_Q0TO7_RESERVED_27_27_Pos 27UL
#define ETH_TX_Q_SEG_ALLOC_Q0TO7_RESERVED_27_27_Msk 0x8000000UL
#define ETH_TX_Q_SEG_ALLOC_Q0TO7_REMOVED_30_28_Pos 28UL
#define ETH_TX_Q_SEG_ALLOC_Q0TO7_REMOVED_30_28_Msk 0x70000000UL
#define ETH_TX_Q_SEG_ALLOC_Q0TO7_RESERVED_31_31_Pos 31UL
#define ETH_TX_Q_SEG_ALLOC_Q0TO7_RESERVED_31_31_Msk 0x80000000UL
/* ETH.TX_Q_SEG_ALLOC_Q8TO15 */
#define ETH_TX_Q_SEG_ALLOC_Q8TO15_REMOVED_31_0_Pos 0UL
#define ETH_TX_Q_SEG_ALLOC_Q8TO15_REMOVED_31_0_Msk 0xFFFFFFFFUL
/* ETH.RECEIVE_Q8_PTR */
#define ETH_RECEIVE_Q8_PTR_REMOVED_31_0_Pos     0UL
#define ETH_RECEIVE_Q8_PTR_REMOVED_31_0_Msk     0xFFFFFFFFUL
/* ETH.RECEIVE_Q15_PTR */
#define ETH_RECEIVE_Q15_PTR_REMOVED_31_0_Pos    0UL
#define ETH_RECEIVE_Q15_PTR_REMOVED_31_0_Msk    0xFFFFFFFFUL
/* ETH.DMA_RXBUF_SIZE_Q8 */
#define ETH_DMA_RXBUF_SIZE_Q8_REMOVED_31_0_Pos  0UL
#define ETH_DMA_RXBUF_SIZE_Q8_REMOVED_31_0_Msk  0xFFFFFFFFUL
/* ETH.DMA_RXBUF_SIZE_Q15 */
#define ETH_DMA_RXBUF_SIZE_Q15_REMOVED_31_0_Pos 0UL
#define ETH_DMA_RXBUF_SIZE_Q15_REMOVED_31_0_Msk 0xFFFFFFFFUL
/* ETH.INT_Q1_ENABLE */
#define ETH_INT_Q1_ENABLE_ENABLE_RECEIVE_COMPLETE_INTERRUPT_Pos 1UL
#define ETH_INT_Q1_ENABLE_ENABLE_RECEIVE_COMPLETE_INTERRUPT_Msk 0x2UL
#define ETH_INT_Q1_ENABLE_ENABLE_RX_USED_BIT_READ_INTERRUPT_Pos 2UL
#define ETH_INT_Q1_ENABLE_ENABLE_RX_USED_BIT_READ_INTERRUPT_Msk 0x4UL
#define ETH_INT_Q1_ENABLE_ENABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT_Pos 5UL
#define ETH_INT_Q1_ENABLE_ENABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT_Msk 0x20UL
#define ETH_INT_Q1_ENABLE_ENABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT_Pos 6UL
#define ETH_INT_Q1_ENABLE_ENABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT_Msk 0x40UL
#define ETH_INT_Q1_ENABLE_ENABLE_TRANSMIT_COMPLETE_INTERRUPT_Pos 7UL
#define ETH_INT_Q1_ENABLE_ENABLE_TRANSMIT_COMPLETE_INTERRUPT_Msk 0x80UL
#define ETH_INT_Q1_ENABLE_ENABLE_RESP_NOT_OK_INTERRUPT_Pos 11UL
#define ETH_INT_Q1_ENABLE_ENABLE_RESP_NOT_OK_INTERRUPT_Msk 0x800UL
/* ETH.INT_Q2_ENABLE */
#define ETH_INT_Q2_ENABLE_ENABLE_RECEIVE_COMPLETE_INTERRUPT_Pos 1UL
#define ETH_INT_Q2_ENABLE_ENABLE_RECEIVE_COMPLETE_INTERRUPT_Msk 0x2UL
#define ETH_INT_Q2_ENABLE_ENABLE_RX_USED_BIT_READ_INTERRUPT_Pos 2UL
#define ETH_INT_Q2_ENABLE_ENABLE_RX_USED_BIT_READ_INTERRUPT_Msk 0x4UL
#define ETH_INT_Q2_ENABLE_ENABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT_Pos 5UL
#define ETH_INT_Q2_ENABLE_ENABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT_Msk 0x20UL
#define ETH_INT_Q2_ENABLE_ENABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT_Pos 6UL
#define ETH_INT_Q2_ENABLE_ENABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT_Msk 0x40UL
#define ETH_INT_Q2_ENABLE_ENABLE_TRANSMIT_COMPLETE_INTERRUPT_Pos 7UL
#define ETH_INT_Q2_ENABLE_ENABLE_TRANSMIT_COMPLETE_INTERRUPT_Msk 0x80UL
#define ETH_INT_Q2_ENABLE_ENABLE_RESP_NOT_OK_INTERRUPT_Pos 11UL
#define ETH_INT_Q2_ENABLE_ENABLE_RESP_NOT_OK_INTERRUPT_Msk 0x800UL
/* ETH.INT_Q3_ENABLE */
#define ETH_INT_Q3_ENABLE_REMOVED_31_0_Pos      0UL
#define ETH_INT_Q3_ENABLE_REMOVED_31_0_Msk      0xFFFFFFFFUL
/* ETH.INT_Q7_ENABLE */
#define ETH_INT_Q7_ENABLE_REMOVED_31_0_Pos      0UL
#define ETH_INT_Q7_ENABLE_REMOVED_31_0_Msk      0xFFFFFFFFUL
/* ETH.INT_Q1_DISABLE */
#define ETH_INT_Q1_DISABLE_DISABLE_RECEIVE_COMPLETE_INTERRUPT_Pos 1UL
#define ETH_INT_Q1_DISABLE_DISABLE_RECEIVE_COMPLETE_INTERRUPT_Msk 0x2UL
#define ETH_INT_Q1_DISABLE_DISABLE_RX_USED_BIT_READ_INTERRUPT_Pos 2UL
#define ETH_INT_Q1_DISABLE_DISABLE_RX_USED_BIT_READ_INTERRUPT_Msk 0x4UL
#define ETH_INT_Q1_DISABLE_DISABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT_Pos 5UL
#define ETH_INT_Q1_DISABLE_DISABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT_Msk 0x20UL
#define ETH_INT_Q1_DISABLE_DISABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT_Pos 6UL
#define ETH_INT_Q1_DISABLE_DISABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT_Msk 0x40UL
#define ETH_INT_Q1_DISABLE_DISABLE_TRANSMIT_COMPLETE_INTERRUPT_Pos 7UL
#define ETH_INT_Q1_DISABLE_DISABLE_TRANSMIT_COMPLETE_INTERRUPT_Msk 0x80UL
#define ETH_INT_Q1_DISABLE_DISABLE_RESP_NOT_OK_INTERRUPT_Pos 11UL
#define ETH_INT_Q1_DISABLE_DISABLE_RESP_NOT_OK_INTERRUPT_Msk 0x800UL
/* ETH.INT_Q2_DISABLE */
#define ETH_INT_Q2_DISABLE_DISABLE_RECEIVE_COMPLETE_INTERRUPT_Pos 1UL
#define ETH_INT_Q2_DISABLE_DISABLE_RECEIVE_COMPLETE_INTERRUPT_Msk 0x2UL
#define ETH_INT_Q2_DISABLE_DISABLE_RX_USED_BIT_READ_INTERRUPT_Pos 2UL
#define ETH_INT_Q2_DISABLE_DISABLE_RX_USED_BIT_READ_INTERRUPT_Msk 0x4UL
#define ETH_INT_Q2_DISABLE_DISABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT_Pos 5UL
#define ETH_INT_Q2_DISABLE_DISABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT_Msk 0x20UL
#define ETH_INT_Q2_DISABLE_DISABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT_Pos 6UL
#define ETH_INT_Q2_DISABLE_DISABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT_Msk 0x40UL
#define ETH_INT_Q2_DISABLE_DISABLE_TRANSMIT_COMPLETE_INTERRUPT_Pos 7UL
#define ETH_INT_Q2_DISABLE_DISABLE_TRANSMIT_COMPLETE_INTERRUPT_Msk 0x80UL
#define ETH_INT_Q2_DISABLE_DISABLE_RESP_NOT_OK_INTERRUPT_Pos 11UL
#define ETH_INT_Q2_DISABLE_DISABLE_RESP_NOT_OK_INTERRUPT_Msk 0x800UL
/* ETH.INT_Q3_DISABLE */
#define ETH_INT_Q3_DISABLE_REMOVED_31_0_Pos     0UL
#define ETH_INT_Q3_DISABLE_REMOVED_31_0_Msk     0xFFFFFFFFUL
/* ETH.INT_Q7_DISABLE */
#define ETH_INT_Q7_DISABLE_REMOVED_31_0_Pos     0UL
#define ETH_INT_Q7_DISABLE_REMOVED_31_0_Msk     0xFFFFFFFFUL
/* ETH.INT_Q1_MASK */
#define ETH_INT_Q1_MASK_RECEIVE_COMPLETE_INTERRUPT_MASK_Pos 1UL
#define ETH_INT_Q1_MASK_RECEIVE_COMPLETE_INTERRUPT_MASK_Msk 0x2UL
#define ETH_INT_Q1_MASK_RX_USED_INTERRUPT_MASK_Pos 2UL
#define ETH_INT_Q1_MASK_RX_USED_INTERRUPT_MASK_Msk 0x4UL
#define ETH_INT_Q1_MASK_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT_MASK_Pos 5UL
#define ETH_INT_Q1_MASK_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT_MASK_Msk 0x20UL
#define ETH_INT_Q1_MASK_AMBA_ERROR_INTERRUPT_MASK_Pos 6UL
#define ETH_INT_Q1_MASK_AMBA_ERROR_INTERRUPT_MASK_Msk 0x40UL
#define ETH_INT_Q1_MASK_TRANSMIT_COMPLETE_INTERRUPT_MASK_Pos 7UL
#define ETH_INT_Q1_MASK_TRANSMIT_COMPLETE_INTERRUPT_MASK_Msk 0x80UL
#define ETH_INT_Q1_MASK_RESP_NOT_OK_INTERRUPT_MASK_Pos 11UL
#define ETH_INT_Q1_MASK_RESP_NOT_OK_INTERRUPT_MASK_Msk 0x800UL
/* ETH.INT_Q2_MASK */
#define ETH_INT_Q2_MASK_RECEIVE_COMPLETE_INTERRUPT_MASK_Pos 1UL
#define ETH_INT_Q2_MASK_RECEIVE_COMPLETE_INTERRUPT_MASK_Msk 0x2UL
#define ETH_INT_Q2_MASK_RX_USED_INTERRUPT_MASK_Pos 2UL
#define ETH_INT_Q2_MASK_RX_USED_INTERRUPT_MASK_Msk 0x4UL
#define ETH_INT_Q2_MASK_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT_MASK_Pos 5UL
#define ETH_INT_Q2_MASK_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT_MASK_Msk 0x20UL
#define ETH_INT_Q2_MASK_AMBA_ERROR_INTERRUPT_MASK_Pos 6UL
#define ETH_INT_Q2_MASK_AMBA_ERROR_INTERRUPT_MASK_Msk 0x40UL
#define ETH_INT_Q2_MASK_TRANSMIT_COMPLETE_INTERRUPT_MASK_Pos 7UL
#define ETH_INT_Q2_MASK_TRANSMIT_COMPLETE_INTERRUPT_MASK_Msk 0x80UL
#define ETH_INT_Q2_MASK_RESP_NOT_OK_INTERRUPT_MASK_Pos 11UL
#define ETH_INT_Q2_MASK_RESP_NOT_OK_INTERRUPT_MASK_Msk 0x800UL
/* ETH.INT_Q3_MASK */
#define ETH_INT_Q3_MASK_REMOVED_31_0_Pos        0UL
#define ETH_INT_Q3_MASK_REMOVED_31_0_Msk        0xFFFFFFFFUL
/* ETH.INT_Q7_MASK */
#define ETH_INT_Q7_MASK_REMOVED_31_0_Pos        0UL
#define ETH_INT_Q7_MASK_REMOVED_31_0_Msk        0xFFFFFFFFUL
/* ETH.INT_Q8_ENABLE */
#define ETH_INT_Q8_ENABLE_REMOVED_31_0_Pos      0UL
#define ETH_INT_Q8_ENABLE_REMOVED_31_0_Msk      0xFFFFFFFFUL
/* ETH.INT_Q15_ENABLE */
#define ETH_INT_Q15_ENABLE_REMOVED_31_0_Pos     0UL
#define ETH_INT_Q15_ENABLE_REMOVED_31_0_Msk     0xFFFFFFFFUL
/* ETH.INT_Q8_DISABLE */
#define ETH_INT_Q8_DISABLE_REMOVED_31_0_Pos     0UL
#define ETH_INT_Q8_DISABLE_REMOVED_31_0_Msk     0xFFFFFFFFUL
/* ETH.INT_Q15_DISABLE */
#define ETH_INT_Q15_DISABLE_REMOVED_31_0_Pos    0UL
#define ETH_INT_Q15_DISABLE_REMOVED_31_0_Msk    0xFFFFFFFFUL
/* ETH.INT_Q8_MASK */
#define ETH_INT_Q8_MASK_REMOVED_31_0_Pos        0UL
#define ETH_INT_Q8_MASK_REMOVED_31_0_Msk        0xFFFFFFFFUL
/* ETH.INT_Q15_MASK */
#define ETH_INT_Q15_MASK_REMOVED_31_0_Pos       0UL
#define ETH_INT_Q15_MASK_REMOVED_31_0_Msk       0xFFFFFFFFUL
/* ETH.SCREENING_TYPE_2_ETHERTYPE_REG_0 */
#define ETH_SCREENING_TYPE_2_ETHERTYPE_REG_0_COMPARE_VALUE_Pos 0UL
#define ETH_SCREENING_TYPE_2_ETHERTYPE_REG_0_COMPARE_VALUE_Msk 0xFFFFUL
#define ETH_SCREENING_TYPE_2_ETHERTYPE_REG_0_RESERVED_31_16_Pos 16UL
#define ETH_SCREENING_TYPE_2_ETHERTYPE_REG_0_RESERVED_31_16_Msk 0xFFFF0000UL
/* ETH.SCREENING_TYPE_2_ETHERTYPE_REG_1 */
#define ETH_SCREENING_TYPE_2_ETHERTYPE_REG_1_COMPARE_VALUE_Pos 0UL
#define ETH_SCREENING_TYPE_2_ETHERTYPE_REG_1_COMPARE_VALUE_Msk 0xFFFFUL
#define ETH_SCREENING_TYPE_2_ETHERTYPE_REG_1_RESERVED_31_16_Pos 16UL
#define ETH_SCREENING_TYPE_2_ETHERTYPE_REG_1_RESERVED_31_16_Msk 0xFFFF0000UL
/* ETH.SCREENING_TYPE_2_ETHERTYPE_REG_2 */
#define ETH_SCREENING_TYPE_2_ETHERTYPE_REG_2_COMPARE_VALUE_Pos 0UL
#define ETH_SCREENING_TYPE_2_ETHERTYPE_REG_2_COMPARE_VALUE_Msk 0xFFFFUL
#define ETH_SCREENING_TYPE_2_ETHERTYPE_REG_2_RESERVED_31_16_Pos 16UL
#define ETH_SCREENING_TYPE_2_ETHERTYPE_REG_2_RESERVED_31_16_Msk 0xFFFF0000UL
/* ETH.SCREENING_TYPE_2_ETHERTYPE_REG_3 */
#define ETH_SCREENING_TYPE_2_ETHERTYPE_REG_3_COMPARE_VALUE_Pos 0UL
#define ETH_SCREENING_TYPE_2_ETHERTYPE_REG_3_COMPARE_VALUE_Msk 0xFFFFUL
#define ETH_SCREENING_TYPE_2_ETHERTYPE_REG_3_RESERVED_31_16_Pos 16UL
#define ETH_SCREENING_TYPE_2_ETHERTYPE_REG_3_RESERVED_31_16_Msk 0xFFFF0000UL
/* ETH.SCREENING_TYPE_2_ETHERTYPE_REG_4 */
#define ETH_SCREENING_TYPE_2_ETHERTYPE_REG_4_COMPARE_VALUE_Pos 0UL
#define ETH_SCREENING_TYPE_2_ETHERTYPE_REG_4_COMPARE_VALUE_Msk 0xFFFFUL
#define ETH_SCREENING_TYPE_2_ETHERTYPE_REG_4_RESERVED_31_16_Pos 16UL
#define ETH_SCREENING_TYPE_2_ETHERTYPE_REG_4_RESERVED_31_16_Msk 0xFFFF0000UL
/* ETH.SCREENING_TYPE_2_ETHERTYPE_REG_5 */
#define ETH_SCREENING_TYPE_2_ETHERTYPE_REG_5_COMPARE_VALUE_Pos 0UL
#define ETH_SCREENING_TYPE_2_ETHERTYPE_REG_5_COMPARE_VALUE_Msk 0xFFFFUL
#define ETH_SCREENING_TYPE_2_ETHERTYPE_REG_5_RESERVED_31_16_Pos 16UL
#define ETH_SCREENING_TYPE_2_ETHERTYPE_REG_5_RESERVED_31_16_Msk 0xFFFF0000UL
/* ETH.SCREENING_TYPE_2_ETHERTYPE_REG_6 */
#define ETH_SCREENING_TYPE_2_ETHERTYPE_REG_6_COMPARE_VALUE_Pos 0UL
#define ETH_SCREENING_TYPE_2_ETHERTYPE_REG_6_COMPARE_VALUE_Msk 0xFFFFUL
#define ETH_SCREENING_TYPE_2_ETHERTYPE_REG_6_RESERVED_31_16_Pos 16UL
#define ETH_SCREENING_TYPE_2_ETHERTYPE_REG_6_RESERVED_31_16_Msk 0xFFFF0000UL
/* ETH.SCREENING_TYPE_2_ETHERTYPE_REG_7 */
#define ETH_SCREENING_TYPE_2_ETHERTYPE_REG_7_COMPARE_VALUE_Pos 0UL
#define ETH_SCREENING_TYPE_2_ETHERTYPE_REG_7_COMPARE_VALUE_Msk 0xFFFFUL
#define ETH_SCREENING_TYPE_2_ETHERTYPE_REG_7_RESERVED_31_16_Pos 16UL
#define ETH_SCREENING_TYPE_2_ETHERTYPE_REG_7_RESERVED_31_16_Msk 0xFFFF0000UL
/* ETH.TYPE2_COMPARE_0_WORD_0 */
#define ETH_TYPE2_COMPARE_0_WORD_0_MASK_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_0_WORD_0_MASK_VALUE_Msk 0xFFFFUL
#define ETH_TYPE2_COMPARE_0_WORD_0_COMPARE_VALUE_TYPE2_Pos 16UL
#define ETH_TYPE2_COMPARE_0_WORD_0_COMPARE_VALUE_TYPE2_Msk 0xFFFF0000UL
/* ETH.TYPE2_COMPARE_0_WORD_1 */
#define ETH_TYPE2_COMPARE_0_WORD_1_OFFSET_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_0_WORD_1_OFFSET_VALUE_Msk 0x7FUL
#define ETH_TYPE2_COMPARE_0_WORD_1_COMPARE_OFFSET_Pos 7UL
#define ETH_TYPE2_COMPARE_0_WORD_1_COMPARE_OFFSET_Msk 0x180UL
#define ETH_TYPE2_COMPARE_0_WORD_1_DISABLE_MASK_Pos 9UL
#define ETH_TYPE2_COMPARE_0_WORD_1_DISABLE_MASK_Msk 0x200UL
#define ETH_TYPE2_COMPARE_0_WORD_1_RESERVED_31_10_Pos 10UL
#define ETH_TYPE2_COMPARE_0_WORD_1_RESERVED_31_10_Msk 0xFFFFFC00UL
/* ETH.TYPE2_COMPARE_1_WORD_0 */
#define ETH_TYPE2_COMPARE_1_WORD_0_MASK_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_1_WORD_0_MASK_VALUE_Msk 0xFFFFUL
#define ETH_TYPE2_COMPARE_1_WORD_0_COMPARE_VALUE_TYPE2_Pos 16UL
#define ETH_TYPE2_COMPARE_1_WORD_0_COMPARE_VALUE_TYPE2_Msk 0xFFFF0000UL
/* ETH.TYPE2_COMPARE_1_WORD_1 */
#define ETH_TYPE2_COMPARE_1_WORD_1_OFFSET_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_1_WORD_1_OFFSET_VALUE_Msk 0x7FUL
#define ETH_TYPE2_COMPARE_1_WORD_1_COMPARE_OFFSET_Pos 7UL
#define ETH_TYPE2_COMPARE_1_WORD_1_COMPARE_OFFSET_Msk 0x180UL
#define ETH_TYPE2_COMPARE_1_WORD_1_DISABLE_MASK_Pos 9UL
#define ETH_TYPE2_COMPARE_1_WORD_1_DISABLE_MASK_Msk 0x200UL
#define ETH_TYPE2_COMPARE_1_WORD_1_RESERVED_31_10_Pos 10UL
#define ETH_TYPE2_COMPARE_1_WORD_1_RESERVED_31_10_Msk 0xFFFFFC00UL
/* ETH.TYPE2_COMPARE_2_WORD_0 */
#define ETH_TYPE2_COMPARE_2_WORD_0_MASK_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_2_WORD_0_MASK_VALUE_Msk 0xFFFFUL
#define ETH_TYPE2_COMPARE_2_WORD_0_COMPARE_VALUE_TYPE2_Pos 16UL
#define ETH_TYPE2_COMPARE_2_WORD_0_COMPARE_VALUE_TYPE2_Msk 0xFFFF0000UL
/* ETH.TYPE2_COMPARE_2_WORD_1 */
#define ETH_TYPE2_COMPARE_2_WORD_1_OFFSET_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_2_WORD_1_OFFSET_VALUE_Msk 0x7FUL
#define ETH_TYPE2_COMPARE_2_WORD_1_COMPARE_OFFSET_Pos 7UL
#define ETH_TYPE2_COMPARE_2_WORD_1_COMPARE_OFFSET_Msk 0x180UL
#define ETH_TYPE2_COMPARE_2_WORD_1_DISABLE_MASK_Pos 9UL
#define ETH_TYPE2_COMPARE_2_WORD_1_DISABLE_MASK_Msk 0x200UL
#define ETH_TYPE2_COMPARE_2_WORD_1_RESERVED_31_10_Pos 10UL
#define ETH_TYPE2_COMPARE_2_WORD_1_RESERVED_31_10_Msk 0xFFFFFC00UL
/* ETH.TYPE2_COMPARE_3_WORD_0 */
#define ETH_TYPE2_COMPARE_3_WORD_0_MASK_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_3_WORD_0_MASK_VALUE_Msk 0xFFFFUL
#define ETH_TYPE2_COMPARE_3_WORD_0_COMPARE_VALUE_TYPE2_Pos 16UL
#define ETH_TYPE2_COMPARE_3_WORD_0_COMPARE_VALUE_TYPE2_Msk 0xFFFF0000UL
/* ETH.TYPE2_COMPARE_3_WORD_1 */
#define ETH_TYPE2_COMPARE_3_WORD_1_OFFSET_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_3_WORD_1_OFFSET_VALUE_Msk 0x7FUL
#define ETH_TYPE2_COMPARE_3_WORD_1_COMPARE_OFFSET_Pos 7UL
#define ETH_TYPE2_COMPARE_3_WORD_1_COMPARE_OFFSET_Msk 0x180UL
#define ETH_TYPE2_COMPARE_3_WORD_1_DISABLE_MASK_Pos 9UL
#define ETH_TYPE2_COMPARE_3_WORD_1_DISABLE_MASK_Msk 0x200UL
#define ETH_TYPE2_COMPARE_3_WORD_1_RESERVED_31_10_Pos 10UL
#define ETH_TYPE2_COMPARE_3_WORD_1_RESERVED_31_10_Msk 0xFFFFFC00UL
/* ETH.TYPE2_COMPARE_4_WORD_0 */
#define ETH_TYPE2_COMPARE_4_WORD_0_MASK_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_4_WORD_0_MASK_VALUE_Msk 0xFFFFUL
#define ETH_TYPE2_COMPARE_4_WORD_0_COMPARE_VALUE_TYPE2_Pos 16UL
#define ETH_TYPE2_COMPARE_4_WORD_0_COMPARE_VALUE_TYPE2_Msk 0xFFFF0000UL
/* ETH.TYPE2_COMPARE_4_WORD_1 */
#define ETH_TYPE2_COMPARE_4_WORD_1_OFFSET_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_4_WORD_1_OFFSET_VALUE_Msk 0x7FUL
#define ETH_TYPE2_COMPARE_4_WORD_1_COMPARE_OFFSET_Pos 7UL
#define ETH_TYPE2_COMPARE_4_WORD_1_COMPARE_OFFSET_Msk 0x180UL
#define ETH_TYPE2_COMPARE_4_WORD_1_DISABLE_MASK_Pos 9UL
#define ETH_TYPE2_COMPARE_4_WORD_1_DISABLE_MASK_Msk 0x200UL
#define ETH_TYPE2_COMPARE_4_WORD_1_RESERVED_31_10_Pos 10UL
#define ETH_TYPE2_COMPARE_4_WORD_1_RESERVED_31_10_Msk 0xFFFFFC00UL
/* ETH.TYPE2_COMPARE_5_WORD_0 */
#define ETH_TYPE2_COMPARE_5_WORD_0_MASK_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_5_WORD_0_MASK_VALUE_Msk 0xFFFFUL
#define ETH_TYPE2_COMPARE_5_WORD_0_COMPARE_VALUE_TYPE2_Pos 16UL
#define ETH_TYPE2_COMPARE_5_WORD_0_COMPARE_VALUE_TYPE2_Msk 0xFFFF0000UL
/* ETH.TYPE2_COMPARE_5_WORD_1 */
#define ETH_TYPE2_COMPARE_5_WORD_1_OFFSET_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_5_WORD_1_OFFSET_VALUE_Msk 0x7FUL
#define ETH_TYPE2_COMPARE_5_WORD_1_COMPARE_OFFSET_Pos 7UL
#define ETH_TYPE2_COMPARE_5_WORD_1_COMPARE_OFFSET_Msk 0x180UL
#define ETH_TYPE2_COMPARE_5_WORD_1_DISABLE_MASK_Pos 9UL
#define ETH_TYPE2_COMPARE_5_WORD_1_DISABLE_MASK_Msk 0x200UL
#define ETH_TYPE2_COMPARE_5_WORD_1_RESERVED_31_10_Pos 10UL
#define ETH_TYPE2_COMPARE_5_WORD_1_RESERVED_31_10_Msk 0xFFFFFC00UL
/* ETH.TYPE2_COMPARE_6_WORD_0 */
#define ETH_TYPE2_COMPARE_6_WORD_0_MASK_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_6_WORD_0_MASK_VALUE_Msk 0xFFFFUL
#define ETH_TYPE2_COMPARE_6_WORD_0_COMPARE_VALUE_TYPE2_Pos 16UL
#define ETH_TYPE2_COMPARE_6_WORD_0_COMPARE_VALUE_TYPE2_Msk 0xFFFF0000UL
/* ETH.TYPE2_COMPARE_6_WORD_1 */
#define ETH_TYPE2_COMPARE_6_WORD_1_OFFSET_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_6_WORD_1_OFFSET_VALUE_Msk 0x7FUL
#define ETH_TYPE2_COMPARE_6_WORD_1_COMPARE_OFFSET_Pos 7UL
#define ETH_TYPE2_COMPARE_6_WORD_1_COMPARE_OFFSET_Msk 0x180UL
#define ETH_TYPE2_COMPARE_6_WORD_1_DISABLE_MASK_Pos 9UL
#define ETH_TYPE2_COMPARE_6_WORD_1_DISABLE_MASK_Msk 0x200UL
#define ETH_TYPE2_COMPARE_6_WORD_1_RESERVED_31_10_Pos 10UL
#define ETH_TYPE2_COMPARE_6_WORD_1_RESERVED_31_10_Msk 0xFFFFFC00UL
/* ETH.TYPE2_COMPARE_7_WORD_0 */
#define ETH_TYPE2_COMPARE_7_WORD_0_MASK_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_7_WORD_0_MASK_VALUE_Msk 0xFFFFUL
#define ETH_TYPE2_COMPARE_7_WORD_0_COMPARE_VALUE_TYPE2_Pos 16UL
#define ETH_TYPE2_COMPARE_7_WORD_0_COMPARE_VALUE_TYPE2_Msk 0xFFFF0000UL
/* ETH.TYPE2_COMPARE_7_WORD_1 */
#define ETH_TYPE2_COMPARE_7_WORD_1_OFFSET_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_7_WORD_1_OFFSET_VALUE_Msk 0x7FUL
#define ETH_TYPE2_COMPARE_7_WORD_1_COMPARE_OFFSET_Pos 7UL
#define ETH_TYPE2_COMPARE_7_WORD_1_COMPARE_OFFSET_Msk 0x180UL
#define ETH_TYPE2_COMPARE_7_WORD_1_DISABLE_MASK_Pos 9UL
#define ETH_TYPE2_COMPARE_7_WORD_1_DISABLE_MASK_Msk 0x200UL
#define ETH_TYPE2_COMPARE_7_WORD_1_RESERVED_31_10_Pos 10UL
#define ETH_TYPE2_COMPARE_7_WORD_1_RESERVED_31_10_Msk 0xFFFFFC00UL
/* ETH.TYPE2_COMPARE_8_WORD_0 */
#define ETH_TYPE2_COMPARE_8_WORD_0_MASK_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_8_WORD_0_MASK_VALUE_Msk 0xFFFFUL
#define ETH_TYPE2_COMPARE_8_WORD_0_COMPARE_VALUE_TYPE2_Pos 16UL
#define ETH_TYPE2_COMPARE_8_WORD_0_COMPARE_VALUE_TYPE2_Msk 0xFFFF0000UL
/* ETH.TYPE2_COMPARE_8_WORD_1 */
#define ETH_TYPE2_COMPARE_8_WORD_1_OFFSET_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_8_WORD_1_OFFSET_VALUE_Msk 0x7FUL
#define ETH_TYPE2_COMPARE_8_WORD_1_COMPARE_OFFSET_Pos 7UL
#define ETH_TYPE2_COMPARE_8_WORD_1_COMPARE_OFFSET_Msk 0x180UL
#define ETH_TYPE2_COMPARE_8_WORD_1_DISABLE_MASK_Pos 9UL
#define ETH_TYPE2_COMPARE_8_WORD_1_DISABLE_MASK_Msk 0x200UL
#define ETH_TYPE2_COMPARE_8_WORD_1_RESERVED_31_10_Pos 10UL
#define ETH_TYPE2_COMPARE_8_WORD_1_RESERVED_31_10_Msk 0xFFFFFC00UL
/* ETH.TYPE2_COMPARE_9_WORD_0 */
#define ETH_TYPE2_COMPARE_9_WORD_0_MASK_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_9_WORD_0_MASK_VALUE_Msk 0xFFFFUL
#define ETH_TYPE2_COMPARE_9_WORD_0_COMPARE_VALUE_TYPE2_Pos 16UL
#define ETH_TYPE2_COMPARE_9_WORD_0_COMPARE_VALUE_TYPE2_Msk 0xFFFF0000UL
/* ETH.TYPE2_COMPARE_9_WORD_1 */
#define ETH_TYPE2_COMPARE_9_WORD_1_OFFSET_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_9_WORD_1_OFFSET_VALUE_Msk 0x7FUL
#define ETH_TYPE2_COMPARE_9_WORD_1_COMPARE_OFFSET_Pos 7UL
#define ETH_TYPE2_COMPARE_9_WORD_1_COMPARE_OFFSET_Msk 0x180UL
#define ETH_TYPE2_COMPARE_9_WORD_1_DISABLE_MASK_Pos 9UL
#define ETH_TYPE2_COMPARE_9_WORD_1_DISABLE_MASK_Msk 0x200UL
#define ETH_TYPE2_COMPARE_9_WORD_1_RESERVED_31_10_Pos 10UL
#define ETH_TYPE2_COMPARE_9_WORD_1_RESERVED_31_10_Msk 0xFFFFFC00UL
/* ETH.TYPE2_COMPARE_10_WORD_0 */
#define ETH_TYPE2_COMPARE_10_WORD_0_MASK_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_10_WORD_0_MASK_VALUE_Msk 0xFFFFUL
#define ETH_TYPE2_COMPARE_10_WORD_0_COMPARE_VALUE_TYPE2_Pos 16UL
#define ETH_TYPE2_COMPARE_10_WORD_0_COMPARE_VALUE_TYPE2_Msk 0xFFFF0000UL
/* ETH.TYPE2_COMPARE_10_WORD_1 */
#define ETH_TYPE2_COMPARE_10_WORD_1_OFFSET_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_10_WORD_1_OFFSET_VALUE_Msk 0x7FUL
#define ETH_TYPE2_COMPARE_10_WORD_1_COMPARE_OFFSET_Pos 7UL
#define ETH_TYPE2_COMPARE_10_WORD_1_COMPARE_OFFSET_Msk 0x180UL
#define ETH_TYPE2_COMPARE_10_WORD_1_DISABLE_MASK_Pos 9UL
#define ETH_TYPE2_COMPARE_10_WORD_1_DISABLE_MASK_Msk 0x200UL
#define ETH_TYPE2_COMPARE_10_WORD_1_RESERVED_31_10_Pos 10UL
#define ETH_TYPE2_COMPARE_10_WORD_1_RESERVED_31_10_Msk 0xFFFFFC00UL
/* ETH.TYPE2_COMPARE_11_WORD_0 */
#define ETH_TYPE2_COMPARE_11_WORD_0_MASK_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_11_WORD_0_MASK_VALUE_Msk 0xFFFFUL
#define ETH_TYPE2_COMPARE_11_WORD_0_COMPARE_VALUE_TYPE2_Pos 16UL
#define ETH_TYPE2_COMPARE_11_WORD_0_COMPARE_VALUE_TYPE2_Msk 0xFFFF0000UL
/* ETH.TYPE2_COMPARE_11_WORD_1 */
#define ETH_TYPE2_COMPARE_11_WORD_1_OFFSET_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_11_WORD_1_OFFSET_VALUE_Msk 0x7FUL
#define ETH_TYPE2_COMPARE_11_WORD_1_COMPARE_OFFSET_Pos 7UL
#define ETH_TYPE2_COMPARE_11_WORD_1_COMPARE_OFFSET_Msk 0x180UL
#define ETH_TYPE2_COMPARE_11_WORD_1_DISABLE_MASK_Pos 9UL
#define ETH_TYPE2_COMPARE_11_WORD_1_DISABLE_MASK_Msk 0x200UL
#define ETH_TYPE2_COMPARE_11_WORD_1_RESERVED_31_10_Pos 10UL
#define ETH_TYPE2_COMPARE_11_WORD_1_RESERVED_31_10_Msk 0xFFFFFC00UL
/* ETH.TYPE2_COMPARE_12_WORD_0 */
#define ETH_TYPE2_COMPARE_12_WORD_0_MASK_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_12_WORD_0_MASK_VALUE_Msk 0xFFFFUL
#define ETH_TYPE2_COMPARE_12_WORD_0_COMPARE_VALUE_TYPE2_Pos 16UL
#define ETH_TYPE2_COMPARE_12_WORD_0_COMPARE_VALUE_TYPE2_Msk 0xFFFF0000UL
/* ETH.TYPE2_COMPARE_12_WORD_1 */
#define ETH_TYPE2_COMPARE_12_WORD_1_OFFSET_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_12_WORD_1_OFFSET_VALUE_Msk 0x7FUL
#define ETH_TYPE2_COMPARE_12_WORD_1_COMPARE_OFFSET_Pos 7UL
#define ETH_TYPE2_COMPARE_12_WORD_1_COMPARE_OFFSET_Msk 0x180UL
#define ETH_TYPE2_COMPARE_12_WORD_1_DISABLE_MASK_Pos 9UL
#define ETH_TYPE2_COMPARE_12_WORD_1_DISABLE_MASK_Msk 0x200UL
#define ETH_TYPE2_COMPARE_12_WORD_1_RESERVED_31_10_Pos 10UL
#define ETH_TYPE2_COMPARE_12_WORD_1_RESERVED_31_10_Msk 0xFFFFFC00UL
/* ETH.TYPE2_COMPARE_13_WORD_0 */
#define ETH_TYPE2_COMPARE_13_WORD_0_MASK_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_13_WORD_0_MASK_VALUE_Msk 0xFFFFUL
#define ETH_TYPE2_COMPARE_13_WORD_0_COMPARE_VALUE_TYPE2_Pos 16UL
#define ETH_TYPE2_COMPARE_13_WORD_0_COMPARE_VALUE_TYPE2_Msk 0xFFFF0000UL
/* ETH.TYPE2_COMPARE_13_WORD_1 */
#define ETH_TYPE2_COMPARE_13_WORD_1_OFFSET_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_13_WORD_1_OFFSET_VALUE_Msk 0x7FUL
#define ETH_TYPE2_COMPARE_13_WORD_1_COMPARE_OFFSET_Pos 7UL
#define ETH_TYPE2_COMPARE_13_WORD_1_COMPARE_OFFSET_Msk 0x180UL
#define ETH_TYPE2_COMPARE_13_WORD_1_DISABLE_MASK_Pos 9UL
#define ETH_TYPE2_COMPARE_13_WORD_1_DISABLE_MASK_Msk 0x200UL
#define ETH_TYPE2_COMPARE_13_WORD_1_RESERVED_31_10_Pos 10UL
#define ETH_TYPE2_COMPARE_13_WORD_1_RESERVED_31_10_Msk 0xFFFFFC00UL
/* ETH.TYPE2_COMPARE_14_WORD_0 */
#define ETH_TYPE2_COMPARE_14_WORD_0_MASK_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_14_WORD_0_MASK_VALUE_Msk 0xFFFFUL
#define ETH_TYPE2_COMPARE_14_WORD_0_COMPARE_VALUE_TYPE2_Pos 16UL
#define ETH_TYPE2_COMPARE_14_WORD_0_COMPARE_VALUE_TYPE2_Msk 0xFFFF0000UL
/* ETH.TYPE2_COMPARE_14_WORD_1 */
#define ETH_TYPE2_COMPARE_14_WORD_1_OFFSET_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_14_WORD_1_OFFSET_VALUE_Msk 0x7FUL
#define ETH_TYPE2_COMPARE_14_WORD_1_COMPARE_OFFSET_Pos 7UL
#define ETH_TYPE2_COMPARE_14_WORD_1_COMPARE_OFFSET_Msk 0x180UL
#define ETH_TYPE2_COMPARE_14_WORD_1_DISABLE_MASK_Pos 9UL
#define ETH_TYPE2_COMPARE_14_WORD_1_DISABLE_MASK_Msk 0x200UL
#define ETH_TYPE2_COMPARE_14_WORD_1_RESERVED_31_10_Pos 10UL
#define ETH_TYPE2_COMPARE_14_WORD_1_RESERVED_31_10_Msk 0xFFFFFC00UL
/* ETH.TYPE2_COMPARE_15_WORD_0 */
#define ETH_TYPE2_COMPARE_15_WORD_0_MASK_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_15_WORD_0_MASK_VALUE_Msk 0xFFFFUL
#define ETH_TYPE2_COMPARE_15_WORD_0_COMPARE_VALUE_TYPE2_Pos 16UL
#define ETH_TYPE2_COMPARE_15_WORD_0_COMPARE_VALUE_TYPE2_Msk 0xFFFF0000UL
/* ETH.TYPE2_COMPARE_15_WORD_1 */
#define ETH_TYPE2_COMPARE_15_WORD_1_OFFSET_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_15_WORD_1_OFFSET_VALUE_Msk 0x7FUL
#define ETH_TYPE2_COMPARE_15_WORD_1_COMPARE_OFFSET_Pos 7UL
#define ETH_TYPE2_COMPARE_15_WORD_1_COMPARE_OFFSET_Msk 0x180UL
#define ETH_TYPE2_COMPARE_15_WORD_1_DISABLE_MASK_Pos 9UL
#define ETH_TYPE2_COMPARE_15_WORD_1_DISABLE_MASK_Msk 0x200UL
#define ETH_TYPE2_COMPARE_15_WORD_1_RESERVED_31_10_Pos 10UL
#define ETH_TYPE2_COMPARE_15_WORD_1_RESERVED_31_10_Msk 0xFFFFFC00UL
/* ETH.TYPE2_COMPARE_16_WORD_0 */
#define ETH_TYPE2_COMPARE_16_WORD_0_MASK_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_16_WORD_0_MASK_VALUE_Msk 0xFFFFUL
#define ETH_TYPE2_COMPARE_16_WORD_0_COMPARE_VALUE_TYPE2_Pos 16UL
#define ETH_TYPE2_COMPARE_16_WORD_0_COMPARE_VALUE_TYPE2_Msk 0xFFFF0000UL
/* ETH.TYPE2_COMPARE_16_WORD_1 */
#define ETH_TYPE2_COMPARE_16_WORD_1_OFFSET_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_16_WORD_1_OFFSET_VALUE_Msk 0x7FUL
#define ETH_TYPE2_COMPARE_16_WORD_1_COMPARE_OFFSET_Pos 7UL
#define ETH_TYPE2_COMPARE_16_WORD_1_COMPARE_OFFSET_Msk 0x180UL
#define ETH_TYPE2_COMPARE_16_WORD_1_DISABLE_MASK_Pos 9UL
#define ETH_TYPE2_COMPARE_16_WORD_1_DISABLE_MASK_Msk 0x200UL
#define ETH_TYPE2_COMPARE_16_WORD_1_RESERVED_31_10_Pos 10UL
#define ETH_TYPE2_COMPARE_16_WORD_1_RESERVED_31_10_Msk 0xFFFFFC00UL
/* ETH.TYPE2_COMPARE_17_WORD_0 */
#define ETH_TYPE2_COMPARE_17_WORD_0_MASK_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_17_WORD_0_MASK_VALUE_Msk 0xFFFFUL
#define ETH_TYPE2_COMPARE_17_WORD_0_COMPARE_VALUE_TYPE2_Pos 16UL
#define ETH_TYPE2_COMPARE_17_WORD_0_COMPARE_VALUE_TYPE2_Msk 0xFFFF0000UL
/* ETH.TYPE2_COMPARE_17_WORD_1 */
#define ETH_TYPE2_COMPARE_17_WORD_1_OFFSET_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_17_WORD_1_OFFSET_VALUE_Msk 0x7FUL
#define ETH_TYPE2_COMPARE_17_WORD_1_COMPARE_OFFSET_Pos 7UL
#define ETH_TYPE2_COMPARE_17_WORD_1_COMPARE_OFFSET_Msk 0x180UL
#define ETH_TYPE2_COMPARE_17_WORD_1_DISABLE_MASK_Pos 9UL
#define ETH_TYPE2_COMPARE_17_WORD_1_DISABLE_MASK_Msk 0x200UL
#define ETH_TYPE2_COMPARE_17_WORD_1_RESERVED_31_10_Pos 10UL
#define ETH_TYPE2_COMPARE_17_WORD_1_RESERVED_31_10_Msk 0xFFFFFC00UL
/* ETH.TYPE2_COMPARE_18_WORD_0 */
#define ETH_TYPE2_COMPARE_18_WORD_0_MASK_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_18_WORD_0_MASK_VALUE_Msk 0xFFFFUL
#define ETH_TYPE2_COMPARE_18_WORD_0_COMPARE_VALUE_TYPE2_Pos 16UL
#define ETH_TYPE2_COMPARE_18_WORD_0_COMPARE_VALUE_TYPE2_Msk 0xFFFF0000UL
/* ETH.TYPE2_COMPARE_18_WORD_1 */
#define ETH_TYPE2_COMPARE_18_WORD_1_OFFSET_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_18_WORD_1_OFFSET_VALUE_Msk 0x7FUL
#define ETH_TYPE2_COMPARE_18_WORD_1_COMPARE_OFFSET_Pos 7UL
#define ETH_TYPE2_COMPARE_18_WORD_1_COMPARE_OFFSET_Msk 0x180UL
#define ETH_TYPE2_COMPARE_18_WORD_1_DISABLE_MASK_Pos 9UL
#define ETH_TYPE2_COMPARE_18_WORD_1_DISABLE_MASK_Msk 0x200UL
#define ETH_TYPE2_COMPARE_18_WORD_1_RESERVED_31_10_Pos 10UL
#define ETH_TYPE2_COMPARE_18_WORD_1_RESERVED_31_10_Msk 0xFFFFFC00UL
/* ETH.TYPE2_COMPARE_19_WORD_0 */
#define ETH_TYPE2_COMPARE_19_WORD_0_MASK_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_19_WORD_0_MASK_VALUE_Msk 0xFFFFUL
#define ETH_TYPE2_COMPARE_19_WORD_0_COMPARE_VALUE_TYPE2_Pos 16UL
#define ETH_TYPE2_COMPARE_19_WORD_0_COMPARE_VALUE_TYPE2_Msk 0xFFFF0000UL
/* ETH.TYPE2_COMPARE_19_WORD_1 */
#define ETH_TYPE2_COMPARE_19_WORD_1_OFFSET_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_19_WORD_1_OFFSET_VALUE_Msk 0x7FUL
#define ETH_TYPE2_COMPARE_19_WORD_1_COMPARE_OFFSET_Pos 7UL
#define ETH_TYPE2_COMPARE_19_WORD_1_COMPARE_OFFSET_Msk 0x180UL
#define ETH_TYPE2_COMPARE_19_WORD_1_DISABLE_MASK_Pos 9UL
#define ETH_TYPE2_COMPARE_19_WORD_1_DISABLE_MASK_Msk 0x200UL
#define ETH_TYPE2_COMPARE_19_WORD_1_RESERVED_31_10_Pos 10UL
#define ETH_TYPE2_COMPARE_19_WORD_1_RESERVED_31_10_Msk 0xFFFFFC00UL
/* ETH.TYPE2_COMPARE_20_WORD_0 */
#define ETH_TYPE2_COMPARE_20_WORD_0_MASK_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_20_WORD_0_MASK_VALUE_Msk 0xFFFFUL
#define ETH_TYPE2_COMPARE_20_WORD_0_COMPARE_VALUE_TYPE2_Pos 16UL
#define ETH_TYPE2_COMPARE_20_WORD_0_COMPARE_VALUE_TYPE2_Msk 0xFFFF0000UL
/* ETH.TYPE2_COMPARE_20_WORD_1 */
#define ETH_TYPE2_COMPARE_20_WORD_1_OFFSET_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_20_WORD_1_OFFSET_VALUE_Msk 0x7FUL
#define ETH_TYPE2_COMPARE_20_WORD_1_COMPARE_OFFSET_Pos 7UL
#define ETH_TYPE2_COMPARE_20_WORD_1_COMPARE_OFFSET_Msk 0x180UL
#define ETH_TYPE2_COMPARE_20_WORD_1_DISABLE_MASK_Pos 9UL
#define ETH_TYPE2_COMPARE_20_WORD_1_DISABLE_MASK_Msk 0x200UL
#define ETH_TYPE2_COMPARE_20_WORD_1_RESERVED_31_10_Pos 10UL
#define ETH_TYPE2_COMPARE_20_WORD_1_RESERVED_31_10_Msk 0xFFFFFC00UL
/* ETH.TYPE2_COMPARE_21_WORD_0 */
#define ETH_TYPE2_COMPARE_21_WORD_0_MASK_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_21_WORD_0_MASK_VALUE_Msk 0xFFFFUL
#define ETH_TYPE2_COMPARE_21_WORD_0_COMPARE_VALUE_TYPE2_Pos 16UL
#define ETH_TYPE2_COMPARE_21_WORD_0_COMPARE_VALUE_TYPE2_Msk 0xFFFF0000UL
/* ETH.TYPE2_COMPARE_21_WORD_1 */
#define ETH_TYPE2_COMPARE_21_WORD_1_OFFSET_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_21_WORD_1_OFFSET_VALUE_Msk 0x7FUL
#define ETH_TYPE2_COMPARE_21_WORD_1_COMPARE_OFFSET_Pos 7UL
#define ETH_TYPE2_COMPARE_21_WORD_1_COMPARE_OFFSET_Msk 0x180UL
#define ETH_TYPE2_COMPARE_21_WORD_1_DISABLE_MASK_Pos 9UL
#define ETH_TYPE2_COMPARE_21_WORD_1_DISABLE_MASK_Msk 0x200UL
#define ETH_TYPE2_COMPARE_21_WORD_1_RESERVED_31_10_Pos 10UL
#define ETH_TYPE2_COMPARE_21_WORD_1_RESERVED_31_10_Msk 0xFFFFFC00UL
/* ETH.TYPE2_COMPARE_22_WORD_0 */
#define ETH_TYPE2_COMPARE_22_WORD_0_MASK_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_22_WORD_0_MASK_VALUE_Msk 0xFFFFUL
#define ETH_TYPE2_COMPARE_22_WORD_0_COMPARE_VALUE_TYPE2_Pos 16UL
#define ETH_TYPE2_COMPARE_22_WORD_0_COMPARE_VALUE_TYPE2_Msk 0xFFFF0000UL
/* ETH.TYPE2_COMPARE_22_WORD_1 */
#define ETH_TYPE2_COMPARE_22_WORD_1_OFFSET_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_22_WORD_1_OFFSET_VALUE_Msk 0x7FUL
#define ETH_TYPE2_COMPARE_22_WORD_1_COMPARE_OFFSET_Pos 7UL
#define ETH_TYPE2_COMPARE_22_WORD_1_COMPARE_OFFSET_Msk 0x180UL
#define ETH_TYPE2_COMPARE_22_WORD_1_DISABLE_MASK_Pos 9UL
#define ETH_TYPE2_COMPARE_22_WORD_1_DISABLE_MASK_Msk 0x200UL
#define ETH_TYPE2_COMPARE_22_WORD_1_RESERVED_31_10_Pos 10UL
#define ETH_TYPE2_COMPARE_22_WORD_1_RESERVED_31_10_Msk 0xFFFFFC00UL
/* ETH.TYPE2_COMPARE_23_WORD_0 */
#define ETH_TYPE2_COMPARE_23_WORD_0_MASK_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_23_WORD_0_MASK_VALUE_Msk 0xFFFFUL
#define ETH_TYPE2_COMPARE_23_WORD_0_COMPARE_VALUE_TYPE2_Pos 16UL
#define ETH_TYPE2_COMPARE_23_WORD_0_COMPARE_VALUE_TYPE2_Msk 0xFFFF0000UL
/* ETH.TYPE2_COMPARE_23_WORD_1 */
#define ETH_TYPE2_COMPARE_23_WORD_1_OFFSET_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_23_WORD_1_OFFSET_VALUE_Msk 0x7FUL
#define ETH_TYPE2_COMPARE_23_WORD_1_COMPARE_OFFSET_Pos 7UL
#define ETH_TYPE2_COMPARE_23_WORD_1_COMPARE_OFFSET_Msk 0x180UL
#define ETH_TYPE2_COMPARE_23_WORD_1_DISABLE_MASK_Pos 9UL
#define ETH_TYPE2_COMPARE_23_WORD_1_DISABLE_MASK_Msk 0x200UL
#define ETH_TYPE2_COMPARE_23_WORD_1_RESERVED_31_10_Pos 10UL
#define ETH_TYPE2_COMPARE_23_WORD_1_RESERVED_31_10_Msk 0xFFFFFC00UL
/* ETH.TYPE2_COMPARE_24_WORD_0 */
#define ETH_TYPE2_COMPARE_24_WORD_0_MASK_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_24_WORD_0_MASK_VALUE_Msk 0xFFFFUL
#define ETH_TYPE2_COMPARE_24_WORD_0_COMPARE_VALUE_TYPE2_Pos 16UL
#define ETH_TYPE2_COMPARE_24_WORD_0_COMPARE_VALUE_TYPE2_Msk 0xFFFF0000UL
/* ETH.TYPE2_COMPARE_24_WORD_1 */
#define ETH_TYPE2_COMPARE_24_WORD_1_OFFSET_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_24_WORD_1_OFFSET_VALUE_Msk 0x7FUL
#define ETH_TYPE2_COMPARE_24_WORD_1_COMPARE_OFFSET_Pos 7UL
#define ETH_TYPE2_COMPARE_24_WORD_1_COMPARE_OFFSET_Msk 0x180UL
#define ETH_TYPE2_COMPARE_24_WORD_1_DISABLE_MASK_Pos 9UL
#define ETH_TYPE2_COMPARE_24_WORD_1_DISABLE_MASK_Msk 0x200UL
#define ETH_TYPE2_COMPARE_24_WORD_1_RESERVED_31_10_Pos 10UL
#define ETH_TYPE2_COMPARE_24_WORD_1_RESERVED_31_10_Msk 0xFFFFFC00UL
/* ETH.TYPE2_COMPARE_25_WORD_0 */
#define ETH_TYPE2_COMPARE_25_WORD_0_MASK_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_25_WORD_0_MASK_VALUE_Msk 0xFFFFUL
#define ETH_TYPE2_COMPARE_25_WORD_0_COMPARE_VALUE_TYPE2_Pos 16UL
#define ETH_TYPE2_COMPARE_25_WORD_0_COMPARE_VALUE_TYPE2_Msk 0xFFFF0000UL
/* ETH.TYPE2_COMPARE_25_WORD_1 */
#define ETH_TYPE2_COMPARE_25_WORD_1_OFFSET_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_25_WORD_1_OFFSET_VALUE_Msk 0x7FUL
#define ETH_TYPE2_COMPARE_25_WORD_1_COMPARE_OFFSET_Pos 7UL
#define ETH_TYPE2_COMPARE_25_WORD_1_COMPARE_OFFSET_Msk 0x180UL
#define ETH_TYPE2_COMPARE_25_WORD_1_DISABLE_MASK_Pos 9UL
#define ETH_TYPE2_COMPARE_25_WORD_1_DISABLE_MASK_Msk 0x200UL
#define ETH_TYPE2_COMPARE_25_WORD_1_RESERVED_31_10_Pos 10UL
#define ETH_TYPE2_COMPARE_25_WORD_1_RESERVED_31_10_Msk 0xFFFFFC00UL
/* ETH.TYPE2_COMPARE_26_WORD_0 */
#define ETH_TYPE2_COMPARE_26_WORD_0_MASK_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_26_WORD_0_MASK_VALUE_Msk 0xFFFFUL
#define ETH_TYPE2_COMPARE_26_WORD_0_COMPARE_VALUE_TYPE2_Pos 16UL
#define ETH_TYPE2_COMPARE_26_WORD_0_COMPARE_VALUE_TYPE2_Msk 0xFFFF0000UL
/* ETH.TYPE2_COMPARE_26_WORD_1 */
#define ETH_TYPE2_COMPARE_26_WORD_1_OFFSET_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_26_WORD_1_OFFSET_VALUE_Msk 0x7FUL
#define ETH_TYPE2_COMPARE_26_WORD_1_COMPARE_OFFSET_Pos 7UL
#define ETH_TYPE2_COMPARE_26_WORD_1_COMPARE_OFFSET_Msk 0x180UL
#define ETH_TYPE2_COMPARE_26_WORD_1_DISABLE_MASK_Pos 9UL
#define ETH_TYPE2_COMPARE_26_WORD_1_DISABLE_MASK_Msk 0x200UL
#define ETH_TYPE2_COMPARE_26_WORD_1_RESERVED_31_10_Pos 10UL
#define ETH_TYPE2_COMPARE_26_WORD_1_RESERVED_31_10_Msk 0xFFFFFC00UL
/* ETH.TYPE2_COMPARE_27_WORD_0 */
#define ETH_TYPE2_COMPARE_27_WORD_0_MASK_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_27_WORD_0_MASK_VALUE_Msk 0xFFFFUL
#define ETH_TYPE2_COMPARE_27_WORD_0_COMPARE_VALUE_TYPE2_Pos 16UL
#define ETH_TYPE2_COMPARE_27_WORD_0_COMPARE_VALUE_TYPE2_Msk 0xFFFF0000UL
/* ETH.TYPE2_COMPARE_27_WORD_1 */
#define ETH_TYPE2_COMPARE_27_WORD_1_OFFSET_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_27_WORD_1_OFFSET_VALUE_Msk 0x7FUL
#define ETH_TYPE2_COMPARE_27_WORD_1_COMPARE_OFFSET_Pos 7UL
#define ETH_TYPE2_COMPARE_27_WORD_1_COMPARE_OFFSET_Msk 0x180UL
#define ETH_TYPE2_COMPARE_27_WORD_1_DISABLE_MASK_Pos 9UL
#define ETH_TYPE2_COMPARE_27_WORD_1_DISABLE_MASK_Msk 0x200UL
#define ETH_TYPE2_COMPARE_27_WORD_1_RESERVED_31_10_Pos 10UL
#define ETH_TYPE2_COMPARE_27_WORD_1_RESERVED_31_10_Msk 0xFFFFFC00UL
/* ETH.TYPE2_COMPARE_28_WORD_0 */
#define ETH_TYPE2_COMPARE_28_WORD_0_MASK_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_28_WORD_0_MASK_VALUE_Msk 0xFFFFUL
#define ETH_TYPE2_COMPARE_28_WORD_0_COMPARE_VALUE_TYPE2_Pos 16UL
#define ETH_TYPE2_COMPARE_28_WORD_0_COMPARE_VALUE_TYPE2_Msk 0xFFFF0000UL
/* ETH.TYPE2_COMPARE_28_WORD_1 */
#define ETH_TYPE2_COMPARE_28_WORD_1_OFFSET_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_28_WORD_1_OFFSET_VALUE_Msk 0x7FUL
#define ETH_TYPE2_COMPARE_28_WORD_1_COMPARE_OFFSET_Pos 7UL
#define ETH_TYPE2_COMPARE_28_WORD_1_COMPARE_OFFSET_Msk 0x180UL
#define ETH_TYPE2_COMPARE_28_WORD_1_DISABLE_MASK_Pos 9UL
#define ETH_TYPE2_COMPARE_28_WORD_1_DISABLE_MASK_Msk 0x200UL
#define ETH_TYPE2_COMPARE_28_WORD_1_RESERVED_31_10_Pos 10UL
#define ETH_TYPE2_COMPARE_28_WORD_1_RESERVED_31_10_Msk 0xFFFFFC00UL
/* ETH.TYPE2_COMPARE_29_WORD_0 */
#define ETH_TYPE2_COMPARE_29_WORD_0_MASK_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_29_WORD_0_MASK_VALUE_Msk 0xFFFFUL
#define ETH_TYPE2_COMPARE_29_WORD_0_COMPARE_VALUE_TYPE2_Pos 16UL
#define ETH_TYPE2_COMPARE_29_WORD_0_COMPARE_VALUE_TYPE2_Msk 0xFFFF0000UL
/* ETH.TYPE2_COMPARE_29_WORD_1 */
#define ETH_TYPE2_COMPARE_29_WORD_1_OFFSET_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_29_WORD_1_OFFSET_VALUE_Msk 0x7FUL
#define ETH_TYPE2_COMPARE_29_WORD_1_COMPARE_OFFSET_Pos 7UL
#define ETH_TYPE2_COMPARE_29_WORD_1_COMPARE_OFFSET_Msk 0x180UL
#define ETH_TYPE2_COMPARE_29_WORD_1_DISABLE_MASK_Pos 9UL
#define ETH_TYPE2_COMPARE_29_WORD_1_DISABLE_MASK_Msk 0x200UL
#define ETH_TYPE2_COMPARE_29_WORD_1_RESERVED_31_10_Pos 10UL
#define ETH_TYPE2_COMPARE_29_WORD_1_RESERVED_31_10_Msk 0xFFFFFC00UL
/* ETH.TYPE2_COMPARE_30_WORD_0 */
#define ETH_TYPE2_COMPARE_30_WORD_0_MASK_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_30_WORD_0_MASK_VALUE_Msk 0xFFFFUL
#define ETH_TYPE2_COMPARE_30_WORD_0_COMPARE_VALUE_TYPE2_Pos 16UL
#define ETH_TYPE2_COMPARE_30_WORD_0_COMPARE_VALUE_TYPE2_Msk 0xFFFF0000UL
/* ETH.TYPE2_COMPARE_30_WORD_1 */
#define ETH_TYPE2_COMPARE_30_WORD_1_OFFSET_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_30_WORD_1_OFFSET_VALUE_Msk 0x7FUL
#define ETH_TYPE2_COMPARE_30_WORD_1_COMPARE_OFFSET_Pos 7UL
#define ETH_TYPE2_COMPARE_30_WORD_1_COMPARE_OFFSET_Msk 0x180UL
#define ETH_TYPE2_COMPARE_30_WORD_1_DISABLE_MASK_Pos 9UL
#define ETH_TYPE2_COMPARE_30_WORD_1_DISABLE_MASK_Msk 0x200UL
#define ETH_TYPE2_COMPARE_30_WORD_1_RESERVED_31_10_Pos 10UL
#define ETH_TYPE2_COMPARE_30_WORD_1_RESERVED_31_10_Msk 0xFFFFFC00UL
/* ETH.TYPE2_COMPARE_31_WORD_0 */
#define ETH_TYPE2_COMPARE_31_WORD_0_MASK_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_31_WORD_0_MASK_VALUE_Msk 0xFFFFUL
#define ETH_TYPE2_COMPARE_31_WORD_0_COMPARE_VALUE_TYPE2_Pos 16UL
#define ETH_TYPE2_COMPARE_31_WORD_0_COMPARE_VALUE_TYPE2_Msk 0xFFFF0000UL
/* ETH.TYPE2_COMPARE_31_WORD_1 */
#define ETH_TYPE2_COMPARE_31_WORD_1_OFFSET_VALUE_Pos 0UL
#define ETH_TYPE2_COMPARE_31_WORD_1_OFFSET_VALUE_Msk 0x7FUL
#define ETH_TYPE2_COMPARE_31_WORD_1_COMPARE_OFFSET_Pos 7UL
#define ETH_TYPE2_COMPARE_31_WORD_1_COMPARE_OFFSET_Msk 0x180UL
#define ETH_TYPE2_COMPARE_31_WORD_1_DISABLE_MASK_Pos 9UL
#define ETH_TYPE2_COMPARE_31_WORD_1_DISABLE_MASK_Msk 0x200UL
#define ETH_TYPE2_COMPARE_31_WORD_1_RESERVED_31_10_Pos 10UL
#define ETH_TYPE2_COMPARE_31_WORD_1_RESERVED_31_10_Msk 0xFFFFFC00UL


#endif /* _CYIP_ETH_H_ */


/* [] END OF FILE */
