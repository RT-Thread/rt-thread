/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-08-08     Yang        the first version
 */

#include <board.h>
#include <rtdevice.h>
#include <drv_lcd.h>
#include <string.h>

#include "fsl_iocon.h"
#include "fsl_sctimer.h"
#include "fsl_lcdc.h"


static  rt_uint16_t *lcd_framebuffer = RT_NULL;
static  rt_uint16_t *_rt_framebuffer = RT_NULL;

#define RT_HW_LCD_WIDTH     480
#define RT_HW_LCD_HEIGHT    272

static struct rt_device_graphic_info _lcd_info;
static struct rt_device  lcd;

#define LCD_PANEL_CLK (9 * 1000000UL)
#define LCD_PPL 480
#define LCD_HSW 2
#define LCD_HFP 8
#define LCD_HBP 43
#define LCD_LPP 272
#define LCD_VSW 10
#define LCD_VFP 4
#define LCD_VBP 12
#define LCD_POL_FLAGS kLCDC_InvertVsyncPolarity | kLCDC_InvertHsyncPolarity

#define LCD_WIDTH 480
#define LCD_HEIGHT 272

#define LCD_BITS_PER_PIXEL 16


static void lcd_gpio_init(void)
{
    const uint32_t port2_pin11_config = (
                                            IOCON_PIO_FUNC1 |                                        /* Pin is configured as LCD_PWR */
                                            IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                            IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                            IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                            IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                            IOCON_PIO_SLEW_STANDARD |                                /* Standard mode, output slew rate control is enabled */
                                            IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                        );
    IOCON_PinMuxSet(IOCON, PORT2_IDX, PIN11_IDX, port2_pin11_config); /* PORT2 PIN11 (coords: K3) is configured as LCD_PWR */
    const uint32_t port2_pin13_config = (
                                            IOCON_PIO_FUNC1 |                                        /* Pin is configured as LCD_DCLK */
                                            IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                            IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                            IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                            IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                            IOCON_PIO_SLEW_STANDARD |                                /* Standard mode, output slew rate control is enabled */
                                            IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                        );
    IOCON_PinMuxSet(IOCON, PORT2_IDX, PIN13_IDX, port2_pin13_config); /* PORT2 PIN13 (coords: P7) is configured as LCD_DCLK */
    const uint32_t port2_pin14_config = (
                                            IOCON_PIO_FUNC1 |                                        /* Pin is configured as LCD_FP */
                                            IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                            IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                            IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                            IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                            IOCON_PIO_SLEW_STANDARD |                                /* Standard mode, output slew rate control is enabled */
                                            IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                        );
    IOCON_PinMuxSet(IOCON, PORT2_IDX, PIN14_IDX, port2_pin14_config); /* PORT2 PIN14 (coords: L7) is configured as LCD_FP */
    const uint32_t port2_pin15_config = (
                                            IOCON_PIO_FUNC1 |                                        /* Pin is configured as LCD_AC */
                                            IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                            IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                            IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                            IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                            IOCON_PIO_SLEW_STANDARD |                                /* Standard mode, output slew rate control is enabled */
                                            IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                        );
    IOCON_PinMuxSet(IOCON, PORT2_IDX, PIN15_IDX, port2_pin15_config); /* PORT2 PIN15 (coords: M8) is configured as LCD_AC */
    const uint32_t port2_pin16_config = (
                                            IOCON_PIO_FUNC1 |                                        /* Pin is configured as LCD_LP */
                                            IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                            IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                            IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                            IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                            IOCON_PIO_SLEW_STANDARD |                                /* Standard mode, output slew rate control is enabled */
                                            IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                        );
    IOCON_PinMuxSet(IOCON, PORT2_IDX, PIN16_IDX, port2_pin16_config); /* PORT2 PIN16 (coords: L8) is configured as LCD_LP */
    const uint32_t port2_pin21_config = (
                                            IOCON_PIO_FUNC1 |                                        /* Pin is configured as LCD_VD(3) */
                                            IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                            IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                            IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                            IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                            IOCON_PIO_SLEW_STANDARD |                                /* Standard mode, output slew rate control is enabled */
                                            IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                        );
    IOCON_PinMuxSet(IOCON, PORT2_IDX, PIN21_IDX, port2_pin21_config); /* PORT2 PIN21 (coords: L10) is configured as LCD_VD(3) */
    const uint32_t port2_pin22_config = (
                                            IOCON_PIO_FUNC1 |                                        /* Pin is configured as LCD_VD(4) */
                                            IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                            IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                            IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                            IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                            IOCON_PIO_SLEW_STANDARD |                                /* Standard mode, output slew rate control is enabled */
                                            IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                        );
    IOCON_PinMuxSet(IOCON, PORT2_IDX, PIN22_IDX, port2_pin22_config); /* PORT2 PIN22 (coords: K10) is configured as LCD_VD(4) */
    const uint32_t port2_pin23_config = (
                                            IOCON_PIO_FUNC1 |                                        /* Pin is configured as LCD_VD(5) */
                                            IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                            IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                            IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                            IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                            IOCON_PIO_SLEW_STANDARD |                                /* Standard mode, output slew rate control is enabled */
                                            IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                        );
    IOCON_PinMuxSet(IOCON, PORT2_IDX, PIN23_IDX, port2_pin23_config); /* PORT2 PIN23 (coords: M14) is configured as LCD_VD(5) */
    const uint32_t port2_pin24_config = (
                                            IOCON_PIO_FUNC1 |                                        /* Pin is configured as LCD_VD(6) */
                                            IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                            IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                            IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                            IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                            IOCON_PIO_SLEW_STANDARD |                                /* Standard mode, output slew rate control is enabled */
                                            IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                        );
    IOCON_PinMuxSet(IOCON, PORT2_IDX, PIN24_IDX, port2_pin24_config); /* PORT2 PIN24 (coords: K14) is configured as LCD_VD(6) */
    const uint32_t port2_pin25_config = (
                                            IOCON_PIO_FUNC1 |                                        /* Pin is configured as LCD_VD(7) */
                                            IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                            IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                            IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                            IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                            IOCON_PIO_SLEW_STANDARD |                                /* Standard mode, output slew rate control is enabled */
                                            IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                        );
    IOCON_PinMuxSet(IOCON, PORT2_IDX, PIN25_IDX, port2_pin25_config); /* PORT2 PIN25 (coords: J11) is configured as LCD_VD(7) */
    const uint32_t port2_pin27_config = (
                                            IOCON_PIO_FUNC0 |                                        /* Pin is configured as PIO2_27 */
                                            IOCON_PIO_MODE_PULLUP |                                  /* Selects pull-up function */
                                            IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                            IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                            IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                            IOCON_PIO_SLEW_STANDARD |                                /* Standard mode, output slew rate control is enabled */
                                            IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                        );
    IOCON_PinMuxSet(IOCON, PORT2_IDX, PIN27_IDX, port2_pin27_config); /* PORT2 PIN27 (coords: H14) is configured as PIO2_27 */
    const uint32_t port2_pin28_config = (
                                            IOCON_PIO_FUNC1 |                                        /* Pin is configured as LCD_VD(10) */
                                            IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                            IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                            IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                            IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                            IOCON_PIO_SLEW_STANDARD |                                /* Standard mode, output slew rate control is enabled */
                                            IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                        );
    IOCON_PinMuxSet(IOCON, PORT2_IDX, PIN28_IDX, port2_pin28_config); /* PORT2 PIN28 (coords: G13) is configured as LCD_VD(10) */
    const uint32_t port2_pin29_config = (
                                            IOCON_PIO_FUNC1 |                                        /* Pin is configured as LCD_VD(11) */
                                            IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                            IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                            IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                            IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                            IOCON_PIO_SLEW_STANDARD |                                /* Standard mode, output slew rate control is enabled */
                                            IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                        );
    IOCON_PinMuxSet(IOCON, PORT2_IDX, PIN29_IDX, port2_pin29_config); /* PORT2 PIN29 (coords: G11) is configured as LCD_VD(11) */
    const uint32_t port2_pin30_config = (
                                            IOCON_PIO_FUNC1 |                                        /* Pin is configured as LCD_VD(12) */
                                            IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                            IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                            IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                            IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                            IOCON_PIO_SLEW_STANDARD |                                /* Standard mode, output slew rate control is enabled */
                                            IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                        );
    IOCON_PinMuxSet(IOCON, PORT2_IDX, PIN30_IDX, port2_pin30_config); /* PORT2 PIN30 (coords: F12) is configured as LCD_VD(12) */
    const uint32_t port2_pin31_config = (
                                            IOCON_PIO_FUNC1 |                                        /* Pin is configured as LCD_VD(13) */
                                            IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                            IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                            IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                            IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                            IOCON_PIO_SLEW_STANDARD |                                /* Standard mode, output slew rate control is enabled */
                                            IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                        );
    IOCON_PinMuxSet(IOCON, PORT2_IDX, PIN31_IDX, port2_pin31_config); /* PORT2 PIN31 (coords: D14) is configured as LCD_VD(13) */
    const uint32_t port3_pin0_config = (
                                           IOCON_PIO_FUNC1 |                                        /* Pin is configured as LCD_VD(14) */
                                           IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                           IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                           IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                           IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                           IOCON_PIO_SLEW_STANDARD |                                /* Standard mode, output slew rate control is enabled */
                                           IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                       );
    IOCON_PinMuxSet(IOCON, PORT3_IDX, PIN0_IDX, port3_pin0_config); /* PORT3 PIN0 (coords: D12) is configured as LCD_VD(14) */
    const uint32_t port3_pin1_config = (
                                           IOCON_PIO_FUNC1 |                                        /* Pin is configured as LCD_VD(15) */
                                           IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                           IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                           IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                           IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                           IOCON_PIO_SLEW_STANDARD |                                /* Standard mode, output slew rate control is enabled */
                                           IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                       );
    IOCON_PinMuxSet(IOCON, PORT3_IDX, PIN1_IDX, port3_pin1_config); /* PORT3 PIN1 (coords: D11) is configured as LCD_VD(15) */
    const uint32_t port3_pin5_config = (
                                           IOCON_PIO_FUNC1 |                                        /* Pin is configured as LCD_VD(19) */
                                           IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                           IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                           IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                           IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                           IOCON_PIO_SLEW_STANDARD |                                /* Standard mode, output slew rate control is enabled */
                                           IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                       );
    IOCON_PinMuxSet(IOCON, PORT3_IDX, PIN5_IDX, port3_pin5_config); /* PORT3 PIN5 (coords: B10) is configured as LCD_VD(19) */
    const uint32_t port3_pin6_config = (
                                           IOCON_PIO_FUNC1 |                                        /* Pin is configured as LCD_VD(20) */
                                           IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                           IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                           IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                           IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                           IOCON_PIO_SLEW_STANDARD |                                /* Standard mode, output slew rate control is enabled */
                                           IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                       );
    IOCON_PinMuxSet(IOCON, PORT3_IDX, PIN6_IDX, port3_pin6_config); /* PORT3 PIN6 (coords: C9) is configured as LCD_VD(20) */
    const uint32_t port3_pin7_config = (
                                           IOCON_PIO_FUNC1 |                                        /* Pin is configured as LCD_VD(21) */
                                           IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                           IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                           IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                           IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                           IOCON_PIO_SLEW_STANDARD |                                /* Standard mode, output slew rate control is enabled */
                                           IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                       );
    IOCON_PinMuxSet(IOCON, PORT3_IDX, PIN7_IDX, port3_pin7_config); /* PORT3 PIN7 (coords: B8) is configured as LCD_VD(21) */
    const uint32_t port3_pin8_config = (
                                           IOCON_PIO_FUNC1 |                                        /* Pin is configured as LCD_VD(22) */
                                           IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                           IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                           IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                           IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                           IOCON_PIO_SLEW_STANDARD |                                /* Standard mode, output slew rate control is enabled */
                                           IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                       );
    IOCON_PinMuxSet(IOCON, PORT3_IDX, PIN8_IDX, port3_pin8_config); /* PORT3 PIN8 (coords: A7) is configured as LCD_VD(22) */
    const uint32_t port3_pin9_config = (
                                           IOCON_PIO_FUNC1 |                                        /* Pin is configured as LCD_VD(23) */
                                           IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                           IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                           IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                           IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                           IOCON_PIO_SLEW_STANDARD |                                /* Standard mode, output slew rate control is enabled */
                                           IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                       );
    IOCON_PinMuxSet(IOCON, PORT3_IDX, PIN9_IDX, port3_pin9_config); /* PORT3 PIN9 (coords: C7) is configured as LCD_VD(23) */
}

