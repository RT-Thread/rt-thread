/*
 * Copyright (c) 2006-2026 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef GD32VW553_MQTT_DEMO_H
#define GD32VW553_MQTT_DEMO_H

#include <rtthread.h>

typedef void (*gd32vw553_mqtt_receive_callback_t)(const char *topic,
                                                   const void *payload,
                                                   rt_size_t payload_length);
typedef void (*gd32vw553_mqtt_status_callback_t)(const char *status,
                                                  int result);

int gd32vw553_mqtt_demo_start(void);
int gd32vw553_mqtt_demo_publish(const char *topic, const char *payload);
int gd32vw553_mqtt_demo_stop(void);
rt_bool_t gd32vw553_mqtt_demo_is_running(void);
rt_bool_t gd32vw553_mqtt_demo_is_connected(void);
void gd32vw553_mqtt_demo_set_receive_callback(
    gd32vw553_mqtt_receive_callback_t callback);
void gd32vw553_mqtt_demo_set_status_callback(
    gd32vw553_mqtt_status_callback_t callback);

#endif /* GD32VW553_MQTT_DEMO_H */
