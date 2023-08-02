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
 * FilePath: fsata.c
 * Date: 2022-02-10 14:55:11
 * LastEditTime: 2022-02-18 09:05:09
 * Description:  This file is for sata ctrl function implementation
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   wangxiaodong  2022/2/10    first release
 * 1.1   wangxiaodong  2022/9/9     improve functions
 * 1.2   wangxiaodong  2022/10/21   improve functions
 */

#include <string.h>
#include <stdlib.h>
#include "ftypes.h"
#include "fassert.h"
#include "fcache.h"
#include "fdebug.h"
#include "fsleep.h"
#include "fswap.h"
#include "fsata.h"
#include "fsata_hw.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

/************************** Variable Definitions *****************************/

#define FSATA_DEBUG_TAG "SATA"
#define FSATA_ERROR(format, ...)     FT_DEBUG_PRINT_E(FSATA_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSATA_WARN(format, ...)      FT_DEBUG_PRINT_W(FSATA_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSATA_INFO(format, ...)      FT_DEBUG_PRINT_I(FSATA_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSATA_DEBUG(format, ...)     FT_DEBUG_PRINT_D(FSATA_DEBUG_TAG, format, ##__VA_ARGS__)

#ifndef MAX_SATA_BLOCKS_READ_WRITE
    #define MAX_SATA_BLOCKS_READ_WRITE  0x80
#endif

/* Maximum timeouts for each event */
#define WAIT_MS_RESET   1000
#define WAIT_MS_TFD     20000 /* task file data transfer is not busy */
#define WAIT_MS_DATAIO  20000
#define WAIT_MS_LINKUP  200


static FError FSataAhciDataIO(FSataCtrl *instance_p, u8 port, u8 *fis,
                              int fis_len, u8 *buf, int buf_len, boolean is_ncq, boolean is_write);

/**
 * @name: FSataAhciPortBase
 * @msg: get port x base address
 * @param {uintptr} base_address FSata base address
 * @param {u32} port sata port number
 * @return {uintptr} port x base address
 */
static uintptr FSataAhciPortBase(uintptr base_address, u32 port)
{
    return (base_address + 0x100 + (port * 0x80));
}

/**
 * @name: FSataWaitCmdCompleted
 * @msg: read register status and wait command execution is completed
 * @param {uintptr} reg FSata register
 * @param {int} timeout_msec wait timeout value
 * @param {u32} sign register status flag bit
 * @return {int} return 0 if command execute success, return -1 if command execute timeout
 */
static int FSataWaitCmdCompleted(uintptr reg, int timeout_msec, u32 sign)
{
    int i;

    for (i = 0; (FtIn32(reg)& sign) && (i < timeout_msec); i++)
    {
        fsleep_millisec(1);
    }

    return (i < timeout_msec) ? 0 : -1;
}

/**
 * @name: FSataAhciLinkUp
 * @msg:  check sata ahci port link status
 * @param {FSataCtrl} *instance_p, pointer to the FSataCtrl instance.
 * @param {u8} port, port number
 * @return {int} return FSATA_SUCCESS if successful, return others if failed
 */
static FError FSataAhciLinkUp(FSataCtrl *instance_p, u8 port)
{
    u32 reg_val;
    int i = 0;
    uintptr port_base_addr = instance_p->port[port].port_base_addr;

    /*
     * Bring up SATA link.
     * SATA link bringup time is usually less than 1 ms; only very
     * rarely has it taken between 1-2 ms. Never seen it above 2 ms.
     */
    while (i < WAIT_MS_LINKUP)
    {
        reg_val = FSATA_READ_REG32(port_base_addr, FSATA_PORT_SCR_STAT);
        if ((reg_val & FSATA_PORT_SCR_STAT_DET_MASK) == FSATA_PORT_SCR_STAT_DET_PHYRDY)
        {
            return FSATA_SUCCESS;
        }
        fsleep_microsec(1000);
        i++;
    }

    return FSATA_ERR_TIMEOUT;
}

/**
 * @name: FSataAhciInquiry
 * @msg:  inquiry sata information
 * @param {FSataCtrl} *instance_p, pointer to the FSataCtrl instance.
 * @param {u8} port, port number
 * @return {FError} return FSATA_SUCCESS if successful, return others if failed
 */
