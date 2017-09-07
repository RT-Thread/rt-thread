/*
 * File      : sensors.cpp
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2014, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2014-08-03     Bernard      the first version
 */

#include <stddef.h>
#include <string.h>

#include "sensor.h"

/**
 * SensorBase
 */
SensorBase::SensorBase(int type)
{
    memset(&(this->config), 0x0, sizeof(SensorConfig));

    this->type = type;
    this->next = this->prev = NULL;
    subscribe(NULL, NULL);
}

SensorBase::~SensorBase()
{
}

int SensorBase::getType(void)
{
    return this->type;
}

int SensorBase::setConfig(SensorConfig *config)
{
    int result;

    /* configure to the low level sensor */
    result = this->configure(config);
    if (result == 0)
    {
        this->config = *config;
    }

    return result;
}

int SensorBase::getConfig(SensorConfig *config)
{
    *config = this->config;
    return 0;
}

int SensorBase::subscribe(SensorEventHandler_t handler, void *user_data)
{
    this->evtHandler = handler;
    this->userData = user_data;

    return 0;
}

int SensorBase::publish(void)
{
    if (this->evtHandler != NULL)
    {
        /* invoke subscribed handler */
        (*evtHandler)(this->userData);
    }

    return 0;
}

/**
 * Sensor Manager
 */
/* sensors list */
static SensorBase *sensor_list = NULL;

SensorManager::SensorManager()
{
}

SensorManager::~SensorManager()
{
}

int SensorManager::registerSensor(SensorBase *sensor)
{
    RT_ASSERT(sensor != RT_NULL);

    /* add sensor into the list */
    if (sensor_list == NULL)
    {
        sensor->prev = sensor->next = sensor;
    }
    else
    {
        sensor_list->prev->next = sensor;
        sensor->prev = sensor_list->prev;

        sensor_list->prev = sensor;
        sensor->next = sensor_list;
    }

    /* point the sensorList to this sensor */
    sensor_list = sensor;

    return 0;
}

int SensorManager::unregisterSensor(SensorBase *sensor)
{
    /* disconnect sensor list */
    sensor->next->prev = sensor->prev;
    sensor->prev->next = sensor->next;

    /* check the sensorList */
    if (sensor == sensor_list)
    {
        if (sensor->next == sensor) sensor_list = NULL; /* empty list */
        else sensor_list = sensor->next;
    }

    /* re-initialize sensor node */
    sensor->next = sensor->prev = sensor;

    return 0;
}

SensorBase *SensorManager::getDefaultSensor(int type)
{
    SensorBase *sensor = sensor_list;

    if (sensor == NULL) return NULL;

    do
    {
        /* find the same type */
        if (sensor->getType() == type) return sensor;

        sensor = sensor->next;
    }while (sensor != sensor_list);

    return NULL;
}

int SensorManager::subscribe(int type, SensorEventHandler_t handler, void *user_data)
{
    SensorBase *sensor;

    sensor = SensorManager::getDefaultSensor(type);
    if (sensor != NULL)
    {
        sensor->subscribe(handler, user_data);
        return 0;
    }

    return -1;
}

int SensorManager::sensorEventReady(SensorBase *sensor)
{
    return 0;
}

int SensorManager::pollSensor(SensorBase *sensor, sensors_event_t *events, int number, int duration)
{
    rt_tick_t tick;
    int result, index;

    if (sensor == NULL) return -1;

    tick = rt_tick_get();
    for (index = 0; index < number; index ++)
    {
        result = sensor->poll(&events[index]);
        if (result < 0) break;

        if (rt_tick_get() - tick > duration) break;
    }

    return index;
}

rt_sensor_t rt_sensor_get_default(int type)
{
    return (rt_sensor_t)SensorManager::getDefaultSensor(type);
}

int rt_sensor_subscribe(rt_sensor_t sensor, SensorEventHandler_t handler, void *user_data)
{
    SensorBase *sensor_base;
    if (sensor == NULL) return -1;

    sensor_base = (SensorBase*)sensor;

    return sensor_base->subscribe(handler, user_data);
}

int rt_sensor_poll(rt_sensor_t sensor, sensors_event_t *event)
{
    SensorBase *sensor_base;
    if (sensor == NULL || event == NULL) return -1;

    sensor_base = (SensorBase*)sensor;
    return sensor_base->poll(event);
}

int rt_sensor_configure(rt_sensor_t sensor, SensorConfig *config)
{
    SensorBase *sensor_base;
    if (sensor == NULL || config == NULL) return -1;

    sensor_base = (SensorBase*)sensor;
    return sensor_base->setConfig(config);
}

int rt_sensor_activate(rt_sensor_t sensor, int enable)
{
    SensorBase *sensor_base;
    if (sensor == NULL) return -1;
    
    sensor_base = (SensorBase*)sensor;
    return sensor_base->activate(enable);
}
