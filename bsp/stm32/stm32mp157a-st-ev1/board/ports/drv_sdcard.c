/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-07-04     thread-liu        the first version
 */

#include "board.h"

#if defined(BSP_USING_SDCARD)
#include <dfs_fs.h>

#define DRV_DEBUG
//#define SDMMC_TX_DUMP
//#define SDMMC_RX_DUMP
#define LOG_TAG             "drv.sdmmc"
#include <drv_log.h>

static SD_HandleTypeDef        SDCARD_Handler = {0};
static HAL_SD_CardInfoTypeDef  SDCardInfo     = {0};

struct stm32_sd
{
    struct rt_device sdcard;
    struct rt_semaphore sd_lock;
    volatile rt_uint8_t write_flage;
    volatile rt_uint8_t read_flage;
    volatile rt_base_t level;
};
static struct stm32_sd sd_device;

#define SD_TIMEOUT      ((uint32_t)30 * 1000)
#define DETECT_PIN      GET_PIN(G, 1)
#define LDO_PIN         GET_PIN(F, 14)

struct rt_completion tx_comp;
struct rt_completion rx_comp;

/* SYSRAM SDMMC1/2 accesses */
#define SDIO_BUFF_SIZE       512
#define SDCARD_ADDR          0x2FFC0000
#if defined(__CC_ARM) || defined(__CLANG_ARM)
__attribute__((at(SDCARD_ADDR))) static rt_uint32_t cache_buf[SDIO_BUFF_SIZE];
#elif defined ( __GNUC__ )
static rt_uint32_t cache_buf[SDIO_BUFF_SIZE] __attribute__((section(".SdCardSection")));
#elif defined(__ICCARM__)
#pragma location = SDCARD_ADDR
__no_init static rt_uint32_t cache_buf[SDIO_BUFF_SIZE];
#endif

#if defined(SDMMC_RX_DUMP) || defined(SDMMC_TX_DUMP)
#define __is_print(ch) ((unsigned int)((ch) - ' ') < 127u - ' ')
static void dump_hex(const rt_uint8_t *ptr, rt_size_t buflen)
{
    unsigned char *buf = (unsigned char *)ptr;
    int i, j;

    for (i = 0; i < buflen; i += 16)
    {
        rt_kprintf("%08X: ", i);

        for (j = 0; j < 16; j++)
            if (i + j < buflen)
                rt_kprintf("%02X ", buf[i + j]);
            else
                rt_kprintf("   ");
        rt_kprintf(" ");

        for (j = 0; j < 16; j++)
            if (i + j < buflen)
                rt_kprintf("%c", __is_print(buf[i + j]) ? buf[i + j] : '.');
        rt_kprintf("\n");
    }
}
#endif

static rt_err_t rt_hw_sd_is_detected(void)
{
   return rt_pin_read(DETECT_PIN);
}

static rt_err_t rt_hw_sd_init(void)
{
    /* sd ldo*/
    rt_pin_mode(LDO_PIN, PIN_MODE_OUTPUT);
    /* sd detect */
    rt_pin_mode(DETECT_PIN, PIN_MODE_INPUT_PULLUP);
    /* judge we have a sd card */
    if (rt_hw_sd_is_detected() != 0x00)
    {
        LOG_E("can't find sd card!");
        return RT_ERROR;
    }

    SDCARD_Handler.Instance = SDMMC1;
    HAL_SD_DeInit(&SDCARD_Handler);

  /* if CLKDIV = 0 then SDMMC Clock frequency = SDMMC Kernel Clock
     else SDMMC Clock frequency = SDMMC Kernel Clock / [2 * CLKDIV].
     SDMMC Kernel Clock = 99MHz, SDMMC Clock frequency = 50MHz  */

    SDCARD_Handler.Init.ClockDiv             = 1;
    SDCARD_Handler.Init.ClockPowerSave       = SDMMC_CLOCK_POWER_SAVE_DISABLE;
    SDCARD_Handler.Init.ClockEdge            = SDMMC_CLOCK_EDGE_FALLING;
    SDCARD_Handler.Init.HardwareFlowControl  = SDMMC_HARDWARE_FLOW_CONTROL_DISABLE;
    SDCARD_Handler.Init.BusWide              = SDMMC_BUS_WIDE_4B;

    if (HAL_SD_Init(&SDCARD_Handler) != RT_EOK)
    {
        LOG_E("sd device init error!");
        return RT_ERROR;
    }

    if (HAL_SD_ConfigWideBusOperation(&SDCARD_Handler, SDMMC_BUS_WIDE_4B) != RT_EOK)
    {
        LOG_E("sd bus config error!");
        return RT_ERROR;
    }

    if (HAL_SD_GetCardInfo(&SDCARD_Handler, &SDCardInfo) != RT_EOK)
    {
        LOG_E("sd get card info error!");
        return RT_ERROR;
    }

    rt_thread_mdelay(100);

    if(HAL_SD_GetCardState(&SDCARD_Handler) != HAL_SD_CARD_TRANSFER)
    {
        LOG_E("sd get card state error!");
        return RT_ERROR;
    }

    return RT_EOK;
}

