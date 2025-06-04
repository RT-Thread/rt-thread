/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-08-03     thread-liu        the first version
 */

#include "board.h"

#if defined(BSP_USING_GC0328C)

#include <drivers/i2c.h>
#include <drv_gc0328c.h>
#include <drv_dcmi.h>
#include <lcd_port.h>

#define DRV_DEBUG
//#define CAMERA_DUMP
#define LOG_TAG     "drv.gc0328c"
#include <drv_log.h>

#define DEV_ADDRESS      0x21 /* gc0328c address */
#define I2C_NAME        "i2c2"

volatile rt_uint32_t jpeg_data_len = 0;
volatile rt_uint8_t  jpeg_data_ok  = 0;
struct rt_i2c_bus_device *i2c_bus  = RT_NULL;

#define JPEG_BUF_SIZE   (320 * 240 *2)
#define JPEG_LINE_SIZE  (38400)
#define RESET_PIN  GET_PIN(A, 3)

#define RGB565_RED      0xf800
#define RGB565_GREEN    0x07e0
#define RGB565_BLUE     0x001f

typedef enum {
    QVGA_320_240    = 0,
    VGA_640_480,
    PPI_MAX
} PPI_TYPE; // Pixel per inch

typedef enum {
    TYPE_5FPS            = 0,
    TYPE_10FPS,
    TYPE_20FPS,
    FPS_MAX
} FPS_TYPE; // frame per second

static rt_uint8_t *jpeg_data_buf = RT_NULL;
static rt_uint32_t JPEG_LINE0_BUF[JPEG_LINE_SIZE];
static rt_uint32_t JPEG_LINE1_BUF[JPEG_LINE_SIZE];
rt_uint8_t model_input_data_rgb[96*96*3];
rt_uint8_t model_input_data_gray[96*96];
//rt_uint32_t *JPEG_LINE0_BUF;
//rt_uint32_t *JPEG_LINE1_BUF;
extern struct drv_lcd_device _lcd;
extern struct rt_event ov2640_event;

#if defined(CAMERA_DUMP)
#define __is_print(ch) ((unsigned int)((ch) - ' ') < 127u - ' ')
static void dump_hex(const rt_uint8_t *ptr, rt_size_t buflen)
{
    unsigned char *buf = (unsigned char *)ptr;
    int i, j;

    for (i = 0; i < buflen; i += 16)
    {
        rt_kprintf("%08x:", i);

        for (j = 0; j < 16; j++)
        {
            if (i + j < buflen)
            {
                rt_kprintf("%02x", buf[i + j]);
            }
            else
            {
                rt_kprintf(" ");
            }
        }
        rt_kprintf(" ");

        for (j = 0; j < 16; j++)
        {
            if (i + j < buflen)
            {
                rt_kprintf("%c", __is_print(buf[i + j]) ? buf[i + j] : '.');
            }
        }
        rt_kprintf("\n");
    }
}
#endif

#define RANGE_LIMIT(x) (x > 255 ? 255 : (x < 0 ? 0 : x))

/*
* YUV422打包数据,UYVY,转换为RGB565,
* inBuf -- YUV data
* outBuf -- RGB565 data
* imgWidth,imgHeight -- image width and height
* cvtMethod -- 无效参数
*/
int convert_uyvy_to_rgb(unsigned char *inBuf, unsigned char *outBuf, int imgWidth, int imgHeight)
{
    int rows ,cols; /* 行列标志 */
    int y, u, v, r, g, b;   /* yuv rgb 相关分量 */
    unsigned char *YUVdata, *RGBdata;   /* YUV和RGB数据指针 */
    int Ypos, Upos, Vpos;   /* Y U V在数据缓存中的偏移 */
    unsigned int i = 0;

    YUVdata = inBuf;
    RGBdata = outBuf;
#if 1
//    /*  YUYV */
//    Ypos = 0;
//    Upos = Ypos + 1;
//    Vpos = Upos + 2;

    /* YVYU */
    Ypos = 0;
    Vpos = Ypos + 1;
    Upos = Vpos + 2;
#endif

#if 0   /* UYVY */
    Ypos = 1;
    Upos = Ypos - 1;
    Vpos = Ypos + 1;
#endif

    /* 每个像素两个字节 */
    for(rows = 0; rows < imgHeight; rows++)
    {
        for(cols = 0; cols < imgWidth; cols++)
        {
            /* 矩阵推到，百度 */
            y = YUVdata[Ypos];
            u = YUVdata[Upos] - 128;
            v = YUVdata[Vpos] - 128;

            r = y + v + ((v * 103) >> 8);
            g = y - ((u * 88) >> 8) - ((v * 183) >> 8);
            b = y + u + ((u * 198) >> 8);

            r = r > 255?255:(r < 0?0:r);
            g = g > 255?255:(g < 0?0:g);
            b = b > 255?255:(b < 0?0:b);

            /* 从低到高r g b */
            *(RGBdata ++) = (((g & 0x1c) << 3) | (b >> 3)); /* g低5位，b高5位 */
            *(RGBdata ++) = ((r & 0xf8) | (g >> 5));    /* r高5位，g高3位 */

            /* 两个字节数据中包含一个Y */
            Ypos += 2;
            //Ypos++;
            i++;
            /* 每两个Y更新一次UV */
            if(!(i & 0x01))
            {
                Upos = Ypos - 1;
                Vpos = Ypos + 1;
            }

        }
    }

    return 0;
}

