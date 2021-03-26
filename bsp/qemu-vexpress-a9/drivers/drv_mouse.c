/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020/12/31     Bernard      Add license info
 */
#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include "board.h"
#include "interrupt.h"
#include "drv_mouse.h"
#include "drv_clcd.h"

#define DBG_TAG "drv.mouse"
#define DBG_LVL DBG_INFO
#include "rtdbg.h"

#define MOUSE_ADDRESS    (0x10007000)
#define MOUSE_IRQ_NUM    (IRQ_VEXPRESS_A9_MOUSE)
#define MOUSE_XMAX       (BSP_LCD_WIDTH)
#define MOUSE_YMAX       (BSP_LCD_HEIGHT)

#define MOUSE_BUTTON_LEFT    (0x01)
#define MOUSE_BUTTON_RIGHT   (0x02)
#define MOUSE_BUTTON_MIDDLE  (0x04)
#define MOUSE_BUTTON_DOWN    (0x10)
#define MOUSE_BUTTON_UP      (0x20)
#define MOUSE_BUTTON_MOVE    (0x40)
#define MOUSE_BUTTON_WHELL   (0x80)

#ifdef PKG_USING_GUIENGINE

#include <rtgui/event.h>
#include <rtgui/rtgui_server.h>

typedef rt_uint32_t virtual_addr_t;

enum {
    MOUSE_CR        = 0x00,
    MOUSE_STAT      = 0x04,
    MOUSE_DATA      = 0x08,
    MOUSE_CLKDIV    = 0x0c,
    MOUSE_IIR       = 0x10,
};

struct mouse_pl050_pdata_t {
    virtual_addr_t virt;
    int irq;
    int xmax, ymax;
    int xpos, ypos;
    unsigned char packet[4];
    int index;
    int obtn;
    int type;
};

rt_inline rt_uint8_t read8(uint32_t addr)
{
    return (*((volatile rt_uint8_t *)(addr)));
}

rt_inline void write8(uint32_t addr, rt_uint8_t value)
{
    *((volatile rt_uint8_t *)(addr)) = value;
}

rt_inline rt_uint32_t read32(uint32_t addr)
{
    return (*((volatile rt_uint32_t *)(addr)));
}

rt_inline void write32(uint32_t addr, rt_uint32_t value)
{
    *((volatile rt_uint32_t *)(addr)) = value;
}

rt_inline int kmi_write(struct mouse_pl050_pdata_t * pdat, rt_uint8_t value)
{
    int timeout = 1000;

    while((read8(pdat->virt + MOUSE_STAT) & (1 << 6)) == 0 && timeout--);

    if(timeout)
    {
        write8(pdat->virt + MOUSE_DATA, value);
        while((read8(pdat->virt + MOUSE_STAT) & (1 << 4)) == 0);

        if(read8(pdat->virt + MOUSE_DATA) == 0xfa)
            return RT_TRUE;
    }
    return RT_FALSE;
}

rt_inline int kmi_read(struct mouse_pl050_pdata_t * pdat, rt_uint8_t * value)
{
    if((read8(pdat->virt + MOUSE_STAT) & (1 << 4)))
    {
        *value = read8(pdat->virt + MOUSE_DATA);
        return RT_TRUE;
    }
    return RT_FALSE;
}

static rt_uint32_t emouse_id;

void push_event_touch_move(int x, int y)
{
    struct rtgui_event_mouse emouse;

    emouse.parent.sender = RT_NULL;
    emouse.wid = RT_NULL;

    emouse.button = RTGUI_MOUSE_BUTTON_LEFT | RTGUI_MOUSE_BUTTON_DOWN;
    emouse.parent.type = RTGUI_EVENT_MOUSE_MOTION;
    emouse.x = x;
    emouse.y = y;
    emouse.ts = rt_tick_get();
    emouse.id = emouse_id;

    LOG_D("[line]:%d motion event id:%d x:%d y:%d", __LINE__, emouse.id, x, y);
    rtgui_server_post_event(&emouse.parent, sizeof(emouse));
}

void push_event_touch_begin(int x, int y)
{
    struct rtgui_event_mouse emouse;

    emouse_id = rt_tick_get();

    emouse.parent.sender = RT_NULL;
    emouse.wid = RT_NULL;

    emouse.parent.type = RTGUI_EVENT_MOUSE_BUTTON;
    emouse.button = RTGUI_MOUSE_BUTTON_LEFT | RTGUI_MOUSE_BUTTON_DOWN;
    emouse.x = x;
    emouse.y = y;
    emouse.ts = rt_tick_get();
    emouse.id = emouse_id;
    LOG_D("[line]:%d down event id:%d x:%d y:%d", __LINE__, emouse.id, x, y);
    rtgui_server_post_event(&emouse.parent, sizeof(emouse));
}

void push_event_touch_end(int x, int y)
{
    struct rtgui_event_mouse emouse;

    emouse.parent.sender = RT_NULL;
    emouse.wid = RT_NULL;

    emouse.parent.type = RTGUI_EVENT_MOUSE_BUTTON;
    emouse.button = RTGUI_MOUSE_BUTTON_LEFT | RTGUI_MOUSE_BUTTON_UP;
    emouse.x = x;
    emouse.y = y;
    emouse.ts = rt_tick_get();
    emouse.id = emouse_id;
    
    LOG_D("[line]:%d up event id:%d x:%d y:%d", __LINE__, emouse.id, x, y);
    rtgui_server_post_event(&emouse.parent, sizeof(emouse));
}

