/*
 * File      : usart.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-10-30     Tanek        the first version
 */

#include <board.h>
#include <rtthread.h>

#include "fsl_common.h"
#include "fsl_elcdif.h"
#include "fsl_gpio.h"

//#define LCD_DEBUG

#ifdef PKG_USING_GUIENGINE

#define APP_HSW 41
#define APP_HFP 4
#define APP_HBP 8
#define APP_VSW 10
#define APP_VFP 4
#define APP_VBP 2
#define APP_POL_FLAGS \
    (kELCDIF_DataEnableActiveHigh | kELCDIF_VsyncActiveLow | kELCDIF_HsyncActiveLow | kELCDIF_DriveDataOnRisingClkEdge)

#define FRAME_BUFFER_ALIGN              64
        
#define LCD_PIXEL_T                     uint16_t
#define LCD_BITS_PER_PIXEL              (sizeof(LCD_PIXEL_T) * 8)

#define LCD_INIT_DATA                   (0x00)

        
/* Display. */
#define LCD_DISP_GPIO                   GPIO1
#define LCD_DISP_GPIO_PIN               2
/* Back light. */
#define LCD_BL_GPIO                     GPIO2
#define LCD_BL_GPIO_PIN                 31
        
#define APP_ELCDIF LCDIF
#define APP_LCDIF_DATA_BUS              kELCDIF_DataBus16Bit
#define FRAME_BUFFER_COUNT              2

#define RT_HW_LCD_WIDTH                 ((uint16_t)800)     /* LCD PIXEL WIDTH            */
#define RT_HW_LCD_HEIGHT                ((uint16_t)480)     /* LCD PIXEL HEIGHT           */
        
ALIGN(FRAME_BUFFER_ALIGN)
static LCD_PIXEL_T lcdif_frame_buffer[FRAME_BUFFER_COUNT][RT_HW_LCD_HEIGHT][RT_HW_LCD_WIDTH] SECTION("NonCacheable");


#ifdef LCD_DEBUG
static volatile bool s_frameDone = false;
#endif

struct imxrt_lcd_t
{
    struct rt_device_graphic_info lcd_info;
    struct rt_device lcd;
    struct rt_semaphore lcd_sem;
    rt_uint32_t index;              //lcd buffer
    LCD_PIXEL_T * framebuffer;
    bool update;
};

static struct imxrt_lcd_t imxrt_lcd;

