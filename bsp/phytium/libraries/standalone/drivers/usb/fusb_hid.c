/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: fusb_hid.c
 * Date: 2022-09-28 18:26:42
 * LastEditTime: 2022-09-29 14:50:09
 * Description:  This files is for usb hid class implmentation
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2022/9/28   init commit
 */

#include <string.h>

#include "fkernel.h"
#include "fdebug.h"
#include "fsleep.h"

#include "fusb.h"
#include "fusb_hid.h"

enum FUsbHidRequests
{
    GET_REPORT = 0x1,
    GET_IDLE = 0x2,
    GET_PROTOCOL = 0x3,
    SET_REPORT = 0x9,
    SET_IDLE = 0xa,
    SET_PROTOCOL = 0xb
};

enum FUsbHidKeyboardModifiers
{
    KB_MOD_SHIFT = (1 << 0),
    KB_MOD_ALT = (1 << 1),
    KB_MOD_CTRL = (1 << 2),
    KB_MOD_CAPSLOCK = (1 << 3),
};

typedef union
{
    struct
    {
        u8 modifiers;
        u8 repeats;
        u8 keys[6];
    };
    u8 buffer[8];
} FUsbHidKeyboardEvent;

typedef struct
{
    void *queue;
    FUsbHidDescriptor *descriptor;

    FUsbHidKeyboardEvent previous;
    int lastkeypress;
    int repeat_delay;
} FUsbHid;

#define KEYBOARD_REPEAT_MS      30
#define INITIAL_REPEAT_DELAY    10
#define REPEAT_DELAY            2

#define FUSB_HID_INST(dev) ((FUsbHid*)(dev)->data)

#define FUSB_DEBUG_TAG "FUSB_HID"
#define FUSB_ERROR(format, ...) FT_DEBUG_PRINT_E(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)
#define FUSB_WARN(format, ...) FT_DEBUG_PRINT_W(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)
#define FUSB_INFO(format, ...) FT_DEBUG_PRINT_I(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)
#define FUSB_DEBUG(format, ...) FT_DEBUG_PRINT_D(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)

static const char *boot_protos[3] = { "(none)", "keyboard", "mouse" };

static void FUsbHidDestory(FUsbDev *dev)
{
    FUsb *instance = dev->controller->usb;

    if (FUSB_HID_INST(dev)->queue)
    {
        int i;
        for (i = 0; i <= dev->num_endp; i++)
        {
            if (dev->endpoints[i].endpoint == 0)
            {
                continue;
            }
            if (dev->endpoints[i].type != FUSB_INTERRUPT_EP)
            {
                continue;
            }
            if (dev->endpoints[i].direction != FUSB_IN)
            {
                continue;
            }
            break;
        }
        dev->controller->destroy_intr_queue(
            &dev->endpoints[i], FUSB_HID_INST(dev)->queue);
        FUSB_HID_INST(dev)->queue = NULL;
    }
    FUSB_FREE(instance, FUSB_HID_INST(dev)->descriptor);
    FUSB_HID_INST(dev)->descriptor = NULL;

    FUSB_FREE(instance, dev->data);
}

/* keybuffer is global to all USB keyboards */
static int keycount;
#define KEYBOARD_BUFFER_SIZE 16
static short keybuffer[KEYBOARD_BUFFER_SIZE];
static int modifiers;

static const char *countries[36][2] =
{
    { "not supported", "us" },
    { "Arabic", "ae" },
    { "Belgian", "be" },
    { "Canadian-Bilingual", "ca" },
    { "Canadian-French", "ca" },
    { "Czech Republic", "cz" },
    { "Danish", "dk" },
    { "Finnish", "fi" },
    { "French", "fr" },
    { "German", "de" },
    { "Greek", "gr" },
    { "Hebrew", "il" },
    { "Hungary", "hu" },
    { "International (ISO)", "iso" },
    { "Italian", "it" },
    { "Japan (Katakana)", "jp" },
    { "Korean", "us" },
    { "Latin American", "us" },
    { "Netherlands/Dutch", "nl" },
    { "Norwegian", "no" },
    { "Persian (Farsi)", "ir" },
    { "Poland", "pl" },
    { "Portuguese", "pt" },
    { "Russia", "ru" },
    { "Slovakia", "sl" },
    { "Spanish", "es" },
    { "Swedish", "se" },
    { "Swiss/French", "ch" },
    { "Swiss/German", "ch" },
    { "Switzerland", "ch" },
    { "Taiwan", "tw" },
    { "Turkish-Q", "tr" },
    { "UK", "uk" },
    { "US", "us" },
    { "Yugoslavia", "yu" },
    { "Turkish-F", "tr" },
    /* 36 - 255: Reserved */
};

