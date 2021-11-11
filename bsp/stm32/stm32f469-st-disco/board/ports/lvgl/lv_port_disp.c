/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-10-18     Meco Man     The first version
 */
#include <lvgl.h>
#include <lcd_port.h>

//#define DRV_DEBUG
#define LOG_TAG             "lvgl.disp"
#include <drv_log.h>

/*A static or global variable to store the buffers*/
static lv_disp_draw_buf_t disp_buf;

rt_device_t lcd_device = 0;
static struct rt_device_graphic_info info;

static lv_disp_drv_t disp_drv;  /*Descriptor of a display driver*/

static DMA_HandleTypeDef         DmaHandle;
#define DMA_STREAM               DMA2_Stream0
#define DMA_CHANNEL              DMA_CHANNEL_0
#define DMA_STREAM_IRQ           DMA2_Stream0_IRQn
#define DMA_STREAM_IRQHANDLER    DMA2_Stream0_IRQHandler

static int32_t x1_flush;
static int32_t y1_flush;
static int32_t x2_flush;
static int32_t y2_fill;
static int32_t y_fill_act;
static const lv_color_t * buf_to_flush;

static void DMA_TransferComplete(DMA_HandleTypeDef *han)
{
    y_fill_act ++;

    if(y_fill_act > y2_fill)
    {
          lv_disp_flush_ready(&disp_drv);
    }
    else
    {
        buf_to_flush += (x2_flush - x1_flush + 1);

        if (HAL_DMA_Start_IT(han,(uint32_t)buf_to_flush,
            (uint32_t)&((uint32_t *)info.framebuffer)[y_fill_act * info.width + x1_flush],
            (x2_flush - x1_flush + 1)) != HAL_OK)
        {
            LOG_E("lvgl dma start error");
            while(1);
        }
    }
}

static void DMA_TransferError(DMA_HandleTypeDef *han)
{
    LOG_E("dma transfer error");
    while(1);
}

void DMA_STREAM_IRQHANDLER(void)
{
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&DmaHandle);

    rt_interrupt_leave();
}

static void lvgl_dma_config(void)
{
    /*## -1- Enable DMA2 clock #################################################*/
    __HAL_RCC_DMA2_CLK_ENABLE();

    /*##-2- Select the DMA functional Parameters ###############################*/
    DmaHandle.Init.Channel = DMA_CHANNEL;                     /* DMA_CHANNEL_0                    */
    DmaHandle.Init.Direction = DMA_MEMORY_TO_MEMORY;          /* M2M transfer mode                */
    DmaHandle.Init.PeriphInc = DMA_PINC_ENABLE;               /* Peripheral increment mode Enable */
    DmaHandle.Init.MemInc = DMA_MINC_ENABLE;                  /* Memory increment mode Enable     */
    DmaHandle.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD; /* Peripheral data alignment : 32bit */
    DmaHandle.Init.MemDataAlignment = DMA_PDATAALIGN_WORD;    /* memory data alignment : 32bit     */
    DmaHandle.Init.Mode = DMA_NORMAL;                         /* Normal DMA mode                  */
    DmaHandle.Init.Priority = DMA_PRIORITY_HIGH;              /* priority level : high            */
    DmaHandle.Init.FIFOMode = DMA_FIFOMODE_ENABLE;            /* FIFO mode enabled                */
    DmaHandle.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_1QUARTERFULL;   /* FIFO threshold: 1/4 full   */
    DmaHandle.Init.MemBurst = DMA_MBURST_SINGLE;              /* Memory burst                     */
    DmaHandle.Init.PeriphBurst = DMA_PBURST_SINGLE;           /* Peripheral burst                 */

    DmaHandle.Instance = DMA_STREAM;

    if (HAL_DMA_Init(&DmaHandle) != HAL_OK)
    {
        while(1);
    }

    HAL_DMA_RegisterCallback(&DmaHandle, HAL_DMA_XFER_CPLT_CB_ID, DMA_TransferComplete);
    HAL_DMA_RegisterCallback(&DmaHandle, HAL_DMA_XFER_ERROR_CB_ID, DMA_TransferError);

    HAL_NVIC_SetPriority(DMA_STREAM_IRQ, 0, 0);
    HAL_NVIC_EnableIRQ(DMA_STREAM_IRQ);
}

static void lcd_fb_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
    /*Return if the area is out the screen*/
    if (area->x2 < 0) return;
    if (area->y2 < 0) return;
    if (area->x1 > info.width - 1) return;
    if (area->y1 > info.height - 1) return;

    /*Truncate the area to the screen*/
    int32_t act_x1 = area->x1 < 0 ? 0 : area->x1;
    int32_t act_y1 = area->y1 < 0 ? 0 : area->y1;
    int32_t act_x2 = area->x2 > info.width - 1 ? info.width - 1 : area->x2;
    int32_t act_y2 = area->y2 > info.height - 1 ? info.height - 1 : area->y2;

    x1_flush = act_x1;
    y1_flush = act_y1;
    x2_flush = act_x2;
    y2_fill = act_y2;
    y_fill_act = act_y1;
    buf_to_flush = color_p;

    if (HAL_DMA_Start_IT(&DmaHandle,(uint32_t)buf_to_flush,
        (uint32_t)&((uint32_t *)info.framebuffer)[y_fill_act * info.width + x1_flush],
        (x2_flush - x1_flush + 1)) != HAL_OK)
    {
        LOG_E("dma start it error");
        while(1);
    }
}

void lv_port_disp_init(void)
{
    rt_err_t result;
    void* buf_1 = RT_NULL;
    void* buf_2 = RT_NULL;

    lcd_device = rt_device_find("lcd");
    if (lcd_device == 0)
    {
        LOG_E("error!");
        return;
    }
    result = rt_device_open(lcd_device, 0);
    if (result != RT_EOK)
    {
        LOG_E("error!");
        return;
    }

    /* get framebuffer address */
    result = rt_device_control(lcd_device, RTGRAPHIC_CTRL_GET_INFO, &info);
    if (result != RT_EOK)
    {
        LOG_E("error!");
        /* get device information failed */
        return;
    }

    RT_ASSERT (info.bits_per_pixel == 8 || info.bits_per_pixel == 16 ||
              info.bits_per_pixel == 24 || info.bits_per_pixel == 32);

    lvgl_dma_config();

    buf_1 = rt_malloc(info.width * 30 * sizeof(lv_color_t));
    if (buf_1 == RT_NULL)
    {
        LOG_E("malloc memory failed");
        return;
    }

    buf_2 = rt_malloc(info.width * 30 * sizeof(lv_color_t));
    if (buf_2 == RT_NULL)
    {
        LOG_E("malloc memory failed");
        return;
    }

    /*Initialize `disp_buf` with the buffer(s).*/
    lv_disp_draw_buf_init(&disp_buf, buf_1, buf_2, info.width * 30);

    lv_disp_drv_init(&disp_drv); /*Basic initialization*/

    /*Set the resolution of the display*/
    disp_drv.hor_res = info.width;
    disp_drv.ver_res = info.height;

    /*Set a display buffer*/
    disp_drv.draw_buf = &disp_buf;

    /*Used to copy the buffer's content to the display*/
    disp_drv.flush_cb = lcd_fb_flush;

    /*Finally register the driver*/
    lv_disp_drv_register(&disp_drv);
}
