/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#ifndef __UFS_H__
#define __UFS_H__

#include <rthw.h>
#include <rtthread.h>
#include <drivers/blk.h>
#include <drivers/misc.h>
#include <drivers/scsi.h>
#include <drivers/byteorder.h>

#define __BIT_FIELD(v, h, l)                        ((v & RT_GENMASK(h, l)) >> l)

/* Host Capabilities */
#define RT_UFS_REG_CAP                              0x00 /* Host Controller Capabiities */
#define   RT_UFS_REG_CAP_NUTRS(v)                   __BIT_FIELD(v, 4, 0) /* Number of UTP Transfer Request Slots */
#define   RT_UFS_REG_CAP_NORTT(v)                   __BIT_FIELD(v, 15, 8) /* Number of outstanding READY TO TRANSFER requests supported */
#define   RT_UFS_REG_CAP_NUTMRS(v)                  __BIT_FIELD(v, 18, 16) /* Number of UTP Task Management Request Slots */
#define   RT_UFS_REG_CAP_AUTOH8                     RT_BIT(23) /* Auto-Hibernation Support */
#define   RT_UFS_REG_CAP_64AS                       RT_BIT(24) /* 64-bit addressing supported */
#define   RT_UFS_REG_CAP_OODDS                      RT_BIT(25) /* Out of order data delivery supported */
#define   RT_UFS_REG_CAP_UICDMETMS                  RT_BIT(26) /* UIC DME_TEST_MODE command supported */
#define   RT_UFS_REG_CAP_UME                        RT_BIT(27) /* Reserved for Unified Memory Extension */
#define RT_UFS_REG_VER                              0x08 /* UFS Version */
#define   RT_UFS_REG_VER_VS(v)                      __BIT_FIELD(v, 03, 0) /* Version Suffix (VS) */
#define   RT_UFS_REG_VER_MNR(v)                     __BIT_FIELD(v, 07, 4) /* Minor Version Number (MNR) */
#define   RT_UFS_REG_VER_MJR(v)                     __BIT_FIELD(v, 15, 8) /* Major Version Number (MJR) */
#define RT_UFS_REG_HCPID                            0x10 /* Host Controller Identification Descriptor – Product ID */
#define RT_UFS_REG_HCMID                            0x14 /* Host Controller Identification Descriptor – Manufacturer ID */
#define   RT_UFS_REG_HCMID_MIC(v)                   __BIT_FIELD(v, 7, 0) /* Manufacturer Identification Code */
#define   RT_UFS_REG_HCMID_BI(v)                    __BIT_FIELD(v, 15, 8) /* Bank Index */
#define RT_UFS_REG_AHIT                             0x18 /* Auto-Hibernate Idle Timer */
#define   RT_UFS_REG_AHIT_AH8ITV(v)                 __BIT_FIELD(v, 9, 0) /* Auto-Hibern8 Idle Timer Value */
#define   RT_UFS_REG_AHIT_TS(v)                     __BIT_FIELD(v, 12, 10) /* Timer scale */
/* Operation and Runtime */
#define RT_UFS_REG_IS                               0x20  /* Interrupt Status */
#define   RT_UFS_REG_IS_UTRCS                       RT_BIT(0)  /* UTP Transfer Request Completion Status */
#define   RT_UFS_REG_IS_UDEPRI                      RT_BIT(1)  /* UIC DME_ENDPOINTRESET Indication */
#define   RT_UFS_REG_IS_UE                          RT_BIT(2)  /* UIC Error */
#define   RT_UFS_REG_IS_UTMS                        RT_BIT(3)  /* UIC Test Mode Status */
#define   RT_UFS_REG_IS_UPMS                        RT_BIT(4)  /* UIC Power Mode Status */
#define   RT_UFS_REG_IS_UHXS                        RT_BIT(5)  /* UIC Hibernate Exit Status */
#define   RT_UFS_REG_IS_UHES                        RT_BIT(6)  /* UIC Hibernate Enter Status */
#define   RT_UFS_REG_IS_ULLS                        RT_BIT(7)  /* UIC Link Lost Status */
#define   RT_UFS_REG_IS_ULSS                        RT_BIT(8)  /* UIC Link Startup Status */
#define   RT_UFS_REG_IS_UTMRCS                      RT_BIT(9)  /* UTP Task Management Request Completion Status */
#define   RT_UFS_REG_IS_UCCS                        RT_BIT(10) /* UIC Command Completion Status */
#define   RT_UFS_REG_IS_DFES                        RT_BIT(11) /* Device Fatal Error Status */
#define   RT_UFS_REG_IS_UTPES                       RT_BIT(12) /* UTP Error Status */
#define   RT_UFS_REG_IS_HCFES                       RT_BIT(16) /* Host Controller Fatal Error Status */
#define   RT_UFS_REG_IS_SBFES                       RT_BIT(17) /* System Bus Fatal Error Status */
#define RT_UFS_REG_IE                               0x24  /* Interrupt Enable */
#define   RT_UFS_REG_IE_UTRCE                       RT_BIT(0)  /* UTP Transfer Request Completion Enable */
#define   RT_UFS_REG_IE_UDEPRIE                     RT_BIT(1)  /* UIC DME_ENDPOINTRESET */
#define   RT_UFS_REG_IE_UEE                         RT_BIT(2)  /* UIC Error Enable */
#define   RT_UFS_REG_IE_UTMSE                       RT_BIT(3)  /* UIC Test Mode Status Enable */
#define   RT_UFS_REG_IE_UPMSE                       RT_BIT(4)  /* UIC Power Mode Status Enable */
#define   RT_UFS_REG_IE_UHXSE                       RT_BIT(5)  /* UIC Hibernate Exit Status Enable */
#define   RT_UFS_REG_IE_UHESE                       RT_BIT(6)  /* UIC Hibernate Enter Status Enable */
#define   RT_UFS_REG_IE_ULLSE                       RT_BIT(7)  /* UIC Link Lost Status Enable */
#define   RT_UFS_REG_IE_ULSSE                       RT_BIT(8)  /* UIC Link Startup Status Enable */
#define   RT_UFS_REG_IE_UTMRCE                      RT_BIT(9)  /* UTP Task Management Request Completion Enable */
#define   RT_UFS_REG_IE_UCCE                        RT_BIT(10) /* UIC COMMAND Completion Enable */
#define   RT_UFS_REG_IE_DFEE                        RT_BIT(11) /* Device Fatal Error Enable */
#define   RT_UFS_REG_IE_UTPEE                       RT_BIT(12) /* UTP Error Enable */
#define   RT_UFS_REG_IE_HCFEE                       RT_BIT(16) /* Host Controller Fatal Error Enable */
#define   RT_UFS_REG_IE_SBFEE                       RT_BIT(17) /* System Bus Fatal Error Enable */
#define RT_UFS_REG_HCS                              0x30  /* Host Controller Status */
#define   RT_UFS_REG_HCS_DP                         RT_BIT(0) /* Device Present */
#define   RT_UFS_REG_HCS_UTRLRDY                    RT_BIT(1) /* UTP Transfer Request List Ready */
#define   RT_UFS_REG_HCS_UTMRLRDY                   RT_BIT(2) /* UTP Task Management Request List Ready */
#define   RT_UFS_REG_HCS_UCRDY                      RT_BIT(3) /* UIC COMMAND Ready */
#define   RT_UFS_REG_HCS_UPMCRS(v)                  __BIT_FIELD(v, 10, 8) /* UIC Power Mode Change Request Status */
#define   RT_UFS_REG_HCS_UTPEC(v)                   __BIT_FIELD(v, 15, 12) /* UTP Error Code */
#define   RT_UFS_REG_HCS_TTAGUTPE(v)                __BIT_FIELD(v, 23, 16) /* Task Tag of UTP error */
#define   RT_UFS_REG_HCS_TLUNUTPE(v)                __BIT_FIELD(v, 31, 24) /* Target LUN of UTP error */
#define RT_UFS_REG_HCE                              0x34  /* Host Controller Enable */
#define RT_UFS_REG_UECPA                            0x38  /* Host UIC Error Code PHY Adapter Layer */
#define   RT_UFS_REG_UECPA_EC(v)                    __BIT_FIELD(v, 4, 0) /* UIC PHY Adapter Layer Error Code */
#define   RT_UFS_REG_UECPA_ERR                      RT_BIT(31) /* UIC PHY AdapterA Layer Error */
#define RT_UFS_REG_UECDL                            0x3c  /* Host UIC Error Code Data Link Layer */
#define   RT_UFS_REG_UECDL_EC(v)                    __BIT_FIELD(v, 14, 0) /* UIC Data Link Layer Error Code */
#define   RT_UFS_REG_UECDL_ERR                      RT_BIT(31) /* UIC Data Link Layer Error */
#define RT_UFS_REG_UECN                             0x40  /* Host UIC Error Code Network Layer */
#define   RT_UFS_REG_UECN_EC(v)                     __BIT_FIELD(v, 2, 0) /* UIC Network Layer Error Code */
#define   RT_UFS_REG_UECN_ERR                       RT_BIT(31) /* UIC Network Layer Error */
#define RT_UFS_REG_UECT                             0x44  /* Host UIC Error Code Transport Layer */
#define   RT_UFS_REG_UECT_EC(v)                     __BIT_FIELD(v, 6, 0) /* UIC Transport Layer Error Code */
#define   RT_UFS_REG_UECT_ERR                       RT_BIT(31) /* UIC Transport Layer Error */
#define RT_UFS_REG_UECDME                           0x48  /* Host UIC Error Code DME */
#define   RT_UFS_REG_UECDME_EC(v)                   __BIT_FIELD(v, 0, 0) /* UIC DME Error Code */
#define   RT_UFS_REG_UECDME_ERR                     RT_BIT(31) /* UIC DME Error */
#define RT_UFS_REG_UTRIACR                          0x4c  /* UTP Transfer Request Interrupt Aggregation Control Register */
#define   RT_UFS_REG_UTRIACR_IAEN                   RT_BIT(31) /* Interrupt Aggregation Enable/Disable */
#define   RT_UFS_REG_UTRIACR_IAPWEN                 RT_BIT(24) /* Interrupt aggregation parameter write enable */
#define   RT_UFS_REG_UTRIACR_IASB                   RT_BIT(20) /* Interrupt aggregation status bit */
#define   RT_UFS_REG_UTRIACR_CTR                    RT_BIT(16) /* Counter and Timer Reset */
#define   RT_UFS_REG_UTRIACR_IACTH(v)               __BIT_FIELD(v, 12, 8) /* Interrupt aggregation counter threshold */
#define   RT_UFS_REG_UTRIACR_IATOVAL(v)             __BIT_FIELD(v, 7, 0) /* Interrupt aggregation timeout (40us units) */
/* UTRIACR compose */
#define RT_UFS_UTRIACR_TIMEOUT_MASK                 RT_GENMASK(7, 0)
#define RT_UFS_UTRIACR_COUNTER_THLD_MASK            RT_GENMASK(12, 8)
#define RT_UFS_UTRIACR_CTR                          RT_BIT(16)
#define RT_UFS_UTRIACR_IASB                         RT_BIT(20)
#define RT_UFS_UTRIACR_IAPWEN                       RT_BIT(24)
#define RT_UFS_UTRIACR_IAEN                         RT_BIT(31)
#define RT_UFS_UTRIACR_COUNTER_THLD(c)              ((((rt_uint32_t)(c)) & 0x1fu) << 8)
#define RT_UFS_UTRIACR_TIMEOUT(t)                   (((rt_uint32_t)(t)) & 0xffu)
#define RT_UFS_UTRIACR_ENABLE_PARAMS(cnt, to)       (RT_UFS_UTRIACR_IAEN | RT_UFS_UTRIACR_IAPWEN | \
                                                            RT_UFS_UTRIACR_COUNTER_THLD(cnt) | RT_UFS_UTRIACR_TIMEOUT(to))