void LCD_IRQHandler(void)
{
    uint32_t intStatus = LCDC_GetEnabledInterruptsPendingStatus(LCD);

    LCDC_ClearInterruptsStatus(LCD, intStatus);

    if (intStatus & kLCDC_VerticalCompareInterrupt)
    {
        //s_frameEndFlag = true;
    }
    //__DSB();
}

/* RT-Thread Device Interface */
static rt_err_t rt_lcd_init(rt_device_t dev)
{

    /* Route Main clock to LCD. */
    CLOCK_AttachClk(kMCLK_to_LCD_CLK);

    CLOCK_SetClkDiv(kCLOCK_DivLcdClk, 1, true);

    /*LCD管脚配置*/
    lcd_gpio_init();

    /* Set the back light PWM. */
    {
        sctimer_config_t config;
        sctimer_pwm_signal_param_t pwmParam;
        uint32_t event;

        CLOCK_AttachClk(kMCLK_to_SCT_CLK);

        CLOCK_SetClkDiv(kCLOCK_DivSctClk, 2, true);

        SCTIMER_GetDefaultConfig(&config);

        SCTIMER_Init(SCT0, &config);

        pwmParam.output = kSCTIMER_Out_5;
        pwmParam.level = kSCTIMER_HighTrue;
        pwmParam.dutyCyclePercent = 5;

        SCTIMER_SetupPwm(SCT0, &pwmParam, kSCTIMER_CenterAlignedPwm, 1000U, CLOCK_GetFreq(kCLOCK_Sct), &event);
    }

    lcd_framebuffer = rt_malloc_align(sizeof(rt_uint16_t) * RT_HW_LCD_HEIGHT * RT_HW_LCD_WIDTH, 32);
    rt_memset(lcd_framebuffer, 0, sizeof(rt_uint16_t) * RT_HW_LCD_HEIGHT * RT_HW_LCD_WIDTH);

    {
        /* Initialize the display. */
        lcdc_config_t lcdConfig;

        LCDC_GetDefaultConfig(&lcdConfig);

        lcdConfig.panelClock_Hz = LCD_PANEL_CLK;
        lcdConfig.ppl = LCD_PPL;
        lcdConfig.hsw = LCD_HSW;
        lcdConfig.hfp = LCD_HFP;
        lcdConfig.hbp = LCD_HBP;
        lcdConfig.lpp = LCD_LPP;
        lcdConfig.vsw = LCD_VSW;
        lcdConfig.vfp = LCD_VFP;
        lcdConfig.vbp = LCD_VBP;
        lcdConfig.polarityFlags = LCD_POL_FLAGS;
        lcdConfig.upperPanelAddr = (uint32_t)lcd_framebuffer;//VRAM_ADDR;
        lcdConfig.bpp = kLCDC_16BPP565;
        lcdConfig.display = kLCDC_DisplayTFT;
        lcdConfig.swapRedBlue = true;

        LCDC_Init(LCD, &lcdConfig, CLOCK_GetFreq(kCLOCK_LCD));

        /* Trigger interrupt at start of every vertical back porch. */
        LCDC_SetVerticalInterruptMode(LCD, kLCDC_StartOfBackPorch);
        LCDC_EnableInterrupts(LCD, kLCDC_VerticalCompareInterrupt);
        NVIC_EnableIRQ(LCD_IRQn);

        LCDC_Start(LCD);
        LCDC_PowerUp(LCD);
    }

    return RT_EOK;
}

