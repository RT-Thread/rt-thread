/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-06-30     thread-liu   first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#ifdef BSP_USING_NAND

#define DRV_DEBUG
#define LOG_TAG     "drv.nand"
#include <drv_log.h>
#include "drv_nand.h"

#define NAND_RB_PIN GET_PIN(D, 6)

static rt_uint32_t ecc_rdbuf[NAND_MAX_PAGE_SIZE/NAND_ECC_SECTOR_SIZE];
static rt_uint32_t ecc_hdbuf[NAND_MAX_PAGE_SIZE/NAND_ECC_SECTOR_SIZE];
struct rthw_fmc
{
    rt_uint32_t id;
    struct rt_mutex lock;
};
static struct rthw_fmc _device = {0};

static void rt_hw_nand_gpio_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

    if (IS_ENGINEERING_BOOT_MODE())
    {
        PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_FMC;
        PeriphClkInit.AdcClockSelection = RCC_FMCCLKSOURCE_ACLK;
        if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
        {
            Error_Handler();
        }
    }
    __HAL_RCC_FMC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();

    /* PD6 R/B */
    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    /* PG9 NCE */
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

    /* PD0,1,4,5,11,12,14,15 */
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5 |
                          GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_14 | GPIO_PIN_15;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    /* PE7,8,9,10 */
    GPIO_InitStruct.Pin = GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
}

/* nand delay */
static void rt_hw_nand_delay(volatile uint32_t i)
{
    while (i > 0)
    {
        i--;
    }
}

/* read nand flash status */
static rt_err_t rt_hw_nand_read_status(void)
{
    rt_err_t result = RT_EOK;

    NAND_CMD_AREA = NAND_READSTA;

    rt_hw_nand_delay(NAND_TWHR_DELAY);

    result = NAND_ADDR_AREA;

    return result;
}

/* wait nand flash read */
static rt_err_t rt_hw_nand_wait_ready(void)
{
    rt_err_t result = RT_EOK;
    static uint32_t time = 0;

    while (1)
    {
        result = rt_hw_nand_read_status();

        if (result & NAND_READY)
        {
            break;
        }
        time++;
        if (time >= 0X1FFFFFFF)
        {
            return RT_ETIMEOUT;
        }
    }

    return RT_EOK;
}

/* set nand mode */
static rt_err_t rt_hw_nand_set_mode(uint8_t mode)
{
    NAND_CMD_AREA = NAND_FEATURE;
    NAND_DATA_AREA = 0x01;
    NAND_ADDR_AREA = mode;
    NAND_ADDR_AREA = 0;
    NAND_ADDR_AREA = 0;
    NAND_ADDR_AREA = 0;

    if (rt_hw_nand_wait_ready() == RT_EOK)
    {
        return RT_EOK;
    }
    else
    {
        return RT_ERROR;
    }
}

/* reset nand flash */
static rt_err_t rt_hw_nand_reset(void)
{
    NAND_CMD_AREA = NAND_RESET;

    if (rt_hw_nand_wait_ready() == RT_EOK)
    {
        return RT_EOK; /* success */
    }
    else
    {
        return RT_ERROR;
    }
}

/* read nand flash id */
static rt_err_t _read_id(struct rt_mtd_nand_device *device)
{
    RT_ASSERT(device != RT_NULL);

    uint8_t deviceid[5];

    NAND_CMD_AREA = NAND_READID; /* read id command */
    NAND_DATA_AREA = 0x00;

    deviceid[0] = NAND_ADDR_AREA; /* Byte 0 */
    deviceid[1] = NAND_ADDR_AREA; /* Byte 1 */
    deviceid[2] = NAND_ADDR_AREA; /* Byte 2 */
    deviceid[3] = NAND_ADDR_AREA; /* Byte 3 */
    deviceid[4] = NAND_ADDR_AREA; /* Byte 4 */

    _device.id = ((uint32_t)deviceid[4]) << 24 | ((uint32_t)deviceid[3]) << 16 | ((uint32_t)deviceid[2]) << 8 | deviceid[1];

    LOG_D("nand id: 0x%08x", _device.id);

    return RT_EOK;
}

