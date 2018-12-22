/*
 * File      : focaltech_ts.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2017, RT-Thread Development Team
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
 * 2017-01-01     Urey      first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#include <board.h>
#include <drv_gpio.h>

#include <rtgui/event.h>
#include <rtgui/rtgui_server.h>

#include <string.h>

#ifdef RT_USING_FT6x06
#include "focaltech_ts.h"

#ifndef BIT
#define BIT(n)          (0x01u << (n))
#endif

static int fts_init_success = 0;

#define TP_DEBUG   0

#if TP_DEBUG
#define TP_DBG(...)     rt_kprintf("[TP]"),rt_kprintf(__VA_ARGS__)
#else
#define TP_DBG(...)
#endif

/*ic update info*/
static struct Upgrade_Info fts_updateinfo[] =
{
    {0x55,"FT5x06",TPD_MAX_POINTS_5,AUTO_CLB_NEED,50, 30, 0x79, 0x03, 10, 2000},
    {0x08,"FT5606",TPD_MAX_POINTS_5,AUTO_CLB_NEED,50, 10, 0x79, 0x06, 100, 2000},
    {0x0a,"FT5x16",TPD_MAX_POINTS_5,AUTO_CLB_NEED,50, 30, 0x79, 0x07, 10, 1500},
    {0x06,"FT6x06",TPD_MAX_POINTS_2,AUTO_CLB_NONEED,100, 30, 0x79, 0x08, 10, 2000},
    {0x36,"FT6x36",TPD_MAX_POINTS_2,AUTO_CLB_NONEED,10, 10, 0x79, 0x18, 10, 2000},
    {0x55,"FT5x06i",TPD_MAX_POINTS_5,AUTO_CLB_NEED,50, 30, 0x79, 0x03, 10, 2000},
    {0x14,"FT5336",TPD_MAX_POINTS_5,AUTO_CLB_NONEED,30, 30, 0x79, 0x11, 10, 2000},
    {0x13,"FT3316",TPD_MAX_POINTS_5,AUTO_CLB_NONEED,30, 30, 0x79, 0x11, 10, 2000},
    {0x12,"FT5436i",TPD_MAX_POINTS_5,AUTO_CLB_NONEED,30, 30, 0x79, 0x11, 10, 2000},
    {0x11,"FT5336i",TPD_MAX_POINTS_5,AUTO_CLB_NONEED,30, 30, 0x79, 0x11, 10, 2000},
    {0x54,"FT5x46",TPD_MAX_POINTS_5,AUTO_CLB_NONEED,2, 2, 0x54, 0x2c, 20, 2000},
    {0x58,"FT5x22",TPD_MAX_POINTS_5,AUTO_CLB_NONEED,2, 2, 0x58, 0x2c, 20, 2000},
    {0x59,"FT5x26",TPD_MAX_POINTS_5,AUTO_CLB_NONEED,30, 50, 0x79, 0x10, 1, 2000},
};

static struct Upgrade_Info fts_updateinfo_curr;
static int touch_down_up_status = 0;

#ifndef TOUCH_MAX_X
#  define TOUCH_MAX_X       480
#endif
#ifndef TOUCH_MAX_Y
#  define TOUCH_MAX_Y       320
#endif

#define ANDROID_INPUT_PROTOCOL_B
#define FTS_RESET_PIN_NAME                      "ft3417-rst"
#define FTS_INT_PIN_NAME                        "ft3417-int"
static uint8_t buf_addr[2] = { 0 };
static uint8_t buf_value[2] = { 0 };

