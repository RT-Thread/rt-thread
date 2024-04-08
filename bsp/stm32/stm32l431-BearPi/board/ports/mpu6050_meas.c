/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-19     liYony       first version
 */

#include <rtthread.h>
#include "mpu6xxx.h"

#define DBG_TAG "mpu6050"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

#define MPU6050_DEVICE_NAME  "i2c1"

#ifdef BSP_USING_MQTT_HW_CLOUD
#include "mqttclient.h"
#include <netdev_ipaddr.h>
#include <netdev.h>
#include <cJSON.h>

#ifndef KAWAII_MQTT_HOST
#define KAWAII_MQTT_HOST "jiejie01.top"
#endif
#ifndef KAWAII_MQTT_PORT
#define KAWAII_MQTT_PORT "1883"
#endif
#ifndef KAWAII_MQTT_CLIENTID
#define KAWAII_MQTT_CLIENTID "rtthread001"
#endif
#ifndef KAWAII_MQTT_USERNAME
#define KAWAII_MQTT_USERNAME "rt-thread"
#endif
#ifndef KAWAII_MQTT_PASSWORD
#define KAWAII_MQTT_PASSWORD "rt-thread"
#endif
#ifndef KAWAII_MQTT_SUBTOPIC
#define KAWAII_MQTT_SUBTOPIC "rtt-sub"
#endif
#ifndef KAWAII_MQTT_PUBTOPIC
#define KAWAII_MQTT_PUBTOPIC "rtt-pub"
#endif

static char payload_buf[256];///////////////////////
static rt_bool_t is_upload = RT_TRUE;

static void mqtt_subscribe_handle(void *client, message_data_t *msg)
{
    (void)client;
    KAWAII_MQTT_LOG_I("-----------------------------------------------------------------------------------");
    KAWAII_MQTT_LOG_I("%s:%d %s()...\ntopic: %s\nmessage:%s", __FILE__, __LINE__, __FUNCTION__, msg->topic_name, (char *)msg->message->payload);
    KAWAII_MQTT_LOG_I("-----------------------------------------------------------------------------------");

    cJSON* json_data = RT_NULL;
    cJSON* json_upload = RT_NULL;
    json_data = cJSON_Parse((char *)msg->message->payload);
    if (json_data == RT_NULL)
    {
        return;
    }
    json_upload = cJSON_GetObjectItem(json_data, "paras");
    json_upload = cJSON_GetObjectItem(json_upload, "upload_bool");

    if (json_upload->valueint == RT_TRUE)
    {
        is_upload = RT_TRUE;
        LOG_I("start upload.");
    }
    else
    {
        is_upload = RT_FALSE;
        LOG_I("stop upload.");
    }

}

static int mqtt_publish_handle(mqtt_client_t *client, void *payload)
{
    mqtt_message_t msg;
    memset(&msg, 0, sizeof(msg));

    msg.qos = QOS1;
    msg.payload = payload;

    return mqtt_publish(client, KAWAII_MQTT_PUBTOPIC, &msg);
}
#endif /* BSP_USING_MQTT_HW_CLOUD */

static void mpu6050_accel_entry(void *parameter)
{
    struct mpu6xxx_device *dev;
    struct mpu6xxx_3axes accel;

    /* Initialize mpu6050, The parameter is RT_NULL, means auto probing for i2c*/
    dev = mpu6xxx_init(MPU6050_DEVICE_NAME, RT_NULL);

    if (dev == RT_NULL)
    {
        LOG_E("mpu6050 init failed.");
        return;
    }
    LOG_I("mpu6050 init succeed.");
#ifdef BSP_USING_MQTT_HW_CLOUD
    /* wait network init. */
    while(!netdev_get_first_by_flags(NETDEV_FLAG_INTERNET_UP))
    {
        rt_thread_mdelay(2);
    }

    LOG_I("network init succeed.");

    mqtt_log_init();
    mqtt_client_t *client = mqtt_lease();
    mqtt_set_host(client, KAWAII_MQTT_HOST);
    mqtt_set_port(client, KAWAII_MQTT_PORT);
    mqtt_set_user_name(client, KAWAII_MQTT_USERNAME);
    mqtt_set_password(client, KAWAII_MQTT_PASSWORD);
    mqtt_set_client_id(client, KAWAII_MQTT_CLIENTID);
    mqtt_set_clean_session(client, 1);

    KAWAII_MQTT_LOG_I("The ID of the Kawaii client is: %s ", KAWAII_MQTT_CLIENTID);

    mqtt_connect(client);
    mqtt_subscribe(client, KAWAII_MQTT_SUBTOPIC, QOS1, mqtt_subscribe_handle);
#endif /* BSP_USING_MQTT_HW_CLOUD */
    while(1)
    {
        mpu6xxx_get_accel(dev, &accel);

#ifdef BSP_USING_MQTT_HW_CLOUD
        if (is_upload == RT_TRUE)
        {
            rt_sprintf(payload_buf, "{\"services\":[{\"service_id\":\"mpu6050\",\"properties\":{\"accel_x\":%3d,\"accel_y\":%3d,\"accel_z\":%3d}}]}", accel.x, accel.y, accel.z);
            mqtt_publish_handle(client, payload_buf);
        }
#endif /* BSP_USING_MQTT_HW_CLOUD */
        LOG_D("accel.x = %3d, accel.y = %3d, accel.z = %3d", accel.x, accel.y, accel.z);

        rt_thread_mdelay(1000);
    }
}

static int rt_hw_mpu6050_init()
{
    rt_thread_t tid_mpu;

    tid_mpu = rt_thread_create("mpu_accel", mpu6050_accel_entry, RT_NULL, 2048, 6, 10);
    if (tid_mpu == RT_NULL)
    {
        return -RT_ERROR;
    }

    rt_thread_startup(tid_mpu);

    return RT_EOK;
}

INIT_APP_EXPORT(rt_hw_mpu6050_init);
