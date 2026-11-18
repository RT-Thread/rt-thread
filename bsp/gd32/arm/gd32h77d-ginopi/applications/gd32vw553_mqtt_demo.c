/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-09-03     CYFS         integrate synchronous MQTT controls over wifi0 with clean shutdown
 */
#include "rtconfig.h"
#if defined(BSP_USING_GD32VW553_MQTT_DEMO) && defined(PKG_USING_KAWAII_MQTT)

#include <rtthread.h>
#include <at_device.h>
#include <mqttclient.h>
#include <netdev.h>

#include "gd32vw553_mqtt_demo.h"

#ifndef GD32VW553_SAMPLE_DEVICE_NAME
#define GD32VW553_SAMPLE_DEVICE_NAME "wifi0"
#endif

#define GD32VW553_MQTT_ARG_LEN         64
#define GD32VW553_MQTT_TOPIC_LEN       64
#define GD32VW553_MQTT_MSG_LEN         256
#define GD32VW553_MQTT_STACK_SIZE      4096
#define GD32VW553_MQTT_PRIORITY        14
#define GD32VW553_MQTT_WIFI_WAIT_MS    45000
#define GD32VW553_MQTT_WIFI_LOG_MS     5000
#define GD32VW553_MQTT_CMD_TIMEOUT_MS  20000
#define GD32VW553_MQTT_STOP_TIMEOUT_MS 30000

#define GD32VW553_MQTT_STR_HELPER(x)   #x
#define GD32VW553_MQTT_STR(x)          GD32VW553_MQTT_STR_HELPER(x)

#ifndef BSP_GD32VW553_MQTT_HOST
#define BSP_GD32VW553_MQTT_HOST "broker.emqx.io"
#endif

#ifndef BSP_GD32VW553_MQTT_PORT
#define BSP_GD32VW553_MQTT_PORT 1883
#endif

#ifndef BSP_GD32VW553_MQTT_SUB_TOPIC
#define BSP_GD32VW553_MQTT_SUB_TOPIC "rtt/gd32vw553/sub"
#endif

#ifndef BSP_GD32VW553_MQTT_PUB_TOPIC
#define BSP_GD32VW553_MQTT_PUB_TOPIC "rtt/gd32vw553/pub"
#endif

#ifndef BSP_GD32VW553_MQTT_MESSAGE
#define BSP_GD32VW553_MQTT_MESSAGE "hello from GD32VW553"
#endif

#ifndef BSP_GD32VW553_MQTT_CLIENT_ID
#define BSP_GD32VW553_MQTT_CLIENT_ID "gd32vw553"
#endif

#ifndef BSP_GD32VW553_MQTT_USERNAME
#define BSP_GD32VW553_MQTT_USERNAME ""
#endif

#ifndef BSP_GD32VW553_MQTT_PASSWORD
#define BSP_GD32VW553_MQTT_PASSWORD ""
#endif

struct gd32vw553_mqtt_arg
{
    char host[GD32VW553_MQTT_ARG_LEN];
    char port[8];
    char sub_topic[GD32VW553_MQTT_TOPIC_LEN];
    char pub_topic[GD32VW553_MQTT_TOPIC_LEN];
    char message[GD32VW553_MQTT_MSG_LEN];
    char client_id[GD32VW553_MQTT_ARG_LEN];
    char username[GD32VW553_MQTT_ARG_LEN];
    char mqtt_password[GD32VW553_MQTT_ARG_LEN];
};

static mqtt_client_t *gd32vw553_mqtt_client = RT_NULL;
static rt_bool_t gd32vw553_mqtt_running = RT_FALSE;
static rt_mutex_t gd32vw553_mqtt_lock = RT_NULL;
static gd32vw553_mqtt_receive_callback_t gd32vw553_mqtt_receive_callback;
static gd32vw553_mqtt_status_callback_t gd32vw553_mqtt_status_callback;

