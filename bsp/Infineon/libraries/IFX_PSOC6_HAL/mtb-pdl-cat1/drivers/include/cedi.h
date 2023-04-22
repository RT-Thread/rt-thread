 /**********************************************************************
 * Copyright (C) 2013-2015 Cadence Design Systems, Inc.- http://www.cadence.com
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
 **********************************************************************
 * WARNING: This file is auto-generated using api-generator utility.
 *          Do not edit it manually.
 **********************************************************************
 * Cadence Core Driver for the Cadence Ethernet MAC (EMAC) core. This
 * header file lists the API providing a HAL (hardware abstraction
 * layer) interface for the EMAC core, GEM_GXL  part no. IP7014
 **********************************************************************/

#ifndef _CEDI_H_
#define _CEDI_H_

#include "cdn_stdint.h"

/** @defgroup ConfigInfo  Configuration and Hardware Operation Information
 *  The following definitions specify the driver operation environment that
 *  is defined by hardware configuration or client code. These defines are
 *  located in the header file of the core driver.
 *  @{
 */

/**********************************************************************
* Defines
**********************************************************************/
/**
 * General config.
 * @xmlonly <defstofollow>4</defstofollow> REMOVE_ME @endxmlonly
 * Max number of Rx priority queues supported by driver
*/
#define    CEDI_MAX_RX_QUEUES (16)

/** Max number of Tx priority queues supported by driver */
#define    CEDI_MAX_TX_QUEUES (16)

/** Allows en/disabling of events on all priority queues */
#define    CEDI_ALL_QUEUES (255)

/** Max size of each Rx buffer descriptor list */
#define    CEDI_MAX_RBQ_LENGTH (1000)

/** max size of each Tx buffer descriptor list */
#define    CEDI_MAX_TBQ_LENGTH (1000)

/** Bit-flags to specify DMA endianism. @xmlonly <defstofollow>1</defstofollow> REMOVE_ME @endxmlonly */
#define    CEDI_END_SWAP_DESC (0x01)

#define    CEDI_END_SWAP_DATA (0x02)

/** Bit-flags to specify DMA config register bits 24-27; see EMAC User Guide for details. @xmlonly <defstofollow>3</defstofollow> REMOVE_ME @endxmlonly */
#define    CEDI_CFG_DMA_DISC_RXP (0x01)

#define    CEDI_CFG_DMA_FRCE_RX_BRST (0x02)

#define    CEDI_CFG_DMA_FRCE_TX_BRST (0x04)

/**
 * Bit-flags to specify checksum offload operation.
 * @xmlonly <defstofollow>1</defstofollow> REMOVE_ME @endxmlonly
*/
#define    CEDI_CFG_CHK_OFF_TX (0x01)

#define    CEDI_CFG_CHK_OFF_RX (0x02)

/**
 * Bit-flags for selecting interrupts to enable/disable/read.
 * @xmlonly <defstofollow>28</defstofollow> REMOVE_ME @endxmlonly
 * Frame has been transmitted successfully
*/
#define    CEDI_EV_TX_COMPLETE (0x00000001)

/** Used bit set has been read in Tx descriptor list */
#define    CEDI_EV_TX_USED_READ (0x00000002)

/** Tx underrun */
#define    CEDI_EV_TX_UNDERRUN (0x00000004)

/** Retry limit exceeded or late collision */
#define    CEDI_EV_TX_RETRY_EX_LATE_COLL (0x00000008)

/** Tx frame corruption */
#define    CEDI_EV_TX_FR_CORRUPT (0x00000010)

/** Frame received successfully and stored */
#define    CEDI_EV_RX_COMPLETE (0x00000020)

/** Used bit set has been read in Rx descriptor list */
#define    CEDI_EV_RX_USED_READ (0x00000040)

/** Rx overrun error */
#define    CEDI_EV_RX_OVERRUN (0x00000080)

/** DMA hresp not OK */
#define    CEDI_EV_HRESP_NOT_OK (0x00000100)

/** PCS auto-negotiation link partner page received */
#define    CEDI_EV_PCS_LP_PAGE_RX (0x00000200)

/** PCS auto-negotiation has completed */
#define    CEDI_EV_PCS_AN_COMPLETE (0x00000400)

/** Link status change detected by PCS */
#define    CEDI_EV_PCS_LINK_CHANGE_DET (0x00000800)

/** Pause frame transmitted */
#define    CEDI_EV_PAUSE_FRAME_TX (0x00001000)

/** Pause time reaches zero or zeroq pause frame received */
#define    CEDI_EV_PAUSE_TIME_ZERO (0x00002000)

/** Pause frame with non-zero quantum received */
#define    CEDI_EV_PAUSE_NZ_QU_RX (0x00004000)

/** PTP delay_req frame transmitted */
#define    CEDI_EV_PTP_TX_DLY_REQ (0x00008000)

/** PTP sync frame transmitted */
#define    CEDI_EV_PTP_TX_SYNC (0x00010000)

/** PTP pdelay_req frame transmitted */
#define    CEDI_EV_PTP_TX_PDLY_REQ (0x00020000)

/** PTP pdelay_resp frame transmitted */
#define    CEDI_EV_PTP_TX_PDLY_RSP (0x00040000)

/** PTP delay_req frame received */
#define    CEDI_EV_PTP_RX_DLY_REQ (0x00080000)

/** PTP sync frame received */
#define    CEDI_EV_PTP_RX_SYNC (0x00100000)

/** PTP pdelay_req frame received */
#define    CEDI_EV_PTP_RX_PDLY_REQ (0x00200000)

/** PTP pdelay_resp frame received */
#define    CEDI_EV_PTP_RX_PDLY_RSP (0x00400000)

/** TSU seconds register increment */
#define    CEDI_EV_TSU_SEC_INC (0x00800000)

/** TSU timer count match */
#define    CEDI_EV_TSU_TIME_MATCH (0x01000000)

/** Management Frame Sent */
#define    CEDI_EV_MAN_FRAME (0x02000000)

/** LPI indication status bit change received */
#define    CEDI_EV_LPI_CH_RX (0x04000000)

/** Wake on LAN event received */
#define    CEDI_EV_WOL_RX (0x08000000)

/** External input interrupt detected */
#define    CEDI_EV_EXT_INTR (0x10000000)

/** Bit-flags for indicating functionality supported by the driver/EMAC @xmlonly <defstofollow>3</defstofollow> REMOVE_ME @endxmlonly Large Segmentation Offload */
#define    CEDI_CAP_LSO (0x00000001)

/** Receive Side Coalescing offload */
#define    CEDI_CAP_RSC (0x00000002)

/** Receive Side Scaling offload */
#define    CEDI_CAP_RSS (0x00000004)

/** Bit-flags for selecting Tx Status fields to reset. @xmlonly <defstofollow>7</defstofollow> REMOVE_ME @endxmlonly */
#define    CEDI_TXS_USED_READ (0x0001)

#define    CEDI_TXS_COLLISION (0x0002)

#define    CEDI_TXS_RETRY_EXC (0x0004)

#define    CEDI_TXS_FRAME_ERR (0x0010)

#define    CEDI_TXS_TX_COMPLETE (0x0020)

#define    CEDI_TXS_UNDERRUN (0x0040)

#define    CEDI_TXS_LATE_COLL (0x0080)

#define    CEDI_TXS_HRESP_ERR (0x0100)

/**
 * Bit-flags for selecting Rx Status fields to reset.
 * @xmlonly <defstofollow>3</defstofollow> REMOVE_ME @endxmlonly
*/
#define    CEDI_RXS_NO_BUFF (0x0001)

#define    CEDI_RXS_FRAME_RX (0x0002)

#define    CEDI_RXS_OVERRUN (0x0004)

#define    CEDI_RXS_HRESP_ERR (0x0008)

/**
 * Transmit IP/TCP/UDP checksum generation offload errors
 * reported in Tx descriptor status.
 * @xmlonly <defstofollow>7</defstofollow> REMOVE_ME @endxmlonly
*/
#define    CEDI_TXD_CHKOFF_NO_ERROR (0)

#define    CEDI_TXD_CHKOFF_VLAN_HDR_ERR (1)

#define    CEDI_TXD_CHKOFF_SNAP_HDR_ERR (2)

#define    CEDI_TXD_CHKOFF_INVALID_IP (3)

#define    CEDI_TXD_CHKOFF_INVALID_PKT (4)

#define    CEDI_TXD_CHKOFF_PKT_FRAGMENT (5)

#define    CEDI_TXD_CHKOFF_NON_TCP_UDP (6)

#define    CEDI_TXD_CHKOFF_PREM_END_PKT (7)

/**
 * Bit-flags to control queueTxBuf/qTxBuf behaviour.
 * @xmlonly <defstofollow>5</defstofollow> REMOVE_ME @endxmlonly
 * Indicates last buffer in frame
*/
#define    CEDI_TXB_LAST_BUFF (0x01)

/** EMAC will not calculate & insert frame CRC. */
#define    CEDI_TXB_NO_AUTO_CRC (0x02)

/**
 * Prevents transmission being started automatically
 * after queueing the last buffer in the frame;
 * has no effect if CEDI_TXB_LAST_BUFF not also present.
*/
#define    CEDI_TXB_NO_AUTO_START (0x04)

/** select TCP encapsulation for the current frame - must be set for first and second buffers in frame, ie header and first data buffers */
#define    CEDI_TXB_TCP_ENCAP (0x08)

/** select UFO fragmentation for the current frame - only relevant for first buffer in frame, which includes the header only; Ignored if CEDI_TXB_TCP_ENCAP is set. */
#define    CEDI_TXB_UDP_ENCAP (0x10)

/**
 * select auto sequence-number generation, based on the current value of
 * the EMAC sequence number counter for this stream
*/
#define    CEDI_TXB_TSO_AUTO_SEQ (0x20)

/** Max length accepted by queueTxBuf */
#define    CEDI_TXD_LMASK ((1 << 14) - 1)

/** TCP flags (standard, some used to control RSC) @xmlonly <defstofollow>5</defstofollow> REMOVE_ME @endxmlonly */
#define    CEDI_TCP_FLG_FIN (0x0001)

#define    CEDI_TCP_FLG_SYN (0x0002)

#define    CEDI_TCP_FLG_RST (0x0004)

#define    CEDI_TCP_FLG_PSH (0x0008)

#define    CEDI_TCP_FLG_ACK (0x0010)

#define    CEDI_TCP_FLG_URG (0x0020)

/**
 * Bit-flags to control MDIO write/read operations.
 * @xmlonly <defstofollow>2</defstofollow> REMOVE_ME @endxmlonly
*/
#define    CEDI_MDIO_FLG_CLAUSE_45 (0x01)

#define    CEDI_MDIO_FLG_SET_ADDR (0x02)

#define    CEDI_MDIO_FLG_INC_ADDR (0x04)

/**
 * PFC Priority based pause frame support:
 * Maximum number of quantum priorities supported.
*/
#define    CEDI_QUANTA_PRIORITY_MAX 8

/**
 *  @}
 */

#define    CEDI_EVSET_ALL_Q0_EVENTS (CEDI_EV_TX_COMPLETE|CEDI_EV_TX_USED_READ| CEDI_EV_TX_UNDERRUN|CEDI_EV_TX_FR_CORRUPT| CEDI_EV_TX_RETRY_EX_LATE_COLL| CEDI_EV_RX_COMPLETE|CEDI_EV_RX_USED_READ|CEDI_EV_RX_OVERRUN|CEDI_EV_HRESP_NOT_OK| CEDI_EV_PCS_LP_PAGE_RX|CEDI_EV_PCS_AN_COMPLETE|CEDI_EV_PCS_LINK_CHANGE_DET| CEDI_EV_PAUSE_FRAME_TX|CEDI_EV_PAUSE_TIME_ZERO|CEDI_EV_PAUSE_NZ_QU_RX| CEDI_EV_PTP_TX_DLY_REQ|CEDI_EV_PTP_TX_SYNC|CEDI_EV_PTP_TX_PDLY_REQ| CEDI_EV_PTP_TX_PDLY_RSP|CEDI_EV_PTP_RX_DLY_REQ|CEDI_EV_PTP_RX_SYNC| CEDI_EV_PTP_RX_PDLY_REQ|CEDI_EV_PTP_RX_PDLY_RSP| CEDI_EV_TSU_SEC_INC|CEDI_EV_TSU_TIME_MATCH| CEDI_EV_MAN_FRAME|CEDI_EV_LPI_CH_RX|CEDI_EV_WOL_RX| CEDI_EV_EXT_INTR )

#define    CEDI_EVSET_ALL_QN_EVENTS (CEDI_EV_TX_COMPLETE| CEDI_EV_TX_RETRY_EX_LATE_COLL| CEDI_EV_TX_FR_CORRUPT|CEDI_EV_RX_COMPLETE| CEDI_EV_RX_USED_READ|CEDI_EV_HRESP_NOT_OK)

#define    CEDI_EVSET_TX_RX_EVENTS (CEDI_EV_TX_COMPLETE|CEDI_EV_TX_USED_READ|CEDI_EV_TX_UNDERRUN| CEDI_EV_TX_RETRY_EX_LATE_COLL| CEDI_EV_TX_FR_CORRUPT|CEDI_EV_RX_COMPLETE| CEDI_EV_RX_USED_READ|CEDI_EV_RX_OVERRUN| CEDI_EV_HRESP_NOT_OK)


/** @defgroup DataStructure Dynamic Data Structures
 *  This section defines the data structures used by the driver to provide
 *  hardware information, modification and dynamic operation of the driver.
 *  These data structures are defined in the header file of the core driver
 *  and utilized by the API.
 *  @{
 */

/**********************************************************************
 * Forward declarations
 **********************************************************************/
struct CEDI_Config;
struct CEDI_SysReq;
struct CEDI_TxStatus;
struct CEDI_RxStatus;
struct CEDI_BuffAddr;
struct CEDI_TimeStampData;
struct CEDI_TxDescData;
struct CEDI_TxDescStat;
struct CEDI_RxDescData;
struct CEDI_RxDescStat;
struct CEDI_qTxBufParams;
struct CEDI_FrameSize;
struct CEDI_MacAddress;
struct CEDI_Statistics;
struct CEDI_NumScreeners;
struct CEDI_T1Screen;
struct CEDI_T2Screen;
struct CEDI_T2Compare;
struct CEDI_1588TimerVal;
struct CEDI_TsuTimerVal;
struct CEDI_TimerIncrement;
struct CEDI_AnAdvPage;
struct CEDI_defLpAbility;
struct CEDI_sgmLpAbility;
union CEDI_LpAbility;
struct CEDI_LpAbilityPage;
struct CEDI_AnNextPage;
struct CEDI_LpNextPage;
union CEDI_LpPage;
struct CEDI_LpPageRx;
struct CEDI_NetAnStatus;
struct CEDI_WakeOnLanReg;
struct CEDI_LpiStats;
struct CEDI_DesignCfg;
struct CEDI_Callbacks;

/**********************************************************************
 * Enumerations
 **********************************************************************/
/** @defgroup DataStructure Dynamic Data Structures This section defines the data structures used by the driver to provide hardware information, modification, and dynamic operation of the driver. These data structures are defined in the header file of the core driver and utilized by the API. @{ */
typedef enum
{
    CEDI_DMA_BUS_WIDTH_32 = 0,
    CEDI_DMA_BUS_WIDTH_64 = 1,
    CEDI_DMA_BUS_WIDTH_128 = 2,
} CEDI_BusWidth;

typedef enum
{
    CEDI_DMA_DBUR_LEN_1 = 0,
    CEDI_DMA_DBUR_LEN_4 = 1,
    CEDI_DMA_DBUR_LEN_8 = 2,
    CEDI_DMA_DBUR_LEN_16 = 3,
} CEDI_DmaDatBLen;

typedef enum
{
    CEDI_MDC_DIV_BY_8 = 0,
    CEDI_MDC_DIV_BY_16 = 1,
    CEDI_MDC_DIV_BY_32 = 2,
    CEDI_MDC_DIV_BY_48 = 3,
    CEDI_MDC_DIV_BY_64 = 4,
    CEDI_MDC_DIV_BY_96 = 5,
    CEDI_MDC_DIV_BY_128 = 6,
    CEDI_MDC_DIV_BY_224 = 7,
} CEDI_MdcClkDiv;

typedef enum
{
    CEDI_MDIO_DEV_PMD_PMA = 1,
    CEDI_MDIO_DEV_WIS = 2,
    CEDI_MDIO_DEV_PCS = 3,
    CEDI_MDIO_DEV_PHY_XS = 4,
    CEDI_MDIO_DEV_DTE_XS = 5,
} CEDI_MdioDevType;

typedef enum
{
    CEDI_IFSP_10M_MII = 0,
    CEDI_IFSP_100M_MII = 1,
    CEDI_IFSP_1000M_GMII = 2,
    CEDI_IFSP_10M_SGMII = 3,
    CEDI_IFSP_100M_SGMII = 4,
    CEDI_IFSP_1000M_SGMII = 5,
    CEDI_IFSP_1000BASE_X = 6,
} CEDI_Interface;

typedef enum
{
    CEDI_TX_TS_DISABLED = 0,
    CEDI_TX_TS_PTP_EVENT_ONLY = 1,
    CEDI_TX_TS_PTP_ALL = 2,
    CEDI_TX_TS_ALL = 3,
} CEDI_TxTsMode;

typedef enum
{
    CEDI_RX_TS_DISABLED = 0,
    CEDI_RX_TS_PTP_EVENT_ONLY = 1,
    CEDI_RX_TS_PTP_ALL = 2,
    CEDI_RX_TS_ALL = 3,
} CEDI_RxTsMode;