/************************************************************************
* Name: fts_i2c_Read
* Brief: i2c read
* Input: i2c info, write buf, write len, read buf, read len
* Output: get data in the 3rd buf
* Return: fail <0
***********************************************************************/
static int fts_i2c_Read(struct fts_ts_data *fts_ts, char *writebuf, int writelen, char *readbuf, int readlen)
{
    struct rt_i2c_msg msgs[2];
    int ret;
    if (writelen > 0)
    {
        msgs[0].addr  = fts_ts->addr;
        msgs[0].flags = RT_I2C_WR;
        msgs[0].len   = writelen;
        msgs[0].buf   = writebuf;

        msgs[1].addr  = fts_ts->addr;
        msgs[1].flags = RT_I2C_RD;
        msgs[1].len   = readlen;
        msgs[1].buf   = readbuf;
        ret = rt_i2c_transfer(fts_ts->i2c_bus, msgs, 2);
        if (ret < 0)
        {
            TP_DBG("f%s: i2c read error. error code = %d \n", __func__, ret);
        }
    }
    else
    {
        msgs[0].addr  = fts_ts->addr;
        msgs[0].flags = RT_I2C_RD;
        msgs[0].len   = readlen;
        msgs[0].buf   = readbuf;

        ret = rt_i2c_transfer(fts_ts->i2c_bus, msgs, 1);
        if (ret < 0)
        {
            TP_DBG("%s:i2c read error.  error code = %d \n", __func__, ret);
        }
    }
    return ret;
}

/************************************************************************
* Name: fts_i2c_Write
* Brief: i2c write
* Input: i2c info, write buf, write len
* Output: no
* Return: fail <0
***********************************************************************/
static int fts_i2c_Write(struct fts_ts_data *fts_ts, char *writebuf, int writelen)
{
    struct rt_i2c_msg msgs[2];
    int ret;
    msgs[0].addr  = fts_ts->addr;
    msgs[0].flags = RT_I2C_WR;
    msgs[0].len   = writelen;
    msgs[0].buf   = writebuf;

    ret = rt_i2c_transfer(fts_ts->i2c_bus, msgs, 1);
    if (ret < 0)
    {
        TP_DBG("%s i2c write error.\n", __func__);
    }
    return ret;
}

/************************************************************************
* Name: fts_read_Touchdata
* Brief: report the point information
* Input: event info
* Output: get touch data in pinfo
* Return: success is zero
***********************************************************************/
static unsigned int buf_count_add=0;
static unsigned int buf_count_neg=0;
//unsigned int buf_count_add1;
//unsigned int buf_count_neg1;
static uint8_t buf_touch_data[30 * POINT_READ_BUF] = { 0 };    //0xFF
static int fts_read_Touchdata(struct fts_ts_data *fts_ts)
{
    struct fts_event *event = &fts_ts->event;
    uint8_t buf[POINT_READ_BUF] = { 0 };    //0xFF
    int ret = -1;
    int i = 0;
    uint8_t pointid = FTS_MAX_ID;
    //uint8_t pt00f=0;
    ret = fts_i2c_Read(fts_ts, buf, 1, buf, POINT_READ_BUF);
    if (ret < 0)
    {
        TP_DBG("%s read touchdata failed.\n", __func__);
        return ret;
    }
    buf_count_add++;
    //buf_count_add1=buf_count_add;
    rt_memcpy(buf_touch_data + (((buf_count_add - 1) % 30) * POINT_READ_BUF),
              buf, sizeof(uint8_t) * POINT_READ_BUF);




    return 0;
}

