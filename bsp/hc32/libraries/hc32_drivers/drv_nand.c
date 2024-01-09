/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-01     CDT          first version
 */


/*******************************************************************************
 * Include files
 ******************************************************************************/
#include <rtthread.h>


#if defined (BSP_USING_EXMC)
#if defined (BSP_USING_NAND)

#include "drv_nand.h"
#include "board_config.h"
#include "nand_port.h"

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/
/* rthw nand */
struct rthw_nand
{
    struct rt_mtd_nand_device nand_dev;

    rt_uint32_t nfc_bank;
    rt_uint32_t id;
    struct rt_mutex lock;
};

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
//#define DRV_DEBUG
#define LOG_TAG "drv.nand"
#include <drv_log.h>

/* Nand status */
#define NAND_BUSY                   0x00000000U
#define NAND_FAIL                   0x00000001U
#define NAND_READY                  0x00000040U
#define NAND_VALID_ADDRESS          0x00000100U
#define NAND_INVALID_ADDRESS        0x00000200U
#define NAND_TIMEOUT_ERROR          0x00000400U

#define NAND_ERASE_TIMEOUT          2000000UL
#define NAND_READ_TIMEOUT           2000000UL
#define NAND_WRITE_TIMEOUT          2000000UL
#define NAND_RESET_TIMEOUT          2000000UL

#define NAND_ECC_SECTOR_SIZE        512UL
#define NAND_ECC_CODE_SIZE          ((NAND_EXMC_NFC_ECC_MD == EXMC_NFC_1BIT_ECC) ? 3UL : 8UL)
#define NAND_SPARE_FREE_SIZE        (NAND_SPARE_AREA_SIZE - (NAND_BYTES_PER_PAGE / NAND_ECC_SECTOR_SIZE) * NAND_ECC_CODE_SIZE)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
#if defined (BSP_USING_NAND)
    extern rt_err_t rt_hw_board_nand_init(void);
#endif

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
struct rthw_nand _hw_nand;

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

static rt_err_t _nand_verify_clock_frequency(void)
{
    rt_err_t ret = RT_EOK;

#if defined (HC32F4A0)
    /* EXCLK max frequency for Nand: 60MHz */
    if (CLK_GetBusClockFreq(CLK_BUS_EXCLK) > (60 * 1000000))
    {
        ret = -RT_ERROR;
    }
#endif

    return ret;
}