static rt_uint8_t rt_hw_nand_ecc_check(rt_uint32_t generatedEcc, rt_uint32_t readEcc, rt_uint8_t* data)
{
#define ECC_MASK28    0x0FFFFFFF          /* 28 valid ECC parity bits. */
#define ECC_MASK      0x05555555          /* 14 ECC parity bits.       */

    rt_uint32_t count, bitNum, byteAddr;
    rt_uint32_t mask;
    rt_uint32_t syndrome;
    rt_uint32_t eccP;                            /* 14 even ECC parity bits. */
    rt_uint32_t eccPn;                           /* 14 odd ECC parity bits.  */

    syndrome = (generatedEcc ^ readEcc) & ECC_MASK28;

    if (syndrome == 0)
    {
        return (RT_EOK);                     /* No errors in data. */
    }

    eccPn = syndrome & ECC_MASK;              /* Get 14 odd parity bits.  */
    eccP  = (syndrome >> 1) & ECC_MASK;       /* Get 14 even parity bits. */

    if ((eccPn ^ eccP) == ECC_MASK)           /* 1-bit correctable error ? */
    {
        bitNum = (eccP & 0x01) |
                 ((eccP >> 1) & 0x02) |
                 ((eccP >> 2) & 0x04);
        LOG_D("ECC bit %d\n",bitNum);
        byteAddr = ((eccP >> 6) & 0x001) |
                   ((eccP >> 7) & 0x002) |
                   ((eccP >> 8) & 0x004) |
                   ((eccP >> 9) & 0x008) |
                   ((eccP >> 10) & 0x010) |
                   ((eccP >> 11) & 0x020) |
                   ((eccP >> 12) & 0x040) |
                   ((eccP >> 13) & 0x080) |
                   ((eccP >> 14) & 0x100) |
                   ((eccP >> 15) & 0x200) |
                   ((eccP >> 16) & 0x400) ;

        data[ byteAddr ] ^= 1 << bitNum;

        return RT_EOK;
    }

    /* Count number of one's in the syndrome. */
    count = 0;
    mask  = 0x00800000;
    while (mask)
    {
        if (syndrome & mask)
            count++;
        mask >>= 1;
    }

    if (count == 1)           /* Error in the ECC itself. */
        return RT_EIO;

    return RT_EIO;       /* Unable to correct data. */

#undef ECC_MASK
#undef ECC_MASK24
}

