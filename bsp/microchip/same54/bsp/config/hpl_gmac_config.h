/* Auto-generated config file hpl_gmac_config.h */
#ifndef HPL_GMAC_CONFIG_H
#define HPL_GMAC_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

#include <peripheral_clk_config.h>

// <h> Network Control configuration

// <q> Enable LoopBack Local
// <i> Connects GTX to GRX, GTXEN to GRXDV and forces full duplex mode.
// <id> gmac_arch_ncr_lbl
#ifndef CONF_GMAC_NCR_LBL
#define CONF_GMAC_NCR_LBL 0
#endif

// <q> Management Port Enable
// <i> Enable the Management port
// <id> gmac_arch_ncr_mpe
#ifndef CONF_GMAC_NCR_MPE
#define CONF_GMAC_NCR_MPE 1
#endif

// <q> Enable write for Static Register
// <i> Make the statistics registers writable for functional test proposes.
// <id> gmac_arch_ncr_westat
#ifndef CONF_GMAC_NCR_WESTAT
#define CONF_GMAC_NCR_WESTAT 0
#endif

// <q> Enable Back pressure
// <i> If set in 10M or 100M half duplex mode, forces collisions on all received frames.
// <id> gmac_arch_ncr_bp
#ifndef CONF_GMAC_NCR_BP
#define CONF_GMAC_NCR_BP 0
#endif

// <q> Enable PFC Priority-based Pause Reception
// <i> Enables PFC negotiation and recognition of priority-based pause frames.
// <id> gmac_arch_ncr_enpbpr
#ifndef CONF_GMAC_NCR_ENPBPR
#define CONF_GMAC_NCR_ENPBPR 0
#endif

// <q> Enable PFC Priority-based Pause Frame
// <i> Takes the values stored in the Transmit PFC Pause Register.
// <id> gmac_arch_ncr_txpbpf
#ifndef CONF_GMAC_NCR_TXPBPF
#define CONF_GMAC_NCR_TXPBPF 0
#endif

// </h>

// <h> Network Configuration

// <q> 100Mbps Speed
// <i> Set to one to indicate 100 Mbps operation, zero for 10 Mbps.
// <id> gmac_arch_ncfgr_spd
#ifndef CONF_GMAC_NCFGR_SPD
#define CONF_GMAC_NCFGR_SPD 1
#endif

// <q> Enable Full Duplex
// <i> Enable Full duplex
// <id> gmac_arch_ncfgr_df
#ifndef CONF_GMAC_NCFGR_FD
#define CONF_GMAC_NCFGR_FD 1
#endif

// <q> Discard Non-VLAN Frames
// <i> Discard Non-VLAN Frames
// <id> gmac_arch_ncfgr_dnvlan
#ifndef CONF_GMAC_NCFGR_DNVLAN
#define CONF_GMAC_NCFGR_DNVLAN 0
#endif

// <q> Enable Jumbo Frame
// <i> Enable jumbo frames up to 10240 bytes to be accepted.
// <id> gmac_arch_ncfgr_jframe
#ifndef CONF_GMAC_NCFGR_JFRAME
#define CONF_GMAC_NCFGR_JFRAME 0
#endif

// <q> Copy All Frames
// <i> All valid frames will be accepted
// <id> gmac_arch_ncfgr_caf
#ifndef CONF_GMAC_NCFGR_CAF
#define CONF_GMAC_NCFGR_CAF 0
#endif

// <q> No broadcast
// <i> Frames addressed to the broadcast address of all ones will not be accepted.
// <id> gmac_arch_ncfgr_nbc
#ifndef CONF_GMAC_NCFGR_NBC
#define CONF_GMAC_NCFGR_NBC 0
#endif

// <q> Multicast Hash Enable
// <i> Multicast frames will be accepted when the 6-bit hash function of the destination address points to a bit that is set in the Hash Register.
// <id> gmac_arch_ncfgr_mtihen
#ifndef CONF_GMAC_NCFGR_MTIHEN
#define CONF_GMAC_NCFGR_MTIHEN 0
#endif

