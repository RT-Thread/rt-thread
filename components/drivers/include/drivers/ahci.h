/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#ifndef __AHCI_H__
#define __AHCI_H__

#include <rthw.h>
#include <rtthread.h>
#include <drivers/scsi.h>
#include <drivers/misc.h>

struct rt_ahci_ops;

/* Generic Host Control */
#define RT_AHCI_HBA_CAP                     0x00    /* Host capability*/
#define   RT_AHCI_CAP_NP                    RT_GENMASK(4, 0)    /* Number of Ports */
#define   RT_AHCI_CAP_NCS                   RT_GENMASK(8, 12)   /* Number of Command Slots */
#define   RT_AHCI_CAP_PSC                   RT_BIT(13)          /* Partial State Capable */
#define   RT_AHCI_CAP_SSC                   RT_BIT(14)          /* Slumber capable */
#define   RT_AHCI_CAP_PMD                   RT_BIT(15)          /* PIO Multiple DRQ Block */
#define   RT_AHCI_CAP_SPM                   RT_BIT(17)          /* Port Multiplier */
#define   RT_AHCI_CAP_AHCI                  RT_BIT(18)          /* AHCI only */
#define   RT_AHCI_CAP_SNZO                  RT_BIT(19)          /* Non-Zero DMA Offsets */
#define   RT_AHCI_CAP_ISS                   RT_GENMASK(23, 20)  /* Interface Speed Support */
#define   RT_AHCI_CAP_CLO                   RT_BIT(24)          /* Command List Override support */
#define   RT_AHCI_CAP_SAL                   RT_BIT(25)          /* Activity LED */
#define   RT_AHCI_CAP_SALP                  RT_BIT(26)          /* Aggressive Link Power Management */
#define   RT_AHCI_CAP_SSS                   RT_BIT(27)          /* Staggered Spin-up */
#define   RT_AHCI_CAP_SIS                   RT_BIT(28)          /* Interlock Switch */
#define   RT_AHCI_CAP_NCQ                   RT_BIT(30)          /* Native Command Queueing */
#define   RT_AHCI_CAP_64                    RT_BIT(31)          /* PCI DAC (64-bit DMA) support */
#define RT_AHCI_HBA_GHC                     0x04    /* Global host control */
#define   RT_AHCI_GHC_RESET                 RT_BIT(0)           /* Reset controller; self-clear */
#define   RT_AHCI_GHC_IRQ_EN                RT_BIT(1)           /* Global IRQ enable */
#define   RT_AHCI_GHC_AHCI_EN               RT_BIT(31)          /* AHCI enabled */
#define RT_AHCI_HBA_INTS                    0x08    /* Interrupt status */
#define RT_AHCI_HBA_PI                      0x0c    /* Port implemented */
#define RT_AHCI_HBA_VS                      0x10    /* Version */
#define RT_AHCI_HBA_CCC_CTL                 0x14    /* Command completion coalescing control */
#define RT_AHCI_HBA_CCC_PTS                 0x18    /* Command completion coalescing ports */
#define RT_AHCI_HBA_EM_LOC                  0x1c    /* Enclosure management location */
#define RT_AHCI_HBA_EM_CTL                  0x20    /* Enclosure management control */
#define RT_AHCI_HBA_CAP2                    0x24    /* Host capabilities extended */
#define RT_AHCI_HBA_BOHC                    0x28    /* BIOS/OS handoff control and status */
#define RT_AHCI_HBA_VENDOR                  0xa0    /* Vendor specific registers (0xa0 - 0xff) */