static rt_err_t _read_page(struct rt_mtd_nand_device *device,
                           rt_off_t page,
                           rt_uint8_t *data,
                           rt_uint32_t data_len,
                           rt_uint8_t *spare,
                           rt_uint32_t spare_len)
{
    RT_ASSERT(device != RT_NULL);

    rt_uint32_t index, i, tickstart, eccnum;
    rt_err_t result;
    rt_uint8_t *p = RT_NULL;

    page = page + device->block_start * device->pages_per_block;
    if (page / device->pages_per_block > device->block_end)
    {
        return -RT_EIO;
    }

    rt_mutex_take(&_device.lock, RT_WAITING_FOREVER);
    if (data && data_len)
    {
        NAND_CMD_AREA  = NAND_AREA_A;
        NAND_DATA_AREA = (rt_uint8_t)0;
        NAND_DATA_AREA = (rt_uint8_t)(0 >> 8);
        NAND_DATA_AREA = (rt_uint8_t)page;
        NAND_DATA_AREA = (rt_uint8_t)(page >> 8);
        NAND_DATA_AREA = (rt_uint8_t)(page >> 16);
        NAND_CMD_AREA  = NAND_AREA_TRUE1;

        rt_hw_nand_delay(10);

        /* not an integer multiple of NAND ECC SECTOR SIZE, no ECC checks*/
        if (data_len % NAND_ECC_SECTOR_SIZE)
        {
            for (i = 0; i < data_len; i++)
            {
                *data++ = NAND_ADDR_AREA;
            }
        }
        else
        {
            eccnum = data_len/NAND_ECC_SECTOR_SIZE;
            p = data;
            for (index = 0; index < 4; index++)
            {
                FMC_Bank3_R->PCR |= 1<<6;   /* enable ecc */

                for (i = 0; i < NAND_ECC_SECTOR_SIZE; i++)
                {
                    *data++ = NAND_ADDR_AREA;
                }
                /* Get tick */
                tickstart = rt_tick_get();
                /* Wait until FIFO is empty */
                while ((FMC_Bank3_R->SR & (1 << 6)) == RESET)
                {
                    /* Check for the Timeout */
                    if ((rt_tick_get() - tickstart) > 10000)
                    {
                        result = RT_ETIMEOUT;
                        goto _exit;
                    }
                }
                ecc_hdbuf[index] = FMC_Bank3_R->HECCR;  /* read hardware ecc */
                FMC_Bank3_R->PCR &= ~(1<<6);            /* disable ecc */
            }
            i = device->page_size + 0x10;

            rt_hw_nand_delay(10);

            NAND_CMD_AREA  = 0x05;
            NAND_DATA_AREA = (rt_uint8_t)i;
            NAND_DATA_AREA = (rt_uint8_t)(i>>8);
            NAND_CMD_AREA  = 0xE0;

            rt_hw_nand_delay(10);

            data =(rt_uint8_t*)&ecc_rdbuf[0];
            for (i = 0; i < 4*eccnum; i++)
            {
                *data++ = NAND_ADDR_AREA;
            }
            /* check ecc */
            for(i  = 0;  i< eccnum; i++)
            {
                if(ecc_rdbuf[i] != ecc_hdbuf[i])
                {
                    result = rt_hw_nand_ecc_check(ecc_hdbuf[i], ecc_rdbuf[i], p + NAND_ECC_SECTOR_SIZE*i);
                    if (result != RT_EOK)
                    {
                        goto _exit;
                    }
                }
            }
        }
    }
    if (spare && spare_len)
    {
        NAND_CMD_AREA  = NAND_AREA_A;
        NAND_DATA_AREA = (rt_uint8_t)0;
        NAND_DATA_AREA = (rt_uint8_t)(0 >> 8);
        NAND_DATA_AREA = (rt_uint8_t)page;
        NAND_DATA_AREA = (rt_uint8_t)(page >> 8);
        NAND_DATA_AREA = (rt_uint8_t)(page >> 16);
        NAND_CMD_AREA  = NAND_AREA_TRUE1;
        rt_thread_delay(10);

        for (i = 0; i < spare_len; i ++)
        {
            *spare++ = NAND_ADDR_AREA;
        }
    }

    if (rt_hw_nand_wait_ready() != RT_EOK)
    {
        result = RT_ETIMEOUT;
        goto _exit;
    }

_exit:
    rt_mutex_release(&_device.lock);

    return result;
}

static rt_err_t _write_page(struct rt_mtd_nand_device *device,
                            rt_off_t page,
                            const rt_uint8_t *data,
                            rt_uint32_t data_len,
                            const rt_uint8_t *spare,
                            rt_uint32_t spare_len)
{
    RT_ASSERT(device != RT_NULL);

    rt_err_t result = RT_EOK;
    rt_uint32_t eccnum;
    rt_uint32_t i, index;
    rt_uint32_t tickstart = 0;

    page = page + device->block_start * device->pages_per_block;
    if (page / device->pages_per_block > device->block_end)
    {
        return -RT_EIO;
    }

    rt_mutex_take(&_device.lock, RT_WAITING_FOREVER);

    if (data && data_len)
    {
        NAND_CMD_AREA = NAND_WRITE0;

        NAND_DATA_AREA = (rt_uint8_t)0;
        NAND_DATA_AREA = (rt_uint8_t)(0 >> 8);
        NAND_DATA_AREA = (rt_uint8_t)(page & 0xFF);
        NAND_DATA_AREA = (rt_uint8_t)(page >> 8);
        NAND_DATA_AREA = (rt_uint8_t)(page >> 16);

        rt_hw_nand_delay(10);

        if (data_len % NAND_ECC_SECTOR_SIZE)
        {
            /* read nand flash */
            for (i = 0; i < data_len; i++)
            {
                NAND_ADDR_AREA = *data++;
            }
        }
        else
        {
            eccnum   = data_len/NAND_ECC_SECTOR_SIZE;
            for (index = 0; index < eccnum; index++)
            {
                FMC_Bank3_R->PCR |= 1<<6;               /* enable ecc */

                for (i = 0; i < NAND_ECC_SECTOR_SIZE; i++)
                {
                    NAND_ADDR_AREA = *data++;
                }
                /* Get tick */
                tickstart = rt_tick_get();
                /* Wait until FIFO is empty */
                while ((FMC_Bank3_R->SR & (1 << 6)) == RESET)
                {
                    /* Check for the Timeout */
                    if ((rt_tick_get() - tickstart) > 10000)
                    {
                        result = RT_ETIMEOUT;
                        goto _exit;
                    }
                }
                ecc_hdbuf[index] = FMC_Bank3_R->HECCR;  /* read hardware ecc */
                FMC_Bank3_R->PCR &= ~(1<<6);            /* disable ecc */
            }

            i = device->page_size + 0x10;
            rt_hw_nand_delay(10);
            NAND_CMD_AREA  = 0x85;
            NAND_DATA_AREA = (rt_uint8_t)i;
            NAND_DATA_AREA = (rt_uint8_t)(i>>8);
            rt_hw_nand_delay(10);

            data = (uint8_t*)&ecc_hdbuf[0];

            for (index = 0; index < eccnum; index++)
            {
                for (i = 0; i < 4; i++)
                {
                    NAND_ADDR_AREA = *data++;
                }
            }
        }
    }
    NAND_CMD_AREA = NAND_WRITE_TURE1;
    if (rt_hw_nand_wait_ready() != RT_EOK)
    {
        result = -RT_EIO;
        goto _exit;
    }

    if (spare && spare_len)
    {
        NAND_CMD_AREA = NAND_WRITE0;
        NAND_DATA_AREA = (rt_uint8_t)(4096 & 0xFF);
        NAND_DATA_AREA = (rt_uint8_t)(4096 >> 8);
        NAND_DATA_AREA = (rt_uint8_t)(page & 0xFF);
        NAND_DATA_AREA = (rt_uint8_t)(page >> 8);
        NAND_DATA_AREA = (rt_uint8_t)(page >> 16);

        for (i = 4; i < spare_len; i++)
        {
            NAND_ADDR_AREA = spare[i];
        }
        NAND_CMD_AREA = NAND_WRITE_TURE1;
        if (rt_hw_nand_wait_ready() != RT_EOK)
        {
            result = -RT_EIO;
            goto _exit;
        }
    }
_exit:
    rt_mutex_release(&_device.lock);

    return result;
}