/************************************************************************
* Name: fts_report_value
* Brief: report the point information
* Input: event info
* Output: no
* Return: success is 0(RT_EOK)
***********************************************************************/
static struct rtgui_event_mouse emouse = {0};
static int xx = 0, yy = 0, zz = 0;
static int fts_report_value(struct fts_ts_data *fts_ts)
{
    struct fts_event *event = &fts_ts->event;
    int i,result;
    int uppoint = 0;
    int touchs = 0;
    uint8_t pointid = FTS_MAX_ID;
    uint8_t buf[POINT_READ_BUF] = { 0 };//0xFF
    //struct rtgui_event_mouse emouse;

    static int touch_down = 0;

    buf_count_neg++;
    //buf_count_neg1=buf_count_neg;
    rt_memcpy(buf,
              buf_touch_data + (((buf_count_neg - 1) % 30) * POINT_READ_BUF),
              sizeof(uint8_t) * POINT_READ_BUF);


    rt_memset(event, 0, sizeof(struct fts_event));
    event->touch_point_num = buf[FT_TOUCH_POINT_NUM] & 0x0F;
    event->touch_point = 0;
    for (i = 0; i < fts_updateinfo_curr.TPD_MAX_POINTS; i++)
    {
        pointid = (buf[FTS_TOUCH_ID_POS + FTS_TOUCH_STEP * i]) >> 4;
        if (pointid >= FTS_MAX_ID)
            break;
        else
            event->touch_point++;

#if TOUCH_SWAP_XY
        event->au16_y[i] = (((int16_t) buf[FTS_TOUCH_X_H_POS + FTS_TOUCH_STEP * i]) & 0x0F) << 8
                           |  (((int16_t) buf[FTS_TOUCH_X_L_POS + FTS_TOUCH_STEP * i])& 0xFF);
        event->au16_x[i] = (((int16_t) buf[FTS_TOUCH_Y_H_POS + FTS_TOUCH_STEP * i]) & 0x0F) << 8
                           |  (((int16_t) buf[FTS_TOUCH_Y_L_POS + FTS_TOUCH_STEP * i]) & 0xFF);

#else
        event->au16_x[i] = (((int16_t) buf[FTS_TOUCH_X_H_POS + FTS_TOUCH_STEP * i]) & 0x0F) << 8
                           |  (((int16_t) buf[FTS_TOUCH_X_L_POS + FTS_TOUCH_STEP * i])& 0xFF);
        event->au16_y[i] = (((int16_t) buf[FTS_TOUCH_Y_H_POS + FTS_TOUCH_STEP * i]) & 0x0F) << 8
                           |  (((int16_t) buf[FTS_TOUCH_Y_L_POS + FTS_TOUCH_STEP * i]) & 0xFF);

#endif

#if TOUCH_SWAP_Y

        event->au16_y[i] = TOUCH_MAX_Y - event->au16_y[i];
#endif
        TP_DBG("event->au16_x[%d] = %04x\n",i,event->au16_x[i]);
        TP_DBG("event->au16_y[%d] = %04x\n",i,event->au16_y[i]);

        event->au8_touch_event[i] = buf[FTS_TOUCH_EVENT_POS + FTS_TOUCH_STEP * i] >> 6;
        event->au8_finger_id[i] = (buf[FTS_TOUCH_ID_POS + FTS_TOUCH_STEP * i]) >> 4;
        event->pressure[i] = (buf[FTS_TOUCH_XY_POS + FTS_TOUCH_STEP * i]);//cannot constant value
        event->area[i] = (buf[FTS_TOUCH_MISC + FTS_TOUCH_STEP * i]) >> 4;
        if((event->au8_touch_event[i]==0 || event->au8_touch_event[i]==2)&&((event->touch_point_num==0)||(event->pressure[i]==0 && event->area[i]==0  )))
            return 1;
#ifdef DEBUG
        TP_DBG("id=%d event=%d x=%d y=%d pressure=%d area=%d\n",
               event->au8_finger_id[i],
               event->au8_touch_event[i],
               event->au16_x[i],
               event->au16_y[i],
               event->pressure[i],
               event->area[i]);
#endif
    }

    /*protocol B*/
    for (i = 0; i < event->touch_point; i++)
    {
        if (event->au8_touch_event[i]== 0 || event->au8_touch_event[i] == 2)
        {
//            input_mt_report_slot_state(fts_ts->input_dev, MT_TOOL_FINGER, true);
//            input_report_abs(fts_ts->input_dev, ABS_MT_PRESSURE, event->pressure[i]);
//            input_report_abs(fts_ts->input_dev, ABS_MT_TOUCH_MAJOR, event->area[i]);
//            input_report_abs(fts_ts->input_dev, ABS_MT_POSITION_X, event->au16_x[i]);
//            input_report_abs(fts_ts->input_dev, ABS_MT_POSITION_Y, event->au16_y[i]);
            touchs |= BIT(event->au8_finger_id[i]);
            fts_ts->touchs |= BIT(event->au8_finger_id[i]);

            TP_DBG("finger true\n");
            TP_DBG("report_abs_X = %d, report_abs_Y = %d  !\n", event->au16_x[i], event->au16_y[i]);


            if(touch_down_up_status == 1)
            {
                //send mouse motion event;
                emouse.parent.type = RTGUI_EVENT_MOUSE_MOTION;
                emouse.x = event->au16_x[0] > 479 ? 479 : event->au16_x[0];
                emouse.y = event->au16_y[0];
                emouse.ts = rt_tick_get();
				
				if (xx != 0 || yy != 0 || (xx == 0 && yy == 0))
				{
					if (xx != emouse.x || emouse.y != yy)
					{
						rtgui_server_post_event(&emouse.parent, sizeof(emouse));
						TP_DBG("RTGUI_EVENT_MOUSE_MOTION x=%d,y=%d\n",event->au16_x[0],event->au16_y[0]);
						zz = 0;
					}
					else
					{
						zz ++;
					}
				}
				
				xx = emouse.x;
				yy = emouse.y;
				
				if (zz >= 10)
				{
					xx = 0;
					yy = 0;
				}
            }
        }
        else
        {
            uppoint++;
//            input_mt_report_slot_state(fts_ts->input_dev, MT_TOOL_FINGER, false);
            fts_ts->touchs &= ~BIT(event->au8_finger_id[i]);
        }
    }

    if (0 == (fts_ts->touchs ^ touchs))
    {
        for (i = 0; i < CFG_MAX_TOUCH_POINTS; i++)
        {
            if (BIT(i) & (fts_ts->touchs ^ touchs))
            {
//                input_mt_slot(fts_ts->input_dev, i);
//                input_mt_report_slot_state(fts_ts->input_dev, MT_TOOL_FINGER, false);
                TP_DBG("finger false\n");
            }
        }
    }
    fts_ts->touchs = touchs;
    if(event->touch_point == uppoint && touch_down_up_status == 1)
    {
//        input_report_key(fts_ts->input_dev, BTN_TOUCH, 0);
        touch_down_up_status = 0;
        TP_DBG("touch up !\n");

        /* Always send touch up event. */
        emouse.parent.type = RTGUI_EVENT_MOUSE_BUTTON;
        emouse.button = RTGUI_MOUSE_BUTTON_LEFT | RTGUI_MOUSE_BUTTON_UP;
        emouse.x = event->au16_x[0] > 479 ? 479 : event->au16_x[0];
        emouse.y = event->au16_y[0];
        emouse.ts = rt_tick_get();
        do
        {
            result = rtgui_server_post_event(&emouse.parent, sizeof(emouse));
            if (result != RT_EOK)
            {
                rt_thread_delay(RT_TICK_PER_SECOND / 10);
            }
        }
        while (result != RT_EOK);
        TP_DBG("RTGUI_MOUSE_BUTTON_UP x=%d,y=%d\n",event->au16_x[0],event->au16_y[0]);
    }
    else
    {
//        input_report_key(fts_ts->input_dev, BTN_TOUCH, event->touch_point > 0);
        if (touch_down_up_status == 0)
        {
            touch_down_up_status = 1;
            TP_DBG("touch down !\n");

            //send mouse down event
            emouse.parent.sender = RT_NULL;
            emouse.wid = RT_NULL;

            emouse.parent.type = RTGUI_EVENT_MOUSE_BUTTON;
            emouse.button = RTGUI_MOUSE_BUTTON_LEFT | RTGUI_MOUSE_BUTTON_DOWN;
            emouse.x = event->au16_x[0] > 479 ? 479 : event->au16_x[0];
            emouse.y = event->au16_y[0];
            emouse.ts = rt_tick_get();
            emouse.id = emouse.ts;

            do
            {
                result = rtgui_server_post_event(&emouse.parent, sizeof(emouse));
                if (result != RT_EOK)
                {
                    rt_thread_delay(RT_TICK_PER_SECOND / 10);
                }
            }
            while (result != RT_EOK);
            TP_DBG("RTGUI_MOUSE_BUTTON_DOWN x=%d,y=%d\n",event->au16_x[0],event->au16_y[0]);
        }
    }

    return 0;
}





