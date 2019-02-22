/*
 * File      : drv_touch_gt9xx.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2017, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-02-08     Zhangyihong  the first version
 * 2018-04-03     XY           gt9xx for 1024 * 600
 * 2018-10-11     sundm75      ls1c for  480 * 272
 */
#include "rtthread.h"

#include "drv_touch.h"
#include "string.h"
#include "ls1c_gpio.h"
#include "ls1c.h"
#include "ls1c_pin.h"

#ifdef TINA_USING_TOUCH

#define TP_INT_PIN          (89)
#define TP_RESET_PIN        (87)
#define LED_PIN        		(52)


#define gt9xx_READ_XY_REG 			0x814E    	/* 坐标寄存器 当前检测到的触摸情况 */
#define gt9xx_CLEARBUF_REG 			0x814E   	/* 清除坐标寄存器 */
#define gt9xx_CONFIG_REG    		0x8047  	/* 配置参数寄存器 */
#define gt9xx_COMMAND_REG 			0x8040 		/* 实时命令 */
#define gt9xx_PRODUCT_ID_REG 		0x8140 		/* productid */
#define gt9xx_VENDOR_ID_REG 		0x814A 		/* 当前模组选项信息 */
#define gt9xx_CONFIG_VERSION_REG 	0x8047 		/* 配置文件版本号 */
#define gt9xx_CONFIG_CHECKSUM_REG 	0x80FF 		/* 配置文件校验码 */
#define gt9xx_FIRMWARE_VERSION_REG 	0x8144 		/* 固件版本号 */

#define IIC_RETRY_NUM 1

void touch_down(void);
void touch_mo(void);
void touch_up(void);

static struct rt_i2c_bus_device *gt9xx_i2c_bus;
static void gt9xx_isr_enable(rt_bool_t enable);
static rt_err_t gt9xx_read_point(touch_msg_t msg);
static void gt9xx_init(struct rt_i2c_bus_device *i2c_bus);
static void gt9xx_deinit(void);
static int gt9xx_read_xy(void);

static gpio_direction_output( int pin, int level)
{
    gpio_init(pin, gpio_mode_output);
    gpio_set(pin, level);
}
static gpio_direction_input(int pin)
{
    gpio_init(pin, gpio_mode_input);
}
static gpio_irq_enable( int pin)
{
    int touch_irq = LS1C_GPIO_TO_IRQ(TP_INT_PIN); 
    rt_hw_interrupt_umask(touch_irq); 
}
static gpio_irq_disable(int pin)
{
    int touch_irq = LS1C_GPIO_TO_IRQ(TP_INT_PIN);
    rt_hw_interrupt_mask(touch_irq); 
}
static gpio_set_value(int pin, int level)
{
    gpio_set(pin, level); 
}
struct touch_ops gt9xx_ops =
{
    gt9xx_isr_enable,
    gt9xx_read_point,
    gt9xx_init,
    gt9xx_deinit,
};

static struct touch_drivers gt9xx_driver;
extern struct lcd_config lcd_config;

static rt_uint8_t gt9xx_config[186];

static int gt9xx_read(struct rt_i2c_bus_device *i2c_bus, rt_uint16_t addr, rt_uint8_t *buffer, rt_size_t length)
{
    int ret = -1;
    int retries = 0;
    rt_uint8_t tmp_buf[2];

    struct rt_i2c_msg msgs[] =
    {
        {
            .addr   = gt9xx_driver.address,
            .flags  = RT_I2C_WR,
            .len    = 2,
            .buf    = tmp_buf,
        },
        {
            .addr   = gt9xx_driver.address,
            .flags  = RT_I2C_RD,
            .len    = length,
            .buf    = buffer,
        },
    };

    tmp_buf[0] = (rt_uint8_t)(addr >> 8);
    tmp_buf[1] = (rt_uint8_t)(addr);

    while (retries < IIC_RETRY_NUM)
    {
        ret = rt_i2c_transfer(i2c_bus, msgs, 2);
        ret = rt_i2c_transfer(i2c_bus, msgs, 2);
        ret = rt_i2c_transfer(i2c_bus, msgs, 2);
        ret = rt_i2c_transfer(i2c_bus, msgs, 2);
        if (ret == 2)break;
        retries++;
    }

    if (retries >= IIC_RETRY_NUM)
    {
        rt_kprintf("%s i2c read error: %d\n", __func__, ret);
        return -1;
    }

    return ret;
}

