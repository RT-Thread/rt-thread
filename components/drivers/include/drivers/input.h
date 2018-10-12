/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/*
 * File       : input.h
 *
 * Change Logs:
 * Date           Author        Notes
   2018-10-10     heyuanjie87   first version

 */

#ifndef __INPUT_H__
#define __INPUT_H__

#include <rtthread.h>
#include <stdint.h>

#include "input_ev_code.h"

typedef enum
{
    INPUT_DEVTYPE_KBD = 1,
    INPUT_DEVTYPE_TOUCH = 2,
} input_devtype_t;

struct input_event;
struct input_ops;
struct input_handler;

struct input_value
{
    uint8_t type;
    uint16_t code;
    int value;
};

typedef struct input_dev
{
    struct rt_device parent;
    const struct input_ops *ops;

    /* driver not  touch */
    uint8_t type; /* @input_devtype_t */
    struct input_value *buf;
    uint8_t wpos;
    uint8_t numbuf;

    struct input_handler *handler;
    rt_list_t node;
} rt_input_t;

struct input_ops
{
    int (*init)(rt_input_t *dev);
    void (*deinit)(rt_input_t *dev);
};

#pragma pack(1)
struct input_event
{
    uint16_t type;
    uint16_t code;
    int value;
    uint32_t usec;
};
#pragma pack()

struct input_handler
{
    struct rt_device parent;
    uint8_t type; /* @input_devtype_t */
    void (*events)(struct input_handler *handler, struct input_dev *dev,
                   struct input_value *v, int cnt);
    void (*disconnect)(struct input_handler *handler, struct input_dev *dev);

    rt_list_t node;
    rt_list_t c_list; /* clients connect to this list */
    rt_list_t d_list; /* input devices connect to this list */
};

int rt_input_device_register(rt_input_t *dev, int devtype, const char *name);
int rt_input_device_unregister(rt_input_t *dev);

int rt_input_handler_register(struct input_handler *handler, const char *name);
int rt_input_device_open(struct input_handler *h);
int rt_input_device_close(struct input_handler *h);

int rt_input_report(rt_input_t *dev, int type, int code, int value);
int rt_input_rel_report(rt_input_t *dev, int code, int value);
int rt_input_abs_report(rt_input_t *dev, int code, int value);
int rt_input_key_report(rt_input_t *dev, int code, int value);
int rt_input_sync(rt_input_t *dev);

#endif