static FError FSataAhciInquiry(FSataCtrl *instance_p, u8 port)
{
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    FError ret = FSATA_SUCCESS;
    u16 *idbuf;

    /* 64位需要预留给内存池更大的空间 */
    static u16 tmpid[FSATA_ID_WORDS] __attribute__((aligned(128))) = {0};

    u8 fis[20];
    /* Preset the FIS */
    memset(fis, 0, sizeof(fis));

    fis[0] = FSATA_FIS_REG_HOST_TO_DEVICE; /* Register Host to Device FIS */
    fis[1] = FSATA_FIS_REG_HOST_TO_DEVICE_C;
    fis[2] = FSATA_CMD_IDENTIFY_DEVICE; /* Command byte. */
    ret = FSataAhciDataIO(instance_p, port, fis, sizeof(fis),
                          (u8 *)tmpid, FSATA_ID_WORDS * 2, FALSE, FALSE);
    if (ret != FSATA_SUCCESS)
    {
        FSATA_ERROR("FSataAhciInquiry: command failure. ret = %#x.", ret);
        return FSATA_ERR_OPERATION;
    }

    instance_p->ataid[port] = tmpid;

    return FSATA_SUCCESS;
}

/**
 * @name: FSataIdentityCopy
 * @msg:  parse sata Identity information to vendor, product, revision
 * @param {unsigned char } *dest, pointer to the destination address.
 * @param {unsigned char } *src, pointer to the source address.
 * @param {u32} len, parse length.
 * @return {void}
 */
static void FSataIdentityCopy(unsigned char *dest, unsigned char *src, u32 len)
{
    FASSERT(dest != NULL);
    FASSERT(src != NULL);
    FASSERT(len != 0);

    u32 start, end;

    start = 0;
    while (start < len)
    {
        if (src[start] != 0x20)/* character is not sapce */
        {
            break;
        }
        start++;
    }
    end = len - 1;
    while (end > start)
    {
        if (src[end] != 0x20)/* character is not sapce */
        {
            break;
        }
        end--;
    }
    for (; start <= end; start++)
    {
        *dest ++ = src[start];
    }
    *dest = '\0';
}

/**
 * @name: FSataIdToSectors
 * @msg:  parse sata Identity information to capacity.
 * @param {u16} *id, pointer to Identity information .
 * @return {u64} capacity
 */
static u64 FSataIdToSectors(u16 *id)
{
    if (FSataIdHasLba(id))
    {
        if (FSataIdHasLba48(id))
        {
            return FSATA_ID_U64(id, FSATA_ID_LBA48_SECTORS);
        }
        else
        {
            return (u64)(FSATA_ID_U32(id, FSATA_ID_LBA_SECTORS));
        }
    }
    else
    {
        return 0;
    }
}

/**
 * @name: FSataIdStrCopy
 * @msg:  swap sata Identity information
 * @param {u16} *dest, pointer to the destination address.
 * @param {u16} *src, pointer to the source address.
 * @param {int} len, swap length.
 * @return {void}
 */
static void FSataIdStrCopy(u16 *dest, u16 *src, int len)
{
    int i;
    for (i = 0; i < len / 2; i++)
    {
        dest[i] = __swab16(src[i]);
    }
}

/**
 * @name: FSataBlockToMB
 * @msg:  Converts the number of blocks in 512 byte to 0.1MB
 * @param {unsigned long} block_count, block count.
 * @param {unsigned long} mul_by, multiple value.
 * @param {int} div_by, divided value.
 * @return {unsigned long} convert value
 */
static unsigned long FSataBlockToMB(unsigned long block_count, unsigned long mul, int div)
{
    unsigned long bc_quot, bc_rem;

    /* x * m / d == x / d * m + (x % d) * m / d */
    bc_quot = (block_count >> div);  /* upper > div bit */
    bc_rem  = block_count - (bc_quot << div); /* low div bit */
    return (bc_quot * mul + ((bc_rem * mul) >> div));
}

/**
 * @name: FSataInfoPrint
 * @msg:  printf sata information
 * @param {FSataInfo} *dev_desc, pointer to the FSata information.
 * @return {void}
 */
