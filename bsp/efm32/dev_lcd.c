/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author      Notes
 * 2011-12-16   onelife     Initial creation of address mapped method (pixel
 *                            drive) for EFM32GG_DK3750 board
 * 2011-12-29   onelife     Add direct drive method (frame buffer) support
 */

/***************************************************************************//**
 * @addtogroup EFM32GG_DK3750
 * @{
 ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "board.h"
#include "drv_usart.h"
#include "dev_lcd.h"

#if defined(EFM32_USING_LCD)
 #if (!defined(LCD_MAPPED) && !defined(LCD_DIRECT))
  #error "Unknown LCD access mode"
 #endif
#include <rtgui/rtgui.h>
#include <rtgui/driver.h>

#include <dmd_ssd2119.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#ifdef EFM32_LCD_DEBUG
#define lcd_debug(format,args...)           rt_kprintf(format, ##args)
#else
#define lcd_debug(format,args...)
#endif

/* Private function prototypes -----------------------------------------------*/
#if defined(LCD_MAPPED)
static void efm32_spiLcd_setPixel(rtgui_color_t *c, int x, int y);
static void efm32_spiLcd_getPixel(rtgui_color_t *c, int x, int y);
static void efm32_spiLcd_drawRawHLine(rt_uint8_t *pixels, int x1, int x2, int y);
static void efm32_spiLcd_drawHLine(rtgui_color_t *c, int x1, int x2, int y);
static void efm32_spiLcd_drawVLine(rtgui_color_t *c, int x1, int x2, int y);
#endif

/* Private variables ---------------------------------------------------------*/
static rt_device_t lcd;
static struct rt_device lcd_device;
static rt_bool_t lcdAutoCs = true;
static struct rt_device_graphic_info lcd_info;
#if defined(LCD_MAPPED)
static const struct rtgui_graphic_driver_ops lcd_ops =
    {
        efm32_spiLcd_setPixel,
        efm32_spiLcd_getPixel,
        efm32_spiLcd_drawHLine,
        efm32_spiLcd_drawVLine,
        efm32_spiLcd_drawRawHLine
    };

/* Private functions ---------------------------------------------------------*/
/***************************************************************************//**
 * @brief
 *   Draw a pixel with specified color
 *
 * @details
 *
 * @note
 *
 * @param[in] c
 *  Pointer to color
 *
 * @param[in] x
 *  Horizontal position
 *
 * @param[in] y
 *  Vertical position
 ******************************************************************************/
static void efm32_spiLcd_setPixel(rtgui_color_t *c, int x, int y)
{
    rt_uint32_t ret = RT_EOK;

    do
    {
        /* Check if pixel is outside clipping region */
        if ((x < 0) || (x > lcd_info.width))
        {
            break;
        }
        if ((y < 0) || (y > lcd_info.height))
        {
            break;
        }

        /* Write color */
        ret = DMD_writePixel((rt_uint16_t)x, (rt_uint16_t)y, (rt_uint16_t)*c, 1);
        if (ret != 0)
        {
            break;
        }
        return;
    } while(0);

//    lcd_debug("LCD err: Set pixel at (%d,%d: %x) failed (%x)!\n", x, y, *c, ret);
}

/***************************************************************************//**
 * @brief
 *   Get the color of a pixel
 *
 * @details
 *
 * @note
 *
 * @param[out] c
 *  Pointer to color
 *
 * @param[in] x
 *  Horizontal position
 *
 * @param[in] y
 *  Vertical position
 ******************************************************************************/
static void efm32_spiLcd_getPixel(rtgui_color_t *c, int x, int y)
{
    rt_uint32_t ret = RT_EOK;

    do
    {
        /* Check if pixel is outside clipping region */
        if ((x < 0) || (x > lcd_info.width))
        {
            break;
        }
        if ((y < 0) || (y > lcd_info.height))
        {
            break;
        }

        /* Read color */
        ret = DMD_readPixel((rt_uint16_t)x, (rt_uint16_t)y, (rt_uint16_t *)c);
        if (ret != 0)
        {
            break;
        }
        return;
    } while(0);

    lcd_debug("LCD err: Get pixel at (%d,%d: %x) failed (%x)!\n",
        x, y, *c, ret);
}