/* erase one block */
static rt_err_t _erase_block(struct rt_mtd_nand_device *device, rt_uint32_t block)
{
    RT_ASSERT(device != RT_NULL);
    unsigned int block_num;
    rt_err_t result = RT_EOK;

    block = block + device->block_start;
    block_num = block << 6;

    rt_mutex_take(&_device.lock, RT_WAITING_FOREVER);

    NAND_CMD_AREA = NAND_ERASE0;
    NAND_DATA_AREA = (uint8_t)block_num;
    NAND_DATA_AREA = (uint8_t)(block_num >> 8);
    NAND_DATA_AREA = (uint8_t)(block_num >> 16);
    NAND_CMD_AREA = NAND_ERASE1;

    rt_thread_delay(NAND_TBERS_DELAY);

    if (rt_hw_nand_wait_ready() != RT_EOK)
    {
        result = -RT_ERROR;
    }

    rt_mutex_release(&_device.lock);

    return result;
}

static rt_err_t _page_copy(struct rt_mtd_nand_device *device,
                           rt_off_t src_page,
                           rt_off_t dst_page)
{
    RT_ASSERT(device != RT_NULL);
    rt_err_t result = RT_EOK;
    rt_uint32_t source_block = 0, dest_block = 0;

    src_page = src_page + device->block_start * device->pages_per_block;
    dst_page = dst_page + device->block_start * device->pages_per_block;
    source_block = src_page / device->pages_per_block;
    dest_block = dst_page / device->pages_per_block;
    if ((source_block % 2) != (dest_block % 2))
    {
        return RT_MTD_ESRC;
    }

    NAND_CMD_AREA = NAND_MOVEDATA_CMD0;
    NAND_DATA_AREA = (rt_uint8_t)(0 & 0xFF);
    NAND_DATA_AREA = (rt_uint8_t)(0 >> 8);
    NAND_DATA_AREA = (rt_uint8_t)(src_page & 0xFF);
    NAND_DATA_AREA = (rt_uint8_t)(src_page >> 8);
    NAND_DATA_AREA = (rt_uint8_t)(src_page >> 16);
    NAND_CMD_AREA = NAND_MOVEDATA_CMD1;

    rt_hw_nand_delay(10);

    NAND_CMD_AREA = NAND_MOVEDATA_CMD2;
    NAND_DATA_AREA = ((rt_uint8_t)(0 & 0xFF));
    NAND_DATA_AREA = ((rt_uint8_t)(0 >> 8));
    NAND_DATA_AREA = ((rt_uint8_t)(dst_page & 0xFF));
    NAND_DATA_AREA = ((rt_uint8_t)(dst_page >> 8));
    NAND_DATA_AREA = ((rt_uint8_t)(dst_page >> 16));
    NAND_CMD_AREA = (NAND_MOVEDATA_CMD3);

    if (rt_hw_nand_wait_ready() != RT_EOK)
    {
        result = -RT_ERROR;
    }

    return result;
}