void FSataInfoPrint(FSataInfo *dev_desc)
{
    unsigned long lba512; /* number of blocks if 512bytes block size */

    if (dev_desc->type == FSATA_DEV_TYPE_UNKNOWN)
    {
        FSATA_INFO("Not available.");
        return;
    }

    if (dev_desc->if_type == FSATA_IF_TYPE_SCSI)
    {
        FSATA_INFO("Vendor: %s Prod: %s Rev: %s",
                   dev_desc->vendor,
                   dev_desc->product,
                   dev_desc->revision);
    }

    if (dev_desc->type == FSATA_DEV_TYPE_HARDDISK)
    {
        FSATA_INFO("Type: Hard Disk");
    }

    if ((dev_desc->lba > 0L) && (dev_desc->blksz > 0L))
    {
        unsigned long mb, mb_quot, mb_rem, gb, gb_quot, gb_rem;
        unsigned long lba;

        lba = dev_desc->lba;

        lba512 = (lba * (dev_desc->blksz / 512));
        /* round to 1 digit */
        /* 2048 = (1024 * 1024) / 512 MB */
        mb = FSataBlockToMB(lba512, 10, 11);

        dev_desc->lba512 = lba512;

        FSATA_INFO("lba512=%lu, mb=%lu", lba512, mb);

        mb_quot = mb / 10;
        mb_rem  = mb - (10 * mb_quot);

        gb = mb / 1024;
        gb_quot = gb / 10;
        gb_rem  = gb - (10 * gb_quot);

        FSATA_INFO("Capacity: %lu.%lu MB = %lu.%lu GB (%lu x %lu)",
                   mb_quot, mb_rem,
                   gb_quot, gb_rem,
                   (unsigned long)lba,
                   dev_desc->blksz);
    }
    else
    {
        FSATA_INFO("Capacity: not available.");
    }
}

/**
 * @name: FSataAhciReadCapacity
 * @msg:  get sata capacity by parse instance_p ataid
 * @param {FSataCtrl} *instance_p, pointer to the FSataCtrl instance.
 * @param {u8} port, port number
 * @param {unsigned long} *capacity, pointer to capacity value
 * @param {unsigned long} *blksz, pointer to block size
 * @return {FError} return FSATA_SUCCESS if successful, return others if failed
 */
static FError FSataAhciReadCapacity(FSataCtrl *instance_p, u8 port,
                                    unsigned long *capacity, unsigned long *blksz)
{
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    FError ret = FSATA_SUCCESS;

    u32 transfer_size; /* number of bytes per iteration */

    if (!instance_p->ataid[port])
    {
        FSATA_ERROR("READ CAPACITY10 command failure. "
                    "\tNo ATA info!\n"
                    "\tPlease run command INQUIRY first!");
        return FSATA_ERR_OPERATION;
    }

    u64 cap64 = FSataIdToSectors(instance_p->ataid[port]);
    if (cap64 > 0x100000000ULL)
    {
        cap64 = 0xffffffff;
    }

    *capacity = (unsigned long)(cap64);
    if (*capacity != 0xffffffff)
    {
        /* Read capacity (10) was sufficient for this drive. */
        *blksz = 512;
        return FSATA_SUCCESS;
    }
    else
    {
        FSATA_DEBUG("Should read capacity 16?");
    }

    return FSATA_SUCCESS;
}

/**
 * @name: FSataAhciReadInfo
 * @msg:  get sata information
 * @param {FSataCtrl} *instance_p, pointer to the FSataCtrl instance.
 * @param {u8} port, port number
 * @return {FError} return FSATA_SUCCESS if read successful, return others if read failed
 */
FError FSataAhciReadInfo(FSataCtrl *instance_p, u8 port)
{
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    uintptr base_addr = instance_p->config.base_addr;
    FError ret = FSATA_SUCCESS;

    u16 *idbuf;
    unsigned long capacity, blksz;
    unsigned char info_data[50];
    memset(info_data, 0, sizeof(info_data));

    ret = FSataAhciInquiry(instance_p, port);
    if (ret != FSATA_SUCCESS)
    {
        FSATA_ERROR("FSataAhciInquiry!");
        return FSATA_ERR_OPERATION;
    }

    /* Parse SATA Information */
    idbuf = instance_p->ataid[port];
    FSataIdStrCopy((u16 *)&info_data[16], &idbuf[FSATA_ID_PROD], 16);
    FSataIdStrCopy((u16 *)&info_data[32], &idbuf[FSATA_ID_FW_REV], 4);

    /* is ata device */
    if (!((__swab16(idbuf[0]) & FSATA_ID_ATA_DEVICE)))
    {
        instance_p->port[port].dev_info.type = FSATA_DEV_TYPE_HARDDISK;
        memcpy(&info_data[8], "ATA     ", 8); /* copy 8 bytes */
    }
    else
    {
        instance_p->port[port].dev_info.type = FSATA_DEV_TYPE_UNKNOWN;
    }

    /* get info for this device */
    FSataIdentityCopy((unsigned char *)instance_p->port[port].dev_info.vendor, &info_data[8], 8);
    FSataIdentityCopy((unsigned char *)instance_p->port[port].dev_info.product, &info_data[16], 16);
    FSataIdentityCopy((unsigned char *)instance_p->port[port].dev_info.revision, &info_data[32], 4);

    /* get sata capacity by parse ataid */
    ret = FSataAhciReadCapacity(instance_p, port, &capacity, &blksz);
    if (ret != FSATA_SUCCESS)
    {
        FSATA_ERROR("FSataAhciReadCapacity error!");
        return FSATA_ERR_OPERATION;
    }

    instance_p->port[port].dev_info.lba = capacity;
    instance_p->port[port].dev_info.blksz = blksz;
    instance_p->port[port].dev_info.if_type = FSATA_IF_TYPE_SCSI;

    FSataInfoPrint(&(instance_p->port[port].dev_info));

    return ret;
}