/***************************************************************************//**
 * @brief
 *   Draw a horizontal line with raw color
 *
 * @details
 *
 * @note
 *
 * @param[in] pixels
 *  Pointer to raw color
 *
 * @param[in] x1
 *  Horizontal start position
 *
 * @param[in] x2
 *  Horizontal end position
 *
 * @param[in] y
 *  Vertical position
 ******************************************************************************/
static void efm32_spiLcd_drawRawHLine(rt_uint8_t *pixels, int x1, int x2, int y)
{
    lcd_debug("LCD: RAW H LINE!\n");
}

/***************************************************************************//**
 * @brief
 *   Draw a horizontal line with specified color
 *
 * @details
 *
 * @note
 *
 * @param[in] c
 *  Pointer to color
 *
 * @param[in] x1
 *  Horizontal start position
 *
 * @param[in] x2
 *  Horizontal end position
 *
 * @param[in] y
 *  Vertical position
 ******************************************************************************/
static void efm32_spiLcd_drawHLine(rtgui_color_t *c, int x1, int x2, int y)
{
    rt_uint32_t ret = RT_EOK;

    do
    {
        /* Check if line is outside of clipping region */
        if ((y < 0) || (y > lcd_info.height))
        {
            break;
        }

        /* Swap the coordinates if x1 is larger than x2 */
        if (x1 > x2)
        {
            int swap;
            swap = x1;
            x1   = x2;
            x2   = swap;
        }

        /* Check if entire line is outside clipping region */
        if ((x1 > lcd_info.width) || (x2 < 0))
        {
            /* Nothing to draw */
            break;
        }

        /* Clip the line if necessary */
        if (x1 < 0)
        {
            x1 = 0;
        }
        if (x2 > lcd_info.width)
        {
            x2 = lcd_info.width;
        }

        /* Write color */
        rt_uint32_t length = x2 - x1 + 1;
        ret = DMD_writePixel((rt_uint16_t)x1, (rt_uint16_t)y,
            (rt_uint16_t)*c, length);
        if (ret != 0)
        {
            break;
        }
        return;
    } while(0);

//    lcd_debug("LCD err: Draw hline at (%d-%d,%d: %x) failed (%x)!\n", x1, x2, y, *c, ret);
}

/***************************************************************************//**
 * @brief
 *   Draw a vertical line with specified color
 *
 * @details
 *
 * @note
 *
 * @param[in] c
 *  Pointer to color
 *
 * @param[in] x
 *  Horizontal position
 *
 * @param[in] y1
 *  Vertical start position
 *
 * @param[in] y2
 *  Vertical end position
 ******************************************************************************/
static void efm32_spiLcd_drawVLine(rtgui_color_t *c, int x , int y1, int y2)
{
    rt_uint32_t ret = RT_EOK;

    do
    {
        /* Check if line is outside of clipping region */
        if ((x < 0) || (x > lcd_info.width))
        {
            break;
        }

        /* Swap the coordinates if y1 is larger than y2 */
        if (y1 > y2)
        {
            rt_uint16_t swap;
            swap = y1;
            y1   = y2;
            y2   = swap;
        }

        /* Check if entire line is outside clipping region */
        if ((y1 > lcd_info.height) || (y2 < 0))
        {
            /* Nothing to draw */
            break;
        }

        /* Clip the line if necessary */
        if (y1 < 0)
        {
            y1 = 0;
        }

        if (y2 > lcd_info.height)
        {
            y2 = lcd_info.height;
        }

        /* Set clipping area */
        rt_uint16_t length = y2 - y1 + 1;
        ret = DMD_setClippingArea((rt_uint16_t)x, (rt_uint16_t)y1, 1, length);
        if (ret != DMD_OK)
        {
            break;
        }

        /* Write color */
        ret= DMD_writePixel(0, 0, (rt_uint16_t)*c, length);
        if (ret != DMD_OK)
        {
            break;
        }

        /* Reset clipping area */
        ret = DMD_setClippingArea(0, 0, lcd_info.width, lcd_info.height);
        if (ret != DMD_OK)
        {
            break;
        }
        return;
    } while(0);

//    lcd_debug("LCD err: Draw vline at (%d,%d-%d: %x) failed (%x)!\n", x, y1, y2, *c, ret);
}
#endif

