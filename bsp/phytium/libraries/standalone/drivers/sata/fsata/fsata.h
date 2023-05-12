/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: fsata.h
 * Date: 2022-02-10 14:55:11
 * LastEditTime: 2022-02-18 09:05:24
 * Description:  This file is for sata ctrl function definition
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   wangxiaodong  2022/2/10    first release
 * 1.1   wangxiaodong  2022/9/9     improve functions
 * 1.2   wangxiaodong  2022/10/21   improve functions
 */

#ifndef FSATA_H
#define FSATA_H

#include "ftypes.h"
#include "ferror_code.h"
#include "fkernel.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define FSATA_SUCCESS               FT_SUCCESS
#define FSATA_ERR_INVAILD_PARAMETER FT_MAKE_ERRCODE(ErrModBsp, ErrBspSata, 1)
#define FSATA_ERR_TIMEOUT           FT_MAKE_ERRCODE(ErrModBsp, ErrBspSata, 2)
#define FSATA_ERR_OPERATION         FT_MAKE_ERRCODE(ErrModBsp, ErrBspSata, 3)
#define FSATA_UNKNOWN_DEVICE        FT_MAKE_ERRCODE(ErrModBsp, ErrBspSata, 4)

/************************** Constant Definitions *****************************/
#define FSATA_AHCI_MAX_PORTS        32
#define FSATA_AHCI_MAX_PRD_ENTRIES  16

#define MAX_DATA_BYTE_COUNT     SZ_4M

#define FSATA_AHCI_CMD_LIST_HEADER_SIZE 0x20
#define FSATA_AHCI_CMD_LIST_HEADER_NUM  32
#define FSATA_AHCI_RX_FIS_SZ            0x100
#define FSATA_AHCI_CMD_TABLE_HEADER_SIZE    0x80
#define FSATA_AHCI_PRTD_ITEM_SIZE       0x10
#define FSATA_AHCI_PRTD_ITEM_NUM        0x40 /*set 64 item, hardware max is 64K */

#define FSATA_AHCI_CMD_TABLE_SIZE       (FSATA_AHCI_CMD_TABLE_HEADER_SIZE + (FSATA_AHCI_PRTD_ITEM_NUM * FSATA_AHCI_PRTD_ITEM_SIZE))
#define FSATA_AHCI_PORT_PRIV_DMA_SZ     (FSATA_AHCI_CMD_LIST_HEADER_SIZE * FSATA_AHCI_CMD_LIST_HEADER_NUM + \
        FSATA_AHCI_CMD_TABLE_SIZE + FSATA_AHCI_RX_FIS_SZ)

#define FSATA_AHCI_CMD_ATAPI        BIT(5)
#define FSATA_AHCI_CMD_WRITE        BIT(6)
#define FSATA_AHCI_CMD_PREFETCH     BIT(7)
#define FSATA_AHCI_CMD_RESET        BIT(8)
#define FSATA_AHCI_CMD_CLR_BUSY     BIT(10)

#define FSATA_ID_LBA48_SECTORS  100
#define FSATA_ID_LBA_SECTORS    60

#define FSATA_ID_ATA_DEVICE BIT(15) /* IDENTIFY DEVICE word 0, if ATA device  */
#define FSATA_ID_COMPLETE   BIT(2) /* IDENTIFY DEVICE word 0, if the content of the IDENTIFY DEVICE data is incomplete  */

#define FSATA_ID_FW_REV 23  /* firmware revision position */
#define FSATA_ID_PROD   27  /* Model number position */
#define FSATA_ID_WORDS  256 /* IDENTIFY DEVICE data length */

enum
{
    FSATA_FIS_REG_HOST_TO_DEVICE = 0x27,
    FSATA_FIS_REG_DEVICE_TO_HOST = 0x34,
    FSATA_FIS_DMA_SETUP = 0x41
};

#define FSATA_FIS_REG_HOST_TO_DEVICE_C  BIT(7)  /* update of the command register */
#define FSATA_CMD_EXT_DEVICE            BIT(6)  /* command device byte requirement */

enum
{
    FSATA_CMD_READ_EXT  = 0x25,
    FSATA_CMD_WRITE_EXT = 0x35,
    FSATA_CMD_IDENTIFY_DEVICE = 0xEC,
    FSATA_CMD_FPDMA_READ    = 0x60,
    FSATA_CMD_FPDMA_WRITE   = 0x61
};

#define FSATA_BUSY              BIT(7)  /* BSY status bit */

#define FSATA_SECT_SIZE         512     /* sata sector size */

#define FSATA_BLK_VEN_SIZE      40      /* device vendor string size */
#define FSATA_BLK_PRD_SIZE      20      /* device product number size */
#define FSATA_BLK_REV_SIZE      8       /* firmware revision size */

#define FSATA_DEV_TYPE_UNKNOWN  0xff    /* not connected */
#define FSATA_DEV_TYPE_HARDDISK 0x00    /* harddisk */

#define FSATA_IF_TYPE_UNKNOWN   0xff
#define FSATA_IF_TYPE_SCSI      0x00

enum
{
    FSATA_TYPE_PCIE = 0,
    FSATA_TYPE_CONTROLLER = 1
};

/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/

/* Number of User Addressable Logical Sectors lba28 */
#define FSATA_ID_U32(id,n)  \
    (((u32) (id)[(n) + 1] << 16) | ((u32) (id)[(n)]))

/* Number of User Addressable Logical Sectors lba48 */
#define FSATA_ID_U64(id,n)  \
    ( ((u64) (id)[(n) + 3] << 48) | \
      ((u64) (id)[(n) + 2] << 32) | \
      ((u64) (id)[(n) + 1] << 16) | \
      ((u64) (id)[(n) + 0]) )

