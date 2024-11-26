/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#ifndef __SCSI_H__
#define __SCSI_H__

#include <rthw.h>
#include <rtthread.h>
#include <drivers/byteorder.h>

#define RT_SCSI_LUN_SHIFT       5

rt_packed(struct rt_scsi_unknow
{
    rt_uint8_t opcode;
});

rt_packed(struct rt_scsi_test_unit_ready
{
    rt_uint8_t opcode;
    rt_uint8_t reserved[4];
    rt_uint8_t control;
    rt_uint8_t pad[6];      /* To be ATAPI compatible */
});

rt_packed(struct rt_scsi_inquiry
{
    rt_uint8_t opcode;
    rt_uint8_t config;      /* 7-2 Reserved, 1 Obsolete Formerly CMDDT, 0 EVPD */
    rt_uint8_t page;        /* Page code if EVPD=1 */
    rt_uint8_t reserved;
    rt_uint8_t alloc_length;
    rt_uint8_t control;
    rt_uint8_t pad[6];      /* To be ATAPI compatible */
});

rt_packed(struct rt_scsi_inquiry_data
{
#define RT_SCSI_DEVTYPE_MASK  31
    rt_uint8_t devtype;
#define RT_SCSI_REMOVABLE_BIT 7
    rt_uint8_t rmb;
    rt_uint8_t reserved[2];
    rt_uint8_t length;
    rt_uint8_t reserved1[3];
    char vendor[8];
    char prodid[16];
    char prodrev[4];
});

rt_packed(struct rt_scsi_request_sense
{
    rt_uint8_t opcode;
    rt_uint8_t config;      /* 7-2 Reserved, 1 Obsolete, 0 SP */
    rt_uint8_t reserved[2];
    rt_uint8_t alloc_length;
    rt_uint8_t control;
    rt_uint8_t pad[6];      /* To be ATAPI compatible */
});

rt_packed(struct rt_scsi_request_sense_data
{
    rt_uint8_t error_code;  /* 7 Valid, 6-0 Err. code */
    rt_uint8_t segment_number;
    rt_uint8_t sense_key;   /* 7 FileMark, 6 EndOfMedia, 5 ILI, 4-0 sense key */
    rt_be32_t information;
    rt_uint8_t additional_sense_length;
    rt_be32_t cmd_specific_info;
    rt_uint8_t additional_sense_code;
    rt_uint8_t additional_sense_code_qualifier;
    rt_uint8_t field_replaceable_unit_code;
    rt_uint8_t sense_key_specific[3];
});

rt_packed(struct rt_scsi_read_capacity10
{
    rt_uint8_t opcode;
    rt_uint8_t config;              /* 7-1 Reserved, 0 Obsolete */
    rt_be32_t logical_block_addr;   /* only if PMI=1 */
    rt_uint8_t reserved[2];
    rt_uint8_t pmi;
    rt_uint8_t control;
    rt_be16_t pad;                  /* To be ATAPI compatible */
});

rt_packed(struct rt_scsi_read_capacity10_data
{
    rt_be32_t last_block;
    rt_be32_t block_size;
});

rt_packed(struct rt_scsi_read_capacity16
{
    rt_uint8_t opcode;
    rt_uint8_t config;              /* 7-5 Reserved, 4-0 SERVICE ACTION 0x10 */
    rt_be64_t logical_block_addr;   /* only if PMI=1 */
    rt_be32_t alloc_len;
    rt_uint8_t pmi;
    rt_uint8_t control;
});

rt_packed(struct rt_scsi_read_capacity16_data
{
    rt_be64_t last_block;
    rt_be32_t block_size;
    rt_uint8_t pad[20];
});

rt_packed(struct rt_scsi_read10
{
    rt_uint8_t opcode;
    rt_uint8_t config;      /* 7-5 RDPROTECT, 4 DPO, 3 FUA, 2 RARC, 1 Obsolete, 0 Obsolete */
    rt_be32_t lba;
    rt_uint8_t reserved;
    rt_be16_t size;
    rt_uint8_t reserved2;
    rt_be16_t pad;
});