/************************************************************************
* Name: fts_get_upgrade_array
* Brief: decide which ic
* Input: no
* Output: get ic info in fts_updateinfo_curr
* Return: no
***********************************************************************/
static void fts_get_upgrade_array(struct fts_ts_data *fts_ts)
{
    uint8_t reg_ofs;
    uint8_t chip_id;
    uint32_t i;

    reg_ofs = FTS_REG_CHIP_ID;
    fts_i2c_Read(fts_ts,&reg_ofs,1,&chip_id,1);

    TP_DBG("%s chip_id = %x\n", __func__, chip_id);

    for (i = 0; i < sizeof(fts_updateinfo) / sizeof(struct Upgrade_Info); i++)
    {
        if (chip_id == fts_updateinfo[i].CHIP_ID)
        {
            memcpy(&fts_updateinfo_curr, &fts_updateinfo[i], sizeof(struct Upgrade_Info));
            break;
        }
    }

    if(i >= sizeof(fts_updateinfo)/sizeof(struct Upgrade_Info))
    {
        memcpy(&fts_updateinfo_curr, &fts_updateinfo[0], sizeof(struct Upgrade_Info));
    }
}




/************************************************************************
* Name: fts_ts_probe
* Brief: driver entrance function for initial/power on/create channel
* Input: i2c info, device id
* Output: no
* Return: 0
***********************************************************************/
int fts_ts_probe(struct fts_ts_data *fts_ts,struct rt_i2c_bus_device *i2c_bus, const uint8_t addr)
{
    int err = 0;
    uint8_t uc_reg_value;
    uint8_t uc_reg_addr;
    TP_DBG("FT device prob process Start !\n");

    fts_ts->i2c_bus = i2c_bus;
    fts_ts->addr    = addr;
    fts_ts->init_success = 0;
    if (fts_ts->x_max > TOUCH_MAX_X)
        fts_ts->x_max = TOUCH_MAX_X;
    if (fts_ts->y_max > TOUCH_MAX_Y)
        fts_ts->y_max = TOUCH_MAX_Y;

    fts_get_upgrade_array(fts_ts);

    /*get some register information */
    uc_reg_addr = FTS_REG_FW_VER;
    err = fts_i2c_Read(fts_ts, &uc_reg_addr, 1, &uc_reg_value, 1);
    if (err < 0)
    {
        fts_ts->init_success = 0;
        fts_ts->fw_ver = 0xff;
    }
    else
    {
        fts_ts->init_success = 1;
        TP_DBG("Firmware version = 0x%x\n", uc_reg_value);
        fts_ts->fw_ver = uc_reg_value;
    }

    uc_reg_addr = FTS_REG_POINT_RATE;
    err = fts_i2c_Read(fts_ts, &uc_reg_addr, 1, &uc_reg_value, 1);
    if (err < 0)
        fts_ts->init_success = 0;
    else
    {
        fts_ts->init_success = 1;
        TP_DBG("report rate is %dHz.\n", uc_reg_value * 10);
    }

    uc_reg_addr = FTS_REG_THGROUP;
    err = fts_i2c_Read(fts_ts, &uc_reg_addr, 1, &uc_reg_value, 1);
    if (err < 0)
        fts_ts->init_success = 0;
    else
    {
        fts_ts->init_success = 1;
        TP_DBG("touch threshold is %d.\n", uc_reg_value * 4);
    }

    uc_reg_addr = FTS_REG_VENDOR_ID;
    err = fts_i2c_Read(fts_ts, &uc_reg_addr, 1, &uc_reg_value, 1);
    if (err < 0)
        fts_ts->init_success = 0;
    else
    {
        fts_ts->init_success = 1;
        TP_DBG("VENDOR ID = 0x%x\n", uc_reg_value);
    }

    if (fts_ts->init_success == 1)
        fts_init_success = 1;
    return 0;
}