static rt_err_t _nand_init(struct rt_mtd_nand_device *device)
{
    rt_uint8_t au8DevId[4];
    rt_err_t ret = -RT_ERROR;
    stc_exmc_nfc_init_t nfc_init_params;
    struct rthw_nand *hw_nand = (struct rthw_nand *)device;
    rt_uint16_t oob_free = (rt_uint16_t)(NAND_SPARE_AREA_SIZE - \
                                         (NAND_BYTES_PER_PAGE / NAND_ECC_SECTOR_SIZE) * NAND_ECC_CODE_SIZE);

    RT_ASSERT(device != RT_NULL);

    hw_nand->nfc_bank = NAND_EXMC_NFC_BANK;

    /* verify nand clock frequency */
    if (_nand_verify_clock_frequency() != RT_EOK)
    {
        LOG_E("EXMC clock frequency is over limit for NAND!");
        return -RT_ERROR;
    }

    /* Initialize nand port.*/
    rt_hw_board_nand_init();

    /* Enable NFC module clock */
    FCG_Fcg3PeriphClockCmd(FCG3_PERIPH_NFC, ENABLE);

    /* Enable NFC. */
    EXMC_NFC_Cmd(ENABLE);

    /* Configure NFC base parameters. */
    nfc_init_params.u32OpenPage = EXMC_NFC_OPEN_PAGE_DISABLE;
    nfc_init_params.stcBaseConfig.u32CapacitySize = NAND_EXMC_NFC_BANK_CAPACITY;
    nfc_init_params.stcBaseConfig.u32MemoryWidth = NAND_EXMC_NFC_MEMORY_WIDTH;
    nfc_init_params.stcBaseConfig.u32BankNum = EXMC_NFC_1BANK;
    nfc_init_params.stcBaseConfig.u32PageSize = NAND_EXMC_NFC_PAGE_SIZE;
    nfc_init_params.stcBaseConfig.u32WriteProtect = EXMC_NFC_WR_PROTECT_DISABLE;
    nfc_init_params.stcBaseConfig.u32EccMode = NAND_EXMC_NFC_ECC_MD;
    nfc_init_params.stcBaseConfig.u32RowAddrCycle = NAND_EXMC_NFC_ROW_ADDR_CYCLE;
    nfc_init_params.stcBaseConfig.u8SpareSizeForUserData = (rt_uint8_t)(oob_free >> 2);

    /* Configure NFC timing */
    nfc_init_params.stcTimingReg0.u32TS = NAND_TS;
    nfc_init_params.stcTimingReg0.u32TWP = NAND_TWP;
    nfc_init_params.stcTimingReg0.u32TRP = NAND_TRP;

    nfc_init_params.stcTimingReg0.u32TH = NAND_TH;

    nfc_init_params.stcTimingReg1.u32TWH = NAND_TWH;
    nfc_init_params.stcTimingReg1.u32TRH = NAND_TRH;
    nfc_init_params.stcTimingReg1.u32TRR = NAND_TRR;
    nfc_init_params.stcTimingReg1.u32TWB = NAND_TWB;

    nfc_init_params.stcTimingReg2.u32TCCS = NAND_TCCS;
    nfc_init_params.stcTimingReg2.u32TWTR = NAND_TWTR;
    nfc_init_params.stcTimingReg2.u32TRTW = NAND_TRTW;
    nfc_init_params.stcTimingReg2.u32TADL = NAND_TADL;
    if (LL_OK == EXMC_NFC_Init(&nfc_init_params))
    {
        /* Reset NFC device. */
        if (LL_OK == EXMC_NFC_Reset(hw_nand->nfc_bank, NAND_RESET_TIMEOUT))
        {
            EXMC_NFC_ReadId(hw_nand->nfc_bank, 0UL, au8DevId, sizeof(au8DevId), NAND_READ_TIMEOUT);
            hw_nand->id = (((rt_uint32_t)au8DevId[3]) << 24 | ((rt_uint32_t)au8DevId[2]) << 16 | \
                           ((rt_uint32_t)au8DevId[1]) << 8  | (rt_uint32_t)au8DevId[0]);

            LOG_D("Nand Flash ID = 0x%02X,0x%02X,0x%02X,0x%02X",
                  au8DevId[0], au8DevId[1], au8DevId[2], au8DevId[3]);

            ret = RT_EOK;
        }
    }

    return ret;
}

static rt_err_t _nand_wait_ready(rt_uint32_t nfc_bank, rt_uint32_t timeout)
{
    rt_err_t ret = RT_EOK;
    rt_uint32_t to = 0UL;
    rt_uint32_t status = 0UL;

    do
    {
        /* Block checking flag if timeout value is NAND_WRITE_TIMEOUT */
        if (to++ > timeout)
        {
            ret = -RT_ETIMEOUT;
            LOG_E("get nand status timeout!");
            break;
        }

        status = EXMC_NFC_ReadStatus(nfc_bank);
    }
    while (0UL == (status & NAND_READY));

    if (RT_ETIMEOUT != ret)
    {
        if (0UL != (status & NAND_FAIL))
        {
            ret = -RT_ERROR;
            LOG_E("nand status error!");
        }
    }

    return ret;
}

rt_err_t _nand_erase_block(struct rt_mtd_nand_device *device, rt_uint32_t block)
{
    rt_err_t ret = -RT_ERROR;
    rt_uint32_t block_num;
    struct rthw_nand *hw_nand = (struct rthw_nand *)device;

    RT_ASSERT(device != RT_NULL);

    block = block + device->block_start;
    block_num = block << 6;

    rt_mutex_take(&hw_nand->lock, RT_WAITING_FOREVER);

    if (LL_OK == EXMC_NFC_EraseBlock(hw_nand->nfc_bank,  block_num, NAND_ERASE_TIMEOUT))
    {
        if (_nand_wait_ready(hw_nand->nfc_bank, NAND_ERASE_TIMEOUT) == RT_EOK)
        {
            ret = RT_MTD_EOK;
        }
    }

    rt_mutex_release(&hw_nand->lock);

    return ret;
}

static rt_err_t _nand_check_block(struct rt_mtd_nand_device *device, rt_uint32_t block)
{
    RT_ASSERT(device != RT_NULL);
    return (RT_MTD_EOK);
}