static void _lcd_gpio_config(void) 
{
  CLOCK_EnableClock(kCLOCK_Iomuxc);          /* iomuxc clock (iomuxc_clk_enable): 0x03u */

  IOMUXC_SetPinMux(
      IOMUXC_GPIO_AD_B0_02_GPIO1_IO02,        /* GPIO_AD_B0_02 is configured as GPIO1_IO02 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_B0_00_LCD_CLK,              /* GPIO_B0_00 is configured as LCD_CLK */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_B0_01_LCD_ENABLE,           /* GPIO_B0_01 is configured as LCD_ENABLE */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_B0_02_LCD_HSYNC,            /* GPIO_B0_02 is configured as LCD_HSYNC */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_B0_03_LCD_VSYNC,            /* GPIO_B0_03 is configured as LCD_VSYNC */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_B0_04_LCD_DATA00,           /* GPIO_B0_04 is configured as LCD_DATA00 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_B0_05_LCD_DATA01,           /* GPIO_B0_05 is configured as LCD_DATA01 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_B0_06_LCD_DATA02,           /* GPIO_B0_06 is configured as LCD_DATA02 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_B0_07_LCD_DATA03,           /* GPIO_B0_07 is configured as LCD_DATA03 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_B0_08_LCD_DATA04,           /* GPIO_B0_08 is configured as LCD_DATA04 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_B0_09_LCD_DATA05,           /* GPIO_B0_09 is configured as LCD_DATA05 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_B0_10_LCD_DATA06,           /* GPIO_B0_10 is configured as LCD_DATA06 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_B0_11_LCD_DATA07,           /* GPIO_B0_11 is configured as LCD_DATA07 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_B0_12_LCD_DATA08,           /* GPIO_B0_12 is configured as LCD_DATA08 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_B0_13_LCD_DATA09,           /* GPIO_B0_13 is configured as LCD_DATA09 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_B0_14_LCD_DATA10,           /* GPIO_B0_14 is configured as LCD_DATA10 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_B0_15_LCD_DATA11,           /* GPIO_B0_15 is configured as LCD_DATA11 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_B1_00_LCD_DATA12,           /* GPIO_B1_00 is configured as LCD_DATA12 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_B1_01_LCD_DATA13,           /* GPIO_B1_01 is configured as LCD_DATA13 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_B1_02_LCD_DATA14,           /* GPIO_B1_02 is configured as LCD_DATA14 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_B1_03_LCD_DATA15,           /* GPIO_B1_03 is configured as LCD_DATA15 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_B1_15_GPIO2_IO31,           /* GPIO_B1_15 is configured as GPIO2_IO31 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_AD_B0_02_GPIO1_IO02,        /* GPIO_AD_B0_02 PAD functional properties : */
      0x10B0u);                               /* Slew Rate Field: Slow Slew Rate
                                                 Drive Strength Field: R0/6
                                                 Speed Field: medium(100MHz)
                                                 Open Drain Enable Field: Open Drain Disabled
                                                 Pull / Keep Enable Field: Pull/Keeper Enabled
                                                 Pull / Keep Select Field: Keeper
                                                 Pull Up / Down Config. Field: 100K Ohm Pull Down
                                                 Hyst. Enable Field: Hysteresis Disabled */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_B0_00_LCD_CLK,              /* GPIO_B0_00 PAD functional properties : */
      0x01B0B0u);                             /* Slew Rate Field: Slow Slew Rate
                                                 Drive Strength Field: R0/6
                                                 Speed Field: medium(100MHz)
                                                 Open Drain Enable Field: Open Drain Disabled
                                                 Pull / Keep Enable Field: Pull/Keeper Enabled
                                                 Pull / Keep Select Field: Pull
                                                 Pull Up / Down Config. Field: 100K Ohm Pull Up
                                                 Hyst. Enable Field: Hysteresis Enabled */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_B0_01_LCD_ENABLE,           /* GPIO_B0_01 PAD functional properties : */
      0x01B0B0u);                             /* Slew Rate Field: Slow Slew Rate
                                                 Drive Strength Field: R0/6
                                                 Speed Field: medium(100MHz)
                                                 Open Drain Enable Field: Open Drain Disabled
                                                 Pull / Keep Enable Field: Pull/Keeper Enabled
                                                 Pull / Keep Select Field: Pull
                                                 Pull Up / Down Config. Field: 100K Ohm Pull Up
                                                 Hyst. Enable Field: Hysteresis Enabled */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_B0_02_LCD_HSYNC,            /* GPIO_B0_02 PAD functional properties : */
      0x01B0B0u);                             /* Slew Rate Field: Slow Slew Rate
                                                 Drive Strength Field: R0/6
                                                 Speed Field: medium(100MHz)
                                                 Open Drain Enable Field: Open Drain Disabled
                                                 Pull / Keep Enable Field: Pull/Keeper Enabled
                                                 Pull / Keep Select Field: Pull
                                                 Pull Up / Down Config. Field: 100K Ohm Pull Up
                                                 Hyst. Enable Field: Hysteresis Enabled */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_B0_03_LCD_VSYNC,            /* GPIO_B0_03 PAD functional properties : */
      0x01B0B0u);                             /* Slew Rate Field: Slow Slew Rate
                                                 Drive Strength Field: R0/6
                                                 Speed Field: medium(100MHz)
                                                 Open Drain Enable Field: Open Drain Disabled
                                                 Pull / Keep Enable Field: Pull/Keeper Enabled
                                                 Pull / Keep Select Field: Pull
                                                 Pull Up / Down Config. Field: 100K Ohm Pull Up
                                                 Hyst. Enable Field: Hysteresis Enabled */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_B0_04_LCD_DATA00,           /* GPIO_B0_04 PAD functional properties : */
      0x01B0B0u);                             /* Slew Rate Field: Slow Slew Rate
                                                 Drive Strength Field: R0/6
                                                 Speed Field: medium(100MHz)
                                                 Open Drain Enable Field: Open Drain Disabled
                                                 Pull / Keep Enable Field: Pull/Keeper Enabled
                                                 Pull / Keep Select Field: Pull
                                                 Pull Up / Down Config. Field: 100K Ohm Pull Up
                                                 Hyst. Enable Field: Hysteresis Enabled */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_B0_05_LCD_DATA01,           /* GPIO_B0_05 PAD functional properties : */
      0x01B0B0u);                             /* Slew Rate Field: Slow Slew Rate
                                                 Drive Strength Field: R0/6
                                                 Speed Field: medium(100MHz)
                                                 Open Drain Enable Field: Open Drain Disabled
                                                 Pull / Keep Enable Field: Pull/Keeper Enabled
                                                 Pull / Keep Select Field: Pull
                                                 Pull Up / Down Config. Field: 100K Ohm Pull Up
                                                 Hyst. Enable Field: Hysteresis Enabled */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_B0_06_LCD_DATA02,           /* GPIO_B0_06 PAD functional properties : */
      0x01B0B0u);                             /* Slew Rate Field: Slow Slew Rate
                                                 Drive Strength Field: R0/6
                                                 Speed Field: medium(100MHz)
                                                 Open Drain Enable Field: Open Drain Disabled
                                                 Pull / Keep Enable Field: Pull/Keeper Enabled
                                                 Pull / Keep Select Field: Pull
                                                 Pull Up / Down Config. Field: 100K Ohm Pull Up
                                                 Hyst. Enable Field: Hysteresis Enabled */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_B0_07_LCD_DATA03,           /* GPIO_B0_07 PAD functional properties : */
      0x01B0B0u);                             /* Slew Rate Field: Slow Slew Rate
                                                 Drive Strength Field: R0/6
                                                 Speed Field: medium(100MHz)
                                                 Open Drain Enable Field: Open Drain Disabled
                                                 Pull / Keep Enable Field: Pull/Keeper Enabled
                                                 Pull / Keep Select Field: Pull
                                                 Pull Up / Down Config. Field: 100K Ohm Pull Up
                                                 Hyst. Enable Field: Hysteresis Enabled */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_B0_08_LCD_DATA04,           /* GPIO_B0_08 PAD functional properties : */
      0x01B0B0u);                             /* Slew Rate Field: Slow Slew Rate
                                                 Drive Strength Field: R0/6
                                                 Speed Field: medium(100MHz)
                                                 Open Drain Enable Field: Open Drain Disabled
                                                 Pull / Keep Enable Field: Pull/Keeper Enabled
                                                 Pull / Keep Select Field: Pull
                                                 Pull Up / Down Config. Field: 100K Ohm Pull Up
                                                 Hyst. Enable Field: Hysteresis Enabled */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_B0_09_LCD_DATA05,           /* GPIO_B0_09 PAD functional properties : */
      0x01B0B0u);                             /* Slew Rate Field: Slow Slew Rate
                                                 Drive Strength Field: R0/6
                                                 Speed Field: medium(100MHz)
                                                 Open Drain Enable Field: Open Drain Disabled
                                                 Pull / Keep Enable Field: Pull/Keeper Enabled
                                                 Pull / Keep Select Field: Pull
                                                 Pull Up / Down Config. Field: 100K Ohm Pull Up
                                                 Hyst. Enable Field: Hysteresis Enabled */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_B0_10_LCD_DATA06,           /* GPIO_B0_10 PAD functional properties : */
      0x01B0B0u);                             /* Slew Rate Field: Slow Slew Rate
                                                 Drive Strength Field: R0/6
                                                 Speed Field: medium(100MHz)
                                                 Open Drain Enable Field: Open Drain Disabled
                                                 Pull / Keep Enable Field: Pull/Keeper Enabled
                                                 Pull / Keep Select Field: Pull
                                                 Pull Up / Down Config. Field: 100K Ohm Pull Up
                                                 Hyst. Enable Field: Hysteresis Enabled */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_B0_11_LCD_DATA07,           /* GPIO_B0_11 PAD functional properties : */
      0x01B0B0u);                             /* Slew Rate Field: Slow Slew Rate
                                                 Drive Strength Field: R0/6
                                                 Speed Field: medium(100MHz)
                                                 Open Drain Enable Field: Open Drain Disabled
                                                 Pull / Keep Enable Field: Pull/Keeper Enabled
                                                 Pull / Keep Select Field: Pull
                                                 Pull Up / Down Config. Field: 100K Ohm Pull Up
                                                 Hyst. Enable Field: Hysteresis Enabled */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_B0_12_LCD_DATA08,           /* GPIO_B0_12 PAD functional properties : */
      0x01B0B0u);                             /* Slew Rate Field: Slow Slew Rate
                                                 Drive Strength Field: R0/6
                                                 Speed Field: medium(100MHz)
                                                 Open Drain Enable Field: Open Drain Disabled
                                                 Pull / Keep Enable Field: Pull/Keeper Enabled
                                                 Pull / Keep Select Field: Pull
                                                 Pull Up / Down Config. Field: 100K Ohm Pull Up
                                                 Hyst. Enable Field: Hysteresis Enabled */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_B0_13_LCD_DATA09,           /* GPIO_B0_13 PAD functional properties : */
      0x01B0B0u);                             /* Slew Rate Field: Slow Slew Rate
                                                 Drive Strength Field: R0/6
                                                 Speed Field: medium(100MHz)
                                                 Open Drain Enable Field: Open Drain Disabled
                                                 Pull / Keep Enable Field: Pull/Keeper Enabled
                                                 Pull / Keep Select Field: Pull
                                                 Pull Up / Down Config. Field: 100K Ohm Pull Up
                                                 Hyst. Enable Field: Hysteresis Enabled */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_B0_14_LCD_DATA10,           /* GPIO_B0_14 PAD functional properties : */
      0x01B0B0u);                             /* Slew Rate Field: Slow Slew Rate
                                                 Drive Strength Field: R0/6
                                                 Speed Field: medium(100MHz)
                                                 Open Drain Enable Field: Open Drain Disabled
                                                 Pull / Keep Enable Field: Pull/Keeper Enabled
                                                 Pull / Keep Select Field: Pull
                                                 Pull Up / Down Config. Field: 100K Ohm Pull Up
                                                 Hyst. Enable Field: Hysteresis Enabled */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_B0_15_LCD_DATA11,           /* GPIO_B0_15 PAD functional properties : */
      0x01B0B0u);                             /* Slew Rate Field: Slow Slew Rate
                                                 Drive Strength Field: R0/6
                                                 Speed Field: medium(100MHz)
                                                 Open Drain Enable Field: Open Drain Disabled
                                                 Pull / Keep Enable Field: Pull/Keeper Enabled
                                                 Pull / Keep Select Field: Pull
                                                 Pull Up / Down Config. Field: 100K Ohm Pull Up
                                                 Hyst. Enable Field: Hysteresis Enabled */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_B1_00_LCD_DATA12,           /* GPIO_B1_00 PAD functional properties : */
      0x01B0B0u);                             /* Slew Rate Field: Slow Slew Rate
                                                 Drive Strength Field: R0/6
                                                 Speed Field: medium(100MHz)
                                                 Open Drain Enable Field: Open Drain Disabled
                                                 Pull / Keep Enable Field: Pull/Keeper Enabled
                                                 Pull / Keep Select Field: Pull
                                                 Pull Up / Down Config. Field: 100K Ohm Pull Up
                                                 Hyst. Enable Field: Hysteresis Enabled */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_B1_01_LCD_DATA13,           /* GPIO_B1_01 PAD functional properties : */
      0x01B0B0u);                             /* Slew Rate Field: Slow Slew Rate
                                                 Drive Strength Field: R0/6
                                                 Speed Field: medium(100MHz)
                                                 Open Drain Enable Field: Open Drain Disabled
                                                 Pull / Keep Enable Field: Pull/Keeper Enabled
                                                 Pull / Keep Select Field: Pull
                                                 Pull Up / Down Config. Field: 100K Ohm Pull Up
                                                 Hyst. Enable Field: Hysteresis Enabled */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_B1_02_LCD_DATA14,           /* GPIO_B1_02 PAD functional properties : */
      0x01B0B0u);                             /* Slew Rate Field: Slow Slew Rate
                                                 Drive Strength Field: R0/6
                                                 Speed Field: medium(100MHz)
                                                 Open Drain Enable Field: Open Drain Disabled
                                                 Pull / Keep Enable Field: Pull/Keeper Enabled
                                                 Pull / Keep Select Field: Pull
                                                 Pull Up / Down Config. Field: 100K Ohm Pull Up
                                                 Hyst. Enable Field: Hysteresis Enabled */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_B1_03_LCD_DATA15,           /* GPIO_B1_03 PAD functional properties : */
      0x01B0B0u);                             /* Slew Rate Field: Slow Slew Rate
                                                 Drive Strength Field: R0/6
                                                 Speed Field: medium(100MHz)
                                                 Open Drain Enable Field: Open Drain Disabled
                                                 Pull / Keep Enable Field: Pull/Keeper Enabled
                                                 Pull / Keep Select Field: Pull
                                                 Pull Up / Down Config. Field: 100K Ohm Pull Up
                                                 Hyst. Enable Field: Hysteresis Enabled */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_B1_15_GPIO2_IO31,           /* GPIO_B1_15 PAD functional properties : */
      0x10B0u);                               /* Slew Rate Field: Slow Slew Rate
                                                 Drive Strength Field: R0/6
                                                 Speed Field: medium(100MHz)
                                                 Open Drain Enable Field: Open Drain Disabled
                                                 Pull / Keep Enable Field: Pull/Keeper Enabled
                                                 Pull / Keep Select Field: Keeper
                                                 Pull Up / Down Config. Field: 100K Ohm Pull Down
                                                 Hyst. Enable Field: Hysteresis Disabled */
}

