/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-07-27     thread-liu        the first version
 */

#include "board.h"

#if defined(BSP_USING_DCMI)

#include <drv_dcmi.h>

#define DRV_DEBUG
#define LOG_TAG             "drv.dcmi"
#include <drv_log.h>

struct stm32_dcmi
{
    DCMI_HandleTypeDef DCMI_Handle;
    struct rt_dcmi_device dev;
};
static struct stm32_dcmi rt_dcmi = {0};

DMA_HandleTypeDef hdma_dcmi;

static void rt_hw_dcmi_dma_init(void)
{
    __HAL_RCC_DMA2_CLK_ENABLE();

    hdma_dcmi.Instance                 = DMA2_Stream1;
    hdma_dcmi.Init.Request             = DMA_REQUEST_DCMI;
    hdma_dcmi.Init.Direction           = DMA_PERIPH_TO_MEMORY;
    hdma_dcmi.Init.PeriphInc           = DMA_PINC_DISABLE;
    hdma_dcmi.Init.MemInc              = DMA_MINC_ENABLE;
    hdma_dcmi.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_dcmi.Init.MemDataAlignment    = DMA_MDATAALIGN_WORD;
    hdma_dcmi.Init.Mode                = DMA_CIRCULAR;
    hdma_dcmi.Init.Priority            = DMA_PRIORITY_HIGH;
    hdma_dcmi.Init.FIFOMode            = DMA_FIFOMODE_ENABLE;
    hdma_dcmi.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
    hdma_dcmi.Init.MemBurst            = DMA_MBURST_SINGLE;
    hdma_dcmi.Init.PeriphBurst         = DMA_PBURST_SINGLE;

    HAL_DMA_DeInit(&hdma_dcmi);
    HAL_DMA_Init(&hdma_dcmi);

    __HAL_LINKDMA(&rt_dcmi.DCMI_Handle, DMA_Handle, hdma_dcmi);

    HAL_NVIC_SetPriority(DMA2_Stream1_IRQn, 0x00, 0x00);
    HAL_NVIC_EnableIRQ(DMA2_Stream1_IRQn);;
}

void rt_hw_dcmi_dma_config(rt_uint32_t dst_addr1, rt_uint32_t dst_addr2, rt_uint32_t len)
{
    __HAL_UNLOCK(&hdma_dcmi);

    HAL_DMAEx_MultiBufferStart(&hdma_dcmi, (rt_uint32_t)&DCMI->DR, dst_addr1, dst_addr2, len);

    __HAL_DMA_ENABLE_IT(&hdma_dcmi, DMA_IT_TC);
}

static rt_err_t rt_hw_dcmi_init(DCMI_HandleTypeDef *device)
{
    RT_ASSERT(device != RT_NULL);

    device->Instance               = DCMI;
    device->Init.SynchroMode       = DCMI_SYNCHRO_HARDWARE;
    device->Init.PCKPolarity       = DCMI_PCKPOLARITY_RISING;
    device->Init.VSPolarity        = DCMI_VSPOLARITY_LOW;
    device->Init.HSPolarity        = DCMI_HSPOLARITY_LOW;
    device->Init.CaptureRate       = DCMI_CR_ALL_FRAME;
    device->Init.ExtendedDataMode  = DCMI_EXTEND_DATA_8B;
    device->Init.JPEGMode          = DCMI_JPEG_ENABLE;
    device->Init.ByteSelectMode    = DCMI_BSM_ALL;
    device->Init.ByteSelectStart   = DCMI_OEBS_ODD;
    device->Init.LineSelectMode    = DCMI_LSM_ALL;
    device->Init.LineSelectStart   = DCMI_OELS_ODD;

    if (HAL_DCMI_Init(device) != HAL_OK)
    {
        LOG_E("dcmi init error!");
        return RT_ERROR;
    }

    DCMI->IER = 0x0;

    __HAL_DCMI_ENABLE_IT(device, DCMI_IT_FRAME);
    __HAL_DCMI_ENABLE(device);

    return RT_EOK;
}

void DCMI_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DCMI_IRQHandler(&rt_dcmi.DCMI_Handle);

    /* leave interrupt */
    rt_interrupt_leave();
}

void DCMI_Start(void)
{
    __HAL_DMA_ENABLE(&hdma_dcmi);
    DCMI->CR |= DCMI_CR_CAPTURE;
}

void DCMI_Stop(void)
{
    DCMI->CR &= ~(DCMI_CR_CAPTURE);
    while (DCMI->CR & 0x01);
    __HAL_DMA_DISABLE(&hdma_dcmi);
}

/* Capture a frame of the image */
void HAL_DCMI_FrameEventCallback(DCMI_HandleTypeDef *hdcmi)
{
    extern void camera_frame_data_process(void);
    /* enter interrupt */
    rt_interrupt_enter();
    /* move frame data to buffer */
    camera_frame_data_process();

    __HAL_DCMI_ENABLE_IT(&rt_dcmi.DCMI_Handle, DCMI_IT_FRAME);

    /* leave interrupt */
    rt_interrupt_leave();
}

void DMA2_Stream1_IRQHandler(void)
{
    extern void camera_dma_data_process(void);
    /* enter interrupt */
    rt_interrupt_enter();

    if (__HAL_DMA_GET_FLAG(&hdma_dcmi, DMA_FLAG_TCIF1_5) != RESET)
    {
        __HAL_DMA_CLEAR_FLAG(&hdma_dcmi, DMA_FLAG_TCIF1_5);
        /* move dma data to buffer */
        camera_dma_data_process();
    }

    /* leave interrupt */
    rt_interrupt_leave();
}

static rt_err_t rt_dcmi_init(rt_device_t dev)
{
    RT_ASSERT(dev != RT_NULL);
    rt_err_t result = RT_EOK;

    result = rt_hw_dcmi_init(&rt_dcmi.DCMI_Handle);
    if (result != RT_EOK)
    {
        return result;
    }

    rt_hw_dcmi_dma_init();

    return result;
}

static rt_err_t rt_dcmi_open(rt_device_t dev, rt_uint16_t oflag)
{
    RT_ASSERT(dev != RT_NULL);

    return RT_EOK;
}

static rt_err_t rt_dcmi_close(rt_device_t dev)
{
    RT_ASSERT(dev != RT_NULL);

    return RT_EOK;
}

static rt_err_t rt_dcmi_control(rt_device_t dev, int cmd, void *args)
{
    RT_ASSERT(dev != RT_NULL);

    return RT_EOK;
}

static rt_size_t rt_dcmi_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    RT_ASSERT(dev != RT_NULL);

    return RT_EOK;
}

static rt_size_t rt_dcmi_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    RT_ASSERT(dev != RT_NULL);

    return RT_EOK;
}

int dcmi_init(void)
{
    rt_dcmi.dev.parent.type      = RT_Device_Class_Miscellaneous;
    rt_dcmi.dev.parent.init      = rt_dcmi_init;
    rt_dcmi.dev.parent.open      = rt_dcmi_open;
    rt_dcmi.dev.parent.close     = rt_dcmi_close;
    rt_dcmi.dev.parent.read      = rt_dcmi_read;
    rt_dcmi.dev.parent.write     = rt_dcmi_write;
    rt_dcmi.dev.parent.control   = rt_dcmi_control;
    rt_dcmi.dev.parent.user_data = RT_NULL;

    rt_device_register(&rt_dcmi.dev.parent, "dcmi", RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_REMOVABLE | RT_DEVICE_FLAG_STANDALONE);

    LOG_I("dcmi init success!");

    return RT_EOK;
}
INIT_BOARD_EXPORT(dcmi_init);

#endif