/**
 * @name: FSataAhciReset
 * @msg: reset ahci / hba(host bus adapter)
 * @param {FSataCtrl} *instance_p, pointer to the FSataCtrl instance
 * @return {FError} return FSATA_SUCCESS if successful, return others if failed
 */
static FError FSataAhciReset(FSataCtrl *instance_p)
{
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    int i = WAIT_MS_RESET;
    uintptr base_addr = instance_p->config.base_addr;

    u32 reg_val = 0;

    /* read host control register and reset */
    reg_val = FSATA_READ_REG32(base_addr, FSATA_HOST_CTL);

    if ((reg_val & FSATA_HOST_RESET) == 0)
    {
        FSATA_SETBIT(base_addr, FSATA_HOST_CTL, FSATA_HOST_RESET);
    }

    /* reset must complete within 1 millisecond, or the hardware should be considered fried.*/
    do
    {
        fsleep_microsec(1000);
        reg_val = FSATA_READ_REG32(base_addr, FSATA_HOST_CTL);
        i--;
    }
    while ((i > 0) && (reg_val & FSATA_HOST_RESET));

    if (i == 0)
    {
        FSATA_ERROR("Controller reset failed (0x%x).", reg_val);
        return FSATA_ERR_TIMEOUT;
    }

    return FSATA_SUCCESS;
}

/**
 * @name: FSataAhciInit
 * @msg: init ahci / hba(host bus adapter)
 * @param {FSataCtrl} *instance_p, pointer to the FSataCtrl instance
 * @return {FError} return FSATA_SUCCESS if successful, return others if failed
 */