static rt_err_t _nand_mark_badblock(struct rt_mtd_nand_device *device, rt_uint32_t block)
{
    RT_ASSERT(device != RT_NULL);
    return (RT_MTD_EOK);
}

/* read nand flash id */
static rt_err_t _nand_read_id(struct rt_mtd_nand_device *device)
{
    rt_uint8_t device_id[4];
    struct rthw_nand *hw_nand = (struct rthw_nand *)device;

    RT_ASSERT(device != RT_NULL);

    EXMC_NFC_ReadId(hw_nand->nfc_bank, 0UL, device_id, sizeof(device_id), NAND_READ_TIMEOUT);
    hw_nand->id = (((rt_uint32_t)device_id[3]) << 24 | ((rt_uint32_t)device_id[2]) << 16 | \
                   ((rt_uint32_t)device_id[1]) << 8  | (rt_uint32_t)device_id[0]);

    LOG_D("Nand Flash ID: Manufacturer ID = 0x%02X, Device ID=[0x%02X,0x%02X,0x%02X]",
          device_id[0], device_id[1], device_id[2], device_id[3]);

    return RT_EOK;
}

static rt_ssize_t _nand_read_page(struct rt_mtd_nand_device *device,
                                  rt_off_t page,
                                  rt_uint8_t *data,
                                  rt_uint32_t data_len,
                                  rt_uint8_t *spare,
                                  rt_uint32_t spare_len)
{
    rt_err_t result = RT_EOK;
    struct rthw_nand *hw_nand = (struct rthw_nand *)device;

    RT_ASSERT(device != RT_NULL);

    page = page + device->block_start * device->pages_per_block;
    if (page / device->pages_per_block > device->block_end)
    {
        return -RT_EIO;
    }

    rt_mutex_take(&hw_nand->lock, RT_WAITING_FOREVER);

    if ((data != RT_NULL) && (data_len != 0UL))
    {
        /* not an integer multiple of NAND ECC SECTOR SIZE, no ECC checks */
        if ((data_len % NAND_ECC_SECTOR_SIZE) != 0UL)
        {
            if (LL_OK != EXMC_NFC_ReadPageMeta(hw_nand->nfc_bank, page, data, data_len, NAND_READ_TIMEOUT))
            {
                result = -RT_EIO;
                goto _exit;
            }
        }
        else
        {
            if (LL_OK != EXMC_NFC_ReadPageHwEcc(hw_nand->nfc_bank, page, data, data_len, NAND_READ_TIMEOUT))
            {
                result = -RT_EIO;
                goto _exit;
            }
            else
            {
                if (SET == EXMC_NFC_GetStatus(EXMC_NFC_FLAG_ECC_UNCORRECTABLE_ERR))
                {
                    EXMC_NFC_ClearStatus(EXMC_NFC_FLAG_ECC_UNCORRECTABLE_ERR);
                    result = RT_MTD_EECC;
                    goto _exit;
                }
            }
        }
    }

    if ((spare != RT_NULL) && (spare_len != 0UL))
    {
        RT_ASSERT(spare_len <= device->oob_free);

        if (LL_OK != EXMC_NFC_Read(hw_nand->nfc_bank, page, (rt_uint32_t)device->page_size,
                                   (rt_uint32_t *)spare, (spare_len >> 2), DISABLE, NAND_READ_TIMEOUT))
        {
            result = -RT_EIO;
            goto _exit;
        }
    }

_exit:
    rt_mutex_release(&hw_nand->lock);

    return result;
}