/** Enum defining speed selection or indication */
typedef enum
{
    CEDI_SPEED_10M = 0,
    CEDI_SPEED_100M = 1,
    CEDI_SPEED_1000M = 2,
} CEDI_IfSpeed;

/** Enum defining Tx free descriptor call status */
typedef enum
{
    CEDI_TXDATA_1ST_NOT_LAST = 0,
    CEDI_TXDATA_1ST_AND_LAST = 1,
    CEDI_TXDATA_MID_BUFFER = 2,
    CEDI_TXDATA_LAST_BUFFER = 3,
    CEDI_TXDATA_NONE_FREED = 4,
} CEDI_TxFreeDStat;

/** Enum defining Rx data buffer read status */
typedef enum
{
    CEDI_RXDATA_SOF_EOF = 0,
    CEDI_RXDATA_SOF_ONLY = 1,
    CEDI_RXDATA_NO_FLAG = 2,
    CEDI_RXDATA_EOF_ONLY = 3,
    CEDI_RXDATA_NODATA = 4,
} CEDI_RxRdStat;

/** enum defining offset for screener type 2 compare values. Note the offset is applied after the specified point, e.g. T2COMP_OFF_ETYPE denotes the ethertype field, so an offset of 12 bytes from this would be the source IP address in an IP header. */
typedef enum
{
    CEDI_T2COMP_OFF_SOF = 0,
    CEDI_T2COMP_OFF_ETYPE = 1,
    CEDI_T2COMP_OFF_IPHDR = 2,
    CEDI_T2COMP_OFF_TCPUDP = 3,
} CEDI_T2Offset;

/** enum defining pause capability in auto-negotiation */
typedef enum
{
    CEDI_AN_PAUSE_CAP_NONE = 0,
    CEDI_AN_PAUSE_CAP_SYM = 1,
    CEDI_AN_PAUSE_CAP_ASYM = 2,
    CEDI_AN_PAUSE_CAP_BOTH = 3,
} CEDI_PauseCap;

/** enum defining loopback mode selection */
typedef enum
{
    CEDI_NO_LOOPBACK = 0,
    CEDI_LOCAL_LOOPBACK = 1,
    CEDI_SERDES_LOOPBACK = 2,
} CEDI_LoopbackMode;

/** enum defining remote fault indication by link partner in auto-negotiation */
typedef enum
{
    CEDI_AN_REM_FLT_NONE = 0,
    CEDI_AN_REM_FLT_LNK_FAIL = 1,
    CEDI_AN_REM_FLT_OFFLINE = 2,
    CEDI_AN_REM_FLT_AN_ERR = 3,
} CEDI_RemoteFault;

/**********************************************************************
 * Callbacks
 **********************************************************************/
/**
 * Reports PHY Management frame tx complete.
 * Params: read = 1 if a read operation, = 0 if a write operation, and
 * readData - data from the PHY, if read operation.
*/
typedef void (*CEDI_CbPhyManComplete)(void* pD, uint8_t read, uint16_t readData);

/**
 * Reports Tx completed / Tx used bit read events.
 * Params: event - indicates two types of event, which are OR'd together if both
 * occurred (CEDI_EV_TX_COMPLETE: frame has been transmitted successfully,
 * and CEDI_EV_TX_USED_READ: used bit set has been read in Tx descriptor list),
 * and queueNum- the priority queue number (only relevant to TX_COMPLETE)
 * range 0 to txQs-1.
*/
typedef void (*CEDI_CbTxEvent)(void* pD, uint32_t event, uint8_t queueNum);

/**
 * Reports Tx errors.  Params: error - indicates one or more of three
 * possible events, OR'd together (CEDI_EV_TX_UNDERRUN: Tx underrun,
 * CEDI_EV_TX_RETRY_EX_LATE_COLL: retry limit exceeded or late collision,
 * CEDI_EV_TX_FR_CORRUPT: Tx frame corruption), and queueNum - the priority
 * queue number, range 0 to txQs-1 (not relevant to TX_UNDERRUN).
*/
typedef void (*CEDI_CbTxError)(void* pD, uint32_t error, uint8_t queueNum);

/**
 * Reports Frame Rx completed successfully.  Param: queueNum - the priority
 * queue number, range 0 to rxQs-1.
*/
typedef void (*CEDI_CbRxFrame)(void* pD, uint8_t queueNum);

/**
 * Reports Rx errors.  Params: error - one or more of two possible errors,
 * together (CEDI_EV_RX_USED_READ: used bit set has been read in Rx descriptor
 * list; CEDI_EV_RX_OVERRUN: Rx overrun error),
 * and queueNum - the priority queue number, range 0 to rxQs-1.
*/
typedef void (*CEDI_CbRxError)(void* pD, uint32_t error, uint8_t queueNum);

/**
 * Reports Hresp not OK error.  Param: queueNum - number of the Tx or Rx
 * queue being accessed (range 0 to rxQs-1).
*/
typedef void (*CEDI_CbHrespError)(void* pD, uint8_t queueNum);

/**
 * Reports PCS auto-negotiation page received. Param: pageRx - pointer to a
 * struct containing the link partner base or next page data.
*/
typedef void (*CEDI_CbLpPageRx)(void* pD, struct CEDI_LpPageRx* pageRx);

/**
 * Reports PCS auto-negotiation completed. Param: netStat - pointer to a
 * struct with the network resolution status.
*/
typedef void (*CEDI_CbAnComplete)(void* pD, struct CEDI_NetAnStatus* netStat);

/**
 * Reports Link Status Changed. Param: linkState - link status: if
 * auto-negotiation enabled, when =1 link is up, else link is down;
 * if auto-negotiation not enabled, this will indicate the synchronisation
 * status.  If link status has gone down, the value will not return to 1
 * until after it has been read, therefore to see current state must
 * re-read with a getLinkStatus call.
*/
typedef void (*CEDI_CbLinkChange)(void* pD, uint8_t linkState);

/**
 * Reports TSU Event occurred. Param: event - indicates one of two events,
 * OR'd together (CEDI_EV_TSU_SEC_INC: TSU seconds register increment;
 * CEDI_EV_TSU_TIME_MATCH: TSU timer count match).
*/
typedef void (*CEDI_CbTsuEvent)(void* pD, uint32_t event);

/**
 * Reports Pause Event occurred.  Param: event - indicates one or more of
 * three event types, OR'd together (CEDI_EV_PAUSE_FRAME_TX: Pause frame
 * transmitted; CEDI_EV_PAUSE_TIME_ZERO: Pause time zero;
 * CEDI_EV_PAUSE_NZ_QU_RX: Pause frame with non-zero quantum received).
*/
typedef void (*CEDI_CbPauseEvent)(void* pD, uint32_t event);

/**
 * Reports PTP Primary Frame transmitted.  Params: type - indicates
 * one of two frame types, OR'd together (CEDI_EV_PTP_TX_DLY_REQ:
 * delay_req; CEDI_EV_PTP_TX_SYNC: sync)
 * , and time: pointer to
 * a struct containing the time latched when the frame was
 * transmitted.  This is not set if IP config param tsu=0.
*/
typedef void (*CEDI_CbPtpPriFrameTx)(void* pD, uint32_t type, struct CEDI_1588TimerVal* time);

/**
 * Reports PTP Peer Frame transmitted. Params: type - indicates
 * one of two frame types, OR'd together (CEDI_EV_PTP_TX_PDLY_REQ:
 * pdelay_req; CEDI_EV_PTP_TX_PDLY_RSP: pdelay_rsp)
 * , and time: pointer to
 * a struct containing the time latched when the frame was
 * transmitted.  This is not set if IP config param tsu=0.
*/
typedef void (*CEDI_CbPtpPeerFrameTx)(void* pD, uint32_t type, struct CEDI_1588TimerVal* time);

/**
 * Reports PTP Primary Frame received. Params: type - indicates
 * one of two frame types, OR'd together (CEDI_EV_PTP_RX_DLY_REQ:
 * delay_req; CEDI_EV_PTP_RX_SYNC: sync)
 * , and time: pointer to
 * a struct containing the time latched when the frame was
 * received.  This is not set if IP config param tsu=0.
*/
typedef void (*CEDI_CbPtpPriFrameRx)(void* pD, uint32_t type, struct CEDI_1588TimerVal* time);

/**
 * Reports PTP Peer Frame received. Params: type - indicates
 * one of two frame types, OR'd together (CEDI_EV_PTP_RX_PDLY_REQ:
 * pdelay_req; CEDI_EV_PTP_RX_PDLY_RSP: pdelay_rsp)
 * , and time: pointer to
 * a struct containing the time latched when the frame was
 * received.  This is not set if IP config param tsu=0.
*/
typedef void (*CEDI_CbPtpPeerFrameRx)(void* pD, uint32_t type, struct CEDI_1588TimerVal* time);

/** Reports LPI Status changed. */
typedef void (*CEDI_CbLpiStatus)(void* pD);

/** Reports Wake On LAN event received. */
typedef void (*CEDI_CbWolEvent)(void* pD);

/** Reports External input interrupt occurred. */
typedef void (*CEDI_CbExtInpIntr)(void* pD);

/**********************************************************************
 * Structures and unions
 **********************************************************************/
/**
 * Configuration parameters passed to probe & init.
 * Note that only the first eight fields are required for the probe call;
 * all are required by init
*/
typedef struct CEDI_Config
{
    /** base address of EMAC registers */
    uintptr_t regBase;
    /**
     * number of Rx priority queues, up to 1 more than
     * highest defined dma_priority_queueN value
     * (for example, =4 if highest is dma_priority_queue3)
    */
    uint8_t rxQs;
    /** number of Tx priority queues, same limit as for rxQs */
    uint8_t txQs;
    /**
     * number of descriptors in each Tx
     * descriptor queue
    */
    uint16_t txQLen[16];
    /**
     * number of descriptors in each Rx
     * descriptor queue
    */
    uint16_t rxQLen[16];
    /** DMA address bus width. 0=32b , 1=64b */
    uint8_t dmaAddrBusWidth;
    /** enable Tx extended BD mode */
    uint8_t enTxExtBD;
    /** enable Rx extended BD mode */
    uint8_t enRxExtBD;
    /**
     * sets endian swap for data buffers and descriptors
     * accesses: OR'd combination of CEDI_END_SWAP_DESC
     * and CEDI_END_SWAP_DATA
    */
    uint8_t dmaEndianism;
    /** DMA bus width: 32, 64 or 128 bits */
    CEDI_BusWidth dmaBusWidth;
    /**
     * events to enable on start, OR together bit-flags
     * defined in Interrupt control
    */
    uint32_t intrEnable;
    /**
     * Upper 32 bits of physical address of Tx descriptor queues.
     * Used only if DMA configured for 64-bit addressing.
     * This is the single upper address used for Tx & Rx descriptors by older
     * MAC h/w, in GEM_GXL before r1p06f2, and XGM_GXL up to r1p01
    */
    uint32_t upper32BuffTxQAddr;
    /**
     * Upper 32 bits of physical address of Rx descriptor queues.
     * Used only if DMA configured for 64-bit addressing
    */
    uint32_t upper32BuffRxQAddr;
    /**
     * start address of Tx descriptor queues (contiguous
     * block for all queues)
    */
    uintptr_t txQAddr;
    /** physical address of Tx descriptor queues */
    uint32_t txQPhyAddr;
    /**
     * start address of Rx descriptor queues (contiguous
     * block for all queues)
    */
    uintptr_t rxQAddr;
    /** physical address of Rx descriptor queues */
    uint32_t rxQPhyAddr;
    /**
     * length of rx buffers, as a multiple of 64 bytes,
     * e.g. 2 = 128 bytes
    */
    uint8_t rxBufLength[16];
    /** transmit packet buffer size select */
    uint8_t txPktBufSize;
    /** receive packet buffer size select */
    uint8_t rxPktBufSize;
    /** fixed burst length for DMA data transfers */
    CEDI_DmaDatBLen dmaDataBurstLen;
    /**
     * DMA config register bits 24, 25 & 26.
     * OR the following bit-flags to set corresponding bits -
     * CEDI_CFG_DMA_DISC_RXP,
     * CEDI_CFG_DMA_FRCE_RX_BRST,
     * CEDI_CFG_DMA_FRCE_TX_BRST
    */
    uint8_t dmaCfgFlags;
    /**
     * set to 1 to initialise with MDIO enabled, or 0 to
     * disable
    */
    uint8_t enableMdio;
    /** divisor to generate MDC from pclk */
    CEDI_MdcClkDiv mdcPclkDiv;
    /** MII/GMII/SGMII and speed selection */
    CEDI_Interface ifTypeSel;
    /**
     * enable alternative SGMII mode (auto-negotiation
     * ACK driven differently)
    */
    uint8_t altSgmiiEn;
    /** full/half duplex operation */
    uint8_t fullDuplex;
    /** enable Rx in half-duplex while Tx */
    uint8_t enRxHalfDupTx;
    /** enable external address match interface */
    uint8_t extAddrMatch;
    /** start-of-frame offset for writing Rx data (0 to 3 bytes) */
    uint8_t rxBufOffset;
    /** enable discard of frames with length field error */
    uint8_t rxLenErrDisc;
    /** disable copying Rx pause frames to memory */
    uint8_t disCopyPause;
    /** enable uni-direction Tx operation */
    uint8_t uniDirEnable;
    /**
     * enable checksum offload operation - OR bit-flags
     * to enable in Tx and/or Rx:
     * CEDI_CFG_CHK_OFF_TX,  CEDI_CFG_CHK_OFF_RX
    */
    uint8_t chkSumOffEn;
    /** enable Rx of frames up to 1536 bytes */
    uint8_t rx1536ByteEn;
    /** enable Rx of jumbo frames */
    uint8_t rxJumboFrEn;
    /** enable Rx frames with non-standard preamble */
    uint8_t enRxBadPreamble;
    /** ignore IPG rx_er (NetCfg b30) */
    uint8_t ignoreIpgRxEr;
    /**
     * replace CRC upper 16 bits with offset to UDP/TCP
     * header for Rx frames
    */
    uint8_t storeUdpTcpOffset;
    /** enable external TSU timer port */
    uint8_t enExtTsuPort;
    /**
     * Maximum number of outstanding AXI write requests,
     * that can be issued by DMA via the AW channel.
     * Must not be = 0 if using AXI as this would disable writes
    */
    uint8_t aw2wMaxPipeline;
    /**
     * Maximum number of outstanding AXI read requests,
     * that can be issued by DMA via the AR channel.
     * Must not be = 0 if using AXI as this would disable reads
    */
    uint8_t ar2rMaxPipeline;
    /** enable pfc multiple quantum (8 different priorities) */
    uint8_t pfcMultiQuantum;
    /**
     * address of CEDI_Statistics struct for driver to fill out: ignored if
     * no_stats = 1
    */
    uintptr_t statsRegs;
}  CEDI_Config;

/** System requirements returned by probe */
typedef struct CEDI_SysReq
{
    /** size of memory required for driver's private data */
    uint32_t privDataSize;
    /** size of contiguous block of Tx descriptor lists */
    uint32_t txDescListSize;
    /** size of contiguous block of Rx descriptor lists */
    uint32_t rxDescListSize;
    /**
     * size of memory for storing statistics register contents:
     * returned as 0 if no_stats was set to 1
    */
    uint32_t statsSize;
}  CEDI_SysReq;

/** struct for returning contents of the Tx Status register */
typedef struct CEDI_TxStatus
{
    uint8_t usedBitRead;
    uint8_t collisionOcc;
    uint8_t retryLimExc;
    uint8_t txActive;
    uint8_t txFrameErr;
    uint8_t txComplete;
    uint8_t txUnderRun;
    uint8_t lateCollision;
    uint8_t hRespNotOk;
}  CEDI_TxStatus;

/** Bit-field struct for returning contents of the Rx Status register */
typedef struct CEDI_RxStatus
{
    uint8_t buffNotAvail;
    uint8_t frameRx;
    uint8_t rxOverrun;
    uint8_t hRespNotOk;
}  CEDI_RxStatus;

/** Struct for virtual & physical addresses of DMA-addressable data buffer */
typedef struct CEDI_BuffAddr
{
    uintptr_t vAddr;
    uintptr_t pAddr;
}  CEDI_BuffAddr;

/** Struct describing  time stamp data allocated in descriptor */
typedef struct CEDI_TimeStampData
{
    /** TS valid - set to 1 if valid data stored */
    uint8_t tsValid;
    /** Timestamp nanoseconds[29:0] - word2/4[29:0] */
    uint32_t tsNanoSec;
    /** Timestamp seconds[1:0] from word2/4[31:30], seconds[5:2]from word3/5[5:2] */
    uint32_t tsSecs;
}  CEDI_TimeStampData;

/** struct for returning tx descriptor data */
typedef struct CEDI_TxDescData
{
    /** physical & virtual addresses of buffer freed up */
    struct CEDI_BuffAddr bufAdd;
    /** Tx descriptor status word - only valid if first buffer of frame */
    uint32_t txDescStat;
    /** descriptor queue status, see freeTxDesc for description */
    uint8_t status;
    /** Tx descriptor timestamp when valid (txTsData.tsValid will be set to 1) */
    struct CEDI_TimeStampData txTsData;
}  CEDI_TxDescData;

/** struct for returning tx descriptor status fields */
typedef struct CEDI_TxDescStat
{
    /** IP/TCP/UDP checksum offload errors - see CEDI_TXD_CHKOFF_ constants */
    uint8_t chkOffErr;
    /** late collision Tx error detected */
    uint8_t lateColl;
    /** DMA frame corruption */
    uint8_t frameCorr;
    /** Tx Underrun error detected */
    uint8_t txUnderrun;
    /** Tx error, retries limit exceeded */
    uint8_t retryExc;
}  CEDI_TxDescStat;

