/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
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
#include "drv_keyboard.h"

#define DBG_LVL DBG_INFO
#include "rtdbg.h"

#define KEYBOARD_ADDRESS    (0x10006000)
#define KEYBOARD_IRQ_NUM    (IRQ_VEXPRESS_A9_KBD)

#ifdef PKG_USING_GUIENGINE

#include <rtgui/event.h>
#include <rtgui/rtgui_server.h>

typedef rt_uint32_t virtual_addr_t;

enum{
    KEYBOARD_CR     = 0x00,
    KEYBOARD_STAT   = 0x04,
    KEYBOARD_DATA   = 0x08,
    KEYBOARD_CLKDIV = 0x0c,
    KEYBOARD_IIR    = 0x10,
};

struct keyboard_pl050_pdata_t
{
    virtual_addr_t virt;
    int irq;
};

enum decode_state {
    DECODE_STATE_MAKE_CODE,
    DECODE_STATE_BREAK_CODE,
    DECODE_STATE_LONG_MAKE_CODE,
    DECODE_STATE_LONG_BREAK_CODE
};

struct keymap {
    rt_uint8_t data;
    rt_uint32_t key;
    rt_uint32_t unicode;
    char *normal_key;
};

enum key_value_t {
    KEY_BUTTON_UP,
    KEY_BUTTON_DOWN,
};

enum {
    KBD_LEFT_SHIFT  = (0x1 << 0),
    KBD_RIGHT_SHIFT = (0x1 << 1),
    KBD_LEFT_CTRL   = (0x1 << 2),
    KBD_RIGHT_CTRL  = (0x1 << 3),
    KBD_CAPS_LOCK   = (0x1 << 6),
    KBD_NUM_LOCK    = (0x1 << 7),
    KBD_SCROLL_LOCK = (0x1 << 8),
};