static rt_err_t _check_block(struct rt_mtd_nand_device *device, rt_uint32_t block)
{
    RT_ASSERT(device != RT_NULL);
    return (RT_MTD_EOK);
}

static rt_err_t _mark_bad(struct rt_mtd_nand_device *device, rt_uint32_t block)
{
    RT_ASSERT(device != RT_NULL);
    return (RT_MTD_EOK);
}

static const struct rt_mtd_nand_driver_ops ops =
    {
        _read_id,
        _read_page,
        _write_page,
        _page_copy,
        _erase_block,
        _check_block,
        _mark_bad,
};
static struct rt_mtd_nand_device nand_dev;

static rt_err_t nand_init(struct rt_mtd_nand_device *device)
{
    RT_ASSERT(device != RT_NULL);
    uint32_t tempreg = 0;

    rt_hw_nand_gpio_init();

    tempreg |= 0 << 1;          /* disable Wait feature enable bit */
    tempreg |= 0 << 4;          /* Data bus width 8*/
    tempreg |= 0 << 6;          /* disable ECC */
    tempreg |= 1 << 17;         /* ECC page 512 BYTE */
    tempreg |= 5 << 9;          /* set TCLR */
    tempreg |= 5 << 13;         /* set TAR */
    FMC_Bank3_R->PCR = tempreg; /* set nand control register */

    tempreg &= 0;
    tempreg |= 3 << 0;  /* set MEMSET  */
    tempreg |= 5 << 8;  /* set MEMWAIT */
    tempreg |= 2 << 16; /* set MEMHOLD */
    tempreg |= 3 << 24; /* set MEMHIZ  */
    FMC_Bank3_R->PMEM = tempreg;
    FMC_Bank3_R->PATT = 0;                     /* Attribute memory space timing registers */
    FMC_Bank3_R->PCR |= 1 << 2;                /* NAND Flash memory bank enable bit */
    FMC_Bank1_R->BTCR[0] |= (uint32_t)1 << 31; /* enable fmc */

    rt_hw_nand_reset(); /* reset nand flash*/
    rt_thread_delay(100);

    /* read id */
    _read_id(&nand_dev);

    if (_device.id != MT29F8G08ABACAH4)
    {
        LOG_E("nand id 0x%08x not support", _device.id);
        return RT_ERROR; /* can't find nand flash */
    }

    rt_hw_nand_set_mode(4); /* set mode 4, high speed mode*/

    return RT_EOK;
}

int rt_hw_nand_init(void)
{
    rt_err_t result = RT_EOK;

    rt_pin_mode(NAND_RB_PIN, PIN_MODE_INPUT_PULLUP); /* nand flash R/B pin */

    result = nand_init(&nand_dev);
    if (result != RT_EOK)
    {
        LOG_D("nand flash init error!");
        return RT_ERROR;
    }
    rt_mutex_init(&_device.lock, "nand", RT_IPC_FLAG_FIFO);

    nand_dev.page_size       = 4096;
    nand_dev.pages_per_block = 224;
    nand_dev.plane_num       = 2;
    nand_dev.oob_size        = 64;
    nand_dev.oob_free        = 64 - ((4096) * 3 / 256);
    nand_dev.block_start     = 0;
    nand_dev.block_end       = 4095;

    nand_dev.block_total = nand_dev.block_end - nand_dev.block_start;
    nand_dev.ops = &ops;

    result = rt_mtd_nand_register_device("nand", &nand_dev);
    if (result != RT_EOK)
    {
        rt_device_unregister(&nand_dev.parent);
        return RT_ERROR;
    }

    rt_kprintf("nand flash init success, id: 0x%08x\n", _device.id);

    return RT_EOK;
}

INIT_DEVICE_EXPORT(rt_hw_nand_init);

#endif