static rt_ssize_t _nand_write_page(struct rt_mtd_nand_device *device,
                                   rt_off_t page,
                                   const rt_uint8_t *data,
                                   rt_uint32_t data_len,
                                   const rt_uint8_t *spare,
                                   rt_uint32_t spare_len)
{
    rt_err_t result = RT_EOK;
    struct rthw_nand *hw_nand = (struct rthw_nand *)device;

    RT_ASSERT(device != RT_NULL);

    page = page + device->block_start * device->pages_per_block;
    if (page / device->pages_per_block > device->block_end)
    {
        return -RT_EIO;
    }

    rt_mutex_take(&hw_nand->lock, RT_WAITING_FOREVER);

    if ((data != RT_NULL) && (data_len != 0UL))
    {
        if ((data_len % NAND_ECC_SECTOR_SIZE) != 0UL)
        {
            if (LL_OK != EXMC_NFC_WritePageMeta(hw_nand->nfc_bank, page, data, data_len, NAND_WRITE_TIMEOUT))
            {
                result = -RT_EIO;
                goto _exit;
            }
        }
        else
        {
            if (LL_OK != EXMC_NFC_WritePageHwEcc(hw_nand->nfc_bank, page, data, data_len, NAND_WRITE_TIMEOUT))
            {
                result = -RT_EIO;
                goto _exit;
            }
        }

        if (RT_EOK != _nand_wait_ready(hw_nand->nfc_bank, NAND_WRITE_TIMEOUT))
        {
            result = -RT_EIO;
            goto _exit;
        }
    }

    if ((spare != RT_NULL) && (spare_len != 0UL))
    {
        RT_ASSERT(spare_len <= device->oob_free);

        if (LL_OK != EXMC_NFC_Write(hw_nand->nfc_bank, page, (rt_uint32_t)device->page_size,
                                    (rt_uint32_t *)spare, (spare_len >> 2), DISABLE, NAND_WRITE_TIMEOUT))
        {
            result = -RT_EIO;
            goto _exit;
        }

        if (RT_EOK != _nand_wait_ready(hw_nand->nfc_bank, NAND_WRITE_TIMEOUT))
        {
            result = -RT_EIO;
            goto _exit;
        }
    }

_exit:
    rt_mutex_release(&hw_nand->lock);

    return result;
}

rt_err_t _nand_move_page(struct rt_mtd_nand_device *device, rt_off_t src_page, rt_off_t dst_page)
{
    RT_ASSERT(device != RT_NULL);
    return (RT_MTD_EOK);
}

static const struct rt_mtd_nand_driver_ops _ops =
{
    _nand_read_id,
    _nand_read_page,
    _nand_write_page,
    _nand_move_page,
    _nand_erase_block,
    _nand_check_block,
    _nand_mark_badblock,
};

int rt_hw_nand_init(void)
{
    rt_err_t result = RT_EOK;
    struct rt_mtd_nand_device *nand_dev = &_hw_nand.nand_dev;

    result = _nand_init(nand_dev);
    if (result != RT_EOK)
    {
        LOG_D("nand flash init error!");
        return -RT_ERROR;
    }
    rt_mutex_init(&_hw_nand.lock, "nand", RT_IPC_FLAG_PRIO);

    nand_dev->page_size       = NAND_BYTES_PER_PAGE;
    nand_dev->pages_per_block = NAND_PAGES_PER_BLOCK;
    nand_dev->plane_num       = NAND_PLANE_PER_DEVICE;
    nand_dev->oob_size        = NAND_SPARE_AREA_SIZE;
    nand_dev->oob_free        = (rt_uint16_t)(NAND_SPARE_AREA_SIZE - (NAND_BYTES_PER_PAGE / NAND_ECC_SECTOR_SIZE) * NAND_ECC_CODE_SIZE);
    nand_dev->block_total     = NAND_DEVICE_BLOCKS;
    nand_dev->block_start     = 0;
    nand_dev->block_end       = nand_dev->block_total - 1UL;
    nand_dev->ops = &_ops;

    result = rt_mtd_nand_register_device("nand", nand_dev);
    if (result != RT_EOK)
    {
        rt_device_unregister(&nand_dev->parent);
        return -RT_ERROR;
    }

    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_hw_nand_init);