FError FSataAhciInit(FSataCtrl *instance_p)
{
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    uintptr base_addr = instance_p->config.base_addr;
    FError ret = FSATA_SUCCESS;
    u32 i;
    uintptr port_base_addr = 0; /* ahci port x base address */
    u32 reg_val = 0;
    u32 port_num = 0;

    /* reset host control */
    ret = FSataAhciReset(instance_p);
    if (ret != FSATA_SUCCESS)
    {
        return ret;
    }

    /* ahci enable */
    FSATA_WRITE_REG32(base_addr, FSATA_HOST_CTL, FSATA_HOST_AHCI_EN);
    FSATA_READ_REG32(base_addr, FSATA_HOST_CTL);

    /* read cap.np, set the ports bit which are available for software to use. */
    port_num = FSATA_READ_REG32(base_addr, FSATA_HOST_CAP) & FSATA_HOST_CAP_NP_MASK;
    FSATA_WRITE_REG32(base_addr, FSATA_HOST_PORTS_IMPL, FSATA_HOST_PORTS_IMPL_MASK(port_num));

    /* set instance_p paramameters */
    instance_p->n_ports = port_num + 1;
    instance_p->port_map = FSATA_READ_REG32(base_addr, FSATA_HOST_PORTS_IMPL);
    FSATA_DEBUG("port_map 0x%x  n_ports %d", instance_p->port_map, instance_p->n_ports);

    for (i = 0; i < instance_p->n_ports; i++)
    {
        if (!(instance_p->port_map & BIT(i)))
        {
            continue;
        }
        /* set ports base address */
        instance_p->port[i].port_base_addr = FSataAhciPortBase(base_addr, i);
        port_base_addr = instance_p->port[i].port_base_addr;

        /* make sure port is not active */
        reg_val = FSATA_READ_REG32(port_base_addr, FSATA_PORT_CMD);
        if (reg_val & (FSATA_PORT_CMD_LIST_ON | FSATA_PORT_CMD_FIS_ON |
                       FSATA_PORT_CMD_FIS_RX | FSATA_PORT_CMD_START))
        {
            FSATA_DEBUG("Port %d is active, reg = %#x. Deactivating.", i, reg_val);
            reg_val &= ~(FSATA_PORT_CMD_LIST_ON | FSATA_PORT_CMD_FIS_ON |
                         FSATA_PORT_CMD_FIS_RX | FSATA_PORT_CMD_START);
            FSATA_WRITE_REG32(port_base_addr, FSATA_PORT_CMD, reg_val);

            /* spec says 500 msecs for each bit, so this is slightly incorrect.*/
            fsleep_millisec(500);
        }

        /* Add the spinup command to whatever mode bits may
         * already be on in the command register, set not support staggered spin-up */
        reg_val = FSATA_READ_REG32(port_base_addr, FSATA_PORT_CMD);
        reg_val |= FSATA_PORT_CMD_SPIN_UP;
        FSATA_WRITE_REG32(port_base_addr, FSATA_PORT_CMD, reg_val);

        /* check sata port is linked */
        ret = FSataAhciLinkUp(instance_p, i);
        if (ret)
        {
            FSATA_DEBUG("sata host %d, port %d link timeout.", instance_p->config.instance_id, i);    
            continue;
        }
        else
        {
            FSATA_DEBUG("sata host %d , port %d link ok.", instance_p->config.instance_id, i) ;
        }

        /* Clear error status */
        reg_val = FSATA_READ_REG32(port_base_addr, FSATA_PORT_SCR_ERR);
        if (reg_val)
        {
            FSATA_WRITE_REG32(port_base_addr, FSATA_PORT_SCR_ERR, reg_val);
        }

        /* Device presence detected but Phy communication not established, retry once more */
        reg_val = FSATA_READ_REG32(port_base_addr, FSATA_PORT_SCR_STAT) & FSATA_PORT_SCR_STAT_DET_MASK;
        if (reg_val == FSATA_PORT_SCR_STAT_DET_COMINIT)
        {
            FSATA_INFO("sata link %d down, retrying...", i);
            i--;
            continue;
        }

        /* Clear error status */
        reg_val = FSATA_READ_REG32(port_base_addr, FSATA_PORT_SCR_ERR);
        if (reg_val)
        {
            FSATA_WRITE_REG32(port_base_addr, FSATA_PORT_SCR_ERR, reg_val);
        }

        /* clear port irq status */
        reg_val = FSATA_READ_REG32(port_base_addr, FSATA_PORT_IRQ_STAT);
        if (reg_val)
        {
            FSATA_WRITE_REG32(port_base_addr, FSATA_PORT_IRQ_STAT, reg_val);
        }

        /* clear host corresponding port interrupt status register */
        FSATA_WRITE_REG32(base_addr, FSATA_HOST_IRQ_STAT, BIT(i));

        /* register linkup ports */
        reg_val = FSATA_READ_REG32(port_base_addr, FSATA_PORT_SCR_STAT);
        if ((reg_val & FSATA_PORT_SCR_STAT_DET_MASK) == FSATA_PORT_SCR_STAT_DET_PHYRDY)
        {
            instance_p->link_port_map |= BIT(i);
        }
    }
    if (instance_p->link_port_map == 0)
    {
        FSATA_ERROR("Sata ports link failed.\n");
        return FSATA_UNKNOWN_DEVICE;
    }       

    /* host interrupt enable */
    reg_val = FSATA_READ_REG32(base_addr, FSATA_HOST_CTL);
    FSATA_WRITE_REG32(base_addr, FSATA_HOST_CTL, reg_val | FSATA_HOST_IRQ_EN);

    return FSATA_SUCCESS;
}

/**
 * @name: FSataAhciPortStart
 * @msg: init ahci port, allocate Port Memory Usage
 * @param {FSataCtrl} *instance_p, pointer to the FSataCtrl instance
 * @param {u8} port, port number
 * @param {uintptr} mem, Memory start address allocated to port
 * @return {FError} return FSATA_SUCCESS if successful, return others if failed
 */
