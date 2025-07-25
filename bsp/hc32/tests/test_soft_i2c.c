/*
 * Copyright (c) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-12-30     CDT          first version
 */

/*
 * 程序清单：这是 Soft I2C 设备使用例程。
 * 例程导出了 sw_i2c_sample 到控制终端。
 * 命令调用格式：sw_i2c_sample cmd_id [options]
 * 命令解释：命令第二个参数是要使用的Soft I2C设备的命令，为空则打印命令使用说明
 * 程序功能：查找Soft I2C设备，读写I2C设备寄存器。
 * 注意：测试要用逻辑分析仪或示波器抓取信号
*/

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include "rtconfig.h"
#include "rtdef.h"

#if defined(RT_USING_I2C)

#if defined(BSP_USING_I2C1_SW)

/* using i2c1 control oled12864 */
#define SW_I2C_NAME         "i2c1_sw"
#define SSD1306_ADDR        (0x78U >> 1)
#define SSD1306_MD_CMD      (0x00U)
#define SSD1306_MD_DATA     (0x40U)

/* symbol parameters: width pixles, lenght pixels */
#define SYM_W_PIX           (8U)
#define SYM_H_PIX           (8U)
/* ssd ohysical parameters */
#define SSD_PAGE_SIZE       (8U)
#define SSD_COL_SIZE        (128U)
/* each page 8 pix */
#define PAGE_PIX_SIZE       (8U)

/* each byte set horizontal 1 pix */
#define SYM_W_BYTE          (SYM_W_PIX / 1)
/* each byte set vertical 8 pix */
#define SYM_H_BYTE          (SYM_H_PIX / 8)
/* each character occupis */
#define SYM_BYTE_SIZE       (SYM_W_BYTE * SYM_H_BYTE)

/* soft i2c command defines */
enum SW_I2C_CMD
{
    SW_I2C_INIT = 0x01,
    SSD1306_CMD_INIT,
    SSD1306_CMD_DISPLAY,
    SSD1306_CMD_DEINIT,
};

/* local variables */
struct rt_i2c_msg msg;
rt_uint8_t ssd_init_array[30];
rt_uint8_t logo_array[5][SYM_BYTE_SIZE];

/* local functions */
static void ssd1306_init(struct rt_i2c_bus_device *i2c_dev);
static void ssd1306_roll_display(struct rt_i2c_bus_device *i2c_dev);
static void ssd1306_deinit(struct rt_i2c_bus_device *i2c_dev);

/* write_reg ssd1306 basic opertion */
static void ssd1306_write_single_reg(struct rt_i2c_bus_device *i2c_dev,
                                     rt_bool_t is_write_cmd, rt_uint8_t data)
{
    rt_uint8_t buff[2];
    struct rt_i2c_msg msgs;

    msgs.addr = SSD1306_ADDR;
    msgs.flags = RT_I2C_WR;

    if (RT_TRUE == is_write_cmd)
    {
        buff[0] = SSD1306_MD_CMD;
    }
    else
    {
        buff[0] = SSD1306_MD_DATA;
    }

    buff[1] = data;
    msgs.buf = buff;
    msgs.len = 2;

    if (1 != rt_i2c_transfer(i2c_dev, &msgs, 1))
    {
        rt_kprintf("failed to send cmd\n");
    }
}

/* write_reg ssd1306 basic opertion */
static void ssd1306_write_mult_reg(struct rt_i2c_bus_device *i2c_dev,
                                   rt_bool_t is_write_cmd, rt_uint8_t len, rt_uint8_t *data
                                   /*rt_uint8_t data*/)
{
    rt_uint8_t *buff = NULL;
    struct rt_i2c_msg msgs;

    msgs.addr = SSD1306_ADDR;
    msgs.flags = RT_I2C_WR;
    buff = (rt_uint8_t *)rt_malloc((len + 1) * sizeof(rt_uint8_t));

    if (RT_TRUE == is_write_cmd)
    {
        buff[0] = SSD1306_MD_CMD;
    }
    else
    {
        buff[0] = SSD1306_MD_DATA;
    }
    rt_memcpy(buff + 1, data, len);
    msgs.buf = buff;
    msgs.len = len + 1;

    if (1 != rt_i2c_transfer(i2c_dev, &msgs, 1))
    {
        rt_kprintf("failed to send cmd\n");
    }
    rt_free(buff);
    buff = NULL;
}

