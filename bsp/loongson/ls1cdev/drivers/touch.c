/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-12-30    Sundm75       first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <stdbool.h>
#include <drivers/spi.h>
#include "ls1c.h"
#include "ls1c_gpio.h"
#include "ls1c_spi.h"
#include "drv_spi.h"
#include "touch.h"

#ifdef XPT2046_USING_TOUCH

#include <rtgui/calibration.h>
#include <rtgui/event.h>
#include <rtgui/kbddef.h>
#include <rtgui/rtgui_server.h>
#include <rtgui/rtgui_system.h>


//竖屏幕 不需要  _ILI_HORIZONTAL_DIRECTION_
//横屏幕 需要  _ILI_HORIZONTAL_DIRECTION_

//#define _ILI_HORIZONTAL_DIRECTION_

#if defined(_ILI_HORIZONTAL_DIRECTION_)
#define X_WIDTH 272
#define Y_WIDTH 480
#else
#define X_WIDTH 480
#define Y_WIDTH 272
#endif
/*
TOUCH INT: 84
*/
#define IS_TOUCH_UP()     gpio_get(TOUCH_INT_PIN)

#define led_gpio 52    // led1指示

#define DUMMY                 0x00

/*
7  6 - 4  3      2     1-0
s  A2-A0 MODE SER/DFR PD1-PD0
*/
/* bit[1:0] power-down */
#define POWER_MODE0     (0) /* Power-Down Between Conversions. When */
                            /* each conversion is finished, the converter */
                            /* enters a low-power mode. At the start of the */
                            /* next conversion, the device instantly powers up */
                            /* to full power. There is no need for additional */
                            /* delays to ensure full operation, and the very first */
                            /* conversion is valid. The Y? switch is on when in */
                            /* power-down.*/
#define POWER_MODE1     (1) /* Reference is off and ADC is on. */
#define POWER_MODE2     (2) /* Reference is on and ADC is off. */
#define POWER_MODE3     (3) /* Device is always powered. Reference is on and */
                            /* ADC is on. */
/* bit[2] SER/DFR */
#define DIFFERENTIAL    (0<<2)
#define SINGLE_ENDED    (1<<2)
/* bit[3] mode */
#define MODE_12BIT      (0<<3)
#define MODE_8BIT       (1<<3)
/* bit[6:4] differential mode */
#define MEASURE_X       (((1<<2) | (0<<1) | (1<<0))<<4)
#define MEASURE_Y       (((0<<2) | (0<<1) | (1<<0))<<4)
#define MEASURE_Z1      (((0<<2) | (1<<1) | (1<<0))<<4)
#define MEASURE_Z2      (((1<<2) | (0<<1) | (0<<0))<<4)
/* bit[7] start */
#define START           (1<<7)

/* X Y change. */
#define TOUCH_MSR_X     (START | MEASURE_X | MODE_12BIT | DIFFERENTIAL | POWER_MODE0)
#define TOUCH_MSR_Y     (START | MEASURE_Y | MODE_12BIT | DIFFERENTIAL | POWER_MODE0)


/* 以下定义XPT2046 的触摸屏位置*/
#if defined(_ILI_HORIZONTAL_DIRECTION_)
#define MIN_X_DEFAULT   2047
#define MAX_X_DEFAULT   47
#define MIN_Y_DEFAULT   102
#define MAX_Y_DEFAULT   1939
#else
#define MIN_X_DEFAULT   47
#define MAX_X_DEFAULT   2047
#define MIN_Y_DEFAULT   1939
#define MAX_Y_DEFAULT   102
#endif



#define SAMP_CNT 8                              //the adc array size
#define SAMP_CNT_DIV2 4                         //the middle of the adc array
#define SH   10                                 // Valve value


/*宏定义 */
#define TOUCH_SPI_X                 SPI1
#define TOUCH_INT_PIN               84
#define TOUCH_CS_PIN                49
#define TOUCH_SCK_PIN               46
#define TOUCH_MISO_PIN              47
#define TOUCH_MOSI_PIN              48


/*创建结构体将需要用到的东西进行打包*/
struct rtgui_touch_device
{
    struct rt_device parent;                    /* 用于注册设备*/