#define RT_UFS_UTRIACR_RESET                        (RT_UFS_UTRIACR_IAEN | RT_UFS_UTRIACR_CTR)
/* UTP Transfer */
#define RT_UFS_REG_UTRLBA                           0x50 /* UTP Transfer Request List Base Address */
#define   RT_UFS_REG_UTRLBA_MASK(v)                 __BIT_FIELD(v, 31, 10)
#define RT_UFS_REG_UTRLBAU                          0x54 /* UTP Transfer Request List Base Address Upper 32-Bits */
#define   RT_UFS_REG_UTRLBAU_MASK(v)                __BIT_FIELD(v, 31, 0)
#define RT_UFS_REG_UTRLDBR                          0x58 /* UTP Transfer Request List Door Bell Register */
#define RT_UFS_REG_UTRLCLR                          0x5c /* UTP Transfer Request List CLear Register */
#define RT_UFS_REG_UTRLRSR                          0x60 /* UTP Transfer Request Run-Stop Register */
/* UTP Task Managemeng */
#define RT_UFS_REG_UTMRLBA                          0x70 /* UTP Task Management Request List Base Address */
#define   RT_UFS_REG_UTMRLBA_MASK(v)                __BIT_FIELD(v, 31, 10)
#define RT_UFS_REG_UTMRLBAU                         0x74 /* UTP Task Management Request List Base Address Upper 32-Bits */
#define   RT_UFS_REG_UTMRLBAU_MASK(v)               __BIT_FIELD(v, 31, 0)
#define RT_UFS_REG_UTMRLDBR                         0x78 /* UTP Task Management Request List Door Bell Register */
#define RT_UFS_REG_UTMRLCLR                         0x7c /* UTP Task Management Request List CLear Register */
#define RT_UFS_REG_UTMRLRSR                         0x80 /* UTP Task Management Run-Stop Register */
/* UIC Command */
#define RT_UFS_REG_UICCMD                           0x90 /* UIC Command Register */
#define   RT_UFS_REG_UICCMD_CMDOP(v)                __BIT_FIELD(v, 7, 0) /* Command Opcode */
#define RT_UFS_REG_UCMDARG1                         0x94 /* UIC Command Argument 1 */
#define RT_UFS_REG_UCMDARG2                         0x98 /* UIC Command Argument 2 */
#define RT_UFS_REG_UCMDARG3                         0x9c /* UIC Command Argument 3 */
/* UMA */
#define RT_UFS_REG_UMA_EXT                          0xb0 /* Reserved for Unified Memory Extension */
/* Vendor Specific */
#define RT_UFS_REG_VS                               0xc0 /* Vendor Specific Registers */