static void _lcd_clock_config(void)
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
    clock_video_pll_config_t config = {
        .loopDivider = 31, .postDivider = 8, .numerator = 0, .denominator = 0,
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
    CLOCK_SetMux(kCLOCK_Lcdif1PreMux, 2);

    CLOCK_SetDiv(kCLOCK_Lcdif1PreDiv, 4);

    CLOCK_SetDiv(kCLOCK_Lcdif1Div, 1);

    /*
     * 000 derive clock from divided pre-muxed lcdif1 clock
     * 001 derive clock from ipp_di0_clk
     * 010 derive clock from ipp_di1_clk
     * 011 derive clock from ldb_di0_clk
     * 100 derive clock from ldb_di1_clk
     */
    CLOCK_SetMux(kCLOCK_Lcdif1Mux, 0);
}

/* Initialize the LCD_DISP. */
static void _lcd_hardware_reset(void)
{
    volatile uint32_t i = 0x100U;

    gpio_pin_config_t config = {
        kGPIO_DigitalOutput, 0,
    };

    /* Reset the LCD. */
    GPIO_PinInit(LCD_DISP_GPIO, LCD_DISP_GPIO_PIN, &config);

    GPIO_PinWrite(LCD_DISP_GPIO, LCD_DISP_GPIO_PIN, 0);

    while (i--)
    {
    }

    GPIO_PinWrite(LCD_DISP_GPIO, LCD_DISP_GPIO_PIN, 1);

    /* Backlight. */
    config.outputLogic = 1;
    GPIO_PinInit(LCD_BL_GPIO, LCD_BL_GPIO_PIN, &config);
}