/***************************************************************************//**
* @brief
*   Configure LCD device
*
* @details
*
* @note
*
* @param[in] dev
*   Pointer to device descriptor
*
* @param[in] cmd
*   IIC control command
*
* @param[in] args
*   Arguments
*
* @return
*   Error code
******************************************************************************/
static rt_err_t efm32_spiLcd_control (rt_device_t dev, int cmd, void *args)
{
    switch (cmd)
    {
    case RTGRAPHIC_CTRL_RECT_UPDATE:
        break;
    case RTGRAPHIC_CTRL_POWERON:
        break;
    case RTGRAPHIC_CTRL_POWEROFF:
        break;
    case RTGRAPHIC_CTRL_GET_INFO:
        rt_memcpy(args, &lcd_info, sizeof(struct rt_device_graphic_info));
        break;
    case RTGRAPHIC_CTRL_SET_MODE:
        break;
    }

    return RT_EOK;
}

/***************************************************************************//**
 * @brief
 *   Set/Clear chip select
 *
 * @details
 *
 * @note
 *
 * @param[in] enable
 *  Chip select pin setting
 ******************************************************************************/
static void efm32_spiLcd_cs(rt_uint8_t enable)
{
    if (!lcdAutoCs)
    {
        if (enable)
        {
            GPIO_PinOutClear(LCD_CS_PORT, LCD_CS_PIN);
        }
        else
        {
            GPIO_PinOutSet(LCD_CS_PORT, LCD_CS_PIN);
        }
    }
}

/***************************************************************************//**
 * @brief
 *  Write data to SSD2119 controller
 *
 * @param[in] reg
 *  Register to write to
 *
 * @param[in] data
 *  16-bit data to write into register
 *
 * @note
 *  It's not possible to read back register value through SSD2119 SPI interface
 ******************************************************************************/
rt_err_t efm32_spiLcd_writeRegister(rt_uint8_t reg, rt_uint16_t data)
{
    struct efm32_usart_device_t *usart;
    rt_uint8_t buf_ins[3];
    rt_uint8_t buf_res[3];

    RT_ASSERT(lcd != RT_NULL);
    usart = (struct efm32_usart_device_t *)(lcd->user_data);

    /* Build instruction buffer */
    buf_res[0] = (data & 0xff00) >> 8;
    buf_res[1] = data & 0x00ff;
    buf_ins[0] = 1;                             /* Instruction length */
    buf_ins[1] = reg;                           /* Instruction */
    *(rt_uint8_t **)(&buf_ins[2]) = buf_res;    /* Data */
    efm32_spiLcd_cs(1);
    if (lcd->write(lcd, EFM32_NO_DATA, buf_ins, 2) == 0)
    {
        lcd_debug("LCD: Write data failed!\n");
        return -RT_ERROR;
    }
    efm32_spiLcd_cs(0);

    return RT_EOK;
}

/***************************************************************************//**
 * @brief
 *  Register LCD device
 *
 * @details
 *
 * @note
 *
 * @param[in] device
 *  Pointer to device descriptor
 *
 * @param[in] name
 *  Device name
 *
 * @param[in] flag
 *  Configuration flags
 *
 * @param[in] iic
 *  Pointer to IIC device descriptor
 *
 * @return
 *  Error code
 ******************************************************************************/
rt_err_t efm32_spiLcd_register(
    rt_device_t                     device,
    const char                      *name,
    rt_uint32_t                     flag,
    void                            *data)
{
    RT_ASSERT(device != RT_NULL);

    device->type        = RT_Device_Class_Graphic;
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;
    device->init        = RT_NULL;
    device->open        = RT_NULL;
    device->close       = RT_NULL;
    device->read        = RT_NULL;
    device->write       = RT_NULL;
    device->control     = efm32_spiLcd_control;
    device->user_data   = data;

    /* register a character device */
    return rt_device_register(device, name, RT_DEVICE_FLAG_RDWR | flag);
}

