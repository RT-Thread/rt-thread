#include <rtthread.h>
#include <rtdevice.h>
#include <rtgui/rtgui.h>
#include <rtgui/driver.h>
#include <rtgui/rtgui_server.h>
#include <rtgui/rtgui_system.h>

struct st7735 
{
    struct rt_device        parent;
    rt_bool_t               horizontal;
    rt_device_t             spi;
    rt_base_t               pin_dc;
    rt_base_t               pin_bl;
    rt_base_t               pin_rst;
};

static struct st7735 _st7735;

static inline void priv_mode_cmd()
{
    rt_pin_write(_st7735.pin_dc, 0);
}

static inline void priv_mode_data()
{
    rt_pin_write(_st7735.pin_dc, 1);
}

static inline void priv_write(const uint8_t * data, size_t length)
{
    struct rt_spi_message message;
    message.send_buf = (void*)data;
    message.recv_buf = NULL;
    message.length = length;
    message.next = NULL;
    message.cs_take = 0;
    message.cs_release = 0;
    rt_spi_transfer_message(SPI_DEVICE(_st7735.spi), &message);
}

static inline void priv_write_byte(const uint8_t byte)
{
    priv_write(&byte, 1);
}

static inline void priv_take()
{
    rt_spi_take(SPI_DEVICE(_st7735.spi));
}

static inline void priv_release()
{
    rt_spi_release(SPI_DEVICE(_st7735.spi));
}

static inline void priv_cmd_data(uint8_t cmd, const uint8_t * data, size_t length)
{
    priv_mode_cmd();
    priv_write_byte(cmd);
    if (length)
    {
        priv_mode_data();
        priv_write(data, length);
    }
}

static inline void priv_sequence_init()
{
    uint8_t cmdlist[] = {
        0x11,  0,
        0xB1,  3, 0x01, 0x2C, 0x2D,
        0xB2,  3, 0x01, 0x2C, 0x2D,
        0xB3,  6, 0x01, 0x2C, 0x2D, 0x01, 0x2C, 0x2D,
        0xB4,  1, 0x07,
        0xC0,  5, 0xA2, 0x02, 0x84, 0xC1, 0xC5,
        0xC2,  2, 0x0A, 0x00,
        0xC3,  5, 0x8A, 0x2A, 0xC4, 0x8A, 0xEE,
        0xC5,  1, 0x0E,
        // 0x36,  1, 0xC0,
        0xE0, 16, 0x0F, 0x1A, 0x0F, 0x18, 0x2F, 0x28, 0x20, 0x22, 0x1F, 0x1B, 0x23, 0x37, 0x00, 0x07, 0x02, 0x10,
        0xE1, 16, 0x0F, 0x1B, 0x0F, 0x17, 0x33, 0x2C, 0x29, 0x2E, 0x30, 0x30, 0x39, 0x3F, 0x00, 0x07, 0x03, 0x10,
        0x2A,  4, 0x00, 0x00, 0x00, 0x7F,
        0x2B,  4, 0x00, 0x00, 0x00, 0x9F,
        0xF0,  3, 0x01, 0xF6, 0x00,
        // 0x3A,  1, 0x05,
        0x3A,  1, 0x06,
        0x29,  0,
    };
    uint8_t *p, *end;
    p = cmdlist;
    end = cmdlist + sizeof(cmdlist);
    while(p < end)
    {
        priv_cmd_data(p[0], &p[2], p[1]);
        p += 2 + p[1];
    }
}

static inline void priv_set_direction()
{
    uint8_t data[1];
    if (_st7735.horizontal)
    {
        data[0] = 0xA0;
    }
    else
    {
        data[0] = 0xC0;
    }
    priv_cmd_data(0x36, data, 1);
}

static inline void priv_region(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
    if (w == 0 || h == 0)
    {
        return;
    }
    
//    if (_st7735.horizontal)
//    {
//        uint8_t tmp;
//        tmp = x;
//        x = y;
//        y = tmp;
//        tmp = w;
//        w = h;
//        h = tmp;
//    }
    
    uint8_t data[4];
    if (_st7735.horizontal)
    {
        x += 1;
        y += 2;
    }
    else
    {
        x += 2;
        y += 1;
    }

    data[0] = x >> 8;
    data[1] = x & 0xff;
    x += w - 1;
    data[2] = x >> 8;
    data[3] = x & 0xff;
    priv_cmd_data(0x2a, data, 4);

    data[0] = y >> 8;
    data[1] = y & 0xff;
    y += h - 1;
    data[2] = y >> 8;
    data[3] = y & 0xff;
    priv_cmd_data(0x2b, data, 4);
}

static inline void priv_draw(const uint8_t* buffer, size_t length)
{
    priv_cmd_data(0x2c, buffer, length);
}

static rt_err_t lcd_init(rt_device_t dev)
{
    return RT_EOK;
}