rt_packed(struct rt_scsi_read12
{
    rt_uint8_t opcode;
    rt_uint8_t config;      /* 7-5 RDPROTECT, 4 DPO, 3 FUA, 2 RARC, 1 Obsolete, 0 Obsolete */
    rt_be32_t lba;
    rt_be32_t size;
    rt_uint8_t reserved;
    rt_uint8_t control;
});

rt_packed(struct rt_scsi_read16
{
    rt_uint8_t opcode;
    rt_uint8_t config;      /* 7-5 RDPROTECT, 4 DPO, 3 FUA, 2 RARC, 1 Obsolete, 0 DLD2 */
    rt_be64_t lba;
    rt_be32_t size;
    rt_uint8_t reserved;
    rt_uint8_t control;
});

rt_packed(struct rt_scsi_write10
{
    rt_uint8_t opcode;
    rt_uint8_t config;      /* 7-5 WRPROTECT, 4 DPO, 3 FUA, 2 Reserved, 1 Obsolete, 0 Obsolete */
    rt_be32_t lba;
    rt_uint8_t reserved;
    rt_be16_t size;
    rt_uint8_t reserved2;
    rt_be16_t pad;
});

rt_packed(struct rt_scsi_write12
{
    rt_uint8_t opcode;
    rt_uint8_t config;      /* 7-5 WRPROTECT, 4 DPO, 3 FUA, 2 Reserved, 1 Obsolete, 0 Obsolete */
    rt_be32_t lba;
    rt_be32_t size;
    rt_uint8_t reserved;
    rt_uint8_t control;
});

rt_packed(struct rt_scsi_write16
{
    rt_uint8_t opcode;
    rt_uint8_t config;      /* 7-5 WRPROTECT, 4 DPO, 3 FUA, 2 Reserved, 1 Obsolete, 0 DLD2 */
    rt_be64_t lba;
    rt_be32_t size;
    rt_uint8_t reserved;
    rt_uint8_t control;
});

rt_packed(struct rt_scsi_synchronize_cache10
{
    rt_uint8_t opcode;
    rt_uint8_t config;      /* 7-3 Reserved, 2 Obsolete, 1 IMMED, 0 Obsolete */
    rt_be32_t lba;
    rt_uint8_t reserved;
    rt_be16_t size;
    rt_uint8_t control;
});

rt_packed(struct rt_scsi_synchronize_cache16
{
    rt_uint8_t opcode;
    rt_uint8_t config;      /* 7-3 Reserved, 2 Obsolete, 1 IMMED, 0 Obsolete */
    rt_be64_t lba;
    rt_be32_t size;
    rt_uint8_t reserved;
    rt_uint8_t control;
});

#define RT_SCSI_UNMAP_SHIFT     3

rt_packed(struct rt_scsi_write_same10
{
    rt_uint8_t opcode;
    rt_uint8_t config;      /* 7-5 WRPROTECT, 4 ANCHOR, 3 UNMAP, 2 Obsolete, 1 Obsolete, 0 Obsolete */
    rt_be32_t lba;
    rt_uint8_t reserved;
    rt_be16_t size;
    rt_uint8_t control;
});

rt_packed(struct rt_scsi_write_same16
{
    rt_uint8_t opcode;
    rt_uint8_t config;      /* 7-5 WRPROTECT, 4 ANCHOR, 3 UNMAP, 2 Obsolete, 1 Obsolete, 0 NDOB */
    rt_be64_t lba;
    rt_be32_t size;
    rt_uint8_t reserved;
    rt_uint8_t control;
});

#define RT_SCSI_PF_SHIFT        4
#define RT_SCSI_RTD_SHIFT       1
#define RT_SCSI_SP_SHIFT        0