static void gd32vw553_mqtt_report_status(const char *status, int result)
{
    gd32vw553_mqtt_status_callback_t callback;

    if (result == RT_EOK)
    {
        rt_kprintf("[mqtt] %s\n", status);
    }
    else
    {
        rt_kprintf("[mqtt] %s: %d\n", status, result);
    }

    rt_enter_critical();
    callback = gd32vw553_mqtt_status_callback;
    rt_exit_critical();
    if (callback != RT_NULL)
    {
        callback(status, result);
    }
}

static rt_bool_t gd32vw553_mqtt_running_get(void)
{
    rt_bool_t running;

    if (gd32vw553_mqtt_lock == RT_NULL)
    {
        return RT_FALSE;
    }

    rt_mutex_take(gd32vw553_mqtt_lock, RT_WAITING_FOREVER);
    running = gd32vw553_mqtt_running;
    rt_mutex_release(gd32vw553_mqtt_lock);

    return running;
}

static void gd32vw553_mqtt_strncpy(char *dst, const char *src, rt_size_t dst_size)
{
    if (dst_size == 0)
    {
        return;
    }

    rt_strncpy(dst, src, dst_size - 1);
    dst[dst_size - 1] = '\0';
}

static void gd32vw553_mqtt_sub_callback(void *client, message_data_t *msg)
{
    RT_UNUSED(client);

    if (msg == RT_NULL || msg->message == RT_NULL)
    {
        return;
    }

    rt_kprintf("mqtt recv topic: %s\n", msg->topic_name);
    rt_kprintf("mqtt recv payload: %.*s\n",
               (int)msg->message->payloadlen, (char *)msg->message->payload);

    if (gd32vw553_mqtt_receive_callback != RT_NULL)
    {
        gd32vw553_mqtt_receive_callback(msg->topic_name,
                                        msg->message->payload,
                                        msg->message->payloadlen);
    }
}

static int gd32vw553_mqtt_publish_text(mqtt_client_t *client, const char *topic, const char *payload)
{
    mqtt_message_t msg;

    rt_memset(&msg, 0, sizeof(msg));
    msg.qos = QOS0;
    msg.payload = (void *)payload;
    msg.payloadlen = rt_strlen(payload);

    return mqtt_publish(client, topic, &msg);
}

static rt_bool_t gd32vw553_mqtt_netdev_is_ready(struct at_device *device)
{
    struct netdev *netdev;

    if (device == RT_NULL || device->netdev == RT_NULL)
    {
        return RT_FALSE;
    }

    netdev = device->netdev;
    return (netdev_is_up(netdev) && netdev_is_link_up(netdev) &&
            !ip_addr_isany(&netdev->ip_addr)) ? RT_TRUE : RT_FALSE;
}

static rt_bool_t gd32vw553_mqtt_wait_netdev_ready(struct at_device *device)
{
    int waited;

    for (waited = 0; waited < GD32VW553_MQTT_WIFI_WAIT_MS; waited += 500)
    {
        if (gd32vw553_mqtt_netdev_is_ready(device))
        {
            return RT_TRUE;
        }

        if ((waited % GD32VW553_MQTT_WIFI_LOG_MS) == 0)
        {
            struct netdev *netdev = device->netdev;

            rt_kprintf("[mqtt] %s state: init=%d up=%d link=%d ip=%s\n",
                       GD32VW553_SAMPLE_DEVICE_NAME,
                       device->is_init ? 1 : 0,
                       (netdev != RT_NULL && netdev_is_up(netdev)) ? 1 : 0,
                       (netdev != RT_NULL && netdev_is_link_up(netdev)) ? 1 : 0,
                       (netdev != RT_NULL && !ip_addr_isany(&netdev->ip_addr)) ?
                       inet_ntoa(netdev->ip_addr) : "0.0.0.0");
        }

        rt_thread_mdelay(500);
    }

    return RT_FALSE;
}