/* if sata id is support lba */
#define FSataIdHasLba(id)       ((id)[49] & BIT(9))

/* if sata id is support lba48 */
static inline int FSataIdHasLba48(const u16 *id)
{
    if ((id[83] & 0xC000) != 0x4000)
    {
        return 0;
    }
    if (!FSATA_ID_U64(id, 100))
    {
        return 0;
    }
    return id[83] & BIT(10);
}

/**************************** Type Definitions *******************************/
typedef void (*FSataIrqCallBack)(void *args);

/* sata info */
typedef struct
{
    unsigned char if_type;                 /* type of the interface */
    unsigned char type;                    /* device type */
    char vendor[FSATA_BLK_VEN_SIZE + 1];   /* device vendor string */
    char product[FSATA_BLK_PRD_SIZE + 1];  /* device product number */
    char revision[FSATA_BLK_REV_SIZE + 1]; /* firmware revision */
    unsigned long lba;                     /* number of blocks */
    unsigned long lba512;                  /* number of blocks of 512 bytes */
    unsigned long blksz;                   /* block size */
} FSataInfo;

/* Received FIS Structure */
typedef struct __attribute__((__packed__))
{
    u8 dma_setup_fis[28];
    u8 reserved0[4];
    u8 pio_setup_fis[20];
    u8 reserved1[12];
    u8 d2h_register_fis[20];
    u8 reserved2[4];
    u8 set_device_bits_fis[8];
    u8 unknown_fis[64];
    u8 reserved3[96];
}
FSataAhciRecvFis;

/* command list structure - command header */
typedef struct
{
    u32 description_info;/* DW 0 – Description Information */
    u32 status; /* DW 1 - Command Status */
    u32 tbl_addr; /* DW 2 – Command Table Base Address */
    u32 tbl_addr_hi; /* DW 3 – Command Table Base Address Upper */
    u32 reserved[4];
} FSataAhciCommandList;

/* command table - PRDT */
typedef struct
{
    u32 addr_low; /* DW 0 – Data Base Address */
    u32 addr_high; /* DW 1 – Data Base Address Upper */
    u32 reserved; /* DW 2 – Reserved */
    u32 data_byte; /* DW 3 – Description Information */
} FSataAhciCommandTablePrdt;

/* ahci port information structure */
typedef struct
{
    uintptr port_base_addr; /* port base address */
    FSataAhciCommandList *cmd_list; /*  Command List structure, will include cmd_tbl's address */
    FSataAhciRecvFis *rx_fis;   /* Received FIS Structure */
    uintptr cmd_tbl_base_addr; /* command table addr, also the command table's first part */
    FSataAhciCommandTablePrdt *cmd_tbl_prdt;/* command table's second part , cmd_tbl + cmd_tbl_prdt = command table*/
    FSataInfo dev_info;
} FSataAhciPorts;

typedef struct
{
    u32 instance_id; /* Device instance id */
    uintptr base_addr; /* sata base address */
    char *instance_name; /* instance name */
    u32 irq_num;     /* Irq number */
} FSataConfig; /* sata config */

typedef struct
{
    FSataConfig config;
    u32 is_ready;

    FSataAhciPorts port[FSATA_AHCI_MAX_PORTS];
    u16 *ataid[FSATA_AHCI_MAX_PORTS];
    u32 n_ports;    /* maximum number of ports supported by the ahci, Number of Ports (NP)*/
    u32 port_map;   /* each bit indicate port can be used, If a bit is set to ‘1’, the corresponding port is available for software to use. */
    u32 link_port_map; /* each bit indicate port linkup sata device */
    u32 private_data;  /* each bit indicate port sata achi started */

    FSataIrqCallBack fsata_dhrs_cb; /* device-to-host register fis interrupt */
    void *dhrs_args;
    FSataIrqCallBack fsata_pss_cb; /* pio setup fis interrupt */
    void *pss_args;
    FSataIrqCallBack fsata_dss_cb; /* dma setup fis interrupt */
    void *dss_args;
    FSataIrqCallBack fsata_sdbs_cb; /* set device bits interrupt */
    void *sdbs_args;
    FSataIrqCallBack fsata_pcs_cb; /* port connect change status interrupt */
    void *pcs_args;

    volatile u8 dhrs_flag;
    volatile u8 sdb_flag;
} FSataCtrl;


/************************** Function Prototypes ******************************/

/* sata config init */
const FSataConfig *FSataLookupConfig(u32 instance_id, u8 type);

/* initialize sata ctrl */
FError FSataCfgInitialize(FSataCtrl *instance_p, const FSataConfig *input_config_p);

/* deinitialize sata ctrl */
void FSataCfgDeInitialize(FSataCtrl *pctrl);

/* read sata info */
FError FSataAhciReadInfo(FSataCtrl *instance_p, u8 port);

/* init ahci */
FError FSataAhciInit(FSataCtrl *instance_p);

/* init ahci port */
FError FSataAhciPortStart(FSataCtrl *instance_p, u8 port, uintptr mem);

/* read or write sata data */
FError FSataReadWrite(FSataCtrl *instance_p, u8 port, u32 start,
                      u16 blk_cnt, u8 *buffer, boolean is_ncq, boolean is_write);

/* sata all irq handler entry */
void FSataIrqHandler(s32 vector, void *param);

/* set specific sata irq function entry */
FError FSataSetHandler(FSataCtrl *instance_p, u32 handler_type,
                       void *func_pointer, void *call_back_ref);

/* set sata irq mask */
void FSataIrqEnable(FSataCtrl *instance_p, u32 int_mask);

#ifdef __cplusplus
}
#endif

#endif