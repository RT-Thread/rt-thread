/**************************************************************************//**
*
* @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2021-1-13       Wayne        First version
*
******************************************************************************/

#ifndef __SPINAND_H__
#define __SPINAND_H__

#include <rtthread.h>

#include <drivers/mtd_nand.h>
#include "drv_spi.h"
#include <board.h>

/* SPI NAND flash information */
struct nu_spinand_info
{
    uint32_t   u32JEDECID;
    uint16_t   u16PageSize;
    uint16_t   u16OOBSize;
    uint8_t    u8QuadReadCmdId;
    uint8_t    u8ReadStatusCmdId;
    uint8_t    u8WriteStatusCmdid;
    uint8_t    u8StatusValue;
    uint8_t    u8DummyByte;
    uint32_t   u32BlockPerFlash;
    uint32_t   u32PagePerBlock;
    uint8_t    u8IsDieSelect;
    const char *szDescription;
};
typedef struct nu_spinand_info *nu_spinand_info_t;

struct spinand_ops
{
    rt_err_t (*block_erase)(struct rt_qspi_device *qspi, uint8_t u8Addr2, uint8_t u8Addr1, uint8_t u8Addr0);
    uint8_t (*block_isbad)(struct rt_qspi_device *qspi, uint32_t u32PageAddr);
    rt_err_t (*block_markbad)(struct rt_qspi_device *qspi,  uint32_t u32PageAddr);
    rt_err_t (*die_select)(struct rt_qspi_device *qspi, uint8_t select_die);
    rt_err_t (*jedecid_get)(struct rt_qspi_device *qspi, uint32_t *pu32ID);
    rt_err_t (*program_dataload)(struct rt_qspi_device *qspi, uint8_t u8AddrH, uint8_t u8AddrL, uint8_t *pu8DataBuff,
                                 uint32_t u32DataCount, uint8_t *pu8SpareBuff, uint32_t u32SpareCount);

    rt_err_t (*program_execute)(struct rt_qspi_device *qspi,  uint8_t u8Addr2, uint8_t u8Addr1, uint8_t u8Addr0);
    rt_err_t (*read_dataload)(struct rt_qspi_device *qspi, uint8_t u8Addr2, uint8_t u8Addr1, uint8_t u8Addr0);
    rt_err_t (*read_quadoutput)(struct rt_qspi_device *qspi, uint8_t u8AddrH, uint8_t u8AddrL, uint8_t *pu8DataBuff, uint32_t u32DataCount);
};
typedef struct spinand_ops *nu_spinand_ops_t;

struct nu_spinand
{
    struct nu_spinand_info info;
    struct rt_qspi_device *qspi_device;
    nu_spinand_ops_t       ops;
    struct rt_mutex        lock;
};
typedef struct nu_spinand *nu_spinand_t;

#define SPINAND_FLASH_JEDECID              g_spinandflash_dev.info.u32JEDECID
#define SPINAND_FLASH_PAGE_SIZE            g_spinandflash_dev.info.u16PageSize
#define SPINAND_FLASH_OOB_SIZE             g_spinandflash_dev.info.u16OOBSize
#define SPINAND_FLASH_QUADREAD_CMDID       g_spinandflash_dev.info.u8QuadReadCmdId
#define SPINAND_FLASH_DUMMYBYTE            g_spinandflash_dev.info.u8DummyByte
#define SPINAND_FLASH_BLOCK_NUM            g_spinandflash_dev.info.u32BlockPerFlash
#define SPINAND_FLASH_PAGE_PER_BLOCK_NUM   g_spinandflash_dev.info.u32PagePerBlock
#define SPINAND_FLASH_DESCRIPTION          g_spinandflash_dev.info.szDescription
#define SPINAND_FLASH_MCP                  g_spinandflash_dev.info.u8IsDieSelect

#define SPINAND_FLASH_INFO                 &g_spinandflash_dev.info
#define SPINAND_FLASH_QSPI                 g_spinandflash_dev.qspi_device
#define SPINAND_FLASH_LOCK                 &g_spinandflash_dev.lock
#define SPINAND_FLASH_OPS                  g_spinandflash_dev.ops

#define SPINAND_DIE_ID0 (0)
#define SPINAND_DIE_ID1 (1)

#define SPINAND_SPARE_LAYOUT_SIZE          16

rt_err_t rt_hw_mtd_spinand_register(const char *device_name);
rt_size_t nu_qspi_transfer_message(struct rt_qspi_device  *device, struct rt_qspi_message *message);
rt_err_t nu_qspi_send_then_recv(struct rt_qspi_device *device, const void *send_buf, rt_size_t send_length, void *recv_buf, rt_size_t recv_length);
rt_err_t nu_qspi_send(struct rt_qspi_device *device, const void *send_buf, rt_size_t length);
rt_err_t spinand_flash_init(struct rt_qspi_device *qspi);

extern struct nu_spinand g_spinandflash_dev;
extern rt_uint8_t spinand_flash_data_layout[SPINAND_SPARE_LAYOUT_SIZE];
extern rt_uint8_t spinand_flash_ecc_layout[SPINAND_SPARE_LAYOUT_SIZE];

#endif /* __SPINAND_H__ */