/* UTP Error Code */
enum
{
    RT_UFS_UTPEC_ERR_INV_TYPE                       = 1,
};

/* UIC Power Mode Change Request Status */
enum
{
    RT_UFS_UPMCRS_PWR_OK                            = 0x0,
    RT_UFS_UPMCRS_PWR_LOCAL                         = 0x1,
    RT_UFS_UPMCRS_PWR_REMOTE                        = 0x2,
    RT_UFS_UPMCRS_PWR_BUSY                          = 0x3,
    RT_UFS_UPMCRS_PWR_ERROR_CAP                     = 0x4,
    RT_UFS_UPMCRS_PWR_FATAL_ERROR                   = 0x5,
};

/* UIC PHY Adapter Layer Error Code */
enum
{
    RT_UFS_UECPA_EC_LANE0                           = RT_BIT(0),
    RT_UFS_UECPA_EC_LANE1                           = RT_BIT(1),
    RT_UFS_UECPA_EC_LANE2                           = RT_BIT(2),
    RT_UFS_UECPA_EC_LANE3                           = RT_BIT(3),
    RT_UFS_UECPA_EC_GENERIC                         = RT_BIT(4),
};

/* UIC Data Link Layer Error Code */
enum
{
    RT_UFS_UECDL_EC_NAC_RECEIVED                    = RT_BIT(0),
    RT_UFS_UECDL_EC_TCx_REPLAY_TIMER_EXPIRED        = RT_BIT(1),
    RT_UFS_UECDL_EC_AFCx_REQUEST_TIMER_EXPIRED      = RT_BIT(2),
    RT_UFS_UECDL_EC_FCx_PROTECTION_TIMER_EXPIRED    = RT_BIT(3),
    RT_UFS_UECDL_EC_CRC_ERROR                       = RT_BIT(4),
    RT_UFS_UECDL_EC_RX_BUFFER_OVERFLOW              = RT_BIT(5),
    RT_UFS_UECDL_EC_MAX_FRAME_LENGTH_EXCEEDED       = RT_BIT(6),
    RT_UFS_UECDL_EC_WRONG_SEQUENCE_NUMBER           = RT_BIT(7),
    RT_UFS_UECDL_EC_AFC_FRAME_SYNTAX_ERROR          = RT_BIT(8),
    RT_UFS_UECDL_EC_NAC_FRAME_SYNTAX_ERROR          = RT_BIT(9),
    RT_UFS_UECDL_EC_EOF_SYNTAX_ERROR                = RT_BIT(10),
    RT_UFS_UECDL_EC_FRAME_SYNTAX_ERROR              = RT_BIT(11),
    RT_UFS_UECDL_EC_BAD_CTRL_SYMBOL_TYPE            = RT_BIT(12),
    RT_UFS_UECDL_EC_PA_INIT_ERROR                   = RT_BIT(13),
    RT_UFS_UECDL_EC_PA_ERROR_IND_RECEIVED           = RT_BIT(14),
};

