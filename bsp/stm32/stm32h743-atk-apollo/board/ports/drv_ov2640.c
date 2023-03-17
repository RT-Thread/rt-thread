/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-08-03     thread-liu        the first version
 */

#include "board.h"

#if defined(BSP_USING_OV2640)

#include <dfs_file.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/statfs.h>
#include <drv_ov2640.h>
#include <drv_dcmi.h>
#include "pcf8574.h"

#define DRV_DEBUG
//#define CAMERA_DUMP
#define LOG_TAG     "drv.ov2640"
#include <drv_log.h>

#define DEV_ADDRESS      0x30 /* OV2640 address */
#define I2C_NAME        "i2c2"

#define RESET_PIN        GET_PIN(A, 15) /* camera reset pin */

/* camera PWDN pin */
#define DCMI_PWDN_IO    2 /* pcf8574 (0-7) */

volatile rt_uint32_t jpeg_data_len = 0;
volatile rt_uint8_t  jpeg_data_ok  = 0;
struct rt_i2c_bus_device *i2c_bus  = RT_NULL;

#define JPEG_BUF_SIZE   32 * 1024
#define JPEG_LINE_SIZE  1 * 1024

static pcf8574_device_t pcf_dev = RT_NULL;

static rt_uint32_t *jpeg_data_buf = RT_NULL;
static rt_uint32_t JPEG_LINE0_BUF[JPEG_LINE_SIZE];
static rt_uint32_t JPEG_LINE1_BUF[JPEG_LINE_SIZE];

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

static rt_err_t read_reg(struct rt_i2c_bus_device *bus, rt_uint8_t reg, rt_uint8_t len, rt_uint8_t *buf)
{
    struct rt_i2c_msg msg[2];

    RT_ASSERT(bus != RT_NULL);

    msg[0].addr  = DEV_ADDRESS;
    msg[0].flags = RT_I2C_WR;
    msg[0].buf   = &reg;
    msg[0].len   = 2;

    msg[1].addr  = DEV_ADDRESS;
    msg[1].flags = RT_I2C_RD;
    msg[1].len   = len;
    msg[1].buf   = buf;

    if (rt_i2c_transfer(bus, msg, 2) == 2)
    {
        return RT_EOK;
    }

    return -RT_ERROR;
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

    return -RT_ERROR;
}

static rt_err_t ov2640_read_id(struct rt_i2c_bus_device *bus)
{
    rt_uint8_t read_value[2];
    rt_uint16_t id = 0;
    read_reg(bus, OV2640_SENSOR_MIDH, 1, &read_value[0]);
    read_reg(bus, OV2640_SENSOR_MIDL, 1, &read_value[1]);
    id = ((rt_uint16_t)(read_value[0] << 8) & 0xFF00);
    id |= ((rt_uint16_t)(read_value[1]) & 0x00FF);

    if (id != OV2640_MID)
    {
        LOG_E("ov2640 init error, mid: 0x%04x", id);
        return -RT_ERROR;
    }

    LOG_I("ov2640 read mid success, mid: 0x%04x", id);

    read_reg(bus, OV2640_SENSOR_PIDH, 1, &read_value[0]);
    read_reg(bus, OV2640_SENSOR_PIDL, 1, &read_value[1]);
    id = ((rt_uint16_t)(read_value[0] << 8) & 0xFF00);
    id |= ((rt_uint16_t)(read_value[1]) & 0x00FF);

    if (id != OV2640_PID)
    {
        LOG_E("ov2640 init error, pid: 0x%04x", id);
        return -RT_ERROR;
    }

    LOG_I("ov2640 read hid success, pid: 0x%04x", id);

    return RT_EOK;
}

/* change ov2640 to jpeg mode */
void ov2640_jpeg_mode(void)
{
    rt_uint16_t i=0;
    /* set yun422 mode */
    for (i = 0; i < (sizeof(ov2640_yuv422_reg_tbl) / 2); i++)
    {
        write_reg(i2c_bus, ov2640_yuv422_reg_tbl[i][0],ov2640_yuv422_reg_tbl[i][1]);
    }

    /* set jpeg mode */
    for(i=0;i<(sizeof(ov2640_jpeg_reg_tbl)/2);i++)
    {
        write_reg(i2c_bus, ov2640_jpeg_reg_tbl[i][0],ov2640_jpeg_reg_tbl[i][1]);
    }
}

/* change ov2640 to rgb565 mode */
void ov2640_rgb565_mode(void)
{
    rt_uint16_t i=0;
    for (i = 0; i < (sizeof(ov2640_rgb565_reg_tbl) / 2); i++)
    {
        write_reg(i2c_bus, ov2640_rgb565_reg_tbl[i][0],ov2640_rgb565_reg_tbl[i][1]);
    }
}