#define RT_AHCI_PORT_CLB                    0x00    /* Command list base address, 1K-byte aligned */
#define RT_AHCI_PORT_CLBU                   0x04    /* Command list base address upper 32 bits */
#define RT_AHCI_PORT_FB                     0x08    /* FIS base address, 256-byte aligned */
#define RT_AHCI_PORT_FBU                    0x0C    /* FIS base address upper 32 bits */
#define RT_AHCI_PORT_INTS                   0x10    /* Interrupt status */
#define RT_AHCI_PORT_INTE                   0x14    /* Interrupt enable */
#define   RT_AHCI_PORT_INTE_D2H_REG_FIS     RT_BIT(0)           /* D2H Register FIS rx'd */
#define   RT_AHCI_PORT_INTE_PIOS_FIS        RT_BIT(1)           /* PIO Setup FIS rx'd */
#define   RT_AHCI_PORT_INTE_DMAS_FIS        RT_BIT(2)           /* DMA Setup FIS rx'd */
#define   RT_AHCI_PORT_INTE_SDB_FIS         RT_BIT(3)           /* Set Device Bits FIS rx'd */
#define   RT_AHCI_PORT_INTE_UNK_FIS         RT_BIT(4)           /* Unknown FIS rx'd */
#define   RT_AHCI_PORT_INTE_SG_DONE         RT_BIT(5)           /* Descriptor processed */
#define   RT_AHCI_PORT_INTE_CONNECT         RT_BIT(6)           /* Port connect change status */
#define   RT_AHCI_PORT_INTE_DMPS            RT_BIT(7)           /* Mechanical presence status */
#define   RT_AHCI_PORT_INTE_PHYRDY          RT_BIT(22)          /* PhyRdy changed */
#define   RT_AHCI_PORT_INTE_BAD_PMP         RT_BIT(23)          /* Incorrect port multiplier */
#define   RT_AHCI_PORT_INTE_OVERFLOW        RT_BIT(24)          /* Xfer exhausted available S/G */
#define   RT_AHCI_PORT_INTE_IF_NONFATAL     RT_BIT(26)          /* Interface non-fatal error */
#define   RT_AHCI_PORT_INTE_IF_ERR          RT_BIT(27)          /* Interface fatal error */
#define   RT_AHCI_PORT_INTE_HBUS_DATA_ERR   RT_BIT(28)          /* Host bus data error */
#define   RT_AHCI_PORT_INTE_HBUS_ERR        RT_BIT(29)          /* Host bus fatal error */
#define   RT_AHCI_PORT_INTE_TF_ERR          RT_BIT(30)          /* Task file error */
#define   RT_AHCI_PORT_INTE_COLD_PRES       RT_BIT(31)          /* Cold presence detect */
#define RT_AHCI_PORT_CMD                    0x18    /* Command and status */
#define   RT_AHCI_PORT_CMD_START            RT_BIT(0)           /* Enable port DMA engine */
#define   RT_AHCI_PORT_CMD_SPIN_UP          RT_BIT(1)           /* Spin up device */
#define   RT_AHCI_PORT_CMD_POWER_ON         RT_BIT(2)           /* Power up device */
#define   RT_AHCI_PORT_CMD_CLO              RT_BIT(3)           /* Command list override */
#define   RT_AHCI_PORT_CMD_FIS_RX           RT_BIT(4)           /* Enable FIS receive DMA engine */
#define   RT_AHCI_PORT_CMD_FIS_ON           RT_BIT(14)          /* FIS DMA engine running */
#define   RT_AHCI_PORT_CMD_LIST_ON          RT_BIT(15)          /* cmd list DMA engine running */
#define   RT_AHCI_PORT_CMD_ATAPI            RT_BIT(24)          /* Device is ATAPI */
#define   RT_AHCI_PORT_CMD_ACTIVE           RT_BIT(28)          /* Active state */
#define RT_AHCI_PORT_TFD                    0x20    /* Task file data */
#define   RT_AHCI_PORT_TFDATA_ERR           RT_BIT(0)           /* Indicates an error during the transfer */
#define   RT_AHCI_PORT_TFDATA_DRQ           RT_BIT(3)           /* Indicates a data transfer is requested */
#define   RT_AHCI_PORT_TFDATA_BSY           RT_BIT(7)           /* Indicates the interface is busy */
#define RT_AHCI_PORT_SIG                    0x24    /* Signature */
#define   RT_AHCI_PORT_SIG_REG_MASK         0xff
#define   RT_AHCI_PORT_SIG_SECTOR_NR_SHIFT  0       /* Sector Count Register */
#define   RT_AHCI_PORT_SIG_LBA_LOW_SHIFT    8       /* LBA Low Register */
#define   RT_AHCI_PORT_SIG_LBA_MID_SHIFT    16      /* LBA Mid Register */
#define   RT_AHCI_PORT_SIG_LBA_HIGH_SHIFT   24      /* LBA High Register */
#define RT_AHCI_PORT_SIG_SATA_CDROM         0xeb140101
#define RT_AHCI_PORT_SIG_SATA_DISK          0x00000101
#define RT_AHCI_PORT_SSTS                   0x28    /* SATA status (SCR0:SStatus) */
#define   RT_AHCI_PORT_SSTS_DET_MASK        0x3
#define   RT_AHCI_PORT_SSTS_DET_COMINIT     0x1
#define   RT_AHCI_PORT_SSTS_DET_PHYRDY      0x3
#define RT_AHCI_PORT_SCTL                   0x2c    /* SATA control (SCR2:SControl) */
#define RT_AHCI_PORT_SERR                   0x30    /* SATA error (SCR1:SError) */
#define   RT_AHCI_PORT_SERR_ERR_I           RT_BIT(0)           /* Recovered Data Integrity Error */
#define   RT_AHCI_PORT_SERR_ERR_M           RT_BIT(1)           /* Recovered Communications Error */
#define   RT_AHCI_PORT_SERR_ERR_T           RT_BIT(8)           /* Transient Data Integrity Error */
#define   RT_AHCI_PORT_SERR_ERR_C           RT_BIT(9)           /* Persistent Communication or Data Integrity Error */
#define   RT_AHCI_PORT_SERR_ERR_P           RT_BIT(10)          /* Protocol Error */
#define   RT_AHCI_PORT_SERR_ERR_E           RT_BIT(11)          /* Internal Error */
#define   RT_AHCI_PORT_SERR_DIAG_N          RT_BIT(16)          /* PhyRdy Change */
#define   RT_AHCI_PORT_SERR_DIAG_I          RT_BIT(17)          /* Phy Internal Error */
#define   RT_AHCI_PORT_SERR_DIAG_W          RT_BIT(18)          /* Comm Wake */
#define   RT_AHCI_PORT_SERR_DIAG_B          RT_BIT(19)          /* 10B to 8B Decode Error */
#define   RT_AHCI_PORT_SERR_DIAG_D          RT_BIT(20)          /* Disparity Error */
#define   RT_AHCI_PORT_SERR_DIAG_C          RT_BIT(21)          /* CRC Error */
#define   RT_AHCI_PORT_SERR_DIAG_H          RT_BIT(22)          /* Handshake Error */
#define   RT_AHCI_PORT_SERR_DIAG_S          RT_BIT(23)          /* Link Sequence Error */
#define   RT_AHCI_PORT_SERR_DIAG_T          RT_BIT(24)          /* Transport state transition error */
#define   RT_AHCI_PORT_SERR_DIAG_F          RT_BIT(25)          /* Unknown FIS Type */
#define   RT_AHCI_PORT_SERR_DIAG_X          RT_BIT(26)          /* Exchanged */
#define RT_AHCI_PORT_SACT                   0x34    /* SATA active (SCR3:SActive) */
#define RT_AHCI_PORT_CI                     0x38    /* Command issue */
#define RT_AHCI_PORT_SNTF                   0x3c    /* SATA notification (SCR4:SNotification) */
#define RT_AHCI_PORT_FBS                    0x40    /* FIS-based switch control */
#define RT_AHCI_PORT_VENDOR                 0x70    /* Vendor specific (0x70 - 0x7f) */