static rt_err_t lcd_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t lcd_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_err_t lcd_control(rt_device_t dev, int cmd, void *args)
{
    switch (cmd)
    {
    case RTGRAPHIC_CTRL_GET_INFO:
    {
        struct rt_device_graphic_info *info;

        info = (struct rt_device_graphic_info*) args;
        RT_ASSERT(info != RT_NULL);

        info->bits_per_pixel = 24;
        info->pixel_format = RTGRAPHIC_PIXEL_FORMAT_RGB888;
        info->framebuffer = RT_NULL;
        if (_st7735.horizontal)
        {
            info->width = 160;
            info->height = 128;
        }
        else
        {
            info->width = 128;
            info->height = 160;
        }
    }
    break;

    case RTGRAPHIC_CTRL_RECT_UPDATE:
        /* nothong to be done */
        break;

    default:
        break;
    }

    return RT_EOK;
}

static void st7735_set_pixel(const char* pixel, int x, int y)
{
    priv_take();
    priv_region(x, y, 1, 1);
    priv_draw((uint8_t*)pixel, 3);
    priv_release();
}

/* 获取像素点颜色 */
static void st7735_get_pixel(char* pixel, int x, int y)
{
    return;
}

/* 画水平线 */
static void st7735_draw_hline(const char* pixel, int x1, int x2, int y)
{
    int len = x2 - x1;
    if (len <= 0)
    {
        return;
    }
    priv_take();
    priv_region(x1, y, len, 1);
    priv_draw(NULL, 0);
    priv_mode_data();
    while (len--)
    {
        priv_write((uint8_t*)pixel, 3);
    }
    priv_release();
}

/* 垂直线 */
static void st7735_draw_vline(const char* pixel, int x, int y1, int y2)
{
    int len = y2 - y1;
    if (len <= 0)
    {
        return;
    }
    priv_take();
    priv_region(x, y1, 1, len);
    priv_draw(NULL, 0);
    priv_mode_data();
    while (len--)
    {
        priv_write((uint8_t*)pixel, 3);
    }
    priv_release();
}

/* ?? */
static void st7735_draw_blit_line(const char* pixels, int x, int y, rt_size_t size)
{
    priv_take();
    priv_region(x, y, 1, size);
    priv_draw((uint8_t*)pixels, 3*size);
    priv_release();
}


static struct rt_device_graphic_ops st7735_ops =
{
    st7735_set_pixel,
    st7735_get_pixel,
    st7735_draw_hline,
    st7735_draw_vline,
    st7735_draw_blit_line
};

static rt_device_t priv_device_register(struct st7735 * st7735, const char * name)
{
    if (st7735->pin_dc < 0)
    {
        rt_kprintf("ERROR: No pin_dc available for ST7735\n");
        return RT_NULL;
    }
    if (st7735->pin_rst < 0)
    {
        rt_kprintf("WARNING: No pin_rst available for ST7735, assume hardware reset\n");
    }
    if (!st7735->spi)
    {
        rt_kprintf("ERROR: No SPI device available for ST7735\n");
        return RT_NULL;
    }
    if (rt_device_open(st7735->spi, RT_DEVICE_OFLAG_RDWR) != RT_EOK)
    {
        rt_kprintf("Open SPI device failed for ST7735\n");
        return RT_NULL;
    }
    
    struct rt_spi_configuration spi_config;
    spi_config.mode = RT_SPI_MODE_0 | RT_SPI_MSB;
    spi_config.data_width = 8;
    spi_config.reserved = 0;
    spi_config.max_hz = 50*1000*1000;
    rt_spi_configure(SPI_DEVICE(st7735->spi), &spi_config);
    rt_pin_mode(st7735->pin_dc, PIN_MODE_OUTPUT);
    
    /* turn on backlight */
    if (st7735->pin_bl >= 0)
    {
        rt_pin_mode(st7735->pin_bl, PIN_MODE_OUTPUT);
        rt_pin_write(st7735->pin_bl, 1);
    }
    
    /* reset st7735 */
    if (st7735->pin_rst >= 0)
    {
        rt_pin_mode(st7735->pin_rst, PIN_MODE_OUTPUT);
        rt_pin_write(st7735->pin_rst, 0);
    }
    rt_thread_delay(rt_tick_from_millisecond(100));
    if (st7735->pin_rst >= 0)
    {
        rt_pin_write(st7735->pin_rst, 1);
    }
    rt_thread_delay(rt_tick_from_millisecond(50));
    
    /* init registers */
    priv_take();
    priv_sequence_init();
    priv_set_direction();
    priv_release();
    
    
    st7735->parent.type  = RT_Device_Class_Graphic;
    st7735->parent.init  = lcd_init;
    st7735->parent.open  = lcd_open;
    st7735->parent.close = lcd_close;
    st7735->parent.control = lcd_control;
    st7735->parent.read  = RT_NULL;
    st7735->parent.write = RT_NULL;
    st7735->parent.user_data = &st7735_ops;

    /* register graphic device driver */
    rt_device_register(&st7735->parent, name, RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_STANDALONE);
    return &st7735->parent;
}

rt_device_t rt_st7735_probe(const char * lcd_name, const char * spi_dev_name, rt_bool_t horizontal, rt_base_t pin_dc, rt_base_t pin_bl, rt_base_t pin_rst)
{
    /* register lcd device */
    _st7735.spi = rt_device_find(spi_dev_name);
    _st7735.horizontal = horizontal;
    _st7735.pin_bl = pin_bl;
    _st7735.pin_dc = pin_dc;
    _st7735.pin_rst = pin_rst;
    return priv_device_register(&_st7735, lcd_name);
}
