/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-30     flybreak     first version
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "board.h"
#include "hal_data.h"

#include "drv_common.h"

#if defined(RT_USING_FAL)
    #include "fal.h"
#endif

//#define DRV_DEBUG
#define LOG_TAG                "drv.flash"
#ifdef DRV_DEBUG
    #define DBG_LVL               DBG_LOG
#else
    #define DBG_LVL               DBG_INFO
#endif /* DRV_DEBUG */
#include <rtdbg.h>

#if BSP_FEATURE_FLASH_HP_VERSION
    /* FLASH API */
    #define R_FLASH_Open    R_FLASH_HP_Open
    #define R_FLASH_Reset   R_FLASH_HP_Reset
    #define R_FLASH_Write   R_FLASH_HP_Write
    #define R_FLASH_Erase   R_FLASH_HP_Erase
    #define R_FLASH_StartUpAreaSelect   R_FLASH_HP_StartUpAreaSelect
    /* BSP_FEATURE_FLASH */
    #define FLASH_CF_WRITE_SIZE     BSP_FEATURE_FLASH_HP_CF_WRITE_SIZE

#else /* FLASH LP */
    /* FLASH API */
    #define R_FLASH_Open    R_FLASH_LP_Open
    #define R_FLASH_Reset   R_FLASH_LP_Reset
    #define R_FLASH_Write   R_FLASH_LP_Write
    #define R_FLASH_Erase   R_FLASH_LP_Erase
    #define R_FLASH_StartUpAreaSelect   R_FLASH_LP_StartUpAreaSelect
    /* BSP_FEATURE_FLASH */
    #define FLASH_CF_WRITE_SIZE     BSP_FEATURE_FLASH_LP_CF_WRITE_SIZE

#endif

int _flash_init(void)
{
    fsp_err_t err = FSP_SUCCESS;
    /* Open Flash_HP */
    err = R_FLASH_Open(&g_flash_ctrl, &g_flash_cfg);
    /* Handle Error */
    if (FSP_SUCCESS != err)
    {
        LOG_E("\r\n Flah_HP_Open API failed");
    }
    /* Setup Default  Block 0 as Startup Setup Block */
    err = R_FLASH_StartUpAreaSelect(&g_flash_ctrl, FLASH_STARTUP_AREA_BLOCK0, true);
    if (err != FSP_SUCCESS)
    {
        LOG_E("\r\n Flah_HP_StartUpAreaSelect API failed");
    }
    return 0;
}

/**
 * Read data from flash.
 * @note This operation's units is word.
 *
 * @param addr flash address
 * @param buf buffer to store read data
 * @param size read bytes size
 *
 * @return result
 */
int _flash_read(rt_uint32_t addr, rt_uint8_t *buf, size_t size)
{
    size_t i;

    for (i = 0; i < size; i++, buf++, addr++)
    {
        *buf = *(rt_uint8_t *) addr;
    }

    return size;
}

/**
 * Write data to flash.
 * @note This operation's units is word.
 * @note This operation must after erase. @see flash_erase.
 *
 * @param addr flash address
 * @param buf the write data buffer
 * @param size write bytes size
 *
 * @return result
 */
int _flash_write(rt_uint32_t addr, const rt_uint8_t *buf, size_t size)
{
    rt_err_t result      = RT_EOK;
    rt_base_t level;
    fsp_err_t err = FSP_SUCCESS;
    size_t written_size = 0;

    if (size % FLASH_CF_WRITE_SIZE)
    {
        LOG_E("Flash Write size must be an integer multiple of %d", FLASH_CF_WRITE_SIZE);
    }

    while (written_size < size)
    {
        level = rt_hw_interrupt_disable();
        R_FLASH_Reset(&g_flash_ctrl);
        /* Write code flash data*/
        err = R_FLASH_Write(&g_flash_ctrl, (uint32_t)(buf + written_size), addr + written_size, FLASH_CF_WRITE_SIZE);
        rt_hw_interrupt_enable(level);

        /* Error Handle */
        if (FSP_SUCCESS != err)
        {
            LOG_E("Write API failed");
            return -RT_EIO;
        }

        written_size += FLASH_CF_WRITE_SIZE;
    }

    if (result != RT_EOK)
    {
        return result;
    }

    return size;
}

typedef bool (*block_func)(int no, size_t addr, size_t size, void *parm1, void *parm2, void *parm3);
void fal_block_iter(const struct fal_flash_dev *flash, block_func func, void *parm1, void *parm2, void *parm3)
{
    int no = 0;
    size_t addr = flash->addr;
    for (int i = 0; i < FAL_DEV_BLK_MAX; i++)
    {
        /* blocks[i] */
        const struct flash_blk *cur_blk = &flash->blocks[i];
        if (cur_blk->size == 0 || cur_blk->count == 0)
        {
            break;
        }
        int j = cur_blk->count;
        while (j--)
        {
            /* block_no */
            if (func(no, addr, cur_blk->size, parm1, parm2, parm3) == true)
            {
                return;
            }
            addr += cur_blk->size;
            no ++;
        }
    }
}

bool calculate_block_num(int no, size_t addr, size_t size, void *erase_addr, void *erase_size, void *number)
{
    rt_uint32_t e_addr = (rt_uint32_t)erase_addr;
    size_t e_size = (size_t)erase_size;
    int *i = (int *)number;

    LOG_D("block_num: no: %d, addr is (0x%p), size: %d\n, i:%d", no, addr, size, *i);
    LOG_D("erase_addr: (0x%p), erase_size: %d\n", e_addr, e_size);
    if (e_addr >= addr && e_addr < addr + size)
    {
        (*i) ++;
        return false;
    }
    else if (addr > e_addr && addr < e_addr + e_size)
    {
        (*i) ++;
        return false;
    }
    else if (addr >= e_addr + e_size)
    {
        return true;
    }
    return false;
}

