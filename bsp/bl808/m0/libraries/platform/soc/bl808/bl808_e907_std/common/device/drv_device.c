/**
 * @file drv_device.c
 *
 * Copyright (c) 2021 Bouffalolab team
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 */
#include "drv_device.h"

#define DEVICE_CHECK_PARAM

#define dev_open    (dev->open)
#define dev_close   (dev->close)
#define dev_read    (dev->read)
#define dev_write   (dev->write)
#define dev_control (dev->control)

dlist_t device_head = DLIST_OBJECT_INIT(device_head);

/**
 * This function get device list header
 *
 * @param None
 *
 * @return device header
 */
dlist_t *device_get_list_header(void)
{
    return &device_head;
}

/**
 * This function registers a device driver with specified name.
 *
 * @param dev the pointer of device driver structure
 * @param name the device driver's name
 * @param flags the capabilities flag of device
 *
 * @return the error code, DEVICE_EOK on initialization successfully.
 */
int device_register(struct device *dev, const char *name)
{
    dlist_t *node;

    dlist_for_each(node, &device_head)
    {
        struct device *dev_obj;
        dev_obj = dlist_entry(node, struct device, list);

        if (dev_obj == dev) {
            return -DEVICE_EEXIST;
        }
    }

    strcpy(dev->name, name);

    dlist_insert_after(&device_head, &(dev->list));
    dev->status = DEVICE_REGISTERED;
    return DEVICE_EOK;
}

/**
 * This function unregisters a device driver with specified name.
 *
 * @param dev the pointer of device driver structure
 * @param name the device driver's name
 * @param flags the capabilities flag of device
 *
 * @return the error code, DEVICE_EOK on initialization successfully.
 */
int device_unregister(const char *name)
{
    struct device *dev = device_find(name);

    if (!dev) {
        return -DEVICE_ENODEV;
    }
    dev->status = DEVICE_UNREGISTER;
    /* remove from old list */
    dlist_remove(&(dev->list));
    return DEVICE_EOK;
}

/**
 * This function finds a device driver by specified name.
 *
 * @param name the device driver's name
 *
 * @return the registered device driver on successful, or NULL on failure.
 */
struct device *device_find(const char *name)
{
    struct device *dev;
    dlist_t *node;

    dlist_for_each(node, &device_head)
    {
        dev = dlist_entry(node, struct device, list);

        if (strncmp(dev->name, name, DEVICE_NAME_MAX) == 0) {
            return dev;
        }
    }
    return NULL;
}

/**
 * This function will open a device
 *
 * @param dev the pointer of device driver structure
 * @param oflag the flags for device open
 *
 * @return the result
 */
int device_open(struct device *dev, uint16_t oflag)
{
#ifdef DEVICE_CHECK_PARAM
    int retval = DEVICE_EOK;

    if ((dev->status == DEVICE_REGISTERED) || (dev->status == DEVICE_CLOSED)) {
        if (dev_open != NULL) {
            retval = dev_open(dev, oflag);
            dev->status = DEVICE_OPENED;
            dev->oflag |= oflag;
        } else {
            retval = -DEVICE_EFAULT;
        }
    } else {
        retval = -DEVICE_EINVAL;
    }

    return retval;
#else
    return dev_open(dev, oflag);
#endif
}
/**
 * This function will close a device
 *
 * @param dev the pointer of device driver structure
 *
 * @return the result
 */
int device_close(struct device *dev)
{
#ifdef DEVICE_CHECK_PARAM
    int retval = DEVICE_EOK;

    if (dev->status == DEVICE_OPENED) {
        if (dev_close != NULL) {
            retval = dev_close(dev);
            dev->status = DEVICE_CLOSED;
            dev->oflag = 0;
        } else {
            retval = -DEVICE_EFAULT;
        }
    } else {
        retval = -DEVICE_EINVAL;
    }

    return retval;
#else
    return dev_close(dev);
#endif
}
/**
 * This function will perform a variety of control functions on devices.
 *
 * @param dev the pointer of device driver structure
 * @param cmd the command sent to device
 * @param arg the argument of command
 *
 * @return the result
 */
int device_control(struct device *dev, int cmd, void *args)
{
#ifdef DEVICE_CHECK_PARAM
    int retval = DEVICE_EOK;

    if (dev->status > DEVICE_UNREGISTER) {
        if (dev_control != NULL) {
            retval = dev_control(dev, cmd, args);
        } else {
            retval = -DEVICE_EFAULT;
        }
    } else {
        retval = -DEVICE_EINVAL;
    }

    return retval;
#else
    return dev_control(dev, cmd, args);
#endif
}
/**
 * This function will write some data to a device.
 *
 * @param dev the pointer of device driver structure
 * @param pos the position of written
 * @param buffer the data buffer to be written to device
 * @param size the size of buffer
 *
 * @return the actually written size on successful, otherwise negative returned.
 */
int device_write(struct device *dev, uint32_t pos, const void *buffer, uint32_t size)
{
#ifdef DEVICE_CHECK_PARAM
    int retval = DEVICE_EOK;

    if (dev->status == DEVICE_OPENED) {
        if (dev_write != NULL) {
            retval = dev_write(dev, pos, buffer, size);
        } else {
            retval = -DEVICE_EFAULT;
        }
    } else {
        retval = -DEVICE_EINVAL;
    }

    return retval;
#else
    return dev_write(dev, pos, buffer, size);
#endif
}
/**
 * This function will read some data from a device.
 *
 * @param dev the pointer of device driver structure
 * @param pos the position of reading
 * @param buffer the data buffer to save read data
 * @param size the size of buffer
 *
 * @return the actually read size on successful, otherwise negative returned.
 */
int device_read(struct device *dev, uint32_t pos, void *buffer, uint32_t size)
{
#ifdef DEVICE_CHECK_PARAM
    int retval = DEVICE_EOK;

    if (dev->status == DEVICE_OPENED) {
        if (dev_read != NULL) {
            retval = dev_read(dev, pos, buffer, size);
        } else {
            retval = -DEVICE_EFAULT;
        }
    } else {
        retval = -DEVICE_EINVAL;
    }

    return retval;
#else
    return dev_read(dev, pos, buffer, size);
#endif
}
/**
 * This function will read some data from a device.
 *
 * @param dev the pointer of device driver structure
 * @param pos the position of reading
 * @param buffer the data buffer to save read data
 * @param size the size of buffer
 *
 * @return the actually read size on successful, otherwise negative returned.
 */
int device_set_callback(struct device *dev, void (*callback)(struct device *dev, void *args, uint32_t size, uint32_t event))
{
    int retval = DEVICE_EOK;

    if (dev->status > DEVICE_UNREGISTER) {
        if (callback != NULL) {
            dev->callback = callback;
        } else {
            retval = -DEVICE_EFAULT;
        }
    } else {
        retval = -DEVICE_EINVAL;
    }

    return retval;
}