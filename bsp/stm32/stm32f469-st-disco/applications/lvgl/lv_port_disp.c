/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-10-18     Meco Man     The first version
 * 2021-12-24     Rb           Refresh using dma2d
 */
#include <lvgl.h>
#include <lcd_port.h>

//#define DRV_DEBUG
#define LOG_TAG             "LVGL.port.disp"
#include <drv_log.h>

/*A static or global variable to store the buffers*/
static lv_disp_draw_buf_t disp_buf;

static rt_device_t lcd_device = RT_NULL;
static struct rt_device_graphic_info info;

static lv_disp_drv_t disp_drv;  /*Descriptor of a display driver*/

#define DISP_BUF_SIZE        (LV_HOR_RES_MAX * LV_VER_RES_MAX / 2)

static lv_disp_drv_t g_disp_drv;
extern LTDC_HandleTypeDef  hltdc;
volatile rt_bool_t g_gpu_state = RT_FALSE;

static void lvgl_dma_config(void)
{
    HAL_NVIC_SetPriority(DMA2D_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(DMA2D_IRQn);
    __HAL_RCC_DMA2D_CLK_ENABLE();
}

static void lcd_fb_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
    uint32_t OffLineSrc = LV_HOR_RES_MAX - (area->x2 - area->x1 + 1);
    uint32_t addr = (uint32_t) hltdc.LayerCfg[0].FBStartAdress + 2 * (LV_HOR_RES_MAX * area->y1 + area->x1);

    DMA2D->CR = 0x00000000UL | (1 << 9);
    DMA2D->FGMAR = (uint32_t) (uint16_t*) (color_p);
    DMA2D->OMAR = (uint32_t) addr;

    DMA2D->FGOR = 0;
    DMA2D->OOR = OffLineSrc;

    DMA2D->FGPFCCR = DMA2D_OUTPUT_RGB565;
    DMA2D->OPFCCR = DMA2D_OUTPUT_RGB565;

    DMA2D->NLR = (area->y2 - area->y1 + 1) | ((area->x2 - area->x1 + 1) << 16);
    DMA2D->CR |= DMA2D_IT_TC | DMA2D_IT_TE | DMA2D_IT_CE;
    DMA2D->CR |= DMA2D_CR_START;

    g_gpu_state = RT_TRUE;
}

void DMA2D_IRQHandler(void)
{
    rt_interrupt_enter();

    if ((DMA2D->ISR & DMA2D_FLAG_TC) != 0U)
    {
        if ((DMA2D->CR & DMA2D_IT_TC) != 0U)
        {

            DMA2D->CR &= ~DMA2D_IT_TC;
            DMA2D->IFCR = DMA2D_FLAG_TC;

            if (g_gpu_state == RT_TRUE)
            {
                g_gpu_state = RT_FALSE;
                lv_disp_flush_ready(&g_disp_drv);
            }
        }
    }

    rt_interrupt_leave();
}

void lv_port_disp_init(void)
{
    rt_err_t result;

    void *lv_disp_buf1 = RT_NULL;
    void *lv_disp_buf2 = RT_NULL;

    lv_disp_buf1 = rt_malloc(DISP_BUF_SIZE * sizeof(lv_color_t));
    rt_memset(lv_disp_buf1, 0, DISP_BUF_SIZE * sizeof(lv_color_t));
    RT_ASSERT(lv_disp_buf1 != RT_NULL);

    lv_disp_buf2 = rt_malloc(DISP_BUF_SIZE * sizeof(lv_color_t));
    rt_memset(lv_disp_buf2, 0, DISP_BUF_SIZE * sizeof(lv_color_t));
    RT_ASSERT(lv_disp_buf2 != RT_NULL);

    lcd_device = rt_device_find("lcd");

    if (lcd_device == 0)
    {
        LOG_E("lcd_device error!");
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

    /*Initialize `disp_buf` with the buffer(s).*/
    lv_disp_draw_buf_init(&disp_buf, lv_disp_buf1, lv_disp_buf2, DISP_BUF_SIZE);

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

    g_disp_drv = disp_drv;
}