/***************************************************************************//**
 * @brief
 *   Initialize LCD device
 *
 * @details
 *
 * @note
 *
 ******************************************************************************/
void efm32_spiLcd_init(void)
{
    struct efm32_usart_device_t *usart;
    rt_uint32_t                 flag;
    DMD_DisplayGeometry         *geometry;
    rt_uint32_t                 ret;

    do
    {
        USART_InitSync_TypeDef init = USART_INITSYNC_DEFAULT;

        /* Find SPI device */
        lcd = rt_device_find(LCD_USING_DEVICE_NAME);
        if (lcd == RT_NULL)
        {
            lcd_debug("LCD err: Can't find %s!\n", LCD_USING_DEVICE_NAME);
            break;
        }
        lcd_debug("LCD: Find device %s\n", LCD_USING_DEVICE_NAME);

        /* Config CS pin */
        usart = (struct efm32_usart_device_t *)(lcd->user_data);
        if (!(usart->state & USART_STATE_AUTOCS))
        {
            GPIO_PinModeSet(LCD_CS_PORT, LCD_CS_PIN, gpioModePushPull, 1);
            lcdAutoCs = false;
        }

        /* TFT initialize or reinitialize. Assumes EBI has been configured
           correctly in DVK_init(DVK_Init_EBI) */
        rt_uint32_t freq = SystemCoreClockGet();
        rt_uint32_t i;
        rt_bool_t warning = RT_FALSE;

        /* If we are in BC_UIF_AEM_EFM state, we can redraw graphics */
        while (DVK_readRegister(&BC_REGISTER->UIF_AEM) != BC_UIF_AEM_EFM)
        {
            if (!warning)
            {
                lcd_debug("LCD: Please press AEM button!!!\n");
                warning = RT_TRUE;
            }
        }

        lcd_debug("LCD: Got LCD control\n");
        /* If we're not BC_ARB_CTRL_EBI state, we need to reconfigure display controller */
        if (DVK_readRegister(&BC_REGISTER->ARB_CTRL) != BC_ARB_CTRL_EBI)
        {
            lcd_debug("LCD: Set to EBI mode\n");
            /* Configure for EBI mode and reset display */
            DVK_displayControl(DVK_Display_EBI);
            DVK_displayControl(DVK_Display_ResetAssert);
            DVK_displayControl(DVK_Display_PowerDisable);
            /* Short delay */
            freq = SystemCoreClockGet();
            for(i = 0; i < (freq / 100); i++)
            {
                __NOP();
            }
#if defined(LCD_MAPPED)
            /* Configure display for address mapped method + 3-wire SPI mode */
            DVK_displayControl(DVK_Display_Mode8080);
            DVK_displayControl(DVK_Display_PowerEnable);
            DVK_displayControl(DVK_Display_ResetRelease);

            /* Initialize graphics - abort on failure */
            ret = DMD_init(BC_SSD2119_BASE, BC_SSD2119_BASE + 2);
            if (ret == DMD_OK)
            {
                /* Make sure display is configured with correct rotation */
                DMD_flipDisplay(1, 1);
            }
            else if (ret != DMD_ERROR_DRIVER_ALREADY_INITIALIZED)
            {
                lcd_debug("LCD err: driver init failed %x\n", ret);
                break;
            }
#elif defined(LCD_DIRECT)
            /* Configure TFT direct drive method from EBI BANK2 */
            const EBI_TFTInit_TypeDef tftInit =
            {
                ebiTFTBank2,                  /* Select EBI Bank 2 */
                ebiTFTWidthHalfWord,          /* Select 2-byte (16-bit RGB565) increments */
                ebiTFTColorSrcMem,            /* Use memory as source for mask/blending */
                ebiTFTInterleaveUnlimited,    /* Unlimited interleaved accesses */
                ebiTFTFrameBufTriggerVSync,   /* VSYNC as frame buffer update trigger */
                false,                        /* Drive DCLK from negative edge of internal clock */
                ebiTFTMBDisabled,             /* No masking and alpha blending enabled */
                ebiTFTDDModeExternal,         /* Drive from external memory */
                ebiActiveLow,                 /* CS Active Low polarity */
                ebiActiveHigh,                /* DCLK Active High polarity */
                ebiActiveLow,                 /* DATAEN Active Low polarity */
                ebiActiveLow,                 /* HSYNC Active Low polarity */
                ebiActiveLow,                 /* VSYNC Active Low polarity */
                320,                          /* Horizontal size in pixels */
                1,                            /* Horizontal Front Porch */
                30,                           /* Horizontal Back Porch */
                2,                            /* Horizontal Synchronization Pulse Width */
                240,                          /* Vertical size in pixels */
                1,                            /* Vertical Front Porch */
                4,                            /* Vertical Back Porch */
                2,                            /* Vertical Synchronization Pulse Width */
                0x0000,                       /* Frame Address pointer offset to EBI memory base */
                4,                            /* DCLK Period */
                0,                            /* DCLK Start cycles */
                0,                            /* DCLK Setup cycles */
                0,                            /* DCLK Hold cycles */
            };

            DVK_enablePeripheral(DVK_TFT);

            /* Configure display for Direct Drive + 3-wire SPI mode */
            DVK_displayControl(DVK_Display_ModeGeneric);
            DVK_displayControl(DVK_Display_PowerEnable);
            DVK_displayControl(DVK_Display_ResetRelease);

            /* Configure GPIO for EBI and TFT */
            /* EBI TFT DCLK/Dot Clock */
            GPIO_PinModeSet(gpioPortA, 8, gpioModePushPull, 0);
            /* EBI TFT DATAEN */
            GPIO_PinModeSet(gpioPortA, 9, gpioModePushPull, 0);
            /* EBI TFT VSYNC  */
            GPIO_PinModeSet(gpioPortA, 10, gpioModePushPull, 0);
            /* EBI TFT HSYNC */
            GPIO_PinModeSet(gpioPortA, 11, gpioModePushPull, 0);

            /* Initialize display */
            DMD_init(0, (rt_uint32_t)EBI_BankAddress(EBI_BANK2));

            /* Configure EBI TFT direct drive */
            EBI_TFTInit(&tftInit);
#endif
        }

        /* Get LCD geometry */
        ret = DMD_getDisplayGeometry(&geometry);
        if (ret != DMD_OK)
        {
            lcd_debug("LCD err: get geometry failed!\n");
            break;
        }

        /* Init LCD info */
        flag = RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_DMA_TX;
        lcd_info.pixel_format       = RTGRAPHIC_PIXEL_FORMAT_RGB565P;
        lcd_info.bits_per_pixel     = 16;
        lcd_info.width              = geometry->xSize;
        lcd_info.height             = geometry->ySize;
#if defined(LCD_MAPPED)
        lcd_info.framebuffer        = RT_NULL;
        efm32_spiLcd_register(&lcd_device, LCD_DEVICE_NAME, flag, (void *)&lcd_ops);
#elif defined(LCD_DIRECT)
        lcd_info.framebuffer        = (rt_uint8_t *)EBI_BankAddress(EBI_BANK2);
        efm32_spiLcd_register(&lcd_device, LCD_DEVICE_NAME, flag, RT_NULL);
#endif

        /* Set clipping area */
        ret = DMD_setClippingArea(0, 0, geometry->xSize, geometry->ySize);
        if (ret != DMD_OK)
        {
            lcd_debug("LCD err: set clipping area failed!\n");
            break;
        }
        /* Read device code */
        rt_uint16_t code = 0xFFFF;
#if defined(LCD_MAPPED)
        code = DMDIF_readDeviceCode();
#endif
        /* Set as rtgui graphic driver */
        rtgui_graphic_set_device(&lcd_device);

        lcd_debug("LCD: H/W init OK!\n");
        return;
    } while(0);

    lcd_debug("LCD err: H/W init failed!\n");
}

 #endif /* defined(EFM32_USING_LCD) */
/***************************************************************************//**
 * @}
 ******************************************************************************/