static int gd32vw553_mqtt_prepare_wifi(struct at_device **device_out)
{
    struct at_device *device;

    *device_out = RT_NULL;
    device = at_device_get_by_name(AT_DEVICE_NAMETYPE_DEVICE, GD32VW553_SAMPLE_DEVICE_NAME);
    if (device == RT_NULL)
    {
        return -RT_ENOSYS;
    }
    *device_out = device;

    if (gd32vw553_mqtt_wait_netdev_ready(device) == RT_FALSE)
    {
        return -RT_ETIMEOUT;
    }

    return RT_EOK;
}

static const char *gd32vw553_mqtt_wifi_error(struct at_device *device)
{
    if (device == RT_NULL || device->netdev == RT_NULL)
    {
        return "GD32VW553 network interface is unavailable";
    }
    if (device->is_init == RT_FALSE)
    {
        return "GD32VW553 AT initialization failed or is incomplete";
    }
    if (!netdev_is_up(device->netdev))
    {
        return "GD32VW553 network interface is down";
    }
    if (!netdev_is_link_up(device->netdev))
    {
        return "GD32VW553 Wi-Fi AP is not connected";
    }
    if (ip_addr_isany(&device->netdev->ip_addr))
    {
        return "GD32VW553 Wi-Fi has no IPv4 address";
    }

    return "GD32VW553 Wi-Fi is not ready";
}

static const char *gd32vw553_mqtt_connect_error(int result)
{
    switch (result)
    {
    case KAWAII_MQTT_SOCKET_UNKNOWN_HOST_ERROR:
        return "MQTT broker DNS lookup failed";
    case KAWAII_MQTT_SOCKET_FAILED_ERROR:
        return "MQTT socket creation failed";
    case KAWAII_MQTT_CONNECT_FAILED_ERROR:
        return "MQTT broker TCP or protocol connection failed";
    default:
        return "MQTT broker connection failed";
    }
}

