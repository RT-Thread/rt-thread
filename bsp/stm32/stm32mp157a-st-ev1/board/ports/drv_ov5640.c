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

#if defined(BSP_USING_DCMI)

#include "drv_mfx.h"
#include <dfs_file.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/statfs.h>
#include "drv_ov5640.h"

//#define DRV_DEBUG
//#define CAMERA_DUMP
#define LOG_TAG     "drv.ov5640"
#include <drv_log.h>

#define CHIP_ADDRESS    0x3C /* OV5640 address */
#define I2C_NAME        "i2c2"

#define JPEG_BUF_SIZE   8 * 1024
#define JPEG_LINE_SIZE  1 * 1024

#if defined(__ARMCC_VERSION)
__attribute__((at(0x2FFCC000))) static rt_int32_t JPEG_DATA_BUF[JPEG_BUF_SIZE];
#elif defined(__GNUC__)
static rt_int32_t JPEG_DATA_BUF[JPEG_BUF_SIZE] __attribute__((section(".Dcmi0Section")));
#elif defined(__ICCARM__)
#pragma location = 0x2FFCC000
__no_init static rt_int32_t JPEG_DATA_BUF[JPEG_BUF_SIZE];
#endif

#if defined(__ARMCC_VERSION)
__attribute__((at(0x2FFDC000))) static rt_int32_t JPEG_LINE_BUF[2][JPEG_LINE_SIZE];
#elif defined(__GNUC__)
static rt_int32_t JPEG_LINE_BUF[2][JPEG_LINE_SIZE]  __attribute__((section(".Dcmi1Section")));
#elif defined(__ICCARM__)
#pragma location = 0x2FFDC000
__no_init static rt_int32_t JPEG_LINE_BUF[2][JPEG_LINE_SIZE];
#endif

volatile rt_uint32_t jpeg_data_len = 0;
volatile rt_uint8_t  jpeg_data_ok  = 0;
struct rt_i2c_bus_device *i2c_bus  = RT_NULL;
extern DCMI_HandleTypeDef dcmi;
extern DMA_HandleTypeDef hdma_dcmi;

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