rt_packed(struct rt_scsi_mode_select6
{
    rt_uint8_t opcode;
    rt_uint8_t config;      /* 7-5 Reserved, 4 PF, 3-2 Reserved, 1 RTD, 0 SP */
    rt_uint8_t reserved[2];
    rt_uint8_t param_list_len;
    rt_uint8_t control;
});

rt_packed(struct rt_scsi_mode_select10
{
    rt_uint8_t opcode;
    rt_uint8_t config;      /* 7-5 Reserved, 4 PF, 3-1 Reserved, 0 SP */
    rt_uint8_t reserved[5];
    rt_be16_t param_list_len;
    rt_uint8_t control;
});

struct rt_scsi_mode_select_data
{
    rt_uint32_t length;
    rt_uint16_t block_descriptor_length;
    rt_uint8_t medium_type;
    rt_uint8_t device_specific;
    rt_uint8_t header_length;
    rt_uint8_t longlba:1;
};

#define RT_SCSI_DBD_SHIFT       3
#define RT_SCSI_LLBAA_SHIFT     4
#define RT_SCSI_PC_SHIFT        6
#define RT_SCSI_PAGE_CODE_SHIFT 0

rt_packed(struct rt_scsi_mode_sense6
{
    rt_uint8_t opcode;
    rt_uint8_t config;      /* 7-4 Reserved, 3 DBD, 2-0 Reserved */
    rt_uint8_t page_control_code;
    rt_uint8_t subpage_code;
    rt_uint8_t allocation_len;
    rt_uint8_t control;
});

rt_packed(struct rt_scsi_mode_sense10
{
    rt_uint8_t opcode;
    rt_uint8_t config;      /* 7-5 Reserved, 4 LLBAA, 3 DBD, 2-0 Reserved */
    rt_uint8_t page_control_code;
    rt_uint8_t subpage_code;
    rt_uint8_t reserved[3];
    rt_be16_t allocation_len;
    rt_uint8_t control;
});

#define RT_SCSI_CMD_TEST_UNIT_READY     0x00
#define RT_SCSI_CMD_REQUEST_SENSE       0x03
#define RT_SCSI_CMD_INQUIRY             0x12
#define RT_SCSI_CMD_MODE_SELECT         0x15
#define RT_SCSI_CMD_MODE_SENSE          0x1a
#define RT_SCSI_CMD_READ_CAPACITY10     0x25
#define RT_SCSI_CMD_READ10              0x28
#define RT_SCSI_CMD_WRITE10             0x2a
#define RT_SCSI_CMD_SYNCHRONIZE_CACHE10 0x35
#define RT_SCSI_CMD_WRITE_SAME10        0x41
#define RT_SCSI_CMD_MODE_SELECT10       0x55
#define RT_SCSI_CMD_MODE_SENSE10        0x5a
#define RT_SCSI_CMD_READ16              0x88
#define RT_SCSI_CMD_WRITE16             0x8a
#define RT_SCSI_CMD_SYNCHRONIZE_CACHE16 0x91
#define RT_SCSI_CMD_WRITE_SAME16        0x93
#define RT_SCSI_CMD_READ_CAPACITY16     0x9e
#define RT_SCSI_CMD_READ12              0xa8
#define RT_SCSI_CMD_WRITE12             0xaa

struct rt_scsi_cmd
{
    union
    {
        struct rt_scsi_unknow unknow;
        struct rt_scsi_test_unit_ready test_unit_ready;
        struct rt_scsi_inquiry inquiry;
        struct rt_scsi_request_sense request_sense;
        struct rt_scsi_read_capacity10 read_capacity10;
        struct rt_scsi_read_capacity16 read_capacity16;
        struct rt_scsi_read10 read10;
        struct rt_scsi_read12 read12;
        struct rt_scsi_read16 read16;
        struct rt_scsi_write10 write10;
        struct rt_scsi_write12 write12;
        struct rt_scsi_write16 write16;
        struct rt_scsi_synchronize_cache10 synchronize_cache10;
        struct rt_scsi_synchronize_cache16 synchronize_cache16;
        struct rt_scsi_write_same10 write_same10;
        struct rt_scsi_write_same16 write_same16;
        struct rt_scsi_mode_select6 mode_select6;
        struct rt_scsi_mode_select10 mode_select10;
        struct rt_scsi_mode_sense6 mode_sense6;
        struct rt_scsi_mode_sense10 mode_sense10;
    } op;
    rt_size_t op_size;

