/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-08-19     lizhirui     porting to ls2k
 */

#ifndef _AHCI_H_
#define _AHCI_H_

#define AHCI_PCI_BAR 0x24
#define AHCI_MAX_SG 56 /* hardware max is 64K */
#define AHCI_CMD_SLOT_SZ 32
#define AHCI_MAX_CMD_SLOT 32
#define AHCI_RX_FIS_SZ 256
#define AHCI_CMD_TBL_HDR 0x80
#define AHCI_CMD_TBL_CDB 0x40
#define AHCI_CMD_TBL_SZ AHCI_CMD_TBL_HDR + (AHCI_MAX_SG * 16)
#define AHCI_PORT_PRIV_DMA_SZ (AHCI_CMD_SLOT_SZ * AHCI_MAX_CMD_SLOT + \
                               AHCI_CMD_TBL_SZ + AHCI_RX_FIS_SZ)
#define AHCI_CMD_ATAPI (1 << 5)
#define AHCI_CMD_WRITE (1 << 6)
#define AHCI_CMD_PREFETCH (1 << 7)
#define AHCI_CMD_RESET (1 << 8)
#define AHCI_CMD_CLR_BUSY (1 << 10)

#define RX_FIS_D2H_REG 0x40 /* offset of D2H Register FIS data */

/* Global controller registers */
#define HOST_CAP 0x00        /* host capabilities */
#define HOST_CTL 0x04        /* global host control */
#define HOST_IRQ_STAT 0x08   /* interrupt status */
#define HOST_PORTS_IMPL 0x0c /* bitmap of implemented ports */
#define HOST_VERSION 0x10    /* AHCI spec. version compliancy */
#define HOST_CAP2 0x24       /* host capabilities, extended */

/* HOST_CTL bits */
#define HOST_RESET (1 << 0)    /* reset controller; self-clear */
#define HOST_IRQ_EN (1 << 1)   /* global IRQ enable */
#define HOST_AHCI_EN (1 << 31) /* AHCI enabled */

/* Registers for each SATA port */
#define PORT_LST_ADDR 0x00    /* command list DMA addr */
#define PORT_LST_ADDR_HI 0x04 /* command list DMA addr hi */
#define PORT_FIS_ADDR 0x08    /* FIS rx buf addr */
#define PORT_FIS_ADDR_HI 0x0c /* FIS rx buf addr hi */
#define PORT_IRQ_STAT 0x10    /* interrupt status */
#define PORT_IRQ_MASK 0x14    /* interrupt enable/disable mask */
#define PORT_CMD 0x18         /* port command */
#define PORT_TFDATA 0x20      /* taskfile data */
#define PORT_SIG 0x24         /* device TF signature */
#define PORT_CMD_ISSUE 0x38   /* command issue */
#define PORT_SCR 0x28         /* SATA phy register block */
#define PORT_SCR_STAT 0x28    /* SATA phy register: SStatus */
#define PORT_SCR_CTL 0x2c     /* SATA phy register: SControl */
#define PORT_SCR_ERR 0x30     /* SATA phy register: SError */
#define PORT_SCR_ACT 0x34     /* SATA phy register: SActive */

#ifdef CONFIG_SUNXI_AHCI
#define PORT_P0DMACR 0x70 /* SUNXI specific "DMA register" */
#endif

/* PORT_IRQ_{STAT,MASK} bits */
#define PORT_IRQ_COLD_PRES (1 << 31)     /* cold presence detect */
#define PORT_IRQ_TF_ERR (1 << 30)        /* task file error */
#define PORT_IRQ_HBUS_ERR (1 << 29)      /* host bus fatal error */
#define PORT_IRQ_HBUS_DATA_ERR (1 << 28) /* host bus data error */
#define PORT_IRQ_IF_ERR (1 << 27)        /* interface fatal error */
#define PORT_IRQ_IF_NONFATAL (1 << 26)   /* interface non-fatal error */
#define PORT_IRQ_OVERFLOW (1 << 24)      /* xfer exhausted available S/G */
#define PORT_IRQ_BAD_PMP (1 << 23)       /* incorrect port multiplier */