/* UIC Network Layer Error Code */
enum
{
    RT_UFS_UECN_EC_UNSUPPORTED_HEADER_TYPE          = RT_BIT(0),
    RT_UFS_UECN_EC_BAD_DEVICEID_ENC                 = RT_BIT(1),
    RT_UFS_UECN_EC_LHDR_TRAP_PACKET_DROPPING        = RT_BIT(2),
};

/* UIC Transport Layer Error Code */
enum
{
    RT_UFS_UECT_EC_UNSUPPORTED_HEADER_TYPE          = RT_BIT(0),
    RT_UFS_UECT_EC_UNKNOWN_CPORTID                  = RT_BIT(1),
    RT_UFS_UECT_EC_NO_CONNECTION_RX                 = RT_BIT(2),
    RT_UFS_UECT_EC_CONTROLLED_SEGMENT_DROPPING      = RT_BIT(3),
    RT_UFS_UECT_EC_BAD_TC                           = RT_BIT(4),
    RT_UFS_UECT_EC_E2E_CREDIT_OVERFLOW              = RT_BIT(5),
    RT_UFS_UECT_EC_SAFETY_VALVE_DROPPING            = RT_BIT(6),
};

/* UIC DME Error Code */
enum
{
    RT_UFS_UECDME_EC_GENERIC                        = RT_BIT(0),
};

/* UIC Command Opcode */
enum
{
    /* Configuration */
    RT_UFS_CMDOP_DME_GET                            = 0x1,
    RT_UFS_CMDOP_DME_SET                            = 0x2,
    RT_UFS_CMDOP_DME_PEER_GET                       = 0x3,
    RT_UFS_CMDOP_DME_PEER_SET                       = 0x4,
    /* Control */
    RT_UFS_CMDOP_DME_POWERON                        = 0x10,
    RT_UFS_CMDOP_DME_POWEROFF                       = 0x11,
    RT_UFS_CMDOP_DME_ENABLE                         = 0x12,
    RT_UFS_CMDOP_DME_RESET                          = 0x14,
    RT_UFS_CMDOP_DME_ENDPOINTRESET                  = 0x15,
    RT_UFS_CMDOP_DME_LINKSTARTUP                    = 0x16,
    RT_UFS_CMDOP_DME_HIBERNATE_ENTER                = 0x17,
    RT_UFS_CMDOP_DME_HIBERNATE_EXIT                 = 0x18,
    RT_UFS_CMDOP_DME_TEST_MODE                      = 0x1a,
};