FError FSataAhciPortStart(FSataCtrl *instance_p, u8 port, uintptr mem)
{
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    FASSERT(mem);
    uintptr base_addr = instance_p->config.base_addr;

    FError ret = FSATA_SUCCESS;
    FSataAhciPorts *port_info = &(instance_p->port[port]);
    uintptr port_base_addr = port_info->port_base_addr;

    u32 reg_val = FSATA_READ_REG32(port_base_addr, FSATA_PORT_SCR_STAT);
    if ((reg_val & FSATA_PORT_SCR_STAT_DET_MASK) != FSATA_PORT_SCR_STAT_DET_PHYRDY)
    {
        FSATA_ERROR("No Link on host %d port %d!", instance_p->config.instance_id, port);
        return FSATA_ERR_OPERATION;
    }

    memset((void *)mem, 0, FSATA_AHCI_PORT_PRIV_DMA_SZ);

    /* First item in chunk of DMA memory: 32 command lists, 32 bytes each in size */
    port_info->cmd_list = (FSataAhciCommandList *)(mem);
    mem += FSATA_AHCI_CMD_LIST_HEADER_SIZE * FSATA_AHCI_CMD_LIST_HEADER_NUM;

    /* Second item: Received-FIS area */
    port_info->rx_fis = (FSataAhciRecvFis *)(mem);
    mem += FSATA_AHCI_RX_FIS_SZ;

    /* Third item: data area for storing a single command and its scatter-gather table */
    port_info->cmd_tbl_base_addr = (uintptr)mem;
    mem += FSATA_AHCI_CMD_TABLE_HEADER_SIZE;

    /* command table prdt */
    port_info->cmd_tbl_prdt = (FSataAhciCommandTablePrdt *)mem;

    /* set ahci port registers */
    FSATA_WRITE_REG32(port_base_addr, FSATA_PORT_LST_ADDR,
                      (uintptr)port_info->cmd_list & FSATA_PORT_CMD_LIST_ADDR_MASK);

    FSATA_WRITE_REG32(port_base_addr, FSATA_PORT_LST_ADDR_HI, 0);

    FSATA_WRITE_REG32(port_base_addr, FSATA_PORT_FIS_ADDR,
                      (uintptr)port_info->rx_fis & FSATA_PORT_CMD_FIS_ADDR_MASK);

    FSATA_WRITE_REG32(port_base_addr, FSATA_PORT_FIS_ADDR_HI, 0);

    FSATA_WRITE_REG32(port_base_addr, FSATA_PORT_CMD, FSATA_PORT_CMD_ICC_ACTIVE | FSATA_PORT_CMD_FIS_RX |
                      FSATA_PORT_CMD_POWER_ON | FSATA_PORT_CMD_SPIN_UP | FSATA_PORT_CMD_START);

    /*
     * Make sure interface is not busy based on error and status
     * information from task file data register before proceeding
     */
    if (FSataWaitCmdCompleted(port_base_addr + FSATA_PORT_TFDATA, WAIT_MS_TFD, FSATA_BUSY))
    {
        FSATA_DEBUG("Timeout exit!");
        return FSATA_ERR_TIMEOUT;
    }

    instance_p->private_data |= BIT(port);

    return ret;
}

/**
 * @name: FSataAhciFillCmdTablePrdt
 * @msg: allocate ahci command table prdt information
 * @param {FSataCtrl} *instance_p, pointer to the FSataCtrl instance
 * @param {u8} port, port number
 * @param {unsigned char} *buffer, data buffer address
 * @param {int} buf_len, data length
 * @return {int} return item_count if successful, return -1 if failed
 */
static int FSataAhciFillCmdTablePrdt(FSataCtrl *instance_p, u8 port,
                                     unsigned char *buf, int buf_len)
{
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);

    FSataAhciPorts *port_info = &(instance_p->port[port]);
    FSataAhciCommandTablePrdt *command_table_prdt = port_info->cmd_tbl_prdt;
    int item_count;
    int i;

    item_count = ((buf_len - 1) / MAX_DATA_BYTE_COUNT) + 1;
    if (item_count > FSATA_AHCI_PRTD_ITEM_NUM)
    {
        FSATA_ERROR("Too much command table prdt items %d!", item_count);
        return -1;
    }

    for (i = 0; i < item_count; i++)
    {
        command_table_prdt->addr_low = ((unsigned long) buf + i * MAX_DATA_BYTE_COUNT);
        command_table_prdt->addr_high = 0;
        command_table_prdt->data_byte = (0x3fffff &
                                         (buf_len < MAX_DATA_BYTE_COUNT
                                          ? (buf_len - 1)
                                          : (MAX_DATA_BYTE_COUNT - 1)));
        command_table_prdt++;
        buf_len -= MAX_DATA_BYTE_COUNT;
    }

    return item_count;
}

/**
 * @name: FSataAhciFillCmdList
 * @msg: allocate ahci command list information
 * @param {FSataAhciPorts} *port_info is a pointer to the FSataAhciPorts instance
 * @param {u32} description_info, prdtl+flag+cfl
 * @return {void}
 */