#define RT_AHCI_MAX_SG                      56
#define RT_AHCI_CMD_SLOT_SIZE               32
#define RT_AHCI_MAX_CMD_SLOT                32
#define RT_AHCI_RX_FIS_SIZE                 256
#define RT_AHCI_CMD_TBL_HDR                 0x80
#define RT_AHCI_CMD_TBL_CDB                 0x40
#define RT_AHCI_CMD_TBL_SIZE                RT_AHCI_CMD_TBL_HDR + (RT_AHCI_MAX_SG * 16)
#define RT_AHCI_DMA_SIZE                    (RT_AHCI_CMD_SLOT_SIZE * RT_AHCI_MAX_CMD_SLOT + RT_AHCI_CMD_TBL_SIZE + RT_AHCI_RX_FIS_SIZE)
#define RT_ACHI_PRDT_BYTES_MAX              (4 * 1024 * 1024)

#define RT_AHCI_FIS_TYPE_REG_H2D            0x27    /* Register FIS - host to device */
#define RT_AHCI_FIS_TYPE_REG_D2H            0x34    /* Register FIS - device to host */
#define RT_AHCI_FIS_TYPE_DMA_ACT            0x39    /* DMA activate FIS - device to host */
#define RT_AHCI_FIS_TYPE_DMA_SETUP          0x41    /* DMA setup FIS - bidirectional */
#define RT_AHCI_FIS_TYPE_DATA               0x46    /* Data FIS - bidirectional */
#define RT_AHCI_FIS_TYPE_BIST               0x58    /* BIST activate FIS - bidirectional */
#define RT_AHCI_FIS_TYPE_PIO_SETUP          0x5f    /* PIO setup FIS - device to host */
#define RT_AHCI_FIS_TYPE_DEV_BITS           0xa1    /* Set device bits FIS - device to host */

