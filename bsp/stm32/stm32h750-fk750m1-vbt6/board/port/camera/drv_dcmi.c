/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2023-03-24     spaceman          the first version
 */

#include "board.h"
#include "drv_dcmi.h"

#ifdef BSP_USING_DCMI

#define DRV_DEBUG
#define LOG_TAG "drv.dcmi"
#include <drv_log.h>

static struct stm32_dcmi rt_dcmi_dev = {0};
static volatile uint8_t ov2640_fps; // 帧率


static void rt_hw_dmci_dma_init(struct stm32_dcmi *dcmi_dev)
{
    RT_ASSERT(dcmi_dev != RT_NULL);
    DCMI_HandleTypeDef *_dcmi_handle = &dcmi_dev->dcmi_handle;
    DMA_HandleTypeDef *_dma_handle = &dcmi_dev->dma_handle;
    RT_ASSERT(_dcmi_handle != RT_NULL);
    RT_ASSERT(_dma_handle != RT_NULL);

    __HAL_RCC_DMA2_CLK_ENABLE(); // 使能DMA2时钟

    _dma_handle->Instance                 = DMA2_Stream7;            // DMA2数据流7
    _dma_handle->Init.Request             = DMA_REQUEST_DCMI;        // DMA请求来自DCMI
    _dma_handle->Init.Direction           = DMA_PERIPH_TO_MEMORY;    // 外设到存储器模式
    _dma_handle->Init.PeriphInc           = DMA_PINC_DISABLE;        // 外设地址禁止自增
    _dma_handle->Init.MemInc              = DMA_MINC_ENABLE;         // 存储器地址自增
    _dma_handle->Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;     // DCMI数据位宽，32位
    _dma_handle->Init.MemDataAlignment    = DMA_MDATAALIGN_WORD;     // 存储器数据位宽，32位
    _dma_handle->Init.Mode                = DMA_CIRCULAR;            // 循环模式
    _dma_handle->Init.Priority            = DMA_PRIORITY_LOW;        // 优先级低
    _dma_handle->Init.FIFOMode            = DMA_FIFOMODE_ENABLE;     // 使能fifo
    _dma_handle->Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL; // 全fifo模式，4*32bit大小
    _dma_handle->Init.MemBurst            = DMA_MBURST_SINGLE;       // 单次传输
    _dma_handle->Init.PeriphBurst         = DMA_PBURST_SINGLE;       // 单次传输

    if (HAL_DMA_Init(_dma_handle) != HAL_OK) {
        Error_Handler();
    }
    HAL_DMA_Init(_dma_handle);                      // 配置DMA
    __HAL_LINKDMA(_dcmi_handle, DMA_Handle, *_dma_handle);  // 关联DCMI句柄
    HAL_NVIC_SetPriority(DMA2_Stream7_IRQn, 0, 0); // 设置中断优先级
    HAL_NVIC_EnableIRQ(DMA2_Stream7_IRQn);         // 使能中断
}

static rt_err_t rt_hw_dcmi_init(struct stm32_dcmi *dcmi_dev)
{
    RT_ASSERT(dcmi_dev != RT_NULL);
    DCMI_HandleTypeDef *_dcmi_handle = &dcmi_dev->dcmi_handle;
    RT_ASSERT(_dcmi_handle != RT_NULL);

    _dcmi_handle->Instance              = DCMI;
    _dcmi_handle->Init.SynchroMode      = DCMI_SYNCHRO_HARDWARE;   // 硬件同步模式，即使用外部的VS、HS信号进行同步
    _dcmi_handle->Init.PCKPolarity      = DCMI_PCKPOLARITY_RISING; // 像素时钟上升沿有效
    _dcmi_handle->Init.VSPolarity       = DCMI_VSPOLARITY_LOW;     // VS低电平有效
    _dcmi_handle->Init.HSPolarity       = DCMI_HSPOLARITY_LOW;     // HS低电平有效
    _dcmi_handle->Init.CaptureRate      = DCMI_CR_ALL_FRAME;       // 捕获等级，设置每一帧都进行捕获
    _dcmi_handle->Init.ExtendedDataMode = DCMI_EXTEND_DATA_8B;     // 8位数据模式
    _dcmi_handle->Init.JPEGMode         = DCMI_JPEG_DISABLE;       // 禁止JPEG模式
    _dcmi_handle->Init.ByteSelectMode   = DCMI_BSM_ALL;            // DCMI接口捕捉所有数据
    _dcmi_handle->Init.ByteSelectStart  = DCMI_OEBS_ODD;           // 选择开始字节，从 帧/行 的第一个数据开始捕获
    _dcmi_handle->Init.LineSelectMode   = DCMI_LSM_ALL;            // 捕获所有行
    _dcmi_handle->Init.LineSelectStart  = DCMI_OELS_ODD;           // 选择开始行,在帧开始后捕获第一行
    if (HAL_DCMI_Init(_dcmi_handle) != HAL_OK) {
        LOG_E("dcmi init error!");
        return -RT_ERROR;
    }

    HAL_NVIC_SetPriority(DCMI_IRQn, 0, 5); // 设置中断优先级
    HAL_NVIC_EnableIRQ(DCMI_IRQn);         // 开启DCMI中断

    DCMI->IER = 0x0;

    // 在JPG模式下，一定要单独使能该中断
    __HAL_DCMI_ENABLE_IT(_dcmi_handle, DCMI_IT_FRAME);
    __HAL_DCMI_ENABLE(_dcmi_handle);

    rt_hw_dmci_dma_init(dcmi_dev);

    return RT_EOK;
}