static void rgb565_to_rgb888(rt_uint16_t *rgb565Color, rt_uint8_t *rgb888Color, int size)
{
    rt_uint16_t color;
    rt_uint32_t i, n;

    for (i=0, n=0; i<size; i++, n+=3)
    {
        color = rgb565Color[i];
        // 获取RGB单色，并填充低位
        rgb888Color[n]  = ((color & RGB565_RED)    >> 11) <<3;
        rgb888Color[n+1]  = ((color & RGB565_GREEN)  >> 5) <<2;
        rgb888Color[n+2]    = (color & RGB565_BLUE) <<3;
    }
}

static rt_err_t read_reg(struct rt_i2c_bus_device *bus, rt_uint8_t reg, rt_uint8_t len, rt_uint8_t *buf)
{
    struct rt_i2c_msg msg[2];

    RT_ASSERT(bus != RT_NULL);

    msg[0].addr  = DEV_ADDRESS;
    msg[0].flags = RT_I2C_WR;
    msg[0].buf   = &reg;
    msg[0].len   = 1;

    msg[1].addr  = DEV_ADDRESS;
    msg[1].flags = RT_I2C_RD;
    msg[1].len   = len;
    msg[1].buf   = buf;

    if (rt_i2c_transfer(bus, msg, 2) == 2)
    {
        return RT_EOK;
    }

    return RT_ERROR;
}

/* i2c write reg */
static rt_err_t write_reg(struct rt_i2c_bus_device *bus, rt_uint8_t reg, rt_uint8_t data)
{
    rt_uint8_t buf[2];
    struct rt_i2c_msg msgs;

    RT_ASSERT(bus != RT_NULL);

    buf[0] = reg ;
    buf[1] = data;

    msgs.addr = DEV_ADDRESS;
    msgs.flags = RT_I2C_WR;
    msgs.buf = buf;
    msgs.len = 2;

    if (rt_i2c_transfer(bus, &msgs, 1) == 1)
    {
        return RT_EOK;
    }

    return RT_ERROR;
}

static rt_err_t gc0328c_read_id(struct rt_i2c_bus_device *bus)
{
    rt_uint8_t id = 0;
    read_reg(bus, 0xf0, 1, &id);

    if (id != GC0328C_ID)
    {
         LOG_E("GC0328C init error, pid: 0x%04x", id);
         return RT_ERROR;
    }
    LOG_I("GC0328C read hid success, pid: 0x%04x", id);

    return RT_EOK;
}

static rt_err_t  camera_inf_cfg_gc0328c_ppi(rt_uint8_t ppi_type)
{
    rt_err_t  ret;
    rt_uint32_t i, size = 0;
    rt_uint8_t *addr, *data;

    switch (ppi_type)
    {
        case QVGA_320_240:
            size = sizeof(gc0328c_QVGA_320_240_talbe) / 2;
            addr = &gc0328c_QVGA_320_240_talbe[0][0];
            data = &gc0328c_QVGA_320_240_talbe[0][1];
            break;
        case VGA_640_480:
            size = sizeof(gc0328c_VGA_640_480_talbe) / 2;
            addr = &gc0328c_VGA_640_480_talbe[0][0];
            data = &gc0328c_VGA_640_480_talbe[0][1];
            break;
        default:
            LOG_E("set PPI unknown\r\n");
            break;
    }

    for(i=0; i<size; i++)
    {
        ret  =  write_reg(i2c_bus, *addr, *data);
        addr += 2;
        data += 2;
    }
    return ret;
}