#define RT_AHCI_ATA_ID_WORDS                256
#define RT_AHCI_ATA_ID_CONFIG               0
#define RT_AHCI_ATA_ID_CYLS                 1
#define RT_AHCI_ATA_ID_HEADS                3
#define RT_AHCI_ATA_ID_SECTORS              6
#define RT_AHCI_ATA_ID_SERNO                10
#define RT_AHCI_ATA_ID_BUF_SIZE             21
#define RT_AHCI_ATA_ID_FW_REV               23
#define RT_AHCI_ATA_ID_PROD                 27
#define RT_AHCI_ATA_ID_MAX_MULTSECT         47
#define RT_AHCI_ATA_ID_DWORD_IO             48
#define RT_AHCI_ATA_ID_TRUSTED              48
#define RT_AHCI_ATA_ID_CAPABILITY           49
#define RT_AHCI_ATA_ID_OLD_PIO_MODES        51
#define RT_AHCI_ATA_ID_OLD_DMA_MODES        52
#define RT_AHCI_ATA_ID_FIELD_VALID          53
#define RT_AHCI_ATA_ID_CUR_CYLS             54
#define RT_AHCI_ATA_ID_CUR_HEADS            55
#define RT_AHCI_ATA_ID_CUR_SECTORS          56
#define RT_AHCI_ATA_ID_MULTSECT             59
#define RT_AHCI_ATA_ID_LBA_CAPACITY         60
#define RT_AHCI_ATA_ID_SWDMA_MODES          62
#define RT_AHCI_ATA_ID_MWDMA_MODES          63
#define RT_AHCI_ATA_ID_PIO_MODES            64
#define RT_AHCI_ATA_ID_EIDE_DMA_MIN         65
#define RT_AHCI_ATA_ID_EIDE_DMA_TIME        66
#define RT_AHCI_ATA_ID_EIDE_PIO             67
#define RT_AHCI_ATA_ID_EIDE_PIO_IORDY       68
#define RT_AHCI_ATA_ID_ADDITIONAL_SUPP      69
#define RT_AHCI_ATA_ID_QUEUE_DEPTH          75
#define RT_AHCI_ATA_ID_SATA_CAPABILITY      76
#define RT_AHCI_ATA_ID_SATA_CAPABILITY_2    77
#define RT_AHCI_ATA_ID_FEATURE_SUPP         78
#define RT_AHCI_ATA_ID_MAJOR_VER            80
#define RT_AHCI_ATA_ID_COMMAND_SET_1        82
#define RT_AHCI_ATA_ID_COMMAND_SET_2        83
#define RT_AHCI_ATA_ID_CFSSE                84
#define RT_AHCI_ATA_ID_CFS_ENABLE_1         85
#define RT_AHCI_ATA_ID_CFS_ENABLE_2         86
#define RT_AHCI_ATA_ID_CSF_DEFAULT          87
#define RT_AHCI_ATA_ID_UDMA_MODES           88
#define RT_AHCI_ATA_ID_HW_CONFIG            93
#define RT_AHCI_ATA_ID_SPG                  98
#define RT_AHCI_ATA_ID_LBA_CAPACITY_2       100
#define RT_AHCI_ATA_ID_SECTOR_SIZE          106
#define RT_AHCI_ATA_ID_WWN                  108
#define RT_AHCI_ATA_ID_LOGICAL_SECTOR_SIZE  117
#define RT_AHCI_ATA_ID_COMMAND_SET_3        119
#define RT_AHCI_ATA_ID_COMMAND_SET_4        120
#define RT_AHCI_ATA_ID_LAST_LUN             126
#define RT_AHCI_ATA_ID_DLF                  128
#define RT_AHCI_ATA_ID_CSFO                 129
#define RT_AHCI_ATA_ID_CFA_POWER            160
#define RT_AHCI_ATA_ID_CFA_KEY_MGMT         162
#define RT_AHCI_ATA_ID_CFA_MODES            163
#define RT_AHCI_ATA_ID_DATA_SET_MGMT        169
#define RT_AHCI_ATA_ID_SCT_CMD_XPORT        206
#define RT_AHCI_ATA_ID_ROT_SPEED            217
#define RT_AHCI_ATA_ID_PIO4                 (1 << 1)
#define RT_AHCI_ATA_ID_SERNO_LEN            20
#define RT_AHCI_ATA_ID_FW_REV_LEN           8
#define RT_AHCI_ATA_ID_PROD_LEN             40
#define RT_AHCI_ATA_ID_WWN_LEN              8