static void _lcdif_init(void)
{
    const elcdif_rgb_mode_config_t config = {
        .panelWidth = RT_HW_LCD_WIDTH,
        .panelHeight = RT_HW_LCD_HEIGHT,
        .hsw = APP_HSW,
        .hfp = APP_HFP,
        .hbp = APP_HBP,
        .vsw = APP_VSW,
        .vfp = APP_VFP,
        .vbp = APP_VBP,
        .polarityFlags = APP_POL_FLAGS,
        .bufferAddr = (uint32_t)lcdif_frame_buffer[0],
        .pixelFormat = kELCDIF_PixelFormatRGB565,
        .dataBus = APP_LCDIF_DATA_BUS,
    };

    ELCDIF_RgbModeInit(LCDIF, &config);
}

static void _lcd_interrupt_init(void)
{
    EnableIRQ(LCDIF_IRQn);
    ELCDIF_EnableInterrupts(LCDIF, kELCDIF_CurFrameDoneInterruptEnable);
}

static void _lcd_start(void)
{
    ELCDIF_RgbModeStart(LCDIF);
}

void LCDIF_IRQHandler(void)
{
    uint32_t intStatus;

    intStatus = ELCDIF_GetInterruptStatus(LCDIF);

    ELCDIF_ClearInterruptStatus(LCDIF, intStatus);

    if (intStatus & kELCDIF_CurFrameDone)
    {
#ifdef LCD_DEBUG
        s_frameDone = true;  
#endif

        if (imxrt_lcd.update)
        {
            ELCDIF_SetNextBufferAddr(LCDIF, (uint32_t)lcdif_frame_buffer[imxrt_lcd.index]);
            imxrt_lcd.update = false;
            rt_sem_release(&imxrt_lcd.lcd_sem);
        }

    }
}