/* UIC Config result code / Generic error code */
enum
{
    RT_UFS_CMDRES_SUCCESS                           = 0x0,
    RT_UFS_CMDRES_INVALID_MIB_ATTRIBUTE             = 0x1,
    RT_UFS_CMDRES_INVALID_MIB_ATTRIBUTE_VALUE       = 0x2,
    RT_UFS_CMDRES_READ_ONLY_MIB_ATTRIBUTE           = 0x3,
    RT_UFS_CMDRES_WRITE_ONLY_MIB_ATTRIBUTE          = 0x4,
    RT_UFS_CMDRES_BAD_INDEX                         = 0x5,
    RT_UFS_CMDRES_LOCKED_MIB_ATTRIBUTE              = 0x6,
    RT_UFS_CMDRES_BAD_TEST_FEATURE_INDEX            = 0x7,
    RT_UFS_CMDRES_PEER_COMMUNICATION_FAILURE        = 0x8,
    RT_UFS_CMDRES_BUSY                              = 0x9,
    RT_UFS_CMDRES_DME_FAILURE                       = 0xa,
    RT_UFS_CMDRES_MASK                              = 0xff,
};

/*
 * UIC DME attribute encoding (JEDEC UFS / UniPro PA)
 */
#define RT_UFS_UIC_ARG_MIB_SEL(attr, sel)           ((((rt_uint32_t)(attr) & 0xffffU) << 16) | ((rt_uint32_t)(sel) & 0xffffU))
#define RT_UFS_UIC_ARG_MIB(attr)                    RT_UFS_UIC_ARG_MIB_SEL(attr, 0)

/* PHY Adapter — subset used for power / link configuration */
#define RT_UFS_PA_RXGEAR                            0x1583
#define RT_UFS_PA_TXGEAR                            0x1568
#define RT_UFS_PA_ACTIVERXDATALANES                 0x1580
#define RT_UFS_PA_ACTIVETXDATALANES                 0x1560
#define RT_UFS_PA_RXTERMINATION                     0x1584
#define RT_UFS_PA_TXTERMINATION                     0x1569
#define RT_UFS_PA_HSSERIES                          0x156a
#define RT_UFS_PA_PWRMODE                           0x1571
#define RT_UFS_PA_PWRMODEUSERDATA0                  0x15b0
#define RT_UFS_PA_PWRMODEUSERDATA1                  0x15b1
#define RT_UFS_PA_PWRMODEUSERDATA2                  0x15b2
#define RT_UFS_PA_PWRMODEUSERDATA3                  0x15b3
#define RT_UFS_PA_PWRMODEUSERDATA4                  0x15b4
#define RT_UFS_PA_PWRMODEUSERDATA5                  0x15b5
#define RT_UFS_DME_LOCAL_FC0_PROT_TO                0xd041
#define RT_UFS_DME_LOCAL_TC0_REPLAY_TO              0xd042
#define RT_UFS_DME_LOCAL_AFC0_REQ_TO                0xd043

#define RT_UFS_DL_FC0_PROT_TO_DEFAULT               8191U
#define RT_UFS_DL_TC0_REPLAY_TO_DEFAULT             65535U
#define RT_UFS_DL_AFC0_REQ_TO_DEFAULT               32767U
#define RT_UFS_DL_FC1_PROT_TO_DEFAULT               8191U
#define RT_UFS_DL_TC1_REPLAY_TO_DEFAULT             65535U
#define RT_UFS_DL_AFC1_REQ_TO_DEFAULT               32767U

enum rt_ufs_pa_pwr_mode
{
    RT_UFS_PA_FAST_MODE                             = 1,
    RT_UFS_PA_SLOW_MODE                             = 2,
    RT_UFS_PA_FASTAUTO_MODE                         = 4,
    RT_UFS_PA_SLOWAUTO_MODE                         = 5,
    RT_UFS_PA_UNCHANGED_MODE                        = 7,
};

enum rt_ufs_pa_hs_rate
{
    RT_UFS_PA_HS_MODE_A                             = 1,
    RT_UFS_PA_HS_MODE_B                             = 2,
};

/* Auto-Hibernate Idle Timer (AHIT) — REG 0x18 */
#define RT_UFS_AHIT_TIMER_MASK                      RT_GENMASK(9, 0)
#define RT_UFS_AHIT_SCALE_MASK                      RT_GENMASK(12, 10)

rt_inline rt_uint32_t rt_ufs_ahit_encode(rt_uint16_t timer, rt_uint8_t scale)
{
    return ((rt_uint32_t)timer & RT_UFS_AHIT_TIMER_MASK) | (((rt_uint32_t)scale << 10) & RT_UFS_AHIT_SCALE_MASK);
}

/* 150 * 10^3 us idle before auto-Hibernate8 */
#define RT_UFS_AHIT_DEFAULT                         rt_ufs_ahit_encode(150, 3)

/*
 * UTP / UPIU (refer to JEDEC UFS & UFSHCI)
 */