static void FSataAhciFillCmdList(FSataAhciPorts *port_info, u32 description_info)
{
    FASSERT(port_info != NULL);

    port_info->cmd_list->description_info = description_info;
    port_info->cmd_list->status = 0;
    port_info->cmd_list->tbl_addr = ((u32)port_info->cmd_tbl_base_addr & FSATA_PORT_CMD_TABLE_ADDR_MASK);
#ifdef __aarch64__
    port_info->cmd_list->tbl_addr_hi = (u32)(((port_info->cmd_tbl_base_addr) >> 16) >> 16);
#endif
}

/**
 * @name: FSataAhciDataIO
 * @msg: transfer ahci command fis and data buffer
 * @param {FSataCtrl} *instance_p, pointer to the FSataCtrl instance
 * @param {u8} port number
 * @param {u8} *fis, command fis buffer
 * @param {int} fis_len, command fis length
 * @param {u8} *buf, data read/write buffer
 * @param {int} buf_len, data length
 * @param {u8} is_write, 0-read, 1-write
 * @return {FError} return FSATA_SUCCESS if successful, return others if failed
 */
static FError FSataAhciDataIO(FSataCtrl *instance_p, u8 port, u8 *fis,
                              int fis_len, u8 *buf, int buf_len, boolean is_ncq, boolean is_write)
{
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    FASSERT(fis != NULL);

    FSataAhciPorts *port_info = &(instance_p->port[port]);

    uintptr base_addr = instance_p->config.base_addr;
    uintptr port_base_addr = instance_p->port[port].port_base_addr;

    if (port >= instance_p->n_ports)
    {
        FSATA_DEBUG("Invalid port number %d.", port);
        return FSATA_ERR_INVALID_PARAMETER;
    }

    u32 reg_val = FSATA_READ_REG32(port_base_addr, FSATA_PORT_SCR_STAT);
    if ((reg_val & FSATA_PORT_SCR_STAT_DET_MASK) != FSATA_PORT_SCR_STAT_DET_PHYRDY)
    {
        FSATA_ERROR("No Link on host %d port %d!", instance_p->config.instance_id, port);
        return FSATA_ERR_OPERATION;
    }

    /* copy fis command to command table CFIS */
    memcpy((unsigned char *)port_info->cmd_tbl_base_addr, fis, fis_len);

    /* copy data buffer address to command table prdt item */
    int prdt_length = FSataAhciFillCmdTablePrdt(instance_p, port, buf, buf_len);
    if (prdt_length == -1)
    {
        FSATA_ERROR("FSataAhciFillCmdTablePrdt failed, buf_len = %d.\n", buf_len);
        return FSATA_ERR_INVALID_PARAMETER;
    }

    /* command list DW0: PRDTL(buf len) + W/R + CFL(fis len, 4 Byte(Dword) aligned) */
    u32 description_info = (prdt_length << 16) | (is_write << 6) | (fis_len >> 2);

    /* copy data to command list struct */
    FSataAhciFillCmdList(port_info, description_info);

    FCacheDCacheFlushRange((unsigned long)port_info->cmd_list, FSATA_AHCI_PORT_PRIV_DMA_SZ);
    FCacheDCacheFlushRange((unsigned long)buf, (unsigned long)buf_len);

    /* set tag bit in SACT register before write CI register when use native cmd */
    if (is_ncq == TRUE)
    {
        FSATA_WRITE_REG32(port_base_addr, FSATA_PORT_SCR_ACT, FSATA_PORT_SCR_ACT_ENABLE);
    }

    /* send cmd */
    FSATA_WRITE_REG32(port_base_addr, FSATA_PORT_CMD_ISSUE, FSATA_PORT_CMD_ISSUE_ENABLE);

    if (FSataWaitCmdCompleted(port_base_addr + FSATA_PORT_CMD_ISSUE, WAIT_MS_DATAIO, FSATA_PORT_CMD_ISSUE_ENABLE))
    {
        FSATA_ERROR("Timeout exit!");
        return FSATA_ERR_TIMEOUT;
    }

    return FSATA_SUCCESS;
}

/**
 * @name: FSataReadWrite
 * @msg: read or write sata block data, choose if use ncq
 * @param {FSataCtrl} *instance_p, pointer to the FSataCtrl instance
 * @param {u8} port, port number
 * @param {u32} start, start block
 * @param {u32} blk_cnt, block count
 * @param {u8} *buffer, data buffer
 * @param {boolean} is_ncq, FALSE-not support ncq, TRUE-support ncq
 * @param {boolean} is_write, read or write, FALSE-read, TRUE-write
 * @return {FError} return FSATA_SUCCESS if successful, return others if failed
 */