static void gd32vw553_mqtt_thread_entry(void *parameter)
{
    struct gd32vw553_mqtt_arg *arg = (struct gd32vw553_mqtt_arg *)parameter;
    struct at_device *device = RT_NULL;
    struct netdev *saved_default_netdev = RT_NULL;
    mqtt_client_t *client;
    int result;
    rt_bool_t failure_reported = RT_FALSE;
    rt_bool_t default_netdev_changed = RT_FALSE;

    gd32vw553_mqtt_report_status("Waiting for GD32VW553 Wi-Fi", RT_EOK);
    result = gd32vw553_mqtt_prepare_wifi(&device);
    if (result != RT_EOK)
    {
        gd32vw553_mqtt_report_status(
            result == -RT_ENOSYS ? "GD32VW553 AT device is unavailable" :
                                   gd32vw553_mqtt_wifi_error(device),
            result);
        failure_reported = RT_TRUE;
        goto __exit;
    }

    saved_default_netdev = netdev_default;
    if (device->netdev != netdev_default)
    {
        netdev_set_default(device->netdev);
        default_netdev_changed = RT_TRUE;
    }
    rt_kprintf("[mqtt] SAL netdev: %s\n", device->netdev->name);

    mqtt_log_init();

    client = mqtt_lease();
    if (client == RT_NULL)
    {
        gd32vw553_mqtt_report_status("MQTT client allocation failed", -RT_ENOMEM);
        failure_reported = RT_TRUE;
        goto __exit;
    }

    mqtt_set_host(client, arg->host);
    mqtt_set_port(client, arg->port);
    mqtt_set_client_id(client, arg->client_id);
    mqtt_set_clean_session(client, 1);
    mqtt_set_cmd_timeout(client, GD32VW553_MQTT_CMD_TIMEOUT_MS);

    if (arg->username[0] != '\0')
    {
        mqtt_set_user_name(client, arg->username);
    }
    if (arg->mqtt_password[0] != '\0')
    {
        mqtt_set_password(client, arg->mqtt_password);
    }

    gd32vw553_mqtt_report_status("Connecting to MQTT broker", RT_EOK);
    result = mqtt_connect(client);
    if (result != KAWAII_MQTT_SUCCESS_ERROR)
    {
        gd32vw553_mqtt_report_status(gd32vw553_mqtt_connect_error(result), result);
        failure_reported = RT_TRUE;
        client->mqtt_client_state = CLIENT_STATE_INVALID;
        mqtt_release(client);
        goto __exit;
    }

    result = mqtt_subscribe(client, arg->sub_topic, QOS0, gd32vw553_mqtt_sub_callback);
    if (result != KAWAII_MQTT_SUCCESS_ERROR)
    {
        gd32vw553_mqtt_report_status("MQTT subscription failed", result);
        failure_reported = RT_TRUE;
        mqtt_disconnect(client);
        mqtt_release(client);
        goto __exit;
    }

    rt_mutex_take(gd32vw553_mqtt_lock, RT_WAITING_FOREVER);
    gd32vw553_mqtt_client = client;
    rt_mutex_release(gd32vw553_mqtt_lock);

    rt_kprintf("GD32VW553 MQTT connected to %s:%s\n", arg->host, arg->port);
    rt_kprintf("mqtt subscribed: %s\n", arg->sub_topic);
    gd32vw553_mqtt_report_status("MQTT connected and subscribed", RT_EOK);

    while (gd32vw553_mqtt_running_get())
    {
        rt_thread_mdelay(100);
    }

    rt_mutex_take(gd32vw553_mqtt_lock, RT_WAITING_FOREVER);
    gd32vw553_mqtt_client = RT_NULL;
    rt_mutex_release(gd32vw553_mqtt_lock);

    mqtt_set_cmd_timeout(client, GD32VW553_MQTT_STOP_TIMEOUT_MS);
    mqtt_disconnect(client);
    mqtt_release(client);

__exit:
    if (default_netdev_changed && saved_default_netdev != RT_NULL &&
        netdev_default == device->netdev)
    {
        netdev_set_default(saved_default_netdev);
    }

    rt_mutex_take(gd32vw553_mqtt_lock, RT_WAITING_FOREVER);
    gd32vw553_mqtt_running = RT_FALSE;
    rt_mutex_release(gd32vw553_mqtt_lock);

    rt_free(arg);
    if (!failure_reported)
    {
        gd32vw553_mqtt_report_status("MQTT stopped", RT_EOK);
    }
}