// <q> Unicast Hash Enable
// <i> Unicast frames will be accepted when the 6-bit hash function of the destination address points to a bit that is set in the Hash Register.
// <id> gmac_arch_ncfgr_unihen
#ifndef CONF_GMAC_NCFGR_UNIHEN
#define CONF_GMAC_NCFGR_UNIHEN 0
#endif

// <q> 1536 Maximum Frame Size
// <i> Accept frames up to 1536 bytes in length.
// <id> gmac_arch_ncfgr_maxfs
#ifndef CONF_GMAC_NCFGR_MAXFS
#define CONF_GMAC_NCFGR_MAXFS 1
#endif

// <q> Retry Test
// <i> Must be set to zero for normal operation. If set to one the backoff
// <i> between collisions will always be one slot time. Setting this bit to
// <i> one helps test the too many retries condition. Also used in the pause
// <i> frame tests to reduce the pause counter's decrement time from 512 bit
// <i> times, to every GRXCK cycle.
// <id> gmac_arch_ncfgr_rty
#ifndef CONF_GMAC_NCFGR_RTY
#define CONF_GMAC_NCFGR_RTY 0
#endif

// <q> Pause Enable
// <i> When set, transmission will pause if a non-zero 802.3 classic pause
// <i> frame is received and PFC has not been negotiated
// <id> gmac_arch_ncfgr_pen
#ifndef CONF_GMAC_NCFGR_PEN
#define CONF_GMAC_NCFGR_PEN 0
#endif

// <o> Receive Buffer Offset <0-3>
// <i> Indicates the number of bytes by which the received data is offset from
// <i> the start of the receive buffer.
// <id> gmac_arch_ncfgr_rxbufo
#ifndef CONF_GMAC_NCFGR_RXBUFO
#define CONF_GMAC_NCFGR_RXBUFO 0
#endif

// <q> Length Field Error Frame Discard
// <i> Setting this bit causes frames with a measured length shorter than the
// <i> extracted length field (as indicated by bytes 13 and 14 in a non-VLAN
// <i> tagged frame) to be discarded. This only applies to frames with a length
// <i> field less than 0x0600.
// <id> gmac_arch_ncfgr_lferd
#ifndef CONF_GMAC_NCFGR_LFERD
#define CONF_GMAC_NCFGR_LFERD 0
#endif

// <q> Remove FCS
// <i> Setting this bit will cause received frames to be written to memory
// <i> without their frame check sequence (last 4 bytes). The frame length
// <i> indicated will be reduced by four bytes in this mode.
// <id> gmac_arch_ncfgr_rfcs
#ifndef CONF_GMAC_NCFGR_RFCS
#define CONF_GMAC_NCFGR_RFCS 0
#endif

// <o> MDC Clock Division
// <i> Set according to MCK speed. These three bits determine the number MCK
// <i> will be divided by to generate Management Data Clock (MDC). For
// <i> conformance with the 802.3 specification, MDC must not exceed 2.5 MHz
// <i> (MDC is only active during MDIO read and write operations).
// <0=> 8
// <1=> 16
// <2=> 32
// <3=> 48
// <4=> 64
// <5=> 96
// <id> gmac_arch_ncfgr_clk
#ifndef CONF_GMAC_NCFGR_CLK
#define CONF_GMAC_NCFGR_CLK 4
#endif

/**
 * For conformance with the 802.3 specification, MDC must not exceed 2.5 MHz
 **/
#ifndef CONF_GMAC_MCK_FREQUENCY
#if CONF_GMAC_NCFGR_CLK == 0
#define CONF_GMAC_MCK_FREQUENCY (CONF_GMAC_FREQUENCY / 8)
#elif CONF_GMAC_NCFGR_CLK == 1
#define CONF_GMAC_MCK_FREQUENCY (CONF_GMAC_FREQUENCY / 16)
#elif CONF_GMAC_NCFGR_CLK == 2
#define CONF_GMAC_MCK_FREQUENCY (CONF_GMAC_FREQUENCY / 32)
#elif CONF_GMAC_NCFGR_CLK == 3
#define CONF_GMAC_MCK_FREQUENCY (CONF_GMAC_FREQUENCY / 48)
#elif CONF_GMAC_NCFGR_CLK == 4
#define CONF_GMAC_MCK_FREQUENCY (CONF_GMAC_FREQUENCY / 64)
#elif CONF_GMAC_NCFGR_CLK == 5
#define CONF_GMAC_MCK_FREQUENCY (CONF_GMAC_FREQUENCY / 96)
#endif
#endif