static rt_err_t read_reg(struct rt_i2c_bus_device *bus, rt_uint16_t reg, rt_uint8_t len, rt_uint8_t *buf)
{
    struct rt_i2c_msg msg[2] = {0, 0};
    static rt_uint8_t i2c_reg[2] = {0, 0};

    RT_ASSERT(bus != RT_NULL);

    i2c_reg[0] = ((uint16_t)(reg >> 8) & 0xFF);
    i2c_reg[1] = ((uint16_t)(reg & 0xFF));

    msg[0].addr  = CHIP_ADDRESS;
    msg[0].flags = RT_I2C_WR;
    msg[0].buf   = i2c_reg;
    msg[0].len   = 2;

    msg[1].addr  = CHIP_ADDRESS;
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
static rt_err_t write_reg(struct rt_i2c_bus_device *bus, rt_uint16_t reg, rt_uint8_t data)
{
    rt_uint8_t buf[3];
    struct rt_i2c_msg msgs;

    RT_ASSERT(bus != RT_NULL);

    buf[0] = ((uint16_t)(reg >> 8) & 0xFF);
    buf[1] = ((uint16_t)(reg)&0xFF);

    buf[2] = data;

    msgs.addr = CHIP_ADDRESS;
    msgs.flags = RT_I2C_WR;
    msgs.buf = buf;
    msgs.len = 3;

    if (rt_i2c_transfer(bus, &msgs, 1) == 1)
    {
        return RT_EOK;
    }

    return -RT_ERROR;
}

static rt_err_t ov5640_read_id(struct rt_i2c_bus_device *bus, rt_uint16_t *id)
{
    rt_uint8_t read_value[2];

    read_reg(bus, 0x300A, 1, &read_value[0]);
    read_reg(bus, 0x300B, 1, &read_value[1]);
    *id = ((uint16_t)(read_value[0] << 8) & 0xFF00);
    *id |= ((uint16_t)(read_value[1]) & 0x00FF);

    if (*id != OV5640_ID)
    {
        LOG_E("ov5640 init error, id: 0x%04x", *id);
        return -RT_ERROR;
    }

    LOG_I("ov5640 init success, id: 0x%04x", *id);

    return RT_EOK;
}

static rt_err_t ov5640_hard_reset(struct rt_i2c_bus_device *bus)
{
    /* Camera sensor RESET sequence */
    rt_mfx_pin_mode(CAMERA_RST1, IO_MODE_OUTPUT);
    rt_mfx_pin_mode(CAMERA_XSDN, IO_MODE_OUTPUT);

    /* Assert the camera STANDBY pin (active high)  */
    rt_mfx_pin_write(CAMERA_XSDN, BSP_IO_PIN_SET);

    /* Assert the camera RSTI pin (active low) */
    rt_mfx_pin_write(CAMERA_RST1, BSP_IO_PIN_RESET);

    rt_thread_delay(100); /* RST and XSDN signals asserted during 100ms */

    /* De-assert the camera STANDBY pin (active high) */
    rt_mfx_pin_write(CAMERA_XSDN, BSP_IO_PIN_RESET);

    rt_thread_delay(3); /* RST de-asserted and XSDN asserted during 3ms */

    /* De-assert the camera RSTI pin (active low) */
    rt_mfx_pin_write(CAMERA_RST1, BSP_IO_PIN_SET);

    rt_thread_delay(6); /* RST de-asserted during 3ms */

    return RT_EOK;
}

void OV5640_Flash_Ctrl(struct rt_i2c_bus_device *bus, rt_uint8_t sw)
{
    write_reg(bus, 0x3016, 0X02);
    write_reg(bus, 0x301C, 0X02);
    if (sw)
    {
        write_reg(bus, 0X3019, 0X02);
    }
    else
    {
        write_reg(bus, 0X3019, 0X00);
    }
}

static rt_err_t ov5640_config(struct rt_i2c_bus_device *bus)
{
    rt_uint32_t i = 0;
    rt_uint8_t value = 0;

    write_reg(bus, 0x3103, 0X11); /* system clock from pad, bit[1] */
    write_reg(bus, 0X3008, 0X82); /* soft reset */

    rt_thread_delay(10);

    for (i = 0; i < (sizeof(RGB565_Init) / 4); i++)
    {
        write_reg(bus, RGB565_Init[i][0], RGB565_Init[i][1]);
        rt_thread_delay(10);
        read_reg(bus, RGB565_Init[i][0], 1, &value);

        if (RGB565_Init[i][1] != value)
        {
            LOG_D("error reg value[0x%x]:0x%02x - 0x%02x", RGB565_Init[i][0], RGB565_Init[i][1], value);
        }
    }

    OV5640_Flash_Ctrl(bus, 1); /* open camera flash*/
    rt_thread_delay(3);
    OV5640_Flash_Ctrl(bus, 0); /* close camera flash*/

    return RT_EOK;
}

/* JPEG */
void ov5640_jpeg_mode(struct rt_i2c_bus_device *bus)
{
    rt_uint16_t i = 0;
    for (i = 0; i < (sizeof(OV5640_jpeg_reg_tbl) / 4); i++)
    {
        write_reg(bus, OV5640_jpeg_reg_tbl[i][0], OV5640_jpeg_reg_tbl[i][1]);
    }
}

/* RGB565 */
void ov5640_rgb565_mode(struct rt_i2c_bus_device *bus)
{
    rt_uint16_t i = 0;
    for (i = 0; i < (sizeof(ov5640_rgb565_reg_tbl) / 4); i++)
    {
        write_reg(bus, ov5640_rgb565_reg_tbl[i][0], ov5640_rgb565_reg_tbl[i][1]);
    }

    write_reg(bus, 0x3821, 0x06);
}

rt_uint8_t ov5640_focus_init(struct rt_i2c_bus_device *bus)
{
    rt_uint16_t tickstart = 0 ,i = 0;
    rt_uint16_t addr = 0x8000;
    rt_uint8_t state = 0x8F;

    write_reg(bus, 0x3000, 0x20); //reset MCU
    for (i = 0; i < sizeof(OV5640_AF_Config); i++)
    {
        write_reg(bus, addr, OV5640_AF_Config[i]);
        addr++;
    }
    write_reg(bus, 0x3022, 0x00);
    write_reg(bus, 0x3023, 0x00);
    write_reg(bus, 0x3024, 0x00);
    write_reg(bus, 0x3025, 0x00);
    write_reg(bus, 0x3026, 0x00);
    write_reg(bus, 0x3027, 0x00);
    write_reg(bus, 0x3028, 0x00);
    write_reg(bus, 0x3029, 0x7f);
    write_reg(bus, 0x3000, 0x00);
    i = 0;

    tickstart = rt_tick_get();
    do
    {
        read_reg(bus, 0x3029, 1, &state);
        if (rt_tick_get() - tickstart > 1000)
        {
            return -RT_ERROR;
        }
    } while (state != 0x70);

    return RT_EOK;
}

void ov5640_set_light(struct rt_i2c_bus_device *bus, rt_uint8_t mode)
{
    rt_uint8_t i = 0;
    write_reg(bus, 0x3212, 0x03); //start group 3

    for (i = 0; i < 7; i++)
    {
        write_reg(bus, 0x3400 + i, OV5640_LIGHTMODE_TBL[mode][i]);
    }

    write_reg(bus, 0x3212, 0x13); //end group 3
    write_reg(bus, 0x3212, 0xa3); //launch group 3
}

/* sat:0~6 */
void ov5640_color_saturation(struct rt_i2c_bus_device *bus, rt_uint8_t sat)
{
    rt_uint8_t i = 0;
    write_reg(bus, 0x3212, 0x03); //start group 3
    write_reg(bus, 0x5381, 0x1c);
    write_reg(bus, 0x5382, 0x5a);
    write_reg(bus, 0x5383, 0x06);
    for (i = 0; i < 6; i++)
    {
        write_reg(bus, 0x5384 + i, OV5640_SATURATION_TBL[sat][i]);
    }
    write_reg(bus, 0x538b, 0x98);
    write_reg(bus, 0x538a, 0x01);
    write_reg(bus, 0x3212, 0x13); //end group 3
    write_reg(bus, 0x3212, 0xa3); //launch group 3
}

/* bright:0~8 */
void ov5640_set_brightness(struct rt_i2c_bus_device *bus, rt_uint8_t bright)
{
    rt_uint8_t brtval;
    if (bright < 4)
    {
        brtval = 4 - bright;
    }
    else
    {
        brtval = bright - 4;
    }
    write_reg(bus, 0x3212, 0x03); //start group 3
    write_reg(bus, 0x5587, brtval << 4);
    if (bright < 4)
    {
        write_reg(bus, 0x5588, 0x09);
    }
    else
    {
        write_reg(bus, 0x5588, 0x01);
    }
    write_reg(bus, 0x3212, 0x13); //end group 3
    write_reg(bus, 0x3212, 0xa3); //launch group 3
}

/* contrast:0~6 */
void ov5640_contrast(struct rt_i2c_bus_device *bus, rt_uint8_t contrast)
{
    rt_uint8_t reg0val = 0x00;
    rt_uint8_t reg1val = 0x20;
    switch (contrast)
    {
    case 0:
        reg1val = reg0val = 0X14;
        break;

    case 1:
        reg1val = reg0val = 0X18;
        break;

    case 2:
        reg1val = reg0val = 0X1C;
        break;

    case 4:
        reg0val = 0X10;
        reg1val = 0X24;
        break;

    case 5:
        reg0val = 0X18;
        reg1val = 0X28;
        break;

    case 6:
        reg0val = 0X1C;
        reg1val = 0X2C;

        break;
    }
    write_reg(bus, 0x3212, 0x03); //start group 3
    write_reg(bus, 0x5585, reg0val);
    write_reg(bus, 0x5586, reg1val);
    write_reg(bus, 0x3212, 0x13); //end group 3
    write_reg(bus, 0x3212, 0xa3); //launch group 3
}
/* sharp:0~33 */
void ov5640_set_sharpness(struct rt_i2c_bus_device *bus, rt_uint8_t sharp)
{
    if (sharp < 33)
    {
        write_reg(bus, 0x5308, 0x65);
        write_reg(bus, 0x5302, sharp);
    }
    else
    {
        write_reg(bus, 0x5308, 0x25);
        write_reg(bus, 0x5300, 0x08);
        write_reg(bus, 0x5301, 0x30);
        write_reg(bus, 0x5302, 0x10);
        write_reg(bus, 0x5303, 0x00);
        write_reg(bus, 0x5309, 0x08);
        write_reg(bus, 0x530a, 0x30);
        write_reg(bus, 0x530b, 0x04);
        write_reg(bus, 0x530c, 0x06);
    }
}

rt_uint8_t ov5640_focus_constant(struct rt_i2c_bus_device *bus)
{
    rt_uint8_t temp = 0;
    rt_uint16_t tickstrat = 0;

    write_reg(bus, 0x3023, 0x01);
    write_reg(bus, 0x3022, 0x08);
    do
    {
        tickstrat = rt_tick_get();
        read_reg(bus, 0x3023, 1, &temp);
        if (rt_tick_get() - tickstrat > 1000)
        {
            return -RT_ERROR;
        }
    } while (temp != 0x00);

    write_reg(bus, 0x3023, 0x01);
    write_reg(bus, 0x3022, 0x04);

    do
    {
        tickstrat = rt_tick_get();
        read_reg(bus, 0x3023, 1, &temp);
        if (rt_tick_get() - tickstrat > 1000)
        {
            return -RT_ERROR;
        }
    } while (temp != 0x00);

    return 0;
}

rt_uint8_t ov5640_set_outsize(struct rt_i2c_bus_device *bus, rt_uint16_t offx, rt_uint16_t offy, rt_uint16_t width, rt_uint16_t height)
{
    write_reg(bus, 0X3212, 0X03);

    write_reg(bus, 0x3808, width >> 8);
    write_reg(bus, 0x3809, width & 0xff);
    write_reg(bus, 0x380a, height >> 8);
    write_reg(bus, 0x380b, height & 0xff);

    write_reg(bus, 0x3810, offx >> 8);
    write_reg(bus, 0x3811, offx & 0xff);

    write_reg(bus, 0x3812, offy >> 8);
    write_reg(bus, 0x3813, offy & 0xff);

    write_reg(bus, 0X3212, 0X13);
    write_reg(bus, 0X3212, 0Xa3);

    return RT_EOK;
}

void rt_hw_camera_rx_callback(void)
{
    rt_uint16_t i;
    rt_int32_t *pbuf = RT_NULL;
    pbuf = JPEG_DATA_BUF + jpeg_data_len;

    if (hdma_dcmi.Instance->CR & (1 << 19))
    {
        for (i = 0; i < JPEG_LINE_SIZE; i++)
        {
            pbuf[i] = JPEG_LINE_BUF[0][i];
        }
        jpeg_data_len += JPEG_LINE_SIZE;

    }
    else
    {
        for (i = 0; i < JPEG_LINE_SIZE; i++)
        {
            pbuf[i] = JPEG_LINE_BUF[1][i];
        }
        jpeg_data_len += JPEG_LINE_SIZE;
    }
}

/* After a frame of JPEG data has been collected. */
void jpeg_data_process(void)
{
    rt_uint16_t i, rlen;
    int *pbuf = RT_NULL;

    if (!jpeg_data_ok)
    {
        __HAL_DMA_DISABLE(&hdma_dcmi);
        rlen = JPEG_LINE_SIZE - __HAL_DMA_GET_COUNTER(&hdma_dcmi);
        pbuf = JPEG_DATA_BUF + jpeg_data_len;
        if (hdma_dcmi.Instance->CR & (1 << 19))
        {
            for (i = 0; i < rlen; i++)
            {
                pbuf[i] = JPEG_LINE_BUF[1][i];
            }
        }
        else
        {
            for (i = 0; i < rlen; i++)
            {
                pbuf[i] = JPEG_LINE_BUF[0][i];
            }
        }
        jpeg_data_len += rlen;
        jpeg_data_ok   = 1;
    }

    if (jpeg_data_ok == 2)
    {
        __HAL_DMA_SET_COUNTER(&hdma_dcmi, JPEG_LINE_SIZE);
        __HAL_DMA_ENABLE(&hdma_dcmi);

        jpeg_data_ok  = 0;
        jpeg_data_len = 0;
    }
}

int rt_hw_ov5640_init(void)
{
    extern void rt_hw_dcmi_dma_config(rt_uint32_t dst_addr1, rt_uint32_t dst_addr2, rt_uint16_t len);

    static rt_uint16_t id = 0;
    rt_device_t dcmi_dev = RT_NULL;

    i2c_bus = rt_i2c_bus_device_find(I2C_NAME);
    if (i2c_bus == RT_NULL)
    {
        LOG_E("can't find %c deivce", I2C_NAME);
        return -RT_ERROR;
    }

    ov5640_hard_reset(i2c_bus);
    ov5640_read_id(i2c_bus, &id);
    ov5640_config(i2c_bus);
    ov5640_rgb565_mode(i2c_bus);        /* rgb565 mode */
    ov5640_focus_init(i2c_bus);
    ov5640_jpeg_mode(i2c_bus);          /* jpeg mode */
    ov5640_set_light(i2c_bus, 0);       /* auto mode  */
    ov5640_color_saturation(i2c_bus, 3);
    ov5640_set_brightness(i2c_bus, 4);  /* brigetness 0 */
    ov5640_contrast(i2c_bus, 3);
    ov5640_set_sharpness(i2c_bus, 33);
    ov5640_focus_constant(i2c_bus);

    /* dcmi init */
    dcmi_dev = rt_device_find("dcmi");
    if (dcmi_dev == RT_NULL)
    {
        LOG_E("can't find dcmi device!");
        return -RT_ERROR;
    }
    rt_device_open(dcmi_dev, RT_DEVICE_FLAG_RDWR);

    rt_hw_dcmi_dma_config((rt_uint32_t)&JPEG_LINE_BUF[0], (rt_uint32_t)&JPEG_LINE_BUF[1], JPEG_LINE_SIZE);
    ov5640_set_outsize(i2c_bus, 4, 0, jpeg_picture_size[1][0], jpeg_picture_size[1][1]);

    return RT_EOK;
}
INIT_APP_EXPORT(rt_hw_ov5640_init);

int camera_sample(int argc, char **argv)
{

    int fd = -1;
    rt_uint32_t i, jpg_start, jpg_len;
    rt_uint16_t tickstart = 0;
    rt_uint8_t jpg_head = 0;
    rt_uint8_t *p = RT_NULL;

    if (argc != 2)
    {
        rt_kprintf("Usage:\n");
        rt_kprintf("camera_sample file.jpg\n");
        return -1;
    }

    /* start dcmi capture */
    __HAL_DMA_ENABLE(&hdma_dcmi);
    dcmi.Instance->CR |= DCMI_CR_CAPTURE;

    tickstart = rt_tick_get();
    while (1)
    {
        if (rt_tick_get() - tickstart > 1000)
        {
            LOG_E("picture capture overtime!");
            break;
        }

        if (jpeg_data_ok == 1)
        {
            dcmi.Instance->CR &= ~(DCMI_CR_CAPTURE);
            tickstart = rt_tick_get();
            while(dcmi.Instance->CR & 0x01)
            {
                if (rt_tick_get() - tickstart > 0x1000)
                {
                    rt_kprintf("dcmi close failed!\n");
                    jpeg_data_ok = 2;
                    break;
                }
            }
            __HAL_DMA_DISABLE(&hdma_dcmi);

            p = (rt_uint8_t *)JPEG_DATA_BUF;
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

                fd = open(argv[1], O_WRONLY | O_CREAT);
                if (fd < 0)
                {
                    rt_kprintf("open file for recording failed!\n");
                    return -RT_ERROR;
                }
                else
                {
                    write(fd, p, jpg_len);
                    close(fd);
                    rt_kprintf("picture capture complate!\n");

                    break;
                }
            }

            jpeg_data_ok = 2;
        }
    }

    return RT_EOK;
}
MSH_CMD_EXPORT(camera_sample, record picture to a jpg file);

#endif