FError FSataReadWrite(FSataCtrl *instance_p, u8 port, u32 start,
                      u16 blk_cnt, u8 *buffer, boolean is_ncq, boolean is_write)
{
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    FASSERT(blk_cnt);
    uintptr base_addr = instance_p->config.base_addr;
    FError ret = FSATA_SUCCESS;

    u16 now_blocks; /* number of blocks per iteration */
    u32 transfer_size; /* number of bytes per iteration */

    u8 fis[20];
    /* Preset the FIS */
    memset(fis, 0, sizeof(fis));

    fis[0] = FSATA_FIS_REG_HOST_TO_DEVICE;/* fis type */
    fis[1] = FSATA_FIS_REG_HOST_TO_DEVICE_C; /* C and PM Port */
    if (is_ncq == FALSE)
    {
        fis[2] = is_write ? FSATA_CMD_WRITE_EXT : FSATA_CMD_READ_EXT;    /* Command */
    }
    else
    {
        fis[2] = is_write ? FSATA_CMD_FPDMA_WRITE : FSATA_CMD_FPDMA_READ;    /* Command */
    }

    while (blk_cnt)
    {
        now_blocks = min((u16)MAX_SATA_BLOCKS_READ_WRITE, blk_cnt);
        transfer_size = FSATA_SECT_SIZE * now_blocks;
        if (is_ncq == FALSE)
        {
            /* FEATURE Reserved */
            fis[3] = 0; /* features 7:0 */
            fis[11] = 0; /* features 15:8 */

            /* LBA of first logical sector to be transferred */
            fis[4] = ((start >> 0)  & 0xff); /* lba 7:0 */
            fis[5] = ((start >> 8)  & 0xff); /* lba 15:8 */
            fis[6] = ((start >> 16) & 0xff); /* lba 23:16 */
            fis[8] = ((start >> 24) & 0xff); /* lba 31:24 */

            /* device reg, bit 6 Shall be set to one in read command */
            fis[7] = FSATA_CMD_EXT_DEVICE;

            /* The number of logical sectors to be transferred. */
            fis[12] = (now_blocks >> 0) & 0xff;/* count 7:0 */
            fis[13] = (now_blocks >> 8) & 0xff;/* count 15:8 */
        }
        else
        {
            /* FEATURE：The number of logical sectors to be transferred. */
            fis[3] = (now_blocks >> 0) & 0xff; /* features 7:0 */
            fis[11] = (now_blocks >> 8) & 0xff; /* features 15:8 */

            /* LBA of first logical sector to be transferred */
            fis[4] = ((start >> 0)  & 0xff); /* lba 7:0 */
            fis[5] = ((start >> 8)  & 0xff); /* lba 15:8 */
            fis[6] = ((start >> 16) & 0xff); /* lba 23:16 */
            fis[8] = ((start >> 24) & 0xff); /* lba 31:24 */

            /* device reg, bit 6 Shall be set to one */
            fis[7] = FSATA_CMD_EXT_DEVICE;

            /* count */
            fis[12] = 0;/* count 7:0, NCQ TAG field */
            fis[13] = 0;/* count 15:8, Normal priority */
        }

        ret = FSataAhciDataIO(instance_p, port, fis, sizeof(fis),
                              buffer, transfer_size, is_ncq, is_write);
        if (ret)
        {
            FSATA_ERROR("scsi_ahci: SCSI command failure. ret = %#x.", ret);
            return FSATA_ERR_OPERATION;
        }

        buffer += transfer_size;
        blk_cnt -= now_blocks;
        start += now_blocks;
    }
    return ret;
}

/**
 * @name: FSataCfgInitialize
 * @msg: Initialize Sata ctrl
 * @param {FSataCtrl} *instance_p, pointer to the FSataCtrl instance.
 * @param {FSataConfig} *input_config_p, Default configuration parameters of FSata
 * @return {FError} return FSATA_SUCCESS if successful, return others if failed
 */
FError FSataCfgInitialize(FSataCtrl *instance_p, const FSataConfig *input_config_p)
{
    FASSERT(instance_p);

    /*Set default values and configuration data */
    FSataCfgDeInitialize(instance_p);

    instance_p->config = *input_config_p;

    instance_p->is_ready = FT_COMPONENT_IS_READY;

    return FSATA_SUCCESS;
}

/**
 * @name: FSataCfgDeInitialize
 * @msg: DeInitialization function for the device instance
 * @param {FSataCtrl} *instance_p, pointer to the FSataCtrl instance.
 * @return {*}
 */
void FSataCfgDeInitialize(FSataCtrl *pctrl)
{
    FASSERT(pctrl);

    pctrl->is_ready = 0;
    memset(pctrl, 0, sizeof(*pctrl));

    return;
}