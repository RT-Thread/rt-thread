/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#ifndef __NVME_H__
#define __NVME_H__

#include <rthw.h>
#include <rtthread.h>
#include <drivers/blk.h>

#define NVME_RSVD(offset, bytes_size)   rt_uint8_t __rsvd##offset[bytes_size]

enum
{
    /*
     * Generic Command Status:
     */
    RT_NVME_SC_SUCCESS                          = 0x0,
    RT_NVME_SC_INVALID_OPCODE                   = 0x1,
    RT_NVME_SC_INVALID_FIELD                    = 0x2,
    RT_NVME_SC_CMDID_CONFLICT                   = 0x3,
    RT_NVME_SC_DATA_XFER_ERROR                  = 0x4,
    RT_NVME_SC_POWER_LOSS                       = 0x5,
    RT_NVME_SC_INTERNAL                         = 0x6,
    RT_NVME_SC_ABORT_REQ                        = 0x7,
    RT_NVME_SC_ABORT_QUEUE                      = 0x8,
    RT_NVME_SC_FUSED_FAIL                       = 0x9,
    RT_NVME_SC_FUSED_MISSING                    = 0xa,
    RT_NVME_SC_INVALID_NS                       = 0xb,
    RT_NVME_SC_CMD_SEQ_ERROR                    = 0xc,
    RT_NVME_SC_SGL_INVALID_LAST                 = 0xd,
    RT_NVME_SC_SGL_INVALID_COUNT                = 0xe,
    RT_NVME_SC_SGL_INVALID_DATA                 = 0xf,
    RT_NVME_SC_SGL_INVALID_METADATA             = 0x10,
    RT_NVME_SC_SGL_INVALID_TYPE                 = 0x11,
    RT_NVME_SC_CMB_INVALID_USE                  = 0x12,
    RT_NVME_SC_PRP_INVALID_OFFSET               = 0x13,
    RT_NVME_SC_ATOMIC_WU_EXCEEDED               = 0x14,
    RT_NVME_SC_OP_DENIED                        = 0x15,
    RT_NVME_SC_SGL_INVALID_OFFSET               = 0x16,
    RT_NVME_SC_RESERVED                         = 0x17,
    RT_NVME_SC_HOST_ID_INCONSIST                = 0x18,
    RT_NVME_SC_KA_TIMEOUT_EXPIRED               = 0x19,
    RT_NVME_SC_KA_TIMEOUT_INVALID               = 0x1a,
    RT_NVME_SC_ABORTED_PREEMPT_ABORT            = 0x1b,
    RT_NVME_SC_SANITIZE_FAILED                  = 0x1c,
    RT_NVME_SC_SANITIZE_IN_PROGRESS             = 0x1d,
    RT_NVME_SC_SGL_INVALID_GRANULARITY          = 0x1e,
    RT_NVME_SC_CMD_NOT_SUP_CMB_QUEUE            = 0x1f,
    RT_NVME_SC_NS_WRITE_PROTECTED               = 0x20,
    RT_NVME_SC_CMD_INTERRUPTED                  = 0x21,
    RT_NVME_SC_TRANSIENT_TR_ERR                 = 0x22,
    RT_NVME_SC_ADMIN_COMMAND_MEDIA_NOT_READY    = 0x24,
    RT_NVME_SC_INVALID_IO_CMD_SET               = 0x2c,

    RT_NVME_SC_LBA_RANGE                        = 0x80,
    RT_NVME_SC_CAP_EXCEEDED                     = 0x81,
    RT_NVME_SC_NS_NOT_READY                     = 0x82,
    RT_NVME_SC_RESERVATION_CONFLICT             = 0x83,
    RT_NVME_SC_FORMAT_IN_PROGRESS               = 0x84,

    /*
     * Command Specific Status:
     */
    RT_NVME_SC_CQ_INVALID                       = 0x100,
    RT_NVME_SC_QID_INVALID                      = 0x101,
    RT_NVME_SC_QUEUE_SIZE                       = 0x102,
    RT_NVME_SC_ABORT_LIMIT                      = 0x103,
    RT_NVME_SC_ABORT_MISSING                    = 0x104,
    RT_NVME_SC_ASYNC_LIMIT                      = 0x105,
    RT_NVME_SC_FIRMWARE_SLOT                    = 0x106,
    RT_NVME_SC_FIRMWARE_IMAGE                   = 0x107,
    RT_NVME_SC_INVALID_VECTOR                   = 0x108,
    RT_NVME_SC_INVALID_LOG_PAGE                 = 0x109,
    RT_NVME_SC_INVALID_FORMAT                   = 0x10a,
    RT_NVME_SC_FW_NEEDS_CONV_RESET              = 0x10b,
    RT_NVME_SC_INVALID_QUEUE                    = 0x10c,
    RT_NVME_SC_FEATURE_NOT_SAVEABLE             = 0x10d,
    RT_NVME_SC_FEATURE_NOT_CHANGEABLE           = 0x10e,
    RT_NVME_SC_FEATURE_NOT_PER_NS               = 0x10f,
    RT_NVME_SC_FW_NEEDS_SUBSYS_RESET            = 0x110,
    RT_NVME_SC_FW_NEEDS_RESET                   = 0x111,
    RT_NVME_SC_FW_NEEDS_MAX_TIME                = 0x112,
    RT_NVME_SC_FW_ACTIVATE_PROHIBITED           = 0x113,
    RT_NVME_SC_OVERLAPPING_RANGE                = 0x114,
    RT_NVME_SC_NS_INSUFFICIENT_CAP              = 0x115,
    RT_NVME_SC_NS_ID_UNAVAILABLE                = 0x116,
    RT_NVME_SC_NS_ALREADY_ATTACHED              = 0x118,
    RT_NVME_SC_NS_IS_PRIVATE                    = 0x119,
    RT_NVME_SC_NS_NOT_ATTACHED                  = 0x11a,
    RT_NVME_SC_THIN_PROV_NOT_SUPP               = 0x11b,
    RT_NVME_SC_CTRL_LIST_INVALID                = 0x11c,
    RT_NVME_SC_SELT_TEST_IN_PROGRESS            = 0x11d,
    RT_NVME_SC_BP_WRITE_PROHIBITED              = 0x11e,
    RT_NVME_SC_CTRL_ID_INVALID                  = 0x11f,
    RT_NVME_SC_SEC_CTRL_STATE_INVALID           = 0x120,
    RT_NVME_SC_CTRL_RES_NUM_INVALID             = 0x121,
    RT_NVME_SC_RES_ID_INVALID                   = 0x122,
    RT_NVME_SC_PMR_SAN_PROHIBITED               = 0x123,
    RT_NVME_SC_ANA_GROUP_ID_INVALID             = 0x124,
    RT_NVME_SC_ANA_ATTACH_FAILED                = 0x125,