    rt_uint16_t x, y;                           /* 记录读取到的位置值  */

    rt_bool_t calibrating;                      /* 触摸校准标志 */
    rt_touch_calibration_func_t calibration_func;/* 触摸函数 函数指针 */

    rt_uint16_t min_x, max_x;                   /* 校准后 X 方向最小 最大值 */
    rt_uint16_t min_y, max_y;                   /* 校准后 Y 方向最小 最大值 */

    struct rt_spi_device * spi_device;          /* SPI 设备 用于通信 */
    struct rt_event event;                       /* 事件同步，用于“笔中断” */
};
static struct rtgui_touch_device *touch = RT_NULL;

static rt_err_t  touch_send_then_recv(struct rt_spi_device *device,
                               const void           *send_buf,
                               rt_size_t             send_length,
                               void                 *recv_buf,
                               rt_size_t             recv_length)
{
    rt_err_t result;
    struct rt_spi_message message;
    rt_uint8_t dummy[128] ;

    rt_memset(dummy, DUMMY, sizeof(dummy));

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);

    result = rt_mutex_take(&(device->bus->lock), RT_WAITING_FOREVER);
    if (result == RT_EOK)
    {
        if (device->bus->owner != device)
        {
            /* not the same owner as current, re-configure SPI bus */
            result = device->bus->ops->configure(device, &device->config);
            if (result == RT_EOK)
            {
                /* set SPI bus owner */
                device->bus->owner = device;
            }
            else
            {
                /* configure SPI bus failed */
                result = -RT_EIO;
                goto __exit;
            }
        }

        /* send data */
        message.send_buf   = send_buf;
        message.recv_buf   = RT_NULL;
        message.length     = send_length;
        message.cs_take    = 1;
        message.cs_release = 0;
        message.next       = RT_NULL;

        result = device->bus->ops->xfer(device, &message);
        if (result == 0)
        {
            result = -RT_EIO;
            goto __exit;
        }

        /* recv data */
        message.send_buf   = dummy;
        message.recv_buf   = recv_buf;
        message.length     = recv_length;
        message.cs_take    = 0;
        message.cs_release = 1;
        message.next       = RT_NULL;

        result = device->bus->ops->xfer(device, &message);
        if (result == 0)
        {
            result = -RT_EIO;
            goto __exit;
        }

        result = RT_EOK;
    }
    else
    {
        return -RT_EIO;
    }

__exit:
    rt_mutex_release(&(device->bus->lock));

    return result;
}