static rt_err_t rt_lcd_control(rt_device_t dev, int cmd, void *args)
{
    switch (cmd)
    {
    case RTGRAPHIC_CTRL_RECT_UPDATE:
    {
        struct rt_device_rect_info *rect_info = (struct rt_device_rect_info *)args;

        /* 先指向绘图 buff 显示 */
        LCD->UPBASE = (rt_uint32_t)_rt_framebuffer;

        /* 从绘图 buff copy 数据到显示 buff */
        if (rect_info->width * rect_info->height < RT_HW_LCD_WIDTH * RT_HW_LCD_HEIGHT / 5 * 3)
        {
            int index = 0;
            rt_uint8_t *p = (rt_uint8_t *)lcd_framebuffer;
            rt_uint8_t *q = (rt_uint8_t *)_rt_framebuffer;

            p += (rect_info->x + rect_info->y * RT_HW_LCD_WIDTH) * sizeof(rt_uint16_t);
            q += (rect_info->x + rect_info->y * RT_HW_LCD_WIDTH) * sizeof(rt_uint16_t);

            for (index = 0; index < rect_info->height; index ++)
            {
                memcpy((void *)p, (void *)q, sizeof(rt_uint16_t) * rect_info->width);
                p += RT_HW_LCD_WIDTH * sizeof(rt_uint16_t);
                q += RT_HW_LCD_WIDTH * sizeof(rt_uint16_t);
            }
        }
        else
        {
            memcpy((void *)lcd_framebuffer, _rt_framebuffer, sizeof(rt_uint16_t)*RT_HW_LCD_HEIGHT * RT_HW_LCD_WIDTH);
        }
        /* 指回显示 buff */
        LCD->UPBASE = (rt_uint32_t)lcd_framebuffer;
        rt_kprintf("====> rect_info : %d %d %d %d\n", rect_info->x, rect_info->y, rect_info->width, rect_info->height);
    }
    break;
    case RTGRAPHIC_CTRL_POWERON:
        break;
    case RTGRAPHIC_CTRL_POWEROFF:
        break;
    case RTGRAPHIC_CTRL_GET_INFO:
        memcpy(args, &_lcd_info, sizeof(_lcd_info));
        break;
    case RTGRAPHIC_CTRL_SET_MODE:
        break;
    }

    return RT_EOK;
}