static void gt9xx_write(struct rt_i2c_bus_device *i2c_bus, rt_uint16_t addr, rt_uint8_t *buffer, rt_size_t length)
{

    rt_uint8_t *send_buffer = rt_malloc(length + 2);

    RT_ASSERT(send_buffer);

    send_buffer[0] = (rt_uint8_t)(addr >> 8);
    send_buffer[1] = (rt_uint8_t)(addr);
    memcpy(send_buffer + 2, buffer, length);

    struct rt_i2c_msg msgs[] =
    {
        {
            .addr   = gt9xx_driver.address,
            .flags  = RT_I2C_WR,
            .len    = length + 2,
            .buf    = send_buffer,
        }
    };

    length = rt_i2c_transfer(i2c_bus, msgs, 1);
    rt_free(send_buffer);
    send_buffer = RT_NULL;
}

static void gt9xx_isr_enable(rt_bool_t enable)
{
    if (enable)
    {
        gpio_irq_enable( TP_INT_PIN);
    }
    else
    {
        gpio_irq_disable( TP_INT_PIN);
    }
}

static rt_err_t gt9xx_read_point(touch_msg_t msg)
{
    rt_uint8_t buf[8];
    rt_uint8_t clean = 0;
    static rt_uint8_t s_tp_down = 0;

    gt9xx_read(gt9xx_i2c_bus, gt9xx_READ_XY_REG, buf, 8);
    gt9xx_write(gt9xx_i2c_bus, gt9xx_CLEARBUF_REG, &clean, 1);
    if ((buf[0] & 0x80) == 0)
    {
        if (s_tp_down)
        {
            s_tp_down = 0;
            msg->event = TOUCH_EVENT_UP;
            return RT_EOK;
        }
        msg->event = TOUCH_EVENT_NONE;
        return RT_EOK;
    }
    msg->x = ((rt_uint16_t)buf[3] << 8) | buf[2];
    msg->y = ((rt_uint16_t)buf[5] << 8) | buf[4];
    if (s_tp_down)
    {
        msg->event = TOUCH_EVENT_MOVE;
        return RT_EOK;
    }
    msg->event = TOUCH_EVENT_DOWN;
    s_tp_down = 1;

    return RT_EOK;
}

void gt9xx_touch_isr(int irq, void *param)  
{
    gpio_irq_disable(TP_INT_PIN);
    rt_sem_release(gt9xx_driver.isr_sem);
}

static void gt9xx_set_address(rt_uint8_t address)
{
    pin_set_purpose(TP_INT_PIN, PIN_PURPOSE_OTHER);
    pin_set_purpose(TP_RESET_PIN, PIN_PURPOSE_OTHER);
    gpio_direction_output( TP_INT_PIN, 0);
    gpio_direction_output( TP_RESET_PIN, 0);
    if (address == 0x5D)
    {
        rt_thread_delay(30);
        gpio_set_value( TP_RESET_PIN, 1);
        rt_thread_delay(300);
        pin_set_purpose(TP_INT_PIN, PIN_PURPOSE_OTHER);
        gpio_direction_input(TP_INT_PIN);
        rt_thread_delay(10);
    }
    else
    {
        gpio_set_value( TP_INT_PIN, 1);
        gpio_set_value( TP_RESET_PIN, 0);
        rt_thread_delay(30);
        gpio_set_value( TP_RESET_PIN, 1);
        gpio_set_value( TP_INT_PIN, 1);
        rt_thread_delay(30);
        gpio_set_value( TP_INT_PIN, 0);
        rt_thread_delay(30);
        gpio_set_value( TP_INT_PIN, 1);    
    }
}

static void gt9xx_soft_reset(struct rt_i2c_bus_device *i2c_bus)
{
    rt_uint8_t buf = 2;
    gt9xx_write(i2c_bus, gt9xx_COMMAND_REG, &buf, 1);
}

static void gt9xx_init(struct rt_i2c_bus_device *i2c_bus)
{
    rt_uint8_t id = 0;
    int touch_irq = LS1C_GPIO_TO_IRQ(TP_INT_PIN); 
    
    gt9xx_driver.isr_sem = rt_sem_create("gt9xx", 0, RT_IPC_FLAG_FIFO);
    RT_ASSERT(gt9xx_driver.isr_sem);
    
    gt9xx_i2c_bus = i2c_bus;
    gt9xx_set_address(gt9xx_driver.address);
    
    gt9xx_read(i2c_bus, gt9xx_CONFIG_VERSION_REG, &id, 1);
    rt_kprintf("\r\nGT9xx Config version:0x%02X\r\n", id);
    
    gt9xx_read(i2c_bus, gt9xx_VENDOR_ID_REG, &id, 1);
    rt_kprintf("\r\nGT9xx sensor id:0x%02X\r\n", id);
    
    gpio_set_irq_type( TP_INT_PIN, IRQ_TYPE_EDGE_RISING);	
    gpio_irq_disable( TP_INT_PIN);

    rt_hw_interrupt_install(touch_irq, gt9xx_touch_isr, RT_NULL, "touch");  
    
    rt_thread_delay(RT_TICK_PER_SECOND / 5);
    gpio_init(LED_PIN, gpio_mode_output);
}