struct FUsbHidLayoutMaps
{
    const char *country;
    const short map[4][0x80];
};

static const struct FUsbHidLayoutMaps *map;

static const struct FUsbHidLayoutMaps keyboard_layouts[] =
{
    {
        .country = "us",
        .map = {
            { /* No modifier */
                -1, -1, -1, -1, 'a', 'b', 'c', 'd',
                    'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
                    /* 0x10 */
                    'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
                    'u', 'v', 'w', 'x', 'y', 'z', '1', '2',
                    /* 0x20 */
                    '3', '4', '5', '6', '7', '8', '9', '0',
                    '\n', '\e', '\b', '\t', ' ', '-', '=', '[',
                    /* 0x30 */
                    ']', '\\', -1, ';', '\'', '`', ',', '.',
                    '/', -1 /* CapsLk */, KEY_F(1), KEY_F(2), KEY_F(3), KEY_F(4), KEY_F(5), KEY_F(6),
                    /* 0x40 */
                    KEY_F(7), KEY_F(8), KEY_F(9), KEY_F(10), KEY_F(11), KEY_F(12), KEY_PRINT, -1 /* ScrLk */,
                    KEY_BREAK, KEY_IC, KEY_HOME, KEY_PPAGE, KEY_DC, KEY_END, KEY_NPAGE, KEY_RIGHT,
                    /* 50 */
                    KEY_LEFT, KEY_DOWN, KEY_UP, -1 /*NumLck*/, '/', '*', '-' /* = ? */, '+',
                    KEY_ENTER, KEY_END, KEY_DOWN, KEY_NPAGE, KEY_LEFT, -1, KEY_RIGHT, KEY_HOME,
                    /* 60 */
                    KEY_UP, KEY_PPAGE, -1, KEY_DC, -1 /* < > | */, -1 /* Win Key Right */, -1, -1,
                    -1, -1, -1, -1, -1, -1, -1, -1,
                    /* 70 */
                    -1, -1, -1, -1, -1, -1, -1, -1,
                    -1, -1, -1, -1, -1, -1, -1, -1,
                },
            { /* Shift modifier */
                -1, -1, -1, -1, 'A', 'B', 'C', 'D',
                    'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
                    /* 0x10 */
                    'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
                    'U', 'V', 'W', 'X', 'Y', 'Z', '!', '@',
                    /* 0x20 */
                    '#', '$', '%', '^', '&', '*', '(', ')',
                    '\n', '\e', '\b', '\t', ' ', '_', '+', '[',
                    /* 0x30 */
                    ']', '\\', -1, ':', '\'', '`', ',', '.',
                    '/', -1 /* CapsLk */, KEY_F(1), KEY_F(2), KEY_F(3), KEY_F(4), KEY_F(5), KEY_F(6),
                    /* 0x40 */
                    KEY_F(7), KEY_F(8), KEY_F(9), KEY_F(10), KEY_F(11), KEY_F(12), KEY_PRINT, -1 /* ScrLk */,
                    KEY_BREAK, KEY_IC, KEY_HOME, KEY_PPAGE, KEY_DC, KEY_END, KEY_NPAGE, KEY_RIGHT,
                    /* 50 */
                    KEY_LEFT, KEY_DOWN, KEY_UP, -1 /*NumLck*/, '/', '*', '-' /* = ? */, '+',
                    KEY_ENTER, KEY_END, KEY_DOWN, KEY_NPAGE, KEY_LEFT, -1, KEY_RIGHT, KEY_HOME,
                    /* 60 */
                    KEY_UP, KEY_PPAGE, -1, KEY_DC, -1 /* < > | */, -1 /* Win Key Right */, -1, -1,
                    -1, -1, -1, -1, -1, -1, -1, -1,
                    /* 70 */
                    -1, -1, -1, -1, -1, -1, -1, -1,
                    -1, -1, -1, -1, -1, -1, -1, -1,
                },
            { /* Alt */
                -1, -1, -1, -1, 'a', 'b', 'c', 'd',
                    'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
                    /* 0x10 */
                    'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
                    'u', 'v', 'w', 'x', 'y', 'z', '1', '2',
                    /* 0x20 */
                    '3', '4', '5', '6', '7', '8', '9', '0',
                    '\n', '\e', '\b', '\t', ' ', '-', '=', '[',
                    /* 0x30 */
                    ']', '\\', -1, ';', '\'', '`', ',', '.',
                    '/', -1 /* CapsLk */, KEY_F(1), KEY_F(2), KEY_F(3), KEY_F(4), KEY_F(5), KEY_F(6),
                    /* 0x40 */
                    KEY_F(7), KEY_F(8), KEY_F(9), KEY_F(10), KEY_F(11), KEY_F(12), KEY_PRINT, -1 /* ScrLk */,
                    KEY_BREAK, KEY_IC, KEY_HOME, KEY_PPAGE, KEY_DC, KEY_END, KEY_NPAGE, KEY_RIGHT,
                    /* 50 */
                    KEY_LEFT, KEY_DOWN, KEY_UP, -1 /*NumLck*/, '/', '*', '-' /* = ? */, '+',
                    KEY_ENTER, KEY_END, KEY_DOWN, KEY_NPAGE, KEY_LEFT, -1, KEY_RIGHT, KEY_HOME,
                    /* 60 */
                    KEY_UP, KEY_PPAGE, -1, KEY_DC, -1 /* < > | */, -1 /* Win Key Right */, -1, -1,
                    -1, -1, -1, -1, -1, -1, -1, -1,
                    /* 70 */
                    -1, -1, -1, -1, -1, -1, -1, -1,
                    -1, -1, -1, -1, -1, -1, -1, -1,
                },
            { /* Shift+Alt modifier */
                -1, -1, -1, -1, 'A', 'B', 'C', 'D',
                    'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
                    /* 0x10 */
                    'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
                    'U', 'V', 'W', 'X', 'Y', 'Z', '!', '@',
                    /* 0x20 */
                    '#', '$', '%', '^', '&', '*', '(', ')',
                    '\n', '\e', '\b', '\t', ' ', '-', '=', '[',
                    /* 0x30 */
                    ']', '\\', -1, ':', '\'', '`', ',', '.',
                    '/', -1 /* CapsLk */, KEY_F(1), KEY_F(2), KEY_F(3), KEY_F(4), KEY_F(5), KEY_F(6),
                    /* 0x40 */
                    KEY_F(7), KEY_F(8), KEY_F(9), KEY_F(10), KEY_F(11), KEY_F(12), KEY_PRINT, -1 /* ScrLk */,
                    KEY_BREAK, KEY_IC, KEY_HOME, KEY_PPAGE, KEY_DC, KEY_END, KEY_NPAGE, KEY_RIGHT,
                    /* 50 */
                    KEY_LEFT, KEY_DOWN, KEY_UP, -1 /*NumLck*/, '/', '*', '-' /* = ? */, '+',
                    KEY_ENTER, KEY_END, KEY_DOWN, KEY_NPAGE, KEY_LEFT, -1, KEY_RIGHT, KEY_HOME,
                    /* 60 */
                    KEY_UP, KEY_PPAGE, -1, KEY_DC, -1 /* < > | */, -1 /* Win Key Right */, -1, -1,
                    -1, -1, -1, -1, -1, -1, -1, -1,
                    /* 70 */
                    -1, -1, -1, -1, -1, -1, -1, -1,
                    -1, -1, -1, -1, -1, -1, -1, -1,
                }
        }
    },
};