static rt_err_t  camera_inf_cfg_gc0328c_fps(rt_uint8_t fps_type)
{
    rt_err_t  ret;
    rt_uint32_t i, size = 0;
    rt_uint8_t *addr, *data;

    switch (fps_type)
    {
        case TYPE_5FPS:
            size = sizeof(gc0328c_5pfs_talbe) / 2;
            addr = &gc0328c_5pfs_talbe[0][0];
            data = &gc0328c_5pfs_talbe[0][1];
            break;
        case TYPE_10FPS:
            size = sizeof(gc0328c_10pfs_talbe) / 2;
            addr = &gc0328c_10pfs_talbe[0][0];
            data = &gc0328c_10pfs_talbe[0][1];
            break;
        case TYPE_20FPS:
            size = sizeof(gc0328c_20pfs_talbe) / 2;
            addr = &gc0328c_20pfs_talbe[0][0];
            data = &gc0328c_20pfs_talbe[0][1];
            break;
        default:
            LOG_E("set FPS unknown\r\n");
            break;
    }

    for(i=0; i<size; i++)
    {
        ret = write_reg(i2c_bus, *addr, *data);
        addr += 2;
        data += 2;
    }
    return ret;
}

/* change gc0328c to rgb565 mode */
void gc0328c_rgb565_mode(void)
{
    write_reg(i2c_bus, 0xfe, 0x00);
    write_reg(i2c_bus, 0x49, 0x23);  //切换大小端
    write_reg(i2c_bus, 0x44, 0x26);  //切换到RGB565输出
}

void camera_dma_data_process(void)
{
   //rt_uint16_t i;
   //rt_uint32_t *pbuf;
   //pbuf = jpeg_data_buf + jpeg_data_len;

//   if (DMA2_Stream1->CR & (1<<19))
//   {
//       for (i = 0; i < JPEG_LINE_SIZE; i++)
//       {
//           pbuf[i] = JPEG_LINE0_BUF[i];
//       }
//       _lcd.lcd_info.framebuffer
//       jpeg_data_len += JPEG_LINE_SIZE;
//   }
//   else
//   {
//       for (i = 0; i < JPEG_LINE_SIZE; i++)
//       {
//           pbuf[i] = JPEG_LINE1_BUF[i];
//       }
//       jpeg_data_len += JPEG_LINE_SIZE;
//   }
}

/* After a frame of picture data has been collected. */
void camera_frame_data_process(void)
{
    DCMI_Stop();
    rt_uint32_t i , j , num = 0 , n = 0;
    rt_uint8_t *pbuf;
    rt_uint8_t *dbuf = _lcd.lcd_info.framebuffer;
    rt_uint8_t w = 0 , h = 0;
    rt_uint16_t color;

    if (DMA2_Stream1->CR & (1<<19))
    {
        pbuf = (rt_uint8_t *)JPEG_LINE1_BUF;
    }
    else
    {
        pbuf = (rt_uint8_t *)JPEG_LINE0_BUF;
    }
    SCB_CleanInvalidateDCache();
    //convert_uyvy_to_rgb(pbuf, jpeg_data_buf, 320, 240);
    //pbuf = jpeg_data_buf;
    for(i=0; i<240; i++)
    {
        //rt_memcpy(dbuf+ (i*320*2), pbuf + (i*320*2), 320*2);
        rgb565_to_rgb888((rt_uint16_t *)(pbuf + (i*320*2)), dbuf+ (i*320*3), 320);
    }
    //convert to 96*96*3
    for(j=0 ; j<240 ; j++)
    {
        if(h == 4)
        {
            h = 0;
            continue;
        }
        if(h != 1 && h!= 3)
        {
            h = h + 1;
            continue;
        }
        for(i=40 ; i<280 ; i++)
        {
            if(w == 4)
            {
                w = 0;
                continue;
            }
            if(w != 1 && w != 3)
            {
                w = w + 1;
                continue;
            }
            //96*96 rgb
            model_input_data_rgb[num] = dbuf[j*320*3+i*3];
            model_input_data_rgb[num+1] = dbuf[j*320*3+i*3+1];
            model_input_data_rgb[num+2] = dbuf[j*320*3+i*3+2];
            num = num + 3;

            //96*96 gray
            color = (rt_uint16_t *)(pbuf + (j*320*2) + i*2);
            model_input_data_gray[n] = ((((color>>11)&0xff)<<3)*299+(((color>>5)&0x3f)<<2)*587+((color & 0x1f)<<2)*114+500)/1000;
            n = n + 1;

            w = w + 1;
        }
        h = h + 1;
    }
    rt_event_send(&ov2640_event, 1);
}