    /*
     * I/O Command Set Specific - NVM commands:
     */
    RT_NVME_SC_BAD_ATTRIBUTES                   = 0x180,
    RT_NVME_SC_INVALID_PI                       = 0x181,
    RT_NVME_SC_READ_ONLY                        = 0x182,
    RT_NVME_SC_ONCS_NOT_SUPPORTED               = 0x183,

    /*
     * I/O Command Set Specific - Fabrics commands:
     */
    RT_NVME_SC_CONNECT_FORMAT                   = 0x180,
    RT_NVME_SC_CONNECT_CTRL_BUSY                = 0x181,
    RT_NVME_SC_CONNECT_INVALID_PARAM            = 0x182,
    RT_NVME_SC_CONNECT_RESTART_DISC             = 0x183,
    RT_NVME_SC_CONNECT_INVALID_HOST             = 0x184,

    RT_NVME_SC_DISCOVERY_RESTART                = 0x190,
    RT_NVME_SC_AUTH_REQUIRED                    = 0x191,

    /*
     * I/O Command Set Specific - Zoned commands:
     */
    RT_NVME_SC_ZONE_BOUNDARY_ERROR              = 0x1b8,
    RT_NVME_SC_ZONE_FULL                        = 0x1b9,
    RT_NVME_SC_ZONE_READ_ONLY                   = 0x1ba,
    RT_NVME_SC_ZONE_OFFLINE                     = 0x1bb,
    RT_NVME_SC_ZONE_INVALID_WRITE               = 0x1bc,
    RT_NVME_SC_ZONE_TOO_MANY_ACTIVE             = 0x1bd,
    RT_NVME_SC_ZONE_TOO_MANY_OPEN               = 0x1be,
    RT_NVME_SC_ZONE_INVALID_TRANSITION          = 0x1bf,

    /*
     * Media and Data Integrity Errors:
     */
    RT_NVME_SC_WRITE_FAULT                      = 0x280,
    RT_NVME_SC_READ_ERROR                       = 0x281,
    RT_NVME_SC_GUARD_CHECK                      = 0x282,
    RT_NVME_SC_APPTAG_CHECK                     = 0x283,
    RT_NVME_SC_REFTAG_CHECK                     = 0x284,
    RT_NVME_SC_COMPARE_FAILED                   = 0x285,
    RT_NVME_SC_ACCESS_DENIED                    = 0x286,
    RT_NVME_SC_UNWRITTEN_BLOCK                  = 0x287,

    /*
     * Path-related Errors:
     */
    RT_NVME_SC_INTERNAL_PATH_ERROR              = 0x300,
    RT_NVME_SC_ANA_PERSISTENT_LOSS              = 0x301,
    RT_NVME_SC_ANA_INACCESSIBLE                 = 0x302,
    RT_NVME_SC_ANA_TRANSITION                   = 0x303,
    RT_NVME_SC_CTRL_PATH_ERROR                  = 0x360,
    RT_NVME_SC_HOST_PATH_ERROR                  = 0x370,
    RT_NVME_SC_HOST_ABORTED_CMD                 = 0x371,

    RT_NVME_SC_CRD                              = 0x1800,
    RT_NVME_SC_MORE                             = 0x2000,
    RT_NVME_SC_DNR                              = 0x4000,
};

/* Admin commands */
enum
{
    RT_NVME_ADMIN_OPCODE_DELETE_SQ          = 0x00,
    RT_NVME_ADMIN_OPCODE_CREATE_SQ          = 0x01,
    RT_NVME_ADMIN_OPCODE_GET_LOG_PAGE       = 0x02,
    RT_NVME_ADMIN_OPCODE_DELETE_CQ          = 0x04,
    RT_NVME_ADMIN_OPCODE_CREATE_CQ          = 0x05,
    RT_NVME_ADMIN_OPCODE_IDENTIFY           = 0x06,
    RT_NVME_ADMIN_OPCODE_ABORT_CMD          = 0x08,
    RT_NVME_ADMIN_OPCODE_SET_FEATURES       = 0x09,
    RT_NVME_ADMIN_OPCODE_GET_FEATURES       = 0x0a,
    RT_NVME_ADMIN_OPCODE_ASYNC_EVENT        = 0x0c,
    RT_NVME_ADMIN_OPCODE_NS_MGMT            = 0x0d,
    RT_NVME_ADMIN_OPCODE_ACTIVATE_FW        = 0x10,
    RT_NVME_ADMIN_OPCODE_DOWNLOAD_FW        = 0x11,
    RT_NVME_ADMIN_OPCODE_DEV_SELF_TEST      = 0x14,
    RT_NVME_ADMIN_OPCODE_NS_ATTACH          = 0x15,
    RT_NVME_ADMIN_OPCODE_KEEP_ALIVE         = 0x18,
    RT_NVME_ADMIN_OPCODE_DIRECTIVE_SEND     = 0x19,
    RT_NVME_ADMIN_OPCODE_DIRECTIVE_RECV     = 0x1a,
    RT_NVME_ADMIN_OPCODE_VIRTUAL_MGMT       = 0x1c,
    RT_NVME_ADMIN_OPCODE_NVME_MI_SEND       = 0x1d,
    RT_NVME_ADMIN_OPCODE_NVME_MI_RECV       = 0x1e,
    RT_NVME_ADMIN_OPCODE_DBBUF              = 0x7c,
    RT_NVME_ADMIN_OPCODE_FORMAT_NVM         = 0x80,
    RT_NVME_ADMIN_OPCODE_SECURITY_SEND      = 0x81,
    RT_NVME_ADMIN_OPCODE_SECURITY_RECV      = 0x82,
    RT_NVME_ADMIN_OPCODE_SANITIZE_NVM       = 0x84,
    RT_NVME_ADMIN_OPCODE_GET_LBA_STATUS     = 0x86,
    RT_NVME_ADMIN_OPCODE_VENDOR_START       = 0xc0,
};