static void FUsbHidKeyboardQueue(int ch)
{
    /* ignore key presses if buffer full */
    if (keycount < KEYBOARD_BUFFER_SIZE)
    {
        keybuffer[keycount++] = ch;
    }
}

/* handle hid received data */
static void FUsbHidProcessKeyboardEvent(FUsbHid *const inst,
                                        const FUsbHidKeyboardEvent *const current)
{
    const FUsbHidKeyboardEvent *const previous = &inst->previous;

    int i, keypress = 0;

    modifiers = 0;

    if (current->modifiers & 0x01) /* Left-Ctrl */
    {
        modifiers |= KB_MOD_CTRL;
    }
    if (current->modifiers & 0x02) /* Left-Shift */
    {
        modifiers |= KB_MOD_SHIFT;
    }
    if (current->modifiers & 0x04) /* Left-Alt */
    {
        modifiers |= KB_MOD_ALT;
    }
    if (current->modifiers & 0x08) /* Left-GUI */
    {

    }

    if (current->modifiers & 0x10) /* Right-Ctrl */
    {
        modifiers |= KB_MOD_CTRL;
    }
    if (current->modifiers & 0x20) /* Right-Shift */
    {
        modifiers |= KB_MOD_SHIFT;
    }
    if (current->modifiers & 0x40) /* Right-AltGr */
    {
        modifiers |= KB_MOD_ALT;
    }
    if (current->modifiers & 0x80) /* Right-GUI */
    {

    }

    if ((current->modifiers & 0x05) && ((current->keys[0] == 0x4c) ||
                                        (current->keys[0] == 0x63)))
    {
        /* todo, Reboot here */
    }

    /* Did the event change at all? */
    if (inst->lastkeypress &&
        !memcmp(current, previous, sizeof(*current)))
    {
        /* No. Then it's a key repeat event. */
        if (inst->repeat_delay)
        {
            inst->repeat_delay--;
        }
        else
        {
            FUsbHidKeyboardQueue(inst->lastkeypress);
            inst->repeat_delay = REPEAT_DELAY;
        }

        return;
    }

    inst->lastkeypress = 0;

    for (i = 0; i < 6; i++)
    {
        int j;
        int skip = 0;
        /* No more keys? skip */
        if (current->keys[i] == 0)
        {
            return;
        }

        for (j = 0; j < 6; j++)
        {
            if (current->keys[i] == previous->keys[j])
            {
                skip = 1;
                break;
            }
        }

        if (skip)
        {
            continue;
        }

        /* Mask off KB_MOD_CTRL */
        keypress = map->map[modifiers & 0x03][current->keys[i]];

        if (modifiers & KB_MOD_CTRL)
        {
            switch (keypress)
            {
                case 'a' ... 'z':
                    keypress &= 0x1f;
                    break;
                default:
                    continue;
            }
        }

        if (keypress == -1)
        {
            /* Debug: Print unknown keys */
            FUSB_INFO("usbhid: <%x> %x [ %x %x %x %x %x %x ] %d\n",
                      current->modifiers, current->repeats,
                      current->keys[0], current->keys[1],
                      current->keys[2], current->keys[3],
                      current->keys[4], current->keys[5], i);

            /* Unknown key? Try next one in the queue */
            continue;
        }

        FUsbHidKeyboardQueue(keypress);

        /* Remember for authentic key repeat */
        inst->lastkeypress = keypress;
        inst->repeat_delay = INITIAL_REPEAT_DELAY;
    }
}

