/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#ifndef __INPUT_UAPI_H__
#define __INPUT_UAPI_H__

#include <stdint.h>
#include <sys/time.h>
#include <sys/ioctl.h>

#include <dt-bindings/input/event-codes.h>

struct input_event
{
    struct timeval time;
    uint16_t type;
    uint16_t code;
    int32_t value;
};

#define EV_VERSION  0x010001

struct input_id
{
    uint16_t bustype;
    uint16_t vendor;
    uint16_t product;
    uint16_t version;
};

struct input_absinfo
{
    int32_t value;
    int32_t minimum;
    int32_t maximum;
    int32_t fuzz;
    int32_t flat;
    int32_t resolution;
};

/* Get driver version */
#define EVIOCGVERSION           _IOR('E', 0x01, int)
/* Get device ID */
#define EVIOCGID                _IOR('E', 0x02, struct input_id)

/* Get device name */
#define EVIOCGNAME(len)         _IOC(_IOC_READ, 'E', 0x06, len)
/* Get device properties */
#define EVIOCGPROP(len)         _IOC(_IOC_READ, 'E', 0x09, len)

/* Get event bits */
#define EVIOCGBIT(ev, len)      _IOC(_IOC_READ, 'E', 0x20 + (ev), len)

/* Get abs value/limits */
#define EVIOCGABS(abs)          _IOR('E', 0x40 + (abs), struct input_absinfo)

/* Grab/Release device */
#define EVIOCGRAB               _IOW('E', 0x90, int)

#endif /* __INPUT_UAPI_H__ */