rt_uint16_t* get_lcd_framebuffer(void)
{
    return lcd_framebuffer;
}

void lcd_clear(rt_uint16_t color)
{
    volatile rt_uint16_t *p = (rt_uint16_t *)lcd_framebuffer;
    int x, y;

    for (y = 0; y <= RT_HW_LCD_HEIGHT; y++)
    {
        for (x = 0; x <= RT_HW_LCD_WIDTH; x++)
        {
            *p++ = color; /* red */
        }
    }
}

void rt_hw_lcd_init(void)
{
    _rt_framebuffer = rt_malloc_align(sizeof(rt_uint16_t) * RT_HW_LCD_HEIGHT * RT_HW_LCD_WIDTH, 32);
    if (_rt_framebuffer == RT_NULL) return; /* no memory yet */
    _lcd_info.bits_per_pixel = LCD_BITS_PER_PIXEL;
    _lcd_info.pixel_format = RTGRAPHIC_PIXEL_FORMAT_RGB565;     // RTGRAPHIC_PIXEL_FORMAT_ARGB888
    _lcd_info.framebuffer = (void *)_rt_framebuffer;
    _lcd_info.width = RT_HW_LCD_WIDTH;
    _lcd_info.height = RT_HW_LCD_HEIGHT;

    /* init device structure */
    lcd.type = RT_Device_Class_Graphic;
    lcd.init = rt_lcd_init;
    lcd.open = RT_NULL;
    lcd.close = RT_NULL;
    lcd.control = rt_lcd_control;
    lcd.user_data = (void *)&_lcd_info;

    /* register lcd device to RT-Thread */
    rt_device_register(&lcd, "lcd", RT_DEVICE_FLAG_RDWR);

    rt_lcd_init(&lcd);
}

void lcd_test(void)
{
    lcd_clear(0xf800);
    rt_thread_delay(200);
    lcd_clear(0x07e0);
    rt_thread_delay(200);
    lcd_clear(0x001f);
    rt_thread_delay(200);
}
#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT(lcd_clear, lcd_clear);
FINSH_FUNCTION_EXPORT(lcd_test, lcd_test);
#ifdef FINSH_USING_MSH
MSH_CMD_EXPORT(lcd_clear, lcd_clear);
MSH_CMD_EXPORT(lcd_test, lcd_test);
#endif
#endif