static void FUsbHidPoll(FUsbDev *dev)
{
    FUsbHidKeyboardEvent current;
    const u8 *buf;

    while ((buf = dev->controller->poll_intr_queue(FUSB_HID_INST(dev)->queue)))
    {
        memcpy(&current.buffer, buf, 8);
        FUsbHidProcessKeyboardEvent(FUSB_HID_INST(dev), &current);
        FUSB_HID_INST(dev)->previous = current;
    }
}

static void FUsbHidSetIdle(FUsbDev *dev, FUsbInterfaceDescriptor *interface, u16 duration)
{
    FUsbDevReq dr;
    dr.data_dir = FUSB_REQ_HOST_TO_DEVICE;
    dr.req_type = FUSB_REQ_TYPE_CLASS;
    dr.req_recp = FUSB_REQ_RECP_IF;
    dr.bRequest = SET_IDLE;
    dr.wValue = (duration >> 2) << 8;
    dr.wIndex = interface->bInterfaceNumber;
    dr.wLength = 0;
    dev->controller->control(dev, FUSB_OUT, sizeof(FUsbDevReq), &dr, 0, NULL);
}

static void FUsbHidSetProtocol(FUsbDev *dev, FUsbInterfaceDescriptor *interface, FUsbHidProtocol proto)
{
    FUsbDevReq dr;
    dr.data_dir = FUSB_REQ_HOST_TO_DEVICE;
    dr.req_type = FUSB_REQ_TYPE_CLASS;
    dr.req_recp = FUSB_REQ_RECP_IF;
    dr.bRequest = SET_PROTOCOL;
    dr.wValue = proto;
    dr.wIndex = interface->bInterfaceNumber;
    dr.wLength = 0;
    dev->controller->control(dev, FUSB_OUT, sizeof(FUsbDevReq), &dr, 0, 0);
}