#if CONF_GMAC_MCK_FREQUENCY > 2500000
#warning For conformance with the 802.3 specification, MDC must not exceed 2.5 MHz
#endif
// <q> Disable Copy of Pause Frames
// <i> Set to one to prevent valid pause frames being copied to memory. When
// <i> set, pause frames are not copied to memory regardless of the state of
// <i> the Copy All Frames bit, whether a hash match is found or whether a
// <i> type ID match is identified. If a destination address match is found,
// <i> the pause frame will be copied to memory. Note that valid pause frames
// <i> received will still increment pause statistics and pause the
// <i> transmission of frames as required.
// <id> gmac_arch_ncfgr_dcpf
#ifndef CONF_GMAC_NCFGR_DCPF
#define CONF_GMAC_NCFGR_DCPF 0
#endif

// <q> Receive Checksum Offload Enable
// <i> When set, the receive checksum engine is enabled. Frames with bad IP,
// <i> TCP or UDP checksums are discarded.
// <id> gmac_arch_ncfgr_rxcoen
#ifndef CONF_GMAC_NCFGR_RXCOEN
#define CONF_GMAC_NCFGR_RXCOEN 0
#endif

// <q> Enable Frames Received in Half Duplex
// <i> Enable frames to be received in half-duplex mode while transmittinga.
// <id> gmac_arch_ncfgr_efrhd
#ifndef CONF_GMAC_NCFGR_EFRHD
#define CONF_GMAC_NCFGR_EFRHD 0
#endif

// <q> Ignore RX FCS
// <i> When set, frames with FCS/CRC errors will not be rejected. FCS error
// <i> statistics will still be collected for frames with bad FCS and FCS
// <i> status will be recorded in frame's DMA descriptor. For normal operation
// <i> this bit must be set to zero.
// <id> gmac_arch_ncfgr_irxfcs
#ifndef CONF_GMAC_NCFGR_IRXFCS
#define CONF_GMAC_NCFGR_IRXFCS 0
#endif

// <q> IP Stretch Enable
// <i> When set, the transmit IPG can be increased above 96 bit times depending
// <i> on the previous frame length using the IPG Stretch Register.
// <id> gmac_arch_ncfgr_ipgsen
#ifndef CONF_GMAC_NCFGR_IPGSEN
#define CONF_GMAC_NCFGR_IPGSEN 0
#endif

// <q> Receive Bad Preamble
// <i> When set, frames with non-standard preamble are not rejected.
// <id> gmac_arch_ncfgr_rxbp
#ifndef CONF_GMAC_NCFGR_RXBP
#define CONF_GMAC_NCFGR_RXBP 0
#endif

// <q> Ignore IPG GRXER
// <i> When set, GRXER has no effect on the GMAC's operation when GRXDV is low.
// <id> gmac_arch_ncfgr_irxer
#ifndef CONF_GMAC_NCFGR_IRXER
#define CONF_GMAC_NCFGR_IRXER 0
#endif

// </h>

// <e> MII Configuration
// <id> gmac_arch_mii_cfg

// <o> MII Mode
// <i> Select MII or RMII mode
// <0=> RMII
// <1=> MII
// <id> gmac_arch_ur_mii
#ifndef CONF_GMAC_ur_mii
#define CONF_GMAC_UR_MII 0
#endif

// <o> PHY Clause Operation
// <i> Chose which Clause operation will be used
// <0=>Clause 45 Operation
// <1=>Clause 22 Operation
// <id> gmac_arch_cltto
#ifndef CONF_GMAC_CLTTO
#define CONF_GMAC_CLTTO 1
#endif

// </e>