static void rtgui_touch_calculate(void)
{
    if (touch != RT_NULL)
    {
        /* read touch */
        {
            rt_uint8_t i, j, k, min;
            rt_uint16_t temp;
            rt_uint16_t tmpxy[2][SAMP_CNT];
            rt_uint8_t send_buffer[1];
            rt_uint8_t recv_buffer[2];
            for(i=0; i<SAMP_CNT; i++)
            {
                send_buffer[0] = TOUCH_MSR_X;
          touch_send_then_recv(touch->spi_device, send_buffer, 1, recv_buffer, 2);
                rt_kprintf("touch x: %d ",(recv_buffer[0]*256|recv_buffer[1])>>4);
#if defined(_ILI_HORIZONTAL_DIRECTION_)
                tmpxy[1][i]  = (recv_buffer[0]<<8)|recv_buffer[1] ;
                tmpxy[1][i] >>= 4;
#else
                tmpxy[0][i]  = (recv_buffer[0]<<8)|recv_buffer[1] ;
                tmpxy[0][i] >>=4;

#endif
                send_buffer[0] = TOUCH_MSR_Y;
                touch_send_then_recv(touch->spi_device, send_buffer, 1, recv_buffer, 2);
          rt_kprintf("touch y: %d \n",(recv_buffer[0]*256|recv_buffer[1])>>4);

#if defined(_ILI_HORIZONTAL_DIRECTION_)
                tmpxy[0][i]  = (recv_buffer[0]<<8)|recv_buffer[1] ;
                tmpxy[0][i] >>= 4;
#else
                tmpxy[1][i]  = (recv_buffer[0]<<8)|recv_buffer[1] ;
                tmpxy[1][i] >>= 4;
#endif
            }
            /*再次打开触摸中断*/
            send_buffer[0] = 1 << 7;
          touch_send_then_recv(touch->spi_device, send_buffer, 1, recv_buffer, 2);
                touch_send_then_recv(touch->spi_device, send_buffer, 1, recv_buffer, 2);
            /* calculate average */
            {
                rt_uint32_t total_x = 0;
                rt_uint32_t total_y = 0;
                for(k=0; k<2; k++)
                {
                    // sorting the ADC value
                    for(i=0; i<SAMP_CNT-1; i++)
                    {
                        min=i;
                        for (j=i+1; j<SAMP_CNT; j++)
                        {
                            if (tmpxy[k][min] > tmpxy[k][j])
                                min=j;
                        }
                        temp = tmpxy[k][i];
                        tmpxy[k][i] = tmpxy[k][min];
                        tmpxy[k][min] = temp;
                    }
                    //check value for Valve value
                    if((tmpxy[k][SAMP_CNT_DIV2+1]-tmpxy[k][SAMP_CNT_DIV2-2]) > SH)
                    {
                        return;
                    }
                }
                total_x=tmpxy[0][SAMP_CNT_DIV2-2]+tmpxy[0][SAMP_CNT_DIV2-1]+tmpxy[0][SAMP_CNT_DIV2]+tmpxy[0][SAMP_CNT_DIV2+1];
                total_y=tmpxy[1][SAMP_CNT_DIV2-2]+tmpxy[1][SAMP_CNT_DIV2-1]+tmpxy[1][SAMP_CNT_DIV2]+tmpxy[1][SAMP_CNT_DIV2+1];
                //calculate average value
                touch->x=total_x>>2;
                touch->y=total_y>>2;
                rt_kprintf("touch->x:%d touch->y:%d\r\n", touch->x, touch->y);
           } /* calculate average */
        } /* read touch */

        /* if it's not in calibration status  */
        /*触摸值缩放*/
        if (touch->calibrating != RT_TRUE)
        {
            if (touch->max_x > touch->min_x)
            {
                touch->x = (touch->x - touch->min_x) * X_WIDTH/(touch->max_x - touch->min_x);
            }
            else
            {
                touch->x = (touch->min_x - touch->x) * X_WIDTH/(touch->min_x - touch->max_x);
            }

            if (touch->max_y > touch->min_y)
            {
                touch->y = (touch->y - touch->min_y) * Y_WIDTH /(touch->max_y - touch->min_y);
            }
            else
            {
                touch->y = (touch->min_y - touch->y) * Y_WIDTH /(touch->min_y - touch->max_y);
            }
        }
    }
}
#include "ls1c_regs.h"
#define TOUCH_INT_EN                __REG32(LS1C_INT4_EN)
rt_inline void touch_int_cmd(rt_bool_t NewState)
{
    if(NewState == RT_TRUE)
        {
            //TOUCH_INT_EN |= (1<<(TOUCH_INT_PIN-64));
            reg_set_one_bit(LS1C_INT4_EN, 1<<(TOUCH_INT_PIN-64));
        }
    else
        {
            //TOUCH_INT_EN &=(~ (1<<(TOUCH_INT_PIN-64)));
            reg_clr_one_bit(LS1C_INT4_EN, 1<<(TOUCH_INT_PIN-64));
        }

}

void ls1c_touch_irqhandler(void) /* TouchScreen */
{
  if(gpio_get(TOUCH_INT_PIN)==0)
  {
    /* 触摸屏按下后操作 */
    if (gpio_level_low == gpio_get(led_gpio))
        gpio_set(led_gpio, gpio_level_high);
    else
        gpio_set(led_gpio, gpio_level_low);
    touch_int_cmd(RT_FALSE);
    rt_event_send(&touch->event, 1);
  }
}

