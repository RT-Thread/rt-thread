/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-07-28     thread-liu        the first version
 */

#include "board.h"

#if defined(BSP_USING_SPDIFRX)
#include "drv_spdifrx.h"

#define DRV_DEBUG
#define LOG_TAG             "drv.spdifrx"
#include <drv_log.h>

struct stm32_spdifrx
{
    struct rt_device dev;
    SPDIFRX_HandleTypeDef spdifrx;
    SAI_HandleTypeDef sai4;
    volatile rt_uint8_t complate;
};
static struct stm32_spdifrx rt_spdifrx = {0};

extern DMA_HandleTypeDef hdma_spdifrx_rx;
extern DMA_HandleTypeDef hdma_sai4_a;

static void sai4a_init(SAI_HandleTypeDef* sai)
{
    sai->Instance                 = SAI4_Block_A;
    sai->Init.Protocol            = SAI_SPDIF_PROTOCOL;
    sai->Init.AudioMode           = SAI_MODEMASTER_TX;
    sai->Init.Synchro             = SAI_ASYNCHRONOUS;
    sai->Init.OutputDrive         = SAI_OUTPUTDRIVE_DISABLE;
    sai->Init.FIFOThreshold       = SAI_FIFOTHRESHOLD_EMPTY;
    sai->Init.AudioFrequency      = SAI_AUDIO_FREQUENCY_96K;
    sai->Init.MonoStereoMode      = SAI_STEREOMODE;
    sai->Init.CompandingMode      = SAI_NOCOMPANDING;
    sai->Init.PdmInit.Activation  = DISABLE;
    sai->Init.PdmInit.MicPairsNbr = 0;
    sai->Init.PdmInit.ClockEnable = SAI_PDM_CLOCK1_ENABLE;
    sai->Init.DataSize            = SAI_DATASIZE_24;
    sai->Init.FirstBit            = SAI_FIRSTBIT_MSB;
    sai->Init.ClockStrobing       = SAI_CLOCKSTROBING_FALLINGEDGE;

    sai->FrameInit.FrameLength       = 64;
    sai->FrameInit.ActiveFrameLength = 32;
    sai->FrameInit.FSDefinition      = SAI_FS_STARTFRAME;
    sai->FrameInit.FSPolarity        = SAI_FS_ACTIVE_LOW;
    sai->FrameInit.FSOffset          = SAI_FS_FIRSTBIT;

    sai->SlotInit.FirstBitOffset = 0;
    sai->SlotInit.SlotSize       = SAI_SLOTSIZE_DATASIZE;
    sai->SlotInit.SlotNumber     = 4;
    sai->SlotInit.SlotActive     = SAI_SLOTACTIVE_ALL;

    if (HAL_SAI_Init(sai) != HAL_OK)
    {
        Error_Handler();
    }
}

void DMA1_Stream7_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&hdma_spdifrx_rx);

    /* leave interrupt */
    rt_interrupt_leave();
}

void DMA1_Stream2_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&hdma_sai4_a);

    /* leave interrupt */
    rt_interrupt_leave();
}

void HAL_SPDIFRX_RxCpltCallback(SPDIFRX_HandleTypeDef *hspdif)
{
    rt_spdifrx.complate = SET;
}

static rt_err_t _init(rt_device_t dev)
{
    RT_ASSERT(dev != RT_NULL);
    struct stm32_spdifrx *device = (struct stm32_spdifrx *)dev;

    device->spdifrx.Instance = SPDIFRX;
    HAL_SPDIFRX_DeInit(&device->spdifrx);

    device->spdifrx.Init.InputSelection     = SPDIFRX_INPUT_IN1;
    device->spdifrx.Init.Retries            = SPDIFRX_MAXRETRIES_15;
    device->spdifrx.Init.WaitForActivity    = SPDIFRX_WAITFORACTIVITY_ON;
    device->spdifrx.Init.ChannelSelection   = SPDIFRX_CHANNEL_A;
    device->spdifrx.Init.DataFormat         = SPDIFRX_DATAFORMAT_MSB;
    device->spdifrx.Init.StereoMode         = SPDIFRX_STEREOMODE_ENABLE;
    device->spdifrx.Init.PreambleTypeMask   = SPDIFRX_PREAMBLETYPEMASK_ON;
    device->spdifrx.Init.ChannelStatusMask  = SPDIFRX_CHANNELSTATUS_ON;

    if (HAL_SPDIFRX_Init(&device->spdifrx) != HAL_OK)
    {
        return -RT_ERROR;
    }

    sai4a_init(&device->sai4);

    rt_spdifrx.complate = RESET;

    return RT_EOK;
}

static rt_err_t _open(rt_device_t dev, rt_uint16_t oflag)
{
    RT_ASSERT(dev != RT_NULL);

    return RT_EOK;
}

static rt_err_t _close(rt_device_t dev)
{
    RT_ASSERT(dev != RT_NULL);

    return RT_EOK;
}