int rt_gc0328c_init(void)
{
    rt_uint16_t i = 0;
    rt_err_t result = RT_EOK;
    rt_device_t dcmi_dev = RT_NULL;

    /* ov2640 reset */
//    rt_pin_mode(RESET_PIN, PIN_MODE_OUTPUT);
//    rt_pin_write(RESET_PIN, PIN_LOW);
//    rt_thread_delay(20);
//    rt_pin_write(RESET_PIN, PIN_HIGH);
//    rt_thread_delay(20);

    i2c_bus = rt_i2c_bus_device_find(I2C_NAME);
    if (i2c_bus == RT_NULL)
    {
        LOG_E("can't find %s deivce", I2C_NAME);
        return RT_ERROR;
    }

    result = gc0328c_read_id(i2c_bus);
    if (result != RT_EOK)
    {
        LOG_E("gc0328c read id error!");
        return RT_ERROR;
    }

    for (i = 0; i < sizeof(gc0328c_init_talbe) / 2; i++)
    {
        write_reg(i2c_bus, gc0328c_init_talbe[i][0], gc0328c_init_talbe[i][1]);
    }

    result = camera_inf_cfg_gc0328c_ppi(QVGA_320_240);
    if(result != RT_EOK)
    {
        LOG_E("camera_inf_cfg_gc0328c_ppi iic err\n");
        return RT_ERROR;
    }

    result = camera_inf_cfg_gc0328c_fps(TYPE_10FPS);
    if(result != RT_EOK)
    {
        LOG_E("camera_inf_cfg_gc0328c_fps iic err\n");
        return RT_ERROR;
    }

    dcmi_dev = rt_device_find("dcmi");
    if (dcmi_dev == RT_NULL)
    {
        LOG_E("can't find dcmi device!");
        return RT_ERROR;
    }
    rt_device_open(dcmi_dev, RT_DEVICE_FLAG_RDWR);

//    JPEG_LINE0_BUF = rt_malloc(JPEG_BUF_SIZE);
//    if (RT_NULL == JPEG_LINE0_BUF)
//    {
//        rt_kprintf("jpeg data buf0 malloc error!\n");
//        return RT_ERROR;
//    }
//
//    JPEG_LINE1_BUF = rt_malloc(JPEG_BUF_SIZE);
//    if (RT_NULL == JPEG_LINE1_BUF)
//    {
//        rt_kprintf("jpeg data buf1 malloc error!\n");
//        return RT_ERROR;
//    }
//
    jpeg_data_buf = rt_malloc(JPEG_BUF_SIZE);
    if (RT_NULL == jpeg_data_buf)
    {
        rt_kprintf("jpeg data buf2 malloc error!\n");
        return RT_ERROR;
    }
    /* start dcmi capture */
    rt_hw_dcmi_dma_config((rt_uint32_t)JPEG_LINE0_BUF, (rt_uint32_t)JPEG_LINE1_BUF, JPEG_LINE_SIZE);

    rt_kprintf("camera init success!\n");
    return RT_EOK;
}
//INIT_APP_EXPORT(rt_gc0328c_init);

int camera_sample(int argc, char **argv)
{
   rt_err_t result = RT_EOK;

   if (argc != 1)
   {
       rt_kprintf("Usage:\n");
       rt_kprintf("camera_sample file.jpg\n");
       return -1;
   }
   rt_gc0328c_init();
   DCMI_Start();
   return result;;
}
MSH_CMD_EXPORT(camera_sample, record picture to a jpg file);

int read_camera(int argc, char **argv)
{
   rt_err_t result = RT_EOK;
   rt_uint8_t data;
   rt_uint8_t reg;

   reg = atoi(argv[1]);
   read_reg(i2c_bus, reg, 1, &data);

   rt_kprintf("camera reg=0x%02x data=0x%02x\n", reg, data);
   return result;
}
MSH_CMD_EXPORT(read_camera, record picture to a jpg file);

int write_camera(int argc, char **argv)
{
   rt_err_t result = RT_EOK;
   rt_uint8_t data;
   rt_uint8_t reg;

   reg = atoi(argv[1]);
   data = atoi(argv[2]);
   write_reg(i2c_bus, reg, data);

   rt_kprintf("camera reg=0x%02x data=0x%02x\n", reg, data);
   return result;
}
MSH_CMD_EXPORT(write_camera, record picture to a jpg file);

#endif