/* I/O commands */
enum
{
    RT_NVME_CMD_FLUSH           = 0x00,
    RT_NVME_CMD_WRITE           = 0x01,
    RT_NVME_CMD_READ            = 0x02,
    RT_NVME_CMD_WRITE_UNCOR     = 0x04,
    RT_NVME_CMD_COMPARE         = 0x05,
    RT_NVME_CMD_WRITE_ZEROES    = 0x08,
    RT_NVME_CMD_DSM             = 0x09,
    RT_NVME_CMD_VERIFY          = 0x0c,
    RT_NVME_CMD_RESV_REGISTER   = 0x0d,
    RT_NVME_CMD_RESV_REPORT     = 0x0e,
    RT_NVME_CMD_RESV_ACQUIRE    = 0x11,
    RT_NVME_CMD_RESV_RELEASE    = 0x15,
    RT_NVME_CMD_ZONE_MGMT_SEND  = 0x79,
    RT_NVME_CMD_ZONE_MGMT_RECV  = 0x7a,
    RT_NVME_CMD_ZONE_APPEND     = 0x7d,
    RT_NVME_CMD_VENDOR_START    = 0x80,
};

enum
{
    RT_NVME_PSDT_PRP                    = 0x0,
    RT_NVME_PSDT_SGL_MPTR_CONTIGUOUS    = 0x1,
    RT_NVME_PSDT_SGL_MPTR_SGL           = 0x2,
};

/* Commands flags */
enum
{
    RT_NVME_CMD_FLAGS_FUSE_SHIFT        = 0x00,
    RT_NVME_CMD_FLAGS_PSDT_SHIFT        = 0x06,
};

struct rt_nvme_command_common
{
    rt_uint8_t  opcode;
    rt_uint8_t  flags;
    rt_uint16_t cmdid;
    rt_le32_t   nsid;
    rt_le32_t   cmd_dw2[2];
    rt_le64_t   metadata;
    rt_le64_t   prp1;
    rt_le64_t   prp2;
    rt_le32_t   cmd_dw10[6];
};

rt_packed(struct rt_nvme_sgl_desc
{
    rt_le64_t adddress;
    rt_le32_t length;
    rt_uint8_t reserved[3];
#define SGL_DESC_TYPE_DATA_BLOCK        0x0
#define SGL_DESC_TYPE_BIT_BUCKET        0x1
#define SGL_DESC_TYPE_SEGMENT           0x2
#define SGL_DESC_TYPE_LAST_SEGMENT      0x3
#define SGL_DESC_TYPE_KEYED_DATA_BLOCK  0x4
#define SGL_DESC_TYPE_VENDOR_SPECIFIC   0xf
    rt_uint8_t sgl_identify;
});

struct rt_nvme_command_rw
{
    rt_uint8_t  opcode;
    rt_uint8_t  flags;
    rt_uint16_t cmdid;
    rt_le32_t   nsid;
    NVME_RSVD(8, 8);
    rt_le64_t   metadata;
    union
    {
        struct
        {
            rt_le64_t prp1;
            rt_le64_t prp2;
        };
        struct rt_nvme_sgl_desc sgl;
    };
    rt_le64_t   slba;
    rt_le16_t   length;
    rt_le16_t   control;
    rt_le32_t   dsmgmt;
    rt_le32_t   reftag;
    rt_le16_t   apptag;
    rt_le16_t   appmask;
};

enum
{
    RT_NVME_RW_LR                   = 1 << 15,
    RT_NVME_RW_FUA                  = 1 << 14,
    RT_NVME_RW_APPEND_PIREMAP       = 1 << 9,
    RT_NVME_RW_DSM_FREQ_UNSPEC      = 0,
    RT_NVME_RW_DSM_FREQ_TYPICAL     = 1,
    RT_NVME_RW_DSM_FREQ_RARE        = 2,
    RT_NVME_RW_DSM_FREQ_READS       = 3,
    RT_NVME_RW_DSM_FREQ_WRITES      = 4,
    RT_NVME_RW_DSM_FREQ_RW          = 5,
    RT_NVME_RW_DSM_FREQ_ONCE        = 6,
    RT_NVME_RW_DSM_FREQ_PREFETCH    = 7,
    RT_NVME_RW_DSM_FREQ_TEMP        = 8,
    RT_NVME_RW_DSM_LATENCY_NONE     = 0 << 4,
    RT_NVME_RW_DSM_LATENCY_IDLE     = 1 << 4,
    RT_NVME_RW_DSM_LATENCY_NORM     = 2 << 4,
    RT_NVME_RW_DSM_LATENCY_LOW      = 3 << 4,
    RT_NVME_RW_DSM_SEQ_REQ          = 1 << 6,
    RT_NVME_RW_DSM_COMPRESSED       = 1 << 7,
    RT_NVME_RW_PRINFO_PRCHK_REF     = 1 << 10,
    RT_NVME_RW_PRINFO_PRCHK_APP     = 1 << 11,
    RT_NVME_RW_PRINFO_PRCHK_GUARD   = 1 << 12,
    RT_NVME_RW_PRINFO_PRACT         = 1 << 13,
    RT_NVME_RW_DTYPE_STREAMS        = 1 << 4,
    RT_NVME_WZ_DEAC                 = 1 << 9,
};