#define PORT_IRQ_PHYRDY (1 << 22)     /* PhyRdy changed */
#define PORT_IRQ_DEV_ILCK (1 << 7)    /* device interlock */
#define PORT_IRQ_CONNECT (1 << 6)     /* port connect change status */
#define PORT_IRQ_SG_DONE (1 << 5)     /* descriptor processed */
#define PORT_IRQ_UNK_FIS (1 << 4)     /* unknown FIS rx'd */
#define PORT_IRQ_SDB_FIS (1 << 3)     /* Set Device Bits FIS rx'd */
#define PORT_IRQ_DMAS_FIS (1 << 2)    /* DMA Setup FIS rx'd */
#define PORT_IRQ_PIOS_FIS (1 << 1)    /* PIO Setup FIS rx'd */
#define PORT_IRQ_D2H_REG_FIS (1 << 0) /* D2H Register FIS rx'd */

#define PORT_IRQ_FATAL PORT_IRQ_TF_ERR | PORT_IRQ_HBUS_ERR | PORT_IRQ_HBUS_DATA_ERR | PORT_IRQ_IF_ERR

#define DEF_PORT_IRQ PORT_IRQ_FATAL | PORT_IRQ_PHYRDY | PORT_IRQ_CONNECT | PORT_IRQ_SG_DONE | PORT_IRQ_UNK_FIS | PORT_IRQ_SDB_FIS | PORT_IRQ_DMAS_FIS | PORT_IRQ_PIOS_FIS | PORT_IRQ_D2H_REG_FIS

/* PORT_SCR_STAT bits */
#define PORT_SCR_STAT_DET_MASK 0x3
#define PORT_SCR_STAT_DET_COMINIT 0x1
#define PORT_SCR_STAT_DET_PHYRDY 0x3

/* PORT_CMD bits */
#define PORT_CMD_ATAPI (1 << 24)   /* Device is ATAPI */
#define PORT_CMD_LIST_ON (1 << 15) /* cmd list DMA engine running */
#define PORT_CMD_FIS_ON (1 << 14)  /* FIS DMA engine running */
#define PORT_CMD_FIS_RX (1 << 4)   /* Enable FIS receive DMA engine */
#define PORT_CMD_CLO (1 << 3)      /* Command list override */
#define PORT_CMD_POWER_ON (1 << 2) /* Power up device */
#define PORT_CMD_SPIN_UP (1 << 1)  /* Spin up device */
#define PORT_CMD_START (1 << 0)    /* Enable port DMA engine */

#define PORT_CMD_ICC_ACTIVE (0x1 << 28)  /* Put i/f in active state */
#define PORT_CMD_ICC_PARTIAL (0x2 << 28) /* Put i/f in partial state */
#define PORT_CMD_ICC_SLUMBER (0x6 << 28) /* Put i/f in slumber state */

#define AHCI_MAX_PORTS 32

#define ATA_FLAG_SATA (1 << 3)
#define ATA_FLAG_NO_LEGACY (1 << 4)  /* no legacy mode check */
#define ATA_FLAG_MMIO (1 << 6)       /* use MMIO, not PIO */
#define ATA_FLAG_SATA_RESET (1 << 7) /* (obsolete) use COMRESET */
#define ATA_FLAG_PIO_DMA (1 << 8)    /* PIO cmds via DMA */
#define ATA_FLAG_NO_ATAPI (1 << 11)  /* No ATAPI support */

struct ahci_cmd_hdr
{
    u32 opts;
    u32 status;
    u64 tbl_addr;
    //u32 tbl_addr_hi;
    u32 reserved[4];
};

struct ahci_sg
{
    u64 addr;
    //u32 addr_hi;
    u32 reserved;
    u32 flags_size;
};

struct ahci_ioports
{
    void __iomem *port_mmio;
    struct ahci_cmd_hdr *cmd_slot;
    struct ahci_sg *cmd_tbl_sg;
    ulong cmd_tbl;
    u32 rx_fis;
};