/************************************************************************
* Name: fts_ts_interrupt
* Brief: the focaltech device will signal the host about TRIGGER_FALLING, and processed when the interrupt is asserted.
* Input: irq, device id
* Output: no
* Return: irq handle
***********************************************************************/
static void fts_ts_interrupt(struct fts_ts_data *fts_ts)
{
    rt_sem_release(&fts_ts->sem);
    return ;
}


static void thread_fts_ts_service(void *param)
{
    struct fts_ts_data *fts_ts = (struct fts_ts_data *)param;
    int ret = 0;

    while(rt_sem_take(&fts_ts->sem,RT_WAITING_FOREVER) == RT_EOK)
    {
#ifdef FTS_GESTRUE
        i2c_smbus_read_i2c_block_data(fts_ts->client, 0xd0, 1, &state);
        /*TP_DBG("tpd fts_read_Gestruedata state=%d\n", state);*/
        if (state == 1)
        {
            fts_read_Gestruedata(fts_ts);
            rt_hw_interrupt_umask(fts_ts->irq);
            /*continue;*/
        }
        else
        {
#endif
        //disable_irq_nosync(fts_ts->irq);
        ret = fts_read_Touchdata(fts_ts);
        if (ret == 0)
            fts_report_value(fts_ts);
		rt_thread_delay(RT_TICK_PER_SECOND / 30);
#ifdef FTS_GESTRUE
        }
#endif
    }
}

