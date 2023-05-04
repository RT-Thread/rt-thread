/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-10-18     Meco Man     The first version
 * 2021-12-24       Rb         Refresh using dma2d
 */
#include <lvgl.h>

//#define DRV_DEBUG
#define LOG_TAG             "LVGL.port.disp"
#include <drv_log.h>

#if LV_USE_NXP_SOC
#include "fsl_gpio.h"
#include "fsl_elcdif.h"
#include "fsl_cache.h"
#endif

/*A static or global variable to store the buffers*/
static lv_disp_draw_buf_t disp_buf;

static lv_disp_drv_t disp_drv;  /*Descriptor of a display driver*/

/* Macros for panel. */
#define LCD_FB_BYTE_PER_PIXEL 2
#define LCD_POL_FLAGS \
    (kELCDIF_DataEnableActiveHigh | kELCDIF_VsyncActiveLow | kELCDIF_HsyncActiveLow | kELCDIF_DriveDataOnRisingClkEdge)
#define LCD_LCDIF_DATA_BUS kELCDIF_DataBus16Bit

/* Back light. */
#define LCD_BL_GPIO     GPIO2
#define LCD_BL_GPIO_PIN 31

#define DEMO_FB_ALIGN LV_ATTRIBUTE_MEM_ALIGN_SIZE
#define DISP_BUF_SIZE (((LCD_WIDTH * LCD_HEIGHT * LCD_FB_BYTE_PER_PIXEL) + DEMO_FB_ALIGN - 1) & ~(DEMO_FB_ALIGN - 1))

/*******************************************************************************
 * Variables
 ******************************************************************************/
static volatile bool s_framePending;

static lv_disp_drv_t disp_drv; /*Descriptor of a display driver*/

SDK_ALIGN(static uint8_t s_frameBuffer[2][DISP_BUF_SIZE], DEMO_FB_ALIGN);

static rt_sem_t s_frameSema = RT_NULL;

static void lcd_fb_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
    rt_sem_take(s_frameSema, RT_WAITING_FOREVER);

    DCACHE_CleanInvalidateByRange((uint32_t)color_p, DISP_BUF_SIZE);

    ELCDIF_SetNextBufferAddr(LCDIF, (uint32_t)color_p);

    s_framePending = true;
}

static void DEMO_InitLcdClock(void)
{
    /*
     * The desired output frame rate is 60Hz. So the pixel clock frequency is:
     * (480 + 41 + 4 + 18) * (272 + 10 + 4 + 2) * 60 = 9.2M.
     * Here set the LCDIF pixel clock to 9.3M.
     */

    /*
     * Initialize the Video PLL.
     * Video PLL output clock is OSC24M * (loopDivider + (denominator / numerator)) / postDivider = 93MHz.
     */
    clock_video_pll_config_t config =
    {
        .loopDivider = 31,
        .postDivider = 8,
        .numerator   = 0,
        .denominator = 0,
    };

    CLOCK_InitVideoPll(&config);

    /*
     * 000 derive clock from PLL2
     * 001 derive clock from PLL3 PFD3
     * 010 derive clock from PLL5
     * 011 derive clock from PLL2 PFD0
     * 100 derive clock from PLL2 PFD1
     * 101 derive clock from PLL3 PFD1
     */
    CLOCK_SetMux(kCLOCK_LcdifPreMux, 2);

    CLOCK_SetDiv(kCLOCK_LcdifPreDiv, 4);

    CLOCK_SetDiv(kCLOCK_LcdifDiv, 1);
}

static void DEMO_InitLcdBackLight(void)
{
    const gpio_pin_config_t config =
    {
        kGPIO_DigitalOutput,
        1,
        kGPIO_NoIntmode,
    };

    /* Backlight. */
    GPIO_PinInit(LCD_BL_GPIO, LCD_BL_GPIO_PIN, &config);
}

#if LV_USE_GPU_NXP_PXP
static void DEMO_CleanInvalidateCache(lv_disp_drv_t *disp_drv)
{
    SCB_CleanInvalidateDCache();
}
#endif

static void DEMO_InitLcd(void)
{
    /* Initialize the display. */
    const elcdif_rgb_mode_config_t config =
    {
        .panelWidth    = LCD_WIDTH,
        .panelHeight   = LCD_HEIGHT,
        .hsw           = LCD_HSW,
        .hfp           = LCD_HFP,
        .hbp           = LCD_HBP,
        .vsw           = LCD_VSW,
        .vfp           = LCD_VFP,
        .vbp           = LCD_VBP,
        .polarityFlags = LCD_POL_FLAGS,
        /* lvgl starts render in frame buffer 0, so show frame buffer 1 first. */
        .bufferAddr  = (uint32_t)s_frameBuffer[1],
        .pixelFormat = kELCDIF_PixelFormatRGB565,
        .dataBus     = LCD_LCDIF_DATA_BUS,
    };

    /* Clear frame buffer. */
    rt_memset((void *)s_frameBuffer, 0, sizeof(s_frameBuffer));

    s_frameSema = rt_sem_create("lvgl_sem", 1, RT_IPC_FLAG_PRIO);

    if (RT_NULL == s_frameSema)
    {
        rt_kprintf("lvgl semaphore create failed\r\n");
        RT_ASSERT(0);
    }

    /* No frame pending. */
    s_framePending = false;

    NVIC_SetPriority(LCDIF_IRQn, 3);

    DEMO_InitLcdClock();

    ELCDIF_RgbModeInit(LCDIF, &config);

    ELCDIF_EnableInterrupts(LCDIF, kELCDIF_CurFrameDoneInterruptEnable);

    NVIC_EnableIRQ(LCDIF_IRQn);

    ELCDIF_RgbModeStart(LCDIF);

    DEMO_InitLcdBackLight();
}

void LCDIF_IRQHandler(void)
{
    rt_interrupt_enter();

    uint32_t intStatus = ELCDIF_GetInterruptStatus(LCDIF);

    ELCDIF_ClearInterruptStatus(LCDIF, intStatus);

    if (s_framePending)
    {
        if (intStatus & kELCDIF_CurFrameDone)
        {
            /* IMPORTANT!!!
             * Inform the graphics library that you are ready with the flushing*/
            lv_disp_flush_ready(&disp_drv);

            s_framePending = false;

            rt_sem_release(s_frameSema);
        }
    }

    rt_interrupt_leave();

    SDK_ISR_EXIT_BARRIER;
}

void lv_port_disp_init(void)
{
    lv_disp_draw_buf_init(&disp_buf, s_frameBuffer[0], s_frameBuffer[1], LCD_WIDTH * LCD_HEIGHT);

    /*-------------------------
     * Initialize your display
     * -----------------------*/
    DEMO_InitLcd();

    /*-----------------------------------
     * Register the display in LittlevGL
     *----------------------------------*/

    lv_disp_drv_init(&disp_drv); /*Basic initialization*/

    /*Set up the functions to access to your display*/

    /*Set the resolution of the display*/
    disp_drv.hor_res = LCD_WIDTH;
    disp_drv.ver_res = LCD_HEIGHT;

    /*Used to copy the buffer's content to the display*/
    disp_drv.flush_cb = lcd_fb_flush;

#if LV_USE_GPU_NXP_PXP
    disp_drv.clean_dcache_cb = DEMO_CleanInvalidateCache;
#endif

    /*Set a display buffer*/
    disp_drv.draw_buf = &disp_buf;

    /* Partial refresh */
    disp_drv.full_refresh = 1;

    /*Finally register the driver*/
    lv_disp_drv_register(&disp_drv);
}
