/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-07-07     thread-liu   first version
 */

#include "board.h"

#if defined(BSP_USING_DFSDM)
#include "drv_wm8994.h"
#include "drv_dfsdm.h"

#define DRV_DEBUG
#define LOG_TAG             "drv.dfsdm"
#include <drv_log.h>

#define FILTER_FIFO_SIZE    (1024)
#if defined(__ARMCC_VERSION)
__attribute__((at(0x2FFC8000))) static rt_int32_t FILTER0_FIFO[FILTER_FIFO_SIZE];
#elif defined ( __GNUC__ )
static rt_int32_t FILTER0_FIFO[FILTER_FIFO_SIZE] __attribute__((section(".Filter0Section")));
#elif defined(__ICCARM__)
#pragma location = 0x2FFC8000
__no_init static rt_int32_t FILTER0_FIFO[FILTER_FIFO_SIZE];
#endif

#if defined(__ARMCC_VERSION)
__attribute__((at(0x2FFC9000))) static rt_int32_t FILTER0_FIFO[FILTER_FIFO_SIZE];
#elif defined ( __GNUC__ )
static rt_int32_t FILTER0_FIFO[FILTER_FIFO_SIZE] __attribute__((section(".Filter1Section")));
#elif defined(__ICCARM__)
#pragma location = 0x2FFC9000
__no_init static rt_int32_t FILTER1_FIFO[FILTER_FIFO_SIZE];
#endif

#define PALY_SIZE 2048
#if defined(__ARMCC_VERSION)
__attribute__((at(0x2FFCA000))) static rt_int16_t PLAY_BUF[PALY_SIZE];
#elif defined ( __GNUC__ )
__attribute__((at(0x2FFCA000))) __attribute__((section(".DfsdmSection")));
#elif defined(__ICCARM__)
#pragma location = 0x2FFCA000
 __no_init static rt_int16_t PLAY_BUF[PALY_SIZE];
#endif

static volatile rt_uint8_t DmaLeftRecBuffCplt  = 0;
static volatile rt_uint8_t DmaRightRecBuffCplt = 0;
static volatile rt_uint8_t DmaLeftRecHalfBuffCplt = 0;
static volatile rt_uint8_t DmaRightRecHalfBuffCplt = 0;

static DFSDM_Channel_HandleTypeDef hdfsdm1_channel0 = {0}; /* data_in1_right */
static DFSDM_Channel_HandleTypeDef hdfsdm1_channel1 = {0}; /* data_in1_left */

static DFSDM_Filter_HandleTypeDef hdfsdm1_filter0 = {0}; /* data_in1_right */
static DFSDM_Filter_HandleTypeDef hdfsdm1_filter1 = {0}; /* data_in1_left */

extern DMA_HandleTypeDef hdma_dfsdm1_flt0;
extern DMA_HandleTypeDef hdma_dfsdm1_flt1;

static struct rt_device dfsdm_dev =  {0};

void DMA2_Stream2_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&hdma_dfsdm1_flt1);

    /* leave interrupt */
    rt_interrupt_leave();
}

void DMA2_Stream1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&hdma_dfsdm1_flt0);

    /* leave interrupt */
    rt_interrupt_leave();
}

void HAL_DFSDM_FilterRegConvHalfCpltCallback(DFSDM_Filter_HandleTypeDef *hdfsdm_filter)
{
    if(hdfsdm_filter == &hdfsdm1_filter1)
    {
        DmaLeftRecHalfBuffCplt = 1;
    }
    else
    {
        DmaRightRecHalfBuffCplt = 1;
    }
}

void HAL_DFSDM_FilterRegConvCpltCallback(DFSDM_Filter_HandleTypeDef *hdfsdm_filter)
{
    if (hdfsdm_filter == &hdfsdm1_filter1)
    {
        DmaLeftRecBuffCplt = 1;
    }
    else
    {
        DmaRightRecBuffCplt = 1;
    }
}