    union
    {
        struct
        {
            struct rt_scsi_inquiry_data inquiry;
            struct rt_scsi_request_sense_data request_sense;
            struct rt_scsi_read_capacity10_data read_capacity10;
            struct rt_scsi_read_capacity16_data read_capacity16;
        };
        struct
        {
            void *ptr;
            rt_size_t size;
        };
    } data;
};

enum
{
    SCSI_DEVICE_TYPE_DIRECT                     = 0x00, /* DiskPeripheral (GenDisk) */
    SCSI_DEVICE_TYPE_SEQUENTIAL                 = 0x01, /* TapePeripheral */
    SCSI_DEVICE_TYPE_PRINTER                    = 0x02, /* PrinterPeripheral (GenPrinter) */
    SCSI_DEVICE_TYPE_PROCESSOR                  = 0x03, /* OtherPeripheral */
    SCSI_DEVICE_TYPE_WRITE_ONCE_READ_MULTIPLE   = 0x04, /* WormPeripheral (GenWorm) */
    SCSI_DEVICE_TYPE_CDROM                      = 0x05, /* CdRomPeripheral (GenCdRom) */
    SCSI_DEVICE_TYPE_SCANNER                    = 0x06, /* ScannerPeripheral (GenScanner) */
    SCSI_DEVICE_TYPE_OPTICAL                    = 0x07, /* OpticalDiskPeripheral (GenOptical) */
    SCSI_DEVICE_TYPE_MEDIUM_CHANGER             = 0x08, /* MediumChangerPeripheral (ScsiChanger) */
    SCSI_DEVICE_TYPE_COMMUNICATION              = 0x09, /* CommunicationsPeripheral (ScsiNet) */
    SCSI_DEVICE_TYPE_ASC_PREPRESS_GRAPHICS10    = 0x0a, /* ASCPrePressGraphicsPeripheral (ScsiASCIT8) */
    SCSI_DEVICE_TYPE_ASC_PREPRESS_GRAPHICS11    = 0x0b, /* ASCPrePressGraphicsPeripheral (ScsiASCIT8) */
    SCSI_DEVICE_TYPE_ARRAY                      = 0x0c, /* ArrayPeripheral (ScsiArray) */
    SCSI_DEVICE_TYPE_ENCLOSURE                  = 0x0d, /* EnclosurePeripheral (ScsiEnclosure) */
    SCSI_DEVICE_TYPE_RBC                        = 0x0e, /* RBCPeripheral (ScsiRBC) */
    SCSI_DEVICE_TYPE_CARDREADER                 = 0x0f, /* CardReaderPeripheral (ScsiCardReader) */
    SCSI_DEVICE_TYPE_BRIDGE                     = 0x10, /* BridgePeripheral (ScsiBridge) */
    SCSI_DEVICE_TYPE_OTHER                      = 0x11, /* OtherPeripheral (ScsiOther) */
    SCSI_DEVICE_TYPE_MAX,
};

struct rt_scsi_ops;

struct rt_scsi_host
{
    struct rt_device *dev;

    const struct rt_scsi_ops *ops;

    rt_size_t max_id;
    rt_size_t max_lun;

    rt_list_t lun_nodes;
};

struct rt_scsi_device
{
    struct rt_scsi_host *host;

    rt_list_t list;

    rt_size_t id;
    rt_size_t lun;
    rt_uint32_t devtype;
    rt_uint32_t removable;
    rt_size_t last_block;
    rt_size_t block_size;

    void *priv;
};