/***************************************************************************************************************************************
 *    函 数 名: ov2640_dcmi_crop
 *
 *    入口参数:  displey_xsize 、displey_ysize - 显示器的长宽
 *              sensor_xsize、sensor_ysize - 摄像头传感器输出图像的长宽
 *
 *    函数功能: 使用DCMI的裁剪功能，将传感器输出的图像裁剪成适应屏幕的大小
 *
 *    说    明: 1. 因为摄像头输出的画面比例固定为4:3，不一定匹配显示器
 *              2. 需要注意的是，摄像头输出的图像长、宽必须要能被4整除！（ 使用OV2640_Set_Framesize函数进行设置 ）
 *              3. DCMI的水平有效像素也必须要能被4整除！
 *              4. 函数会计算水平和垂直偏移，尽量让画面居中裁剪
 *****************************************************************************************************************************************/
static rt_err_t ov2640_dcmi_crop(struct stm32_dcmi *dcmi_dev, uint16_t displey_xsize, uint16_t displey_ysize, uint16_t sensor_xsize, uint16_t sensor_ysize)
{
    RT_ASSERT(dcmi_dev != RT_NULL);
    DCMI_HandleTypeDef *_dcmi_handle = &dcmi_dev->dcmi_handle;
    RT_ASSERT(_dcmi_handle != RT_NULL);

    uint16_t dcmi_x_offset, dcmi_y_offset; // 水平和垂直偏移，垂直代表的是行数，水平代表的是像素时钟数（pclk周期数）
    uint16_t dcmi_capcnt;                  // 水平有效像素，代表的是像素时钟数（pclk周期数）
    uint16_t dcmi_vline;                   // 垂直有效行数

    if ((displey_xsize >= sensor_xsize) || (displey_ysize >= sensor_ysize)) {
        LOG_E("actual displayed size (%d, %d) >= camera output size (%d, %d), exit dcmi cropping", displey_xsize, displey_ysize, sensor_xsize, sensor_ysize);
        return -RT_ERROR; // 如果实际显示的尺寸大于或等于摄像头输出的尺寸，则退出当前函数，不进行裁剪
    }

    // 在设置为rgb565格式时，水平偏移，必须是奇数，否则画面色彩不正确，
    // 因为一个有效像素是2个字节，需要2个pclk周期，所以必须从奇数位开始，不然数据会错乱，
    // 需要注意的是，寄存器值是从0开始算起的    ！
    dcmi_x_offset = sensor_xsize - displey_xsize; // 实际计算过程为（sensor_xsize - lcd_xsize）/2*2

    // 计算垂直偏移，尽量让画面居中裁剪，该值代表的是行数，
    dcmi_y_offset = (sensor_ysize - displey_ysize) / 2 - 1; // 寄存器值是从0开始算起的，所以要-1

    // 因为一个有效像素是2个字节，需要2个pclk周期，所以要乘2
    // 最终得到的寄存器值，必须要能被4整除！
    dcmi_capcnt = displey_xsize * 2 - 1; // 寄存器值是从0开始算起的，所以要-1

    dcmi_vline = displey_ysize - 1; // 垂直有效行数

    // LOG_D("%d  %d  %d  %d", dcmi_x_offset, dcmi_y_offset, dcmi_capcnt, dcmi_vline);
    HAL_DCMI_ConfigCrop(_dcmi_handle, dcmi_x_offset, dcmi_y_offset, dcmi_capcnt, dcmi_vline); // 设置裁剪窗口
    HAL_DCMI_EnableCrop(_dcmi_handle);                                                        // 使能裁剪

    return RT_EOK;
}