/* set auto exposure */
void ov2640_set_auto_exposure(rt_uint8_t level)
{
    rt_uint8_t i = 0;
    rt_uint8_t *p = (rt_uint8_t*)OV2640_AUTOEXPOSURE_LEVEL[level];
    for (i = 0; i < 4; i++)
    {
        write_reg(i2c_bus, p[i*2],p[i*2+1]);
    }
}

/* set light mode
 * 0: auto
 * 1: sunny
 * 2: cloudy
 * 3: office
 * 4: home
 * */
void ov2640_set_light_mode(rt_uint8_t mode)
{
    rt_uint8_t regccval, regcdval, regceval;

    switch(mode)
    {
        case 0:
            write_reg(i2c_bus, 0xFF, 0x00);
            write_reg(i2c_bus, 0xC7, 0x10);
            return;

        case 2:
            regccval = 0x65;
            regcdval = 0x41;
            regceval = 0x4F;
            break;

        case 3:
            regccval = 0x52;
            regcdval = 0x41;
            regceval = 0x66;
            break;

        case 4:
            regccval = 0x42;
            regcdval = 0x3F;
            regceval = 0x71;
            break;

        default:
            regccval = 0x5E;
            regcdval = 0x41;
            regceval = 0x54;
            break;
    }

    write_reg(i2c_bus, 0xFF, 0x00);
    write_reg(i2c_bus, 0xC7, 0x40);
    write_reg(i2c_bus, 0xCC, regccval);
    write_reg(i2c_bus, 0xCD, regcdval);
    write_reg(i2c_bus, 0xCE, regceval);
}

/* set color saturation
 * 0: -2
 * 1: -1
 * 2: 0
 * 3: +1
 * 4: +2
 * */
void ov2640_set_color_saturation(rt_uint8_t sat)
{
    rt_uint8_t reg7dval = ((sat+2)<<4) | 0x08;
    write_reg(i2c_bus, 0xFF, 0X00);
    write_reg(i2c_bus, 0x7C, 0X00);
    write_reg(i2c_bus, 0x7D, 0X02);
    write_reg(i2c_bus, 0x7C, 0X03);
    write_reg(i2c_bus, 0x7D, reg7dval);
    write_reg(i2c_bus, 0x7D, reg7dval);
}

/* set brightness
 * 0: -2
 * 1: -1
 * 2: 0
 * 3: 1
 * 4: 2
 * */
void ov2640_set_brightness(rt_uint8_t bright)
{
  write_reg(i2c_bus, 0xff, 0x00);
  write_reg(i2c_bus, 0x7c, 0x00);
  write_reg(i2c_bus, 0x7d, 0x04);
  write_reg(i2c_bus, 0x7c, 0x09);
  write_reg(i2c_bus, 0x7d, bright << 4);
  write_reg(i2c_bus, 0x7d, 0x00);
}

/* set contrast
 * 0: -2
 * 1: -1
 * 2: 0
 * 3: 1
 * 4: 2
 * */
void ov2640_set_contrast(rt_uint8_t contrast)
{
    rt_uint8_t reg7d0val, reg7d1val;

    switch(contrast)
    {
        case 0:
            reg7d0val = 0x18;
            reg7d1val = 0x34;
            break;

        case 1:
            reg7d0val = 0x1C;
            reg7d1val = 0x2A;
            break;

        case 3:
            reg7d0val = 0x24;
            reg7d1val = 0x16;
            break;

        case 4:
            reg7d0val = 0x28;
            reg7d1val = 0x0C;
            break;

        default:
            reg7d0val = 0x20;
            reg7d1val = 0x20;
            break;
    }
    write_reg(i2c_bus, 0xff, 0x00);
    write_reg(i2c_bus, 0x7c, 0x00);
    write_reg(i2c_bus, 0x7d, 0x04);
    write_reg(i2c_bus, 0x7c, 0x07);
    write_reg(i2c_bus, 0x7d, 0x20);
    write_reg(i2c_bus, 0x7d, reg7d0val);
    write_reg(i2c_bus, 0x7d, reg7d1val);
    write_reg(i2c_bus, 0x7d, 0x06);
}