static int FUsbHidSetLayout(const char *country)
{
    /* FIXME should be per keyboard */
    for (fsize_t i = 0; i < ARRAY_SIZE(keyboard_layouts); i++)
    {
        if (strncmp(keyboard_layouts[i].country, country,
                    strlen(keyboard_layouts[i].country)))
        {
            continue;
        }

        /* Found, changing keyboard layout */
        map = &keyboard_layouts[i];
        FUSB_DEBUG("  Keyboard layout '%s'\n", map->country);
        return 0;
    }

    FUSB_DEBUG("  Keyboard layout '%s' not found, using '%s'\n",
               country, map->country);

    /* Nothing found, not changed */
    return -1;
}

void FUsbHidInit(FUsbDev *dev)
{
    FUsb *instance = dev->controller->usb;

    FUsbConfigurationDescriptor *cd = (FUsbConfigurationDescriptor *)dev->configuration;
    FUsbInterfaceDescriptor *interface = (FUsbInterfaceDescriptor *)(((char *) cd) + cd->bLength);

    if (interface->bInterfaceSubClass == FUSB_HID_SUBCLASS_BOOT)
    {
        u8 countrycode;
        FUSB_DEBUG("  supports boot interface..\n");
        FUSB_DEBUG("  it's a %s\n",
                   boot_protos[interface->bInterfaceProtocol]);
        switch (interface->bInterfaceProtocol)
        {
            case FUSB_HID_BOOT_PROTOCOL_KEYBOARD:
                dev->data = FUSB_ALLOCATE(instance, sizeof(FUsbHid), FUSB_DEFAULT_ALIGN);
                FUSB_DEBUG("  configuring...\n");
                FUsbHidSetProtocol(dev, interface, FUSB_HID_PROTOCOL_BOOT);
                FUsbHidSetIdle(dev, interface, KEYBOARD_REPEAT_MS);
                FUSB_DEBUG("  activating...\n");

                FUsbHidDescriptor *desc = FUSB_ALLOCATE(instance, sizeof(FUsbHidDescriptor), FUSB_DEFAULT_ALIGN);
                if (!desc || FUsbGetDescriptor(dev, FUsbGenerateReqType(
                                                   FUSB_REQ_DEVICE_TO_HOST, FUSB_REQ_TYPE_STANDARD, FUSB_REQ_RECP_IF),
                                               0x21, 0, desc, sizeof(*desc)) != sizeof(*desc))
                {
                    FUSB_DEBUG("FUsbGetDescriptor(HID) failed\n");
                    FUsbDetachDev(dev->controller, dev->address);
                    return;
                }
                FUSB_HID_INST(dev)->descriptor = desc;
                countrycode = desc->bCountryCode;
                /* 35 countries defined: */
                if (countrycode >= ARRAY_SIZE(countries))
                {
                    countrycode = 0;
                }
                FUSB_INFO("  Keyboard has %s layout (country code %02x)\n",
                       countries[countrycode][0], countrycode);

                /* Set keyboard layout accordingly */
                FUsbHidSetLayout(countries[countrycode][1]);

                // only add here, because we only support boot-keyboard HID devices
                dev->destroy = FUsbHidDestory;
                dev->poll = FUsbHidPoll;
                int i;
                for (i = 1; i < dev->num_endp; i++)
                {
                    if (dev->endpoints[i].type != FUSB_INTERRUPT_EP)
                    {
                        continue;
                    }
                    if (dev->endpoints[i].direction != FUSB_IN)
                    {
                        continue;
                    }
                    break;
                }

                if (i >= dev->num_endp)
                {
                    FUSB_DEBUG("Could not find HID endpoint\n");
                    FUsbDetachDev(dev->controller, dev->address);
                    return;
                }

                FUSB_DEBUG("  found endpoint %x for interrupt-in\n", i);
                /* 20 buffers of 8 bytes, for every 10 msecs */
                FUSB_HID_INST(dev)->queue = dev->controller->create_intr_queue(&dev->endpoints[i], 8, 20, 10);
                keycount = 0;
                FUSB_DEBUG("  configuration done.\n");
                break;
            case FUSB_HID_BOOT_PROTOCOL_MOUSE:
                FUSB_DEBUG("NOTICE: USB mice are not supported.\n");
                break;
        }
    }
}

int FUsbHidCheckInput(FUsbDev *dev, int times)
{
    short ret;
    FUsb *instance = dev->controller->usb;

    for (int i = 0; i < times; i++)
    {
        FUsbPoll(instance);

        while (keycount != 0)
        {
            ret = keybuffer[0];
            memmove(keybuffer, keybuffer + 1, --keycount);
            FUSB_INFO("%c", ret);
        }

        fsleep_millisec(10);
    }

    FUSB_INFO("\r\n");
}