/***************************************************************************************************************************************
 *  函 数 名: ov2640_dma_transmit_continuous
 *
 *  入口参数:  dma_buffer - DMA将要传输的地址，即用于存储摄像头数据的存储区地址
 *            dma_buffersize - 传输的数据大小，32位宽
 *
 *  函数功能: 启动DMA传输，连续模式
 *
 *  说    明: 1. 开启连续模式之后，会一直进行传输，除非挂起或者停止DCMI
 *            2. OV2640使用RGB565模式时，1个像素点需要2个字节来存储
 *            3. 因为DMA配置传输数据为32位宽，计算 dma_buffersize 时，需要除以4，例如：
 *               要获取 240*240分辨率 的图像，需要传输 240*240*2 = 115200 字节的数据，
 *               则 dma_buffersize = 115200 / 4 = 28800 。
 *
 *****************************************************************************************************************************************/
static void ov2640_dma_transmit_continuous(struct stm32_dcmi *dcmi_dev, uint32_t dma_buffer, uint32_t dma_buffersize)
{
    RT_ASSERT(dcmi_dev != RT_NULL);
    DCMI_HandleTypeDef *_dcmi_handle = &dcmi_dev->dcmi_handle;
    DMA_HandleTypeDef *_dma_handle = &dcmi_dev->dma_handle;
    RT_ASSERT(_dcmi_handle != RT_NULL);
    RT_ASSERT(_dma_handle != RT_NULL);

    _dma_handle->Init.Mode = DMA_CIRCULAR; // 循环模式

    HAL_DMA_Init(_dma_handle); // 配置DMA

    // 使能DCMI采集数据,连续采集模式
    HAL_DCMI_Start_DMA(_dcmi_handle, DCMI_MODE_CONTINUOUS, (uint32_t)dma_buffer, dma_buffersize);
}

/***************************************************************************************************************************************
 *  函 数 名: ov2640_dma_transmit_snapshot
 *
 *  入口参数:  dma_buffer - DMA将要传输的地址，即用于存储摄像头数据的存储区地址
 *            dma_buffersize - 传输的数据大小，32位宽
 *
 *  函数功能: 启动DMA传输，快照模式，传输一帧图像后停止
 *
 *  说    明: 1. 快照模式，只传输一帧的数据
 *            2. OV2640使用RGB565模式时，1个像素点需要2个字节来存储
 *            3. 因为DMA配置传输数据为32位宽，计算 dma_buffersize 时，需要除以4，例如：
 *               要获取 240*240分辨率 的图像，需要传输 240*240*2 = 115200 字节的数据，
 *               则 dma_buffersize = 115200 / 4 = 28800 。
 *            4. 使用该模式传输完成之后，DCMI会被挂起，再次启用传输之前，需要调用 OV2640_DCMI_Resume() 恢复DCMI
 *
 *****************************************************************************************************************************************/
static void ov2640_dma_transmit_snapshot(struct stm32_dcmi *dcmi_dev, uint32_t dma_buffer, uint32_t dma_buffersize)
{
    RT_ASSERT(dcmi_dev != RT_NULL);
    DCMI_HandleTypeDef *_dcmi_handle = &dcmi_dev->dcmi_handle;
    DMA_HandleTypeDef *_dma_handle = &dcmi_dev->dma_handle;
    RT_ASSERT(_dcmi_handle != RT_NULL);
    RT_ASSERT(_dma_handle != RT_NULL);

    _dma_handle->Init.Mode = DMA_NORMAL; // 正常模式

    HAL_DMA_Init(_dma_handle); // 配置DMA

    HAL_DCMI_Start_DMA(_dcmi_handle, DCMI_MODE_SNAPSHOT, (uint32_t)dma_buffer, dma_buffersize);
}