/** struct for returning rx descriptor data */
typedef struct CEDI_RxDescData
{
    /** Rx descriptor status word */
    uint32_t rxDescStat;
    /** Rx data status, see readRxBuf for description */
    uint8_t status;
    /** Rx descriptor timestamp when valid (rxTsData.tsValid will be set to 1) */
    struct CEDI_TimeStampData rxTsData;
}  CEDI_RxDescData;

/** struct for rx descriptor status fields */
typedef struct CEDI_RxDescStat
{
    /** valid when eoh (length of header) or eof (total frame length) - includes b13 if not ignore fcs enabled */
    uint16_t bufLen;
    /** ignore if jumbo frames enabled */
    uint8_t fcsStatus;
    /** Start Of Frame in this buffer */
    uint8_t sof;
    /** End Of Frame in this buffer */
    uint8_t eof;
    /** Header-data split: header buffer */
    uint8_t header;
    /** Header-data split: End Of Header in this buffer */
    uint8_t eoh;
    /** Canonical Format Indicator */
    uint8_t cfi;
    /** VLAN Priority */
    uint8_t vlanPri;
    /** Priority tag detected */
    uint8_t priTagDet;
    /** VLAN tag detected */
    uint8_t vlanTagDet;
    /** only set if rx chksum offload disabled */
    uint8_t typeIdMatch;
    /** Type ID match register if typeIdMatch set (RegNumber-1, i.e. 0 => reg. 1 ) */
    uint8_t typeMatchReg;
    /** ignore if rx chksum offload disabled */
    uint8_t snapNoVlanCfi;
    /** chksum offload checking status */
    uint8_t chkOffStat;
    /**
     * specific address register match (b27 OR b28)
     * If packet buffer mode and extra specific address
     * registers are used, this indicates match in
     * one of the first eight registers
    */
    uint8_t specAddMatch;
    /**
     * specific addr match register if specAddMatch set
     * (RegNumber-1, i.e. 0 => reg. 1 )
    */
    uint8_t specAddReg;
    /** external address match */
    uint8_t extAddrMatch;
    /** unicast hash match */
    uint8_t uniHashMatch;
    /** multicast hash match */
    uint8_t multiHashMatch;
    /** all-1's broadcast address detected */
    uint8_t broadcast;
}  CEDI_RxDescStat;

/** parameters for qTxBuf function */
typedef struct CEDI_qTxBufParams
{
    /** number of Tx queue */
    uint8_t queueNum;
    /** pointer to struct containing physical & virtual addresses of buffer - virtual field is for upper layer use only, can contain other reference/status if required */
    struct CEDI_BuffAddr* bufAdd;
    /** length of data in buffer */
    uint32_t length;
    /** bit-flags (CEDI_TXB_xx) specifying last buffer/auto CRC and LSO controls */
    uint8_t flags;
    /** Segment/fragment size (MSS for TCP or MFS for UDP) - used for all data descriptors */
    uint16_t mssMfs;
    /** TCP Stream number, determines which auto-sequence counter to use - only for first (header) descriptor used when flags includes CEDI_TXB_TSO_AUTO_SEQ and CEDI_TXB_TCP_ENCAP */
    uint8_t tcpStream;
}  CEDI_qTxBufParams;

/** Q buffer sizes */
typedef struct CEDI_FrameSize
{
    /** array of sizes per queue */
    uint32_t FrameSize[16];
}  CEDI_FrameSize;

/** struct for MAC address */
typedef struct CEDI_MacAddress
{
    uint8_t byte[6];
}  CEDI_MacAddress;

/** struct containing all statistics register values (144 bytes long) */
typedef struct CEDI_Statistics
{
    /** b31:0 of octets transmitted */
    uint32_t octetsTxLo;
    /** b47:32 of octets transmitted */
    uint16_t octetsTxHi;
    uint32_t framesTx;
    uint32_t broadcastTx;
    uint32_t multicastTx;
    uint16_t pauseFrTx;
    uint32_t fr64byteTx;
    uint32_t fr65_127byteTx;
    uint32_t fr128_255byteTx;
    uint32_t fr256_511byteTx;
    uint32_t fr512_1023byteTx;
    uint32_t fr1024_1518byteTx;
    uint32_t fr1519_byteTx;
    uint16_t underrunFrTx;
    uint32_t singleCollFrTx;
    uint32_t multiCollFrTx;
    uint16_t excessCollFrTx;
    uint16_t lateCollFrTx;
    uint32_t deferredFrTx;
    uint16_t carrSensErrsTx;
    /** b31:0 of octets received */
    uint32_t octetsRxLo;
    /** b47:32 of octets received */
    uint16_t octetsRxHi;
    uint32_t framesRx;
    uint32_t broadcastRx;
    uint32_t multicastRx;
    uint16_t pauseFrRx;
    uint32_t fr64byteRx;
    uint32_t fr65_127byteRx;
    uint32_t fr128_255byteRx;
    uint32_t fr256_511byteRx;
    uint32_t fr512_1023byteRx;
    uint32_t fr1024_1518byteRx;
    uint32_t fr1519_byteRx;
    uint16_t undersizeFrRx;
    uint16_t oversizeFrRx;
    uint16_t jabbersRx;
    uint16_t fcsErrorsRx;
    uint16_t lenChkErrRx;
    uint16_t rxSymbolErrs;
    uint16_t alignErrsRx;
    uint32_t rxResourcErrs;
    uint16_t overrunFrRx;
    uint16_t ipChksumErrs;
    uint16_t tcpChksumErrs;
    uint16_t udpChksumErrs;
    uint16_t dmaRxPBufFlush;
}  CEDI_Statistics;

/** struct for returning number of screening registers */
typedef struct CEDI_NumScreeners
{
    /** number of Type1 screener registers */
    uint8_t type1ScrRegs;
    /** number of Type2 screener registers */
    uint8_t type2ScrRegs;
    /** number of ethtype registers */
    uint8_t ethtypeRegs;
    /** number of compare registers */
    uint8_t compareRegs;
}  CEDI_NumScreeners;

/** struct for writing/reading Type1 screening registers */
typedef struct CEDI_T1Screen
{
    /** the priority queue allocated if match found, */
    uint8_t qNum;
    /** if =1, enable UDP port matching */
    uint8_t udpEnable;
    /** UDP port number to match if udpEnable=1 (ignored otherwise) */
    uint16_t udpPort;
    /** if =1, enable DS/TC field matching */
    uint8_t dstcEnable;
    /** DS field (IPv4) or TC field (IPv6) value to match against */
    uint8_t dstcMatch;
}  CEDI_T1Screen;

/** struct for writing/reading Type2 screening registers */
typedef struct CEDI_T2Screen
{
    /** the priority queue allocated if match found, */
    uint8_t qNum;
    /** if =1, enable VLAN priority matching */
    uint8_t vlanEnable;
    /** VLAN priority to match if vlanEnable=1 (ignored otherwise) */
    uint8_t vlanPriority;
    /** if =1, enable EtherType field matching */
    uint8_t eTypeEnable;
    /** Index of EtherType match register: when supported up to: CEDI_DesignCfg.num_scr2_ethtype_regs */
    uint8_t ethTypeIndex;
    /** if =1, enable compare A matching */
    uint8_t compAEnable;
    /** Index of compare register for compare A match. When supported up to: CEDI_DesignCfg.num_scr2_compare_regs */
    uint8_t compAIndex;
    /** if =1, enable compare B matching */
    uint8_t compBEnable;
    /** Index of compare register for compare B match. When supported up to: CEDI_DesignCfg.num_scr2_compare_regs */
    uint8_t compBIndex;
    /** if =1, enable compare C matching */
    uint8_t compCEnable;
    /** Index of compare register for compare C match. When supported up to: CEDI_DesignCfg.num_scr2_compare_regs */
    uint8_t compCIndex;
}  CEDI_T2Screen;

/** struct for writing/reading screener Type 2 compare registers */
typedef struct CEDI_T2Compare
{
    /** Mask Value field (or 1st 16 bits of compare when disableMask set) */
    uint16_t compMask;
    /** Compare Value field (or 2nd 16 bits of compare when disableMask set) */
    uint16_t compValue;
    /** Offset value */
    uint8_t offsetVal;
    /** Position in frame to apply offset */
    CEDI_T2Offset offsetPosition;
    /** Disable mask value function, to extend compare value to 4 bytes. Set to 1 to disable mask. */
    uint8_t disableMask;
}  CEDI_T2Compare;

/** struct for writing/reading 1588 timer */
typedef struct CEDI_1588TimerVal
{
    /** Upper 16 bits of seconds value */
    uint16_t secsUpper;
    /** Lower 32 bits of seconds value */
    uint32_t secsLower;
    /** Nanoseconds value (30 bits) */
    uint32_t nanosecs;
}  CEDI_1588TimerVal;

/** struct for writing/reading TSU timer */
typedef struct CEDI_TsuTimerVal
{
    /** Upper 16 bits of seconds value */
    uint16_t secsUpper;
    /** Lower 32 bits of seconds value */
    uint32_t secsLower;
    /** Upper 22 bits of nanoseconds value */
    uint32_t nanosecs;
}  CEDI_TsuTimerVal;

/** struct for writing/reading the 1588 timer increment registers */
typedef struct CEDI_TimerIncrement
{
    /** Whole nanoseconds to increment timer each clock cycle */
    uint8_t nanoSecsInc;
    /** Sub-nanoseconds to increment the timer (16 bits) */
    uint16_t subNsInc;
    /** Lower 8 bits of sub-nanoseconds to increment the timer */
    uint8_t lsbSubNsInc;
    /** Number of increments before changing to alternative increment. If = 0 then never use alternative increment. */
    uint8_t altIncCount;
    /** Alternative nanoseconds increment to apply */
    uint8_t altNanoSInc;
}  CEDI_TimerIncrement;

/**
 * struct for returning contents of the auto-negotiation advertisement
 * register
*/
typedef struct CEDI_AnAdvPage
{
    /** full duplex capability */
    uint8_t fullDuplex;
    /** half duplex capability */
    uint8_t halfDuplex;
    /** pause capability */
    CEDI_PauseCap pauseCap;
    /** remote fault condition */
    CEDI_RemoteFault remFlt;
    /** next page exchange required */
    uint8_t nextPage;
}  CEDI_AnAdvPage;

/** struct for default (non-SGMII) auto-negotiation link partner abilities */
typedef struct CEDI_defLpAbility
{
    /** full duplex capability */
    uint8_t fullDuplex;
    /** half duplex capability */
    uint8_t halfDuplex;
    /** pause capability */
    CEDI_PauseCap pauseCap;
    /** remote fault condition */
    CEDI_RemoteFault remFlt;
    /** link partner acknowledge indication */
    uint8_t lpAck;
    /** next page exchange required */
    uint8_t lpNextPage;
}  CEDI_defLpAbility;

/** struct for SGMII mode auto-negotiation link partner abilities */
typedef struct CEDI_sgmLpAbility
{
    /** speed, = 10/100/1000Mbps */
    CEDI_IfSpeed speed;
    /**
     * duplex capability, = 0 for half duplex,
     * =1 for full duplex
    */
    uint8_t duplex;
    /** link partner acknowledge indication */
    uint8_t lpAck;
    /** =0 if link down, =1 if link up */
    uint8_t linkStatus;
}  CEDI_sgmLpAbility;

/**
 * union of two possible link partner ability structs,
 * one for default configuration and one for SGMII configuration
*/
typedef union CEDI_LpAbility
{
    struct CEDI_defLpAbility defLpAbl;
    struct CEDI_sgmLpAbility sgmLpAbl;
}  CEDI_LpAbility;

/** Struct for link partner ability page info. If sgmii =0 then read default ability page struct from ablInfo. If sgmii =1 then read SGMII mode ability page struct from ablInfo. */
typedef struct CEDI_LpAbilityPage
{
    union CEDI_LpAbility ablInfo;
    uint8_t sgmii;
}  CEDI_LpAbilityPage;

/** Struct for auto-negotiation next page register data */
typedef struct CEDI_AnNextPage
{
    /** message data as defined by message page indicator (11 bits) */
    uint16_t message;
    /** acknowledge 2 */
    uint8_t ack2;
    /** message page indicator */
    uint8_t msgPage;
    /** set if another next page to transmit */
    uint8_t np;
}  CEDI_AnNextPage;

/** struct for auto-negotiation link partner next page data */
typedef struct CEDI_LpNextPage
{
    /** message data as defined by message page indicator (11 bits) */
    uint16_t message;
    /** toggles for each received page */
    uint8_t toggle;
    /** acknowledge 2 */
    uint8_t ack2;
    /** message page indicator */
    uint8_t msgPage;
    /**
     * indicates if link partner successfully
     * received last message
    */
    uint8_t ack;
    /** set if another next page to transmit */
    uint8_t np;
}  CEDI_LpNextPage;

/** union for link partner page data - ability page or next page */
typedef union CEDI_LpPage
{
    struct CEDI_LpAbilityPage lpBasePage;
    struct CEDI_LpNextPage lpNextPage;
}  CEDI_LpPage;

/** Struct for returning page data from link partner. If nextPage = 0 then read link partner base page from lpPage.lpBasePage, else read next page from lpPage.lpNextPage */
typedef struct CEDI_LpPageRx
{
    union CEDI_LpPage lpPageDat;
    uint8_t nextPage;
}  CEDI_LpPageRx;

/** Struct for returning network status related to auto-negotiation */
typedef struct CEDI_NetAnStatus
{
    /**
     * if auto-negotiation enabled: = 1 if LINK up,
     * = 0 if LINK down
     * else synchronisation status
    */
    uint8_t linkState;
    /** if = 1 then both devices full duplex */
    uint8_t duplexRes;
    /** enable pause Tx */
    uint8_t pauseTxRes;
    /** enable pause Rx */
    uint8_t pauseRxRes;
}  CEDI_NetAnStatus;

/** Struct for writing/reading the Wake On LAN register */
typedef struct CEDI_WakeOnLanReg
{
    /** Least significant 16 bits of target IP address to match */
    uint16_t wolReqAddr;
    /** Magic packet events cause WOL assert (equal 1 means enabled) */
    uint8_t magPktEn;
    /** ARP request events cause WOL assert (equal 1 means enabled) */
    uint8_t arpEn;
    /** Specific address 1 events cause WOL assert (equal 1 means enabled) */
    uint8_t specAd1En;
    /** Multicast hash events cause WOL assert (equal 1 means enabled) */
    uint8_t multiHashEn;
}  CEDI_WakeOnLanReg;

/** Struct for returning the LPI Tx and Rx statistics */
typedef struct CEDI_LpiStats
{
    /** Number of transitions to Rx low power idle */
    uint16_t rxLpiTrans;
    /** Counts time in Rx LPI indication */
    uint32_t rxLpiTime;
    /** Number of transitions to LPI Tx enable */
    uint16_t txLpiTrans;
    /** Counts time in LPI Tx enable */
    uint32_t txLpiTime;
}  CEDI_LpiStats;

/** Struct containing all design configuration fields, plus some other features which are revision-dependent, e.g. intrp_mod */
typedef struct CEDI_DesignCfg
{
    uint16_t moduleId;
    uint16_t moduleRev;
    uint8_t fixNumber;
    uint8_t numQueues;
    uint8_t no_pcs;
    uint8_t serdes;
    uint8_t RDC_50;
    uint8_t TDC_50;
    uint8_t int_loopback;
    uint8_t no_int_loopback;
    uint8_t ext_fifo_interface;
    uint8_t apb_rev1;
    uint8_t apb_rev2;
    uint8_t user_io;
    uint8_t user_out_width;
    uint8_t user_in_width;
    uint8_t no_scan_pins;
    uint8_t no_stats;
    uint8_t no_snapshot;
    uint8_t irq_read_clear;
    uint8_t exclude_cbs;
    uint8_t num_spec_add_filters;
    uint8_t dma_bus_width;
    uint8_t axi_cache_value;
    uint16_t jumbo_max_length;
    uint8_t hprot_value;
    uint8_t rx_pkt_buffer;
    uint8_t tx_pkt_buffer;
    uint8_t rx_pbuf_addr;
    uint8_t tx_pbuf_addr;
    uint8_t axi;
    uint8_t rx_fifo_cnt_width;
    uint8_t tx_fifo_cnt_width;
    uint8_t tsu;
    uint8_t phy_ident;
    uint8_t dma_bus_width_def;
    uint8_t mdc_clock_div;
    uint8_t endian_swap_def;
    uint8_t rx_pbuf_size_def;
    uint8_t tx_pbuf_size_def;
    uint8_t rx_buffer_length_def;
    uint8_t tsu_clk;
    uint8_t axi_prot_value;
    uint8_t tx_pbuf_queue_segment_size;
    uint8_t ext_tsu_timer;
    uint8_t tx_add_fifo_if;
    uint8_t host_if_soft_select;
    uint8_t tx_pbuf_num_segments_q0;
    uint8_t tx_pbuf_num_segments_q1;
    uint8_t tx_pbuf_num_segments_q2;
    uint8_t tx_pbuf_num_segments_q3;
    uint8_t tx_pbuf_num_segments_q4;
    uint8_t tx_pbuf_num_segments_q5;
    uint8_t tx_pbuf_num_segments_q6;
    uint8_t tx_pbuf_num_segments_q7;
    uint8_t dma_addr_width;
    uint8_t tx_pbuf_num_segments_q8;
    uint8_t tx_pbuf_num_segments_q9;
    uint8_t tx_pbuf_num_segments_q10;
    uint8_t tx_pbuf_num_segments_q11;
    uint8_t tx_pbuf_num_segments_q12;
    uint8_t tx_pbuf_num_segments_q13;
    uint8_t tx_pbuf_num_segments_q14;
    uint8_t tx_pbuf_num_segments_q15;
    uint8_t num_type1_screeners;
    uint8_t num_type2_screeners;
    uint8_t num_scr2_ethtype_regs;
    uint8_t num_scr2_compare_regs;
    uint8_t axi_access_pipeline_bits;
    uint8_t pfc_multi_quantum;
    uint8_t pbuf_rsc;
    uint8_t pbuf_lso;
    uint8_t intrpt_mod;
    uint8_t hdr_split;
    uint8_t rx_pbuf_data;
    uint8_t tx_pbuf_data;
}  CEDI_DesignCfg;