int gd32vw553_mqtt_demo_start(void)
{
    rt_thread_t tid;
    struct gd32vw553_mqtt_arg *arg;
    const char *host = BSP_GD32VW553_MQTT_HOST;
    const char *port_string = GD32VW553_MQTT_STR(BSP_GD32VW553_MQTT_PORT);

    if (host[0] == '\0' ||
        BSP_GD32VW553_MQTT_SUB_TOPIC[0] == '\0' ||
        BSP_GD32VW553_MQTT_PUB_TOPIC[0] == '\0' ||
        BSP_GD32VW553_MQTT_CLIENT_ID[0] == '\0')
    {
        rt_kprintf("please configure GD32VW553 MQTT demo in menuconfig first\n");
        return -RT_EINVAL;
    }

    if (gd32vw553_mqtt_lock == RT_NULL)
    {
        gd32vw553_mqtt_lock = rt_mutex_create("vw553mq", RT_IPC_FLAG_PRIO);
        if (gd32vw553_mqtt_lock == RT_NULL)
        {
            return -RT_ENOMEM;
        }
    }

    rt_mutex_take(gd32vw553_mqtt_lock, RT_WAITING_FOREVER);
    if (gd32vw553_mqtt_client != RT_NULL || gd32vw553_mqtt_running == RT_TRUE)
    {
        rt_mutex_release(gd32vw553_mqtt_lock);
        rt_kprintf("GD32VW553 MQTT demo is already running\n");
        return -RT_EBUSY;
    }
    gd32vw553_mqtt_running = RT_TRUE;
    rt_mutex_release(gd32vw553_mqtt_lock);

    arg = (struct gd32vw553_mqtt_arg *)rt_calloc(1, sizeof(struct gd32vw553_mqtt_arg));
    if (arg == RT_NULL)
    {
        rt_mutex_take(gd32vw553_mqtt_lock, RT_WAITING_FOREVER);
        gd32vw553_mqtt_running = RT_FALSE;
        rt_mutex_release(gd32vw553_mqtt_lock);
        return -RT_ENOMEM;
    }

    gd32vw553_mqtt_strncpy(arg->host, host, sizeof(arg->host));
    gd32vw553_mqtt_strncpy(arg->port, port_string, sizeof(arg->port));
    gd32vw553_mqtt_strncpy(arg->sub_topic, BSP_GD32VW553_MQTT_SUB_TOPIC, sizeof(arg->sub_topic));
    gd32vw553_mqtt_strncpy(arg->pub_topic, BSP_GD32VW553_MQTT_PUB_TOPIC, sizeof(arg->pub_topic));
    gd32vw553_mqtt_strncpy(arg->message, BSP_GD32VW553_MQTT_MESSAGE, sizeof(arg->message));
    gd32vw553_mqtt_strncpy(arg->client_id, BSP_GD32VW553_MQTT_CLIENT_ID, sizeof(arg->client_id));
    gd32vw553_mqtt_strncpy(arg->username, BSP_GD32VW553_MQTT_USERNAME, sizeof(arg->username));
    gd32vw553_mqtt_strncpy(arg->mqtt_password, BSP_GD32VW553_MQTT_PASSWORD, sizeof(arg->mqtt_password));

    tid = rt_thread_create("vw553mqtt", gd32vw553_mqtt_thread_entry, arg,
                           GD32VW553_MQTT_STACK_SIZE, GD32VW553_MQTT_PRIORITY, 10);
    if (tid == RT_NULL)
    {
        rt_mutex_take(gd32vw553_mqtt_lock, RT_WAITING_FOREVER);
        gd32vw553_mqtt_running = RT_FALSE;
        rt_mutex_release(gd32vw553_mqtt_lock);
        rt_free(arg);
        return -RT_ERROR;
    }

    if (rt_thread_startup(tid) != RT_EOK)
    {
        rt_thread_delete(tid);
        rt_mutex_take(gd32vw553_mqtt_lock, RT_WAITING_FOREVER);
        gd32vw553_mqtt_running = RT_FALSE;
        rt_mutex_release(gd32vw553_mqtt_lock);
        rt_free(arg);
        return -RT_ERROR;
    }
    rt_kprintf("[mqtt] MQTT worker started\n");
    return RT_EOK;
}

static int gd32vw553_mqtt_start(int argc, char **argv)
{
    RT_UNUSED(argv);

    if (argc != 1)
    {
        rt_kprintf("usage: gd32vw553_mqtt_start\n");
        return -RT_EINVAL;
    }

    return gd32vw553_mqtt_demo_start();
}
MSH_CMD_EXPORT(gd32vw553_mqtt_start, start GD32VW553 MQTT demo with kawaii-mqtt);