static rt_err_t rt_lcd_control(rt_device_t dev, int cmd, void *args)
{
    switch (cmd)
    {
    case RTGRAPHIC_CTRL_RECT_UPDATE:
    {        
        if(rt_sem_take(&imxrt_lcd.lcd_sem, RT_TICK_PER_SECOND/20) != RT_EOK)
        {
            rt_kprintf("lcdtimeout!\n");
        }
        
        imxrt_lcd.index = (imxrt_lcd.index + 1) % FRAME_BUFFER_COUNT;
        memcpy(lcdif_frame_buffer[imxrt_lcd.index], imxrt_lcd.framebuffer, 
               sizeof(LCD_PIXEL_T) * RT_HW_LCD_WIDTH * RT_HW_LCD_HEIGHT);
        imxrt_lcd.update = true;
    }
    break;
    
    case RTGRAPHIC_CTRL_POWERON:
        break;
    
    case RTGRAPHIC_CTRL_POWEROFF:
        break;
    
    case RTGRAPHIC_CTRL_GET_INFO:
        memcpy(args, &imxrt_lcd.lcd_info, sizeof(imxrt_lcd.lcd_info));
        break;
    
    case RTGRAPHIC_CTRL_SET_MODE:
        break;
    }

    return RT_EOK;
}