static int sw_i2c_sample(int argc, char *argv[])
{
    static struct rt_i2c_bus_device *rt_i2c_dev;
    /* print soft i2c usage */
    if (argc <= 1)
    {
        rt_kprintf("soft i2c usage as following:\n");
        rt_kprintf("sw_i2c_sample %d: soft i2c init\n", SW_I2C_INIT);
        rt_kprintf("sw_i2c_sample %d: oled ssd1306 init\n", SSD1306_CMD_INIT);
        rt_kprintf("sw_i2c_sample %d: write ssd1306 \n", SSD1306_CMD_DISPLAY);
        rt_kprintf("sw_i2c_sample %d: turn off ssd1306\n", SSD1306_CMD_DEINIT);
        return -RT_ERROR;
    }

    switch (*argv[1] - '0')
    {
    case SW_I2C_INIT:
        rt_i2c_dev = (struct rt_i2c_bus_device *)rt_device_find(SW_I2C_NAME);
        if (NULL == rt_i2c_dev)
        {
            rt_kprintf("failed to find i2c device %s\n", SW_I2C_NAME);
            return -RT_ERROR;
        }
        break;
    /* communicate with eeprom to soft i2c read function */
    case SSD1306_CMD_INIT:
        ssd1306_init(rt_i2c_dev);
        break;
    /* communicate with ssd1306 to soft i2c read function */
    case SSD1306_CMD_DISPLAY:
        ssd1306_roll_display(rt_i2c_dev);
        break;
    case SSD1306_CMD_DEINIT:
        ssd1306_deinit(rt_i2c_dev);
        break;
    default:
        rt_kprintf("unkwon command\n");
        break;
    }

    return RT_EOK;
}

/* ssd1306 de-init and turn off */
static void ssd1306_deinit(struct rt_i2c_bus_device *i2c_dev)
{
    rt_uint8_t ssd_deinit_array[] =
    {
        0X8D, /* set charge pump */
        0X10, /* turn off charge pump */
        0XAE, /* OLED sleep */
    };

    ssd1306_write_mult_reg(i2c_dev, RT_TRUE,
                           sizeof(ssd_deinit_array) / sizeof(ssd_deinit_array[0]),
                           ssd_deinit_array);
}

/* ssd oled initialize */
static void ssd1306_init(struct rt_i2c_bus_device *i2c_dev)
{
    ssd1306_write_mult_reg(i2c_dev, RT_TRUE,
                           sizeof(ssd_init_array) / sizeof(ssd_init_array[0]),
                           ssd_init_array);
}

/*
    Function:   write a heigh * width = 16 *16 --->pixel: 16 * 8character
    Input:      void
    Output:     void
    Data:       20210828
*/

void mOledWriteCharHnWm(struct rt_i2c_bus_device *i2c_dev,
                        uint8_t page, uint8_t col, uint8_t *ArrChar)
{
    if (ArrChar == NULL)
        return;
    rt_kprintf("x=%3d, y=%d\n", col, page);
    for (uint8_t page_idx = 0; page_idx < SYM_H_BYTE; page_idx++)
    {
        /* set start page: page0-page1 */
        ssd1306_write_single_reg(i2c_dev, RT_TRUE, 0xb0 + page + page_idx);
        /* lower 4-bit address of column start */
        ssd1306_write_single_reg(i2c_dev, RT_TRUE, 0x00 + ((col & 0x0F) >> 0));
        /* higher 4-bit address of column start */
        ssd1306_write_single_reg(i2c_dev, RT_TRUE, 0x10 + ((col & 0xF0) >> 4));
        /* send a character(total BYTE_CHAR byte) from array */
        ssd1306_write_mult_reg(i2c_dev, RT_FALSE, SYM_W_BYTE,
                               ArrChar + SYM_W_BYTE * page_idx);
    }
}