#define RT_AHCI_ATA_CMD_DSM                 0x06
#define RT_AHCI_ATA_CMD_DEV_RESET           0x08    /* ATAPI device reset */
#define RT_AHCI_ATA_CMD_PIO_READ            0x20    /* Read sectors with retry */
#define RT_AHCI_ATA_CMD_PIO_READ_EXT        0x24
#define RT_AHCI_ATA_CMD_READ_EXT            0x25
#define RT_AHCI_ATA_CMD_READ_NATIVE_MAX_EXT 0x27
#define RT_AHCI_ATA_CMD_READ_MULTI_EXT      0x29
#define RT_AHCI_ATA_CMD_READ_LOG_EXT        0x2f
#define RT_AHCI_ATA_CMD_PIO_WRITE           0x30    /* Write sectors with retry */
#define RT_AHCI_ATA_CMD_PIO_WRITE_EXT       0x34
#define RT_AHCI_ATA_CMD_WRITE_EXT           0x35
#define RT_AHCI_ATA_CMD_SET_MAX_EXT         0x37
#define RT_AHCI_ATA_CMD_WRITE_MULTI_EXT     0x39
#define RT_AHCI_ATA_CMD_WRITE_FUA_EXT       0x3d
#define RT_AHCI_ATA_CMD_VERIFY              0x40    /* Read verify sectors with retry */
#define RT_AHCI_ATA_CMD_VERIFY_EXT          0x42
#define RT_AHCI_ATA_CMD_FPDMA_READ          0x60
#define RT_AHCI_ATA_CMD_FPDMA_WRITE         0x61
#define RT_AHCI_ATA_CMD_EDD                 0x90    /* Execute device diagnostic */
#define RT_AHCI_ATA_CMD_INIT_DEV_PARAMS     0x91    /* Initialize device parameters */
#define RT_AHCI_ATA_CMD_PACKET              0xa0    /* ATAPI packet */
#define RT_AHCI_ATA_CMD_ID_ATAPI            0xa1    /* ATAPI identify device */
#define RT_AHCI_ATA_CMD_CONF_OVERLAY        0xb1
#define RT_AHCI_ATA_CMD_READ_MULTI          0xc4    /* Read multiple */
#define RT_AHCI_ATA_CMD_WRITE_MULTI         0xc5    /* Write multiple */
#define RT_AHCI_ATA_CMD_SET_MULTI           0xc6    /* Set multiple mode */
#define RT_AHCI_ATA_CMD_READ                0xc8    /* Read DMA with retry */
#define RT_AHCI_ATA_CMD_WRITE               0xca    /* Write DMA with retry */
#define RT_AHCI_ATA_CMD_WRITE_MULTI_FUA_EXT 0xce
#define RT_AHCI_ATA_CMD_STANDBYNOW1         0xe0    /* Standby immediate */
#define RT_AHCI_ATA_CMD_IDLEIMMEDIATE       0xe1    /* Idle immediate */
#define RT_AHCI_ATA_CMD_STANDBY             0xe2    /* Place in standby power mode */
#define RT_AHCI_ATA_CMD_IDLE                0xe3    /* Place in idle power mode */
#define RT_AHCI_ATA_CMD_PMP_READ            0xe4    /* Read buffer */
#define RT_AHCI_ATA_CMD_CHK_POWER           0xe5    /* Check power mode */
#define RT_AHCI_ATA_CMD_SLEEP               0xe6    /* Sleep */
#define RT_AHCI_ATA_CMD_FLUSH               0xe7
#define RT_AHCI_ATA_CMD_PMP_WRITE           0xe8    /* Write buffer */
#define RT_AHCI_ATA_CMD_FLUSH_EXT           0xea
#define RT_AHCI_ATA_CMD_ID_ATA              0xec    /* Identify device */
#define RT_AHCI_ATA_CMD_SET_FEATURES        0xef    /* Set features */
#define RT_AHCI_ATA_CMD_SEC_FREEZE_LOCK     0xf5    /* Security freeze */
#define RT_AHCI_ATA_CMD_READ_NATIVE_MAX     0xf8
#define RT_AHCI_ATA_CMD_SET_MAX             0xf9