/*管脚初始化，配置中断打开SPI1 CS0 设备*/
rt_inline void touch_init(void)
{
    unsigned int touch_int_gpio = TOUCH_INT_PIN;     // 触摸屏中断
    int touch_irq = LS1C_GPIO_TO_IRQ(touch_int_gpio);

    // 初始化按键中断
    gpio_set_irq_type(touch_int_gpio, IRQ_TYPE_EDGE_FALLING);
    rt_hw_interrupt_install(touch_irq, ls1c_touch_irqhandler, RT_NULL, "touch");
    rt_hw_interrupt_umask(touch_irq);
    gpio_init(touch_int_gpio, gpio_mode_input);

    // 初始化led
    gpio_init(led_gpio, gpio_mode_output);
    gpio_set(led_gpio, gpio_level_high);
}


/* RT-Thread Device Interface */
static rt_err_t rtgui_touch_init (rt_device_t dev)
{
    rt_uint8_t send;
    rt_uint8_t recv_buffer[2];
    struct rtgui_touch_device * touch_device = (struct rtgui_touch_device *)dev;

    touch_init();
    rt_kprintf("touch_init ...\n");
    send = START | DIFFERENTIAL | POWER_MODE0;
    touch_send_then_recv(touch->spi_device, &send, 1, recv_buffer, 2);

    return RT_EOK;
}

static rt_err_t rtgui_touch_control (rt_device_t dev, int cmd, void *args)
{
    switch (cmd)
    {
    case RT_TOUCH_CALIBRATION:
        touch->calibrating = RT_TRUE;
        touch->calibration_func = (rt_touch_calibration_func_t)args;
        break;

    case RT_TOUCH_NORMAL:
        touch->calibrating = RT_FALSE;
        break;

    case RT_TOUCH_CALIBRATION_DATA:
    {
        struct calibration_data* data;
        data = (struct calibration_data*) args;

        //update
        touch->min_x = data->min_x;
        touch->max_x = data->max_x;
        touch->min_y = data->min_y;
        touch->max_y = data->max_y;
    }
    break;
    }

    return RT_EOK;
}

void _set_mouse_position(rt_uint32_t X, rt_uint32_t Y)
{}
static void touch_thread_entry(void *parameter)
{
    rt_bool_t touch_down = RT_FALSE;
    rt_uint32_t event_value;
    struct rtgui_event_mouse emouse;
    static struct _touch_previous
    {
        rt_uint32_t x;
        rt_uint32_t y;
    } touch_previous;

    RTGUI_EVENT_MOUSE_BUTTON_INIT(&emouse);
    emouse.wid = RT_NULL;

    while(1)
    {
        /* 接收到触摸中断事件 */
        if(rt_event_recv(&touch->event,
                         1,
                         RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
                         100,
                         &event_value)
                == RT_EOK)
        {
            while(1)
            {
                if (IS_TOUCH_UP())
                {
                    /* 触摸笔抬起 */
                    /* touch up */
                    emouse.button = (RTGUI_MOUSE_BUTTON_LEFT |RTGUI_MOUSE_BUTTON_UP);

                    /* use old value */
                    emouse.x = touch->x;
                    emouse.y = touch->y;

                    if(touch_down != RT_TRUE)
                    {
                        touch_int_cmd(RT_TRUE);
                        break;
                    }

                    if ((touch->calibrating == RT_TRUE) && (touch->calibration_func != RT_NULL))
                    {
                        /* 触摸校准处理 */
                        /* callback function */
                        touch->calibration_func(emouse.x, emouse.y);

                    }
                    else
                    {
                        /* 向ui发送触摸坐标 */
                        rtgui_server_post_event(&emouse.parent, sizeof(struct rtgui_event_mouse));
                    }
                    rt_kprintf("touch up: (%d, %d)\n", emouse.x, emouse.y);

                    /* clean */
                    touch_previous.x = touch_previous.y = 0;
                    touch_down = RT_FALSE;

                    touch_int_cmd(RT_TRUE);
                    break;
                } /* touch up */
                else /* touch down or move */
                {
                    if(touch_down == RT_FALSE)
                    {
                        rt_thread_delay(RT_TICK_PER_SECOND / 10);
                    }
                    else
                    {
                        rt_thread_delay(5);
                    }

                    if(IS_TOUCH_UP()) continue;

                    /* calculation */
                    rtgui_touch_calculate();

                    /* send mouse event */
                    emouse.parent.type = RTGUI_EVENT_MOUSE_BUTTON;
                    emouse.parent.sender = RT_NULL;

                    emouse.x = touch->x;
                    emouse.y = touch->y;
                    _set_mouse_position(emouse.x, emouse.y);
                    /* 光标跟随 */
                    /* init mouse button */
                    emouse.button = (RTGUI_MOUSE_BUTTON_LEFT |RTGUI_MOUSE_BUTTON_DOWN);

                    /* send event to server */
                    if (touch->calibrating != RT_TRUE)
                    {
#define previous_keep      8
                        /* filter. */
                        if((touch_previous.x > touch->x + previous_keep)
                            || (touch_previous.x < touch->x - previous_keep)
                            || (touch_previous.y > touch->y + previous_keep)
                            || (touch_previous.y < touch->y - previous_keep))
                        {
                            touch_previous.x = touch->x;
                            touch_previous.y = touch->y;
                            /* 向ui发送触摸坐标 */
                            rtgui_server_post_event(&emouse.parent, sizeof(struct rtgui_event_mouse));
                            if(touch_down == RT_FALSE)
                            {
                                touch_down = RT_TRUE;
                                rt_kprintf("touch down: (%d, %d)\n", emouse.x, emouse.y);
                            }
                            else
                            {
                                rt_kprintf("touch motion: (%d, %d)\n", emouse.x, emouse.y);
                            }
                        }
                    }
                    else
                    {
                        touch_down = RT_TRUE;
                    }
                } /* touch down or move */
            } /* read touch */
        } /* event recv */
    } /* thread while(1) */
}