#define RT_UFS_CDB_SIZE                             16
#define RT_UFS_ALIGNED_UPIU_SIZE                    512
#define RT_UFS_SENSE_SIZE                           18

/* UTP Transfer Request Command Type */
#define RT_UTP_CMD_TYPE_SCSI                        0x0
#define RT_UTP_CMD_TYPE_UFS_STORAGE                 0x1
#define RT_UTP_CMD_TYPE_DEV_MANAGE                  0x2

/* UTP Data Direction */
#define RT_UTP_NO_DATA_TRANSFER                     0
#define RT_UTP_HOST_TO_DEVICE                       1
#define RT_UTP_DEVICE_TO_HOST                       2

/* Overall Command Status (OCS) in UTRD */
enum rt_ufs_ocs
{
    RT_UFS_OCS_SUCCESS                              = 0x0,
    RT_UFS_OCS_INVALID_CMD_TABLE_ATTR               = 0x1,
    RT_UFS_OCS_INVALID_PRDT_ATTR                    = 0x2,
    RT_UFS_OCS_MISMATCH_DATA_BUF_SIZE               = 0x3,
    RT_UFS_OCS_MISMATCH_RESP_UPIU_SIZE              = 0x4,
    RT_UFS_OCS_PEER_COMM_FAILURE                    = 0x5,
    RT_UFS_OCS_ABORTED                              = 0x6,
    RT_UFS_OCS_FATAL_ERROR                          = 0x7,
    RT_UFS_OCS_DEVICE_FATAL_ERROR                   = 0x8,
    RT_UFS_OCS_INVALID_COMMAND_STATUS               = 0xf,
};

/* UPIU Transaction Codes (Initiator to Target) */
#define RT_UPIU_TRANSACTION_NOP_OUT                 0x00
#define RT_UPIU_TRANSACTION_COMMAND                 0x01
#define RT_UPIU_TRANSACTION_DATA_OUT                0x02
#define RT_UPIU_TRANSACTION_TASK_REQ                0x04
#define RT_UPIU_TRANSACTION_QUERY_REQ               0x16

/* UPIU Transaction Codes (Target to Initiator) */
#define RT_UPIU_TRANSACTION_NOP_IN                  0x20
#define RT_UPIU_TRANSACTION_RESPONSE                0x21
#define RT_UPIU_TRANSACTION_DATA_IN                 0x22
#define RT_UPIU_TRANSACTION_TASK_RSP                0x24
#define RT_UPIU_TRANSACTION_QUERY_RSP               0x36

/* UPIU Command Set Type */
#define RT_UPIU_COMMAND_SET_TYPE_SCSI               0x0

/* UPIU Command flags */
#define RT_UPIU_CMD_FLAGS_NONE                      0x00
#define RT_UPIU_CMD_FLAGS_WRITE                     0x20
#define RT_UPIU_CMD_FLAGS_READ                      0x40

/* PRDT: max single entry size 256KB, granularity 4 bytes */
#define RT_UFS_PRDT_BYTE_COUNT_MAX                  (256 * 1024)

/* UPIU header - 12 bytes, big-endian */
rt_packed(struct rt_utp_upiu_header
{
    rt_uint8_t transaction_code;
    rt_uint8_t flags;
    rt_uint8_t lun;
    rt_uint8_t task_tag;
    rt_uint8_t command_set_type;    /* 4:0, iid 7:5 in same byte on LE */
    rt_uint8_t query_function;      /* or tm_function */
    rt_uint8_t response;
    rt_uint8_t status;
    rt_uint8_t ehs_length;
    rt_uint8_t device_information;
    rt_be16_t data_segment_length;
});

/* Command UPIU - SCSI CDB */
rt_packed(struct rt_utp_upiu_cmd
{
    rt_be32_t exp_data_transfer_len;
    rt_uint8_t cdb[RT_UFS_CDB_SIZE];
});

/* Request UPIU - command type */
rt_packed(struct rt_utp_upiu_req
{
    struct rt_utp_upiu_header header;
    struct rt_utp_upiu_cmd sc;
});

/* Response UPIU - SCSI response (cmd_rsp) */
rt_packed(struct rt_utp_cmd_rsp
{
    rt_be32_t residual_transfer_count;
    rt_be32_t reserved[4];
    rt_be16_t sense_data_len;
    rt_uint8_t sense_data[RT_UFS_SENSE_SIZE];
});

rt_packed(struct rt_utp_upiu_rsp
{
    struct rt_utp_upiu_header header;
    struct rt_utp_cmd_rsp sr;
});

/* Physical Region Descriptor Table entry (LE, used by controller) */
rt_packed(struct rt_ufs_sg_entry
{
    rt_uint64_t addr;   /* LE in memory for UFSHCI */
    rt_uint32_t reserved;
    rt_uint32_t size;   /* LE */
});

/* Request Descriptor Header - common to UTRD/UTMRD (4DW) */
rt_packed(struct rt_ufs_request_desc_header
{
    rt_uint32_t dword_0;
    rt_uint32_t dword_1;
    rt_uint32_t dword_2;
    rt_uint32_t dword_3;
});