/* set special effects
 * 0: noraml
 * 1: negative film
 * 2: black-and-white
 * 3: the red
 * 4: the green
 * 5: the blue
 * 6: Retro
*/
void ov2640_set_special_effects(rt_uint8_t eft)
{
    rt_uint8_t reg7d0val, reg7d1val, reg7d2val;

    switch(eft)
    {
        case 1:
            reg7d0val = 0x40;
            break;
        case 2:
            reg7d0val = 0x18;
            break;
        case 3:
            reg7d0val = 0x18;
            reg7d1val = 0x40;
            reg7d2val = 0xC0;
            break;
        case 4:
            reg7d0val = 0x18;
            reg7d1val = 0x40;
            reg7d2val = 0x40;
            break;
        case 5:
            reg7d0val = 0x18;
            reg7d1val = 0xA0;
            reg7d2val = 0x40;
            break;
        case 6:
            reg7d0val = 0x18;
            reg7d1val = 0x40;
            reg7d2val = 0xA6;
            break;
        default:
            reg7d0val = 0x00;
            reg7d1val = 0x80;
            reg7d2val = 0x80;
            break;
    }
    write_reg(i2c_bus, 0xff, 0x00);
    write_reg(i2c_bus, 0x7c, 0x00);
    write_reg(i2c_bus, 0x7d, reg7d0val);
    write_reg(i2c_bus, 0x7c, 0x05);
    write_reg(i2c_bus, 0x7d, reg7d1val);
    write_reg(i2c_bus, 0x7d, reg7d2val);
}

/* set the image output window */
void ov2640_set_window_size(rt_uint16_t sx,rt_uint16_t sy,rt_uint16_t width,rt_uint16_t height)
{
    rt_uint16_t endx;
    rt_uint16_t endy;
    rt_uint8_t temp;
    endx = sx + width / 2;
    endy = sy + height / 2;

    write_reg(i2c_bus, 0xFF, 0x01);
    read_reg(i2c_bus, 0x03, 1, &temp);
    temp &= 0xF0;
    temp |= ((endy & 0x03) << 2) | (sy & 0x03);
    write_reg(i2c_bus, 0x03, temp);
    write_reg(i2c_bus, 0x19, sy>>2);
    write_reg(i2c_bus, 0x1A, endy>>2);

    read_reg(i2c_bus, 0x32, 1, &temp);
    temp &= 0xC0;
    temp |= ((endx & 0x07) << 3) | (sx & 0x07);
    write_reg(i2c_bus, 0x32, temp);
    write_reg(i2c_bus, 0x17, sx>>3);
    write_reg(i2c_bus, 0x18, endx>>3);
}

/* set the image output size */
rt_uint8_t ov2640_set_image_out_size(rt_uint16_t width,rt_uint16_t height)
{
    rt_uint16_t outh, outw;
    rt_uint8_t temp;

    if(width%4)return 1;
    if(height%4)return 2;
    outw = width / 4;
    outh = height / 4;
    write_reg(i2c_bus, 0xFF, 0x00);
    write_reg(i2c_bus, 0xE0, 0x04);
    write_reg(i2c_bus, 0x5A, outw & 0XFF);
    write_reg(i2c_bus, 0x5B, outh & 0XFF);
    temp = (outw >> 8) & 0x03;
    temp |= (outh >> 6) & 0x04;
    write_reg(i2c_bus, 0x5C, temp);
    write_reg(i2c_bus, 0xE0, 0X00);

    return RT_EOK;
}

/* set the image window size */
rt_err_t ov2640_set_image_window_size(rt_uint16_t offx, rt_uint16_t offy, rt_uint16_t width, rt_uint16_t height)
{
    rt_uint16_t hsize, vsize;
    rt_uint8_t temp;
    if ((width % 4) || (height%4))
    {
        return -RT_ERROR;
    }
    hsize = width / 4;
    vsize = height / 4;
    write_reg(i2c_bus, 0XFF,0X00);
    write_reg(i2c_bus, 0XE0,0X04);
    write_reg(i2c_bus, 0X51,hsize&0XFF);
    write_reg(i2c_bus, 0X52,vsize&0XFF);
    write_reg(i2c_bus, 0X53,offx&0XFF);
    write_reg(i2c_bus, 0X54,offy&0XFF);
    temp=(vsize>>1)&0X80;
    temp|=(offy>>4)&0X70;
    temp|=(hsize>>5)&0X08;
    temp|=(offx>>8)&0X07;
    write_reg(i2c_bus, 0X55,temp);
    write_reg(i2c_bus, 0X57,(hsize>>2)&0X80);
    write_reg(i2c_bus, 0XE0,0X00);
    return RT_EOK;
}

