/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2020-11-08     bigmagic       first version
 */
#include <rtthread.h>
#include <rtdevice.h>

#include <raspi4.h>
#include <drv_spi.h>
#include "drv_ili9486.h"

#ifdef USING_LCD_CONSOLE
#include "lcd_console.h"
#endif

//http://www.lcdwiki.com/MHS-3.5inch_RPi_Display
#define LCD_DEVICE_NAME       ("spi0.0")

#define LCD_SPI_SEND_FAST
//waveshare
#define LCD_SCREEN_WIDTH      (320)
#define LCD_SCREEN_HEIGHT     (480)

#define LCD_RESET_PIN         (25)
#define LCD_RS_PIN            (24)

#define LCD_SPI_FREQ_MAX      (125*1000*1000)

uint16_t LCD_HEIGHT = LCD_SCREEN_HEIGHT;
uint16_t LCD_WIDTH  = LCD_SCREEN_WIDTH;

#define SCREEN_VERTICAL_1           (0)
#define SCREEN_HORIZONTAL_1         (1)
#define SCREEN_VERTICAL_2           (2)
#define SCREEN_HORIZONTAL_2         (3)

struct rt_semaphore lcd_spi_lock;
struct rt_semaphore lcd_lock;

//rgb565 lcd buffer
uint16_t _lcd_buffer[LCD_SCREEN_WIDTH * LCD_SCREEN_HEIGHT];
uint16_t send_buffer[LCD_SCREEN_WIDTH * LCD_SCREEN_HEIGHT];

static struct rt_spi_device *lcd_dev;

static inline void send_cmd(void)
{
    rt_pin_write(LCD_RS_PIN, PIN_LOW);
}

static inline void send_data(void)
{
    rt_pin_write(LCD_RS_PIN, PIN_HIGH);
}

void writeData16(rt_uint16_t data)
{
    rt_uint8_t send_data[2];
    send_data[1] = data & 0x00FF;
    send_data[0] = ((data >> 8) & 0x00FF);
    rt_spi_transfer(lcd_dev, &send_data[0], RT_NULL, 2);
}

void writeData(void* dev,rt_uint8_t data)
{
    writeData16((rt_uint16_t)(data));
}

void writeCommand(void* dev, rt_uint8_t cmd)
{
    send_cmd();
    writeData16((rt_uint16_t)(cmd));
    send_data();
}

void lcd_write_commmand(rt_uint8_t cmd)
{
    writeCommand(lcd_dev, cmd);
}

void lcd_write_data(rt_uint8_t data)
{
    writeData(lcd_dev, data);
}

/*Ser rotation of the screen - changes x0 and y0*/
static inline void lcd_set_rotation(uint8_t rotation)
{
    writeCommand(lcd_dev, 0x36);
    rt_thread_mdelay(100);

    switch(rotation) {
        case SCREEN_VERTICAL_1:
            writeData(lcd_dev, 0x48);
            LCD_WIDTH  = 320;
            LCD_HEIGHT = 480;
            break;
        case SCREEN_HORIZONTAL_1:
            writeData(lcd_dev, 0x28);
            LCD_WIDTH  = 480;
            LCD_HEIGHT = 320;
            break;
        case SCREEN_VERTICAL_2:
            writeData(lcd_dev, 0x98);
            LCD_WIDTH  = 320;
            LCD_HEIGHT = 480;
            break;
        case SCREEN_HORIZONTAL_2:
            writeData(lcd_dev, 0xF8);
            LCD_WIDTH  = 480;
            LCD_HEIGHT = 320;
            break;
        default:
            //EXIT IF SCREEN ROTATION NOT VALID!
            break;
    }

    if((rotation == SCREEN_VERTICAL_1) || (rotation == SCREEN_VERTICAL_2))
    {
        lcd_write_commmand(0x2A);
        lcd_write_data(0x00);
        lcd_write_data(0x00);
        lcd_write_data(0x01);
        lcd_write_data(0x3F);

        lcd_write_commmand(0x2B);
        lcd_write_data(0x00);
        lcd_write_data(0x00);
        lcd_write_data(0x01);
        lcd_write_data(0xE0);
    }

    if((rotation == SCREEN_HORIZONTAL_1) || (rotation == SCREEN_HORIZONTAL_2))
    {
        lcd_write_commmand(0x2B);
        lcd_write_data(0x00);
        lcd_write_data(0x00);
        lcd_write_data(0x01);
        lcd_write_data(0x3F);

        lcd_write_commmand(0x2A);
        lcd_write_data(0x00);
        lcd_write_data(0x00);
        lcd_write_data(0x01);
        lcd_write_data(0xE0);
    }
}