static int rt_hw_dfsdm_init(void)
{
    /* DATAIN1_LEFT */
    __HAL_DFSDM_CHANNEL_RESET_HANDLE_STATE(&hdfsdm1_channel1);
    hdfsdm1_channel1.Instance                      = DFSDM1_Channel1;
    hdfsdm1_channel1.Init.OutputClock.Activation   = ENABLE;
    hdfsdm1_channel1.Init.OutputClock.Selection    = DFSDM_CHANNEL_OUTPUT_CLOCK_SYSTEM; /* 209MHZ */
    hdfsdm1_channel1.Init.OutputClock.Divider      = 74; /* 209/74 = 2.82MHZ*/
    hdfsdm1_channel1.Init.Input.Multiplexer        = DFSDM_CHANNEL_EXTERNAL_INPUTS;
    hdfsdm1_channel1.Init.Input.DataPacking        = DFSDM_CHANNEL_STANDARD_MODE;
    hdfsdm1_channel1.Init.Input.Pins               = DFSDM_CHANNEL_SAME_CHANNEL_PINS;
    hdfsdm1_channel1.Init.SerialInterface.Type     = DFSDM_CHANNEL_SPI_RISING ;   /* left */
    hdfsdm1_channel1.Init.SerialInterface.SpiClock = DFSDM_CHANNEL_SPI_CLOCK_INTERNAL;
    hdfsdm1_channel1.Init.Awd.FilterOrder          = DFSDM_CHANNEL_FASTSINC_ORDER;
    hdfsdm1_channel1.Init.Awd.Oversampling         = 10;
    hdfsdm1_channel1.Init.Offset                   = 0;
    hdfsdm1_channel1.Init.RightBitShift            = 2;
    if(HAL_OK != HAL_DFSDM_ChannelInit(&hdfsdm1_channel1))
    {
        return -RT_ERROR;
    }

    /* DATAIN1_RIGHT */
    __HAL_DFSDM_CHANNEL_RESET_HANDLE_STATE(&hdfsdm1_channel0);
    hdfsdm1_channel0.Instance                      = DFSDM1_Channel0;
    hdfsdm1_channel0.Init.OutputClock.Activation   = ENABLE;
    hdfsdm1_channel0.Init.OutputClock.Selection    = DFSDM_CHANNEL_OUTPUT_CLOCK_SYSTEM;
    hdfsdm1_channel0.Init.OutputClock.Divider      = 74;  /* 209/74 = 2.82MHZ*/
    hdfsdm1_channel0.Init.Input.Multiplexer        = DFSDM_CHANNEL_EXTERNAL_INPUTS;
    hdfsdm1_channel0.Init.Input.DataPacking        = DFSDM_CHANNEL_STANDARD_MODE;
    hdfsdm1_channel0.Init.Input.Pins               = DFSDM_CHANNEL_FOLLOWING_CHANNEL_PINS;
    hdfsdm1_channel0.Init.SerialInterface.Type     = DFSDM_CHANNEL_SPI_FALLING;   /* right */
    hdfsdm1_channel0.Init.SerialInterface.SpiClock = DFSDM_CHANNEL_SPI_CLOCK_INTERNAL;
    hdfsdm1_channel0.Init.Awd.FilterOrder          = DFSDM_CHANNEL_FASTSINC_ORDER;
    hdfsdm1_channel0.Init.Awd.Oversampling         = 10;
    hdfsdm1_channel0.Init.Offset                   = 0;
    hdfsdm1_channel0.Init.RightBitShift            = 2;
    if(HAL_OK != HAL_DFSDM_ChannelInit(&hdfsdm1_channel0))
    {
        return -RT_ERROR;
    }

    /* Initialize filter 0 (data_in1 right channel) */
    __HAL_DFSDM_FILTER_RESET_HANDLE_STATE(&hdfsdm1_filter0);
    hdfsdm1_filter0.Instance                          = DFSDM1_Filter0;
    hdfsdm1_filter0.Init.RegularParam.Trigger         = DFSDM_FILTER_SW_TRIGGER;
    hdfsdm1_filter0.Init.RegularParam.FastMode        = ENABLE;
    hdfsdm1_filter0.Init.RegularParam.DmaMode         = ENABLE;
    hdfsdm1_filter0.Init.InjectedParam.Trigger        = DFSDM_FILTER_SW_TRIGGER;
    hdfsdm1_filter0.Init.InjectedParam.ScanMode       = DISABLE;
    hdfsdm1_filter0.Init.InjectedParam.DmaMode        = DISABLE;
    hdfsdm1_filter0.Init.FilterParam.SincOrder        = DFSDM_FILTER_SINC3_ORDER;
    hdfsdm1_filter0.Init.FilterParam.Oversampling     = 64; /* 209 / ( 74 * 64) = 44.1KHZ*/
    hdfsdm1_filter0.Init.FilterParam.IntOversampling  = 1;
    if (HAL_OK != HAL_DFSDM_FilterInit(&hdfsdm1_filter0))
    {
        return -RT_ERROR;
    }

    /* Initialize filter 1 (data_in1 left channel) */
    __HAL_DFSDM_FILTER_RESET_HANDLE_STATE(&hdfsdm1_filter1);
    hdfsdm1_filter1.Instance                          = DFSDM1_Filter1;
    hdfsdm1_filter1.Init.RegularParam.Trigger         = DFSDM_FILTER_SW_TRIGGER;
    hdfsdm1_filter1.Init.RegularParam.FastMode        = ENABLE;
    hdfsdm1_filter1.Init.RegularParam.DmaMode         = ENABLE;
    hdfsdm1_filter1.Init.InjectedParam.Trigger        = DFSDM_FILTER_SW_TRIGGER;
    hdfsdm1_filter1.Init.InjectedParam.ScanMode       = DISABLE;
    hdfsdm1_filter1.Init.InjectedParam.DmaMode        = DISABLE;
    hdfsdm1_filter1.Init.FilterParam.SincOrder        = DFSDM_FILTER_SINC3_ORDER;
    hdfsdm1_filter1.Init.FilterParam.Oversampling     = 64; /* 209 / ( 74 * 64) = 44.1KHZ*/
    hdfsdm1_filter1.Init.FilterParam.IntOversampling  = 1;
    if (HAL_OK != HAL_DFSDM_FilterInit(&hdfsdm1_filter1))
    {
        return -RT_ERROR;
    }

    /* Configure regular channel and continuous mode for filter 0 (data_in1 left channel) */
    if (HAL_OK != HAL_DFSDM_FilterConfigRegChannel(&hdfsdm1_filter1, DFSDM_CHANNEL_1, DFSDM_CONTINUOUS_CONV_ON))
    {
        return -RT_ERROR;
    }

    /* Configure regular channel and continuous mode for filter 1 (data_in1 right channel) */
    if (HAL_OK != HAL_DFSDM_FilterConfigRegChannel(&hdfsdm1_filter0, DFSDM_CHANNEL_0, DFSDM_CONTINUOUS_CONV_ON))
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

/* dfsdm start coversions */
static rt_err_t rt_hw_dfsdm_open(void)
{
    if (HAL_OK != HAL_DFSDM_FilterRegularStart_DMA(&hdfsdm1_filter0, FILTER0_FIFO, FILTER_FIFO_SIZE))
    {
        LOG_E("DFSDM DATA_IN1 rifht channel start conversions failed!");
        return -RT_ERROR;
    }

    if (HAL_OK != HAL_DFSDM_FilterRegularStart_DMA(&hdfsdm1_filter1, FILTER1_FIFO, FILTER_FIFO_SIZE))
    {
        LOG_E("DFSDM DATA_IN1 left channel start conversions failed!");
        return -RT_ERROR;
    }

    return RT_EOK;
}

static rt_err_t _init(rt_device_t dev)
{
   RT_ASSERT(dev != RT_NULL);

   rt_hw_dfsdm_init();

   return RT_EOK;
}

static rt_err_t _open(rt_device_t dev, rt_uint16_t oflag)
{
   RT_ASSERT(dev != RT_NULL);

   rt_hw_dfsdm_open();

   return RT_EOK;
}

static rt_err_t _close(rt_device_t dev)
{
   RT_ASSERT(dev != RT_NULL);

   HAL_DFSDM_FilterRegularStop_DMA(&hdfsdm1_filter0);
   HAL_DFSDM_FilterRegularStop_DMA(&hdfsdm1_filter1);

   return RT_EOK;
}

static rt_ssize_t _read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    RT_ASSERT(dev != RT_NULL);
    rt_uint32_t i = 0;
    rt_int16_t *p = RT_NULL;
    p = (rt_int16_t *)buffer;

    if (!pos)
    {
        for (i = 0; i < 512; i++)
        {
            p[2*i]     = (int16_t)SaturaLH((FILTER0_FIFO[i] >> 8), -32768, 32767);
            p[(2*i)+1] = (int16_t)SaturaLH((FILTER1_FIFO[i] >> 8), -32768, 32767);
        }
    }
    else
    {
        for (i = 512; i < 1024; i++)
        {
            p[2*i]     = (int16_t)SaturaLH((FILTER0_FIFO[i] >> 8), -32768, 32767);
            p[(2*i)+1] = (int16_t)SaturaLH((FILTER1_FIFO[i] >> 8), -32768, 32767);
        }
    }

    return size;
}