/**
 * Erase data on flash.
 * @note This operation is irreversible.
 * @note This operation's units is different which on many chips.
 *
 * @param addr flash address
 * @param size erase bytes size
 *
 * @return result
 */
#if BSP_FEATURE_FLASH_HP_VERSION
    int _flash_hp0_erase(rt_uint32_t addr, size_t size)
#else
    int _flash_lp_erase(rt_uint32_t addr, size_t size)
#endif
{
    fsp_err_t err = FSP_SUCCESS;
    rt_base_t level;
    int block_num = 0;

    if ((addr + size) > BSP_FEATURE_FLASH_CODE_FLASH_START + BSP_ROM_SIZE_BYTES)
    {
        LOG_E("ERROR: erase outrange flash size! addr is (0x%p)\n", (void *)(addr + size));
        return -RT_EINVAL;
    }

    if (size < 1)
    {
        return -RT_EINVAL;
    }

    level = rt_hw_interrupt_disable();
    R_FLASH_Reset(&g_flash_ctrl);

    fal_block_iter(&_onchip_flash_hp0, &calculate_block_num, (void *)addr, (void *)size, &block_num);

    /* Erase Block */
#if BSP_FEATURE_FLASH_HP_VERSION
    err = R_FLASH_Erase(&g_flash_ctrl,
                        RT_ALIGN_DOWN(addr, BSP_FEATURE_FLASH_HP_CF_REGION0_BLOCK_SIZE),
                        block_num);
#else
    err = R_FLASH_Erase(&g_flash_ctrl,
                        RT_ALIGN_DOWN(addr, BSP_FEATURE_FLASH_LP_CF_BLOCK_SIZE),
                        ((size - 1) / BSP_FEATURE_FLASH_LP_CF_BLOCK_SIZE + 1));
#endif
    rt_hw_interrupt_enable(level);

    if (err != FSP_SUCCESS)
    {
        LOG_E("Erase failed:addr (0x%p), size %d", (void *)addr, size);
        return -RT_EIO;
    }

    LOG_D("erase done: addr (0x%p), size %d", (void *)addr, size);
    return size;
}

#if defined(RT_USING_FAL)

#if BSP_FEATURE_FLASH_HP_VERSION

static int fal_flash_hp0_read(long offset, rt_uint8_t *buf, size_t size);
static int fal_flash_hp0_write(long offset, const rt_uint8_t *buf, size_t size);
static int fal_flash_hp0_erase(long offset, size_t size);

const struct fal_flash_dev _onchip_flash_hp0 =
{
    "onchip_flash_hp0",
    BSP_FEATURE_FLASH_CODE_FLASH_START,
    BSP_ROM_SIZE_BYTES,
    BSP_FEATURE_FLASH_HP_CF_REGION0_BLOCK_SIZE,
    {
        _flash_init,
        fal_flash_hp0_read,
        fal_flash_hp0_write,
        fal_flash_hp0_erase
    },
    (BSP_FEATURE_FLASH_HP_CF_WRITE_SIZE * 8)
    , {
        {
            .size = BSP_FEATURE_FLASH_HP_CF_REGION0_BLOCK_SIZE,
            .count = BSP_FEATURE_FLASH_HP_CF_REGION0_SIZE / BSP_FEATURE_FLASH_HP_CF_REGION0_BLOCK_SIZE
        },
        {
            .size = BSP_FEATURE_FLASH_HP_CF_REGION1_BLOCK_SIZE,
            .count = (BSP_ROM_SIZE_BYTES - BSP_FEATURE_FLASH_HP_CF_REGION0_SIZE) / BSP_FEATURE_FLASH_HP_CF_REGION1_BLOCK_SIZE
        },
    }
};

/* code flash region0 */
static int fal_flash_hp0_read(long offset, rt_uint8_t *buf, size_t size)
{
    return _flash_read(_onchip_flash_hp0.addr + offset, buf, size);
}

static int fal_flash_hp0_write(long offset, const rt_uint8_t *buf, size_t size)
{
    return _flash_write(_onchip_flash_hp0.addr + offset, buf, size);
}

static int fal_flash_hp0_erase(long offset, size_t size)
{
    return _flash_hp0_erase(_onchip_flash_hp0.addr + offset, size);
}

#else /* flash lp code flash */

static int fal_flash_lp_read(long offset, rt_uint8_t *buf, size_t size);
static int fal_flash_lp_write(long offset, const rt_uint8_t *buf, size_t size);
static int fal_flash_lp_erase(long offset, size_t size);

const struct fal_flash_dev _onchip_flash_lp =
{
    "onchip_flash_lp",
    FLASH_START_ADDRESS,
    BSP_ROM_SIZE_BYTES,
    BSP_FEATURE_FLASH_LP_CF_BLOCK_SIZE,
    {
        _flash_init,
        fal_flash_lp_read,
        fal_flash_lp_write,
        fal_flash_lp_erase
    },
    (BSP_FEATURE_FLASH_LP_CF_WRITE_SIZE * 8)
};

static int fal_flash_lp_read(long offset, rt_uint8_t *buf, size_t size)
{
    return _flash_read(_onchip_flash_lp.addr + offset, buf, size);
}

static int fal_flash_lp_write(long offset, const rt_uint8_t *buf, size_t size)
{
    return _flash_write(_onchip_flash_lp.addr + offset, buf, size);
}

static int fal_flash_lp_erase(long offset, size_t size)
{
    return _flash_lp_erase(_onchip_flash_lp.addr + offset, size);
}

#endif

#endif