static void rt_hw_sd_deinit(void)
{
    HAL_SD_DeInit(&SDCARD_Handler);
}

static rt_err_t sdcard_wait_ok(void)
{
    rt_uint32_t tick_start = 0;

    tick_start = rt_tick_get();
    while ((rt_tick_get() - tick_start) < SD_TIMEOUT)
    {
        if (HAL_SD_GetCardState(&SDCARD_Handler) == HAL_SD_CARD_TRANSFER)
        {
            return HAL_OK;
        }
    }
    return HAL_ERROR;
}

void HAL_SD_DriveTransceiver_1_8V_Callback(FlagStatus status)
{
    if (status == SET)
    {
        rt_pin_write(LDO_PIN, PIN_HIGH);
    }
    else
    {
        rt_pin_write(LDO_PIN, PIN_LOW);
    }
}

static rt_err_t rt_sdcard_init(rt_device_t dev)
{
    RT_ASSERT(dev != RT_NULL);
    struct stm32_sd *sd = (struct stm32_sd *)dev;

    if (rt_sem_init(&sd->sd_lock, "sdlock", 1, RT_IPC_FLAG_FIFO) != RT_EOK)
    {
        LOG_E("init sd lock semaphore failed\n");
    }

    return RT_EOK;
}

static rt_err_t rt_sdcard_open(rt_device_t dev, rt_uint16_t oflag)
{
    RT_ASSERT(dev != RT_NULL);
    return RT_EOK;
}

static rt_err_t rt_sdcard_close(rt_device_t dev)
{
    RT_ASSERT(dev != RT_NULL);
    return RT_EOK;
}

/**
  * @brief  Reads Sector(s)
  * @param  dev : sd dev
  * @param  sector: Sector address (LBA) Data buffer to store read data
  * @param  *buffer: Data buffer to store read data
  * @param  count: Number of sectors to read (1..128)
  * @retval DRESULT: Operation result
  */

static rt_size_t rt_sdcard_read(rt_device_t dev, rt_off_t sector, void *buffer, rt_size_t count)
{
    RT_ASSERT(dev != RT_NULL);
    struct stm32_sd *sd = (struct stm32_sd *)dev;

    rt_uint8_t ret = RT_EOK;
    volatile uint32_t tickstart = 0;
    sd->read_flage  = 0;

    rt_memset(cache_buf, 0x00, BLOCKSIZE * count);

    ret = sdcard_wait_ok();
    if (ret != RT_EOK)
    {
        LOG_D("sdmmc busy!");
        return 0;
    }

    rt_sem_take(&sd->sd_lock, RT_WAITING_FOREVER);
    ret = HAL_SD_ReadBlocks_DMA(&SDCARD_Handler, (rt_uint8_t *)cache_buf, (uint32_t)sector, count);
    rt_sem_release(&sd->sd_lock);

    /* Wait that writing process is completed or a timeout occurs */
    tickstart = rt_tick_get();
    if (ret == HAL_OK)
    {
        while ((sd->read_flage == 0) && (rt_tick_get() - tickstart) < SD_TIMEOUT)
        {
        }
        /* over time */
        if (sd->read_flage == 0)
        {
            return 0;
        }
        else
        {
          sd->read_flage = 0;
          tickstart = rt_tick_get();
          while ((rt_tick_get() - tickstart) < SD_TIMEOUT)
          {
              if (sdcard_wait_ok() == RT_EOK)
              {
                 sd->level=rt_hw_interrupt_disable();
                 rt_memcpy((rt_uint8_t *)(buffer), cache_buf, BLOCKSIZE * count);
                 rt_hw_interrupt_enable(sd->level);
#if defined(SDMMC_RX_DUMP)
                rt_kprintf("\nsd rx: \n");
                dump_hex(cache_buf, BLOCKSIZE * count);
#endif
                 return count;
              }
          }
        }
    }

    return 0;
}

/**
  * @brief  Writes block(s) to a specified address in an SD card, in DMA mode.
  * @param  dev        SD device
  * @param  sector     Block index from where data is to be written P
  * @param  *buffer    Pointer to the buffer that will contain the data to transmit
  * @param  count      Number of SD blocks to write
  * @retval BSP status
  */