/***************************************************************************************************************************************
 *  函 数 名: ov2640_dcmi_suspend
 *
 *  函数功能: 挂起dcmi，停止捕获数据
 *
 *  说    明: 1. 开启连续模式之后，再调用该函数，会停止捕获dcmi的数据
 *            2. 可以调用 ov2640_dcmi_resume() 恢复dcmi
 *            3. 需要注意的，挂起dcmi期间，dma是没有停止工作的
 *fanke
 *****************************************************************************************************************************************/
static void ov2640_dcmi_suspend(struct stm32_dcmi *dcmi_dev)
{
    RT_ASSERT(dcmi_dev != RT_NULL);
    DCMI_HandleTypeDef *_dcmi_handle = &dcmi_dev->dcmi_handle;
    RT_ASSERT(_dcmi_handle != RT_NULL);

    HAL_DCMI_Suspend(_dcmi_handle); // 挂起dcmi
}

/***************************************************************************************************************************************
 *  函 数 名: ov2640_dcmi_resume
 *
 *  函数功能: 恢复dcmi，开始捕获数据
 *
 *  说    明: 1. 当dcmi被挂起时，可以调用该函数恢复
 *            2. 使用 ov2640_dma_transmit_snapshot() 快照模式，传输完成之后，dcmi也会被挂起，再次启用传输之前，
 *               需要调用本函数恢复dcmi捕获
 *
 *****************************************************************************************************************************************/
static void ov2640_dcmi_resume(struct stm32_dcmi *dcmi_dev)
{
    RT_ASSERT(dcmi_dev != RT_NULL);
    DCMI_HandleTypeDef *_dcmi_handle = &dcmi_dev->dcmi_handle;
    RT_ASSERT(_dcmi_handle != RT_NULL);

    _dcmi_handle->State = HAL_DCMI_STATE_BUSY;     // 变更dcmi标志
    _dcmi_handle->Instance->CR |= DCMI_CR_CAPTURE; // 开启dcmi捕获
}

/***************************************************************************************************************************************
 *  函 数 名: ov2640_dcmi_stop
 *
 *  函数功能: 禁止dcmi的dma请求，停止dcmi捕获，禁止dcmi外设
 *
 *****************************************************************************************************************************************/
static void ov2640_dcmi_stop(struct stm32_dcmi *dcmi_dev)
{
    RT_ASSERT(dcmi_dev != RT_NULL);
    DCMI_HandleTypeDef *_dcmi_handle = &dcmi_dev->dcmi_handle;
    RT_ASSERT(_dcmi_handle != RT_NULL);

    HAL_DCMI_Stop(_dcmi_handle);
}

void DCMI_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DCMI_IRQHandler(&rt_dcmi_dev.dcmi_handle);

    /* leave interrupt */
    rt_interrupt_leave();
}

void DMA2_Stream7_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&rt_dcmi_dev.dma_handle);

    /* leave interrupt */
    rt_interrupt_leave();
}

/* Capture a frame of the image */
void HAL_DCMI_FrameEventCallback(DCMI_HandleTypeDef *hdcmi)
{
    /* enter interrupt */
    rt_interrupt_enter();

    static uint32_t dcmi_tick       = 0;   // 用于保存当前的时间计数值
    static uint8_t dcmi_frame_count = 0;   // 帧数计数
    if (HAL_GetTick() - dcmi_tick >= 1000) // 每隔 1s 计算一次帧率
    {
        dcmi_tick        = HAL_GetTick();    // 重新获取当前时间计数值
        ov2640_fps       = dcmi_frame_count; // 获得fps
        dcmi_frame_count = 0;                // 计数清0
    }
    dcmi_frame_count++; // 没进入一次中断（每次传输完一帧数据），计数值+1

    rt_sem_release(&rt_dcmi_dev.cam_semaphore);
    /* leave interrupt */
    rt_interrupt_leave();
}

void HAL_DCMI_ErrorCallback(DCMI_HandleTypeDef *hdcmi)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (HAL_DCMI_GetError(hdcmi) == HAL_DCMI_ERROR_OVR) {
        LOG_E("FIFO overflow error");
    }
    LOG_E("error:0x%08x", HAL_DCMI_GetError(hdcmi));

    /* leave interrupt */
    rt_interrupt_leave();
}