enum
{
    RT_NVME_QUEUE_PHYS_CONTIG   = (1 << 0),
    RT_NVME_CQ_IRQ_ENABLED      = (1 << 1),
    RT_NVME_SQ_PRIO_URGENT      = (0 << 1),
    RT_NVME_SQ_PRIO_HIGH        = (1 << 1),
    RT_NVME_SQ_PRIO_MEDIUM      = (2 << 1),
    RT_NVME_SQ_PRIO_LOW         = (3 << 1),
    RT_NVME_FEAT_ARBITRATION    = 0x01,
    RT_NVME_FEAT_POWER_MGMT     = 0x02,
    RT_NVME_FEAT_LBA_RANGE      = 0x03,
    RT_NVME_FEAT_TEMP_THRESH    = 0x04,
    RT_NVME_FEAT_ERR_RECOVERY   = 0x05,
    RT_NVME_FEAT_VOLATILE_WC    = 0x06,
    RT_NVME_FEAT_NUM_QUEUES     = 0x07,
    RT_NVME_FEAT_IRQ_COALESCE   = 0x08,
    RT_NVME_FEAT_IRQ_CONFIG     = 0x09,
    RT_NVME_FEAT_WRITE_ATOMIC   = 0x0a,
    RT_NVME_FEAT_ASYNC_EVENT    = 0x0b,
    RT_NVME_FEAT_AUTO_PST       = 0x0c,
    RT_NVME_FEAT_SW_PROGRESS    = 0x80,
    RT_NVME_FEAT_HOST_ID        = 0x81,
    RT_NVME_FEAT_RESV_MASK      = 0x82,
    RT_NVME_FEAT_RESV_PERSIST   = 0x83,
    RT_NVME_LOG_ERROR           = 0x01,
    RT_NVME_LOG_SMART           = 0x02,
    RT_NVME_LOG_FW_SLOT         = 0x03,
    RT_NVME_LOG_RESERVATION     = 0x80,
    RT_NVME_FWACT_REPL          = (0 << 3),
    RT_NVME_FWACT_REPL_ACTV     = (1 << 3),
    RT_NVME_FWACT_ACTV          = (2 << 3),
};

struct rt_nvme_command_identify
{
    rt_uint8_t  opcode;
    rt_uint8_t  flags;
    rt_uint16_t cmdid;
    rt_le32_t   nsid;
    NVME_RSVD(8, 16);
    rt_le64_t   prp1;
    rt_le64_t   prp2;
    rt_le32_t   cns;
    NVME_RSVD(64, 20);
};

struct rt_nvme_command_features
{
    rt_uint8_t  opcode;
    rt_uint8_t  flags;
    rt_uint16_t cmdid;
    rt_le32_t   nsid;
    NVME_RSVD(8, 16);
    rt_le64_t   prp1;
    rt_le64_t   prp2;
    rt_le32_t   fid;
    rt_le32_t   dword11;
    NVME_RSVD(68, 16);
};

struct rt_nvme_command_create_cq
{
    rt_uint8_t  opcode;
    rt_uint8_t  flags;
    rt_uint16_t cmdid;
    NVME_RSVD(4, 20);
    rt_le64_t   prp1;
    NVME_RSVD(32, 8);
    rt_le16_t   cqid;
    rt_le16_t   qsize;
    rt_le16_t   cq_flags;
    rt_le16_t   irq_vector;
    NVME_RSVD(104, 16);
};

struct rt_nvme_command_create_sq
{
    rt_uint8_t  opcode;
    rt_uint8_t  flags;
    rt_uint16_t cmdid;
    NVME_RSVD(4, 20);
    rt_le64_t   prp1;
    NVME_RSVD(32, 8);
    rt_le16_t   sqid;
    rt_le16_t   qsize;
    rt_le16_t   sq_flags;
    rt_le16_t   cqid;
    NVME_RSVD(104, 16);
};

struct rt_nvme_command_delete_queue
{
    rt_uint8_t  opcode;
    rt_uint8_t  flags;
    rt_uint16_t cmdid;
    NVME_RSVD(4, 36);
    rt_le16_t   qid;
    NVME_RSVD(42, 22);
};

struct rt_nvme_command_write_zeroes
{
    rt_uint8_t  opcode;
    rt_uint8_t  flags;
    rt_uint16_t cmdid;
    rt_le32_t   nsid;
    NVME_RSVD(8, 8);
    rt_le64_t   metadata;
    rt_le64_t   prp1;
    rt_le64_t   prp2;
    rt_le64_t   slba;
    rt_le16_t   length;
    rt_le16_t   control;
    rt_le32_t   dsmgmt;
    rt_le32_t   reftag;
    rt_le16_t   apptag;
    rt_le16_t   appmask;
};

struct rt_nvme_command
{
    union
    {
        struct rt_nvme_command_common common;
        struct rt_nvme_command_rw rw;
        struct rt_nvme_command_identify identify;
        struct rt_nvme_command_features features;
        struct rt_nvme_command_create_cq create_cq;
        struct rt_nvme_command_create_sq create_sq;
        struct rt_nvme_command_delete_queue delete_queue;
        struct rt_nvme_command_write_zeroes write_zeroes;
    };
};

struct rt_nvme_completion
{
    union
    {
        rt_le16_t  u16;
        rt_le32_t  u32;
        rt_le64_t  u64;
    } result;
    rt_le16_t   sq_head;    /* How much of this queue may be reclaimed */
    rt_le16_t   sq_id;      /* Submission queue that generated this entry */
    rt_uint16_t cmdid;      /* Which command completed */
    rt_le16_t   status;     /* Command status */
};

enum
{
    RT_NVME_REG_CAP         = 0x0000,   /* Controller Capabilities */
    RT_NVME_REG_VS          = 0x0008,   /* Version */
    RT_NVME_REG_INTMS       = 0x000c,   /* Interrupt Mask Set */
    RT_NVME_REG_INTMC       = 0x0010,   /* Interrupt Mask Clear */
    RT_NVME_REG_CC          = 0x0014,   /* Controller Configuration */
    RT_NVME_REG_CSTS        = 0x001c,   /* Controller Status */
    RT_NVME_REG_NSSR        = 0x0020,   /* NVM Subsystem Reset */
    RT_NVME_REG_AQA         = 0x0024,   /* Admin Queue Attributes */
    RT_NVME_REG_ASQ         = 0x0028,   /* Admin SQ Base Address */
    RT_NVME_REG_ACQ         = 0x0030,   /* Admin CQ Base Address */
    RT_NVME_REG_CMBLOC      = 0x0038,   /* Controller Memory Buffer Location */
    RT_NVME_REG_CMBSZ       = 0x003c,   /* Controller Memory Buffer Size */
    RT_NVME_REG_BPINFO      = 0x0040,   /* Boot Partition Information */
    RT_NVME_REG_BPRSEL      = 0x0044,   /* Boot Partition Read Select */
    RT_NVME_REG_BPMBL       = 0x0048,   /* Boot Partition Memory Buffer Location */
    RT_NVME_REG_CMBMSC      = 0x0050,   /* Controller Memory Buffer Memory Space Control */
    RT_NVME_REG_CRTO        = 0x0068,   /* Controller Ready Timeouts */
    RT_NVME_REG_PMRCAP      = 0x0e00,   /* Persistent Memory Capabilities */
    RT_NVME_REG_PMRCTL      = 0x0e04,   /* Persistent Memory Region Control */
    RT_NVME_REG_PMRSTS      = 0x0e08,   /* Persistent Memory Region Status */
    RT_NVME_REG_PMREBS      = 0x0e0c,   /* Persistent Memory Region Elasticity Buffer Size */
    RT_NVME_REG_PMRSWTP     = 0x0e10,   /* Persistent Memory Region Sustained Write Throughput */
    RT_NVME_REG_DBS         = 0x1000,   /* SQ 0 Tail Doorbell */
};