int imxrt_hw_lcd_init(void)
{
    LCD_PIXEL_T * framebuffer;
    
    framebuffer = rt_malloc_align(sizeof(LCD_PIXEL_T) * RT_HW_LCD_WIDTH * RT_HW_LCD_HEIGHT, FRAME_BUFFER_ALIGN);
    if(!framebuffer)
    {
        rt_kprintf("malloc framebuffer fail\n");
        return -1;
    }
    imxrt_lcd.framebuffer = framebuffer;
    
    memset(framebuffer,         LCD_INIT_DATA, sizeof(LCD_PIXEL_T) * RT_HW_LCD_WIDTH * RT_HW_LCD_HEIGHT);
    memset(lcdif_frame_buffer,  LCD_INIT_DATA, sizeof(lcdif_frame_buffer));
    
    rt_kprintf("framebuffer: %p, lcdif_frame_buffer: %p, lcdif_frame_buffer[0]: %p, lcdif_frame_buffer[1]: %p\n", \
        framebuffer, lcdif_frame_buffer, lcdif_frame_buffer[0], lcdif_frame_buffer[1]);

    _lcd_gpio_config();
    _lcd_clock_config();
    _lcd_hardware_reset();
    _lcdif_init();
    _lcd_interrupt_init();
    _lcd_start();
        
    imxrt_lcd.index = 0;
    imxrt_lcd.update = false;
    
    imxrt_lcd.lcd_info.bits_per_pixel = LCD_BITS_PER_PIXEL;
    imxrt_lcd.lcd_info.pixel_format   = RTGRAPHIC_PIXEL_FORMAT_RGB565;
    imxrt_lcd.lcd_info.framebuffer    = (void *)framebuffer;
    imxrt_lcd.lcd_info.width          = RT_HW_LCD_WIDTH;
    imxrt_lcd.lcd_info.height         = RT_HW_LCD_HEIGHT;
    
    imxrt_lcd.lcd.type    = RT_Device_Class_Graphic;
    imxrt_lcd.lcd.init    = NULL;
    imxrt_lcd.lcd.open    = NULL;
    imxrt_lcd.lcd.close   = NULL;
    imxrt_lcd.lcd.read    = NULL;
    imxrt_lcd.lcd.write   = NULL;
    imxrt_lcd.lcd.control = rt_lcd_control;
    imxrt_lcd.lcd.user_data = (void *)&imxrt_lcd.lcd_info;
    
    rt_sem_init(&imxrt_lcd.lcd_sem, "lcd_sem", 1, RT_IPC_FLAG_FIFO);
    
    /* register lcd device to RT-Thread */
    rt_device_register(&imxrt_lcd.lcd, "lcd", RT_DEVICE_FLAG_RDWR);
    

    return 0;
}
//INIT_DEVICE_EXPORT(imxrt_hw_lcd_init);