static rt_err_t rt_dcmi_init(rt_device_t dev)
{
    RT_ASSERT(dev != RT_NULL);
    rt_err_t result = RT_EOK;
    struct stm32_dcmi *_rt_dcmi_dev = DCMI_DEVICE(dev);

    result = rt_hw_dcmi_init(_rt_dcmi_dev);
    if (result != RT_EOK) {
        return result;
    }

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
    struct stm32_dcmi *_rt_dcmi_dev = DCMI_DEVICE(dev);

    switch (cmd) {
        case DCMI_CTRL_CROP: {
            RT_ASSERT(args != RT_NULL);
            struct stm32_dcmi_cropsize* cropsize = (struct stm32_dcmi_cropsize*)args;
            ov2640_dcmi_crop(_rt_dcmi_dev, cropsize->displey_xsize, cropsize->displey_ysize, cropsize->sensor_xsize, cropsize->sensor_ysize);
        } break;
        case DCMI_CTRL_TRANSMIT_CONTINUOUS: {
            RT_ASSERT(args != RT_NULL);
            struct stm32_dcmi_dma_transmitbuffer* transmitbuffer = (struct stm32_dcmi_dma_transmitbuffer*)args;
            ov2640_dma_transmit_continuous(_rt_dcmi_dev, transmitbuffer->dma_buffer, transmitbuffer->dma_buffersize);
        } break;
        case DCMI_CTRL_TRANSMIT_SNAPSHOT: {
            RT_ASSERT(args != RT_NULL);
            struct stm32_dcmi_dma_transmitbuffer* transmitbuffer = (struct stm32_dcmi_dma_transmitbuffer*)args;
            ov2640_dma_transmit_snapshot(_rt_dcmi_dev, transmitbuffer->dma_buffer, transmitbuffer->dma_buffersize);
        } break;
        case DCMI_CTRL_SUSPEND: {
            ov2640_dcmi_suspend(_rt_dcmi_dev);
        } break;
        case DCMI_CTRL_RESUME: {
            ov2640_dcmi_resume(_rt_dcmi_dev);
        } break;
        case DCMI_CTRL_STOP: {
            ov2640_dcmi_stop(_rt_dcmi_dev);
        } break;
        case DCMI_CTRL_GET_FPS: {
            *(uint8_t*)args = ov2640_fps;
        } break;

        default:
            return -RT_EINVAL;
    }

    return RT_EOK;
}

static rt_ssize_t rt_dcmi_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    RT_ASSERT(dev != RT_NULL);

    return RT_EOK;
}

static rt_ssize_t rt_dcmi_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    RT_ASSERT(dev != RT_NULL);

    return RT_EOK;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops dcmi_ops =
{
    rt_dcmi_init,
    rt_dcmi_open,
    rt_dcmi_close,
    rt_dcmi_read,
    rt_dcmi_write,
    rt_dcmi_control,
};
#endif

int dcmi_init(void)
{
    int ret              = 0;
    rt_device_t device = &rt_dcmi_dev.parent;

    /* memset rt_dcmi_dev to zero */
    memset(&rt_dcmi_dev, 0x00, sizeof(rt_dcmi_dev));

    /* init cam_semaphore semaphore */
    ret = rt_sem_init(&rt_dcmi_dev.cam_semaphore, "cam_sem", 0, RT_IPC_FLAG_FIFO);
    if (ret != RT_EOK) {
        LOG_E("init semaphore failed!\n");
        ret = -RT_ENOMEM;
        goto __exit;
    }

    device->type      = RT_Device_Class_Miscellaneous;
#ifdef RT_USING_DEVICE_OPS
    device->ops = &dcmi_ops;
#else
    device->init      = rt_dcmi_init;
    device->open      = rt_dcmi_open;
    device->close     = rt_dcmi_close;
    device->read      = rt_dcmi_read;
    device->write     = rt_dcmi_write;
    device->control   = rt_dcmi_control;
#endif
    device->user_data = RT_NULL;

    ret = rt_device_register(device, "dcmi", RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_REMOVABLE | RT_DEVICE_FLAG_STANDALONE);
    if (ret != RT_EOK) {
        LOG_E("dcmi registered fail!\n\r");
        return -RT_ERROR;
    }

    LOG_I("dcmi init success!");

    return RT_EOK;
__exit:
    if (ret != RT_EOK) {
        rt_sem_delete(&rt_dcmi_dev.cam_semaphore);
    }
    return ret;
}
INIT_BOARD_EXPORT(dcmi_init);

#endif /* BSP_USING_DCMI */