struct rt_scsi_ops
{
    rt_err_t (*reset)(struct rt_scsi_device *sdev);
    rt_err_t (*transfer)(struct rt_scsi_device *sdev, struct rt_scsi_cmd *cmd);
};

rt_err_t rt_scsi_host_register(struct rt_scsi_host *scsi);
rt_err_t rt_scsi_host_unregister(struct rt_scsi_host *scsi);

rt_inline rt_bool_t rt_scsi_cmd_is_write(struct rt_scsi_cmd *cmd)
{
    return cmd->op.write10.opcode == RT_SCSI_CMD_WRITE10 ||
            cmd->op.write12.opcode == RT_SCSI_CMD_WRITE16 ||
            cmd->op.write16.opcode == RT_SCSI_CMD_WRITE12;
}

rt_err_t rt_scsi_request_sense(struct rt_scsi_device *sdev,
        struct rt_scsi_request_sense_data *out_data);

rt_err_t rt_scsi_test_unit_ready(struct rt_scsi_device *sdev);
rt_err_t rt_scsi_inquiry(struct rt_scsi_device *sdev,
        struct rt_scsi_inquiry_data *out_data);

rt_err_t rt_scsi_read_capacity10(struct rt_scsi_device *sdev,
        struct rt_scsi_read_capacity10_data *out_data);
rt_err_t rt_scsi_read_capacity16(struct rt_scsi_device *sdev,
        struct rt_scsi_read_capacity16_data *out_data);

rt_err_t rt_scsi_read10(struct rt_scsi_device *sdev,
        rt_off_t lba, void *buffer, rt_size_t size);
rt_err_t rt_scsi_read12(struct rt_scsi_device *sdev,
        rt_off_t lba, void *buffer, rt_size_t size);
rt_err_t rt_scsi_read16(struct rt_scsi_device *sdev,
        rt_off_t lba, void *buffer, rt_size_t size);

rt_err_t rt_scsi_write10(struct rt_scsi_device *sdev,
        rt_off_t lba, const void *buffer, rt_size_t size);
rt_err_t rt_scsi_write12(struct rt_scsi_device *sdev,
        rt_off_t lba, const void *buffer, rt_size_t size);
rt_err_t rt_scsi_write16(struct rt_scsi_device *sdev,
        rt_off_t lba, const void *buffer, rt_size_t size);

rt_err_t rt_scsi_synchronize_cache10(struct rt_scsi_device *sdev,
        rt_off_t lba, rt_size_t size);
rt_err_t rt_scsi_synchronize_cache16(struct rt_scsi_device *sdev,
        rt_off_t lba, rt_size_t size);

rt_err_t rt_scsi_write_same10(struct rt_scsi_device *sdev,
        rt_off_t lba, rt_size_t size);
rt_err_t rt_scsi_write_same16(struct rt_scsi_device *sdev,
        rt_off_t lba, rt_size_t size);

rt_err_t rt_scsi_mode_select6(struct rt_scsi_device *sdev,
        rt_uint8_t pf, rt_uint8_t sp, void *buffer, rt_size_t size,
        struct rt_scsi_mode_select_data *data);
rt_err_t rt_scsi_mode_select10(struct rt_scsi_device *sdev,
        rt_uint8_t pf, rt_uint8_t sp, void *buffer, rt_size_t size,
        struct rt_scsi_mode_select_data *data);

rt_err_t rt_scsi_mode_sense6(struct rt_scsi_device *sdev,
        rt_uint8_t dbd, rt_uint8_t modepage, rt_uint8_t subpage, void *buffer, rt_size_t size,
        struct rt_scsi_mode_select_data *data);
rt_err_t rt_scsi_mode_sense10(struct rt_scsi_device *sdev,
        rt_uint8_t dbd, rt_uint8_t modepage, rt_uint8_t subpage, void *buffer, rt_size_t size,
        struct rt_scsi_mode_select_data *data);

#endif /* __SCSI_H__ */