#ifdef DRV_DEBUG
#ifdef FINSH_USING_MSH
static int _nand_test(void)
{
    rt_err_t ret;
    rt_uint32_t i = 0;
    rt_uint32_t err_count = 0;
    rt_uint32_t page;
    rt_uint32_t block;

    rt_uint8_t *page_rbuf;
    rt_uint8_t *page_wbuf;
    rt_uint8_t *page_oob_free_wbuf;
    rt_uint8_t *page_oob_free_rbuf;

    static rt_device_t nand;
    static struct rt_mtd_nand_device *mtd_nand;

    nand = rt_device_find("nand");
    if (RT_NULL == nand)
    {
        LOG_E("nand device not found");
        return -RT_ERROR;
    }

    ret = rt_device_open(nand, RT_DEVICE_FLAG_RDWR);
    if (ret != RT_EOK)
    {
        LOG_E("nand device failed to open");
        return -RT_ERROR;
    }

    mtd_nand = (struct rt_mtd_nand_device *)nand;

    page_rbuf = rt_malloc(mtd_nand->page_size);
    if (page_rbuf == RT_NULL)
    {
        LOG_E("out of memory!");
        return -RT_ERROR;
    }

    page_wbuf = rt_malloc(mtd_nand->page_size);
    if (page_wbuf == RT_NULL)
    {
        rt_free(page_rbuf);
        LOG_E("out of memory!");
        return -RT_ERROR;
    }

    page_oob_free_rbuf = rt_malloc(mtd_nand->oob_free);
    if (page_oob_free_rbuf == RT_NULL)
    {
        rt_free(page_rbuf);
        rt_free(page_wbuf);
        LOG_E("out of memory!");
        return -RT_ERROR;
    }

    page_oob_free_wbuf = rt_malloc(mtd_nand->oob_free);
    if (page_oob_free_wbuf == RT_NULL)
    {
        rt_free(page_rbuf);
        rt_free(page_wbuf);
        rt_free(page_oob_free_rbuf);
        LOG_E("out of memory!");
        return -RT_ERROR;
    }

    /* Fill the buffer to send */
    for (i = 0; i < mtd_nand->page_size; i++)
    {
        page_wbuf[i] = i;
    }

    for (i = 0; i < mtd_nand->oob_free; i++)
    {
        page_oob_free_wbuf[i] = i;
    }

    /* read ID */
    _nand_read_id(mtd_nand);

    /* test page */
    page = 0UL;

    /* erase the NAND Block */
    block = page >> 6;
    ret = _nand_erase_block(mtd_nand, block);
    if (ret == RT_EOK)
    {
        LOG_D("erase block%d: ok", block);
    }
    else
    {
        LOG_E("erase block%d: error", block);
        err_count++;
    }

    /* Write data to NAND memory page 0 */
    ret = _nand_write_page(mtd_nand, page, page_wbuf, mtd_nand->page_size, page_oob_free_wbuf, mtd_nand->oob_free);
    if (ret == RT_EOK)
    {
        LOG_D("_nand_write_page page%d(include oob free area): ok", page);
    }
    else
    {
        LOG_E("_nand_write_page page%d(include oob free area): error", page);
        err_count++;
    }

    /* Read data from NAND memory page 0 */
    ret = _nand_read_page(mtd_nand, page, page_rbuf, mtd_nand->page_size, page_oob_free_rbuf, mtd_nand->oob_free);
    if (ret == RT_EOK)
    {
        LOG_D("_nand_read_page page%d(include oob free area): ok", page);
    }
    else if (ret == -RT_MTD_EECC)
    {
        LOG_E("_nand_read_page page%d(include oob free area): ECC error", page);
        err_count++;
    }
    else
    {
        LOG_E("_nand_read_page page%d(include oob free area): error", page);
        err_count++;
    }

    if (rt_memcmp(page_rbuf, page_wbuf, mtd_nand->page_size) == 0)
    {
        LOG_D("rt_memcmp page%d data consistency: ok", page);
    }
    else
    {
        LOG_E("rt_memcmp page%d data consistency: error", page);
        err_count++;
    }

    if (rt_memcmp(page_oob_free_rbuf, page_oob_free_wbuf, mtd_nand->oob_free) == 0)
    {
        LOG_D("rt_memcmp page%d oob_free data consistency: ok", page);
    }
    else
    {
        LOG_E("rt_memcmp page%d oob_free data consistency: error", page);
        err_count++;
    }

    ret = rt_device_close(nand);
    if (ret != RT_EOK)
    {
        LOG_E("nand device failed to close");
        err_count++;
    }

    rt_free(page_rbuf);
    rt_free(page_wbuf);
    rt_free(page_oob_free_rbuf);
    rt_free(page_oob_free_wbuf);

    return (err_count == 0UL) ? RT_EOK : -RT_ERROR;
}
MSH_CMD_EXPORT(_nand_test, nand test)
#endif /* FINSH_USING_MSH */
#endif /* DRV_DEBUG */

#endif /* BSP_USING_NAND */
#endif /* BSP_USING_EXMC */