#define RT_NVME_CAP_MQES(cap)       ((cap) & 0xffff)
#define RT_NVME_CAP_TIMEOUT(cap)    (((cap) >> 24) & 0xff)
#define RT_NVME_CAP_STRIDE(cap)     (((cap) >> 32) & 0xf)
#define RT_NVME_CAP_MPSMIN(cap)     (((cap) >> 48) & 0xf)
#define RT_NVME_CAP_MPSMAX(cap)     (((cap) >> 52) & 0xf)

#define RT_NVME_VS(major, minor)    (((major) << 16) | ((minor) << 8))

#define RT_NVME_AQ_DEPTH            32
#define RT_NVME_NR_AEN_COMMANDS     1
#define RT_NVME_AQ_BLK_MQ_DEPTH     (RT_NVME_AQ_DEPTH - RT_NVME_NR_AEN_COMMANDS)
#define RT_NVME_AQ_MQ_TAG_DEPTH     (RT_NVME_AQ_BLK_MQ_DEPTH - 1)

enum
{
    RT_NVME_CC_ENABLE           = 1 << 0,
    RT_NVME_CC_CSS_NVM          = 0 << 4,
    RT_NVME_CC_MPS_SHIFT        = 7,
    RT_NVME_CC_ARB_RR           = 0 << 11,
    RT_NVME_CC_ARB_WRRU         = 1 << 11,
    RT_NVME_CC_ARB_VS           = 7 << 11,
    RT_NVME_CC_SHN_NONE         = 0 << 14,
    RT_NVME_CC_SHN_NORMAL       = 1 << 14,
    RT_NVME_CC_SHN_ABRUPT       = 2 << 14,
    RT_NVME_CC_SHN_MASK         = 3 << 14,
    RT_NVME_CC_IOSQES           = 6 << 16,
    RT_NVME_CC_IOCQES           = 4 << 20,
    RT_NVME_CSTS_RDY            = 1 << 0,
    RT_NVME_CSTS_CFS            = 1 << 1,
    RT_NVME_CSTS_SHST_NORMAL    = 0 << 2,
    RT_NVME_CSTS_SHST_OCCUR     = 1 << 2,
    RT_NVME_CSTS_SHST_CMPLT     = 2 << 2,
    RT_NVME_CSTS_SHST_MASK      = 3 << 2,
};

rt_packed(struct rt_nvme_id_power_state
{
    rt_le16_t   mp;         /* Maximum Power */
    NVME_RSVD(1, 1);
    rt_uint8_t  mxps_nops;  /* Max Power Scale, Non-Operational State */
    rt_le32_t   enlat;      /* Entry Latency: microseconds */
    rt_le32_t   exlat;      /* Exit Latency: microseconds */
    rt_uint8_t  rrt;        /* Relative Read Throughput */
    rt_uint8_t  rrl;        /* Relative Read Latency */
    rt_uint8_t  rwt;        /* Relative Write Throughput */
    rt_uint8_t  rwl;        /* Relative Write Latency */
    rt_le16_t   idlp;       /* Idle Power */
    rt_uint8_t  ips;        /* Idle Power Scale */
    NVME_RSVD(19, 1);
    rt_le16_t   actp;       /* Active Power */
    rt_uint8_t  apw_aps;    /* Active Power Workload, Active Power Scale */
    NVME_RSVD(23, 9);
});