/* UTP Transfer Request Descriptor bits (dword_0) */
#define RT_UFS_UPIU_COMMAND_TYPE_OFFSET 28
#define RT_UFS_UTP_REQ_DESC_INT_CMD     0x01000000

/* UTP Transfer Request Descriptor (UTRD) - 32 bytes, host byte order for HC (LE in spec) */
rt_packed(struct rt_utp_transfer_req_desc
{
    struct rt_ufs_request_desc_header header;
    /* DW 4-5: UCD base address low/high dwords */
    rt_uint32_t command_desc_base_addr_lo; /* 128-byte aligned, HC reads as LE */
    rt_uint32_t command_desc_base_addr_hi; /* 128-byte aligned, HC reads as LE */
    rt_uint16_t response_upiu_length;
    rt_uint16_t response_upiu_offset;
    rt_uint16_t prd_table_length;
    rt_uint16_t prd_table_offset;
});

/* UTP Transfer Command Descriptor (UCD) - command_upiu + response_upiu + prd_table */
struct rt_utp_transfer_cmd_desc
{
    rt_uint8_t command_upiu[RT_UFS_ALIGNED_UPIU_SIZE];
    rt_uint8_t response_upiu[RT_UFS_ALIGNED_UPIU_SIZE];
    struct rt_ufs_sg_entry prd_table[];
};

/* One slot: UCD size = 512 + 512 + N*16. N=1 for single buffer. */
/*
 * PRDT entries per slot.
 * Partition probing may read multiple blocks with buffers not page-aligned,
 * so we keep a generous entry count to safely split by page boundaries.
 */
#define RT_UFS_PRDT_ENTRIES_PER_SLOT    32
#define RT_UFS_UCD_SIZE                 (RT_UFS_ALIGNED_UPIU_SIZE * 2 + sizeof(struct rt_ufs_sg_entry) * RT_UFS_PRDT_ENTRIES_PER_SLOT)

struct rt_ufs_ops;
struct rt_ufs_host;

enum rt_ufs_notify_change_status
{
    RT_UFS_NOTIFY_CHANGE_STATUS_PRE,
    RT_UFS_NOTIFY_CHANGE_STATUS_POST,
};

/* PA layer attributes for link gear / power mode (ufshcd_change_power_mode) */
struct rt_ufs_pa_layer_attr
{
    rt_uint32_t gear_rx;
    rt_uint32_t gear_tx;
    rt_uint32_t lane_rx;
    rt_uint32_t lane_tx;
    rt_uint32_t pwr_rx;   /* enum rt_ufs_pa_pwr_mode */
    rt_uint32_t pwr_tx;
    rt_uint32_t hs_rate;  /* enum rt_ufs_pa_hs_rate when in FAST* mode */
};

struct rt_ufs_host
{
    struct rt_scsi_host parent;

    void *regs;
    int irq;

    rt_uint32_t cap;
    rt_uint32_t nutrs;                          /* Number of UTP transfer request slots, 1..32 */

    const struct rt_ufs_ops *ops;

    /* UTRL (UTRD list) base (must be 1KB aligned); we use slot0 only */
    struct rt_utp_transfer_req_desc *utrd;      /* Points to utrl_base[0] */
    void *utrl_base;                            /* Full UTRL base */
    rt_size_t utrl_size;                        /* Bytes */
    rt_ubase_t utrl_handle;

    /* UTMRL (UTMRD list) base (must be 1KB aligned); placeholder for now */
    void *utmrl_base;
    rt_size_t utmrl_size;
    rt_ubase_t utmrl_handle;
    rt_uint8_t utmrl_coherent;

    rt_uint8_t *ucd_base;                       /* One UCD: command_upiu + response_upiu + prd_table */
    rt_size_t ucd_size;                         /* RT_UFS_UCD_SIZE or platform value */
    rt_ubase_t ucd_handle;
    rt_uint8_t ucd_coherent;

    /* Bounce buffer for small DMA I/O (avoid stack/unmapped buffers) */
    rt_uint8_t *bounce;
    rt_size_t bounce_size;
    rt_ubase_t bounce_handle;

    /* IRQ status snapshot (written by ISR, read by transfer thread) */
    volatile rt_uint32_t irq_status;

    struct rt_completion done;
    struct rt_spinlock lock;

    struct rt_ufs_pa_layer_attr pwr_active;
    rt_uint8_t pwr_active_valid;
    /**
     * Raw AHIT register value. 0 = use RT_UFS_AHIT_DEFAULT when CAP reports Auto-H8 support.
     * Write 0 via rt_ufs_auto_hibern8_set() to turn off auto-hibernate.
     */
    rt_uint32_t ahit;
};

struct rt_ufs_ops
{
    rt_err_t (*init)(struct rt_ufs_host *ufs);
    rt_err_t (*exit)(struct rt_ufs_host *ufs);
    rt_err_t (*reset)(struct rt_ufs_host *ufs);
    rt_err_t (*link_startup_notify)(struct rt_ufs_host *ufs, enum rt_ufs_notify_change_status status);
};