static const struct keymap map[] = {
    {0x1c,  RTGUIK_a, 0, "a",          },
    {0x32,  RTGUIK_b, 0, "b",          },
    {0x21,  RTGUIK_c, 0, "c",          },
    {0x23,  RTGUIK_d, 0, "d",          },
    {0x24,  RTGUIK_e, 0, "e",          },
    {0x2b,  RTGUIK_f, 0, "f",          },
    {0x34,  RTGUIK_g, 0, "g",          },
    {0x33,  RTGUIK_h, 0, "h",          },
    {0x43,  RTGUIK_i, 0, "i",          },
    {0x3b,  RTGUIK_j, 0, "j",          },
    {0x42,  RTGUIK_k, 0, "k",          },
    {0x4b,  RTGUIK_l, 0, "l",          },
    {0x3a,  RTGUIK_m, 0, "m",          },
    {0x31,  RTGUIK_n, 0, "n",          },
    {0x44,  RTGUIK_o, 0, "o",          },
    {0x4d,  RTGUIK_p, 0, "p",          },
    {0x15,  RTGUIK_q, 0, "q",          },
    {0x2d,  RTGUIK_r, 0, "r",          },
    {0x1b,  RTGUIK_s, 0, "s",          },
    {0x2c,  RTGUIK_k, 0, "k",          },
    {0x3c,  RTGUIK_u, 0, "u",          },
    {0x2a,  RTGUIK_v, 0, "v",          },
    {0x1d,  RTGUIK_w, 0, "w",          },
    {0x22,  RTGUIK_x, 0, "x",          },
    {0x35,  RTGUIK_y, 0, "y",          },
    {0x1a,  RTGUIK_z, 0, "z",          },

    {0x45,  RTGUIK_0, 0, "0",          },
    {0x16,  RTGUIK_1, 0, "1",          },
    {0x1e,  RTGUIK_2, 0, "2",          },
    {0x26,  RTGUIK_3, 0, "3",          },
    {0x25,  RTGUIK_4, 0, "4",          },
    {0x2e,  RTGUIK_5, 0, "5",          },
    {0x36,  RTGUIK_6, 0, "6",          },
    {0x3d,  RTGUIK_7, 0, "7",          },
    {0x3e,  RTGUIK_8, 0, "8",          },
    {0x46,  RTGUIK_9, 0, "9",          },

    {0x05,  RTGUIK_F1,  0, "F1",       },
    {0x06,  RTGUIK_F2,  0, "F2",       },
    {0x04,  RTGUIK_F3,  0, "F3",       },
    {0x0c,  RTGUIK_F4,  0, "F4",       },
    {0x03,  RTGUIK_F5,  0, "F5",       },
    {0x0b,  RTGUIK_F6,  0, "F6",       },
    {0x83,  RTGUIK_F7,  0, "F7",       },
    {0x0a,  RTGUIK_F8,  0, "F8",       },
    {0x01,  RTGUIK_F9,  0, "F9",       },
    {0x09,  RTGUIK_F10, 0, "F10",      },
    {0x78,  RTGUIK_F11, 0, "F11",      },
    {0x07,  RTGUIK_F12, 0, "F12",      },

    {0x29,  RTGUIK_SPACE,  0, "SPACE"  },
    {0x71,  RTGUIK_DELETE, 0, "DELETE" },
    {0x52,  RTGUIK_QUOTE,  0, "'"      },
    {0x55,  RTGUIK_EQUALS, 0, "="      },
    {0x41,  RTGUIK_COMMA,  0, ","      },
    {0x4e,  RTGUIK_MINUS,  0, "-"      },
    // {0x49,  RTGUIK_,    0, "."         },
    {0x4a,  RTGUIK_SLASH,  0, "/"      },
    {0x4c,  RTGUIK_SEMICOLON, 0, ";"   },
    {0x54,  RTGUIK_LEFTBRACKET, 0, "[" },
    {0x5d,  RTGUIK_BACKSLASH, 0, "\\"  },
    {0x5b,  RTGUIK_RIGHTBRACKET, 0, "]"},
    {0x75,  RTGUIK_UP,    0, "UP"      },
    {0x72,  RTGUIK_DOWN,  0, "DOWN"    },
    {0x6b,  RTGUIK_LEFT,  0, "LEFT"    },
    {0x74,  RTGUIK_RIGHT, 0, "RIGHT"   },
    {0x0d,  RTGUIK_TAB,   0, "TAB"     },
    {0x76,  RTGUIK_ESCAPE, 0, "ESC"    },
    {0x37,  RTGUIK_POWER,  0, "POWER"  },
    {0x5a,  RTGUIK_KP_ENTER, 0, "ENTER"},
    {0x66,  RTGUIK_BACKSPACE, 0, "BACKSPACE"},
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

rt_inline int kmi_write(struct keyboard_pl050_pdata_t * pdat, rt_uint8_t value)
{
    int timeout = 1000;

    while((read8(pdat->virt + KEYBOARD_STAT) & (1 << 6)) == 0 && timeout--);

    if(timeout)
    {
        write8(pdat->virt + KEYBOARD_DATA, value);
        while((read8(pdat->virt + KEYBOARD_STAT) & (1 << 4)) == 0);

        if(read8(pdat->virt + KEYBOARD_DATA) == 0xfa)
            return RT_TRUE;
    }
    return RT_FALSE;
}

rt_inline int kmi_read(struct keyboard_pl050_pdata_t * pdat, rt_uint8_t * value)
{
    if((read8(pdat->virt + KEYBOARD_STAT) & (1 << 4)))
    {
        *value = read8(pdat->virt + KEYBOARD_DATA);
        return RT_TRUE;
    }
    return RT_FALSE;
}

static void keyboard_report_event(void * device, rt_uint32_t flag, rt_uint8_t data, enum key_value_t press)
{
    struct rtgui_event_kbd key_event;
    rt_uint16_t i = 0, mod = 0, find_key = 0;

    for(i = 0; i < sizeof(map)/sizeof(map[0]); i++)
    {
        if (map[i].data == data)
        {
            LOG_D("KEY info:");
            if (flag & KBD_CAPS_LOCK)
            {
                LOG_D("CAPS:LOCK");
            }
            else
            {
                LOG_D("CAPS:UNLOCK");
            }

            if (flag & KBD_LEFT_SHIFT)
            {
                mod |= RTGUI_KMOD_LSHIFT;
                LOG_D("SHIFT:LEFT");
            }
            else if (flag & KBD_RIGHT_SHIFT)
            {
                mod |= RTGUI_KMOD_RSHIFT;
                LOG_D("SHIFT:RIGHT");
            }
            else
            {
                LOG_D("SHIFT:NULL");
            }

            if (flag & KBD_LEFT_CTRL)
            {
                mod |= RTGUI_KMOD_LCTRL;
                LOG_D("CTRL:LEFT");
            }
            else if (flag & KBD_RIGHT_CTRL)
            {
                mod |= RTGUI_KMOD_RCTRL;
                LOG_D("CTRL:RIGHT");
            }
            else
            {
                LOG_D("CTRL:NULL");
            }

            LOG_D("flag:0x%08x value:0x%x key:%s status:%s", \
                flag, data, map[i].normal_key, press ==0 ? "UP" : "DOWN");
            find_key = 1;
            break;
        }
    }
    if (find_key == 0)
    {
        LOG_D("flag:0x%08x value:0x%x key:%s status:%s", \
            flag, data, "UNKNOWN", press ==0 ? "UP" : "DOWN");
        return;
    }

    key_event.parent.sender = RT_NULL;
    key_event.parent.type = RTGUI_EVENT_KBD;
    key_event.type = (press == 0 ? RTGUI_KEYUP : RTGUI_KEYDOWN);
    key_event.key = map[i].key;
    key_event.mod = mod;
    key_event.unicode = map[i].unicode;
    rtgui_server_post_event(&key_event.parent, sizeof(key_event));
}

static void keyboard_pl050_interrupt(int irq, void *data)
{
    struct keyboard_pl050_pdata_t * pdat = (struct keyboard_pl050_pdata_t *)data;
    static enum decode_state ds = DECODE_STATE_MAKE_CODE;
    static rt_uint32_t kbd_flag = KBD_NUM_LOCK;
    rt_uint8_t status, value;

    status = read8(pdat->virt + KEYBOARD_IIR);

    while(status & (1 << 0))
    {
        value = read8(pdat->virt + KEYBOARD_DATA);

        switch(ds)
        {
        case DECODE_STATE_MAKE_CODE:
            /* break code */
            if(value == 0xf0)
            {
                ds = DECODE_STATE_BREAK_CODE;
            }
            /* long make code */
            else if(value == 0xe0)
            {
                ds = DECODE_STATE_LONG_MAKE_CODE;
            }
            else
            {
                ds = DECODE_STATE_MAKE_CODE;

                /* left shift */
                if(value == 0x12)
                {
                    kbd_flag |= KBD_LEFT_SHIFT;
                }
                /* right shift */
                else if(value == 0x59)
                {
                    kbd_flag |= KBD_RIGHT_SHIFT;
                }
                /* left ctrl */
                else if(value == 0x14)
                {
                    kbd_flag |= KBD_LEFT_CTRL;
                }
                /* caps lock */
                else if(value == 0x58)
                {
                    if(kbd_flag & KBD_CAPS_LOCK)
                        kbd_flag &= ~KBD_CAPS_LOCK;
                    else
                        kbd_flag |= KBD_CAPS_LOCK;
                }
                /* scroll lock */
                else if(value == 0x7e)
                {
                    if(kbd_flag & KBD_SCROLL_LOCK)
                        kbd_flag &= ~KBD_SCROLL_LOCK;
                    else
                        kbd_flag |= KBD_SCROLL_LOCK;
                }
                /* num lock */
                else if(value == 0x77)
                {
                    if(kbd_flag & KBD_NUM_LOCK)
                        kbd_flag &= ~KBD_NUM_LOCK;
                    else
                        kbd_flag |= KBD_NUM_LOCK;
                }
                /* others */
                else
                {
                    keyboard_report_event(data, kbd_flag, value, KEY_BUTTON_DOWN);
                }
            }
            break;

        case DECODE_STATE_BREAK_CODE:
            if( (value != 0xf0) && (value != 0xe0))
            {
                ds = DECODE_STATE_MAKE_CODE;

                /* left shift */
                if(value == 0x12)
                {
                    kbd_flag &= ~KBD_LEFT_SHIFT;
                }
                /* right shift */
                else if(value == 0x59)
                {
                    kbd_flag &= ~KBD_RIGHT_SHIFT;
                }
                /* left ctrl */
                else if(value == 0x14)
                {
                    kbd_flag &= ~KBD_LEFT_CTRL;
                }
                /* others */
                else
                {
                    keyboard_report_event(data, kbd_flag, value, KEY_BUTTON_UP);
                }
            }
            else
            {
                ds = DECODE_STATE_BREAK_CODE;
            }
            break;

        case DECODE_STATE_LONG_MAKE_CODE:
            if( value != 0xf0 && value!= 0xe0)
            {
                ds = DECODE_STATE_MAKE_CODE;

                /* left ctrl */
                if(value == 0x14)
                {
                    kbd_flag |= KBD_RIGHT_CTRL;
                }
                /* others */
                else
                {
                    keyboard_report_event(data, kbd_flag, value, KEY_BUTTON_DOWN);
                }
            }
            else
            {
                ds = DECODE_STATE_LONG_BREAK_CODE;
            }
            break;

        case DECODE_STATE_LONG_BREAK_CODE:
            if( (value != 0xf0) && (value != 0xe0))
            {
                ds = DECODE_STATE_MAKE_CODE;

                /* left ctrl */
                if(value == 0x14)
                {
                    kbd_flag &= ~KBD_RIGHT_CTRL;
                }
                /* others */
                else
                {
                    keyboard_report_event(data, kbd_flag, value, KEY_BUTTON_UP);
                }
            }
            else
            {
                ds = DECODE_STATE_LONG_BREAK_CODE;
            }
            break;

        default:
            ds = DECODE_STATE_MAKE_CODE;
            break;
        }

        status = read8(pdat->virt + KEYBOARD_IIR);
    }
}

int rt_hw_keyboard_init(void)
{
    rt_uint8_t value;
    rt_uint32_t id;
    struct keyboard_pl050_pdata_t *pdat;
    virtual_addr_t virt;
    int irq = KEYBOARD_IRQ_NUM;

    virt = (virtual_addr_t)rt_ioremap((void*)KEYBOARD_ADDRESS, 0x1000);

    id = (((read32(virt + 0xfec) & 0xff) << 24) |
                ((read32(virt + 0xfe8) & 0xff) << 16) |
                ((read32(virt + 0xfe4) & 0xff) <<  8) |
                ((read32(virt + 0xfe0) & 0xff) <<  0));

    if(((id >> 12) & 0xff) != 0x41 || (id & 0xfff) != 0x050)
    {
        LOG_E("read id fail id:0x%08x", id);
        return -RT_ERROR;
    }

    pdat = rt_malloc(sizeof(struct keyboard_pl050_pdata_t));
    if(!pdat)
    {
        LOG_E("malloc memory failed");
        return -RT_ERROR;
    }
    rt_memset(pdat, 0, sizeof(struct keyboard_pl050_pdata_t));

    pdat->virt = virt;
    pdat->irq = irq;

    write8(pdat->virt + KEYBOARD_CLKDIV, 0);
    write8(pdat->virt + KEYBOARD_CR, (1 << 2));
    kmi_read(pdat, &value);
    kmi_write(pdat, 0xff);
    kmi_read(pdat, &value);
    kmi_write(pdat, 0xf3);
    kmi_write(pdat, 0x2b);
    kmi_write(pdat, 0xf0);
    kmi_write(pdat, 0x02);
    kmi_write(pdat, 0xfa);
    kmi_write(pdat, 0xed);
    kmi_write(pdat, 0x02);
    write8(pdat->virt + KEYBOARD_CR, (1 << 2) | (1 << 4));

    rt_hw_interrupt_install(irq, keyboard_pl050_interrupt, (void *)pdat, "keyboard");
    rt_hw_interrupt_umask(irq);

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_keyboard_init);

#endif