static struct fts_ts_data g_fts_ts =
{
    .addr   = 0,
    .fw_ver = 0,     //firmware version
    .x_min  = 0,
    .x_max  = 480,
    .y_min  = 0,
    .y_max  = 320,
    .touchs = 0,

    .init_success = 0,
};

int rt_hw_touch_init(void)
{
    struct rt_i2c_bus_device *i2c_bus;
#define TP_INT_PORT                GPIO_PORT_C
#define TP_INT_PIN                 GPIO_Pin_25
    /* init IO */
    gpio_direction_input(TP_INT_PORT,TP_INT_PIN);
    gpio_enable_pull(TP_INT_PORT,TP_INT_PIN);

    /* register irq */
    gpio_mask_irq(TP_INT_PORT,TP_INT_PIN);
    gpio_set_func(TP_INT_PORT,TP_INT_PIN,GPIO_INPUT_PULL | GPIO_INT_FE);
    gpio_set_irq_callback(TP_INT_PORT,TP_INT_PIN,fts_ts_interrupt, (void*)&g_fts_ts);

    /* try to probe device */
    i2c_bus = rt_i2c_bus_device_find("i2c0");
    if (i2c_bus == RT_NULL)
    {
        rt_kprintf("[TP]:can't find the i2c bus:%s\n", "i2c0");
        return -RT_EIO;
    }

    fts_ts_probe(&g_fts_ts,i2c_bus,FTS_SLAVE_ADDR);
    if(g_fts_ts.init_success == 1)
    {
        rt_thread_t tid;

        /* init semaphore wakeup thread... */
        rt_sem_init(&g_fts_ts.sem,"tp_sem",0,RT_IPC_FLAG_FIFO);

        /* create thread for fts device */
        tid = rt_thread_create("tp_srv",
                               thread_fts_ts_service, (void *) &g_fts_ts,
                               2048,
                               RT_TOUCH_THREAD_PRIORITY,
                               10);
        if(tid != RT_NULL)
            rt_thread_startup(tid);

        /* enable interrupt */
        gpio_unmask_irq(TP_INT_PORT,TP_INT_PIN);

        return RT_EOK;
    }

    return -RT_EIO;
}
INIT_DEVICE_EXPORT(rt_hw_touch_init);

#endif /* RT_USING_FT6x06 */