#define RT_AHCI_ATA_DSM_TRIM                0x01

#define RT_AHCI_ATA_PROT_FLAG_PIO           RT_BIT(0)
#define RT_AHCI_ATA_PROT_FLAG_DMA           RT_BIT(1)
#define RT_AHCI_ATA_PROT_FLAG_NCQ           RT_BIT(2)
#define RT_AHCI_ATA_PROT_FLAG_ATAPI         RT_BIT(3)

#define rt_ahci_ata_id_is_ata(id)           (((id)[0] & (1 << 15)) == 0)
#define rt_ahci_ata_id_has_lba(id)          ((id)[49] & (1 << 9))
#define rt_ahci_ata_id_has_dma(id)          ((id)[49] & (1 << 8))
#define rt_ahci_ata_id_has_ncq(id)          ((id)[76] & (1 << 8))
#define rt_ahci_ata_id_queue_depth(id)      (((id)[75] & 0x1f) + 1)
#define rt_ahci_ata_id_removeable(id)       ((id)[0] & (1 << 7))
#define rt_ahci_ata_id_iordy_disable(id)    ((id)[49] & (1 << 10))
#define rt_ahci_ata_id_has_iordy(id)        ((id)[49] & (1 << 11))

#define rt_ahci_ata_id_u32(id, n)           (((rt_uint32_t)(id)[(n) + 1] << 16) | ((rt_uint32_t) (id)[(n)]))
#define rt_ahci_ata_id_u64(id, n)           (((rt_uint64_t)(id)[(n) + 3] << 48) | ((rt_uint64_t)(id)[(n) + 2] << 32) | \
                                            ((rt_uint64_t)(id)[(n) + 1] << 16) | ((rt_uint64_t)(id)[(n) + 0]) )