int gd32vw553_mqtt_demo_publish(const char *topic, const char *payload)
{
    mqtt_client_t *client;
    int result;

    if ((topic == RT_NULL) || (payload == RT_NULL) ||
        (topic[0] == '\0') || (payload[0] == '\0'))
    {
        return -RT_EINVAL;
    }

    if ((rt_strlen(topic) >= GD32VW553_MQTT_TOPIC_LEN) ||
        (rt_strlen(payload) >= GD32VW553_MQTT_MSG_LEN))
    {
        rt_kprintf("MQTT topic or payload is too long\n");
        return -RT_EINVAL;
    }

    if (gd32vw553_mqtt_lock == RT_NULL)
    {
        rt_kprintf("GD32VW553 MQTT demo is not running\n");
        return -RT_ERROR;
    }

    rt_mutex_take(gd32vw553_mqtt_lock, RT_WAITING_FOREVER);
    if (gd32vw553_mqtt_running == RT_FALSE)
    {
        rt_mutex_release(gd32vw553_mqtt_lock);
        rt_kprintf("GD32VW553 MQTT demo is not running\n");
        return -RT_ERROR;
    }
    client = gd32vw553_mqtt_client;
    if (client == RT_NULL)
    {
        rt_mutex_release(gd32vw553_mqtt_lock);
        rt_kprintf("GD32VW553 MQTT demo is not connected\n");
        return -RT_ERROR;
    }

    rt_kprintf("[mqtt] publishing: %s (%u bytes)\n",
               topic, (unsigned int)rt_strlen(payload));
    gd32vw553_mqtt_report_status("Sending MQTT message", RT_EOK);
    result = gd32vw553_mqtt_publish_text(client, topic, payload);
    rt_mutex_release(gd32vw553_mqtt_lock);

    if (result == KAWAII_MQTT_SUCCESS_ERROR)
    {
        rt_kprintf("mqtt published: %s -> %s\n", topic, payload);
        gd32vw553_mqtt_report_status("MQTT message published", RT_EOK);
        return RT_EOK;
    }

    rt_kprintf("[mqtt] publish failed: topic=%s result=%d\n", topic, result);
    gd32vw553_mqtt_report_status("MQTT publish failed", result);

    return result;
}

static int gd32vw553_mqtt_pub(int argc, char **argv)
{
    if (argc < 3)
    {
        rt_kprintf("usage: gd32vw553_mqtt_pub <topic> <message>\n");
        return -RT_EINVAL;
    }

    return gd32vw553_mqtt_demo_publish(argv[1], argv[2]);
}
MSH_CMD_EXPORT(gd32vw553_mqtt_pub, publish through GD32VW553 MQTT demo);

int gd32vw553_mqtt_demo_stop(void)
{
    if (gd32vw553_mqtt_lock == RT_NULL)
    {
        rt_kprintf("GD32VW553 MQTT demo is not running\n");
        return -RT_ERROR;
    }

    rt_mutex_take(gd32vw553_mqtt_lock, RT_WAITING_FOREVER);
    gd32vw553_mqtt_running = RT_FALSE;
    rt_mutex_release(gd32vw553_mqtt_lock);

    rt_kprintf("GD32VW553 MQTT demo stopping\n");
    return RT_EOK;
}

static int gd32vw553_mqtt_stop(int argc, char **argv)
{
    RT_UNUSED(argc);
    RT_UNUSED(argv);

    return gd32vw553_mqtt_demo_stop();
}
MSH_CMD_EXPORT(gd32vw553_mqtt_stop, stop GD32VW553 MQTT demo);

rt_bool_t gd32vw553_mqtt_demo_is_running(void)
{
    return gd32vw553_mqtt_running_get();
}

rt_bool_t gd32vw553_mqtt_demo_is_connected(void)
{
    rt_bool_t connected;

    if (gd32vw553_mqtt_lock == RT_NULL)
    {
        return RT_FALSE;
    }

    rt_mutex_take(gd32vw553_mqtt_lock, RT_WAITING_FOREVER);
    connected = (gd32vw553_mqtt_client != RT_NULL) ? RT_TRUE : RT_FALSE;
    rt_mutex_release(gd32vw553_mqtt_lock);
    return connected;
}

void gd32vw553_mqtt_demo_set_receive_callback(
    gd32vw553_mqtt_receive_callback_t callback)
{
    rt_enter_critical();
    gd32vw553_mqtt_receive_callback = callback;
    rt_exit_critical();
}

void gd32vw553_mqtt_demo_set_status_callback(
    gd32vw553_mqtt_status_callback_t callback)
{
    rt_enter_critical();
    gd32vw553_mqtt_status_callback = callback;
    rt_exit_critical();
}

#endif /* BSP_USING_GD32VW553_MQTT_DEMO && PKG_USING_KAWAII_MQTT */