// <e> Stacked VLAN Processing
// <i> When enabled, the first VLAN tag in a received frame will only be
// <i> accepted if the VLAN type field is equal to the User defined VLAN Type,
// <i> OR equal to the standard VLAN type (0x8100). Note that the second VLAN
// <i> tag of a Stacked VLAN packet will only be matched correctly if its
// <i> VLAN_TYPE field equals 0x8100.
// <id> gmac_arch_svlan_enable
#ifndef CONF_GMAC_SVLAN_ENABLE
#define CONF_GMAC_SVLAN_ENABLE 0
#endif

// <o> User Defined VLAN Type <0x0-0xFFFF>
// <i> User defined VLAN TYPE
// <id> gmac_arch_svlan_type
#ifndef CONF_GMAC_SVLAN_TYPE
#define CONF_GMAC_SVLAN_TYPE 0x8100
#endif
// </e>

// <e> DMA Configuration
// <i> The GMAC DMA controller is connected to the MAC FIFO interface and
// <i> provides a scatter-gather type capability for packet data storage.
// <i> The DMA implements packet buffering where dual-port memories are used
// <i> to buffer multiple frames.
// <id> gmac_arch_dma_cfg
#ifndef CONF_GMAC_DMA_CFG
#define CONF_GMAC_DMACFG 1
#endif

// <o> Fixed Burst Length for DMA Data Operations
// <i> Selects the burst length to attempt to use on the AHB when transferring
// <i> frame data. Not used for DMA management operations and only used where
// <i> space and data size allow. Otherwise SINGLE type AHB transfers are used.
// <1=> Always use SINGLE AHB bursts
// <4=> Always use INCR4 AHB bursts
// <8=> Always use INCR8 AHB bursts
// <16=> Always use INCR16 AHB bursts
// <id> gmac_arch_dcfgr_fbldo
#ifndef CONF_GMAC_DCFGR_FBLDO
#define CONF_GMAC_DCFGR_FBLDO 4
#endif

// <q> Endian Swap Mode Enable for Management Descriptor Accesses
// <i> When set, selects swapped endianism for AHB transfers. When clear,
// <i> selects little endian mode.
// <id> gmac_arch_dcfgr_esma
#ifndef CONF_GMAC_DCFGR_ESMA
#define CONF_GMAC_DCFGR_ESMA 0
#endif

// <q> Endian Swap Mode Enable for Packet Data Accesses
// <i> When set, selects swapped endianism for AHB transfers. When clear,
// <i> selects little endian mode.
// <id> gmac_arch_dcfgr_espa
#ifndef CONF_GMAC_DCFGR_ESPA
#define CONF_GMAC_DCFGR_ESPA 0
#endif

// <o> Receiver Packet Buffer Memory Size Select
// <i> Select the receive packet buffer size
// <0=> 0.5 Kbytes
// <1=> 1 Kbytes
// <2=> 2 Kbytes
// <3=> 4 Kbytes
// <id> gmac_arch_dcfgr_rxbms
#ifndef CONF_GMAC_DCFGR_RXBMS
#define CONF_GMAC_DCFGR_RXBMS 3
#endif

// <o> Transmitter Packet Buffer Memory Size Select
// <i> Select the Transmitter packet buffer size
// <0=> 2 Kbytes
// <1=> 4 Kbytes
// <id> gmac_arch_dcfgr_txpbms
#ifndef CONF_GMAC_DCFGR_TXPBMS
#define CONF_GMAC_DCFGR_TXPBMS 1
#endif

// <q> Transmitter Checksum Generation Offload Enable
// <i> Transmitter IP, TCP and UDP checksum generation offload enable. When
// <i> set, the transmitter checksum generation engine is enabled to calculate
// <i> and substitute checksums for transmit frames. When clear, frame data is
// <i> unaffected
// <id> gmac_arch_dcfgr_txcoen
#ifndef CONF_GMAC_DCFGR_TXCOEN
#define CONF_GMAC_DCFGR_TXCOEN 0
#endif