static rt_ssize_t _read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    rt_uint32_t tickstart = 0;

    RT_ASSERT(dev != RT_NULL);
    struct stm32_spdifrx *device = (struct stm32_spdifrx *)dev;
    rt_err_t result = RT_EOK;

    result = HAL_SPDIFRX_ReceiveDataFlow_DMA(&device->spdifrx, (uint32_t *)buffer, size);
    if (result != HAL_OK)
    {
        return 0;
    }

    if(device->spdifrx.ErrorCode != HAL_SPDIFRX_ERROR_NONE)
    {
        return 0;
    }

    tickstart = rt_tick_get();
    while (rt_spdifrx.complate == RESET)
    {
        if (rt_tick_get() - tickstart > 0xFFFF)
        {
            return 0;
        }
    }

    rt_spdifrx.complate = RESET;

    return size;
}

static rt_ssize_t _write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    RT_ASSERT(dev != RT_NULL);

    struct stm32_spdifrx *device = (struct stm32_spdifrx *)dev;
    rt_err_t result = RT_EOK;

    result = HAL_SAI_Transmit_DMA(&device->sai4, (rt_uint8_t *)buffer, size);
    if (result != HAL_OK)
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

static rt_err_t _control(rt_device_t dev, int cmd, void *args)
{
    RT_ASSERT(dev != RT_NULL);

    return RT_EOK;
}

int spdifrx_init(void)
{
    rt_spdifrx.dev.type      = RT_Device_Class_Miscellaneous;
    rt_spdifrx.dev.init      = _init;
    rt_spdifrx.dev.open      = _open;
    rt_spdifrx.dev.close     = _close;
    rt_spdifrx.dev.read      = _read;
    rt_spdifrx.dev.write     = _write;
    rt_spdifrx.dev.control   = _control;
    rt_spdifrx.dev.user_data = RT_NULL;

    rt_device_register(&rt_spdifrx.dev, "spdifrx", RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_REMOVABLE | RT_DEVICE_FLAG_STANDALONE);
    rt_device_init(&rt_spdifrx.dev);

    LOG_I("spdifrx init success!");

    return RT_EOK;
}
INIT_DEVICE_EXPORT(spdifrx_init);

#ifdef FINSH_USING_MSH
#include <finsh.h>

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

static int spdifrx_sample(int argc, char **argv)
{
    extern SAI_HandleTypeDef hsai_block4_a;

    if (argc != 1)
    {
        rt_kprintf("Usage:\n");
        rt_kprintf("spdifrx_sample\n");
        return -1;
    }

    /* 16 bit Data Buffer for Transmission */
    static rt_uint16_t tx_buffer[64] = {
    0x5152, 0x5354, 0x5556, 0x5758, 0x595A, 0x5B5C, 0x5D5E, 0x5F60,
    0x6162, 0x6364, 0x6566, 0x6768, 0x696A, 0x6B6C, 0x6D6E, 0x6F70,
    0x7172, 0x7374, 0x7576, 0x7778, 0x797A, 0x7B7C, 0x7D7E, 0x7F80,
    0x8182, 0x8384, 0x8586, 0x8788, 0x898A, 0x8B8C, 0x8D8E, 0x8F90,
    0x5152, 0x5354, 0x5556, 0x5758, 0x595A, 0x5B5C, 0x5D5E, 0x5F60,
    0x6162, 0x6364, 0x6566, 0x6768, 0x696A, 0x6B6C, 0x6D6E, 0x6F70,
    0x7172, 0x7374, 0x7576, 0x7778, 0x797A, 0x7B7C, 0x7D7E, 0x7F80,
    0x8182, 0x8384, 0x8586, 0x8788, 0x898A, 0x8B8C, 0x8D8E, 0x8F90};

    static rt_uint32_t *rx_buffer = NULL;
    rt_uint8_t size = 64;
    struct rt_device *dev = RT_NULL;

    dev = rt_device_find("spdifrx");
    if (dev == RT_NULL)
    {
        rt_kprintf("can't find spdifrx device!\n");
    }

    rt_device_open(dev, RT_DEVICE_OFLAG_RDWR);

    rt_kprintf("spdifrx test tx data : \n");
    dump_hex((rt_uint8_t *)tx_buffer, size);

    rx_buffer = (rt_uint32_t *)rt_malloc(size);

    rt_device_write(dev, 0, tx_buffer, size);
    rt_device_read(dev, 0, rx_buffer, size);

    /* Compare the received data with the expected one */
    while (size--)
    {
        if (((rx_buffer[size] & 0x00ffff00) >>  8) != (tx_buffer[size]))
        {
            rt_kprintf("spdirex loopback mode test failed!\n");

            return -RT_ERROR;
        }
    }

    rt_kprintf("spdifrx rx : \n");
    dump_hex((rt_uint8_t *)rx_buffer, size);

    rt_kprintf("spdirex loopback mode test success!\n");

    return RT_EOK;
}
MSH_CMD_EXPORT(spdifrx_sample, spdifrx loopback test);
#endif

#endif