rt_inline rt_bool_t rt_ahci_ata_id_has_lba48(const rt_uint16_t *id)
{
    if ((id[RT_AHCI_ATA_ID_COMMAND_SET_2] & 0xc000) != 0x4000 ||
        !rt_ahci_ata_id_u64(id, RT_AHCI_ATA_ID_LBA_CAPACITY_2))
    {
        return 0;
    }

    return !!(id[RT_AHCI_ATA_ID_COMMAND_SET_2] & (1 << 10));
}

rt_inline rt_uint64_t rt_ahci_ata_id_n_sectors(rt_uint16_t *id)
{
    if (rt_ahci_ata_id_has_lba(id))
    {
        if (rt_ahci_ata_id_has_lba48(id))
        {
            return rt_ahci_ata_id_u64(id, RT_AHCI_ATA_ID_LBA_CAPACITY_2);
        }

        return rt_ahci_ata_id_u32(id, RT_AHCI_ATA_ID_LBA_CAPACITY);
    }

    return 0;
}

rt_inline rt_bool_t rt_ahci_ata_id_wcache_enabled(const rt_uint16_t *id)
{
    if ((id[RT_AHCI_ATA_ID_CSF_DEFAULT] & 0xc000) != 0x4000)
    {
        return RT_FALSE;
    }
    return id[RT_AHCI_ATA_ID_CFS_ENABLE_1] & (1 << 5);
}

rt_inline rt_bool_t rt_ahci_ata_id_has_flush(const rt_uint16_t *id)
{
    if ((id[RT_AHCI_ATA_ID_COMMAND_SET_2] & 0xc000) != 0x4000)
    {
        return RT_FALSE;
    }
    return id[RT_AHCI_ATA_ID_COMMAND_SET_2] & (1 << 12);
}

rt_inline rt_bool_t rt_ahci_ata_id_has_flush_ext(const rt_uint16_t *id)
{
    if ((id[RT_AHCI_ATA_ID_COMMAND_SET_2] & 0xc000) != 0x4000)
    {
        return RT_FALSE;
    }
    return id[RT_AHCI_ATA_ID_COMMAND_SET_2] & (1 << 13);
}

struct rt_ahci_cmd_hdr
{
    rt_uint32_t opts;
    rt_uint32_t status;
    rt_uint32_t tbl_addr_lo;
    rt_uint32_t tbl_addr_hi;
    rt_uint32_t reserved[4];
};

struct rt_ahci_sg
{
    rt_uint32_t addr_lo;
    rt_uint32_t addr_hi;
    rt_uint32_t reserved;
    rt_uint32_t flags_size;
};

struct rt_ahci_port
{
    void *regs;

    void *dma;
    rt_ubase_t dma_handle;

    struct rt_ahci_cmd_hdr *cmd_slot;
    struct rt_ahci_sg *cmd_tbl_sg;
    void *cmd_tbl;
    rt_ubase_t cmd_tbl_dma;
    void *rx_fis;

    rt_uint32_t int_enabled;
    rt_size_t block_size;

    rt_uint16_t *ataid;

    rt_bool_t link;
    struct rt_completion done;
};

struct rt_ahci_host
{
    struct rt_scsi_host parent;

    int irq;
    void *regs;

    rt_size_t ports_nr;
    rt_uint32_t ports_map;
    struct rt_ahci_port ports[32];

    rt_uint32_t cap;
    rt_uint32_t max_blocks;

    const struct rt_ahci_ops *ops;
};

struct rt_ahci_ops
{
    rt_err_t (*host_init)(struct rt_ahci_host *host);
    rt_err_t (*port_init)(struct rt_ahci_host *host, struct rt_ahci_port *port);
    rt_err_t (*port_link_up)(struct rt_ahci_host *host, struct rt_ahci_port *port);
    rt_err_t (*port_dma_init)(struct rt_ahci_host *host, struct rt_ahci_port *port);
    rt_err_t (*port_isr)(struct rt_ahci_host *host, struct rt_ahci_port *port, rt_uint32_t isr);
};

rt_err_t rt_ahci_host_register(struct rt_ahci_host *host);
rt_err_t rt_ahci_host_unregister(struct rt_ahci_host *host);

#endif /* __AHCI_H__ */