// <o> DMA Receive Buffer Size <1-255>
// <i> DMA receive buffer size in AHB system memory. The value defined by these
// <i> bits determines the size of buffer to use in main AHB system memory when
// <i> writing received data. The value is defined in multiples of 64 bytes,
// <i> thus a value of 0x01 corresponds to buffers of 64 bytes, 0x02
// <i> corresponds to 128 bytes etc.
// <id> gmac_arch_dcfgr_drbs
#ifndef CONF_GMAC_DCFGR_DRBS
#define CONF_GMAC_DCFGR_DRBS 2
#endif

// <q> DMA Discard Received Packets
// <i> When set, the GMAC DMA will automatically discard receive packets from
// <i> the receiver packet buffer memory when no AHB resource is available.
// <i> When low, the received packets will remain to be stored in the SRAM
// <i> based packet buffer until AHB buffer resource next becomes available.
// <i> Note: packet buffer full store and forward mode should be enabled.
// <id> gmac_arch_dcfgr_ddrp
#ifndef CONF_GMAC_DCFGR_DDRP
#define CONF_GMAC_DCFGR_DDRP 0
#endif
// </e>

// <e> Advanced configuration
// <id> gmac_arch_adv_cfg
#ifndef CONF_GMAC_ADV_CFG
#define CONF_GMAC_ADV_CFG 1
#endif

// <o> Number of Transmit Buffer Descriptor <1-255>
// <i> Number of Transmit Buffer Descriptor
// <id> gmac_arch_txdescr_num
#ifndef CONF_GMAC_TXDESCR_NUM
#define CONF_GMAC_TXDESCR_NUM 2
#endif

// <o> Number of Receive Buffer Descriptor <1-255>
// <i> Number of Receive Buffer Descriptor
// <id> gmac_arch_rxdescr_num
#ifndef CONF_GMAC_RXDESCR_NUM
#define CONF_GMAC_RXDESCR_NUM 16
#endif

// <o> Byte size of Transmit Buffer <64-10240>
// <i> Byte size of buffer for each transmit buffer descriptor.
// <id> gmac_arch_txbuf_size
#ifndef CONF_GMAC_TXBUF_SIZE
#define CONF_GMAC_TXBUF_SIZE 1500
#endif

#ifndef CONF_GMAC_RXBUF_SIZE
#define CONF_GMAC_RXBUF_SIZE (CONF_GMAC_DCFGR_DRBS * 64)
#endif

// <e> Enable Transmit Partial Store and Forward
// <i> This allows for a reduced latency but there are performance implications.
// <id> gmac_arch_tpsf_en
#ifndef CONF_GMAC_TPSF_EN
#define CONF_GMAC_TPSF_EN 0
#endif

// <o> Watermark <20-4095>
// <i> Byte size of buffer for each transmit buffer descriptor.
// <id> gmac_arch_tpsf_wm
#ifndef CONF_GMAC_TPSF_WM
#define CONF_GMAC_TPSF_WM 100
#endif
// </e>

// <e> Enable Receive Partial Store and Forward
// <i> This allows for a reduced latency but there are performance implications.
// <id> gmac_arch_rpsf_en
#ifndef CONF_GMAC_RPSF_EN
#define CONF_GMAC_RPSF_EN 0
#endif

// <o> Watermark <20-4095>
// <i> Byte size of buffer for each transmite buffer descriptor.
// <id> gmac_arch_rpsf_wm
#ifndef CONF_GMAC_RPSF_WM
#define CONF_GMAC_RPSF_WM 100
#endif

// <o> IPG Stretch Multiple <0-15>
// <i> This value will multiplied with the previously transmitted frame length
// <i> (including preamble)
// <id> gmac_arch_ipgs_fl_mul
#ifndef CONF_GMAC_IPGS_FL_MUL
#define CONF_GMAC_IPGS_FL_MUL 1
#endif

// <o> IPG Stretch Divide <1-16>
// <i> Divide the frame length. If the resulting number is greater than 96 and
// <i> IP Stretch Enabled then the resulting number is used for the transmit
// <i> inter-packet-gap
// <id> gmac_arch_ipgs_fl_div
#ifndef CONF_GMAC_IPGS_FL_DIV
#define CONF_GMAC_IPGS_FL_DIV 1
#endif

// </e>

// </e>

// <<< end of configuration section >>>

#endif // HPL_GMAC_CONFIG_H