static rt_ssize_t _write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
   RT_ASSERT(dev != RT_NULL);

   return RT_EOK;
}

static rt_err_t _control(rt_device_t dev, int cmd, void *args)
{
   RT_ASSERT(dev != RT_NULL);

   return RT_EOK;
}

int dfsdm_init(void)
{
    dfsdm_dev.type      = RT_Device_Class_Miscellaneous;
    dfsdm_dev.init      = _init;
    dfsdm_dev.open      = _open;
    dfsdm_dev.close     = _close;
    dfsdm_dev.read      = _read;
    dfsdm_dev.write     = _write;
    dfsdm_dev.control   = _control;
    dfsdm_dev.user_data = RT_NULL;

    rt_device_register(&dfsdm_dev, "dfsdm1", RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_REMOVABLE | RT_DEVICE_FLAG_STANDALONE);

    LOG_I("dfsdm1 init success!");

    return RT_EOK;
}
INIT_DEVICE_EXPORT(dfsdm_init);

static int dfsdm_sample(int argc, char **argv)
{
    if (argc != 1)
    {
        rt_kprintf("Usage:\n");
        rt_kprintf("dfsdm_sample\n");
        return -1;
    }

    static struct rt_device *dfsdm_dev = RT_NULL;
    static struct rt_device *sound_dev = RT_NULL;
    rt_uint16_t play_type = OUTPUT_DEVICE_HEADPHONE;
    rt_uint16_t tickstart = 0;

    extern SAI_HandleTypeDef hsai_BlockA2;

    dfsdm_dev = rt_device_find("dfsdm1");
    if (dfsdm_dev == RT_NULL)
    {
        rt_kprintf("no dfsdm device!");
        return -RT_ERROR;
    }

    sound_dev = rt_device_find("decoder");
    if (sound_dev == RT_NULL)
    {
        rt_kprintf("no decoder device!");
        return -RT_ERROR;
    }

    /* open dfsdm device */
    rt_device_open(dfsdm_dev, RT_DEVICE_OFLAG_RDWR);
    /* open sound device */
    rt_device_open(sound_dev, RT_DEVICE_OFLAG_WRONLY);

    rt_device_control(sound_dev, SET_PLAY_TYPE, &play_type);
    rt_device_control(sound_dev, START_PLAY, RT_NULL);

    rt_memset(PLAY_BUF, 0, PALY_SIZE);

    tickstart = rt_tick_get();
    if (HAL_SAI_Transmit_DMA(&hsai_BlockA2, (uint8_t *)PLAY_BUF, PALY_SIZE) != HAL_OK)
    {
        rt_kprintf("sai transmit dma failed!\n");
        return -RT_ERROR;
    }
    rt_kprintf("dfsdm audio record test begin!\n");

    while (1)
    {
        if ((rt_tick_get() - tickstart) > 0x1000)
        {
            HAL_SAI_DMAStop(&hsai_BlockA2);
            rt_device_close(dfsdm_dev);
            break;
        }
        if (DmaLeftRecHalfBuffCplt && DmaRightRecHalfBuffCplt)
        {
            rt_device_read(dfsdm_dev, 0, PLAY_BUF, 512);
            DmaLeftRecHalfBuffCplt  = 0;
            DmaRightRecHalfBuffCplt = 0;
        }
        else if (DmaLeftRecBuffCplt && DmaRightRecBuffCplt)
        {
            rt_device_read(dfsdm_dev, 1, PLAY_BUF, 512);
            DmaLeftRecBuffCplt  = 0;
            DmaRightRecBuffCplt = 0;
        }
    }

    rt_kprintf("dfsdm audio record test end!\n");

    return RT_EOK;
}
MSH_CMD_EXPORT(dfsdm_sample, dfsdm audiorecord test);

#endif