/**
 * struct ahci_uc_priv - information about an AHCI controller
 *
 * When driver model is used, this is accessible using dev_get_uclass_priv(dev)
 * where dev is the controller (although at present it sometimes stands alone).
 */
struct ahci_uc_priv
{
    struct rt_device parent;
    struct ahci_ioports port[AHCI_MAX_PORTS];
    u16 *ataid[AHCI_MAX_PORTS];
    u32 n_ports;
    u32 hard_port_no;
    u32 host_flags;
    u32 host_set_flags;
    void *mmio_base;
    u32 pio_mask;
    u32 udma_mask;
    u32 flags;
    u32 cap;           /* cache of HOST_CAP register */
    u32 port_map;      /* cache of HOST_PORTS_IMPL reg */
    u32 link_port_map; /*linkup port map*/
};

struct ahci_ops
{
    /**
     * reset() - reset the controller
     *
     * @dev:    Controller to reset
     * @return 0 if OK, -ve on error
     */
    int (*reset)(struct rt_device *dev);

    /**
     * port_status() - get the status of a SATA port
     *
     * @dev:    Controller to reset
     * @port:    Port number to check (0 for first)
     * @return 0 if detected, -ENXIO if nothing on port, other -ve on error
     */
    int (*port_status)(struct rt_device *dev, int port);

    /**
     * scan() - scan SATA ports
     *
     * @dev:    Controller to scan
     * @return 0 if OK, -ve on error
     */
    int (*scan)(struct rt_device *dev);
};

#define ahci_get_ops(dev) ((struct ahci_ops *)(dev)->driver->ops)

/**
 * sata_reset() - reset the controller
 *
 * @dev:    Controller to reset
 * @return 0 if OK, -ve on error
 */
int sata_reset(struct rt_device *dev);

/**
 * sata_port_status() - get the status of a SATA port
 *
 * @dev:    Controller to reset
 * @port:    Port number to check (0 for first)
 * @return 0 if detected, -ENXIO if nothin on port, other -ve on error
 */
int sata_dm_port_status(struct rt_device *dev, int port);

/**
 * sata_scan() - scan SATA ports
 *
 * @dev:    Controller to scan
 * @return 0 if OK, -ve on error
 */
int sata_scan(struct rt_device *dev);

int ahci_init(void __iomem *base);
int ahci_reset(void __iomem *base);

/**
 * ahci_init_one_dm() - set up a single AHCI port
 *
 * @dev: Controller to init
 */
int ahci_init_one_dm(struct rt_device *dev);

/**
 * ahci_start_ports_dm() - start all AHCI ports for a controller
 *
 * @dev: Controller containing ports to start
 */
int ahci_start_ports_dm(struct rt_device *dev);

/**
 * ahci_init_dm() - init AHCI for a controller, finding all ports
 *
 * @dev: Device to init
 */
int ahci_init_dm(struct rt_device *dev, void __iomem *base);

/**
 * ahci_bind_scsi() - bind a new SCSI bus as a child
 *
 * Note that the SCSI bus device will itself bind block devices
 *
 * @ahci_dev: AHCI parent device
 * @devp: Returns new SCSI bus device
 * @return 0 if OK, -ve on error
 */
int ahci_bind_scsi(struct rt_device *ahci_dev, struct rt_device **devp);

/**
 * ahci_probe_scsi() - probe and scan the attached SCSI bus
 *
 * Note that the SCSI device will itself bind block devices for any storage
 * devices it finds.
 *
 * @ahci_dev: AHCI parent device
 * @base: Base address of AHCI port
 * @return 0 if OK, -ve on error
 */
int ahci_probe_scsi(struct rt_device *ahci_dev, ulong base);

/**
 * ahci_probe_scsi_pci() - probe and scan the attached SCSI bus on PCI
 *
 * Note that the SCSI device will itself bind block devices for any storage
 * devices it finds.
 *
 * @ahci_dev: AHCI parent device
 * @return 0 if OK, -ve on error
 */
int ahci_probe_scsi_pci(struct rt_device *ahci_dev);

#endif