rt_err_t rtgui_touch_hw_init(const char * spi_device_name)
{
         rt_uint32_t arg[2];
    struct rt_device * spi_device;
        struct rt_thread * touch_thread;
    rt_err_t err;

    rt_kprintf("spi1 cs0 start...\n");
    spi_device = rt_device_find("spi10");
    if(spi_device ==  RT_NULL)
    {
        rt_kprintf("Did not find spi1, exit thread....\n");
        return;
    }
    err = rt_device_open(spi_device, RT_DEVICE_OFLAG_RDWR);
    if(err != RT_EOK)
    {
        rt_kprintf("Open spi1 failed %08X, exit thread....\n", err);
        return;
    }

      /* config spi */
      {
          struct rt_spi_configuration cfg;
          cfg.data_width = 8;
          cfg.mode = RT_SPI_MODE_0;
       cfg.max_hz  = 200 * 1000; /* 200K */
        rt_spi_configure((struct rt_spi_device *)spi_device, &cfg);
      }

    touch = (struct rtgui_touch_device*)rt_malloc (sizeof(struct rtgui_touch_device));
    if (touch == RT_NULL) return -RT_ENOMEM; /* no memory yet */

    /* clear device structure */
    rt_memset(&(touch->parent), 0, sizeof(struct rt_device));

    rt_event_init(&touch->event, "touch", RT_IPC_FLAG_FIFO);

    touch->spi_device = (struct rt_spi_device *)spi_device;
    touch->calibrating = false;

    touch->min_x = MIN_X_DEFAULT;
    touch->max_x = MAX_X_DEFAULT;
    touch->min_y = MIN_Y_DEFAULT;
    touch->max_y = MAX_Y_DEFAULT;

    /* init device structure */
    touch->parent.type = RT_Device_Class_Miscellaneous;
    touch->parent.init = rtgui_touch_init;
    touch->parent.control = rtgui_touch_control;
    touch->parent.user_data = RT_NULL;

    /* register touch device to RT-Thread */
    rt_device_register(&(touch->parent), "touch", RT_DEVICE_FLAG_RDWR);


    touch_thread = rt_thread_create("touch_thread",
                                    touch_thread_entry, RT_NULL,
                                    4096, RTGUI_SVR_THREAD_PRIORITY-1, 1);
    if (touch_thread != RT_NULL) rt_thread_startup(touch_thread);

     rt_device_init((rt_device_t)touch);
   return RT_EOK;
}

#endif