/**
 * struct containing function pointers for event notification callbacks issued
 * by isr().
 * <para>Each call passes the driver's privateData (pD) pointer for instance
 * identification if necessary, and may also pass data related to the event.</para>
*/
typedef struct CEDI_Callbacks
{
    CEDI_CbPhyManComplete phyManComplete;
    CEDI_CbTxEvent txEvent;
    CEDI_CbTxError txError;
    CEDI_CbRxFrame rxFrame;
    CEDI_CbRxError rxError;
    CEDI_CbHrespError hrespError;
    CEDI_CbLpPageRx lpPageRx;
    CEDI_CbAnComplete anComplete;
    CEDI_CbLinkChange linkChange;
    CEDI_CbTsuEvent tsuEvent;
    CEDI_CbPauseEvent pauseEvent;
    CEDI_CbPtpPriFrameTx ptpPriFrameTx;
    CEDI_CbPtpPeerFrameTx ptpPeerFrameTx;
    CEDI_CbPtpPriFrameRx ptpPriFrameRx;
    CEDI_CbPtpPeerFrameRx ptpPeerFrameRx;
    CEDI_CbLpiStatus lpiStatus;
    CEDI_CbWolEvent wolEvent;
    CEDI_CbExtInpIntr extInpIntr;
}  CEDI_Callbacks;

/**
 *  @}
 */

/** @defgroup DriverObject Driver API Object
 *  API listing for the driver. The API is contained in the object as
 *  function pointers in the object structure. As the actual functions
 *  resides in the Driver Object, the client software must first use the
 *  global GetInstance function to obtain the Driver Object Pointer.
 *  The actual APIs then can be invoked using obj->(api_name)() syntax.
 *  These functions are defined in the header file of the core driver
 *  and utilized by the API.
 *  @{
 */

/**********************************************************************
 * API methods
 **********************************************************************/