#ifdef LCD_DEBUG
#include <finsh.h>

void APP_FillFrameBuffer(uint32_t frameBuffer[RT_HW_LCD_HEIGHT][RT_HW_LCD_WIDTH])
{
    /* Background color. */
    static const uint32_t bgColor = 0U;
    /* Foreground color. */
    static uint8_t fgColorIndex = 0U;
    static const uint32_t fgColorTable[] = {0x000000FFU, 0x0000FF00U, 0x0000FFFFU, 0x00FF0000U,
                                            0x00FF00FFU, 0x00FFFF00U, 0x00FFFFFFU};
    uint32_t fgColor = fgColorTable[fgColorIndex];

    /* Position of the foreground rectangle. */
    static uint16_t upperLeftX = 0U;
    static uint16_t upperLeftY = 0U;
    static uint16_t lowerRightX = (RT_HW_LCD_WIDTH - 1U) / 2U;
    static uint16_t lowerRightY = (RT_HW_LCD_HEIGHT - 1U) / 2U;

    static int8_t incX = 1;
    static int8_t incY = 1;

    /* Change color in next forame or not. */
    static bool changeColor = false;

    uint32_t i, j;

    /* Background color. */
    for (i = 0; i < RT_HW_LCD_HEIGHT; i++)
    {
        for (j = 0; j < RT_HW_LCD_WIDTH; j++)
        {
            frameBuffer[i][j] = bgColor;
        }
    }

    /* Foreground color. */
    for (i = upperLeftY; i < lowerRightY; i++)
    {
        for (j = upperLeftX; j < lowerRightX; j++)
        {
            frameBuffer[i][j] = fgColor;
        }
    }

    /* Update the format: color and rectangle position. */
    upperLeftX += incX;
    upperLeftY += incY;
    lowerRightX += incX;
    lowerRightY += incY;

    changeColor = false;

    if (0U == upperLeftX)
    {
        incX = 1;
        changeColor = true;
    }
    else if (RT_HW_LCD_WIDTH - 1 == lowerRightX)
    {
        incX = -1;
        changeColor = true;
    }

    if (0U == upperLeftY)
    {
        incY = 1;
        changeColor = true;
    }
    else if (RT_HW_LCD_HEIGHT - 1 == lowerRightY)
    {
        incY = -1;
        changeColor = true;
    }

    if (changeColor)
    {
        fgColorIndex++;

        if (ARRAY_SIZE(fgColorTable) == fgColorIndex)
        {
            fgColorIndex = 0U;
        }
    }
}

void lcd_test(void)
{
    uint32_t frameBufferIndex = 0;
    
    APP_FillFrameBuffer(lcdif_frame_buffer[frameBufferIndex]);
     
    while (1)
    {
        frameBufferIndex ^= 1U;

        APP_FillFrameBuffer(lcdif_frame_buffer[frameBufferIndex]);

        ELCDIF_SetNextBufferAddr(LCDIF, (uint32_t)lcdif_frame_buffer[frameBufferIndex]);

        s_frameDone = false;
        /* Wait for previous frame complete. */
        while (!s_frameDone)
        {
        }
    }
}
FINSH_FUNCTION_EXPORT(lcd_test, lcd test);
#endif
#endif