/* set output resolution */
rt_uint8_t ov2640_set_image_size(rt_uint16_t width ,rt_uint16_t height)
{
   rt_uint8_t temp;
   write_reg(i2c_bus, 0xFF, 0x00);
   write_reg(i2c_bus, 0xE0, 0x04);
   write_reg(i2c_bus, 0xC0, (width >>3) & 0xFF);
   write_reg(i2c_bus, 0xC1, (height >> 3) & 0xFF);
   temp = (width & 0x07) << 3;
   temp |= height & 0x07;
   temp |= (width >> 4) & 0x80;
   write_reg(i2c_bus, 0x8C, temp);
   write_reg(i2c_bus, 0xE0, 0x00);

   return RT_EOK;
}

void camera_dma_data_process(void)
{
   rt_uint16_t i;
   rt_uint32_t *pbuf;
   pbuf = jpeg_data_buf + jpeg_data_len;

   if (DMA2_Stream1->CR & (1<<19))
   {
       for (i = 0; i < JPEG_LINE_SIZE; i++)
       {
           pbuf[i] = JPEG_LINE0_BUF[i];
       }
       jpeg_data_len += JPEG_LINE_SIZE;
   }
   else
   {
       for (i = 0; i < JPEG_LINE_SIZE; i++)
       {
           pbuf[i] = JPEG_LINE1_BUF[i];
       }
       jpeg_data_len += JPEG_LINE_SIZE;
   }
   SCB_CleanInvalidateDCache();
}

/* After a frame of picture data has been collected. */
void camera_frame_data_process(void)
{
   rt_uint16_t i, rlen;
   rt_uint32_t *pbuf = RT_NULL;

   if (jpeg_data_ok == 0)
   {
       DMA2_Stream1->CR &= ~(1<<0);
       while(DMA2_Stream1->CR & 0x01);

       rlen = JPEG_LINE_SIZE - DMA2_Stream1->NDTR;
       pbuf = jpeg_data_buf + jpeg_data_len;

       if (DMA2_Stream1->CR & (1<<19))
       {
           for (i = 0; i < rlen; i++)
           {
               pbuf[i] = JPEG_LINE1_BUF[i];
           }
       }
       else
       {
           for (i = 0; i < rlen; i++)
           {
               pbuf[i] = JPEG_LINE0_BUF[i];
           }
       }
       jpeg_data_len += rlen;
       jpeg_data_ok   = 1;
   }
   if (jpeg_data_ok==2)
   {
       DMA2_Stream1->NDTR = JPEG_LINE_SIZE;
       DMA2_Stream1->CR  |= 1<<0;
       jpeg_data_ok  = 0;
       jpeg_data_len = 0;
   }
}

int ov2640_pwdn_set(rt_uint8_t sta)
{
    if (pcf_dev == RT_NULL)
    {
       LOG_E("can't find pcf8574 device!");
        return -1;
    }
    pcf8574_pin_write(pcf_dev, DCMI_PWDN_IO, sta);

    return 0;
}

void sw_ov2640_mode(void)
{
    GPIO_InitTypeDef GPIO_Initure = {0};

    ov2640_pwdn_set(0);

    GPIO_Initure.Pin       = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_11;
    GPIO_Initure.Mode      = GPIO_MODE_AF_PP;
    GPIO_Initure.Pull      = GPIO_PULLUP;
    GPIO_Initure.Speed     = GPIO_SPEED_HIGH;
    GPIO_Initure.Alternate = GPIO_AF13_DCMI;
    HAL_GPIO_Init(GPIOC,&GPIO_Initure);
}

void sw_sdcard_mode(void)
{
    GPIO_InitTypeDef GPIO_Initure = {0};

    ov2640_pwdn_set(1); /* OV2640 Power Down */

    GPIO_Initure.Pin       = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_11;
    GPIO_Initure.Mode      = GPIO_MODE_AF_PP;
    GPIO_Initure.Pull      = GPIO_PULLUP;
    GPIO_Initure.Speed     = GPIO_SPEED_HIGH;
    GPIO_Initure.Alternate = GPIO_AF12_SDMMC1;
    HAL_GPIO_Init(GPIOC, &GPIO_Initure);
}