static inline void fast_send_data(void)
{
    rt_uint32_t ii = 0;
    rt_uint32_t tx_index = 0;
    char *tx_data = (char *)send_buffer;
    rt_sem_take(&lcd_spi_lock, RT_WAITING_FOREVER);

    SPI_REG_CS(SPI_0_BASE) &= (~(3 << 0));
    SPI_REG_CLK(SPI_0_BASE) = 4;
    SPI_REG_CS(SPI_0_BASE) |= SPI_CS_TA;
    for(tx_index=0;tx_index<(LCD_SCREEN_WIDTH * LCD_SCREEN_HEIGHT) * 2;tx_index++)
    {
        for(ii = 0; ii < 32; ii = ii + 2)
        {
            SPI_REG_FIFO(SPI_0_BASE) = tx_data[tx_index + ii + 1];
            SPI_REG_FIFO(SPI_0_BASE) = tx_data[tx_index + ii];
        }
        while (!(SPI_REG_CS(SPI_0_BASE) & SPI_CS_DONE));
        SPI_REG_CS(SPI_0_BASE) |= (SPI_CS_CLEAR_TX) | (SPI_CS_CLEAR_RX);
        tx_index = tx_index + 31;
    }
    SPI_REG_CS(SPI_0_BASE) |= (SPI_CS_CLEAR_TX) | (SPI_CS_CLEAR_RX);
    SPI_REG_CS(SPI_0_BASE) &= (~SPI_CS_TA);
    rt_sem_release(&lcd_spi_lock);
}

static inline void lcd_show(void)
{

    lcd_write_commmand(0x2C); // Memory write?

    //rt_thread_mdelay(150);

#ifdef LCD_SPI_SEND_FAST
    fast_send_data();
#else
    int i, j;
    for (i = 0 ; i < 30  ; i ++)
    {
        uint16_t *tx_data = (uint16_t*)&send_buffer[5120* i];
        int32_t data_sz = 5120;
        for( j=0; j<data_sz; j++)
        {
            writeData16(tx_data[j]);
        }
    }
#endif

}

static void lcd_init(void)
{
    writeCommand(lcd_dev, 0x28);
    rt_thread_mdelay(150);

    writeCommand(lcd_dev, 0x3A);    // Interface Pixel Format
    writeData(lcd_dev, 0x55);       // 16 bit/pixe

    writeCommand(lcd_dev, 0xC2);    // Interface Pixel Format
    writeData(lcd_dev, 0x44);

    writeCommand(lcd_dev, 0xC5);     // VCOM Control
    writeData(lcd_dev, 0x00);
    writeData(lcd_dev, 0x00);
    writeData(lcd_dev, 0x00);
    writeData(lcd_dev, 0x00);

    writeCommand(lcd_dev, 0xE0);     // PGAMCTRL(Positive Gamma Control)
    writeData(lcd_dev, 0x0F);
    writeData(lcd_dev, 0x1F);
    writeData(lcd_dev, 0x1C);
    writeData(lcd_dev, 0x0C);
    writeData(lcd_dev, 0x0F);
    writeData(lcd_dev, 0x08);
    writeData(lcd_dev, 0x48);
    writeData(lcd_dev, 0x98);
    writeData(lcd_dev, 0x37);
    writeData(lcd_dev, 0x0A);
    writeData(lcd_dev, 0x13);
    writeData(lcd_dev, 0x04);
    writeData(lcd_dev, 0x11);
    writeData(lcd_dev, 0x0D);
    writeData(lcd_dev, 0x00);

    writeCommand(lcd_dev, 0xE1);     // NGAMCTRL (Negative Gamma Correction)
    writeData(lcd_dev, 0x0F);
    writeData(lcd_dev, 0x32);
    writeData(lcd_dev, 0x2E);
    writeData(lcd_dev, 0x0B);
    writeData(lcd_dev, 0x0D);
    writeData(lcd_dev, 0x05);
    writeData(lcd_dev, 0x47);
    writeData(lcd_dev, 0x75);
    writeData(lcd_dev, 0x37);
    writeData(lcd_dev, 0x06);
    writeData(lcd_dev, 0x10);
    writeData(lcd_dev, 0x03);
    writeData(lcd_dev, 0x24);
    writeData(lcd_dev, 0x20);
    writeData(lcd_dev, 0x00);

    writeCommand(lcd_dev, 0x11); // Sleep out, also SW reset
    rt_thread_mdelay(150);

    writeCommand(lcd_dev, 0x20);   // Display Inversion OFF   RPi LCD (A)
    //writeCommand(lcd_dev, 0x21); // Display Inversion ON    RPi LCD (B)

    lcd_set_rotation(SCREEN_VERTICAL_2);
    writeCommand(lcd_dev, 0x29);   // Display ON
    rt_thread_mdelay(150);
}

