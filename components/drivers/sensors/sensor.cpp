#include <stddef.h>
#include "sensor.h"

/**
 * Sensor
 */
Sensor::Sensor()
{
    this->next = this->prev = NULL;
    Subscribe(NULL, NULL);
}

Sensor::~Sensor()
{
}

int Sensor::GetType(void)
{
    return this->type;
}

int Sensor::Subscribe(SensorEventHandler_t *handler, void *user_data)
{
    this->evtHandler = handler;
    this->userData = user_data;

    return 0;
}

int Sensor::Publish(sensors_event_t *event)
{
    if (this->evtHandler != NULL)
    {
        /* invoke subscribed handler */
        (*evtHandler)(this, event, this->userData);
    }

    return 0;
}

/**
 * Sensor Manager
 */
/* sensor manager instance */
static SensorManager _sensor_manager;

SensorManager::SensorManager()
{
    sensorList = NULL;
}

SensorManager::~SensorManager()
{
}

int SensorManager::RegisterSensor(Sensor *sensor)
{
    SensorManager *self = &_sensor_manager;

    RT_ASSERT(sensor != RT_NULL);

    /* add sensor into the list */
    if (self->sensorList = NULL)
    {
        sensor->prev = sensor->next = sensor;
    }
    else
    {
        sensor->prev = self->sensorList;
        sensor->next = self->sensorList->next;

        self->sensorList->next->prev = sensor;
        self->sensorList->next = sensor;
    }

    /* point the sensorList to this sensor */
    self->sensorList = sensor;

    return 0;
}

int SensorManager::DeregisterSensor(Sensor *sensor)
{
    SensorManager *self = &_sensor_manager;

    /* disconnect sensor list */
    sensor->next->prev = sensor->prev;
    sensor->prev->next = sensor->next;

    /* check the sensorList */
    if (sensor == self->sensorList)
    {
        if (sensor->next == sensor) self->sensorList = NULL; /* empty list */
        else self->sensorList = sensor->next;
    }

    /* re-initialize sensor node */
    sensor->next = sensor->prev = sensor;

    return 0;
}

Sensor *SensorManager::GetDefaultSensor(int type)
{
    SensorManager *self = &_sensor_manager;
    Sensor *sensor = self->sensorList;

    if (sensor == NULL) return NULL;

    do
    {
        /* find the same type */
        if (sensor->GetType() == type) return sensor;

        sensor = sensor->next;
    }
    while (sensor != self->sensorList);

    return NULL;
}

int SensorManager::Subscribe(int type, SensorEventHandler_t *handler, void *user_data)
{
    Sensor *sensor;

    sensor = SensorManager::GetDefaultSensor(type);
    if (sensor != NULL)
    {
        sensor->Subscribe(handler, user_data);
        return 0;
    }

    return -1;
}