/* fill oled with character "XHSC" */
static void ssd1306_roll_display(struct rt_i2c_bus_device *i2c_dev)
{
    rt_uint8_t base_col, base_page;
    rt_uint8_t offset_page, offset_col;
    rt_uint16_t idx;
    /* using a write times related variable control position */
    static rt_uint16_t u16WriteTimes = 0;

    if (u16WriteTimes >= (SSD_COL_SIZE / SYM_W_PIX) * (SSD_PAGE_SIZE / (SYM_H_PIX / PAGE_PIX_SIZE)))
    {
        u16WriteTimes = 0;
    }
    /* each page write, eg. base_page = 7 / (128 / 8) = 0 */
    base_page = u16WriteTimes / (SSD_COL_SIZE / SYM_W_PIX);
    /* eg. base_col = (7 % (128 / 8)) * 8 = 56 */
    base_col = (u16WriteTimes % (SSD_COL_SIZE / SYM_W_PIX)) * SYM_W_PIX;
    offset_page = 0;
    offset_col = 0;
    /* each write cycle finish the data writing in array */
    for (idx = 0; idx < sizeof(logo_array) / sizeof(logo_array[0]); idx++)
    {
        offset_col = idx * SYM_W_PIX;
        if (base_col + offset_col >= SSD_COL_SIZE)
        {
            /*
                base_col + offset_col = [128, 256), page_offset = 1,
                base_col + offset_col = [256, 384), page_offset = 2,
                ...
            */
            offset_page = (base_col + offset_col) / SSD_COL_SIZE;
        }
        mOledWriteCharHnWm(i2c_dev, ((base_page + offset_page) * SYM_H_BYTE) % SSD_PAGE_SIZE, (base_col + offset_col) % SSD_COL_SIZE, *(logo_array + idx));
    }
    u16WriteTimes++;
}

rt_uint8_t ssd_init_array[] =
{
    0xAE, /* display off */
    0x20, /* Set Memory Addressing Mode */
    0x10, /* Set addressing orient */
    0xB0, /* Set Page Start Address for Page Addressing Mode,0-7 */
    0xC8, /* Set COM Output Scan Direction */
    0x00, /* set low column address */
    0x10, /* set high column address */
    0x40, /* set start line address */
    0x81, /* set contrast control register */
    0xFF, /* breightness 0x00~0xff */
    0xA1, /* set segment re-map 0 to 127 */
    0xA6, /* set normal display */
    0xA8, /* set multiplex ratio(1 to 64) */
    0x3F, /*      */
    0xC8, /*     */
    0xA4, /* 0xa4,Output follows RAM content;0xa5,Output ignores RAM content */
    0xD3, /* set display offset */
    0x00, /* not offset */
    0xD5, /* set display clock divide ratio/oscillator frequency */
    0xF0, /* set divide ratio */
    0xD9, /* set pre-charge period */
    0x22, /*  */
    0xDA, /* set com pins hardware configuration */
    0x12, /*  */
    0xDB, /* set vcomh */
    0x20, /* 0x20,0.77xVcc */
    0x8D, /* set DC-DC enable */
    0x14, /*  */
    0xAF, /* --turn on oled panel */
};


rt_uint8_t logo_array[][SYM_BYTE_SIZE] =
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x44, 0x44, 0x6C, 0x74, 0x54, 0x6C, 0x44, 0x44, /*"X"*/
    0x44, 0x7C, 0x54, 0x10, 0x10, 0x54, 0x7C, 0x44, /*"H"*/
    0x00, 0x68, 0x54, 0x54, 0x54, 0x54, 0x24, 0x00, /*"S"*/
    0x38, 0x6C, 0x44, 0x44, 0x44, 0x44, 0x24, 0x00, /*"C"*/
};

MSH_CMD_EXPORT(sw_i2c_sample, soft i2c sample);

#endif /* BSP_USING_I2C1_SW */

#endif/* RT_USING_I2C */
/*
EOF
*/