rt_packed(struct rt_nvme_id_ctrl
{
    /* Controller Capabilities and Features */
    rt_le16_t       vid;            /* PCI Vendor ID */
    rt_le16_t       ssvid;          /* PCI Subsystem Vendor */
    char            sn[20];         /* Serial Number */
    char            mn[40];         /* Model Number */
    char            fr[8];          /* Firmware Revision */
    rt_uint8_t      rab;            /* Recommended Arbitration Burst */
    rt_uint8_t      ieee[3];        /* IEEE OUI Identifier */
    rt_uint8_t      mic;            /* Controller Multi-Path I/O and Namespace Sharing Capabilities */
    rt_uint8_t      mdts;           /* Maximum Data Transfer Size */
    rt_uint16_t     cntlid;         /* Controller ID */
    rt_uint32_t     ver;            /* Version */
    rt_uint32_t     rtd3r;          /* RTD3 Resume Latency */
    rt_uint32_t     rtd3e;          /* RTD3 Entry Latency */
    rt_uint32_t     oaes;           /* Optional Asynchronous Events Supported */
#define RT_NVME_ID_CTRATT_ELBAS     15  /* Extended LBA Formats Supported */
#define RT_NVME_ID_CTRATT_DNVMS     14  /* Delete NVM Set */
#define RT_NVME_ID_CTRATT_DEG       13  /* Delete Endurance Group */
#define RT_NVME_ID_CTRATT_VCM       12  /* Variable Capacity Management */
#define RT_NVME_ID_CTRATT_FCM       11  /* Fixed Capacity Management */
#define RT_NVME_ID_CTRATT_MDS       10  /* Multi-Domain Subsystem */
#define RT_NVME_ID_CTRATT_UUIDL     9   /* UUID List */
#define RT_NVME_ID_CTRATT_SQA       8   /* SQ Associations */
#define RT_NVME_ID_CTRATT_NG        7   /* Namespace Granularity */
#define RT_NVME_ID_CTRATT_TBKAS     6   /* Traffic Based Keep Alive Support */
#define RT_NVME_ID_CTRATT_PLM       5   /* Predictable Latency Mode */
#define RT_NVME_ID_CTRATT_EG        4   /* Endurance Groups */
#define RT_NVME_ID_CTRATT_RRL       3   /* Read Recovery Levels */
#define RT_NVME_ID_CTRATT_NVMS      2   /* NVM Sets */
#define RT_NVME_ID_CTRATT_NOPSPM    1   /* Non-Operational Power State Permissive Mode */
#define RT_NVME_ID_CTRATT_HIS       0   /* Host Identifier Support */
    rt_uint32_t     ctratt;         /* Controller Attributes */
    rt_uint16_t     rrls;           /* Read Recovery Levels Supported */
    NVME_RSVD(102, 9);
    rt_uint8_t      cntrltype;      /* Controller Type */
    rt_uint8_t      fguid[16];      /* FRU Globally Unique Identifier */
    rt_uint16_t     crdt1;          /* Command Retry Delay Time 1 */
    rt_uint16_t     crdt2;          /* Command Retry Delay Time 2 */
    rt_uint16_t     crdt3;          /* Command Retry Delay Time 3 */
    NVME_RSVD(134, 119);
#define RT_NVME_ID_NVMSR_NVMEE      1   /* NVMe Enclosure */
#define RT_NVME_ID_NVMSR_NVMESD     0   /* NVMe Storage Device */
    rt_uint8_t      nvmsr;          /* NVM Subsystem Report */

#define RT_NVME_ID_VWCI_VWCRV       7   /* VPD Write Cycles Remaining Valid */
#define RT_NVME_ID_VWCI_VWCR        0   /* VPD Write Cycles Remaining */
    rt_uint8_t      vwci;           /* VPD Write Cycle Information */
#define RT_NVME_ID_MEC_PCIEME       1   /* PCIe Port Management Endpoint */
#define RT_NVME_ID_MEC_SMBUSME      0   /* SMBus/I2C Port Management Endpoint */
    rt_uint8_t      mec;            /* Management Endpoint Capabilities  */

    /* Admin Command Set Attributes & Optional Controller Capabilities */
    rt_le16_t       oacs;           /* Optional Admin Command Support */
    rt_uint8_t      acl;            /* Abort Command Limit */
    rt_uint8_t      aerl;           /* Asynchronous Event Request Limit */
#define RT_NVME_ID_FRMW_SMUD        5   /* Support Multiple Update Detection */
#define RT_NVME_ID_FRMW_FAWR        4   /* Firmware Activation Without Reset */
#define RT_NVME_ID_FRMW_NOFS        1   /* Number Of Firmware Slots */
#define RT_NVME_ID_FRMW_FFSRO       0   /* First Firmware Slot Read Only */
    rt_uint8_t      frmw;           /* Firmware Updates */
    rt_uint8_t      lpa;            /* Log Page Attributes */
    rt_uint8_t      elpe;           /* Error Log Page Entries */
    rt_uint8_t      npss;           /* Number of Power States Support */
    rt_uint8_t      avscc;          /* Admin Vendor Specific Command Configuration */
    rt_uint8_t      apsta;          /* Autonomous Power State Transition Attributes */
    rt_le16_t       wctemp;         /* Warning Composite Temperature Threshold */
    rt_le16_t       cctemp;         /* Critical Composite Temperature Threshold */
    rt_uint16_t     mtfa;           /* Maximum Time for Firmware Activation */
    rt_uint32_t     hmpre;          /* Host Memory Buffer Preferred Size */
    rt_uint32_t     hmmin;          /* Host Memory Buffer Minimum Size */
    rt_uint8_t      tnvmcap[16];    /* Total NVM Capacity */
    rt_uint8_t      unvmcap[16];    /* Unallocated NVM Capacity */
#define RT_NVME_ID_RPMBS_ASZ        24  /* Access Size */
#define RT_NVME_ID_RPMBS_TSZ        16  /* Total Size */
#define RT_NVME_ID_RPMBS_AM         3   /* Authentication Method */
#define RT_NVME_ID_RPMBS_NORPMBU    2   /* Number of RPMB Units */
    rt_uint32_t     rpmbs;          /* Replay Protected Memory Block Support */
    rt_uint16_t     edstt;          /* Extended Device Self-test Time */
    rt_uint8_t      dsto;           /* Device Self-test Options */
    rt_uint8_t      fwug;           /* Firmware Update Granularity */
    rt_uint16_t     kas;            /* Keep Alive Support */
    rt_uint16_t     hctma;          /* Host Controlled Thermal Management Attributes */
    rt_uint16_t     mntmt;          /* Minimum Thermal Management Temperature */
    rt_uint16_t     mxtmt;          /* Maximum Thermal Management Temperature */
#define RT_NVME_ID_SANICAP_NODMMAS  30  /* No-Deallocate Modifies Media After Sanitize */
#define RT_NVME_ID_SANICAP_NDI      29  /* No-Deallocate Inhibited */
#define RT_NVME_ID_SANICAP_OWS      2   /* Overwrite Support */
#define RT_NVME_ID_SANICAP_BES      1   /* Block Erase Support */
#define RT_NVME_ID_SANICAP_CES      0   /* Crypto Erase Support */
    rt_uint32_t     sanicap;        /* Sanitize Capabilities */
    rt_uint32_t     hmminds;        /* Host Memory Buffer Minimum Descriptor Entry Size */
    rt_uint16_t     hmmaxd;         /* Host Memory Maximum Descriptors Entries */
    rt_uint16_t     nsetidmax;      /* NVM Set Identifier Maximum */
    rt_uint16_t     endgidmax;      /* Endurance Group Identifier Maximum */
    rt_uint8_t      anatt;          /* ANA Transition Time */
    rt_uint8_t      anacap;         /* Asymmetric Namespace Access Capabilities */
    rt_uint32_t     anagrpmax;      /* ANA Group Identifier Maximum */
    rt_uint32_t     nanagrpid;      /* Number of ANA Group Identifiers */
    rt_uint32_t     pels;           /* Persistent Event Log Size */
    rt_uint16_t     dmid;           /* Domain Identifier */
    NVME_RSVD(358, 10);
    rt_uint8_t      megcap[16];     /* Max Endurance Group Capacity */
    NVME_RSVD(384, 128);

    /* NVM Command Set Attributes */
    rt_uint8_t      sqes;           /* Submission Queue Entry Size */
    rt_uint8_t      cqes;           /* Completion Queue Entry Size */
    rt_le16_t       maxcmd;         /* Maximum Outstanding Commands */
    rt_le32_t       nn;             /* Number of Namespaces */
    rt_le16_t       oncs;           /* Optional NVM Command Support */
    rt_le16_t       fuses;          /* Fused Operation Support */
    rt_uint8_t      fna;            /* Format NVM Attributes */
    rt_uint8_t      vwc;            /* Volatile Write Cache */
    rt_le16_t       awun;           /* Atomic Write Unit Normal */
    rt_le16_t       awupf;          /* Atomic Write Unit Power Fail */
    rt_uint8_t      nvscc;          /* I/O Command Set Vendor Specific Command Configuration */
    rt_uint8_t      nwpc;           /* Namespace Write Protection Capabilities */
    rt_le16_t       acwu;           /* Atomic Compare & Write Unit */
    rt_le16_t       cdfs;           /* Copy Descriptor Formats Supported */
#define RT_NVME_ID_SGL_SUPPORT_MASK 0x3
    rt_le32_t       sgls;           /* SGL Support */
    rt_uint32_t     mnan;           /* Maximum Number of Allowed Namespaces */
    char            maxdna[16];     /* Maximum Domain Namespace Attachments */
    rt_le32_t       maxcna;         /* Maximum I/O Controller Namespace Attachments */
    NVME_RSVD(564, 204);
    rt_uint8_t      subnqn[256];    /* NVM Subsystem NVMe Qualified Name */
    NVME_RSVD(1024, 768);
    rt_le32_t       ioccsz;         /* I/O Queue Command Capsule Supported Size */
    rt_le32_t       iorcsz;         /* I/O Queue Response Capsule Supported Size */
    rt_le16_t       icdoff;         /* In Capsule Data Offset */
    rt_uint8_t      ctrattr;        /* Fabrics Controller Attributes */
    rt_uint8_t      msdbd;          /* Maximum SGL Data Block Descriptors */
    rt_le16_t       ofcs;           /* Optional Fabric Commands Support */
    rt_uint8_t      dctype;
    NVME_RSVD(1807, 241);

    /* Power State Descriptors */
    struct rt_nvme_id_power_state psd[32];

    /* Vendor Specific */
    rt_uint8_t      vs[1024];
});