rt_err_t rt_ufs_host_register(struct rt_ufs_host *ufs);
rt_err_t rt_ufs_host_unregister(struct rt_ufs_host *ufs);

/**
 * @brief Send a UIC command and wait for completion
 *
 * Used during controller bring-up and in the link_startup_notify hook (e.g. DME_GET/SET,
 * DME_LINK_STARTUP).
 *
 * @param ufs   UFS host controller
 * @param cmd   UIC opcode (e.g. RT_UFS_CMDOP_DME_LINKSTARTUP)
 * @param arg1  UIC command argument 1
 * @param arg2  UIC argument 2; on return, low 8 bits contain the UIC result code
 * @param arg3  UIC command argument 3
 *
 * @return RT_EOK on success, -RT_ETIMEOUT on timeout, -RT_ERROR on failure
 */
rt_err_t rt_ufs_uic_cmd_send(struct rt_ufs_host *ufs, rt_uint32_t cmd,
        rt_uint32_t arg1, rt_uint32_t *arg2, rt_uint32_t arg3);

/**
 * @brief Apply default power/performance settings after the link is up
 *
 * Programs interrupt aggregation (UTRIACR) and, if the host supports it (CAP Auto-H8), the
 * Auto-Hibernate idle timer (AHIT). Called from rt_ufs_host_register(); BSP code may call
 * again after custom link training if needed.
 *
 * @param ufs UFS host controller
 */
void rt_ufs_pm_post_linkup(struct rt_ufs_host *ufs);

/**
 * @brief UIC DME_SET with UIC result check
 *
 * @param ufs       UFS host controller
 * @param attr_sel  MIB selector (e.g. RT_UFS_UIC_ARG_MIB)
 * @param value     Attribute value written to UIC argument 3
 *
 * @return RT_EOK on success, otherwise an error code
 */
rt_err_t rt_ufs_dme_set(struct rt_ufs_host *ufs, rt_uint32_t attr_sel, rt_uint32_t value);

/**
 * @brief UIC DME_GET
 *
 * @param ufs       UFS host controller
 * @param attr_sel  MIB selector
 * @param value     Storage for the attribute value read from UIC argument 3
 *
 * @return RT_EOK on success, otherwise an error code
 */
rt_err_t rt_ufs_dme_get(struct rt_ufs_host *ufs, rt_uint32_t attr_sel, rt_uint32_t *value);

/**
 * @brief Set PHY power mode via PA_PWRMODE
 *
 * @param ufs  UFS host controller
 * @param mode Encoded as (rx_mode << 4) | tx_mode (see UniPro PA power modes)
 *
 * @return RT_EOK on success, otherwise an error code
 */
rt_err_t rt_ufs_uic_pa_pwrmode(struct rt_ufs_host *ufs, rt_uint8_t mode);

/**
 * @brief Change PA layer gear, lanes, termination, HS series, and trigger power mode
 *
 * @param ufs   UFS host controller
 * @param attr  Desired PA layer parameters
 * @param force If true, apply even when attr matches the last successful configuration
 *
 * @return RT_EOK on success, otherwise an error code
 */
rt_err_t rt_ufs_pa_power_mode_set(struct rt_ufs_host *ufs, const struct rt_ufs_pa_layer_attr *attr, rt_bool_t force);

/**
 * @brief Request link Hibernate8 enter (UIC DME_HIBERNATE_ENTER)
 *
 * @param ufs UFS host controller
 *
 * @return RT_EOK on success, otherwise an error code
 */
rt_err_t rt_ufs_hibern8_enter(struct rt_ufs_host *ufs);

/**
 * @brief Request link Hibernate8 exit (UIC DME_HIBERNATE_EXIT)
 *
 * @param ufs UFS host controller
 *
 * @return RT_EOK on success, otherwise an error code
 */
rt_err_t rt_ufs_hibern8_exit(struct rt_ufs_host *ufs);

/**
 * @brief Program the Auto-Hibernate idle timer register (AHIT)
 *
 * Requires host capability RT_UFS_REG_CAP_AUTOH8. Pass 0 to disable auto-hibernate.
 *
 * @param ufs      UFS host controller
 * @param reg_val  Raw AHIT register value
 *
 * @return RT_EOK on success, -RT_ENOSYS if Auto-H8 is not supported, otherwise an error code
 */
rt_err_t rt_ufs_auto_hibern8_set(struct rt_ufs_host *ufs, rt_uint32_t reg_val);

/**
 * @brief Configure UTP transfer completion interrupt aggregation (UTRIACR, offset 0x4C)
 *
 * @param ufs     UFS host controller
 * @param enable  RT_TRUE to enable aggregation; RT_FALSE clears the register
 * @param cnt     Completion counter threshold before an interrupt (0–31)
 * @param timeout Aggregation timeout in 40 µs steps (UFSHCI)
 */
void rt_ufs_intr_aggr_configure(struct rt_ufs_host *ufs, rt_bool_t enable, rt_uint8_t cnt, rt_uint8_t timeout);

#endif /* __UFS_H__ */