int rt_ov2640_init(void)
{
    rt_uint16_t i = 0;
    rt_err_t result = RT_EOK;
    rt_device_t dcmi_dev = RT_NULL;

    sw_ov2640_mode();
    pcf_dev = pcf8574_init("i2c1", RT_NULL);
    if (pcf_dev == RT_NULL)
    {
        LOG_E("can't find pcf8574, please check it");
        return -RT_ERROR;
    }

    ov2640_pwdn_set(0);
    rt_thread_delay(20);

    /* ov2640 hard reset */
    rt_pin_mode(RESET_PIN, PIN_MODE_OUTPUT);
    rt_pin_write(RESET_PIN, PIN_LOW);
    rt_thread_delay(20);
    rt_pin_write(RESET_PIN, PIN_HIGH);
    rt_thread_delay(20);

    i2c_bus = rt_i2c_bus_device_find(I2C_NAME);
    if (i2c_bus == RT_NULL)
    {
        LOG_E("can't find %s deivce", I2C_NAME);
        return -RT_ERROR;
    }
    /* Prepare the camera to be configured */
    result = write_reg(i2c_bus, OV2640_DSP_RA_DLMT, 0x01);
    if (result != RT_EOK )
    {
        LOG_E("ov2640 write reg error!");
        return -RT_ERROR;
    }
    rt_thread_delay(10);
    result = write_reg(i2c_bus, OV2640_SENSOR_COM7, 0x80);
    if (result != RT_EOK)
    {
        LOG_E("ov2640 soft reset error!");
        return -RT_ERROR;
    }
    rt_thread_delay(20);

    result = ov2640_read_id(i2c_bus);
    if (result != RT_EOK )
    {
        LOG_E("ov2640 read id error!");
        return -RT_ERROR;
    }

    for (i = 0; i < sizeof(ov2640_svga_init_reg_tbl) / 2; i++)
    {
        write_reg(i2c_bus, ov2640_svga_init_reg_tbl[i][0], ov2640_svga_init_reg_tbl[i][1]);
    }

    ov2640_rgb565_mode();
    ov2640_set_light_mode(0);
    ov2640_set_color_saturation(3);
    ov2640_set_brightness(4);
    ov2640_set_contrast(3);
    ov2640_jpeg_mode();
    ov2640_set_image_window_size(0, 0, 320, 240);
    ov2640_set_image_out_size(320, 240);

    dcmi_dev = rt_device_find("dcmi");
    if (dcmi_dev == RT_NULL)
    {
        LOG_E("can't find dcmi device!");
        return -RT_ERROR;
    }
    rt_device_open(dcmi_dev, RT_DEVICE_FLAG_RDWR);

   jpeg_data_buf = rt_malloc(JPEG_BUF_SIZE);
   if (RT_NULL == jpeg_data_buf)
   {
       rt_kprintf("jpeg data buf malloc error!\n");
       return -RT_ERROR;
   }

    /* start dcmi capture */
    rt_hw_dcmi_dma_config((rt_uint32_t)JPEG_LINE0_BUF, (rt_uint32_t)JPEG_LINE1_BUF, JPEG_LINE_SIZE);

    rt_kprintf("camera init success!\n");

    return RT_EOK;
}
INIT_APP_EXPORT(rt_ov2640_init);

int camera_sample(int argc, char **argv)
{
   rt_err_t result = RT_EOK;
   int fd = -1;
   rt_uint32_t i, jpg_start, jpg_len;
   rt_uint8_t jpg_head = 0;
   rt_uint8_t *p = RT_NULL;

   if (argc != 2)
   {
       rt_kprintf("Usage:\n");
       rt_kprintf("camera_sample file.jpg\n");
       return -1;
   }

   sw_ov2640_mode();
   DCMI_Start();

   while (1)
   {
       while (jpeg_data_ok != 1);
       jpeg_data_ok = 2;
       while (jpeg_data_ok != 1);
       DCMI_Stop();

       p = (rt_uint8_t *)jpeg_data_buf;
       jpg_len  = 0;
       jpg_head = 0;
       for (i = 0; i < jpeg_data_len * 4; i++)
       {
           /* jpg head */
           if ((p[i] == 0xFF) && (p[i + 1] == 0xD8))
           {
               jpg_start = i;
               jpg_head = 1;
           }
           /* jpg end */
           if ((p[i] == 0xFF) && (p[i + 1] == 0xD9) && jpg_head)
           {
               jpg_len = i - jpg_start + 2; /* a picture len */
               break;
           }
       }
       if (jpg_len)
       {
           p += jpg_start;
           sw_sdcard_mode();
           fd = open(argv[1], O_WRONLY | O_CREAT);
           if (fd < 0)
           {
               rt_kprintf("open file for recording failed!\n");
               result = -RT_ERROR;
               goto _exit;
           }
           else
           {
               write(fd, p, jpg_len);
               close(fd);
               rt_kprintf("%s picture capture complate!\n", argv[1]);
               break;
           }
       }
       else
       {
           rt_kprintf("jpg_len error!\n");
           result = -RT_ERROR;
           goto _exit;
       }
   }

_exit:
    return result;;
}
MSH_CMD_EXPORT(camera_sample, record picture to a jpg file);

#endif