typedef struct CEDI_OBJ
{
    /**
     * Get the driver's memory requirements to support the given
     * configuration. If config->txQs or config->rxQs specify more than
     * the number of queues available in the h/w configuration, they will
     * be reduced to match the latter value, and the memReq values will
     * be based on this.
     * @param[out] memReq returns the size of memory allocations required
     * @param[in] config driver/hardware configuration required
     * @return EOK on success (requirements struct filled)
     * @return ENOTSUP if configuration cannot be supported due to driver/hardware constraints
     * @return EINVAL if config is NULL, or hardware not present
     */
    uint32_t (*probe)(CEDI_Config* config, CEDI_SysReq* memReq);

    /**
     * Initialise the driver instance and state, configure the EMAC as
     * specified in the 'config' settings, set up Tx & Rx descriptor
     * lists.
     * @param[in] callbacks client-supplied callback functions
     * @param[in,out] config specifies driver/hardware configuration
     * @param[in] pD driver state info specific to this instance
     * @return EOK on success
     * @return ENOTSUP if hardware has an inconsistent configuration or doesn't support feature(s) required by 'config' parameters
     * @return EIO if driver encountered an error accessing hardware
     * @return EINVAL if illegal/inconsistent values in 'config'
     */
    uint32_t (*init)(void* pD, const CEDI_Config* config, CEDI_Callbacks* callbacks);

    /**
     * Destroy the driver (automatically performs a stop)
     * @param[in] pD driver state info specific to this instance
     */
    void (*destroy)(void* pD);

    /**
     * Start the EMAC driver, enabling interrupts and PCS auto-
     * negotiation.
     * @param[in] pD driver state info specific to this instance
     */
    void (*start)(void* pD);

    /**
     * Stop the driver. This should disable the hardware, including its
     * interrupt at the source, and make a best-effort to cancel any
     * pending transactions.
     * @param[in] pD driver state info specific to this instance
     */
    void (*stop)(void* pD);

    /**
     * Driver ISR.  Platform-specific code is responsible for ensuring
     * this gets called when the corresponding hardware's interrupt is
     * asserted. Registering the ISR should be done after calling init,
     * and before calling start. The driver's ISR will not attempt to
     * lock any locks, but will perform client callbacks. If the client
     * wishes to defer processing to non-interrupt time, it is
     * responsible for doing so.
     * @param[in] pD driver state info specific to this instance
     * @return EOK if any interrupt detected (and callback)
     * @return ECANCELED if no interrupt bit detected
     * @return EINVAL for invalid pD pointer
     */
    uint32_t (*isr)(void* pD);

    /**
     * Enable or disable the specified interrupts. mechanical test will
     * always fail as no callback pointers are given
     * @param[in] enable if =1 enable the events, if =0 then disable
     * @param[in] events OR'd combination of bit-flags selecting the events to be enabled or disabled
     * @param[in] pD driver private state info specific to this instance
     * @param[in] queueNum between 0 and config->rxQs-1, or = CEDI_ALL_QUEUES
     *     - number of Tx or Rx priority queue,
     *    relevant to some of Tx and Rx events: CEDI_EV_TX_COMPLETE,          CEDI_EV_TX_RETRY_EX_LATE_COLL, CEDI_EV_TX_FR_CORRUPT, CEDI_EV_RX_COMPLETE,
     *    CEDI_EV_RX_USED_READ, CEDI_EV_RX_OVERRUN, CEDI_EV_HRESP_NOT_OK.
     *    Must be = 0 or CEDI_ALL_QUEUES for other events.
     *    To dis/enable on all available Qs, set queueNum to CEDI_ALL_QUEUES
     *    and set events to CEDI_EVSET_ALL_Q0_EVENTS.
     * @return EOK for success
     * @return EINVAL for invalid queueNum
     */
    uint32_t (*setEventEnable)(void* pD, uint32_t events, uint8_t enable, uint8_t queueNum);

    /**
     * Read the enabled state of the specifed interrupts. OR the returned
     * event value with the CEDI_EV_ event bit-flags to determine if
     * event(s) are enabled.
     * @param[out] event returned enabled events
     * @param[in] pD driver private state info specific to this instance
     * @param[in] queueNum Tx or Rx priority queue to report events for
     * @return EOK for success
     * @return EINVAL for invalid pointer or queueNum
     */
    uint32_t (*getEventEnable)(void* pD, uint8_t queueNum, uint32_t* event);

    /**
     * Set the value of the Tx & Rx interrupt moderation register fields.
     * A non-zero value in either field introduces an interrupt stand-off
     * delay of the 8-bit value in units of 800ns before the
     * corresponding frame complete event causes an interrupt, limiting
     * the interrupt rate.
     * @param[in] txIntDelay Interrupt delay to apply to Tx frame complete
     * @param[in] rxIntDelay Interrupt delay to apply to Rx frame complete
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return EINVAL for invalid pointer
     */
    uint32_t (*setIntrptModerate)(void* pD, uint8_t txIntDelay, uint8_t rxIntDelay);

    /**
     * Read the values of the interrupt moderation register fields
     * @param[out] txIntDelay Interrupt delay to apply to Tx frame complete
     * @param[out] rxIntDelay Interrupt delay to apply to Rx frame complete
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return EINVAL for invalid pointers
     */
    uint32_t (*getIntrptModerate)(void* pD, uint8_t* txIntDelay, uint8_t* rxIntDelay);

    /**
     * Select 10/100/1000Mbps operation speed.
     * @param[in] speedSel a CEDI_IfSpeed enum indicating Tx/Rx speed
     * @param[in] pD driver private state info specific to this instance
     * @return EOK if successful
     * @return EINVAL if invalid parameter
     */
    uint32_t (*setIfSpeed)(void* pD, CEDI_IfSpeed speedSel);

    /**
     * Read selected operation speed
     * @param[out] speedSel returns CEDI_IfSpeed enum indicating Tx/Rx speed "
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return EINVAL if invalid parameter
     */
    uint32_t (*getIfSpeed)(void* pD, CEDI_IfSpeed* speedSel);

    /**
     * Enable/disable reception of jumbo frames
     * @param[in] enable if =1 then enable jumbo frames accept, if =0 disable.
     * @param[in] pD driver private state info specific to this instance
     */
    void (*setJumboFramesRx)(void* pD, uint8_t enable);

    /**
     * Read jumbo frames enable status
     * @param[out] enable equal 1 if jumbo frames accept enabled; equal 0 if disabled.
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return EINVAL for invalid pointer
     */
    uint32_t (*getJumboFramesRx)(void* pD, uint8_t* enable);

    /**
     * Set maximum length of jumbo frames to be received. (This is
     * initialised to gem_jumbo_max_length bytes.) Disables jumbo frame
     * reception temporarily while changing max length.
     * @param[in] length max. length to receive, in bytes.  Maximum is 16383
     * @param[in] pD driver private state info specific to this instance
     * @return EOK if successful
     * @return EINVAL if length greater than 16383
     */
    uint32_t (*setJumboFrameRxMaxLen)(void* pD, uint16_t length);

    /**
     * Read maximum length of jumbo frames to be received
     * @param[out] length returns max. length to receive, in bytes
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return EINVAL for invalid pointer
     */
    uint32_t (*getJumboFrameRxMaxLen)(void* pD, uint16_t* length);

    /**
     * Enable/disable uni-direction transmit operation.
     * @param[in] enable if =1 enable, if =0 then disable
     * @param[in] pD driver private state info specific to this instance
     */
    void (*setUniDirEnable)(void* pD, uint8_t enable);

    /**
     * Read enable status for uni-direction transmit operation
     * @param[out] enable equal 1 if enabled, equal 0 if disabled
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return EINVAL for invalid pointer
     */
    uint32_t (*getUniDirEnable)(void* pD, uint8_t* enable);

    /**
     * Enable/disable Tx IP, TCP and UDP checksum generation offload.
     * Only valid if using DMA packet buffering mode.
     * @param[in] enable if =1 then enable, if =0 then disable
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return EINVAL if packet buffering not enabled or null pointer
     */
    uint32_t (*setTxChecksumOffload)(void* pD, uint8_t enable);

    /**
     * Read enable/disable of Tx IP, TCP and UDP checksum generation
     * offload
     * @param[out] enable equal 1 if enabled, equal 0 if disabled
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return EINVAL for invalid pointer
     */
    uint32_t (*getTxChecksumOffload)(void* pD, uint8_t* enable);

    /**
     * Set Rx buffer offset for writing start of frame.
     * @param[in] pD driver private state info specific to this instance
     * @param[in] offset offset to use, range 0 to 3 bytes
     * @return EOK for success
     * @return EINVAL if offset invalid or null pointer
     */
    uint32_t (*setRxBufOffset)(void* pD, uint8_t offset);

    /**
     * Read Rx buffer offset for writing start of frame
     * @param[in] pD driver private state info specific to this instance
     * @param[out] offset offset in use, range 0 to 3 bytes
     * @return EOK for success
     * @return EINVAL for invalid pointer
     */
    uint32_t (*getRxBufOffset)(void* pD, uint8_t* offset);

    /**
     * Enable/disable reception of frames up to 1536 bytes, instead of
     * normal 1518 bytes limit
     * @param[in] enable if =1 then enable 1536-byte frames accept, if =0 disable
     * @param[in] pD driver private state info specific to this instance
     */
    void (*set1536ByteFramesRx)(void* pD, uint8_t enable);

    /**
     * Read 1536-byte frames Rx enable status
     * @param[out] enable equal 1 if 1536-byte frames accept enabled equal 0 if disabled.
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return EINVAL for invalid pointer
     */
    uint32_t (*get1536ByteFramesRx)(void* pD, uint8_t* enable);

    /**
     * Enable/disable Rx IP, TCP and UDP checksum offload. When enabled,
     * frames with bad IP, TCP or UDP checksums will be discarded.
     * @param[in] enable if =1 then enable, if =0 then disable
     * @param[in] pD driver private state info specific to this instance
     */
    void (*setRxChecksumOffload)(void* pD, uint8_t enable);

    /**
     * Read enable/disable of Rx IP, TCP and UDP checksum offload
     * @param[out] enable equal 1 if enabled, equal 0 if disabled
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return EINVAL for invalid pointer
     */
    uint32_t (*getRxChecksumOffload)(void* pD, uint8_t* enable);

    /**
     * Enable/disable FCS remove feature. When enabled, received frames
     * will be written without frame check sequence (last four bytes).
     * @param[in] enable if =1 then enable, if =0 then disable
     * @param[in] pD driver private state info specific to this instance
     */
    void (*setFcsRemove)(void* pD, uint8_t enable);

    /**
     * Read enable/disable status for FCS remove feature
     * @param[out] enable equal 1 if enabled, equal 0 if disabled
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return EINVAL for invalid pointer
     */
    uint32_t (*getFcsRemove)(void* pD, uint8_t* enable);

    /**
     * Enable/disable partial store and forward Tx mode if possible
     * @param[in] enable if =1 then enables partial store and forward Tx mode, if =0 then disables
     * @param[in] pD driver private state info specific to this instance
     * @param[in] watermark value to control data forwarding - ignored if enable==0
     * @return EOK if successful
     * @return ENOTSUP if not in tx packet buffer mode
     * @return EINVAL if parameter invalid
     */
    uint32_t (*setTxPartialStFwd)(void* pD, uint32_t watermark, uint8_t enable);

    /**
     * Get watermark value for partial store and forward Tx mode
     * @param[out] enable =1 if partial store and forward Tx mode enabled
     * @param[in] pD driver private state info specific to this instance
     * @param[out] watermark returns value to control data forwarding if partial store and forward Tx mode enabled
     * @return EOK for success
     * @return ENOTSUP if not in tx packet buffer mode
     * @return EINVAL if invalid parameter
     */
    uint32_t (*getTxPartialStFwd)(void* pD, uint32_t* watermark, uint8_t* enable);

    /**
     * Enable/disable partial store and forward Rx mode if possible
     * @param[in] enable if =1 then enables partial store and forward Rx mode, if =0 then disables
     * @param[in] pD driver private state info specific to this instance
     * @param[in] watermark value to control data forwarding
     * @return EOK if successful
     * @return ENOTSUP if not in rx packet buffer mode
     * @return EINVAL if invalid parameter
     */
    uint32_t (*setRxPartialStFwd)(void* pD, uint32_t watermark, uint8_t enable);

    /**
     * Get watermark value for partial store and forward Rx mode
     * @param[out] enable =1 if partial store and forward Rx mode enabled
     * @param[in] pD driver private state info specific to this instance
     * @param[out] watermark pointer for returning watermark value set (undefined if partial store & forward not enabled)
     * @return EOK for success
     * @return ENOTSUP if not in rx packet buffer mode
     * @return EINVAL if invalid parameter
     */
    uint32_t (*getRxPartialStFwd)(void* pD, uint32_t* watermark, uint8_t* enable);

    /**
     * Set the fields of the Rx DMA Data Buffer Address Mask register,
     * which allows any/all of bits 31:28 of rx data buffer address to be
     * forced to a particular value
     * @param[in] bitValues 4-bit field specifying values to force address bits 31:28 to, if corresponding bit in enableBit is set to 1
     * @param[in] pD driver private state info specific to this instance
     * @param[in] enableBit 4-bit field selecting bits to force value on
     * @return EOK if successful
     * @return EINVAL if parameter value invalid
     */
    uint32_t (*setRxDmaDataAddrMask)(void* pD, uint8_t enableBit, uint8_t bitValues);

    /**
     * Read the fields of the Rx DMA Data Buffer Address Mask register,
     * which allows any/all of bits 31:28 of rx data buffer address to be
     * forced to a particular value
     * @param[out] bitValues pointer for returning 4-bit field specifying values to force address bits to, if corresponding bit in enableBit is set to 1
     * @param[in] pD driver private state info specific to this instance
     * @param[out] enableBit pointer for returning 4-bit field selecting bits to force value on
     * @return EOK if successful
     * @return EINVAL if any parameter equal NULL
     */
    uint32_t (*getRxDmaDataAddrMask)(void* pD, uint8_t* enableBit, uint8_t* bitValues);

    /**
     * Enable/disable receive bad preamble feature. When enabled, frames
     * with non-standard preamble will not be rejected.
     * @param[in] enable if =1 then enable, if =0 then disable
     * @param[in] pD driver private state info specific to this instance
     */
    void (*setRxBadPreamble)(void* pD, uint8_t enable);

    /**
     * Read enable/disable status for receive bad preamble feature
     * @param[out] enable equal 1 if enabled, equal 0 if disabled
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return EINVAL for invalid pointer
     */
    uint32_t (*getRxBadPreamble)(void* pD, uint8_t* enable);

    /**
     * Select full/half duplex operation.
     * @param[in] enable if =1 select full duplex operation if =0 select half duplex.
     * @param[in] pD driver private state info specific to this instance
     */
    void (*setFullDuplex)(void* pD, uint8_t enable);

    /**
     * Read full/half duplex operation
     * @param[out] enable equal 1 if full duplex operation enabled equal 0 if half duplex.
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return EINVAL for invalid pointer
     */
    uint32_t (*getFullDuplex)(void* pD, uint8_t* enable);

    /**
     * Enable/disable ignore FCS feature. When enabled, frames with
     * FCS/CRC errors will not be rejected.
     * @param[in] enable if =1 then enable, if =0 then disable
     * @param[in] pD driver private state info specific to this instance
     */
    void (*setIgnoreFcsRx)(void* pD, uint8_t enable);

    /**
     * Read enable/disable status for FCS ignore feature
     * @param[out] enable equal 1 if enabled, equal 0 if disabled
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return EINVAL for invalid pointer
     */
    uint32_t (*getIgnoreFcsRx)(void* pD, uint8_t* enable);

    /**
     * Enable/disable frame Rx in half-duplex mode while transmitting.
     * @param[in] enable if =1 then enable, if =0 then disable
     * @param[in] pD driver private state info specific to this instance
     */
    void (*setRxHalfDuplexInTx)(void* pD, uint8_t enable);

    /**
     * Read enable status for frame Rx in half-duplex mode while
     * transmitting
     * @param[out] enable equal 1 if enabled, equal 0 if disabled
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return EINVAL for invalid pointer
     */
    uint32_t (*getRxHalfDuplexInTx)(void* pD, uint8_t* enable);

    /**
     * Return capabilities supported by the driver/EMAC hardware
     * @param[out] cap pointer for returning supported capabilities, OR combination of CEDI_CAP_XXX flags
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return EINVAL for invalid pointer
     */
    uint32_t (*getIfCapabilities)(void* pD, uint32_t* cap);

    /**
     * Enable or disable loop back mode in the EMAC.
     * @param[in] mode enum selecting mode enable/disable. =CEDI_SERDES_LOOPBACK: select loopback mode in PHY transceiver, if available; =CEDI_LOCAL_LOOPBACK: select internal loopback mode. Tx and Rx should be disabled when enabling or disabling this mode. Only available if int_loopback defined; =CEDI_NO_LOOPBACK: disable loopback mode
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return ENOTSUP if CEDI_SERDES_LOOPBACK selected and no_pcs defined, or if CEDI_LOCAL_LOOPBACK selected and either (no_int_loopback defined or PCS mode is selected)
     */
    uint32_t (*setLoopback)(void* pD, uint8_t mode);

    /**
     * Return loopback mode, same values as for setLoopbackMode.
     * @param[out] mode returns enum for mode enable/disable. =CEDI_SERDES_LOOPBACK: selected loopback mode in PHY transceiver, if available; =CEDI_LOCAL_LOOPBACK: selected internal loopback mode. Only available if int_loopback defined; =CEDI_NO_LOOPBACK: disabled loopback mode
     * @param[in] pD driver private state info specific to this instance
     */
    uint32_t (*getLoopback)(void* pD, uint8_t* mode);

    /**
     * Identify max Tx pkt size for queues. When using full store &
     * forward packet buffering, this is based on the sram size for each
     * queue, otherwise it is limited by an internal counter to 16kB.
     * @param[out] maxTxSize pointer for returning array of sizes for queues
     * @param[in] pD driver private state info specific to this instance
     * @return EOK if successful
     * @return EINVAL if any parameter equal NULL
     */
    uint32_t (*calcMaxTxFrameSize)(void* pD, CEDI_FrameSize* maxTxSize);

    /**
     * Add a buffer containing Tx data to the end of the transmit queue.
     * Use repeated calls for multi-buffer frames, setting lastBuffer on
     * the last call, to indicate the end of the frame.
     * @param[in] bufAdd pointer to address of buffer
     * @param[in] flags bit-flags (CEDI_TXB_xx) specifying last buffer/auto CRC
     * @param[in] length length of data in buffer
     * @param[in] pD driver private state info specific to this instance
     * @param[in] queueNum number of Tx queue
     * @return EOK if successful
     * @return ENOENT if no available descriptors
     * @return EINVAL if invalid queueNum, length or buffer alignment, NULL pointers or buffer address
     */
    uint32_t (*queueTxBuf)(void* pD, uint8_t queueNum, CEDI_BuffAddr* bufAdd, uint32_t length, uint8_t flags);

    /**
     * Add a buffer containing Tx data to the end of the transmit queue.
     * Use repeated calls for multi-buffer frames, setting
     * CEDI_TXB_LAST_BUFF in the flags on the last call, to indicate the
     * end of the frame. This function is required for utilising TSO/UFO.
     * @param[in] params pointer to struct for all parameters required by the function
     * @param[in] pD driver private state info specific to this instance
     * @return EOK if successful
     * @return ENOENT if no available descriptors
     * @return EINVAL if invalid queueNum, length or buffer alignment, NULL pointers or buffer address or prm->flags specifies CEDI_TXB_LAST_BUFF at same time as CEDI_TXB_TCP_ENCAP or CEDI_TXB_UDP_ENCAP
     */
    uint32_t (*qTxBuf)(void* pD, CEDI_qTxBufParams* params);

    /**
     * Remove buffer from head of transmit queue in case of error during
     * queueing and free the corresponding descriptor.  Caller must have
     * knowledge of queueing status, i.e. latest frame has not been
     * completed for transmission (first used bit still set) and how many
     * descriptors have been queued for untransmitted frame.
     * @param[in, out] params pointer to struct for parameters to be returned. Not all fields are used - queueNum must be specified, and bufAdd and length are returned
     * @param[in] pD driver private state info specific to this instance
     * @return EOK if successful
     * @return ENOENT if no unfree descriptors
     * @return EINVAL if invalid queueNum or NULL parameters
     */
    uint32_t (*deQTxBuf)(void* pD, CEDI_qTxBufParams* params);

    /**
     * Get number of free descriptors in specified Tx queue
     * @param[out] numFree pointer for returning number of free descriptors
     * @param[in] pD driver private state info specific to this instance
     * @param[in] queueNum number of Tx queue
     * @return EOK if successful
     * @return EINVAL if invalid parameter
     */
    uint32_t (*txDescFree)(void* pD, uint8_t queueNum, uint16_t* numFree);

    /**
     * Read Tx descriptor queue and free used descriptor.\n Struct
     * fields:\n CEDI_BuffAddr bufAdd - addresses of buffer freed up
     * uint32_t txDescStat - descriptor status word. Only valid if first
     * buffer of frame. uint8_t status  - descriptor queue status, one of
     * the following values: CEDI_TXDATA_1ST_NOT_LAST :a first descriptor
     * was freed,                         frame not finished:
     * bufAdd & txDescStat are valid CEDI_TXDATA_1ST_AND_LAST :a first
     * descriptor was freed,                         frame is finished:
     * bufAdd & txDescStat are valid CEDI_TXDATA_MID_BUFFER   :a
     * descriptor was freed,                         (not first in
     * frame),                         frame not finished: bufAdd valid,
     * txDescStat not valid CEDI_TXDATA_LAST_BUFFER  :a descriptor was
     * freed, frame is finished:                         bufAdd valid,
     * txDescStat not valid CEDI_TXDATA_NONE_FREED   :no used descriptor
     * to free:                         bufAdd & txDescStat not valid
     * CEDI_TimeStampData txTsData - Tx descriptor timestamp when valid
     * (txTsData->tsValid will be set to 1).
     * @param[out] descData pointer for returning status & descriptor data
     * @param[in] pD driver private state info specific to this instance
     * @param[in] queueNum number of Tx queue
     * @return EOK if successful (and status is set)
     * @return ENOENT if the queue is empty (status equal CEDI_TXDATA_NONE_FREED)
     * @return EIO if an incomplete frame was detected (no lastBuffer flag in queue)
     * @return EINVAL if any parameter invalid
     */
    uint32_t (*freeTxDesc)(void* pD, uint8_t queueNum, CEDI_TxDescData* descData);

    /**
     * Decode the Tx descriptor status into a bit-field struct
     * @param[in] txDStatWord - Tx descriptor status word
     * @param[in] pD driver private state info specific to this instance
     * @param[out] txDStat - pointer to bit-field struct for decoded status fields
     */
    void (*getTxDescStat)(void* pD, uint32_t txDStatWord, CEDI_TxDescStat* txDStat);

    /**
     * Provides the size of Tx descriptor calculated for current
     * configuration.
     * @param[out] txDescSize - pointer to Tx descriptor size
     * @param[in] pD driver private state info specific to this instance
     */
    void (*getTxDescSize)(void* pD, uint32_t* txDescSize);

    /**
     * Reset transmit buffer queue. Any untransmitted buffer data will be
     * discarded and must be re-queued.  Transmission must be disabled
     * before calling this function.
     * @param[in] pD driver private state info specific to this instance
     * @param[in] queueNum number of Tx queue
     * @return EOK if successful
     * @return EINVAL if invalid parameter
     */
    uint32_t (*resetTxQ)(void* pD, uint8_t queueNum);

    /**
     * Enable & start the transmit circuit. Not required during normal
     * operation, as queueTxBuf will automatically start Tx when complete
     * frame has been queued, but may be used to restart after a Tx
     * error.
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return ECANCELED if no entries in buffer
     */
    uint32_t (*startTx)(void* pD);

    /**
     * Halt transmission as soon as current frame Tx has finished
     * @param[in] pD driver private state info specific to this instance
     */
    void (*stopTx)(void* pD);

    /**
     * Immediately disable transmission without waiting for completion.
     * Since the EMAC will reset to point to the start of transmit
     * descriptor list, the buffer queues may have to be reset after this
     * call.
     * @param[in] pD driver private state info specific to this instance
     */
    void (*abortTx)(void* pD);

    /**
     * Get state of transmitter
     * @param[in] pD driver private state info specific to this instance
     * @return 1 if active
     * @return 0 if idle or pD equal NULL
     */
    uint32_t (*transmitting)(void* pD);

    /**
     * Enable the transmit circuit.  This will be done automatically when
     * call startTx, but it may be desirable to call this earlier, since
     * some functionality depends on transmit being enabled.
     * @param[in] pD driver private state info specific to this instance
     */
    void (*enableTx)(void* pD);

    /**
     * Get state of transmision enabled
     * @param[in] pD driver private state info specific to this instance
     * @return 1 if transmission enabled
     * @return 0 if transmission disabled or pD equal NULL
     */
    uint32_t (*getTxEnabled)(void* pD);

    /**
     * Get the content of EMAC transmit status register
     * @param[out] status pointer to struct with fields for each flag
     * @param[in] pD driver private state info specific to this instance
     * @return 0 if no status bits set or status equal NULL
     * @return number raw Tx status value read
     */
    uint32_t (*getTxStatus)(void* pD, CEDI_TxStatus* status);

    /**
     * Reset the bits of EMAC transmit status register as selected in
     * resetStatus
     * @param[in] resetStatus OR'd combination of CEDI_TXS_ bit-flags
     * @param[in] pD driver private state info specific to this instance
     */
    void (*clearTxStatus)(void* pD, uint32_t resetStatus);

    /**
     * Enable credit-based shaping (CBS) on the specified queue.  If
     * already enabled then first disables, sets a new idle slope value
     * for the queue, and re-enables CBS
     * @param[in] idleSlope new idle slope value (in bytes/sec)
     * @param[in] pD driver private state info specific to this instance
     * @param[in] qSel if =0 selects highest priority queue (queue A), if =1 selects next-highest priority queue (queue B)
     * @return EOK if successful
     * @return ENOTSUP if CBS not present in h/w config
     * @return EINVAL if priority queueing not enabled (i.e. only one Tx queue) or invalid parameter
     */
    uint32_t (*enableCbs)(void* pD, uint8_t qSel, uint32_t idleSlope);

    /**
     * Disable CBS on the specified queue
     * @param[in] pD driver private state info specific to this instance
     * @param[in] qSel if =0 selects highest priority queue (queue A), if =1 selectsnext-highest priority queue (queue B)
     */
    void (*disableCbs)(void* pD, uint8_t qSel);

    /**
     * Read CBS setting for the specified queue.
     * @param[out] enable returns: 1 if CBS enabled for the specified queue 0 if not enabled
     * @param[out] idleSlope pointer for returning the idleSlope value for selected queue.
     * @param[in] pD driver private state info specific to this instance
     * @param[in] qSel if =0 selects highest priority queue (queue A), if =1 selects next-highest priority queue (queue B)
     * @return EOK for success
     * @return ENOTSUP if CBS not present in h/w config
     * @return EINVAL for invalid pointer
     */
    uint32_t (*getCbsQSetting)(void* pD, uint8_t qSel, uint8_t* enable, uint32_t* idleSlope);

    /**
     * Enable/disable the inter-packet gap (IPG) stretch function.
     * @param[in] enable if =1 then enable IPG stretch, if =0 then disable
     * @param[in] divisor after multiplying previous frame length, divide by (divisor+1) - if result>96 bits,
     *    this is used for the Tx IPG. Ignored if enable equal 0.
     * @param[in] pD driver private state info specific to this instance
     * @param[in] multiplier multiplying factor applied to previous Tx frame length.  Ignored if enable equal 0.
     * @return EOK if successful
     * @return EINVAL if pD equal NULL
     */
    uint32_t (*setIpgStretch)(void* pD, uint8_t enable, uint8_t multiplier, uint8_t divisor);

    /**
     * Read the inter-packet gap (IPG) stretch settings.
     * @param[out] enable pointer for returning enabled state: returns 1 if IPG stretch enabled, 0 if disabled.
     * @param[out] divisor pointer for returning IPG divisor
     * @param[in] pD driver private state info specific to this instance
     * @param[out] multiplier pointer for returning IPG multiplying factor
     * @return EOK if successful
     * @return EINVAL if any parameter equal NULL
     */
    uint32_t (*getIpgStretch)(void* pD, uint8_t* enable, uint8_t* multiplier, uint8_t* divisor);

    /**
     * Identify max Rx pkt size for queues - determined by size of Rx
     * packet buffer (if using full store & forward mode), and the
     * current maximum frame size, e.g. 1518, 1536 or jumbo frame.
     * @param[out] maxSize pointer for returning max frame size same for each Rx queue
     * @param[in] pD driver private state info specific to this instance
     * @return EOK if successful
     * @return EINVAL if NULL parameters
     */
    uint32_t (*calcMaxRxFrameSize)(void* pD, uint32_t* maxSize);

    /**
     * Add a buffer (size determined by rxBufLength in CEDI_Config) to
     * the end of the receive buffer queue.  This function is intended to
     * be used during setting up the receive buffers, and should not be
     * called while Rx is enabled or unread data remains in the queue.
     * Note that one extra descriptor is reserved, to provide wrap-around
     * protection (must always have one used bit set).
     * @param[in] init if >0 then initialise the buffer data to all zeros
     * @param[in] buf pointer to address of buffer. Checked for word-alignment in 64/128-bit width cases.
     * @param[in] pD driver private state info specific to this instance
     * @param[in] queueNum number of the Rx queue
     * @return EOK if successful
     * @return EINVAL if invalid queueNum, buffer alignment, or bufStart pointer/addresses
     */
    uint32_t (*addRxBuf)(void* pD, uint8_t queueNum, CEDI_BuffAddr* buf, uint8_t init);

    /**
     * Get the total number of buffers/descriptors present in the
     * specified Rx queue.
     * @param[out] numBufs pointer for returning number of descriptors
     * @param[in] pD driver private state info specific to this instance
     * @param[in] queueNum number of the Rx queue
     * @return EOK if successful
     * @return EINVAL if invalid parameter
     */
    uint32_t (*numRxBufs)(void* pD, uint8_t queueNum, uint16_t* numBufs);

    /**
     * Get the number of buffers/descriptors marked "used" in the
     * specified Rx    queue, i.e. those holding unread data.
     * @param[in] pD driver private state info specific to this instance
     * @param[in] queueNum number of the Rx queue
     * @return 0 if invalid parameter or NULL pointer
     * @return number of used buffers
     */
    uint32_t (*numRxUsed)(void* pD, uint8_t queueNum);

    /**
     * Read first unread descriptor (at tail of queue): if new data is
     * available it swaps out the buffer and replaces it with a new one,
     * clears the descriptor for re-use, then updates the driver queue-
     * pointer. Checks for Start Of Frame (SOF) and End Of Frame (EOF)
     * flags in the descriptors, passing back in status parameter. If EOF
     * set, the descriptor status is returned via rxDescStat.   Struct
     * fields:    uint32_t rxDescStat  - Rx descriptor status word
     * uint8_t status    - Rx data status, one of the following values:
     * CEDI_RXDATA_SOF_EOF  :data available, single-buffer frame (SOF &
     * EOF                            set)      CEDI_RXDATA_SOF_ONLY
     * :data available, start of multi-buffer frame
     * CEDI_RXDATA_NO_FLAG  :data available, intermediate buffer of
     * multi-                            buffer frame
     * CEDI_RXDATA_EOF_ONLY :data available, end of multi-buffer frame
     * CEDI_RXDATA_NODATA   :no data available    CEDI_TimeStampData
     * rxTsData - Rx descriptor timestamp when valid
     * (rxTsData->tsValid will be set to 1)
     * @param[in] init if >0 then initialise the (new) buffer data to all zeros. Ignored if no data available.
     * @param[out] descData pointer for returning status & descriptor data
     * @param[in,out] buf pointer to address of memory for new buffer to add to Rx descriptor queue; if data is available the buffer addresses for this are returned in buf, else if no data available then the new buffer can be re-used. Physical address of buffer is checked for word-alignment in 64/128-bit width cases.
     * @param[in] pD driver private state info specific to this instance
     * @param[in] queueNum number of the Rx queue
     * @return EOK if successful
     * @return EINVAL if invalid queueNum, buf, rxDescStat or status parameters
     */
    uint32_t (*readRxBuf)(void* pD, uint8_t queueNum, CEDI_BuffAddr* buf, uint8_t init, CEDI_RxDescData* descData);

    /**
     * Decode the Rx descriptor status into a bit-field struct.  Note
     * that most of these fields are only valid when End Of Frame bit15
     * is set - see hardware user guide
     * @param[in] rxDStatWord - Rx descriptor status word
     * @param[in] pD driver private state info specific to this instance
     * @param[out] rxDStat pointer to bit-field struct for decoded status fields
     */
    void (*getRxDescStat)(void* pD, uint32_t rxDStatWord, CEDI_RxDescStat* rxDStat);

    /**
     * Provides the size of Rx descriptor calculated for current
     * configuration.
     * @param[out] rxDescSize - pointer to Rx descriptor size
     * @param[in] pD driver private state info specific to this instance
     */
    void (*getRxDescSize)(void* pD, uint32_t* rxDescSize);

    /**
     * Get state of receiver
     * @param[in] pD driver private state info specific to this instance
     * @return 1 if enabled
     * @return 0 if disabled or pD equal NULL
     */
    uint32_t (*rxEnabled)(void* pD);

    /**
     * Enable the receive circuit.
     * @param[in] pD driver private state info specific to this instance
     */
    void (*enableRx)(void* pD);

    /**
     * Disable the receive circuit.
     * @param[in] pD driver private state info specific to this instance
     */
    void (*disableRx)(void* pD);

    /**
     * Remove a buffer from the end of the receive buffer queue.  This
     * function is intended to be used when shutting down the driver,
     * prior to deallocating the receive buffers, and should not be
     * called while Rx is enabled or unread data remains in the queue.
     * @param[out] buf pointer to struct for returning virtual and physical addresses of buffer.
     * @param[in] pD driver private state info specific to this instance
     * @param[in] queueNum number of the Rx queue
     * @return EOK if successful
     * @return ENOENT if no buffers left to free (mechanical success)
     * @return EINVAL if invalid queueNum
     */
    uint32_t (*removeRxBuf)(void* pD, uint8_t queueNum, CEDI_BuffAddr* buf);

    /**
     * Reset Rx buffer descriptor list to initial empty state (if
     * ptrsOnly=0), clearing all descriptors.  For use after a fatal
     * error.  Disables receive circuit.
     * @param[in] ptrsOnly "flag to allow full queue to be reset after link down/up (enableRx).
     *    if =1 then only reset tail & stop pointers and clear used bits"
     * @param[in] pD driver private state info specific to this instance
     * @param[in] queueNum number of the Rx queue
     * @return EOK if successful
     * @return EINVAL if invalid parameter
     */
    uint32_t (*resetRxQ)(void* pD, uint8_t queueNum, uint8_t ptrsOnly);

    /**
     * Return the content of EMAC receive status register
     * @param[out] status pointer to struct with fields for each flag
     * @param[in] pD driver private state info specific to this instance
     * @return 1 if any flags set
     * @return 0 if not or status equal NULL
     */
    uint32_t (*getRxStatus)(void* pD, CEDI_RxStatus* status);

    /**
     * Reset the bits of EMAC receive status register as selected in
     * resetStatus
     * @param[in] resetStatus OR'd combination of CEDI_RXS_ bit-flags
     * @param[in] pD driver private state info specific to this instance
     */
    void (*clearRxStatus)(void* pD, uint32_t resetStatus);

    /**
     * Enable/disable header-data split feature. When enabled, frame
     * L2/L3/L4 headers will written to separate buffer, before data
     * starts in a second buffer (if not zero payload)
     * @param[in] enable if =1 then enable; if =0 then disable
     * @param[in] pD driver private state info specific to this instance
     * @return EOK if success
     * @return EINVAL if invalid parameter
     */
    uint32_t (*setHdrDataSplit)(void* pD, uint8_t enable);

    /**
     * Read enable/disable status for header-data split feature
     * @param[out] enable pointer for returning enabled status
     * @param[in] pD driver private state info specific to this instance
     * @return EOK successful
     * @return EINVAL if invalid parameter
     */
    uint32_t (*getHdrDataSplit)(void* pD, uint8_t* enable);

    /**
     * Enable/disable Receive Segment Coalescing function. When enabled,
     * consecutive TCP/IP frames on a priority queue will be combined to
     * form a single large frame
     * @param[in] queue priority queue to enable or disable RSC on
     * @param[in] enable if =1 enable RSC on selected priority queue(s); else disable it
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return ENOTSUP if feature not available
     * @return EINVAL for invalid parameter
     */
    uint32_t (*setRscEnable)(void* pD, uint8_t queue, uint8_t enable);

    /**
     * Read enabled status of RSC on a specified priority queue
     * @param[in] queue priority queue to read RSC enabled status for
     * @param[out] enable pointer for returning enabled status
     * @param[in] pD driver private state info specific to this instance
     * @return EOK successful
     * @return ENOTSUP if feature not available
     * @return EINVAL if invalid parameter
     */
    uint32_t (*getRscEnable)(void* pD, uint8_t queue, uint8_t* enable);

    /**
     * "Set/Clear Mask of Receive Segment Coalescing disabling. When mask
     * is set and RSC is enabled, the RSC operation is not disabled by
     * receipt of frame with an end-coalesce flag set (SYN/FIN/RST/URG)"
     * @param[in] pD driver private state info specific to this instance
     * @param[in] setMask if =1 prevents RSC disabling by end-coalesce flags (SYN/FIN/RST/URG) - applies to all queues
     * @return EOK for success
     * @return ENOTSUP if feature not available
     * @return EINVAL for invalid pointer
     */
    uint32_t (*setRscClearMask)(void* pD, uint8_t setMask);

    /**
     * Set specific address register to the given address value
     * @param[in] specFilterType flag specifying whether to use MAC source or destination address to be compared for filtering. Source filter when =1.
     * @param[in] addrNum number of specific address filter, in range 1 - num_spec_add_filters
     * @param[in] addr pointer to the 6-byte MAC address value to write
     * @param[in] pD driver private state info specific to this instance
     * @param[in] byteMask Bits masking out bytes of specific address from comparison.
     * @return EOK if success
     * @return ENOTSUP if no specific address registers available
     * @return EINVAL if invalid parameter
     */
    uint32_t (*setSpecificAddr)(void* pD, uint8_t addrNum, CEDI_MacAddress* addr, uint8_t specFilterType, uint8_t byteMask);

    /**
     * Get the value of a specific address register destination address
     * for filtering. When set to 1 use source address.
     * @param[out] specFilterType flag specifying whether to use MAC source or destination address to be
     *    compared for filtering. =1 for source address
     * @param[in] addrNum number of specific address filter, in range 1 - num_spec_add_filters
     * @param[out] addr pointer to a 6-byte MAC address struct for returning the address value
     * @param[in] pD driver private state info specific to this instance
     * @param[out] byteMask "Bits masking out bytes of specific address from comparison.  When high,
     *    the associated address byte will be ignored. e.g. LSB of byteMask=1
     *    implies first byte received should not be compared."
     * @return EOK if success
     * @return ENOTSUP if no specific address registers available
     * @return EINVAL if invalid parameter
     */
    uint32_t (*getSpecificAddr)(void* pD, uint8_t addrNum, CEDI_MacAddress* addr, uint8_t* specFilterType, uint8_t* byteMask);

    /**
     * Set the specific address 1 mask register to the given value,
     * allowing address matching against a portion of the specific
     * address 1 register
     * @param[in] mask pointer to the address mask value to write
     * @param[in] pD driver private state info specific to this instance
     * @return EOK if successful
     * @return ENOTSUP if CEDI_DesignCfg.num_spec_add_filters==0
     * @return EINVAL if mask equal NULL
     */
    uint32_t (*setSpecificAddr1Mask)(void* pD, CEDI_MacAddress* mask);

    /**
     * Get the value of specific address 1 mask register
     * @param[out] mask pointer to a 6-byte MAC address struct for returning the mask value
     * @param[in] pD driver private state info specific to this instance
     * @return EOK if successful
     * @return ENOTSUP if CEDI_DesignCfg.num_spec_add_filters==0
     * @return EINVAL if mask equal NULL
     */
    uint32_t (*getSpecificAddr1Mask)(void* pD, CEDI_MacAddress* mask);

    /**
     * Disable the specific address match stored at given register, by
     * writing 0 to lower address register
     * @param[in] addrNum - number of specific address filters, in range 1 - num_spec_add_filters
     * @param[in] pD - driver private state info specific to this instance
     * @return EOK if successful
     * @return ENOTSUP if (CEDI_DesignCfg.num_spec_add_filters==0)
     * @return EINVAL if ((addrNum==0) || (addrNum>CEDI_DesignCfg.num_spec_add_filters))
     */
    uint32_t (*disableSpecAddr)(void* pD, uint8_t addrNum);

    /**
     * En/Disable Type ID match field of the specified register, and set
     * type Id value if enabling
     * @param[in] typeId the Type ID match value to write ignored if enable equal 0
     * @param[in] enable if =1 enables the type matching for this ID, if =0 then disables type matching for this ID
     * @param[in] matchSel number of TypeID Match register, range 1 - 4
     * @param[in] pD driver private state info specific to this instance
     * @return EOK if successful
     * @return EINVAL if matchSel invalid
     */
    uint32_t (*setTypeIdMatch)(void* pD, uint8_t matchSel, uint16_t typeId, uint8_t enable);

    /**
     * Read the specified Type ID match register settings
     * @param[out] typeId pointer for returning the Type ID match value read ignored if disabled
     * @param[out] enable "pointer for returning enabled status: equal 1 if typeId matching is
     *    enabled for this register, equal 0 if disabled"
     * @param[in] matchSel number of TypeID Match register, range 1 - 4
     * @param[in] pD driver private state info specific to this instance
     * @return EOK if successful
     * @return EINVAL if matchSel invalid
     */
    uint32_t (*getTypeIdMatch)(void* pD, uint8_t matchSel, uint16_t* typeId, uint8_t* enable);

    /**
     * En/disable reception of unicast frames when hash register matched
     * @param[in] enable if =1 enables reception, if =0 then disables
     * @param[in] pD driver private state info specific to this instance
     */
    void (*setUnicastEnable)(void* pD, uint8_t enable);

    /**
     * Return state of unicast frame matching
     * @param[out] enable equal 1 if reception enabled, equal 0 if disabled
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return EINVAL for invalid pointer
     */
    uint32_t (*getUnicastEnable)(void* pD, uint8_t* enable);

    /**
     * En/disable reception of multicast frames when hash register
     * matched
     * @param[in] enable if =1 enables, if =0 then disables
     * @param[in] pD driver private state info specific to this instance
     */
    void (*setMulticastEnable)(void* pD, uint8_t enable);

    /**
     * Return state of multicast frame matching
     * @param[out] enable equal 1 if enabled, equal 0 if disabled
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return EINVAL for invalid pointer
     */
    uint32_t (*getMulticastEnable)(void* pD, uint8_t* enable);

    /**
     * Dis/Enable receipt of broadcast frames
     * @param[in] pD driver private state info specific to this instance
     * @param[in] reject if =0 broadcasts are accepted, if =1 they are rejected.
     */
    void (*setNoBroadcast)(void* pD, uint8_t reject);

    /**
     * Return broadcast rejection setting
     * @param[in] pD driver private state info specific to this instance
     * @param[out] reject returns 0 if broadcasts are accepted, 1 if they are rejected
     * @return EOK for success
     * @return EINVAL for invalid pointer
     */
    uint32_t (*getNoBroadcast)(void* pD, uint8_t* reject);

    /**
     * En/Disable receipt of only frames which have been VLAN tagged
     * @param[in] enable if =1 reject non-VLAN-tagged frames, if =0 then accept
     * @param[in] pD driver private state info specific to this instance
     */
    void (*setVlanOnly)(void* pD, uint8_t enable);

    /**
     * Return VLAN-tagged filter setting
     * @param[out] enable returns 1 if non-VLAN-tagged frames rejected
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return EINVAL for invalid pointer
     */
    uint32_t (*getVlanOnly)(void* pD, uint8_t* enable);

    /**
     * En/Disable stacked VLAN processing mode.
     * @param[in] enable if =1 enables stacked VLAN processing, if =0 disables it
     * @param[in] pD driver private state info specific to this instance
     * @param[in] vlanType sets user defined VLAN type for matching first VLAN tag. Ignored if enable equal 0.
     */
    void (*setStackedVlanReg)(void* pD, uint8_t enable, uint16_t vlanType);

    /**
     * Reads stacked VLAN register settings.
     * @param[out] enable pointer for returning Enabled field equal 1 if enabled equal 0 if disabled.
     * @param[in] pD driver private state info specific to this instance
     * @param[out] vlanType pointer for returning VLAN type field
     */
    void (*getStackedVlanReg)(void* pD, uint8_t* enable, uint16_t* vlanType);

    /**
     * En/Disable copy all frames mode
     * @param[in] enable if =1 enables copy all frames mode, if =0 then this is disabled
     * @param[in] pD driver private state info specific to this instance
     */
    void (*setCopyAllFrames)(void* pD, uint8_t enable);

    /**
     * Get "copy all" setting
     * @param[out] enable equal 1 if copy all frames mode enabled equal 0 if this is disabled
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return EINVAL for invalid pointer
     */
    uint32_t (*getCopyAllFrames)(void* pD, uint8_t* enable);

    /**
     * Set the hash address register.
     * @param[in] hAddrBot least significant 32 bits of hash register
     * @param[in] hAddrTop most significant 32 bits of hash register
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return EINVAL if pD equal NULL
     */
    uint32_t (*setHashAddr)(void* pD, uint32_t hAddrTop, uint32_t hAddrBot);

    /**
     * Read the hash address register.
     * @param[out] hAddrBot pointer for returning least significant 32 bits of hash register
     * @param[out] hAddrTop pointer for returning most significant 32 bits of hash register
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return EINVAL if any parameter equal NULL
     */
    uint32_t (*getHashAddr)(void* pD, uint32_t* hAddrTop, uint32_t* hAddrBot);

    /**
     * Enable/disable discard of frames with length shorter than given in
     * length field
     * @param[in] enable if =1 then enable, if =0 then disable
     * @param[in] pD driver private state info specific to this instance
     */
    void (*setLenErrDiscard)(void* pD, uint8_t enable);

    /**
     * Read enable/disable status for discard of frames with length
     * shorter than given in length field.
     * @param[out] enable equal 1 if enabled, equal 0 if disabled
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return EINVAL for invalid pointer
     */
    uint32_t (*getLenErrDiscard)(void* pD, uint8_t* enable);

    /**
     * Read numbers of screener, ethtype & compare registers
     * @param[out] regNums points to a CEDI_NumScreeners struct for returning the numbers of registers
     * @param[in] pD driver private state info specific to this instance
     * @return EOK if successful
     * @return EINVAL if parameter invalid
     */
    uint32_t (*getNumScreenRegs)(void* pD, CEDI_NumScreeners* regNums);

    /**
     * Write Rx frame matching values to a Type 1 screening register, for
     * allocating to a priority queue.
     * @param[in] regNum Type 1 register number, range 0 to CEDI_DesignCfg.num_type1_screeners-1
     * @param[in] regVals points to a CEDI_T1Screen struct with the match parameters to be written
     * @param[in] pD driver private state info specific to this instance
     * @return EOK if successful
     * @return EINVAL if parameter invalid
     */
    uint32_t (*setType1ScreenReg)(void* pD, uint8_t regNum, CEDI_T1Screen* regVals);

    /**
     * Read Rx frame matching values from a Type1 screening register
     * @param[in] regNum Type 1 register number, range 0 to CEDI_DesignCfg.num_type1_screeners-1
     * @param[out] regVals points to a CEDI_T1Screen struct for returning the match parameters
     * @param[in] pD driver private state info specific to this instance
     * @return EOK if successful
     * @return EINVAL if parameter invalid
     */
    uint32_t (*getType1ScreenReg)(void* pD, uint8_t regNum, CEDI_T1Screen* regVals);

    /**
     * Write Rx frame matching values to a Type 2 screening register, for
     * allocating to a priority queue.
     * @param[in] regNum Type 2 register number, range 0 to CEDI_DesignCfg.num_type2_screeners-1
     * @param[in] regVals points to a CEDI_T2Screen struct with the match parameters to be written
     * @param[in] pD driver private state info specific to this instance
     * @return EOK if successful
     * @return EINVAL if parameter invalid
     */
    uint32_t (*setType2ScreenReg)(void* pD, uint8_t regNum, CEDI_T2Screen* regVals);

    /**
     * Read Rx frame matching values from a Type 2 screening register
     * @param[in] regNum Type 2 register number, range 0 to CEDI_DesignCfg.num_type2_screeners-1
     * @param[out] regVals points to a CEDI_T2Screen struct for returning the match parameters
     * @param[in] pD driver private state info specific to this instance
     * @return EOK if successful
     * @return EINVAL if parameter invalid
     */
    uint32_t (*getType2ScreenReg)(void* pD, uint8_t regNum, CEDI_T2Screen* regVals);

    /**
     * Write the ethertype compare value at the given index in the
     * Ethertype registers
     * @param[in] index Type 2 ethertype register number, range 0 to CEDI_DesignCfg.num_scr2_ethtype_regs-1
     * @param[in] eTypeVal Ethertype compare value to write
     * @param[in] pD driver private state info specific to this instance
     * @return EOK if successful
     * @return EINVAL if parameter invalid
     */
    uint32_t (*setType2EthertypeReg)(void* pD, uint8_t index, uint16_t eTypeVal);

    /**
     * Read the ethertype compare value at the given index in the
     * Ethertype registers
     * @param[in] index Type 2 ethertype register number, range 0 to CEDI_DesignCfg.num_scr2_ethtype_regs-1
     * @param[out] eTypeVal pointer for returning the Ethertype compare value
     * @param[in] pD driver private state info specific to this instance
     * @return EOK if successful
     * @return EINVAL if parameter invalid
     */
    uint32_t (*getType2EthertypeReg)(void* pD, uint8_t index, uint16_t* eTypeVal);

    /**
     * Write the compare value at the given index in the Type 2 compare
     * register
     * @param[in] index Type 2 compare register number, range 0 to CEDI_DesignCfg.num_scr2_compare_regs-1
     * @param[in] regVals points to a CEDI_T2Compare struct with the compare parameters to be written
     * @param[in] pD driver private state info specific to this instance
     * @return EOK if successful
     * @return EINVAL if parameter invalid
     */
    uint32_t (*setType2CompareReg)(void* pD, uint8_t index, CEDI_T2Compare* regVals);

    /**
     * Read the compare value at the given index in the Type 2 compare
     * register
     * @param[in] index Type 2 compare register number, range 0 to CEDI_DesignCfg.num_scr2_compare_regs-1
     * @param[out] regVals points to a CEDI_T2Compare struct for returning the compare parameters
     * @param[in] pD driver private state info specific to this instance
     * @return EOK if successful
     * @return EINVAL if parameter invalid
     */
    uint32_t (*getType2CompareReg)(void* pD, uint8_t index, CEDI_T2Compare* regVals);

    /**
     * Enable/disable pausing after valid non-zero (non-PFC) pause frame
     * received
     * @param[in] enable if =1 then enable, if =0 then disable
     * @param[in] pD driver private state info specific to this instance
     */
    void (*setPauseEnable)(void* pD, uint8_t enable);

    /**
     * Read enable/disable of pausing after valid non-zero (non-PFC)
     * pause frame received.
     * @param[out] enable equal 1 if enabled, equal 0 if disabled
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return EINVAL for invalid pointer
     */
    uint32_t (*getPauseEnable)(void* pD, uint8_t* enable);

    /**
     * Transmit a normal pause frame
     * @param[in] pD driver private state info specific to this instance
     */
    void (*txPauseFrame)(void* pD);

    /**
     * Transmit a pause frame with zero quantum value
     * @param[in] pD driver private state info specific to this instance
     */
    void (*txZeroQPause)(void* pD);

    /**
     * Return the current value of received pause quantum
     * @param[out] value returns transmit pause quantum value
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return EINVAL for invalid pointer
     */
    uint32_t (*getRxPauseQuantum)(void* pD, uint16_t* value);

    /**
     * Set the pause quantum value to use when transmitting non-zero
     * quantum pause frame.
     * @param[in] qpriority quantum priority, the priority for the pause quantum
     * @param[in] value transmit pause quantum value
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return EINVAL if invalid parameter
     */
    uint32_t (*setTxPauseQuantum)(void* pD, uint16_t value, uint8_t qpriority);

    /**
     * Read the non-zero transmit pause quantum value
     * @param[in] qpriority quantum priority,the priority for the pause quantum
     * @param[out] value returns transmit pause quantum value
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return EINVAL if invalid parameter
     */
    uint32_t (*getTxPauseQuantum)(void* pD, uint16_t* value, uint8_t qpriority);

    /**
     * Disable/Enable copying of valid Rx pause frames to memory.
     * @param[in] disable if =1 disable, if =0 enable
     * @param[in] pD driver private state info specific to this instance
     */
    void (*setCopyPauseDisable)(void* pD, uint8_t disable);

    /**
     * Read disable/enable state for copying of valid Rx pause frames to
     * memory.
     * @param[out] disable if =1 disabled, if =0 enabled
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return EINVAL for invalid pointer
     */
    uint32_t (*getCopyPauseDisable)(void* pD, uint8_t* disable);

    /**
     * Enable/disable PFC negotiation and reception of priority based
     * pause frames.
     * @param[in] enable if =1 enable, if =0 then disable
     * @param[in] pD driver private state info specific to this instance
     */
    void (*setPfcPriorityBasedPauseRx)(void* pD, uint8_t enable);

    /**
     * Read enable/disable state of reception for priority based pause
     * frames, and negotiation state. value can be decoded with two
     * constants:   if (OR with CEDI_PFC_PBP_RX_EN) not equal 0 then
     * PFC priority based pause frame Rx enabled   if (OR with
     * CEDI_PFC_PBP_NEG) not equal 0 then     PFC priority based pause
     * has been negotiated
     * @param[out] enable returns combined enabled Rx state and negotiated state
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return EINVAL for invalid pointer
     */
    uint32_t (*getPfcPriorityBasedPauseRx)(void* pD, uint8_t* enable);

    /**
     * Transmit PFC Priority Based Pause Frame, taking field values as
     * defined by setTxPfcPauseFrameFields.
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return EINVAL if NULL pointer or not using full duplex mode or if transmission is disabled (mechanical success)
     */
    uint32_t (*txPfcPriorityBasedPause)(void* pD);

    /**
     * Set priority enable vector and zero quantum select vector fields
     * of the Tx PFC Pause Frame (see User Guide for description)
     * @param[in] priEnVector written to priority enable vector of PFC priority based pause frame
     * @param[in] zeroQSelVector selects pause quantum fields to set to zero
     * @param[in] pD driver private state info specific to this instance
     * @return EOK if successful
     * @return EINVAL if pD equal NULL
     */
    uint32_t (*setTxPfcPauseFrameFields)(void* pD, uint8_t priEnVector, uint8_t zeroQSelVector);

    /**
     * Read priority enable vector and zero quantum select vector fields
     * selected by setTxPfcPauseFrameFields.
     * @param[out] priEnVector pointer for returning priority enable vector to be written to PFC priority based pause frame
     * @param[out] zeroQSelVector pointer for returning vector selecting pause quantum fields to set to zero
     * @param[in] pD driver private state info specific to this instance
     * @return EOK if successful
     * @return EINVAL if any parameter equal NULL
     */
    uint32_t (*getTxPfcPauseFrameFields)(void* pD, uint8_t* priEnVector, uint8_t* zeroQSelVector);

    /**
     * Set Enable bit for multiple PFC pause quantums, one per pause
     * priority.
     * @param[in] enMultiPfcPause set this field to 1 to enable multiple PFC pause quantums.
     * @param[in] pD driver private state info specific to this instance
     * @return EOK if successful
     * @return EINVAL if pD equal NULL
     */
    uint32_t (*setEnableMultiPfcPauseQuantum)(void* pD, uint8_t enMultiPfcPause);

    /**
     * Get the Enable bit for multiple PFC pause quantums, one per pause
     * priority.
     * @param[out] enMultiPfcPause equal 1 if multiple PFC pause quantums enabled
     * @param[in] pD driver private state info specific to this instance
     * @return EOK if successful
     * @return EINVAL if any parameter equal NULL
     */
    uint32_t (*getEnableMultiPfcPauseQuantum)(void* pD, uint8_t* enMultiPfcPause);

    /**
     * Enable/disable detection of unicast PTP frames.
     * @param[in] enable if =1 enable, if =0 then disable
     * @param[in] pD driver private state info specific to this instance
     */
    void (*setUnicastPtpDetect)(void* pD, uint8_t enable);

    /**
     * Read enable/disable state for detection of unicast PTP frames.
     * @param[out] enable equal 1 if enabled, equal 0 if disabled
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return EINVAL for invalid pointer
     */
    uint32_t (*getUnicastPtpDetect)(void* pD, uint8_t* enable);

    /**
     * Set Unicast IP destination address for detection of PTP Rx frames.
     * Unicast PTP frame recognition must be disabled.
     * @param[in] rxAddr IP destination address
     * @param[in] pD driver private state info specific to this instance
     * @return EOK if successful
     * @return ENOTSUP if unicast PTP frame recognition enabled
     * @return EINVAL if pD = NULL
     */
    uint32_t (*setPtpRxUnicastIpAddr)(void* pD, uint32_t rxAddr);

    /**
     * Read Unicast IP destination address for detection of PTP Rx
     * frames.
     * @param[out] rxAddr returns IP destination address
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return EINVAL for invalid pointer
     */
    uint32_t (*getPtpRxUnicastIpAddr)(void* pD, uint32_t* rxAddr);

    /**
     * Set Unicast IP destination address for detection of PTP Tx frames.
     * Unicast PTP frame recognition must be disabled.
     * @param[in] txAddr IP destination address
     * @param[in] pD driver private state info specific to this instance
     * @return EOK if successful
     * @return ENOTSUP if unicast PTP frame recognition enabled
     * @return EINVAL if pD = NULL
     */
    uint32_t (*setPtpTxUnicastIpAddr)(void* pD, uint32_t txAddr);

    /**
     * Returns Unicast IP destination address for detection of PTP Tx
     * frames.
     * @param[out] txAddr returns IP destination address
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return EINVAL for invalid pointer
     */
    uint32_t (*getPtpTxUnicastIpAddr)(void* pD, uint32_t* txAddr);

    /**
     * Write 1588 timer registers.
     * @param[in] pD driver private state info specific to this instance
     * @param[in] time pointer to CEDI_1588TimerVal struct with values to write to timer registers
     * @return EOK for success
     * @return ENOTSUP if tsu equal 0
     * @return EINVAL if either parameter equal NULL, or nanosecs >0x3FFFFFFF
     */
    uint32_t (*set1588Timer)(void* pD, CEDI_1588TimerVal* time);

    /**
     * Read 1588 timer registers.
     * @param[in] pD driver private state info specific to this instance
     * @param[out] time pointer to a CEDI_1588TimerVal struct for returning timer registers contents
     * @return EOK for success
     * @return ENOTSUP if tsu equal 0
     * @return EINVAL if either parameter NULL
     */
    uint32_t (*get1588Timer)(void* pD, CEDI_1588TimerVal* time);

    /**
     * Adjust the 1588 timer by adding or subtracting the specified
     * number of nanoseconds.
     * @param[in] nSecAdjust nanoseconds to adjust timer by: - if =1, enable time stamp storing, else disable (restore normal operation)
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return ENOTSUP if tsu equal 0
     * @return EINVAL if invalid parameter
     */
    uint32_t (*adjust1588Timer)(void* pD, int32_t nSecAdjust);

    /**
     * Set 1588 timer initial and alternative increments, and when to
     * switch to alternative increment. The initial, or normal, increment
     * is how many nanoseconds are added to the timer value on each pclk
     * or tsu_clk cycle (if tsu_clk equal 1 in DesignCfgReg5). If
     * altIncCount>0, after altIncCount increments the altNanoSInc value
     * is used for one cycle, then the increment returns to the initial
     * value. See EMAC User Guide [01] for further description.
     * @param[in] incSettings pointer to CEDI_TimerIncrement struct for defining how much to increment the timer each clock cycle
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return ENOTSUP if tsu equal 0
     * @return EINVAL if either parameter equal NULL
     */
    uint32_t (*set1588TimerInc)(void* pD, CEDI_TimerIncrement* incSettings);

    /**
     * Read 1588 timer increment settings.
     * @param[out] incSettings pointer to a CEDI_TimerIncrement struct for returning how the timer increment values
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return ENOTSUP if tsu equal 0
     */
    uint32_t (*get1588TimerInc)(void* pD, CEDI_TimerIncrement* incSettings);

    /**
     * Write TSU timer comparison value.
     * @param[in] pD driver private state info specific to this instance
     * @param[in] time pointer to CEDI_TsuTimerVal struct with values to write to comparison registers
     * @return EOK for success
     * @return ENOTSUP if tsu equal 0, or nanosecs >0x003FFFFF
     */
    uint32_t (*setTsuTimerCompVal)(void* pD, CEDI_TsuTimerVal* time);

    /**
     * Read TSU timer comparison value.
     * @param[in] pD driver private state info specific to this instance
     * @param[out] time pointer to a CEDI_TsuTimerVal struct for returning comparison registers settings
     * @return EOK for success
     * @return ENOTSUP if tsu equal 0
     * @return EINVAL if either param equal NULL
     */
    uint32_t (*getTsuTimerCompVal)(void* pD, CEDI_TsuTimerVal* time);

    /**
     * Read 1588 timer value latched when SFD of PTP transmit primary
     * event crosses MII interface.
     * @param[in] pD driver private state info specific to this instance
     * @param[out] time pointer to a CEDI_1588TimerVal struct for returning latched timer registers contents.
     * @return EOK for success
     * @return ENOTSUP if tsu equal 0
     */
    uint32_t (*getPtpFrameTxTime)(void* pD, CEDI_1588TimerVal* time);

    /**
     * Read 1588 timer value latched when SFD of PTP receive primary
     * event crosses MII interface.
     * @param[in] pD driver private state info specific to this instance
     * @param[out] time pointer to a CEDI_1588TimerVal struct for returning latched timer registers contents.
     * @return EOK for success
     * @return ENOTSUP if tsu equal 0
     */
    uint32_t (*getPtpFrameRxTime)(void* pD, CEDI_1588TimerVal* time);

    /**
     * Read 1588 timer value latched when SFD of PTP transmit peer event
     * crosses MII interface.
     * @param[in] pD driver private state info specific to this instance
     * @param[out] time pointer to a CEDI_1588TimerVal struct for returning latched timer registers contents.
     * @return EOK for success
     * @return ENOTSUP if tsu equal 0
     */
    uint32_t (*getPtpPeerFrameTxTime)(void* pD, CEDI_1588TimerVal* time);

    /**
     * Read 1588 timer value latched when SFD of PTP receive peer event
     * crosses MII interface.
     * @param[in] pD driver private state info specific to this instance
     * @param[out] time pointer to a CEDI_1588TimerVal struct for returning latched timer registers contents.
     * @return EOK for success
     * @return ENOTSUP if tsu equal 0
     */
    uint32_t (*getPtpPeerFrameRxTime)(void* pD, CEDI_1588TimerVal* time);

    /**
     * Read nanoseconds and seconds (lo & hi words) from 1588 Timer Sync
     * Strobe registers
     * @param[in] pD driver private state info specific to this instance
     * @param[out] time pointer to a CEDI_1588TimerVal struct for returning latched timer registers contents.
     * @return EOK for success
     * @return ENOTSUP if tsu equal 0
     */
    uint32_t (*get1588SyncStrobeTime)(void* pD, CEDI_1588TimerVal* time);

    /**
     * Enable/disable use of external time stamp port.
     * @param[in] enable if =1 then enable, if =0 then disable
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return ENOTSUP if ext_tsu_timer equal 0
     * @return EINVAL if invalid parameter
     */
    uint32_t (*setExtTsuPortEnable)(void* pD, uint8_t enable);

    /**
     * Read enable status for use of external time stamp port.
     * @param[out] enable equal 1 if enabled, equal 0 if disabled
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return EINVAL for invalid pointer
     */
    uint32_t (*getExtTsuPortEnable)(void* pD, uint8_t* enable);

    /**
     * Enable/disable one-step Tx sync mode in which timestamp field of
     * every transmitted 1588 sync frame is replaced with the current TSU
     * timestamp.
     * @param[in] enable if =1 then enable, if =0 then disable
     * @param[in] pD driver private state info specific to this instance
     * @return EOK if successful
     * @return ENOTSUP if tsu equal 0
     * @return EINVAL if invalid parameter
     */
    uint32_t (*set1588OneStepTxSyncEnable)(void* pD, uint8_t enable);

    /**
     * Read enable/disable state of one-step 1588 Tx sync mode.
     * @param[out] enable pointer for returning state equal 1 if enabled equal 0 if disabled.
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return EINVAL for invalid pointer
     */
    uint32_t (*get1588OneStepTxSyncEnable)(void* pD, uint8_t* enable);

    /**
     * Set the descriptor time stamp mode.
     * @param[in] txMode TX Descriptor timestamp insertion mode
     * @param[in] rxMode RX Descriptor timestamp insertion mode
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return EINVAL if pD is NULL/parameters out of range
     */
    uint32_t (*setDescTimeStampMode)(void* pD, CEDI_TxTsMode txMode, CEDI_RxTsMode rxMode);

    /**
     * Get the descriptor time stamp mode.
     * @param[out] txMode TX Descriptor timestamp insertion mode
     * @param[out] rxMode RX Descriptor timestamp insertion mode
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return EINVAL if pD is NULL
     */
    uint32_t (*getDescTimeStampMode)(void* pD, CEDI_TxTsMode* txMode, CEDI_RxTsMode* rxMode);

    /**
     * Enable/disable storing of nanoseconds field of Rx time stamp in
     * CRC field of received frame.
     * @param[in] enable if =1 then enable, if =0 then disable
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return ENOTSUP if tsu equal 0
     */
    uint32_t (*setStoreRxTimeStamp)(void* pD, uint8_t enable);

    /**
     * Read Enable/disable state for storing nanoseconds Rx time stamp in
     * CRC field of received frame.
     * @param[out] enable equal 1 if time stamp storing enabled equal 0 if disabled
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return EINVAL for invalid pointer
     */
    uint32_t (*getStoreRxTimeStamp)(void* pD, uint8_t* enable);

    /**
     * Does a PCS reset. After this, software can monitor getPcsReady to
     * determine when this has finished.
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return ENOTSUP if no_pcs defined
     */
    uint32_t (*resetPcs)(void* pD);

    /**
     * Read PCS software reset bit, which goes high when resetPcs is
     * called, and returns low when the reset has completed, provided PCS
     * is enabled.
     * @param[out] ready pointer for returning 1 when PCS ready, i.e. reset has gone low or 0 if still in reset.
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return ENOTSUP if PCS not enabled
     * @return EINVAL for invalid pointer
     */
    uint32_t (*getPcsReady)(void* pD, uint8_t* ready);

    /**
     * Enables and restarts auto-negotiation after writing the specified
     * abilities to the auto-negotiation advertisement register.  After
     * this, normal progress of auto-negotiation will lead to a lpPageRx
     * callback, which includes the ability register data received from
     * the link partner.
     * @param[in] advDat pointer to CEDI_AnAdvPage struct for setting the advertised abilities register
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return ENOTSUP if no_pcs defined or in SGMII mode
     * @return EBUSY if auto-negotiation already in progress
     * @return EINVAL if NULL parameter, invalid struct fields or completion event not enabled
     */
    uint32_t (*startAutoNegotiation)(void* pD, CEDI_AnAdvPage* advDat);

    /**
     * Enable/disable PCS auto-negotiation functionality.  If auto-
     * negotiation is in progress,  disabling will halt it.  If enabling
     * while underway, an error is returned.
     * @param[in] enable if =1 then enable, if =0 then disable
     * @param[in] pD driver private state info specific to this instance
     * @return EBUSY if enable = 1 when auto-negotiation is under way
     * @return EOK for success
     * @return ENOTSUP if in SGMII mode
     * @return EINVAL if pD equal NULL
     */
    uint32_t (*setAutoNegEnable)(void* pD, uint8_t enable);

    /**
     * Read enable/disable of PCS auto-negotiation functionality.
     * @param[out] enable pointer for returning state, equal 1 if enabled equal 0 if disabled.
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return ENOTSUP if (CEDI_DesignCfg.no_pcs==1)
     * @return EINVAL if NULL parameter
     */
    uint32_t (*getAutoNegEnable)(void* pD, uint8_t* enable);

    /**
     * If auto-negotiation is enabled, this reads the status of
     * connection to link partner, else it reads the synchronisation
     * status. If link goes down, status remains low until this is read.
     * The driver will remember the low condition when read from register
     * (by this or other PCS functions), and this will only update to
     * current state when this function is called (i.e. after reading the
     * value to return), or when link status is reported via the
     * AnComplete callback. Therefore, if getLinkStatus reports link
     * down, the function should be called again if the current status is
     * required.
     * @param[out] status pointer returning 1 if link up (or sync) 0 if link down.
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return EINVAL for invalid pointer
     */
    uint32_t (*getLinkStatus)(void* pD, uint8_t* status);

    /**
     * Read the remote fault status reported by link partner. Driver will
     * remember the high state when read from register, and only reset
     * when this function is called.
     * @param[out] status pointer returning 1 if remote fault indicated by link partner, 0 otherwise.
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return EINVAL for invalid pointer
     */
    uint32_t (*getAnRemoteFault)(void* pD, uint8_t* status);

    /**
     * Read the auto-negotiation complete status. Completion will also be
     * reported by the anComplete callback, provided the
     * CEDI_EV_PCS_AN_COMPLETE interrupt is enabled.
     * @param[out] status pointer returning 1 if auto-negotiation complete 0 if incomplete.
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return ENOTSUP if (CEDI_DesignCfg.no_pcs==1)
     * @return EINVAL for invalid pointer
     */
    uint32_t (*getAnComplete)(void* pD, uint8_t* status);

    /**
     * Set advertisement base page fields.
     * @param[in] advDat - pointer to advertisement register data
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return ENOTSUP if (CEDI_DesignCfg.no_pcs==1)
     * @return EINVAL if NULL parameter
     */
    uint32_t (*setAnAdvPage)(void* pD, CEDI_AnAdvPage* advDat);

    /**
     * Get advertisement base page fields, extracted into a
     * CEDI_AnAdvPage struct
     * @param[out] advDat - pointer for returning the advertisement register data
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return ENOTSUP if (CEDI_DesignCfg.no_pcs==1)
     * @return EINVAL if NULL parameter
     */
    uint32_t (*getAnAdvPage)(void* pD, CEDI_AnAdvPage* advDat);

    /**
     * Get link partner ability page fields, extracted into a
     * CEDI_LpAbilityPage struct.  This is a union of two different
     * structs, since the format depends on whether SGMII mode is in use
     * (network config bit 27)
     * @param[out] lpAbl pointer for returning the link partner ability data
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return ENOTSUP if (CEDI_DesignCfg.no_pcs==1)
     * @return EINVAL if NULL parameter
     */
    uint32_t (*getLpAbilityPage)(void* pD, CEDI_LpAbilityPage* lpAbl);

    /**
     * Read flag from auto-negotiation expansion register, indicating a
     * base or next page has been received from the link partner.
     * @param[in] pD driver private state info specific to this instance
     * @return 1 if page received and no_pcs not defined
     * @return 0 if page not received or invalid pointer
     */
    uint32_t (*getPageRx)(void* pD);

    /**
     * Set next page register fields for auto-negotiation with fields
     * specified in a CEDI_AnNextPage struct.
     * @param[in] npDat - pointer to struct containing next page data to transmit
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return ENOTSUP if (CEDI_DesignCfg.no_pcs==1)
     * @return EINVAL if NULL parameter or invalid struct fields
     */
    uint32_t (*setNextPageTx)(void* pD, CEDI_AnNextPage* npDat);

    /**
     * Read next page register field data.
     * @param[out] npDat - pointer to struct for returning next page register data.
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return ENOTSUP if (CEDI_DesignCfg.no_pcs==1)
     * @return EINVAL if NULL parameter
     */
    uint32_t (*getNextPageTx)(void* pD, CEDI_AnNextPage* npDat);

    /**
     * Read next page data received from link partner.
     * @param[out] npDat - pointer to CEDI_LpNextPage struct for returning link partner next page data.
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return ENOTSUP if (CEDI_DesignCfg.no_pcs==1)
     * @return EINVAL if NULL parameter
     */
    uint32_t (*getLpNextPage)(void* pD, CEDI_LpNextPage* npDat);

    /**
     * Get PCS PHY upper ID (= EMAC Module ID) & PCS PHY lower ID (= EMAC
     * Rev)
     * @param[in] pD driver private state info specific to this instance
     * @param[out] phyId composed of PCS PHY upper ID (= EMAC Module ID) in the upper 16 bits, and PCS PHY
     *    lower ID (= EMAC Rev) in the lower 16 bits.
     * @return EOK for success
     * @return EINVAL for invalid pointer
     */
    uint32_t (*getPhyId)(void* pD, uint32_t* phyId);

    /**
     * Enable/disable MDIO interface
     * @param[in] enable if =1 enable MDIO interface, if =0 then disable it
     * @param[in] pD driver private state info specific to this instance
     */
    void (*setMdioEnable)(void* pD, uint8_t enable);

    /**
     * Get en/disable state of MDIO interface
     * @param[in] pD driver private state info specific to this instance
     * @return 1 if MDIO interface enabled
     * @return 0 if MDIO interface disabled or pD equal NULL, or NULL parameter
     */
    uint32_t (*getMdioEnable)(void* pD);

    /**
     * Initiate a write or set address operation on the MDIO interface.
     * Clause 45 devices require a call to set the register address (if
     * this is changing since last access), and then a write or read
     * operation. The command writes to the shift register, which starts
     * output on the MDIO interface. Write completion is signalled by the
     * phyManComplete callback, or by polling getMdioIdle.
     * @param[in] addrData register address (if CEDI_MDIO_FLG_SET_ADDR) or data to write
     * @param[in] phyAddr PHY address
     * @param[in] flags Combination of 2 bit-flags: if CEDI_MDIO_FLG_CLAUSE_45 present, specifies
     *    clause 45 PHY (else clause 22);
     *    if CEDI_MDIO_FLG_SET_ADDR present, specifies a set address operation (else
     *    do a write operation) - if not clause 45, this will be ignored.
     * @param[in] pD driver private state info specific to this instance
     * @param[in] devReg device type (clause 45) or register address (clause 22) - enum CEDI_MdioDevType
     *    is available to specify the device type
     */
    void (*phyStartMdioWrite)(void* pD, uint8_t flags, uint8_t phyAddr, uint8_t devReg, uint16_t addrData);

    /**
     * Initiate a read operation on the MDIO interface.  If clause 45,
     * the register address will need to be set by a preceding
     * phyStartMdioWrite call, unless same as for last operation.
     * Completion is signalled by the phyManComplete callback, which will
     * return the read data by a pointer parameter. Alternatively polling
     * getMdioIdle will indicate when the operation completes, then
     * getMdioReadDat will return the data.
     * @param[in] phyAddr PHY address
     * @param[in] flags Combination of 2 bit-flags: if CEDI_MDIO_FLG_CLAUSE_45 present,
     *    specifies clause 45 PHY (else clause 22);
     *    If CEDI_MDIO_FLG_INC_ADDR present, and clause 45, then address will be
     *    incremented after the read operation.
     * @param[in] pD driver private state info specific to this instance
     * @param[in] devReg device type (clause 45) or register address (clause 22) - enum CEDI_MdioDevType
     *    is available to specify the device type
     */
    void (*phyStartMdioRead)(void* pD, uint8_t flags, uint8_t phyAddr, uint8_t devReg);

    /**
     * Get data read from the PHY during a read operation.
     * @param[out] readData PHY read data, from in lower 16 bits of maintenance register
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return EINVAL for invalid pointer
     */
    uint32_t (*getMdioReadData)(void* pD, uint16_t* readData);

    /**
     * Read status of PHY management logic
     * @param[in] pD driver private state info specific to this instance
     * @return 1 for idle (mechanical success)
     * @return 0 for busy, or pD equal NULL
     */
    uint32_t (*getMdioIdle)(void* pD);

    /**
     * Copy the statistics registers contents into the statsRegs struct
     * reserved by client
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return ENOTSUP if no_stats defined
     */
    uint32_t (*readStats)(void* pD);

    /**
     * Clear the statistics registers.
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return ENOTSUP if no_stats defined
     */
    uint32_t (*clearStats)(void* pD);

    /**
     * Record snapshot of current statistics counts into snapshot
     * registers.
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return ENOTSUP if no_snapshot or no_stats defined
     */
    uint32_t (*takeSnapshot)(void* pD);

    /**
     * Define action taken when statistics registers are read
     * @param[in] enable if =1 then enable, if =0 then disable
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return ENOTSUP if no_snapshot or no_stats defined
     */
    uint32_t (*setReadSnapshot)(void* pD, uint8_t enable);

    /**
     * Read state of ReadSnapshot flag
     * @param[out] enable pointer for returning ReadSnapshot flag: if =1 then read
     *    snapshot is enabled; if =0 registers will show current statistics
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return ENOTSUP if no_snapshot or no_stats defined
     */
    uint32_t (*getReadSnapshot)(void* pD, uint8_t* enable);

    /**
     * Set Wake On LAN (WOL) register using CEDI_WakeOnLanReg struct
     * @param[in] regVals pointer to CEDI_WakeOnLanReg struct for register values to set
     * @param[in] pD driver private state info specific to this instance
     * @return EOK if successful
     * @return EINVAL if invalid parameter
     */
    uint32_t (*setWakeOnLanReg)(void* pD, CEDI_WakeOnLanReg* regVals);

    /**
     * Read Wake On LAN register using CEDI_WakeOnLanReg struct
     * @param[out] regVals pointer to CEDI_WakeOnLanReg struct for returning WOL register contents
     * @param[in] pD driver private state info specific to this instance
     * @return EOK if successful
     * @return EINVAL if invalid parameter
     */
    uint32_t (*getWakeOnLanReg)(void* pD, CEDI_WakeOnLanReg* regVals);

    /**
     * Enable/disable low power indication (LPI) transmission.
     * @param[in] enable if =1 then enable, if =0 then disable
     * @param[in] pD driver private state info specific to this instance
     * @return EOK if successful
     * @return EINVAL if invalid parameter
     */
    uint32_t (*setLpiTxEnable)(void* pD, uint8_t enable);

    /**
     * Get LPI transmission status
     * @param[out] enable equal 1 if enabled, equal 0 if disabled
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return EINVAL for invalid parameter
     */
    uint32_t (*getLpiTxEnable)(void* pD, uint8_t* enable);

    /**
     * Read LPI transitions & time in both Tx and Rx directions.  The
     * registers are all cleared on read.
     * @param[out] lpiStats pointer to a CEDI_LpiStats struct for returning the LPI statistics.
     * @param[in] pD driver private state info specific to this instance
     * @return EOK if successful
     * @return EINVAL if invalid parameter
     */
    uint32_t (*getLpiStats)(void* pD, CEDI_LpiStats* lpiStats);

    /**
     * Copies all design configuration register fields into a
     * CEDI_DesignCfg struct declared by client software.
     * @param[out] hwCfg pointer to struct for receiving configuration data
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return EINVAL if any parameters =NULL
     */
    uint32_t (*getDesignConfig)(void* pD, CEDI_DesignCfg* hwCfg);

    /**
     * Enable/disable writing to the statistics registers for debugging.
     * @param[in] enable if =1 enable writing, if =0 then disable
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return EINVAL if no_stats defined
     */
    uint32_t (*setWriteStatsEnable)(void* pD, uint8_t enable);

    /**
     * Read enable/disable state of writing to the statistics registers
     * for debugging.
     * @param[out] enable pointer for returning state: equal 1 if writing enabled equal 0 if disabled.
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return EINVAL if no_stats defined
     */
    uint32_t (*getWriteStatsEnable)(void* pD, uint8_t* enable);

    /**
     * Increments all statistics registers contents by 1 for debugging.
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return EINVAL if no_stats defined
     */
    uint32_t (*incStatsRegs)(void* pD);

    /**
     * Enable/disable back pressure to force collisions an all received
     * frames in 10M or 100M half duplex mode.
     * @param[in] enable if =1 enable back pressure, if =0 then disable
     * @param[in] pD driver private state info specific to this instance
     */
    void (*setRxBackPressure)(void* pD, uint8_t enable);

    /**
     * Read Enable/disable state of back pressure to force collisions an
     * all received frames in 10M or 100M half duplex mode.
     * @param[out] enable equal 1 if enabled, equal 0 if disabled
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return EINVAL for invalid pointer
     */
    uint32_t (*getRxBackPressure)(void* pD, uint8_t* enable);

    /**
     * Enable/disable forcing collisions by PCS on transmit.
     * @param[in] enable if =1 enable forcing collisions, if =0 then disable
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return ENOTSUP if no_pcs defined
     */
    uint32_t (*setCollisionTest)(void* pD, uint8_t enable);

    /**
     * Read enable/disable state for forcing collisions by PCS on
     * transmit.
     * @param[out] enable pointer for returning state: equal 1 if forcing collisions enabled, equal 0 if disabled.
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return ENOTSUP if no_pcs defined
     */
    uint32_t (*getCollisionTest)(void* pD, uint8_t* enable);

    /**
     * Enable/disable functionality to set backoff between collisions to
     * one slot time. This helps test for too many retries, and also
     * shortens pause countdown time in pause frame tests.
     * @param[in] enable if =1 enable retry test, if =0 then disable
     * @param[in] pD driver private state info specific to this instance
     */
    void (*setRetryTest)(void* pD, uint8_t enable);

    /**
     * Read enable/disable status of retry test functionality.
     * @param[out] enable =1 if retry test enabled, =0 if disabled
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return EINVAL for invalid pointer
     */
    uint32_t (*getRetryTest)(void* pD, uint8_t* enable);

    /**
     * Write to the user_out_width user outputs.
     * @param[in] pD driver private state info specific to this instance
     * @param[in] outVal value to write to the user outputs
     * @return EOK for success
     * @return ENOTSUP if user_io not defined
     * @return EINVAL if pD equal NULL
     */
    uint32_t (*writeUserOutputs)(void* pD, uint16_t outVal);

    /**
     * Read from the user_out_width user outputs.
     * @param[in] pD driver private state info specific to this instance
     * @param[out] outVal pointer for returning value read from the user outputs
     * @return EOK for success
     * @return ENOTSUP if user_io not defined
     * @return EINVAL if NULL parameters
     */
    uint32_t (*readUserOutputs)(void* pD, uint16_t* outVal);

    /**
     * Set the state of the specified user output pin.
     * @param[in] state level to set on the pin 1 for high, 0 for low
     * @param[in] pin pin number to set, range 0 to user_out_width-1
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return ENOTSUP if user_io not defined
     * @return EINVAL if pin out of range, or pD equal NULL
     */
    uint32_t (*setUserOutPin)(void* pD, uint8_t pin, uint8_t state);

    /**
     * Read from the user_in_width user inputs.
     * @param[in] pD driver private state info specific to this instance
     * @param[out] inVal pointer for returning value read from the user inputs
     * @return EOK for success
     * @return ENOTSUP if user_io not defined
     * @return EINVAL if NULL parameter
     */
    uint32_t (*readUserInputs)(void* pD, uint16_t* inVal);

    /**
     * Get the state of the specified user input pin.
     * @param[out] state pointer for returning level present on the pin, 1 for high, 0 for low
     * @param[in] pin pin number to read
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return ENOTSUP if user_io not defined
     * @return EINVAL if pin out of range, or pD equal NULL
     */
    uint32_t (*getUserInPin)(void* pD, uint8_t pin, uint8_t* state);

    /**
     * Read the state of the MDIO pin
     * @param[out] state 1 for high, 0 for low
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return EINVAL for invalid pointer
     */
    uint32_t (*getMdioInState)(void* pD, uint8_t* state);

    /**
     * Direct read of register contents
     * @param[in] offs address offset to register
     * @param[out] data pointer for returning data read
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return EINVAL if offs out of range, or pD equal NULL
     */
    uint32_t (*readReg)(void* pD, uint32_t offs, uint32_t* data);

    /**
     * Direct write to register
     * @param[in] offs address offset to register
     * @param[in] data data to write
     * @param[in] pD driver private state info specific to this instance
     * @return EOK for success
     * @return EINVAL if offs out of range, or pD equal NULL
     */
    uint32_t (*writeReg)(void* pD, uint32_t offs, uint32_t data);

} CEDI_OBJ;

/**
 * In order to access the CEDI APIs, the upper layer software must call
 * this global function to obtain the pointer to the driver object.
 * @return CEDI_OBJ* Driver Object Pointer
 */
extern CEDI_OBJ *CEDI_GetInstance(void);

/**
 *  @}
 */


#endif    /* _CEDI_H_ */