enum
{
    RT_NVME_CTRL_CMIC_MULTI_PORT                = 1 << 0,
    RT_NVME_CTRL_CMIC_MULTI_CTRL                = 1 << 1,
    RT_NVME_CTRL_CMIC_ANA                       = 1 << 3,
    RT_NVME_CTRL_ONCS_COMPARE                   = 1 << 0,
    RT_NVME_CTRL_ONCS_WRITE_UNCORRECTABLE       = 1 << 1,
    RT_NVME_CTRL_ONCS_DSM                       = 1 << 2,
    RT_NVME_CTRL_ONCS_WRITE_ZEROES              = 1 << 3,
    RT_NVME_CTRL_ONCS_RESERVATIONS              = 1 << 5,
    RT_NVME_CTRL_ONCS_TIMESTAMP                 = 1 << 6,
    RT_NVME_CTRL_VWC_PRESENT                    = 1 << 0,
    RT_NVME_CTRL_OACS_SEC_SUPP                  = 1 << 0,
    RT_NVME_CTRL_OACS_NS_MNGT_SUPP              = 1 << 3,
    RT_NVME_CTRL_OACS_DIRECTIVES                = 1 << 5,
    RT_NVME_CTRL_OACS_DBBUF_SUPP                = 1 << 8,
    RT_NVME_CTRL_LPA_CMD_EFFECTS_LOG            = 1 << 1,
    RT_NVME_CTRL_CTRATT_128_ID                  = 1 << 0,
    RT_NVME_CTRL_CTRATT_NON_OP_PSP              = 1 << 1,
    RT_NVME_CTRL_CTRATT_NVM_SETS                = 1 << 2,
    RT_NVME_CTRL_CTRATT_READ_RECV_LVLS          = 1 << 3,
    RT_NVME_CTRL_CTRATT_ENDURANCE_GROUPS        = 1 << 4,
    RT_NVME_CTRL_CTRATT_PREDICTABLE_LAT         = 1 << 5,
    RT_NVME_CTRL_CTRATT_NAMESPACE_GRANULARITY   = 1 << 7,
    RT_NVME_CTRL_CTRATT_UUID_LIST               = 1 << 9,
};

struct rt_nvme_lba_format
{
    rt_le16_t   ms;         /* Metadata size */
    rt_uint8_t  ds;         /* Data size */
    rt_uint8_t  rp;         /* Relative performance */
};

rt_packed(struct rt_nvme_id_ns
{
    rt_le64_t   nsze;       /* Namespace size */
    rt_le64_t   ncap;       /* Namespace capacity */
    rt_le64_t   nuse;       /* Namespace utilization */
    rt_uint8_t  nsfeat;     /* Namespace features */
    rt_uint8_t  nlbaf;      /* Number of lba formats */
    rt_uint8_t  flbas;      /* Formatted lba size */
    rt_uint8_t  mc;         /* Metadata capabilities */
    rt_uint8_t  dpc;        /* End-to-end data protection capabilities */
    rt_uint8_t  dps;        /* End-to-end data protection type settings */
    rt_uint8_t  nmic;       /* Namespace Multi-path I/O and Namespace Sharing Capabilities */
    rt_uint8_t  rescap;     /* Reservation Capabilities */
    rt_uint8_t  fpi;        /* Format Progress Indicator */
    rt_uint8_t  dlfeat;     /* Deallocate Logical Block Features */
    rt_le16_t   nawun;      /* Namespace Atomic Write Unit Normal  */
    rt_le16_t   nawupf;     /* Namespace Atomic Write Unit Power Fail */
    rt_le16_t   nacwu;      /* Namespace Atomic Compare & Write Unit */
    rt_le16_t   nabsn;      /* Namespace Atomic Boundary Size Normal */
    rt_le16_t   nabo;       /* Namespace Atomic Boundary Offset */
    rt_le16_t   nabspf;     /* Namespace Atomic Boundary Size Power Fail */
    rt_uint16_t noiob;      /* Namespace Optimal IO Boundary */
    rt_le64_t   nvmcap[2];  /* NVMe Capacity */
    rt_uint16_t npwg;       /* Namespace Preferred Write Granularity  */
    rt_uint16_t npwa;       /* Namespace Preferred Write Alignment */
    rt_uint16_t npdg;       /* Namespace Preferred Deallocate Granularity */
    rt_uint16_t npda;       /* Namespace Preferred Deallocate Alignment */
    rt_uint16_t nows;       /* Namespace Optimal Write Size */
    NVME_RSVD(118, 18);
    rt_uint32_t anagrpid;   /* ANA Group Identifier */
    NVME_RSVD(139, 3);
    rt_uint8_t  nsattr;     /* Namespace Attributes */
    rt_uint16_t nvmsetid;   /* NVMe Set Identifier */
    rt_uint16_t endgid;     /* Endurance Group Identifier */
    rt_uint8_t  nguid[16];  /* Namespace Globally Unique Identifier */
    rt_uint8_t  eui64[8];   /* IEEE Extended Unique Identifier */

    /* Logical Block Address Format */
    struct rt_nvme_lba_format lbaf[16];
    NVME_RSVD(171, 192);

    /* Vendor specific */
    rt_uint8_t  vs[3712];
});