static rt_size_t rt_sdcard_write(rt_device_t dev, rt_off_t sector, const void *buffer, rt_size_t count)
{
    RT_ASSERT(dev != RT_NULL);
    struct stm32_sd *sd = (struct stm32_sd *)dev;
    rt_uint32_t i = 0;
    rt_uint8_t ret = RT_EOK;

    for (i = 0; i < count; i++)
    {
        sd->level = rt_hw_interrupt_disable();
        rt_memset(cache_buf, 0x00, BLOCKSIZE);
        rt_memcpy(cache_buf, (rt_uint32_t *)((uintptr_t)buffer + BLOCKSIZE * i), BLOCKSIZE);
        rt_hw_interrupt_enable(sd->level);

#if defined(SDMMC_TX_DUMP)
        rt_kprintf("\nsd tx: \n");
        dump_hex(cache_buf, BLOCKSIZE);
#endif
        ret = sdcard_wait_ok();
        if (ret != RT_EOK)
        {
            LOG_D("sdmmc busy!");
            return 0;
        }
        rt_completion_init(&tx_comp);
        ret = HAL_SD_WriteBlocks_DMA(&SDCARD_Handler, (rt_uint8_t *)cache_buf, (rt_uint32_t)(sector + i),  1);
        if (ret != HAL_OK)
        {
            rt_kprintf("sd write error!\n");
            return 0;
        }
        rt_completion_wait(&tx_comp,RT_WAITING_FOREVER);

    }

    return count;
}

static rt_err_t rt_sdcard_control(rt_device_t dev, int cmd, void *args)
{
    RT_ASSERT(dev != RT_NULL);

    if (cmd == RT_DEVICE_CTRL_BLK_GETGEOME)
    {
        struct rt_device_blk_geometry *geometry;

        geometry = (struct rt_device_blk_geometry *)args;

        geometry->bytes_per_sector = 512;
        geometry->block_size       = SDCARD_Handler.SdCard.BlockSize;
        geometry->sector_count     = SDCARD_Handler.SdCard.BlockNbr;
    }

    return RT_EOK;
}

void SDMMC1_IRQHandler(void)
{
    rt_interrupt_enter();

    HAL_SD_IRQHandler(&SDCARD_Handler);

    rt_interrupt_leave();
}

void HAL_SD_RxCpltCallback(SD_HandleTypeDef *hsd)
{
    if (hsd->Instance == SDCARD_Handler.Instance)
    {
        sd_device.read_flage = 1;
    }
}

void HAL_SD_TxCpltCallback(SD_HandleTypeDef *hsd)
{
    if (hsd->Instance == SDCARD_Handler.Instance)
    {
        rt_completion_done(&tx_comp);
    }
}

int rt_hw_sdcard_init(void)
{
    if (rt_hw_sd_init() != RT_EOK)
    {
        rt_hw_sd_deinit();
        LOG_E("sdcard init failed");

        return RT_ERROR;
    }
    /* register sdcard device */
    sd_device.sdcard.type    = RT_Device_Class_Block;
    sd_device.sdcard.init    = rt_sdcard_init;
    sd_device.sdcard.open    = rt_sdcard_open;
    sd_device.sdcard.close   = rt_sdcard_close;
    sd_device.sdcard.read    = rt_sdcard_read;
    sd_device.sdcard.write   = rt_sdcard_write;
    sd_device.sdcard.control = rt_sdcard_control;

    /* no private */
    sd_device.sdcard.user_data = &SDCardInfo;

    rt_device_register(&sd_device.sdcard, "sd_card", RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_REMOVABLE | RT_DEVICE_FLAG_STANDALONE);

    LOG_I("sd card init success!");

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_sdcard_init);

#if defined(BSP_USING_SDCARD_FS)
int mnt_init(void)
{
    rt_device_t sd_dev = RT_NULL;

    LOG_I("init sd card file system.");
#if defined(SDMMC_RX_DUMP) || defined(SDMMC_TX_DUMP)
    rt_thread_delay(3000);
#else
    rt_thread_delay(RT_TICK_PER_SECOND);
#endif
    sd_dev = rt_device_find("sd_card");
    if (sd_dev == RT_NULL)
    {
        LOG_E("can't find sd deivce name!");
        return RT_ERROR;
    }

    if (dfs_mount("sd_card", "/", "elm", 0, 0) != 0)
    {
        rt_kprintf("file system mount failed!\n");
    }
    else
    {
        rt_kprintf("file system mount success!\n");
    }

    return 0;
}
INIT_APP_EXPORT(mnt_init);
#endif

#endif