static inline void lcd_reset(void)
{
    //Reset signal, low reset (pin22)
    rt_pin_mode(LCD_RESET_PIN,PIN_MODE_OUTPUT);

    rt_pin_write(LCD_RESET_PIN, PIN_HIGH);
    rt_thread_mdelay(100);
    rt_pin_write(LCD_RESET_PIN, PIN_LOW);
    rt_thread_mdelay(100);
    rt_pin_write(LCD_RESET_PIN, PIN_HIGH);
}


rt_err_t ili9486_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

rt_err_t ili9486_close(rt_device_t dev)
{
    return RT_EOK;
}

rt_size_t ili9486_read(rt_device_t dev, rt_off_t pos, void *buf, rt_size_t size)
{
    return 0;
}

rt_size_t ili9486_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
#ifdef USING_LCD_CONSOLE
    fb_print((char*)buffer);
#endif
    return size;
}

rt_err_t ili9486_control(rt_device_t dev, int cmd, void *args)
{
    rt_sem_take(&lcd_lock, RT_WAITING_FOREVER);
    switch (cmd)
    {
    case RTGRAPHIC_CTRL_RECT_UPDATE:
        {
            struct rt_device_rect_info *info = (struct rt_device_rect_info*)args;
            info = info;
            rt_memcpy(send_buffer, _lcd_buffer, LCD_SCREEN_WIDTH * LCD_SCREEN_HEIGHT * 2);
            lcd_show();
        }
        break;

    case RTGRAPHIC_CTRL_GET_INFO:
        {
           struct rt_device_graphic_info* info = (struct rt_device_graphic_info*)args;

            RT_ASSERT(info != RT_NULL);
            info->pixel_format  = RTGRAPHIC_PIXEL_FORMAT_RGB565;
            info->bits_per_pixel= 16;
            info->width         = LCD_WIDTH;
            info->height        = LCD_HEIGHT;
            info->framebuffer   = (void *)_lcd_buffer;//lcd->fb;
        }
        break;
    }
    rt_sem_release(&lcd_lock);
    return RT_EOK;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops ili9486_ops =
{
    RT_NULL,
    ili9486_open,
    ili9486_close,
    ili9486_read,
    ili9486_write,
    ili9486_control,
};
#endif

static int hw_ili9486_lcd_init(void)
{
    struct rt_device *device;
    device = rt_malloc(sizeof(struct rt_device));
    rt_memset(device, 0, sizeof(struct rt_device));

    lcd_reset();
    rt_pin_mode(LCD_RS_PIN, PIN_MODE_OUTPUT);
    lcd_dev = (struct rt_spi_device *)rt_device_find(LCD_DEVICE_NAME);
    if (!lcd_dev)
    {
        rt_kprintf("no %s!\n", LCD_DEVICE_NAME);
    }
    lcd_dev->config.max_hz = LCD_SPI_FREQ_MAX;//125M
    lcd_init();

    rt_sem_init(&lcd_spi_lock, "lcd_spi_lock", 1, RT_IPC_FLAG_FIFO);
    rt_sem_init(&lcd_lock, "lcd_spi_lock", 1, RT_IPC_FLAG_FIFO);
     /* set device type */
    device->type = RT_Device_Class_Graphic;
    /* initialize device interface */
#ifdef RT_USING_DEVICE_OPS
    device->ops = &ili9486_ops;
#else
    device->init = RT_NULL;
    device->open = ili9486_open;
    device->close = ili9486_close;
    device->read = ili9486_read;
    device->write = ili9486_write;
    device->control = ili9486_control;
#endif
    /* register to device manager */
    rt_device_register(device, "lcd", RT_DEVICE_FLAG_RDWR);

    return RT_EOK;
}
INIT_DEVICE_EXPORT(hw_ili9486_lcd_init);