static void mouse_pl050_interrupt(int irq, void * data)
{
    struct mouse_pl050_pdata_t * pdat = (struct mouse_pl050_pdata_t *)data;
    int x, y, relx, rely, delta;
    int btndown, btnup, btn;
    int status = 0;

    status = read8(pdat->virt + MOUSE_IIR);
    while(status & (1 << 0))
    {
        pdat->packet[pdat->index] = read8(pdat->virt + MOUSE_DATA);
        pdat->index = (pdat->index + 1) & 0x3;

        if(pdat->index == 0)
        {
            btn = pdat->packet[0] & 0x7;
            btndown = (btn ^ pdat->obtn) & btn;
            btnup = (btn ^ pdat->obtn) & pdat->obtn;
            pdat->obtn = btn;

            if(pdat->packet[0] & 0x10)
                relx = 0xffffff00 | pdat->packet[1];
            else
                relx = pdat->packet[1];

            if(pdat->packet[0] & 0x20)
                rely = 0xffffff00 | pdat->packet[2];
            else
                rely = pdat->packet[2];
            rely = -rely;

            delta = pdat->packet[3] & 0xf;
            if(delta == 0xf)
                delta = -1;

            if(relx != 0)
            {
                pdat->xpos = pdat->xpos + relx;
                if(pdat->xpos < 0)
                    pdat->xpos = 0;
                if(pdat->xpos > pdat->xmax - 1)
                    pdat->xpos = pdat->xmax - 1;
            }
            if(rely != 0)
            {
                pdat->ypos = pdat->ypos + rely;
                if(pdat->ypos < 0)
                    pdat->ypos = 0;
                if(pdat->ypos > pdat->ymax - 1)
                    pdat->ypos = pdat->ymax - 1;
            }
            x = pdat->xpos;
            y = pdat->ypos;

            if((btn & (0x01 << 0)) && ((relx != 0) || (rely != 0)))
                push_event_touch_move(x, y);

            if(btndown & (0x01 << 0))
                push_event_touch_begin(x, y);

            if(btnup & (0x01 << 0))
                push_event_touch_end(x, y);
        }

        status = read8(pdat->virt + MOUSE_IIR);
    }
}

int rt_hw_mouse_init(void)
{
    rt_uint8_t value;
    rt_uint32_t id;
    struct mouse_pl050_pdata_t *pdat;
    virtual_addr_t virt = MOUSE_ADDRESS;
    int irq = MOUSE_IRQ_NUM;

    id = (((read32(virt + 0xfec) & 0xff) << 24) |
                ((read32(virt + 0xfe8) & 0xff) << 16) |
                ((read32(virt + 0xfe4) & 0xff) <<  8) |
                ((read32(virt + 0xfe0) & 0xff) <<  0));
    
    if(((id >> 12) & 0xff) != 0x41 || (id & 0xfff) != 0x050)
    {
        LOG_E("read id fail id:0x%08x", id);
        return RT_ERROR;
    }

    pdat = rt_malloc(sizeof(struct mouse_pl050_pdata_t));
    if(!pdat)
    {
        LOG_E("malloc memory failed");
        return RT_ERROR;
    }
    rt_memset(pdat, 0, sizeof(struct mouse_pl050_pdata_t));

    pdat->virt = virt;
    pdat->irq = irq;
    pdat->xmax = MOUSE_XMAX;
    pdat->ymax = MOUSE_YMAX;
    pdat->xpos = pdat->xmax / 2;
    pdat->ypos = pdat->ymax / 2;
    pdat->packet[0] = 0;
    pdat->packet[1] = 0;
    pdat->packet[2] = 0;
    pdat->packet[3] = 0;
    pdat->index = 0;
    pdat->obtn = 0;

    write8(pdat->virt + MOUSE_CLKDIV, 0);
    write8(pdat->virt + MOUSE_CR, (1 << 2));
    kmi_write(pdat, 0xff);
    kmi_read(pdat, &value);
    kmi_write(pdat, 0xf3);
    kmi_write(pdat, 200);
    kmi_write(pdat, 0xf3);
    kmi_write(pdat, 100);
    kmi_write(pdat, 0xf3);
    kmi_write(pdat, 80);
    kmi_write(pdat, 0xf2);
    kmi_read(pdat, &value);
    kmi_read(pdat, &value);
    kmi_write(pdat, 0xf3);
    kmi_write(pdat, 100);
    kmi_write(pdat, 0xe8);
    kmi_write(pdat, 0x02);
    kmi_write(pdat, 0xe6);
    kmi_write(pdat, 0xf4);
    kmi_read(pdat, &value);
    kmi_read(pdat, &value);
    kmi_read(pdat, &value);
    kmi_read(pdat, &value);
    write8(pdat->virt + MOUSE_CR, (1 << 2) | (1 << 4));

    rt_hw_interrupt_install(pdat->irq, mouse_pl050_interrupt, (void *)pdat, "mouse");
    rt_hw_interrupt_umask(pdat->irq);

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_mouse_init);

#endif