enum
{
    RT_NVME_NS_FEAT_THIN        = 1 << 0,
    RT_NVME_NS_FLBAS_LBA_MASK   = 0xf,
    RT_NVME_NS_FLBAS_LBA_UMASK  = 0x60,
    RT_NVME_NS_FLBAS_LBA_SHIFT  = 1,
    RT_NVME_NS_FLBAS_META_EXT   = 0x10,
    RT_NVME_LBAF_RP_BEST        = 0,
    RT_NVME_LBAF_RP_BETTER      = 1,
    RT_NVME_LBAF_RP_GOOD        = 2,
    RT_NVME_LBAF_RP_DEGRADED    = 3,
    RT_NVME_NS_DPC_PI_LAST      = 1 << 4,
    RT_NVME_NS_DPC_PI_FIRST     = 1 << 3,
    RT_NVME_NS_DPC_PI_TYPE3     = 1 << 2,
    RT_NVME_NS_DPC_PI_TYPE2     = 1 << 1,
    RT_NVME_NS_DPC_PI_TYPE1     = 1 << 0,
    RT_NVME_NS_DPS_PI_FIRST     = 1 << 3,
    RT_NVME_NS_DPS_PI_MASK      = 0x7,
    RT_NVME_NS_DPS_PI_TYPE1     = 1,
    RT_NVME_NS_DPS_PI_TYPE2     = 2,
    RT_NVME_NS_DPS_PI_TYPE3     = 3,
};

struct rt_nvme_ops;
struct rt_nvme_controller;

/*
 * An NVM Express queue. Each device has at least two (one for admin commands
 * and one for I/O commands).
 */
struct rt_nvme_queue
{
    struct rt_nvme_controller *nvme;
    struct rt_nvme_command *sq_cmds;
    struct rt_nvme_completion *cq_entry;

    rt_ubase_t sq_cmds_phy;
    rt_ubase_t cq_entry_phy;

    rt_uint32_t *doorbell;
    rt_uint16_t qid;
    rt_uint16_t depth;
    rt_uint16_t sq_head;
    rt_uint16_t sq_tail;
    rt_uint16_t cq_head;
    rt_uint16_t cq_phase;

    rt_err_t err;
    struct rt_nvme_command *cmd;

    struct rt_completion done;
    struct rt_spinlock lock;
};

struct rt_nvme_controller
{
    rt_list_t list;
    struct rt_device *dev;

    int nvme_id;
    char name[RT_NAME_MAX];

    void *regs;
    rt_uint64_t cap;
    rt_uint32_t page_shift;
    rt_uint32_t page_size;
    rt_uint32_t queue_depth;
    rt_uint32_t io_queue_max;
    rt_uint32_t ctrl_config;
    rt_uint32_t max_transfer_shift:8;
    rt_uint32_t volatile_write_cache:8;
    rt_uint32_t write_zeroes:1;
    rt_uint32_t sgl_mode:2;
    rt_uint32_t doorbell_stride;
    rt_uint32_t *doorbell_tbl;

    const struct rt_nvme_ops *ops;

#define RT_USING_NVME_QUEUE (1 + (RT_USING_NVME_IO_QUEUE * RT_CPUS_NR))
    int irqs_nr;
    int irqs[RT_USING_NVME_QUEUE];
    union
    {
        struct
        {
            struct rt_nvme_queue admin_queue;
            struct rt_nvme_queue io_queues[RT_USING_NVME_IO_QUEUE * RT_CPUS_NR];
        };
        struct rt_nvme_queue queue[RT_USING_NVME_QUEUE];
    };

    volatile rt_atomic_t cmdid;
    volatile rt_atomic_t ioqid[RT_CPUS_NR];

    rt_list_t ns_nodes;
};

struct rt_nvme_device
{
    struct rt_blk_disk parent;
    struct rt_nvme_controller *ctrl;

    rt_list_t list;

    rt_uint32_t nsid;
    rt_uint32_t lba_shift;
    struct rt_nvme_id_ns id;
};
#define rt_disk_to_nvme_device(disk) rt_container_of(disk, struct rt_nvme_device, parent)

struct rt_nvme_ops
{
    const char *name;

    /* Controller-specific NVM Express queue setup */
    rt_err_t (*setup_queue)(struct rt_nvme_queue *queue);
    /* Controller-specific NVM Express queue cleanup */
    rt_err_t (*cleanup_queue)(struct rt_nvme_queue *queue);
    /* Controller-specific NVM Express command submission */
    rt_err_t (*submit_cmd)(struct rt_nvme_queue *queue, struct rt_nvme_command *cmd);
    /* Controller-specific NVM Express command completion */
    void (*complete_cmd)(struct rt_nvme_queue *queue, struct rt_nvme_command *cmd);
};

rt_err_t rt_nvme_controller_register(struct rt_nvme_controller *nvme);
rt_err_t rt_nvme_controller_unregister(struct rt_nvme_controller *nvme);

#endif /* __NVME_H__ */