static int gt9xx_write_config(void)
{
    int i;
    rt_uint8_t config_checksum = 0;
    gt9xx_set_address(gt9xx_driver.address);
    //Add sth...
    gt9xx_config[5] = 0x05;
    gt9xx_config[6] = 0x0C;
    for (i = 0; i < sizeof(gt9xx_config) - 2; i++)
    {
        config_checksum += gt9xx_config[i];
    }
    gt9xx_config[184] = (~config_checksum) + 1;
    gt9xx_config[185] = 0x01;
    gt9xx_write(gt9xx_i2c_bus, gt9xx_CONFIG_REG, gt9xx_config, sizeof(gt9xx_config));
    return 0;
}
MSH_CMD_EXPORT(gt9xx_write_config,please read first);

static int gt9xx_read_config(void)
{
    int i;
    rt_uint8_t buf[8];
    rt_uint8_t clean = 0;
    gt9xx_read(gt9xx_i2c_bus, gt9xx_CONFIG_VERSION_REG, gt9xx_config, sizeof(gt9xx_config));
    gt9xx_config[sizeof(gt9xx_config)-1] = 1;
    
    rt_kprintf("\n");
    for(i = 0; i < sizeof(gt9xx_config); i++)
    {
        rt_kprintf("0x%02X,",gt9xx_config[i]);
        if((i+1)%8 == 0)
        {
            rt_kprintf("\n");
        }
    }
    rt_kprintf("\n");
    return 0;
}
MSH_CMD_EXPORT(gt9xx_read_config,read gt9xx config);
static int gt9xx_read_xy(void)
{
    int i;
    rt_uint8_t buf[8];
    rt_uint8_t clean = 0;
    rt_uint16_t x,y;
    
    gt9xx_read(gt9xx_i2c_bus, gt9xx_READ_XY_REG, buf, 8);
    gt9xx_write(gt9xx_i2c_bus, gt9xx_CLEARBUF_REG, &clean, 1);
    x = ((rt_uint16_t)buf[3] << 8) | buf[2];
    y = ((rt_uint16_t)buf[5] << 8) | buf[4];
    rt_kprintf("\n814e= 0x%02x; 814f= 0x%02x;\n x1 : %d, y1 : %d\n", buf[0], buf[1], x, y);	

    rt_kprintf("\n");
    return 0;
}
MSH_CMD_EXPORT(gt9xx_read_xy,read gt9xx xy);

static rt_bool_t gt9xx_probe(struct rt_i2c_bus_device *i2c_bus)
{
    rt_uint8_t buffer[5] = { 0 };

    gt9xx_set_address(gt9xx_driver.address);
    gt9xx_soft_reset(i2c_bus);
	rt_thread_delay(10);
    gt9xx_read(i2c_bus, gt9xx_PRODUCT_ID_REG, buffer, 4);
    buffer[4] = '\0';
    if (buffer[0] == '9' && buffer[1] == '1' && buffer[2] == '1')
    {
        rt_kprintf("Found chip gt911\r\n");
        return RT_TRUE;
    }
    else if (buffer[0] == '9' && buffer[1] == '1' && buffer[2] == '4' && buffer[3] == '7')
    {
        rt_kprintf("Found chip gt9147\r\n");
        return RT_TRUE;
    }
    else if (buffer[0] == '9' && buffer[1] == '1' && buffer[2] == '5' && buffer[3] == '7')
    {
        rt_kprintf("Found chip gt9157\r\n");
        return RT_TRUE;
    }
    else
    {
        rt_kprintf("Uknow chip :");
	    rt_kprintf("%d%d%d%d\r\n",buffer[0], buffer[1] , buffer[2], buffer[3]);
		return RT_TRUE;
    }
    return RT_FALSE;
}

static void gt9xx_deinit(void)
{
    rt_sem_delete(gt9xx_driver.isr_sem);
}

static int gt9xx_driver_register(void)
{
    rt_kprintf("\r\n%s \r\n", __FUNCTION__);
    gt9xx_driver.address = 0x5D;
    gt9xx_driver.probe = gt9xx_probe;
    gt9xx_driver.ops = &gt9xx_ops;
    gt9xx_driver.user_data = RT_NULL;
    rt_touch_drivers_register(&gt9xx_driver);
    return 0;
}
INIT_ENV_EXPORT(gt9xx_driver_register);

void touch_down(void)
{
    gpio_set(LED_PIN, gpio_level_low);
}

void touch_mo(void)
{
    if (0 == (gpio_get(LED_PIN)))
        gpio_set(LED_PIN, gpio_level_high); 
    else
        gpio_set(LED_PIN, gpio_level_low); 
}

void touch_up(void)
{
    gpio_set(LED_PIN, gpio_level_high); 
}


#endif
